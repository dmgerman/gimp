begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpitem.h"
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
name|open_dialog
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
name|file_open_dialog_open_image
parameter_list|(
name|GtkWidget
modifier|*
name|open_dialog
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|entered_filename
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
name|file_open_dialog_open_layer
parameter_list|(
name|GtkWidget
modifier|*
name|open_dialog
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
specifier|const
name|gchar
modifier|*
name|entered_filename
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
name|gimp_file_dialog_new
argument_list|(
name|gimp
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_OPEN
argument_list|,
name|_
argument_list|(
literal|"Open Image"
argument_list|)
argument_list|,
literal|"gimp-file-open"
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|GIMP_HELP_FILE_OPEN
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
DECL|function|file_open_dialog_response (GtkWidget * open_dialog,gint response_id,Gimp * gimp)
name|file_open_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|open_dialog
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
name|dialog
init|=
name|GIMP_FILE_DIALOG
argument_list|(
name|open_dialog
argument_list|)
decl_stmt|;
name|GSList
modifier|*
name|uris
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
name|dialog
operator|->
name|busy
condition|)
name|gtk_widget_hide
argument_list|(
name|open_dialog
argument_list|)
expr_stmt|;
return|return;
block|}
name|uris
operator|=
name|gtk_file_chooser_get_uris
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|open_dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_file_dialog_set_sensitive
argument_list|(
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  open layers in reverse order so they appear in the same    *  order as in the file dialog    */
if|if
condition|(
name|dialog
operator|->
name|image
condition|)
name|uris
operator|=
name|g_slist_reverse
argument_list|(
name|uris
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|uris
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
name|gchar
modifier|*
name|filename
init|=
name|file_utils_filename_from_uri
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|gboolean
name|regular
init|=
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|regular
condition|)
continue|continue;
block|}
if|if
condition|(
name|dialog
operator|->
name|image
condition|)
block|{
if|if
condition|(
name|file_open_dialog_open_layer
argument_list|(
name|open_dialog
argument_list|,
name|dialog
operator|->
name|image
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|dialog
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
name|open_dialog
argument_list|,
name|gimp
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|list
operator|->
name|data
argument_list|,
name|dialog
operator|->
name|file_proc
argument_list|)
condition|)
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
name|gdk_window_raise
argument_list|(
name|open_dialog
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|dialog
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
name|gtk_widget_hide
argument_list|(
name|open_dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|image
condition|)
name|gimp_image_flush
argument_list|(
name|dialog
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
name|gimp_file_dialog_set_sensitive
argument_list|(
name|dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
name|uris
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|uris
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_open_dialog_open_image (GtkWidget * open_dialog,Gimp * gimp,const gchar * uri,const gchar * entered_filename,GimpPlugInProcedure * load_proc)
name|file_open_dialog_open_image
parameter_list|(
name|GtkWidget
modifier|*
name|open_dialog
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|entered_filename
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
name|open_dialog
argument_list|)
argument_list|,
name|uri
argument_list|,
name|entered_filename
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
name|image
condition|)
block|{
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
name|open_dialog
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
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_open_dialog_open_layer (GtkWidget * open_dialog,GimpImage * image,const gchar * uri,const gchar * entered_filename,GimpPlugInProcedure * load_proc)
name|file_open_dialog_open_layer
parameter_list|(
name|GtkWidget
modifier|*
name|open_dialog
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
specifier|const
name|gchar
modifier|*
name|entered_filename
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|load_proc
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|new_layer
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
name|new_layer
operator|=
name|file_open_layer
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
name|open_dialog
argument_list|)
argument_list|,
name|image
argument_list|,
name|uri
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
name|new_layer
condition|)
block|{
name|GimpItem
modifier|*
name|new_item
init|=
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|new_item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|off_x
operator|=
operator|(
name|width
operator|-
name|gimp_item_width
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_x
expr_stmt|;
name|off_y
operator|=
operator|(
name|height
operator|-
name|gimp_item_height
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_y
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|new_item
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|new_layer
argument_list|,
operator|-
literal|1
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
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|open_dialog
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
return|return
name|FALSE
return|;
block|}
end_function

end_unit

