begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolve.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolveoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|FIELD_COLS
define|#
directive|define
name|FIELD_COLS
value|4
end_define

begin_define
DECL|macro|MIN_BLUR
define|#
directive|define
name|MIN_BLUR
value|64
end_define

begin_comment
DECL|macro|MIN_BLUR
comment|/*  (8/9 original pixel)   */
end_comment

begin_define
DECL|macro|MAX_BLUR
define|#
directive|define
name|MAX_BLUR
value|0.25
end_define

begin_comment
DECL|macro|MAX_BLUR
comment|/*  (1/33 original pixel)  */
end_comment

begin_define
DECL|macro|MIN_SHARPEN
define|#
directive|define
name|MIN_SHARPEN
value|-512
end_define

begin_define
DECL|macro|MAX_SHARPEN
define|#
directive|define
name|MAX_SHARPEN
value|-64
end_define

begin_comment
comment|/* Different clip relationships between a blur-blob and edges:  * see convolve_motion  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a1cec230103
block|{
DECL|enumerator|CONVOLVE_NCLIP
name|CONVOLVE_NCLIP
block|,
comment|/* Left or top edge     */
DECL|enumerator|CONVOLVE_NOT_CLIPPED
name|CONVOLVE_NOT_CLIPPED
block|,
comment|/* No edges             */
DECL|enumerator|CONVOLVE_PCLIP
name|CONVOLVE_PCLIP
comment|/* Right or bottom edge */
DECL|typedef|ConvolveClipType
block|}
name|ConvolveClipType
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_convolve_class_init
parameter_list|(
name|GimpConvolveClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_init
parameter_list|(
name|GimpConvolve
modifier|*
name|convolve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintCoreState
name|paint_state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_calculate_matrix
parameter_list|(
name|GimpConvolveType
name|type
parameter_list|,
name|gdouble
name|rate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_integer_matrix
parameter_list|(
name|gfloat
modifier|*
name|source
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_convolve_copy_matrix
parameter_list|(
name|gfloat
modifier|*
name|src
parameter_list|,
name|gfloat
modifier|*
name|dest
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_convolve_sum_matrix
parameter_list|(
name|gint
modifier|*
name|matrix
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|matrix
specifier|static
name|gint
name|matrix
index|[
literal|25
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|matrix_size
specifier|static
name|gint
name|matrix_size
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|matrix_divisor
specifier|static
name|gint
name|matrix_divisor
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|custom_matrix
specifier|static
name|gfloat
name|custom_matrix
index|[
literal|25
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blur_matrix
specifier|static
name|gfloat
name|blur_matrix
index|[
literal|25
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
name|MIN_BLUR
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sharpen_matrix
specifier|static
name|gfloat
name|sharpen_matrix
index|[
literal|25
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
name|MIN_SHARPEN
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|1
block|,
literal|1
block|,
literal|1
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintCoreClass
modifier|*
name|parent_class
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_convolve_register (Gimp * gimp,GimpPaintRegisterCallback callback)
name|gimp_convolve_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_CONVOLVE
argument_list|,
name|GIMP_TYPE_CONVOLVE_OPTIONS
argument_list|,
name|_
argument_list|(
literal|"Convolve"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_convolve_get_type (void)
name|gimp_convolve_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpConvolveClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_convolve_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpConvolve
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_convolve_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_CORE
argument_list|,
literal|"GimpConvolve"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_class_init (GimpConvolveClass * klass)
name|gimp_convolve_class_init
parameter_list|(
name|GimpConvolveClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
decl_stmt|;
name|paint_core_class
operator|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_convolve_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_init (GimpConvolve * convolve)
name|gimp_convolve_init
parameter_list|(
name|GimpConvolve
modifier|*
name|convolve
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintCoreState paint_state)
name|gimp_convolve_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintCoreState
name|paint_state
parameter_list|)
block|{
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|MOTION_PAINT
case|:
name|gimp_convolve_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options)
name|gimp_convolve_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
block|{
name|GimpConvolveOptions
modifier|*
name|options
decl_stmt|;
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|guchar
modifier|*
name|temp_data
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|gdouble
name|rate
decl_stmt|;
name|ConvolveClipType
name|area_hclip
init|=
name|CONVOLVE_NOT_CLIPPED
decl_stmt|;
name|ConvolveClipType
name|area_vclip
init|=
name|CONVOLVE_NOT_CLIPPED
decl_stmt|;
name|gint
name|marginx
init|=
literal|0
decl_stmt|;
name|gint
name|marginy
init|=
literal|0
decl_stmt|;
name|options
operator|=
name|GIMP_CONVOLVE_OPTIONS
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
name|pressure_options
operator|=
name|paint_options
operator|->
name|pressure_options
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|)
condition|)
return|return;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
comment|/* If the brush is smaller than the convolution matrix, don't convolve */
if|if
condition|(
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|<
name|matrix_size
operator|||
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|<
name|matrix_size
condition|)
return|return;
name|opacity
operator|=
name|gimp_paint_options_get_fade
argument_list|(
name|paint_options
argument_list|,
name|gimage
argument_list|,
name|paint_core
operator|->
name|pixel_dist
argument_list|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|==
literal|0.0
condition|)
return|return;
if|if
condition|(
name|pressure_options
operator|->
name|size
condition|)
name|scale
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
else|else
name|scale
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|scale
argument_list|)
operator|)
condition|)
return|return;
comment|/*  configure the source pixel region  */
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|gimp_drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  configure the destination pixel region  */
name|destPR
operator|.
name|bytes
operator|=
name|area
operator|->
name|bytes
expr_stmt|;
name|destPR
operator|.
name|tiles
operator|=
name|NULL
expr_stmt|;
name|destPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|destPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|destPR
operator|.
name|rowstride
operator|=
name|area
operator|->
name|width
operator|*
name|destPR
operator|.
name|bytes
expr_stmt|;
name|destPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|rate
operator|=
name|options
operator|->
name|rate
expr_stmt|;
if|if
condition|(
name|pressure_options
operator|->
name|rate
condition|)
name|rate
operator|*=
literal|2.0
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
name|gimp_convolve_calculate_matrix
argument_list|(
name|options
operator|->
name|type
argument_list|,
name|rate
argument_list|)
expr_stmt|;
comment|/*  Image region near edges? If so, paint area will be clipped   */
comment|/*  with respect to brush mask + 1 pixel border (# 19285)        */
if|if
condition|(
operator|(
name|marginx
operator|=
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
operator|-
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
literal|2
operator|-
literal|1
operator|)
operator|!=
name|area
operator|->
name|x
condition|)
name|area_hclip
operator|=
name|CONVOLVE_NCLIP
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|marginx
operator|=
name|area
operator|->
name|width
operator|-
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|-
literal|2
operator|)
operator|!=
literal|0
condition|)
name|area_hclip
operator|=
name|CONVOLVE_PCLIP
expr_stmt|;
if|if
condition|(
operator|(
name|marginy
operator|=
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
operator|-
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
literal|2
operator|-
literal|1
operator|)
operator|!=
name|area
operator|->
name|y
condition|)
name|area_vclip
operator|=
name|CONVOLVE_NCLIP
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|marginy
operator|=
name|area
operator|->
name|height
operator|-
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|-
literal|2
operator|)
operator|!=
literal|0
condition|)
name|area_vclip
operator|=
name|CONVOLVE_PCLIP
expr_stmt|;
comment|/*  Has the TempBuf been clipped by a canvas edge or two?  */
if|if
condition|(
name|area_hclip
operator|==
name|CONVOLVE_NOT_CLIPPED
operator|&&
name|area_vclip
operator|==
name|CONVOLVE_NOT_CLIPPED
condition|)
block|{
comment|/* No clipping...                                              */
comment|/* Standard case: copy src to temp. convolve temp to dest.     */
comment|/* Brush defines pipe size and no edge adjustments are needed. */
comment|/*  If the source has no alpha, then add alpha pixels          */
comment|/*  Because paint_core.c is alpha-only code. See below.        */
name|PixelRegion
name|tempPR
decl_stmt|;
name|tempPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|tiles
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
comment|/* note: this particular approach needlessly convolves the totally- 	     opaque alpha channel. A faster approach would be to keep 	     tempPR the same number of bytes as srcPR, and extend the 	     paint_core_replace_canvas API to handle non-alpha images. */
name|tempPR
operator|.
name|bytes
operator|=
name|srcPR
operator|.
name|bytes
operator|+
literal|1
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|tempPR
operator|.
name|bytes
operator|*
name|tempPR
operator|.
name|w
expr_stmt|;
name|temp_data
operator|=
name|g_malloc
argument_list|(
name|tempPR
operator|.
name|h
operator|*
name|tempPR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|temp_data
expr_stmt|;
name|add_alpha_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|tempPR
operator|.
name|bytes
operator|=
name|srcPR
operator|.
name|bytes
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|tempPR
operator|.
name|bytes
operator|*
name|tempPR
operator|.
name|w
expr_stmt|;
name|temp_data
operator|=
name|g_malloc
argument_list|(
name|tempPR
operator|.
name|h
operator|*
name|tempPR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|temp_data
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
block|}
comment|/*  Convolve the region  */
name|tempPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|temp_data
expr_stmt|;
name|convolve_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|matrix
argument_list|,
name|matrix_size
argument_list|,
name|matrix_divisor
argument_list|,
name|GIMP_NORMAL_CONVOL
argument_list|)
expr_stmt|;
comment|/*  Free the allocated temp space  */
name|g_free
argument_list|(
name|temp_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* TempBuf clipping has occured on at least one edge...        * Edge case: expand area under brush margin px on near edge(s), convolve        * expanded buffers. copy src -> ovrsz1 convolve ovrsz1 -> ovrsz2        * copy-with-crop ovrsz2 -> dest        */
name|PixelRegion
name|ovrsz1PR
decl_stmt|;
name|PixelRegion
name|ovrsz2PR
decl_stmt|;
name|guchar
modifier|*
name|ovrsz1_data
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|ovrsz2_data
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|fillcolor
decl_stmt|;
name|fillcolor
operator|=
name|gimp_drawable_get_color_at
argument_list|(
name|drawable
argument_list|,
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|cur_coords
operator|.
name|x
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|-
literal|1
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|cur_coords
operator|.
name|y
argument_list|,
literal|0
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|marginx
operator|*=
operator|(
name|marginx
operator|<
literal|0
operator|)
condition|?
operator|-
literal|1
else|:
literal|0
expr_stmt|;
name|marginy
operator|*=
operator|(
name|marginy
operator|<
literal|0
operator|)
condition|?
operator|-
literal|1
else|:
literal|0
expr_stmt|;
name|ovrsz2PR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|ovrsz2PR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|ovrsz2PR
operator|.
name|w
operator|=
name|area
operator|->
name|width
operator|+
name|marginx
expr_stmt|;
name|ovrsz2PR
operator|.
name|h
operator|=
name|area
operator|->
name|height
operator|+
name|marginy
expr_stmt|;
name|ovrsz2PR
operator|.
name|bytes
operator|=
operator|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|?
name|srcPR
operator|.
name|bytes
else|:
name|srcPR
operator|.
name|bytes
operator|+
literal|1
operator|)
expr_stmt|;
name|ovrsz2PR
operator|.
name|offx
operator|=
literal|0
expr_stmt|;
name|ovrsz2PR
operator|.
name|offy
operator|=
literal|0
expr_stmt|;
name|ovrsz2PR
operator|.
name|rowstride
operator|=
name|ovrsz2PR
operator|.
name|bytes
operator|*
name|ovrsz2PR
operator|.
name|w
expr_stmt|;
name|ovrsz2PR
operator|.
name|tiles
operator|=
name|NULL
expr_stmt|;
name|ovrsz2_data
operator|=
name|g_malloc
argument_list|(
name|ovrsz2PR
operator|.
name|h
operator|*
name|ovrsz2PR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
name|ovrsz2PR
operator|.
name|data
operator|=
name|ovrsz2_data
expr_stmt|;
name|ovrsz1PR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|w
operator|=
name|area
operator|->
name|width
operator|+
name|marginx
expr_stmt|;
name|ovrsz1PR
operator|.
name|h
operator|=
name|area
operator|->
name|height
operator|+
name|marginy
expr_stmt|;
name|ovrsz1PR
operator|.
name|bytes
operator|=
operator|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|?
name|srcPR
operator|.
name|bytes
else|:
name|srcPR
operator|.
name|bytes
operator|+
literal|1
operator|)
expr_stmt|;
name|ovrsz1PR
operator|.
name|offx
operator|=
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|offy
operator|=
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|rowstride
operator|=
name|ovrsz2PR
operator|.
name|bytes
operator|*
name|ovrsz2PR
operator|.
name|w
expr_stmt|;
name|ovrsz1PR
operator|.
name|tiles
operator|=
name|NULL
expr_stmt|;
name|ovrsz1_data
operator|=
name|g_malloc
argument_list|(
name|ovrsz1PR
operator|.
name|h
operator|*
name|ovrsz1PR
operator|.
name|rowstride
argument_list|)
expr_stmt|;
name|ovrsz1PR
operator|.
name|data
operator|=
name|ovrsz1_data
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|ovrsz1PR
argument_list|,
name|fillcolor
argument_list|)
expr_stmt|;
name|ovrsz1PR
operator|.
name|x
operator|=
operator|(
name|area_hclip
operator|==
name|CONVOLVE_NCLIP
operator|)
condition|?
name|marginx
else|:
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|y
operator|=
operator|(
name|area_vclip
operator|==
name|CONVOLVE_NCLIP
operator|)
condition|?
name|marginy
else|:
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|ovrsz1PR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|ovrsz1PR
operator|.
name|data
operator|=
operator|(
name|ovrsz1_data
operator|+
operator|(
name|ovrsz1PR
operator|.
name|rowstride
operator|*
name|ovrsz1PR
operator|.
name|y
operator|)
operator|+
operator|(
name|ovrsz1PR
operator|.
name|bytes
operator|*
name|ovrsz1PR
operator|.
name|x
operator|)
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|add_alpha_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|ovrsz1PR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|ovrsz1PR
argument_list|)
expr_stmt|;
comment|/*  Convolve the region  */
name|ovrsz1PR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|ovrsz1PR
operator|.
name|w
operator|=
name|area
operator|->
name|width
operator|+
name|marginx
expr_stmt|;
name|ovrsz1PR
operator|.
name|h
operator|=
name|area
operator|->
name|height
operator|+
name|marginy
expr_stmt|;
name|ovrsz1PR
operator|.
name|data
operator|=
name|ovrsz1_data
expr_stmt|;
name|convolve_region
argument_list|(
operator|&
name|ovrsz1PR
argument_list|,
operator|&
name|ovrsz2PR
argument_list|,
name|matrix
argument_list|,
name|matrix_size
argument_list|,
name|matrix_divisor
argument_list|,
name|GIMP_NORMAL_CONVOL
argument_list|)
expr_stmt|;
comment|/* Crop and copy to destination */
name|ovrsz2PR
operator|.
name|x
operator|=
operator|(
name|area_hclip
operator|==
name|CONVOLVE_NCLIP
operator|)
condition|?
name|marginx
else|:
literal|0
expr_stmt|;
name|ovrsz2PR
operator|.
name|y
operator|=
operator|(
name|area_vclip
operator|==
name|CONVOLVE_NCLIP
operator|)
condition|?
name|marginy
else|:
literal|0
expr_stmt|;
name|ovrsz2PR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|ovrsz2PR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|ovrsz2PR
operator|.
name|data
operator|=
operator|(
name|ovrsz2_data
operator|+
operator|(
name|ovrsz2PR
operator|.
name|rowstride
operator|*
name|ovrsz2PR
operator|.
name|y
operator|)
operator|+
operator|(
name|ovrsz2PR
operator|.
name|bytes
operator|*
name|ovrsz2PR
operator|.
name|x
operator|)
operator|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|ovrsz2PR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ovrsz1_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ovrsz2_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|fillcolor
argument_list|)
expr_stmt|;
block|}
comment|/*  paste the newly painted canvas to the gimage which is being worked on  */
name|gimp_paint_core_replace_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|MIN
argument_list|(
name|opacity
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|scale
argument_list|,
name|GIMP_PAINT_INCREMENTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_calculate_matrix (GimpConvolveType type,gdouble rate)
name|gimp_convolve_calculate_matrix
parameter_list|(
name|GimpConvolveType
name|type
parameter_list|,
name|gdouble
name|rate
parameter_list|)
block|{
name|gfloat
name|percent
decl_stmt|;
comment|/*  find percent of tool pressure  */
name|percent
operator|=
name|MIN
argument_list|(
name|rate
operator|/
literal|100.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
comment|/*  get the appropriate convolution matrix and size and divisor  */
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_BLUR_CONVOLVE
case|:
name|matrix_size
operator|=
literal|5
expr_stmt|;
name|blur_matrix
index|[
literal|12
index|]
operator|=
name|MIN_BLUR
operator|+
name|percent
operator|*
operator|(
name|MAX_BLUR
operator|-
name|MIN_BLUR
operator|)
expr_stmt|;
name|gimp_convolve_copy_matrix
argument_list|(
name|blur_matrix
argument_list|,
name|custom_matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SHARPEN_CONVOLVE
case|:
name|matrix_size
operator|=
literal|5
expr_stmt|;
name|sharpen_matrix
index|[
literal|12
index|]
operator|=
name|MIN_SHARPEN
operator|+
name|percent
operator|*
operator|(
name|MAX_SHARPEN
operator|-
name|MIN_SHARPEN
operator|)
expr_stmt|;
name|gimp_convolve_copy_matrix
argument_list|(
name|sharpen_matrix
argument_list|,
name|custom_matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CUSTOM_CONVOLVE
case|:
name|matrix_size
operator|=
literal|5
expr_stmt|;
break|break;
block|}
name|gimp_convolve_integer_matrix
argument_list|(
name|custom_matrix
argument_list|,
name|matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
name|matrix_divisor
operator|=
name|gimp_convolve_sum_matrix
argument_list|(
name|matrix
argument_list|,
name|matrix_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|matrix_divisor
condition|)
name|matrix_divisor
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_integer_matrix (gfloat * source,gint * dest,gint size)
name|gimp_convolve_integer_matrix
parameter_list|(
name|gfloat
modifier|*
name|source
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
DECL|macro|PRECISION
define|#
directive|define
name|PRECISION
value|10000
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|size
operator|*
name|size
condition|;
name|i
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
call|(
name|gint
call|)
argument_list|(
operator|*
name|source
operator|++
operator|*
name|PRECISION
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_copy_matrix (gfloat * src,gfloat * dest,gint size)
name|gimp_convolve_copy_matrix
parameter_list|(
name|gfloat
modifier|*
name|src
parameter_list|,
name|gfloat
modifier|*
name|dest
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|size
operator|*
name|size
condition|;
name|i
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_convolve_sum_matrix (gint * matrix,gint size)
name|gimp_convolve_sum_matrix
parameter_list|(
name|gint
modifier|*
name|matrix
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|gint
name|sum
init|=
literal|0
decl_stmt|;
name|size
operator|*=
name|size
expr_stmt|;
while|while
condition|(
name|size
operator|--
condition|)
name|sum
operator|+=
operator|*
name|matrix
operator|++
expr_stmt|;
return|return
name|sum
return|;
block|}
end_function

end_unit

