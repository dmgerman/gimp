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
file|<gegl.h>
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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpbrushcore.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_brush_tool_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_brush_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_brush_transformed
parameter_list|(
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_set_brush
parameter_list|(
name|GimpBrushCore
modifier|*
name|brush_core
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_set_brush_after
parameter_list|(
name|GimpBrushCore
modifier|*
name|brush_core
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_tool_notify_brush
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBrushTool,gimp_brush_tool,GIMP_TYPE_PAINT_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrushTool
argument_list|,
argument|gimp_brush_tool
argument_list|,
argument|GIMP_TYPE_PAINT_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brush_tool_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_brush_tool_class_init
parameter_list|(
name|GimpBrushToolClass
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
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_brush_tool_constructor
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_brush_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_brush_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_brush_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_brush_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_init (GimpBrushTool * brush_tool)
name|gimp_brush_tool_init
parameter_list|(
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|brush_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_action_value_2
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"tools/tools-paint-brush-scale-set"
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_value_3
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"context/context-brush-aspect-set"
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_value_4
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"context/context-brush-angle-set"
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_object_1
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"context/context-brush-select-set"
argument_list|)
expr_stmt|;
name|brush_tool
operator|->
name|show_cursor
operator|=
name|TRUE
expr_stmt|;
name|brush_tool
operator|->
name|draw_brush
operator|=
name|TRUE
expr_stmt|;
name|brush_tool
operator|->
name|brush_x
operator|=
literal|0.0
expr_stmt|;
name|brush_tool
operator|->
name|brush_y
operator|=
literal|0.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_brush_tool_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_brush_tool_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|GimpBrushTool
modifier|*
name|brush_tool
decl_stmt|;
name|GimpDisplayConfig
modifier|*
name|display_config
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|brush_tool
operator|=
name|GIMP_BRUSH_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_BRUSH_CORE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
argument_list|)
expr_stmt|;
name|display_config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|brush_tool
operator|->
name|show_cursor
operator|=
name|display_config
operator|->
name|show_paint_tool_cursor
expr_stmt|;
name|brush_tool
operator|->
name|draw_brush
operator|=
name|display_config
operator|->
name|show_brush_outline
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|display_config
argument_list|,
literal|"notify::show-paint-tool-cursor"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_notify_brush
argument_list|)
argument_list|,
name|brush_tool
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|display_config
argument_list|,
literal|"notify::show-brush-outline"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_notify_brush
argument_list|)
argument_list|,
name|brush_tool
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp_tool_get_options
argument_list|(
name|tool
argument_list|)
argument_list|,
literal|"brush-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_brush_changed
argument_list|)
argument_list|,
name|brush_tool
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp_tool_get_options
argument_list|(
name|tool
argument_list|)
argument_list|,
literal|"notify::brush-scale"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_brush_transformed
argument_list|)
argument_list|,
name|brush_tool
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp_tool_get_options
argument_list|(
name|tool
argument_list|)
argument_list|,
literal|"notify::brush-angle"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_brush_transformed
argument_list|)
argument_list|,
name|brush_tool
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp_tool_get_options
argument_list|(
name|tool
argument_list|)
argument_list|,
literal|"notify::brush-aspect-ratio"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_brush_transformed
argument_list|)
argument_list|,
name|brush_tool
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|,
literal|"set-brush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_set_brush
argument_list|)
argument_list|,
name|brush_tool
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|,
literal|"set-brush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_tool_set_brush_after
argument_list|)
argument_list|,
name|brush_tool
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_brush_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpBrushTool
modifier|*
name|brush_tool
init|=
name|GIMP_BRUSH_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|motion
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_color_tool_is_enabled
argument_list|(
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
condition|)
block|{
name|brush_tool
operator|->
name|brush_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|brush_tool
operator|->
name|brush_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
block|}
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_brush_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpBrushTool
modifier|*
name|brush_tool
init|=
name|GIMP_BRUSH_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|paint_options
init|=
name|GIMP_PAINT_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|oper_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_color_tool_is_enabled
argument_list|(
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
operator|&&
name|drawable
operator|&&
name|proximity
condition|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|GimpDynamics
modifier|*
name|dynamics
decl_stmt|;
name|brush_tool
operator|->
name|brush_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|brush_tool
operator|->
name|brush_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_core
operator|->
name|main_brush
operator|!=
name|brush
condition|)
name|gimp_brush_core_set_brush
argument_list|(
name|brush_core
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|dynamics
operator|=
name|gimp_context_get_dynamics
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_core
operator|->
name|dynamics
operator|!=
name|dynamics
condition|)
name|gimp_brush_core_set_dynamics
argument_list|(
name|brush_core
argument_list|,
name|dynamics
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
name|paint_tool
operator|->
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_brush_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpBrushTool
modifier|*
name|brush_tool
init|=
name|GIMP_BRUSH_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|brush_tool
operator|->
name|show_cursor
operator|&&
operator|!
name|gimp_color_tool_is_enabled
argument_list|(
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
operator|&&
name|gimp_tool_control_get_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|)
operator|!=
name|GIMP_CURSOR_MODIFIER_BAD
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|GIMP_CURSOR_NONE
argument_list|,
name|GIMP_TOOL_CURSOR_NONE
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_draw (GimpDrawTool * draw_tool)
name|gimp_brush_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpBrushTool
modifier|*
name|brush_tool
init|=
name|GIMP_BRUSH_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|draw
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_color_tool_is_enabled
argument_list|(
name|GIMP_COLOR_TOOL
argument_list|(
name|draw_tool
argument_list|)
argument_list|)
condition|)
return|return;
name|gimp_brush_tool_draw_brush
argument_list|(
name|brush_tool
argument_list|,
name|brush_tool
operator|->
name|brush_x
argument_list|,
name|brush_tool
operator|->
name|brush_y
argument_list|,
operator|!
name|brush_tool
operator|->
name|show_cursor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_tool_draw_brush (GimpBrushTool * brush_tool,gdouble x,gdouble y,gboolean draw_fallback)
name|gimp_brush_tool_draw_brush
parameter_list|(
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gboolean
name|draw_fallback
parameter_list|)
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
decl_stmt|;
name|GimpBrushCore
modifier|*
name|brush_core
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|options
decl_stmt|;
name|GimpMatrix3
name|matrix
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_TOOL
argument_list|(
name|brush_tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|brush_tool
operator|->
name|draw_brush
condition|)
return|return;
name|draw_tool
operator|=
name|GIMP_DRAW_TOOL
argument_list|(
name|brush_tool
argument_list|)
expr_stmt|;
name|brush_core
operator|=
name|GIMP_BRUSH_CORE
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|brush_tool
argument_list|)
operator|->
name|core
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_PAINT_TOOL_GET_OPTIONS
argument_list|(
name|brush_tool
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|brush_core
operator|->
name|brush_bound_segs
operator|&&
name|brush_core
operator|->
name|main_brush
condition|)
name|gimp_brush_core_create_boundary
argument_list|(
name|brush_core
argument_list|,
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_core
operator|->
name|brush_bound_segs
operator|&&
name|gimp_brush_core_get_transform
argument_list|(
name|brush_core
argument_list|,
operator|&
name|matrix
argument_list|)
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|draw_tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|gdouble
name|width
init|=
name|brush_core
operator|->
name|transformed_brush_bound_width
decl_stmt|;
name|gdouble
name|height
init|=
name|brush_core
operator|->
name|transformed_brush_bound_height
decl_stmt|;
comment|/*  don't draw the boundary if it becomes too small  */
if|if
condition|(
name|SCALEX
argument_list|(
name|shell
argument_list|,
name|width
argument_list|)
operator|>
literal|4
operator|&&
name|SCALEY
argument_list|(
name|shell
argument_list|,
name|height
argument_list|)
operator|>
literal|4
condition|)
block|{
name|x
operator|-=
name|width
operator|/
literal|2.0
expr_stmt|;
name|y
operator|-=
name|height
operator|/
literal|2.0
expr_stmt|;
if|if
condition|(
name|gimp_paint_options_get_brush_mode
argument_list|(
name|options
argument_list|)
operator|==
name|GIMP_BRUSH_HARD
condition|)
block|{
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|0.000001
comment|/*  Add EPSILON before rounding since e.g.                *  (5.0 - 0.5) may end up at (4.499999999....)                *  due to floating point fnords                */
name|x
operator|=
name|RINT
argument_list|(
name|x
operator|+
name|EPSILON
argument_list|)
expr_stmt|;
name|y
operator|=
name|RINT
argument_list|(
name|y
operator|+
name|EPSILON
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|EPSILON
block|}
name|gimp_draw_tool_add_boundary
argument_list|(
name|draw_tool
argument_list|,
name|brush_core
operator|->
name|brush_bound_segs
argument_list|,
name|brush_core
operator|->
name|n_brush_bound_segs
argument_list|,
operator|&
name|matrix
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|draw_fallback
condition|)
block|{
name|gimp_draw_tool_add_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|5
argument_list|,
literal|5
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_brush_changed (GimpContext * context,GimpBrush * brush,GimpBrushTool * brush_tool)
name|gimp_brush_tool_brush_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|brush_tool
argument_list|)
decl_stmt|;
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
decl_stmt|;
if|if
condition|(
name|brush_core
operator|->
name|main_brush
operator|!=
name|brush
condition|)
name|gimp_brush_core_set_brush
argument_list|(
name|brush_core
argument_list|,
name|brush
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_brush_transformed (GimpPaintOptions * options,GParamSpec * pspec,GimpBrushTool * brush_tool)
name|gimp_brush_tool_brush_transformed
parameter_list|(
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|brush_tool
argument_list|)
decl_stmt|;
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
decl_stmt|;
name|gimp_brush_core_set_brush
argument_list|(
name|brush_core
argument_list|,
name|brush_core
operator|->
name|main_brush
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_set_brush (GimpBrushCore * brush_core,GimpBrush * brush,GimpBrushTool * brush_tool)
name|gimp_brush_tool_set_brush
parameter_list|(
name|GimpBrushCore
modifier|*
name|brush_core
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|paint_core
init|=
name|GIMP_PAINT_CORE
argument_list|(
name|brush_core
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|brush_tool
argument_list|)
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
name|paint_core
argument_list|,
name|NULL
argument_list|,
name|GIMP_PAINT_TOOL_GET_OPTIONS
argument_list|(
name|brush_tool
argument_list|)
argument_list|,
operator|&
name|paint_core
operator|->
name|cur_coords
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_set_brush_after (GimpBrushCore * brush_core,GimpBrush * brush,GimpBrushTool * brush_tool)
name|gimp_brush_tool_set_brush_after
parameter_list|(
name|GimpBrushCore
modifier|*
name|brush_core
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
block|{
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|brush_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_notify_brush (GimpDisplayConfig * config,GParamSpec * pspec,GimpBrushTool * brush_tool)
name|gimp_brush_tool_notify_brush
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|brush_tool
argument_list|)
argument_list|)
expr_stmt|;
name|brush_tool
operator|->
name|show_cursor
operator|=
name|config
operator|->
name|show_paint_tool_cursor
expr_stmt|;
name|brush_tool
operator|->
name|draw_brush
operator|=
name|config
operator|->
name|show_brush_outline
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|brush_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

