begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-convert-indexed.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-convert-precision.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-convert-type.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitemstack.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimppdberror.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"internal-procs.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_convert_rgb_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp_pdb_image_is_not_base_type
argument_list|(
name|image
argument_list|,
name|GIMP_RGB
argument_list|,
name|error
argument_list|)
operator|&&
name|gimp_babl_is_valid
argument_list|(
name|GIMP_RGB
argument_list|,
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
block|{
name|success
operator|=
name|gimp_image_convert_type
argument_list|(
name|image
argument_list|,
name|GIMP_RGB
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_convert_grayscale_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp_pdb_image_is_not_base_type
argument_list|(
name|image
argument_list|,
name|GIMP_GRAY
argument_list|,
name|error
argument_list|)
operator|&&
name|gimp_babl_is_valid
argument_list|(
name|GIMP_GRAY
argument_list|,
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
block|{
name|success
operator|=
name|gimp_image_convert_type
argument_list|(
name|image
argument_list|,
name|GIMP_GRAY
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_convert_indexed_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gint
name|dither_type
decl_stmt|;
name|gint
name|palette_type
decl_stmt|;
name|gint
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
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|dither_type
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|palette_type
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
name|num_cols
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
name|alpha_dither
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|)
expr_stmt|;
name|remove_unused
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
argument_list|)
expr_stmt|;
name|palette
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|6
argument_list|)
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
name|gimp_pdb_image_is_not_base_type
argument_list|(
name|image
argument_list|,
name|GIMP_INDEXED
argument_list|,
name|error
argument_list|)
operator|&&
name|gimp_pdb_image_is_precision
argument_list|(
name|image
argument_list|,
name|GIMP_PRECISION_U8_NON_LINEAR
argument_list|,
name|error
argument_list|)
operator|&&
name|gimp_babl_is_valid
argument_list|(
name|GIMP_INDEXED
argument_list|,
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
argument_list|)
operator|&&
name|gimp_item_stack_is_flat
argument_list|(
name|GIMP_ITEM_STACK
argument_list|(
name|gimp_image_get_layers
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|palette_type
condition|)
block|{
case|case
name|GIMP_CONVERT_PALETTE_GENERATE
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
name|GIMP_CONVERT_PALETTE_CUSTOM
case|:
name|pal
operator|=
name|gimp_pdb_get_palette
argument_list|(
name|gimp
argument_list|,
name|palette
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pal
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|pal
operator|->
name|n_colors
operator|>
name|MAXNUMCOLORS
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_INVALID_ARGUMENT
argument_list|,
name|_
argument_list|(
literal|"Cannot convert to a palette "
literal|"with more than 256 colors."
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
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
name|success
operator|=
name|gimp_image_convert_indexed
argument_list|(
name|image
argument_list|,
name|palette_type
argument_list|,
name|num_cols
argument_list|,
name|remove_unused
argument_list|,
name|dither_type
argument_list|,
name|alpha_dither
argument_list|,
name|FALSE
argument_list|,
name|pal
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_convert_set_dither_matrix_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_convert_set_dither_matrix_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|matrix_length
decl_stmt|;
specifier|const
name|guint8
modifier|*
name|matrix
decl_stmt|;
name|width
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|matrix_length
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
name|matrix
operator|=
name|gimp_value_get_uint8_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|width
operator|==
literal|0
operator|||
name|height
operator|==
literal|0
operator|||
name|matrix_length
operator|==
name|width
operator|*
name|height
condition|)
block|{
name|gimp_image_convert_indexed_set_dither_matrix
argument_list|(
name|matrix
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_INVALID_ARGUMENT
argument_list|,
literal|"Dither matrix length must be width * height"
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_convert_precision_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_convert_precision_invoker
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gint
name|precision
decl_stmt|;
name|image
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|precision
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp_pdb_image_is_not_base_type
argument_list|(
name|image
argument_list|,
name|GIMP_INDEXED
argument_list|,
name|error
argument_list|)
operator|&&
name|gimp_pdb_image_is_not_precision
argument_list|(
name|image
argument_list|,
name|precision
argument_list|,
name|error
argument_list|)
operator|&&
name|gimp_babl_is_valid
argument_list|(
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
argument_list|,
name|precision
argument_list|)
condition|)
block|{
name|gimp_image_convert_precision
argument_list|(
name|image
argument_list|,
name|precision
argument_list|,
name|GEGL_DITHER_NONE
argument_list|,
name|GEGL_DITHER_NONE
argument_list|,
name|GEGL_DITHER_NONE
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_image_convert_procs (GimpPDB * pdb)
name|register_image_convert_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
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
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-convert-rgb"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Convert specified image to RGB color"
argument_list|,
literal|"This procedure converts the specified image to RGB color. This process requires an image in Grayscale or Indexed color mode. No image content is lost in this process aside from the colormap for an indexed image."
argument_list|,
name|NULL
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
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
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
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-convert-grayscale"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Convert specified image to grayscale"
argument_list|,
literal|"This procedure converts the specified image to grayscale. This process requires an image in RGB or Indexed color mode."
argument_list|,
name|NULL
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
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
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
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-convert-indexed"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Convert specified image to and Indexed image"
argument_list|,
literal|"This procedure converts the specified image to 'indexed' color. This process requires an image in RGB or Grayscale mode. The 'palette_type' specifies what kind of palette to use, A type of '0' means to use an optimal palette of 'num_cols' generated from the colors in the image. A type of '1' means to re-use the previous palette (not currently implemented). A type of '2' means to use the so-called WWW-optimized palette. Type '3' means to use only black and white colors. A type of '4' means to use a palette from the gimp palettes directories. The 'dither type' specifies what kind of dithering to use. '0' means no dithering, '1' means standard Floyd-Steinberg error diffusion, '2' means Floyd-Steinberg error diffusion with reduced bleeding, '3' means dithering based on pixel location ('Fixed' dithering)."
argument_list|,
name|NULL
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
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
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
name|g_param_spec_enum
argument_list|(
literal|"dither-type"
argument_list|,
literal|"dither type"
argument_list|,
literal|"The dither type to use"
argument_list|,
name|GIMP_TYPE_CONVERT_DITHER_TYPE
argument_list|,
name|GIMP_CONVERT_DITHER_NONE
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
literal|"The type of palette to use"
argument_list|,
name|GIMP_TYPE_CONVERT_PALETTE_TYPE
argument_list|,
name|GIMP_CONVERT_PALETTE_GENERATE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-cols"
argument_list|,
literal|"num cols"
argument_list|,
literal|"The number of colors to quantize to, ignored unless (palette_type == GIMP_CONVERT_PALETTE_GENERATE)"
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
literal|"Remove unused or duplicate color entries from final palette, ignored if (palette_type == GIMP_CONVERT_PALETTE_GENERATE)"
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
literal|"The name of the custom palette to use, ignored unless (palette_type == GIMP_CONVERT_PALETTE_CUSTOM)"
argument_list|,
name|FALSE
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
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-image-convert-set-dither-matrix    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_convert_set_dither_matrix_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-convert-set-dither-matrix"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Set dither matrix for conversion to indexed"
argument_list|,
literal|"This procedure sets the dither matrix used when converting images to INDEXED mode with positional dithering."
argument_list|,
name|NULL
argument_list|,
literal|"David Gowers"
argument_list|,
literal|"David Gowers"
argument_list|,
literal|"2006"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"Width of the matrix (0 to reset to default matrix)"
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
name|g_param_spec_int
argument_list|(
literal|"height"
argument_list|,
literal|"height"
argument_list|,
literal|"Height of the matrix (0 to reset to default matrix)"
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
name|g_param_spec_int
argument_list|(
literal|"matrix-length"
argument_list|,
literal|"matrix length"
argument_list|,
literal|"The length of 'matrix'"
argument_list|,
literal|1
argument_list|,
literal|1024
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_uint8_array
argument_list|(
literal|"matrix"
argument_list|,
literal|"matrix"
argument_list|,
literal|"The matrix -- all values must be>= 1"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-image-convert-precision    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_convert_precision_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-convert-precision"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Convert the image to the specified precision"
argument_list|,
literal|"This procedure converts the image to the specified precision. Note that indexed images cannot be converted and are always in GIMP_PRECISION_U8."
argument_list|,
name|NULL
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2012"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"image"
argument_list|,
literal|"The image"
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
name|g_param_spec_enum
argument_list|(
literal|"precision"
argument_list|,
literal|"precision"
argument_list|,
literal|"The new precision"
argument_list|,
name|GIMP_TYPE_PRECISION
argument_list|,
name|GIMP_PRECISION_U8_LINEAR
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

