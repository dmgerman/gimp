begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* spline.h: manipulate the spline representation.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|SPLINE_H
end_ifndef

begin_define
DECL|macro|SPLINE_H
define|#
directive|define
name|SPLINE_H
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"bounding-box.h"
end_include

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_comment
comment|/* Third degree is the highest we deal with.  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29afb5d70103
block|{
DECL|enumerator|LINEAR
DECL|enumerator|QUADRATIC
DECL|enumerator|CUBIC
name|LINEAR
init|=
literal|1
block|,
name|QUADRATIC
init|=
literal|2
block|,
name|CUBIC
init|=
literal|3
DECL|typedef|polynomial_degree
block|}
name|polynomial_degree
typedef|;
end_typedef

begin_comment
comment|/* A Bezier spline can be represented as four points in the real plane:    a starting point, ending point, and two control points.  The    curve always lies in the convex hull defined by the four points.  It    is also convenient to save the divergence of the spline from the    straight line defined by the endpoints.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29afb5d70208
block|{
DECL|member|v
name|real_coordinate_type
name|v
index|[
literal|4
index|]
decl_stmt|;
comment|/* The control points.  */
DECL|member|degree
name|polynomial_degree
name|degree
decl_stmt|;
DECL|member|linearity
name|real
name|linearity
decl_stmt|;
DECL|typedef|spline_type
block|}
name|spline_type
typedef|;
end_typedef

begin_define
DECL|macro|START_POINT (spl)
define|#
directive|define
name|START_POINT
parameter_list|(
name|spl
parameter_list|)
value|((spl).v[0])
end_define

begin_define
DECL|macro|CONTROL1 (spl)
define|#
directive|define
name|CONTROL1
parameter_list|(
name|spl
parameter_list|)
value|((spl).v[1])
end_define

begin_define
DECL|macro|CONTROL2 (spl)
define|#
directive|define
name|CONTROL2
parameter_list|(
name|spl
parameter_list|)
value|((spl).v[2])
end_define

begin_define
DECL|macro|END_POINT (spl)
define|#
directive|define
name|END_POINT
parameter_list|(
name|spl
parameter_list|)
value|((spl).v[3])
end_define

begin_define
DECL|macro|SPLINE_DEGREE (spl)
define|#
directive|define
name|SPLINE_DEGREE
parameter_list|(
name|spl
parameter_list|)
value|((spl).degree)
end_define

begin_define
DECL|macro|SPLINE_LINEARITY (spl)
define|#
directive|define
name|SPLINE_LINEARITY
parameter_list|(
name|spl
parameter_list|)
value|((spl).linearity)
end_define

begin_comment
comment|/* Return a spline structure.  */
end_comment

begin_function_decl
specifier|extern
name|spline_type
name|new_spline
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Print a spline on the given file.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|print_spline
parameter_list|(
name|FILE
modifier|*
parameter_list|,
name|spline_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Evaluate SPLINE at the given T value.  */
end_comment

begin_function_decl
specifier|extern
name|real_coordinate_type
name|evaluate_spline
parameter_list|(
name|spline_type
name|spline
parameter_list|,
name|real
name|t
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Each outline in a character is typically represented by many    splines.  So, here is a list structure for that:  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29afb5d70308
block|{
DECL|member|data
name|spline_type
modifier|*
name|data
decl_stmt|;
DECL|member|length
name|unsigned
name|length
decl_stmt|;
DECL|typedef|spline_list_type
block|}
name|spline_list_type
typedef|;
end_typedef

begin_comment
comment|/* An empty list will have length zero (and null data).  */
end_comment

begin_define
DECL|macro|SPLINE_LIST_LENGTH (s_l)
define|#
directive|define
name|SPLINE_LIST_LENGTH
parameter_list|(
name|s_l
parameter_list|)
value|((s_l).length)
end_define

begin_comment
comment|/* The address of the beginning of the array of data.  */
end_comment

begin_define
DECL|macro|SPLINE_LIST_DATA (s_l)
define|#
directive|define
name|SPLINE_LIST_DATA
parameter_list|(
name|s_l
parameter_list|)
value|((s_l).data)
end_define

begin_comment
comment|/* The element INDEX in S_L.  */
end_comment

begin_define
DECL|macro|SPLINE_LIST_ELT (s_l,index)
define|#
directive|define
name|SPLINE_LIST_ELT
parameter_list|(
name|s_l
parameter_list|,
name|index
parameter_list|)
value|(SPLINE_LIST_DATA (s_l)[index])
end_define

begin_comment
comment|/* The last element in S_L.  */
end_comment

begin_define
DECL|macro|LAST_SPLINE_LIST_ELT (s_l)
define|#
directive|define
name|LAST_SPLINE_LIST_ELT
parameter_list|(
name|s_l
parameter_list|)
define|\
value|(SPLINE_LIST_DATA (s_l)[SPLINE_LIST_LENGTH (s_l) - 1])
end_define

begin_comment
comment|/* The previous and next elements to INDEX in S_L.  */
end_comment

begin_define
DECL|macro|NEXT_SPLINE_LIST_ELT (s_l,index)
define|#
directive|define
name|NEXT_SPLINE_LIST_ELT
parameter_list|(
name|s_l
parameter_list|,
name|index
parameter_list|)
define|\
value|SPLINE_LIST_ELT (s_l, ((index) + 1) % SPLINE_LIST_LENGTH (s_l))
end_define

begin_define
DECL|macro|PREV_SPLINE_LIST_ELT (s_l,index)
define|#
directive|define
name|PREV_SPLINE_LIST_ELT
parameter_list|(
name|s_l
parameter_list|,
name|index
parameter_list|)
define|\
value|SPLINE_LIST_ELT (s_l, index == 0					\                         ? SPLINE_LIST_LENGTH (s_l) - 1			\                         : index - 1)
end_define

begin_comment
comment|/* Construct and destroy new `spline_list_type' objects.  */
end_comment

begin_function_decl
specifier|extern
name|spline_list_type
modifier|*
name|new_spline_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|spline_list_type
modifier|*
name|init_spline_list
parameter_list|(
name|spline_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|free_spline_list
parameter_list|(
name|spline_list_type
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Append the spline S to the list S_LIST.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|append_spline
parameter_list|(
name|spline_list_type
modifier|*
name|s_list
parameter_list|,
name|spline_type
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Append the elements in list S2 to S1, changing S1.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|concat_spline_lists
parameter_list|(
name|spline_list_type
modifier|*
name|s1
parameter_list|,
name|spline_list_type
name|s2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Each character is in general made up of many outlines. So here is one    more list structure.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29afb5d70408
block|{
DECL|member|data
name|spline_list_type
modifier|*
name|data
decl_stmt|;
DECL|member|length
name|unsigned
name|length
decl_stmt|;
DECL|typedef|spline_list_array_type
block|}
name|spline_list_array_type
typedef|;
end_typedef

begin_comment
comment|/* Turns out we can use the same definitions for lists of lists as for    just lists.  But we define the usual names, just in case.  */
end_comment

begin_define
DECL|macro|SPLINE_LIST_ARRAY_LENGTH
define|#
directive|define
name|SPLINE_LIST_ARRAY_LENGTH
value|SPLINE_LIST_LENGTH
end_define

begin_define
DECL|macro|SPLINE_LIST_ARRAY_DATA
define|#
directive|define
name|SPLINE_LIST_ARRAY_DATA
value|SPLINE_LIST_DATA
end_define

begin_define
DECL|macro|SPLINE_LIST_ARRAY_ELT
define|#
directive|define
name|SPLINE_LIST_ARRAY_ELT
value|SPLINE_LIST_ELT
end_define

begin_define
DECL|macro|LAST_SPLINE_LIST_ARRAY_ELT
define|#
directive|define
name|LAST_SPLINE_LIST_ARRAY_ELT
value|LAST_SPLINE_LIST_ELT
end_define

begin_comment
comment|/* The usual routines.  */
end_comment

begin_function_decl
specifier|extern
name|spline_list_array_type
name|new_spline_list_array
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|free_spline_list_array
parameter_list|(
name|spline_list_array_type
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|append_spline_list
parameter_list|(
name|spline_list_array_type
modifier|*
parameter_list|,
name|spline_list_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not SPLINE_H */
end_comment

end_unit

