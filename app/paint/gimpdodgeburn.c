begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"gegl/gimp-gegl-loops.h"
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
file|"core/gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamicsoutput.h"
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintState
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
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDodgeBurn,gimp_dodge_burn,GIMP_TYPE_BRUSH_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDodgeBurn
argument_list|,
argument|gimp_dodge_burn
argument_list|,
argument|GIMP_TYPE_BRUSH_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dodge_burn_parent_class
end_define

begin_function
name|void
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
literal|"gimp-dodge-burn"
argument_list|,
name|_
argument_list|(
literal|"Dodge/Burn"
argument_list|)
argument_list|,
literal|"gimp-tool-dodge"
argument_list|)
expr_stmt|;
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
name|gimp_dodge_burn_paint
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
DECL|function|gimp_dodge_burn_init (GimpDodgeBurn * dodgeburn)
name|gimp_dodge_burn_init
parameter_list|(
name|GimpDodgeBurn
modifier|*
name|dodgeburn
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GimpPaintState paint_state,guint32 time)
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
specifier|const
name|GimpCoords
modifier|*
name|coords
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
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
name|gimp_dodge_burn_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords)
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
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|GimpDodgeBurnOptions
modifier|*
name|options
init|=
name|GIMP_DODGE_BURN_OPTIONS
argument_list|(
name|paint_options
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
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
operator|->
name|dynamics
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
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
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|GimpDynamicsOutput
modifier|*
name|force_output
decl_stmt|;
name|gdouble
name|force
decl_stmt|;
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
name|opacity
operator|=
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
name|coords
argument_list|,
operator|&
name|paint_buffer_x
argument_list|,
operator|&
name|paint_buffer_y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_buffer
condition|)
return|return;
comment|/*  DodgeBurn the region  */
name|gimp_gegl_dodgeburn
argument_list|(
name|gimp_paint_core_get_orig_image
argument_list|(
name|paint_core
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|paint_buffer_x
argument_list|,
name|paint_buffer_y
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|paint_buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|paint_buffer
argument_list|)
argument_list|)
argument_list|,
name|paint_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|,
name|options
operator|->
name|exposure
operator|/
literal|100.0
argument_list|,
name|options
operator|->
name|type
argument_list|,
name|options
operator|->
name|mode
argument_list|)
expr_stmt|;
name|force_output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dynamics_output_is_enabled
argument_list|(
name|force_output
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
comment|/* Replace the newly dodgedburned area (paint_area) to the image */
name|gimp_brush_core_replace_canvas
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
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
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|force
argument_list|,
name|GIMP_PAINT_CONSTANT
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

