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
file|"core/gimpprogress.h"
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
file|"file-save-dialog.h"
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
name|file_save_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
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
name|void
name|file_save_overwrite
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_save_overwrite_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|overwrite
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|file_save_dialog_save_image
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|set_uri_and_proc
parameter_list|,
name|gboolean
name|set_image_clean
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|file_save_dialog_new (Gimp * gimp)
name|file_save_dialog_new
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
name|GTK_FILE_CHOOSER_ACTION_SAVE
argument_list|,
name|_
argument_list|(
literal|"Save Image"
argument_list|)
argument_list|,
literal|"gimp-file-save"
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|GIMP_HELP_FILE_SAVE
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
name|file_save_dialog_response
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
DECL|function|file_save_dialog_response (GtkWidget * save_dialog,gint response_id,Gimp * gimp)
name|file_save_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
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
name|save_dialog
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
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
name|save_dialog
argument_list|)
expr_stmt|;
return|return;
block|}
name|uri
operator|=
name|gtk_file_chooser_get_uri
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|save_dialog
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
name|file_save_overwrite
argument_list|(
name|save_dialog
argument_list|,
name|uri
argument_list|,
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_file_dialog_set_sensitive
argument_list|(
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_save_dialog_save_image
argument_list|(
name|save_dialog
argument_list|,
name|dialog
operator|->
name|gimage
argument_list|,
name|uri
argument_list|,
name|uri
argument_list|,
name|dialog
operator|->
name|file_proc
argument_list|,
name|dialog
operator|->
name|set_uri_and_proc
argument_list|,
name|dialog
operator|->
name|set_image_clean
argument_list|)
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|save_dialog
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
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|typedef|OverwriteData
typedef|typedef
name|struct
name|_OverwriteData
name|OverwriteData
typedef|;
end_typedef

begin_struct
DECL|struct|_OverwriteData
struct|struct
name|_OverwriteData
block|{
DECL|member|save_dialog
name|GtkWidget
modifier|*
name|save_dialog
decl_stmt|;
DECL|member|uri
name|gchar
modifier|*
name|uri
decl_stmt|;
DECL|member|raw_filename
name|gchar
modifier|*
name|raw_filename
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|file_save_overwrite (GtkWidget * save_dialog,const gchar * uri,const gchar * raw_filename)
name|file_save_overwrite
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|)
block|{
name|OverwriteData
modifier|*
name|overwrite_data
decl_stmt|;
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|overwrite_data
operator|=
name|g_new0
argument_list|(
name|OverwriteData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|overwrite_data
operator|->
name|save_dialog
operator|=
name|save_dialog
expr_stmt|;
name|overwrite_data
operator|->
name|uri
operator|=
name|g_strdup
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|overwrite_data
operator|->
name|raw_filename
operator|=
name|g_strdup
argument_list|(
name|raw_filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|message
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"A file named '%s' already exists.\n\n"
literal|"Do you want to replace it with the image "
literal|"you are saving?"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|query_box
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"File exists!"
argument_list|)
argument_list|,
name|save_dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|message
argument_list|,
name|_
argument_list|(
literal|"Replace"
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|file_save_overwrite_callback
argument_list|,
name|overwrite_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|query_box
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|save_dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_file_dialog_set_sensitive
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|save_dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|save_dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_save_overwrite_callback (GtkWidget * widget,gboolean overwrite,gpointer data)
name|file_save_overwrite_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|overwrite
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|OverwriteData
modifier|*
name|overwrite_data
init|=
name|data
decl_stmt|;
name|GimpFileDialog
modifier|*
name|dialog
init|=
name|GIMP_FILE_DIALOG
argument_list|(
name|overwrite_data
operator|->
name|save_dialog
argument_list|)
decl_stmt|;
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|overwrite
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_save_dialog_save_image
argument_list|(
name|overwrite_data
operator|->
name|save_dialog
argument_list|,
name|dialog
operator|->
name|gimage
argument_list|,
name|overwrite_data
operator|->
name|uri
argument_list|,
name|overwrite_data
operator|->
name|raw_filename
argument_list|,
name|dialog
operator|->
name|file_proc
argument_list|,
name|dialog
operator|->
name|set_uri_and_proc
argument_list|,
name|dialog
operator|->
name|set_image_clean
argument_list|)
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|overwrite_data
operator|->
name|save_dialog
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_file_dialog_set_sensitive
argument_list|(
name|dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_data
operator|->
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_data
operator|->
name|raw_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_save_dialog_save_image (GtkWidget * save_dialog,GimpImage * gimage,const gchar * uri,const gchar * raw_filename,PlugInProcDef * save_proc,gboolean set_uri_and_proc,gboolean set_image_clean)
name|file_save_dialog_save_image
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|set_uri_and_proc
parameter_list|,
name|gboolean
name|set_image_clean
parameter_list|)
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
name|status
operator|=
name|file_save_as
argument_list|(
name|gimage
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|save_dialog
argument_list|)
argument_list|,
name|uri
argument_list|,
name|raw_filename
argument_list|,
name|save_proc
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|set_uri_and_proc
argument_list|,
name|set_image_clean
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_SUCCESS
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
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

