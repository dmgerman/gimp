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
file|"plug-in/plug-in-proc-def.h"
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
name|gboolean
name|file_save_dialog_check_uri
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gchar
modifier|*
modifier|*
name|ret_uri
parameter_list|,
name|gchar
modifier|*
modifier|*
name|ret_basename
parameter_list|,
name|PlugInProcDef
modifier|*
modifier|*
name|ret_save_proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|file_save_dialog_use_extension
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
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
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|save_a_copy
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
specifier|const
name|gchar
modifier|*
name|uri
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
name|uri
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"gimp-file-save-last-uri"
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|gchar
modifier|*
name|folder_uri
init|=
name|g_path_get_dirname
argument_list|(
name|uri
argument_list|)
decl_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|: FIXME: should use set_uri() but idle stuff in the file chooser seems to override set_current_name() when called immediately after set_uri()
endif|#
directive|endif
if|if
condition|(
name|folder_uri
condition|)
block|{
name|gtk_file_chooser_set_current_folder_uri
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|folder_uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|folder_uri
argument_list|)
expr_stmt|;
block|}
name|gtk_file_chooser_set_current_name
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
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
name|basename
decl_stmt|;
name|PlugInProcDef
modifier|*
name|save_proc
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
name|gimp_file_dialog_set_sensitive
argument_list|(
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_save_dialog_check_uri
argument_list|(
name|save_dialog
argument_list|,
name|gimp
argument_list|,
operator|&
name|uri
argument_list|,
operator|&
name|basename
argument_list|,
operator|&
name|save_proc
argument_list|)
condition|)
block|{
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
name|save_proc
argument_list|,
name|dialog
operator|->
name|save_a_copy
argument_list|)
condition|)
block|{
name|gtk_widget_hide
argument_list|(
name|save_dialog
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
name|basename
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
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_save_dialog_check_uri (GtkWidget * save_dialog,Gimp * gimp,gchar ** ret_uri,gchar ** ret_basename,PlugInProcDef ** ret_save_proc)
name|file_save_dialog_check_uri
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gchar
modifier|*
modifier|*
name|ret_uri
parameter_list|,
name|gchar
modifier|*
modifier|*
name|ret_basename
parameter_list|,
name|PlugInProcDef
modifier|*
modifier|*
name|ret_save_proc
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
name|basename
decl_stmt|;
name|PlugInProcDef
modifier|*
name|save_proc
decl_stmt|;
name|PlugInProcDef
modifier|*
name|uri_proc
decl_stmt|;
name|PlugInProcDef
modifier|*
name|basename_proc
decl_stmt|;
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
if|if
condition|(
operator|!
operator|(
name|uri
operator|&&
name|strlen
argument_list|(
name|uri
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|save_proc
operator|=
name|dialog
operator|->
name|file_proc
expr_stmt|;
name|uri_proc
operator|=
name|file_utils_find_proc
argument_list|(
name|gimp
operator|->
name|save_procs
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|basename_proc
operator|=
name|file_utils_find_proc
argument_list|(
name|gimp
operator|->
name|save_procs
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n\n%s: URI = %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%s: basename = %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%s: selected save_proc: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|save_proc
condition|?
name|save_proc
operator|->
name|menu_label
else|:
literal|"NULL"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%s: URI save_proc: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|uri_proc
condition|?
name|uri_proc
operator|->
name|menu_label
else|:
literal|"NULL"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%s: basename save_proc: %s\n\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|basename_proc
condition|?
name|basename_proc
operator|->
name|menu_label
else|:
literal|"NULL"
argument_list|)
expr_stmt|;
comment|/*  first check if the user entered an extension at all  */
if|if
condition|(
operator|!
name|basename_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: basename has no valid extension\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strchr
argument_list|(
name|basename
argument_list|,
literal|'.'
argument_list|)
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|ext
init|=
name|NULL
decl_stmt|;
name|g_print
argument_list|(
literal|"%s: basename has no '.', trying to add extension\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|save_proc
condition|)
block|{
name|ext
operator|=
literal|"xcf"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|save_proc
operator|->
name|extensions_list
condition|)
block|{
name|ext
operator|=
name|save_proc
operator|->
name|extensions_list
operator|->
name|data
expr_stmt|;
block|}
if|if
condition|(
name|ext
condition|)
block|{
name|gchar
modifier|*
name|ext_uri
init|=
name|g_strconcat
argument_list|(
name|uri
argument_list|,
literal|"."
argument_list|,
name|ext
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|ext_basename
init|=
name|g_strconcat
argument_list|(
name|basename
argument_list|,
literal|"."
argument_list|,
name|ext
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|g_print
argument_list|(
literal|"%s: appending .%s to basename\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|ext
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|uri
operator|=
name|ext_uri
expr_stmt|;
name|basename
operator|=
name|ext_basename
expr_stmt|;
name|uri_proc
operator|=
name|file_utils_find_proc
argument_list|(
name|gimp
operator|->
name|save_procs
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|basename_proc
operator|=
name|file_utils_find_proc
argument_list|(
name|gimp
operator|->
name|save_procs
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|utf8
operator|=
name|g_filename_to_utf8
argument_list|(
name|basename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_current_name
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|save_dialog
argument_list|)
argument_list|,
name|utf8
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"%s: save_proc has no extensions, continuing without\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
comment|/*  there may be file formats with no extension at all, use                *  the selected proc in this case.                */
name|basename_proc
operator|=
name|save_proc
expr_stmt|;
if|if
condition|(
operator|!
name|uri_proc
condition|)
name|uri_proc
operator|=
name|basename_proc
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|basename_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: unable to figure save_proc, bailing out\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The given filename does not have any known "
literal|"file extension. Please enter a known file "
literal|"extension or select a file format from the "
literal|"file format list."
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|save_proc
operator|&&
operator|!
name|save_proc
operator|->
name|extensions_list
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: basename has '.', but save_proc has no extensions, "
literal|"accepting random extension\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
comment|/*  accept any random extension if the file format has            *  no extensions at all            */
name|basename_proc
operator|=
name|save_proc
expr_stmt|;
if|if
condition|(
operator|!
name|uri_proc
condition|)
name|uri_proc
operator|=
name|basename_proc
expr_stmt|;
block|}
block|}
comment|/*  then check if the selected format matches the entered extension  */
if|if
condition|(
operator|!
name|save_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: no save_proc was selected from the list\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|basename_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: basename had no useful extension, bailing out\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The given filename does not have any known "
literal|"file extension. Please enter a known file "
literal|"extension or select a file format from the "
literal|"file format list."
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_print
argument_list|(
literal|"%s: use URI's proc '%s' so indirect saving works\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|uri_proc
operator|->
name|menu_label
argument_list|)
expr_stmt|;
comment|/*  use the URI's proc if no save proc was selected  */
name|save_proc
operator|=
name|uri_proc
expr_stmt|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"%s: save_proc '%s' was selected from the list\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|save_proc
operator|->
name|menu_label
argument_list|)
expr_stmt|;
if|if
condition|(
name|save_proc
operator|!=
name|basename_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: however the basename's proc is '%s'\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|basename_proc
condition|?
name|basename_proc
operator|->
name|menu_label
else|:
literal|"NULL"
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri_proc
operator|!=
name|basename_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: that's impossible for remote URIs, bailing out\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
comment|/*  remote URI  */
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Saving remote files needs to determine the "
literal|"file format from the file extension. Please "
literal|"enter a file extension that matches the selected "
literal|"file format or enter no file extension at all."
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"%s: ask the user if she really wants that filename\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
comment|/*  local URI  */
if|if
condition|(
operator|!
name|file_save_dialog_use_extension
argument_list|(
name|save_dialog
argument_list|,
name|uri
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|save_proc
operator|!=
name|uri_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: use URI's proc '%s' so indirect saving works\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|uri_proc
operator|->
name|menu_label
argument_list|)
expr_stmt|;
comment|/*  need to use the URI's proc for saving because e.g.            *  the GIF plug-in can't save a GIF to sftp://            */
name|save_proc
operator|=
name|uri_proc
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|save_proc
condition|)
block|{
name|g_print
argument_list|(
literal|"%s: EEEEEEK\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"Yay! You found a bug. Please report this at "
literal|"http://bugzilla.gnome.org/ and paste the console "
literal|"output to the 'Additional Comments' field"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gtk_file_chooser_set_uri
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|save_dialog
argument_list|)
argument_list|,
name|uri
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_file_overwrite_dialog
argument_list|(
name|save_dialog
argument_list|,
name|uri
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
operator|*
name|ret_uri
operator|=
name|uri
expr_stmt|;
operator|*
name|ret_basename
operator|=
name|basename
expr_stmt|;
operator|*
name|ret_save_proc
operator|=
name|save_proc
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_save_dialog_use_extension (GtkWidget * save_dialog,const gchar * uri)
name|file_save_dialog_use_extension
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gboolean
name|use_name
init|=
name|FALSE
decl_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Extension Mismatch"
argument_list|)
argument_list|,
name|GIMP_STOCK_QUESTION
argument_list|,
name|save_dialog
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GTK_STOCK_NO
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_YES
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
literal|"The given file extension does "
literal|"not match the chosen file type."
argument_list|)
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
literal|"Do you want to use this name anyway?"
argument_list|)
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
name|g_object_ref
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|use_name
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dialog
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
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|use_name
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|file_save_dialog_save_image (GtkWidget * save_dialog,GimpImage * gimage,const gchar * uri,PlugInProcDef * save_proc,gboolean save_a_copy)
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
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|save_a_copy
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
name|g_object_ref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|status
operator|=
name|file_save
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
name|save_proc
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|save_a_copy
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
literal|"gimp-file-save-last-uri"
argument_list|,
name|g_strdup
argument_list|(
name|uri
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimage
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

