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
file|<stdlib.h>
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

begin_function_decl
specifier|static
name|void
name|d_draw_ellipse
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
name|d_paint_ellipse
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
name|d_copy_ellipse
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
name|d_update_ellipse
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
DECL|function|d_draw_ellipse (GfigObject * obj)
name|d_draw_ellipse
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
argument_list|,
name|obj
operator|==
name|gfig_context
operator|->
name|selected_obj
argument_list|)
expr_stmt|;
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
name|bound_wx
argument_list|,
name|bound_wy
argument_list|,
literal|0
argument_list|,
literal|360
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|d_paint_ellipse (GfigObject * obj)
name|d_paint_ellipse
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
comment|/* Drawing ellipse is hard .    * 1) select ellipse    * 2) stroke it    */
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
name|gfig_context
operator|->
name|image_id
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
name|paint_layer_fill
argument_list|(
name|top_x
argument_list|,
name|top_y
argument_list|,
name|top_x
operator|+
name|bound_wx
argument_list|,
name|top_y
operator|+
name|bound_wy
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
DECL|function|d_copy_ellipse (GfigObject * obj)
name|d_copy_ellipse
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
name|ELLIPSE
argument_list|)
expr_stmt|;
name|nc
operator|=
name|d_new_object
argument_list|(
name|ELLIPSE
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
DECL|function|d_ellipse_object_class_init (void)
name|d_ellipse_object_class_init
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
name|ELLIPSE
index|]
decl_stmt|;
name|class
operator|->
name|type
operator|=
name|ELLIPSE
expr_stmt|;
name|class
operator|->
name|name
operator|=
literal|"ELLIPSE"
expr_stmt|;
name|class
operator|->
name|drawfunc
operator|=
name|d_draw_ellipse
expr_stmt|;
name|class
operator|->
name|paintfunc
operator|=
name|d_paint_ellipse
expr_stmt|;
name|class
operator|->
name|copyfunc
operator|=
name|d_copy_ellipse
expr_stmt|;
name|class
operator|->
name|update
operator|=
name|d_update_ellipse
expr_stmt|;
block|}
end_function

begin_function
specifier|static
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
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gdk_draw_arc
argument_list|(
name|gfig_context
operator|->
name|preview
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
name|draw_circle
argument_list|(
operator|&
name|edge_pnt
operator|->
name|pnt
argument_list|,
name|TRUE
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
name|gfig_context
operator|->
name|preview
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
end_function

begin_function
name|void
DECL|function|d_ellipse_start (GdkPoint * pnt,gboolean shift_down)
name|d_ellipse_start
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
name|ELLIPSE
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
DECL|function|d_ellipse_end (GdkPoint * pnt,gboolean shift_down)
name|d_ellipse_end
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
name|draw_circle
argument_list|(
name|pnt
argument_list|,
name|TRUE
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
block|}
name|obj_creating
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

