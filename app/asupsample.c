begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * General, non-jittered adaptive supersampling library  * Copyright (C) 1997 Federico Mena Quintero  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  */
end_comment

begin_comment
comment|/* This code is *largely* based on the sources for POV-Ray 3.0.  I am  * grateful to the POV-Team for such a great program and for making  * their sources available.  All comments / bug reports /  * etc. regarding this library should be addressed to me, not to the  * POV-Ray team.  Any bugs are my responsibility, not theirs.  */
end_comment

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"asupsample.h"
end_include

begin_comment
comment|/***** Types *****/
end_comment

begin_typedef
DECL|struct|__anon28c2f99a0108
typedef|typedef
struct|struct
block|{
DECL|member|ready
name|char
name|ready
decl_stmt|;
DECL|member|color
name|color_t
name|color
decl_stmt|;
DECL|typedef|sample_t
block|}
name|sample_t
typedef|;
end_typedef

begin_comment
comment|/***** Local functions *****/
end_comment

begin_function_decl
specifier|static
name|unsigned
name|long
name|render_sub_pixel
parameter_list|(
name|int
name|max_depth
parameter_list|,
name|int
name|depth
parameter_list|,
name|sample_t
modifier|*
modifier|*
name|block
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x3
parameter_list|,
name|int
name|y3
parameter_list|,
name|double
name|threshold
parameter_list|,
name|int
name|sub_pixel_size
parameter_list|,
name|render_func_t
name|render_func
parameter_list|,
name|color_t
modifier|*
name|color
parameter_list|,
name|void
modifier|*
name|render_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|double
name|color_dist
parameter_list|(
name|color_t
name|c1
parameter_list|,
name|color_t
name|c2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/***** Functions *****/
end_comment

begin_comment
comment|/*****/
end_comment

begin_function
name|unsigned
name|long
DECL|function|adaptive_supersample_area (int x1,int y1,int x2,int y2,int max_depth,double threshold,render_func_t render_func,void * render_data,put_pixel_func_t put_pixel_func,void * put_pixel_data,progress_func_t progress_func,void * progress_data)
name|adaptive_supersample_area
parameter_list|(
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x2
parameter_list|,
name|int
name|y2
parameter_list|,
name|int
name|max_depth
parameter_list|,
name|double
name|threshold
parameter_list|,
name|render_func_t
name|render_func
parameter_list|,
name|void
modifier|*
name|render_data
parameter_list|,
name|put_pixel_func_t
name|put_pixel_func
parameter_list|,
name|void
modifier|*
name|put_pixel_data
parameter_list|,
name|progress_func_t
name|progress_func
parameter_list|,
name|void
modifier|*
name|progress_data
parameter_list|)
block|{
name|int
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|;
comment|/* Counters, width of region */
name|int
name|xt
decl_stmt|,
name|yt
decl_stmt|;
comment|/* Temporary counters */
name|int
name|sub_pixel_size
decl_stmt|;
comment|/* Numbe of samples per pixel (1D) */
name|size_t
name|row_size
decl_stmt|;
comment|/* Memory needed for one row */
name|color_t
name|color
decl_stmt|;
comment|/* Rendered pixel's color */
name|sample_t
name|tmp_sample
decl_stmt|;
comment|/* For swapping samples */
name|sample_t
modifier|*
name|top_row
decl_stmt|,
modifier|*
name|bot_row
decl_stmt|,
modifier|*
name|tmp_row
decl_stmt|;
comment|/* Sample rows */
name|sample_t
modifier|*
modifier|*
name|block
decl_stmt|;
comment|/* Sample block matrix */
name|unsigned
name|long
name|num_samples
decl_stmt|;
comment|/* Initialize color */
name|color
operator|.
name|r
operator|=
literal|0.0
expr_stmt|;
name|color
operator|.
name|g
operator|=
literal|0.0
expr_stmt|;
name|color
operator|.
name|b
operator|=
literal|0.0
expr_stmt|;
name|color
operator|.
name|a
operator|=
literal|0.0
expr_stmt|;
comment|/* Calculate sub-pixel size */
name|sub_pixel_size
operator|=
literal|1
operator|<<
name|max_depth
expr_stmt|;
comment|/* 2**max_depth */
comment|/* Create row arrays */
name|width
operator|=
name|x2
operator|-
name|x1
operator|+
literal|1
expr_stmt|;
name|row_size
operator|=
operator|(
name|sub_pixel_size
operator|*
name|width
operator|+
literal|1
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|sample_t
argument_list|)
expr_stmt|;
name|top_row
operator|=
name|g_malloc
argument_list|(
name|row_size
argument_list|)
expr_stmt|;
name|bot_row
operator|=
name|g_malloc
argument_list|(
name|row_size
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
operator|(
name|sub_pixel_size
operator|*
name|width
operator|+
literal|1
operator|)
condition|;
name|x
operator|++
control|)
block|{
name|top_row
index|[
name|x
index|]
operator|.
name|ready
operator|=
literal|0
expr_stmt|;
name|top_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|r
operator|=
literal|0.0
expr_stmt|;
name|top_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|g
operator|=
literal|0.0
expr_stmt|;
name|top_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|b
operator|=
literal|0.0
expr_stmt|;
name|top_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|a
operator|=
literal|0.0
expr_stmt|;
name|bot_row
index|[
name|x
index|]
operator|.
name|ready
operator|=
literal|0
expr_stmt|;
name|bot_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|r
operator|=
literal|0.0
expr_stmt|;
name|bot_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|g
operator|=
literal|0.0
expr_stmt|;
name|bot_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|b
operator|=
literal|0.0
expr_stmt|;
name|bot_row
index|[
name|x
index|]
operator|.
name|color
operator|.
name|a
operator|=
literal|0.0
expr_stmt|;
block|}
comment|/* for */
comment|/* Allocate block matrix */
name|block
operator|=
name|g_malloc
argument_list|(
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|sample_t
operator|*
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Rows */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|y
operator|++
control|)
comment|/* Columns */
name|block
index|[
name|y
index|]
operator|=
name|g_malloc0
argument_list|(
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|sample_t
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Render region */
name|num_samples
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y1
init|;
name|y
operator|<=
name|y2
condition|;
name|y
operator|++
control|)
block|{
comment|/* Clear the bottom row */
for|for
control|(
name|xt
operator|=
literal|0
init|;
name|xt
operator|<
operator|(
name|sub_pixel_size
operator|*
name|width
operator|+
literal|1
operator|)
condition|;
name|xt
operator|++
control|)
name|bot_row
index|[
name|xt
index|]
operator|.
name|ready
operator|=
literal|0
expr_stmt|;
comment|/* Clear first column */
for|for
control|(
name|yt
operator|=
literal|0
init|;
name|yt
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|yt
operator|++
control|)
name|block
index|[
name|yt
index|]
index|[
literal|0
index|]
operator|.
name|ready
operator|=
literal|0
expr_stmt|;
comment|/* Render row */
for|for
control|(
name|x
operator|=
name|x1
init|;
name|x
operator|<=
name|x2
condition|;
name|x
operator|++
control|)
block|{
comment|/* Initialize block by clearing all but first row/column */
for|for
control|(
name|yt
operator|=
literal|1
init|;
name|yt
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|yt
operator|++
control|)
for|for
control|(
name|xt
operator|=
literal|1
init|;
name|xt
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|xt
operator|++
control|)
name|block
index|[
name|yt
index|]
index|[
name|xt
index|]
operator|.
name|ready
operator|=
literal|0
expr_stmt|;
comment|/* Copy samples from top row to block */
name|memcpy
argument_list|(
name|block
index|[
literal|0
index|]
argument_list|,
name|top_row
operator|+
operator|(
operator|(
name|x
operator|-
name|x1
operator|)
operator|*
name|sub_pixel_size
operator|)
argument_list|,
sizeof|sizeof
argument_list|(
name|sample_t
argument_list|)
operator|*
name|sub_pixel_size
argument_list|)
expr_stmt|;
comment|/* Render pixel on (x, y) */
name|num_samples
operator|+=
name|render_sub_pixel
argument_list|(
name|max_depth
argument_list|,
literal|1
argument_list|,
name|block
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|sub_pixel_size
argument_list|,
name|sub_pixel_size
argument_list|,
name|threshold
argument_list|,
name|sub_pixel_size
argument_list|,
name|render_func
argument_list|,
operator|&
name|color
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|put_pixel_func
condition|)
call|(
modifier|*
name|put_pixel_func
call|)
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|color
argument_list|,
name|put_pixel_data
argument_list|)
expr_stmt|;
comment|/* Copy block information to rows */
name|top_row
index|[
operator|(
operator|(
name|x
operator|-
name|x1
operator|)
operator|+
literal|1
operator|)
operator|*
name|sub_pixel_size
index|]
operator|=
name|block
index|[
literal|0
index|]
index|[
name|sub_pixel_size
index|]
expr_stmt|;
name|memcpy
argument_list|(
name|bot_row
operator|+
operator|(
operator|(
name|x
operator|-
name|x1
operator|)
operator|*
name|sub_pixel_size
operator|)
argument_list|,
name|block
index|[
name|sub_pixel_size
index|]
argument_list|,
name|sub_pixel_size
operator|*
sizeof|sizeof
argument_list|(
name|sample_t
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Swap first and last columns */
for|for
control|(
name|yt
operator|=
literal|0
init|;
name|yt
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|yt
operator|++
control|)
block|{
name|tmp_sample
operator|=
name|block
index|[
name|yt
index|]
index|[
literal|0
index|]
expr_stmt|;
name|block
index|[
name|yt
index|]
index|[
literal|0
index|]
operator|=
name|block
index|[
name|yt
index|]
index|[
name|sub_pixel_size
index|]
expr_stmt|;
name|block
index|[
name|yt
index|]
index|[
name|sub_pixel_size
index|]
operator|=
name|tmp_sample
expr_stmt|;
block|}
comment|/* for */
block|}
comment|/* for */
comment|/* Swap rows */
name|tmp_row
operator|=
name|top_row
expr_stmt|;
name|top_row
operator|=
name|bot_row
expr_stmt|;
name|bot_row
operator|=
name|tmp_row
expr_stmt|;
comment|/* Call progress display function */
if|if
condition|(
name|progress_func
condition|)
call|(
modifier|*
name|progress_func
call|)
argument_list|(
name|y1
argument_list|,
name|y2
argument_list|,
name|y
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
block|}
comment|/* for */
comment|/* Free memory */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|y
operator|++
control|)
name|g_free
argument_list|(
name|block
index|[
name|y
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|block
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|top_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bot_row
argument_list|)
expr_stmt|;
return|return
name|num_samples
return|;
block|}
end_function

begin_comment
comment|/* adaptive_supersample_area */
end_comment

begin_comment
comment|/*****/
end_comment

begin_function
specifier|static
name|unsigned
name|long
DECL|function|render_sub_pixel (int max_depth,int depth,sample_t ** block,int x,int y,int x1,int y1,int x3,int y3,double threshold,int sub_pixel_size,render_func_t render_func,color_t * color,void * render_data)
name|render_sub_pixel
parameter_list|(
name|int
name|max_depth
parameter_list|,
name|int
name|depth
parameter_list|,
name|sample_t
modifier|*
modifier|*
name|block
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x3
parameter_list|,
name|int
name|y3
parameter_list|,
name|double
name|threshold
parameter_list|,
name|int
name|sub_pixel_size
parameter_list|,
name|render_func_t
name|render_func
parameter_list|,
name|color_t
modifier|*
name|color
parameter_list|,
name|void
modifier|*
name|render_data
parameter_list|)
block|{
name|int
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/* Coords of center sample */
name|double
name|dx1
decl_stmt|,
name|dy1
decl_stmt|;
comment|/* Delta to upper left sample */
name|double
name|dx3
decl_stmt|,
name|dy3
decl_stmt|;
comment|/* Delta to lower right sample */
name|color_t
name|c1
decl_stmt|,
name|c2
decl_stmt|,
name|c3
decl_stmt|,
name|c4
decl_stmt|;
comment|/* Sample colors */
name|unsigned
name|long
name|num_samples
decl_stmt|;
comment|/* Get offsets for corners */
name|dx1
operator|=
call|(
name|double
call|)
argument_list|(
name|x1
operator|-
name|sub_pixel_size
operator|/
literal|2
argument_list|)
operator|/
name|sub_pixel_size
expr_stmt|;
name|dx3
operator|=
call|(
name|double
call|)
argument_list|(
name|x3
operator|-
name|sub_pixel_size
operator|/
literal|2
argument_list|)
operator|/
name|sub_pixel_size
expr_stmt|;
name|dy1
operator|=
call|(
name|double
call|)
argument_list|(
name|y1
operator|-
name|sub_pixel_size
operator|/
literal|2
argument_list|)
operator|/
name|sub_pixel_size
expr_stmt|;
name|dy3
operator|=
call|(
name|double
call|)
argument_list|(
name|y3
operator|-
name|sub_pixel_size
operator|/
literal|2
argument_list|)
operator|/
name|sub_pixel_size
expr_stmt|;
name|num_samples
operator|=
literal|0
expr_stmt|;
comment|/* Render upper left sample */
if|if
condition|(
operator|!
name|block
index|[
name|y1
index|]
index|[
name|x1
index|]
operator|.
name|ready
condition|)
block|{
name|num_samples
operator|++
expr_stmt|;
call|(
modifier|*
name|render_func
call|)
argument_list|(
name|x
operator|+
name|dx1
argument_list|,
name|y
operator|+
name|dy1
argument_list|,
operator|&
name|c1
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|block
index|[
name|y1
index|]
index|[
name|x1
index|]
operator|.
name|ready
operator|=
literal|1
expr_stmt|;
name|block
index|[
name|y1
index|]
index|[
name|x1
index|]
operator|.
name|color
operator|=
name|c1
expr_stmt|;
block|}
else|else
name|c1
operator|=
name|block
index|[
name|y1
index|]
index|[
name|x1
index|]
operator|.
name|color
expr_stmt|;
comment|/* Render upper right sample */
if|if
condition|(
operator|!
name|block
index|[
name|y1
index|]
index|[
name|x3
index|]
operator|.
name|ready
condition|)
block|{
name|num_samples
operator|++
expr_stmt|;
call|(
modifier|*
name|render_func
call|)
argument_list|(
name|x
operator|+
name|dx3
argument_list|,
name|y
operator|+
name|dy1
argument_list|,
operator|&
name|c2
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|block
index|[
name|y1
index|]
index|[
name|x3
index|]
operator|.
name|ready
operator|=
literal|1
expr_stmt|;
name|block
index|[
name|y1
index|]
index|[
name|x3
index|]
operator|.
name|color
operator|=
name|c2
expr_stmt|;
block|}
else|else
name|c2
operator|=
name|block
index|[
name|y1
index|]
index|[
name|x3
index|]
operator|.
name|color
expr_stmt|;
comment|/* Render lower left sample */
if|if
condition|(
operator|!
name|block
index|[
name|y3
index|]
index|[
name|x1
index|]
operator|.
name|ready
condition|)
block|{
name|num_samples
operator|++
expr_stmt|;
call|(
modifier|*
name|render_func
call|)
argument_list|(
name|x
operator|+
name|dx1
argument_list|,
name|y
operator|+
name|dy3
argument_list|,
operator|&
name|c3
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|block
index|[
name|y3
index|]
index|[
name|x1
index|]
operator|.
name|ready
operator|=
literal|1
expr_stmt|;
name|block
index|[
name|y3
index|]
index|[
name|x1
index|]
operator|.
name|color
operator|=
name|c3
expr_stmt|;
block|}
else|else
name|c3
operator|=
name|block
index|[
name|y3
index|]
index|[
name|x1
index|]
operator|.
name|color
expr_stmt|;
comment|/* Render lower right sample */
if|if
condition|(
operator|!
name|block
index|[
name|y3
index|]
index|[
name|x3
index|]
operator|.
name|ready
condition|)
block|{
name|num_samples
operator|++
expr_stmt|;
call|(
modifier|*
name|render_func
call|)
argument_list|(
name|x
operator|+
name|dx3
argument_list|,
name|y
operator|+
name|dy3
argument_list|,
operator|&
name|c4
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|block
index|[
name|y3
index|]
index|[
name|x3
index|]
operator|.
name|ready
operator|=
literal|1
expr_stmt|;
name|block
index|[
name|y3
index|]
index|[
name|x3
index|]
operator|.
name|color
operator|=
name|c4
expr_stmt|;
block|}
else|else
name|c4
operator|=
name|block
index|[
name|y3
index|]
index|[
name|x3
index|]
operator|.
name|color
expr_stmt|;
comment|/* Check for supersampling */
if|if
condition|(
name|depth
operator|<=
name|max_depth
condition|)
block|{
comment|/* Check whether we have tu supersample */
if|if
condition|(
operator|(
name|color_dist
argument_list|(
name|c1
argument_list|,
name|c2
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|color_dist
argument_list|(
name|c1
argument_list|,
name|c3
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|color_dist
argument_list|(
name|c1
argument_list|,
name|c4
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|color_dist
argument_list|(
name|c2
argument_list|,
name|c3
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|color_dist
argument_list|(
name|c2
argument_list|,
name|c4
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|color_dist
argument_list|(
name|c3
argument_list|,
name|c4
argument_list|)
operator|>=
name|threshold
operator|)
condition|)
block|{
comment|/* Calc coordinates of center subsample */
name|x2
operator|=
operator|(
name|x1
operator|+
name|x3
operator|)
operator|/
literal|2
expr_stmt|;
name|y2
operator|=
operator|(
name|y1
operator|+
name|y3
operator|)
operator|/
literal|2
expr_stmt|;
comment|/* Render sub-blocks */
name|num_samples
operator|+=
name|render_sub_pixel
argument_list|(
name|max_depth
argument_list|,
name|depth
operator|+
literal|1
argument_list|,
name|block
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|threshold
argument_list|,
name|sub_pixel_size
argument_list|,
name|render_func
argument_list|,
operator|&
name|c1
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|num_samples
operator|+=
name|render_sub_pixel
argument_list|(
name|max_depth
argument_list|,
name|depth
operator|+
literal|1
argument_list|,
name|block
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x2
argument_list|,
name|y1
argument_list|,
name|x3
argument_list|,
name|y2
argument_list|,
name|threshold
argument_list|,
name|sub_pixel_size
argument_list|,
name|render_func
argument_list|,
operator|&
name|c2
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|num_samples
operator|+=
name|render_sub_pixel
argument_list|(
name|max_depth
argument_list|,
name|depth
operator|+
literal|1
argument_list|,
name|block
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x1
argument_list|,
name|y2
argument_list|,
name|x2
argument_list|,
name|y3
argument_list|,
name|threshold
argument_list|,
name|sub_pixel_size
argument_list|,
name|render_func
argument_list|,
operator|&
name|c3
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|num_samples
operator|+=
name|render_sub_pixel
argument_list|(
name|max_depth
argument_list|,
name|depth
operator|+
literal|1
argument_list|,
name|block
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|x3
argument_list|,
name|y3
argument_list|,
name|threshold
argument_list|,
name|sub_pixel_size
argument_list|,
name|render_func
argument_list|,
operator|&
name|c4
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
block|}
comment|/* if */
block|}
comment|/* if */
name|color
operator|->
name|r
operator|=
literal|0.25
operator|*
operator|(
name|c1
operator|.
name|r
operator|+
name|c2
operator|.
name|r
operator|+
name|c3
operator|.
name|r
operator|+
name|c4
operator|.
name|r
operator|)
expr_stmt|;
name|color
operator|->
name|g
operator|=
literal|0.25
operator|*
operator|(
name|c1
operator|.
name|g
operator|+
name|c2
operator|.
name|g
operator|+
name|c3
operator|.
name|g
operator|+
name|c4
operator|.
name|g
operator|)
expr_stmt|;
name|color
operator|->
name|b
operator|=
literal|0.25
operator|*
operator|(
name|c1
operator|.
name|b
operator|+
name|c2
operator|.
name|b
operator|+
name|c3
operator|.
name|b
operator|+
name|c4
operator|.
name|b
operator|)
expr_stmt|;
name|color
operator|->
name|a
operator|=
literal|0.25
operator|*
operator|(
name|c1
operator|.
name|a
operator|+
name|c2
operator|.
name|a
operator|+
name|c3
operator|.
name|a
operator|+
name|c4
operator|.
name|a
operator|)
expr_stmt|;
return|return
name|num_samples
return|;
block|}
end_function

begin_comment
comment|/* render_sub_pixel */
end_comment

begin_comment
comment|/*****/
end_comment

begin_function
specifier|static
name|double
DECL|function|color_dist (color_t c1,color_t c2)
name|color_dist
parameter_list|(
name|color_t
name|c1
parameter_list|,
name|color_t
name|c2
parameter_list|)
block|{
return|return
name|fabs
argument_list|(
name|c1
operator|.
name|r
operator|-
name|c2
operator|.
name|r
argument_list|)
operator|+
name|fabs
argument_list|(
name|c1
operator|.
name|g
operator|-
name|c2
operator|.
name|g
argument_list|)
operator|+
name|fabs
argument_list|(
name|c1
operator|.
name|b
operator|-
name|c2
operator|.
name|b
argument_list|)
operator|+
name|fabs
argument_list|(
name|c1
operator|.
name|a
operator|-
name|c2
operator|.
name|a
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* color_dist */
end_comment

end_unit

