begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gfig-line.h"
end_include

begin_include
include|#
directive|include
file|"gfig-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gfig-poly.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|poly_num_sides
specifier|static
name|gint
name|poly_num_sides
init|=
literal|3
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|poly_num_sides
comment|/* Default to three sided object */
end_comment

begin_function_decl
specifier|static
name|void
name|d_draw_poly
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GfigObject
modifier|*
name|d_copy_poly
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
name|d_update_poly
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|tool_options_poly (GtkWidget * notebook)
name|tool_options_poly
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
literal|"Regular Polygon Number of Sides"
argument_list|)
argument_list|,
operator|&
name|poly_num_sides
argument_list|,
name|NULL
argument_list|,
literal|3
argument_list|,
literal|200
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
DECL|function|d_draw_poly (GfigObject * obj,cairo_t * cr)
name|d_draw_poly
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|,
name|cairo_t
modifier|*
name|cr
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
name|gint
name|loop
decl_stmt|;
name|GdkPoint
name|start_pnt
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GdkPoint
name|first_pnt
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gboolean
name|do_line
init|=
name|FALSE
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
argument_list|,
name|obj
operator|==
name|gfig_context
operator|->
name|selected_obj
argument_list|,
name|cr
argument_list|)
expr_stmt|;
comment|/* Next point defines the radius */
name|radius_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vertices */
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
literal|"Internal error in polygon - no vertice point \n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* DEBUG */
return|return;
block|}
comment|/* Other control point */
if|if
condition|(
name|obj
operator|==
name|obj_creating
condition|)
name|draw_circle
argument_list|(
operator|&
name|radius_pnt
operator|->
name|pnt
argument_list|,
name|TRUE
argument_list|,
name|cr
argument_list|)
expr_stmt|;
else|else
name|draw_sqr
argument_list|(
operator|&
name|radius_pnt
operator|->
name|pnt
argument_list|,
name|obj
operator|==
name|gfig_context
operator|->
name|selected_obj
argument_list|,
name|cr
argument_list|)
expr_stmt|;
comment|/* Have center and radius - draw polygon */
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
name|obj
operator|->
name|type_data
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
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
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
argument_list|,
name|cr
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
name|gfig_draw_line
argument_list|(
name|first_pnt
operator|.
name|x
argument_list|,
name|first_pnt
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
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_paint_poly (GfigObject * obj)
name|d_paint_poly
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
name|gint
name|loop
decl_stmt|;
name|GdkPoint
name|first_pnt
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GdkPoint
name|last_pnt
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gboolean
name|first
init|=
name|TRUE
decl_stmt|;
name|gdouble
modifier|*
name|min_max
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
operator|||
operator|!
name|center_pnt
operator|->
name|next
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
name|min_max
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
literal|4
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
comment|/* Lines */
name|ang_grid
operator|=
literal|2.0
operator|*
name|G_PI
operator|/
operator|(
name|gdouble
operator|)
name|obj
operator|->
name|type_data
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
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
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
name|min_max
index|[
literal|0
index|]
operator|=
name|min_max
index|[
literal|2
index|]
operator|=
name|calc_pnt
operator|.
name|x
expr_stmt|;
name|min_max
index|[
literal|1
index|]
operator|=
name|min_max
index|[
literal|3
index|]
operator|=
name|calc_pnt
operator|.
name|y
expr_stmt|;
block|}
else|else
block|{
name|min_max
index|[
literal|0
index|]
operator|=
name|MIN
argument_list|(
name|min_max
index|[
literal|0
index|]
argument_list|,
name|calc_pnt
operator|.
name|x
argument_list|)
expr_stmt|;
name|min_max
index|[
literal|1
index|]
operator|=
name|MIN
argument_list|(
name|min_max
index|[
literal|1
index|]
argument_list|,
name|calc_pnt
operator|.
name|y
argument_list|)
expr_stmt|;
name|min_max
index|[
literal|2
index|]
operator|=
name|MAX
argument_list|(
name|min_max
index|[
literal|2
index|]
argument_list|,
name|calc_pnt
operator|.
name|x
argument_list|)
expr_stmt|;
name|min_max
index|[
literal|3
index|]
operator|=
name|MAX
argument_list|(
name|min_max
index|[
literal|3
index|]
argument_list|,
name|calc_pnt
operator|.
name|y
argument_list|)
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
comment|/* Scale before drawing */
if|if
condition|(
name|selvals
operator|.
name|scaletoimage
condition|)
block|{
comment|/* FIXME scale xmax and al. */
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
name|scale_to_original_xy
argument_list|(
name|min_max
argument_list|,
literal|2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|scale_to_xy
argument_list|(
name|min_max
argument_list|,
literal|2
argument_list|)
expr_stmt|;
block|}
name|gimp_context_push
argument_list|()
expr_stmt|;
name|gimp_context_set_antialias
argument_list|(
name|selopt
operator|.
name|antia
argument_list|)
expr_stmt|;
name|gimp_context_set_feather
argument_list|(
name|selopt
operator|.
name|feather
argument_list|)
expr_stmt|;
name|gimp_context_set_feather_radius
argument_list|(
name|selopt
operator|.
name|feather_radius
argument_list|,
name|selopt
operator|.
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_select_polygon
argument_list|(
name|gfig_context
operator|->
name|image_id
argument_list|,
name|selopt
operator|.
name|type
argument_list|,
name|i
argument_list|,
name|line_pnts
argument_list|)
expr_stmt|;
name|gimp_context_pop
argument_list|()
expr_stmt|;
name|paint_layer_fill
argument_list|(
name|min_max
index|[
literal|0
index|]
argument_list|,
name|min_max
index|[
literal|1
index|]
argument_list|,
name|min_max
index|[
literal|2
index|]
argument_list|,
name|min_max
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|gimp_selection_none
argument_list|(
name|gfig_context
operator|->
name|image_id
argument_list|)
expr_stmt|;
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
name|g_free
argument_list|(
name|line_pnts
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|min_max
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_poly2lines (GfigObject * obj)
name|d_poly2lines
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
comment|/* first point center */
comment|/* Next point is radius */
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
name|gint
name|loop
decl_stmt|;
name|GdkPoint
name|first_pnt
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GdkPoint
name|last_pnt
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gboolean
name|first
init|=
name|TRUE
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
condition|)
return|return;
comment|/* no-line */
comment|/* NULL out these points free later */
name|obj
operator|->
name|points
operator|=
name|NULL
expr_stmt|;
comment|/* Go around all the points creating line points */
name|radius_pnt
operator|=
name|center_pnt
operator|->
name|next
expr_stmt|;
comment|/* this defines the vertices */
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
comment|/* Lines */
name|ang_grid
operator|=
literal|2.0
operator|*
name|G_PI
operator|/
operator|(
name|gdouble
operator|)
name|obj
operator|->
name|type_data
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
for|for
control|(
name|loop
operator|=
literal|0
init|;
name|loop
operator|<
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
name|d_pnt_add_line
argument_list|(
name|obj
argument_list|,
name|calc_pnt
operator|.
name|x
argument_list|,
name|calc_pnt
operator|.
name|y
argument_list|,
literal|0
argument_list|)
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
name|d_pnt_add_line
argument_list|(
name|obj
argument_list|,
name|first_pnt
operator|.
name|x
argument_list|,
name|first_pnt
operator|.
name|y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Free old pnts */
name|d_delete_dobjpoints
argument_list|(
name|center_pnt
argument_list|)
expr_stmt|;
comment|/* hey we're a line now */
name|obj
operator|->
name|type
operator|=
name|LINE
expr_stmt|;
name|obj
operator|->
name|class
operator|=
operator|&
name|dobj_class
index|[
name|LINE
index|]
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_star2lines (GfigObject * obj)
name|d_star2lines
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
comment|/* first point center */
comment|/* Next point is radius */
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
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GdkPoint
name|last_pnt
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gboolean
name|first
init|=
name|TRUE
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
condition|)
return|return;
comment|/* no-line */
comment|/* NULL out these points free later */
name|obj
operator|->
name|points
operator|=
name|NULL
expr_stmt|;
comment|/* Go around all the points creating line points */
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
literal|2.0
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
name|d_pnt_add_line
argument_list|(
name|obj
argument_list|,
name|calc_pnt
operator|.
name|x
argument_list|,
name|calc_pnt
operator|.
name|y
argument_list|,
literal|0
argument_list|)
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
name|d_pnt_add_line
argument_list|(
name|obj
argument_list|,
name|first_pnt
operator|.
name|x
argument_list|,
name|first_pnt
operator|.
name|y
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Free old pnts */
name|d_delete_dobjpoints
argument_list|(
name|center_pnt
argument_list|)
expr_stmt|;
comment|/* hey we're a line now */
name|obj
operator|->
name|type
operator|=
name|LINE
expr_stmt|;
name|obj
operator|->
name|class
operator|=
operator|&
name|dobj_class
index|[
name|LINE
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GfigObject
modifier|*
DECL|function|d_copy_poly (GfigObject * obj)
name|d_copy_poly
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
name|POLY
argument_list|)
expr_stmt|;
name|np
operator|=
name|d_new_object
argument_list|(
name|POLY
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
DECL|function|d_poly_object_class_init (void)
name|d_poly_object_class_init
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
name|POLY
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|POLY
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"POLY"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_poly
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_poly
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_poly
expr_stmt|;
name|class
operator|->
name|update
operator|=
name|d_update_poly
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_update_poly (GdkPoint * pnt)
name|d_update_poly
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
block|}
block|}
end_function

begin_function
name|void
DECL|function|d_poly_start (GdkPoint * pnt,gboolean shift_down)
name|d_poly_start
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gboolean
name|shift_down
parameter_list|)
block|{
name|obj_creating
operator|=
name|d_new_object
argument_list|(
name|POLY
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
name|poly_num_sides
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|d_poly_end (GdkPoint * pnt,gboolean shift_down)
name|d_poly_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gboolean
name|shift_down
parameter_list|)
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
name|obj_creating
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

