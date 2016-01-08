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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_comment
comment|/* GIMP_TIMER */
end_comment

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable-contiguous-region.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
specifier|const
name|Babl
modifier|*
name|choose_format
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gint
modifier|*
name|n_components
parameter_list|,
name|gboolean
modifier|*
name|has_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gfloat
name|pixel_difference
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|col1
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|col2
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gint
name|n_components
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|find_contiguous_segment
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|col
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|Babl
modifier|*
name|src_format
parameter_list|,
name|gint
name|n_components
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gint
name|width
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gint
name|initial_x
parameter_list|,
name|gint
name|initial_y
parameter_list|,
name|gint
modifier|*
name|start
parameter_list|,
name|gint
modifier|*
name|end
parameter_list|,
name|gfloat
modifier|*
name|row
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|find_contiguous_region
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gint
name|n_components
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gboolean
name|diagonal_neighbors
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|col
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_pickable_contiguous_region_by_seed (GimpPickable * pickable,gboolean antialias,gfloat threshold,gboolean select_transparent,GimpSelectCriterion select_criterion,gboolean diagonal_neighbors,gint x,gint y)
name|gimp_pickable_contiguous_region_by_seed
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gboolean
name|diagonal_neighbors
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|GeglRectangle
name|extent
decl_stmt|;
name|gint
name|n_components
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|gfloat
name|start_col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pickable_flush
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|src_buffer
operator|=
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|format
operator|=
name|choose_format
argument_list|(
name|src_buffer
argument_list|,
name|select_criterion
argument_list|,
operator|&
name|n_components
argument_list|,
operator|&
name|has_alpha
argument_list|)
expr_stmt|;
name|gegl_buffer_sample
argument_list|(
name|src_buffer
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|,
name|start_col
argument_list|,
name|format
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
if|if
condition|(
name|select_transparent
condition|)
block|{
comment|/*  don't select transparent regions if the start pixel isn't            *  fully transparent            */
if|if
condition|(
name|start_col
index|[
name|n_components
operator|-
literal|1
index|]
operator|>
literal|0
condition|)
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
else|else
block|{
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
name|extent
operator|=
operator|*
name|gegl_buffer_get_extent
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
name|mask_buffer
operator|=
name|gegl_buffer_new
argument_list|(
operator|&
name|extent
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|>=
name|extent
operator|.
name|x
operator|&&
name|x
operator|<
operator|(
name|extent
operator|.
name|x
operator|+
name|extent
operator|.
name|width
operator|)
operator|&&
name|y
operator|>=
name|extent
operator|.
name|y
operator|&&
name|y
operator|<
operator|(
name|extent
operator|.
name|y
operator|+
name|extent
operator|.
name|height
operator|)
condition|)
block|{
name|GIMP_TIMER_START
argument_list|()
expr_stmt|;
name|find_contiguous_region
argument_list|(
name|src_buffer
argument_list|,
name|mask_buffer
argument_list|,
name|format
argument_list|,
name|n_components
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|diagonal_neighbors
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|start_col
argument_list|)
expr_stmt|;
name|GIMP_TIMER_END
argument_list|(
literal|"foo"
argument_list|)
expr_stmt|;
block|}
return|return
name|mask_buffer
return|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_pickable_contiguous_region_by_color (GimpPickable * pickable,gboolean antialias,gfloat threshold,gboolean select_transparent,GimpSelectCriterion select_criterion,const GimpRGB * color)
name|gimp_pickable_contiguous_region_by_color
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
comment|/*  Scan over the pickable's active layer, finding pixels within the    *  specified threshold from the given R, G,& B values.  If    *  antialiasing is on, use the same antialiasing scheme as in    *  fuzzy_select.  Modify the pickable's mask to reflect the    *  additional selection    */
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|n_components
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|gfloat
name|start_col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pickable_flush
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|src_buffer
operator|=
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|format
operator|=
name|choose_format
argument_list|(
name|src_buffer
argument_list|,
name|select_criterion
argument_list|,
operator|&
name|n_components
argument_list|,
operator|&
name|has_alpha
argument_list|)
expr_stmt|;
name|gimp_rgba_get_pixel
argument_list|(
name|color
argument_list|,
name|format
argument_list|,
name|start_col
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
if|if
condition|(
name|select_transparent
condition|)
block|{
comment|/*  don't select transparancy if "color" isn't fully transparent            */
if|if
condition|(
name|start_col
index|[
name|n_components
operator|-
literal|1
index|]
operator|>
literal|0.0
condition|)
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
else|else
block|{
name|select_transparent
operator|=
name|FALSE
expr_stmt|;
block|}
name|mask_buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|gegl_buffer_get_extent
argument_list|(
name|src_buffer
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|mask_buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_ACCESS_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
specifier|const
name|gfloat
modifier|*
name|src
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
name|gfloat
modifier|*
name|dest
init|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
decl_stmt|;
name|gint
name|count
init|=
name|iter
operator|->
name|length
decl_stmt|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
comment|/*  Find how closely the colors match  */
operator|*
name|dest
operator|=
name|pixel_difference
argument_list|(
name|start_col
argument_list|,
name|src
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|n_components
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
argument_list|)
expr_stmt|;
name|src
operator|+=
name|n_components
expr_stmt|;
name|dest
operator|+=
literal|1
expr_stmt|;
block|}
block|}
return|return
name|mask_buffer
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
specifier|const
name|Babl
modifier|*
DECL|function|choose_format (GeglBuffer * buffer,GimpSelectCriterion select_criterion,gint * n_components,gboolean * has_alpha)
name|choose_format
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gint
modifier|*
name|n_components
parameter_list|,
name|gboolean
modifier|*
name|has_alpha
parameter_list|)
block|{
specifier|const
name|Babl
modifier|*
name|format
init|=
name|gegl_buffer_get_format
argument_list|(
name|buffer
argument_list|)
decl_stmt|;
operator|*
name|has_alpha
operator|=
name|babl_format_has_alpha
argument_list|(
name|format
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|select_criterion
condition|)
block|{
case|case
name|GIMP_SELECT_CRITERION_COMPOSITE
case|:
if|if
condition|(
name|babl_format_is_palette
argument_list|(
name|format
argument_list|)
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|gimp_babl_format
argument_list|(
name|gimp_babl_format_get_base_type
argument_list|(
name|format
argument_list|)
argument_list|,
name|GIMP_PRECISION_FLOAT_GAMMA
argument_list|,
operator|*
name|has_alpha
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_R
case|:
case|case
name|GIMP_SELECT_CRITERION_G
case|:
case|case
name|GIMP_SELECT_CRITERION_B
case|:
case|case
name|GIMP_SELECT_CRITERION_A
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_H
case|:
case|case
name|GIMP_SELECT_CRITERION_S
case|:
case|case
name|GIMP_SELECT_CRITERION_V
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"HSVA float"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
operator|*
name|n_components
operator|=
name|babl_format_get_n_components
argument_list|(
name|format
argument_list|)
expr_stmt|;
return|return
name|format
return|;
block|}
end_function

begin_function
specifier|static
name|gfloat
DECL|function|pixel_difference (const gfloat * col1,const gfloat * col2,gboolean antialias,gfloat threshold,gint n_components,gboolean has_alpha,gboolean select_transparent,GimpSelectCriterion select_criterion)
name|pixel_difference
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|col1
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|col2
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gint
name|n_components
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|)
block|{
name|gfloat
name|max
init|=
literal|0.0
decl_stmt|;
comment|/*  if there is an alpha channel, never select transparent regions  */
if|if
condition|(
operator|!
name|select_transparent
operator|&&
name|has_alpha
operator|&&
name|col2
index|[
name|n_components
operator|-
literal|1
index|]
operator|==
literal|0.0
condition|)
return|return
literal|0.0
return|;
if|if
condition|(
name|select_transparent
operator|&&
name|has_alpha
condition|)
block|{
name|max
operator|=
name|fabs
argument_list|(
name|col1
index|[
name|n_components
operator|-
literal|1
index|]
operator|-
name|col2
index|[
name|n_components
operator|-
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gfloat
name|diff
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|n_components
operator|--
expr_stmt|;
switch|switch
condition|(
name|select_criterion
condition|)
block|{
case|case
name|GIMP_SELECT_CRITERION_COMPOSITE
case|:
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|n_components
condition|;
name|b
operator|++
control|)
block|{
name|diff
operator|=
name|fabs
argument_list|(
name|col1
index|[
name|b
index|]
operator|-
name|col2
index|[
name|b
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|diff
operator|>
name|max
condition|)
name|max
operator|=
name|diff
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_SELECT_CRITERION_R
case|:
name|max
operator|=
name|fabs
argument_list|(
name|col1
index|[
literal|0
index|]
operator|-
name|col2
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_G
case|:
name|max
operator|=
name|fabs
argument_list|(
name|col1
index|[
literal|1
index|]
operator|-
name|col2
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_B
case|:
name|max
operator|=
name|fabs
argument_list|(
name|col1
index|[
literal|2
index|]
operator|-
name|col2
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_A
case|:
name|max
operator|=
name|fabs
argument_list|(
name|col1
index|[
literal|3
index|]
operator|-
name|col2
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_H
case|:
block|{
comment|/* wrap around candidates for the actual distance */
name|gfloat
name|dist1
init|=
name|fabs
argument_list|(
name|col1
index|[
literal|0
index|]
operator|-
name|col2
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gfloat
name|dist2
init|=
name|fabs
argument_list|(
name|col1
index|[
literal|0
index|]
operator|-
literal|1.0
operator|-
name|col2
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gfloat
name|dist3
init|=
name|fabs
argument_list|(
name|col1
index|[
literal|0
index|]
operator|-
name|col2
index|[
literal|0
index|]
operator|+
literal|1.0
argument_list|)
decl_stmt|;
name|max
operator|=
name|MIN
argument_list|(
name|dist1
argument_list|,
name|dist2
argument_list|)
expr_stmt|;
if|if
condition|(
name|max
operator|>
name|dist3
condition|)
name|max
operator|=
name|dist3
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_SELECT_CRITERION_S
case|:
name|max
operator|=
name|fabs
argument_list|(
name|col1
index|[
literal|1
index|]
operator|-
name|col2
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_SELECT_CRITERION_V
case|:
name|max
operator|=
name|fabs
argument_list|(
name|col1
index|[
literal|2
index|]
operator|-
name|col2
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|antialias
operator|&&
name|threshold
operator|>
literal|0.0
condition|)
block|{
name|gfloat
name|aa
init|=
literal|1.5
operator|-
operator|(
name|max
operator|/
name|threshold
operator|)
decl_stmt|;
if|if
condition|(
name|aa
operator|<=
literal|0.0
condition|)
return|return
literal|0.0
return|;
elseif|else
if|if
condition|(
name|aa
operator|<
literal|0.5
condition|)
return|return
name|aa
operator|*
literal|2.0
return|;
else|else
return|return
literal|1.0
return|;
block|}
else|else
block|{
if|if
condition|(
name|max
operator|>
name|threshold
condition|)
return|return
literal|0.0
return|;
else|else
return|return
literal|1.0
return|;
block|}
block|}
end_function

begin_comment
comment|/* #define FETCH_ROW 1 */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|find_contiguous_segment (const gfloat * col,GeglBuffer * src_buffer,GeglBuffer * mask_buffer,const Babl * format,gint n_components,gboolean has_alpha,gint width,gboolean select_transparent,GimpSelectCriterion select_criterion,gboolean antialias,gfloat threshold,gint initial_x,gint initial_y,gint * start,gint * end,gfloat * row)
name|find_contiguous_segment
parameter_list|(
specifier|const
name|gfloat
modifier|*
name|col
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gint
name|n_components
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gint
name|width
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gint
name|initial_x
parameter_list|,
name|gint
name|initial_y
parameter_list|,
name|gint
modifier|*
name|start
parameter_list|,
name|gint
modifier|*
name|end
parameter_list|,
name|gfloat
modifier|*
name|row
parameter_list|)
block|{
name|gfloat
modifier|*
name|s
decl_stmt|;
name|gfloat
name|mask_row
index|[
name|width
index|]
decl_stmt|;
name|gfloat
name|diff
decl_stmt|;
ifdef|#
directive|ifdef
name|FETCH_ROW
name|gegl_buffer_get
argument_list|(
name|src_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|initial_y
argument_list|,
name|width
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|row
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|s
operator|=
name|row
operator|+
name|initial_x
operator|*
name|n_components
expr_stmt|;
else|#
directive|else
name|s
operator|=
name|g_alloca
argument_list|(
name|n_components
operator|*
sizeof|sizeof
argument_list|(
name|gfloat
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_sample
argument_list|(
name|src_buffer
argument_list|,
name|initial_x
argument_list|,
name|initial_y
argument_list|,
name|NULL
argument_list|,
name|s
argument_list|,
name|format
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|n_components
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
argument_list|)
expr_stmt|;
comment|/* check the starting pixel */
if|if
condition|(
operator|!
name|diff
condition|)
return|return
name|FALSE
return|;
name|mask_row
index|[
name|initial_x
index|]
operator|=
name|diff
expr_stmt|;
operator|*
name|start
operator|=
name|initial_x
operator|-
literal|1
expr_stmt|;
ifdef|#
directive|ifdef
name|FETCH_ROW
name|s
operator|=
name|row
operator|+
operator|*
name|start
operator|*
name|n_components
expr_stmt|;
endif|#
directive|endif
while|while
condition|(
operator|*
name|start
operator|>=
literal|0
operator|&&
name|diff
condition|)
block|{
ifndef|#
directive|ifndef
name|FETCH_ROW
name|gegl_buffer_sample
argument_list|(
name|src_buffer
argument_list|,
operator|*
name|start
argument_list|,
name|initial_y
argument_list|,
name|NULL
argument_list|,
name|s
argument_list|,
name|format
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|n_components
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
argument_list|)
expr_stmt|;
name|mask_row
index|[
operator|*
name|start
index|]
operator|=
name|diff
expr_stmt|;
if|if
condition|(
name|diff
condition|)
block|{
operator|(
operator|*
name|start
operator|)
operator|--
expr_stmt|;
ifdef|#
directive|ifdef
name|FETCH_ROW
name|s
operator|-=
name|n_components
expr_stmt|;
endif|#
directive|endif
block|}
block|}
name|diff
operator|=
literal|1
expr_stmt|;
operator|*
name|end
operator|=
name|initial_x
operator|+
literal|1
expr_stmt|;
ifdef|#
directive|ifdef
name|FETCH_ROW
name|s
operator|=
name|row
operator|+
operator|*
name|end
operator|*
name|n_components
expr_stmt|;
endif|#
directive|endif
while|while
condition|(
operator|*
name|end
operator|<
name|width
operator|&&
name|diff
condition|)
block|{
ifndef|#
directive|ifndef
name|FETCH_ROW
name|gegl_buffer_sample
argument_list|(
name|src_buffer
argument_list|,
operator|*
name|end
argument_list|,
name|initial_y
argument_list|,
name|NULL
argument_list|,
name|s
argument_list|,
name|format
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|diff
operator|=
name|pixel_difference
argument_list|(
name|col
argument_list|,
name|s
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|n_components
argument_list|,
name|has_alpha
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
argument_list|)
expr_stmt|;
name|mask_row
index|[
operator|*
name|end
index|]
operator|=
name|diff
expr_stmt|;
if|if
condition|(
name|diff
condition|)
block|{
operator|(
operator|*
name|end
operator|)
operator|++
expr_stmt|;
ifdef|#
directive|ifdef
name|FETCH_ROW
name|s
operator|+=
name|n_components
expr_stmt|;
endif|#
directive|endif
block|}
block|}
name|gegl_buffer_set
argument_list|(
name|mask_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
operator|*
name|start
argument_list|,
name|initial_y
argument_list|,
operator|*
name|end
operator|-
operator|*
name|start
argument_list|,
literal|1
argument_list|)
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
operator|&
name|mask_row
index|[
operator|*
name|start
index|]
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|find_contiguous_region (GeglBuffer * src_buffer,GeglBuffer * mask_buffer,const Babl * format,gint n_components,gboolean has_alpha,gboolean select_transparent,GimpSelectCriterion select_criterion,gboolean antialias,gfloat threshold,gboolean diagonal_neighbors,gint x,gint y,const gfloat * col)
name|find_contiguous_region
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gint
name|n_components
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gboolean
name|diagonal_neighbors
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|col
parameter_list|)
block|{
name|gint
name|start
decl_stmt|,
name|end
decl_stmt|;
name|gint
name|new_start
decl_stmt|,
name|new_end
decl_stmt|;
name|GQueue
modifier|*
name|coord_stack
decl_stmt|;
name|gfloat
modifier|*
name|row
init|=
name|NULL
decl_stmt|;
ifdef|#
directive|ifdef
name|FETCH_ROW
name|row
operator|=
name|g_new
argument_list|(
name|gfloat
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|src_buffer
argument_list|)
operator|*
name|n_components
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|coord_stack
operator|=
name|g_queue_new
argument_list|()
expr_stmt|;
comment|/* To avoid excessive memory allocation (y, start, end) tuples are    * stored in interleaved format:    *    * [y1] [start1] [end1] [y2] [start2] [end2]    */
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|y
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|x
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|x
operator|+
literal|1
argument_list|)
argument_list|)
expr_stmt|;
do|do
block|{
name|y
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_queue_pop_head
argument_list|(
name|coord_stack
argument_list|)
argument_list|)
expr_stmt|;
name|start
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_queue_pop_head
argument_list|(
name|coord_stack
argument_list|)
argument_list|)
expr_stmt|;
name|end
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_queue_pop_head
argument_list|(
name|coord_stack
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
name|start
operator|+
literal|1
init|;
name|x
operator|<
name|end
condition|;
name|x
operator|++
control|)
block|{
name|gfloat
name|val
decl_stmt|;
name|gegl_buffer_sample
argument_list|(
name|mask_buffer
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|NULL
argument_list|,
operator|&
name|val
argument_list|,
name|babl_format
argument_list|(
literal|"Y float"
argument_list|)
argument_list|,
name|GEGL_SAMPLER_NEAREST
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|val
operator|!=
literal|0.0
condition|)
continue|continue;
if|if
condition|(
operator|!
name|find_contiguous_segment
argument_list|(
name|col
argument_list|,
name|src_buffer
argument_list|,
name|mask_buffer
argument_list|,
name|format
argument_list|,
name|n_components
argument_list|,
name|has_alpha
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|src_buffer
argument_list|)
argument_list|,
name|select_transparent
argument_list|,
name|select_criterion
argument_list|,
name|antialias
argument_list|,
name|threshold
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|new_start
argument_list|,
operator|&
name|new_end
argument_list|,
name|row
argument_list|)
condition|)
continue|continue;
if|if
condition|(
name|diagonal_neighbors
condition|)
block|{
if|if
condition|(
name|new_start
operator|>=
literal|0
condition|)
name|new_start
operator|--
expr_stmt|;
if|if
condition|(
name|new_end
operator|<
name|gegl_buffer_get_width
argument_list|(
name|src_buffer
argument_list|)
condition|)
name|new_end
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|+
literal|1
operator|<
name|gegl_buffer_get_height
argument_list|(
name|src_buffer
argument_list|)
condition|)
block|{
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|y
operator|+
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_start
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_end
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|-
literal|1
operator|>=
literal|0
condition|)
block|{
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|y
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_start
argument_list|)
argument_list|)
expr_stmt|;
name|g_queue_push_tail
argument_list|(
name|coord_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_end
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
do|while
condition|(
operator|!
name|g_queue_is_empty
argument_list|(
name|coord_stack
argument_list|)
condition|)
do|;
name|g_queue_free
argument_list|(
name|coord_stack
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|FETCH_ROW
name|g_free
argument_list|(
name|row
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

end_unit

