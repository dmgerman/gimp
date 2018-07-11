begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
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
file|"gfig-poly.h"
end_include

begin_include
include|#
directive|include
file|"gfig-circle.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|gint
name|calc_radius
parameter_list|(
name|GdkPoint
modifier|*
name|center
parameter_list|,
name|GdkPoint
modifier|*
name|edge
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|d_draw_circle
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
name|void
name|d_paint_circle
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
name|d_copy_circle
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
name|d_update_circle
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|gint
DECL|function|calc_radius (GdkPoint * center,GdkPoint * edge)
name|calc_radius
parameter_list|(
name|GdkPoint
modifier|*
name|center
parameter_list|,
name|GdkPoint
modifier|*
name|edge
parameter_list|)
block|{
name|gint
name|dx
init|=
name|center
operator|->
name|x
operator|-
name|edge
operator|->
name|x
decl_stmt|;
name|gint
name|dy
init|=
name|center
operator|->
name|y
operator|-
name|edge
operator|->
name|y
decl_stmt|;
return|return
operator|(
name|gint
operator|)
name|sqrt
argument_list|(
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_draw_circle (GfigObject * obj,cairo_t * cr)
name|d_draw_circle
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
name|edge_pnt
decl_stmt|;
name|gint
name|radius
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
return|return;
name|radius
operator|=
name|calc_radius
argument_list|(
operator|&
name|center_pnt
operator|->
name|pnt
argument_list|,
operator|&
name|edge_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
if|if
condition|(
name|obj_creating
operator|==
name|obj
condition|)
name|draw_circle
argument_list|(
operator|&
name|edge_pnt
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
name|edge_pnt
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
name|gfig_draw_arc
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|center_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|,
name|radius
argument_list|,
name|radius
argument_list|,
literal|0
argument_list|,
literal|360
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_circle (GfigObject * obj)
name|d_paint_circle
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
name|edge_pnt
decl_stmt|;
name|gint
name|radius
decl_stmt|;
name|gdouble
name|dpnts
index|[
literal|4
index|]
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
literal|"Internal error - circle no edge pnt"
argument_list|)
expr_stmt|;
block|}
name|radius
operator|=
name|calc_radius
argument_list|(
operator|&
name|center_pnt
operator|->
name|pnt
argument_list|,
operator|&
name|edge_pnt
operator|->
name|pnt
argument_list|)
expr_stmt|;
name|dpnts
index|[
literal|0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|radius
expr_stmt|;
name|dpnts
index|[
literal|1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|radius
expr_stmt|;
name|dpnts
index|[
literal|3
index|]
operator|=
name|dpnts
index|[
literal|2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|radius
operator|*
literal|2
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
if|if
condition|(
name|gfig_context_get_current_style
argument_list|()
operator|->
name|fill_type
operator|!=
name|FILL_NONE
condition|)
block|{
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
name|gimp_image_select_ellipse
argument_list|(
name|gfig_context
operator|->
name|image_id
argument_list|,
name|selopt
operator|.
name|type
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
argument_list|)
expr_stmt|;
name|gimp_context_pop
argument_list|()
expr_stmt|;
name|paint_layer_fill
argument_list|(
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|-
name|radius
argument_list|,
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|-
name|radius
argument_list|,
name|center_pnt
operator|->
name|pnt
operator|.
name|x
operator|+
name|radius
argument_list|,
name|center_pnt
operator|->
name|pnt
operator|.
name|y
operator|+
name|radius
argument_list|)
expr_stmt|;
name|gimp_selection_none
argument_list|(
name|gfig_context
operator|->
name|image_id
argument_list|)
expr_stmt|;
block|}
comment|/* Drawing a circle may be harder than stroking a circular selection,    * but we have to do it or we will not be able to draw outside of the    * layer. */
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
specifier|const
name|gdouble
name|r
init|=
name|dpnts
index|[
literal|2
index|]
operator|/
literal|2
decl_stmt|;
specifier|const
name|gdouble
name|cx
init|=
name|dpnts
index|[
literal|0
index|]
operator|+
name|r
decl_stmt|,
name|cy
init|=
name|dpnts
index|[
literal|1
index|]
operator|+
name|r
decl_stmt|;
name|gdouble
name|line_pnts
index|[
literal|362
index|]
decl_stmt|;
name|gdouble
name|angle
init|=
literal|0
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
while|while
condition|(
name|i
operator|<
literal|362
condition|)
block|{
specifier|static
specifier|const
name|gdouble
name|step
init|=
literal|2
operator|*
name|G_PI
operator|/
literal|180
decl_stmt|;
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|cx
operator|+
name|r
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
expr_stmt|;
name|line_pnts
index|[
name|i
operator|++
index|]
operator|=
name|cy
operator|+
name|r
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
expr_stmt|;
name|angle
operator|+=
name|step
expr_stmt|;
block|}
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
block|}
end_function

begin_function
specifier|static
name|GfigObject
modifier|*
DECL|function|d_copy_circle (GfigObject * obj)
name|d_copy_circle
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
name|GfigObject
modifier|*
name|nc
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|->
name|type
operator|==
name|CIRCLE
argument_list|)
expr_stmt|;
name|nc
operator|=
name|d_new_object
argument_list|(
name|CIRCLE
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
DECL|function|d_circle_object_class_init (void)
name|d_circle_object_class_init
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
name|CIRCLE
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|CIRCLE
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"CIRCLE"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_circle
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_circle
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_circle
expr_stmt|;
name|class
operator|->
name|update
operator|=
name|d_update_circle
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_update_circle (GdkPoint * pnt)
name|d_update_circle
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
name|center_pnt
operator|->
name|next
operator|=
name|edge_pnt
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|d_circle_start (GdkPoint * pnt,gboolean shift_down)
name|d_circle_start
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
name|CIRCLE
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
end_function

begin_function
name|void
DECL|function|d_circle_end (GdkPoint * pnt,gboolean shift_down)
name|d_circle_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gboolean
name|shift_down
parameter_list|)
block|{
comment|/* Under control point */
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
block|}
end_function

end_unit

