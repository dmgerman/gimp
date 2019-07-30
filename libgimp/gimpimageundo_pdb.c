begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpimageundo_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpimageundo  * @title: gimpimageundo  * @short_description: Control of image undo/redo.  *  * Control of image undo/redo.  **/
end_comment

begin_comment
comment|/**  * gimp_image_undo_group_start:  * @image_ID: The ID of the image in which to open an undo group.  *  * Starts a group undo.  *  * This function is used to start a group undo--necessary for logically  * combining two or more undo operations into a single operation. This  * call must be used in conjunction with a gimp_image_undo_group_end()  * call.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo_group_start (gint32 image_ID)
name|gimp_image_undo_group_start
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
name|success
init|=
name|TRUE
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
literal|"gimp-image-undo-group-start"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
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
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_undo_group_end:  * @image_ID: The ID of the image in which to close an undo group.  *  * Finish a group undo.  *  * This function must be called once for each  * gimp_image_undo_group_start() call that is made.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo_group_end (gint32 image_ID)
name|gimp_image_undo_group_end
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
name|success
init|=
name|TRUE
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
literal|"gimp-image-undo-group-end"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
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
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_undo_is_enabled:  * @image_ID: The image.  *  * Check if the image's undo stack is enabled.  *  * This procedure checks if the image's undo stack is currently enabled  * or disabled. This is useful when several plug-ins or scripts call  * each other and want to check if their caller has already used  * gimp_image_undo_disable() or gimp_image_undo_freeze().  *  * Returns: TRUE if undo is enabled for this image.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo_is_enabled (gint32 image_ID)
name|gimp_image_undo_is_enabled
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
name|enabled
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
literal|"gimp-image-undo-is-enabled"
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
name|enabled
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
name|enabled
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_undo_disable:  * @image_ID: The image.  *  * Disable the image's undo stack.  *  * This procedure disables the image's undo stack, allowing subsequent  * operations to ignore their undo steps. This is generally called in  * conjunction with gimp_image_undo_enable() to temporarily disable an  * image undo stack. This is advantageous because saving undo steps can  * be time and memory intensive.  *  * Returns: TRUE if the image undo has been disabled.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo_disable (gint32 image_ID)
name|gimp_image_undo_disable
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
name|disabled
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
literal|"gimp-image-undo-disable"
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
name|disabled
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
name|disabled
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_undo_enable:  * @image_ID: The image.  *  * Enable the image's undo stack.  *  * This procedure enables the image's undo stack, allowing subsequent  * operations to store their undo steps. This is generally called in  * conjunction with gimp_image_undo_disable() to temporarily disable an  * image undo stack.  *  * Returns: TRUE if the image undo has been enabled.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo_enable (gint32 image_ID)
name|gimp_image_undo_enable
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
name|enabled
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
literal|"gimp-image-undo-enable"
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
name|enabled
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
name|enabled
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_undo_freeze:  * @image_ID: The image.  *  * Freeze the image's undo stack.  *  * This procedure freezes the image's undo stack, allowing subsequent  * operations to ignore their undo steps. This is generally called in  * conjunction with gimp_image_undo_thaw() to temporarily disable an  * image undo stack. This is advantageous because saving undo steps can  * be time and memory intensive. gimp_image_undo_freeze() /  * gimp_image_undo_thaw() and gimp_image_undo_disable() /  * gimp_image_undo_enable() differ in that the former does not free up  * all undo steps when undo is thawed, so is more suited to interactive  * in-situ previews. It is important in this case that the image is  * back to the same state it was frozen in before thawing, else 'undo'  * behaviour is undefined.  *  * Returns: TRUE if the image undo has been frozen.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo_freeze (gint32 image_ID)
name|gimp_image_undo_freeze
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
name|frozen
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
literal|"gimp-image-undo-freeze"
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
name|frozen
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
name|frozen
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_undo_thaw:  * @image_ID: The image.  *  * Thaw the image's undo stack.  *  * This procedure thaws the image's undo stack, allowing subsequent  * operations to store their undo steps. This is generally called in  * conjunction with gimp_image_undo_freeze() to temporarily freeze an  * image undo stack. gimp_image_undo_thaw() does NOT free the undo  * stack as gimp_image_undo_enable() does, so is suited for situations  * where one wishes to leave the undo stack in the same state in which  * one found it despite non-destructively playing with the image in the  * meantime. An example would be in-situ plug-in previews. Balancing  * freezes and thaws and ensuring image consistency is the  * responsibility of the caller.  *  * Returns: TRUE if the image undo has been thawed.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_undo_thaw (gint32 image_ID)
name|gimp_image_undo_thaw
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
name|thawed
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
literal|"gimp-image-undo-thaw"
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
name|thawed
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
name|thawed
return|;
block|}
end_function

end_unit

