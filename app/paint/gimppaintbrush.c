begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPaintbrush,gimp_paintbrush,GIMP_TYPE_BRUSH_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPaintbrush
argument_list|,
argument|gimp_paintbrush
argument_list|,
argument|GIMP_TYPE_BRUSH_CORE
argument_list|)
end_macro

begin_function
name|void
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
literal|"gimp-paintbrush"
argument_list|,
name|_
argument_list|(
literal|"Paintbrush"
argument_list|)
argument_list|,
literal|"gimp-tool-paintbrush"
argument_list|)
expr_stmt|;
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
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpBrushCoreClass
modifier|*
name|brush_core_class
init|=
name|GIMP_BRUSH_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_paintbrush_paint
expr_stmt|;
name|brush_core_class
operator|->
name|handles_changing_brush
operator|=
name|TRUE
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
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paintbrush_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintState paint_state,guint32 time)
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
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_MOTION
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
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
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
name|GimpVelocityOptions
modifier|*
name|velocity_options
init|=
name|paint_options
operator|->
name|velocity_options
decl_stmt|;
name|GimpImage
modifier|*
name|image
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
name|GimpPaintApplicationMode
name|paint_appl_mode
decl_stmt|;
name|gdouble
name|grad_point
decl_stmt|;
name|gdouble
name|hardness
decl_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|opacity
operator|*=
name|gimp_paint_options_get_fade
argument_list|(
name|paint_options
argument_list|,
name|image
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
name|paint_appl_mode
operator|=
name|paint_options
operator|->
name|application_mode
expr_stmt|;
name|grad_point
operator|=
name|gimp_paint_options_get_dynamic_color
argument_list|(
name|paint_options
argument_list|,
operator|&
name|paint_core
operator|->
name|cur_coords
argument_list|,
name|paint_core
operator|->
name|use_pressure
argument_list|)
expr_stmt|;
comment|/* optionally take the color from the current gradient */
if|if
condition|(
name|gimp_paint_options_get_gradient_color
argument_list|(
name|paint_options
argument_list|,
name|image
argument_list|,
name|grad_point
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
comment|/* otherwise check if the brush has a pixmap and use that to color the area */
elseif|else
if|if
condition|(
name|brush_core
operator|->
name|brush
operator|&&
name|brush_core
operator|->
name|brush
operator|->
name|pixmap
condition|)
block|{
name|gimp_brush_core_color_area_with_pixmap
argument_list|(
name|brush_core
argument_list|,
name|drawable
argument_list|,
name|area
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
comment|/* otherwise fill the area with the foreground color */
else|else
block|{
name|gimp_image_get_foreground
argument_list|(
name|image
argument_list|,
name|context
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
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
name|opacity
operator|*=
name|gimp_paint_options_get_dynamic_opacity
argument_list|(
name|paint_options
argument_list|,
operator|&
name|paint_core
operator|->
name|cur_coords
argument_list|,
name|paint_core
operator|->
name|use_pressure
argument_list|)
expr_stmt|;
name|hardness
operator|=
name|gimp_paint_options_get_dynamic_hardness
argument_list|(
name|paint_options
argument_list|,
operator|&
name|paint_core
operator|->
name|cur_coords
argument_list|,
name|paint_core
operator|->
name|use_pressure
argument_list|)
expr_stmt|;
comment|/* finally, let the brush core paste the colored area on the canvas */
name|gimp_brush_core_paste_canvas
argument_list|(
name|brush_core
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
name|hardness
argument_list|,
name|paint_appl_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

