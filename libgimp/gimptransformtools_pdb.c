begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimptransformtools_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
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
comment|/**  * gimp_flip:  * @drawable_ID: The affected drawable.  * @flip_type: Type of flip.  *  * This procedure is deprecated! Use  * gimp_drawable_transform_flip_simple() instead.  *  * Returns: The flipped drawable.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_flip (gint32 drawable_ID,GimpOrientationType flip_type)
name|gimp_flip
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|ret_drawable_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-flip"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|flip_type
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|ret_drawable_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|ret_drawable_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_perspective:  * @drawable_ID: The affected drawable.  * @interpolation: Whether to use interpolation.  * @x0: The new x coordinate of upper-left corner of original bounding box.  * @y0: The new y coordinate of upper-left corner of original bounding box.  * @x1: The new x coordinate of upper-right corner of original bounding box.  * @y1: The new y coordinate of upper-right corner of original bounding box.  * @x2: The new x coordinate of lower-left corner of original bounding box.  * @y2: The new y coordinate of lower-left corner of original bounding box.  * @x3: The new x coordinate of lower-right corner of original bounding box.  * @y3: The new y coordinate of lower-right corner of original bounding box.  *  * This procedure is deprecated! Use  * gimp_drawable_transform_perspective_default() instead.  *  * Returns: The newly mapped drawable.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_perspective (gint32 drawable_ID,gboolean interpolation,gdouble x0,gdouble y0,gdouble x1,gdouble y1,gdouble x2,gdouble y2,gdouble x3,gdouble y3)
name|gimp_perspective
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
name|x3
parameter_list|,
name|gdouble
name|y3
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|ret_drawable_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-perspective"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x0
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y0
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x1
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y1
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x2
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y2
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x3
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y3
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|ret_drawable_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|ret_drawable_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_rotate:  * @drawable_ID: The affected drawable.  * @interpolation: Whether to use interpolation.  * @angle: The angle of rotation (radians).  *  * This procedure is deprecated! Use  * gimp_drawable_transform_rotate_default() instead.  *  * Returns: The rotated drawable.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_rotate (gint32 drawable_ID,gboolean interpolation,gdouble angle)
name|gimp_rotate
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|ret_drawable_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-rotate"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|angle
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|ret_drawable_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|ret_drawable_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_scale:  * @drawable_ID: The affected drawable.  * @interpolation: Whether to use interpolation.  * @x0: The new x coordinate of upper-left corner of newly scaled region.  * @y0: The new y coordinate of upper-left corner of newly scaled region.  * @x1: The new x coordinate of lower-right corner of newly scaled region.  * @y1: The new y coordinate of lower-right corner of newly scaled region.  *  * This procedure is deprecated! Use  * gimp_drawable_transform_scale_default() instead.  *  * Returns: The scaled drawable.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_scale (gint32 drawable_ID,gboolean interpolation,gdouble x0,gdouble y0,gdouble x1,gdouble y1)
name|gimp_scale
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|ret_drawable_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-scale"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x0
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y0
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|x1
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|y1
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|ret_drawable_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|ret_drawable_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_shear:  * @drawable_ID: The affected drawable.  * @interpolation: Whether to use interpolation.  * @shear_type: Type of shear.  * @magnitude: The magnitude of the shear.  *  * This procedure is deprecated! Use  * gimp_drawable_transform_shear_default() instead.  *  * Returns: The sheared drawable.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_shear (gint32 drawable_ID,gboolean interpolation,GimpOrientationType shear_type,gdouble magnitude)
name|gimp_shear
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|GimpOrientationType
name|shear_type
parameter_list|,
name|gdouble
name|magnitude
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|ret_drawable_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-shear"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|shear_type
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|magnitude
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|ret_drawable_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|ret_drawable_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_transform_2d:  * @drawable_ID: The affected drawable.  * @interpolation: Whether to use interpolation.  * @source_x: X coordinate of the transformation center.  * @source_y: Y coordinate of the transformation center.  * @scale_x: Amount to scale in x direction.  * @scale_y: Amount to scale in y direction.  * @angle: The angle of rotation (radians).  * @dest_x: X coordinate of where the centre goes.  * @dest_y: Y coordinate of where the centre goes.  *  * This procedure is deprecated! Use  * gimp_drawable_transform_2d_default() instead.  *  * Returns: The transformed drawable.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_transform_2d (gint32 drawable_ID,gboolean interpolation,gdouble source_x,gdouble source_y,gdouble scale_x,gdouble scale_y,gdouble angle,gdouble dest_x,gdouble dest_y)
name|gimp_transform_2d
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|interpolation
parameter_list|,
name|gdouble
name|source_x
parameter_list|,
name|gdouble
name|source_y
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|dest_x
parameter_list|,
name|gdouble
name|dest_y
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint32
name|ret_drawable_ID
init|=
operator|-
literal|1
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-transform-2d"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|source_x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|source_y
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|scale_x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|scale_y
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|angle
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|dest_x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|dest_y
argument_list|,
name|GIMP_PDB_END
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
name|GIMP_PDB_SUCCESS
condition|)
name|ret_drawable_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|ret_drawable_ID
return|;
block|}
end_function

end_unit

