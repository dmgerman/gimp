begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpcagetool.c  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"tools/tools-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpcagetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcageoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_cage_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_cage_tool_finalize
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
name|gimp_cage_tool_start
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
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
name|gimp_cage_tool_halt
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_cage_tool_button_press
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
name|gimp_cage_tool_button_release
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
name|gboolean
name|gimp_cage_tool_key_press
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
name|gimp_cage_tool_motion
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
name|gimp_cage_tool_control
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
name|gimp_cage_tool_cursor_update
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
name|gimp_cage_tool_oper_update
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
name|gimp_cage_tool_draw
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
name|gimp_cage_tool_switch_to_deform
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_cage_tool_remove_last_handle
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCageTool,gimp_cage_tool,GIMP_TYPE_TRANSFORM_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCageTool
argument_list|,
argument|gimp_cage_tool
argument_list|,
argument|GIMP_TYPE_TRANSFORM_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cage_tool_parent_class
end_define

begin_define
DECL|macro|HANDLE_SIZE
define|#
directive|define
name|HANDLE_SIZE
value|10
end_define

begin_function
name|void
name|gimp_cage_tool_register
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
name|GIMP_TYPE_CAGE_TOOL
argument_list|,
comment|//Tool type
name|GIMP_TYPE_CAGE_OPTIONS
argument_list|,
comment|//Tool options type
name|gimp_cage_options_gui
argument_list|,
comment|//Tool opions gui
literal|0
argument_list|,
comment|//context_props
literal|"gimp-cage-tool"
argument_list|,
name|_
argument_list|(
literal|"Cage Transform"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cage Transform: Deform a selection with a cage"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Cage Transform"
argument_list|)
argument_list|,
literal|"<shift>R"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_CAGE
argument_list|,
name|GIMP_STOCK_TOOL_CAGE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_class_init (GimpCageToolClass * klass)
name|gimp_cage_tool_class_init
parameter_list|(
name|GimpCageToolClass
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
name|GimpTransformToolClass
modifier|*
name|transformtool_class
init|=
name|GIMP_TRANSFORM_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_cage_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_cage_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_cage_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_cage_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_cage_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_cage_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_cage_tool_control
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_cage_tool_cursor_update
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_cage_tool_oper_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_cage_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_init (GimpCageTool * self)
name|gimp_cage_tool_init
parameter_list|(
name|GimpCageTool
modifier|*
name|self
parameter_list|)
block|{
name|self
operator|->
name|cage
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CAGE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|self
operator|->
name|cursor_position
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|self
operator|->
name|cursor_position
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|self
operator|->
name|handle_moved
operator|=
operator|-
literal|1
expr_stmt|;
name|self
operator|->
name|cage_complete
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_cage_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_cage_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpCageTool
modifier|*
name|cage_tool
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
return|return
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|initialize
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_finalize (GObject * object)
name|gimp_cage_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|ct
operator|->
name|cage
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
DECL|function|gimp_cage_tool_start (GimpCageTool * ct,GimpDisplay * display)
name|gimp_cage_tool_start
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
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
name|ct
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCageOptions
modifier|*
name|options
init|=
name|GIMP_CAGE_TOOL_GET_OPTIONS
argument_list|(
name|ct
argument_list|)
decl_stmt|;
name|gimp_cage_tool_halt
argument_list|(
name|ct
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|draw_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_halt (GimpCageTool * ct)
name|gimp_cage_tool_halt
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|ct
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_draw_tool_is_active
argument_list|(
name|draw_tool
argument_list|)
condition|)
name|gimp_draw_tool_stop
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|NULL
expr_stmt|;
name|g_object_unref
argument_list|(
name|ct
operator|->
name|cage
argument_list|)
expr_stmt|;
name|ct
operator|->
name|cage
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CAGE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ct
operator|->
name|cursor_position
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|ct
operator|->
name|cursor_position
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|ct
operator|->
name|handle_moved
operator|=
operator|-
literal|1
expr_stmt|;
name|ct
operator|->
name|cage_complete
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_cage_tool_button_press
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
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCage
modifier|*
name|cage
init|=
name|ct
operator|->
name|cage
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
name|gimp_cage_tool_start
argument_list|(
name|ct
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ct
operator|->
name|handle_moved
operator|<
literal|0
condition|)
block|{
name|ct
operator|->
name|handle_moved
operator|=
name|gimp_cage_is_on_handle
argument_list|(
name|cage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
name|HANDLE_SIZE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ct
operator|->
name|handle_moved
operator|<
literal|0
condition|)
block|{
name|gimp_cage_add_cage_point
argument_list|(
name|cage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
comment|// user is clicking on the first handle, we close the cage and switch to deform mode
if|if
condition|(
name|ct
operator|->
name|handle_moved
operator|==
literal|0
condition|)
block|{
name|ct
operator|->
name|cage_complete
operator|=
name|TRUE
expr_stmt|;
name|gimp_cage_tool_switch_to_deform
argument_list|(
name|ct
argument_list|)
expr_stmt|;
block|}
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cage_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_cage_tool_button_release
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
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
name|ct
operator|->
name|handle_moved
operator|=
operator|-
literal|1
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_cage_tool_key_press (GimpTool * tool,GdkEventKey * kevent,GimpDisplay * display)
name|gimp_cage_tool_key_press
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
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCage
modifier|*
name|cage
init|=
name|ct
operator|->
name|cage
decl_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_BackSpace
case|:
name|gimp_cage_tool_remove_last_handle
argument_list|(
name|ct
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|GDK_Return
case|:
case|case
name|GDK_KP_Enter
case|:
case|case
name|GDK_ISO_Enter
case|:
name|gimp_cage_tool_switch_to_deform
argument_list|(
name|ct
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
case|case
name|GDK_Escape
case|:
name|gimp_cage_tool_halt
argument_list|(
name|ct
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_cage_tool_motion
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
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCage
modifier|*
name|cage
init|=
name|ct
operator|->
name|cage
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
comment|/*   if (ct->handle_moved>= 0)   {     gimp_cage_move_cage_point  (cage,                                 ct->handle_moved,                                 coords->x,                                 coords->y);   } */
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_cage_tool_control
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
name|gimp_cage_tool_halt
argument_list|(
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
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
DECL|function|gimp_cage_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_cage_tool_cursor_update
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
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCageOptions
modifier|*
name|options
init|=
name|GIMP_CAGE_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
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
block|}
else|else
block|{
name|GimpCursorModifier
name|modifier
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|cage_mode
operator|==
name|GIMP_CAGE_MODE_CAGE_CHANGE
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_ANCHOR
expr_stmt|;
block|}
else|else
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_cage_tool_oper_update
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
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCage
modifier|*
name|cage
init|=
name|ct
operator|->
name|cage
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|ct
operator|->
name|cursor_position
operator|.
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|ct
operator|->
name|cursor_position
operator|.
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
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

begin_comment
comment|/**  * gimp_cage_tool_draw:  * @draw_tool:   *   * Draw the tool on the canvas.   */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_draw (GimpDrawTool * draw_tool)
name|gimp_cage_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpCageTool
modifier|*
name|ct
init|=
name|GIMP_CAGE_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|GimpCage
modifier|*
name|cage
init|=
name|ct
operator|->
name|cage
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|gint
name|n
init|=
literal|0
decl_stmt|;
name|gint
name|on_handle
init|=
operator|-
literal|1
decl_stmt|;
if|if
condition|(
name|cage
operator|->
name|cage_vertice_number
operator|<=
literal|0
condition|)
block|{
return|return;
block|}
name|gimp_draw_tool_draw_lines
argument_list|(
name|draw_tool
argument_list|,
name|cage
operator|->
name|cage_vertices
argument_list|,
name|cage
operator|->
name|cage_vertice_number
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|ct
operator|->
name|cage_complete
condition|)
block|{
name|gimp_draw_tool_draw_line
argument_list|(
name|draw_tool
argument_list|,
name|cage
operator|->
name|cage_vertices
index|[
name|cage
operator|->
name|cage_vertice_number
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|cage
operator|->
name|cage_vertices
index|[
name|cage
operator|->
name|cage_vertice_number
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|cage
operator|->
name|cage_vertices
index|[
literal|0
index|]
operator|.
name|x
argument_list|,
name|cage
operator|->
name|cage_vertices
index|[
literal|0
index|]
operator|.
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_draw_tool_draw_line
argument_list|(
name|draw_tool
argument_list|,
name|cage
operator|->
name|cage_vertices
index|[
name|cage
operator|->
name|cage_vertice_number
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|cage
operator|->
name|cage_vertices
index|[
name|cage
operator|->
name|cage_vertice_number
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|ct
operator|->
name|cursor_position
operator|.
name|x
argument_list|,
name|ct
operator|->
name|cursor_position
operator|.
name|y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|n
operator|=
name|cage
operator|->
name|cage_vertice_number
expr_stmt|;
name|on_handle
operator|=
name|gimp_cage_is_on_handle
argument_list|(
name|cage
argument_list|,
name|ct
operator|->
name|cursor_position
operator|.
name|x
argument_list|,
name|ct
operator|->
name|cursor_position
operator|.
name|y
argument_list|,
name|HANDLE_SIZE
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
name|n
condition|;
name|i
operator|++
control|)
block|{
name|GimpVector2
name|point
init|=
name|cage
operator|->
name|cage_vertices
index|[
name|i
index|]
decl_stmt|;
name|GimpHandleType
name|handle
init|=
name|GIMP_HANDLE_CIRCLE
decl_stmt|;
if|if
condition|(
name|i
operator|==
name|on_handle
condition|)
block|{
name|handle
operator|=
name|GIMP_HANDLE_FILLED_CIRCLE
expr_stmt|;
block|}
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|handle
argument_list|,
name|point
operator|.
name|x
argument_list|,
name|point
operator|.
name|y
argument_list|,
name|HANDLE_SIZE
argument_list|,
name|HANDLE_SIZE
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_switch_to_deform (GimpCageTool * ct)
name|gimp_cage_tool_switch_to_deform
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
parameter_list|)
block|{
name|GimpCageOptions
modifier|*
name|options
init|=
name|GIMP_CAGE_TOOL_GET_OPTIONS
argument_list|(
name|ct
argument_list|)
decl_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"cage-mode"
argument_list|,
name|GIMP_CAGE_MODE_DEFORM
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_remove_last_handle (GimpCageTool * ct)
name|gimp_cage_tool_remove_last_handle
parameter_list|(
name|GimpCageTool
modifier|*
name|ct
parameter_list|)
block|{
name|GimpCage
modifier|*
name|cage
init|=
name|ct
operator|->
name|cage
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_cage_remove_last_cage_point
argument_list|(
name|cage
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

