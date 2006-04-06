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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-pdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
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

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|image_convert_rgb_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|image_convert_rgb_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|image
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
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
name|image
argument_list|)
operator|!=
name|GIMP_RGB
condition|)
name|gimp_image_convert
argument_list|(
name|image
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|image_convert_grayscale_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|image_convert_grayscale_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|image
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
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
name|image
argument_list|)
operator|!=
name|GIMP_GRAY
condition|)
name|gimp_image_convert
argument_list|(
name|image
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|image_convert_indexed_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|image_convert_indexed_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|image
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
specifier|const
name|gchar
modifier|*
name|palette
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|dither_type
operator|=
name|g_value_get_enum
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|palette_type
operator|=
name|g_value_get_enum
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|num_cols
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|alpha_dither
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|4
index|]
argument_list|)
expr_stmt|;
name|remove_unused
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|5
index|]
argument_list|)
expr_stmt|;
name|palette
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|6
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPalette
modifier|*
name|pal
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_image_base_type
argument_list|(
name|image
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
name|pal
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
name|palette
argument_list|)
expr_stmt|;
if|if
condition|(
name|pal
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
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_image_convert
argument_list|(
name|image
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
name|pal
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

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
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimp-image-convert-rgb    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_convert_rgb_invoker
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-image-convert-rgb"
argument_list|,
literal|"gimp-image-convert-rgb"
argument_list|,
literal|"Convert specified image to RGB color"
argument_list|,
literal|"This procedure converts the specified image to RGB color. This process requires an image of type GIMP_GRAY or GIMP_INDEXED. No image content is lost in this process aside from the colormap for an indexed image."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-image-convert-grayscale    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_convert_grayscale_invoker
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-image-convert-grayscale"
argument_list|,
literal|"gimp-image-convert-grayscale"
argument_list|,
literal|"Convert specified image to grayscale (256 intensity levels)"
argument_list|,
literal|"This procedure converts the specified image to grayscale with 8 bits per pixel (256 intensity levels). This process requires an image of type GIMP_RGB or GIMP_INDEXED."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-image-convert-indexed    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_convert_indexed_invoker
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-image-convert-indexed"
argument_list|,
literal|"gimp-image-convert-indexed"
argument_list|,
literal|"Convert specified image to and Indexed image"
argument_list|,
literal|"This procedure converts the specified image to 'indexed' color. This process requires an image of type GIMP_GRAY or GIMP_RGB. The 'palette_type' specifies what kind of palette to use, A type of '0' means to use an optimal palette of 'num_cols' generated from the colors in the image. A type of '1' means to re-use the previous palette (not currently implemented). A type of '2' means to use the so-called WWW-optimized palette. Type '3' means to use only black and white colors. A type of '4' means to use a palette from the gimp palettes directories. The 'dither type' specifies what kind of dithering to use. '0' means no dithering, '1' means standard Floyd-Steinberg error diffusion, '2' means Floyd-Steinberg error diffusion with reduced bleeding, '3' means dithering based on pixel location ('Fixed' dithering)."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"dither-type"
argument_list|,
literal|"dither type"
argument_list|,
literal|"The dither type to use: { GIMP_NO_DITHER (0), GIMP_FS_DITHER (1), GIMP_FSLOWBLEED_DITHER (2), GIMP_FIXED_DITHER (3) }"
argument_list|,
name|GIMP_TYPE_CONVERT_DITHER_TYPE
argument_list|,
name|GIMP_NO_DITHER
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"palette-type"
argument_list|,
literal|"palette type"
argument_list|,
literal|"The type of palette to use: { GIMP_MAKE_PALETTE (0), GIMP_REUSE_PALETTE (1), GIMP_WEB_PALETTE (2), GIMP_MONO_PALETTE (3), GIMP_CUSTOM_PALETTE (4) }"
argument_list|,
name|GIMP_TYPE_CONVERT_PALETTE_TYPE
argument_list|,
name|GIMP_MAKE_PALETTE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-cols"
argument_list|,
literal|"num cols"
argument_list|,
literal|"The number of colors to quantize to, ignored unless (palette_type == GIMP_MAKE_PALETTE)"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"alpha-dither"
argument_list|,
literal|"alpha dither"
argument_list|,
literal|"Dither transparency to fake partial opacity"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"remove-unused"
argument_list|,
literal|"remove unused"
argument_list|,
literal|"Remove unused or duplicate color entries from final palette, ignored if (palette_type == GIMP_MAKE_PALETTE)"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"palette"
argument_list|,
literal|"palette"
argument_list|,
literal|"The name of the custom palette to use, ignored unless (palette_type == GIMP_CUSTOM_PALETTE)"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

