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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"core/gimpcontext.h"
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
file|"gimpsmudge.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_smudge_class_init
parameter_list|(
name|GimpSmudgeClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_init
parameter_list|(
name|GimpSmudge
modifier|*
name|smudge
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_paint
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
name|gboolean
name|gimp_smudge_start
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPressureOptions
modifier|*
name|pressure_options
parameter_list|,
name|gdouble
name|smudge_rate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_finish
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_nonclipped_painthit_coords
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_smudge_allocate_accum_buffer
parameter_list|(
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|do_fill
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|accumPR
specifier|static
name|PixelRegion
name|accumPR
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|accum_data
specifier|static
name|guchar
modifier|*
name|accum_data
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintCoreClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_smudge_get_type (void)
name|gimp_smudge_get_type
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
name|GimpSmudgeClass
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
name|gimp_smudge_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpSmudge
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_smudge_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_CORE
argument_list|,
literal|"GimpSmudge"
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
DECL|function|gimp_smudge_class_init (GimpSmudgeClass * klass)
name|gimp_smudge_class_init
parameter_list|(
name|GimpSmudgeClass
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
name|gimp_smudge_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_init (GimpSmudge * smudge)
name|gimp_smudge_init
parameter_list|(
name|GimpSmudge
modifier|*
name|smudge
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|paint_core
decl_stmt|;
name|paint_core
operator|=
name|GIMP_PAINT_CORE
argument_list|(
name|smudge
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|flags
operator||=
name|CORE_HANDLES_CHANGING_BRUSH
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintCoreState paint_state)
name|gimp_smudge_paint
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
name|GimpSmudgeOptions
modifier|*
name|options
decl_stmt|;
comment|/* initialization fails if the user starts outside the drawable */
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|options
operator|=
operator|(
name|GimpSmudgeOptions
operator|*
operator|)
name|paint_options
expr_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|MOTION_PAINT
case|:
if|if
condition|(
operator|!
name|initialized
condition|)
name|initialized
operator|=
name|gimp_smudge_start
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|initialized
condition|)
name|gimp_smudge_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
operator|->
name|pressure_options
argument_list|,
name|options
operator|->
name|rate
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH_PAINT
case|:
name|gimp_smudge_finish
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|FALSE
expr_stmt|;
break|break;
default|default:
break|break;
block|}
return|return;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_smudge_start (GimpPaintCore * paint_core,GimpDrawable * drawable)
name|gimp_smudge_start
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|was_clipped
decl_stmt|;
name|guchar
modifier|*
name|do_fill
init|=
name|NULL
decl_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  If the image type is indexed, don't smudge  */
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|area
condition|)
return|return
name|FALSE
return|;
comment|/*  adjust the x and y coordinates to the upper left corner of the brush  */
name|gimp_smudge_nonclipped_painthit_coords
argument_list|(
name|paint_core
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|!=
name|area
operator|->
name|x
operator|||
name|y
operator|!=
name|area
operator|->
name|y
operator|||
name|w
operator|!=
name|area
operator|->
name|width
operator|||
name|h
operator|!=
name|area
operator|->
name|height
condition|)
name|was_clipped
operator|=
name|TRUE
expr_stmt|;
else|else
name|was_clipped
operator|=
name|FALSE
expr_stmt|;
comment|/* When clipped, accum_data may contain pixels that map to      off-canvas pixels of the under-the-brush image, particulary      when the brush image contains an edge or corner of the      image. These off-canvas pixels are not a part of the current      composite, but may be composited in later generations. do_fill      contains a copy of the color of the pixel at the center of the      brush; assumed this is a reasonable choice for off- canvas pixels      that may enter into the blend */
if|if
condition|(
name|was_clipped
condition|)
name|do_fill
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
name|gimp_drawable_width
argument_list|(
name|drawable
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
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_smudge_allocate_accum_buffer
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|do_fill
argument_list|)
expr_stmt|;
name|accumPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|accumPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
expr_stmt|;
name|accumPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|accumPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|accumPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|bytes
operator|*
name|w
expr_stmt|;
name|accumPR
operator|.
name|data
operator|=
name|accum_data
operator|+
name|accumPR
operator|.
name|rowstride
operator|*
name|accumPR
operator|.
name|y
operator|+
name|accumPR
operator|.
name|x
operator|*
name|accumPR
operator|.
name|bytes
expr_stmt|;
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
comment|/* copy the region under the original painthit. */
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|accumPR
argument_list|)
expr_stmt|;
name|accumPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|accumPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
expr_stmt|;
name|accumPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|accumPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|accumPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|bytes
operator|*
name|w
expr_stmt|;
name|accumPR
operator|.
name|data
operator|=
name|accum_data
operator|+
name|accumPR
operator|.
name|rowstride
operator|*
name|accumPR
operator|.
name|y
operator|+
name|accumPR
operator|.
name|x
operator|*
name|accumPR
operator|.
name|bytes
expr_stmt|;
if|if
condition|(
name|do_fill
condition|)
name|g_free
argument_list|(
name|do_fill
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPressureOptions * pressure_options,gdouble smudge_rate)
name|gimp_smudge_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPressureOptions
modifier|*
name|pressure_options
parameter_list|,
name|gdouble
name|smudge_rate
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|tempPR
decl_stmt|;
name|gdouble
name|rate
decl_stmt|;
name|gint
name|opacity
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  If the image type is indexed, don't smudge  */
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
name|gimp_smudge_nonclipped_painthit_coords
argument_list|(
name|paint_core
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
comment|/*  Get the paint area */
comment|/*  Smudge won't scale!  */
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
literal|1.0
argument_list|)
operator|)
condition|)
return|return;
comment|/* srcPR will be the pixels under the current painthit from       the drawable*/
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
comment|/* Enable pressure sensitive rate */
if|if
condition|(
name|pressure_options
operator|->
name|rate
condition|)
name|rate
operator|=
name|MIN
argument_list|(
name|smudge_rate
operator|/
literal|100.0
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
operator|*
literal|2.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
else|else
name|rate
operator|=
name|smudge_rate
operator|/
literal|100.0
expr_stmt|;
comment|/* The tempPR will be the built up buffer (for smudge) */
name|tempPR
operator|.
name|bytes
operator|=
name|accumPR
operator|.
name|bytes
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|rowstride
expr_stmt|;
name|tempPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
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
name|accum_data
operator|+
name|tempPR
operator|.
name|rowstride
operator|*
name|tempPR
operator|.
name|y
operator|+
name|tempPR
operator|.
name|x
operator|*
name|tempPR
operator|.
name|bytes
expr_stmt|;
comment|/* The dest will be the paint area we got above (= canvas_buf) */
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
name|area
operator|->
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
comment|/*        Smudge uses the buffer Accum.      For each successive painthit Accum is built like this 	Accum =  rate*Accum  + (1-rate)*I.      where I is the pixels under the current painthit.       Then the paint area (canvas_buf) is built as  	(Accum,1) (if no alpha),   */
name|blend_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|,
operator|&
name|tempPR
argument_list|,
name|ROUND
argument_list|(
name|rate
operator|*
literal|255.0
argument_list|)
argument_list|)
expr_stmt|;
comment|/* re-init the tempPR */
name|tempPR
operator|.
name|bytes
operator|=
name|accumPR
operator|.
name|bytes
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|rowstride
expr_stmt|;
name|tempPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
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
name|accum_data
operator|+
name|tempPR
operator|.
name|rowstride
operator|*
name|tempPR
operator|.
name|y
operator|+
name|tempPR
operator|.
name|x
operator|*
name|tempPR
operator|.
name|bytes
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
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|opacity
operator|=
literal|255
operator|*
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|pressure_options
operator|->
name|opacity
condition|)
name|opacity
operator|=
name|opacity
operator|*
literal|2.0
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
comment|/*Replace the newly made paint area to the gimage*/
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
literal|255
argument_list|)
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|pressure_options
operator|->
name|pressure
condition|?
name|PRESSURE
else|:
name|SOFT
argument_list|,
literal|1.0
argument_list|,
name|INCREMENTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_finish (GimpPaintCore * paint_core,GimpDrawable * drawable)
name|gimp_smudge_finish
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|accum_data
condition|)
block|{
name|g_free
argument_list|(
name|accum_data
argument_list|)
expr_stmt|;
name|accum_data
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_nonclipped_painthit_coords (GimpPaintCore * paint_core,gint * x,gint * y,gint * w,gint * h)
name|gimp_smudge_nonclipped_painthit_coords
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
parameter_list|)
block|{
comment|/* Note: these are the brush mask size plus a border of 1 pixel */
operator|*
name|x
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
expr_stmt|;
operator|*
name|y
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
expr_stmt|;
operator|*
name|w
operator|=
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|+
literal|2
expr_stmt|;
operator|*
name|h
operator|=
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|+
literal|2
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_smudge_allocate_accum_buffer (gint w,gint h,gint bytes,guchar * do_fill)
name|gimp_smudge_allocate_accum_buffer
parameter_list|(
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|do_fill
parameter_list|)
block|{
comment|/*  Allocate the accumulation buffer */
name|accumPR
operator|.
name|bytes
operator|=
name|bytes
expr_stmt|;
name|accum_data
operator|=
name|g_malloc
argument_list|(
name|w
operator|*
name|h
operator|*
name|bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|do_fill
operator|!=
name|NULL
condition|)
block|{
comment|/* guchar color[3] = {0,0,0}; */
name|accumPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|accumPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|accumPR
operator|.
name|w
operator|=
name|w
expr_stmt|;
name|accumPR
operator|.
name|h
operator|=
name|h
expr_stmt|;
name|accumPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|bytes
operator|*
name|w
expr_stmt|;
name|accumPR
operator|.
name|data
operator|=
name|accum_data
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|accumPR
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|do_fill
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  paint options stuff  */
end_comment

begin_define
DECL|macro|SMUDGE_DEFAULT_RATE
define|#
directive|define
name|SMUDGE_DEFAULT_RATE
value|50.0
end_define

begin_function
name|GimpSmudgeOptions
modifier|*
DECL|function|gimp_smudge_options_new (void)
name|gimp_smudge_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpSmudgeOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|GimpSmudgeOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_paint_options_init
argument_list|(
operator|(
name|GimpPaintOptions
operator|*
operator|)
name|options
argument_list|)
expr_stmt|;
name|options
operator|->
name|rate
operator|=
name|options
operator|->
name|rate_d
operator|=
name|SMUDGE_DEFAULT_RATE
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

end_unit

