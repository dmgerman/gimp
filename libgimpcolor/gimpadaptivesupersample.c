begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpadaptivesupersample.h"
end_include

begin_include
include|#
directive|include
file|"gimprgb.h"
end_include

begin_comment
comment|/*********************************************************************/
end_comment

begin_comment
comment|/* Sumpersampling code (Quartic)                                     */
end_comment

begin_comment
comment|/* This code is *largely* based on the sources for POV-Ray 3.0. I am */
end_comment

begin_comment
comment|/* grateful to the POV-Team for such a great program and for making  */
end_comment

begin_comment
comment|/* their sources available.  All comments / bug reports /            */
end_comment

begin_comment
comment|/* etc. regarding this code should be addressed to me, not to the    */
end_comment

begin_comment
comment|/* POV-Ray team.  Any bugs are my responsibility, not theirs.        */
end_comment

begin_comment
comment|/*********************************************************************/
end_comment

begin_typedef
DECL|typedef|GimpSampleType
typedef|typedef
name|struct
name|_GimpSampleType
name|GimpSampleType
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSampleType
struct|struct
name|_GimpSampleType
block|{
DECL|member|ready
name|guchar
name|ready
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|gulong
DECL|function|gimp_render_sub_pixel (gint max_depth,gint depth,GimpSampleType ** block,gint x,gint y,gint x1,gint y1,gint x3,gint y3,gdouble threshold,gint sub_pixel_size,GimpRGB * color,GimpRenderFunc render_func,gpointer render_data)
name|gimp_render_sub_pixel
parameter_list|(
name|gint
name|max_depth
parameter_list|,
name|gint
name|depth
parameter_list|,
name|GimpSampleType
modifier|*
modifier|*
name|block
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x3
parameter_list|,
name|gint
name|y3
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gint
name|sub_pixel_size
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpRenderFunc
name|render_func
parameter_list|,
name|gpointer
name|render_data
parameter_list|)
block|{
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/* Coords of center sample */
name|gdouble
name|dx1
decl_stmt|,
name|dy1
decl_stmt|;
comment|/* Delta to upper left sample */
name|gdouble
name|dx3
decl_stmt|,
name|dy3
decl_stmt|;
comment|/* Delta to lower right sample */
name|GimpRGB
name|c
index|[
literal|4
index|]
decl_stmt|;
comment|/* Sample colors */
name|gulong
name|num_samples
init|=
literal|0
decl_stmt|;
name|gint
name|cnt
decl_stmt|;
comment|/* Get offsets for corners */
name|dx1
operator|=
call|(
name|gdouble
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
name|gdouble
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
name|gdouble
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
name|gdouble
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
if|if
condition|(
name|render_func
condition|)
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
name|c
index|[
literal|0
index|]
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
name|TRUE
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
name|c
index|[
literal|0
index|]
expr_stmt|;
block|}
else|else
block|{
name|c
index|[
literal|0
index|]
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
block|}
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
if|if
condition|(
name|render_func
condition|)
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
name|c
index|[
literal|1
index|]
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
name|TRUE
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
name|c
index|[
literal|1
index|]
expr_stmt|;
block|}
else|else
block|{
name|c
index|[
literal|1
index|]
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
block|}
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
if|if
condition|(
name|render_func
condition|)
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
name|c
index|[
literal|2
index|]
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
name|TRUE
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
name|c
index|[
literal|2
index|]
expr_stmt|;
block|}
else|else
block|{
name|c
index|[
literal|2
index|]
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
block|}
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
if|if
condition|(
name|render_func
condition|)
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
name|c
index|[
literal|3
index|]
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
name|TRUE
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
name|c
index|[
literal|3
index|]
expr_stmt|;
block|}
else|else
block|{
name|c
index|[
literal|3
index|]
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
block|}
comment|/* Check for supersampling */
if|if
condition|(
name|depth
operator|<=
name|max_depth
condition|)
block|{
comment|/* Check whether we have to supersample */
if|if
condition|(
operator|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|c
index|[
literal|0
index|]
argument_list|,
operator|&
name|c
index|[
literal|1
index|]
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|c
index|[
literal|0
index|]
argument_list|,
operator|&
name|c
index|[
literal|2
index|]
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|c
index|[
literal|0
index|]
argument_list|,
operator|&
name|c
index|[
literal|3
index|]
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|c
index|[
literal|1
index|]
argument_list|,
operator|&
name|c
index|[
literal|2
index|]
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|c
index|[
literal|1
index|]
argument_list|,
operator|&
name|c
index|[
literal|3
index|]
argument_list|)
operator|>=
name|threshold
operator|)
operator|||
operator|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|c
index|[
literal|2
index|]
argument_list|,
operator|&
name|c
index|[
literal|3
index|]
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
name|gimp_render_sub_pixel
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
operator|&
name|c
index|[
literal|0
index|]
argument_list|,
name|render_func
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|num_samples
operator|+=
name|gimp_render_sub_pixel
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
operator|&
name|c
index|[
literal|1
index|]
argument_list|,
name|render_func
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|num_samples
operator|+=
name|gimp_render_sub_pixel
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
operator|&
name|c
index|[
literal|2
index|]
argument_list|,
name|render_func
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
name|num_samples
operator|+=
name|gimp_render_sub_pixel
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
operator|&
name|c
index|[
literal|3
index|]
argument_list|,
name|render_func
argument_list|,
name|render_data
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|c
index|[
literal|0
index|]
operator|.
name|a
operator|==
literal|0.0
operator|||
name|c
index|[
literal|1
index|]
operator|.
name|a
operator|==
literal|0.0
operator|||
name|c
index|[
literal|2
index|]
operator|.
name|a
operator|==
literal|0.0
operator|||
name|c
index|[
literal|3
index|]
operator|.
name|a
operator|==
literal|0.0
condition|)
block|{
name|GimpRGB
name|tmpcol
decl_stmt|;
name|gdouble
name|weight
decl_stmt|;
name|gimp_rgb_set
argument_list|(
operator|&
name|tmpcol
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|weight
operator|=
literal|2.0
expr_stmt|;
for|for
control|(
name|cnt
operator|=
literal|0
init|;
name|cnt
operator|<
literal|4
condition|;
name|cnt
operator|++
control|)
block|{
if|if
condition|(
name|c
index|[
name|cnt
index|]
operator|.
name|a
operator|!=
literal|0.0
condition|)
block|{
name|tmpcol
operator|.
name|r
operator|+=
name|c
index|[
name|cnt
index|]
operator|.
name|r
expr_stmt|;
name|tmpcol
operator|.
name|g
operator|+=
name|c
index|[
name|cnt
index|]
operator|.
name|g
expr_stmt|;
name|tmpcol
operator|.
name|b
operator|+=
name|c
index|[
name|cnt
index|]
operator|.
name|b
expr_stmt|;
name|weight
operator|/=
literal|2.0
expr_stmt|;
block|}
block|}
name|color
operator|->
name|r
operator|=
name|weight
operator|*
name|tmpcol
operator|.
name|r
expr_stmt|;
name|color
operator|->
name|g
operator|=
name|weight
operator|*
name|tmpcol
operator|.
name|g
expr_stmt|;
name|color
operator|->
name|b
operator|=
name|weight
operator|*
name|tmpcol
operator|.
name|b
expr_stmt|;
block|}
else|else
block|{
name|color
operator|->
name|r
operator|=
literal|0.25
operator|*
operator|(
name|c
index|[
literal|0
index|]
operator|.
name|r
operator|+
name|c
index|[
literal|1
index|]
operator|.
name|r
operator|+
name|c
index|[
literal|2
index|]
operator|.
name|r
operator|+
name|c
index|[
literal|3
index|]
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
name|c
index|[
literal|0
index|]
operator|.
name|g
operator|+
name|c
index|[
literal|1
index|]
operator|.
name|g
operator|+
name|c
index|[
literal|2
index|]
operator|.
name|g
operator|+
name|c
index|[
literal|3
index|]
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
name|c
index|[
literal|0
index|]
operator|.
name|b
operator|+
name|c
index|[
literal|1
index|]
operator|.
name|b
operator|+
name|c
index|[
literal|2
index|]
operator|.
name|b
operator|+
name|c
index|[
literal|3
index|]
operator|.
name|b
operator|)
expr_stmt|;
block|}
name|color
operator|->
name|a
operator|=
literal|0.25
operator|*
operator|(
name|c
index|[
literal|0
index|]
operator|.
name|a
operator|+
name|c
index|[
literal|1
index|]
operator|.
name|a
operator|+
name|c
index|[
literal|2
index|]
operator|.
name|a
operator|+
name|c
index|[
literal|3
index|]
operator|.
name|a
operator|)
expr_stmt|;
return|return
name|num_samples
return|;
block|}
end_function

begin_function
name|gulong
DECL|function|gimp_adaptive_supersample_area (gint x1,gint y1,gint x2,gint y2,gint max_depth,gdouble threshold,GimpRenderFunc render_func,gpointer render_data,GimpPutPixelFunc put_pixel_func,gpointer put_pixel_data,GimpProgressFunc progress_func,gpointer progress_data)
name|gimp_adaptive_supersample_area
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|max_depth
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|GimpRenderFunc
name|render_func
parameter_list|,
name|gpointer
name|render_data
parameter_list|,
name|GimpPutPixelFunc
name|put_pixel_func
parameter_list|,
name|gpointer
name|put_pixel_data
parameter_list|,
name|GimpProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|;
comment|/* Counters, width of region */
name|gint
name|xt
decl_stmt|,
name|xtt
decl_stmt|,
name|yt
decl_stmt|;
comment|/* Temporary counters */
name|gint
name|sub_pixel_size
decl_stmt|;
comment|/* Number of samples per pixel (1D) */
name|GimpRGB
name|color
decl_stmt|;
comment|/* Rendered pixel's color */
name|GimpSampleType
name|tmp_sample
decl_stmt|;
comment|/* For swapping samples */
name|GimpSampleType
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
name|GimpSampleType
modifier|*
modifier|*
name|block
decl_stmt|;
comment|/* Sample block matrix */
name|gulong
name|num_samples
decl_stmt|;
comment|/* Initialize color */
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
comment|/* Calculate sub-pixel size */
name|sub_pixel_size
operator|=
literal|1
operator|<<
name|max_depth
expr_stmt|;
comment|/* Create row arrays */
name|width
operator|=
name|x2
operator|-
name|x1
operator|+
literal|1
expr_stmt|;
name|top_row
operator|=
name|g_new
argument_list|(
name|GimpSampleType
argument_list|,
name|sub_pixel_size
operator|*
name|width
operator|+
literal|1
argument_list|)
expr_stmt|;
name|bot_row
operator|=
name|g_new
argument_list|(
name|GimpSampleType
argument_list|,
name|sub_pixel_size
operator|*
name|width
operator|+
literal|1
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
name|FALSE
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|top_row
index|[
name|x
index|]
operator|.
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|bot_row
index|[
name|x
index|]
operator|.
name|ready
operator|=
name|FALSE
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|bot_row
index|[
name|x
index|]
operator|.
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
comment|/* Allocate block matrix */
name|block
operator|=
name|g_new
argument_list|(
name|GimpSampleType
operator|*
argument_list|,
name|sub_pixel_size
operator|+
literal|1
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
block|{
name|block
index|[
name|y
index|]
operator|=
name|g_new
argument_list|(
name|GimpSampleType
argument_list|,
name|sub_pixel_size
operator|+
literal|1
argument_list|)
expr_stmt|;
comment|/* Columns */
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
operator|+
literal|1
operator|)
condition|;
name|x
operator|++
control|)
block|{
name|block
index|[
name|y
index|]
index|[
name|x
index|]
operator|.
name|ready
operator|=
name|FALSE
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|block
index|[
name|y
index|]
index|[
name|x
index|]
operator|.
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
block|}
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
name|FALSE
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
name|FALSE
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
name|FALSE
expr_stmt|;
comment|/* Copy samples from top row to block */
for|for
control|(
name|xtt
operator|=
literal|0
operator|,
name|xt
operator|=
operator|(
name|x
operator|-
name|x1
operator|)
operator|*
name|sub_pixel_size
init|;
name|xtt
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|xtt
operator|++
operator|,
name|xt
operator|++
control|)
name|block
index|[
literal|0
index|]
index|[
name|xtt
index|]
operator|=
name|top_row
index|[
name|xt
index|]
expr_stmt|;
comment|/* Render pixel on (x, y) */
name|num_samples
operator|+=
name|gimp_render_sub_pixel
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
operator|&
name|color
argument_list|,
name|render_func
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
operator|&
name|color
argument_list|,
name|put_pixel_data
argument_list|)
expr_stmt|;
comment|/* Copy block information to rows */
name|top_row
index|[
operator|(
name|x
operator|-
name|x1
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
for|for
control|(
name|xtt
operator|=
literal|0
operator|,
name|xt
operator|=
operator|(
name|x
operator|-
name|x1
operator|)
operator|*
name|sub_pixel_size
init|;
name|xtt
operator|<
operator|(
name|sub_pixel_size
operator|+
literal|1
operator|)
condition|;
name|xtt
operator|++
operator|,
name|xt
operator|++
control|)
name|bot_row
index|[
name|xt
index|]
operator|=
name|block
index|[
name|sub_pixel_size
index|]
index|[
name|xtt
index|]
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
block|}
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
comment|/* Call progress display function (if any) */
if|if
condition|(
name|progress_func
operator|!=
name|NULL
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

end_unit

