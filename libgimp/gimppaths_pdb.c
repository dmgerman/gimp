begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimppaths_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_path_list:  * @image_ID: The ID of the image to list the paths from.  * @num_paths: The number of paths returned.  *  * List the paths associated with the passed image.  *  * List the paths associated with the passed image.  *  * Returns: List of the paths belonging to this image.  */
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
literal|"gimp_path_list"
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
comment|/**  * gimp_path_get_points:  * @image_ID: The ID of the image to list the paths from.  * @pathname: the name of the path whose points should be listed.  * @path_closed: Return if the path is closed. {0=path open, 1= path closed}.  * @num_path_point_details: The number of points returned. Each point is made up of (x,y,pnt_type) of floats.  * @points_pairs: The points in the path represented as 3 floats. The first is the x pos, next is the y pos, last is the type of the pnt. The type field is dependant on the path type. For beziers (type 1 paths) the type can either be {1.0= BEZIER_ANCHOR, 2.0= BEZIER_CONTROL}. Note all points are returned in pixel resolution.  *  * List the points associated with the named path.  *  * List the points associated with the named path.  *  * Returns: The type of the path. Currently only one type (1 = Bezier) is supported.  */
end_comment

begin_function
name|gint
DECL|function|gimp_path_get_points (gint32 image_ID,gchar * pathname,gint * path_closed,gint * num_path_point_details,gdouble ** points_pairs)
name|gimp_path_get_points
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|pathname
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
literal|"gimp_path_get_points"
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
name|pathname
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
comment|/**  * gimp_path_get_current:  * @image_ID: The ID of the image to get the current paths from.  *  * The name of the current path. Error if no paths.  *  * The name of the current path. Error if no paths.  *  * Returns: The name of the current path.  */
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
name|current_path_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_path_get_current"
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
name|current_path_name
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
name|current_path_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_set_current:  * @image_ID: The ID of the image to list set the paths in.  * @set_current_path_name: The name of the path to set the current path to.  *  * List the paths associated with the passed image.  *  * List the paths associated with the passed image.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_current (gint32 image_ID,gchar * set_current_path_name)
name|gimp_path_set_current
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|set_current_path_name
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
literal|"gimp_path_set_current"
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
name|set_current_path_name
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
comment|/**  * gimp_path_set_points:  * @image_ID: The ID of the image to set the paths in.  * @pathname: The name of the path to create (if it exists then a unique name will be created - query the list of paths if you want to make sure that the name of the path you create is unique. This will be set as the current path.  * @ptype: The type of the path. Currently only one type (1 = Bezier) is supported.  * @num_path_points: The number of points in the path. Each point is made up of (x,y,type) of floats. Currently only the creation of bezier curves is allowed. The type parameter must be set to (1) to indicate a BEZIER type curve. For BEZIERS. Note the that points must be given in the following order... ACCACCAC ... If the path is not closed the last control point is missed off. Points consist of three control points (control/anchor/control) so for a curve that is not closed there must be at least two points passed (2 x,y pairs). If num_path_pnts % 3 = 0 then the path is assumed to be closed and the points are ACCACCACCACC.  * @points_pairs: The points in the path represented as 3 floats. The first is the x pos, next is the y pos, last is the type of the pnt. The type field is dependant on the path type. For beziers (type 1 paths) the type can either be {1.0= BEZIER_ANCHOR, 2.0= BEZIER_CONTROL}. Note all points are returned in pixel resolution.  *  * Set the points associated with the named path.  *  * Set the points associated with the named path.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_points (gint32 image_ID,gchar * pathname,gint ptype,gint num_path_points,gdouble * points_pairs)
name|gimp_path_set_points
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|pathname
parameter_list|,
name|gint
name|ptype
parameter_list|,
name|gint
name|num_path_points
parameter_list|,
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
literal|"gimp_path_set_points"
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
name|pathname
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
literal|"gimp_path_stroke_current"
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
comment|/**  * gimp_path_get_point_at_dist:  * @image_ID: The ID of the image the paths belongs to.  * @distance: The distance along the path.  * @y_point: The y position of the point.  * @gradient: The gradient at the specified point.  *  * Get point on a path at a specified distance along the path.  *  * This will return the x,y position of a point at a given distance  * along the bezier curve. The distance will the obtained by first  * digitizing the curve internally an then walking along the curve. For  * a closed curve the start of the path is the first point on the path  * that was created. This might not be obvious. Note the current path  * is used.  *  * Returns: The x position of the point.  */
end_comment

begin_function
name|gint
DECL|function|gimp_path_get_point_at_dist (gint32 image_ID,gdouble distance,gint * y_point,gdouble * gradient)
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
name|gradient
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
literal|"gimp_path_get_point_at_dist"
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
name|gradient
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
comment|/**  * gimp_path_get_tattoo:  * @image_ID: The image.  * @pathname: the name of the path whose tattoo should be obtained.  *  * Returns the tattoo associated with the name path.  *  * This procedure returns the tattoo associated with the specified  * path. A tattoo is a unique and permanent identifier attached to a  * path that can be used to uniquely identify a path within an image  * even between sessions.  *  * Returns: The tattoo associated with the name path.  */
end_comment

begin_function
name|gint
DECL|function|gimp_path_get_tattoo (gint32 image_ID,gchar * pathname)
name|gimp_path_get_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|pathname
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
literal|"gimp_path_get_tattoo"
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
name|pathname
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
comment|/**  * gimp_get_path_by_tattoo:  * @image_ID: The image.  * @tattoo: The tattoo of the required path.  *  * Return the name of the path with the given tattoo.  *  * The procedure returns the name of the path in the specified image  * which has the passed tattoo. The tattoos are unique within the image  * and will be preserved across sessions and through renaming of the  * path. An error is returned if no path woth the specified tattoo can  * be found.  *  * Returns: The name of the path with the specified tattoo.  */
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
name|path_name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_get_path_by_tattoo"
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
name|path_name
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
name|path_name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_delete:  * @image_ID: The ID of the image to list delete the paths from.  * @path_name_to_del: The name of the path to delete.  *  * Delete the named paths associated with the passed image.  *  * Delete the named path.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_delete (gint32 image_ID,gchar * path_name_to_del)
name|gimp_path_delete
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|path_name_to_del
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
literal|"gimp_path_delete"
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
name|path_name_to_del
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
comment|/**  * gimp_path_get_locked:  * @image_ID: The image.  * @pathname: the name of the path whose locked status should be obtained.  *  * Returns the locked status associated with the name path.  *  * This procedure returns the lock status associated with the specified  * path. A path can be \"locked\" which means that the transformation  * tool operations will also apply to the path.  *  * Returns: The lock status associated with the name path. 0 returned if the path is not locked. 1 is returned if the path is locked.  */
end_comment

begin_function
name|gint
DECL|function|gimp_path_get_locked (gint32 image_ID,gchar * pathname)
name|gimp_path_get_locked
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|pathname
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
name|lockstatus
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_path_get_locked"
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
name|pathname
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
name|lockstatus
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
name|lockstatus
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_set_locked:  * @image_ID: The image.  * @pathname: the name of the path whose locked status should be set.  * @lockstatus: The lock status associated with the name path. 0 if the path is not locked. 1 if the path is to be locked.  *  * Set the locked status associated with the name path.  *  * This procedure sets the lock status associated with the specified  * path. A path can be \"locked\" which means that the transformation  * tool operations will also apply to the path.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_locked (gint32 image_ID,gchar * pathname,gint lockstatus)
name|gimp_path_set_locked
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|pathname
parameter_list|,
name|gint
name|lockstatus
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
literal|"gimp_path_set_locked"
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
name|pathname
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|lockstatus
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
comment|/**  * gimp_path_set_tattoo:  * @image_ID: The image.  * @pathname: the name of the path whose tattoo should be set.  * @tattovalue: The tattoo associated with the name path. Only values returned from 'path_get_tattoo' should be used here.  *  * Sets the tattoo associated with the name path.  *  * This procedure sets the tattoo associated with the specified path. A  * tattoo is a unique and permenant identifier attached to a path that  * can be used to uniquely identify a path within an image even between  * sessions. Note that the value passed to this function must have been  * obtained from a previous call to path_get_tattoo.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_path_set_tattoo (gint32 image_ID,gchar * pathname,gint tattovalue)
name|gimp_path_set_tattoo
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gchar
modifier|*
name|pathname
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
literal|"gimp_path_set_tattoo"
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
name|pathname
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

end_unit

