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
name|INIT_PAINT
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
name|MOTION_PAINT
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
argument_list|)
expr_stmt|;
name|core
operator|->
name|last_coords
operator|=
name|core
operator|->
name|cur_coords
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
name|FINISH_PAINT
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
name|closed
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
comment|/*  gimp_stroke_interpolate() may return NULL, so iterate over the    *  list of strokes until one returns coords    */
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
condition|)
break|break;
block|}
if|if
condition|(
operator|!
name|coords
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
name|gimp_paint_core_start
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
operator|&
operator|(
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
operator|)
argument_list|)
condition|)
block|{
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|INIT_PAINT
argument_list|)
expr_stmt|;
do|do
block|{
name|gint
name|i
decl_stmt|;
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
name|MOTION_PAINT
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
argument_list|)
expr_stmt|;
name|core
operator|->
name|last_coords
operator|=
name|core
operator|->
name|cur_coords
expr_stmt|;
block|}
if|if
condition|(
name|closed
condition|)
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
literal|0
argument_list|)
expr_stmt|;
name|gimp_paint_core_interpolate
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
name|core
operator|->
name|last_coords
operator|=
name|core
operator|->
name|cur_coords
expr_stmt|;
block|}
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|coords
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|stroke
operator|->
name|next
condition|)
block|{
name|stroke
operator|=
name|stroke
operator|->
name|next
expr_stmt|;
comment|/*  see above  */
for|for
control|(
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
condition|)
break|break;
block|}
block|}
block|}
do|while
condition|(
name|coords
condition|)
do|;
name|gimp_paint_core_paint
argument_list|(
name|core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|FINISH_PAINT
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
end_function

end_unit

