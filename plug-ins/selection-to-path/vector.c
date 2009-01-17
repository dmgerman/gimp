begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* vector.c: vector/point operations.  *  * Copyright (C) 1992 Free Software Foundation, Inc.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<assert.h>
end_include

begin_include
include|#
directive|include
file|"global.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"vector.h"
end_include

begin_comment
comment|/* Given the point COORD, return the corresponding vector.  */
end_comment

begin_function
name|vector_type
DECL|function|make_vector (const real_coordinate_type c)
name|make_vector
parameter_list|(
specifier|const
name|real_coordinate_type
name|c
parameter_list|)
block|{
name|vector_type
name|v
decl_stmt|;
name|v
operator|.
name|dx
operator|=
name|c
operator|.
name|x
expr_stmt|;
name|v
operator|.
name|dy
operator|=
name|c
operator|.
name|y
expr_stmt|;
return|return
name|v
return|;
block|}
end_function

begin_comment
comment|/* And the converse: given a vector, return the corresponding point.  */
end_comment

begin_function
name|real_coordinate_type
DECL|function|vector_to_point (const vector_type v)
name|vector_to_point
parameter_list|(
specifier|const
name|vector_type
name|v
parameter_list|)
block|{
name|real_coordinate_type
name|coord
decl_stmt|;
name|coord
operator|.
name|x
operator|=
name|v
operator|.
name|dx
expr_stmt|;
name|coord
operator|.
name|y
operator|=
name|v
operator|.
name|dy
expr_stmt|;
return|return
name|coord
return|;
block|}
end_function

begin_function
name|real
DECL|function|magnitude (const vector_type v)
name|magnitude
parameter_list|(
specifier|const
name|vector_type
name|v
parameter_list|)
block|{
return|return
name|hypot
argument_list|(
name|v
operator|.
name|dx
argument_list|,
name|v
operator|.
name|dy
argument_list|)
return|;
block|}
end_function

begin_function
name|vector_type
DECL|function|normalize (const vector_type v)
name|normalize
parameter_list|(
specifier|const
name|vector_type
name|v
parameter_list|)
block|{
name|vector_type
name|new_v
decl_stmt|;
name|real
name|m
init|=
name|magnitude
argument_list|(
name|v
argument_list|)
decl_stmt|;
name|assert
argument_list|(
name|m
operator|>
literal|0.0
argument_list|)
expr_stmt|;
name|new_v
operator|.
name|dx
operator|=
name|v
operator|.
name|dx
operator|/
name|m
expr_stmt|;
name|new_v
operator|.
name|dy
operator|=
name|v
operator|.
name|dy
operator|/
name|m
expr_stmt|;
return|return
name|new_v
return|;
block|}
end_function

begin_function
name|vector_type
DECL|function|Vadd (const vector_type v1,const vector_type v2)
name|Vadd
parameter_list|(
specifier|const
name|vector_type
name|v1
parameter_list|,
specifier|const
name|vector_type
name|v2
parameter_list|)
block|{
name|vector_type
name|new_v
decl_stmt|;
name|new_v
operator|.
name|dx
operator|=
name|v1
operator|.
name|dx
operator|+
name|v2
operator|.
name|dx
expr_stmt|;
name|new_v
operator|.
name|dy
operator|=
name|v1
operator|.
name|dy
operator|+
name|v2
operator|.
name|dy
expr_stmt|;
return|return
name|new_v
return|;
block|}
end_function

begin_function
name|real
DECL|function|Vdot (const vector_type v1,const vector_type v2)
name|Vdot
parameter_list|(
specifier|const
name|vector_type
name|v1
parameter_list|,
specifier|const
name|vector_type
name|v2
parameter_list|)
block|{
return|return
name|v1
operator|.
name|dx
operator|*
name|v2
operator|.
name|dx
operator|+
name|v1
operator|.
name|dy
operator|*
name|v2
operator|.
name|dy
return|;
block|}
end_function

begin_function
name|vector_type
DECL|function|Vmult_scalar (const vector_type v,const real r)
name|Vmult_scalar
parameter_list|(
specifier|const
name|vector_type
name|v
parameter_list|,
specifier|const
name|real
name|r
parameter_list|)
block|{
name|vector_type
name|new_v
decl_stmt|;
name|new_v
operator|.
name|dx
operator|=
name|v
operator|.
name|dx
operator|*
name|r
expr_stmt|;
name|new_v
operator|.
name|dy
operator|=
name|v
operator|.
name|dy
operator|*
name|r
expr_stmt|;
return|return
name|new_v
return|;
block|}
end_function

begin_comment
comment|/* Given the IN_VECTOR and OUT_VECTOR, return the angle between them in    degrees, in the range zero to 180.  */
end_comment

begin_function
name|real
DECL|function|Vangle (const vector_type in_vector,const vector_type out_vector)
name|Vangle
parameter_list|(
specifier|const
name|vector_type
name|in_vector
parameter_list|,
specifier|const
name|vector_type
name|out_vector
parameter_list|)
block|{
name|vector_type
name|v1
init|=
name|normalize
argument_list|(
name|in_vector
argument_list|)
decl_stmt|;
name|vector_type
name|v2
init|=
name|normalize
argument_list|(
name|out_vector
argument_list|)
decl_stmt|;
return|return
name|my_acosd
argument_list|(
name|Vdot
argument_list|(
name|v2
argument_list|,
name|v1
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|real_coordinate_type
DECL|function|Vadd_point (const real_coordinate_type c,const vector_type v)
name|Vadd_point
parameter_list|(
specifier|const
name|real_coordinate_type
name|c
parameter_list|,
specifier|const
name|vector_type
name|v
parameter_list|)
block|{
name|real_coordinate_type
name|new_c
decl_stmt|;
name|new_c
operator|.
name|x
operator|=
name|c
operator|.
name|x
operator|+
name|v
operator|.
name|dx
expr_stmt|;
name|new_c
operator|.
name|y
operator|=
name|c
operator|.
name|y
operator|+
name|v
operator|.
name|dy
expr_stmt|;
return|return
name|new_c
return|;
block|}
end_function

begin_function
name|real_coordinate_type
DECL|function|Vsubtract_point (const real_coordinate_type c,const vector_type v)
name|Vsubtract_point
parameter_list|(
specifier|const
name|real_coordinate_type
name|c
parameter_list|,
specifier|const
name|vector_type
name|v
parameter_list|)
block|{
name|real_coordinate_type
name|new_c
decl_stmt|;
name|new_c
operator|.
name|x
operator|=
name|c
operator|.
name|x
operator|-
name|v
operator|.
name|dx
expr_stmt|;
name|new_c
operator|.
name|y
operator|=
name|c
operator|.
name|y
operator|-
name|v
operator|.
name|dy
expr_stmt|;
return|return
name|new_c
return|;
block|}
end_function

begin_function
name|coordinate_type
DECL|function|Vadd_int_point (const coordinate_type c,const vector_type v)
name|Vadd_int_point
parameter_list|(
specifier|const
name|coordinate_type
name|c
parameter_list|,
specifier|const
name|vector_type
name|v
parameter_list|)
block|{
name|coordinate_type
name|a
decl_stmt|;
name|a
operator|.
name|x
operator|=
name|SROUND
argument_list|(
operator|(
name|real
operator|)
name|c
operator|.
name|x
operator|+
name|v
operator|.
name|dx
argument_list|)
expr_stmt|;
name|a
operator|.
name|y
operator|=
name|SROUND
argument_list|(
operator|(
name|real
operator|)
name|c
operator|.
name|y
operator|+
name|v
operator|.
name|dy
argument_list|)
expr_stmt|;
return|return
name|a
return|;
block|}
end_function

begin_function
name|vector_type
DECL|function|Vabs (const vector_type v)
name|Vabs
parameter_list|(
specifier|const
name|vector_type
name|v
parameter_list|)
block|{
name|vector_type
name|new_v
decl_stmt|;
name|new_v
operator|.
name|dx
operator|=
name|fabs
argument_list|(
name|v
operator|.
name|dx
argument_list|)
expr_stmt|;
name|new_v
operator|.
name|dy
operator|=
name|fabs
argument_list|(
name|v
operator|.
name|dy
argument_list|)
expr_stmt|;
return|return
name|new_v
return|;
block|}
end_function

begin_comment
comment|/* Operations on points.  */
end_comment

begin_function
name|vector_type
DECL|function|Psubtract (const real_coordinate_type c1,const real_coordinate_type c2)
name|Psubtract
parameter_list|(
specifier|const
name|real_coordinate_type
name|c1
parameter_list|,
specifier|const
name|real_coordinate_type
name|c2
parameter_list|)
block|{
name|vector_type
name|v
decl_stmt|;
name|v
operator|.
name|dx
operator|=
name|c1
operator|.
name|x
operator|-
name|c2
operator|.
name|x
expr_stmt|;
name|v
operator|.
name|dy
operator|=
name|c1
operator|.
name|y
operator|-
name|c2
operator|.
name|y
expr_stmt|;
return|return
name|v
return|;
block|}
end_function

begin_comment
comment|/* Operations on integer points.  */
end_comment

begin_function
name|vector_type
DECL|function|IPsubtract (const coordinate_type coord1,const coordinate_type coord2)
name|IPsubtract
parameter_list|(
specifier|const
name|coordinate_type
name|coord1
parameter_list|,
specifier|const
name|coordinate_type
name|coord2
parameter_list|)
block|{
name|vector_type
name|v
decl_stmt|;
name|v
operator|.
name|dx
operator|=
name|coord1
operator|.
name|x
operator|-
name|coord2
operator|.
name|x
expr_stmt|;
name|v
operator|.
name|dy
operator|=
name|coord1
operator|.
name|y
operator|-
name|coord2
operator|.
name|y
expr_stmt|;
return|return
name|v
return|;
block|}
end_function

begin_function
name|coordinate_type
DECL|function|IPsubtractP (const coordinate_type c1,const coordinate_type c2)
name|IPsubtractP
parameter_list|(
specifier|const
name|coordinate_type
name|c1
parameter_list|,
specifier|const
name|coordinate_type
name|c2
parameter_list|)
block|{
name|coordinate_type
name|c
decl_stmt|;
name|c
operator|.
name|x
operator|=
name|c1
operator|.
name|x
operator|-
name|c2
operator|.
name|x
expr_stmt|;
name|c
operator|.
name|y
operator|=
name|c1
operator|.
name|y
operator|-
name|c2
operator|.
name|y
expr_stmt|;
return|return
name|c
return|;
block|}
end_function

begin_function
name|coordinate_type
DECL|function|IPadd (const coordinate_type c1,const coordinate_type c2)
name|IPadd
parameter_list|(
specifier|const
name|coordinate_type
name|c1
parameter_list|,
specifier|const
name|coordinate_type
name|c2
parameter_list|)
block|{
name|coordinate_type
name|c
decl_stmt|;
name|c
operator|.
name|x
operator|=
name|c1
operator|.
name|x
operator|+
name|c2
operator|.
name|x
expr_stmt|;
name|c
operator|.
name|y
operator|=
name|c1
operator|.
name|y
operator|+
name|c2
operator|.
name|y
expr_stmt|;
return|return
name|c
return|;
block|}
end_function

begin_function
name|coordinate_type
DECL|function|IPmult_scalar (const coordinate_type c,const int i)
name|IPmult_scalar
parameter_list|(
specifier|const
name|coordinate_type
name|c
parameter_list|,
specifier|const
name|int
name|i
parameter_list|)
block|{
name|coordinate_type
name|a
decl_stmt|;
name|a
operator|.
name|x
operator|=
name|c
operator|.
name|x
operator|*
name|i
expr_stmt|;
name|a
operator|.
name|y
operator|=
name|c
operator|.
name|y
operator|*
name|i
expr_stmt|;
return|return
name|a
return|;
block|}
end_function

begin_function
name|real_coordinate_type
DECL|function|IPmult_real (const coordinate_type c,const real r)
name|IPmult_real
parameter_list|(
specifier|const
name|coordinate_type
name|c
parameter_list|,
specifier|const
name|real
name|r
parameter_list|)
block|{
name|real_coordinate_type
name|a
decl_stmt|;
name|a
operator|.
name|x
operator|=
name|c
operator|.
name|x
operator|*
name|r
expr_stmt|;
name|a
operator|.
name|y
operator|=
name|c
operator|.
name|y
operator|*
name|r
expr_stmt|;
return|return
name|a
return|;
block|}
end_function

begin_function
name|boolean
DECL|function|IPequal (const coordinate_type c1,const coordinate_type c2)
name|IPequal
parameter_list|(
specifier|const
name|coordinate_type
name|c1
parameter_list|,
specifier|const
name|coordinate_type
name|c2
parameter_list|)
block|{
return|return
name|c1
operator|.
name|x
operator|==
name|c2
operator|.
name|x
operator|&&
name|c1
operator|.
name|y
operator|==
name|c2
operator|.
name|y
return|;
block|}
end_function

end_unit

