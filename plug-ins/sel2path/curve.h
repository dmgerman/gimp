begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* curve.h: data structures for the conversion from pixels to splines.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|CURVE_H
end_ifndef

begin_define
DECL|macro|CURVE_H
define|#
directive|define
name|CURVE_H
end_define

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_include
include|#
directive|include
file|"vector.h"
end_include

begin_comment
comment|/* We are simultaneously manipulating two different representations of    the same outline: one based on (x,y) positions in the plane, and one    based on parametric splines.  (We are trying to match the latter to    the former.)  Although the original (x,y)'s are pixel positions,    i.e., integers, after filtering they are reals.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2974c83b0108
block|{
DECL|member|coord
name|real_coordinate_type
name|coord
decl_stmt|;
DECL|member|t
name|real
name|t
decl_stmt|;
DECL|typedef|point_type
block|}
name|point_type
typedef|;
end_typedef

begin_comment
comment|/* It turns out to be convenient to break the list of all the pixels in    the outline into sublists, divided at ``corners''.  Then each of the    sublists is treated independently.  Each of these sublists is a `curve'.  */
end_comment

begin_struct
DECL|struct|curve
struct|struct
name|curve
block|{
DECL|member|point_list
name|point_type
modifier|*
name|point_list
decl_stmt|;
DECL|member|length
name|int
name|length
decl_stmt|;
DECL|member|cyclic
name|boolean
name|cyclic
decl_stmt|;
DECL|member|start_tangent
name|vector_type
modifier|*
name|start_tangent
decl_stmt|;
DECL|member|end_tangent
name|vector_type
modifier|*
name|end_tangent
decl_stmt|;
DECL|member|previous
name|struct
name|curve
modifier|*
name|previous
decl_stmt|;
DECL|member|next
name|struct
name|curve
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|curve_type
typedef|typedef
name|struct
name|curve
modifier|*
name|curve_type
typedef|;
end_typedef

begin_comment
comment|/* Get at the coordinates and the t values.  */
end_comment

begin_define
DECL|macro|CURVE_POINT (c,n)
define|#
directive|define
name|CURVE_POINT
parameter_list|(
name|c
parameter_list|,
name|n
parameter_list|)
value|((c)->point_list[n].coord)
end_define

begin_define
DECL|macro|LAST_CURVE_POINT (c)
define|#
directive|define
name|LAST_CURVE_POINT
parameter_list|(
name|c
parameter_list|)
value|((c)->point_list[(c)->length-1].coord)
end_define

begin_define
DECL|macro|CURVE_T (c,n)
define|#
directive|define
name|CURVE_T
parameter_list|(
name|c
parameter_list|,
name|n
parameter_list|)
value|((c)->point_list[n].t)
end_define

begin_define
DECL|macro|LAST_CURVE_T (c)
define|#
directive|define
name|LAST_CURVE_T
parameter_list|(
name|c
parameter_list|)
value|((c)->point_list[(c)->length-1].t)
end_define

begin_comment
comment|/* This is the length of `point_list'.  */
end_comment

begin_define
DECL|macro|CURVE_LENGTH (c)
define|#
directive|define
name|CURVE_LENGTH
parameter_list|(
name|c
parameter_list|)
value|((c)->length)
end_define

begin_comment
comment|/* A curve is ``cyclic'' if it didn't have any corners, after all, so    the last point is adjacent to the first.  */
end_comment

begin_define
DECL|macro|CURVE_CYCLIC (c)
define|#
directive|define
name|CURVE_CYCLIC
parameter_list|(
name|c
parameter_list|)
value|((c)->cyclic)
end_define

begin_comment
comment|/* If the curve is cyclic, the next and previous points should wrap    around; otherwise, if we get to the end, we return CURVE_LENGTH and    -1, respectively.  */
end_comment

begin_define
DECL|macro|CURVE_NEXT (c,n)
define|#
directive|define
name|CURVE_NEXT
parameter_list|(
name|c
parameter_list|,
name|n
parameter_list|)
define|\
value|((n) + 1>= CURVE_LENGTH (c)						\   ? CURVE_CYCLIC (c) ? ((n) + 1) % CURVE_LENGTH (c) : CURVE_LENGTH (c)	\   : (n) + 1)
end_define

begin_define
DECL|macro|CURVE_PREV (c,n)
define|#
directive|define
name|CURVE_PREV
parameter_list|(
name|c
parameter_list|,
name|n
parameter_list|)
define|\
value|((int) (n) - 1< 0							\   ? CURVE_CYCLIC (c) ? CURVE_LENGTH (c) + (int) (n) - 1 : -1		\   : (int) (n) - 1)
end_define

begin_comment
comment|/* The tangents at the endpoints are computed using the neighboring curves.  */
end_comment

begin_define
DECL|macro|CURVE_START_TANGENT (c)
define|#
directive|define
name|CURVE_START_TANGENT
parameter_list|(
name|c
parameter_list|)
value|((c)->start_tangent)
end_define

begin_define
DECL|macro|CURVE_END_TANGENT (c)
define|#
directive|define
name|CURVE_END_TANGENT
parameter_list|(
name|c
parameter_list|)
value|((c)->end_tangent)
end_define

begin_define
DECL|macro|PREVIOUS_CURVE (c)
define|#
directive|define
name|PREVIOUS_CURVE
parameter_list|(
name|c
parameter_list|)
value|((c)->previous)
end_define

begin_define
DECL|macro|NEXT_CURVE (c)
define|#
directive|define
name|NEXT_CURVE
parameter_list|(
name|c
parameter_list|)
value|((c)->next)
end_define

begin_comment
comment|/* Return an entirely empty curve.  */
end_comment

begin_function_decl
specifier|extern
name|curve_type
name|new_curve
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return a curve with the point P as its first element.  */
end_comment

begin_function_decl
specifier|extern
name|curve_type
name|init_curve
parameter_list|(
name|coordinate_type
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return a curve the same as C, except without any points.  */
end_comment

begin_function_decl
specifier|extern
name|curve_type
name|copy_most_of_curve
parameter_list|(
name|curve_type
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Free the memory C uses.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|free_curve
parameter_list|(
name|curve_type
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Append the point P to the end of C's list.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|append_pixel
parameter_list|(
name|curve_type
name|c
parameter_list|,
name|coordinate_type
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Like `append_pixel', for a point in real coordinates.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|append_point
parameter_list|(
name|curve_type
name|c
parameter_list|,
name|real_coordinate_type
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Write some or all, respectively, of the curve C in human-readable    form to the log file, if logging is enabled.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|log_curve
parameter_list|(
name|curve_type
name|c
parameter_list|,
name|boolean
name|print_t
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|log_entire_curve
parameter_list|(
name|curve_type
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Display the curve C online, if displaying is enabled.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|display_curve
parameter_list|(
name|curve_type
parameter_list|)
function_decl|;
end_function_decl

begin_escape
end_escape

begin_comment
comment|/* So, an outline is a list of curves.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2974c83b0208
block|{
DECL|member|data
name|curve_type
modifier|*
name|data
decl_stmt|;
DECL|member|length
name|unsigned
name|length
decl_stmt|;
DECL|member|clockwise
name|boolean
name|clockwise
decl_stmt|;
DECL|typedef|curve_list_type
block|}
name|curve_list_type
typedef|;
end_typedef

begin_comment
comment|/* Number of curves in the list.  */
end_comment

begin_define
DECL|macro|CURVE_LIST_LENGTH (c_l)
define|#
directive|define
name|CURVE_LIST_LENGTH
parameter_list|(
name|c_l
parameter_list|)
value|((c_l).length)
end_define

begin_comment
comment|/* Access the individual curves.  */
end_comment

begin_define
DECL|macro|CURVE_LIST_ELT (c_l,n)
define|#
directive|define
name|CURVE_LIST_ELT
parameter_list|(
name|c_l
parameter_list|,
name|n
parameter_list|)
value|((c_l).data[n])
end_define

begin_define
DECL|macro|LAST_CURVE_LIST_ELT (c_l)
define|#
directive|define
name|LAST_CURVE_LIST_ELT
parameter_list|(
name|c_l
parameter_list|)
value|((c_l).data[CURVE_LIST_LENGTH (c_l) - 1])
end_define

begin_comment
comment|/* Says whether the outline that this curve list represents moves    clockwise or counterclockwise.  */
end_comment

begin_define
DECL|macro|CURVE_LIST_CLOCKWISE (c_l)
define|#
directive|define
name|CURVE_LIST_CLOCKWISE
parameter_list|(
name|c_l
parameter_list|)
value|((c_l).clockwise)
end_define

begin_function_decl
specifier|extern
name|curve_list_type
name|new_curve_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|free_curve_list
parameter_list|(
name|curve_list_type
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|append_curve
parameter_list|(
name|curve_list_type
modifier|*
parameter_list|,
name|curve_type
parameter_list|)
function_decl|;
end_function_decl

begin_escape
end_escape

begin_comment
comment|/* And a character is a list of outlines.  I named this    `curve_list_array_type' because `curve_list_list_type' seemed pretty    monstrous.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2974c83b0308
block|{
DECL|member|data
name|curve_list_type
modifier|*
name|data
decl_stmt|;
DECL|member|length
name|unsigned
name|length
decl_stmt|;
DECL|typedef|curve_list_array_type
block|}
name|curve_list_array_type
typedef|;
end_typedef

begin_comment
comment|/* Turns out we can use the same definitions for lists of lists as for    just lists.  But we define the usual names, just in case.  */
end_comment

begin_define
DECL|macro|CURVE_LIST_ARRAY_LENGTH
define|#
directive|define
name|CURVE_LIST_ARRAY_LENGTH
value|CURVE_LIST_LENGTH
end_define

begin_define
DECL|macro|CURVE_LIST_ARRAY_ELT
define|#
directive|define
name|CURVE_LIST_ARRAY_ELT
value|CURVE_LIST_ELT
end_define

begin_define
DECL|macro|LAST_CURVE_LIST_ARRAY_ELT
define|#
directive|define
name|LAST_CURVE_LIST_ARRAY_ELT
value|LAST_CURVE_LIST_ELT
end_define

begin_function_decl
specifier|extern
name|curve_list_array_type
name|new_curve_list_array
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|free_curve_list_array
parameter_list|(
name|curve_list_array_type
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|append_curve_list
parameter_list|(
name|curve_list_array_type
modifier|*
parameter_list|,
name|curve_list_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not CURVE_H */
end_comment

end_unit

