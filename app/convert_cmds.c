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
file|"convert.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_decl_stmt
DECL|variable|convert_rgb_proc
specifier|static
name|ProcRecord
name|convert_rgb_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|convert_grayscale_proc
specifier|static
name|ProcRecord
name|convert_grayscale_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|convert_indexed_proc
specifier|static
name|ProcRecord
name|convert_indexed_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|convert_indexed_palette_proc
specifier|static
name|ProcRecord
name|convert_indexed_palette_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_convert_procs (void)
name|register_convert_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|convert_rgb_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|convert_grayscale_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|convert_indexed_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|convert_indexed_palette_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|convert_rgb_invoker (Argument * args)
name|convert_rgb_invoker
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
name|GimpImage
modifier|*
name|gimage
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
if|if
condition|(
name|success
condition|)
if|if
condition|(
operator|(
name|success
operator|=
operator|(
name|gimage_base_type
argument_list|(
name|gimage
argument_list|)
operator|!=
name|RGB
operator|)
operator|)
condition|)
name|convert_image
argument_list|(
operator|(
name|void
operator|*
operator|)
name|gimage
argument_list|,
name|RGB
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|convert_rgb_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|convert_rgb_inargs
specifier|static
name|ProcArg
name|convert_rgb_inargs
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|convert_rgb_proc
specifier|static
name|ProcRecord
name|convert_rgb_proc
init|=
block|{
literal|"gimp_convert_rgb"
block|,
literal|"Convert specified image to RGB color"
block|,
literal|"This procedure converts the specified image to RGB color. This process requires an image of type GRAY or INDEXED. No image content is lost in this process aside from the colormap for an indexed image."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|convert_rgb_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|convert_rgb_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|convert_grayscale_invoker (Argument * args)
name|convert_grayscale_invoker
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
name|GimpImage
modifier|*
name|gimage
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
if|if
condition|(
name|success
condition|)
if|if
condition|(
operator|(
name|success
operator|=
operator|(
name|gimage_base_type
argument_list|(
name|gimage
argument_list|)
operator|!=
name|GRAY
operator|)
operator|)
condition|)
name|convert_image
argument_list|(
operator|(
name|void
operator|*
operator|)
name|gimage
argument_list|,
name|GRAY
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|convert_grayscale_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|convert_grayscale_inargs
specifier|static
name|ProcArg
name|convert_grayscale_inargs
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|convert_grayscale_proc
specifier|static
name|ProcRecord
name|convert_grayscale_proc
init|=
block|{
literal|"gimp_convert_grayscale"
block|,
literal|"Convert specified image to grayscale (256 intensity levels)"
block|,
literal|"This procedure converts the specified image to grayscale with 8 bits per pixel (256 intensity levels). This process requires an image of type RGB or INDEXED."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|convert_grayscale_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|convert_grayscale_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|convert_indexed_invoker (Argument * args)
name|convert_indexed_invoker
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gboolean
name|dither
decl_stmt|;
name|gint32
name|num_cols
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
name|dither
operator|=
name|args
index|[
literal|1
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
name|num_cols
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
name|success
condition|)
block|{
name|success
operator|=
name|gimage_base_type
argument_list|(
name|gimage
argument_list|)
operator|!=
name|INDEXED
expr_stmt|;
if|if
condition|(
name|num_cols
operator|<
literal|1
operator|||
name|num_cols
operator|>
name|MAXNUMCOLORS
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|convert_image
argument_list|(
operator|(
name|void
operator|*
operator|)
name|gimage
argument_list|,
name|INDEXED
argument_list|,
name|num_cols
argument_list|,
name|dither
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|convert_indexed_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|convert_indexed_inargs
specifier|static
name|ProcArg
name|convert_indexed_inargs
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
name|PDB_INT32
block|,
literal|"dither"
block|,
literal|"Floyd-Steinberg dithering"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_cols"
block|,
literal|"the number of colors to quantize to"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|convert_indexed_proc
specifier|static
name|ProcRecord
name|convert_indexed_proc
init|=
block|{
literal|"gimp_convert_indexed"
block|,
literal|"Convert specified image to indexed color"
block|,
literal|"This procedure converts the specified image to indexed color. This process requires an image of type GRAY or RGB. The 'num_cols' arguments specifies how many colors the resulting image should be quantized to (1-256)."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|3
block|,
name|convert_indexed_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|convert_indexed_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|convert_indexed_palette_invoker (Argument * args)
name|convert_indexed_palette_invoker
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gboolean
name|dither
decl_stmt|;
name|gint32
name|palette_type
decl_stmt|;
name|gint32
name|num_cols
decl_stmt|;
name|gchar
modifier|*
name|palette_name
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
name|dither
operator|=
name|args
index|[
literal|1
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
name|palette_type
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
name|num_cols
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|palette_name
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
name|palette_name
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
operator|(
name|success
operator|=
operator|(
name|gimage_base_type
argument_list|(
name|gimage
argument_list|)
operator|!=
name|INDEXED
operator|)
operator|)
condition|)
block|{
name|PaletteEntriesP
name|entries
decl_stmt|,
name|the_palette
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
switch|switch
condition|(
name|palette_type
condition|)
block|{
case|case
name|MAKE_PALETTE
case|:
if|if
condition|(
name|num_cols
operator|<
literal|1
operator|||
name|num_cols
operator|>
name|MAXNUMCOLORS
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
name|REUSE_PALETTE
case|:
case|case
name|WEB_PALETTE
case|:
case|case
name|MONO_PALETTE
case|:
break|break;
case|case
name|CUSTOM_PALETTE
case|:
if|if
condition|(
operator|!
name|palette_entries_list
condition|)
name|palette_init_palettes
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|palette_entries_list
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|entries
operator|=
operator|(
name|PaletteEntriesP
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|palette_name
argument_list|,
name|entries
operator|->
name|name
argument_list|)
condition|)
block|{
name|the_palette
operator|=
name|entries
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|the_palette
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
else|else
name|theCustomPalette
operator|=
name|the_palette
expr_stmt|;
break|break;
default|default:
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|success
condition|)
name|convert_image
argument_list|(
operator|(
name|void
operator|*
operator|)
name|gimage
argument_list|,
name|INDEXED
argument_list|,
name|num_cols
argument_list|,
name|dither
argument_list|,
name|palette_type
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|convert_indexed_palette_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|convert_indexed_palette_inargs
specifier|static
name|ProcArg
name|convert_indexed_palette_inargs
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
name|PDB_INT32
block|,
literal|"dither"
block|,
literal|"Floyd-Steinberg dithering"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"palette_type"
block|,
literal|"The type of palette to use: { MAKE_PALETTE (0), REUSE_PALETTE (1), WEB_PALETTE (2), MONO_PALETTE (3), CUSTOM_PALETTE (4) }"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_cols"
block|,
literal|"the number of colors to quantize to, ignored unless (palette_type == MAKE_PALETTE)"
block|}
block|,
block|{
name|PDB_STRING
block|,
literal|"palette"
block|,
literal|"The name of the custom palette to use, ignored unless (palette_type == CUSTOM_PALETTE)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|convert_indexed_palette_proc
specifier|static
name|ProcRecord
name|convert_indexed_palette_proc
init|=
block|{
literal|"gimp_convert_indexed_palette"
block|,
literal|"Convert specified image to indexed color"
block|,
literal|"This procedure converts the specified image to indexed color. This process requires an image of type GRAY or RGB. The 'palette_type' specifies what kind of palette to use, A type of '0' means to use an optimal palette of 'num_cols' generated from the colors in the image. A type of '1' means to re-use the previous palette. A type of '2' means to use the WWW-optimized palette. Type '3' means to use only black and white colors. A type of '4' means to use a palette from the gimp palettes directories."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|5
block|,
name|convert_indexed_palette_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|convert_indexed_palette_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

