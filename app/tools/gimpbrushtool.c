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
file|<string.h>
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
file|"core/gimpbezierdesc.h"
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
file|"display/gimpcanvashandle.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpcanvaspath.h"
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
name|void
name|gimp_brush_tool_constructed
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
name|gimp_brush_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
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
name|constructed
operator|=
name|gimp_brush_tool_constructed
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
name|tool_class
operator|->
name|options_notify
operator|=
name|gimp_brush_tool_options_notify
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
literal|"tools/tools-paint-brush-size-set"
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
name|void
DECL|function|gimp_brush_tool_constructed (GObject * object)
name|gimp_brush_tool_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpBrushTool
modifier|*
name|brush_tool
init|=
name|GIMP_BRUSH_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpDisplayConfig
modifier|*
name|display_config
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
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
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
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
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
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
name|gimp_brush_core_set_brush
argument_list|(
name|brush_core
argument_list|,
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_brush_core_set_dynamics
argument_list|(
name|brush_core
argument_list|,
name|gimp_context_get_dynamics
argument_list|(
name|context
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
name|GimpBrushCore
modifier|*
name|brush_core
init|=
name|GIMP_BRUSH_CORE
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|brush_tool
argument_list|)
operator|->
name|core
argument_list|)
decl_stmt|;
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
if|if
condition|(
operator|!
name|brush_core
operator|->
name|main_brush
operator|||
operator|!
name|brush_core
operator|->
name|dynamics
condition|)
block|{
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|gimp_tool_control_get_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|)
argument_list|,
name|gimp_tool_control_get_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|)
argument_list|,
name|GIMP_CURSOR_MODIFIER_BAD
argument_list|)
expr_stmt|;
return|return;
block|}
elseif|else
if|if
condition|(
operator|!
name|brush_tool
operator|->
name|show_cursor
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
return|return;
block|}
block|}
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
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_tool_options_notify (GimpTool * tool,GimpToolOptions * options,const GParamSpec * pspec)
name|gimp_brush_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|options_notify
argument_list|(
name|tool
argument_list|,
name|options
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"brush-size"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"brush-angle"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"brush-aspect-ratio"
argument_list|)
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
name|g_signal_emit_by_name
argument_list|(
name|brush_core
argument_list|,
literal|"set-brush"
argument_list|,
name|brush_core
operator|->
name|main_brush
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
name|GimpCanvasItem
modifier|*
name|item
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
name|item
operator|=
name|gimp_brush_tool_create_outline
argument_list|(
name|brush_tool
argument_list|,
name|draw_tool
operator|->
name|display
argument_list|,
name|brush_tool
operator|->
name|brush_x
argument_list|,
name|brush_tool
operator|->
name|brush_y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|item
operator|&&
operator|!
name|brush_tool
operator|->
name|show_cursor
condition|)
block|{
name|item
operator|=
name|gimp_canvas_handle_new
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|draw_tool
operator|->
name|display
argument_list|)
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|,
name|brush_tool
operator|->
name|brush_x
argument_list|,
name|brush_tool
operator|->
name|brush_y
argument_list|,
name|GIMP_TOOL_HANDLE_SIZE_SMALL
argument_list|,
name|GIMP_TOOL_HANDLE_SIZE_SMALL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|item
condition|)
block|{
name|gimp_draw_tool_add_item
argument_list|(
name|draw_tool
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_brush_tool_create_outline (GimpBrushTool * brush_tool,GimpDisplay * display,gdouble x,gdouble y)
name|gimp_brush_tool_create_outline
parameter_list|(
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpBrushCore
modifier|*
name|brush_core
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|options
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
specifier|const
name|GimpBezierDesc
modifier|*
name|boundary
init|=
name|NULL
decl_stmt|;
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gint
name|height
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_TOOL
argument_list|(
name|brush_tool
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|brush_tool
operator|->
name|draw_brush
condition|)
return|return
name|NULL
return|;
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
name|shell
operator|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|brush_core
operator|->
name|main_brush
operator|||
operator|!
name|brush_core
operator|->
name|dynamics
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|brush_core
operator|->
name|scale
operator|>
literal|0.0
condition|)
name|boundary
operator|=
name|gimp_brush_transform_boundary
argument_list|(
name|brush_core
operator|->
name|main_brush
argument_list|,
name|brush_core
operator|->
name|scale
argument_list|,
name|brush_core
operator|->
name|aspect_ratio
argument_list|,
name|brush_core
operator|->
name|angle
argument_list|,
name|brush_core
operator|->
name|hardness
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
comment|/*  don't draw the boundary if it becomes too small  */
if|if
condition|(
name|boundary
operator|&&
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
comment|/*  Add EPSILON before rounding since e.g.            *  (5.0 - 0.5) may end up at (4.499999999....)            *  due to floating point fnords            */
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
return|return
name|gimp_canvas_path_new
argument_list|(
name|shell
argument_list|,
name|boundary
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PATH_STYLE_OUTLINE
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
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
name|GimpPaintCore
modifier|*
name|paint_core
init|=
name|GIMP_PAINT_CORE
argument_list|(
name|brush_core
argument_list|)
decl_stmt|;
name|gimp_brush_core_eval_transform_dynamics
argument_list|(
name|brush_core
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

