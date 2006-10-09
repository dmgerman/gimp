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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-save.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpfiledialog.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
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
file|"file-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|REVERT_DATA_KEY
define|#
directive|define
name|REVERT_DATA_KEY
value|"revert-confirm-dialog"
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|file_open_dialog_show
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|open_as_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_save_dialog_show
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gboolean
name|save_a_copy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_save_dialog_destroyed
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_new_template_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_revert_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_open_cmd_callback (GtkAction * action,gpointer data)
name|file_open_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|file_open_dialog_show
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_open_from_image_cmd_callback (GtkAction * action,gpointer data)
name|file_open_from_image_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
init|=
name|NULL
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|image
operator|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|file_open_dialog_show
argument_list|(
name|widget
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_open_as_layer_cmd_callback (GtkAction * action,gpointer data)
name|file_open_as_layer_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|image
operator|=
name|display
operator|->
name|image
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|file_open_dialog_show
argument_list|(
name|widget
argument_list|,
name|image
argument_list|,
name|uri
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_open_location_cmd_callback (GtkAction * action,gpointer data)
name|file_open_location_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-file-open-location-dialog"
argument_list|,
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_last_opened_cmd_callback (GtkAction * action,gint value,gpointer data)
name|file_last_opened_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|gint
name|num_entries
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|num_entries
operator|=
name|gimp_container_num_children
argument_list|(
name|gimp
operator|->
name|documents
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|>=
name|num_entries
condition|)
return|return;
name|imagefile
operator|=
operator|(
name|GimpImagefile
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|gimp
operator|->
name|documents
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
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
name|gimp
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
operator|->
name|name
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
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
operator|->
name|name
argument_list|)
decl_stmt|;
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
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
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_save_cmd_callback (GtkAction * action,gpointer data)
name|file_save_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|image
operator|=
name|display
operator|->
name|image
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_image_active_drawable
argument_list|(
name|image
argument_list|)
condition|)
return|return;
comment|/*  Only save if the image has been modified  */
if|if
condition|(
name|image
operator|->
name|dirty
operator|||
operator|!
name|GIMP_GUI_CONFIG
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|trust_dirty_flag
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GimpPlugInProcedure
modifier|*
name|save_proc
init|=
name|NULL
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|save_proc
operator|=
name|gimp_image_get_save_proc
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
operator|&&
operator|!
name|save_proc
condition|)
name|save_proc
operator|=
name|file_utils_find_proc
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|plug_in_manager
operator|->
name|save_procs
argument_list|,
name|uri
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|uri
operator|&&
name|save_proc
operator|)
condition|)
block|{
name|file_save_as_cmd_callback
argument_list|(
name|action
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_action_groups_from_name
argument_list|(
literal|"file"
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
name|gimp_action_group_set_action_sensitive
argument_list|(
name|list
operator|->
name|data
argument_list|,
literal|"file-quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|status
operator|=
name|file_save
argument_list|(
name|image
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|,
name|uri
argument_list|,
name|save_proc
argument_list|,
name|GIMP_RUN_WITH_LAST_VALS
argument_list|,
name|FALSE
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|status
condition|)
block|{
case|case
name|GIMP_PDB_SUCCESS
case|:
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_INFO
argument_list|,
name|_
argument_list|(
literal|"Image saved to '%s'"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PDB_CANCEL
case|:
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_INFO
argument_list|,
name|_
argument_list|(
literal|"Saving canceled"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Saving '%s' failed:\n\n%s"
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
break|break;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_action_groups_from_name
argument_list|(
literal|"file"
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
name|gimp_action_group_set_action_sensitive
argument_list|(
name|list
operator|->
name|data
argument_list|,
literal|"file-quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_save_as_cmd_callback (GtkAction * action,gpointer data)
name|file_save_as_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_image_active_drawable
argument_list|(
name|display
operator|->
name|image
argument_list|)
condition|)
return|return;
name|file_save_dialog_show
argument_list|(
name|display
operator|->
name|image
argument_list|,
name|widget
argument_list|,
name|_
argument_list|(
literal|"Save Image"
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_a_copy_cmd_callback (GtkAction * action,gpointer data)
name|file_save_a_copy_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_image_active_drawable
argument_list|(
name|display
operator|->
name|image
argument_list|)
condition|)
return|return;
name|file_save_dialog_show
argument_list|(
name|display
operator|->
name|image
argument_list|,
name|widget
argument_list|,
name|_
argument_list|(
literal|"Save a Copy of the Image"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_template_cmd_callback (GtkAction * action,gpointer data)
name|file_save_template_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Create New Template"
argument_list|)
argument_list|,
name|display
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_SAVE_AS_TEMPLATE
argument_list|,
name|_
argument_list|(
literal|"Enter a name for this template"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_OBJECT
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|file_new_template_callback
argument_list|,
name|display
operator|->
name|image
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
DECL|function|file_revert_cmd_callback (GtkAction * action,gpointer data)
name|file_revert_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|return_if_no_display
argument_list|(
name|display
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|image
operator|=
name|display
operator|->
name|image
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|REVERT_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|uri
condition|)
block|{
name|gimp_message
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Revert failed. "
literal|"No file name associated with this image."
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Revert Image"
argument_list|)
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|display
operator|->
name|shell
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_REVERT
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_REVERT_TO_SAVED
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
name|display
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
name|file_revert_confirm_response
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|basename
operator|=
name|file_utils_uri_display_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_display_name
argument_list|(
name|uri
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
literal|"Revert '%s' to '%s'?"
argument_list|)
argument_list|,
name|basename
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
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
literal|"By reverting the image to the state saved "
literal|"on disk, you will lose all changes, "
literal|"including all undo information."
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
name|REVERT_DATA_KEY
argument_list|,
name|dialog
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
DECL|function|file_close_all_cmd_callback (GtkAction * action,gpointer data)
name|file_close_all_cmd_callback
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
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_displays_dirty
argument_list|(
name|gimp
argument_list|)
condition|)
block|{
name|gimp_displays_delete
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-close-all-dialog"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_quit_cmd_callback (GtkAction * action,gpointer data)
name|file_quit_cmd_callback
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
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_file_open_dialog (Gimp * gimp,const gchar * uri,GtkWidget * parent)
name|file_file_open_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|file_open_dialog_show
argument_list|(
name|parent
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|file_open_dialog_show (GtkWidget * parent,GimpImage * image,const gchar * uri,gboolean open_as_layer)
name|file_open_dialog_show
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|open_as_layer
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
literal|"gimp-file-open-dialog"
argument_list|,
operator|-
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
block|{
if|if
condition|(
name|uri
condition|)
name|gtk_file_chooser_set_uri
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|open_as_layer
condition|)
block|{
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Open Image as Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|image
operator|=
name|image
expr_stmt|;
block|}
else|else
block|{
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Open Image"
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|image
operator|=
name|NULL
expr_stmt|;
block|}
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_save_dialog_show (GimpImage * image,GtkWidget * parent,const gchar * title,gboolean save_a_copy)
name|file_save_dialog_show
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gboolean
name|save_a_copy
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"gimp-file-save-dialog"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
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
literal|"gimp-file-save-dialog"
argument_list|,
operator|-
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
block|{
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"gimp-file-save-dialog"
argument_list|,
name|dialog
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gtk_widget_destroy
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_save_dialog_destroyed
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|dialog
condition|)
block|{
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|gimp_file_dialog_set_image
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|image
argument_list|,
name|save_a_copy
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_save_dialog_destroyed (GtkWidget * dialog,GimpImage * image)
name|file_save_dialog_destroyed
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
if|if
condition|(
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|image
operator|==
name|image
condition|)
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"gimp-file-save-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_new_template_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|file_new_template_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|image
operator|=
operator|(
name|GimpImage
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
operator|)
condition|)
name|name
operator|=
name|_
argument_list|(
literal|"(Unnamed Template)"
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_template_new
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_template_set_from_image
argument_list|(
name|template
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|image
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
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_revert_confirm_response (GtkWidget * dialog,gint response_id,GimpDisplay * display)
name|file_revert_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpImage
modifier|*
name|old_image
init|=
name|display
operator|->
name|image
decl_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|old_image
argument_list|)
argument_list|,
name|REVERT_DATA_KEY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|old_image
operator|->
name|gimp
decl_stmt|;
name|GimpImage
modifier|*
name|new_image
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
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
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|old_image
argument_list|)
argument_list|)
expr_stmt|;
name|new_image
operator|=
name|file_open_image
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|,
name|uri
argument_list|,
name|uri
argument_list|,
name|NULL
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
operator|&
name|status
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_image
condition|)
block|{
name|gimp_displays_reconnect
argument_list|(
name|gimp
argument_list|,
name|old_image
argument_list|,
name|new_image
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
comment|/*  the displays own the image now  */
name|g_object_unref
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
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
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Reverting to '%s' failed:\n\n%s"
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
block|}
block|}
end_function

end_unit

