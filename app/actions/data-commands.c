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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdataeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"data-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|data_new_data_cmd_callback (GtkAction * action,gpointer user_data)
name|data_new_data_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDataFactoryView
modifier|*
name|view
init|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|factory
operator|->
name|data_new_func
condition|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_data_factory_data_new
argument_list|(
name|view
operator|->
name|factory
argument_list|,
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
name|gimp_context_set_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|edit_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|data_duplicate_data_cmd_callback (GtkAction * action,gpointer user_data)
name|data_duplicate_data_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDataFactoryView
modifier|*
name|view
init|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|GimpData
modifier|*
name|new_data
decl_stmt|;
name|new_data
operator|=
name|gimp_data_factory_data_duplicate
argument_list|(
name|view
operator|->
name|factory
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_data
condition|)
block|{
name|gimp_context_set_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_button_clicked
argument_list|(
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|edit_button
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_typedef
DECL|typedef|GimpDataDeleteData
typedef|typedef
name|struct
name|_GimpDataDeleteData
name|GimpDataDeleteData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataDeleteData
struct|struct
name|_GimpDataDeleteData
block|{
DECL|member|factory
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
DECL|member|data
name|GimpData
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|data_delete_callback (GtkWidget * widget,gboolean delete,gpointer data)
name|data_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|delete
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDataDeleteData
modifier|*
name|delete_data
init|=
name|data
decl_stmt|;
if|if
condition|(
name|delete
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_data_factory_data_delete
argument_list|(
name|delete_data
operator|->
name|factory
argument_list|,
name|delete_data
operator|->
name|data
argument_list|,
name|TRUE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|data_delete_data_cmd_callback (GtkAction * action,gpointer user_data)
name|data_delete_data_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDataFactoryView
modifier|*
name|view
init|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|data
operator|->
name|deletable
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|GimpDataDeleteData
modifier|*
name|delete_data
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|delete_data
operator|=
name|g_new0
argument_list|(
name|GimpDataDeleteData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|delete_data
operator|->
name|factory
operator|=
name|view
operator|->
name|factory
expr_stmt|;
name|delete_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Are you sure you want to delete '%s' "
literal|"from the list and from disk?"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Delete Data Object"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|str
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|data_delete_callback
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|data_refresh_data_cmd_callback (GtkAction * action,gpointer user_data)
name|data_refresh_data_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDataFactoryView
modifier|*
name|view
init|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|gimp_data_factory_data_save
argument_list|(
name|view
operator|->
name|factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|view
operator|->
name|factory
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|data_edit_data_cmd_callback (GtkAction * action,const gchar * value,gpointer user_data)
name|data_edit_data_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpDataFactoryView
modifier|*
name|view
init|=
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|user_data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|data
operator|=
operator|(
name|GimpData
operator|*
operator|)
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|view
operator|->
name|factory
operator|->
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_container_have
argument_list|(
name|view
operator|->
name|factory
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
name|GdkScreen
modifier|*
name|screen
init|=
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
name|screen
argument_list|,
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_data
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

