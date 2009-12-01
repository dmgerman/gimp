begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-dock.c  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpdockwindow.h"
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

begin_include
include|#
directive|include
file|"gimpsessioninfo-private.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b7796050103
block|{
DECL|enumerator|SESSION_INFO_BOOK
name|SESSION_INFO_BOOK
block|}
enum|;
end_enum

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_session_info_dock_serialize (GimpConfigWriter * writer,GList * books)
name|gimp_session_info_dock_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GList
modifier|*
name|books
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|books
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"dock"
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|books
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gimp_session_info_book_serialize
argument_list|(
name|writer
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GTokenType
DECL|function|gimp_session_info_dock_deserialize (GScanner * scanner,gint scope,GimpSessionInfo * info)
name|gimp_session_info_dock_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|scope
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|GTokenType
name|token
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
name|g_return_val_if_fail
argument_list|(
name|info
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
literal|"book"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_BOOK
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
name|GimpSessionInfoBook
modifier|*
name|book
decl_stmt|;
case|case
name|SESSION_INFO_BOOK
case|:
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
name|gimp_session_info_book_deserialize
argument_list|(
name|scanner
argument_list|,
name|scope
operator|+
literal|1
argument_list|,
operator|&
name|book
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|info
operator|->
name|p
operator|->
name|books
operator|=
name|g_list_append
argument_list|(
name|info
operator|->
name|p
operator|->
name|books
argument_list|,
name|book
argument_list|)
expr_stmt|;
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|)
expr_stmt|;
block|}
else|else
return|return
name|token
return|;
break|break;
default|default:
return|return
name|token
return|;
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
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"book"
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_session_info_dock_from_widget (GimpDock * dock)
name|gimp_session_info_dock_from_widget
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GList
modifier|*
name|infos
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_dock_get_dockbooks
argument_list|(
name|dock
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpSessionInfoBook
modifier|*
name|book
decl_stmt|;
name|book
operator|=
name|gimp_session_info_book_from_widget
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|infos
operator|=
name|g_list_prepend
argument_list|(
name|infos
argument_list|,
name|book
argument_list|)
expr_stmt|;
block|}
return|return
name|g_list_reverse
argument_list|(
name|infos
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_session_info_dock_paned_size_allocate (GtkWidget * paned,GtkAllocation * allocation,gpointer data)
name|gimp_session_info_dock_paned_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|paned
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|paned
argument_list|,
name|gimp_session_info_dock_paned_size_allocate
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_paned_set_position
argument_list|(
name|GTK_PANED
argument_list|(
name|paned
argument_list|)
argument_list|,
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_session_info_dock_paned_map (GtkWidget * paned,gpointer data)
name|gimp_session_info_dock_paned_map
parameter_list|(
name|GtkWidget
modifier|*
name|paned
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|paned
argument_list|,
name|gimp_session_info_dock_paned_map
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|paned
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_session_info_dock_paned_size_allocate
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_dock_restore (GimpSessionInfo * info,GimpDialogFactory * factory,GdkScreen * screen)
name|gimp_session_info_dock_restore
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkScreen
modifier|*
name|screen
parameter_list|)
block|{
name|GimpDock
modifier|*
name|dock
init|=
name|NULL
decl_stmt|;
name|GimpDockWindow
modifier|*
name|dock_window
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|books
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
name|g_return_if_fail
argument_list|(
name|GDK_IS_SCREEN
argument_list|(
name|screen
argument_list|)
argument_list|)
expr_stmt|;
name|dock
operator|=
name|GIMP_DOCK
argument_list|(
name|gimp_dialog_factory_dock_with_window_new
argument_list|(
name|factory
argument_list|,
name|screen
argument_list|)
argument_list|)
expr_stmt|;
name|dock_window
operator|=
name|gimp_dock_window_from_dock
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dock
operator|&&
name|info
operator|->
name|p
operator|->
name|aux_info
condition|)
name|gimp_session_info_aux_set_list
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|,
name|info
operator|->
name|p
operator|->
name|aux_info
argument_list|)
expr_stmt|;
for|for
control|(
name|books
operator|=
name|info
operator|->
name|p
operator|->
name|books
init|;
name|books
condition|;
name|books
operator|=
name|g_list_next
argument_list|(
name|books
argument_list|)
control|)
block|{
name|GimpSessionInfoBook
modifier|*
name|book_info
init|=
name|books
operator|->
name|data
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
decl_stmt|;
name|dockbook
operator|=
name|GTK_WIDGET
argument_list|(
name|gimp_session_info_book_restore
argument_list|(
name|book_info
argument_list|,
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|dockbook
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_VPANED
argument_list|(
name|parent
argument_list|)
condition|)
block|{
name|GtkPaned
modifier|*
name|paned
init|=
name|GTK_PANED
argument_list|(
name|parent
argument_list|)
decl_stmt|;
if|if
condition|(
name|dockbook
operator|==
name|gtk_paned_get_child2
argument_list|(
name|paned
argument_list|)
condition|)
name|g_signal_connect_after
argument_list|(
name|paned
argument_list|,
literal|"map"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_session_info_dock_paned_map
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|book_info
operator|->
name|position
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

