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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
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
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_class_init
parameter_list|(
name|GimpPaintbrushClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_init
parameter_list|(
name|GimpPaintbrush
modifier|*
name|paintbrush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_paint
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
name|void
DECL|function|gimp_paintbrush_register (Gimp * gimp,GimpPaintRegisterCallback callback)
name|gimp_paintbrush_register
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
name|GIMP_TYPE_PAINTBRUSH
argument_list|,
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
name|_
argument_list|(
literal|"Paintbrush"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_paintbrush_get_type (void)
name|gimp_paintbrush_get_type
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
name|GimpPaintbrushClass
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
name|gimp_paintbrush_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPaintbrush
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_paintbrush_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_CORE
argument_list|,
literal|"GimpPaintbrush"
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
DECL|function|gimp_paintbrush_class_init (GimpPaintbrushClass * klass)
name|gimp_paintbrush_class_init
parameter_list|(
name|GimpPaintbrushClass
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
name|gimp_paintbrush_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paintbrush_init (GimpPaintbrush * paintbrush)
name|gimp_paintbrush_init
parameter_list|(
name|GimpPaintbrush
modifier|*
name|paintbrush
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
name|paintbrush
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
DECL|function|gimp_paintbrush_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintCoreState paint_state)
name|gimp_paintbrush_paint
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
name|_gimp_paintbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|_gimp_paintbrush_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,gdouble opacity)
name|_gimp_paintbrush_motion
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
name|gdouble
name|opacity
parameter_list|)
block|{
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
name|GimpFadeOptions
modifier|*
name|fade_options
decl_stmt|;
name|GimpGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpRGB
name|gradient_color
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|GimpPaintApplicationMode
name|paint_appl_mode
decl_stmt|;
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
name|fade_options
operator|=
name|paint_options
operator|->
name|fade_options
expr_stmt|;
name|gradient_options
operator|=
name|paint_options
operator|->
name|gradient_options
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
name|opacity
operator|*=
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
name|paint_appl_mode
operator|=
name|paint_options
operator|->
name|application_mode
expr_stmt|;
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
comment|/*  Get a region which can be used to paint to  */
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
if|if
condition|(
name|gimp_paint_options_get_gradient_color
argument_list|(
name|paint_options
argument_list|,
name|gimage
argument_list|,
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
argument_list|,
name|paint_core
operator|->
name|pixel_dist
argument_list|,
operator|&
name|gradient_color
argument_list|)
condition|)
block|{
name|opacity
operator|*=
name|gradient_color
operator|.
name|a
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|gradient_color
argument_list|,
operator|&
name|col
index|[
name|RED_PIX
index|]
argument_list|,
operator|&
name|col
index|[
name|GREEN_PIX
index|]
argument_list|,
operator|&
name|col
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|col
index|[
name|ALPHA_PIX
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
name|GIMP_PAINT_INCREMENTAL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|paint_core
operator|->
name|brush
operator|&&
name|paint_core
operator|->
name|brush
operator|->
name|pixmap
condition|)
block|{
comment|/* if it's a pixmap, do pixmap stuff */
name|gimp_paint_core_color_area_with_pixmap
argument_list|(
name|paint_core
argument_list|,
name|gimage
argument_list|,
name|drawable
argument_list|,
name|area
argument_list|,
name|scale
argument_list|,
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
name|GIMP_PAINT_INCREMENTAL
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|col
index|[
name|area
operator|->
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pressure_options
operator|->
name|opacity
condition|)
name|opacity
operator|*=
literal|2.0
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
name|gimp_paint_core_paste_canvas
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
name|gimp_context_get_paint_mode
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
name|paint_appl_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

