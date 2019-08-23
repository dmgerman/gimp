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
file|"cairo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpguide.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
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
DECL|function|image_add_hguide_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_add_hguide_invoker
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
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|yposition
decl_stmt|;
name|guint
name|guide
init|=
literal|0
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|yposition
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
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|yposition
operator|<=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|GimpGuide
modifier|*
name|g
decl_stmt|;
name|g
operator|=
name|gimp_image_add_hguide
argument_list|(
name|image
argument_list|,
name|yposition
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|guide
operator|=
name|gimp_aux_item_get_id
argument_list|(
name|GIMP_AUX_ITEM
argument_list|(
name|g
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_add_vguide_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_add_vguide_invoker
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
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|xposition
decl_stmt|;
name|guint
name|guide
init|=
literal|0
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|xposition
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
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|xposition
operator|<=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|GimpGuide
modifier|*
name|g
decl_stmt|;
name|g
operator|=
name|gimp_image_add_vguide
argument_list|(
name|image
argument_list|,
name|xposition
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|guide
operator|=
name|gimp_aux_item_get_id
argument_list|(
name|GIMP_AUX_ITEM
argument_list|(
name|g
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_delete_guide_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_delete_guide_invoker
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
name|guint
name|guide
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|guide
operator|=
name|g_value_get_uint
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
name|GimpGuide
modifier|*
name|g
init|=
name|gimp_pdb_image_get_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|g
condition|)
name|gimp_image_remove_guide
argument_list|(
name|image
argument_list|,
name|g
argument_list|,
name|TRUE
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
DECL|function|image_find_next_guide_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_find_next_guide_invoker
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
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|guint
name|guide
decl_stmt|;
name|guint
name|next_guide
init|=
literal|0
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|guide
operator|=
name|g_value_get_uint
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
name|GimpGuide
modifier|*
name|g
init|=
name|gimp_image_get_next_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
operator|&
name|success
argument_list|)
decl_stmt|;
if|if
condition|(
name|g
condition|)
name|next_guide
operator|=
name|gimp_aux_item_get_id
argument_list|(
name|GIMP_AUX_ITEM
argument_list|(
name|g
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_ERROR_INVALID_ARGUMENT
argument_list|,
name|_
argument_list|(
literal|"Image '%s' (%d) does not contain guide with ID %d"
argument_list|)
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|,
name|guide
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_uint
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|next_guide
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_get_guide_orientation_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_get_guide_orientation_invoker
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
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|guint
name|guide
decl_stmt|;
name|gint
name|orientation
init|=
literal|0
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|guide
operator|=
name|g_value_get_uint
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
name|GimpGuide
modifier|*
name|g
init|=
name|gimp_pdb_image_get_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|g
condition|)
name|orientation
operator|=
name|gimp_guide_get_orientation
argument_list|(
name|g
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|orientation
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|image_get_guide_position_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_get_guide_position_invoker
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
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|guint
name|guide
decl_stmt|;
name|gint
name|position
init|=
literal|0
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|guide
operator|=
name|g_value_get_uint
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
name|GimpGuide
modifier|*
name|g
init|=
name|gimp_pdb_image_get_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|g
condition|)
name|position
operator|=
name|gimp_guide_get_position
argument_list|(
name|g
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
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
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|position
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_image_guides_procs (GimpPDB * pdb)
name|register_image_guides_procs
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
comment|/*    * gimp-image-add-hguide    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_add_hguide_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-add-hguide"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Add a horizontal guide to an image."
argument_list|,
literal|"This procedure adds a horizontal guide to an image. It takes the input image and the y-position of the new guide as parameters. It returns the guide ID of the new guide."
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1998"
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
name|pdb
operator|->
name|gimp
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
name|g_param_spec_int
argument_list|(
literal|"yposition"
argument_list|,
literal|"yposition"
argument_list|,
literal|"The guide's y-offset from top of image"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_uint
argument_list|(
literal|"guide"
argument_list|,
literal|"guide"
argument_list|,
literal|"The new guide"
argument_list|,
literal|1
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|1
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
comment|/*    * gimp-image-add-vguide    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_add_vguide_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-add-vguide"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Add a vertical guide to an image."
argument_list|,
literal|"This procedure adds a vertical guide to an image. It takes the input image and the x-position of the new guide as parameters. It returns the guide ID of the new guide."
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1998"
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
name|pdb
operator|->
name|gimp
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
name|g_param_spec_int
argument_list|(
literal|"xposition"
argument_list|,
literal|"xposition"
argument_list|,
literal|"The guide's x-offset from left of image"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_uint
argument_list|(
literal|"guide"
argument_list|,
literal|"guide"
argument_list|,
literal|"The new guide"
argument_list|,
literal|1
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|1
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
comment|/*    * gimp-image-delete-guide    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_delete_guide_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-delete-guide"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Deletes a guide from an image."
argument_list|,
literal|"This procedure takes an image and a guide ID as input and removes the specified guide from the specified image."
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1998"
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
name|pdb
operator|->
name|gimp
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
name|g_param_spec_uint
argument_list|(
literal|"guide"
argument_list|,
literal|"guide"
argument_list|,
literal|"The ID of the guide to be removed"
argument_list|,
literal|1
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|1
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
comment|/*    * gimp-image-find-next-guide    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_find_next_guide_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-find-next-guide"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Find next guide on an image."
argument_list|,
literal|"This procedure takes an image and a guide ID as input and finds the guide ID of the successor of the given guide ID in the image's guide list. If the supplied guide ID is 0, the procedure will return the first Guide. The procedure will return 0 if given the final guide ID as an argument or the image has no guides."
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1998"
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
name|pdb
operator|->
name|gimp
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
name|g_param_spec_uint
argument_list|(
literal|"guide"
argument_list|,
literal|"guide"
argument_list|,
literal|"The ID of the current guide (0 if first invocation)"
argument_list|,
literal|1
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_uint
argument_list|(
literal|"next-guide"
argument_list|,
literal|"next guide"
argument_list|,
literal|"The next guide's ID"
argument_list|,
literal|1
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|1
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
comment|/*    * gimp-image-get-guide-orientation    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_get_guide_orientation_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-get-guide-orientation"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Get orientation of a guide on an image."
argument_list|,
literal|"This procedure takes an image and a guide ID as input and returns the orientations of the guide."
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1998"
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
name|pdb
operator|->
name|gimp
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
name|g_param_spec_uint
argument_list|(
literal|"guide"
argument_list|,
literal|"guide"
argument_list|,
literal|"The guide"
argument_list|,
literal|1
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"orientation"
argument_list|,
literal|"orientation"
argument_list|,
literal|"The guide's orientation"
argument_list|,
name|GIMP_TYPE_ORIENTATION_TYPE
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_param_spec_enum_exclude_value
argument_list|(
name|GIMP_PARAM_SPEC_ENUM
argument_list|(
name|procedure
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|GIMP_ORIENTATION_UNKNOWN
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
comment|/*    * gimp-image-get-guide-position    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_get_guide_position_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-get-guide-position"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Get position of a guide on an image."
argument_list|,
literal|"This procedure takes an image and a guide ID as input and returns the position of the guide relative to the top or left of the image."
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1998"
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
name|pdb
operator|->
name|gimp
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
name|g_param_spec_uint
argument_list|(
literal|"guide"
argument_list|,
literal|"guide"
argument_list|,
literal|"The guide"
argument_list|,
literal|1
argument_list|,
name|G_MAXUINT32
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"position"
argument_list|,
literal|"position"
argument_list|,
literal|"The guide's position relative to top or left of image"
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

