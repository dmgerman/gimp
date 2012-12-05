begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpedit_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|non_empty
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-cut"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|non_empty
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|non_empty
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-copy"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|non_empty
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|non_empty
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_copy_visible:  * @image_ID: The image to copy from.  *  * Copy from the projection.  *  * If there is a selection in the image, then the area specified by the  * selection is copied from the projection and placed in an internal  * GIMP edit buffer. It can subsequently be retrieved using the  * gimp_edit_paste() command. If there is no selection, then the  * projection's contents will be stored in the internal GIMP edit  * buffer.  *  * Returns: TRUE if the copy was successful.  *  * Since: GIMP 2.2  **/
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|non_empty
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-copy-visible"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|non_empty
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|non_empty
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_paste:  * @drawable_ID: The drawable to paste to.  * @paste_into: Clear selection, or paste behind it?  *  * Paste buffer to the specified drawable.  *  * This procedure pastes a copy of the internal GIMP edit buffer to the  * specified drawable. The GIMP edit buffer will be empty unless a call  * was previously made to either gimp_edit_cut() or gimp_edit_copy().  * The \"paste_into\" option specifies whether to clear the current  * image selection, or to paste the buffer \"behind\" the selection.  * This allows the selection to act as a mask for the pasted buffer.  * Anywhere that the selection mask is non-zero, the pasted buffer will  * show through. The pasted buffer will be a new layer in the image  * which is designated as the image floating selection. If the image  * has a floating selection at the time of pasting, the old floating  * selection will be anchored to it's drawable before the new floating  * selection is added. This procedure returns the new floating layer.  * The resulting floating selection will already be attached to the  * specified drawable, and a subsequent call to floating_sel_attach is  * not needed.  *  * Returns: The new floating selection.  **/
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|floating_sel_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-paste"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paste_into
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|floating_sel_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_layer
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|floating_sel_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_paste_as_new:  *  * Paste buffer to a new image.  *  * This procedure pastes a copy of the internal GIMP edit buffer to a  * new image. The GIMP edit buffer will be empty unless a call was  * previously made to either gimp_edit_cut() or gimp_edit_copy(). This  * procedure returns the new image or -1 if the edit buffer was empty.  *  * Returns: The new image.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_paste_as_new (void)
name|gimp_edit_paste_as_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-paste-as-new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|image_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_cut:  * @drawable_ID: The drawable to cut from.  * @buffer_name: The name of the buffer to create.  *  * Cut into a named buffer.  *  * This procedure works like gimp_edit_cut(), but additionally stores  * the cut buffer into a named buffer that will stay available for  * later pasting, regardless of any intermediate copy or cut  * operations.  *  * Returns: The real name given to the buffer, or NULL if the cut  * failed.  *  * Since: GIMP 2.4  **/
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|real_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-named-cut"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|real_name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|real_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_copy:  * @drawable_ID: The drawable to copy from.  * @buffer_name: The name of the buffer to create.  *  * Copy into a named buffer.  *  * This procedure works like gimp_edit_copy(), but additionally stores  * the copied buffer into a named buffer that will stay available for  * later pasting, regardless of any intermediate copy or cut  * operations.  *  * Returns: The real name given to the buffer, or NULL if the copy  * failed.  *  * Since: GIMP 2.4  **/
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|real_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-named-copy"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|real_name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|real_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_copy_visible:  * @image_ID: The image to copy from.  * @buffer_name: The name of the buffer to create.  *  * Copy from the projection into a named buffer.  *  * This procedure works like gimp_edit_copy_visible(), but additionally  * stores the copied buffer into a named buffer that will stay  * available for later pasting, regardless of any intermediate copy or  * cut operations.  *  * Returns: The real name given to the buffer, or NULL if the copy  * failed.  *  * Since: GIMP 2.4  **/
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|real_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-named-copy-visible"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|real_name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|real_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_paste:  * @drawable_ID: The drawable to paste to.  * @buffer_name: The name of the buffer to paste.  * @paste_into: Clear selection, or paste behind it?  *  * Paste named buffer to the specified drawable.  *  * This procedure works like gimp_edit_paste() but pastes a named  * buffer instead of the global buffer.  *  * Returns: The new floating selection.  *  * Since: GIMP 2.4  **/
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
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|floating_sel_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-named-paste"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paste_into
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|floating_sel_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_layer
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|floating_sel_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_paste_as_new:  * @buffer_name: The name of the buffer to paste.  *  * Paste named buffer to a new image.  *  * This procedure works like gimp_edit_paste_as_new() but pastes a  * named buffer instead of the global buffer.  *  * Returns: The new image.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_named_paste_as_new (const gchar * buffer_name)
name|gimp_edit_named_paste_as_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-named-paste-as-new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|buffer_name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|image_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_clear:  * @drawable_ID: The drawable to clear from.  *  * Clear selected area of drawable.  *  * This procedure clears the specified drawable. If the drawable has an  * alpha channel, the cleared pixels will become transparent. If the  * drawable does not have an alpha channel, cleared pixels will be set  * to the background color. This procedure only affects regions within  * a selection if there is a selection active.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_clear (gint32 drawable_ID)
name|gimp_edit_clear
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-clear"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_fill:  * @drawable_ID: The drawable to fill to.  * @fill_type: The type of fill.  *  * Fill selected area of drawable.  *  * This procedure fills the specified drawable with the fill mode. If  * the fill mode is foreground, the current foreground color is used.  * If the fill mode is background, the current background color is  * used. Other fill modes should not be used. This procedure only  * affects regions within a selection if there is a selection active.  * If you want to fill the whole drawable, regardless of the selection,  * use gimp_drawable_fill().  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_fill (gint32 drawable_ID,GimpFillType fill_type)
name|gimp_edit_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-fill"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|fill_type
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_bucket_fill:  * @drawable_ID: The affected drawable.  * @fill_mode: The type of fill.  * @paint_mode: The paint application mode.  * @opacity: The opacity of the final bucket fill.  * @threshold: The threshold determines how extensive the seed fill will be. It's value is specified in terms of intensity levels. This parameter is only valid when there is no selection in the specified image.  * @sample_merged: Use the composite image, not the drawable.  * @x: The x coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image.  * @y: The y coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image.  *  * Fill the area specified either by the current selection if there is  * one, or by a seed fill starting at the specified coordinates.  *  * This tool requires information on the paint application mode, and  * the fill mode, which can either be in the foreground color, or in  * the currently active pattern. If there is no selection, a seed fill  * is executed at the specified coordinates and extends outward in  * keeping with the threshold parameter. If there is a selection in the  * target image, the threshold, sample merged, x, and y arguments are  * unused. If the sample_merged parameter is TRUE, the data of the  * composite image will be used instead of that for the specified  * drawable. This is equivalent to sampling for colors after merging  * all visible layers. In the case of merged sampling, the x and y  * coordinates are relative to the image's origin; otherwise, they are  * relative to the drawable's origin.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_bucket_fill (gint32 drawable_ID,GimpBucketFillMode fill_mode,GimpLayerModeEffects paint_mode,gdouble opacity,gdouble threshold,gboolean sample_merged,gdouble x,gdouble y)
name|gimp_edit_bucket_fill
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-bucket-fill"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|fill_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|threshold
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|sample_merged
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_bucket_fill_full:  * @drawable_ID: The affected drawable.  * @fill_mode: The type of fill.  * @paint_mode: The paint application mode.  * @opacity: The opacity of the final bucket fill.  * @threshold: The threshold determines how extensive the seed fill will be. It's value is specified in terms of intensity levels. This parameter is only valid when there is no selection in the specified image.  * @sample_merged: Use the composite image, not the drawable.  * @fill_transparent: Whether to consider transparent pixels for filling. If TRUE, transparency is considered as a unique fillable color.  * @select_criterion: The criterion used to determine color similarity. SELECT_CRITERION_COMPOSITE is the standard choice.  * @x: The x coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image.  * @y: The y coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image.  *  * Fill the area specified either by the current selection if there is  * one, or by a seed fill starting at the specified coordinates.  *  * This tool requires information on the paint application mode, and  * the fill mode, which can either be in the foreground color, or in  * the currently active pattern. If there is no selection, a seed fill  * is executed at the specified coordinates and extends outward in  * keeping with the threshold parameter. If there is a selection in the  * target image, the threshold, sample merged, x, and y arguments are  * unused. If the sample_merged parameter is TRUE, the data of the  * composite image will be used instead of that for the specified  * drawable. This is equivalent to sampling for colors after merging  * all visible layers. In the case of merged sampling, the x and y  * coordinates are relative to the image's origin; otherwise, they are  * relative to the drawable's origin.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_bucket_fill_full (gint32 drawable_ID,GimpBucketFillMode fill_mode,GimpLayerModeEffects paint_mode,gdouble opacity,gdouble threshold,gboolean sample_merged,gboolean fill_transparent,GimpSelectCriterion select_criterion,gdouble x,gdouble y)
name|gimp_edit_bucket_fill_full
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|fill_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-bucket-fill-full"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|fill_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|threshold
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|sample_merged
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|fill_transparent
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|select_criterion
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_blend:  * @drawable_ID: The affected drawable.  * @blend_mode: The type of blend.  * @paint_mode: The paint application mode.  * @gradient_type: The type of gradient.  * @opacity: The opacity of the final blend.  * @offset: Offset relates to the starting and ending coordinates specified for the blend. This parameter is mode dependent.  * @repeat: Repeat mode.  * @reverse: Use the reverse gradient.  * @supersample: Do adaptive supersampling.  * @max_depth: Maximum recursion levels for supersampling.  * @threshold: Supersampling threshold.  * @dither: Use dithering to reduce banding.  * @x1: The x coordinate of this blend's starting point.  * @y1: The y coordinate of this blend's starting point.  * @x2: The x coordinate of this blend's ending point.  * @y2: The y coordinate of this blend's ending point.  *  * Blend between the starting and ending coordinates with the specified  * blend mode and gradient type.  *  * This tool requires information on the paint application mode, the  * blend mode, and the gradient type. It creates the specified variety  * of blend using the starting and ending coordinates as defined for  * each gradient type.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_blend (gint32 drawable_ID,GimpBlendMode blend_mode,GimpLayerModeEffects paint_mode,GimpGradientType gradient_type,gdouble opacity,gdouble offset,GimpRepeatMode repeat,gboolean reverse,gboolean supersample,gint max_depth,gdouble threshold,gboolean dither,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|gimp_edit_blend
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpBlendMode
name|blend_mode
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpGradientType
name|gradient_type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|offset
parameter_list|,
name|GimpRepeatMode
name|repeat
parameter_list|,
name|gboolean
name|reverse
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|max_depth
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|dither
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-blend"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|blend_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|gradient_type
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|offset
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|repeat
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|reverse
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|max_depth
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|threshold
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|dither
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x1
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y1
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x2
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y2
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_stroke:  * @drawable_ID: The drawable to stroke to.  *  * Stroke the current selection  *  * This procedure strokes the current selection, painting along the  * selection boundary with the active brush and foreground color. The  * paint is applied to the specified drawable regardless of the active  * selection.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_stroke (gint32 drawable_ID)
name|gimp_edit_stroke
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-stroke"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_stroke_vectors:  * @drawable_ID: The drawable to stroke to.  * @vectors_ID: The vectors object.  *  * Stroke the specified vectors object  *  * This procedure strokes the specified vectors object, painting along  * the path with the active brush and foreground color.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_edit_stroke_vectors (gint32 drawable_ID,gint32 vectors_ID)
name|gimp_edit_stroke_vectors
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|vectors_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-edit-stroke-vectors"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_VECTORS
argument_list|,
name|vectors_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

