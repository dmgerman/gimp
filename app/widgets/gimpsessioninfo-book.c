begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-book.c  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-book.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo-dockable.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b4f85590103
block|{
DECL|enumerator|SESSION_INFO_BOOK_POSITION
name|SESSION_INFO_BOOK_POSITION
block|,
DECL|enumerator|SESSION_INFO_BOOK_CURRENT_PAGE
name|SESSION_INFO_BOOK_CURRENT_PAGE
block|,
DECL|enumerator|SESSION_INFO_BOOK_DOCKABLE
name|SESSION_INFO_BOOK_DOCKABLE
block|}
enum|;
end_enum

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpSessionInfoBook
modifier|*
DECL|function|gimp_session_info_book_new (void)
name|gimp_session_info_book_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_slice_new0
argument_list|(
name|GimpSessionInfoBook
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_book_free (GimpSessionInfoBook * info)
name|gimp_session_info_book_free
parameter_list|(
name|GimpSessionInfoBook
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
name|dockables
condition|)
block|{
name|g_list_free_full
argument_list|(
name|info
operator|->
name|dockables
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_session_info_dockable_free
argument_list|)
expr_stmt|;
name|info
operator|->
name|dockables
operator|=
name|NULL
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|GimpSessionInfoBook
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_book_serialize (GimpConfigWriter * writer,GimpSessionInfoBook * info)
name|gimp_session_info_book_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GimpSessionInfoBook
modifier|*
name|info
parameter_list|)
block|{
name|GList
modifier|*
name|pages
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
name|info
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"book"
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|->
name|position
operator|!=
literal|0
condition|)
block|{
name|gint
name|position
decl_stmt|;
name|position
operator|=
name|gimp_session_info_apply_position_accuracy
argument_list|(
name|info
operator|->
name|position
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
literal|"%d"
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"current-page"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|info
operator|->
name|current_page
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
for|for
control|(
name|pages
operator|=
name|info
operator|->
name|dockables
init|;
name|pages
condition|;
name|pages
operator|=
name|g_list_next
argument_list|(
name|pages
argument_list|)
control|)
name|gimp_session_info_dockable_serialize
argument_list|(
name|writer
argument_list|,
name|pages
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
DECL|function|gimp_session_info_book_deserialize (GScanner * scanner,gint scope,GimpSessionInfoBook ** book)
name|gimp_session_info_book_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|scope
parameter_list|,
name|GimpSessionInfoBook
modifier|*
modifier|*
name|book
parameter_list|)
block|{
name|GimpSessionInfoBook
modifier|*
name|info
decl_stmt|;
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
name|book
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
name|SESSION_INFO_BOOK_POSITION
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"current-page"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_BOOK_CURRENT_PAGE
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"dockable"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_BOOK_DOCKABLE
argument_list|)
argument_list|)
expr_stmt|;
name|info
operator|=
name|gimp_session_info_book_new
argument_list|()
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
name|GimpSessionInfoDockable
modifier|*
name|dockable
decl_stmt|;
case|case
name|SESSION_INFO_BOOK_POSITION
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
name|position
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_BOOK_CURRENT_PAGE
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
name|current_page
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_BOOK_DOCKABLE
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
name|gimp_session_info_dockable_deserialize
argument_list|(
name|scanner
argument_list|,
name|scope
operator|+
literal|1
argument_list|,
operator|&
name|dockable
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
name|dockables
operator|=
name|g_list_append
argument_list|(
name|info
operator|->
name|dockables
argument_list|,
name|dockable
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
goto|goto
name|error
goto|;
break|break;
default|default:
goto|goto
name|error
goto|;
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
operator|*
name|book
operator|=
name|info
expr_stmt|;
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
literal|"current-page"
argument_list|)
expr_stmt|;
name|g_scanner_scope_remove_symbol
argument_list|(
name|scanner
argument_list|,
name|scope
argument_list|,
literal|"dockable"
argument_list|)
expr_stmt|;
return|return
name|token
return|;
name|error
label|:
operator|*
name|book
operator|=
name|NULL
expr_stmt|;
name|gimp_session_info_book_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

begin_function
name|GimpSessionInfoBook
modifier|*
DECL|function|gimp_session_info_book_from_widget (GimpDockbook * dockbook)
name|gimp_session_info_book_from_widget
parameter_list|(
name|GimpDockbook
modifier|*
name|dockbook
parameter_list|)
block|{
name|GimpSessionInfoBook
modifier|*
name|info
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|info
operator|=
name|gimp_session_info_book_new
argument_list|()
expr_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_PANED
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
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
operator|==
name|gtk_paned_get_child2
argument_list|(
name|paned
argument_list|)
condition|)
name|info
operator|->
name|position
operator|=
name|gtk_paned_get_position
argument_list|(
name|paned
argument_list|)
expr_stmt|;
block|}
name|info
operator|->
name|current_page
operator|=
name|gtk_notebook_get_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
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
name|GimpSessionInfoDockable
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|gimp_session_info_dockable_from_widget
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|info
operator|->
name|dockables
operator|=
name|g_list_prepend
argument_list|(
name|info
operator|->
name|dockables
argument_list|,
name|dockable
argument_list|)
expr_stmt|;
block|}
name|info
operator|->
name|dockables
operator|=
name|g_list_reverse
argument_list|(
name|info
operator|->
name|dockables
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
return|return
name|info
return|;
block|}
end_function

begin_function
name|GimpDockbook
modifier|*
DECL|function|gimp_session_info_book_restore (GimpSessionInfoBook * info,GimpDock * dock)
name|gimp_session_info_book_restore
parameter_list|(
name|GimpSessionInfoBook
modifier|*
name|info
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GimpDialogFactory
modifier|*
name|dialog_factory
decl_stmt|;
name|GimpMenuFactory
modifier|*
name|menu_factory
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|GList
modifier|*
name|pages
decl_stmt|;
name|gint
name|n_dockables
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|info
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|dialog_factory
operator|=
name|gimp_dock_get_dialog_factory
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|menu_factory
operator|=
name|gimp_dialog_factory_get_menu_factory
argument_list|(
name|dialog_factory
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|gimp_dockbook_new
argument_list|(
name|menu_factory
argument_list|)
expr_stmt|;
name|gimp_dock_add_book
argument_list|(
name|dock
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|pages
operator|=
name|info
operator|->
name|dockables
init|;
name|pages
condition|;
name|pages
operator|=
name|g_list_next
argument_list|(
name|pages
argument_list|)
control|)
block|{
name|GimpSessionInfoDockable
modifier|*
name|dockable_info
init|=
name|pages
operator|->
name|data
decl_stmt|;
name|GimpDockable
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|gimp_session_info_dockable_restore
argument_list|(
name|dockable_info
argument_list|,
name|dock
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockable
condition|)
block|{
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|n_dockables
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
name|info
operator|->
name|current_page
operator|<
name|gtk_notebook_get_n_pages
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
condition|)
block|{
name|gtk_notebook_set_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
name|info
operator|->
name|current_page
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|n_dockables
operator|>
literal|1
condition|)
block|{
name|gtk_notebook_set_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
comment|/*  Return the dockbook even if no dockable could be restored    *  (n_dockables == 0) because otherwise we would have to remove it    *  from the dock right here, which could implicitly destroy the    *  dock and make catching restore errors much harder on higher    *  levels. Instead, we check for restored empty dockbooks in our    *  caller.    */
return|return
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
return|;
block|}
end_function

end_unit

