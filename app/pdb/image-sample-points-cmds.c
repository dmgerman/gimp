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
file|"core/gimpimage-sample-points.h"
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
file|"core/gimpsamplepoint.h"
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
DECL|function|image_add_sample_point_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_add_sample_point_invoker
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
name|position_x
decl_stmt|;
name|gint
name|position_y
decl_stmt|;
name|guint
name|sample_point
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
name|position_x
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
name|position_y
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
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|position_x
operator|<=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|&&
name|position_y
operator|<=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|GimpSamplePoint
modifier|*
name|sp
decl_stmt|;
name|sp
operator|=
name|gimp_image_add_sample_point_at_pos
argument_list|(
name|image
argument_list|,
name|position_x
argument_list|,
name|position_y
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|sample_point
operator|=
name|gimp_aux_item_get_ID
argument_list|(
name|GIMP_AUX_ITEM
argument_list|(
name|sp
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
name|sample_point
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
DECL|function|image_delete_sample_point_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_delete_sample_point_invoker
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
name|sample_point
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
name|sample_point
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
name|GimpSamplePoint
modifier|*
name|sp
init|=
name|gimp_pdb_image_get_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|sp
condition|)
name|gimp_image_remove_sample_point
argument_list|(
name|image
argument_list|,
name|sp
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
DECL|function|image_find_next_sample_point_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_find_next_sample_point_invoker
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
name|sample_point
decl_stmt|;
name|guint
name|next_sample_point
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
name|sample_point
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
name|GimpSamplePoint
modifier|*
name|sp
init|=
name|gimp_image_get_next_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
operator|&
name|success
argument_list|)
decl_stmt|;
if|if
condition|(
name|sp
condition|)
name|next_sample_point
operator|=
name|gimp_aux_item_get_ID
argument_list|(
name|GIMP_AUX_ITEM
argument_list|(
name|sp
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
literal|"Image '%s' (%d) does not contain sample point with ID %d"
argument_list|)
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|image
argument_list|)
argument_list|,
name|sample_point
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
name|next_sample_point
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
DECL|function|image_get_sample_point_position_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|image_get_sample_point_position_invoker
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
name|sample_point
decl_stmt|;
name|gint
name|position_x
init|=
literal|0
decl_stmt|;
name|gint
name|position_y
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
name|sample_point
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
name|GimpSamplePoint
modifier|*
name|sp
init|=
name|gimp_pdb_image_get_sample_point
argument_list|(
name|image
argument_list|,
name|sample_point
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|sp
condition|)
name|gimp_sample_point_get_position
argument_list|(
name|sp
argument_list|,
operator|&
name|position_x
argument_list|,
operator|&
name|position_y
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
block|{
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|position_x
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|,
name|position_y
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_image_sample_points_procs (GimpPDB * pdb)
name|register_image_sample_points_procs
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
comment|/*    * gimp-image-add-sample-point    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_add_sample_point_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-add-sample-point"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-image-add-sample-point"
argument_list|,
literal|"Add a sample point to an image."
argument_list|,
literal|"This procedure adds a sample point to an image. It takes the input image and the position of the new sample points as parameters. It returns the sample point ID of the new sample point."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2016"
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
literal|"position-x"
argument_list|,
literal|"position x"
argument_list|,
literal|"The guide'sample points x-offset from left of image"
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"position-y"
argument_list|,
literal|"position y"
argument_list|,
literal|"The guide'sample points y-offset from top of image"
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
literal|"sample-point"
argument_list|,
literal|"sample point"
argument_list|,
literal|"The new sample point"
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
comment|/*    * gimp-image-delete-sample-point    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_delete_sample_point_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-delete-sample-point"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-image-delete-sample-point"
argument_list|,
literal|"Deletes a sample point from an image."
argument_list|,
literal|"This procedure takes an image and a sample point ID as input and removes the specified sample point from the specified image."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2016"
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
literal|"sample-point"
argument_list|,
literal|"sample point"
argument_list|,
literal|"The ID of the sample point to be removed"
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
comment|/*    * gimp-image-find-next-sample-point    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_find_next_sample_point_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-find-next-sample-point"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-image-find-next-sample-point"
argument_list|,
literal|"Find next sample point on an image."
argument_list|,
literal|"This procedure takes an image and a sample point ID as input and finds the sample point ID of the successor of the given sample point ID in the image's sample point list. If the supplied sample point ID is 0, the procedure will return the first sample point. The procedure will return 0 if given the final sample point ID as an argument or the image has no sample points."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2016"
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
literal|"sample-point"
argument_list|,
literal|"sample point"
argument_list|,
literal|"The ID of the current sample point (0 if first invocation)"
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
literal|"next-sample-point"
argument_list|,
literal|"next sample point"
argument_list|,
literal|"The next sample point's ID"
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
comment|/*    * gimp-image-get-sample-point-position    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|image_get_sample_point_position_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-image-get-sample-point-position"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-image-get-sample-point-position"
argument_list|,
literal|"Get position of a sample point on an image."
argument_list|,
literal|"This procedure takes an image and a sample point ID as input and returns the position of the sample point relative to the top and left of the image."
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2016"
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
literal|"sample-point"
argument_list|,
literal|"sample point"
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
literal|"position-x"
argument_list|,
literal|"position x"
argument_list|,
literal|"The sample points's position relative to top of image"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"position-y"
argument_list|,
literal|"position y"
argument_list|,
literal|"The sample points's position relative to top of image"
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

