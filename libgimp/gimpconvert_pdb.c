begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpconvert_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_convert_rgb (gint32 image_ID)
name|gimp_convert_rgb
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
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_convert_rgb"
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

begin_function
name|gboolean
DECL|function|gimp_convert_grayscale (gint32 image_ID)
name|gimp_convert_grayscale
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
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_convert_grayscale"
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

begin_function
name|gboolean
DECL|function|gimp_convert_indexed (gint32 image_ID,GimpConvertDitherType dither_type,GimpConvertPaletteType palette_type,gint num_cols,gboolean alpha_dither,gboolean remove_unused,gchar * palette)
name|gimp_convert_indexed
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpConvertDitherType
name|dither_type
parameter_list|,
name|GimpConvertPaletteType
name|palette_type
parameter_list|,
name|gint
name|num_cols
parameter_list|,
name|gboolean
name|alpha_dither
parameter_list|,
name|gboolean
name|remove_unused
parameter_list|,
name|gchar
modifier|*
name|palette
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
literal|"gimp_convert_indexed"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|dither_type
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|palette_type
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|num_cols
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|alpha_dither
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|remove_unused
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|palette
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

