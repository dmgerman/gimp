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
file|"gui-types.h"
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
file|"dialogs.h"
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
name|GtkWidget
modifier|*
name|file_open_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

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
name|PlugInProcDef
modifier|*
name|load_proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|fileload
specifier|static
name|GtkWidget
modifier|*
name|fileload
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_open_dialog_show (Gimp * gimp,GimpImage * gimage,const gchar * uri,GtkWidget * parent)
name|file_open_dialog_show
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fileload
condition|)
name|fileload
operator|=
name|file_open_dialog_create
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_file_dialog_set_sensitive
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|fileload
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_file_dialog_set_uri
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|fileload
argument_list|)
argument_list|,
name|gimage
argument_list|,
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|fileload
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|fileload
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|file_open_dialog_create (Gimp * gimp)
name|file_open_dialog_create
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
name|gimp_dialog_factory_add_foreign
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp-file-open-dialog"
argument_list|,
name|dialog
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
name|g_filename_from_uri
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
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
name|gtk_widget_hide
argument_list|(
name|open_dialog
argument_list|)
expr_stmt|;
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
DECL|function|file_open_dialog_open_image (GtkWidget * open_dialog,Gimp * gimp,const gchar * uri,const gchar * entered_filename,PlugInProcDef * load_proc)
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
name|PlugInProcDef
modifier|*
name|load_proc
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
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
name|gimage
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
name|gimage
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
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
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

