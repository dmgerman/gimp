begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimptexttool_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
name|gint32
DECL|function|gimp_text_fontname (gint32 image_ID,gint32 drawable_ID,gdouble x,gdouble y,gchar * text,gint border,gboolean antialias,gdouble size,GimpSizeType size_type,gchar * fontname)
name|gimp_text_fontname
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|border
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpSizeType
name|size_type
parameter_list|,
name|gchar
modifier|*
name|fontname
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
name|text_layer_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_text_fontname"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|text
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|border
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|antialias
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|size
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|size_type
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|fontname
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
name|text_layer_ID
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
name|text_layer_ID
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_get_extents_fontname (gchar * text,gdouble size,GimpSizeType size_type,gchar * fontname,gint * width,gint * height,gint * ascent,gint * descent)
name|gimp_text_get_extents_fontname
parameter_list|(
name|gchar
modifier|*
name|text
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpSizeType
name|size_type
parameter_list|,
name|gchar
modifier|*
name|fontname
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
name|ascent
parameter_list|,
name|gint
modifier|*
name|descent
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_text_get_extents_fontname"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|text
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|size
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|size_type
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|fontname
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
name|ascent
operator|=
literal|0
expr_stmt|;
operator|*
name|descent
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
name|ascent
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
name|descent
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
block|}
end_function

begin_function
name|gint32
DECL|function|gimp_text (gint32 image_ID,gint32 drawable_ID,gdouble x,gdouble y,gchar * text,gint border,gboolean antialias,gdouble size,GimpSizeType size_type,gchar * foundry,gchar * family,gchar * weight,gchar * slant,gchar * set_width,gchar * spacing,gchar * registry,gchar * encoding)
name|gimp_text
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gchar
modifier|*
name|text
parameter_list|,
name|gint
name|border
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpSizeType
name|size_type
parameter_list|,
name|gchar
modifier|*
name|foundry
parameter_list|,
name|gchar
modifier|*
name|family
parameter_list|,
name|gchar
modifier|*
name|weight
parameter_list|,
name|gchar
modifier|*
name|slant
parameter_list|,
name|gchar
modifier|*
name|set_width
parameter_list|,
name|gchar
modifier|*
name|spacing
parameter_list|,
name|gchar
modifier|*
name|registry
parameter_list|,
name|gchar
modifier|*
name|encoding
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
name|text_layer_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_text"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|text
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|border
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|antialias
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|size
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|size_type
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|foundry
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|family
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|weight
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|slant
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|set_width
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|spacing
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|registry
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|encoding
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
name|text_layer_ID
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
name|text_layer_ID
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_text_get_extents (gchar * text,gdouble size,GimpSizeType size_type,gchar * foundry,gchar * family,gchar * weight,gchar * slant,gchar * set_width,gchar * spacing,gchar * registry,gchar * encoding,gint * width,gint * height,gint * ascent,gint * descent)
name|gimp_text_get_extents
parameter_list|(
name|gchar
modifier|*
name|text
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|GimpSizeType
name|size_type
parameter_list|,
name|gchar
modifier|*
name|foundry
parameter_list|,
name|gchar
modifier|*
name|family
parameter_list|,
name|gchar
modifier|*
name|weight
parameter_list|,
name|gchar
modifier|*
name|slant
parameter_list|,
name|gchar
modifier|*
name|set_width
parameter_list|,
name|gchar
modifier|*
name|spacing
parameter_list|,
name|gchar
modifier|*
name|registry
parameter_list|,
name|gchar
modifier|*
name|encoding
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
name|ascent
parameter_list|,
name|gint
modifier|*
name|descent
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_text_get_extents"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|text
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|size
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|size_type
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|foundry
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|family
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|weight
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|slant
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|set_width
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|spacing
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|registry
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|encoding
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
name|ascent
operator|=
literal|0
expr_stmt|;
operator|*
name|descent
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
name|ascent
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
name|descent
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
block|}
end_function

end_unit

