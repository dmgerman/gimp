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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b86dafe0103
block|{
DECL|enumerator|INITIALIZE
name|INITIALIZE
block|,
DECL|enumerator|CONTROL
name|CONTROL
block|,
DECL|enumerator|BUTTON_PRESS
name|BUTTON_PRESS
block|,
DECL|enumerator|BUTTON_RELEASE
name|BUTTON_RELEASE
block|,
DECL|enumerator|MOTION
name|MOTION
block|,
DECL|enumerator|ARROW_KEY
name|ARROW_KEY
block|,
DECL|enumerator|MODIFIER_KEY
name|MODIFIER_KEY
block|,
DECL|enumerator|CURSOR_UPDATE
name|CURSOR_UPDATE
block|,
DECL|enumerator|OPER_UPDATE
name|OPER_UPDATE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_tool_class_init
parameter_list|(
name|GimpToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_init
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|destroy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|tool_action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_arrow_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_real_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_tool_signals
specifier|static
name|guint
name|gimp_tool_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_tool_ID
specifier|static
name|gint
name|global_tool_ID
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_tool_get_type (void)
name|gimp_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
name|GtkTypeInfo
name|tool_info
init|=
block|{
literal|"GimpTool"
block|,
sizeof|sizeof
argument_list|(
name|GimpTool
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpToolClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_tool_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_tool_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
operator|&
name|tool_info
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_class_init (GimpToolClass * klass)
name|gimp_tool_class_init
parameter_list|(
name|GimpToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|INITIALIZE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"initialize"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|initialize
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|CONTROL
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"control"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|control
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__INT_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|BUTTON_PRESS
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"button_press"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|button_press
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|BUTTON_RELEASE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"button_release"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|button_release
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|MOTION
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"motion"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|motion
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|ARROW_KEY
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"arrow_key"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|arrow_key
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|MODIFIER_KEY
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"modifier_key"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|modifier_key
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|CURSOR_UPDATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"cursor_update"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|cursor_update
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gimp_tool_signals
index|[
name|OPER_UPDATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"oper_update"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolClass
argument_list|,
name|oper_update
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_VOID__POINTER_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_tool_destroy
expr_stmt|;
name|klass
operator|->
name|initialize
operator|=
name|gimp_tool_real_initialize
expr_stmt|;
name|klass
operator|->
name|control
operator|=
name|gimp_tool_real_control
expr_stmt|;
name|klass
operator|->
name|button_press
operator|=
name|gimp_tool_real_button_press
expr_stmt|;
name|klass
operator|->
name|button_release
operator|=
name|gimp_tool_real_button_release
expr_stmt|;
name|klass
operator|->
name|motion
operator|=
name|gimp_tool_real_motion
expr_stmt|;
name|klass
operator|->
name|arrow_key
operator|=
name|gimp_tool_real_arrow_key
expr_stmt|;
name|klass
operator|->
name|modifier_key
operator|=
name|gimp_tool_real_modifier_key
expr_stmt|;
name|klass
operator|->
name|cursor_update
operator|=
name|gimp_tool_real_cursor_update
expr_stmt|;
name|klass
operator|->
name|oper_update
operator|=
name|gimp_tool_real_oper_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_init (GimpTool * tool)
name|gimp_tool_init
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|tool
operator|->
name|ID
operator|=
name|global_tool_ID
operator|++
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
name|tool
operator|->
name|paused_count
operator|=
literal|0
expr_stmt|;
name|tool
operator|->
name|scroll_lock
operator|=
name|FALSE
expr_stmt|;
comment|/*  Allow scrolling  */
name|tool
operator|->
name|auto_snap_to
operator|=
name|TRUE
expr_stmt|;
comment|/*  Snap to guides   */
name|tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
comment|/*  Preserve tool across drawable changes  */
name|tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
name|tool
operator|->
name|toggle_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
name|tool
operator|->
name|toggled
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_destroy (GtkObject * object)
name|gimp_tool_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_initialize (GimpTool * tool,GDisplay * gdisp)
name|gimp_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|INITIALIZE
index|]
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control (GimpTool * tool,ToolAction action,GDisplay * gdisp)
name|gimp_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|CONTROL
index|]
argument_list|,
name|action
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_button_press (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|BUTTON_PRESS
index|]
argument_list|,
name|bevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_button_release (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|BUTTON_RELEASE
index|]
argument_list|,
name|bevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_motion (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|MOTION
index|]
argument_list|,
name|mevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_arrow_key (GimpTool * tool,GdkEventKey * kevent,GDisplay * gdisp)
name|gimp_tool_arrow_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|ARROW_KEY
index|]
argument_list|,
name|kevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_modifier_key (GimpTool * tool,GdkEventKey * kevent,GDisplay * gdisp)
name|gimp_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|MODIFIER_KEY
index|]
argument_list|,
name|kevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_cursor_update (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|CURSOR_UPDATE
index|]
argument_list|,
name|mevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_oper_update (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gimp_tool_signals
index|[
name|OPER_UPDATE
index|]
argument_list|,
name|mevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_get_PDB_string (GimpTool * tool)
name|gimp_tool_get_PDB_string
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|GtkObject
modifier|*
name|object
decl_stmt|;
name|GimpToolClass
modifier|*
name|klass
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|object
operator|=
name|GTK_OBJECT
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|klass
operator|=
name|GIMP_TOOL_GET_CLASS
argument_list|(
name|object
argument_list|)
expr_stmt|;
return|return
name|klass
operator|->
name|pdb_string
return|;
block|}
end_function

begin_comment
comment|/*  standard member functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_initialize (GimpTool * tool,GDisplay * gdisp)
name|gimp_tool_real_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_control (GimpTool * tool,ToolAction tool_action,GDisplay * gdisp)
name|gimp_tool_real_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|tool_action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_button_press (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_tool_real_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_button_release (GimpTool * tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_tool_real_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_motion (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_tool_real_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_arrow_key (GimpTool * tool,GdkEventKey * kevent,GDisplay * gdisp)
name|gimp_tool_real_arrow_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_modifier_key (GimpTool * tool,GdkEventKey * kevent,GDisplay * gdisp)
name|gimp_tool_real_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_cursor_update (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_tool_real_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_TOP_LEFT_ARROW
argument_list|,
name|tool
operator|->
name|tool_cursor
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_real_oper_update (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_tool_real_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  Function definitions  */
end_comment

begin_function
name|void
DECL|function|gimp_tool_help_func (const gchar * help_data)
name|gimp_tool_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|gimp_standard_help_func
argument_list|(
name|tool_manager_active_get_help_data
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_define
DECL|macro|STUB (x)
define|#
directive|define
name|STUB
parameter_list|(
name|x
parameter_list|)
value|void * x (void){g_message ("stub function %s called",#x); return NULL;}
end_define

begin_macro
name|STUB
argument_list|(
argument|clone_non_gui
argument_list|)
end_macro

begin_macro
name|STUB
argument_list|(
argument|clone_non_gui_default
argument_list|)
end_macro

begin_macro
name|STUB
argument_list|(
argument|convolve_non_gui
argument_list|)
end_macro

begin_macro
name|STUB
argument_list|(
argument|convolve_non_gui_default
argument_list|)
end_macro

end_unit

