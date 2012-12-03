begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpbrushes_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpbrushes  * @title: gimpbrushes  * @short_description: Functions for manipulating brushes.  *  * Functions related to getting and setting brushes.  **/
end_comment

begin_comment
comment|/**  * gimp_brushes_refresh:  *  * Refresh current brushes. This function always succeeds.  *  * This procedure retrieves all brushes currently in the user's brush  * path and updates the brush dialogs accordingly.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brushes_refresh (void)
name|gimp_brushes_refresh
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brushes-refresh"
argument_list|,
operator|&
name|nreturn_vals
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
comment|/**  * gimp_brushes_get_list:  * @filter: An optional regular expression used to filter the list.  * @num_brushes: The number of brushes in the brush list.  *  * Retrieve a complete listing of the available brushes.  *  * This procedure returns a complete listing of available GIMP brushes.  * Each name returned can be used as input to the  * gimp_context_set_brush() procedure.  *  * Returns: The list of brush names. The returned value must be freed with g_strfreev().  **/
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_brushes_get_list (const gchar * filter,gint * num_brushes)
name|gimp_brushes_get_list
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filter
parameter_list|,
name|gint
modifier|*
name|num_brushes
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
modifier|*
name|brush_list
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brushes-get-list"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|filter
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_brushes
operator|=
literal|0
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
block|{
operator|*
name|num_brushes
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
name|brush_list
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_brushes
operator|+
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_brushes
condition|;
name|i
operator|++
control|)
name|brush_list
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_stringarray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|brush_list
index|[
name|i
index|]
operator|=
name|NULL
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
name|brush_list
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brushes_get_brush:  * @width: The brush width.  * @height: The brush height.  * @spacing: The brush spacing.  *  * Deprecated: Use gimp_context_get_brush() instead.  *  * Returns: The brush name.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_brushes_get_brush (gint * width,gint * height,gint * spacing)
name|gimp_brushes_get_brush
parameter_list|(
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
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brushes-get-brush"
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
block|{
name|name
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
operator|*
name|width
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
name|height
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
name|spacing
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
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brushes_get_spacing:  *  * Deprecated: Use gimp_brush_get_spacing() instead.  *  * Returns: The brush spacing.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_brushes_get_spacing (void)
name|gimp_brushes_get_spacing
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
name|gint
name|spacing
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-brushes-get-spacing"
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
name|spacing
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_brushes_set_spacing:  * @spacing: The brush spacing.  *  * Deprecated: Use gimp_brush_set_spacing() instead.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_brushes_set_spacing (gint spacing)
name|gimp_brushes_set_spacing
parameter_list|(
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
literal|"gimp-brushes-set-spacing"
argument_list|,
operator|&
name|nreturn_vals
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
comment|/**  * gimp_brushes_get_brush_data:  * @name: The brush name (\"\" means current active brush).  * @opacity: The brush opacity.  * @spacing: The brush spacing.  * @paint_mode: The paint mode.  * @width: The brush width.  * @height: The brush height.  * @length: Length of brush mask data.  * @mask_data: The brush mask data.  *  * Deprecated: Use gimp_brush_get_pixels() instead.  *  * Returns: The brush name.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_brushes_get_brush_data (const gchar * name,gdouble * opacity,gint * spacing,GimpLayerModeEffects * paint_mode,gint * width,gint * height,gint * length,guint8 ** mask_data)
name|gimp_brushes_get_brush_data
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
modifier|*
name|opacity
parameter_list|,
name|gint
modifier|*
name|spacing
parameter_list|,
name|GimpLayerModeEffects
modifier|*
name|paint_mode
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
name|length
parameter_list|,
name|guint8
modifier|*
modifier|*
name|mask_data
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
literal|"gimp-brushes-get-brush-data"
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
name|length
operator|=
literal|0
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
block|{
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
operator|*
name|opacity
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|spacing
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
name|paint_mode
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
name|width
operator|=
name|return_vals
index|[
literal|5
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
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|length
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
name|mask_data
operator|=
name|g_new
argument_list|(
name|guint8
argument_list|,
operator|*
name|length
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|mask_data
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
name|length
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
name|actual_name
return|;
block|}
end_function

end_unit

