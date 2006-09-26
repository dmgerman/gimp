begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"base/boundary.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpstroke.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintcore.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintcore-stroke.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_decl_stmt
DECL|variable|default_coords
specifier|static
specifier|const
name|GimpCoords
name|default_coords
init|=
name|GIMP_COORDS_DEFAULT_VALUES
decl_stmt|;
end_decl_stmt

begin_function
name|gboolean
DECL|function|gimp_paint_core_stroke (GimpPaintCore * core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpCoords * strokes,gint n_strokes)
name|gimp_paint_core_stroke
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpCoords
modifier|*
name|strokes
parameter_list|,
name|gint
name|n_strokes
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_CORE
argument_list|(
name|core
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|strokes
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_strokes
operator|>
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_paint_core_start
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
operator|&
name|strokes
index|[
literal|0
index|]
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|core
operator|->
name|start_coords
operator|=
name|strokes
index|[
literal|0
index|]
expr_stmt|;
name|core
operator|->
name|last_coords
operator|=
name|strokes
index|[
literal|0
index|]
expr_stmt|;
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_INIT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|n_strokes
condition|;
name|i
operator|++
control|)
block|{
name|core
operator|->
name|cur_coords
operator|=
name|strokes
index|[
name|i
index|]
expr_stmt|;
name|gimp_paint_core_interpolate
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_FINISH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_paint_core_finish
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_paint_core_cleanup
argument_list|(
name|core
argument_list|)
expr_stmt|;
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
DECL|function|gimp_paint_core_stroke_boundary (GimpPaintCore * core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const BoundSeg * bound_segs,gint n_bound_segs,gint offset_x,gint offset_y)
name|gimp_paint_core_stroke_boundary
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|BoundSeg
modifier|*
name|bound_segs
parameter_list|,
name|gint
name|n_bound_segs
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|BoundSeg
modifier|*
name|stroke_segs
decl_stmt|;
name|gint
name|n_stroke_segs
decl_stmt|;
name|gint
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
name|GimpCoords
modifier|*
name|coords
decl_stmt|;
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|gint
name|n_coords
decl_stmt|;
name|gint
name|seg
decl_stmt|;
name|gint
name|s
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_CORE
argument_list|(
name|core
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bound_segs
operator|!=
name|NULL
operator|&&
name|n_bound_segs
operator|>
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|stroke_segs
operator|=
name|boundary_sort
argument_list|(
name|bound_segs
argument_list|,
name|n_bound_segs
argument_list|,
operator|&
name|n_stroke_segs
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_stroke_segs
operator|==
literal|0
condition|)
return|return
name|TRUE
return|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|off_x
operator|-=
name|offset_x
expr_stmt|;
name|off_y
operator|-=
name|offset_y
expr_stmt|;
name|coords
operator|=
name|g_new0
argument_list|(
name|GimpCoords
argument_list|,
name|n_bound_segs
operator|+
literal|4
argument_list|)
expr_stmt|;
name|seg
operator|=
literal|0
expr_stmt|;
name|n_coords
operator|=
literal|0
expr_stmt|;
comment|/* we offset all coordinates by 0.5 to align the brush with the path */
name|coords
index|[
name|n_coords
index|]
operator|=
name|default_coords
expr_stmt|;
name|coords
index|[
name|n_coords
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
literal|0
index|]
operator|.
name|x1
operator|-
name|off_x
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|coords
index|[
name|n_coords
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
literal|0
index|]
operator|.
name|y1
operator|-
name|off_y
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|n_coords
operator|++
expr_stmt|;
for|for
control|(
name|s
operator|=
literal|0
init|;
name|s
operator|<
name|n_stroke_segs
condition|;
name|s
operator|++
control|)
block|{
while|while
condition|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x2
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|!=
operator|-
literal|1
operator|||
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y2
operator|!=
operator|-
literal|1
condition|)
block|{
name|coords
index|[
name|n_coords
index|]
operator|=
name|default_coords
expr_stmt|;
name|coords
index|[
name|n_coords
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|-
name|off_x
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|coords
index|[
name|n_coords
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|-
name|off_y
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|n_coords
operator|++
expr_stmt|;
name|seg
operator|++
expr_stmt|;
block|}
comment|/* Close the stroke points up */
name|coords
index|[
name|n_coords
index|]
operator|=
name|coords
index|[
literal|0
index|]
expr_stmt|;
name|n_coords
operator|++
expr_stmt|;
if|if
condition|(
name|initialized
operator|||
name|gimp_paint_core_start
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
operator|&
name|coords
index|[
literal|0
index|]
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
name|core
operator|->
name|start_coords
operator|=
name|coords
index|[
literal|0
index|]
expr_stmt|;
name|core
operator|->
name|last_coords
operator|=
name|coords
index|[
literal|0
index|]
expr_stmt|;
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_INIT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|n_coords
condition|;
name|i
operator|++
control|)
block|{
name|core
operator|->
name|cur_coords
operator|=
name|coords
index|[
name|i
index|]
expr_stmt|;
name|gimp_paint_core_interpolate
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_FINISH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|n_coords
operator|=
literal|0
expr_stmt|;
name|seg
operator|++
expr_stmt|;
name|coords
index|[
name|n_coords
index|]
operator|=
name|default_coords
expr_stmt|;
name|coords
index|[
name|n_coords
index|]
operator|.
name|x
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|x1
operator|-
name|off_x
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|coords
index|[
name|n_coords
index|]
operator|.
name|y
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|stroke_segs
index|[
name|seg
index|]
operator|.
name|y1
operator|-
name|off_y
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|n_coords
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|initialized
condition|)
block|{
name|gimp_paint_core_finish
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_paint_core_cleanup
argument_list|(
name|core
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|coords
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stroke_segs
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_paint_core_stroke_vectors (GimpPaintCore * core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpVectors * vectors)
name|gimp_paint_core_stroke_vectors
parameter_list|(
name|GimpPaintCore
modifier|*
name|core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GList
modifier|*
name|stroke
decl_stmt|;
name|GArray
modifier|*
name|coords
init|=
name|NULL
decl_stmt|;
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|closed
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gint
name|vectors_off_x
decl_stmt|,
name|vectors_off_y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_CORE
argument_list|(
name|core
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
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
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
operator|&
name|vectors_off_x
argument_list|,
operator|&
name|vectors_off_y
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|off_x
operator|-=
name|vectors_off_x
expr_stmt|;
name|off_y
operator|-=
name|vectors_off_y
expr_stmt|;
for|for
control|(
name|stroke
operator|=
name|vectors
operator|->
name|strokes
init|;
name|stroke
condition|;
name|stroke
operator|=
name|stroke
operator|->
name|next
control|)
block|{
name|coords
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|GIMP_STROKE
argument_list|(
name|stroke
operator|->
name|data
argument_list|)
argument_list|,
literal|1.0
argument_list|,
operator|&
name|closed
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|&&
name|coords
operator|->
name|len
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|coords
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|.
name|x
operator|-=
name|off_x
expr_stmt|;
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|.
name|y
operator|-=
name|off_y
expr_stmt|;
block|}
if|if
condition|(
name|initialized
operator|||
name|gimp_paint_core_start
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
operator|&
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|initialized
operator|=
name|TRUE
expr_stmt|;
name|core
operator|->
name|start_coords
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|core
operator|->
name|last_coords
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_INIT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|coords
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|core
operator|->
name|cur_coords
operator|=
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gimp_paint_core_interpolate
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_FINISH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|coords
condition|)
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|initialized
condition|)
block|{
name|gimp_paint_core_finish
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gimp_paint_core_cleanup
argument_list|(
name|core
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

