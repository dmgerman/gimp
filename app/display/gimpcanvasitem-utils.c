begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasitem-utils.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpanchor.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpbezierstroke.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasitem-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_canvas_item_on_handle (GimpCanvasItem * item,gdouble x,gdouble y,GimpHandleType type,gdouble handle_x,gdouble handle_y,gint width,gint height,GimpHandleAnchor anchor)
name|gimp_canvas_item_on_handle
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpHandleType
name|type
parameter_list|,
name|gdouble
name|handle_x
parameter_list|,
name|gdouble
name|handle_y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gdouble
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|gdouble
name|handle_tx
decl_stmt|,
name|handle_ty
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|shell
operator|=
name|gimp_canvas_item_get_shell
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|gimp_display_shell_zoom_xy_f
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|)
expr_stmt|;
name|gimp_display_shell_zoom_xy_f
argument_list|(
name|shell
argument_list|,
name|handle_x
argument_list|,
name|handle_y
argument_list|,
operator|&
name|handle_tx
argument_list|,
operator|&
name|handle_ty
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_HANDLE_SQUARE
case|:
case|case
name|GIMP_HANDLE_FILLED_SQUARE
case|:
case|case
name|GIMP_HANDLE_CROSS
case|:
case|case
name|GIMP_HANDLE_CROSSHAIR
case|:
name|gimp_canvas_item_shift_to_north_west
argument_list|(
name|anchor
argument_list|,
name|handle_tx
argument_list|,
name|handle_ty
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|handle_tx
argument_list|,
operator|&
name|handle_ty
argument_list|)
expr_stmt|;
return|return
operator|(
name|tx
operator|==
name|CLAMP
argument_list|(
name|tx
argument_list|,
name|handle_tx
argument_list|,
name|handle_tx
operator|+
name|width
argument_list|)
operator|&&
name|ty
operator|==
name|CLAMP
argument_list|(
name|ty
argument_list|,
name|handle_ty
argument_list|,
name|handle_ty
operator|+
name|height
argument_list|)
operator|)
return|;
case|case
name|GIMP_HANDLE_CIRCLE
case|:
case|case
name|GIMP_HANDLE_FILLED_CIRCLE
case|:
name|gimp_canvas_item_shift_to_center
argument_list|(
name|anchor
argument_list|,
name|handle_tx
argument_list|,
name|handle_ty
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|handle_tx
argument_list|,
operator|&
name|handle_ty
argument_list|)
expr_stmt|;
comment|/* FIXME */
if|if
condition|(
name|width
operator|!=
name|height
condition|)
name|width
operator|=
operator|(
name|width
operator|+
name|height
operator|)
operator|/
literal|2
expr_stmt|;
name|width
operator|/=
literal|2
expr_stmt|;
return|return
operator|(
operator|(
name|SQR
argument_list|(
name|handle_tx
operator|-
name|tx
argument_list|)
operator|+
name|SQR
argument_list|(
name|handle_ty
operator|-
name|ty
argument_list|)
operator|)
operator|<
name|SQR
argument_list|(
name|width
argument_list|)
operator|)
return|;
default|default:
name|g_warning
argument_list|(
literal|"%s: invalid handle type %d"
argument_list|,
name|G_STRFUNC
argument_list|,
name|type
argument_list|)
expr_stmt|;
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_canvas_item_on_vectors_handle (GimpCanvasItem * item,GimpVectors * vectors,const GimpCoords * coord,gint width,gint height,GimpAnchorType preferred,gboolean exclusive,GimpAnchor ** ret_anchor,GimpStroke ** ret_stroke)
name|gimp_canvas_item_on_vectors_handle
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpAnchorType
name|preferred
parameter_list|,
name|gboolean
name|exclusive
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_anchor
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|)
block|{
name|GimpStroke
modifier|*
name|stroke
init|=
name|NULL
decl_stmt|;
name|GimpStroke
modifier|*
name|pref_stroke
init|=
name|NULL
decl_stmt|;
name|GimpAnchor
modifier|*
name|anchor
init|=
name|NULL
decl_stmt|;
name|GimpAnchor
modifier|*
name|pref_anchor
init|=
name|NULL
decl_stmt|;
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|gdouble
name|pref_mindist
init|=
operator|-
literal|1
decl_stmt|;
name|gdouble
name|mindist
init|=
operator|-
literal|1
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coord
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_anchor
condition|)
operator|*
name|ret_anchor
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|NULL
expr_stmt|;
while|while
condition|(
operator|(
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
operator|)
condition|)
block|{
name|GList
modifier|*
name|anchor_list
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|anchor_list
operator|=
name|g_list_concat
argument_list|(
name|gimp_stroke_get_draw_anchors
argument_list|(
name|stroke
argument_list|)
argument_list|,
name|gimp_stroke_get_draw_controls
argument_list|(
name|stroke
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|anchor_list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|dx
operator|=
name|coord
operator|->
name|x
operator|-
name|GIMP_ANCHOR
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|position
operator|.
name|x
expr_stmt|;
name|dy
operator|=
name|coord
operator|->
name|y
operator|-
name|GIMP_ANCHOR
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|position
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|mindist
operator|<
literal|0
operator|||
name|mindist
operator|>
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
condition|)
block|{
name|mindist
operator|=
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
expr_stmt|;
name|anchor
operator|=
name|GIMP_ANCHOR
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|stroke
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|pref_mindist
operator|<
literal|0
operator|||
name|pref_mindist
operator|>
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
operator|)
operator|&&
name|GIMP_ANCHOR
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|->
name|type
operator|==
name|preferred
condition|)
block|{
name|pref_mindist
operator|=
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
expr_stmt|;
name|pref_anchor
operator|=
name|GIMP_ANCHOR
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|pref_stroke
operator|=
name|stroke
expr_stmt|;
block|}
block|}
name|g_list_free
argument_list|(
name|anchor_list
argument_list|)
expr_stmt|;
block|}
comment|/* If the data passed into ret_anchor is a preferred anchor, return it. */
if|if
condition|(
name|ret_anchor
operator|&&
operator|*
name|ret_anchor
operator|&&
name|gimp_canvas_item_on_handle
argument_list|(
name|item
argument_list|,
name|coord
operator|->
name|x
argument_list|,
name|coord
operator|->
name|y
argument_list|,
name|GIMP_HANDLE_CIRCLE
argument_list|,
operator|(
operator|*
name|ret_anchor
operator|)
operator|->
name|position
operator|.
name|x
argument_list|,
operator|(
operator|*
name|ret_anchor
operator|)
operator|->
name|position
operator|.
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|)
operator|&&
operator|(
operator|*
name|ret_anchor
operator|)
operator|->
name|type
operator|==
name|preferred
condition|)
block|{
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|pref_stroke
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|pref_anchor
operator|&&
name|gimp_canvas_item_on_handle
argument_list|(
name|item
argument_list|,
name|coord
operator|->
name|x
argument_list|,
name|coord
operator|->
name|y
argument_list|,
name|GIMP_HANDLE_CIRCLE
argument_list|,
name|pref_anchor
operator|->
name|position
operator|.
name|x
argument_list|,
name|pref_anchor
operator|->
name|position
operator|.
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|)
condition|)
block|{
if|if
condition|(
name|ret_anchor
condition|)
operator|*
name|ret_anchor
operator|=
name|pref_anchor
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|pref_stroke
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|exclusive
operator|&&
name|anchor
operator|&&
name|gimp_canvas_item_on_handle
argument_list|(
name|item
argument_list|,
name|coord
operator|->
name|x
argument_list|,
name|coord
operator|->
name|y
argument_list|,
name|GIMP_HANDLE_CIRCLE
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|x
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|)
condition|)
block|{
if|if
condition|(
name|ret_anchor
condition|)
operator|*
name|ret_anchor
operator|=
name|anchor
expr_stmt|;
comment|/* *ret_stroke already set correctly. */
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|ret_anchor
condition|)
operator|*
name|ret_anchor
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|NULL
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_canvas_item_on_vectors_curve (GimpCanvasItem * item,GimpVectors * vectors,const GimpCoords * coord,gint width,gint height,GimpCoords * ret_coords,gdouble * ret_pos,GimpAnchor ** ret_segment_start,GimpAnchor ** ret_segment_end,GimpStroke ** ret_stroke)
name|gimp_canvas_item_on_vectors_curve
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpCoords
modifier|*
name|ret_coords
parameter_list|,
name|gdouble
modifier|*
name|ret_pos
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_start
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_end
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|)
block|{
name|GimpStroke
modifier|*
name|stroke
init|=
name|NULL
decl_stmt|;
name|GimpAnchor
modifier|*
name|segment_start
decl_stmt|;
name|GimpAnchor
modifier|*
name|segment_end
decl_stmt|;
name|GimpCoords
name|min_coords
init|=
name|GIMP_COORDS_DEFAULT_VALUES
decl_stmt|;
name|GimpCoords
name|cur_coords
decl_stmt|;
name|gdouble
name|min_dist
decl_stmt|,
name|cur_dist
decl_stmt|,
name|cur_pos
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coord
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_coords
condition|)
operator|*
name|ret_coords
operator|=
operator|*
name|coord
expr_stmt|;
if|if
condition|(
name|ret_pos
condition|)
operator|*
name|ret_pos
operator|=
operator|-
literal|1.0
expr_stmt|;
if|if
condition|(
name|ret_segment_start
condition|)
operator|*
name|ret_segment_start
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_segment_end
condition|)
operator|*
name|ret_segment_end
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|NULL
expr_stmt|;
name|min_dist
operator|=
operator|-
literal|1.0
expr_stmt|;
while|while
condition|(
operator|(
name|stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
operator|)
condition|)
block|{
name|cur_dist
operator|=
name|gimp_stroke_nearest_point_get
argument_list|(
name|stroke
argument_list|,
name|coord
argument_list|,
literal|1.0
argument_list|,
operator|&
name|cur_coords
argument_list|,
operator|&
name|segment_start
argument_list|,
operator|&
name|segment_end
argument_list|,
operator|&
name|cur_pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|cur_dist
operator|>=
literal|0
operator|&&
operator|(
name|min_dist
operator|<
literal|0
operator|||
name|cur_dist
operator|<
name|min_dist
operator|)
condition|)
block|{
name|min_dist
operator|=
name|cur_dist
expr_stmt|;
name|min_coords
operator|=
name|cur_coords
expr_stmt|;
if|if
condition|(
name|ret_coords
condition|)
operator|*
name|ret_coords
operator|=
name|cur_coords
expr_stmt|;
if|if
condition|(
name|ret_pos
condition|)
operator|*
name|ret_pos
operator|=
name|cur_pos
expr_stmt|;
if|if
condition|(
name|ret_segment_start
condition|)
operator|*
name|ret_segment_start
operator|=
name|segment_start
expr_stmt|;
if|if
condition|(
name|ret_segment_end
condition|)
operator|*
name|ret_segment_end
operator|=
name|segment_end
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|stroke
expr_stmt|;
block|}
block|}
if|if
condition|(
name|min_dist
operator|>=
literal|0
operator|&&
name|gimp_canvas_item_on_handle
argument_list|(
name|item
argument_list|,
name|coord
operator|->
name|x
argument_list|,
name|coord
operator|->
name|y
argument_list|,
name|GIMP_HANDLE_CIRCLE
argument_list|,
name|min_coords
operator|.
name|x
argument_list|,
name|min_coords
operator|.
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|)
condition|)
block|{
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_canvas_item_on_vectors (GimpCanvasItem * item,const GimpCoords * coords,gint width,gint height,GimpCoords * ret_coords,gdouble * ret_pos,GimpAnchor ** ret_segment_start,GimpAnchor ** ret_segment_end,GimpStroke ** ret_stroke,GimpVectors ** ret_vectors)
name|gimp_canvas_item_on_vectors
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpCoords
modifier|*
name|ret_coords
parameter_list|,
name|gdouble
modifier|*
name|ret_pos
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_start
parameter_list|,
name|GimpAnchor
modifier|*
modifier|*
name|ret_segment_end
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|,
name|GimpVectors
modifier|*
modifier|*
name|ret_vectors
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GList
modifier|*
name|all_vectors
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|shell
operator|=
name|gimp_canvas_item_get_shell
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret_coords
condition|)
operator|*
name|ret_coords
operator|=
operator|*
name|coords
expr_stmt|;
if|if
condition|(
name|ret_pos
condition|)
operator|*
name|ret_pos
operator|=
operator|-
literal|1.0
expr_stmt|;
if|if
condition|(
name|ret_segment_start
condition|)
operator|*
name|ret_segment_start
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_segment_end
condition|)
operator|*
name|ret_segment_end
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|ret_vectors
condition|)
operator|*
name|ret_vectors
operator|=
name|NULL
expr_stmt|;
name|all_vectors
operator|=
name|gimp_image_get_vectors_list
argument_list|(
name|image
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|all_vectors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpVectors
modifier|*
name|vectors
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_item_get_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
condition|)
continue|continue;
if|if
condition|(
name|gimp_canvas_item_on_vectors_curve
argument_list|(
name|item
argument_list|,
name|vectors
argument_list|,
name|coords
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|ret_coords
argument_list|,
name|ret_pos
argument_list|,
name|ret_segment_start
argument_list|,
name|ret_segment_end
argument_list|,
name|ret_stroke
argument_list|)
condition|)
block|{
if|if
condition|(
name|ret_vectors
condition|)
operator|*
name|ret_vectors
operator|=
name|vectors
expr_stmt|;
name|g_list_free
argument_list|(
name|all_vectors
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
name|g_list_free
argument_list|(
name|all_vectors
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_item_shift_to_north_west (GimpHandleAnchor anchor,gdouble x,gdouble y,gint width,gint height,gdouble * shifted_x,gdouble * shifted_y)
name|gimp_canvas_item_shift_to_north_west
parameter_list|(
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
modifier|*
name|shifted_x
parameter_list|,
name|gdouble
modifier|*
name|shifted_y
parameter_list|)
block|{
switch|switch
condition|(
name|anchor
condition|)
block|{
case|case
name|GIMP_HANDLE_ANCHOR_CENTER
case|:
name|x
operator|-=
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|-=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH
case|:
name|x
operator|-=
name|width
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH_WEST
case|:
comment|/*  nothing, this is the default  */
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH_EAST
case|:
name|x
operator|-=
name|width
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH
case|:
name|x
operator|-=
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|-=
name|height
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH_WEST
case|:
name|y
operator|-=
name|height
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH_EAST
case|:
name|x
operator|-=
name|width
expr_stmt|;
name|y
operator|-=
name|height
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_WEST
case|:
name|y
operator|-=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_EAST
case|:
name|x
operator|-=
name|width
expr_stmt|;
name|y
operator|-=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|shifted_x
condition|)
operator|*
name|shifted_x
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|shifted_y
condition|)
operator|*
name|shifted_y
operator|=
name|y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_item_shift_to_center (GimpHandleAnchor anchor,gdouble x,gdouble y,gint width,gint height,gdouble * shifted_x,gdouble * shifted_y)
name|gimp_canvas_item_shift_to_center
parameter_list|(
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
modifier|*
name|shifted_x
parameter_list|,
name|gdouble
modifier|*
name|shifted_y
parameter_list|)
block|{
switch|switch
condition|(
name|anchor
condition|)
block|{
case|case
name|GIMP_HANDLE_ANCHOR_CENTER
case|:
comment|/*  nothing, this is the default  */
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH
case|:
name|y
operator|+=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH_WEST
case|:
name|x
operator|+=
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|+=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_NORTH_EAST
case|:
name|x
operator|-=
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|+=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH
case|:
name|y
operator|-=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH_WEST
case|:
name|x
operator|+=
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|-=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_SOUTH_EAST
case|:
name|x
operator|-=
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|-=
name|height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_WEST
case|:
name|x
operator|+=
name|width
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_HANDLE_ANCHOR_EAST
case|:
name|x
operator|-=
name|width
operator|/
literal|2
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|shifted_x
condition|)
operator|*
name|shifted_x
operator|=
name|x
expr_stmt|;
if|if
condition|(
name|shifted_y
condition|)
operator|*
name|shifted_y
operator|=
name|y
expr_stmt|;
block|}
end_function

end_unit

