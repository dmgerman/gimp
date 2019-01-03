begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
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
file|"file/gimp-file.h"
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
file|"widgets/gimpopendialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"file-open-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|file_open_dialog_response
parameter_list|(
name|GtkWidget
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
name|GimpImage
modifier|*
name|file_open_dialog_open_image
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|load_proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|file_open_dialog_open_layers
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|load_proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|file_open_dialog_new (Gimp * gimp)
name|file_open_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
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
name|gimp_open_dialog_new
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_select_multiple
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_file_dialog_load_state
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-file-open-dialog-state"
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
name|file_open_dialog_response
argument_list|)
argument_list|,
name|gimp
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
DECL|function|file_open_dialog_response (GtkWidget * dialog,gint response_id,Gimp * gimp)
name|file_open_dialog_response
parameter_list|(
name|GtkWidget
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
name|GimpFileDialog
modifier|*
name|file_dialog
init|=
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|GimpOpenDialog
modifier|*
name|open_dialog
init|=
name|GIMP_OPEN_DIALOG
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
name|GSList
modifier|*
name|files
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|gimp_file_dialog_save_state
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-file-open-dialog-state"
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|!=
name|GTK_RESPONSE_OK
condition|)
block|{
if|if
condition|(
operator|!
name|file_dialog
operator|->
name|busy
condition|)
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return;
block|}
name|files
operator|=
name|gtk_file_chooser_get_files
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|files
condition|)
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_FILE_OPEN_LAST_FILE_KEY
argument_list|,
name|g_object_ref
argument_list|(
name|files
operator|->
name|data
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|gimp_file_dialog_set_sensitive
argument_list|(
name|file_dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* When we are going to open new image windows, unset the transient    * window. We don't need it since we will use gdk_window_raise() to    * keep the dialog on top. And if we don't do it, then the dialog    * will pull the image window it was invoked from on top of all the    * new opened image windows, and we don't want that to happen.    */
if|if
condition|(
operator|!
name|open_dialog
operator|->
name|open_as_layers
condition|)
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_dialog
operator|->
name|image
condition|)
name|g_object_ref
argument_list|(
name|file_dialog
operator|->
name|image
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|files
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GFile
modifier|*
name|file
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|open_dialog
operator|->
name|open_as_layers
condition|)
block|{
if|if
condition|(
operator|!
name|file_dialog
operator|->
name|image
condition|)
block|{
name|file_dialog
operator|->
name|image
operator|=
name|file_open_dialog_open_image
argument_list|(
name|dialog
argument_list|,
name|gimp
argument_list|,
name|file
argument_list|,
name|file_dialog
operator|->
name|file_proc
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_dialog
operator|->
name|image
condition|)
block|{
name|g_object_ref
argument_list|(
name|file_dialog
operator|->
name|image
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|file_open_dialog_open_layers
argument_list|(
name|dialog
argument_list|,
name|file_dialog
operator|->
name|image
argument_list|,
name|file
argument_list|,
name|file_dialog
operator|->
name|file_proc
argument_list|)
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|file_open_dialog_open_image
argument_list|(
name|dialog
argument_list|,
name|gimp
argument_list|,
name|file
argument_list|,
name|file_dialog
operator|->
name|file_proc
argument_list|)
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
comment|/* Make the dialog stay on top of all images we open if                * we open say 10 at once                */
name|gdk_window_raise
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|file_dialog
operator|->
name|canceled
condition|)
break|break;
block|}
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|file_dialog
operator|->
name|image
condition|)
block|{
if|if
condition|(
name|open_dialog
operator|->
name|open_as_layers
condition|)
name|gimp_image_flush
argument_list|(
name|file_dialog
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file_dialog
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|file_dialog
operator|->
name|image
condition|)
name|g_object_unref
argument_list|(
name|file_dialog
operator|->
name|image
argument_list|)
expr_stmt|;
name|gimp_file_dialog_set_sensitive
argument_list|(
name|file_dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|g_slist_free_full
argument_list|(
name|files
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpImage
modifier|*
DECL|function|file_open_dialog_open_image (GtkWidget * dialog,Gimp * gimp,GFile * file,GimpPlugInProcedure * load_proc)
name|file_open_dialog_open_image
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|load_proc
parameter_list|)
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
name|dialog
argument_list|)
argument_list|,
name|file
argument_list|,
name|file
argument_list|,
name|FALSE
argument_list|,
name|load_proc
argument_list|,
name|G_OBJECT
argument_list|(
name|gimp_widget_get_monitor
argument_list|(
name|dialog
argument_list|)
argument_list|)
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
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|dialog
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
return|return
name|image
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_open_dialog_open_layers (GtkWidget * dialog,GimpImage * image,GFile * file,GimpPlugInProcedure * load_proc)
name|file_open_dialog_open_layers
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|load_proc
parameter_list|)
block|{
name|GList
modifier|*
name|new_layers
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
name|new_layers
operator|=
name|file_open_layers
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|image
argument_list|,
name|FALSE
argument_list|,
name|file
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|load_proc
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
name|new_layers
condition|)
block|{
name|gimp_image_add_layers
argument_list|(
name|image
argument_list|,
name|new_layers
argument_list|,
name|GIMP_IMAGE_ACTIVE_PARENT
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Open layers"
argument_list|)
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|new_layers
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_CANCEL
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
name|dialog
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
return|return
name|FALSE
return|;
block|}
end_function

end_unit

