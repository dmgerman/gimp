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
file|"paint-types.h"
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
file|"core/gimpsymmetry.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_finalize
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
name|gimp_airbrush_paint
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

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_motion
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_airbrush_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpAirbrush,gimp_airbrush,GIMP_TYPE_PAINTBRUSH)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAirbrush
argument_list|,
argument|gimp_airbrush
argument_list|,
argument|GIMP_TYPE_PAINTBRUSH
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_airbrush_parent_class
end_define

begin_function
name|void
name|gimp_airbrush_register
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
name|GIMP_TYPE_AIRBRUSH
argument_list|,
name|GIMP_TYPE_AIRBRUSH_OPTIONS
argument_list|,
literal|"gimp-airbrush"
argument_list|,
name|_
argument_list|(
literal|"Airbrush"
argument_list|)
argument_list|,
literal|"gimp-tool-airbrush"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_class_init (GimpAirbrushClass * klass)
name|gimp_airbrush_class_init
parameter_list|(
name|GimpAirbrushClass
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_airbrush_finalize
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_airbrush_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_init (GimpAirbrush * airbrush)
name|gimp_airbrush_init
parameter_list|(
name|GimpAirbrush
modifier|*
name|airbrush
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_finalize (GObject * object)
name|gimp_airbrush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpAirbrush
modifier|*
name|airbrush
init|=
name|GIMP_AIRBRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|airbrush
operator|->
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|airbrush
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
name|airbrush
operator|->
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
name|g_clear_object
argument_list|(
operator|&
name|airbrush
operator|->
name|sym
argument_list|)
expr_stmt|;
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
DECL|function|gimp_airbrush_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym,GimpPaintState paint_state,guint32 time)
name|gimp_airbrush_paint
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
name|GimpAirbrush
modifier|*
name|airbrush
init|=
name|GIMP_AIRBRUSH
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpAirbrushOptions
modifier|*
name|options
init|=
name|GIMP_AIRBRUSH_OPTIONS
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
if|if
condition|(
name|airbrush
operator|->
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|airbrush
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
name|airbrush
operator|->
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_INIT
case|:
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|paint
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|,
name|paint_state
argument_list|,
name|time
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
name|gimp_airbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|options
operator|->
name|rate
operator|!=
literal|0.0
operator|)
operator|&&
operator|!
name|options
operator|->
name|motion_only
condition|)
block|{
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
name|gdouble
name|fade_point
decl_stmt|;
name|gdouble
name|dynamic_rate
decl_stmt|;
name|gint
name|timeout
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
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
name|airbrush
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|airbrush
operator|->
name|paint_options
operator|=
name|paint_options
expr_stmt|;
if|if
condition|(
name|airbrush
operator|->
name|sym
condition|)
name|g_object_unref
argument_list|(
name|airbrush
operator|->
name|sym
argument_list|)
expr_stmt|;
name|airbrush
operator|->
name|sym
operator|=
name|g_object_ref
argument_list|(
name|sym
argument_list|)
expr_stmt|;
comment|/* Base our timeout on the original stroke. */
name|coords
operator|=
name|gimp_symmetry_get_origin
argument_list|(
name|sym
argument_list|)
expr_stmt|;
name|dynamic_rate
operator|=
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_RATE
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
name|timeout
operator|=
literal|10000
operator|/
operator|(
name|options
operator|->
name|rate
operator|*
name|dynamic_rate
operator|)
expr_stmt|;
name|airbrush
operator|->
name|timeout_id
operator|=
name|g_timeout_add
argument_list|(
name|timeout
argument_list|,
name|gimp_airbrush_timeout
argument_list|,
name|airbrush
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|paint
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|sym
argument_list|,
name|paint_state
argument_list|,
name|time
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|airbrush
operator|->
name|sym
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpSymmetry * sym)
name|gimp_airbrush_motion
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
parameter_list|)
block|{
name|GimpAirbrushOptions
modifier|*
name|options
init|=
name|GIMP_AIRBRUSH_OPTIONS
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
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|fade_point
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
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
name|coords
operator|=
name|gimp_symmetry_get_origin
argument_list|(
name|sym
argument_list|)
expr_stmt|;
name|opacity
operator|=
operator|(
name|options
operator|->
name|flow
operator|/
literal|100.0
operator|*
name|gimp_dynamics_get_linear_value
argument_list|(
name|dynamics
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FLOW
argument_list|,
name|coords
argument_list|,
name|paint_options
argument_list|,
name|fade_point
argument_list|)
operator|)
expr_stmt|;
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
name|opacity
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_airbrush_timeout (gpointer data)
name|gimp_airbrush_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpAirbrush
modifier|*
name|airbrush
init|=
name|GIMP_AIRBRUSH
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_airbrush_paint
argument_list|(
name|GIMP_PAINT_CORE
argument_list|(
name|airbrush
argument_list|)
argument_list|,
name|airbrush
operator|->
name|drawable
argument_list|,
name|airbrush
operator|->
name|paint_options
argument_list|,
name|airbrush
operator|->
name|sym
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|airbrush
operator|->
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|G_SOURCE_REMOVE
return|;
block|}
end_function

end_unit

