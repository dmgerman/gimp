begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpexportdialog.c  * Copyright (C) 2015 Jehan<jehan@girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpexportdialog.h"
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
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GFile
modifier|*
name|gimp_export_dialog_get_default_folder
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpExportDialog,gimp_export_dialog,GIMP_TYPE_FILE_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpExportDialog
argument_list|,
argument|gimp_export_dialog
argument_list|,
argument|GIMP_TYPE_FILE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_export_dialog_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_export_dialog_class_init
parameter_list|(
name|GimpExportDialogClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_export_dialog_init (GimpExportDialog * dialog)
name|gimp_export_dialog_init
parameter_list|(
name|GimpExportDialog
modifier|*
name|dialog
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_export_dialog_new (Gimp * gimp)
name|gimp_export_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpExportDialog
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
name|GIMP_TYPE_EXPORT_DIALOG
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"title"
argument_list|,
name|_
argument_list|(
literal|"Export Image"
argument_list|)
argument_list|,
literal|"role"
argument_list|,
literal|"gimp-file-export"
argument_list|,
literal|"help-id"
argument_list|,
name|GIMP_HELP_FILE_EXPORT_AS
argument_list|,
literal|"stock-id"
argument_list|,
name|_
argument_list|(
literal|"_Export"
argument_list|)
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
name|export_procs
argument_list|,
literal|"file-procs-all-images"
argument_list|,
name|gimp
operator|->
name|plug_in_manager
operator|->
name|save_procs
argument_list|,
literal|"file-filter-label"
argument_list|,
name|_
argument_list|(
literal|"All export images"
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
DECL|function|gimp_export_dialog_set_image (GimpExportDialog * dialog,Gimp * gimp,GimpImage * image)
name|gimp_export_dialog_set_image
parameter_list|(
name|GimpExportDialog
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_EXPORT_DIALOG
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
comment|/*    * Priority of default paths for Export:    *    *   1. Last Export path    *   2. Path of import source    *   3. Path of XCF source    *   4. Last path of any save to XCF    *   5. Last Export path of any document    *   6. The default path (usually the OS 'Documents' path)    */
name|dir_file
operator|=
name|gimp_image_get_exported_file
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
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_FILE_EXPORT_LAST_FILE_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir_file
condition|)
name|dir_file
operator|=
name|gimp_export_dialog_get_default_folder
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/* Priority of default basenames for Export:    *    *   1. Last Export name    *   3. Save URI    *   2. Source file name    *   3. 'Untitled'    */
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
comment|/* Priority of default type/extension for Export:    *    *   1. Type of last Export    *   2. Type of the image Import    *   3. Type of latest Export of any document    *   4. .png    */
name|ext_file
operator|=
name|gimp_image_get_exported_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ext_file
condition|)
name|ext_file
operator|=
name|gimp_image_get_imported_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ext_file
condition|)
name|ext_file
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_FILE_EXPORT_LAST_FILE_KEY
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
literal|"file:///we/only/care/about/extension.png"
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
DECL|function|gimp_export_dialog_get_default_folder (Gimp * gimp)
name|gimp_export_dialog_get_default_folder
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

end_unit

