begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpbrush_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * SECTION: gimpbrush  * @title: gimpbrush  * @short_description: Functions operating on a single brush.  *  * Functions operating on a single brush.  **/
end_comment

begin_comment
comment|/**  * gimp_brush_new:  * @name: The requested name of the new brush.  *  * Creates a new brush  *  * This procedure creates a new, uninitialized brush  *  * Returns: The actual new brush name.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_brush_new (const gchar * name)
name|gimp_brush_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|actual_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|actual_name
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
name|actual_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_duplicate:  * @name: The brush name.  *  * Duplicates a brush  *  * This procedure creates an identical brush by a different name  *  * Returns: The name of the brush's copy.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_brush_duplicate (const gchar * name)
name|gimp_brush_duplicate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|copy_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-duplicate"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|copy_name
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
name|copy_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_is_generated:  * @name: The brush name.  *  * Tests if brush is generated  *  * Returns TRUE if this brush is parametric, FALSE for other types  *  * Returns: TRUE if the brush is generated.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brush_is_generated (const gchar * name)
name|gimp_brush_is_generated
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|generated
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-is-generated"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|generated
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
name|generated
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_rename:  * @name: The brush name.  * @new_name: The new name of the brush.  *  * Rename a brush  *  * This procedure renames a brush  *  * Returns: The actual new name of the brush.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_brush_rename (const gchar * name,const gchar * new_name)
name|gimp_brush_rename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_name
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
name|actual_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-rename"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|new_name
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
name|actual_name
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
name|actual_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_delete:  * @name: The brush name.  *  * Deletes a brush  *  * This procedure deletes a brush  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brush_delete (const gchar * name)
name|gimp_brush_delete
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
literal|"gimp-brush-delete"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
comment|/**  * gimp_brush_is_editable:  * @name: The brush name.  *  * Tests if brush can be edited  *  * Returns TRUE if you have permission to change the brush  *  * Returns: TRUE if the brush can be edited.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brush_is_editable (const gchar * name)
name|gimp_brush_is_editable
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|editable
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-is-editable"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|editable
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
name|editable
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_get_info:  * @name: The brush name.  * @width: The brush width.  * @height: The brush height.  * @mask_bpp: The brush mask bpp.  * @color_bpp: The brush color bpp.  *  * Retrieve information about the specified brush.  *  * This procedure retrieves information about the specified brush. This  * includes the brush name, and the brush extents (width and height).  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brush_get_info (const gchar * name,gint * width,gint * height,gint * mask_bpp,gint * color_bpp)
name|gimp_brush_get_info
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|mask_bpp
parameter_list|,
name|gint
modifier|*
name|color_bpp
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
literal|"gimp-brush-get-info"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
literal|0
expr_stmt|;
operator|*
name|height
operator|=
literal|0
expr_stmt|;
operator|*
name|mask_bpp
operator|=
literal|0
expr_stmt|;
operator|*
name|color_bpp
operator|=
literal|0
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
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|width
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
operator|*
name|height
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|mask_bpp
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|color_bpp
operator|=
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
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
comment|/**  * gimp_brush_get_pixels:  * @name: The brush name.  * @width: The brush width.  * @height: The brush height.  * @mask_bpp: The brush mask bpp.  * @num_mask_bytes: Length of brush mask data.  * @mask_bytes: The brush mask data.  * @color_bpp: The brush color bpp.  * @num_color_bytes: Length of brush color data.  * @color_bytes: The brush color data.  *  * Retrieve information about the specified brush.  *  * This procedure retrieves information about the specified brush. This  * includes the brush extents (width and height) and its pixels data.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brush_get_pixels (const gchar * name,gint * width,gint * height,gint * mask_bpp,gint * num_mask_bytes,guint8 ** mask_bytes,gint * color_bpp,gint * num_color_bytes,guint8 ** color_bytes)
name|gimp_brush_get_pixels
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|mask_bpp
parameter_list|,
name|gint
modifier|*
name|num_mask_bytes
parameter_list|,
name|guint8
modifier|*
modifier|*
name|mask_bytes
parameter_list|,
name|gint
modifier|*
name|color_bpp
parameter_list|,
name|gint
modifier|*
name|num_color_bytes
parameter_list|,
name|guint8
modifier|*
modifier|*
name|color_bytes
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
literal|"gimp-brush-get-pixels"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
literal|0
expr_stmt|;
operator|*
name|height
operator|=
literal|0
expr_stmt|;
operator|*
name|mask_bpp
operator|=
literal|0
expr_stmt|;
operator|*
name|num_mask_bytes
operator|=
literal|0
expr_stmt|;
operator|*
name|mask_bytes
operator|=
name|NULL
expr_stmt|;
operator|*
name|color_bpp
operator|=
literal|0
expr_stmt|;
operator|*
name|num_color_bytes
operator|=
literal|0
expr_stmt|;
operator|*
name|color_bytes
operator|=
name|NULL
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
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|width
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
operator|*
name|height
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|mask_bpp
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|num_mask_bytes
operator|=
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|mask_bytes
operator|=
name|g_new
argument_list|(
name|guint8
argument_list|,
operator|*
name|num_mask_bytes
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|mask_bytes
argument_list|,
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
operator|*
name|num_mask_bytes
operator|*
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|color_bpp
operator|=
name|return_vals
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|num_color_bytes
operator|=
name|return_vals
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|color_bytes
operator|=
name|g_new
argument_list|(
name|guint8
argument_list|,
operator|*
name|num_color_bytes
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|color_bytes
argument_list|,
name|return_vals
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
operator|*
name|num_color_bytes
operator|*
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
comment|/**  * gimp_brush_get_spacing:  * @name: The brush name.  * @spacing: The brush spacing.  *  * Get the brush spacing.  *  * This procedure returns the spacing setting for the specified brush.  * The return value is an integer between 0 and 1000 which represents  * percentage of the maximum of the width and height of the mask.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brush_get_spacing (const gchar * name,gint * spacing)
name|gimp_brush_get_spacing
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|spacing
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
literal|"gimp-brush-get-spacing"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|spacing
operator|=
literal|0
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
if|if
condition|(
name|success
condition|)
operator|*
name|spacing
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
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_set_spacing:  * @name: The brush name.  * @spacing: The brush spacing.  *  * Set the brush spacing.  *  * This procedure modifies the spacing setting for the specified brush.  * The value should be a integer between 0 and 1000.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brush_set_spacing (const gchar * name,gint spacing)
name|gimp_brush_set_spacing
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|spacing
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
literal|"gimp-brush-set-spacing"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|spacing
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
comment|/**  * gimp_brush_get_shape:  * @name: The brush name.  *  * Get the shape of a generated brush.  *  * This procedure gets the shape value for a generated brush. If called  * for any other type of brush, it does not succeed. The current  * possibilities are Circle (GIMP_BRUSH_GENERATED_CIRCLE), Square  * (GIMP_BRUSH_GENERATED_SQUARE), and Diamond  * (GIMP_BRUSH_GENERATED_DIAMOND). Other shapes are likely to be added  * in the future.  *  * Returns: The brush shape.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GimpBrushGeneratedShape
DECL|function|gimp_brush_get_shape (const gchar * name)
name|gimp_brush_get_shape
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|GimpBrushGeneratedShape
name|shape
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-get-shape"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|shape
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
name|shape
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_set_shape:  * @name: The brush name.  * @shape_in: The brush shape.  *  * Set the shape of a generated brush.  *  * This procedure sets the shape value for a generated brush. If called  * for any other type of brush, it does not succeed. The current  * possibilities are Circle (GIMP_BRUSH_GENERATED_CIRCLE), Square  * (GIMP_BRUSH_GENERATED_SQUARE), and Diamond  * (GIMP_BRUSH_GENERATED_DIAMOND). Other shapes are likely to be added  * in the future.  *  * Returns: The brush shape actually assigned.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GimpBrushGeneratedShape
DECL|function|gimp_brush_set_shape (const gchar * name,GimpBrushGeneratedShape shape_in)
name|gimp_brush_set_shape
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpBrushGeneratedShape
name|shape_in
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|GimpBrushGeneratedShape
name|shape_out
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-set-shape"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|shape_in
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
name|shape_out
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
name|shape_out
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_get_radius:  * @name: The brush name.  *  * Get the radius of a generated brush.  *  * This procedure gets the radius value for a generated brush. If  * called for any other type of brush, it does not succeed.  *  * Returns: The radius of the brush in pixels.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_get_radius (const gchar * name)
name|gimp_brush_get_radius
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|radius
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-get-radius"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|radius
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|radius
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_set_radius:  * @name: The brush name.  * @radius_in: The desired brush radius.  *  * Set the radius of a generated brush.  *  * This procedure sets the radius for a generated brush. If called for  * any other type of brush, it does not succeed.  *  * Returns: The brush radius actually assigned.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_set_radius (const gchar * name,gdouble radius_in)
name|gimp_brush_set_radius
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|radius_in
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|radius_out
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-set-radius"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|radius_in
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
name|radius_out
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|radius_out
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_get_spikes:  * @name: The brush name.  *  * Get the number of spikes for a generated brush.  *  * This procedure gets the number of spikes for a generated brush. If  * called for any other type of brush, it does not succeed.  *  * Returns: The number of spikes on the brush.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_brush_get_spikes (const gchar * name)
name|gimp_brush_get_spikes
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|spikes
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-get-spikes"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|spikes
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
name|spikes
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_set_spikes:  * @name: The brush name.  * @spikes_in: The desired number of spikes.  *  * Set the number of spikes for a generated brush.  *  * This procedure sets the number of spikes for a generated brush. If  * called for any other type of brush, it does not succeed.  *  * Returns: The number of spikes actually assigned.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gint
DECL|function|gimp_brush_set_spikes (const gchar * name,gint spikes_in)
name|gimp_brush_set_spikes
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|spikes_in
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|spikes_out
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-set-spikes"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|spikes_in
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
name|spikes_out
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
name|spikes_out
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_get_hardness:  * @name: The brush name.  *  * Get the hardness of a generated brush.  *  * This procedure gets the hardness of a generated brush. The hardness  * of a brush is the amount its intensity fades at the outside edge. If  * called for any other type of brush, the function does not succeed.  *  * Returns: The hardness of the brush.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_get_hardness (const gchar * name)
name|gimp_brush_get_hardness
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|hardness
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-get-hardness"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|hardness
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|hardness
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_set_hardness:  * @name: The brush name.  * @hardness_in: The desired brush hardness.  *  * Set the hardness of a generated brush.  *  * This procedure sets the hardness for a generated brush. If called  * for any other type of brush, it does not succeed.  *  * Returns: The brush hardness actually assigned.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_set_hardness (const gchar * name,gdouble hardness_in)
name|gimp_brush_set_hardness
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|hardness_in
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|hardness_out
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-set-hardness"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|hardness_in
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
name|hardness_out
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|hardness_out
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_get_aspect_ratio:  * @name: The brush name.  *  * Get the aspect ratio of a generated brush.  *  * This procedure gets the aspect ratio of a generated brush. If called  * for any other type of brush, it does not succeed.  *  * Returns: The aspect ratio of the brush.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_get_aspect_ratio (const gchar * name)
name|gimp_brush_get_aspect_ratio
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|aspect_ratio
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-get-aspect-ratio"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|aspect_ratio
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|aspect_ratio
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_set_aspect_ratio:  * @name: The brush name.  * @aspect_ratio_in: The desired brush aspect ratio.  *  * Set the aspect ratio of a generated brush.  *  * This procedure sets the aspect ratio for a generated brush. If  * called for any other type of brush, it does not succeed.  *  * Returns: The brush aspect ratio actually assigned.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_set_aspect_ratio (const gchar * name,gdouble aspect_ratio_in)
name|gimp_brush_set_aspect_ratio
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|aspect_ratio_in
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|aspect_ratio_out
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-set-aspect-ratio"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|aspect_ratio_in
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
name|aspect_ratio_out
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|aspect_ratio_out
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_get_angle:  * @name: The brush name.  *  * Get the rotation angle of a generated brush.  *  * This procedure gets the angle of rotation for a generated brush. If  * called for any other type of brush, it does not succeed.  *  * Returns: The rotation angle of the brush.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_get_angle (const gchar * name)
name|gimp_brush_get_angle
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|angle
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-get-angle"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|angle
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|angle
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brush_set_angle:  * @name: The brush name.  * @angle_in: The desired brush rotation angle.  *  * Set the rotation angle of a generated brush.  *  * This procedure sets the rotation angle for a generated brush. If  * called for any other type of brush, it does not succeed.  *  * Returns: The brush rotation angle actually assigned.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_brush_set_angle (const gchar * name,gdouble angle_in)
name|gimp_brush_set_angle
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|angle_in
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|angle_out
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brush-set-angle"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|angle_in
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
name|angle_out
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|angle_out
return|;
block|}
end_function

end_unit

