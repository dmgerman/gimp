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
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-run.h"
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
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"file-dialog-utils.h"
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
name|GtkWidget
modifier|*
name|file_save_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

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
name|void
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
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|filesave
specifier|static
name|GtkWidget
modifier|*
name|filesave
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_save_dialog_show (GimpImage * gimage,GimpMenuFactory * menu_factory,GtkWidget * parent)
name|file_save_dialog_show
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
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
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
condition|)
return|return;
if|if
condition|(
operator|!
name|filesave
condition|)
name|filesave
operator|=
name|file_save_dialog_create
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|menu_factory
argument_list|)
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|set_uri_and_proc
operator|=
name|TRUE
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|set_image_clean
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|filesave
argument_list|)
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Save Image"
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_image_get_filename
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|filename
condition|?
name|filename
else|:
literal|"."
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_item_factory_update
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|item_factory
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|file_dialog_show
argument_list|(
name|filesave
argument_list|,
name|parent
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_a_copy_dialog_show (GimpImage * gimage,GimpMenuFactory * menu_factory,GtkWidget * parent)
name|file_save_a_copy_dialog_show
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
condition|)
return|return;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
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
operator|!
name|filesave
condition|)
name|filesave
operator|=
name|file_save_dialog_create
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
name|menu_factory
argument_list|)
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|set_uri_and_proc
operator|=
name|FALSE
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|set_image_clean
operator|=
name|FALSE
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|filesave
argument_list|)
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Save a Copy of the Image"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|filename
condition|?
name|filename
else|:
literal|"."
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_item_factory_update
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|filesave
argument_list|)
operator|->
name|item_factory
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|file_dialog_show
argument_list|(
name|filesave
argument_list|,
name|parent
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
DECL|function|file_save_dialog_create (Gimp * gimp,GimpMenuFactory * menu_factory)
name|file_save_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|save_dialog
decl_stmt|;
name|save_dialog
operator|=
name|gimp_file_dialog_new
argument_list|(
name|gimp
argument_list|,
name|menu_factory
argument_list|,
literal|"<Save>"
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
name|gimp_dialog_factory_add_foreign
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp-file-save-dialog"
argument_list|,
name|save_dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|save_dialog
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
name|save_dialog
return|;
block|}
end_function

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
name|GtkFileSelection
modifier|*
name|fs
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|raw_filename
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
if|if
condition|(
name|response_id
operator|!=
name|GTK_RESPONSE_OK
condition|)
block|{
name|file_dialog_hide
argument_list|(
name|save_dialog
argument_list|)
expr_stmt|;
return|return;
block|}
name|fs
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|save_dialog
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|fs
argument_list|)
expr_stmt|;
name|raw_filename
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|fs
operator|->
name|selection_entry
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|filename
operator|&&
name|raw_filename
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|filename
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
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
if|if
condition|(
name|filename
index|[
name|strlen
argument_list|(
name|filename
argument_list|)
operator|-
literal|1
index|]
operator|!=
name|G_DIR_SEPARATOR
condition|)
block|{
name|gchar
modifier|*
name|s
init|=
name|g_strconcat
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|fs
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|s
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_file_selection_set_filename
argument_list|(
name|fs
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|file_save_overwrite
argument_list|(
name|save_dialog
argument_list|,
name|uri
argument_list|,
name|raw_filename
argument_list|)
expr_stmt|;
block|}
block|}
else|else
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
name|gtk_widget_set_sensitive
argument_list|(
name|save_dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|save_dialog
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
literal|"File '%s' exists.\n"
literal|"Overwrite it?"
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
literal|"File Exists!"
argument_list|)
argument_list|,
name|save_dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_SAVE_OVERWRITE
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|message
argument_list|,
name|GTK_STOCK_YES
argument_list|,
name|GTK_STOCK_NO
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
name|gtk_widget_set_sensitive
argument_list|(
name|save_dialog
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
if|if
condition|(
name|overwrite
condition|)
block|{
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
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|overwrite_data
operator|->
name|save_dialog
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
name|void
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
block|}
else|else
block|{
name|file_dialog_hide
argument_list|(
name|save_dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

