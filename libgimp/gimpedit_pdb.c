begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpedit_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * SECTION: gimpedit  * @title: gimpedit  * @short_description: Edit menu functions (cut, copy, paste, clear, etc.)  *  * Edit menu functions (cut, copy, paste, clear, etc.)  **/
end_comment

begin_comment
comment|/**  * gimp_edit_cut:  * @drawable_ID: The drawable to cut from.  *  * Cut from the specified drawable.  *  * If there is a selection in the image, then the area specified by the  * selection is cut from the specified drawable and placed in an  * internal GIMP edit buffer. It can subsequently be retrieved using  * the gimp_edit_paste() command. If there is no selection, then the  * specified drawable will be removed and its contents stored in the  * internal GIMP edit buffer. This procedure will fail if the selected  * area lies completely outside the bounds of the current drawable and  * there is nothing to copy from.  *  * Returns: TRUE if the cut was successful, FALSE if there was nothing  * to copy from.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_cut (gint32 drawable_ID)
name|gimp_edit_cut
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|non_empty
init|=
name|FALSE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-cut"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|non_empty
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|non_empty
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_copy:  * @drawable_ID: The drawable to copy from.  *  * Copy from the specified drawable.  *  * If there is a selection in the image, then the area specified by the  * selection is copied from the specified drawable and placed in an  * internal GIMP edit buffer. It can subsequently be retrieved using  * the gimp_edit_paste() command. If there is no selection, then the  * specified drawable's contents will be stored in the internal GIMP  * edit buffer. This procedure will fail if the selected area lies  * completely outside the bounds of the current drawable and there is  * nothing to copy from.  *  * Returns: TRUE if the cut was successful, FALSE if there was nothing  * to copy from.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_copy (gint32 drawable_ID)
name|gimp_edit_copy
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|non_empty
init|=
name|FALSE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-copy"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|non_empty
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|non_empty
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_copy_visible:  * @image_ID: The image to copy from.  *  * Copy from the projection.  *  * If there is a selection in the image, then the area specified by the  * selection is copied from the projection and placed in an internal  * GIMP edit buffer. It can subsequently be retrieved using the  * gimp_edit_paste() command. If there is no selection, then the  * projection's contents will be stored in the internal GIMP edit  * buffer.  *  * Returns: TRUE if the copy was successful.  *  * Since: 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_copy_visible (gint32 image_ID)
name|gimp_edit_copy_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|non_empty
init|=
name|FALSE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-copy-visible"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|non_empty
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|non_empty
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_paste:  * @drawable_ID: The drawable to paste to.  * @paste_into: Clear selection, or paste behind it?  *  * Paste buffer to the specified drawable.  *  * This procedure pastes a copy of the internal GIMP edit buffer to the  * specified drawable. The GIMP edit buffer will be empty unless a call  * was previously made to either gimp_edit_cut() or gimp_edit_copy().  * The \"paste_into\" option specifies whether to clear the current  * image selection, or to paste the buffer \"behind\" the selection.  * This allows the selection to act as a mask for the pasted buffer.  * Anywhere that the selection mask is non-zero, the pasted buffer will  * show through. The pasted buffer will be a new layer in the image  * which is designated as the image floating selection. If the image  * has a floating selection at the time of pasting, the old floating  * selection will be anchored to its drawable before the new floating  * selection is added. This procedure returns the new floating layer.  * The resulting floating selection will already be attached to the  * specified drawable, and a subsequent call to floating_sel_attach is  * not needed.  *  * Returns: The new floating selection.  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_paste (gint32 drawable_ID,gboolean paste_into)
name|gimp_edit_paste
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|floating_sel_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|paste_into
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-paste"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|floating_sel_ID
operator|=
name|gimp_value_get_layer_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|floating_sel_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_paste_as_new_image:  *  * Paste buffer to a new image.  *  * This procedure pastes a copy of the internal GIMP edit buffer to a  * new image. The GIMP edit buffer will be empty unless a call was  * previously made to either gimp_edit_cut() or gimp_edit_copy(). This  * procedure returns the new image or -1 if the edit buffer was empty.  *  * Returns: The new image.  *  * Since: 2.10  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_paste_as_new_image (void)
name|gimp_edit_paste_as_new_image
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-paste-as-new-image"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|image_ID
operator|=
name|gimp_value_get_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_cut:  * @drawable_ID: The drawable to cut from.  * @buffer_name: The name of the buffer to create.  *  * Cut into a named buffer.  *  * This procedure works like gimp_edit_cut(), but additionally stores  * the cut buffer into a named buffer that will stay available for  * later pasting, regardless of any intermediate copy or cut  * operations.  *  * Returns: (transfer full) The real name given to the buffer, or NULL  * if the cut failed.  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_edit_named_cut (gint32 drawable_ID,const gchar * buffer_name)
name|gimp_edit_named_cut
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|real_name
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|buffer_name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-named-cut"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|real_name
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|real_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_copy:  * @drawable_ID: The drawable to copy from.  * @buffer_name: The name of the buffer to create.  *  * Copy into a named buffer.  *  * This procedure works like gimp_edit_copy(), but additionally stores  * the copied buffer into a named buffer that will stay available for  * later pasting, regardless of any intermediate copy or cut  * operations.  *  * Returns: (transfer full) The real name given to the buffer, or NULL  * if the copy failed.  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_edit_named_copy (gint32 drawable_ID,const gchar * buffer_name)
name|gimp_edit_named_copy
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|real_name
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|buffer_name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-named-copy"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|real_name
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|real_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_copy_visible:  * @image_ID: The image to copy from.  * @buffer_name: The name of the buffer to create.  *  * Copy from the projection into a named buffer.  *  * This procedure works like gimp_edit_copy_visible(), but additionally  * stores the copied buffer into a named buffer that will stay  * available for later pasting, regardless of any intermediate copy or  * cut operations.  *  * Returns: (transfer full) The real name given to the buffer, or NULL  * if the copy failed.  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_edit_named_copy_visible (gint32 image_ID,const gchar * buffer_name)
name|gimp_edit_named_copy_visible
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|real_name
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|buffer_name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-named-copy-visible"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|real_name
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|real_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_paste:  * @drawable_ID: The drawable to paste to.  * @buffer_name: The name of the buffer to paste.  * @paste_into: Clear selection, or paste behind it?  *  * Paste named buffer to the specified drawable.  *  * This procedure works like gimp_edit_paste() but pastes a named  * buffer instead of the global buffer.  *  * Returns: The new floating selection.  *  * Since: 2.4  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_named_paste (gint32 drawable_ID,const gchar * buffer_name,gboolean paste_into)
name|gimp_edit_named_paste
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|,
name|gboolean
name|paste_into
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|floating_sel_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|buffer_name
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|paste_into
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-named-paste"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|floating_sel_ID
operator|=
name|gimp_value_get_layer_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|floating_sel_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_paste_as_new_image:  * @buffer_name: The name of the buffer to paste.  *  * Paste named buffer to a new image.  *  * This procedure works like gimp_edit_paste_as_new_image() but pastes  * a named buffer instead of the global buffer.  *  * Returns: The new image.  *  * Since: 2.10  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_named_paste_as_new_image (const gchar * buffer_name)
name|gimp_edit_named_paste_as_new_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|buffer_name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-edit-named-paste-as-new-image"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|image_ID
operator|=
name|gimp_value_get_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

end_unit

