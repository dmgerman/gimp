begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdrawabletransform_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
comment|/**  * gimp_drawable_transform_flip:  * @drawable_ID: The affected drawable.  * @flip_type: Type of flip.  * @center: Whether to automatically position the axis in the image center.  * @axis: coord. of flip axis.  * @transform_direction: Direction of Transformation.  * @interpolation: Type of interpolation.  * @supersample: Whether to perform supersample.  * @recursion_level: Level of recursion (3 is a nice default).  * @clip_result: Whether to clip results.  *  * Flip the specified drawable either vertically or horizontally.  *  * This tool flips the specified drawable if no selection exists. If a  * selection exists, the portion of the drawable which lies under the  * selection is cut from the drawable and made into a floating  * selection which is then flipped. If center is set to true, the flip  * is around the image center. Otherwise, the coordinate of the axis  * needs to be specified. The return value is the ID of the flipped  * drawable. If there was no selection, this will be equal to the  * drawable ID supplied as input. Otherwise, this will be the newly  * created and flipped drawable.  *  * Returns: The flipped drawable.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_transform_flip (gint32 drawable_ID,GimpOrientationType flip_type,gboolean center,gdouble axis,GimpTransformDirection transform_direction,GimpInterpolationType interpolation,gboolean supersample,gint recursion_level,gboolean clip_result)
name|gimp_drawable_transform_flip
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gboolean
name|center
parameter_list|,
name|gdouble
name|axis
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
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
literal|"gimp_drawable_transform_flip"
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
name|GIMP_PDB_INT32
argument_list|,
name|center
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|axis
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|transform_direction
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|recursion_level
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|clip_result
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
comment|/**  * gimp_drawable_transform_flip_free:  * @drawable_ID: The affected drawable.  * @x1: horz. coord. of one end of axis.  * @y1: vert. coord. of one end of axis.  * @x2: horz. coord. of other end of axis.  * @y2: vert. coord. of other end of axis.  * @transform_direction: Direction of Transformation.  * @interpolation: Type of interpolation.  * @supersample: Whether to perform supersample.  * @recursion_level: Level of recursion (3 is a nice default).  * @clip_result: Whether to clip results.  *  * Flip the specified drawable around a given line.  *  * This tool flips the specified drawable if no selection exists. If a  * selection exists, the portion of the drawable which lies under the  * selection is cut from the drawable and made into a floating  * selection which is then flipped. The axis to flip around is  * specified by specifying two points from that line. The return value  * is the ID of the flipped drawable. If there was no selection, this  * will be equal to the drawable ID supplied as input. Otherwise, this  * will be the newly created and flipped drawable. The clip results  * parameter specifies wheter current selection will affect the  * transform.  *  * Returns: The flipped drawable.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_transform_flip_free (gint32 drawable_ID,gdouble x1,gdouble y1,gdouble x2,gdouble y2,GimpTransformDirection transform_direction,GimpInterpolationType interpolation,gboolean supersample,gint recursion_level,gboolean clip_result)
name|gimp_drawable_transform_flip_free
parameter_list|(
name|gint32
name|drawable_ID
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
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
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
literal|"gimp_drawable_transform_flip_free"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
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
name|GIMP_PDB_INT32
argument_list|,
name|transform_direction
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|recursion_level
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|clip_result
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
comment|/**  * gimp_drawable_transform_perspective:  * @drawable_ID: The affected drawable.  * @x0: The new x coordinate of upper-left corner of original bounding box.  * @y0: The new y coordinate of upper-left corner of original bounding box.  * @x1: The new x coordinate of upper-right corner of original bounding box.  * @y1: The new y coordinate of upper-right corner of original bounding box.  * @x2: The new x coordinate of lower-left corner of original bounding box.  * @y2: The new y coordinate of lower-left corner of original bounding box.  * @x3: The new x coordinate of lower-right corner of original bounding box.  * @y3: The new y coordinate of lower-right corner of original bounding box.  * @transform_direction: Direction of Transformation.  * @interpolation: Type of interpolation.  * @supersample: Whether to perform supersample.  * @recursion_level: Level of recursion (3 is a nice default).  * @clip_result: Whether to clip results.  *  * Perform a possibly non-affine transformation on the specified  * drawable, with extra parameters.  *  * This tool performs a possibly non-affine transformation on the  * specified drawable by allowing the corners of the original bounding  * box to be arbitrarily remapped to any values. The specified drawable  * is remapped if no selection exists. However, if a selection exists,  * the portion of the drawable which lies under the selection is cut  * from the drawable and made into a floating selection which is then  * remapped as specified. The return value is the ID of the remapped  * drawable. If there was no selection, this will be equal to the  * drawable ID supplied as input. Otherwise, this will be the newly  * created and remapped drawable. The 4 coordinates specify the new  * locations of each corner of the original bounding box. By specifying  * these values, any affine transformation (rotation, scaling,  * translation) can be affected. Additionally, these values can be  * specified such that the resulting transformed drawable will appear  * to have been projected via a perspective transform.  *  * Returns: The newly mapped drawable.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_transform_perspective (gint32 drawable_ID,gdouble x0,gdouble y0,gdouble x1,gdouble y1,gdouble x2,gdouble y2,gdouble x3,gdouble y3,GimpTransformDirection transform_direction,GimpInterpolationType interpolation,gboolean supersample,gint recursion_level,gboolean clip_result)
name|gimp_drawable_transform_perspective
parameter_list|(
name|gint32
name|drawable_ID
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
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
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
literal|"gimp_drawable_transform_perspective"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
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
name|GIMP_PDB_INT32
argument_list|,
name|transform_direction
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|recursion_level
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|clip_result
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
comment|/**  * gimp_drawable_transform_rotate:  * @drawable_ID: The affected drawable.  * @angle: The angle of rotation (radians).  * @cx: The hor. coordinate of the center of rotation.  * @cy: The vert. coordinate of the center of rotation.  * @transform_direction: Direction of Transformation.  * @interpolation: Type of interpolation.  * @supersample: Whether to perform supersample.  * @recursion_level: Level of recursion (3 is a nice default).  * @clip_result: Whether to clip results.  *  * Rotate the specified drawable about given coordinates through the  * specified angle.  *  * This tool rotates the specified drawable if no selection exists. If  * a selection exists, the portion of the drawable which lies under the  * selection is cut from the drawable and made into a floating  * selection which is then rotated by the specified amount. The return  * value is the ID of the rotated drawable. If there was no selection,  * this will be equal to the drawable ID supplied as input. Otherwise,  * this will be the newly created and rotated drawable.  *  * Returns: The rotated drawable.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_transform_rotate (gint32 drawable_ID,gdouble angle,gint cx,gint cy,GimpTransformDirection transform_direction,GimpInterpolationType interpolation,gboolean supersample,gint recursion_level,gboolean clip_result)
name|gimp_drawable_transform_rotate
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gint
name|cx
parameter_list|,
name|gint
name|cy
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
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
literal|"gimp_drawable_transform_rotate"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|angle
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|cx
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|cy
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|transform_direction
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|recursion_level
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|clip_result
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
comment|/**  * gimp_drawable_transform_scale:  * @drawable_ID: The affected drawable.  * @x0: The new x coordinate of upper-left corner of newly scaled region.  * @y0: The new y coordinate of upper-left corner of newly scaled region.  * @x1: The new x coordinate of lower-right corner of newly scaled region.  * @y1: The new y coordinate of lower-right corner of newly scaled region.  * @transform_direction: Direction of Transformation.  * @interpolation: Type of interpolation.  * @supersample: Whether to perform supersample.  * @recursion_level: Level of recursion (3 is a nice default).  * @clip_result: Whether to clip results.  *  * Scale the specified drawable with extra parameters  *  * This tool scales the specified drawable if no selection exists. If a  * selection exists, the portion of the drawable which lies under the  * selection is cut from the drawable and made into a floating  * selection which is then scaled by the specified amount. The return  * value is the ID of the scaled drawable. If there was no selection,  * this will be equal to the drawable ID supplied as input. Otherwise,  * this will be the newly created and scaled drawable.  *  * Returns: The scaled drawable.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_transform_scale (gint32 drawable_ID,gdouble x0,gdouble y0,gdouble x1,gdouble y1,GimpTransformDirection transform_direction,GimpInterpolationType interpolation,gboolean supersample,gint recursion_level,gboolean clip_result)
name|gimp_drawable_transform_scale
parameter_list|(
name|gint32
name|drawable_ID
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
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
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
literal|"gimp_drawable_transform_scale"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
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
name|GIMP_PDB_INT32
argument_list|,
name|transform_direction
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|recursion_level
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|clip_result
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
comment|/**  * gimp_drawable_transform_shear:  * @drawable_ID: The affected drawable.  * @shear_type: Type of shear.  * @magnitude: The magnitude of the shear.  * @transform_direction: Direction of Transformation.  * @interpolation: Type of interpolation.  * @supersample: Whether to perform supersample.  * @recursion_level: Level of recursion (3 is a nice default).  * @clip_result: Whether to clip results.  *  * Shear the specified drawable about its center by the specified  * magnitude, with extra parameters.  *  * This tool shears the specified drawable if no selection exists. If a  * selection exists, the portion of the drawable which lies under the  * selection is cut from the drawable and made into a floating  * selection which is then sheard by the specified amount. The return  * value is the ID of the sheard drawable. If there was no selection,  * this will be equal to the drawable ID supplied as input. Otherwise,  * this will be the newly created and sheard drawable. The shear type  * parameter indicates whether the shear will be applied horizontally  * or vertically. The magnitude can be either positive or negative and  * indicates the extent (in pixels) to shear by.  *  * Returns: The sheared drawable.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_transform_shear (gint32 drawable_ID,GimpOrientationType shear_type,gdouble magnitude,GimpTransformDirection transform_direction,GimpInterpolationType interpolation,gboolean supersample,gint recursion_level,gboolean clip_result)
name|gimp_drawable_transform_shear
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|GimpOrientationType
name|shear_type
parameter_list|,
name|gdouble
name|magnitude
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
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
literal|"gimp_drawable_transform_shear"
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
name|shear_type
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|magnitude
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|transform_direction
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|recursion_level
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|clip_result
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
comment|/**  * gimp_drawable_transform_2d:  * @drawable_ID: The affected drawable.  * @source_x: X coordinate of the transformation center.  * @source_y: Y coordinate of the transformation center.  * @scale_x: Amount to scale in x direction.  * @scale_y: Amount to scale in y direction.  * @angle: The angle of rotation (radians).  * @dest_x: X coordinate of where the center goes.  * @dest_y: Y coordinate of where the center goes.  * @transform_direction: Direction of Transformation.  * @interpolation: Type of interpolation.  * @supersample: Whether to perform supersample.  * @recursion_level: Level of recursion (3 is a nice default).  * @clip_result: Whether to clip results.  *  * Transform the specified drawable in 2d, with extra parameters.  *  * This tool transforms the specified drawable if no selection exists.  * If a selection exists, the portion of the drawable which lies under  * the selection is cut from the drawable and made into a floating  * selection which is then transformed. The transformation is done by  * scaling the image by the x and y scale factors about the point  * (source_x, source_y), then rotating around the same point, then  * translating that point to the new position (dest_x, dest_y). The  * return value is the ID of the rotated drawable. If there was no  * selection, this will be equal to the drawable ID supplied as input.  * Otherwise, this will be the newly created and transformed drawable.  *  * Returns: The transformed drawable.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gint32
DECL|function|gimp_drawable_transform_2d (gint32 drawable_ID,gdouble source_x,gdouble source_y,gdouble scale_x,gdouble scale_y,gdouble angle,gdouble dest_x,gdouble dest_y,GimpTransformDirection transform_direction,GimpInterpolationType interpolation,gboolean supersample,gint recursion_level,gboolean clip_result)
name|gimp_drawable_transform_2d
parameter_list|(
name|gint32
name|drawable_ID
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
parameter_list|,
name|GimpTransformDirection
name|transform_direction
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|gboolean
name|clip_result
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
literal|"gimp_drawable_transform_2d"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
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
name|GIMP_PDB_INT32
argument_list|,
name|transform_direction
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|interpolation
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|supersample
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|recursion_level
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|clip_result
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

