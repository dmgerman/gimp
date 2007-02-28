begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimp-transform-resize.h"
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|HAVE_FINITE
argument_list|)
end_if

begin_define
DECL|macro|FINITE (x)
define|#
directive|define
name|FINITE
parameter_list|(
name|x
parameter_list|)
value|finite(x)
end_define

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|HAVE_ISFINITE
argument_list|)
end_elif

begin_define
DECL|macro|FINITE (x)
define|#
directive|define
name|FINITE
parameter_list|(
name|x
parameter_list|)
value|isfinite(x)
end_define

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
end_elif

begin_define
DECL|macro|FINITE (x)
define|#
directive|define
name|FINITE
parameter_list|(
name|x
parameter_list|)
value|_finite(x)
end_define

begin_else
else|#
directive|else
end_else

begin_error
error|#
directive|error
literal|"no FINITE() implementation available?!"
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|MIN4 (a,b,c,d)
define|#
directive|define
name|MIN4
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|d
parameter_list|)
value|MIN(MIN((a),(b)),MIN((c),(d)))
end_define

begin_define
DECL|macro|MAX4 (a,b,c,d)
define|#
directive|define
name|MAX4
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|d
parameter_list|)
value|MAX(MAX((a),(b)),MAX((c),(d)))
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b74a9eb0108
block|{
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
DECL|typedef|Point
block|}
name|Point
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b74a9eb0208
block|{
DECL|member|xmin
DECL|member|xmax
name|gint
name|xmin
decl_stmt|,
name|xmax
decl_stmt|;
DECL|member|ymin
DECL|member|ymax
name|gint
name|ymin
decl_stmt|,
name|ymax
decl_stmt|;
DECL|member|m
DECL|member|b
name|gdouble
name|m
decl_stmt|,
name|b
decl_stmt|;
comment|/* y = mx + b */
DECL|member|top
DECL|member|right
name|gboolean
name|top
decl_stmt|,
name|right
decl_stmt|;
DECL|typedef|Edge
block|}
name|Edge
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_transform_resize_adjust
parameter_list|(
name|gdouble
name|dx1
parameter_list|,
name|gdouble
name|dy1
parameter_list|,
name|gdouble
name|dx2
parameter_list|,
name|gdouble
name|dy2
parameter_list|,
name|gdouble
name|dx3
parameter_list|,
name|gdouble
name|dy3
parameter_list|,
name|gdouble
name|dx4
parameter_list|,
name|gdouble
name|dy4
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_resize_crop
parameter_list|(
name|gdouble
name|dx1
parameter_list|,
name|gdouble
name|dy1
parameter_list|,
name|gdouble
name|dx2
parameter_list|,
name|gdouble
name|dy2
parameter_list|,
name|gdouble
name|dx3
parameter_list|,
name|gdouble
name|dy3
parameter_list|,
name|gdouble
name|dx4
parameter_list|,
name|gdouble
name|dy4
parameter_list|,
name|gdouble
name|aspect
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * This function wants to be passed the inverse transformation matrix!!  */
end_comment

begin_function
name|void
DECL|function|gimp_transform_resize_boundary (const GimpMatrix3 * inv,GimpTransformResize resize,gint u1,gint v1,gint u2,gint v2,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_transform_resize_boundary
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|inv
parameter_list|,
name|GimpTransformResize
name|resize
parameter_list|,
name|gint
name|u1
parameter_list|,
name|gint
name|v1
parameter_list|,
name|gint
name|u2
parameter_list|,
name|gint
name|v2
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
block|{
name|gdouble
name|dx1
decl_stmt|,
name|dx2
decl_stmt|,
name|dx3
decl_stmt|,
name|dx4
decl_stmt|;
name|gdouble
name|dy1
decl_stmt|,
name|dy2
decl_stmt|,
name|dy3
decl_stmt|,
name|dy4
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|inv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*  initialize with the original boundary  */
operator|*
name|x1
operator|=
name|u1
expr_stmt|;
operator|*
name|y1
operator|=
name|v1
expr_stmt|;
operator|*
name|x2
operator|=
name|u2
expr_stmt|;
operator|*
name|y2
operator|=
name|v2
expr_stmt|;
if|if
condition|(
name|resize
operator|==
name|GIMP_TRANSFORM_RESIZE_CLIP
condition|)
return|return;
name|gimp_matrix3_transform_point
argument_list|(
name|inv
argument_list|,
name|u1
argument_list|,
name|v1
argument_list|,
operator|&
name|dx1
argument_list|,
operator|&
name|dy1
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|inv
argument_list|,
name|u2
argument_list|,
name|v1
argument_list|,
operator|&
name|dx2
argument_list|,
operator|&
name|dy2
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|inv
argument_list|,
name|u1
argument_list|,
name|v2
argument_list|,
operator|&
name|dx3
argument_list|,
operator|&
name|dy3
argument_list|)
expr_stmt|;
name|gimp_matrix3_transform_point
argument_list|(
name|inv
argument_list|,
name|u2
argument_list|,
name|v2
argument_list|,
operator|&
name|dx4
argument_list|,
operator|&
name|dy4
argument_list|)
expr_stmt|;
comment|/*  check if the transformation matrix is valid at all  */
if|if
condition|(
operator|!
name|FINITE
argument_list|(
name|dx1
argument_list|)
operator|||
operator|!
name|FINITE
argument_list|(
name|dy1
argument_list|)
operator|||
operator|!
name|FINITE
argument_list|(
name|dx2
argument_list|)
operator|||
operator|!
name|FINITE
argument_list|(
name|dy2
argument_list|)
operator|||
operator|!
name|FINITE
argument_list|(
name|dx3
argument_list|)
operator|||
operator|!
name|FINITE
argument_list|(
name|dy3
argument_list|)
operator|||
operator|!
name|FINITE
argument_list|(
name|dx4
argument_list|)
operator|||
operator|!
name|FINITE
argument_list|(
name|dy4
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"invalid transform matrix"
argument_list|)
expr_stmt|;
name|resize
operator|=
name|GIMP_TRANSFORM_RESIZE_CLIP
expr_stmt|;
block|}
switch|switch
condition|(
name|resize
condition|)
block|{
case|case
name|GIMP_TRANSFORM_RESIZE_ADJUST
case|:
name|gimp_transform_resize_adjust
argument_list|(
name|dx1
argument_list|,
name|dy1
argument_list|,
name|dx2
argument_list|,
name|dy2
argument_list|,
name|dx3
argument_list|,
name|dy3
argument_list|,
name|dx4
argument_list|,
name|dy4
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_RESIZE_CLIP
case|:
comment|/*  we are all done already  */
break|break;
case|case
name|GIMP_TRANSFORM_RESIZE_CROP
case|:
name|gimp_transform_resize_crop
argument_list|(
name|dx1
argument_list|,
name|dy1
argument_list|,
name|dx2
argument_list|,
name|dy2
argument_list|,
name|dx3
argument_list|,
name|dy3
argument_list|,
name|dx4
argument_list|,
name|dy4
argument_list|,
literal|0.0
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TRANSFORM_RESIZE_CROP_WITH_ASPECT
case|:
name|gimp_transform_resize_crop
argument_list|(
name|dx1
argument_list|,
name|dy1
argument_list|,
name|dx2
argument_list|,
name|dy2
argument_list|,
name|dx3
argument_list|,
name|dy3
argument_list|,
name|dx4
argument_list|,
name|dy4
argument_list|,
operator|(
operator|(
name|gdouble
operator|)
name|u2
operator|-
name|u1
operator|)
operator|/
operator|(
name|v2
operator|-
name|v1
operator|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|*
name|x1
operator|==
operator|*
name|x2
condition|)
operator|(
operator|*
name|x2
operator|)
operator|++
expr_stmt|;
if|if
condition|(
operator|*
name|y1
operator|==
operator|*
name|y2
condition|)
operator|(
operator|*
name|y2
operator|)
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_resize_adjust (gdouble dx1,gdouble dy1,gdouble dx2,gdouble dy2,gdouble dx3,gdouble dy3,gdouble dx4,gdouble dy4,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_transform_resize_adjust
parameter_list|(
name|gdouble
name|dx1
parameter_list|,
name|gdouble
name|dy1
parameter_list|,
name|gdouble
name|dx2
parameter_list|,
name|gdouble
name|dy2
parameter_list|,
name|gdouble
name|dx3
parameter_list|,
name|gdouble
name|dy3
parameter_list|,
name|gdouble
name|dx4
parameter_list|,
name|gdouble
name|dy4
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
block|{
operator|*
name|x1
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|MIN4
argument_list|(
name|dx1
argument_list|,
name|dx2
argument_list|,
name|dx3
argument_list|,
name|dx4
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y1
operator|=
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|MIN4
argument_list|(
name|dy1
argument_list|,
name|dy2
argument_list|,
name|dy3
argument_list|,
name|dy4
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|x2
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|dx1
argument_list|,
name|dx2
argument_list|,
name|dx3
argument_list|,
name|dx4
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|y2
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
name|MAX4
argument_list|(
name|dy1
argument_list|,
name|dy2
argument_list|,
name|dy3
argument_list|,
name|dy4
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|edge_init (Edge * edge,const Point * p,const Point * q)
name|edge_init
parameter_list|(
name|Edge
modifier|*
name|edge
parameter_list|,
specifier|const
name|Point
modifier|*
name|p
parameter_list|,
specifier|const
name|Point
modifier|*
name|q
parameter_list|)
block|{
name|gdouble
name|den
decl_stmt|;
name|edge
operator|->
name|xmin
operator|=
name|MIN
argument_list|(
operator|(
name|p
operator|->
name|x
operator|)
argument_list|,
operator|(
name|q
operator|->
name|x
operator|)
argument_list|)
expr_stmt|;
name|edge
operator|->
name|xmax
operator|=
name|MAX
argument_list|(
operator|(
name|p
operator|->
name|x
operator|)
argument_list|,
operator|(
name|q
operator|->
name|x
operator|)
argument_list|)
expr_stmt|;
name|edge
operator|->
name|ymin
operator|=
name|MIN
argument_list|(
operator|(
name|p
operator|->
name|y
operator|)
argument_list|,
operator|(
name|q
operator|->
name|y
operator|)
argument_list|)
expr_stmt|;
name|edge
operator|->
name|ymax
operator|=
name|MAX
argument_list|(
operator|(
name|p
operator|->
name|y
operator|)
argument_list|,
operator|(
name|q
operator|->
name|y
operator|)
argument_list|)
expr_stmt|;
name|edge
operator|->
name|top
operator|=
name|p
operator|->
name|x
operator|>
name|q
operator|->
name|x
expr_stmt|;
name|edge
operator|->
name|right
operator|=
name|p
operator|->
name|y
operator|>
name|q
operator|->
name|y
expr_stmt|;
name|den
operator|=
name|q
operator|->
name|x
operator|-
name|p
operator|->
name|x
expr_stmt|;
if|if
condition|(
name|den
operator|==
literal|0
condition|)
name|den
operator|=
literal|0.001
expr_stmt|;
name|edge
operator|->
name|m
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|q
operator|->
name|y
operator|-
name|p
operator|->
name|y
operator|)
operator|/
name|den
expr_stmt|;
name|edge
operator|->
name|b
operator|=
name|p
operator|->
name|y
operator|-
name|edge
operator|->
name|m
operator|*
name|p
operator|->
name|x
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|Edge
modifier|*
DECL|function|find_edge (const Edge * edges,gint x,gboolean top)
name|find_edge
parameter_list|(
specifier|const
name|Edge
modifier|*
name|edges
parameter_list|,
name|gint
name|x
parameter_list|,
name|gboolean
name|top
parameter_list|)
block|{
specifier|const
name|Edge
modifier|*
name|emax
init|=
name|edges
decl_stmt|;
specifier|const
name|Edge
modifier|*
name|e
init|=
name|edges
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
literal|4
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|e
operator|->
name|xmin
operator|==
name|x
operator|)
operator|&&
operator|(
name|e
operator|->
name|xmax
operator|!=
name|e
operator|->
name|xmin
operator|)
operator|&&
operator|(
operator|(
name|e
operator|->
name|top
operator|&&
name|top
operator|)
operator|||
operator|(
operator|!
name|e
operator|->
name|top
operator|&&
operator|!
name|top
operator|)
operator|)
condition|)
name|emax
operator|=
name|e
expr_stmt|;
name|e
operator|++
expr_stmt|;
block|}
return|return
name|emax
return|;
block|}
end_function

begin_comment
comment|/* find largest pixel completely inside;  * look through all edges for intersection  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|intersect_x (const Edge * edges,gint y)
name|intersect_x
parameter_list|(
specifier|const
name|Edge
modifier|*
name|edges
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gdouble
name|x0
init|=
literal|0
decl_stmt|;
name|gdouble
name|x1
init|=
literal|0
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
literal|4
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|edges
index|[
name|i
index|]
operator|.
name|right
operator|&&
name|edges
index|[
name|i
index|]
operator|.
name|ymin
operator|<=
name|y
operator|&&
name|edges
index|[
name|i
index|]
operator|.
name|ymax
operator|>=
name|y
condition|)
block|{
name|x0
operator|=
operator|(
name|y
operator|+
literal|0.5
operator|-
name|edges
index|[
name|i
index|]
operator|.
name|b
operator|)
operator|/
name|edges
index|[
name|i
index|]
operator|.
name|m
expr_stmt|;
name|x1
operator|=
operator|(
name|y
operator|-
literal|0.5
operator|-
name|edges
index|[
name|i
index|]
operator|.
name|b
operator|)
operator|/
name|edges
index|[
name|i
index|]
operator|.
name|m
expr_stmt|;
block|}
return|return
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|MIN
argument_list|(
name|x0
argument_list|,
name|x1
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|intersect_y (const Edge * edge,gint xi)
name|intersect_y
parameter_list|(
specifier|const
name|Edge
modifier|*
name|edge
parameter_list|,
name|gint
name|xi
parameter_list|)
block|{
name|gdouble
name|yfirst
init|=
name|edge
operator|->
name|m
operator|*
operator|(
name|xi
operator|-
literal|0.5
operator|)
operator|+
name|edge
operator|->
name|b
decl_stmt|;
name|gdouble
name|ylast
init|=
name|edge
operator|->
name|m
operator|*
operator|(
name|xi
operator|+
literal|0.5
operator|)
operator|+
name|edge
operator|->
name|b
decl_stmt|;
return|return
call|(
name|gint
call|)
argument_list|(
name|edge
operator|->
name|top
condition|?
name|ceil
argument_list|(
name|MAX
argument_list|(
name|yfirst
argument_list|,
name|ylast
argument_list|)
argument_list|)
else|:
name|floor
argument_list|(
name|MIN
argument_list|(
name|yfirst
argument_list|,
name|ylast
argument_list|)
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_resize_crop (gdouble dx1,gdouble dy1,gdouble dx2,gdouble dy2,gdouble dx3,gdouble dy3,gdouble dx4,gdouble dy4,gdouble aspect,gint * x1,gint * y1,gint * x2,gint * y2)
name|gimp_transform_resize_crop
parameter_list|(
name|gdouble
name|dx1
parameter_list|,
name|gdouble
name|dy1
parameter_list|,
name|gdouble
name|dx2
parameter_list|,
name|gdouble
name|dy2
parameter_list|,
name|gdouble
name|dx3
parameter_list|,
name|gdouble
name|dy3
parameter_list|,
name|gdouble
name|dx4
parameter_list|,
name|gdouble
name|dy4
parameter_list|,
name|gdouble
name|aspect
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
block|{
name|Point
name|points
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|ax
decl_stmt|,
name|ay
decl_stmt|;
name|int
name|min
decl_stmt|;
name|gint
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|Edge
name|edges
index|[
literal|4
index|]
decl_stmt|;
specifier|const
name|Point
modifier|*
name|a
decl_stmt|;
specifier|const
name|Point
modifier|*
name|b
decl_stmt|;
specifier|const
name|Edge
modifier|*
name|top
decl_stmt|;
specifier|const
name|Edge
modifier|*
name|bottom
decl_stmt|;
name|gint
name|cxmin
decl_stmt|,
name|cymin
decl_stmt|;
name|gint
name|cxmax
decl_stmt|,
name|cymax
decl_stmt|;
name|Point
modifier|*
name|xint
decl_stmt|;
name|gint
name|ymin
decl_stmt|,
name|ymax
decl_stmt|;
name|gint
name|maxarea
init|=
literal|0
decl_stmt|;
name|gint
name|xi
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/*  fill in the points array  */
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|=
name|floor
argument_list|(
name|dx1
argument_list|)
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|=
name|floor
argument_list|(
name|dy1
argument_list|)
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|x
operator|=
name|floor
argument_list|(
name|dx2
argument_list|)
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|y
operator|=
name|floor
argument_list|(
name|dy2
argument_list|)
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|x
operator|=
name|floor
argument_list|(
name|dx3
argument_list|)
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|y
operator|=
name|floor
argument_list|(
name|dy3
argument_list|)
expr_stmt|;
name|points
index|[
literal|3
index|]
operator|.
name|x
operator|=
name|floor
argument_list|(
name|dx4
argument_list|)
expr_stmt|;
name|points
index|[
literal|3
index|]
operator|.
name|y
operator|=
name|floor
argument_list|(
name|dy4
argument_list|)
expr_stmt|;
comment|/*  first, translate the vertices into the first quadrant */
name|ax
operator|=
literal|0
expr_stmt|;
name|ay
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|points
index|[
name|i
index|]
operator|.
name|x
operator|<
name|ax
condition|)
name|ax
operator|=
name|points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|points
index|[
name|i
index|]
operator|.
name|y
operator|<
name|ay
condition|)
name|ay
operator|=
name|points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|points
index|[
name|i
index|]
operator|.
name|x
operator|+=
operator|(
operator|-
name|ax
operator|)
operator|*
literal|2
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|+=
operator|(
operator|-
name|ay
operator|)
operator|*
literal|2
expr_stmt|;
block|}
comment|/* find the convex hull using Jarvis's March as the points are passed    * in different orders due to gimp_matrix3_transform_point()    */
name|min
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|points
index|[
name|i
index|]
operator|.
name|y
operator|<
name|points
index|[
name|min
index|]
operator|.
name|y
condition|)
name|min
operator|=
name|i
expr_stmt|;
block|}
name|tx
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
name|ty
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|=
name|points
index|[
name|min
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|=
name|points
index|[
name|min
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
name|min
index|]
operator|.
name|x
operator|=
name|tx
expr_stmt|;
name|points
index|[
name|min
index|]
operator|.
name|y
operator|=
name|ty
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|theta
decl_stmt|,
name|theta_m
init|=
literal|2
operator|*
name|G_PI
decl_stmt|;
name|gdouble
name|theta_v
init|=
literal|0
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|min
operator|=
literal|3
expr_stmt|;
for|for
control|(
name|j
operator|=
name|i
init|;
name|j
operator|<
literal|4
condition|;
name|j
operator|++
control|)
block|{
name|gdouble
name|sy
init|=
name|points
index|[
name|j
index|]
operator|.
name|y
operator|-
name|points
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|y
decl_stmt|;
name|gdouble
name|sx
init|=
name|points
index|[
name|j
index|]
operator|.
name|x
operator|-
name|points
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|x
decl_stmt|;
name|theta
operator|=
name|atan2
argument_list|(
name|sy
argument_list|,
name|sx
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|theta
operator|<
name|theta_m
operator|)
operator|&&
operator|(
operator|(
name|theta
operator|>
name|theta_v
operator|)
operator|||
operator|(
operator|(
name|theta
operator|==
name|theta_v
operator|)
operator|&&
operator|(
name|sx
operator|>
literal|0
operator|)
operator|)
operator|)
condition|)
block|{
name|theta_m
operator|=
name|theta
expr_stmt|;
name|min
operator|=
name|j
expr_stmt|;
block|}
block|}
name|theta_v
operator|=
name|theta_m
expr_stmt|;
name|tx
operator|=
name|points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|ty
operator|=
name|points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|x
operator|=
name|points
index|[
name|min
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
name|i
index|]
operator|.
name|y
operator|=
name|points
index|[
name|min
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
name|min
index|]
operator|.
name|x
operator|=
name|tx
expr_stmt|;
name|points
index|[
name|min
index|]
operator|.
name|y
operator|=
name|ty
expr_stmt|;
block|}
comment|/* reverse the order of points */
name|tx
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|x
expr_stmt|;
name|ty
operator|=
name|points
index|[
literal|0
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|3
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
literal|0
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|3
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
literal|3
index|]
operator|.
name|x
operator|=
name|tx
expr_stmt|;
name|points
index|[
literal|3
index|]
operator|.
name|y
operator|=
name|ty
expr_stmt|;
name|tx
operator|=
name|points
index|[
literal|1
index|]
operator|.
name|x
expr_stmt|;
name|ty
operator|=
name|points
index|[
literal|1
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|x
operator|=
name|points
index|[
literal|2
index|]
operator|.
name|x
expr_stmt|;
name|points
index|[
literal|1
index|]
operator|.
name|y
operator|=
name|points
index|[
literal|2
index|]
operator|.
name|y
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|x
operator|=
name|tx
expr_stmt|;
name|points
index|[
literal|2
index|]
operator|.
name|y
operator|=
name|ty
expr_stmt|;
comment|/* now, find the largest rectangle using the method described in    * "Computing the Largest Inscribed Isothetic Rectangle" by    * D. Hsu, J. Snoeyink, et al.    */
comment|/*  first create an array of edges  */
name|cxmin
operator|=
name|cxmax
operator|=
name|points
index|[
literal|3
index|]
operator|.
name|x
expr_stmt|;
name|cymin
operator|=
name|cymax
operator|=
name|points
index|[
literal|3
index|]
operator|.
name|y
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|a
operator|=
name|points
operator|+
literal|3
operator|,
name|b
operator|=
name|points
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
operator|,
name|a
operator|=
name|b
operator|,
name|b
operator|++
control|)
block|{
if|if
condition|(
name|G_UNLIKELY
argument_list|(
name|i
operator|==
literal|0
argument_list|)
condition|)
block|{
name|cxmin
operator|=
name|cxmax
operator|=
name|a
operator|->
name|x
expr_stmt|;
name|cymin
operator|=
name|cymax
operator|=
name|a
operator|->
name|y
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|a
operator|->
name|x
operator|<
name|cxmin
condition|)
name|cxmin
operator|=
name|a
operator|->
name|x
expr_stmt|;
if|if
condition|(
name|a
operator|->
name|x
operator|>
name|cxmax
condition|)
name|cxmax
operator|=
name|a
operator|->
name|x
expr_stmt|;
if|if
condition|(
name|a
operator|->
name|y
operator|<
name|cymin
condition|)
name|cymin
operator|=
name|a
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|a
operator|->
name|y
operator|>
name|cymax
condition|)
name|cymax
operator|=
name|a
operator|->
name|y
expr_stmt|;
block|}
name|edge_init
argument_list|(
name|edges
operator|+
name|i
argument_list|,
name|a
argument_list|,
name|b
argument_list|)
expr_stmt|;
block|}
name|xint
operator|=
name|g_new
argument_list|(
name|Point
argument_list|,
name|cymax
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
name|cymax
condition|;
name|i
operator|++
control|)
block|{
name|xint
index|[
name|i
index|]
operator|.
name|x
operator|=
name|intersect_x
argument_list|(
name|edges
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|xint
index|[
name|i
index|]
operator|.
name|y
operator|=
name|i
expr_stmt|;
block|}
name|top
operator|=
name|find_edge
argument_list|(
name|edges
argument_list|,
name|cxmin
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|bottom
operator|=
name|find_edge
argument_list|(
name|edges
argument_list|,
name|cxmin
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|xi
operator|=
name|cxmin
init|;
name|xi
operator|<
name|cxmax
condition|;
name|xi
operator|++
control|)
block|{
name|gint
name|ylo
decl_stmt|,
name|yhi
decl_stmt|;
name|ymin
operator|=
name|intersect_y
argument_list|(
name|top
argument_list|,
name|xi
argument_list|)
expr_stmt|;
name|ymax
operator|=
name|intersect_y
argument_list|(
name|bottom
argument_list|,
name|xi
argument_list|)
expr_stmt|;
for|for
control|(
name|ylo
operator|=
name|ymax
init|;
name|ylo
operator|>
name|ymin
condition|;
name|ylo
operator|--
control|)
block|{
for|for
control|(
name|yhi
operator|=
name|ymin
init|;
name|yhi
operator|<
name|ymax
condition|;
name|yhi
operator|++
control|)
block|{
if|if
condition|(
name|yhi
operator|>
name|ylo
condition|)
block|{
name|gint
name|xlo
decl_stmt|,
name|xhi
decl_stmt|;
name|gint
name|xright
decl_stmt|;
name|gint
name|height
decl_stmt|,
name|width
decl_stmt|,
name|fixed_width
decl_stmt|;
name|gint
name|area
decl_stmt|;
name|xlo
operator|=
name|xint
index|[
name|ylo
index|]
operator|.
name|x
expr_stmt|;
name|xhi
operator|=
name|xint
index|[
name|yhi
index|]
operator|.
name|x
expr_stmt|;
name|xright
operator|=
name|MIN
argument_list|(
name|xlo
argument_list|,
name|xhi
argument_list|)
expr_stmt|;
name|height
operator|=
name|yhi
operator|-
name|ylo
expr_stmt|;
name|width
operator|=
name|xright
operator|-
name|xi
expr_stmt|;
if|if
condition|(
name|aspect
operator|!=
literal|0
condition|)
block|{
name|fixed_width
operator|=
operator|(
name|gint
operator|)
name|ceil
argument_list|(
operator|(
name|gdouble
operator|)
name|height
operator|*
name|aspect
argument_list|)
expr_stmt|;
if|if
condition|(
name|fixed_width
operator|<=
name|width
condition|)
name|width
operator|=
name|fixed_width
expr_stmt|;
else|else
name|width
operator|=
literal|0
expr_stmt|;
block|}
name|area
operator|=
name|width
operator|*
name|height
expr_stmt|;
if|if
condition|(
name|area
operator|>
name|maxarea
condition|)
block|{
name|maxarea
operator|=
name|area
expr_stmt|;
operator|*
name|x1
operator|=
name|xi
expr_stmt|;
operator|*
name|y1
operator|=
name|ylo
expr_stmt|;
operator|*
name|x2
operator|=
name|xi
operator|+
name|width
expr_stmt|;
operator|*
name|y2
operator|=
name|ylo
operator|+
name|height
expr_stmt|;
block|}
block|}
block|}
block|}
if|if
condition|(
name|xi
operator|==
name|top
operator|->
name|xmax
condition|)
name|top
operator|=
name|find_edge
argument_list|(
name|edges
argument_list|,
name|xi
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|xi
operator|==
name|bottom
operator|->
name|xmax
condition|)
name|bottom
operator|=
name|find_edge
argument_list|(
name|edges
argument_list|,
name|xi
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|xint
argument_list|)
expr_stmt|;
comment|/* translate back the vertices */
operator|*
name|x1
operator|=
operator|*
name|x1
operator|-
operator|(
operator|(
operator|-
name|ax
operator|)
operator|*
literal|2
operator|)
expr_stmt|;
operator|*
name|y1
operator|=
operator|*
name|y1
operator|-
operator|(
operator|(
operator|-
name|ay
operator|)
operator|*
literal|2
operator|)
expr_stmt|;
operator|*
name|x2
operator|=
operator|*
name|x2
operator|-
operator|(
operator|(
operator|-
name|ax
operator|)
operator|*
literal|2
operator|)
expr_stmt|;
operator|*
name|y2
operator|=
operator|*
name|y2
operator|-
operator|(
operator|(
operator|-
name|ay
operator|)
operator|*
literal|2
operator|)
expr_stmt|;
block|}
end_function

end_unit

