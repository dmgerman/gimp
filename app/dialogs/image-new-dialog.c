begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
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
file|"widgets/gimpcontainercombobox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
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
file|"image-new-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon293f6f2b0108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|confirm_dialog
name|GtkWidget
modifier|*
name|confirm_dialog
decl_stmt|;
DECL|member|combo
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
DECL|member|editor
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|template
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
DECL|typedef|ImageNewDialog
block|}
name|ImageNewDialog
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|image_new_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageNewDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_new_template_select
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|ImageNewDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_new_confirm_dialog
parameter_list|(
name|ImageNewDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_new_create_image
parameter_list|(
name|ImageNewDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|image_new_dialog_new (Gimp * gimp)
name|image_new_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|ImageNewDialog
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GimpSizeEntry
modifier|*
name|entry
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_new0
argument_list|(
name|ImageNewDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|dialog
operator|->
name|template
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEMPLATE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Create a New Image"
argument_list|)
argument_list|,
literal|"gimp-image-new"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_NEW
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|RESPONSE_RESET
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
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
literal|"gimp-image-new-dialog"
argument_list|,
name|dialog
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_new_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
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
operator|->
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|combo
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CONTAINER_COMBO_BOX
argument_list|,
literal|"container"
argument_list|,
name|gimp
operator|->
name|templates
argument_list|,
literal|"view-size"
argument_list|,
literal|16
argument_list|,
literal|"view-border-width"
argument_list|,
literal|0
argument_list|,
literal|"focus-on-click"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Template:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|dialog
operator|->
name|combo
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|combo
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_new_template_select
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
comment|/*  Template editor  */
name|dialog
operator|->
name|editor
operator|=
name|gimp_template_editor_new
argument_list|(
name|dialog
operator|->
name|template
argument_list|,
name|gimp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|dialog
operator|->
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
name|dialog
operator|->
name|editor
argument_list|)
expr_stmt|;
name|entry
operator|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|dialog
operator|->
name|editor
argument_list|)
operator|->
name|size_se
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_activates_default
argument_list|(
name|entry
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_grab_focus
argument_list|(
name|entry
argument_list|)
expr_stmt|;
return|return
name|dialog
operator|->
name|dialog
return|;
block|}
end_function

begin_function
name|void
DECL|function|image_new_dialog_set (GtkWidget * widget,GimpImage * image,GimpTemplate * template)
name|image_new_dialog_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|ImageNewDialog
modifier|*
name|dialog
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|template
operator|==
name|NULL
operator|||
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-image-new-dialog"
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dialog
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
condition|)
block|{
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|dialog
operator|->
name|combo
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|template
operator|=
name|gimp_image_new_get_last_template
argument_list|(
name|dialog
operator|->
name|gimp
argument_list|,
name|image
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
name|dialog
operator|->
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
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
DECL|function|image_new_response (GtkWidget * widget,gint response_id,ImageNewDialog * dialog)
name|image_new_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageNewDialog
modifier|*
name|dialog
parameter_list|)
block|{
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_image
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|dialog
operator|->
name|combo
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
if|if
condition|(
name|dialog
operator|->
name|template
operator|->
name|initial_size
operator|>
name|GIMP_GUI_CONFIG
argument_list|(
name|dialog
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|max_new_image_size
condition|)
name|image_new_confirm_dialog
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
else|else
name|image_new_create_image
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_new_template_select (GimpContainerView * view,GimpTemplate * template,gpointer insert_data,ImageNewDialog * dialog)
name|image_new_template_select
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|ImageNewDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gchar
modifier|*
name|comment
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|template
condition|)
return|return;
if|if
condition|(
operator|!
name|template
operator|->
name|comment
operator|||
operator|!
name|strlen
argument_list|(
name|template
operator|->
name|comment
argument_list|)
condition|)
name|comment
operator|=
name|g_strdup
argument_list|(
name|dialog
operator|->
name|template
operator|->
name|comment
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
name|dialog
operator|->
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|comment
condition|)
block|{
name|g_object_set
argument_list|(
name|dialog
operator|->
name|template
argument_list|,
literal|"comment"
argument_list|,
name|comment
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|comment
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  the confirm dialog  */
end_comment

begin_function
specifier|static
name|void
DECL|function|image_new_confirm_response (GtkWidget * dialog,gint response_id,ImageNewDialog * data)
name|image_new_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageNewDialog
modifier|*
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|data
operator|->
name|confirm_dialog
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
name|image_new_create_image
argument_list|(
name|data
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_new_confirm_dialog (ImageNewDialog * data)
name|image_new_confirm_dialog
parameter_list|(
name|ImageNewDialog
modifier|*
name|data
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gchar
modifier|*
name|size
decl_stmt|;
if|if
condition|(
name|data
operator|->
name|confirm_dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|data
operator|->
name|confirm_dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|data
operator|->
name|confirm_dialog
operator|=
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Confirm Image Size"
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|data
operator|->
name|dialog
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
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
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|data
operator|->
name|confirm_dialog
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
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_new_confirm_response
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|size
operator|=
name|gimp_memsize_to_string
argument_list|(
name|data
operator|->
name|template
operator|->
name|initial_size
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
literal|"You are trying to create an image "
literal|"with a size of %s."
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|data
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|size
operator|=
name|gimp_memsize_to_string
argument_list|(
name|config
operator|->
name|max_new_image_size
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
literal|"An image of the chosen size will use more "
literal|"memory than what is configured as "
literal|"\"Maximum Image Size\" in the Preferences "
literal|"dialog (currently %s)."
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|data
operator|->
name|dialog
argument_list|,
name|FALSE
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
DECL|function|image_new_create_image (ImageNewDialog * dialog)
name|image_new_create_image
parameter_list|(
name|ImageNewDialog
modifier|*
name|dialog
parameter_list|)
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
name|g_object_ref
argument_list|(
name|dialog
operator|->
name|template
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|dialog
operator|->
name|gimp
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|gimp_template_create_image
argument_list|(
name|gimp
argument_list|,
name|template
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_new_set_last_template
argument_list|(
name|gimp
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

