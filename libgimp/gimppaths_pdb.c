begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimppaths_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_path_list:  * @image_ID: The ID of the image to list the paths from.  * @num_paths: The number of paths returned.  *  * This procedure is deprecated! Use gimp_image_get_vectors() instead.  *  * Returns: List of the paths belonging to this image.  */
end_comment

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_path_list (gint32 image_ID,gint * num_paths)
name|gimp_path_list
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
modifier|*
name|num_paths
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|path_list
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-list"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_paths
operator|=
literal|0
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
block|{
operator|*
name|num_paths
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
name|path_list
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_paths
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_paths
condition|;
name|i
operator|++
control|)
name|path_list
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_stringarray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|path_list
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_get_current:  * @image_ID: The ID of the image to get the current path from.  *  * This procedure is deprecated! Use gimp_image_get_active_vectors()  * instead.  *  * Returns: The name of the current path.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_path_get_current (gint32 image_ID)
name|gimp_path_get_current
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-get-current"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
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
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_set_current:  * @image_ID: The ID of the image in which a path will become current.  * @name: The name of the path to make current.  *  * This procedure is deprecated! Use gimp_image_set_active_vectors()  * instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_current (gint32 image_ID,const gchar * name)
name|gimp_path_set_current
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-set-current"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_delete:  * @image_ID: The ID of the image to delete the path from.  * @name: The name of the path to delete.  *  * This procedure is deprecated! Use gimp_image_remove_vectors()  * instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_delete (gint32 image_ID,const gchar * name)
name|gimp_path_delete
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-delete"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_get_points:  * @image_ID: The ID of the image to list the paths from.  * @name: The name of the path whose points should be listed.  * @path_closed: Return if the path is closed. (0 = path open, 1 = path closed).  * @num_path_point_details: The number of points returned. Each point is made up of (x, y, pnt_type) of floats.  * @points_pairs: The points in the path represented as 3 floats. The first is the x pos, next is the y pos, last is the type of the pnt. The type field is dependant on the path type. For beziers (type 1 paths) the type can either be (1.0 = BEZIER_ANCHOR, 2.0 = BEZIER_CONTROL, 3.0 = BEZIER_MOVE). Note all points are returned in pixel resolution.  *  * List the points associated with the named path.  *  * List the points associated with the named path.  *  * Returns: The type of the path. Currently only one type (1 = Bezier) is supported.  */
end_comment

begin_function
name|gint
DECL|function|gimp_path_get_points (gint32 image_ID,const gchar * name,gint * path_closed,gint * num_path_point_details,gdouble ** points_pairs)
name|gimp_path_get_points
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|path_closed
parameter_list|,
name|gint
modifier|*
name|num_path_point_details
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|points_pairs
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|path_type
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-get-points"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_path_point_details
operator|=
literal|0
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
block|{
name|path_type
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
operator|*
name|path_closed
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|num_path_point_details
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|points_pairs
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
operator|*
name|num_path_point_details
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|points_pairs
argument_list|,
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_floatarray
argument_list|,
operator|*
name|num_path_point_details
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|path_type
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_set_points:  * @image_ID: The ID of the image to set the paths in.  * @name: The name of the path to create. If it exists then a unique name will be created - query the list of paths if you want to make sure that the name of the path you create is unique. This will be set as the current path.  * @ptype: The type of the path. Currently only one type (1 = Bezier) is supported.  * @num_path_points: The number of elements in the array, i.e. the number of points in the path * 3. Each point is made up of (x, y, type) of floats. Currently only the creation of bezier curves is allowed. The type parameter must be set to (1) to indicate a BEZIER type curve. Note that for BEZIER curves, points must be given in the following order: ACCACCAC... If the path is not closed the last control point is missed off. Points consist of three control points (control/anchor/control) so for a curve that is not closed there must be at least two points passed (2 x,y pairs). If (num_path_points/3) % 3 = 0 then the path is assumed to be closed and the points are ACCACCACCACC.  * @points_pairs: The points in the path represented as 3 floats. The first is the x pos, next is the y pos, last is the type of the pnt. The type field is dependant on the path type. For beziers (type 1 paths) the type can either be (1.0 = BEZIER_ANCHOR, 2.0 = BEZIER_CONTROL, 3.0= BEZIER_MOVE). Note all points are returned in pixel resolution.  *  * Set the points associated with the named path.  *  * Set the points associated with the named path.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_points (gint32 image_ID,const gchar * name,gint ptype,gint num_path_points,const gdouble * points_pairs)
name|gimp_path_set_points
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|ptype
parameter_list|,
name|gint
name|num_path_points
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|points_pairs
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-set-points"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|ptype
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|num_path_points
argument_list|,
name|GIMP_PDB_FLOATARRAY
argument_list|,
name|points_pairs
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_stroke_current:  * @image_ID: The ID of the image which contains the path to stroke.  *  * Stroke the current path in the passed image.  *  * Stroke the current path in the passed image.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_stroke_current (gint32 image_ID)
name|gimp_path_stroke_current
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-stroke-current"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_get_point_at_dist:  * @image_ID: The ID of the image the paths belongs to.  * @distance: The distance along the path.  * @y_point: The y position of the point.  * @slope: The slope (dy / dx) at the specified point.  *  * This procedure is deprecated! Use  * gimp_vectors_stroke_get_point_at_dist() instead.  *  * Returns: The x position of the point.  */
end_comment

begin_function
name|gint
DECL|function|gimp_path_get_point_at_dist (gint32 image_ID,gdouble distance,gint * y_point,gdouble * slope)
name|gimp_path_get_point_at_dist
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
name|distance
parameter_list|,
name|gint
modifier|*
name|y_point
parameter_list|,
name|gdouble
modifier|*
name|slope
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|x_point
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-get-point-at-dist"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|distance
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
block|{
name|x_point
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
operator|*
name|y_point
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|slope
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|x_point
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_get_tattoo:  * @image_ID: The image.  * @name: The name of the path whose tattoo should be obtained.  *  * This procedure is deprecated! Use gimp_vectors_get_tattoo() instead.  *  * Returns: The tattoo associated with the named path.  */
end_comment

begin_function
name|gint
DECL|function|gimp_path_get_tattoo (gint32 image_ID,const gchar * name)
name|gimp_path_get_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gint
name|tattoo
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-get-tattoo"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|tattoo
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
name|tattoo
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_set_tattoo:  * @image_ID: The image.  * @name: the name of the path whose tattoo should be set.  * @tattovalue: The tattoo associated with the name path. Only values returned from 'path_get_tattoo' should be used here.  *  * This procedure is deprecated! Use gimp_vectors_set_tattoo() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_tattoo (gint32 image_ID,const gchar * name,gint tattovalue)
name|gimp_path_set_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|tattovalue
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-set-tattoo"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|tattovalue
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_path_by_tattoo:  * @image_ID: The image.  * @tattoo: The tattoo of the required path.  *  * This procedure is deprecated! Use gimp_image_get_vectors_by_tattoo()  * instead.  *  * Returns: The name of the path with the specified tattoo.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_get_path_by_tattoo (gint32 image_ID,gint tattoo)
name|gimp_get_path_by_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|tattoo
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-get-path-by-tattoo"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|tattoo
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
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_get_locked:  * @image_ID: The image.  * @name: The name of the path whose locked status should be obtained.  *  * This procedure is deprecated! Use gimp_vectors_get_linked() instead.  *  * Returns: TRUE if the path is locked, FALSE otherwise.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_get_locked (gint32 image_ID,const gchar * name)
name|gimp_path_get_locked
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|locked
init|=
name|FALSE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-get-locked"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
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
name|locked
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
name|locked
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_set_locked:  * @image_ID: The image.  * @name: the name of the path whose locked status should be set.  * @locked: Whether the path is locked.  *  * This procedure is deprecated! Use gimp_vectors_set_linked() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_locked (gint32 image_ID,const gchar * name,gboolean locked)
name|gimp_path_set_locked
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|locked
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-set-locked"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|locked
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_to_selection:  * @image_ID: The image.  * @name: The name of the path which should be made into selection.  * @op: The desired operation with current selection.  * @antialias: Antialias selection.  * @feather: Feather selection.  * @feather_radius_x: Feather radius x.  * @feather_radius_y: Feather radius y.  *  * Transforms the active path into a selection  *  * This procedure renders the desired path into the current selection.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_to_selection (gint32 image_ID,const gchar * name,GimpChannelOps op,gboolean antialias,gboolean feather,gdouble feather_radius_x,gdouble feather_radius_y)
name|gimp_path_to_selection
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-to-selection"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|op
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|antialias
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|feather
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|feather_radius_x
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|feather_radius_y
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_import:  * @image_ID: The image.  * @filename: The name of the SVG file to import.  * @merge: Merge paths into a single vectors object.  * @scale: Scale the SVG to image dimensions.  *  * Import paths from an SVG file.  *  * This procedure imports paths from an SVG file. SVG elements other  * than paths and basic shapes are ignored.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_import (gint32 image_ID,const gchar * filename,gboolean merge,gboolean scale)
name|gimp_path_import
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|merge
parameter_list|,
name|gboolean
name|scale
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-import"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|filename
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|merge
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|scale
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_import_string:  * @image_ID: The image.  * @string: A string that must be a complete and valid SVG document.  * @length: Number of bytes in string or -1 if the string is NULL terminated.  * @merge: Merge paths into a single vectors object.  * @scale: Scale the SVG to image dimensions.  *  * Import paths from an SVG string.  *  * This procedure works like gimp_path_import() but takes a string  * rather than reading the SVG from a file. This allows you to write  * scripts that generate SVG and feed it to GIMP.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_import_string (gint32 image_ID,const gchar * string,gint length,gboolean merge,gboolean scale)
name|gimp_path_import_string
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gint
name|length
parameter_list|,
name|gboolean
name|merge
parameter_list|,
name|gboolean
name|scale
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-path-import-string"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|string
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|length
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|merge
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|scale
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
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
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

