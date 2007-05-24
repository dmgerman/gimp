begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo.c  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpsessioninfoaux.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfobook.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfodock.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2992793a0103
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
name|g_slice_new0
argument_list|(
name|GimpSessionInfo
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_free (GimpSessionInfo * info)
name|gimp_session_info_free
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|info
operator|!=
name|NULL
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
block|}
name|g_slice_free
argument_list|(
name|GimpSessionInfo
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_serialize (GimpConfigWriter * writer,GimpSessionInfo * info,const gchar * factory_name)
name|gimp_session_info_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|factory_name
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|dialog_name
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|info
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|factory_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|widget
condition|)
name|gimp_session_info_get_geometry
argument_list|(
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|toplevel_entry
condition|)
name|dialog_name
operator|=
name|info
operator|->
name|toplevel_entry
operator|->
name|identifier
expr_stmt|;
else|else
name|dialog_name
operator|=
literal|"dock"
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"session-info"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|factory_name
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|dialog_name
argument_list|)
expr_stmt|;
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
name|widget
condition|)
block|{
name|gimp_session_info_aux_serialize
argument_list|(
name|writer
argument_list|,
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
name|gimp_session_info_dock_serialize
argument_list|(
name|writer
argument_list|,
name|GIMP_DOCK
argument_list|(
name|info
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
comment|/* session-info */
block|}
end_function

begin_function
name|GTokenType
DECL|function|gimp_session_info_deserialize (GScanner * scanner,gint scope)
name|gimp_session_info_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|scope
parameter_list|)
block|{
name|GimpDialogFactory
modifier|*
name|factory
decl_stmt|;
name|GimpSessionInfo
modifier|*
name|info
init|=
name|NULL
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|gboolean
name|skip
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|factory_name
decl_stmt|;
name|gchar
modifier|*
name|entry_name
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|scanner
operator|!=
name|NULL
argument_list|,
name|G_TOKEN_LEFT_PAREN
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
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
name|scope
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
name|scope
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
name|scope
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
name|scope
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
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|factory_name
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
name|factory_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|factory_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|factory
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|entry_name
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|info
operator|=
name|gimp_session_info_new
argument_list|()
expr_stmt|;
name|info
operator|->
name|screen
operator|=
name|DEFAULT_SCREEN
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|entry_name
argument_list|,
literal|"dock"
argument_list|)
condition|)
block|{
name|info
operator|->
name|toplevel_entry
operator|=
name|gimp_dialog_factory_find_entry
argument_list|(
name|factory
argument_list|,
name|entry_name
argument_list|)
expr_stmt|;
name|skip
operator|=
operator|(
name|info
operator|->
name|toplevel_entry
operator|==
name|NULL
operator|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|entry_name
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
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|x
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
name|y
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
name|scope
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
name|scope
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
name|scope
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
if|if
condition|(
name|token
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
if|if
condition|(
operator|!
name|skip
operator|&&
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
name|factory
operator|->
name|session_infos
operator|=
name|g_list_append
argument_list|(
name|factory
operator|->
name|session_infos
argument_list|,
name|info
argument_list|)
expr_stmt|;
else|else
name|gimp_session_info_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|error
label|:
if|if
condition|(
name|info
condition|)
name|gimp_session_info_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"position"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"size"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"open-on-exit"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"aux-info"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"dock"
argument_list|)
expr_stmt|;
return|return
name|token
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
name|info
operator|!=
name|NULL
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
end_function

begin_comment
comment|/* This function mostly lifted from  * gtk+/gdk/gdkscreen.c:gdk_screen_get_monitor_at_window()  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|get_appropriate_monitor (GdkScreen * screen,gint x,gint y,gint w,gint h)
name|get_appropriate_monitor
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
name|monitor
decl_stmt|;
name|gchar
name|geom
index|[
literal|32
index|]
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|info
operator|!=
name|NULL
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
if|if
condition|(
operator|(
operator|!
name|info
operator|->
name|toplevel_entry
operator|||
name|info
operator|->
name|toplevel_entry
operator|->
name|remember_size
operator|)
operator|&&
operator|(
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
condition|)
block|{
name|gdk_screen_get_monitor_geometry
argument_list|(
name|screen
argument_list|,
name|get_appropriate_monitor
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
argument_list|,
operator|&
name|monitor
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
name|monitor
operator|.
name|x
argument_list|,
name|monitor
operator|.
name|x
operator|+
name|monitor
operator|.
name|width
operator|-
name|info
operator|->
name|width
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
name|monitor
operator|.
name|y
argument_list|,
name|monitor
operator|.
name|y
operator|+
name|monitor
operator|.
name|height
operator|-
name|info
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_screen_get_monitor_geometry
argument_list|(
name|screen
argument_list|,
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
argument_list|,
operator|&
name|monitor
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
name|monitor
operator|.
name|x
argument_list|,
name|monitor
operator|.
name|x
operator|+
name|monitor
operator|.
name|width
operator|-
literal|128
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
name|monitor
operator|.
name|y
argument_list|,
name|monitor
operator|.
name|y
operator|+
name|monitor
operator|.
name|height
operator|-
literal|128
argument_list|)
expr_stmt|;
block|}
name|g_snprintf
argument_list|(
name|geom
argument_list|,
sizeof|sizeof
argument_list|(
name|geom
argument_list|)
argument_list|,
literal|"+%d+%d"
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
operator|!
name|info
operator|->
name|toplevel_entry
operator|||
name|info
operator|->
name|toplevel_entry
operator|->
name|remember_size
condition|)
block|{
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
name|g_return_if_fail
argument_list|(
name|info
operator|!=
name|NULL
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
if|if
condition|(
name|info
operator|->
name|widget
operator|->
name|window
condition|)
block|{
name|gdk_window_get_root_origin
argument_list|(
name|info
operator|->
name|widget
operator|->
name|window
argument_list|,
operator|&
name|info
operator|->
name|x
argument_list|,
operator|&
name|info
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|info
operator|->
name|toplevel_entry
operator|||
name|info
operator|->
name|toplevel_entry
operator|->
name|remember_size
condition|)
block|{
name|info
operator|->
name|width
operator|=
name|info
operator|->
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|info
operator|->
name|height
operator|=
name|info
operator|->
name|widget
operator|->
name|allocation
operator|.
name|height
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
operator|!
name|info
operator|->
name|toplevel_entry
operator|||
name|info
operator|->
name|toplevel_entry
operator|->
name|remember_if_open
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

end_unit

