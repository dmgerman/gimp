begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *   */
end_comment

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
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"gfig.h"
end_include

begin_include
include|#
directive|include
file|"gfig_poly.h"
end_include

begin_function_decl
specifier|static
name|Dobject
modifier|*
name|d_new_ellipse
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|d_save_ellipse (Dobject * obj,FILE * to)
name|d_save_ellipse
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|,
name|FILE
modifier|*
name|to
parameter_list|)
block|{
name|fprintf
argument_list|(
name|to
argument_list|,
literal|"<ELLIPSE>\n"
argument_list|)
expr_stmt|;
name|do_save_obj
argument_list|(
name|obj
argument_list|,
name|to
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|to
argument_list|,
literal|"</ELLIPSE>\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Dobject
modifier|*
DECL|function|d_load_ellipse (FILE * from)
name|d_load_ellipse
parameter_list|(
name|FILE
modifier|*
name|from
parameter_list|)
block|{
name|Dobject
modifier|*
name|new_obj
init|=
name|NULL
decl_stmt|;
name|gint
name|xpnt
decl_stmt|;
name|gint
name|ypnt
decl_stmt|;
name|gchar
name|buf
index|[
name|MAX_LOAD_LINE
index|]
decl_stmt|;
while|while
condition|(
name|get_line
argument_list|(
name|buf
argument_list|,
name|MAX_LOAD_LINE
argument_list|,
name|from
argument_list|,
literal|0
argument_list|)
condition|)
block|{
if|if
condition|(
name|sscanf
argument_list|(
name|buf
argument_list|,
literal|"%d %d"
argument_list|,
operator|&
name|xpnt
argument_list|,
operator|&
name|ypnt
argument_list|)
operator|!=
literal|2
condition|)
block|{
comment|/* Must be the end */
if|if
condition|(
name|strcmp
argument_list|(
literal|"</ELLIPSE>"
argument_list|,
name|buf
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"[%d] Internal load error while loading ellipse"
argument_list|,
name|line_no
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|new_obj
return|;
block|}
if|if
condition|(
operator|!
name|new_obj
condition|)
name|new_obj
operator|=
name|d_new_ellipse
argument_list|(
name|xpnt
argument_list|,
name|ypnt
argument_list|)
expr_stmt|;
else|else
block|{
name|new_obj
operator|->
name|points
operator|->
name|next
operator|=
name|new_dobjpoint
argument_list|(
name|xpnt
argument_list|,
name|ypnt
argument_list|)
expr_stmt|;
block|}
block|}
name|g_message
argument_list|(
literal|"[%d] Not enough points for ellipse"
argument_list|,
name|line_no
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_draw_ellipse (Dobject * obj)
name|d_draw_ellipse
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|center_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|edge_pnt
decl_stmt|;
name|gint
name|bound_wx
decl_stmt|;
name|gint
name|bound_wy
decl_stmt|;
name|gint
name|top_x
decl_stmt|;
name|gint
name|top_y
decl_stmt|;
name|center_pnt
operator|=
name|obj
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|center_pnt
condition|)
return|return;
comment|/* End-of-line */
name|edge_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|edge_pnt
condition|)
block|{
name|g_warning
argument_list|(
literal|"Internal error - ellipse no edge pnt"
argument_list|)
expr_stmt|;
block|}
name|draw_sqr
argument_list|(
operator|&
name|center_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|draw_sqr
argument_list|(
operator|&
name|edge_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|bound_wx
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
operator|*
literal|2
expr_stmt|;
name|bound_wy
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|x
condition|)
name|top_x
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
else|else
name|top_x
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|y
condition|)
name|top_y
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
else|else
name|top_y
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|drawing_pic
condition|)
block|{
name|gdk_draw_arc
argument_list|(
name|pic_preview
operator|->
name|window
argument_list|,
name|pic_preview
operator|->
name|style
operator|->
name|black_gc
argument_list|,
literal|0
argument_list|,
name|adjust_pic_coords
argument_list|(
name|top_x
argument_list|,
name|preview_width
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|top_y
argument_list|,
name|preview_height
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|bound_wx
argument_list|,
name|preview_width
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|bound_wy
argument_list|,
name|preview_height
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_draw_arc
argument_list|(
name|gfig_preview
operator|->
name|window
argument_list|,
name|gfig_gc
argument_list|,
literal|0
argument_list|,
name|gfig_scale_x
argument_list|(
name|top_x
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|top_y
argument_list|)
argument_list|,
name|gfig_scale_x
argument_list|(
name|bound_wx
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|bound_wy
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_approx_ellipse (Dobject * obj)
name|d_paint_approx_ellipse
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
name|DobjPoints
modifier|*
name|center_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|radius_pnt
decl_stmt|;
name|gdouble
name|a_axis
decl_stmt|;
name|gdouble
name|b_axis
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
name|gint
name|first
init|=
literal|1
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* count - add one to close polygon */
name|seg_count
operator|=
literal|600
expr_stmt|;
name|center_pnt
operator|=
name|obj
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|center_pnt
operator|||
operator|!
name|seg_count
condition|)
return|return;
comment|/* no-line */
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
literal|1
argument_list|)
expr_stmt|;
comment|/* Go around all the points drawing a line from one to the next */
name|radius_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vetices */
comment|/* Have center and radius - get lines */
name|a_axis
operator|=
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|radius_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|center_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
operator|)
expr_stmt|;
name|b_axis
operator|=
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|radius_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|center_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
operator|)
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
literal|600
expr_stmt|;
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
literal|600
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
expr_stmt|;
name|radius
operator|=
operator|(
name|a_axis
operator|*
name|b_axis
operator|/
operator|(
name|sqrt
argument_list|(
name|cos
argument_list|(
name|ang_loop
argument_list|)
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
operator|*
operator|(
name|b_axis
operator|*
name|b_axis
operator|-
name|a_axis
operator|*
name|a_axis
operator|)
operator|+
name|a_axis
operator|*
name|a_axis
argument_list|)
operator|)
operator|)
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
name|radius
operator|*
name|sin
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
name|calc_pnt
operator|.
name|x
operator|=
name|RINT
argument_list|(
name|lx
operator|+
name|center_pnt
operator|->
name|pnt
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
operator|->
name|pnt
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
name|last_pnt
operator|.
name|x
operator|=
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
name|last_pnt
operator|.
name|y
operator|=
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
literal|0
expr_stmt|;
block|}
block|}
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|first_pnt
operator|.
name|x
expr_stmt|;
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|first_pnt
operator|.
name|y
expr_stmt|;
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
name|gfig_drawable
argument_list|,
name|i
argument_list|,
name|line_pnts
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_free_select
argument_list|(
name|gfig_image
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
name|void
DECL|function|d_paint_ellipse (Dobject * obj)
name|d_paint_ellipse
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|center_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|edge_pnt
decl_stmt|;
name|gint
name|bound_wx
decl_stmt|;
name|gint
name|bound_wy
decl_stmt|;
name|gint
name|top_x
decl_stmt|;
name|gint
name|top_y
decl_stmt|;
name|gdouble
name|dpnts
index|[
literal|4
index|]
decl_stmt|;
comment|/* Drawing ellipse is hard .    * 1) select circle    * 2) stroke it    */
name|g_assert
argument_list|(
name|obj
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|selvals
operator|.
name|approxcircles
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"Painting ellipse as polygon\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
name|d_paint_approx_ellipse
argument_list|(
name|obj
argument_list|)
expr_stmt|;
return|return;
block|}
name|center_pnt
operator|=
name|obj
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|center_pnt
condition|)
return|return;
comment|/* End-of-line */
name|edge_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|edge_pnt
condition|)
block|{
name|g_error
argument_list|(
literal|"Internal error - ellipse no edge pnt"
argument_list|)
expr_stmt|;
block|}
name|bound_wx
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
operator|*
literal|2
expr_stmt|;
name|bound_wy
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|x
condition|)
name|top_x
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
else|else
name|top_x
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|y
condition|)
name|top_y
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
else|else
name|top_y
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
name|dpnts
index|[
literal|0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|top_x
expr_stmt|;
name|dpnts
index|[
literal|1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|top_y
expr_stmt|;
name|dpnts
index|[
literal|2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|bound_wx
expr_stmt|;
name|dpnts
index|[
literal|3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|bound_wy
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
name|dpnts
index|[
literal|0
index|]
argument_list|,
literal|2
argument_list|)
expr_stmt|;
else|else
name|scale_to_xy
argument_list|(
operator|&
name|dpnts
index|[
literal|0
index|]
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_ellipse_select
argument_list|(
name|gfig_image
argument_list|,
name|dpnts
index|[
literal|0
index|]
argument_list|,
name|dpnts
index|[
literal|1
index|]
argument_list|,
name|dpnts
index|[
literal|2
index|]
argument_list|,
name|dpnts
index|[
literal|3
index|]
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
comment|/* Is selection all we need ? */
if|if
condition|(
name|selvals
operator|.
name|painttype
operator|==
name|PAINT_SELECTION_TYPE
condition|)
return|return;
name|gimp_edit_stroke
argument_list|(
name|gfig_drawable
argument_list|)
expr_stmt|;
name|gimp_selection_clear
argument_list|(
name|gfig_image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Dobject
modifier|*
DECL|function|d_copy_ellipse (Dobject * obj)
name|d_copy_ellipse
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
if|if
condition|(
operator|!
name|obj
condition|)
return|return
operator|(
name|NULL
operator|)
return|;
name|g_assert
argument_list|(
name|obj
operator|->
name|type
operator|==
name|ELLIPSE
argument_list|)
expr_stmt|;
name|nc
operator|=
name|d_new_ellipse
argument_list|(
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
specifier|static
name|Dobject
modifier|*
DECL|function|d_new_ellipse (gint x,gint y)
name|d_new_ellipse
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|Dobject
modifier|*
name|nobj
decl_stmt|;
name|nobj
operator|=
name|g_new0
argument_list|(
name|Dobject
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|nobj
operator|->
name|type
operator|=
name|ELLIPSE
expr_stmt|;
name|nobj
operator|->
name|points
operator|=
name|new_dobjpoint
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|nobj
operator|->
name|drawfunc
operator|=
name|d_draw_ellipse
expr_stmt|;
name|nobj
operator|->
name|loadfunc
operator|=
name|d_load_ellipse
expr_stmt|;
name|nobj
operator|->
name|savefunc
operator|=
name|d_save_ellipse
expr_stmt|;
name|nobj
operator|->
name|paintfunc
operator|=
name|d_paint_ellipse
expr_stmt|;
name|nobj
operator|->
name|copyfunc
operator|=
name|d_copy_ellipse
expr_stmt|;
return|return
name|nobj
return|;
block|}
end_function

begin_function
name|void
DECL|function|d_update_ellipse (GdkPoint * pnt)
name|d_update_ellipse
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|center_pnt
decl_stmt|,
modifier|*
name|edge_pnt
decl_stmt|;
name|gint
name|bound_wx
decl_stmt|;
name|gint
name|bound_wy
decl_stmt|;
name|gint
name|top_x
decl_stmt|;
name|gint
name|top_y
decl_stmt|;
comment|/* Undraw last one then draw new one */
name|center_pnt
operator|=
name|obj_creating
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|center_pnt
condition|)
return|return;
comment|/* No points */
if|if
condition|(
operator|(
name|edge_pnt
operator|=
name|center_pnt
operator|->
name|next
operator|)
condition|)
block|{
comment|/* Undraw current */
name|bound_wx
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
operator|*
literal|2
expr_stmt|;
name|bound_wy
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|x
condition|)
name|top_x
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
else|else
name|top_x
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|y
condition|)
name|top_y
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
else|else
name|top_y
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
name|draw_circle
argument_list|(
operator|&
name|edge_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|gdk_draw_arc
argument_list|(
name|gfig_preview
operator|->
name|window
argument_list|,
name|gfig_gc
argument_list|,
literal|0
argument_list|,
name|top_x
argument_list|,
name|top_y
argument_list|,
name|bound_wx
argument_list|,
name|bound_wy
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
block|}
name|draw_circle
argument_list|(
name|pnt
argument_list|)
expr_stmt|;
name|edge_pnt
operator|=
name|new_dobjpoint
argument_list|(
name|pnt
operator|->
name|x
argument_list|,
name|pnt
operator|->
name|y
argument_list|)
expr_stmt|;
name|bound_wx
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
operator|*
literal|2
expr_stmt|;
name|bound_wy
operator|=
name|abs
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|x
condition|)
name|top_x
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
else|else
name|top_x
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|x
expr_stmt|;
if|if
condition|(
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
operator|>
name|center_pnt
operator|->
name|pnt
operator|.
name|y
condition|)
name|top_y
operator|=
literal|2
operator|*
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
else|else
name|top_y
operator|=
name|edge_pnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
name|gdk_draw_arc
argument_list|(
name|gfig_preview
operator|->
name|window
argument_list|,
name|gfig_gc
argument_list|,
literal|0
argument_list|,
name|top_x
argument_list|,
name|top_y
argument_list|,
name|bound_wx
argument_list|,
name|bound_wy
argument_list|,
literal|0
argument_list|,
literal|360
operator|*
literal|64
argument_list|)
expr_stmt|;
name|center_pnt
operator|->
name|next
operator|=
name|edge_pnt
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_ellipse_start (GdkPoint * pnt,gint shift_down)
name|d_ellipse_start
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gint
name|shift_down
parameter_list|)
block|{
name|obj_creating
operator|=
name|d_new_ellipse
argument_list|(
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
end_function

begin_function
name|void
DECL|function|d_ellipse_end (GdkPoint * pnt,gint shift_down)
name|d_ellipse_end
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
name|obj_creating
operator|->
name|points
operator|->
name|next
condition|)
block|{
comment|/* No circle created */
name|free_one_obj
argument_list|(
name|obj_creating
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|draw_circle
argument_list|(
name|pnt
argument_list|)
expr_stmt|;
name|add_to_all_obj
argument_list|(
name|current_obj
argument_list|,
name|obj_creating
argument_list|)
expr_stmt|;
block|}
name|obj_creating
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

