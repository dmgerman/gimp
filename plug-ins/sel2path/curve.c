begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* curve.c: operations on the lists of pixels and lists of curves.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<malloc.h>
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"global.h"
end_include

begin_include
include|#
directive|include
file|"curve.h"
end_include

begin_comment
comment|/* Return an entirely empty curve.  */
end_comment

begin_function
name|curve_type
DECL|function|new_curve ()
name|new_curve
parameter_list|()
block|{
name|curve_type
name|curve
init|=
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|curve
argument_list|)
argument_list|)
decl_stmt|;
name|curve
operator|->
name|point_list
operator|=
name|NULL
expr_stmt|;
name|CURVE_LENGTH
argument_list|(
name|curve
argument_list|)
operator|=
literal|0
expr_stmt|;
name|CURVE_CYCLIC
argument_list|(
name|curve
argument_list|)
operator|=
name|false
expr_stmt|;
name|CURVE_START_TANGENT
argument_list|(
name|curve
argument_list|)
operator|=
name|CURVE_END_TANGENT
argument_list|(
name|curve
argument_list|)
operator|=
name|NULL
expr_stmt|;
name|PREVIOUS_CURVE
argument_list|(
name|curve
argument_list|)
operator|=
name|NEXT_CURVE
argument_list|(
name|curve
argument_list|)
operator|=
name|NULL
expr_stmt|;
return|return
name|curve
return|;
block|}
end_function

begin_comment
comment|/* Start the returned curve off with COORD as the first point.  */
end_comment

begin_function
name|curve_type
DECL|function|init_curve (coordinate_type coord)
name|init_curve
parameter_list|(
name|coordinate_type
name|coord
parameter_list|)
block|{
name|curve_type
name|curve
init|=
name|new_curve
argument_list|()
decl_stmt|;
name|curve
operator|->
name|point_list
operator|=
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|point_type
argument_list|)
argument_list|)
expr_stmt|;
name|CURVE_LENGTH
argument_list|(
name|curve
argument_list|)
operator|=
literal|1
expr_stmt|;
name|CURVE_POINT
argument_list|(
name|curve
argument_list|,
literal|0
argument_list|)
operator|=
name|int_to_real_coord
argument_list|(
name|coord
argument_list|)
expr_stmt|;
return|return
name|curve
return|;
block|}
end_function

begin_comment
comment|/* Don't copy the points or tangents, but copy everything else.  */
end_comment

begin_function
name|curve_type
DECL|function|copy_most_of_curve (curve_type old_curve)
name|copy_most_of_curve
parameter_list|(
name|curve_type
name|old_curve
parameter_list|)
block|{
name|curve_type
name|curve
init|=
name|new_curve
argument_list|()
decl_stmt|;
name|CURVE_CYCLIC
argument_list|(
name|curve
argument_list|)
operator|=
name|CURVE_CYCLIC
argument_list|(
name|old_curve
argument_list|)
expr_stmt|;
name|PREVIOUS_CURVE
argument_list|(
name|curve
argument_list|)
operator|=
name|PREVIOUS_CURVE
argument_list|(
name|old_curve
argument_list|)
expr_stmt|;
name|NEXT_CURVE
argument_list|(
name|curve
argument_list|)
operator|=
name|NEXT_CURVE
argument_list|(
name|old_curve
argument_list|)
expr_stmt|;
return|return
name|curve
return|;
block|}
end_function

begin_comment
comment|/* The length of CURVE will be zero if we ended up not being able to fit    it (which in turn implies a problem elsewhere in the program, but at    any rate, we shouldn't try here to free the nonexistent curve).  */
end_comment

begin_function
name|void
DECL|function|free_curve (curve_type curve)
name|free_curve
parameter_list|(
name|curve_type
name|curve
parameter_list|)
block|{
if|if
condition|(
name|CURVE_LENGTH
argument_list|(
name|curve
argument_list|)
operator|>
literal|0
condition|)
name|safe_free
argument_list|(
operator|(
name|address
operator|*
operator|)
operator|&
operator|(
name|curve
operator|->
name|point_list
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|append_pixel (curve_type curve,coordinate_type coord)
name|append_pixel
parameter_list|(
name|curve_type
name|curve
parameter_list|,
name|coordinate_type
name|coord
parameter_list|)
block|{
name|append_point
argument_list|(
name|curve
argument_list|,
name|int_to_real_coord
argument_list|(
name|coord
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|append_point (curve_type curve,real_coordinate_type coord)
name|append_point
parameter_list|(
name|curve_type
name|curve
parameter_list|,
name|real_coordinate_type
name|coord
parameter_list|)
block|{
name|CURVE_LENGTH
argument_list|(
name|curve
argument_list|)
operator|++
expr_stmt|;
name|curve
operator|->
name|point_list
operator|=
name|realloc
argument_list|(
name|curve
operator|->
name|point_list
argument_list|,
name|CURVE_LENGTH
argument_list|(
name|curve
argument_list|)
operator|*
sizeof|sizeof
argument_list|(
name|point_type
argument_list|)
argument_list|)
expr_stmt|;
name|LAST_CURVE_POINT
argument_list|(
name|curve
argument_list|)
operator|=
name|coord
expr_stmt|;
comment|/* The t value does not need to be set.  */
block|}
end_function

begin_comment
comment|/* Return an initialized but empty curve list.  */
end_comment

begin_function
name|curve_list_type
DECL|function|new_curve_list ()
name|new_curve_list
parameter_list|()
block|{
name|curve_list_type
name|curve_list
decl_stmt|;
name|curve_list
operator|.
name|length
operator|=
literal|0
expr_stmt|;
name|curve_list
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
return|return
name|curve_list
return|;
block|}
end_function

begin_comment
comment|/* Free a curve list and all the curves it contains.  */
end_comment

begin_function
name|void
DECL|function|free_curve_list (curve_list_type * curve_list)
name|free_curve_list
parameter_list|(
name|curve_list_type
modifier|*
name|curve_list
parameter_list|)
block|{
name|unsigned
name|this_curve
decl_stmt|;
for|for
control|(
name|this_curve
operator|=
literal|0
init|;
name|this_curve
operator|<
name|curve_list
operator|->
name|length
condition|;
name|this_curve
operator|++
control|)
name|free_curve
argument_list|(
name|curve_list
operator|->
name|data
index|[
name|this_curve
index|]
argument_list|)
expr_stmt|;
comment|/* If the character was empty, it won't have any curves.  */
if|if
condition|(
name|curve_list
operator|->
name|data
operator|!=
name|NULL
condition|)
name|safe_free
argument_list|(
operator|(
name|address
operator|*
operator|)
operator|&
operator|(
name|curve_list
operator|->
name|data
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Add an element to a curve list.  */
end_comment

begin_function
name|void
DECL|function|append_curve (curve_list_type * curve_list,curve_type curve)
name|append_curve
parameter_list|(
name|curve_list_type
modifier|*
name|curve_list
parameter_list|,
name|curve_type
name|curve
parameter_list|)
block|{
name|curve_list
operator|->
name|length
operator|++
expr_stmt|;
name|curve_list
operator|->
name|data
operator|=
name|realloc
argument_list|(
name|curve_list
operator|->
name|data
argument_list|,
name|curve_list
operator|->
name|length
operator|*
sizeof|sizeof
argument_list|(
name|curve_type
argument_list|)
argument_list|)
expr_stmt|;
name|curve_list
operator|->
name|data
index|[
name|curve_list
operator|->
name|length
operator|-
literal|1
index|]
operator|=
name|curve
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Return an initialized but empty curve list array.  */
end_comment

begin_function
name|curve_list_array_type
DECL|function|new_curve_list_array ()
name|new_curve_list_array
parameter_list|()
block|{
name|curve_list_array_type
name|curve_list_array
decl_stmt|;
name|CURVE_LIST_ARRAY_LENGTH
argument_list|(
name|curve_list_array
argument_list|)
operator|=
literal|0
expr_stmt|;
name|curve_list_array
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
return|return
name|curve_list_array
return|;
block|}
end_function

begin_comment
comment|/* Free a curve list array and all the curve lists it contains.  */
end_comment

begin_function
name|void
DECL|function|free_curve_list_array (curve_list_array_type * curve_list_array)
name|free_curve_list_array
parameter_list|(
name|curve_list_array_type
modifier|*
name|curve_list_array
parameter_list|)
block|{
name|unsigned
name|this_list
decl_stmt|;
for|for
control|(
name|this_list
operator|=
literal|0
init|;
name|this_list
operator|<
name|CURVE_LIST_ARRAY_LENGTH
argument_list|(
operator|*
name|curve_list_array
argument_list|)
condition|;
name|this_list
operator|++
control|)
name|free_curve_list
argument_list|(
operator|&
name|CURVE_LIST_ARRAY_ELT
argument_list|(
operator|*
name|curve_list_array
argument_list|,
name|this_list
argument_list|)
argument_list|)
expr_stmt|;
comment|/* If the character was empty, it won't have any curves.  */
if|if
condition|(
name|curve_list_array
operator|->
name|data
operator|!=
name|NULL
condition|)
name|safe_free
argument_list|(
operator|(
name|address
operator|*
operator|)
operator|&
operator|(
name|curve_list_array
operator|->
name|data
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Add an element to a curve list array.  */
end_comment

begin_function
name|void
DECL|function|append_curve_list (curve_list_array_type * l,curve_list_type curve_list)
name|append_curve_list
parameter_list|(
name|curve_list_array_type
modifier|*
name|l
parameter_list|,
name|curve_list_type
name|curve_list
parameter_list|)
block|{
name|CURVE_LIST_ARRAY_LENGTH
argument_list|(
operator|*
name|l
argument_list|)
operator|++
expr_stmt|;
name|l
operator|->
name|data
operator|=
name|realloc
argument_list|(
name|l
operator|->
name|data
argument_list|,
operator|(
name|CURVE_LIST_ARRAY_LENGTH
argument_list|(
operator|*
name|l
argument_list|)
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|curve_list_type
argument_list|)
argument_list|)
expr_stmt|;
name|LAST_CURVE_LIST_ARRAY_ELT
argument_list|(
operator|*
name|l
argument_list|)
operator|=
name|curve_list
expr_stmt|;
block|}
end_function

end_unit

