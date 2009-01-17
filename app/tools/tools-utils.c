begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"tools-utils.h"
end_include

begin_function_decl
specifier|static
name|gdouble
name|gimp_tool_utils_point_to_line_distance
parameter_list|(
specifier|const
name|GimpVector2
modifier|*
name|point
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|point_on_line
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|normalized_line_direction
parameter_list|,
name|GimpVector2
modifier|*
name|closest_line_point
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_tool_utils_point_to_line_distance:  * @point:              The point to calculate the distance for.  * @point_on_line:      A point on the line.  * @line_direction:     Normalized line direction vector.  * @closest_line_point: Gets set to the point on the line that is  *                      closest to @point.  *  * Returns: The shortest distance from @point to the line defined by  *          @point_on_line and @normalized_line_direction.  **/
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|gimp_tool_utils_point_to_line_distance (const GimpVector2 * point,const GimpVector2 * point_on_line,const GimpVector2 * line_direction,GimpVector2 * closest_line_point)
name|gimp_tool_utils_point_to_line_distance
parameter_list|(
specifier|const
name|GimpVector2
modifier|*
name|point
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|point_on_line
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|line_direction
parameter_list|,
name|GimpVector2
modifier|*
name|closest_line_point
parameter_list|)
block|{
name|GimpVector2
name|distance_vector
decl_stmt|;
name|GimpVector2
name|tmp_a
decl_stmt|;
name|GimpVector2
name|tmp_b
decl_stmt|;
name|gdouble
name|d
decl_stmt|;
name|gimp_vector2_sub
argument_list|(
operator|&
name|tmp_a
argument_list|,
name|point
argument_list|,
name|point_on_line
argument_list|)
expr_stmt|;
name|d
operator|=
name|gimp_vector2_inner_product
argument_list|(
operator|&
name|tmp_a
argument_list|,
name|line_direction
argument_list|)
expr_stmt|;
name|tmp_b
operator|=
name|gimp_vector2_mul_val
argument_list|(
operator|*
name|line_direction
argument_list|,
name|d
argument_list|)
expr_stmt|;
operator|*
name|closest_line_point
operator|=
name|gimp_vector2_add_val
argument_list|(
operator|*
name|point_on_line
argument_list|,
name|tmp_b
argument_list|)
expr_stmt|;
name|gimp_vector2_sub
argument_list|(
operator|&
name|distance_vector
argument_list|,
name|closest_line_point
argument_list|,
name|point
argument_list|)
expr_stmt|;
return|return
name|gimp_vector2_length
argument_list|(
operator|&
name|distance_vector
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_tool_motion_constrain:  * @start_x:  * @start_y:  * @end_x:  * @end_y:  * @n_snap_lines: Number evenly disributed lines to snap to.  *  * Projects a line onto the specified subset of evenly radially  * distributed lines. @n_lines of 2 makes the line snap horizontally  * or vertically. @n_lines of 4 snaps on 45 degree steps. @n_lines of  * 12 on 15 degree steps. etc.  **/
end_comment

begin_function
name|void
DECL|function|gimp_tool_motion_constrain (gdouble start_x,gdouble start_y,gdouble * end_x,gdouble * end_y,gint n_snap_lines)
name|gimp_tool_motion_constrain
parameter_list|(
name|gdouble
name|start_x
parameter_list|,
name|gdouble
name|start_y
parameter_list|,
name|gdouble
modifier|*
name|end_x
parameter_list|,
name|gdouble
modifier|*
name|end_y
parameter_list|,
name|gint
name|n_snap_lines
parameter_list|)
block|{
name|GimpVector2
name|line_point
init|=
block|{
name|start_x
block|,
name|start_y
block|}
decl_stmt|;
name|GimpVector2
name|point
init|=
block|{
operator|*
name|end_x
block|,
operator|*
name|end_y
block|}
decl_stmt|;
name|GimpVector2
name|constrained_point
decl_stmt|;
name|GimpVector2
name|line_dir
decl_stmt|;
name|gdouble
name|shortest_dist_moved
init|=
name|G_MAXDOUBLE
decl_stmt|;
name|gdouble
name|dist_moved
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_snap_lines
condition|;
name|i
operator|++
control|)
block|{
name|angle
operator|=
name|i
operator|*
name|G_PI
operator|/
name|n_snap_lines
expr_stmt|;
name|gimp_vector2_set
argument_list|(
operator|&
name|line_dir
argument_list|,
name|cos
argument_list|(
name|angle
argument_list|)
argument_list|,
name|sin
argument_list|(
name|angle
argument_list|)
argument_list|)
expr_stmt|;
name|dist_moved
operator|=
name|gimp_tool_utils_point_to_line_distance
argument_list|(
operator|&
name|point
argument_list|,
operator|&
name|line_point
argument_list|,
operator|&
name|line_dir
argument_list|,
operator|&
name|constrained_point
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist_moved
operator|<
name|shortest_dist_moved
condition|)
block|{
name|shortest_dist_moved
operator|=
name|dist_moved
expr_stmt|;
operator|*
name|end_x
operator|=
name|constrained_point
operator|.
name|x
expr_stmt|;
operator|*
name|end_y
operator|=
name|constrained_point
operator|.
name|y
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

