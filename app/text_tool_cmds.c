begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"layer.h"
end_include

begin_include
include|#
directive|include
file|"text_tool.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_decl_stmt
DECL|variable|text_fontname_proc
specifier|static
name|ProcRecord
name|text_fontname_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_get_extents_fontname_proc
specifier|static
name|ProcRecord
name|text_get_extents_fontname_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_proc
specifier|static
name|ProcRecord
name|text_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_get_extents_proc
specifier|static
name|ProcRecord
name|text_get_extents_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_text_tool_procs (void)
name|register_text_tool_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|text_fontname_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|text_get_extents_fontname_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|text_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|text_get_extents_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|text_xlfd_insert_size (gchar * fontname,gdouble size,SizeType metric,gboolean antialias)
name|text_xlfd_insert_size
parameter_list|(
name|gchar
modifier|*
name|fontname
parameter_list|,
name|gdouble
name|size
parameter_list|,
name|SizeType
name|metric
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
block|{
name|gchar
modifier|*
name|newfont
decl_stmt|,
modifier|*
name|workfont
decl_stmt|;
name|gchar
name|buffer
index|[
literal|16
index|]
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|size
operator|<=
literal|0
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|antialias
condition|)
name|size
operator|*=
name|SUPERSAMPLE
expr_stmt|;
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"%d"
argument_list|,
operator|(
name|int
operator|)
name|size
argument_list|)
expr_stmt|;
name|newfont
operator|=
name|workfont
operator|=
name|g_new
argument_list|(
name|char
argument_list|,
name|strlen
argument_list|(
name|fontname
argument_list|)
operator|+
literal|16
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|fontname
condition|)
block|{
operator|*
name|workfont
operator|++
operator|=
operator|*
name|fontname
expr_stmt|;
if|if
condition|(
operator|*
name|fontname
operator|++
operator|==
literal|'-'
condition|)
block|{
name|pos
operator|++
expr_stmt|;
if|if
condition|(
operator|(
name|pos
operator|==
literal|7
operator|&&
name|metric
operator|==
name|PIXELS
operator|)
operator|||
operator|(
name|pos
operator|==
literal|8
operator|&&
name|metric
operator|==
name|POINTS
operator|)
condition|)
block|{
name|int
name|len
init|=
name|strlen
argument_list|(
name|buffer
argument_list|)
decl_stmt|;
name|memcpy
argument_list|(
name|workfont
argument_list|,
name|buffer
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|workfont
operator|+=
name|len
expr_stmt|;
while|while
condition|(
operator|*
name|fontname
operator|!=
literal|'-'
condition|)
name|fontname
operator|++
expr_stmt|;
block|}
block|}
block|}
operator|*
name|workfont
operator|=
literal|'\0'
expr_stmt|;
return|return
name|newfont
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|text_xlfd_create (gchar * foundry,gchar * family,gchar * weight,gchar * slant,gchar * set_width,gchar * spacing,gchar * registry,gchar * encoding)
name|text_xlfd_create
parameter_list|(
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
comment|/* create the fontname */
return|return
name|g_strdup_printf
argument_list|(
literal|"-%s-%s-%s-%s-%s-*-*-*-*-*-%s-*-%s-%s"
argument_list|,
name|foundry
argument_list|,
name|family
argument_list|,
name|weight
argument_list|,
name|slant
argument_list|,
name|set_width
argument_list|,
name|spacing
argument_list|,
name|registry
argument_list|,
name|encoding
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|text_fontname_invoker (Argument * args)
name|text_fontname_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gdouble
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gint32
name|border
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|gdouble
name|size
decl_stmt|;
name|gint32
name|size_type
decl_stmt|;
name|gchar
modifier|*
name|fontname
decl_stmt|;
name|GimpLayer
modifier|*
name|text_layer
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|real_fontname
decl_stmt|;
name|gimage
operator|=
name|pdb_id_to_image
argument_list|(
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_ID
argument_list|(
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
name|x
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|y
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|text
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|text
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|border
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|border
operator|<
operator|-
literal|1
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|antialias
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|size
operator|=
name|args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|size
operator|<=
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|size_type
operator|=
name|args
index|[
literal|8
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|size_type
operator|<
name|PIXELS
operator|||
name|size_type
operator|>
name|POINTS
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|fontname
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|9
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|fontname
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|real_fontname
operator|=
name|text_xlfd_insert_size
argument_list|(
name|fontname
argument_list|,
name|size
argument_list|,
name|size_type
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
name|text_layer
operator|=
name|text_render
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|real_fontname
argument_list|,
name|text
argument_list|,
name|border
argument_list|,
name|antialias
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_layer
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|g_free
argument_list|(
name|real_fontname
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|text_fontname_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|drawable_ID
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|text_layer
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|text_fontname_inargs
specifier|static
name|ProcArg
name|text_fontname_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable: (-1 for a new text layer)"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"x"
block|,
literal|"The x coordinate for the left of the text bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"y"
block|,
literal|"The y coordinate for the top of the text bounding box"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"border"
block|,
literal|"The size of the border: -1<= border"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: PIXELS (0), POINTS (1)"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"fontname"
block|,
literal|"The fontname (conforming to the X Logical Font Description Conventions)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_fontname_outargs
specifier|static
name|ProcArg
name|text_fontname_outargs
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"text_layer"
block|,
literal|"The new text layer"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_fontname_proc
specifier|static
name|ProcRecord
name|text_fontname_proc
init|=
block|{
literal|"gimp_text_fontname"
block|,
literal|"Add text at the specified location as a floating selection or a new layer."
block|,
literal|"This tool requires font information as a fontname conforming to the 'X Logical Font Description Conventions'. You can specify the fontsize in units of pixels or points, and the appropriate metric is specified using the size_type argument. The x and y parameters together control the placement of the new text by specifying the upper left corner of the text bounding box. If the antialias parameter is non-zero, the generated text will blend more smoothly with underlying layers. This option requires more time and memory to compute than non-antialiased text; the resulting floating selection or layer, however, will require the same amount of memory with or without antialiasing. If the specified drawable parameter is valid, the text will be created as a floating selection attached to the drawable. If the drawable parameter is not valid (-1), the text will appear as a new layer. Finally, a border can be specified around the final rendered text. The border is measured in pixels."
block|,
literal|"Martin Edlman& Sven Neumann"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|10
block|,
name|text_fontname_inargs
block|,
literal|1
block|,
name|text_fontname_outargs
block|,
block|{
block|{
name|text_fontname_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|text_get_extents_fontname_invoker (Argument * args)
name|text_get_extents_fontname_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gdouble
name|size
decl_stmt|;
name|gint32
name|size_type
decl_stmt|;
name|gchar
modifier|*
name|fontname
decl_stmt|;
name|gint32
name|width
decl_stmt|;
name|gint32
name|height
decl_stmt|;
name|gint32
name|ascent
decl_stmt|;
name|gint32
name|descent
decl_stmt|;
name|gchar
modifier|*
name|real_fontname
decl_stmt|;
name|text
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|text
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|size
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|size
operator|<=
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|size_type
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|size_type
operator|<
name|PIXELS
operator|||
name|size_type
operator|>
name|POINTS
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|fontname
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|fontname
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|real_fontname
operator|=
name|text_xlfd_insert_size
argument_list|(
name|fontname
argument_list|,
name|size
argument_list|,
name|size_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|success
operator|=
name|text_get_extents
argument_list|(
name|real_fontname
argument_list|,
name|text
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|ascent
argument_list|,
operator|&
name|descent
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|real_fontname
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|text_get_extents_fontname_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|width
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|height
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|ascent
expr_stmt|;
name|return_args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|descent
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|text_get_extents_fontname_inargs
specifier|static
name|ProcArg
name|text_get_extents_fontname_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: PIXELS (0), POINTS (1)"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"fontname"
block|,
literal|"The fontname (conforming to the X Logical Font Description Conventions)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_get_extents_fontname_outargs
specifier|static
name|ProcArg
name|text_get_extents_fontname_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"width"
block|,
literal|"The width of the specified font"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"height"
block|,
literal|"The height of the specified font"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"ascent"
block|,
literal|"The ascent of the specified font"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"descent"
block|,
literal|"The descent of the specified font"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_get_extents_fontname_proc
specifier|static
name|ProcRecord
name|text_get_extents_fontname_proc
init|=
block|{
literal|"gimp_text_get_extents_fontname"
block|,
literal|"Get extents of the bounding box for the specified text."
block|,
literal|"This tool returns the width and height of a bounding box for the specified text string with the specified font information. Ascent and descent for the specified font are returned as well."
block|,
literal|"Martin Edlman& Sven Neumann"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|4
block|,
name|text_get_extents_fontname_inargs
block|,
literal|4
block|,
name|text_get_extents_fontname_outargs
block|,
block|{
block|{
name|text_get_extents_fontname_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|text_invoker (Argument * args)
name|text_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|int
name|i
decl_stmt|;
name|Argument
name|argv
index|[
literal|10
index|]
decl_stmt|;
name|gchar
modifier|*
name|foundry
decl_stmt|;
name|gchar
modifier|*
name|family
decl_stmt|;
name|gchar
modifier|*
name|weight
decl_stmt|;
name|gchar
modifier|*
name|slant
decl_stmt|;
name|gchar
modifier|*
name|set_width
decl_stmt|;
name|gchar
modifier|*
name|spacing
decl_stmt|;
name|gchar
modifier|*
name|registry
decl_stmt|;
name|gchar
modifier|*
name|encoding
decl_stmt|;
name|foundry
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|9
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|foundry
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|family
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|10
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|family
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|weight
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|11
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|weight
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|slant
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|12
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|slant
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|set_width
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|13
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|set_width
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|spacing
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|14
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|spacing
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|registry
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|15
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|registry
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|encoding
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|16
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|encoding
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|text_proc
argument_list|,
name|FALSE
argument_list|)
return|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|9
condition|;
name|i
operator|++
control|)
name|argv
index|[
name|i
index|]
operator|=
name|args
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
literal|9
index|]
operator|.
name|arg_type
operator|=
name|PDB_STRING
expr_stmt|;
name|argv
index|[
literal|9
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|text_xlfd_create
argument_list|(
name|foundry
argument_list|,
name|family
argument_list|,
name|weight
argument_list|,
name|slant
argument_list|,
name|set_width
argument_list|,
name|spacing
argument_list|,
name|registry
argument_list|,
name|encoding
argument_list|)
expr_stmt|;
return|return
name|text_fontname_invoker
argument_list|(
name|argv
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|text_inargs
specifier|static
name|ProcArg
name|text_inargs
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable: (-1 for a new text layer)"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"x"
block|,
literal|"The x coordinate for the left of the text bounding box"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"y"
block|,
literal|"The y coordinate for the top of the text bounding box"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"border"
block|,
literal|"The size of the border: -1<= border"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: PIXELS (0), POINTS (1)"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"foundry"
block|,
literal|"The font foundry, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"family"
block|,
literal|"The font family, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"weight"
block|,
literal|"The font weight, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"slant"
block|,
literal|"The font slant, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"set_width"
block|,
literal|"The font set-width, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"spacing"
block|,
literal|"The font spacing, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"registry"
block|,
literal|"The font registry, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"encoding"
block|,
literal|"The font encoding, \"*\" for any"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_outargs
specifier|static
name|ProcArg
name|text_outargs
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"text_layer"
block|,
literal|"The new text layer"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_proc
specifier|static
name|ProcRecord
name|text_proc
init|=
block|{
literal|"gimp_text"
block|,
literal|"Add text at the specified location as a floating selection or a new layer."
block|,
literal|"This tool requires font information in the form of nine parameters: size, foundry, family, weight, slant, set_width, spacing, registry, encoding. The font size can either be specified in units of pixels or points, and the appropriate metric is specified using the size_type argument. The x and y parameters together control the placement of the new text by specifying the upper left corner of the text bounding box. If the antialias parameter is non-zero, the generated text will blend more smoothly with underlying layers. This option requires more time and memory to compute than non-antialiased text; the resulting floating selection or layer, however, will require the same amount of memory with or without antialiasing. If the specified drawable parameter is valid, the text will be created as a floating selection attached to the drawable. If the drawable parameter is not valid (-1), the text will appear as a new layer. Finally, a border can be specified around the final rendered text."
literal|"The border is measured in pixels."
block|,
literal|"Martin Edlman"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|17
block|,
name|text_inargs
block|,
literal|1
block|,
name|text_outargs
block|,
block|{
block|{
name|text_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|text_get_extents_invoker (Argument * args)
name|text_get_extents_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|int
name|i
decl_stmt|;
name|Argument
name|argv
index|[
literal|4
index|]
decl_stmt|;
name|gchar
modifier|*
name|foundry
decl_stmt|;
name|gchar
modifier|*
name|family
decl_stmt|;
name|gchar
modifier|*
name|weight
decl_stmt|;
name|gchar
modifier|*
name|slant
decl_stmt|;
name|gchar
modifier|*
name|set_width
decl_stmt|;
name|gchar
modifier|*
name|spacing
decl_stmt|;
name|gchar
modifier|*
name|registry
decl_stmt|;
name|gchar
modifier|*
name|encoding
decl_stmt|;
name|foundry
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|foundry
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|family
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|family
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|weight
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|weight
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|slant
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|slant
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|set_width
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|set_width
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|spacing
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|8
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|spacing
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|registry
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|9
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|registry
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|encoding
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|10
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|encoding
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|text_get_extents_proc
argument_list|,
name|FALSE
argument_list|)
return|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
name|argv
index|[
name|i
index|]
operator|=
name|args
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
literal|3
index|]
operator|.
name|arg_type
operator|=
name|PDB_STRING
expr_stmt|;
name|argv
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|text_xlfd_create
argument_list|(
name|foundry
argument_list|,
name|family
argument_list|,
name|weight
argument_list|,
name|slant
argument_list|,
name|set_width
argument_list|,
name|spacing
argument_list|,
name|registry
argument_list|,
name|encoding
argument_list|)
expr_stmt|;
return|return
name|text_get_extents_fontname_invoker
argument_list|(
name|argv
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|text_get_extents_inargs
specifier|static
name|ProcArg
name|text_get_extents_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: PIXELS (0), POINTS (1)"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"foundry"
block|,
literal|"The font foundry, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"family"
block|,
literal|"The font family, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"weight"
block|,
literal|"The font weight, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"slant"
block|,
literal|"The font slant, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"set_width"
block|,
literal|"The font set-width, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"spacing"
block|,
literal|"The font spacing, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"registry"
block|,
literal|"The font registry, \"*\" for any"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"encoding"
block|,
literal|"The font encoding, \"*\" for any"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_get_extents_outargs
specifier|static
name|ProcArg
name|text_get_extents_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"width"
block|,
literal|"The width of the specified font"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"height"
block|,
literal|"The height of the specified font"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"ascent"
block|,
literal|"The ascent of the specified font"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"descent"
block|,
literal|"The descent of the specified font"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|text_get_extents_proc
specifier|static
name|ProcRecord
name|text_get_extents_proc
init|=
block|{
literal|"gimp_text_get_extents"
block|,
literal|"Get extents of the bounding box for the specified text."
block|,
literal|"This tool returns the width and height of a bounding box for the specified text string with the specified font information. Ascent and descent for the specified font are returned as well."
block|,
literal|"Martin Edlman"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1998"
block|,
name|PDB_INTERNAL
block|,
literal|11
block|,
name|text_get_extents_inargs
block|,
literal|4
block|,
name|text_get_extents_outargs
block|,
block|{
block|{
name|text_get_extents_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

