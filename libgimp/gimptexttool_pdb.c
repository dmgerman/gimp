begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimptexttool_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimptexttool  * @title: gimptexttool  * @short_description: Functions for controlling the text tool.  *  * Functions for controlling the text tool.  **/
end_comment

begin_comment
comment|/**  * gimp_text_fontname:  * @image: The image.  * @drawable: (nullable): The affected drawable: (%NULL for a new text layer).  * @x: The x coordinate for the left of the text bounding box.  * @y: The y coordinate for the top of the text bounding box.  * @text: The text to generate (in UTF-8 encoding).  * @border: The size of the border.  * @antialias: Antialiasing.  * @size: The size of text in either pixels or points.  * @size_type: The units of specified size.  * @fontname: The name of the font.  *  * Add text at the specified location as a floating selection or a new  * layer.  *  * This tool requires a fontname matching an installed PangoFT2 font.  * You can specify the fontsize in units of pixels or points, and the  * appropriate metric is specified using the size_type argument. The x  * and y parameters together control the placement of the new text by  * specifying the upper left corner of the text bounding box. If the  * specified drawable parameter is valid, the text will be created as a  * floating selection attached to the drawable. If the drawable  * parameter is not valid (%NULL), the text will appear as a new layer.  * Finally, a border can be specified around the final rendered text.  * The border is measured in pixels. Parameter size-type is not used  * and is currently ignored. If you need to display a font in points,  * divide the size in points by 72.0 and multiply it by the image's  * vertical resolution.  *  * Returns: (nullable) (transfer none):  *          The new text layer or %NULL if no layer was created.  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_text_fontname (GimpImage * image,GimpDrawable * drawable,gdouble x,gdouble y,const gchar * text,gint border,gboolean antialias,gdouble size,GimpSizeType size_type,const gchar * fontname)
name|gimp_text_fontname
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
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
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpLayer
modifier|*
name|text_layer
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|gimp_item_get_id
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|text
argument_list|,
name|G_TYPE_INT
argument_list|,
name|border
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|antialias
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|size
argument_list|,
name|GIMP_TYPE_SIZE_TYPE
argument_list|,
name|size_type
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|fontname
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-text-fontname"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-text-fontname"
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
name|text_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|gimp_value_get_layer_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|text_layer
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_text_fontname: (skip)  * @image_ID: The image.  * @drawable_ID: (nullable): The affected drawable: (%NULL for a new text layer).  * @x: The x coordinate for the left of the text bounding box.  * @y: The y coordinate for the top of the text bounding box.  * @text: The text to generate (in UTF-8 encoding).  * @border: The size of the border.  * @antialias: Antialiasing.  * @size: The size of text in either pixels or points.  * @size_type: The units of specified size.  * @fontname: The name of the font.  *  * Add text at the specified location as a floating selection or a new  * layer.  *  * This tool requires a fontname matching an installed PangoFT2 font.  * You can specify the fontsize in units of pixels or points, and the  * appropriate metric is specified using the size_type argument. The x  * and y parameters together control the placement of the new text by  * specifying the upper left corner of the text bounding box. If the  * specified drawable parameter is valid, the text will be created as a  * floating selection attached to the drawable. If the drawable  * parameter is not valid (%NULL), the text will appear as a new layer.  * Finally, a border can be specified around the final rendered text.  * The border is measured in pixels. Parameter size-type is not used  * and is currently ignored. If you need to display a font in points,  * divide the size in points by 72.0 and multiply it by the image's  * vertical resolution.  *  * Returns: (nullable): The new text layer or %NULL if no layer was created.  **/
end_comment

begin_function
name|gint32
DECL|function|_gimp_text_fontname (gint32 image_ID,gint32 drawable_ID,gdouble x,gdouble y,const gchar * text,gint border,gboolean antialias,gdouble size,GimpSizeType size_type,const gchar * fontname)
name|_gimp_text_fontname
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
specifier|const
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
specifier|const
name|gchar
modifier|*
name|fontname
parameter_list|)
block|{
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|text_layer_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|image_ID
argument_list|,
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|drawable_ID
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|text
argument_list|,
name|G_TYPE_INT
argument_list|,
name|border
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|antialias
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|size
argument_list|,
name|GIMP_TYPE_SIZE_TYPE
argument_list|,
name|size_type
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|fontname
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-text-fontname"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-text-fontname"
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
name|text_layer_ID
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
name|text_layer_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_text_get_extents_fontname:  * @text: The text to generate (in UTF-8 encoding).  * @size: The size of text in either pixels or points.  * @size_type: The units of specified size.  * @fontname: The name of the font.  * @width: (out): The width of the specified font.  * @height: (out): The height of the specified font.  * @ascent: (out): The ascent of the specified font.  * @descent: (out): The descent of the specified font.  *  * Get extents of the bounding box for the specified text.  *  * This tool returns the width and height of a bounding box for the  * specified text string with the specified font information. Ascent  * and descent for the specified font are returned as well. Parameter  * size-type is not used and is currently ignored. If you need to  * display a font in points, divide the size in points by 72.0 and  * multiply it by the vertical resolution of the image you are taking  * into account.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_text_get_extents_fontname (const gchar * text,gdouble size,GimpSizeType size_type,const gchar * fontname,gint * width,gint * height,gint * ascent,gint * descent)
name|gimp_text_get_extents_fontname
parameter_list|(
specifier|const
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
specifier|const
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
name|GimpPDB
modifier|*
name|pdb
init|=
name|gimp_get_pdb
argument_list|()
decl_stmt|;
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
name|NULL
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|text
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|size
argument_list|,
name|GIMP_TYPE_SIZE_TYPE
argument_list|,
name|size_type
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|fontname
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pdb
condition|)
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|pdb
argument_list|,
literal|"gimp-text-get-extents-fontname"
argument_list|,
name|args
argument_list|)
expr_stmt|;
else|else
name|return_vals
operator|=
name|gimp_run_procedure_array
argument_list|(
literal|"gimp-text-get-extents-fontname"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
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
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|width
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|height
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|ascent
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|descent
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|4
argument_list|)
argument_list|)
expr_stmt|;
block|}
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

end_unit

