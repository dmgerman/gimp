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
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"data-delete-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|DataDeleteDialog
typedef|typedef
name|struct
name|_DataDeleteDialog
name|DataDeleteDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_DataDeleteDialog
struct|struct
name|_DataDeleteDialog
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
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|parent
name|GtkWidget
modifier|*
name|parent
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
name|data_delete_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|DataDeleteDialog
modifier|*
name|delete_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|data_delete_dialog_new (GimpDataFactory * factory,GimpData * data,GimpContext * context,GtkWidget * parent)
name|data_delete_dialog_new
parameter_list|(
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|DataDeleteDialog
modifier|*
name|delete_data
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|delete_data
operator|=
name|g_slice_new0
argument_list|(
name|DataDeleteDialog
argument_list|)
expr_stmt|;
name|delete_data
operator|->
name|factory
operator|=
name|factory
expr_stmt|;
name|delete_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|delete_data
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|delete_data
operator|->
name|parent
operator|=
name|parent
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
name|gtk_widget_get_toplevel
argument_list|(
name|parent
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
name|data_delete_dialog_response
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
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|data_delete_dialog_response (GtkWidget * dialog,gint response_id,DataDeleteDialog * delete_data)
name|data_delete_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|DataDeleteDialog
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
name|delete_data
operator|->
name|factory
decl_stmt|;
name|GimpData
modifier|*
name|data
init|=
name|delete_data
operator|->
name|data
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpObject
modifier|*
name|new_active
init|=
name|NULL
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
expr_stmt|;
if|if
condition|(
name|delete_data
operator|->
name|context
operator|&&
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
operator|==
name|gimp_context_get_by_type
argument_list|(
name|delete_data
operator|->
name|context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|container
argument_list|)
argument_list|)
condition|)
block|{
name|new_active
operator|=
name|gimp_container_get_neighbor_of
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
name|parent
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
name|DataDeleteDialog
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

