begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"gfig.h"
end_include

begin_include
include|#
directive|include
file|"gfig-dobject.h"
end_include

begin_include
include|#
directive|include
file|"gfig-line.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Distance between two lines */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|dist (gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|dist
parameter_list|(
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
block|{
name|double
name|s1
init|=
name|x1
operator|-
name|x2
decl_stmt|;
name|double
name|s2
init|=
name|y1
operator|-
name|y2
decl_stmt|;
return|return
name|sqrt
argument_list|(
name|s1
operator|*
name|s1
operator|+
name|s2
operator|*
name|s2
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* Mid point of line returned */
end_comment

begin_function
specifier|static
name|void
DECL|function|mid_point (gdouble x1,gdouble y1,gdouble x2,gdouble y2,gdouble * mx,gdouble * my)
name|mid_point
parameter_list|(
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
modifier|*
name|mx
parameter_list|,
name|gdouble
modifier|*
name|my
parameter_list|)
block|{
operator|*
name|mx
operator|=
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2.0
expr_stmt|;
operator|*
name|my
operator|=
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2.0
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Careful about infinite grads */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|line_grad (gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|line_grad
parameter_list|(
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
block|{
name|double
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|dx
operator|=
name|x1
operator|-
name|x2
expr_stmt|;
name|dy
operator|=
name|y1
operator|-
name|y2
expr_stmt|;
return|return
operator|(
name|dx
operator|==
literal|0.0
operator|)
condition|?
literal|0.0
else|:
name|dy
operator|/
name|dx
return|;
block|}
end_function

begin_comment
comment|/* Constant of line that goes through x, y with grad lgrad */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|line_cons (gdouble x,gdouble y,gdouble lgrad)
name|line_cons
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|lgrad
parameter_list|)
block|{
return|return
name|y
operator|-
name|lgrad
operator|*
name|x
return|;
block|}
end_function

begin_comment
comment|/*Get grad& const for perpend. line to given points */
end_comment

begin_function
specifier|static
name|void
DECL|function|line_definition (gdouble x1,gdouble y1,gdouble x2,gdouble y2,gdouble * lgrad,gdouble * lconst)
name|line_definition
parameter_list|(
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
modifier|*
name|lgrad
parameter_list|,
name|gdouble
modifier|*
name|lconst
parameter_list|)
block|{
name|double
name|grad1
decl_stmt|;
name|double
name|midx
decl_stmt|,
name|midy
decl_stmt|;
name|grad1
operator|=
name|line_grad
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
if|if
condition|(
name|grad1
operator|==
literal|0.0
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"Infinite grad....\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
return|return;
block|}
name|mid_point
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
operator|&
name|midx
argument_list|,
operator|&
name|midy
argument_list|)
expr_stmt|;
comment|/* Invert grad for perpen gradient */
operator|*
name|lgrad
operator|=
operator|-
literal|1.0
operator|/
name|grad1
expr_stmt|;
operator|*
name|lconst
operator|=
name|line_cons
argument_list|(
name|midx
argument_list|,
name|midy
argument_list|,
operator|*
name|lgrad
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Arch details  * Given three points get arc radius and the co-ords  * of center point.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|arc_details (GdkPoint * vert_a,GdkPoint * vert_b,GdkPoint * vert_c,GdkPoint * center_pnt,gdouble * radius)
name|arc_details
parameter_list|(
name|GdkPoint
modifier|*
name|vert_a
parameter_list|,
name|GdkPoint
modifier|*
name|vert_b
parameter_list|,
name|GdkPoint
modifier|*
name|vert_c
parameter_list|,
name|GdkPoint
modifier|*
name|center_pnt
parameter_list|,
name|gdouble
modifier|*
name|radius
parameter_list|)
block|{
comment|/* Only vertices are in whole numbers - everything else is in doubles */
name|double
name|ax
decl_stmt|,
name|ay
decl_stmt|;
name|double
name|bx
decl_stmt|,
name|by
decl_stmt|;
name|double
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|double
name|len_a
decl_stmt|,
name|len_b
decl_stmt|,
name|len_c
decl_stmt|;
name|double
name|sum_sides2
decl_stmt|;
name|double
name|area
decl_stmt|;
name|double
name|circumcircle_R
decl_stmt|;
name|double
name|line1_grad
decl_stmt|,
name|line1_const
decl_stmt|;
name|double
name|line2_grad
decl_stmt|,
name|line2_const
decl_stmt|;
name|double
name|inter_x
init|=
literal|0.0
decl_stmt|,
name|inter_y
init|=
literal|0.0
decl_stmt|;
name|int
name|got_x
init|=
literal|0
decl_stmt|,
name|got_y
init|=
literal|0
decl_stmt|;
name|ax
operator|=
call|(
name|double
call|)
argument_list|(
name|vert_a
operator|->
name|x
argument_list|)
expr_stmt|;
name|ay
operator|=
call|(
name|double
call|)
argument_list|(
name|vert_a
operator|->
name|y
argument_list|)
expr_stmt|;
name|bx
operator|=
call|(
name|double
call|)
argument_list|(
name|vert_b
operator|->
name|x
argument_list|)
expr_stmt|;
name|by
operator|=
call|(
name|double
call|)
argument_list|(
name|vert_b
operator|->
name|y
argument_list|)
expr_stmt|;
name|cx
operator|=
call|(
name|double
call|)
argument_list|(
name|vert_c
operator|->
name|x
argument_list|)
expr_stmt|;
name|cy
operator|=
call|(
name|double
call|)
argument_list|(
name|vert_c
operator|->
name|y
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"Vertices (%f,%f), (%f,%f), (%f,%f)\n"
argument_list|,
name|ax
argument_list|,
name|ay
argument_list|,
name|bx
argument_list|,
name|by
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
name|len_a
operator|=
name|dist
argument_list|(
name|ax
argument_list|,
name|ay
argument_list|,
name|bx
argument_list|,
name|by
argument_list|)
expr_stmt|;
name|len_b
operator|=
name|dist
argument_list|(
name|bx
argument_list|,
name|by
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|)
expr_stmt|;
name|len_c
operator|=
name|dist
argument_list|(
name|cx
argument_list|,
name|cy
argument_list|,
name|ax
argument_list|,
name|ay
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"len_a = %f, len_b = %f, len_c = %f\n"
argument_list|,
name|len_a
argument_list|,
name|len_b
argument_list|,
name|len_c
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
name|sum_sides2
operator|=
operator|(
name|fabs
argument_list|(
name|len_a
argument_list|)
operator|+
name|fabs
argument_list|(
name|len_b
argument_list|)
operator|+
name|fabs
argument_list|(
name|len_c
argument_list|)
operator|)
operator|/
literal|2
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"Sum sides / 2 = %f\n"
argument_list|,
name|sum_sides2
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
comment|/* Area */
name|area
operator|=
name|sqrt
argument_list|(
name|sum_sides2
operator|*
operator|(
name|sum_sides2
operator|-
name|len_a
operator|)
operator|*
operator|(
name|sum_sides2
operator|-
name|len_b
operator|)
operator|*
operator|(
name|sum_sides2
operator|-
name|len_c
operator|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"Area of triangle = %f\n"
argument_list|,
name|area
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
comment|/* Circumcircle */
name|circumcircle_R
operator|=
name|len_a
operator|*
name|len_b
operator|*
name|len_c
operator|/
operator|(
literal|4
operator|*
name|area
operator|)
expr_stmt|;
operator|*
name|radius
operator|=
name|circumcircle_R
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"Circumcircle radius = %f\n"
argument_list|,
name|circumcircle_R
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
comment|/* Deal with exceptions - I hate exceptions */
if|if
condition|(
name|ax
operator|==
name|bx
operator|||
name|ax
operator|==
name|cx
operator|||
name|cx
operator|==
name|bx
condition|)
block|{
comment|/* vert line -> mid point gives inter_x */
if|if
condition|(
name|ax
operator|==
name|bx
operator|&&
name|bx
operator|==
name|cx
condition|)
block|{
comment|/* Straight line */
name|double
name|miny
init|=
name|ay
decl_stmt|;
name|double
name|maxy
init|=
name|ay
decl_stmt|;
if|if
condition|(
name|by
operator|>
name|maxy
condition|)
name|maxy
operator|=
name|by
expr_stmt|;
if|if
condition|(
name|by
operator|<
name|miny
condition|)
name|miny
operator|=
name|by
expr_stmt|;
if|if
condition|(
name|cy
operator|>
name|maxy
condition|)
name|maxy
operator|=
name|cy
expr_stmt|;
if|if
condition|(
name|cy
operator|<
name|miny
condition|)
name|miny
operator|=
name|cy
expr_stmt|;
name|inter_y
operator|=
operator|(
name|maxy
operator|-
name|miny
operator|)
operator|/
literal|2
operator|+
name|miny
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|ax
operator|==
name|bx
condition|)
block|{
name|inter_y
operator|=
operator|(
name|ay
operator|-
name|by
operator|)
operator|/
literal|2
operator|+
name|by
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|bx
operator|==
name|cx
condition|)
block|{
name|inter_y
operator|=
operator|(
name|by
operator|-
name|cy
operator|)
operator|/
literal|2
operator|+
name|cy
expr_stmt|;
block|}
else|else
block|{
name|inter_y
operator|=
operator|(
name|cy
operator|-
name|ay
operator|)
operator|/
literal|2
operator|+
name|ay
expr_stmt|;
block|}
name|got_y
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|ay
operator|==
name|by
operator|||
name|by
operator|==
name|cy
operator|||
name|ay
operator|==
name|cy
condition|)
block|{
comment|/* Horz line -> midpoint gives inter_y */
if|if
condition|(
name|ax
operator|==
name|bx
operator|&&
name|bx
operator|==
name|cx
condition|)
block|{
comment|/* Straight line */
name|double
name|minx
init|=
name|ax
decl_stmt|;
name|double
name|maxx
init|=
name|ax
decl_stmt|;
if|if
condition|(
name|bx
operator|>
name|maxx
condition|)
name|maxx
operator|=
name|bx
expr_stmt|;
if|if
condition|(
name|bx
operator|<
name|minx
condition|)
name|minx
operator|=
name|bx
expr_stmt|;
if|if
condition|(
name|cx
operator|>
name|maxx
condition|)
name|maxx
operator|=
name|cx
expr_stmt|;
if|if
condition|(
name|cx
operator|<
name|minx
condition|)
name|minx
operator|=
name|cx
expr_stmt|;
name|inter_x
operator|=
operator|(
name|maxx
operator|-
name|minx
operator|)
operator|/
literal|2
operator|+
name|minx
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|ay
operator|==
name|by
condition|)
block|{
name|inter_x
operator|=
operator|(
name|ax
operator|-
name|bx
operator|)
operator|/
literal|2
operator|+
name|bx
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|by
operator|==
name|cy
condition|)
block|{
name|inter_x
operator|=
operator|(
name|bx
operator|-
name|cx
operator|)
operator|/
literal|2
operator|+
name|cx
expr_stmt|;
block|}
else|else
block|{
name|inter_x
operator|=
operator|(
name|cx
operator|-
name|ax
operator|)
operator|/
literal|2
operator|+
name|ax
expr_stmt|;
block|}
name|got_x
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|got_x
operator|||
operator|!
name|got_y
condition|)
block|{
comment|/* At least two of the lines are not parallel to the axis */
comment|/*first line */
if|if
condition|(
name|ax
operator|!=
name|bx
operator|&&
name|ay
operator|!=
name|by
condition|)
name|line_definition
argument_list|(
name|ax
argument_list|,
name|ay
argument_list|,
name|bx
argument_list|,
name|by
argument_list|,
operator|&
name|line1_grad
argument_list|,
operator|&
name|line1_const
argument_list|)
expr_stmt|;
else|else
name|line_definition
argument_list|(
name|ax
argument_list|,
name|ay
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|,
operator|&
name|line1_grad
argument_list|,
operator|&
name|line1_const
argument_list|)
expr_stmt|;
comment|/* second line */
if|if
condition|(
name|bx
operator|!=
name|cx
operator|&&
name|by
operator|!=
name|cy
condition|)
name|line_definition
argument_list|(
name|bx
argument_list|,
name|by
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|,
operator|&
name|line2_grad
argument_list|,
operator|&
name|line2_const
argument_list|)
expr_stmt|;
else|else
name|line_definition
argument_list|(
name|ax
argument_list|,
name|ay
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|,
operator|&
name|line2_grad
argument_list|,
operator|&
name|line2_const
argument_list|)
expr_stmt|;
block|}
comment|/* Intersection point */
if|if
condition|(
operator|!
name|got_x
condition|)
name|inter_x
operator|=
comment|/*rint*/
operator|(
operator|(
name|line2_const
operator|-
name|line1_const
operator|)
operator|/
operator|(
name|line1_grad
operator|-
name|line2_grad
operator|)
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|got_y
condition|)
name|inter_y
operator|=
comment|/*rint*/
operator|(
operator|(
name|line1_grad
operator|*
name|inter_x
operator|+
name|line1_const
operator|)
operator|)
expr_stmt|;
name|center_pnt
operator|->
name|x
operator|=
operator|(
name|gint
operator|)
name|inter_x
expr_stmt|;
name|center_pnt
operator|->
name|y
operator|=
operator|(
name|gint
operator|)
name|inter_y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|arc_angle (GdkPoint * pnt,GdkPoint * center)
name|arc_angle
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|GdkPoint
modifier|*
name|center
parameter_list|)
block|{
comment|/* Get angle (in degress) of point given origin of center */
name|gint16
name|shift_x
decl_stmt|;
name|gint16
name|shift_y
decl_stmt|;
name|gdouble
name|offset_angle
decl_stmt|;
name|shift_x
operator|=
name|pnt
operator|->
name|x
operator|-
name|center
operator|->
name|x
expr_stmt|;
name|shift_y
operator|=
operator|-
name|pnt
operator|->
name|y
operator|+
name|center
operator|->
name|y
expr_stmt|;
name|offset_angle
operator|=
name|atan2
argument_list|(
name|shift_y
argument_list|,
name|shift_x
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset_angle
operator|<
literal|0
condition|)
name|offset_angle
operator|+=
literal|2
operator|*
name|G_PI
expr_stmt|;
return|return
name|offset_angle
operator|*
literal|360
operator|/
operator|(
literal|2
operator|*
name|G_PI
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|arc_drawing_details (Dobject * obj,gdouble * minang,GdkPoint * center_pnt,gdouble * arcang,gdouble * radius,gint draw_cnts,gint do_scale)
name|arc_drawing_details
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|,
name|gdouble
modifier|*
name|minang
parameter_list|,
name|GdkPoint
modifier|*
name|center_pnt
parameter_list|,
name|gdouble
modifier|*
name|arcang
parameter_list|,
name|gdouble
modifier|*
name|radius
parameter_list|,
name|gint
name|draw_cnts
parameter_list|,
name|gint
name|do_scale
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|pnt1
init|=
name|NULL
decl_stmt|;
name|DobjPoints
modifier|*
name|pnt2
init|=
name|NULL
decl_stmt|;
name|DobjPoints
modifier|*
name|pnt3
init|=
name|NULL
decl_stmt|;
name|DobjPoints
name|dpnts
index|[
literal|3
index|]
decl_stmt|;
name|gdouble
name|ang1
decl_stmt|,
name|ang2
decl_stmt|,
name|ang3
decl_stmt|;
name|gdouble
name|maxang
decl_stmt|;
name|pnt1
operator|=
name|obj
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|pnt1
condition|)
return|return;
comment|/* Not fully drawn */
name|pnt2
operator|=
name|pnt1
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|pnt2
condition|)
return|return;
comment|/* Not fully drawn */
name|pnt3
operator|=
name|pnt2
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|pnt3
condition|)
return|return;
comment|/* Still not fully drawn */
if|if
condition|(
name|draw_cnts
condition|)
block|{
name|draw_sqr
argument_list|(
operator|&
name|pnt1
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|draw_sqr
argument_list|(
operator|&
name|pnt2
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|draw_sqr
argument_list|(
operator|&
name|pnt3
operator|->
name|pnt
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|do_scale
condition|)
block|{
comment|/* Adjust pnts for scaling */
comment|/* Warning struct copies here! and casting to double<-> int */
comment|/* Too complex fix me - to much hacking */
name|gdouble
name|xy
index|[
literal|2
index|]
decl_stmt|;
name|int
name|j
decl_stmt|;
name|dpnts
index|[
literal|0
index|]
operator|=
operator|*
name|pnt1
expr_stmt|;
name|dpnts
index|[
literal|1
index|]
operator|=
operator|*
name|pnt2
expr_stmt|;
name|dpnts
index|[
literal|2
index|]
operator|=
operator|*
name|pnt3
expr_stmt|;
name|pnt1
operator|=
operator|&
name|dpnts
index|[
literal|0
index|]
expr_stmt|;
name|pnt2
operator|=
operator|&
name|dpnts
index|[
literal|1
index|]
expr_stmt|;
name|pnt3
operator|=
operator|&
name|dpnts
index|[
literal|2
index|]
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
block|{
name|xy
index|[
literal|0
index|]
operator|=
name|dpnts
index|[
name|j
index|]
operator|.
name|pnt
operator|.
name|x
expr_stmt|;
name|xy
index|[
literal|1
index|]
operator|=
name|dpnts
index|[
name|j
index|]
operator|.
name|pnt
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|selvals
operator|.
name|scaletoimage
condition|)
name|scale_to_original_xy
argument_list|(
operator|&
name|xy
index|[
literal|0
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
else|else
name|scale_to_xy
argument_list|(
operator|&
name|xy
index|[
literal|0
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|dpnts
index|[
name|j
index|]
operator|.
name|pnt
operator|.
name|x
operator|=
name|xy
index|[
literal|0
index|]
expr_stmt|;
name|dpnts
index|[
name|j
index|]
operator|.
name|pnt
operator|.
name|y
operator|=
name|xy
index|[
literal|1
index|]
expr_stmt|;
block|}
block|}
name|arc_details
argument_list|(
operator|&
name|pnt1
operator|->
name|pnt
argument_list|,
operator|&
name|pnt2
operator|->
name|pnt
argument_list|,
operator|&
name|pnt3
operator|->
name|pnt
argument_list|,
name|center_pnt
argument_list|,
name|radius
argument_list|)
expr_stmt|;
name|ang1
operator|=
name|arc_angle
argument_list|(
operator|&
name|pnt1
operator|->
name|pnt
argument_list|,
name|center_pnt
argument_list|)
expr_stmt|;
name|ang2
operator|=
name|arc_angle
argument_list|(
operator|&
name|pnt2
operator|->
name|pnt
argument_list|,
name|center_pnt
argument_list|)
expr_stmt|;
name|ang3
operator|=
name|arc_angle
argument_list|(
operator|&
name|pnt3
operator|->
name|pnt
argument_list|,
name|center_pnt
argument_list|)
expr_stmt|;
comment|/* Find min/max angle */
name|maxang
operator|=
name|ang1
expr_stmt|;
if|if
condition|(
name|ang3
operator|>
name|maxang
condition|)
name|maxang
operator|=
name|ang3
expr_stmt|;
operator|*
name|minang
operator|=
name|ang1
expr_stmt|;
if|if
condition|(
name|ang3
operator|<
operator|*
name|minang
condition|)
operator|*
name|minang
operator|=
name|ang3
expr_stmt|;
if|if
condition|(
name|ang2
operator|>
operator|*
name|minang
operator|&&
name|ang2
operator|<
name|maxang
condition|)
operator|*
name|arcang
operator|=
name|maxang
operator|-
operator|*
name|minang
expr_stmt|;
else|else
operator|*
name|arcang
operator|=
name|maxang
operator|-
operator|*
name|minang
operator|-
literal|360
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_draw_arc (Dobject * obj)
name|d_draw_arc
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
block|{
name|GdkPoint
name|center_pnt
decl_stmt|;
name|gdouble
name|radius
decl_stmt|,
name|minang
decl_stmt|,
name|arcang
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|obj
condition|)
return|return;
name|arc_drawing_details
argument_list|(
name|obj
argument_list|,
operator|&
name|minang
argument_list|,
operator|&
name|center_pnt
argument_list|,
operator|&
name|arcang
argument_list|,
operator|&
name|radius
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gfig_draw_arc
argument_list|(
name|center_pnt
operator|.
name|x
argument_list|,
name|center_pnt
operator|.
name|y
argument_list|,
name|radius
argument_list|,
name|radius
argument_list|,
name|minang
argument_list|,
name|arcang
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_arc (Dobject * obj)
name|d_paint_arc
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
block|{
comment|/* first point center */
comment|/* Next point is radius */
name|gdouble
modifier|*
name|line_pnts
decl_stmt|;
name|gint
name|seg_count
init|=
literal|0
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|gdouble
name|ang_grid
decl_stmt|;
name|gdouble
name|ang_loop
decl_stmt|;
name|gdouble
name|radius
decl_stmt|;
name|gint
name|loop
decl_stmt|;
name|GdkPoint
name|first_pnt
decl_stmt|,
name|last_pnt
decl_stmt|;
name|gboolean
name|first
init|=
name|TRUE
decl_stmt|;
name|GdkPoint
name|center_pnt
decl_stmt|;
name|gdouble
name|minang
decl_stmt|,
name|arcang
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|obj
condition|)
return|return;
comment|/* No cnt pnts& must scale */
name|arc_drawing_details
argument_list|(
name|obj
argument_list|,
operator|&
name|minang
argument_list|,
operator|&
name|center_pnt
argument_list|,
operator|&
name|arcang
argument_list|,
operator|&
name|radius
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|seg_count
operator|=
literal|360
expr_stmt|;
comment|/* Should make a smoth-ish curve */
comment|/* +3 because we MIGHT do pie selection */
name|line_pnts
operator|=
name|g_new0
argument_list|(
name|gdouble
argument_list|,
literal|2
operator|*
name|seg_count
operator|+
literal|3
argument_list|)
expr_stmt|;
comment|/* Lines */
name|ang_grid
operator|=
literal|2
operator|*
name|G_PI
operator|/
operator|(
name|gdouble
operator|)
literal|360
expr_stmt|;
if|if
condition|(
name|arcang
operator|<
literal|0.0
condition|)
block|{
comment|/* Swap - since we always draw anti-clock wise */
name|minang
operator|+=
name|arcang
expr_stmt|;
name|arcang
operator|=
operator|-
name|arcang
expr_stmt|;
block|}
name|minang
operator|=
name|minang
operator|*
operator|(
literal|2
operator|*
name|G_PI
operator|/
literal|360
operator|)
expr_stmt|;
comment|/* min ang is in degrees - need in rads*/
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
name|abs
argument_list|(
operator|(
name|gint
operator|)
name|arcang
argument_list|)
condition|;
name|loop
operator|++
control|)
block|{
name|gdouble
name|lx
decl_stmt|,
name|ly
decl_stmt|;
name|GdkPoint
name|calc_pnt
decl_stmt|;
name|ang_loop
operator|=
operator|(
name|gdouble
operator|)
name|loop
operator|*
name|ang_grid
operator|+
name|minang
expr_stmt|;
name|lx
operator|=
name|radius
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
name|ly
operator|=
operator|-
name|radius
operator|*
name|sin
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
comment|/* y grows down screen and angs measured from x clockwise */
name|calc_pnt
operator|.
name|x
operator|=
name|RINT
argument_list|(
name|lx
operator|+
name|center_pnt
operator|.
name|x
argument_list|)
expr_stmt|;
name|calc_pnt
operator|.
name|y
operator|=
name|RINT
argument_list|(
name|ly
operator|+
name|center_pnt
operator|.
name|y
argument_list|)
expr_stmt|;
comment|/* Miss out duped pnts */
if|if
condition|(
operator|!
name|first
condition|)
block|{
if|if
condition|(
name|calc_pnt
operator|.
name|x
operator|==
name|last_pnt
operator|.
name|x
operator|&&
name|calc_pnt
operator|.
name|y
operator|==
name|last_pnt
operator|.
name|y
condition|)
block|{
continue|continue;
block|}
block|}
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|calc_pnt
operator|.
name|x
expr_stmt|;
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|calc_pnt
operator|.
name|y
expr_stmt|;
name|last_pnt
operator|=
name|calc_pnt
expr_stmt|;
if|if
condition|(
name|first
condition|)
block|{
name|first_pnt
operator|=
name|calc_pnt
expr_stmt|;
name|first
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
comment|/* Reverse line if approp */
if|if
condition|(
name|selvals
operator|.
name|reverselines
condition|)
name|reverse_pairs_list
argument_list|(
operator|&
name|line_pnts
index|[
literal|0
index|]
argument_list|,
name|i
operator|/
literal|2
argument_list|)
expr_stmt|;
comment|/* One go */
if|if
condition|(
name|selvals
operator|.
name|painttype
operator|==
name|PAINT_BRUSH_TYPE
condition|)
block|{
name|gfig_paint
argument_list|(
name|selvals
operator|.
name|brshtype
argument_list|,
name|gfig_context
operator|->
name|drawable_id
argument_list|,
name|i
argument_list|,
name|line_pnts
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|selopt
operator|.
name|as_pie
condition|)
block|{
comment|/* Add center point - cause a pie like selection... */
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|center_pnt
operator|.
name|x
expr_stmt|;
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|center_pnt
operator|.
name|y
expr_stmt|;
block|}
name|gimp_free_select
argument_list|(
name|gfig_context
operator|->
name|image_id
argument_list|,
name|i
argument_list|,
name|line_pnts
argument_list|,
name|selopt
operator|.
name|type
argument_list|,
name|selopt
operator|.
name|antia
argument_list|,
name|selopt
operator|.
name|feather
argument_list|,
name|selopt
operator|.
name|feather_radius
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|line_pnts
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Dobject
modifier|*
DECL|function|d_copy_arc (Dobject * obj)
name|d_copy_arc
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
block|{
name|Dobject
modifier|*
name|nc
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|->
name|type
operator|==
name|ARC
argument_list|)
expr_stmt|;
name|nc
operator|=
name|d_new_object
argument_list|(
name|ARC
argument_list|,
name|obj
operator|->
name|points
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|obj
operator|->
name|points
operator|->
name|pnt
operator|.
name|y
argument_list|)
expr_stmt|;
name|nc
operator|->
name|points
operator|->
name|next
operator|=
name|d_copy_dobjpoints
argument_list|(
name|obj
operator|->
name|points
operator|->
name|next
argument_list|)
expr_stmt|;
return|return
name|nc
return|;
block|}
end_function

begin_function
name|void
DECL|function|d_arc_object_class_init ()
name|d_arc_object_class_init
parameter_list|()
block|{
name|DobjClass
modifier|*
name|class
init|=
operator|&
name|dobj_class
index|[
name|ARC
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|ARC
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"Arc"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_arc
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_arc
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_arc
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_update_arc (GdkPoint * pnt)
name|d_update_arc
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|pnt1
init|=
name|NULL
decl_stmt|;
name|DobjPoints
modifier|*
name|pnt2
init|=
name|NULL
decl_stmt|;
name|DobjPoints
modifier|*
name|pnt3
init|=
name|NULL
decl_stmt|;
comment|/* First two points as line only become arch when third    * point is placed on canvas.    */
name|pnt1
operator|=
name|obj_creating
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|pnt1
operator|||
operator|!
operator|(
name|pnt2
operator|=
name|pnt1
operator|->
name|next
operator|)
operator|||
operator|!
operator|(
name|pnt3
operator|=
name|pnt2
operator|->
name|next
operator|)
condition|)
block|{
name|d_update_line
argument_list|(
name|pnt
argument_list|)
expr_stmt|;
return|return;
comment|/* Not fully drawn */
block|}
comment|/* Update a real curve */
comment|/* Nothing to be done ... */
block|}
end_function

begin_function
name|void
DECL|function|d_arc_start (GdkPoint * pnt,gint shift_down)
name|d_arc_start
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gint
name|shift_down
parameter_list|)
block|{
comment|/* Draw lines to start with -- then convert to an arc */
if|if
condition|(
operator|!
name|tmp_line
condition|)
name|draw_sqr
argument_list|(
name|pnt
argument_list|)
expr_stmt|;
name|d_line_start
argument_list|(
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* TRUE means multiple pointed line */
block|}
end_function

begin_function
name|void
DECL|function|d_arc_end (GdkPoint * pnt,gint shift_down)
name|d_arc_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gint
name|shift_down
parameter_list|)
block|{
comment|/* Under contrl point */
if|if
condition|(
operator|!
name|tmp_line
operator|||
operator|!
name|tmp_line
operator|->
name|points
operator|||
operator|!
name|tmp_line
operator|->
name|points
operator|->
name|next
condition|)
block|{
comment|/* No arc created  - yet. Must have three points */
name|d_line_end
argument_list|(
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Complete arc */
comment|/* Convert to an arc ... */
name|tmp_line
operator|->
name|type
operator|=
name|ARC
expr_stmt|;
name|tmp_line
operator|->
name|class
operator|=
operator|&
name|dobj_class
index|[
name|ARC
index|]
expr_stmt|;
name|d_line_end
argument_list|(
name|pnt
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*d_draw_line (newarc);  Should undraw line */
if|if
condition|(
name|need_to_scale
condition|)
block|{
name|selvals
operator|.
name|scaletoimage
operator|=
literal|0
expr_stmt|;
block|}
comment|/*d_draw_arc (newarc);*/
name|gtk_widget_queue_draw
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|need_to_scale
condition|)
block|{
name|selvals
operator|.
name|scaletoimage
operator|=
literal|1
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

