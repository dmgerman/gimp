begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
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
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpclipboard.h"
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
file|"widgets/gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagedialog.h"
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
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|view
name|GimpDataFactoryView
modifier|*
name|view
decl_stmt|;
DECL|member|data
name|GimpData
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|data_delete_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDataDeleteData
modifier|*
name|delete_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|data_open_as_image_cmd_callback (GtkAction * action,gpointer user_data)
name|data_open_as_image_cmd_callback
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
name|gimp_data_factory_view_get_children_type
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_filename_to_uri
argument_list|(
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|image
operator|=
name|file_open_with_display
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gimp_message
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|data_new_cmd_callback (GtkAction * action,gpointer user_data)
name|data_new_cmd_callback
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
name|gimp_data_factory_view_has_data_new_func
argument_list|(
name|view
argument_list|)
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
name|gimp_data_factory_view_get_data_factory
argument_list|(
name|view
argument_list|)
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
name|gimp_data_factory_view_get_children_type
argument_list|(
name|view
argument_list|)
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
name|gimp_data_factory_view_get_edit_button
argument_list|(
name|view
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|data_duplicate_cmd_callback (GtkAction * action,gpointer user_data)
name|data_duplicate_cmd_callback
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
name|gimp_data_factory_view_get_children_type
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_data_factory_view_have
argument_list|(
name|view
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
name|gimp_data_factory_view_get_data_factory
argument_list|(
name|view
argument_list|)
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
name|gimp_data_factory_view_get_children_type
argument_list|(
name|view
argument_list|)
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
name|gimp_data_factory_view_get_edit_button
argument_list|(
name|view
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|data_copy_location_cmd_callback (GtkAction * action,gpointer user_data)
name|data_copy_location_cmd_callback
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
name|gimp_data_factory_view_get_children_type
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|gimp_data_get_filename
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
operator|&&
operator|*
name|filename
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|gimp_clipboard_set_text
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|data_delete_cmd_callback (GtkAction * action,gpointer user_data)
name|data_delete_cmd_callback
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
name|gimp_data_factory_view_get_children_type
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_data_is_deletable
argument_list|(
name|data
argument_list|)
operator|&&
name|gimp_data_factory_view_have
argument_list|(
name|view
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
name|delete_data
operator|=
name|g_slice_new0
argument_list|(
name|GimpDataDeleteData
argument_list|)
expr_stmt|;
name|delete_data
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|delete_data
operator|->
name|view
operator|=
name|view
expr_stmt|;
name|delete_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Delete Object"
argument_list|)
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|data
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|dialog
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|data_delete_confirm_response
argument_list|)
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Delete '%s'?"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Are you sure you want to remove '%s' "
literal|"from the list and delete it on disk?"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|data
argument_list|)
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
DECL|function|data_refresh_cmd_callback (GtkAction * action,gpointer user_data)
name|data_refresh_cmd_callback
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
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_refresh
argument_list|(
name|gimp_data_factory_view_get_data_factory
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|data_edit_cmd_callback (GtkAction * action,const gchar * value,gpointer user_data)
name|data_edit_cmd_callback
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
name|gimp_data_factory_view_get_children_type
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|&&
name|gimp_data_factory_view_have
argument_list|(
name|view
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
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|data_delete_confirm_response (GtkWidget * dialog,gint response_id,GimpDataDeleteData * delete_data)
name|data_delete_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDataDeleteData
modifier|*
name|delete_data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpDataFactory
modifier|*
name|factory
init|=
name|gimp_data_factory_view_get_data_factory
argument_list|(
name|delete_data
operator|->
name|view
argument_list|)
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|delete_data
operator|->
name|data
decl_stmt|;
name|GimpObject
modifier|*
name|new_active
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|new_active
operator|=
name|gimp_container_get_neighbor_of_active
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
argument_list|,
name|delete_data
operator|->
name|context
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_data_factory_data_delete
argument_list|(
name|factory
argument_list|,
name|data
argument_list|,
name|TRUE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|gimp_data_factory_get_gimp
argument_list|(
name|factory
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|delete_data
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
argument_list|,
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
if|if
condition|(
name|new_active
condition|)
name|gimp_context_set_by_type
argument_list|(
name|delete_data
operator|->
name|context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
argument_list|)
argument_list|,
name|new_active
argument_list|)
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|GimpDataDeleteData
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

