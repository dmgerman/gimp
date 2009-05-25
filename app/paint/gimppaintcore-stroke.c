begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
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
file|"core/gimperror.h"
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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_paint_core_stroke_emulate_dynamics
parameter_list|(
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|length
parameter_list|)
function_decl|;
end_function_decl

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
DECL|function|gimp_paint_core_stroke (GimpPaintCore * core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpCoords * strokes,gint n_strokes,gboolean push_undo,GError ** error)
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
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
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
name|error
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
name|gimp_paint_core_interpolate
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
name|i
index|]
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
argument_list|,
name|push_undo
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
DECL|function|gimp_paint_core_stroke_boundary (GimpPaintCore * core,GimpDrawable * drawable,GimpPaintOptions * paint_options,gboolean emulate_dynamics,const BoundSeg * bound_segs,gint n_bound_segs,gint offset_x,gint offset_y,gboolean push_undo,GError ** error)
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
name|gboolean
name|emulate_dynamics
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
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
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
name|gimp_item_get_offset
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
name|emulate_dynamics
condition|)
name|gimp_paint_core_stroke_emulate_dynamics
argument_list|(
name|coords
argument_list|,
name|n_coords
argument_list|)
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
name|error
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
name|cur_coords
operator|=
name|coords
index|[
literal|0
index|]
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
name|gimp_paint_core_interpolate
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
name|i
index|]
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
else|else
block|{
break|break;
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
argument_list|,
name|push_undo
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
name|initialized
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_paint_core_stroke_vectors (GimpPaintCore * core,GimpDrawable * drawable,GimpPaintOptions * paint_options,gboolean emulate_dynamics,GimpVectors * vectors,gboolean push_undo,GError ** error)
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
name|gboolean
name|emulate_dynamics
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GList
modifier|*
name|stroke
decl_stmt|;
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|due_to_lack_of_points
init|=
name|FALSE
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
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
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
name|gimp_item_get_offset
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
name|GArray
modifier|*
name|coords
decl_stmt|;
name|gboolean
name|closed
decl_stmt|;
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
name|emulate_dynamics
condition|)
name|gimp_paint_core_stroke_emulate_dynamics
argument_list|(
operator|(
name|GimpCoords
operator|*
operator|)
name|coords
operator|->
name|data
argument_list|,
name|coords
operator|->
name|len
argument_list|)
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
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|initialized
operator|=
name|TRUE
expr_stmt|;
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
literal|0
argument_list|)
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
name|gimp_paint_core_interpolate
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
name|i
argument_list|)
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
else|else
block|{
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
break|break;
block|}
block|}
else|else
block|{
name|due_to_lack_of_points
operator|=
name|TRUE
expr_stmt|;
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
argument_list|,
name|push_undo
argument_list|)
expr_stmt|;
name|gimp_paint_core_cleanup
argument_list|(
name|core
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|initialized
operator|&&
name|due_to_lack_of_points
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Not enough points to stroke"
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|initialized
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_core_stroke_emulate_dynamics (GimpCoords * coords,gint length)
name|gimp_paint_core_stroke_emulate_dynamics
parameter_list|(
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|length
parameter_list|)
block|{
specifier|const
name|gint
name|ramp_length
init|=
name|length
operator|/
literal|3
decl_stmt|;
comment|/* Calculate and create pressure ramp parameters */
if|if
condition|(
name|ramp_length
operator|>
literal|0
condition|)
block|{
name|gdouble
name|slope
init|=
literal|1.0
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|ramp_length
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* Calculate pressure start ramp */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ramp_length
condition|;
name|i
operator|++
control|)
block|{
name|coords
index|[
name|i
index|]
operator|.
name|pressure
operator|=
name|i
operator|*
name|slope
expr_stmt|;
block|}
comment|/* Calculate pressure end ramp */
for|for
control|(
name|i
operator|=
name|length
operator|-
name|ramp_length
init|;
name|i
operator|<
name|length
condition|;
name|i
operator|++
control|)
block|{
name|coords
index|[
name|i
index|]
operator|.
name|pressure
operator|=
literal|1.0
operator|-
operator|(
name|i
operator|-
operator|(
name|length
operator|-
name|ramp_length
operator|)
operator|)
operator|*
name|slope
expr_stmt|;
block|}
block|}
comment|/* Calculate and create velocity ramp parameters */
if|if
condition|(
name|length
operator|>
literal|0
condition|)
block|{
name|gdouble
name|slope
init|=
literal|1.0
operator|/
name|length
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* Calculate velocity end ramp */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|length
condition|;
name|i
operator|++
control|)
block|{
name|coords
index|[
name|i
index|]
operator|.
name|velocity
operator|=
name|i
operator|*
name|slope
expr_stmt|;
block|}
block|}
if|if
condition|(
name|length
operator|>
literal|0
condition|)
block|{
name|gint
name|i
decl_stmt|;
comment|/* Fill in direction */
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
operator|<
name|length
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|delta_x
init|=
name|coords
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|x
operator|-
name|coords
index|[
name|i
index|]
operator|.
name|x
decl_stmt|;
name|gdouble
name|delta_y
init|=
name|coords
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|y
operator|-
name|coords
index|[
name|i
index|]
operator|.
name|y
decl_stmt|;
if|if
condition|(
name|delta_x
operator|==
literal|0
condition|)
block|{
name|coords
index|[
name|i
index|]
operator|.
name|direction
operator|=
name|coords
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|direction
expr_stmt|;
block|}
else|else
block|{
name|coords
index|[
name|i
index|]
operator|.
name|direction
operator|=
name|atan
argument_list|(
name|delta_y
operator|/
name|delta_x
argument_list|)
operator|/
operator|(
literal|2
operator|*
name|G_PI
operator|)
expr_stmt|;
if|if
condition|(
name|delta_x
operator|>
literal|0.0
condition|)
name|coords
index|[
name|i
index|]
operator|.
name|direction
operator|=
name|coords
index|[
name|i
index|]
operator|.
name|direction
operator|+
literal|0.5
expr_stmt|;
block|}
comment|/* This should avoid confusing the interpolator on sharp            * turns where the angle warps            */
if|if
condition|(
name|fabs
argument_list|(
name|coords
index|[
name|i
index|]
operator|.
name|direction
operator|-
name|coords
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|direction
argument_list|)
operator|>
literal|0.5
condition|)
name|coords
index|[
name|i
index|]
operator|.
name|direction
operator|=
name|coords
index|[
name|i
index|]
operator|.
name|direction
operator|+
literal|1.0
expr_stmt|;
block|}
if|if
condition|(
name|length
operator|>
literal|2
condition|)
block|{
name|coords
index|[
literal|0
index|]
operator|.
name|direction
operator|=
name|coords
index|[
literal|2
index|]
operator|.
name|direction
expr_stmt|;
name|coords
index|[
literal|1
index|]
operator|.
name|direction
operator|=
name|coords
index|[
literal|2
index|]
operator|.
name|direction
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

