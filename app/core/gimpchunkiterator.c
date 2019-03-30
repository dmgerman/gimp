begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpchunkiterator.c  * Copyright (C) 2019 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpchunkiterator.h"
end_include

begin_comment
comment|/* the maximal chunk size */
end_comment

begin_define
DECL|macro|MAX_CHUNK_WIDTH
define|#
directive|define
name|MAX_CHUNK_WIDTH
value|4096
end_define

begin_define
DECL|macro|MAX_CHUNK_HEIGHT
define|#
directive|define
name|MAX_CHUNK_HEIGHT
value|4096
end_define

begin_comment
comment|/* the default iteration interval */
end_comment

begin_define
DECL|macro|DEFAULT_INTERVAL
define|#
directive|define
name|DEFAULT_INTERVAL
value|(1.0 / 15.0)
end_define

begin_comment
DECL|macro|DEFAULT_INTERVAL
comment|/* seconds */
end_comment

begin_comment
comment|/* the minimal area to process per iteration */
end_comment

begin_define
DECL|macro|MIN_AREA_PER_ITERATION
define|#
directive|define
name|MIN_AREA_PER_ITERATION
value|4096
end_define

begin_comment
comment|/* the maximal ratio between the actual processed area and the target area,  * above which the current chunk height is readjusted, even in the middle of a  * row, to better match the target area  */
end_comment

begin_define
DECL|macro|MAX_AREA_RATIO
define|#
directive|define
name|MAX_AREA_RATIO
value|2.0
end_define

begin_comment
comment|/* the width of the target-area sliding window */
end_comment

begin_define
DECL|macro|TARGET_AREA_HISTORY_SIZE
define|#
directive|define
name|TARGET_AREA_HISTORY_SIZE
value|3
end_define

begin_struct
DECL|struct|_GimpChunkIterator
struct|struct
name|_GimpChunkIterator
block|{
DECL|member|region
name|cairo_region_t
modifier|*
name|region
decl_stmt|;
DECL|member|priority_region
name|cairo_region_t
modifier|*
name|priority_region
decl_stmt|;
DECL|member|tile_rect
name|GeglRectangle
name|tile_rect
decl_stmt|;
DECL|member|priority_rect
name|GeglRectangle
name|priority_rect
decl_stmt|;
DECL|member|interval
name|gdouble
name|interval
decl_stmt|;
DECL|member|current_region
name|cairo_region_t
modifier|*
name|current_region
decl_stmt|;
DECL|member|current_rect
name|GeglRectangle
name|current_rect
decl_stmt|;
DECL|member|current_x
name|gint
name|current_x
decl_stmt|;
DECL|member|current_y
name|gint
name|current_y
decl_stmt|;
DECL|member|current_height
name|gint
name|current_height
decl_stmt|;
DECL|member|iteration_time
name|gint64
name|iteration_time
decl_stmt|;
DECL|member|last_time
name|gint64
name|last_time
decl_stmt|;
DECL|member|last_area
name|gint
name|last_area
decl_stmt|;
DECL|member|target_area
name|gdouble
name|target_area
decl_stmt|;
DECL|member|target_area_min
name|gdouble
name|target_area_min
decl_stmt|;
DECL|member|target_area_history
name|gdouble
name|target_area_history
index|[
name|TARGET_AREA_HISTORY_SIZE
index|]
decl_stmt|;
DECL|member|target_area_history_i
name|gint
name|target_area_history_i
decl_stmt|;
DECL|member|target_area_history_n
name|gint
name|target_area_history_n
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_chunk_iterator_set_current_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chunk_iterator_merge_current_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chunk_iterator_merge
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_chunk_iterator_prepare
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chunk_iterator_set_target_area
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|gdouble
name|target_area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_chunk_iterator_get_target_area
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chunk_iterator_reset_target_area
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_chunk_iterator_calc_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
name|gboolean
name|readjust_height
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_chunk_iterator_set_current_rect (GimpChunkIterator * iter,const GeglRectangle * rect)
name|gimp_chunk_iterator_set_current_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|cairo_region_subtract_rectangle
argument_list|(
name|iter
operator|->
name|current_region
argument_list|,
operator|(
specifier|const
name|cairo_rectangle_int_t
operator|*
operator|)
name|rect
argument_list|)
expr_stmt|;
name|iter
operator|->
name|current_rect
operator|=
operator|*
name|rect
expr_stmt|;
name|iter
operator|->
name|current_x
operator|=
name|rect
operator|->
name|x
expr_stmt|;
name|iter
operator|->
name|current_y
operator|=
name|rect
operator|->
name|y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chunk_iterator_merge_current_rect (GimpChunkIterator * iter)
name|gimp_chunk_iterator_merge_current_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
block|{
name|GeglRectangle
name|rect
decl_stmt|;
name|gint
name|current_height
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|gegl_rectangle_is_empty
argument_list|(
operator|&
name|iter
operator|->
name|current_rect
argument_list|)
condition|)
return|return;
comment|/* merge the remainder of the current row */
if|if
condition|(
name|iter
operator|->
name|current_x
operator|!=
name|iter
operator|->
name|current_rect
operator|.
name|x
condition|)
block|{
name|current_height
operator|=
name|iter
operator|->
name|current_height
expr_stmt|;
name|rect
operator|.
name|x
operator|=
name|iter
operator|->
name|current_x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|iter
operator|->
name|current_y
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|iter
operator|->
name|current_rect
operator|.
name|x
operator|+
name|iter
operator|->
name|current_rect
operator|.
name|width
operator|-
name|iter
operator|->
name|current_x
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|current_height
expr_stmt|;
name|cairo_region_union_rectangle
argument_list|(
name|iter
operator|->
name|current_region
argument_list|,
operator|(
specifier|const
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|rect
argument_list|)
expr_stmt|;
block|}
comment|/* merge the remainder of the current rect */
name|rect
operator|.
name|x
operator|=
name|iter
operator|->
name|current_rect
operator|.
name|x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|iter
operator|->
name|current_y
operator|+
name|current_height
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|iter
operator|->
name|current_rect
operator|.
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|iter
operator|->
name|current_rect
operator|.
name|y
operator|+
name|iter
operator|->
name|current_rect
operator|.
name|height
operator|-
name|rect
operator|.
name|y
expr_stmt|;
name|cairo_region_union_rectangle
argument_list|(
name|iter
operator|->
name|current_region
argument_list|,
operator|(
specifier|const
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|rect
argument_list|)
expr_stmt|;
comment|/* reset the current rect and coordinates */
name|iter
operator|->
name|current_rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_rect
operator|.
name|width
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_rect
operator|.
name|height
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_x
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_y
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chunk_iterator_merge (GimpChunkIterator * iter)
name|gimp_chunk_iterator_merge
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
block|{
comment|/* merge the current rect back to the current region */
name|gimp_chunk_iterator_merge_current_rect
argument_list|(
name|iter
argument_list|)
expr_stmt|;
comment|/* merge the priority region back to the global region */
if|if
condition|(
name|iter
operator|->
name|priority_region
condition|)
block|{
name|cairo_region_union
argument_list|(
name|iter
operator|->
name|region
argument_list|,
name|iter
operator|->
name|priority_region
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|iter
operator|->
name|priority_region
argument_list|,
name|cairo_region_destroy
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_chunk_iterator_prepare (GimpChunkIterator * iter)
name|gimp_chunk_iterator_prepare
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
block|{
if|if
condition|(
name|iter
operator|->
name|current_x
operator|>=
name|iter
operator|->
name|current_rect
operator|.
name|x
operator|+
name|iter
operator|->
name|current_rect
operator|.
name|width
condition|)
block|{
name|iter
operator|->
name|current_x
operator|=
name|iter
operator|->
name|current_rect
operator|.
name|x
expr_stmt|;
name|iter
operator|->
name|current_y
operator|+=
name|iter
operator|->
name|current_height
expr_stmt|;
if|if
condition|(
name|iter
operator|->
name|current_y
operator|>=
name|iter
operator|->
name|current_rect
operator|.
name|y
operator|+
name|iter
operator|->
name|current_rect
operator|.
name|height
condition|)
block|{
name|GeglRectangle
name|rect
decl_stmt|;
if|if
condition|(
operator|!
name|iter
operator|->
name|priority_region
operator|&&
operator|!
name|gegl_rectangle_is_empty
argument_list|(
operator|&
name|iter
operator|->
name|priority_rect
argument_list|)
condition|)
block|{
name|iter
operator|->
name|priority_region
operator|=
name|cairo_region_copy
argument_list|(
name|iter
operator|->
name|region
argument_list|)
expr_stmt|;
name|cairo_region_intersect_rectangle
argument_list|(
name|iter
operator|->
name|priority_region
argument_list|,
operator|(
specifier|const
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|iter
operator|->
name|priority_rect
argument_list|)
expr_stmt|;
name|cairo_region_subtract_rectangle
argument_list|(
name|iter
operator|->
name|region
argument_list|,
operator|(
specifier|const
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|iter
operator|->
name|priority_rect
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|iter
operator|->
name|priority_region
operator|||
name|cairo_region_is_empty
argument_list|(
name|iter
operator|->
name|priority_region
argument_list|)
condition|)
block|{
name|iter
operator|->
name|current_region
operator|=
name|iter
operator|->
name|region
expr_stmt|;
block|}
else|else
block|{
name|iter
operator|->
name|current_region
operator|=
name|iter
operator|->
name|priority_region
expr_stmt|;
block|}
if|if
condition|(
name|cairo_region_is_empty
argument_list|(
name|iter
operator|->
name|current_region
argument_list|)
condition|)
block|{
name|iter
operator|->
name|current_rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_rect
operator|.
name|width
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_rect
operator|.
name|height
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_x
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|current_y
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|cairo_region_get_rectangle
argument_list|(
name|iter
operator|->
name|current_region
argument_list|,
literal|0
argument_list|,
operator|(
name|cairo_rectangle_int_t
operator|*
operator|)
operator|&
name|rect
argument_list|)
expr_stmt|;
name|gimp_chunk_iterator_set_current_rect
argument_list|(
name|iter
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|compare_double (const gdouble * x,const gdouble * y)
name|compare_double
parameter_list|(
specifier|const
name|gdouble
modifier|*
name|x
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|y
parameter_list|)
block|{
return|return
operator|(
operator|*
name|x
operator|>
operator|*
name|y
operator|)
operator|-
operator|(
operator|*
name|x
operator|<
operator|*
name|y
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chunk_iterator_set_target_area (GimpChunkIterator * iter,gdouble target_area)
name|gimp_chunk_iterator_set_target_area
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|gdouble
name|target_area
parameter_list|)
block|{
name|gdouble
name|target_area_history
index|[
name|TARGET_AREA_HISTORY_SIZE
index|]
decl_stmt|;
name|iter
operator|->
name|target_area_min
operator|=
name|MIN
argument_list|(
name|iter
operator|->
name|target_area_min
argument_list|,
name|target_area
argument_list|)
expr_stmt|;
name|iter
operator|->
name|target_area_history
index|[
name|iter
operator|->
name|target_area_history_i
operator|++
index|]
operator|=
name|target_area
expr_stmt|;
name|iter
operator|->
name|target_area_history_n
operator|=
name|MAX
argument_list|(
name|iter
operator|->
name|target_area_history_n
argument_list|,
name|iter
operator|->
name|target_area_history_i
argument_list|)
expr_stmt|;
name|iter
operator|->
name|target_area_history_i
operator|%=
name|TARGET_AREA_HISTORY_SIZE
expr_stmt|;
name|memcpy
argument_list|(
name|target_area_history
argument_list|,
name|iter
operator|->
name|target_area_history
argument_list|,
name|iter
operator|->
name|target_area_history_n
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
name|qsort
argument_list|(
name|target_area_history
argument_list|,
name|iter
operator|->
name|target_area_history_n
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|compare_double
argument_list|)
expr_stmt|;
name|iter
operator|->
name|target_area
operator|=
name|target_area_history
index|[
name|iter
operator|->
name|target_area_history_n
operator|/
literal|2
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_chunk_iterator_get_target_area (GimpChunkIterator * iter)
name|gimp_chunk_iterator_get_target_area
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
block|{
if|if
condition|(
name|iter
operator|->
name|target_area
condition|)
return|return
name|iter
operator|->
name|target_area
return|;
else|else
return|return
name|iter
operator|->
name|tile_rect
operator|.
name|width
operator|*
name|iter
operator|->
name|tile_rect
operator|.
name|height
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chunk_iterator_reset_target_area (GimpChunkIterator * iter)
name|gimp_chunk_iterator_reset_target_area
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
block|{
if|if
condition|(
name|iter
operator|->
name|target_area_history_n
condition|)
block|{
name|iter
operator|->
name|target_area
operator|=
name|iter
operator|->
name|target_area_min
expr_stmt|;
name|iter
operator|->
name|target_area_min
operator|=
name|MAX_CHUNK_WIDTH
operator|*
name|MAX_CHUNK_HEIGHT
expr_stmt|;
name|iter
operator|->
name|target_area_history_i
operator|=
literal|0
expr_stmt|;
name|iter
operator|->
name|target_area_history_n
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_chunk_iterator_calc_rect (GimpChunkIterator * iter,GeglRectangle * rect,gboolean readjust_height)
name|gimp_chunk_iterator_calc_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
name|gboolean
name|readjust_height
parameter_list|)
block|{
name|gdouble
name|target_area
decl_stmt|;
name|gdouble
name|aspect_ratio
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
if|if
condition|(
name|readjust_height
condition|)
name|gimp_chunk_iterator_reset_target_area
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|target_area
operator|=
name|gimp_chunk_iterator_get_target_area
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|aspect_ratio
operator|=
operator|(
name|gdouble
operator|)
name|iter
operator|->
name|tile_rect
operator|.
name|height
operator|/
operator|(
name|gdouble
operator|)
name|iter
operator|->
name|tile_rect
operator|.
name|width
expr_stmt|;
name|rect
operator|->
name|x
operator|=
name|iter
operator|->
name|current_x
expr_stmt|;
name|rect
operator|->
name|y
operator|=
name|iter
operator|->
name|current_y
expr_stmt|;
name|offset_x
operator|=
name|rect
operator|->
name|x
operator|-
name|iter
operator|->
name|tile_rect
operator|.
name|x
expr_stmt|;
name|offset_y
operator|=
name|rect
operator|->
name|y
operator|-
name|iter
operator|->
name|tile_rect
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|readjust_height
condition|)
block|{
name|rect
operator|->
name|height
operator|=
name|RINT
argument_list|(
operator|(
name|offset_y
operator|+
name|sqrt
argument_list|(
name|target_area
operator|*
name|aspect_ratio
argument_list|)
operator|)
operator|/
name|iter
operator|->
name|tile_rect
operator|.
name|height
argument_list|)
operator|*
name|iter
operator|->
name|tile_rect
operator|.
name|height
operator|-
name|offset_y
expr_stmt|;
if|if
condition|(
name|rect
operator|->
name|height
operator|<=
literal|0
condition|)
name|rect
operator|->
name|height
operator|+=
name|iter
operator|->
name|tile_rect
operator|.
name|height
expr_stmt|;
name|rect
operator|->
name|height
operator|=
name|MIN
argument_list|(
name|rect
operator|->
name|height
argument_list|,
name|iter
operator|->
name|current_rect
operator|.
name|y
operator|+
name|iter
operator|->
name|current_rect
operator|.
name|height
operator|-
name|rect
operator|->
name|y
argument_list|)
expr_stmt|;
name|rect
operator|->
name|height
operator|=
name|MIN
argument_list|(
name|rect
operator|->
name|height
argument_list|,
name|MAX_CHUNK_HEIGHT
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|rect
operator|->
name|height
operator|=
name|iter
operator|->
name|current_height
expr_stmt|;
block|}
name|rect
operator|->
name|width
operator|=
name|RINT
argument_list|(
operator|(
name|offset_x
operator|+
operator|(
name|gdouble
operator|)
name|target_area
operator|/
operator|(
name|gdouble
operator|)
name|rect
operator|->
name|height
operator|)
operator|/
name|iter
operator|->
name|tile_rect
operator|.
name|width
argument_list|)
operator|*
name|iter
operator|->
name|tile_rect
operator|.
name|width
operator|-
name|offset_x
expr_stmt|;
if|if
condition|(
name|rect
operator|->
name|width
operator|<=
literal|0
condition|)
name|rect
operator|->
name|width
operator|+=
name|iter
operator|->
name|tile_rect
operator|.
name|width
expr_stmt|;
name|rect
operator|->
name|width
operator|=
name|MIN
argument_list|(
name|rect
operator|->
name|width
argument_list|,
name|iter
operator|->
name|current_rect
operator|.
name|x
operator|+
name|iter
operator|->
name|current_rect
operator|.
name|width
operator|-
name|rect
operator|->
name|x
argument_list|)
expr_stmt|;
name|rect
operator|->
name|width
operator|=
name|MIN
argument_list|(
name|rect
operator|->
name|width
argument_list|,
name|MAX_CHUNK_WIDTH
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpChunkIterator
modifier|*
DECL|function|gimp_chunk_iterator_new (cairo_region_t * region)
name|gimp_chunk_iterator_new
parameter_list|(
name|cairo_region_t
modifier|*
name|region
parameter_list|)
block|{
name|GimpChunkIterator
modifier|*
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|region
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iter
operator|=
name|g_slice_new0
argument_list|(
name|GimpChunkIterator
argument_list|)
expr_stmt|;
name|iter
operator|->
name|region
operator|=
name|region
expr_stmt|;
name|g_object_get
argument_list|(
name|gegl_config
argument_list|()
argument_list|,
literal|"tile-width"
argument_list|,
operator|&
name|iter
operator|->
name|tile_rect
operator|.
name|width
argument_list|,
literal|"tile-height"
argument_list|,
operator|&
name|iter
operator|->
name|tile_rect
operator|.
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iter
operator|->
name|interval
operator|=
name|DEFAULT_INTERVAL
expr_stmt|;
return|return
name|iter
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_chunk_iterator_set_tile_rect (GimpChunkIterator * iter,const GeglRectangle * rect)
name|gimp_chunk_iterator_set_tile_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|gegl_rectangle_is_empty
argument_list|(
name|rect
argument_list|)
argument_list|)
expr_stmt|;
name|iter
operator|->
name|tile_rect
operator|=
operator|*
name|rect
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_chunk_iterator_set_priority_rect (GimpChunkIterator * iter,const GeglRectangle * rect)
name|gimp_chunk_iterator_set_priority_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
specifier|const
name|GeglRectangle
name|empty_rect
init|=
block|{}
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|rect
condition|)
name|rect
operator|=
operator|&
name|empty_rect
expr_stmt|;
if|if
condition|(
operator|!
name|gegl_rectangle_equal
argument_list|(
name|rect
argument_list|,
operator|&
name|iter
operator|->
name|priority_rect
argument_list|)
condition|)
block|{
name|iter
operator|->
name|priority_rect
operator|=
operator|*
name|rect
expr_stmt|;
if|if
condition|(
name|gimp_chunk_iterator_prepare
argument_list|(
name|iter
argument_list|)
condition|)
name|gimp_chunk_iterator_merge
argument_list|(
name|iter
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_chunk_iterator_set_interval (GimpChunkIterator * iter,gdouble interval)
name|gimp_chunk_iterator_set_interval
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|gdouble
name|interval
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|interval
operator|=
name|MAX
argument_list|(
name|interval
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|interval
operator|!=
name|iter
operator|->
name|interval
condition|)
block|{
if|if
condition|(
name|iter
operator|->
name|interval
condition|)
block|{
name|gdouble
name|ratio
init|=
name|interval
operator|/
name|iter
operator|->
name|interval
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|iter
operator|->
name|target_area
operator|*=
name|ratio
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TARGET_AREA_HISTORY_SIZE
condition|;
name|i
operator|++
control|)
name|iter
operator|->
name|target_area_history
index|[
name|i
index|]
operator|*=
name|ratio
expr_stmt|;
block|}
name|iter
operator|->
name|interval
operator|=
name|interval
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_chunk_iterator_next (GimpChunkIterator * iter)
name|gimp_chunk_iterator_next
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_chunk_iterator_prepare
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|gimp_chunk_iterator_stop
argument_list|(
name|iter
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|iter
operator|->
name|iteration_time
operator|=
name|g_get_monotonic_time
argument_list|()
expr_stmt|;
name|iter
operator|->
name|last_time
operator|=
name|iter
operator|->
name|iteration_time
expr_stmt|;
name|iter
operator|->
name|last_area
operator|=
literal|0
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_chunk_iterator_get_rect (GimpChunkIterator * iter,GeglRectangle * rect)
name|gimp_chunk_iterator_get_rect
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|gint64
name|time
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_chunk_iterator_prepare
argument_list|(
name|iter
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|time
operator|=
name|g_get_monotonic_time
argument_list|()
expr_stmt|;
if|if
condition|(
name|iter
operator|->
name|last_area
operator|>=
name|MIN_AREA_PER_ITERATION
condition|)
block|{
name|gdouble
name|interval
decl_stmt|;
name|interval
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|time
operator|-
name|iter
operator|->
name|last_time
argument_list|)
operator|/
name|G_TIME_SPAN_SECOND
expr_stmt|;
name|gimp_chunk_iterator_set_target_area
argument_list|(
name|iter
argument_list|,
name|iter
operator|->
name|last_area
operator|*
name|iter
operator|->
name|interval
operator|/
name|interval
argument_list|)
expr_stmt|;
name|interval
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|time
operator|-
name|iter
operator|->
name|iteration_time
argument_list|)
operator|/
name|G_TIME_SPAN_SECOND
expr_stmt|;
if|if
condition|(
name|interval
operator|>
name|iter
operator|->
name|interval
condition|)
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|iter
operator|->
name|current_x
operator|==
name|iter
operator|->
name|current_rect
operator|.
name|x
condition|)
block|{
name|gimp_chunk_iterator_calc_rect
argument_list|(
name|iter
argument_list|,
name|rect
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_chunk_iterator_calc_rect
argument_list|(
name|iter
argument_list|,
name|rect
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|rect
operator|->
name|width
operator|*
name|rect
operator|->
name|height
operator|>=
name|MAX_AREA_RATIO
operator|*
name|gimp_chunk_iterator_get_target_area
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|GeglRectangle
name|old_rect
init|=
operator|*
name|rect
decl_stmt|;
name|gimp_chunk_iterator_calc_rect
argument_list|(
name|iter
argument_list|,
name|rect
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|rect
operator|->
name|height
operator|>=
name|old_rect
operator|.
name|height
condition|)
operator|*
name|rect
operator|=
name|old_rect
expr_stmt|;
block|}
block|}
if|if
condition|(
name|rect
operator|->
name|height
operator|!=
name|iter
operator|->
name|current_height
condition|)
block|{
comment|/* if the chunk height changed in the middle of a row, merge the        * remaining area back into the current region, and reset the current        * area to the remainder of the row, using the new chunk height        */
if|if
condition|(
name|rect
operator|->
name|x
operator|!=
name|iter
operator|->
name|current_rect
operator|.
name|x
condition|)
block|{
name|GeglRectangle
name|rem
decl_stmt|;
name|rem
operator|.
name|x
operator|=
name|rect
operator|->
name|x
expr_stmt|;
name|rem
operator|.
name|y
operator|=
name|rect
operator|->
name|y
expr_stmt|;
name|rem
operator|.
name|width
operator|=
name|iter
operator|->
name|current_rect
operator|.
name|x
operator|+
name|iter
operator|->
name|current_rect
operator|.
name|width
operator|-
name|rect
operator|->
name|x
expr_stmt|;
name|rem
operator|.
name|height
operator|=
name|rect
operator|->
name|height
expr_stmt|;
name|gimp_chunk_iterator_merge_current_rect
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|gimp_chunk_iterator_set_current_rect
argument_list|(
name|iter
argument_list|,
operator|&
name|rem
argument_list|)
expr_stmt|;
block|}
name|iter
operator|->
name|current_height
operator|=
name|rect
operator|->
name|height
expr_stmt|;
block|}
name|iter
operator|->
name|current_x
operator|+=
name|rect
operator|->
name|width
expr_stmt|;
name|iter
operator|->
name|last_time
operator|=
name|time
expr_stmt|;
name|iter
operator|->
name|last_area
operator|=
name|rect
operator|->
name|width
operator|*
name|rect
operator|->
name|height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|cairo_region_t
modifier|*
DECL|function|gimp_chunk_iterator_stop (GimpChunkIterator * iter,gboolean free_region)
name|gimp_chunk_iterator_stop
parameter_list|(
name|GimpChunkIterator
modifier|*
name|iter
parameter_list|,
name|gboolean
name|free_region
parameter_list|)
block|{
name|cairo_region_t
modifier|*
name|result
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|free_region
condition|)
block|{
name|cairo_region_destroy
argument_list|(
name|iter
operator|->
name|region
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_chunk_iterator_prepare
argument_list|(
name|iter
argument_list|)
condition|)
name|gimp_chunk_iterator_merge
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|result
operator|=
name|iter
operator|->
name|region
expr_stmt|;
block|}
name|g_clear_pointer
argument_list|(
operator|&
name|iter
operator|->
name|priority_region
argument_list|,
name|cairo_region_destroy
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpChunkIterator
argument_list|,
name|iter
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

end_unit

