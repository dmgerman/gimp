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
file|"libgimpbase/gimpbasetypes.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-convert.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalette.h"
end_include

begin_decl_stmt
DECL|variable|image_convert_rgb_proc
specifier|static
name|ProcRecord
name|image_convert_rgb_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_convert_grayscale_proc
specifier|static
name|ProcRecord
name|image_convert_grayscale_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_convert_indexed_proc
specifier|static
name|ProcRecord
name|image_convert_indexed_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_convert_procs (Gimp * gimp)
name|register_convert_procs
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
name|image_convert_rgb_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_convert_grayscale_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|image_convert_indexed_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_convert_rgb_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_convert_rgb_invoker
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
name|GimpImage
modifier|*
name|gimage
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
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|!=
name|GIMP_RGB
condition|)
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
name|GIMP_RGB
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|image_convert_rgb_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_convert_rgb_inargs
specifier|static
name|ProcArg
name|image_convert_rgb_inargs
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_convert_rgb_proc
specifier|static
name|ProcRecord
name|image_convert_rgb_proc
init|=
block|{
literal|"gimp_image_convert_rgb"
block|,
literal|"Convert specified image to RGB color"
block|,
literal|"This procedure converts the specified image to RGB color. This process requires an image of type GIMP_GRAY or GIMP_INDEXED. No image content is lost in this process aside from the colormap for an indexed image."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|image_convert_rgb_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_convert_rgb_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_convert_grayscale_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_convert_grayscale_invoker
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
name|GimpImage
modifier|*
name|gimage
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
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|!=
name|GIMP_GRAY
condition|)
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
name|GIMP_GRAY
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|image_convert_grayscale_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_convert_grayscale_inargs
specifier|static
name|ProcArg
name|image_convert_grayscale_inargs
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_convert_grayscale_proc
specifier|static
name|ProcRecord
name|image_convert_grayscale_proc
init|=
block|{
literal|"gimp_image_convert_grayscale"
block|,
literal|"Convert specified image to grayscale (256 intensity levels)"
block|,
literal|"This procedure converts the specified image to grayscale with 8 bits per pixel (256 intensity levels). This process requires an image of type GIMP_RGB or GIMP_INDEXED."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|image_convert_grayscale_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_convert_grayscale_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|image_convert_indexed_invoker (Gimp * gimp,GimpContext * context,Argument * args)
name|image_convert_indexed_invoker
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gint32
name|dither_type
decl_stmt|;
name|gint32
name|palette_type
decl_stmt|;
name|gint32
name|num_cols
decl_stmt|;
name|gboolean
name|alpha_dither
decl_stmt|;
name|gboolean
name|remove_unused
decl_stmt|;
name|gchar
modifier|*
name|palette_name
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
name|dither_type
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|dither_type
operator|<
name|GIMP_NO_DITHER
operator|||
name|dither_type
operator|>
name|GIMP_FIXED_DITHER
condition|)
name|success
operator|=
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
if|if
condition|(
name|palette_type
operator|<
name|GIMP_MAKE_PALETTE
operator|||
name|palette_type
operator|>
name|GIMP_CUSTOM_PALETTE
condition|)
name|success
operator|=
name|FALSE
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
name|alpha_dither
operator|=
name|args
index|[
literal|4
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
name|remove_unused
operator|=
name|args
index|[
literal|5
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
name|palette_name
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
name|palette_name
operator|==
name|NULL
operator|||
operator|!
name|g_utf8_validate
argument_list|(
name|palette_name
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
name|GimpPalette
modifier|*
name|palette
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|!=
name|GIMP_INDEXED
condition|)
block|{
switch|switch
condition|(
name|palette_type
condition|)
block|{
case|case
name|GIMP_MAKE_PALETTE
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
name|GIMP_CUSTOM_PALETTE
case|:
if|if
condition|(
operator|!
name|gimp
operator|->
name|palette_factory
operator|->
name|container
operator|->
name|num_children
condition|)
name|gimp_data_factory_data_init
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|palette
operator|=
operator|(
name|GimpPalette
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|palette_factory
operator|->
name|container
argument_list|,
name|palette_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|palette
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
name|GIMP_INDEXED
argument_list|,
name|num_cols
argument_list|,
name|dither_type
argument_list|,
name|alpha_dither
argument_list|,
name|remove_unused
argument_list|,
name|palette_type
argument_list|,
name|palette
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|image_convert_indexed_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|image_convert_indexed_inargs
specifier|static
name|ProcArg
name|image_convert_indexed_inargs
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
name|GIMP_PDB_INT32
block|,
literal|"dither_type"
block|,
literal|"The dither type to use: { GIMP_NO_DITHER (0), GIMP_FS_DITHER (1), GIMP_FSLOWBLEED_DITHER (2), GIMP_FIXED_DITHER (3) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"palette_type"
block|,
literal|"The type of palette to use: { GIMP_MAKE_PALETTE (0), GIMP_REUSE_PALETTE (1), GIMP_WEB_PALETTE (2), GIMP_MONO_PALETTE (3), GIMP_CUSTOM_PALETTE (4) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_cols"
block|,
literal|"The number of colors to quantize to, ignored unless (palette_type == GIMP_MAKE_PALETTE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"alpha_dither"
block|,
literal|"Dither transparency to fake partial opacity"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"remove_unused"
block|,
literal|"Remove unused or duplicate colour entries from final palette, ignored if (palette_type == GIMP_MAKE_PALETTE)"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"palette"
block|,
literal|"The name of the custom palette to use, ignored unless (palette_type == GIMP_CUSTOM_PALETTE)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_convert_indexed_proc
specifier|static
name|ProcRecord
name|image_convert_indexed_proc
init|=
block|{
literal|"gimp_image_convert_indexed"
block|,
literal|"Convert specified image to and Indexed image"
block|,
literal|"This procedure converts the specified image to 'indexed' color. This process requires an image of type GIMP_GRAY or GIMP_RGB. The 'palette_type' specifies what kind of palette to use, A type of '0' means to use an optimal palette of 'num_cols' generated from the colors in the image. A type of '1' means to re-use the previous palette (not currently implemented). A type of '2' means to use the so-called WWW-optimized palette. Type '3' means to use only black and white colors. A type of '4' means to use a palette from the gimp palettes directories. The 'dither type' specifies what kind of dithering to use. '0' means no dithering, '1' means standard Floyd-Steinberg error diffusion, '2' means Floyd-Steinberg error diffusion with reduced bleeding, '3' means dithering based on pixel location ('Fixed' dithering)."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|7
block|,
name|image_convert_indexed_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|image_convert_indexed_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

