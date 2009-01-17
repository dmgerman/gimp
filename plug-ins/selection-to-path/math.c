begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* math.c: define some simple array operations, and other functions.  *  * Copyright (C) 1992 Free Software Foundation, Inc.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_include
include|#
directive|include
file|"global.h"
end_include

begin_comment
comment|/* Numerical errors sometimes make a floating point number just slightly    larger or smaller than its true value.  When it matters, we need to    compare with some tolerance, REAL_EPSILON, defined in kbase.h.  */
end_comment

begin_function
name|boolean
DECL|function|epsilon_equal (real v1,real v2)
name|epsilon_equal
parameter_list|(
name|real
name|v1
parameter_list|,
name|real
name|v2
parameter_list|)
block|{
return|return
name|v1
operator|==
name|v2
comment|/* Usually they'll be exactly equal, anyway.  */
operator|||
name|fabs
argument_list|(
name|v1
operator|-
name|v2
argument_list|)
operator|<=
name|REAL_EPSILON
return|;
block|}
end_function

begin_comment
comment|/* Return the Euclidean distance between P1 and P2.  */
end_comment

begin_function
name|real
DECL|function|distance (real_coordinate_type p1,real_coordinate_type p2)
name|distance
parameter_list|(
name|real_coordinate_type
name|p1
parameter_list|,
name|real_coordinate_type
name|p2
parameter_list|)
block|{
return|return
name|hypot
argument_list|(
name|p1
operator|.
name|x
operator|-
name|p2
operator|.
name|x
argument_list|,
name|p1
operator|.
name|y
operator|-
name|p2
operator|.
name|y
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* Same thing, for integer points.  */
end_comment

begin_function
name|real
DECL|function|int_distance (coordinate_type p1,coordinate_type p2)
name|int_distance
parameter_list|(
name|coordinate_type
name|p1
parameter_list|,
name|coordinate_type
name|p2
parameter_list|)
block|{
return|return
name|hypot
argument_list|(
operator|(
name|double
operator|)
name|p1
operator|.
name|x
operator|-
name|p2
operator|.
name|x
argument_list|,
operator|(
name|double
operator|)
name|p1
operator|.
name|y
operator|-
name|p2
operator|.
name|y
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* Return the arc cosine of V, in degrees in the range zero to 180.  V    is taken to be in radians.  */
end_comment

begin_function
name|real
DECL|function|my_acosd (real v)
name|my_acosd
parameter_list|(
name|real
name|v
parameter_list|)
block|{
name|real
name|a
decl_stmt|;
if|if
condition|(
name|epsilon_equal
argument_list|(
name|v
argument_list|,
literal|1.0
argument_list|)
condition|)
name|v
operator|=
literal|1.0
expr_stmt|;
elseif|else
if|if
condition|(
name|epsilon_equal
argument_list|(
name|v
argument_list|,
operator|-
literal|1.0
argument_list|)
condition|)
name|v
operator|=
operator|-
literal|1.0
expr_stmt|;
name|errno
operator|=
literal|0
expr_stmt|;
name|a
operator|=
name|acos
argument_list|(
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|errno
operator|==
name|ERANGE
operator|||
name|errno
operator|==
name|EDOM
condition|)
name|FATAL_PERROR
argument_list|(
literal|"acosd"
argument_list|)
expr_stmt|;
return|return
name|a
operator|*
literal|180.0
operator|/
name|G_PI
return|;
block|}
end_function

begin_comment
comment|/* The slope of the line defined by COORD1 and COORD2.  */
end_comment

begin_function
name|real
DECL|function|slope (real_coordinate_type coord1,real_coordinate_type coord2)
name|slope
parameter_list|(
name|real_coordinate_type
name|coord1
parameter_list|,
name|real_coordinate_type
name|coord2
parameter_list|)
block|{
name|g_assert
argument_list|(
name|coord2
operator|.
name|x
operator|-
name|coord1
operator|.
name|x
operator|!=
literal|0
argument_list|)
expr_stmt|;
return|return
operator|(
name|coord2
operator|.
name|y
operator|-
name|coord1
operator|.
name|y
operator|)
operator|/
operator|(
name|coord2
operator|.
name|x
operator|-
name|coord1
operator|.
name|x
operator|)
return|;
block|}
end_function

begin_comment
comment|/* Turn an integer point into a real one, and vice versa.  */
end_comment

begin_function
name|real_coordinate_type
DECL|function|int_to_real_coord (coordinate_type int_coord)
name|int_to_real_coord
parameter_list|(
name|coordinate_type
name|int_coord
parameter_list|)
block|{
name|real_coordinate_type
name|real_coord
decl_stmt|;
name|real_coord
operator|.
name|x
operator|=
name|int_coord
operator|.
name|x
expr_stmt|;
name|real_coord
operator|.
name|y
operator|=
name|int_coord
operator|.
name|y
expr_stmt|;
return|return
name|real_coord
return|;
block|}
end_function

begin_function
name|coordinate_type
DECL|function|real_to_int_coord (real_coordinate_type real_coord)
name|real_to_int_coord
parameter_list|(
name|real_coordinate_type
name|real_coord
parameter_list|)
block|{
name|coordinate_type
name|int_coord
decl_stmt|;
name|int_coord
operator|.
name|x
operator|=
name|SROUND
argument_list|(
name|real_coord
operator|.
name|x
argument_list|)
expr_stmt|;
name|int_coord
operator|.
name|y
operator|=
name|SROUND
argument_list|(
name|real_coord
operator|.
name|y
argument_list|)
expr_stmt|;
return|return
name|int_coord
return|;
block|}
end_function

begin_comment
comment|/* See if two points (described by their row and column) are adjacent.  */
end_comment

begin_function
name|boolean
DECL|function|points_adjacent_p (int row1,int col1,int row2,int col2)
name|points_adjacent_p
parameter_list|(
name|int
name|row1
parameter_list|,
name|int
name|col1
parameter_list|,
name|int
name|row2
parameter_list|,
name|int
name|col2
parameter_list|)
block|{
name|int
name|row_diff
init|=
name|abs
argument_list|(
name|row1
operator|-
name|row2
argument_list|)
decl_stmt|;
name|int
name|col_diff
init|=
name|abs
argument_list|(
name|col1
operator|-
name|col2
argument_list|)
decl_stmt|;
return|return
operator|(
name|row_diff
operator|==
literal|1
operator|&&
name|col_diff
operator|==
literal|1
operator|)
operator|||
operator|(
name|row_diff
operator|==
literal|0
operator|&&
name|col_diff
operator|==
literal|1
operator|)
operator|||
operator|(
name|row_diff
operator|==
literal|1
operator|&&
name|col_diff
operator|==
literal|0
operator|)
return|;
block|}
end_function

begin_comment
comment|/* Find the largest and smallest elements in an array of reals.  */
end_comment

begin_function
name|void
DECL|function|find_bounds (real * values,unsigned value_count,real * min,real * max)
name|find_bounds
parameter_list|(
name|real
modifier|*
name|values
parameter_list|,
name|unsigned
name|value_count
parameter_list|,
name|real
modifier|*
name|min
parameter_list|,
name|real
modifier|*
name|max
parameter_list|)
block|{
name|unsigned
name|this_value
decl_stmt|;
comment|/* We must use FLT_MAX and FLT_MIN, instead of the corresponding      values for double, because gcc uses the native atof to parse      floating point constants, and many atof's choke on the extremes.  */
operator|*
name|min
operator|=
name|FLT_MAX
expr_stmt|;
operator|*
name|max
operator|=
name|FLT_MIN
expr_stmt|;
for|for
control|(
name|this_value
operator|=
literal|0
init|;
name|this_value
operator|<
name|value_count
condition|;
name|this_value
operator|++
control|)
block|{
if|if
condition|(
name|values
index|[
name|this_value
index|]
operator|<
operator|*
name|min
condition|)
operator|*
name|min
operator|=
name|values
index|[
name|this_value
index|]
expr_stmt|;
if|if
condition|(
name|values
index|[
name|this_value
index|]
operator|>
operator|*
name|max
condition|)
operator|*
name|max
operator|=
name|values
index|[
name|this_value
index|]
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Map a range of numbers, some positive and some negative, into all    positive, with the greatest being at one and the least at zero.     This allocates new memory.  */
end_comment

begin_function
name|real
modifier|*
DECL|function|map_to_unit (real * values,unsigned value_count)
name|map_to_unit
parameter_list|(
name|real
modifier|*
name|values
parameter_list|,
name|unsigned
name|value_count
parameter_list|)
block|{
name|real
name|smallest
decl_stmt|,
name|largest
decl_stmt|;
name|int
name|this_value
decl_stmt|;
name|real
modifier|*
name|mapped_values
init|=
name|g_new
argument_list|(
name|real
argument_list|,
name|value_count
argument_list|)
decl_stmt|;
name|find_bounds
argument_list|(
name|values
argument_list|,
name|value_count
argument_list|,
operator|&
name|smallest
argument_list|,
operator|&
name|largest
argument_list|)
expr_stmt|;
name|largest
operator|-=
name|smallest
expr_stmt|;
comment|/* We never care about largest itself. */
for|for
control|(
name|this_value
operator|=
literal|0
init|;
name|this_value
operator|<
name|value_count
condition|;
name|this_value
operator|++
control|)
name|mapped_values
index|[
name|this_value
index|]
operator|=
operator|(
name|values
index|[
name|this_value
index|]
operator|-
name|smallest
operator|)
operator|/
name|largest
expr_stmt|;
return|return
name|mapped_values
return|;
block|}
end_function

end_unit

