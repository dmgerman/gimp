begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* vector.h: operations on vectors and points.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|VECTOR_H
end_ifndef

begin_define
DECL|macro|VECTOR_H
define|#
directive|define
name|VECTOR_H
end_define

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_comment
comment|/* Our vectors are represented as displacements along the x and y axes.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28d59de60108
block|{
DECL|member|dx
DECL|member|dy
name|real
name|dx
decl_stmt|,
name|dy
decl_stmt|;
DECL|typedef|vector_type
block|}
name|vector_type
typedef|;
end_typedef

begin_comment
comment|/* Consider a point as a vector from the origin.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|vector_type
name|make_vector
parameter_list|(
specifier|const
name|real_coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* And a vector as a point, i.e., a displacement from the origin.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|real_coordinate_type
name|vector_to_point
parameter_list|(
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Definitions for these common operations can be found in any decent    linear algebra book, and most calculus books.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|real
name|magnitude
parameter_list|(
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|vector_type
name|normalize
parameter_list|(
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|vector_type
name|Vadd
parameter_list|(
specifier|const
name|vector_type
parameter_list|,
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|real
name|Vdot
parameter_list|(
specifier|const
name|vector_type
parameter_list|,
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|vector_type
name|Vmult_scalar
parameter_list|(
specifier|const
name|vector_type
parameter_list|,
specifier|const
name|real
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|real
name|Vangle
parameter_list|(
specifier|const
name|vector_type
name|in
parameter_list|,
specifier|const
name|vector_type
name|out
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* These operations could have been named `P..._vector' just as well as    V..._point, so we may as well allow both names.  */
end_comment

begin_define
DECL|macro|Padd_vector
define|#
directive|define
name|Padd_vector
value|Vadd_point
end_define

begin_function_decl
specifier|extern
specifier|const
name|real_coordinate_type
name|Vadd_point
parameter_list|(
specifier|const
name|real_coordinate_type
parameter_list|,
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|Psubtract_vector
define|#
directive|define
name|Psubtract_vector
value|Vsubtract_point
end_define

begin_function_decl
specifier|extern
specifier|const
name|real_coordinate_type
name|Vsubtract_point
parameter_list|(
specifier|const
name|real_coordinate_type
parameter_list|,
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* This returns the rounded sum.  */
end_comment

begin_define
DECL|macro|IPadd_vector
define|#
directive|define
name|IPadd_vector
value|Vadd_int_point
end_define

begin_function_decl
specifier|extern
specifier|const
name|coordinate_type
name|Vadd_int_point
parameter_list|(
specifier|const
name|coordinate_type
parameter_list|,
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Take the absolute value of both components.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|vector_type
name|Vabs
parameter_list|(
specifier|const
name|vector_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Operations on points with real coordinates.  It is not orthogonal,    but more convenient, to have the subtraction operator return a    vector, and the addition operator return a point.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|vector_type
name|Psubtract
parameter_list|(
specifier|const
name|real_coordinate_type
parameter_list|,
specifier|const
name|real_coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* These are heavily used in spline fitting, so we define them as macros    instead of functions.  */
end_comment

begin_define
DECL|macro|Padd (rc1,rc2)
define|#
directive|define
name|Padd
parameter_list|(
name|rc1
parameter_list|,
name|rc2
parameter_list|)
define|\
value|((real_coordinate_type) { (rc1).x + (rc2).x, (rc1).y + (rc2).y })
end_define

begin_define
DECL|macro|Pmult_scalar (rc,r)
define|#
directive|define
name|Pmult_scalar
parameter_list|(
name|rc
parameter_list|,
name|r
parameter_list|)
define|\
value|((real_coordinate_type) { (rc).x * (r), (rc).y * (r) })
end_define

begin_comment
comment|/* Similarly, for points with integer coordinates; here, a subtraction    operator that does return another point is useful.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|vector_type
name|IPsubtract
parameter_list|(
specifier|const
name|coordinate_type
parameter_list|,
specifier|const
name|coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|coordinate_type
name|IPsubtractP
parameter_list|(
specifier|const
name|coordinate_type
parameter_list|,
specifier|const
name|coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|coordinate_type
name|IPadd
parameter_list|(
specifier|const
name|coordinate_type
parameter_list|,
specifier|const
name|coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|coordinate_type
name|IPmult_scalar
parameter_list|(
specifier|const
name|coordinate_type
parameter_list|,
specifier|const
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|real_coordinate_type
name|IPmult_real
parameter_list|(
specifier|const
name|coordinate_type
parameter_list|,
specifier|const
name|real
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|boolean
name|IPequal
parameter_list|(
specifier|const
name|coordinate_type
parameter_list|,
specifier|const
name|coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not VECTOR_H */
end_comment

end_unit

