begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphistogram module Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_MP
end_ifdef

begin_include
include|#
directive|include
file|<pthread.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ENABLE_MP */
end_comment

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"base-config.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"pixel-processor.h"
end_include

begin_include
include|#
directive|include
file|"pixel-region.h"
end_include

begin_struct
DECL|struct|_GimpHistogram
struct|struct
name|_GimpHistogram
block|{
DECL|member|bins
name|gint
name|bins
decl_stmt|;
DECL|member|values
name|gdouble
modifier|*
modifier|*
name|values
decl_stmt|;
DECL|member|n_channels
name|gint
name|n_channels
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
DECL|member|mutex
name|pthread_mutex_t
name|mutex
decl_stmt|;
DECL|member|nthreads
name|gint
name|nthreads
decl_stmt|;
DECL|member|tmp_values
name|gdouble
modifier|*
modifier|*
modifier|*
name|tmp_values
decl_stmt|;
DECL|member|tmp_slots
name|gchar
modifier|*
name|tmp_slots
decl_stmt|;
endif|#
directive|endif
comment|/* ENABLE_MP */
block|}
struct|;
end_struct

begin_function
name|GimpHistogram
modifier|*
DECL|function|gimp_histogram_new (void)
name|gimp_histogram_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
name|histogram
operator|=
name|g_new0
argument_list|(
name|GimpHistogram
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|histogram
operator|->
name|bins
operator|=
literal|0
expr_stmt|;
name|histogram
operator|->
name|values
operator|=
name|NULL
expr_stmt|;
name|histogram
operator|->
name|n_channels
operator|=
literal|0
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
name|histogram
operator|->
name|nthreads
operator|=
literal|0
expr_stmt|;
name|histogram
operator|->
name|tmp_values
operator|=
name|NULL
expr_stmt|;
name|histogram
operator|->
name|tmp_slots
operator|=
name|NULL
expr_stmt|;
endif|#
directive|endif
comment|/* ENABLE_MP */
return|return
name|histogram
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_free (GimpHistogram * histogram)
name|gimp_histogram_free
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|histogram
operator|->
name|values
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|histogram
operator|->
name|n_channels
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|histogram
operator|->
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|histogram
operator|->
name|values
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|histogram
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_calculate_sub_region (GimpHistogram * histogram,PixelRegion * region,PixelRegion * mask)
name|gimp_histogram_calculate_sub_region
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|PixelRegion
modifier|*
name|region
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|msrc
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|m
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|gdouble
modifier|*
modifier|*
name|values
decl_stmt|;
name|gint
name|h
decl_stmt|,
name|w
decl_stmt|,
name|max
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
name|gint
name|slot
init|=
literal|0
decl_stmt|;
comment|/* find an unused temporary slot to put our results in and lock it */
name|pthread_mutex_lock
argument_list|(
operator|&
name|histogram
operator|->
name|mutex
argument_list|)
expr_stmt|;
block|{
while|while
condition|(
name|histogram
operator|->
name|tmp_slots
index|[
name|slot
index|]
condition|)
name|slot
operator|++
expr_stmt|;
name|values
operator|=
name|histogram
operator|->
name|tmp_values
index|[
name|slot
index|]
expr_stmt|;
name|histogram
operator|->
name|tmp_slots
index|[
name|slot
index|]
operator|=
literal|1
expr_stmt|;
block|}
name|pthread_mutex_unlock
argument_list|(
operator|&
name|histogram
operator|->
name|mutex
argument_list|)
expr_stmt|;
else|#
directive|else
comment|/* !ENABLE_MP */
name|values
operator|=
name|histogram
operator|->
name|values
expr_stmt|;
endif|#
directive|endif
name|h
operator|=
name|region
operator|->
name|h
expr_stmt|;
name|w
operator|=
name|region
operator|->
name|w
expr_stmt|;
if|if
condition|(
name|mask
condition|)
block|{
name|gdouble
name|masked
decl_stmt|;
name|src
operator|=
name|region
operator|->
name|data
expr_stmt|;
name|msrc
operator|=
name|mask
operator|->
name|data
expr_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
name|s
operator|=
name|src
expr_stmt|;
name|m
operator|=
name|msrc
expr_stmt|;
name|w
operator|=
name|region
operator|->
name|w
expr_stmt|;
switch|switch
condition|(
name|region
operator|->
name|bytes
condition|)
block|{
case|case
literal|1
case|:
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|masked
operator|=
name|m
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|s
operator|+=
literal|1
expr_stmt|;
name|m
operator|+=
literal|1
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|masked
operator|=
name|m
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|values
index|[
literal|1
index|]
index|[
name|s
index|[
literal|1
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|s
operator|+=
literal|2
expr_stmt|;
name|m
operator|+=
literal|1
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
comment|/* calculate seperate value values */
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|masked
operator|=
name|m
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|values
index|[
literal|1
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|values
index|[
literal|2
index|]
index|[
name|s
index|[
literal|1
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|values
index|[
literal|3
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|max
operator|=
operator|(
name|s
index|[
literal|0
index|]
operator|>
name|s
index|[
literal|1
index|]
operator|)
condition|?
name|s
index|[
literal|0
index|]
else|:
name|s
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|s
index|[
literal|2
index|]
operator|>
name|max
condition|)
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
name|masked
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
index|[
name|max
index|]
operator|+=
name|masked
expr_stmt|;
name|s
operator|+=
literal|3
expr_stmt|;
name|m
operator|+=
literal|1
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
comment|/* calculate seperate value values */
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|masked
operator|=
name|m
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|values
index|[
literal|1
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|values
index|[
literal|2
index|]
index|[
name|s
index|[
literal|1
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|values
index|[
literal|3
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|values
index|[
literal|4
index|]
index|[
name|s
index|[
literal|3
index|]
index|]
operator|+=
name|masked
expr_stmt|;
name|max
operator|=
operator|(
name|s
index|[
literal|0
index|]
operator|>
name|s
index|[
literal|1
index|]
operator|)
condition|?
name|s
index|[
literal|0
index|]
else|:
name|s
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|s
index|[
literal|2
index|]
operator|>
name|max
condition|)
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
name|masked
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
index|[
name|max
index|]
operator|+=
name|masked
expr_stmt|;
name|s
operator|+=
literal|3
expr_stmt|;
name|m
operator|+=
literal|1
expr_stmt|;
block|}
break|break;
block|}
name|src
operator|+=
name|region
operator|->
name|rowstride
expr_stmt|;
name|msrc
operator|+=
name|mask
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
else|else
comment|/* no mask */
block|{
name|src
operator|=
name|region
operator|->
name|data
expr_stmt|;
while|while
condition|(
name|h
operator|--
condition|)
block|{
name|s
operator|=
name|src
expr_stmt|;
name|w
operator|=
name|region
operator|->
name|w
expr_stmt|;
switch|switch
condition|(
name|region
operator|->
name|bytes
condition|)
block|{
case|case
literal|1
case|:
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|s
operator|+=
literal|1
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|values
index|[
literal|1
index|]
index|[
name|s
index|[
literal|1
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|s
operator|+=
literal|2
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
comment|/* calculate seperate value values */
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|values
index|[
literal|1
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|values
index|[
literal|2
index|]
index|[
name|s
index|[
literal|1
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|values
index|[
literal|3
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|max
operator|=
operator|(
name|s
index|[
literal|0
index|]
operator|>
name|s
index|[
literal|1
index|]
operator|)
condition|?
name|s
index|[
literal|0
index|]
else|:
name|s
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|s
index|[
literal|2
index|]
operator|>
name|max
condition|)
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
index|[
name|max
index|]
operator|+=
literal|1.0
expr_stmt|;
name|s
operator|+=
literal|3
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
comment|/* calculate seperate value values */
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|values
index|[
literal|1
index|]
index|[
name|s
index|[
literal|0
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|values
index|[
literal|2
index|]
index|[
name|s
index|[
literal|1
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|values
index|[
literal|3
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|values
index|[
literal|4
index|]
index|[
name|s
index|[
literal|3
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
name|max
operator|=
operator|(
name|s
index|[
literal|0
index|]
operator|>
name|s
index|[
literal|1
index|]
operator|)
condition|?
name|s
index|[
literal|0
index|]
else|:
name|s
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|s
index|[
literal|2
index|]
operator|>
name|max
condition|)
name|values
index|[
literal|0
index|]
index|[
name|s
index|[
literal|2
index|]
index|]
operator|+=
literal|1.0
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
index|[
name|max
index|]
operator|+=
literal|1.0
expr_stmt|;
name|s
operator|+=
literal|4
expr_stmt|;
block|}
break|break;
block|}
name|src
operator|+=
name|region
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
ifdef|#
directive|ifdef
name|ENABLE_MP
comment|/* unlock this slot */
comment|/* we shouldn't have to use mutex locks here */
name|pthread_mutex_lock
argument_list|(
operator|&
name|histogram
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|histogram
operator|->
name|tmp_slots
index|[
name|slot
index|]
operator|=
literal|0
expr_stmt|;
name|pthread_mutex_unlock
argument_list|(
operator|&
name|histogram
operator|->
name|mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_alloc (GimpHistogram * histogram,gint bytes)
name|gimp_histogram_alloc
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|bytes
operator|+
literal|1
operator|!=
name|histogram
operator|->
name|n_channels
condition|)
block|{
if|if
condition|(
name|histogram
operator|->
name|values
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|histogram
operator|->
name|n_channels
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|histogram
operator|->
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|histogram
operator|->
name|values
argument_list|)
expr_stmt|;
block|}
name|histogram
operator|->
name|n_channels
operator|=
name|bytes
operator|+
literal|1
expr_stmt|;
name|histogram
operator|->
name|values
operator|=
name|g_new0
argument_list|(
name|gdouble
operator|*
argument_list|,
name|histogram
operator|->
name|n_channels
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|histogram
operator|->
name|n_channels
condition|;
name|i
operator|++
control|)
name|histogram
operator|->
name|values
index|[
name|i
index|]
operator|=
name|g_new
argument_list|(
name|double
argument_list|,
literal|256
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_calculate (GimpHistogram * histogram,PixelRegion * region,PixelRegion * mask)
name|gimp_histogram_calculate
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|PixelRegion
modifier|*
name|region
parameter_list|,
name|PixelRegion
modifier|*
name|mask
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
name|gint
name|k
decl_stmt|;
endif|#
directive|endif
name|gimp_histogram_alloc
argument_list|(
name|histogram
argument_list|,
name|region
operator|->
name|bytes
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
name|pthread_mutex_init
argument_list|(
operator|&
name|histogram
operator|->
name|mutex
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|histogram
operator|->
name|tmp_slots
operator|=
name|g_new0
argument_list|(
name|gchar
argument_list|,
name|base_config
operator|->
name|num_processors
argument_list|)
expr_stmt|;
name|histogram
operator|->
name|tmp_values
operator|=
name|g_new0
argument_list|(
name|gdouble
operator|*
operator|*
argument_list|,
name|base_config
operator|->
name|num_processors
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|base_config
operator|->
name|num_processors
condition|;
name|i
operator|++
control|)
block|{
name|histogram
operator|->
name|tmp_values
index|[
name|i
index|]
operator|=
name|g_new0
argument_list|(
name|double
operator|*
argument_list|,
name|histogram
operator|->
name|n_channels
argument_list|)
expr_stmt|;
name|histogram
operator|->
name|tmp_slots
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|histogram
operator|->
name|n_channels
condition|;
name|j
operator|++
control|)
block|{
name|histogram
operator|->
name|tmp_values
index|[
name|i
index|]
index|[
name|j
index|]
operator|=
name|g_new0
argument_list|(
name|gdouble
argument_list|,
literal|256
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|256
condition|;
name|k
operator|++
control|)
name|histogram
operator|->
name|tmp_values
index|[
name|i
index|]
index|[
name|j
index|]
index|[
name|k
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
block|}
endif|#
directive|endif
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|histogram
operator|->
name|n_channels
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|256
condition|;
name|j
operator|++
control|)
name|histogram
operator|->
name|values
index|[
name|i
index|]
index|[
name|j
index|]
operator|=
literal|0.0
expr_stmt|;
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|p_func
operator|)
name|gimp_histogram_calculate_sub_region
argument_list|,
name|histogram
argument_list|,
literal|2
argument_list|,
name|region
argument_list|,
name|mask
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
comment|/* add up all the tmp buffers and free their memmory */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|base_config
operator|->
name|num_processors
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|histogram
operator|->
name|n_channels
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|256
condition|;
name|k
operator|++
control|)
name|histogram
operator|->
name|values
index|[
name|j
index|]
index|[
name|k
index|]
operator|+=
name|histogram
operator|->
name|tmp_values
index|[
name|i
index|]
index|[
name|j
index|]
index|[
name|k
index|]
expr_stmt|;
name|g_free
argument_list|(
name|histogram
operator|->
name|tmp_values
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|histogram
operator|->
name|tmp_values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|histogram
operator|->
name|tmp_values
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|histogram
operator|->
name|tmp_slots
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_histogram_get_maximum (GimpHistogram * histogram,GimpHistogramChannel channel)
name|gimp_histogram_get_maximum
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
block|{
name|gdouble
name|max
init|=
literal|0.0
decl_stmt|;
name|gint
name|x
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
literal|256
condition|;
name|x
operator|++
control|)
if|if
condition|(
name|histogram
operator|->
name|values
index|[
name|channel
index|]
index|[
name|x
index|]
operator|>
name|max
condition|)
name|max
operator|=
name|histogram
operator|->
name|values
index|[
name|channel
index|]
index|[
name|x
index|]
expr_stmt|;
return|return
name|max
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_histogram_get_value (GimpHistogram * histogram,GimpHistogramChannel channel,gint bin)
name|gimp_histogram_get_value
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|bin
parameter_list|)
block|{
if|if
condition|(
name|channel
operator|<
name|histogram
operator|->
name|n_channels
operator|&&
name|bin
operator|>=
literal|0
operator|&&
name|bin
operator|<
literal|256
condition|)
return|return
name|histogram
operator|->
name|values
index|[
name|channel
index|]
index|[
name|bin
index|]
return|;
return|return
literal|0.0
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_histogram_get_channel (GimpHistogram * histogram,GimpHistogramChannel channel,gint bin)
name|gimp_histogram_get_channel
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|bin
parameter_list|)
block|{
if|if
condition|(
name|histogram
operator|->
name|n_channels
operator|>
literal|3
condition|)
return|return
name|gimp_histogram_get_value
argument_list|(
name|histogram
argument_list|,
name|channel
operator|+
literal|1
argument_list|,
name|bin
argument_list|)
return|;
else|else
return|return
name|gimp_histogram_get_value
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
name|bin
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_histogram_nchannels (GimpHistogram * histogram)
name|gimp_histogram_nchannels
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
block|{
return|return
name|histogram
operator|->
name|n_channels
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_histogram_get_count (GimpHistogram * histogram,gint start,gint end)
name|gimp_histogram_get_count
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|count
init|=
literal|0.0
decl_stmt|;
for|for
control|(
name|i
operator|=
name|start
init|;
name|i
operator|<=
name|end
condition|;
name|i
operator|++
control|)
name|count
operator|+=
name|histogram
operator|->
name|values
index|[
literal|0
index|]
index|[
name|i
index|]
expr_stmt|;
return|return
name|count
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_histogram_get_mean (GimpHistogram * histogram,GimpHistogramChannel channel,gint start,gint end)
name|gimp_histogram_get_mean
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|mean
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|count
decl_stmt|;
for|for
control|(
name|i
operator|=
name|start
init|;
name|i
operator|<=
name|end
condition|;
name|i
operator|++
control|)
name|mean
operator|+=
name|i
operator|*
name|histogram
operator|->
name|values
index|[
name|channel
index|]
index|[
name|i
index|]
expr_stmt|;
name|count
operator|=
name|gimp_histogram_get_count
argument_list|(
name|histogram
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|count
operator|>
literal|0.0
condition|)
return|return
name|mean
operator|/
name|count
return|;
return|return
name|mean
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_histogram_get_median (GimpHistogram * histogram,GimpHistogramChannel channel,gint start,gint end)
name|gimp_histogram_get_median
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|sum
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|count
decl_stmt|;
name|count
operator|=
name|gimp_histogram_get_count
argument_list|(
name|histogram
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|start
init|;
name|i
operator|<=
name|end
condition|;
name|i
operator|++
control|)
block|{
name|sum
operator|+=
name|histogram
operator|->
name|values
index|[
name|channel
index|]
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|sum
operator|*
literal|2
operator|>
name|count
condition|)
return|return
name|i
return|;
block|}
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_histogram_get_std_dev (GimpHistogram * histogram,GimpHistogramChannel channel,gint start,gint end)
name|gimp_histogram_get_std_dev
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|dev
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|count
decl_stmt|;
name|gdouble
name|mean
decl_stmt|;
name|mean
operator|=
name|gimp_histogram_get_mean
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|count
operator|=
name|gimp_histogram_get_count
argument_list|(
name|histogram
argument_list|,
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
if|if
condition|(
name|count
operator|==
literal|0.0
condition|)
name|count
operator|=
literal|1.0
expr_stmt|;
for|for
control|(
name|i
operator|=
name|start
init|;
name|i
operator|<=
name|end
condition|;
name|i
operator|++
control|)
name|dev
operator|+=
name|gimp_histogram_get_value
argument_list|(
name|histogram
argument_list|,
name|channel
argument_list|,
name|i
argument_list|)
operator|*
operator|(
name|i
operator|-
name|mean
operator|)
operator|*
operator|(
name|i
operator|-
name|mean
operator|)
expr_stmt|;
return|return
name|sqrt
argument_list|(
name|dev
operator|/
name|count
argument_list|)
return|;
block|}
end_function

end_unit

