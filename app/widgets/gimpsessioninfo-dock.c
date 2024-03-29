begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-dock.c  * Copyright (C) 2001-2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockcontainer.h"
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

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2be5a6580103
block|{
DECL|enumerator|SESSION_INFO_SIDE
name|SESSION_INFO_SIDE
block|,
DECL|enumerator|SESSION_INFO_POSITION
name|SESSION_INFO_POSITION
block|,
DECL|enumerator|SESSION_INFO_BOOK
name|SESSION_INFO_BOOK
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GimpAlignmentType
name|gimp_session_info_dock_get_side
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|GimpAlignmentType
DECL|function|gimp_session_info_dock_get_side (GimpDock * dock)
name|gimp_session_info_dock_get_side
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GimpAlignmentType
name|result
init|=
operator|-
literal|1
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK_CONTAINER
argument_list|(
name|toplevel
argument_list|)
condition|)
block|{
name|GimpDockContainer
modifier|*
name|container
init|=
name|GIMP_DOCK_CONTAINER
argument_list|(
name|toplevel
argument_list|)
decl_stmt|;
name|result
operator|=
name|gimp_dock_container_get_dock_side
argument_list|(
name|container
argument_list|,
name|dock
argument_list|)
expr_stmt|;
block|}
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpSessionInfoDock
modifier|*
DECL|function|gimp_session_info_dock_new (const gchar * dock_type)
name|gimp_session_info_dock_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dock_type
parameter_list|)
block|{
name|GimpSessionInfoDock
modifier|*
name|dock_info
init|=
name|NULL
decl_stmt|;
name|dock_info
operator|=
name|g_slice_new0
argument_list|(
name|GimpSessionInfoDock
argument_list|)
expr_stmt|;
name|dock_info
operator|->
name|dock_type
operator|=
name|g_strdup
argument_list|(
name|dock_type
argument_list|)
expr_stmt|;
name|dock_info
operator|->
name|side
operator|=
operator|-
literal|1
expr_stmt|;
return|return
name|dock_info
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_dock_free (GimpSessionInfoDock * dock_info)
name|gimp_session_info_dock_free
parameter_list|(
name|GimpSessionInfoDock
modifier|*
name|dock_info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|dock_info
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|dock_info
operator|->
name|dock_type
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
if|if
condition|(
name|dock_info
operator|->
name|books
condition|)
block|{
name|g_list_free_full
argument_list|(
name|dock_info
operator|->
name|books
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_session_info_book_free
argument_list|)
expr_stmt|;
name|dock_info
operator|->
name|books
operator|=
name|NULL
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|GimpSessionInfoDock
argument_list|,
name|dock_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_session_info_dock_serialize (GimpConfigWriter * writer,GimpSessionInfoDock * dock_info)
name|gimp_session_info_dock_serialize
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GimpSessionInfoDock
modifier|*
name|dock_info
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
name|dock_info
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
name|dock_info
operator|->
name|dock_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|dock_info
operator|->
name|side
operator|!=
operator|-
literal|1
condition|)
block|{
specifier|const
name|char
modifier|*
name|side_text
init|=
name|dock_info
operator|->
name|side
operator|==
name|GIMP_ALIGN_LEFT
condition|?
literal|"left"
else|:
literal|"right"
decl_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"side"
argument_list|)
expr_stmt|;
name|gimp_config_writer_print
argument_list|(
name|writer
argument_list|,
name|side_text
argument_list|,
name|strlen
argument_list|(
name|side_text
argument_list|)
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
name|dock_info
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
name|dock_info
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
for|for
control|(
name|list
operator|=
name|dock_info
operator|->
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
DECL|function|gimp_session_info_dock_deserialize (GScanner * scanner,gint scope,GimpSessionInfoDock ** dock_info,const gchar * dock_type)
name|gimp_session_info_dock_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|gint
name|scope
parameter_list|,
name|GimpSessionInfoDock
modifier|*
modifier|*
name|dock_info
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dock_type
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
name|dock_info
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
literal|"side"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_SIDE
argument_list|)
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
literal|"book"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_BOOK
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|dock_info
operator|=
name|gimp_session_info_dock_new
argument_list|(
name|dock_type
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
name|SESSION_INFO_SIDE
case|:
name|token
operator|=
name|G_TOKEN_IDENTIFIER
expr_stmt|;
if|if
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|!=
name|token
condition|)
break|break;
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
literal|"left"
argument_list|,
name|scanner
operator|->
name|value
operator|.
name|v_identifier
argument_list|)
operator|==
literal|0
condition|)
operator|(
operator|*
name|dock_info
operator|)
operator|->
name|side
operator|=
name|GIMP_ALIGN_LEFT
expr_stmt|;
else|else
operator|(
operator|*
name|dock_info
operator|)
operator|->
name|side
operator|=
name|GIMP_ALIGN_RIGHT
expr_stmt|;
break|break;
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
operator|(
operator|(
operator|*
name|dock_info
operator|)
operator|->
name|position
operator|)
argument_list|)
condition|)
operator|(
operator|*
name|dock_info
operator|)
operator|->
name|position
operator|=
literal|0
expr_stmt|;
break|break;
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
operator|(
operator|*
name|dock_info
operator|)
operator|->
name|books
operator|=
name|g_list_append
argument_list|(
operator|(
operator|*
name|dock_info
operator|)
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
literal|"side"
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

begin_function
name|GimpSessionInfoDock
modifier|*
DECL|function|gimp_session_info_dock_from_widget (GimpDock * dock)
name|gimp_session_info_dock_from_widget
parameter_list|(
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GimpSessionInfoDock
modifier|*
name|dock_info
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GtkWidget
modifier|*
name|parent
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
name|dock_info
operator|=
name|gimp_session_info_dock_new
argument_list|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|dock
argument_list|)
condition|?
literal|"gimp-toolbox"
else|:
literal|"gimp-dock"
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
name|dock_info
operator|->
name|books
operator|=
name|g_list_prepend
argument_list|(
name|dock_info
operator|->
name|books
argument_list|,
name|book
argument_list|)
expr_stmt|;
block|}
name|dock_info
operator|->
name|books
operator|=
name|g_list_reverse
argument_list|(
name|dock_info
operator|->
name|books
argument_list|)
expr_stmt|;
name|dock_info
operator|->
name|side
operator|=
name|gimp_session_info_dock_get_side
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|parent
operator|=
name|gtk_widget_get_parent
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock
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
name|dock
argument_list|)
operator|==
name|gtk_paned_get_child2
argument_list|(
name|paned
argument_list|)
condition|)
name|dock_info
operator|->
name|position
operator|=
name|gtk_paned_get_position
argument_list|(
name|paned
argument_list|)
expr_stmt|;
block|}
return|return
name|dock_info
return|;
block|}
end_function

begin_function
name|GimpDock
modifier|*
DECL|function|gimp_session_info_dock_restore (GimpSessionInfoDock * dock_info,GimpDialogFactory * factory,GdkMonitor * monitor,GimpDockContainer * dock_container)
name|gimp_session_info_dock_restore
parameter_list|(
name|GimpSessionInfoDock
modifier|*
name|dock_info
parameter_list|,
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|,
name|GimpDockContainer
modifier|*
name|dock_container
parameter_list|)
block|{
name|gint
name|n_books
init|=
literal|0
decl_stmt|;
name|GtkWidget
modifier|*
name|dock
decl_stmt|;
name|GList
modifier|*
name|iter
decl_stmt|;
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_MONITOR
argument_list|(
name|monitor
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ui_manager
operator|=
name|gimp_dock_container_get_ui_manager
argument_list|(
name|dock_container
argument_list|)
expr_stmt|;
name|dock
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|factory
argument_list|,
name|monitor
argument_list|,
name|ui_manager
argument_list|,
name|NULL
argument_list|,
name|dock_info
operator|->
name|dock_type
argument_list|,
operator|-
literal|1
comment|/*view_size*/
argument_list|,
name|FALSE
comment|/*present*/
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
comment|/* Add the dock to the dock window immediately so the stuff in the    * dock has access to e.g. a dialog factory    */
name|gimp_dock_container_add_dock
argument_list|(
name|dock_container
argument_list|,
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|dock_info
argument_list|)
expr_stmt|;
comment|/* Note that if it is a toolbox, we will get here even though we    * don't have any books    */
for|for
control|(
name|iter
operator|=
name|dock_info
operator|->
name|books
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|GimpSessionInfoBook
modifier|*
name|book_info
init|=
name|iter
operator|->
name|data
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|dockbook
operator|=
name|GTK_WIDGET
argument_list|(
name|gimp_session_info_book_restore
argument_list|(
name|book_info
argument_list|,
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dockbook
condition|)
block|{
name|GtkWidget
modifier|*
name|parent
init|=
name|gtk_widget_get_parent
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
name|n_books
operator|++
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
name|dockbook
operator|==
name|gtk_paned_get_child2
argument_list|(
name|paned
argument_list|)
condition|)
name|gtk_paned_set_position
argument_list|(
name|paned
argument_list|,
name|book_info
operator|->
name|position
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/* Now remove empty dockbooks from the list, check the comment in    * gimp_session_info_book_restore() which explains why the dock    * can contain empty dockbooks at all    */
if|if
condition|(
name|dock_info
operator|->
name|books
condition|)
block|{
name|GList
modifier|*
name|books
decl_stmt|;
name|books
operator|=
name|g_list_copy
argument_list|(
name|gimp_dock_get_dockbooks
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|books
condition|)
block|{
name|GtkContainer
modifier|*
name|dockbook
init|=
name|books
operator|->
name|data
decl_stmt|;
name|GList
modifier|*
name|children
init|=
name|gtk_container_get_children
argument_list|(
name|dockbook
argument_list|)
decl_stmt|;
if|if
condition|(
name|children
condition|)
block|{
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_ref
argument_list|(
name|dockbook
argument_list|)
expr_stmt|;
name|gimp_dock_remove_book
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dockbook
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dockbook
argument_list|)
expr_stmt|;
name|n_books
operator|--
expr_stmt|;
block|}
name|books
operator|=
name|g_list_remove
argument_list|(
name|books
argument_list|,
name|dockbook
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  if we removed all books again, the dock was destroyed, so bail out  */
if|if
condition|(
name|dock_info
operator|->
name|books
operator|&&
name|n_books
operator|==
literal|0
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|gtk_widget_show
argument_list|(
name|dock
argument_list|)
expr_stmt|;
return|return
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
return|;
block|}
end_function

end_unit

