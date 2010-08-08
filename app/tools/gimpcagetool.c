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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-transform-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-shadow.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
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

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_comment
comment|/*static gboolean     gimp_cage_tool_initialize     (GimpTool    *tool,                                                    GimpDisplay *display,                                                    GError     **error);*/
end_comment

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

begin_function_decl
specifier|static
name|void
name|gimp_cage_tool_compute_coef
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
name|gimp_cage_tool_process
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCageTool,gimp_cage_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCageTool
argument_list|,
argument|gimp_cage_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
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
value|14
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_cage_tool_finalize
expr_stmt|;
comment|/*tool_class->initialize          = gimp_cage_tool_initialize;*/
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
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CAGE_CONFIG
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
name|self
operator|->
name|coef
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/*static gboolean gimp_cage_tool_initialize (GimpTool    *tool,                            GimpDisplay *display,                            GError     **error) {   GimpCageTool *cage_tool = GIMP_CAGE_TOOL (tool);    return GIMP_TOOL_CLASS (parent_class)->initialize(tool, display, error); }*/
end_comment

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
name|config
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
name|config
argument_list|)
expr_stmt|;
name|ct
operator|->
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CAGE_CONFIG
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
name|gegl_buffer_destroy
argument_list|(
name|ct
operator|->
name|coef
argument_list|)
expr_stmt|;
name|ct
operator|->
name|coef
operator|=
name|NULL
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
name|GimpCageOptions
modifier|*
name|options
init|=
name|GIMP_CAGE_TOOL_GET_OPTIONS
argument_list|(
name|ct
argument_list|)
decl_stmt|;
name|GimpCageConfig
modifier|*
name|config
init|=
name|ct
operator|->
name|config
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CAGE_CONFIG
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_cage_config_is_on_handle
argument_list|(
name|config
argument_list|,
name|options
operator|->
name|cage_mode
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
name|gimp_cage_config_add_cage_point
argument_list|(
name|config
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
operator|&&
name|config
operator|->
name|cage_vertice_number
operator|>
literal|2
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
name|gimp_cage_config_reverse_cage_if_needed
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|gimp_cage_tool_compute_coef
argument_list|(
name|ct
argument_list|,
name|display
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
if|if
condition|(
name|ct
operator|->
name|cage_complete
condition|)
name|gimp_cage_tool_process
argument_list|(
name|ct
argument_list|,
name|display
argument_list|)
expr_stmt|;
comment|/*RUN IT BABY*/
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
name|GimpCageOptions
modifier|*
name|options
init|=
name|GIMP_CAGE_TOOL_GET_OPTIONS
argument_list|(
name|ct
argument_list|)
decl_stmt|;
name|GimpCageConfig
modifier|*
name|config
init|=
name|ct
operator|->
name|config
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|ct
operator|->
name|handle_moved
operator|>=
literal|0
condition|)
block|{
name|gimp_cage_config_move_cage_point
argument_list|(
name|config
argument_list|,
name|options
operator|->
name|cage_mode
argument_list|,
name|ct
operator|->
name|handle_moved
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
name|ct
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
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
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
name|draw_tool
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
name|GimpCageOptions
modifier|*
name|options
init|=
name|GIMP_CAGE_TOOL_GET_OPTIONS
argument_list|(
name|ct
argument_list|)
decl_stmt|;
name|GimpCageConfig
modifier|*
name|config
init|=
name|ct
operator|->
name|config
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|gint
name|on_handle
init|=
operator|-
literal|1
decl_stmt|;
name|GimpVector2
modifier|*
name|vertices
decl_stmt|;
if|if
condition|(
name|config
operator|->
name|cage_vertice_number
operator|<=
literal|0
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|options
operator|->
name|cage_mode
operator|==
name|GIMP_CAGE_MODE_CAGE_CHANGE
condition|)
block|{
name|vertices
operator|=
name|config
operator|->
name|cage_vertices
expr_stmt|;
block|}
else|else
block|{
name|vertices
operator|=
name|config
operator|->
name|cage_vertices_d
expr_stmt|;
block|}
name|gimp_draw_tool_draw_lines
argument_list|(
name|draw_tool
argument_list|,
name|vertices
argument_list|,
name|config
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
name|vertices
index|[
name|config
operator|->
name|cage_vertice_number
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|vertices
index|[
name|config
operator|->
name|cage_vertice_number
operator|-
literal|1
index|]
operator|.
name|y
argument_list|,
name|vertices
index|[
literal|0
index|]
operator|.
name|x
argument_list|,
name|vertices
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
name|vertices
index|[
name|config
operator|->
name|cage_vertice_number
operator|-
literal|1
index|]
operator|.
name|x
argument_list|,
name|vertices
index|[
name|config
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
name|on_handle
operator|=
name|gimp_cage_config_is_on_handle
argument_list|(
name|config
argument_list|,
name|options
operator|->
name|cage_mode
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
name|config
operator|->
name|cage_vertice_number
condition|;
name|i
operator|++
control|)
block|{
name|GimpVector2
name|point
init|=
name|vertices
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
name|GimpCageConfig
modifier|*
name|config
init|=
name|ct
operator|->
name|config
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|ct
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_cage_config_remove_last_cage_point
argument_list|(
name|config
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

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_compute_coef (GimpCageTool * ct,GimpDisplay * display)
name|gimp_cage_tool_compute_coef
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
name|GimpCageConfig
modifier|*
name|config
init|=
name|ct
operator|->
name|config
decl_stmt|;
name|Babl
modifier|*
name|format
decl_stmt|;
name|GeglRectangle
name|rect
decl_stmt|;
name|GeglNode
modifier|*
name|gegl
decl_stmt|,
modifier|*
name|input
decl_stmt|,
modifier|*
name|output
decl_stmt|;
name|GeglProcessor
modifier|*
name|processor
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|printf
argument_list|(
literal|"compute the coef\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|ct
operator|->
name|coef
condition|)
block|{
name|gegl_buffer_destroy
argument_list|(
name|ct
operator|->
name|coef
argument_list|)
expr_stmt|;
name|ct
operator|->
name|coef
operator|=
name|NULL
expr_stmt|;
block|}
name|format
operator|=
name|babl_format_n
argument_list|(
name|babl_type
argument_list|(
literal|"float"
argument_list|)
argument_list|,
name|config
operator|->
name|cage_vertice_number
operator|*
literal|2
argument_list|)
expr_stmt|;
name|rect
operator|=
name|gimp_cage_config_get_bounding_box
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|gegl
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|input
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:cage_coef_calc"
argument_list|,
literal|"config"
argument_list|,
name|ct
operator|->
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|output
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-sink"
argument_list|,
literal|"buffer"
argument_list|,
operator|&
name|buffer
argument_list|,
literal|"format"
argument_list|,
name|format
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|output
argument_list|)
expr_stmt|;
comment|/*progress = gimp_progress_start (GIMP_PROGRESS (display),                                 _("Coefficient computation"),                                 FALSE);    processor = gegl_node_new_processor (output,&rect);      while (gegl_processor_work (processor,&value))   {       gimp_progress_set_value (progress, value);   }    gimp_progress_end (progress);   gegl_processor_destroy (processor);*/
name|ct
operator|->
name|coef
operator|=
name|buffer
expr_stmt|;
name|g_object_unref
argument_list|(
name|gegl
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cage_tool_process (GimpCageTool * ct,GimpDisplay * display)
name|gimp_cage_tool_process
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
name|TileManager
modifier|*
name|new_tiles
decl_stmt|;
name|GeglRectangle
name|rect
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
init|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Blending"
argument_list|)
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|ct
operator|->
name|coef
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"process the cage\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|GeglNode
modifier|*
name|gegl
init|=
name|gegl_node_new
argument_list|()
decl_stmt|;
name|GeglNode
modifier|*
name|coef
decl_stmt|,
modifier|*
name|cage
decl_stmt|,
modifier|*
name|render
decl_stmt|,
modifier|*
name|input
decl_stmt|,
modifier|*
name|output
decl_stmt|;
name|input
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:tilemanager-source"
argument_list|,
literal|"tile-manager"
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|"linear"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cage
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:cage_transform"
argument_list|,
literal|"config"
argument_list|,
name|ct
operator|->
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|coef
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|ct
operator|->
name|coef
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|coef
argument_list|,
literal|"output"
argument_list|,
name|cage
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|render
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:render_mapping"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|cage
argument_list|,
literal|"output"
argument_list|,
name|render
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
comment|/*    render = gegl_node_new_child (gegl,                                   "operation", "gegl:debugit",                                   NULL);*/
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|render
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
comment|/*    gimp_drawable_apply_operation (drawable, progress, _("Cage transform"),                                    render, TRUE);*/
name|new_tiles
operator|=
name|gimp_drawable_get_shadow_tiles
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|output
operator|=
name|gegl_node_new_child
argument_list|(
name|gegl
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:tilemanager-sink"
argument_list|,
literal|"tile-manager"
argument_list|,
name|new_tiles
argument_list|,
literal|"linear"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|render
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|output
argument_list|)
expr_stmt|;
name|rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|tile_manager_width
argument_list|(
name|new_tiles
argument_list|)
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|tile_manager_height
argument_list|(
name|new_tiles
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow_tiles
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Cage transform"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_free_shadow_tiles
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|width
argument_list|,
name|rect
operator|.
name|height
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gegl
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_cage_tool_halt
argument_list|(
name|ct
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

