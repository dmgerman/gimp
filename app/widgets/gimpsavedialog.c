begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsavedialog.c  * Copyright (C) 2015 Jehan<jehan@girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
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
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"file/gimp-file.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpfiledialog.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpsavedialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|GimpSaveDialogState
typedef|typedef
name|struct
name|_GimpSaveDialogState
name|GimpSaveDialogState
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSaveDialogState
struct|struct
name|_GimpSaveDialogState
block|{
DECL|member|filter_name
name|gchar
modifier|*
name|filter_name
decl_stmt|;
DECL|member|compat
name|gboolean
name|compat
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_save_dialog_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_save_dialog_save_state
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|state_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_save_dialog_load_state
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|state_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GFile
modifier|*
name|gimp_save_dialog_get_default_folder
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
name|gimp_save_dialog_add_compat_toggle
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_save_dialog_compat_toggled
parameter_list|(
name|GtkToggleButton
modifier|*
name|button
parameter_list|,
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpSaveDialogState
modifier|*
name|gimp_save_dialog_get_state
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_save_dialog_set_state
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|,
name|GimpSaveDialogState
modifier|*
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_save_dialog_state_destroy
parameter_list|(
name|GimpSaveDialogState
modifier|*
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSaveDialog,gimp_save_dialog,GIMP_TYPE_FILE_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSaveDialog
argument_list|,
argument|gimp_save_dialog
argument_list|,
argument|GIMP_TYPE_FILE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_save_dialog_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_save_dialog_class_init
parameter_list|(
name|GimpSaveDialogClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpFileDialogClass
modifier|*
name|fd_class
init|=
name|GIMP_FILE_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_save_dialog_constructed
expr_stmt|;
name|fd_class
operator|->
name|save_state
operator|=
name|gimp_save_dialog_save_state
expr_stmt|;
name|fd_class
operator|->
name|load_state
operator|=
name|gimp_save_dialog_load_state
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_init (GimpSaveDialog * dialog)
name|gimp_save_dialog_init
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_constructed (GObject * object)
name|gimp_save_dialog_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSaveDialog
modifier|*
name|dialog
init|=
name|GIMP_SAVE_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
comment|/* GimpFileDialog's constructed() is doing a few initialization    * common to all file dialogs. */
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_save_dialog_add_compat_toggle
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_save_state (GimpFileDialog * dialog,const gchar * state_name)
name|gimp_save_dialog_save_state
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|state_name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SAVE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|gimp
argument_list|)
argument_list|,
name|state_name
argument_list|,
name|gimp_save_dialog_get_state
argument_list|(
name|GIMP_SAVE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_save_dialog_state_destroy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_load_state (GimpFileDialog * dialog,const gchar * state_name)
name|gimp_save_dialog_load_state
parameter_list|(
name|GimpFileDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|state_name
parameter_list|)
block|{
name|GimpSaveDialogState
modifier|*
name|state
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SAVE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|state
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|gimp
argument_list|)
argument_list|,
name|state_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
condition|)
name|gimp_save_dialog_set_state
argument_list|(
name|GIMP_SAVE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_save_dialog_new (Gimp * gimp)
name|gimp_save_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpSaveDialog
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
name|g_object_new
argument_list|(
name|GIMP_TYPE_SAVE_DIALOG
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"title"
argument_list|,
name|_
argument_list|(
literal|"Save Image"
argument_list|)
argument_list|,
literal|"role"
argument_list|,
literal|"gimp-file-save"
argument_list|,
literal|"help-id"
argument_list|,
name|GIMP_HELP_FILE_SAVE
argument_list|,
literal|"stock-id"
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
literal|"automatic-label"
argument_list|,
name|_
argument_list|(
literal|"By Extension"
argument_list|)
argument_list|,
literal|"automatic-help-id"
argument_list|,
name|GIMP_HELP_FILE_SAVE_BY_EXTENSION
argument_list|,
literal|"action"
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_SAVE
argument_list|,
literal|"file-procs"
argument_list|,
name|gimp
operator|->
name|plug_in_manager
operator|->
name|save_procs
argument_list|,
literal|"file-procs-all-images"
argument_list|,
name|gimp
operator|->
name|plug_in_manager
operator|->
name|export_procs
argument_list|,
literal|"file-filter-label"
argument_list|,
name|_
argument_list|(
literal|"All XCF images"
argument_list|)
argument_list|,
literal|"local-only"
argument_list|,
name|FALSE
argument_list|,
literal|"do-overwrite-confirmation"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_save_dialog_set_image (GimpSaveDialog * dialog,Gimp * gimp,GimpImage * image,gboolean save_a_copy,gboolean close_after_saving,GimpObject * display)
name|gimp_save_dialog_set_image
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|save_a_copy
parameter_list|,
name|gboolean
name|close_after_saving
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|GFile
modifier|*
name|dir_file
init|=
name|NULL
decl_stmt|;
name|GFile
modifier|*
name|name_file
init|=
name|NULL
decl_stmt|;
name|GFile
modifier|*
name|ext_file
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|version_string
decl_stmt|;
name|gint
name|rle_version
decl_stmt|;
name|gint
name|zlib_version
decl_stmt|;
name|gchar
modifier|*
name|tooltip
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SAVE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
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
name|dialog
operator|->
name|save_a_copy
operator|=
name|save_a_copy
expr_stmt|;
name|dialog
operator|->
name|close_after_saving
operator|=
name|close_after_saving
expr_stmt|;
name|dialog
operator|->
name|display_to_close
operator|=
name|display
expr_stmt|;
name|gimp_file_dialog_set_file_proc
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*    * Priority of default paths for Save:    *    *   1. Last Save a copy-path (applies only to Save a copy)    *   2. Last Save path    *   3. Path of source XCF    *   4. Path of Import source    *   5. Last Save path of any GIMP document    *   6. The default path (usually the OS 'Documents' path)    */
if|if
condition|(
name|save_a_copy
condition|)
name|dir_file
operator|=
name|gimp_image_get_save_a_copy_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir_file
condition|)
name|dir_file
operator|=
name|gimp_image_get_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir_file
condition|)
name|dir_file
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"gimp-image-source-file"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir_file
condition|)
name|dir_file
operator|=
name|gimp_image_get_imported_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir_file
condition|)
name|dir_file
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_FILE_SAVE_LAST_FILE_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir_file
condition|)
name|dir_file
operator|=
name|gimp_save_dialog_get_default_folder
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/* Priority of default basenames for Save:    *    *   1. Last Save a copy-name (applies only to Save a copy)    *   2. Last Save name    *   3. Last Export name    *   3. The source image path    *   3. 'Untitled'    */
if|if
condition|(
name|save_a_copy
condition|)
name|name_file
operator|=
name|gimp_image_get_save_a_copy_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name_file
condition|)
name|name_file
operator|=
name|gimp_image_get_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name_file
condition|)
name|name_file
operator|=
name|gimp_image_get_exported_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name_file
condition|)
name|name_file
operator|=
name|gimp_image_get_imported_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name_file
condition|)
name|name_file
operator|=
name|gimp_image_get_untitled_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
comment|/* Priority of default type/extension for Save:    *    *   1. Type of last Save    *   2. .xcf (which we don't explicitly append)    */
name|ext_file
operator|=
name|gimp_image_get_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|ext_file
condition|)
name|g_object_ref
argument_list|(
name|ext_file
argument_list|)
expr_stmt|;
else|else
name|ext_file
operator|=
name|g_file_new_for_uri
argument_list|(
literal|"file:///we/only/care/about/extension.xcf"
argument_list|)
expr_stmt|;
name|gimp_image_get_xcf_version
argument_list|(
name|image
argument_list|,
name|FALSE
argument_list|,
operator|&
name|rle_version
argument_list|,
operator|&
name|version_string
argument_list|)
expr_stmt|;
name|gimp_image_get_xcf_version
argument_list|(
name|image
argument_list|,
name|TRUE
argument_list|,
operator|&
name|zlib_version
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|rle_version
operator|==
name|zlib_version
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|dialog
operator|->
name|compat_toggle
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tooltip
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"The image uses features from %s and "
literal|"cannot be saved for older GIMP "
literal|"versions."
argument_list|)
argument_list|,
name|version_string
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|dialog
operator|->
name|compat_toggle
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|tooltip
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Disables compression to make the XCF "
literal|"file readable by %s and later."
argument_list|)
argument_list|,
name|version_string
argument_list|)
expr_stmt|;
block|}
name|gimp_help_set_help_data
argument_list|(
name|dialog
operator|->
name|compat_toggle
argument_list|,
name|tooltip
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tooltip
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|compat_toggle
argument_list|)
expr_stmt|;
comment|/* We set the compatibility mode by default either if the image was   * previously saved with the compatibility mode, or if it has never been   * saved and the last GimpSaveDialogState had compatibility mode ON. */
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|dialog
operator|->
name|compat_toggle
argument_list|)
argument_list|,
name|gtk_widget_get_sensitive
argument_list|(
name|dialog
operator|->
name|compat_toggle
argument_list|)
operator|&&
operator|(
name|gimp_image_get_xcf_compat_mode
argument_list|(
name|image
argument_list|)
operator|||
operator|(
operator|!
name|gimp_image_get_file
argument_list|(
name|image
argument_list|)
operator|&&
name|dialog
operator|->
name|compat
operator|)
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ext_file
condition|)
block|{
name|GFile
modifier|*
name|tmp_file
init|=
name|file_utils_file_with_new_ext
argument_list|(
name|name_file
argument_list|,
name|ext_file
argument_list|)
decl_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|gimp_file_get_utf8_name
argument_list|(
name|tmp_file
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tmp_file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|ext_file
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|gimp_file_get_utf8_name
argument_list|(
name|name_file
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|g_file_query_file_type
argument_list|(
name|dir_file
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|)
operator|==
name|G_FILE_TYPE_DIRECTORY
condition|)
block|{
name|gtk_file_chooser_set_current_folder_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|dir_file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GFile
modifier|*
name|parent_file
init|=
name|g_file_get_parent
argument_list|(
name|dir_file
argument_list|)
decl_stmt|;
name|gtk_file_chooser_set_current_folder_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|parent_file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|parent_file
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
name|basename
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GFile
modifier|*
DECL|function|gimp_save_dialog_get_default_folder (Gimp * gimp)
name|gimp_save_dialog_get_default_folder
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
if|if
condition|(
name|gimp
operator|->
name|default_folder
condition|)
block|{
return|return
name|gimp
operator|->
name|default_folder
return|;
block|}
else|else
block|{
name|GFile
modifier|*
name|file
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"gimp-documents-folder"
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
comment|/* Make sure it ends in '/' */
name|path
operator|=
name|g_build_path
argument_list|(
name|G_DIR_SEPARATOR_S
argument_list|,
name|g_get_user_special_dir
argument_list|(
name|G_USER_DIRECTORY_DOCUMENTS
argument_list|)
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Paranoia fallback, see bug #722400 */
if|if
condition|(
operator|!
name|path
condition|)
name|path
operator|=
name|g_build_path
argument_list|(
name|G_DIR_SEPARATOR_S
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"gimp-documents-folder"
argument_list|,
name|file
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
return|return
name|file
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_add_compat_toggle (GimpSaveDialog * dialog)
name|gimp_save_dialog_add_compat_toggle
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|dialog
operator|->
name|compat_toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Save this XCF file with maximum compatibility"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_file_dialog_add_extra_widget
argument_list|(
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|dialog
operator|->
name|compat_toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|compat_toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_save_dialog_compat_toggled
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_compat_toggled (GtkToggleButton * button,GimpSaveDialog * dialog)
name|gimp_save_dialog_compat_toggled
parameter_list|(
name|GtkToggleButton
modifier|*
name|button
parameter_list|,
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|dialog
operator|->
name|compat
operator|=
name|gtk_toggle_button_get_active
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpSaveDialogState
modifier|*
DECL|function|gimp_save_dialog_get_state (GimpSaveDialog * dialog)
name|gimp_save_dialog_get_state
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpSaveDialogState
modifier|*
name|state
decl_stmt|;
name|GtkFileFilter
modifier|*
name|filter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SAVE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|state
operator|=
name|g_slice_new0
argument_list|(
name|GimpSaveDialogState
argument_list|)
expr_stmt|;
name|filter
operator|=
name|gtk_file_chooser_get_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|filter
condition|)
name|state
operator|->
name|filter_name
operator|=
name|g_strdup
argument_list|(
name|gtk_file_filter_get_name
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|state
operator|->
name|compat
operator|=
name|dialog
operator|->
name|compat
expr_stmt|;
return|return
name|state
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_set_state (GimpSaveDialog * dialog,GimpSaveDialogState * state)
name|gimp_save_dialog_set_state
parameter_list|(
name|GimpSaveDialog
modifier|*
name|dialog
parameter_list|,
name|GimpSaveDialogState
modifier|*
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SAVE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|state
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|->
name|filter_name
condition|)
block|{
name|GSList
modifier|*
name|filters
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|filters
operator|=
name|gtk_file_chooser_list_filters
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|filters
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GtkFileFilter
modifier|*
name|filter
init|=
name|GTK_FILE_FILTER
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
init|=
name|gtk_file_filter_get_name
argument_list|(
name|filter
argument_list|)
decl_stmt|;
if|if
condition|(
name|name
operator|&&
name|strcmp
argument_list|(
name|state
operator|->
name|filter_name
argument_list|,
name|name
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gtk_file_chooser_set_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_slist_free
argument_list|(
name|filters
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|->
name|compat
operator|=
name|state
operator|->
name|compat
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_save_dialog_state_destroy (GimpSaveDialogState * state)
name|gimp_save_dialog_state_destroy
parameter_list|(
name|GimpSaveDialogState
modifier|*
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|state
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|state
operator|->
name|filter_name
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpSaveDialogState
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

