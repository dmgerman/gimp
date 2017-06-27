begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Major improvement to support polygonal segments  * Copyright (C) 2008 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-selection.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptoolpolygon.h"
end_include

begin_include
include|#
directive|include
file|"gimpfreeselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectionoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpFreeSelectToolPrivate
struct|struct
name|_GimpFreeSelectToolPrivate
block|{
comment|/* The selection operation active when the tool was started */
DECL|member|operation_at_start
name|GimpChannelOps
name|operation_at_start
decl_stmt|;
DECL|member|widget
name|GimpToolWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|grab_widget
name|GimpToolWidget
modifier|*
name|grab_widget
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_finalize
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
name|gimp_free_select_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
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
name|gimp_free_select_tool_oper_update
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
name|gimp_free_select_tool_cursor_update
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
name|gimp_free_select_tool_button_press
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
name|GimpButtonPressType
name|press_type
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
name|gimp_free_select_tool_button_release
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
name|GimpButtonReleaseType
name|release_type
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
name|gimp_free_select_tool_motion
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
name|gboolean
name|gimp_free_select_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
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
name|gimp_free_select_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
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
name|gimp_free_select_tool_active_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
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
name|gimp_free_select_tool_real_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_polygon_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|polygon
parameter_list|,
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_free_select_tool_polygon_response
parameter_list|(
name|GimpToolWidget
modifier|*
name|polygon
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpFreeSelectTool
argument_list|,
name|gimp_free_select_tool
argument_list|,
name|GIMP_TYPE_SELECTION_TOOL
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_free_select_tool_parent_class
end_define

begin_function
name|void
DECL|function|gimp_free_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_free_select_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_FREE_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_SELECTION_OPTIONS
argument_list|,
name|gimp_selection_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-free-select-tool"
argument_list|,
name|_
argument_list|(
literal|"Free Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Free Select Tool: Select a hand-drawn region with free "
literal|"and polygonal segments"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Free Select"
argument_list|)
argument_list|,
literal|"F"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_FREE_SELECT
argument_list|,
name|GIMP_ICON_TOOL_FREE_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_class_init (GimpFreeSelectToolClass * klass)
name|gimp_free_select_tool_class_init
parameter_list|(
name|GimpFreeSelectToolClass
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_free_select_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_free_select_tool_control
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_free_select_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_free_select_tool_cursor_update
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_free_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_free_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_free_select_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_free_select_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_free_select_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|active_modifier_key
operator|=
name|gimp_free_select_tool_active_modifier_key
expr_stmt|;
name|klass
operator|->
name|select
operator|=
name|gimp_free_select_tool_real_select
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpFreeSelectToolPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_init (GimpFreeSelectTool * fst)
name|gimp_free_select_tool_init
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|fst
argument_list|)
decl_stmt|;
name|fst
operator|->
name|private
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|fst
argument_list|,
name|GIMP_TYPE_FREE_SELECT_TOOL
argument_list|,
name|GimpFreeSelectToolPrivate
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_motion_mode
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_MOTION_MODE_EXACT
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_wants_click
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_precision
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_PRECISION_SUBPIXEL
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_FREE_SELECT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_finalize (GObject * object)
name|gimp_free_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|priv
operator|->
name|widget
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
DECL|function|gimp_free_select_tool_start (GimpFreeSelectTool * fst,GimpDisplay * display)
name|gimp_free_select_tool_start
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|fst
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|private
init|=
name|fst
operator|->
name|private
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
init|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
comment|/* We want to apply the selection operation that was current when    * the tool was started, so we save this information    */
name|private
operator|->
name|operation_at_start
operator|=
name|options
operator|->
name|operation
expr_stmt|;
name|private
operator|->
name|widget
operator|=
name|gimp_tool_polygon_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_draw_tool_set_widget
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|private
operator|->
name|widget
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|widget
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_free_select_tool_polygon_changed
argument_list|)
argument_list|,
name|fst
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|widget
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_free_select_tool_polygon_response
argument_list|)
argument_list|,
name|fst
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_commit (GimpFreeSelectTool * fst,GimpDisplay * display)
name|gimp_free_select_tool_commit
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectToolPrivate
modifier|*
name|private
init|=
name|fst
operator|->
name|private
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|widget
condition|)
block|{
specifier|const
name|GimpVector2
modifier|*
name|points
decl_stmt|;
name|gint
name|n_points
decl_stmt|;
name|gimp_tool_polygon_get_points
argument_list|(
name|GIMP_TOOL_POLYGON
argument_list|(
name|private
operator|->
name|widget
argument_list|)
argument_list|,
operator|&
name|points
argument_list|,
operator|&
name|n_points
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_points
operator|>=
literal|3
condition|)
block|{
name|GIMP_FREE_SELECT_TOOL_GET_CLASS
argument_list|(
name|fst
argument_list|)
operator|->
name|select
argument_list|(
name|fst
argument_list|,
name|display
argument_list|,
name|points
argument_list|,
name|n_points
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_image_flush
argument_list|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_halt (GimpFreeSelectTool * fst)
name|gimp_free_select_tool_halt
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|)
block|{
name|GimpFreeSelectToolPrivate
modifier|*
name|private
init|=
name|fst
operator|->
name|private
decl_stmt|;
name|gimp_draw_tool_set_widget
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|fst
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_free_select_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|GIMP_TOOL_ACTION_PAUSE
case|:
case|case
name|GIMP_TOOL_ACTION_RESUME
case|:
break|break;
case|case
name|GIMP_TOOL_ACTION_HALT
case|:
name|gimp_free_select_tool_halt
argument_list|(
name|fst
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TOOL_ACTION_COMMIT
case|:
name|gimp_free_select_tool_commit
argument_list|(
name|fst
argument_list|,
name|display
argument_list|)
expr_stmt|;
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_free_select_tool_oper_update
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
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
if|if
condition|(
name|display
operator|!=
name|tool
operator|->
name|display
condition|)
block|{
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
return|return;
block|}
if|if
condition|(
name|priv
operator|->
name|widget
condition|)
block|{
name|gimp_tool_widget_hover
argument_list|(
name|priv
operator|->
name|widget
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_free_select_tool_cursor_update
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
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|display
operator|==
name|NULL
condition|)
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
return|return;
block|}
if|if
condition|(
name|priv
operator|->
name|widget
operator|&&
name|display
operator|==
name|tool
operator|->
name|display
condition|)
block|{
name|gimp_tool_widget_get_cursor
argument_list|(
name|priv
operator|->
name|widget
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|modifier
argument_list|)
expr_stmt|;
block|}
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
name|modifier
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_free_select_tool_button_press
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
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|private
init|=
name|fst
operator|->
name|private
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|display
operator|&&
name|tool
operator|->
name|display
operator|!=
name|display
condition|)
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_COMMIT
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|widget
condition|)
comment|/* not tool->display, we have a subclass */
block|{
comment|/* First of all handle delegation to the selection mask edit logic        * if appropriate.        */
if|if
condition|(
name|gimp_selection_tool_start_edit
argument_list|(
name|GIMP_SELECTION_TOOL
argument_list|(
name|fst
argument_list|)
argument_list|,
name|display
argument_list|,
name|coords
argument_list|)
condition|)
block|{
return|return;
block|}
name|gimp_free_select_tool_start
argument_list|(
name|fst
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_tool_widget_hover
argument_list|(
name|private
operator|->
name|widget
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_tool_widget_button_press
argument_list|(
name|private
operator|->
name|widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|press_type
argument_list|)
condition|)
block|{
name|private
operator|->
name|grab_widget
operator|=
name|private
operator|->
name|widget
expr_stmt|;
block|}
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_free_select_tool_button_release
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|release_type
condition|)
block|{
case|case
name|GIMP_BUTTON_RELEASE_CLICK
case|:
case|case
name|GIMP_BUTTON_RELEASE_NO_MOTION
case|:
comment|/*  If there is a floating selection, anchor it  */
if|if
condition|(
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|floating_sel_anchor
argument_list|(
name|gimp_image_get_floating_selection
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* fallthru */
default|default:
if|if
condition|(
name|priv
operator|->
name|grab_widget
condition|)
block|{
name|gimp_tool_widget_button_release
argument_list|(
name|priv
operator|->
name|grab_widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|release_type
argument_list|)
expr_stmt|;
name|priv
operator|->
name|grab_widget
operator|=
name|NULL
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_free_select_tool_motion
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
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|grab_widget
condition|)
block|{
name|gimp_tool_widget_motion
argument_list|(
name|priv
operator|->
name|grab_widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_free_select_tool_key_press (GimpTool * tool,GdkEventKey * kevent,GimpDisplay * display)
name|gimp_free_select_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|widget
operator|&&
name|display
operator|==
name|tool
operator|->
name|display
condition|)
block|{
return|return
name|gimp_tool_widget_key_press
argument_list|(
name|priv
operator|->
name|widget
argument_list|,
name|kevent
argument_list|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_free_select_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|widget
operator|&&
name|display
operator|==
name|tool
operator|->
name|display
condition|)
block|{
name|gimp_tool_widget_hover_modifier
argument_list|(
name|priv
operator|->
name|widget
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|modifier_key
argument_list|(
name|tool
argument_list|,
name|key
argument_list|,
name|press
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
DECL|function|gimp_free_select_tool_active_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_free_select_tool_active_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpFreeSelectTool
modifier|*
name|fst
init|=
name|GIMP_FREE_SELECT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|widget
condition|)
block|{
name|gimp_tool_widget_motion_modifier
argument_list|(
name|priv
operator|->
name|widget
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|active_modifier_key
argument_list|(
name|tool
argument_list|,
name|key
argument_list|,
name|press
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
DECL|function|gimp_free_select_tool_real_select (GimpFreeSelectTool * fst,GimpDisplay * display,const GimpVector2 * points,gint n_points)
name|gimp_free_select_tool_real_select
parameter_list|(
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|)
block|{
name|GimpSelectionOptions
modifier|*
name|options
init|=
name|GIMP_SELECTION_TOOL_GET_OPTIONS
argument_list|(
name|fst
argument_list|)
decl_stmt|;
name|GimpFreeSelectToolPrivate
modifier|*
name|priv
init|=
name|fst
operator|->
name|private
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gimp_channel_select_polygon
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
name|C_
argument_list|(
literal|"command"
argument_list|,
literal|"Free Select"
argument_list|)
argument_list|,
name|n_points
argument_list|,
name|points
argument_list|,
name|priv
operator|->
name|operation_at_start
argument_list|,
name|options
operator|->
name|antialias
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control
argument_list|(
name|GIMP_TOOL
argument_list|(
name|fst
argument_list|)
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_polygon_changed (GimpToolWidget * polygon,GimpFreeSelectTool * fst)
name|gimp_free_select_tool_polygon_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|polygon
parameter_list|,
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_free_select_tool_polygon_response (GimpToolWidget * polygon,gint response_id,GimpFreeSelectTool * fst)
name|gimp_free_select_tool_polygon_response
parameter_list|(
name|GimpToolWidget
modifier|*
name|polygon
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpFreeSelectTool
modifier|*
name|fst
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|fst
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GIMP_TOOL_WIDGET_RESPONSE_CONFIRM
case|:
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_COMMIT
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TOOL_WIDGET_RESPONSE_CANCEL
case|:
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

end_unit

