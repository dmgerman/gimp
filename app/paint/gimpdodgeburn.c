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
file|"base/gimplut.h"
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
file|"gimpdodgeburn.h"
end_include

begin_include
include|#
directive|include
file|"gimpdodgeburnoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_dodge_burn_class_init
parameter_list|(
name|GimpDodgeBurnClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodge_burn_init
parameter_list|(
name|GimpDodgeBurn
modifier|*
name|dodgeburn
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodge_burn_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodge_burn_paint
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
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodge_burn_motion
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
name|gimp_dodge_burn_make_luts
parameter_list|(
name|GimpDodgeBurn
modifier|*
name|dodgeburn
parameter_list|,
name|gdouble
name|db_exposure
parameter_list|,
name|GimpDodgeBurnType
name|type
parameter_list|,
name|GimpTransferMode
name|mode
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gfloat
name|gimp_dodge_burn_highlights_lut_func
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gfloat
name|gimp_dodge_burn_midtones_lut_func
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gfloat
name|gimp_dodge_burn_shadows_lut_func
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpBrushCoreClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_dodge_burn_register (Gimp * gimp,GimpPaintRegisterCallback callback)
name|gimp_dodge_burn_register
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
name|GIMP_TYPE_DODGE_BURN
argument_list|,
name|GIMP_TYPE_DODGE_BURN_OPTIONS
argument_list|,
name|_
argument_list|(
literal|"Dodge/Burn"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_dodge_burn_get_type (void)
name|gimp_dodge_burn_get_type
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
name|GimpDodgeBurnClass
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
name|gimp_dodge_burn_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpDodgeBurn
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_dodge_burn_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_BRUSH_CORE
argument_list|,
literal|"GimpDodgeBurn"
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
DECL|function|gimp_dodge_burn_class_init (GimpDodgeBurnClass * klass)
name|gimp_dodge_burn_class_init
parameter_list|(
name|GimpDodgeBurnClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_dodge_burn_finalize
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_dodge_burn_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_init (GimpDodgeBurn * dodgeburn)
name|gimp_dodge_burn_init
parameter_list|(
name|GimpDodgeBurn
modifier|*
name|dodgeburn
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|paint_core
init|=
name|GIMP_PAINT_CORE
argument_list|(
name|dodgeburn
argument_list|)
decl_stmt|;
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
DECL|function|gimp_dodge_burn_finalize (GObject * object)
name|gimp_dodge_burn_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDodgeBurn
modifier|*
name|dodgeburn
init|=
name|GIMP_DODGE_BURN
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dodgeburn
operator|->
name|lut
condition|)
block|{
name|gimp_lut_free
argument_list|(
name|dodgeburn
operator|->
name|lut
argument_list|)
expr_stmt|;
name|dodgeburn
operator|->
name|lut
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintCoreState paint_state,guint32 time)
name|gimp_dodge_burn_paint
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
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpDodgeBurn
modifier|*
name|dodgeburn
init|=
name|GIMP_DODGE_BURN
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpDodgeBurnOptions
modifier|*
name|options
init|=
name|GIMP_DODGE_BURN_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|INIT_PAINT
case|:
name|dodgeburn
operator|->
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|gimp_dodge_burn_make_luts
argument_list|(
name|dodgeburn
argument_list|,
name|options
operator|->
name|exposure
argument_list|,
name|options
operator|->
name|type
argument_list|,
name|options
operator|->
name|mode
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|MOTION_PAINT
case|:
name|gimp_dodge_burn_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH_PAINT
case|:
if|if
condition|(
name|dodgeburn
operator|->
name|lut
condition|)
block|{
name|gimp_lut_free
argument_list|(
name|dodgeburn
operator|->
name|lut
argument_list|)
expr_stmt|;
name|dodgeburn
operator|->
name|lut
operator|=
name|NULL
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options)
name|gimp_dodge_burn_motion
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
name|GimpDodgeBurn
modifier|*
name|dodgeburn
init|=
name|GIMP_DODGE_BURN
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpPressureOptions
modifier|*
name|pressure_options
init|=
name|paint_options
operator|->
name|pressure_options
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|TempBuf
modifier|*
name|orig
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|tempPR
decl_stmt|;
name|guchar
modifier|*
name|temp_data
decl_stmt|;
name|gdouble
name|opacity
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
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
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
name|area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|area
condition|)
return|return;
comment|/* Constant painting --get a copy of the orig drawable (with no    * paint from this stroke yet)    */
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|x1
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|x
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|y
argument_list|,
literal|0
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|width
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|area
operator|->
name|y
operator|+
name|area
operator|->
name|height
argument_list|,
literal|0
argument_list|,
name|gimp_item_height
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|x2
operator|-
name|x1
operator|)
operator|||
operator|!
operator|(
name|y2
operator|-
name|y1
operator|)
condition|)
return|return;
comment|/*  get the original untouched image  */
name|orig
operator|=
name|gimp_paint_core_get_orig_image
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|srcPR
operator|.
name|bytes
operator|=
name|orig
operator|->
name|bytes
expr_stmt|;
name|srcPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|srcPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|srcPR
operator|.
name|w
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|srcPR
operator|.
name|h
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|srcPR
operator|.
name|rowstride
operator|=
name|srcPR
operator|.
name|bytes
operator|*
name|orig
operator|->
name|width
expr_stmt|;
name|srcPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|orig
argument_list|)
expr_stmt|;
block|}
comment|/* tempPR will hold the dodgeburned region */
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
name|x
operator|=
name|srcPR
operator|.
name|x
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
name|srcPR
operator|.
name|y
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|srcPR
operator|.
name|w
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|srcPR
operator|.
name|h
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
name|tempPR
operator|.
name|data
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
name|temp_data
operator|=
name|tempPR
operator|.
name|data
expr_stmt|;
comment|/*  DodgeBurn the region  */
name|gimp_lut_process
argument_list|(
name|dodgeburn
operator|->
name|lut
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
comment|/* The dest is the paint area we got above (= canvas_buf) */
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
comment|/* Now add an alpha to the dodgeburned region    * and put this in area = canvas_buf    */
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
if|if
condition|(
name|pressure_options
operator|->
name|opacity
condition|)
name|opacity
operator|*=
name|PRESSURE_SCALE
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
comment|/* Replace the newly dodgedburned area (canvas_buf) to the gimage */
name|gimp_brush_core_replace_canvas
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
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
name|GIMP_PAINT_CONSTANT
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_make_luts (GimpDodgeBurn * dodgeburn,gdouble db_exposure,GimpDodgeBurnType type,GimpTransferMode mode,GimpDrawable * drawable)
name|gimp_dodge_burn_make_luts
parameter_list|(
name|GimpDodgeBurn
modifier|*
name|dodgeburn
parameter_list|,
name|gdouble
name|db_exposure
parameter_list|,
name|GimpDodgeBurnType
name|type
parameter_list|,
name|GimpTransferMode
name|mode
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpLutFunc
name|lut_func
decl_stmt|;
name|gint
name|nchannels
init|=
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
specifier|static
name|gfloat
name|exposure
decl_stmt|;
name|exposure
operator|=
name|db_exposure
operator|/
literal|100.0
expr_stmt|;
comment|/* make the exposure negative if burn for luts*/
if|if
condition|(
name|type
operator|==
name|GIMP_BURN
condition|)
name|exposure
operator|=
operator|-
name|exposure
expr_stmt|;
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GIMP_HIGHLIGHTS
case|:
name|lut_func
operator|=
name|gimp_dodge_burn_highlights_lut_func
expr_stmt|;
break|break;
case|case
name|GIMP_MIDTONES
case|:
name|lut_func
operator|=
name|gimp_dodge_burn_midtones_lut_func
expr_stmt|;
break|break;
case|case
name|GIMP_SHADOWS
case|:
name|lut_func
operator|=
name|gimp_dodge_burn_shadows_lut_func
expr_stmt|;
break|break;
default|default:
name|lut_func
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
name|gimp_lut_setup_exact
argument_list|(
name|dodgeburn
operator|->
name|lut
argument_list|,
name|lut_func
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|exposure
argument_list|,
name|nchannels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gfloat
DECL|function|gimp_dodge_burn_highlights_lut_func (gpointer user_data,gint nchannels,gint channel,gfloat value)
name|gimp_dodge_burn_highlights_lut_func
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gfloat
modifier|*
name|exposure_ptr
init|=
operator|(
name|gfloat
operator|*
operator|)
name|user_data
decl_stmt|;
name|gfloat
name|exposure
init|=
operator|*
name|exposure_ptr
decl_stmt|;
name|gfloat
name|factor
init|=
literal|1.0
operator|+
name|exposure
operator|*
operator|(
literal|.333333
operator|)
decl_stmt|;
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|&&
name|channel
operator|==
literal|1
operator|)
operator|||
operator|(
name|nchannels
operator|==
literal|4
operator|&&
name|channel
operator|==
literal|3
operator|)
condition|)
return|return
name|value
return|;
return|return
name|factor
operator|*
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|gfloat
DECL|function|gimp_dodge_burn_midtones_lut_func (gpointer user_data,gint nchannels,gint channel,gfloat value)
name|gimp_dodge_burn_midtones_lut_func
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gfloat
modifier|*
name|exposure_ptr
init|=
operator|(
name|gfloat
operator|*
operator|)
name|user_data
decl_stmt|;
name|gfloat
name|exposure
init|=
operator|*
name|exposure_ptr
decl_stmt|;
name|gfloat
name|factor
decl_stmt|;
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|&&
name|channel
operator|==
literal|1
operator|)
operator|||
operator|(
name|nchannels
operator|==
literal|4
operator|&&
name|channel
operator|==
literal|3
operator|)
condition|)
return|return
name|value
return|;
if|if
condition|(
name|exposure
operator|<
literal|0
condition|)
name|factor
operator|=
literal|1.0
operator|-
name|exposure
operator|*
operator|(
literal|.333333
operator|)
expr_stmt|;
else|else
name|factor
operator|=
literal|1
operator|/
operator|(
literal|1.0
operator|+
name|exposure
operator|)
expr_stmt|;
return|return
name|pow
argument_list|(
name|value
argument_list|,
name|factor
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gfloat
DECL|function|gimp_dodge_burn_shadows_lut_func (gpointer user_data,gint nchannels,gint channel,gfloat value)
name|gimp_dodge_burn_shadows_lut_func
parameter_list|(
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
block|{
name|gfloat
modifier|*
name|exposure_ptr
init|=
operator|(
name|gfloat
operator|*
operator|)
name|user_data
decl_stmt|;
name|gfloat
name|exposure
init|=
operator|*
name|exposure_ptr
decl_stmt|;
name|gfloat
name|new_value
decl_stmt|;
name|gfloat
name|factor
decl_stmt|;
if|if
condition|(
operator|(
name|nchannels
operator|==
literal|2
operator|&&
name|channel
operator|==
literal|1
operator|)
operator|||
operator|(
name|nchannels
operator|==
literal|4
operator|&&
name|channel
operator|==
literal|3
operator|)
condition|)
return|return
name|value
return|;
if|if
condition|(
name|exposure
operator|>=
literal|0
condition|)
block|{
name|factor
operator|=
literal|0.333333
operator|*
name|exposure
expr_stmt|;
name|new_value
operator|=
name|factor
operator|+
name|value
operator|-
name|factor
operator|*
name|value
expr_stmt|;
block|}
else|else
comment|/* exposure< 0 */
block|{
name|factor
operator|=
operator|-
literal|0.333333
operator|*
name|exposure
expr_stmt|;
if|if
condition|(
name|value
operator|<
name|factor
condition|)
name|new_value
operator|=
literal|0
expr_stmt|;
else|else
comment|/*factor<= value<=1*/
name|new_value
operator|=
operator|(
name|value
operator|-
name|factor
operator|)
operator|/
operator|(
literal|1
operator|-
name|factor
operator|)
expr_stmt|;
block|}
return|return
name|new_value
return|;
block|}
end_function

end_unit

