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
file|"gfig-dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|d_draw_spiral
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
name|d_paint_spiral
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
name|d_copy_spiral
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|spiral_num_turns
specifier|static
name|gint
name|spiral_num_turns
init|=
literal|4
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|spiral_num_turns
comment|/* Default to 4 turns */
end_comment

begin_decl_stmt
DECL|variable|spiral_toggle
specifier|static
name|gint
name|spiral_toggle
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|spiral_toggle
comment|/* 0 = clockwise -1 = anti-clockwise */
end_comment

begin_function
name|void
DECL|function|tool_options_spiral (GtkWidget * notebook)
name|tool_options_spiral
parameter_list|(
name|GtkWidget
modifier|*
name|notebook
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|sides
decl_stmt|;
name|sides
operator|=
name|num_sides_widget
argument_list|(
name|_
argument_list|(
literal|"Spiral Number of Turns"
argument_list|)
argument_list|,
operator|&
name|spiral_num_turns
argument_list|,
operator|&
name|spiral_toggle
argument_list|,
literal|1
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|sides
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_draw_spiral (GfigObject * obj)
name|d_draw_spiral
parameter_list|(
name|GfigObject
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
name|radius_pnt
decl_stmt|;
name|gint16
name|shift_x
decl_stmt|;
name|gint16
name|shift_y
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
name|gdouble
name|offset_angle
decl_stmt|;
name|gdouble
name|sp_cons
decl_stmt|;
name|gint
name|loop
decl_stmt|;
name|GdkPoint
name|start_pnt
decl_stmt|;
name|GdkPoint
name|first_pnt
decl_stmt|;
name|gboolean
name|do_line
init|=
name|FALSE
decl_stmt|;
name|gint
name|clock_wise
init|=
literal|1
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
comment|/* First point is the center */
comment|/* Just draw a control point around it */
name|draw_sqr
argument_list|(
operator|&
name|center_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
comment|/* Next point defines the radius */
name|radius_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vetices */
if|if
condition|(
operator|!
name|radius_pnt
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_warning
argument_list|(
literal|"Internal error in spiral - no vertice point \n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
return|return;
block|}
comment|/* Other control point */
name|draw_sqr
argument_list|(
operator|&
name|radius_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
comment|/* Have center and radius - draw spiral */
name|shift_x
operator|=
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
expr_stmt|;
name|shift_y
operator|=
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
expr_stmt|;
name|radius
operator|=
name|sqrt
argument_list|(
operator|(
name|shift_x
operator|*
name|shift_x
operator|)
operator|+
operator|(
name|shift_y
operator|*
name|shift_y
operator|)
argument_list|)
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
name|clock_wise
operator|=
name|obj
operator|->
name|type_data
operator|/
name|abs
argument_list|(
name|obj
operator|->
name|type_data
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
literal|2.0
operator|*
name|G_PI
expr_stmt|;
name|sp_cons
operator|=
name|radius
operator|/
operator|(
name|obj
operator|->
name|type_data
operator|*
literal|2
operator|*
name|G_PI
operator|+
name|offset_angle
operator|)
expr_stmt|;
comment|/* Lines */
name|ang_grid
operator|=
literal|2.0
operator|*
name|G_PI
operator|/
literal|180.0
expr_stmt|;
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<=
name|abs
argument_list|(
name|obj
operator|->
name|type_data
operator|*
literal|180
argument_list|)
operator|+
name|clock_wise
operator|*
operator|(
name|gint
operator|)
name|RINT
argument_list|(
name|offset_angle
operator|/
name|ang_grid
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
expr_stmt|;
name|lx
operator|=
name|sp_cons
operator|*
name|ang_loop
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
operator|*
name|clock_wise
expr_stmt|;
name|ly
operator|=
name|sp_cons
operator|*
name|ang_loop
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
if|if
condition|(
name|do_line
condition|)
block|{
comment|/* Miss out points that come to the same location */
if|if
condition|(
name|calc_pnt
operator|.
name|x
operator|==
name|start_pnt
operator|.
name|x
operator|&&
name|calc_pnt
operator|.
name|y
operator|==
name|start_pnt
operator|.
name|y
condition|)
continue|continue;
name|gfig_draw_line
argument_list|(
name|calc_pnt
operator|.
name|x
argument_list|,
name|calc_pnt
operator|.
name|y
argument_list|,
name|start_pnt
operator|.
name|x
argument_list|,
name|start_pnt
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|do_line
operator|=
name|TRUE
expr_stmt|;
name|first_pnt
operator|=
name|calc_pnt
expr_stmt|;
block|}
name|start_pnt
operator|=
name|calc_pnt
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_spiral (GfigObject * obj)
name|d_paint_spiral
parameter_list|(
name|GfigObject
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
name|gint16
name|shift_x
decl_stmt|;
name|gint16
name|shift_y
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
name|gdouble
name|offset_angle
decl_stmt|;
name|gdouble
name|sp_cons
decl_stmt|;
name|gint
name|loop
decl_stmt|;
name|GdkPoint
name|last_pnt
decl_stmt|;
name|gint
name|clock_wise
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
name|center_pnt
operator|->
name|next
condition|)
return|return;
comment|/* no-line */
comment|/* Go around all the points drawing a line from one to the next */
name|radius_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vetices */
comment|/* Have center and radius - get lines */
name|shift_x
operator|=
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
expr_stmt|;
name|shift_y
operator|=
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
expr_stmt|;
name|radius
operator|=
name|sqrt
argument_list|(
operator|(
name|shift_x
operator|*
name|shift_x
operator|)
operator|+
operator|(
name|shift_y
operator|*
name|shift_y
operator|)
argument_list|)
expr_stmt|;
name|clock_wise
operator|=
name|obj
operator|->
name|type_data
operator|/
name|abs
argument_list|(
name|obj
operator|->
name|type_data
argument_list|)
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
literal|2.0
operator|*
name|G_PI
expr_stmt|;
name|sp_cons
operator|=
name|radius
operator|/
operator|(
name|obj
operator|->
name|type_data
operator|*
literal|2.0
operator|*
name|G_PI
operator|+
name|offset_angle
operator|)
expr_stmt|;
comment|/* Lines */
name|ang_grid
operator|=
literal|2.0
operator|*
name|G_PI
operator|/
literal|180.0
expr_stmt|;
comment|/* count - */
name|seg_count
operator|=
name|abs
argument_list|(
name|obj
operator|->
name|type_data
operator|*
literal|180.0
argument_list|)
operator|+
name|clock_wise
operator|*
operator|(
name|gint
operator|)
name|RINT
argument_list|(
name|offset_angle
operator|/
name|ang_grid
argument_list|)
expr_stmt|;
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
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<=
name|seg_count
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
name|lx
operator|=
name|sp_cons
operator|*
name|ang_loop
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
operator|*
name|clock_wise
expr_stmt|;
name|ly
operator|=
name|sp_cons
operator|*
name|ang_loop
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
name|loop
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
name|GfigObject
modifier|*
DECL|function|d_copy_spiral (GfigObject * obj)
name|d_copy_spiral
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
name|SPIRAL
argument_list|)
expr_stmt|;
name|np
operator|=
name|d_new_object
argument_list|(
name|SPIRAL
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
DECL|function|d_spiral_object_class_init (void)
name|d_spiral_object_class_init
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
name|SPIRAL
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|SPIRAL
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"Spiral"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_spiral
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_spiral
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_spiral
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_update_spiral (GdkPoint * pnt)
name|d_update_spiral
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
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
name|saved_cnt_pnt
init|=
name|selvals
operator|.
name|opts
operator|.
name|showcontrol
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
comment|/* Leave the first pnt alone -    * Edge point defines "radius"    * Only undraw if already have edge point.    */
comment|/* Hack - turn off cnt points in draw routine    * Looking back over the other update routines I could    * use this trick again and cut down on code size!    */
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
comment|/* Undraw */
name|draw_circle
argument_list|(
operator|&
name|edge_pnt
operator|->
name|pnt
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
name|d_draw_spiral
argument_list|(
name|obj_creating
argument_list|)
expr_stmt|;
name|edge_pnt
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
name|obj_creating
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
name|edge_pnt
operator|=
name|center_pnt
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
name|d_draw_spiral
argument_list|(
name|obj_creating
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
name|edge_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_spiral_start (GdkPoint * pnt,gint shift_down)
name|d_spiral_start
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
name|d_new_object
argument_list|(
name|SPIRAL
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
name|obj_creating
operator|->
name|type_data
operator|=
name|spiral_num_turns
operator|*
operator|(
operator|(
name|spiral_toggle
operator|==
literal|0
operator|)
condition|?
literal|1
else|:
operator|-
literal|1
operator|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_spiral_end (GdkPoint * pnt,gint shift_down)
name|d_spiral_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gint
name|shift_down
parameter_list|)
block|{
name|draw_circle
argument_list|(
name|pnt
argument_list|)
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
name|obj_creating
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

