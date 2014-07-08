begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
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
file|"widgets/gimpcontainerentry.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpprogressbox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"file-open-location-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|file_open_location_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|file_open_location_completion
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|completion
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|file_open_location_dialog_new (Gimp * gimp)
name|file_open_location_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkEntryCompletion
modifier|*
name|completion
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
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Open Location"
argument_list|)
argument_list|,
literal|"gimp-file-open-location"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_OPEN_LOCATION
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OPEN
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
name|file_open_location_response
argument_list|)
argument_list|,
name|gimp
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
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_STOCK_WEB
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Enter location (URI):"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
comment|/* we don't want the context to affect the entry, so create    * a scratch one instead of using e.g. the user context    */
name|context
operator|=
name|gimp_context_new
argument_list|(
name|gimp
argument_list|,
literal|"file-open-location-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_container_entry_new
argument_list|(
name|gimp
operator|->
name|documents
argument_list|,
name|context
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|completion
operator|=
name|gtk_entry_get_completion
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_completion_set_match_func
argument_list|(
name|completion
argument_list|,
name|file_open_location_completion
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|entry
argument_list|,
literal|400
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|entry
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
name|entry
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"location-entry"
argument_list|,
name|entry
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
DECL|function|file_open_location_response (GtkDialog * dialog,gint response_id,Gimp * gimp)
name|file_open_location_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|response_id
operator|!=
name|GTK_RESPONSE_OK
condition|)
block|{
name|box
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"progress-box"
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|&&
name|GIMP_PROGRESS_BOX
argument_list|(
name|box
argument_list|)
operator|->
name|active
condition|)
name|gimp_progress_cancel
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|entry
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"location-entry"
argument_list|)
expr_stmt|;
name|gtk_editable_set_editable
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_dialog_set_response_sensitive
argument_list|(
name|dialog
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|text
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|text
operator|&&
name|strlen
argument_list|(
name|text
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GFile
modifier|*
name|file
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
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|text
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|file
operator|=
name|file_utils_filename_to_file
argument_list|(
name|gimp
argument_list|,
name|text
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|box
operator|=
name|gimp_progress_box_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"progress-box"
argument_list|,
name|box
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|GFile
modifier|*
name|entered_file
init|=
name|g_file_new_for_uri
argument_list|(
name|text
argument_list|)
decl_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|image
operator|=
name|file_open_with_proc_and_display
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
name|box
argument_list|)
argument_list|,
name|file
argument_list|,
name|entered_file
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|G_OBJECT
argument_list|(
name|gtk_widget_get_screen
argument_list|(
name|entry
argument_list|)
argument_list|)
argument_list|,
name|gimp_widget_get_monitor
argument_list|(
name|entry
argument_list|)
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|entered_file
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|==
name|NULL
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
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
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|text
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
name|gtk_dialog_set_response_sensitive
argument_list|(
name|dialog
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_editable_set_editable
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_open_location_completion (GtkEntryCompletion * completion,const gchar * key,GtkTreeIter * iter,gpointer data)
name|file_open_location_completion
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|completion
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_entry_completion_get_model
argument_list|(
name|completion
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|normalized
decl_stmt|;
name|gchar
modifier|*
name|case_normalized
decl_stmt|;
name|gboolean
name|match
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
literal|1
argument_list|,
operator|&
name|name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
return|return
name|FALSE
return|;
name|normalized
operator|=
name|g_utf8_normalize
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|G_NORMALIZE_ALL
argument_list|)
expr_stmt|;
name|case_normalized
operator|=
name|g_utf8_casefold
argument_list|(
name|normalized
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|match
operator|=
operator|(
name|strncmp
argument_list|(
name|key
argument_list|,
name|case_normalized
argument_list|,
name|strlen
argument_list|(
name|key
argument_list|)
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|match
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|colon
init|=
name|strchr
argument_list|(
name|case_normalized
argument_list|,
literal|':'
argument_list|)
decl_stmt|;
if|if
condition|(
name|colon
operator|&&
name|strlen
argument_list|(
name|colon
argument_list|)
operator|>
literal|2
operator|&&
name|colon
index|[
literal|1
index|]
operator|==
literal|'/'
operator|&&
name|colon
index|[
literal|2
index|]
operator|==
literal|'/'
condition|)
name|match
operator|=
operator|(
name|strncmp
argument_list|(
name|key
argument_list|,
name|colon
operator|+
literal|3
argument_list|,
name|strlen
argument_list|(
name|key
argument_list|)
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|normalized
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|case_normalized
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|match
return|;
block|}
end_function

end_unit

