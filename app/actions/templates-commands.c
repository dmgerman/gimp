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
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
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
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"gui/file-new-dialog.h"
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
name|templates_file_new_dialog
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|template
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|templates_new_template_cmd_callback (GtkAction * action,gpointer data)
name|templates_new_template_cmd_callback
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
block|{     }
name|templates_new_template_dialog
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|templates_duplicate_template_cmd_callback (GtkAction * action,gpointer data)
name|templates_duplicate_template_cmd_callback
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
name|container
operator|->
name|children_type
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_template
argument_list|)
argument_list|)
expr_stmt|;
name|templates_edit_template_dialog
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|new_template
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_template
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|templates_edit_template_cmd_callback (GtkAction * action,gpointer data)
name|templates_edit_template_cmd_callback
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
name|templates_edit_template_dialog
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|template
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_typedef
DECL|typedef|GimpTemplateDeleteData
typedef|typedef
name|struct
name|_GimpTemplateDeleteData
name|GimpTemplateDeleteData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTemplateDeleteData
struct|struct
name|_GimpTemplateDeleteData
block|{
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
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|templates_delete_template_callback (GtkWidget * widget,gboolean delete,gpointer data)
name|templates_delete_template_callback
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
name|GimpTemplateDeleteData
modifier|*
name|delete_data
init|=
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|delete
condition|)
return|return;
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
end_function

begin_function
name|void
DECL|function|templates_delete_template_cmd_callback (GtkAction * action,gpointer data)
name|templates_delete_template_cmd_callback
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
name|GimpTemplateDeleteData
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
name|GimpTemplateDeleteData
argument_list|,
literal|1
argument_list|)
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
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Are you sure you want to delete template '%s' "
literal|"from the list and from disk?"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|template
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
literal|"Delete Template"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
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
name|template
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|templates_delete_template_callback
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
specifier|static
name|void
DECL|function|templates_new_template_response (GtkWidget * widget,gint response_id,GtkWidget * dialog)
name|templates_new_template_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|template
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-template"
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp"
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
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
name|void
DECL|function|templates_new_template_dialog (Gimp * gimp,GimpTemplate * unused,GtkWidget * parent)
name|templates_new_template_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemplate
modifier|*
name|unused
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|NULL
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
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_TEMPLATE_NEW
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
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
name|templates_new_template_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|default_image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|template
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
name|editor
operator|=
name|gimp_template_editor_new
argument_list|(
name|template
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-template"
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|editor
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|templates_edit_template_response (GtkWidget * widget,gint response_id,GtkWidget * dialog)
name|templates_edit_template_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
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
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|editor
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-template-editor"
argument_list|)
expr_stmt|;
name|template
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-template"
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp"
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|editor
operator|->
name|template
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
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
name|void
DECL|function|templates_edit_template_dialog (Gimp * gimp,GimpTemplate * template,GtkWidget * parent)
name|templates_edit_template_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|template
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Edit Template"
argument_list|)
argument_list|,
literal|"gimp-template-edit"
argument_list|,
name|GIMP_STOCK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Template"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_TEMPLATE_EDIT
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
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
name|templates_edit_template_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-template"
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|editor
operator|=
name|gimp_template_editor_new
argument_list|(
name|template
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|editor
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-template-editor"
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|templates_file_new_dialog (Gimp * gimp,GimpTemplate * template,GtkWidget * parent)
name|templates_file_new_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|parent
argument_list|)
argument_list|,
literal|"gimp-file-new-dialog"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
name|file_new_dialog_set
argument_list|(
name|dialog
argument_list|,
name|NULL
argument_list|,
name|template
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

