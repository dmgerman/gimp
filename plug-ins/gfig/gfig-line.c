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
file|"gfig-dobject.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function
name|GfigObject
modifier|*
DECL|function|d_copy_line (GfigObject * obj)
name|d_copy_line
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
name|GfigObject
modifier|*
name|nl
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|->
name|type
operator|==
name|LINE
argument_list|)
expr_stmt|;
name|nl
operator|=
name|d_new_object
argument_list|(
name|LINE
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
name|nl
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
name|nl
return|;
block|}
end_function

begin_function
name|void
DECL|function|d_draw_line (GfigObject * obj)
name|d_draw_line
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
name|DobjPoints
modifier|*
name|epnt
decl_stmt|;
name|spnt
operator|=
name|obj
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|spnt
condition|)
return|return;
comment|/* End-of-line */
name|epnt
operator|=
name|spnt
operator|->
name|next
expr_stmt|;
while|while
condition|(
name|spnt
operator|&&
name|epnt
condition|)
block|{
name|draw_sqr
argument_list|(
operator|&
name|spnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
comment|/* Go around all the points drawing a line from one to the next */
name|gfig_draw_line
argument_list|(
name|spnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|spnt
operator|->
name|pnt
operator|.
name|y
argument_list|,
name|epnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|epnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
expr_stmt|;
name|spnt
operator|=
name|epnt
expr_stmt|;
name|epnt
operator|=
name|epnt
operator|->
name|next
expr_stmt|;
block|}
name|draw_sqr
argument_list|(
operator|&
name|spnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_paint_line (GfigObject * obj)
name|d_paint_line
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
name|line_pnts
index|[
name|i
operator|++
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
operator|++
index|]
operator|=
name|spnt
operator|->
name|pnt
operator|.
name|y
expr_stmt|;
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
name|gfig_context
operator|->
name|drawable_id
argument_list|,
name|seg_count
operator|*
literal|2
argument_list|,
name|line_pnts
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_free_select
argument_list|(
name|gfig_context
operator|->
name|image_id
argument_list|,
name|seg_count
operator|*
literal|2
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

begin_comment
comment|/* Create a new line object. starting at the x, y point might add styles  * later.  */
end_comment

begin_function
name|void
DECL|function|d_line_object_class_init (void)
name|d_line_object_class_init
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
name|LINE
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|LINE
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"Line"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_line
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_line
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_line
expr_stmt|;
block|}
end_function

begin_comment
comment|/* You guessed it delete the object !*/
end_comment

begin_comment
comment|/* static void d_delete_line (Dobject *obj) {   g_assert (obj != NULL);   * First free the list of points - then the object itself *   d_delete_dobjpoints (obj->points);   g_free (obj); } */
end_comment

begin_comment
comment|/* Add a point to a line (given x, y)  * pos = 0 = head  * pos = -1 = tail  * 0< pos = nth position  */
end_comment

begin_function
name|void
DECL|function|d_pnt_add_line (GfigObject * obj,gint x,gint y,gint pos)
name|d_pnt_add_line
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|pos
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|npnts
init|=
name|new_dobjpoint
argument_list|(
name|x
argument_list|,
name|y
argument_list|)
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
name|pos
condition|)
block|{
comment|/* Add to head */
name|npnts
operator|->
name|next
operator|=
name|obj
operator|->
name|points
expr_stmt|;
name|obj
operator|->
name|points
operator|=
name|npnts
expr_stmt|;
block|}
else|else
block|{
name|DobjPoints
modifier|*
name|pnt
init|=
name|obj
operator|->
name|points
decl_stmt|;
comment|/* Go down chain until the end if pos */
while|while
condition|(
name|pos
operator|<
literal|0
operator|||
name|pos
operator|--
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|pnt
operator|->
name|next
operator|)
operator|||
operator|!
name|pos
condition|)
block|{
name|npnts
operator|->
name|next
operator|=
name|pnt
operator|->
name|next
expr_stmt|;
name|pnt
operator|->
name|next
operator|=
name|npnts
expr_stmt|;
break|break;
block|}
else|else
block|{
name|pnt
operator|=
name|pnt
operator|->
name|next
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/* Update end point of line */
end_comment

begin_function
name|void
DECL|function|d_update_line (GdkPoint * pnt)
name|d_update_line
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|spnt
decl_stmt|,
modifier|*
name|epnt
decl_stmt|;
comment|/* Get last but one segment and undraw it -    * Then draw new segment in.    * always dealing with the static object.    */
comment|/* Get start of segments */
name|spnt
operator|=
name|obj_creating
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|spnt
condition|)
return|return;
comment|/* No points */
if|if
condition|(
operator|(
name|epnt
operator|=
name|spnt
operator|->
name|next
operator|)
condition|)
block|{
comment|/* undraw  current */
comment|/* Draw square on point */
name|draw_circle
argument_list|(
operator|&
name|epnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|gfig_context
operator|->
name|preview
operator|->
name|window
argument_list|,
comment|/*gfig_context->preview->style->bg_gc[GTK_STATE_NORMAL],*/
name|gfig_gc
argument_list|,
name|spnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|spnt
operator|->
name|pnt
operator|.
name|y
argument_list|,
name|epnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|epnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|epnt
argument_list|)
expr_stmt|;
block|}
comment|/* draw new */
comment|/* Draw circle on point */
name|draw_circle
argument_list|(
name|pnt
argument_list|)
expr_stmt|;
name|epnt
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
name|gdk_draw_line
argument_list|(
name|gfig_context
operator|->
name|preview
operator|->
name|window
argument_list|,
comment|/*gfig_context->preview->style->bg_gc[GTK_STATE_NORMAL],*/
name|gfig_gc
argument_list|,
name|spnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|spnt
operator|->
name|pnt
operator|.
name|y
argument_list|,
name|epnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|epnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
expr_stmt|;
name|spnt
operator|->
name|next
operator|=
name|epnt
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_line_start (GdkPoint * pnt,gboolean shift_down)
name|d_line_start
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
name|obj_creating
operator|||
operator|!
name|shift_down
condition|)
block|{
comment|/* Draw square on point */
comment|/* Must delete obj_creating if we have one */
name|obj_creating
operator|=
name|d_new_object
argument_list|(
name|LINE
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
else|else
block|{
comment|/* Contniuation */
name|d_update_line
argument_list|(
name|pnt
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|d_line_end (GdkPoint * pnt,gboolean shift_down)
name|d_line_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gboolean
name|shift_down
parameter_list|)
block|{
comment|/* Undraw the last circle */
name|draw_circle
argument_list|(
name|pnt
argument_list|)
expr_stmt|;
if|if
condition|(
name|shift_down
condition|)
block|{
if|if
condition|(
name|tmp_line
condition|)
block|{
name|GdkPoint
name|tmp_pnt
init|=
operator|*
name|pnt
decl_stmt|;
if|if
condition|(
name|need_to_scale
condition|)
block|{
name|tmp_pnt
operator|.
name|x
operator|=
name|pnt
operator|->
name|x
operator|*
name|scale_x_factor
expr_stmt|;
name|tmp_pnt
operator|.
name|y
operator|=
name|pnt
operator|->
name|y
operator|*
name|scale_y_factor
expr_stmt|;
block|}
name|d_pnt_add_line
argument_list|(
name|tmp_line
argument_list|,
name|tmp_pnt
operator|.
name|x
argument_list|,
name|tmp_pnt
operator|.
name|y
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|free_one_obj
argument_list|(
name|obj_creating
argument_list|)
expr_stmt|;
comment|/* Must free obj_creating */
block|}
else|else
block|{
name|tmp_line
operator|=
name|obj_creating
expr_stmt|;
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
name|obj_creating
operator|=
name|d_new_object
argument_list|(
name|LINE
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
else|else
block|{
if|if
condition|(
name|tmp_line
condition|)
block|{
name|GdkPoint
name|tmp_pnt
init|=
operator|*
name|pnt
decl_stmt|;
if|if
condition|(
name|need_to_scale
condition|)
block|{
name|tmp_pnt
operator|.
name|x
operator|=
name|pnt
operator|->
name|x
operator|*
name|scale_x_factor
expr_stmt|;
name|tmp_pnt
operator|.
name|y
operator|=
name|pnt
operator|->
name|y
operator|*
name|scale_y_factor
expr_stmt|;
block|}
name|d_pnt_add_line
argument_list|(
name|tmp_line
argument_list|,
name|tmp_pnt
operator|.
name|x
argument_list|,
name|tmp_pnt
operator|.
name|y
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|free_one_obj
argument_list|(
name|obj_creating
argument_list|)
expr_stmt|;
comment|/* Must free obj_creating */
block|}
else|else
block|{
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
name|obj_creating
operator|=
name|NULL
expr_stmt|;
name|tmp_line
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*gtk_widget_queue_draw (gfig_context->preview);*/
block|}
end_function

end_unit

