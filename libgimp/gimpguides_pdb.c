begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpguides_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
DECL|function|gimp_image_add_hguide (gint32 image_ID,gint yposition)
name|gimp_image_add_hguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|yposition
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|guide_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_image_add_hguide"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|yposition
argument_list|,
name|PARAM_END
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
name|STATUS_SUCCESS
condition|)
name|guide_ID
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|guide_ID
return|;
block|}
end_function

begin_function
name|gint32
DECL|function|gimp_image_add_vguide (gint32 image_ID,gint xposition)
name|gimp_image_add_vguide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|xposition
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|guide_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_image_add_vguide"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|xposition
argument_list|,
name|PARAM_END
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
name|STATUS_SUCCESS
condition|)
name|guide_ID
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|guide_ID
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_delete_guide (gint32 image_ID,gint32 guide_ID)
name|gimp_image_delete_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
block|{
name|GParam
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
literal|"gimp_image_delete_guide"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|guide_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
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
DECL|function|gimp_image_find_next_guide (gint32 image_ID,gint32 guide_ID)
name|gimp_image_find_next_guide
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|next_guide_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_image_find_next_guide"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|guide_ID
argument_list|,
name|PARAM_END
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
name|STATUS_SUCCESS
condition|)
name|next_guide_ID
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|next_guide_ID
return|;
block|}
end_function

begin_function
name|GimpOrientationType
DECL|function|gimp_image_get_guide_orientation (gint32 image_ID,gint32 guide_ID)
name|gimp_image_get_guide_orientation
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|GimpOrientationType
name|orientation
init|=
name|GIMP_UNKNOWN
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_image_get_guide_orientation"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|guide_ID
argument_list|,
name|PARAM_END
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
name|STATUS_SUCCESS
condition|)
name|orientation
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|orientation
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_image_get_guide_position (gint32 image_ID,gint32 guide_ID)
name|gimp_image_get_guide_position
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|guide_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|position
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_image_get_guide_position"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|guide_ID
argument_list|,
name|PARAM_END
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
name|STATUS_SUCCESS
condition|)
name|position
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
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|position
return|;
block|}
end_function

end_unit

