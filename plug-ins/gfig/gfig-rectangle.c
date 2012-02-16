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
file|"gfig-rectangle.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|d_draw_rectangle
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
name|d_paint_rectangle
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
name|d_copy_rectangle
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
name|d_update_rectangle
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
DECL|function|d_draw_rectangle (GfigObject * obj,cairo_t * cr)
name|d_draw_rectangle
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
name|first_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|second_pnt
decl_stmt|;
name|gint
name|xmin
decl_stmt|,
name|ymin
decl_stmt|;
name|gint
name|xmax
decl_stmt|,
name|ymax
decl_stmt|;
name|first_pnt
operator|=
name|obj
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|first_pnt
condition|)
return|return;
comment|/* End-of-line */
name|draw_sqr
argument_list|(
operator|&
name|first_pnt
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
name|second_pnt
operator|=
name|first_pnt
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|second_pnt
condition|)
return|return;
if|if
condition|(
name|obj
operator|==
name|obj_creating
condition|)
name|draw_circle
argument_list|(
operator|&
name|second_pnt
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
name|second_pnt
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
name|xmin
operator|=
name|MIN
argument_list|(
name|gfig_scale_x
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
argument_list|,
name|gfig_scale_x
argument_list|(
name|second_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
argument_list|)
expr_stmt|;
name|ymin
operator|=
name|MIN
argument_list|(
name|gfig_scale_y
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|second_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
argument_list|)
expr_stmt|;
name|xmax
operator|=
name|MAX
argument_list|(
name|gfig_scale_x
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
argument_list|,
name|gfig_scale_x
argument_list|(
name|second_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
argument_list|)
expr_stmt|;
name|ymax
operator|=
name|MAX
argument_list|(
name|gfig_scale_y
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
argument_list|,
name|gfig_scale_y
argument_list|(
name|second_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|xmin
operator|+
literal|.5
argument_list|,
name|ymin
operator|+
literal|.5
argument_list|,
name|xmax
operator|-
name|xmin
argument_list|,
name|ymax
operator|-
name|ymin
argument_list|)
expr_stmt|;
name|draw_item
argument_list|(
name|cr
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_rectangle (GfigObject * obj)
name|d_paint_rectangle
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|first_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|second_pnt
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
comment|/* Drawing rectangles is hard .    * 1) select rectangle    * 2) stroke it    */
name|first_pnt
operator|=
name|obj
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|first_pnt
condition|)
return|return;
comment|/* End-of-line */
name|second_pnt
operator|=
name|first_pnt
operator|->
name|next
expr_stmt|;
if|if
condition|(
operator|!
name|second_pnt
condition|)
block|{
name|g_error
argument_list|(
literal|"Internal error - rectangle no second pnt"
argument_list|)
expr_stmt|;
block|}
name|dpnts
index|[
literal|0
index|]
operator|=
operator|(
name|gdouble
operator|)
name|MIN
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|second_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
expr_stmt|;
name|dpnts
index|[
literal|1
index|]
operator|=
operator|(
name|gdouble
operator|)
name|MIN
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|,
name|second_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|)
expr_stmt|;
name|dpnts
index|[
literal|2
index|]
operator|=
operator|(
name|gdouble
operator|)
name|MAX
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|,
name|second_pnt
operator|->
name|pnt
operator|.
name|x
argument_list|)
expr_stmt|;
name|dpnts
index|[
literal|3
index|]
operator|=
operator|(
name|gdouble
operator|)
name|MAX
argument_list|(
name|first_pnt
operator|->
name|pnt
operator|.
name|y
argument_list|,
name|second_pnt
operator|->
name|pnt
operator|.
name|y
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
name|gimp_context_push
argument_list|()
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
name|gimp_image_select_rectangle
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
operator|-
name|dpnts
index|[
literal|0
index|]
argument_list|,
name|dpnts
index|[
literal|3
index|]
operator|-
name|dpnts
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|gimp_context_pop
argument_list|()
expr_stmt|;
name|paint_layer_fill
argument_list|(
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
name|gimp_edit_stroke
argument_list|(
name|gfig_context
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GfigObject
modifier|*
DECL|function|d_copy_rectangle (GfigObject * obj)
name|d_copy_rectangle
parameter_list|(
name|GfigObject
modifier|*
name|obj
parameter_list|)
block|{
name|GfigObject
modifier|*
name|new_rectangle
decl_stmt|;
name|g_assert
argument_list|(
name|obj
operator|->
name|type
operator|==
name|RECTANGLE
argument_list|)
expr_stmt|;
name|new_rectangle
operator|=
name|d_new_object
argument_list|(
name|RECTANGLE
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
name|new_rectangle
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
name|new_rectangle
return|;
block|}
end_function

begin_function
name|void
DECL|function|d_rectangle_object_class_init (void)
name|d_rectangle_object_class_init
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
name|RECTANGLE
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|RECTANGLE
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"RECTANGLE"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_rectangle
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_rectangle
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_rectangle
expr_stmt|;
name|class
operator|->
name|update
operator|=
name|d_update_rectangle
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_update_rectangle (GdkPoint * pnt)
name|d_update_rectangle
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|)
block|{
name|DobjPoints
modifier|*
name|first_pnt
decl_stmt|;
name|DobjPoints
modifier|*
name|second_pnt
decl_stmt|;
name|first_pnt
operator|=
name|obj_creating
operator|->
name|points
expr_stmt|;
if|if
condition|(
operator|!
name|first_pnt
condition|)
return|return;
comment|/* No points */
if|if
condition|(
operator|(
name|second_pnt
operator|=
name|first_pnt
operator|->
name|next
operator|)
condition|)
block|{
name|second_pnt
operator|->
name|pnt
operator|.
name|x
operator|=
name|pnt
operator|->
name|x
expr_stmt|;
name|second_pnt
operator|->
name|pnt
operator|.
name|y
operator|=
name|pnt
operator|->
name|y
expr_stmt|;
block|}
else|else
block|{
name|second_pnt
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
name|first_pnt
operator|->
name|next
operator|=
name|second_pnt
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|d_rectangle_start (GdkPoint * pnt,gboolean shift_down)
name|d_rectangle_start
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
name|RECTANGLE
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
DECL|function|d_rectangle_end (GdkPoint * pnt,gboolean shift_down)
name|d_rectangle_end
parameter_list|(
name|GdkPoint
modifier|*
name|pnt
parameter_list|,
name|gboolean
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

