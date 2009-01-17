begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcoords-interpolate.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcoords.h"
end_include

begin_include
include|#
directive|include
file|"gimpcoords-interpolate.h"
end_include

begin_comment
comment|/* Local helper functions declarations*/
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_coords_interpolate_bezier_internal
parameter_list|(
specifier|const
name|GimpCoords
name|bezier_pt1
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt2
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt3
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt4
parameter_list|,
specifier|const
name|gdouble
name|start_t
parameter_list|,
specifier|const
name|gdouble
name|end_t
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_coords
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_params
parameter_list|,
name|gint
name|depth
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_coords_get_catmull_spline_point
parameter_list|(
name|gdouble
name|t
parameter_list|,
name|gdouble
name|p0
parameter_list|,
name|gdouble
name|p1
parameter_list|,
name|gdouble
name|p2
parameter_list|,
name|gdouble
name|p3
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Functions for bezier subdivision */
end_comment

begin_function
name|void
DECL|function|gimp_coords_interpolate_bezier (const GimpCoords bezier_pt1,const GimpCoords bezier_pt2,const GimpCoords bezier_pt3,const GimpCoords bezier_pt4,const gdouble precision,GArray ** ret_coords,GArray ** ret_params)
name|gimp_coords_interpolate_bezier
parameter_list|(
specifier|const
name|GimpCoords
name|bezier_pt1
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt2
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt3
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt4
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_coords
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_params
parameter_list|)
block|{
name|gimp_coords_interpolate_bezier_internal
argument_list|(
name|bezier_pt1
argument_list|,
name|bezier_pt2
argument_list|,
name|bezier_pt3
argument_list|,
name|bezier_pt4
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
name|precision
argument_list|,
name|ret_coords
argument_list|,
name|ret_params
argument_list|,
literal|10
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Recursive subdivision helper function */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_coords_interpolate_bezier_internal (const GimpCoords bezier_pt1,const GimpCoords bezier_pt2,const GimpCoords bezier_pt3,const GimpCoords bezier_pt4,const gdouble start_t,const gdouble end_t,const gdouble precision,GArray ** ret_coords,GArray ** ret_params,gint depth)
name|gimp_coords_interpolate_bezier_internal
parameter_list|(
specifier|const
name|GimpCoords
name|bezier_pt1
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt2
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt3
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt4
parameter_list|,
specifier|const
name|gdouble
name|start_t
parameter_list|,
specifier|const
name|gdouble
name|end_t
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_coords
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_params
parameter_list|,
name|gint
name|depth
parameter_list|)
block|{
comment|/*    * beziercoords has to contain four GimpCoords with the four control points    * of the bezier segment. We subdivide it at the parameter 0.5.    */
name|GimpCoords
name|subdivided
index|[
literal|8
index|]
decl_stmt|;
name|gdouble
name|middle_t
init|=
operator|(
name|start_t
operator|+
name|end_t
operator|)
operator|/
literal|2
decl_stmt|;
name|subdivided
index|[
literal|0
index|]
operator|=
name|bezier_pt1
expr_stmt|;
name|subdivided
index|[
literal|6
index|]
operator|=
name|bezier_pt4
expr_stmt|;
comment|/* if (!depth) g_printerr ("Hit recursion depth limit!\n"); */
name|gimp_coords_average
argument_list|(
operator|&
name|bezier_pt1
argument_list|,
operator|&
name|bezier_pt2
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|1
index|]
operator|)
argument_list|)
expr_stmt|;
name|gimp_coords_average
argument_list|(
operator|&
name|bezier_pt2
argument_list|,
operator|&
name|bezier_pt3
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|7
index|]
operator|)
argument_list|)
expr_stmt|;
name|gimp_coords_average
argument_list|(
operator|&
name|bezier_pt3
argument_list|,
operator|&
name|bezier_pt4
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|5
index|]
operator|)
argument_list|)
expr_stmt|;
name|gimp_coords_average
argument_list|(
operator|&
operator|(
name|subdivided
index|[
literal|1
index|]
operator|)
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|7
index|]
operator|)
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|2
index|]
operator|)
argument_list|)
expr_stmt|;
name|gimp_coords_average
argument_list|(
operator|&
operator|(
name|subdivided
index|[
literal|7
index|]
operator|)
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|5
index|]
operator|)
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|4
index|]
operator|)
argument_list|)
expr_stmt|;
name|gimp_coords_average
argument_list|(
operator|&
operator|(
name|subdivided
index|[
literal|2
index|]
operator|)
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|4
index|]
operator|)
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|3
index|]
operator|)
argument_list|)
expr_stmt|;
comment|/*    * We now have the coordinates of the two bezier segments in    * subdivided [0-3] and subdivided [3-6]    */
comment|/*    * Here we need to check, if we have sufficiently subdivided, i.e.    * if the stroke is sufficiently close to a straight line.    */
if|if
condition|(
operator|!
name|depth
operator|||
name|gimp_coords_bezier_is_straight
argument_list|(
name|subdivided
index|[
literal|0
index|]
argument_list|,
name|subdivided
index|[
literal|1
index|]
argument_list|,
name|subdivided
index|[
literal|2
index|]
argument_list|,
name|subdivided
index|[
literal|3
index|]
argument_list|,
name|precision
argument_list|)
condition|)
comment|/* 1st half */
block|{
operator|*
name|ret_coords
operator|=
name|g_array_append_vals
argument_list|(
operator|*
name|ret_coords
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|0
index|]
operator|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_params
condition|)
block|{
name|gdouble
name|params
index|[
literal|3
index|]
decl_stmt|;
name|params
index|[
literal|0
index|]
operator|=
name|start_t
expr_stmt|;
name|params
index|[
literal|1
index|]
operator|=
operator|(
literal|2
operator|*
name|start_t
operator|+
name|middle_t
operator|)
operator|/
literal|3
expr_stmt|;
name|params
index|[
literal|2
index|]
operator|=
operator|(
name|start_t
operator|+
literal|2
operator|*
name|middle_t
operator|)
operator|/
literal|3
expr_stmt|;
operator|*
name|ret_params
operator|=
name|g_array_append_vals
argument_list|(
operator|*
name|ret_params
argument_list|,
operator|&
operator|(
name|params
index|[
literal|0
index|]
operator|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_coords_interpolate_bezier_internal
argument_list|(
name|subdivided
index|[
literal|0
index|]
argument_list|,
name|subdivided
index|[
literal|1
index|]
argument_list|,
name|subdivided
index|[
literal|2
index|]
argument_list|,
name|subdivided
index|[
literal|3
index|]
argument_list|,
name|start_t
argument_list|,
operator|(
name|start_t
operator|+
name|end_t
operator|)
operator|/
literal|2
argument_list|,
name|precision
argument_list|,
name|ret_coords
argument_list|,
name|ret_params
argument_list|,
name|depth
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|depth
operator|||
name|gimp_coords_bezier_is_straight
argument_list|(
name|subdivided
index|[
literal|3
index|]
argument_list|,
name|subdivided
index|[
literal|4
index|]
argument_list|,
name|subdivided
index|[
literal|5
index|]
argument_list|,
name|subdivided
index|[
literal|6
index|]
argument_list|,
name|precision
argument_list|)
condition|)
comment|/* 2nd half */
block|{
operator|*
name|ret_coords
operator|=
name|g_array_append_vals
argument_list|(
operator|*
name|ret_coords
argument_list|,
operator|&
operator|(
name|subdivided
index|[
literal|3
index|]
operator|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_params
condition|)
block|{
name|gdouble
name|params
index|[
literal|3
index|]
decl_stmt|;
name|params
index|[
literal|0
index|]
operator|=
name|middle_t
expr_stmt|;
name|params
index|[
literal|1
index|]
operator|=
operator|(
literal|2
operator|*
name|middle_t
operator|+
name|end_t
operator|)
operator|/
literal|3
expr_stmt|;
name|params
index|[
literal|2
index|]
operator|=
operator|(
name|middle_t
operator|+
literal|2
operator|*
name|end_t
operator|)
operator|/
literal|3
expr_stmt|;
operator|*
name|ret_params
operator|=
name|g_array_append_vals
argument_list|(
operator|*
name|ret_params
argument_list|,
operator|&
operator|(
name|params
index|[
literal|0
index|]
operator|)
argument_list|,
literal|3
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_coords_interpolate_bezier_internal
argument_list|(
name|subdivided
index|[
literal|3
index|]
argument_list|,
name|subdivided
index|[
literal|4
index|]
argument_list|,
name|subdivided
index|[
literal|5
index|]
argument_list|,
name|subdivided
index|[
literal|6
index|]
argument_list|,
operator|(
name|start_t
operator|+
name|end_t
operator|)
operator|/
literal|2
argument_list|,
name|end_t
argument_list|,
name|precision
argument_list|,
name|ret_coords
argument_list|,
name|ret_params
argument_list|,
name|depth
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  * a helper function that determines if a bezier segment is "straight  * enough" to be approximated by a line.  *  * To be more exact, it also checks for the control points to be distributed  * evenly along the line. This makes it easier to reconstruct parameters for  * a given point along the segment.  *  * Needs four GimpCoords in an array.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_coords_bezier_is_straight (const GimpCoords bezier_pt1,const GimpCoords bezier_pt2,const GimpCoords bezier_pt3,const GimpCoords bezier_pt4,gdouble precision)
name|gimp_coords_bezier_is_straight
parameter_list|(
specifier|const
name|GimpCoords
name|bezier_pt1
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt2
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt3
parameter_list|,
specifier|const
name|GimpCoords
name|bezier_pt4
parameter_list|,
name|gdouble
name|precision
parameter_list|)
block|{
name|GimpCoords
name|pt1
decl_stmt|,
name|pt2
decl_stmt|;
comment|/* calculate the "ideal" positions for the control points */
name|gimp_coords_mix
argument_list|(
literal|2.0
operator|/
literal|3.0
argument_list|,
operator|&
name|bezier_pt1
argument_list|,
literal|1.0
operator|/
literal|3.0
argument_list|,
operator|&
name|bezier_pt4
argument_list|,
operator|&
name|pt1
argument_list|)
expr_stmt|;
name|gimp_coords_mix
argument_list|(
literal|1.0
operator|/
literal|3.0
argument_list|,
operator|&
name|bezier_pt1
argument_list|,
literal|2.0
operator|/
literal|3.0
argument_list|,
operator|&
name|bezier_pt4
argument_list|,
operator|&
name|pt2
argument_list|)
expr_stmt|;
comment|/* calculate the deviation of the actual control points */
return|return
operator|(
name|gimp_coords_manhattan_dist
argument_list|(
operator|&
name|bezier_pt2
argument_list|,
operator|&
name|pt1
argument_list|)
operator|<
name|precision
operator|&&
name|gimp_coords_manhattan_dist
argument_list|(
operator|&
name|bezier_pt3
argument_list|,
operator|&
name|pt2
argument_list|)
operator|<
name|precision
operator|)
return|;
block|}
end_function

begin_comment
comment|/* Functions for camull-rom interpolation */
end_comment

begin_function
name|void
DECL|function|gimp_coords_interpolate_catmull (const GimpCoords catmul_pt1,const GimpCoords catmul_pt2,const GimpCoords catmul_pt3,const GimpCoords catmul_pt4,gdouble precision,GArray ** ret_coords,GArray ** ret_params)
name|gimp_coords_interpolate_catmull
parameter_list|(
specifier|const
name|GimpCoords
name|catmul_pt1
parameter_list|,
specifier|const
name|GimpCoords
name|catmul_pt2
parameter_list|,
specifier|const
name|GimpCoords
name|catmul_pt3
parameter_list|,
specifier|const
name|GimpCoords
name|catmul_pt4
parameter_list|,
name|gdouble
name|precision
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_coords
parameter_list|,
name|GArray
modifier|*
modifier|*
name|ret_params
parameter_list|)
block|{
name|gdouble
name|delta_x
decl_stmt|,
name|delta_y
decl_stmt|;
name|gdouble
name|distance
decl_stmt|;
name|gint
name|num_points
decl_stmt|;
name|gint
name|n
decl_stmt|;
name|GimpCoords
name|past_coords
decl_stmt|;
name|GimpCoords
name|start_coords
decl_stmt|;
name|GimpCoords
name|end_coords
decl_stmt|;
name|GimpCoords
name|future_coords
decl_stmt|;
name|delta_x
operator|=
name|catmul_pt3
operator|.
name|x
operator|-
name|catmul_pt2
operator|.
name|x
expr_stmt|;
name|delta_y
operator|=
name|catmul_pt3
operator|.
name|y
operator|-
name|catmul_pt2
operator|.
name|y
expr_stmt|;
comment|/* Catmull-Rom interpolation requires 4 points.    * Two endpoints plus one more at each end.    */
name|past_coords
operator|=
name|catmul_pt1
expr_stmt|;
name|start_coords
operator|=
name|catmul_pt2
expr_stmt|;
name|end_coords
operator|=
name|catmul_pt3
expr_stmt|;
name|future_coords
operator|=
name|catmul_pt4
expr_stmt|;
name|distance
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|delta_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|delta_y
argument_list|)
argument_list|)
expr_stmt|;
name|num_points
operator|=
name|distance
operator|/
name|precision
expr_stmt|;
for|for
control|(
name|n
operator|=
literal|1
init|;
name|n
operator|<=
name|num_points
condition|;
name|n
operator|++
control|)
block|{
name|GimpCoords
name|res_coords
decl_stmt|;
name|gdouble
name|velocity
decl_stmt|;
name|gdouble
name|p
init|=
operator|(
name|gdouble
operator|)
name|n
operator|/
name|num_points
decl_stmt|;
name|res_coords
operator|.
name|x
operator|=
name|gimp_coords_get_catmull_spline_point
argument_list|(
name|p
argument_list|,
name|past_coords
operator|.
name|x
argument_list|,
name|start_coords
operator|.
name|x
argument_list|,
name|end_coords
operator|.
name|x
argument_list|,
name|future_coords
operator|.
name|x
argument_list|)
expr_stmt|;
name|res_coords
operator|.
name|y
operator|=
name|gimp_coords_get_catmull_spline_point
argument_list|(
name|p
argument_list|,
name|past_coords
operator|.
name|y
argument_list|,
name|start_coords
operator|.
name|y
argument_list|,
name|end_coords
operator|.
name|y
argument_list|,
name|future_coords
operator|.
name|y
argument_list|)
expr_stmt|;
name|res_coords
operator|.
name|pressure
operator|=
name|gimp_coords_get_catmull_spline_point
argument_list|(
name|p
argument_list|,
name|past_coords
operator|.
name|pressure
argument_list|,
name|start_coords
operator|.
name|pressure
argument_list|,
name|end_coords
operator|.
name|pressure
argument_list|,
name|future_coords
operator|.
name|pressure
argument_list|)
expr_stmt|;
name|res_coords
operator|.
name|xtilt
operator|=
name|gimp_coords_get_catmull_spline_point
argument_list|(
name|p
argument_list|,
name|past_coords
operator|.
name|xtilt
argument_list|,
name|start_coords
operator|.
name|xtilt
argument_list|,
name|end_coords
operator|.
name|xtilt
argument_list|,
name|future_coords
operator|.
name|xtilt
argument_list|)
expr_stmt|;
name|res_coords
operator|.
name|ytilt
operator|=
name|gimp_coords_get_catmull_spline_point
argument_list|(
name|p
argument_list|,
name|past_coords
operator|.
name|ytilt
argument_list|,
name|start_coords
operator|.
name|ytilt
argument_list|,
name|end_coords
operator|.
name|ytilt
argument_list|,
name|future_coords
operator|.
name|ytilt
argument_list|)
expr_stmt|;
name|res_coords
operator|.
name|wheel
operator|=
name|gimp_coords_get_catmull_spline_point
argument_list|(
name|p
argument_list|,
name|past_coords
operator|.
name|wheel
argument_list|,
name|start_coords
operator|.
name|wheel
argument_list|,
name|end_coords
operator|.
name|wheel
argument_list|,
name|future_coords
operator|.
name|wheel
argument_list|)
expr_stmt|;
name|velocity
operator|=
name|gimp_coords_get_catmull_spline_point
argument_list|(
name|p
argument_list|,
name|past_coords
operator|.
name|velocity
argument_list|,
name|start_coords
operator|.
name|velocity
argument_list|,
name|end_coords
operator|.
name|velocity
argument_list|,
name|future_coords
operator|.
name|velocity
argument_list|)
expr_stmt|;
name|res_coords
operator|.
name|velocity
operator|=
name|CLAMP
argument_list|(
name|velocity
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_array_append_val
argument_list|(
operator|*
name|ret_coords
argument_list|,
name|res_coords
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_params
condition|)
name|g_array_append_val
argument_list|(
operator|*
name|ret_params
argument_list|,
name|p
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_coords_get_catmull_spline_point (gdouble t,gdouble p0,gdouble p1,gdouble p2,gdouble p3)
name|gimp_coords_get_catmull_spline_point
parameter_list|(
name|gdouble
name|t
parameter_list|,
name|gdouble
name|p0
parameter_list|,
name|gdouble
name|p1
parameter_list|,
name|gdouble
name|p2
parameter_list|,
name|gdouble
name|p3
parameter_list|)
block|{
return|return
operator|(
operator|(
operator|(
operator|(
operator|-
name|t
operator|+
literal|2.0
operator|)
operator|*
name|t
operator|-
literal|1.0
operator|)
operator|*
name|t
operator|/
literal|2.0
operator|)
operator|*
name|p0
operator|+
operator|(
operator|(
operator|(
operator|(
literal|3.0
operator|*
name|t
operator|-
literal|5.0
operator|)
operator|*
name|t
operator|)
operator|*
name|t
operator|+
literal|2.0
operator|)
operator|/
literal|2.0
operator|)
operator|*
name|p1
operator|+
operator|(
operator|(
operator|(
operator|-
literal|3.0
operator|*
name|t
operator|+
literal|4.0
operator|)
operator|*
name|t
operator|+
literal|1.0
operator|)
operator|*
name|t
operator|/
literal|2.0
operator|)
operator|*
name|p2
operator|+
operator|(
operator|(
operator|(
name|t
operator|-
literal|1
operator|)
operator|*
name|t
operator|*
name|t
operator|)
operator|/
literal|2.0
operator|)
operator|*
name|p3
operator|)
return|;
block|}
end_function

end_unit

