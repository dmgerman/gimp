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
file|"libgimpconfig/gimpconfig.h"
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
file|"config/gimpcoreconfig.h"
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
file|"core/gimpimage-new.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
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
file|"widgets/gimptemplateeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptemplateview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/template-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"templates-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c3a337d0108
block|{
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|template
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
DECL|typedef|TemplateDeleteData
block|}
name|TemplateDeleteData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|templates_new_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateOptionsDialog
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|templates_edit_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateOptionsDialog
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|templates_delete_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateDeleteData
modifier|*
name|delete_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|templates_delete_data_free
parameter_list|(
name|TemplateDeleteData
modifier|*
name|delete_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions */
end_comment

begin_function
name|void
DECL|function|templates_create_image_cmd_callback (GtkAction * action,gpointer data)
name|templates_create_image_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_context_get_template
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|image
operator|=
name|gimp_image_new_from_template
argument_list|(
name|gimp
argument_list|,
name|template
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|gimp_template_get_unit
argument_list|(
name|template
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|G_OBJECT
argument_list|(
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|,
name|gimp_widget_get_monitor
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_new_set_last_template
argument_list|(
name|gimp
argument_list|,
name|template
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|templates_new_cmd_callback (GtkAction * action,gpointer data)
name|templates_new_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|TemplateOptionsDialog
modifier|*
name|options
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|options
operator|=
name|template_options_dialog_new
argument_list|(
name|NULL
argument_list|,
name|context
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"New Template"
argument_list|)
argument_list|,
literal|"gimp-template-new"
argument_list|,
name|GIMP_STOCK_TEMPLATE
argument_list|,
name|_
argument_list|(
literal|"Create a New Template"
argument_list|)
argument_list|,
name|GIMP_HELP_TEMPLATE_NEW
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|templates_new_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|templates_duplicate_cmd_callback (GtkAction * action,gpointer data)
name|templates_duplicate_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_context_get_template
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|)
condition|)
block|{
name|GimpTemplate
modifier|*
name|new_template
decl_stmt|;
name|new_template
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_by_type
argument_list|(
name|context
argument_list|,
name|gimp_container_get_children_type
argument_list|(
name|container
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_template
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_template
argument_list|)
expr_stmt|;
name|templates_edit_cmd_callback
argument_list|(
name|action
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|templates_edit_cmd_callback (GtkAction * action,gpointer data)
name|templates_edit_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_context_get_template
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|)
condition|)
block|{
name|TemplateOptionsDialog
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|template_options_dialog_new
argument_list|(
name|template
argument_list|,
name|context
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Edit Template"
argument_list|)
argument_list|,
literal|"gimp-template-edit"
argument_list|,
name|GTK_STOCK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Template"
argument_list|)
argument_list|,
name|GIMP_HELP_TEMPLATE_EDIT
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|templates_edit_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|templates_delete_cmd_callback (GtkAction * action,gpointer data)
name|templates_delete_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_context_get_template
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
operator|&&
name|gimp_container_have
argument_list|(
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|)
condition|)
block|{
name|TemplateDeleteData
modifier|*
name|delete_data
init|=
name|g_slice_new
argument_list|(
name|TemplateDeleteData
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|delete_data
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|delete_data
operator|->
name|container
operator|=
name|container
expr_stmt|;
name|delete_data
operator|->
name|template
operator|=
name|template
expr_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Delete Template"
argument_list|)
argument_list|,
name|GTK_STOCK_DELETE
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
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
name|templates_delete_data_free
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|template
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
name|templates_delete_response
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
literal|"Are you sure you want to delete "
literal|"template '%s' from the list and "
literal|"from disk?"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|template
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|templates_new_response (GtkWidget * dialog,gint response_id,TemplateOptionsDialog * options)
name|templates_new_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateOptionsDialog
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpTemplateEditor
modifier|*
name|editor
init|=
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|options
operator|->
name|editor
argument_list|)
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|template
operator|=
name|gimp_template_editor_get_template
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|options
operator|->
name|gimp
operator|->
name|templates
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_template
argument_list|(
name|gimp_get_user_context
argument_list|(
name|options
operator|->
name|gimp
argument_list|)
argument_list|,
name|template
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|templates_edit_response (GtkWidget * dialog,gint response_id,TemplateOptionsDialog * options)
name|templates_edit_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateOptionsDialog
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpTemplateEditor
modifier|*
name|editor
init|=
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|options
operator|->
name|editor
argument_list|)
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|template
operator|=
name|gimp_template_editor_get_template
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|options
operator|->
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|templates_delete_response (GtkWidget * dialog,gint response_id,TemplateDeleteData * delete_data)
name|templates_delete_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|TemplateDeleteData
modifier|*
name|delete_data
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpObject
modifier|*
name|new_active
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|delete_data
operator|->
name|template
operator|==
name|gimp_context_get_template
argument_list|(
name|delete_data
operator|->
name|context
argument_list|)
condition|)
block|{
name|new_active
operator|=
name|gimp_container_get_neighbor_of
argument_list|(
name|delete_data
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|delete_data
operator|->
name|template
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_container_have
argument_list|(
name|delete_data
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|delete_data
operator|->
name|template
argument_list|)
argument_list|)
condition|)
block|{
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
name|delete_data
operator|->
name|container
argument_list|)
argument_list|,
name|new_active
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|delete_data
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|delete_data
operator|->
name|template
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|templates_delete_data_free (TemplateDeleteData * delete_data)
name|templates_delete_data_free
parameter_list|(
name|TemplateDeleteData
modifier|*
name|delete_data
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|TemplateDeleteData
argument_list|,
name|delete_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

