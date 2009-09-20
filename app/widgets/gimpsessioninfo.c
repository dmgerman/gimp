begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo.c  * Copyright (C) 2001-2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-aux.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-book.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-dock.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29ed32100103
block|{
DECL|enumerator|SESSION_INFO_POSITION
name|SESSION_INFO_POSITION
block|,
DECL|enumerator|SESSION_INFO_SIZE
name|SESSION_INFO_SIZE
block|,
DECL|enumerator|SESSION_INFO_OPEN
name|SESSION_INFO_OPEN
block|,
DECL|enumerator|SESSION_INFO_AUX
name|SESSION_INFO_AUX
block|,
DECL|enumerator|SESSION_INFO_DOCK
name|SESSION_INFO_DOCK
block|}
enum|;
end_enum

begin_define
DECL|macro|DEFAULT_SCREEN
define|#
directive|define
name|DEFAULT_SCREEN
value|-1
end_define

begin_function_decl
specifier|static
name|void
name|gimp_session_info_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_session_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_session_info_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_session_info_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_session_info_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_session_info_is_for_dock
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpSessionInfo,gimp_session_info,GIMP_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,gimp_session_info_config_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpSessionInfo
argument_list|,
argument|gimp_session_info
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_session_info_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_session_info_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_session_info_class_init
parameter_list|(
name|GimpSessionInfoClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_session_info_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_session_info_get_memsize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_session_info_init (GimpSessionInfo * info)
name|gimp_session_info_init
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|info
operator|->
name|screen
operator|=
name|DEFAULT_SCREEN
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_session_info_config_iface_init (GimpConfigInterface * iface)
name|gimp_session_info_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|serialize
operator|=
name|gimp_session_info_serialize
expr_stmt|;
name|iface
operator|->
name|deserialize
operator|=
name|gimp_session_info_deserialize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_session_info_finalize (GObject * object)
name|gimp_session_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSessionInfo
modifier|*
name|info
init|=
name|GIMP_SESSION_INFO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_session_info_clear_info
argument_list|(
name|info
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
name|gint64
DECL|function|gimp_session_info_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_session_info_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GimpSessionInfo *info    = GIMP_SESSION_INFO (object);
endif|#
directive|endif
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_session_info_serialize (GimpConfig * config,GimpConfigWriter * writer,gpointer data)
name|gimp_session_info_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpSessionInfo
modifier|*
name|info
init|=
name|GIMP_SESSION_INFO
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"position"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d %d"
argument_list|,
name|info
operator|->
name|x
argument_list|,
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|width
operator|>
literal|0
operator|&&
name|info
operator|->
name|height
operator|>
literal|0
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"size"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d %d"
argument_list|,
name|info
operator|->
name|width
argument_list|,
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|info
operator|->
name|open
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"open-on-exit"
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|screen
operator|!=
name|DEFAULT_SCREEN
condition|)
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|info
operator|->
name|screen
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|info
operator|->
name|aux_info
condition|)
name|gimp_session_info_aux_serialize
argument_list|(
name|writer
argument_list|,
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|books
condition|)
name|gimp_session_info_dock_serialize
argument_list|(
name|writer
argument_list|,
name|info
operator|->
name|books
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * This function is just like gimp_scanner_parse_int(), but it is allows  * to detect the special value '-0'. This is used as in X geometry strings.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_session_info_parse_offset (GScanner * scanner,gint * dest,gboolean * negative)
name|gimp_session_info_parse_offset
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
modifier|*
name|dest
parameter_list|,
name|gboolean
modifier|*
name|negative
parameter_list|)
block|{
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
literal|'-'
condition|)
block|{
operator|*
name|negative
operator|=
name|TRUE
expr_stmt|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|negative
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|G_TOKEN_INT
condition|)
return|return
name|FALSE
return|;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|negative
condition|)
operator|*
name|dest
operator|=
operator|-
name|scanner
operator|->
name|value
operator|.
name|v_int64
expr_stmt|;
else|else
operator|*
name|dest
operator|=
name|scanner
operator|->
name|value
operator|.
name|v_int64
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_session_info_deserialize (GimpConfig * config,GScanner * scanner,gint nest_level,gpointer data)
name|gimp_session_info_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|nest_level
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpSessionInfo
modifier|*
name|info
init|=
name|GIMP_SESSION_INFO
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|guint
name|scope_id
decl_stmt|;
name|guint
name|old_scope_id
decl_stmt|;
name|scope_id
operator|=
name|g_type_qname
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|old_scope_id
operator|=
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"position"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_POSITION
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"size"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_SIZE
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"open-on-exit"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_OPEN
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"aux-info"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_AUX
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"dock"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_DOCK
argument_list|)
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
switch|switch
condition|(
name|GPOINTER_TO_INT
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
argument_list|)
condition|)
block|{
case|case
name|SESSION_INFO_POSITION
case|:
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_session_info_parse_offset
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|x
argument_list|,
operator|&
name|info
operator|->
name|right_align
argument_list|)
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|gimp_session_info_parse_offset
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|y
argument_list|,
operator|&
name|info
operator|->
name|bottom_align
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_SIZE
case|:
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|width
argument_list|)
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|height
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_OPEN
case|:
name|info
operator|->
name|open
operator|=
name|TRUE
expr_stmt|;
comment|/*  the screen number is optional  */
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|G_TOKEN_RIGHT_PAREN
condition|)
break|break;
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|screen
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_AUX
case|:
name|token
operator|=
name|gimp_session_info_aux_deserialize
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_PAREN
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_DOCK
case|:
if|if
condition|(
name|info
operator|->
name|toplevel_entry
condition|)
goto|goto
name|error
goto|;
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|scope_id
operator|+
literal|1
argument_list|)
expr_stmt|;
name|token
operator|=
name|gimp_session_info_dock_deserialize
argument_list|(
name|scanner
argument_list|,
name|scope_id
operator|+
literal|1
argument_list|,
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|)
expr_stmt|;
else|else
goto|goto
name|error
goto|;
break|break;
default|default:
break|break;
block|}
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
name|error
label|:
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"position"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"size"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"open-on-exit"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"aux-info"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope_id
argument_list|,
literal|"dock"
argument_list|)
expr_stmt|;
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|old_scope_id
argument_list|)
expr_stmt|;
return|return
name|gimp_config_deserialize_return
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|,
name|nest_level
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_session_info_is_for_dock:  * @info:  *  * Helper function to determine if the session info is for a dock. It  * uses the dialog factory entry state and the associated widget state  * if any to determine that.  *  * Returns: %TRUE if session info is for a dock, %FALSE otherwise.  **/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_session_info_is_for_dock (GimpSessionInfo * info)
name|gimp_session_info_is_for_dock
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|gboolean
name|entry_state_for_dock
init|=
operator|(
operator|!
name|info
operator|->
name|toplevel_entry
operator|&&
operator|!
name|info
operator|->
name|dockable_entry
operator|)
decl_stmt|;
name|gboolean
name|widget_state_for_dock
init|=
operator|(
name|info
operator|->
name|widget
operator|==
name|NULL
operator|||
name|GIMP_IS_DOCK
argument_list|(
name|info
operator|->
name|widget
argument_list|)
operator|)
decl_stmt|;
return|return
name|entry_state_for_dock
operator|&&
name|widget_state_for_dock
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpSessionInfo
modifier|*
DECL|function|gimp_session_info_new (void)
name|gimp_session_info_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_SESSION_INFO
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_restore (GimpSessionInfo * info,GimpDialogFactory * factory)
name|gimp_session_info_restore
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|)
expr_stmt|;
name|display
operator|=
name|gdk_display_get_default
argument_list|()
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|screen
operator|!=
name|DEFAULT_SCREEN
condition|)
name|screen
operator|=
name|gdk_display_get_screen
argument_list|(
name|display
argument_list|,
name|info
operator|->
name|screen
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|screen
condition|)
name|screen
operator|=
name|gdk_display_get_default_screen
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|info
operator|->
name|open
operator|=
name|FALSE
expr_stmt|;
name|info
operator|->
name|screen
operator|=
name|DEFAULT_SCREEN
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|toplevel_entry
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|factory
argument_list|,
name|screen
argument_list|,
name|info
operator|->
name|toplevel_entry
operator|->
name|identifier
argument_list|,
name|info
operator|->
name|toplevel_entry
operator|->
name|view_size
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|&&
name|info
operator|->
name|aux_info
condition|)
name|gimp_session_info_aux_set_list
argument_list|(
name|dialog
argument_list|,
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_session_info_dock_restore
argument_list|(
name|info
argument_list|,
name|factory
argument_list|,
name|screen
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* This function mostly lifted from  * gtk+/gdk/gdkscreen.c:gdk_screen_get_monitor_at_window()  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|gimp_session_info_get_appropriate_monitor (GdkScreen * screen,gint x,gint y,gint w,gint h)
name|gimp_session_info_get_appropriate_monitor
parameter_list|(
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GdkRectangle
name|rect
decl_stmt|;
name|gint
name|area
init|=
literal|0
decl_stmt|;
name|gint
name|monitor
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|num_monitors
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|rect
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|w
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|h
expr_stmt|;
name|num_monitors
operator|=
name|gdk_screen_get_n_monitors
argument_list|(
name|screen
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
name|num_monitors
condition|;
name|i
operator|++
control|)
block|{
name|GdkRectangle
name|geometry
decl_stmt|;
name|gdk_screen_get_monitor_geometry
argument_list|(
name|screen
argument_list|,
name|i
argument_list|,
operator|&
name|geometry
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_rectangle_intersect
argument_list|(
operator|&
name|rect
argument_list|,
operator|&
name|geometry
argument_list|,
operator|&
name|geometry
argument_list|)
operator|&&
name|geometry
operator|.
name|width
operator|*
name|geometry
operator|.
name|height
operator|>
name|area
condition|)
block|{
name|area
operator|=
name|geometry
operator|.
name|width
operator|*
name|geometry
operator|.
name|height
expr_stmt|;
name|monitor
operator|=
name|i
expr_stmt|;
block|}
block|}
if|if
condition|(
name|monitor
operator|>=
literal|0
condition|)
return|return
name|monitor
return|;
else|else
return|return
name|gdk_screen_get_monitor_at_point
argument_list|(
name|screen
argument_list|,
name|rect
operator|.
name|x
operator|+
name|rect
operator|.
name|width
operator|/
literal|2
argument_list|,
name|rect
operator|.
name|y
operator|+
name|rect
operator|.
name|height
operator|/
literal|2
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_set_geometry (GimpSessionInfo * info)
name|gimp_session_info_set_geometry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|;
name|gchar
name|geom
index|[
literal|32
index|]
decl_stmt|;
name|gint
name|monitor
decl_stmt|;
name|gboolean
name|use_size
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WINDOW
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|info
operator|->
name|widget
argument_list|)
expr_stmt|;
name|use_size
operator|=
operator|(
name|gimp_session_info_get_remember_size
argument_list|(
name|info
argument_list|)
operator|&&
name|info
operator|->
name|width
operator|>
literal|0
operator|&&
name|info
operator|->
name|height
operator|>
literal|0
operator|)
expr_stmt|;
if|if
condition|(
name|use_size
condition|)
block|{
name|monitor
operator|=
name|gimp_session_info_get_appropriate_monitor
argument_list|(
name|screen
argument_list|,
name|info
operator|->
name|x
argument_list|,
name|info
operator|->
name|y
argument_list|,
name|info
operator|->
name|width
argument_list|,
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|monitor
operator|=
name|gdk_screen_get_monitor_at_point
argument_list|(
name|screen
argument_list|,
name|info
operator|->
name|x
argument_list|,
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
name|gdk_screen_get_monitor_geometry
argument_list|(
name|screen
argument_list|,
name|monitor
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|info
operator|->
name|x
operator|=
name|CLAMP
argument_list|(
name|info
operator|->
name|x
argument_list|,
name|rect
operator|.
name|x
argument_list|,
name|rect
operator|.
name|x
operator|+
name|rect
operator|.
name|width
operator|-
operator|(
name|info
operator|->
name|width
operator|>
literal|0
condition|?
name|info
operator|->
name|width
else|:
literal|128
operator|)
argument_list|)
expr_stmt|;
name|info
operator|->
name|y
operator|=
name|CLAMP
argument_list|(
name|info
operator|->
name|y
argument_list|,
name|rect
operator|.
name|y
argument_list|,
name|rect
operator|.
name|y
operator|+
name|rect
operator|.
name|height
operator|-
operator|(
name|info
operator|->
name|height
operator|>
literal|0
condition|?
name|info
operator|->
name|height
else|:
literal|128
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|right_align
operator|&&
name|info
operator|->
name|bottom_align
condition|)
block|{
name|g_strlcpy
argument_list|(
name|geom
argument_list|,
literal|"-0-0"
argument_list|,
sizeof|sizeof
argument_list|(
name|geom
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|info
operator|->
name|right_align
condition|)
block|{
name|g_snprintf
argument_list|(
name|geom
argument_list|,
sizeof|sizeof
argument_list|(
name|geom
argument_list|)
argument_list|,
literal|"-0%+d"
argument_list|,
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|info
operator|->
name|bottom_align
condition|)
block|{
name|g_snprintf
argument_list|(
name|geom
argument_list|,
sizeof|sizeof
argument_list|(
name|geom
argument_list|)
argument_list|,
literal|"%+d-0"
argument_list|,
name|info
operator|->
name|x
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_snprintf
argument_list|(
name|geom
argument_list|,
sizeof|sizeof
argument_list|(
name|geom
argument_list|)
argument_list|,
literal|"%+d%+d"
argument_list|,
name|info
operator|->
name|x
argument_list|,
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
name|gtk_window_parse_geometry
argument_list|(
name|GTK_WINDOW
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|,
name|geom
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_size
condition|)
name|gtk_window_set_default_size
argument_list|(
name|GTK_WINDOW
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|,
name|info
operator|->
name|width
argument_list|,
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_get_geometry (GimpSessionInfo * info)
name|gimp_session_info_get_geometry
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WINDOW
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|window
operator|=
name|gtk_widget_get_window
argument_list|(
name|info
operator|->
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
condition|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdk_window_get_root_origin
argument_list|(
name|window
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
comment|/* Don't write negative values to the sessionrc, they are        * interpreted as relative to the right, respective bottom edge        * of the screen.        */
name|info
operator|->
name|x
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|info
operator|->
name|y
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_session_info_get_remember_size
argument_list|(
name|info
argument_list|)
condition|)
block|{
name|gdk_drawable_get_size
argument_list|(
name|GDK_DRAWABLE
argument_list|(
name|window
argument_list|)
argument_list|,
operator|&
name|info
operator|->
name|width
argument_list|,
operator|&
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|info
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|info
operator|->
name|height
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|info
operator|->
name|open
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|gimp_session_info_get_remember_if_open
argument_list|(
name|info
argument_list|)
condition|)
block|{
name|GimpDialogVisibilityState
name|visibility
decl_stmt|;
name|visibility
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|,
name|GIMP_DIALOG_VISIBILITY_KEY
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|visibility
condition|)
block|{
case|case
name|GIMP_DIALOG_VISIBILITY_UNKNOWN
case|:
name|info
operator|->
name|open
operator|=
name|GTK_WIDGET_VISIBLE
argument_list|(
name|info
operator|->
name|widget
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_DIALOG_VISIBILITY_INVISIBLE
case|:
name|info
operator|->
name|open
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|GIMP_DIALOG_VISIBILITY_VISIBLE
case|:
name|info
operator|->
name|open
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
block|}
name|info
operator|->
name|screen
operator|=
name|DEFAULT_SCREEN
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|open
condition|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gtk_widget_get_display
argument_list|(
name|info
operator|->
name|widget
argument_list|)
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
init|=
name|gtk_widget_get_screen
argument_list|(
name|info
operator|->
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|screen
operator|!=
name|gdk_display_get_default_screen
argument_list|(
name|display
argument_list|)
condition|)
name|info
operator|->
name|screen
operator|=
name|gdk_screen_get_number
argument_list|(
name|screen
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_get_info (GimpSessionInfo * info)
name|gimp_session_info_get_info
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_session_info_get_geometry
argument_list|(
name|info
argument_list|)
expr_stmt|;
name|info
operator|->
name|aux_info
operator|=
name|gimp_session_info_aux_get_list
argument_list|(
name|info
operator|->
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|info
operator|->
name|toplevel_entry
condition|)
name|info
operator|->
name|books
operator|=
name|gimp_session_info_dock_from_widget
argument_list|(
name|GIMP_DOCK
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_clear_info (GimpSessionInfo * info)
name|gimp_session_info_clear_info
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|aux_info
condition|)
block|{
name|g_list_foreach
argument_list|(
name|info
operator|->
name|aux_info
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_session_info_aux_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|info
operator|->
name|aux_info
argument_list|)
expr_stmt|;
name|info
operator|->
name|aux_info
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|info
operator|->
name|books
condition|)
block|{
name|g_list_foreach
argument_list|(
name|info
operator|->
name|books
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_session_info_book_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|info
operator|->
name|books
argument_list|)
expr_stmt|;
name|info
operator|->
name|books
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_session_info_is_singleton (GimpSessionInfo * info)
name|gimp_session_info_is_singleton
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
operator|!
name|gimp_session_info_is_for_dock
argument_list|(
name|info
argument_list|)
operator|&&
name|info
operator|->
name|toplevel_entry
operator|&&
name|info
operator|->
name|toplevel_entry
operator|->
name|singleton
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_session_info_is_session_managed (GimpSessionInfo * info)
name|gimp_session_info_is_session_managed
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|gimp_session_info_is_for_dock
argument_list|(
name|info
argument_list|)
operator|||
operator|(
name|info
operator|->
name|toplevel_entry
operator|&&
name|info
operator|->
name|toplevel_entry
operator|->
name|session_managed
operator|)
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_session_info_get_remember_size (GimpSessionInfo * info)
name|gimp_session_info_get_remember_size
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|gimp_session_info_is_for_dock
argument_list|(
name|info
argument_list|)
operator|||
operator|(
name|info
operator|->
name|toplevel_entry
operator|&&
name|info
operator|->
name|toplevel_entry
operator|->
name|remember_size
operator|)
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_session_info_get_remember_if_open (GimpSessionInfo * info)
name|gimp_session_info_get_remember_if_open
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SESSION_INFO
argument_list|(
name|info
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
operator|(
name|gimp_session_info_is_for_dock
argument_list|(
name|info
argument_list|)
operator|||
operator|(
name|info
operator|->
name|toplevel_entry
operator|&&
name|info
operator|->
name|toplevel_entry
operator|->
name|remember_if_open
operator|)
operator|)
return|;
block|}
end_function

end_unit

