begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
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
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptext-compat.h"
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
DECL|function|register_text_tool_procs (Gimp * gimp)
name|register_text_tool_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|text_fontname_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|text_get_extents_fontname_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|text_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|text_get_extents_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|text_fontname_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|text_fontname_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
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
name|gimage
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
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
name|GIMP_PIXELS
operator|||
name|size_type
operator|>
name|GIMP_POINTS
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
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|fontname
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
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
if|if
condition|(
name|drawable
operator|&&
operator|!
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
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
name|gchar
modifier|*
name|real_fontname
init|=
name|g_strdup_printf
argument_list|(
literal|"%s %d"
argument_list|,
name|fontname
argument_list|,
operator|(
name|gint
operator|)
name|size
argument_list|)
decl_stmt|;
name|text_layer
operator|=
name|text_render
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
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
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable: (-1 for a new text layer)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x"
block|,
literal|"The x coordinate for the left of the text bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y"
block|,
literal|"The y coordinate for the top of the text bounding box"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"border"
block|,
literal|"The size of the border: -1<= border"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: GIMP_PIXELS (0) or GIMP_POINTS (1)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"fontname"
block|,
literal|"The name of the font"
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
name|GIMP_PDB_LAYER
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
literal|"This tool requires a fontname matching an installed PangoFT2 font. You can specify the fontsize in units of pixels or points, and the appropriate metric is specified using the size_type argument. The x and y parameters together control the placement of the new text by specifying the upper left corner of the text bounding box. If the specified drawable parameter is valid, the text will be created as a floating selection attached to the drawable. If the drawable parameter is not valid (-1), the text will appear as a new layer. Finally, a border can be specified around the final rendered text. The border is measured in pixels."
block|,
literal|"Martin Edlman& Sven Neumann"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1998- 2001"
block|,
name|GIMP_INTERNAL
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
DECL|function|text_get_extents_fontname_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|text_get_extents_fontname_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
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
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
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
name|GIMP_PIXELS
operator|||
name|size_type
operator|>
name|GIMP_POINTS
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
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|fontname
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
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
name|g_strdup_printf
argument_list|(
literal|"%s %d"
argument_list|,
name|fontname
argument_list|,
operator|(
name|gint
operator|)
name|size
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
name|GIMP_PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: GIMP_PIXELS (0) or GIMP_POINTS (1)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"fontname"
block|,
literal|"The name of the font"
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
name|GIMP_PDB_INT32
block|,
literal|"width"
block|,
literal|"The width of the specified font"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"The height of the specified font"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"ascent"
block|,
literal|"The ascent of the specified font"
block|}
block|,
block|{
name|GIMP_PDB_INT32
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
literal|"1998- 2001"
block|,
name|GIMP_INTERNAL
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
DECL|function|text_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|text_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
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
name|GimpLayer
modifier|*
name|text_layer
init|=
name|NULL
decl_stmt|;
name|gimage
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|!
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
argument_list|(
name|gimp
argument_list|,
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
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
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
name|GIMP_PIXELS
operator|||
name|size_type
operator|>
name|GIMP_POINTS
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
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
name|success
condition|)
block|{
if|if
condition|(
name|drawable
operator|&&
operator|!
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
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
name|gchar
modifier|*
name|real_fontname
init|=
name|g_strdup_printf
argument_list|(
literal|"%s %d"
argument_list|,
name|family
argument_list|,
operator|(
name|gint
operator|)
name|size
argument_list|)
decl_stmt|;
name|text_layer
operator|=
name|text_render
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|context
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
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|text_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
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
DECL|variable|text_inargs
specifier|static
name|ProcArg
name|text_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable: (-1 for a new text layer)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x"
block|,
literal|"The x coordinate for the left of the text bounding box"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y"
block|,
literal|"The y coordinate for the top of the text bounding box"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"border"
block|,
literal|"The size of the border: -1<= border"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"antialias"
block|,
literal|"Antialiasing (TRUE or FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: GIMP_PIXELS (0) or GIMP_POINTS (1)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"foundry"
block|,
literal|"The font foundry"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"family"
block|,
literal|"The font family"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"weight"
block|,
literal|"The font weight"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"slant"
block|,
literal|"The font slant"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"set_width"
block|,
literal|"The font set-width"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"spacing"
block|,
literal|"The font spacing"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"registry"
block|,
literal|"The font registry"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"encoding"
block|,
literal|"The font encoding"
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
name|GIMP_PDB_LAYER
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
literal|"This function is deprecated, use gimp_get_text_fontname() instead."
block|,
literal|"Martin Edlman"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
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
DECL|function|text_get_extents_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|text_get_extents_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
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
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
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
name|GIMP_PIXELS
operator|||
name|size_type
operator|>
name|GIMP_POINTS
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
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
name|success
condition|)
block|{
name|real_fontname
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s %d"
argument_list|,
name|family
argument_list|,
operator|(
name|gint
operator|)
name|size
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
name|text_get_extents_proc
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
DECL|variable|text_get_extents_inargs
specifier|static
name|ProcArg
name|text_get_extents_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"text"
block|,
literal|"The text to generate"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"size"
block|,
literal|"The size of text in either pixels or points"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"size_type"
block|,
literal|"The units of specified size: GIMP_PIXELS (0) or GIMP_POINTS (1)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"foundry"
block|,
literal|"The font foundry"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"family"
block|,
literal|"The font family"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"weight"
block|,
literal|"The font weight"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"slant"
block|,
literal|"The font slant"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"set_width"
block|,
literal|"The font set-width"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"spacing"
block|,
literal|"The font spacing"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"registry"
block|,
literal|"The font registry"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"encoding"
block|,
literal|"The font encoding"
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
name|GIMP_PDB_INT32
block|,
literal|"width"
block|,
literal|"The width of the specified font"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"The height of the specified font"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"ascent"
block|,
literal|"The ascent of the specified font"
block|}
block|,
block|{
name|GIMP_PDB_INT32
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
literal|"This function is deprecated, use gimp_get_text_extents_fontname() instead."
block|,
literal|"Martin Edlman"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1998"
block|,
name|GIMP_INTERNAL
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

