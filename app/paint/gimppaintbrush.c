begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-palettes.h"
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
file|"core/gimpdynamics.h"
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
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpsymmetry.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptempbuf.h"
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
name|GimpSymmetry
modifier|*
name|sym
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
DECL|function|gimp_paintbrush_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym,GimpPaintState paint_state,guint32 time)
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
name|GimpSymmetry
modifier|*
name|sym
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
name|GIMP_PAINT_STATE_INIT
case|:
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpDynamics
modifier|*
name|dynamics
init|=
name|gimp_context_get_dynamics
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_dynamics_is_output_enabled
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_COLOR
argument_list|)
operator|&&
operator|(
operator|!
name|brush_core
operator|->
name|brush
operator|||
operator|!
name|gimp_brush_get_pixmap
argument_list|(
name|brush_core
operator|->
name|brush
argument_list|)
operator|)
condition|)
block|{
comment|/* We don't save gradient color history and pixmap brushes              * have no color to save.              */
name|GimpRGB
name|foreground
decl_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|foreground
argument_list|)
expr_stmt|;
name|gimp_palettes_add_color_history
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
operator|&
name|foreground
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
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
name|sym
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
DECL|function|_gimp_paintbrush_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym,gdouble opacity)
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
name|GimpSymmetry
modifier|*
name|sym
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
name|GimpDynamics
modifier|*
name|dynamics
init|=
name|brush_core
operator|->
name|dynamics
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayerMode
name|paint_mode
decl_stmt|;
name|GimpRGB
name|gradient_color
decl_stmt|;
name|GeglBuffer
modifier|*
name|paint_buffer
decl_stmt|;
name|gint
name|paint_buffer_x
decl_stmt|;
name|gint
name|paint_buffer_y
decl_stmt|;
name|GimpPaintApplicationMode
name|paint_appl_mode
decl_stmt|;
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|grad_point
decl_stmt|;
name|gdouble
name|force
decl_stmt|;
specifier|const
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|GeglNode
modifier|*
name|op
decl_stmt|;
name|gint
name|n_strokes
decl_stmt|;
name|gint
name|i
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
name|fade_point
operator|=
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
name|coords
operator|=
name|gimp_symmetry_get_origin
argument_list|(
name|sym
argument_list|)
expr_stmt|;
comment|/* Some settings are based on the original stroke. */
name|opacity
operator|*=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_OPACITY
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
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
name|grad_point
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_COLOR
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_BRUSH_CORE_GET_CLASS
argument_list|(
name|brush_core
argument_list|)
operator|->
name|handles_transforming_brush
condition|)
block|{
name|gimp_brush_core_eval_transform_dynamics
argument_list|(
name|brush_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
name|paint_mode
operator|=
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|n_strokes
operator|=
name|gimp_symmetry_get_size
argument_list|(
name|sym
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_strokes
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|paint_width
decl_stmt|,
name|paint_height
decl_stmt|;
name|coords
operator|=
name|gimp_symmetry_get_coords
argument_list|(
name|sym
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|paint_buffer
operator|=
name|gimp_paint_core_get_paint_buffer
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|paint_mode
argument_list|,
name|coords
argument_list|,
operator|&
name|paint_buffer_x
argument_list|,
operator|&
name|paint_buffer_y
argument_list|,
operator|&
name|paint_width
argument_list|,
operator|&
name|paint_height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_buffer
condition|)
continue|continue;
name|op
operator|=
name|gimp_symmetry_get_operation
argument_list|(
name|sym
argument_list|,
name|i
argument_list|,
name|paint_width
argument_list|,
name|paint_height
argument_list|)
expr_stmt|;
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
comment|/* optionally take the color from the current gradient */
name|GeglColor
modifier|*
name|color
decl_stmt|;
name|opacity
operator|*=
name|gradient_color
operator|.
name|a
expr_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|gradient_color
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|color
operator|=
name|gimp_gegl_color_new
argument_list|(
operator|&
name|gradient_color
argument_list|,
name|NULL
comment|/* EEK SPACE? */
argument_list|)
expr_stmt|;
name|gegl_buffer_set_color
argument_list|(
name|paint_buffer
argument_list|,
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|color
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
name|brush_core
operator|->
name|brush
operator|&&
name|gimp_brush_get_pixmap
argument_list|(
name|brush_core
operator|->
name|brush
argument_list|)
condition|)
block|{
comment|/* otherwise check if the brush has a pixmap and use that to            * color the area            */
name|gimp_brush_core_color_area_with_pixmap
argument_list|(
name|brush_core
argument_list|,
name|drawable
argument_list|,
name|coords
argument_list|,
name|op
argument_list|,
name|paint_buffer
argument_list|,
name|paint_buffer_x
argument_list|,
name|paint_buffer_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
name|GIMP_PAINT_INCREMENTAL
expr_stmt|;
block|}
else|else
block|{
comment|/* otherwise fill the area with the foreground color */
name|GimpRGB
name|foreground
decl_stmt|;
name|GeglColor
modifier|*
name|color
decl_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|context
argument_list|,
operator|&
name|foreground
argument_list|)
expr_stmt|;
name|gimp_pickable_srgb_to_image_color
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|foreground
argument_list|,
operator|&
name|foreground
argument_list|)
expr_stmt|;
name|color
operator|=
name|gimp_gegl_color_new
argument_list|(
operator|&
name|foreground
argument_list|,
name|gimp_drawable_get_space
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_set_color
argument_list|(
name|paint_buffer
argument_list|,
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_dynamics_is_output_enabled
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|)
condition|)
name|force
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
else|else
name|force
operator|=
name|paint_options
operator|->
name|brush_force
expr_stmt|;
comment|/* finally, let the brush core paste the colored area on the canvas */
name|gimp_brush_core_paste_canvas
argument_list|(
name|brush_core
argument_list|,
name|drawable
argument_list|,
name|coords
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
name|paint_mode
argument_list|,
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|force
argument_list|,
name|paint_appl_mode
argument_list|,
name|op
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

