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

begin_decl_stmt
DECL|variable|star_num_sides
specifier|static
name|gint
name|star_num_sides
init|=
literal|3
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|star_num_sides
comment|/* Default to three sided object */
end_comment

begin_function_decl
specifier|static
name|void
name|d_save_star
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|,
name|FILE
modifier|*
name|to
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|d_draw_star
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|d_paint_star
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Dobject
modifier|*
name|d_copy_star
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Dobject
modifier|*
name|d_new_star
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
name|gint
DECL|function|star_button_press (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|star_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
operator|(
name|event
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
operator|)
operator|&&
operator|(
name|event
operator|->
name|button
operator|==
literal|1
operator|)
condition|)
name|num_sides_dialog
argument_list|(
name|_
argument_list|(
literal|"Star Number of Points"
argument_list|)
argument_list|,
operator|&
name|star_num_sides
argument_list|,
name|NULL
argument_list|,
literal|3
argument_list|,
literal|200
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_save_star (Dobject * obj,FILE * to)
name|d_save_star
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
literal|"<STAR>\n"
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
literal|"<EXTRA>\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|to
argument_list|,
literal|"%d\n</EXTRA>\n"
argument_list|,
name|obj
operator|->
name|type_data
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|to
argument_list|,
literal|"</STAR>\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Dobject
modifier|*
DECL|function|d_load_star (FILE * from)
name|d_load_star
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
operator|!
name|strcmp
argument_list|(
literal|"<EXTRA>"
argument_list|,
name|buf
argument_list|)
condition|)
block|{
name|gint
name|nsides
init|=
literal|3
decl_stmt|;
comment|/* Number of sides - data item */
if|if
condition|(
operator|!
name|new_obj
condition|)
block|{
name|g_warning
argument_list|(
literal|"[%d] Internal load error while loading star (extra area)"
argument_list|,
name|line_no
argument_list|)
expr_stmt|;
return|return
operator|(
name|NULL
operator|)
return|;
block|}
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
expr_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|buf
argument_list|,
literal|"%d"
argument_list|,
operator|&
name|nsides
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|g_warning
argument_list|(
literal|"[%d] Internal load error while loading star (extra area scanf)"
argument_list|,
name|line_no
argument_list|)
expr_stmt|;
return|return
operator|(
name|NULL
operator|)
return|;
block|}
name|new_obj
operator|->
name|type_data
operator|=
name|nsides
expr_stmt|;
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
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
literal|"</EXTRA>"
argument_list|,
name|buf
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"[%d] Internal load error while loading star"
argument_list|,
name|line_no
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/* Go around and read the last line */
continue|continue;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
literal|"</STAR>"
argument_list|,
name|buf
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"[%d] Internal load error while loading star"
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
name|d_new_star
argument_list|(
name|xpnt
argument_list|,
name|ypnt
argument_list|)
expr_stmt|;
else|else
name|d_pnt_add_line
argument_list|(
name|new_obj
argument_list|,
name|xpnt
argument_list|,
name|ypnt
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
return|return
name|new_obj
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_draw_star (Dobject * obj)
name|d_draw_star
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
name|outer_radius_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|inner_radius_pnt
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
name|outer_radius
decl_stmt|;
name|gdouble
name|inner_radius
decl_stmt|;
name|gdouble
name|offset_angle
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
name|gint
name|do_line
init|=
literal|0
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
name|outer_radius_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vetices */
if|if
condition|(
operator|!
name|outer_radius_pnt
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_warning
argument_list|(
literal|"Internal error in star - no outer vertice point \n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
return|return;
block|}
name|inner_radius_pnt
operator|=
name|outer_radius_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vetices */
if|if
condition|(
operator|!
name|inner_radius_pnt
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_warning
argument_list|(
literal|"Internal error in star - no inner vertice point \n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
return|return;
block|}
comment|/* Other control points */
name|draw_sqr
argument_list|(
operator|&
name|outer_radius_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|draw_sqr
argument_list|(
operator|&
name|inner_radius_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
comment|/* Have center and radius - draw star */
name|shift_x
operator|=
name|outer_radius_pnt
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
name|outer_radius_pnt
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
name|outer_radius
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
comment|/* Lines */
name|ang_grid
operator|=
literal|2
operator|*
name|G_PI
operator|/
operator|(
literal|2.0
operator|*
operator|(
name|gdouble
operator|)
name|obj
operator|->
name|type_data
operator|)
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
name|shift_x
operator|=
name|inner_radius_pnt
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
name|inner_radius_pnt
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
name|inner_radius
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
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
literal|2
operator|*
name|obj
operator|->
name|type_data
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
name|offset_angle
expr_stmt|;
if|if
condition|(
name|loop
operator|%
literal|2
condition|)
block|{
name|lx
operator|=
name|inner_radius
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
name|ly
operator|=
name|inner_radius
operator|*
name|sin
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|lx
operator|=
name|outer_radius
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
name|ly
operator|=
name|outer_radius
operator|*
name|sin
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|drawing_pic
condition|)
block|{
name|gdk_draw_line
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
name|adjust_pic_coords
argument_list|(
name|calc_pnt
operator|.
name|x
argument_list|,
name|preview_width
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|calc_pnt
operator|.
name|y
argument_list|,
name|preview_height
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|start_pnt
operator|.
name|x
argument_list|,
name|preview_width
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|start_pnt
operator|.
name|y
argument_list|,
name|preview_height
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_draw_line
argument_list|(
name|gfig_preview
operator|->
name|window
argument_list|,
name|gfig_gc
argument_list|,
name|gfig_scale_x
argument_list|(
name|calc_pnt
operator|.
name|x
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|calc_pnt
operator|.
name|y
argument_list|)
argument_list|,
name|gfig_scale_x
argument_list|(
name|start_pnt
operator|.
name|x
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|start_pnt
operator|.
name|y
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|do_line
operator|=
literal|1
expr_stmt|;
name|first_pnt
operator|.
name|x
operator|=
name|calc_pnt
operator|.
name|x
expr_stmt|;
name|first_pnt
operator|.
name|y
operator|=
name|calc_pnt
operator|.
name|y
expr_stmt|;
block|}
name|start_pnt
operator|.
name|x
operator|=
name|calc_pnt
operator|.
name|x
expr_stmt|;
name|start_pnt
operator|.
name|y
operator|=
name|calc_pnt
operator|.
name|y
expr_stmt|;
block|}
comment|/* Join up */
if|if
condition|(
name|drawing_pic
condition|)
block|{
name|gdk_draw_line
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
name|adjust_pic_coords
argument_list|(
name|first_pnt
operator|.
name|x
argument_list|,
name|preview_width
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|first_pnt
operator|.
name|y
argument_list|,
name|preview_width
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|start_pnt
operator|.
name|x
argument_list|,
name|preview_width
argument_list|)
argument_list|,
name|adjust_pic_coords
argument_list|(
name|start_pnt
operator|.
name|y
argument_list|,
name|preview_width
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_draw_line
argument_list|(
name|gfig_preview
operator|->
name|window
argument_list|,
name|gfig_gc
argument_list|,
name|gfig_scale_x
argument_list|(
name|first_pnt
operator|.
name|x
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|first_pnt
operator|.
name|y
argument_list|)
argument_list|,
name|gfig_scale_x
argument_list|(
name|start_pnt
operator|.
name|x
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|start_pnt
operator|.
name|y
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_star (Dobject * obj)
name|d_paint_star
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
name|outer_radius_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|inner_radius_pnt
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
name|outer_radius
decl_stmt|;
name|gdouble
name|inner_radius
decl_stmt|;
name|gdouble
name|offset_angle
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
literal|2
operator|*
name|obj
operator|->
name|type_data
operator|+
literal|1
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
comment|/* Next point defines the radius */
name|outer_radius_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vetices */
if|if
condition|(
operator|!
name|outer_radius_pnt
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_warning
argument_list|(
literal|"Internal error in star - no outer vertice point \n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
return|return;
block|}
name|inner_radius_pnt
operator|=
name|outer_radius_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vetices */
if|if
condition|(
operator|!
name|inner_radius_pnt
condition|)
block|{
ifdef|#
directive|ifdef
name|DEBUG
name|g_warning
argument_list|(
literal|"Internal error in star - no inner vertice point \n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
return|return;
block|}
name|shift_x
operator|=
name|outer_radius_pnt
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
name|outer_radius_pnt
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
name|outer_radius
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
comment|/* Lines */
name|ang_grid
operator|=
literal|2
operator|*
name|G_PI
operator|/
operator|(
literal|2.0
operator|*
operator|(
name|gdouble
operator|)
name|obj
operator|->
name|type_data
operator|)
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
name|shift_x
operator|=
name|inner_radius_pnt
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
name|inner_radius_pnt
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
name|inner_radius
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
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
literal|2
operator|*
name|obj
operator|->
name|type_data
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
name|offset_angle
expr_stmt|;
if|if
condition|(
name|loop
operator|%
literal|2
condition|)
block|{
name|lx
operator|=
name|inner_radius
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
name|ly
operator|=
name|inner_radius
operator|*
name|sin
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|lx
operator|=
name|outer_radius
operator|*
name|cos
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
name|ly
operator|=
name|outer_radius
operator|*
name|sin
argument_list|(
name|ang_loop
argument_list|)
expr_stmt|;
block|}
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
name|Dobject
modifier|*
DECL|function|d_copy_star (Dobject * obj)
name|d_copy_star
parameter_list|(
name|Dobject
modifier|*
name|obj
parameter_list|)
block|{
name|Dobject
modifier|*
name|np
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
name|STAR
argument_list|)
expr_stmt|;
name|np
operator|=
name|d_new_star
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
specifier|static
name|Dobject
modifier|*
DECL|function|d_new_star (gint x,gint y)
name|d_new_star
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
name|STAR
expr_stmt|;
name|nobj
operator|->
name|type_data
operator|=
literal|3
expr_stmt|;
comment|/* Default to three sides 6 points*/
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
name|d_draw_star
expr_stmt|;
name|nobj
operator|->
name|loadfunc
operator|=
name|d_load_star
expr_stmt|;
name|nobj
operator|->
name|savefunc
operator|=
name|d_save_star
expr_stmt|;
name|nobj
operator|->
name|paintfunc
operator|=
name|d_paint_star
expr_stmt|;
name|nobj
operator|->
name|copyfunc
operator|=
name|d_copy_star
expr_stmt|;
return|return
name|nobj
return|;
block|}
end_function

begin_function
name|void
DECL|function|d_update_star (GdkPoint * pnt)
name|d_update_star
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
name|inner_pnt
decl_stmt|,
modifier|*
name|outer_pnt
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
comment|/* Hack - turn off cnt points in draw routine     * Looking back over the other update routines I could    * use this trick again and cut down on code size!    */
if|if
condition|(
operator|(
name|outer_pnt
operator|=
name|center_pnt
operator|->
name|next
operator|)
condition|)
block|{
comment|/* Undraw */
name|inner_pnt
operator|=
name|outer_pnt
operator|->
name|next
expr_stmt|;
name|draw_circle
argument_list|(
operator|&
name|inner_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|draw_circle
argument_list|(
operator|&
name|outer_pnt
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
name|d_draw_star
argument_list|(
name|obj_creating
argument_list|)
expr_stmt|;
name|outer_pnt
operator|->
name|pnt
operator|.
name|x
operator|=
name|pnt
operator|->
name|x
expr_stmt|;
name|outer_pnt
operator|->
name|pnt
operator|.
name|y
operator|=
name|pnt
operator|->
name|y
expr_stmt|;
name|inner_pnt
operator|->
name|pnt
operator|.
name|x
operator|=
name|pnt
operator|->
name|x
operator|+
operator|(
literal|2
operator|*
operator|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|pnt
operator|->
name|x
operator|)
operator|)
operator|/
literal|3
expr_stmt|;
name|inner_pnt
operator|->
name|pnt
operator|.
name|y
operator|=
name|pnt
operator|->
name|y
operator|+
operator|(
literal|2
operator|*
operator|(
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|pnt
operator|->
name|y
operator|)
operator|)
operator|/
literal|3
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
name|outer_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* Inner radius */
name|d_pnt_add_line
argument_list|(
name|obj_creating
argument_list|,
name|pnt
operator|->
name|x
operator|+
operator|(
literal|2
operator|*
operator|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|pnt
operator|->
name|x
operator|)
operator|)
operator|/
literal|3
argument_list|,
name|pnt
operator|->
name|y
operator|+
operator|(
literal|2
operator|*
operator|(
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|pnt
operator|->
name|y
operator|)
operator|)
operator|/
literal|3
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|inner_pnt
operator|=
name|outer_pnt
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
name|d_draw_star
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
name|outer_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|draw_circle
argument_list|(
operator|&
name|inner_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_star_start (GdkPoint * pnt,gint shift_down)
name|d_star_start
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
name|d_new_star
argument_list|(
operator|(
name|gint
operator|)
name|pnt
operator|->
name|x
argument_list|,
operator|(
name|gint
operator|)
name|pnt
operator|->
name|y
argument_list|)
expr_stmt|;
name|obj_creating
operator|->
name|type_data
operator|=
name|star_num_sides
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_star_end (GdkPoint * pnt,gint shift_down)
name|d_star_end
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

