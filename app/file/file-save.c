begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-save.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
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
file|"core/gimpdocumentlist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"file-remote.h"
end_include

begin_include
include|#
directive|include
file|"file-save.h"
end_include

begin_include
include|#
directive|include
file|"file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-file.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPDBStatusType
DECL|function|file_save (Gimp * gimp,GimpImage * image,GimpProgress * progress,GFile * file,GimpPlugInProcedure * file_proc,GimpRunMode run_mode,gboolean change_saved_state,gboolean export_backward,gboolean export_forward,GError ** error)
name|file_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|gboolean
name|change_saved_state
parameter_list|,
name|gboolean
name|export_backward
parameter_list|,
name|gboolean
name|export_forward
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_EXECUTION_ERROR
decl_stmt|;
name|GFile
modifier|*
name|local_file
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|path
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|uri
init|=
name|NULL
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|drawable_ID
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|file_proc
argument_list|)
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|(
name|export_backward
operator|&&
name|export_forward
operator|)
operator|==
name|FALSE
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|)
expr_stmt|;
comment|/*  ref image and file, so they can't get deleted during save  */
name|g_object_ref
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
goto|goto
name|out
goto|;
comment|/* FIXME enable these tests for remote files again, needs testing */
if|if
condition|(
name|g_file_is_native
argument_list|(
name|file
argument_list|)
operator|&&
name|g_file_query_exists
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GFileInfo
modifier|*
name|info
decl_stmt|;
name|info
operator|=
name|g_file_query_info
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_TYPE
literal|","
name|G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|info
condition|)
goto|goto
name|out
goto|;
if|if
condition|(
name|g_file_info_get_file_type
argument_list|(
name|info
argument_list|)
operator|!=
name|G_FILE_TYPE_REGULAR
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Not a regular file"
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
if|if
condition|(
operator|!
name|g_file_info_get_attribute_boolean
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Permission denied"
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
block|}
if|if
condition|(
operator|!
name|g_file_is_native
argument_list|(
name|file
argument_list|)
operator|&&
operator|!
name|file_remote_mount_file
argument_list|(
name|gimp
argument_list|,
name|file
argument_list|,
name|progress
argument_list|,
operator|&
name|my_error
argument_list|)
condition|)
block|{
if|if
condition|(
name|my_error
condition|)
name|g_propagate_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|)
expr_stmt|;
else|else
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
goto|goto
name|out
goto|;
block|}
if|if
condition|(
operator|!
name|file_proc
operator|->
name|handles_uri
condition|)
block|{
name|path
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|path
condition|)
block|{
name|local_file
operator|=
name|file_remote_upload_image_prepare
argument_list|(
name|gimp
argument_list|,
name|file
argument_list|,
name|progress
argument_list|,
operator|&
name|my_error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|local_file
condition|)
block|{
if|if
condition|(
name|my_error
condition|)
name|g_propagate_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|)
expr_stmt|;
else|else
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|path
operator|=
name|g_file_get_path
argument_list|(
name|local_file
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|path
condition|)
name|path
operator|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|gimp_image_get_ID
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|drawable_ID
operator|=
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|pdb
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|progress
argument_list|,
name|error
argument_list|,
name|gimp_object_get_name
argument_list|(
name|file_proc
argument_list|)
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|run_mode
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|drawable_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|path
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|uri
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|status
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
if|if
condition|(
name|local_file
condition|)
block|{
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|file_remote_upload_image_finish
argument_list|(
name|gimp
argument_list|,
name|file
argument_list|,
name|local_file
argument_list|,
name|progress
argument_list|,
operator|&
name|my_error
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|my_error
condition|)
name|g_propagate_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|)
expr_stmt|;
else|else
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
block|}
name|g_file_delete
argument_list|(
name|local_file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|local_file
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|GimpDocumentList
modifier|*
name|documents
decl_stmt|;
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
if|if
condition|(
name|change_saved_state
condition|)
block|{
name|gimp_image_set_file
argument_list|(
name|image
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|gimp_image_set_save_proc
argument_list|(
name|image
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
comment|/* Forget the import source when we save. We interpret a            * save as that the user is not interested in being able            * to quickly export back to the original any longer            */
name|gimp_image_set_imported_file
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_clean_all
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|export_backward
condition|)
block|{
comment|/* We exported the image back to its imported source,            * change nothing about export/import flags, only set            * the export state to clean            */
name|gimp_image_export_clean_all
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_object_name_changed
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|export_forward
condition|)
block|{
comment|/* Remember the last entered Export URI for the image. We            * only need to do this explicitly when exporting. It            * happens implicitly when saving since the GimpObject name            * of a GimpImage is the last-save URI            */
name|gimp_image_set_exported_file
argument_list|(
name|image
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|gimp_image_set_export_proc
argument_list|(
name|image
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
comment|/* An image can not be considered both exported and imported            * at the same time, so stop consider it as imported now            * that we consider it exported.            */
name|gimp_image_set_imported_file
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_export_clean_all
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|export_backward
operator|||
name|export_forward
condition|)
name|gimp_image_exported
argument_list|(
name|image
argument_list|,
name|file
argument_list|)
expr_stmt|;
else|else
name|gimp_image_saved
argument_list|(
name|image
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|documents
operator|=
name|GIMP_DOCUMENT_LIST
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|documents
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_document_list_add_file
argument_list|(
name|documents
argument_list|,
name|file
argument_list|,
name|file_proc
operator|->
name|mime_type
argument_list|)
expr_stmt|;
comment|/* only save a thumbnail if we are saving as XCF, see bug #25272 */
if|if
condition|(
name|GIMP_PROCEDURE
argument_list|(
name|file_proc
argument_list|)
operator|->
name|proc_type
operator|==
name|GIMP_INTERNAL
condition|)
name|gimp_imagefile_save_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|file_proc
operator|->
name|mime_type
argument_list|,
name|image
argument_list|,
name|NULL
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
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"%s plug-in could not save image"
argument_list|)
argument_list|,
name|gimp_plug_in_procedure_get_label
argument_list|(
name|file_proc
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|out
label|:
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
return|return
name|status
return|;
block|}
end_function

end_unit

