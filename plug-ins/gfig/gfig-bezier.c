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
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"gfig.h"
end_include

begin_include
include|#
directive|include
file|"gfig-line.h"
end_include

begin_include
include|#
directive|include
file|"gfig-dobject.h"
end_include

begin_include
include|#
directive|include
file|"gfig-dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|FP_PNT_MAX
define|#
directive|define
name|FP_PNT_MAX
value|10
end_define

begin_typedef
DECL|typedef|fp_pnt
typedef|typedef
name|gdouble
argument_list|(
operator|*
name|fp_pnt
argument_list|)
index|[
literal|2
index|]
expr_stmt|;
end_typedef

begin_decl_stmt
DECL|variable|bezier_closed
specifier|static
name|gboolean
name|bezier_closed
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|bezier_line_frame
specifier|static
name|gboolean
name|bezier_line_frame
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fp_pnt_cnt
specifier|static
name|int
name|fp_pnt_cnt
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fp_pnt_chunk
specifier|static
name|int
name|fp_pnt_chunk
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fp_pnt_pnts
specifier|static
name|gdouble
modifier|*
name|fp_pnt_pnts
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tmp_bezier
name|GfigObject
modifier|*
name|tmp_bezier
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|tmp_bezier
comment|/* Needed when drawing bezier curves */
end_comment

begin_function_decl
specifier|static
name|void
name|fp_pnt_start
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fp_pnt_add
parameter_list|(
name|gdouble
name|p1
parameter_list|,
name|gdouble
name|p2
parameter_list|,
name|gdouble
name|p3
parameter_list|,
name|gdouble
name|p4
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
modifier|*
name|d_bz_get_array
parameter_list|(
name|gint
modifier|*
name|sz
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|d_bz_line
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|DrawBezier
parameter_list|(
name|fp_pnt
name|points
parameter_list|,
name|gint
name|np
parameter_list|,
name|gdouble
name|mid
parameter_list|,
name|gint
name|depth
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|d_paint_bezier
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GfigObject
modifier|*
name|d_copy_bezier
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|d_update_bezier
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|fp_pnt_start (void)
name|fp_pnt_start
parameter_list|(
name|void
parameter_list|)
block|{
name|fp_pnt_cnt
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Add a line segment to collection array */
end_comment

begin_function
specifier|static
name|void
DECL|function|fp_pnt_add (gdouble p1,gdouble p2,gdouble p3,gdouble p4)
name|fp_pnt_add
parameter_list|(
name|gdouble
name|p1
parameter_list|,
name|gdouble
name|p2
parameter_list|,
name|gdouble
name|p3
parameter_list|,
name|gdouble
name|p4
parameter_list|)
block|{
if|if
condition|(
operator|!
name|fp_pnt_pnts
condition|)
block|{
name|fp_pnt_pnts
operator|=
name|g_new0
argument_list|(
name|gdouble
argument_list|,
name|FP_PNT_MAX
argument_list|)
expr_stmt|;
name|fp_pnt_chunk
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|(
name|fp_pnt_cnt
operator|+
literal|4
operator|)
operator|/
name|FP_PNT_MAX
operator|)
operator|>=
name|fp_pnt_chunk
condition|)
block|{
comment|/* more space pls */
name|fp_pnt_chunk
operator|++
expr_stmt|;
name|fp_pnt_pnts
operator|=
name|g_renew
argument_list|(
name|gdouble
argument_list|,
name|fp_pnt_pnts
argument_list|,
name|fp_pnt_chunk
operator|*
name|FP_PNT_MAX
argument_list|)
expr_stmt|;
block|}
name|fp_pnt_pnts
index|[
name|fp_pnt_cnt
operator|++
index|]
operator|=
name|p1
expr_stmt|;
name|fp_pnt_pnts
index|[
name|fp_pnt_cnt
operator|++
index|]
operator|=
name|p2
expr_stmt|;
name|fp_pnt_pnts
index|[
name|fp_pnt_cnt
operator|++
index|]
operator|=
name|p3
expr_stmt|;
name|fp_pnt_pnts
index|[
name|fp_pnt_cnt
operator|++
index|]
operator|=
name|p4
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
modifier|*
DECL|function|d_bz_get_array (gint * sz)
name|d_bz_get_array
parameter_list|(
name|gint
modifier|*
name|sz
parameter_list|)
block|{
operator|*
name|sz
operator|=
name|fp_pnt_cnt
expr_stmt|;
return|return
name|fp_pnt_pnts
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_bz_line (void)
name|d_bz_line
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|x0
decl_stmt|,
name|y0
decl_stmt|,
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|g_assert
argument_list|(
operator|(
name|fp_pnt_cnt
operator|%
literal|4
operator|)
operator|==
literal|0
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
name|fp_pnt_cnt
condition|;
name|i
operator|+=
literal|4
control|)
block|{
name|x0
operator|=
name|fp_pnt_pnts
index|[
name|i
index|]
expr_stmt|;
name|y0
operator|=
name|fp_pnt_pnts
index|[
name|i
operator|+
literal|1
index|]
expr_stmt|;
name|x1
operator|=
name|fp_pnt_pnts
index|[
name|i
operator|+
literal|2
index|]
expr_stmt|;
name|y1
operator|=
name|fp_pnt_pnts
index|[
name|i
operator|+
literal|3
index|]
expr_stmt|;
name|gfig_draw_line
argument_list|(
name|x0
argument_list|,
name|y0
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  Return points to plot */
end_comment

begin_comment
comment|/* Terminate by point with DBL_MAX, DBL_MAX */
end_comment

begin_function
specifier|static
name|void
DECL|function|DrawBezier (fp_pnt points,gint np,gdouble mid,gint depth)
name|DrawBezier
parameter_list|(
name|fp_pnt
name|points
parameter_list|,
name|gint
name|np
parameter_list|,
name|gdouble
name|mid
parameter_list|,
name|gint
name|depth
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|x0
init|=
literal|0
decl_stmt|,
name|y0
init|=
literal|0
decl_stmt|,
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|fp_pnt
name|left
decl_stmt|;
name|fp_pnt
name|right
decl_stmt|;
if|if
condition|(
name|depth
operator|==
literal|0
condition|)
comment|/* draw polyline */
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|np
condition|;
name|i
operator|++
control|)
block|{
name|x1
operator|=
operator|(
name|int
operator|)
name|points
index|[
name|i
index|]
index|[
literal|0
index|]
expr_stmt|;
name|y1
operator|=
operator|(
name|int
operator|)
name|points
index|[
name|i
index|]
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|i
operator|>
literal|0
operator|&&
operator|(
name|x1
operator|!=
name|x0
operator|||
name|y1
operator|!=
name|y0
operator|)
condition|)
block|{
comment|/* Add pnts up */
name|fp_pnt_add
argument_list|(
operator|(
name|gdouble
operator|)
name|x0
argument_list|,
operator|(
name|gdouble
operator|)
name|y0
argument_list|,
operator|(
name|gdouble
operator|)
name|x1
argument_list|,
operator|(
name|gdouble
operator|)
name|y1
argument_list|)
expr_stmt|;
block|}
name|x0
operator|=
name|x1
expr_stmt|;
name|y0
operator|=
name|y1
expr_stmt|;
block|}
block|}
else|else
comment|/* subdivide control points at mid */
block|{
name|left
operator|=
operator|(
name|fp_pnt
operator|)
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|np
operator|*
literal|2
argument_list|)
expr_stmt|;
name|right
operator|=
operator|(
name|fp_pnt
operator|)
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|np
operator|*
literal|2
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
name|np
condition|;
name|i
operator|++
control|)
block|{
name|right
index|[
name|i
index|]
index|[
literal|0
index|]
operator|=
name|points
index|[
name|i
index|]
index|[
literal|0
index|]
expr_stmt|;
name|right
index|[
name|i
index|]
index|[
literal|1
index|]
operator|=
name|points
index|[
name|i
index|]
index|[
literal|1
index|]
expr_stmt|;
block|}
name|left
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|right
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|left
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|right
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
for|for
control|(
name|j
operator|=
name|np
operator|-
literal|1
init|;
name|j
operator|>=
literal|1
condition|;
name|j
operator|--
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|j
condition|;
name|i
operator|++
control|)
block|{
name|right
index|[
name|i
index|]
index|[
literal|0
index|]
operator|=
operator|(
literal|1
operator|-
name|mid
operator|)
operator|*
name|right
index|[
name|i
index|]
index|[
literal|0
index|]
operator|+
name|mid
operator|*
name|right
index|[
name|i
operator|+
literal|1
index|]
index|[
literal|0
index|]
expr_stmt|;
name|right
index|[
name|i
index|]
index|[
literal|1
index|]
operator|=
operator|(
literal|1
operator|-
name|mid
operator|)
operator|*
name|right
index|[
name|i
index|]
index|[
literal|1
index|]
operator|+
name|mid
operator|*
name|right
index|[
name|i
operator|+
literal|1
index|]
index|[
literal|1
index|]
expr_stmt|;
block|}
name|left
index|[
name|np
operator|-
name|j
index|]
index|[
literal|0
index|]
operator|=
name|right
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|left
index|[
name|np
operator|-
name|j
index|]
index|[
literal|1
index|]
operator|=
name|right
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
block|}
if|if
condition|(
name|depth
operator|>
literal|0
condition|)
block|{
name|DrawBezier
argument_list|(
name|left
argument_list|,
name|np
argument_list|,
name|mid
argument_list|,
name|depth
operator|-
literal|1
argument_list|)
expr_stmt|;
name|DrawBezier
argument_list|(
name|right
argument_list|,
name|np
argument_list|,
name|mid
argument_list|,
name|depth
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|left
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|right
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|d_draw_bezier (GfigObject * obj)
name|d_draw_bezier
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|spnt
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
argument_list|(
operator|*
name|line_pnts
argument_list|)
index|[
literal|2
index|]
expr_stmt|;
name|spnt
operator|=
name|obj
operator|->
name|points
expr_stmt|;
comment|/* First count the number of points */
for|for
control|(
name|spnt
operator|=
name|obj
operator|->
name|points
init|;
name|spnt
condition|;
name|spnt
operator|=
name|spnt
operator|->
name|next
control|)
name|seg_count
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|seg_count
condition|)
return|return;
comment|/* no-line */
name|line_pnts
operator|=
operator|(
name|fp_pnt
operator|)
name|g_new0
argument_list|(
name|gdouble
argument_list|,
literal|2
operator|*
name|seg_count
operator|+
literal|1
argument_list|)
expr_stmt|;
comment|/* Go around all the points drawing a line from one to the next */
for|for
control|(
name|spnt
operator|=
name|obj
operator|->
name|points
init|;
name|spnt
condition|;
name|spnt
operator|=
name|spnt
operator|->
name|next
control|)
block|{
name|draw_sqr
argument_list|(
operator|&
name|spnt
operator|->
name|pnt
argument_list|,
name|obj
operator|==
name|gfig_context
operator|->
name|selected_obj
argument_list|)
expr_stmt|;
name|line_pnts
index|[
name|i
index|]
index|[
literal|0
index|]
operator|=
name|spnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
name|line_pnts
index|[
name|i
index|]
index|[
literal|1
index|]
operator|=
name|spnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
comment|/* Generate an array of doubles which are the control points */
if|if
condition|(
name|bezier_line_frame
operator|&&
name|tmp_bezier
condition|)
block|{
name|fp_pnt_start
argument_list|()
expr_stmt|;
name|DrawBezier
argument_list|(
name|line_pnts
argument_list|,
name|seg_count
argument_list|,
literal|0.5
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|d_bz_line
argument_list|()
expr_stmt|;
block|}
name|fp_pnt_start
argument_list|()
expr_stmt|;
name|DrawBezier
argument_list|(
name|line_pnts
argument_list|,
name|seg_count
argument_list|,
literal|0.5
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|d_bz_line
argument_list|()
expr_stmt|;
comment|/*bezier4 (line_pnts, seg_count, 20);*/
name|g_free
argument_list|(
name|line_pnts
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_bezier (GfigObject * obj)
name|d_paint_bezier
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
name|gdouble
modifier|*
name|line_pnts
decl_stmt|;
name|gdouble
argument_list|(
operator|*
name|bz_line_pnts
argument_list|)
index|[
literal|2
index|]
expr_stmt|;
name|DobjPoints
modifier|*
name|spnt
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
comment|/* First count the number of points */
for|for
control|(
name|spnt
operator|=
name|obj
operator|->
name|points
init|;
name|spnt
condition|;
name|spnt
operator|=
name|spnt
operator|->
name|next
control|)
name|seg_count
operator|++
expr_stmt|;
if|if
condition|(
operator|!
name|seg_count
condition|)
return|return;
comment|/* no-line */
name|bz_line_pnts
operator|=
operator|(
name|fp_pnt
operator|)
name|g_new0
argument_list|(
name|gdouble
argument_list|,
literal|2
operator|*
name|seg_count
operator|+
literal|1
argument_list|)
expr_stmt|;
comment|/* Go around all the points drawing a line from one to the next */
for|for
control|(
name|spnt
operator|=
name|obj
operator|->
name|points
init|;
name|spnt
condition|;
name|spnt
operator|=
name|spnt
operator|->
name|next
control|)
block|{
name|bz_line_pnts
index|[
name|i
index|]
index|[
literal|0
index|]
operator|=
name|spnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
name|bz_line_pnts
index|[
name|i
index|]
index|[
literal|1
index|]
operator|=
name|spnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
name|i
operator|++
expr_stmt|;
block|}
name|fp_pnt_start
argument_list|()
expr_stmt|;
name|DrawBezier
argument_list|(
name|bz_line_pnts
argument_list|,
name|seg_count
argument_list|,
literal|0.5
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|line_pnts
operator|=
name|d_bz_get_array
argument_list|(
operator|&
name|i
argument_list|)
expr_stmt|;
comment|/* Scale before drawing */
if|if
condition|(
name|selvals
operator|.
name|scaletoimage
condition|)
name|scale_to_original_xy
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
else|else
name|scale_to_xy
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
name|obj
operator|->
name|style
operator|.
name|paint_type
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
name|g_free
argument_list|(
name|bz_line_pnts
argument_list|)
expr_stmt|;
comment|/* Don't free line_pnts - may need again */
block|}
end_function

begin_function
specifier|static
name|GfigObject
modifier|*
DECL|function|d_copy_bezier (GfigObject * obj)
name|d_copy_bezier
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
name|GfigObject
modifier|*
name|np
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|->
name|type
operator|==
name|BEZIER
argument_list|)
expr_stmt|;
name|np
operator|=
name|d_new_object
argument_list|(
name|BEZIER
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
name|np
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
name|np
operator|->
name|type_data
operator|=
name|obj
operator|->
name|type_data
expr_stmt|;
return|return
name|np
return|;
block|}
end_function

begin_function
name|void
DECL|function|d_bezier_object_class_init (void)
name|d_bezier_object_class_init
parameter_list|(
name|void
parameter_list|)
block|{
name|GfigObjectClass
modifier|*
name|class
init|=
operator|&
name|dobj_class
index|[
name|BEZIER
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|BEZIER
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"BEZIER"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_bezier
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_bezier
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_bezier
expr_stmt|;
name|class
operator|->
name|update
operator|=
name|d_update_bezier
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_update_bezier (GdkPoint * pnt)
name|d_update_bezier
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|s_pnt
decl_stmt|,
modifier|*
name|l_pnt
decl_stmt|;
name|gint
name|saved_cnt_pnt
init|=
name|selvals
operator|.
name|opts
operator|.
name|showcontrol
decl_stmt|;
name|g_assert
argument_list|(
name|tmp_bezier
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* Undraw last one then draw new one */
name|s_pnt
operator|=
name|tmp_bezier
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|s_pnt
condition|)
return|return;
comment|/* No points */
comment|/* Hack - turn off cnt points in draw routine    */
if|if
condition|(
operator|(
name|l_pnt
operator|=
name|s_pnt
operator|->
name|next
operator|)
condition|)
block|{
comment|/* Undraw */
while|while
condition|(
name|l_pnt
operator|->
name|next
condition|)
block|{
name|l_pnt
operator|=
name|l_pnt
operator|->
name|next
expr_stmt|;
block|}
name|draw_circle
argument_list|(
operator|&
name|l_pnt
operator|->
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|selvals
operator|.
name|opts
operator|.
name|showcontrol
operator|=
literal|0
expr_stmt|;
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
name|l_pnt
operator|->
name|pnt
operator|=
operator|*
name|pnt
expr_stmt|;
block|}
else|else
block|{
comment|/* Radius is a few pixels away */
comment|/* First edge point */
name|d_pnt_add_line
argument_list|(
name|tmp_bezier
argument_list|,
name|pnt
operator|->
name|x
argument_list|,
name|pnt
operator|->
name|y
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|l_pnt
operator|=
name|s_pnt
operator|->
name|next
expr_stmt|;
block|}
comment|/* draw it */
name|selvals
operator|.
name|opts
operator|.
name|showcontrol
operator|=
literal|0
expr_stmt|;
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
name|selvals
operator|.
name|opts
operator|.
name|showcontrol
operator|=
name|saved_cnt_pnt
expr_stmt|;
comment|/* Realy draw the control points */
name|draw_circle
argument_list|(
operator|&
name|l_pnt
operator|->
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_bezier_start (GdkPoint * pnt,gboolean shift_down)
name|d_bezier_start
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gboolean
name|shift_down
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tmp_bezier
condition|)
block|{
comment|/* New curve */
name|tmp_bezier
operator|=
name|obj_creating
operator|=
name|d_new_object
argument_list|(
name|BEZIER
argument_list|,
name|pnt
operator|->
name|x
argument_list|,
name|pnt
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|d_bezier_end (GdkPoint * pnt,gboolean shift_down)
name|d_bezier_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gboolean
name|shift_down
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|l_pnt
decl_stmt|;
if|if
condition|(
operator|!
name|tmp_bezier
condition|)
block|{
name|tmp_bezier
operator|=
name|obj_creating
expr_stmt|;
block|}
name|l_pnt
operator|=
name|tmp_bezier
operator|->
name|points
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|l_pnt
condition|)
return|return;
if|if
condition|(
name|shift_down
condition|)
block|{
comment|/* Undraw circle on last pnt */
while|while
condition|(
name|l_pnt
operator|->
name|next
condition|)
block|{
name|l_pnt
operator|=
name|l_pnt
operator|->
name|next
expr_stmt|;
block|}
if|if
condition|(
name|l_pnt
condition|)
block|{
name|draw_circle
argument_list|(
operator|&
name|l_pnt
operator|->
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|draw_sqr
argument_list|(
operator|&
name|l_pnt
operator|->
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|bezier_closed
condition|)
block|{
name|gboolean
name|tmp_frame
init|=
name|bezier_line_frame
decl_stmt|;
comment|/* if closed then add first point */
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
name|d_pnt_add_line
argument_list|(
name|tmp_bezier
argument_list|,
name|tmp_bezier
operator|->
name|points
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|tmp_bezier
operator|->
name|points
operator|->
name|pnt
operator|.
name|y
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* Final has no frame */
name|bezier_line_frame
operator|=
name|FALSE
expr_stmt|;
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
name|bezier_line_frame
operator|=
name|tmp_frame
expr_stmt|;
comment|/* What is was */
block|}
elseif|else
if|if
condition|(
name|bezier_line_frame
condition|)
block|{
name|gboolean
name|tmp_frame
init|=
name|bezier_line_frame
decl_stmt|;
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
name|bezier_line_frame
operator|=
name|FALSE
expr_stmt|;
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
name|bezier_line_frame
operator|=
name|tmp_frame
expr_stmt|;
comment|/* What is was */
block|}
name|add_to_all_obj
argument_list|(
name|gfig_context
operator|->
name|current_obj
argument_list|,
name|obj_creating
argument_list|)
expr_stmt|;
block|}
comment|/* small mem leak if !l_pnt ? */
name|tmp_bezier
operator|=
name|NULL
expr_stmt|;
name|obj_creating
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|tmp_bezier
operator|->
name|points
operator|->
name|next
condition|)
block|{
name|draw_circle
argument_list|(
operator|&
name|tmp_bezier
operator|->
name|points
operator|->
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|draw_sqr
argument_list|(
operator|&
name|tmp_bezier
operator|->
name|points
operator|->
name|pnt
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
name|d_pnt_add_line
argument_list|(
name|tmp_bezier
argument_list|,
name|pnt
operator|->
name|x
argument_list|,
name|pnt
operator|->
name|y
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|d_draw_bezier
argument_list|(
name|tmp_bezier
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_options_bezier (GtkWidget * notebook)
name|tool_options_bezier
parameter_list|(
name|GtkWidget
modifier|*
name|notebook
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Closed"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|bezier_closed
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|toggle
argument_list|,
name|_
argument_list|(
literal|"Close curve on completion"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|bezier_closed
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Show Line Frame"
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|bezier_line_frame
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|toggle
argument_list|,
name|_
argument_list|(
literal|"Draws lines between the control points. "
literal|"Only during curve creation"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|bezier_line_frame
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

