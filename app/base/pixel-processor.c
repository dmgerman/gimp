begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * pixel_processor.c: Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<string.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"base-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
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

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_define
DECL|macro|TILES_PER_THREAD
define|#
directive|define
name|TILES_PER_THREAD
value|8
end_define

begin_define
DECL|macro|PROGRESS_TIMEOUT
define|#
directive|define
name|PROGRESS_TIMEOUT
value|64
end_define

begin_decl_stmt
DECL|variable|pool
specifier|static
name|GThreadPool
modifier|*
name|pool
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pool_mutex
specifier|static
name|GMutex
modifier|*
name|pool_mutex
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pool_cond
specifier|static
name|GCond
modifier|*
name|pool_cond
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|p1_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p1_func
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|region1
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|p2_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p2_func
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|region1
parameter_list|,
name|PixelRegion
modifier|*
name|region2
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|p3_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p3_func
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|region1
parameter_list|,
name|PixelRegion
modifier|*
name|region2
parameter_list|,
name|PixelRegion
modifier|*
name|region3
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|p4_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p4_func
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|PixelRegion
modifier|*
name|region1
parameter_list|,
name|PixelRegion
modifier|*
name|region2
parameter_list|,
name|PixelRegion
modifier|*
name|region3
parameter_list|,
name|PixelRegion
modifier|*
name|region4
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|PixelProcessor
typedef|typedef
name|struct
name|_PixelProcessor
name|PixelProcessor
typedef|;
end_typedef

begin_struct
DECL|struct|_PixelProcessor
struct|struct
name|_PixelProcessor
block|{
DECL|member|func
name|PixelProcessorFunc
name|func
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
DECL|member|mutex
name|GMutex
modifier|*
name|mutex
decl_stmt|;
DECL|member|threads
name|gint
name|threads
decl_stmt|;
DECL|member|first
name|gboolean
name|first
decl_stmt|;
endif|#
directive|endif
DECL|member|PRI
name|PixelRegionIterator
modifier|*
name|PRI
decl_stmt|;
DECL|member|num_regions
name|gint
name|num_regions
decl_stmt|;
DECL|member|regions
name|PixelRegion
modifier|*
name|regions
index|[
literal|4
index|]
decl_stmt|;
DECL|member|progress
name|gulong
name|progress
decl_stmt|;
block|}
struct|;
end_struct

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_MP
end_ifdef

begin_function
specifier|static
name|void
DECL|function|do_parallel_regions (PixelProcessor * processor)
name|do_parallel_regions
parameter_list|(
name|PixelProcessor
modifier|*
name|processor
parameter_list|)
block|{
name|PixelRegion
name|tr
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_mutex_lock
argument_list|(
name|processor
operator|->
name|mutex
argument_list|)
expr_stmt|;
comment|/*  the first thread getting here must not call pixel_regions_process()  */
if|if
condition|(
operator|!
name|processor
operator|->
name|first
operator|&&
name|processor
operator|->
name|PRI
condition|)
name|processor
operator|->
name|PRI
operator|=
name|pixel_regions_process
argument_list|(
name|processor
operator|->
name|PRI
argument_list|)
expr_stmt|;
else|else
name|processor
operator|->
name|first
operator|=
name|FALSE
expr_stmt|;
while|while
condition|(
name|processor
operator|->
name|PRI
condition|)
block|{
name|guint
name|pixels
init|=
operator|(
name|processor
operator|->
name|PRI
operator|->
name|portion_width
operator|*
name|processor
operator|->
name|PRI
operator|->
name|portion_height
operator|)
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|processor
operator|->
name|num_regions
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|processor
operator|->
name|regions
index|[
name|i
index|]
condition|)
block|{
name|memcpy
argument_list|(
operator|&
name|tr
index|[
name|i
index|]
argument_list|,
name|processor
operator|->
name|regions
index|[
name|i
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|PixelRegion
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tr
index|[
name|i
index|]
operator|.
name|tiles
condition|)
name|tile_lock
argument_list|(
name|tr
index|[
name|i
index|]
operator|.
name|curtile
argument_list|)
expr_stmt|;
block|}
name|g_mutex_unlock
argument_list|(
name|processor
operator|->
name|mutex
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|processor
operator|->
name|num_regions
condition|)
block|{
case|case
literal|1
case|:
operator|(
operator|(
name|p1_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
condition|?
operator|&
name|tr
index|[
literal|0
index|]
else|:
name|NULL
operator|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
operator|(
operator|(
name|p2_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
condition|?
operator|&
name|tr
index|[
literal|0
index|]
else|:
name|NULL
operator|,
name|processor
operator|->
name|regions
index|[
literal|1
index|]
condition|?
operator|&
name|tr
index|[
literal|1
index|]
else|:
name|NULL
operator|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
operator|(
operator|(
name|p3_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
condition|?
operator|&
name|tr
index|[
literal|0
index|]
else|:
name|NULL
operator|,
name|processor
operator|->
name|regions
index|[
literal|1
index|]
condition|?
operator|&
name|tr
index|[
literal|1
index|]
else|:
name|NULL
operator|,
name|processor
operator|->
name|regions
index|[
literal|2
index|]
condition|?
operator|&
name|tr
index|[
literal|2
index|]
else|:
name|NULL
operator|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
operator|(
operator|(
name|p4_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
condition|?
operator|&
name|tr
index|[
literal|0
index|]
else|:
name|NULL
operator|,
name|processor
operator|->
name|regions
index|[
literal|1
index|]
condition|?
operator|&
name|tr
index|[
literal|1
index|]
else|:
name|NULL
operator|,
name|processor
operator|->
name|regions
index|[
literal|2
index|]
condition|?
operator|&
name|tr
index|[
literal|2
index|]
else|:
name|NULL
operator|,
name|processor
operator|->
name|regions
index|[
literal|3
index|]
condition|?
operator|&
name|tr
index|[
literal|3
index|]
else|:
name|NULL
operator|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"do_parallel_regions: Bad number of regions %d\n"
argument_list|,
name|processor
operator|->
name|num_regions
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_mutex_lock
argument_list|(
name|processor
operator|->
name|mutex
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
name|processor
operator|->
name|num_regions
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|processor
operator|->
name|regions
index|[
name|i
index|]
condition|)
block|{
if|if
condition|(
name|tr
index|[
name|i
index|]
operator|.
name|tiles
condition|)
name|tile_release
argument_list|(
name|tr
index|[
name|i
index|]
operator|.
name|curtile
argument_list|,
name|tr
index|[
name|i
index|]
operator|.
name|dirty
argument_list|)
expr_stmt|;
block|}
name|processor
operator|->
name|progress
operator|+=
name|pixels
expr_stmt|;
if|if
condition|(
name|processor
operator|->
name|PRI
condition|)
name|processor
operator|->
name|PRI
operator|=
name|pixel_regions_process
argument_list|(
name|processor
operator|->
name|PRI
argument_list|)
expr_stmt|;
block|}
name|g_mutex_lock
argument_list|(
name|pool_mutex
argument_list|)
expr_stmt|;
name|processor
operator|->
name|threads
operator|--
expr_stmt|;
if|if
condition|(
name|processor
operator|->
name|threads
operator|==
literal|0
condition|)
block|{
name|g_mutex_unlock
argument_list|(
name|pool_mutex
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
name|processor
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|g_cond_signal
argument_list|(
name|pool_cond
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_mutex_unlock
argument_list|(
name|pool_mutex
argument_list|)
expr_stmt|;
name|g_mutex_unlock
argument_list|(
name|processor
operator|->
name|mutex
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  do_parallel_regions_single is just like do_parallel_regions  *   except that all the mutex and tile locks have been removed  *  * If we are processing with only a single thread we don't need to do  * the mutex locks etc. and aditional tile locks even if we were  * configured --with-mp  */
end_comment

begin_function
specifier|static
name|gpointer
DECL|function|do_parallel_regions_single (PixelProcessor * processor,PixelProcessorProgressFunc progress_func,gpointer progress_data,gulong total)
name|do_parallel_regions_single
parameter_list|(
name|PixelProcessor
modifier|*
name|processor
parameter_list|,
name|PixelProcessorProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|,
name|gulong
name|total
parameter_list|)
block|{
name|GTimeVal
name|last_time
decl_stmt|;
if|if
condition|(
name|progress_func
condition|)
name|g_get_current_time
argument_list|(
operator|&
name|last_time
argument_list|)
expr_stmt|;
do|do
block|{
switch|switch
condition|(
name|processor
operator|->
name|num_regions
condition|)
block|{
case|case
literal|1
case|:
operator|(
operator|(
name|p1_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
operator|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
operator|(
operator|(
name|p2_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
operator|,
name|processor
operator|->
name|regions
index|[
literal|1
index|]
operator|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
operator|(
operator|(
name|p3_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
operator|,
name|processor
operator|->
name|regions
index|[
literal|1
index|]
operator|,
name|processor
operator|->
name|regions
index|[
literal|2
index|]
operator|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
operator|(
operator|(
name|p4_func
operator|)
name|processor
operator|->
name|func
operator|)
operator|(
name|processor
operator|->
name|data
operator|,
name|processor
operator|->
name|regions
index|[
literal|0
index|]
operator|,
name|processor
operator|->
name|regions
index|[
literal|1
index|]
operator|,
name|processor
operator|->
name|regions
index|[
literal|2
index|]
operator|,
name|processor
operator|->
name|regions
index|[
literal|3
index|]
operator|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"do_parallel_regions_single: Bad number of regions %d\n"
argument_list|,
name|processor
operator|->
name|num_regions
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|progress_func
condition|)
block|{
name|GTimeVal
name|now
decl_stmt|;
name|processor
operator|->
name|progress
operator|+=
operator|(
name|processor
operator|->
name|PRI
operator|->
name|portion_width
operator|*
name|processor
operator|->
name|PRI
operator|->
name|portion_height
operator|)
expr_stmt|;
name|g_get_current_time
argument_list|(
operator|&
name|now
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|now
operator|.
name|tv_sec
operator|-
name|last_time
operator|.
name|tv_sec
operator|)
operator|*
literal|1024
operator|+
operator|(
name|now
operator|.
name|tv_usec
operator|-
name|last_time
operator|.
name|tv_usec
operator|)
operator|/
literal|1024
operator|)
operator|>
name|PROGRESS_TIMEOUT
condition|)
block|{
name|progress_func
argument_list|(
name|progress_data
argument_list|,
operator|(
name|gdouble
operator|)
name|processor
operator|->
name|progress
operator|/
operator|(
name|gdouble
operator|)
name|total
argument_list|)
expr_stmt|;
name|last_time
operator|=
name|now
expr_stmt|;
block|}
block|}
block|}
do|while
condition|(
name|processor
operator|->
name|PRI
operator|&&
operator|(
name|processor
operator|->
name|PRI
operator|=
name|pixel_regions_process
argument_list|(
name|processor
operator|->
name|PRI
argument_list|)
operator|)
condition|)
do|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pixel_regions_do_parallel (PixelProcessor * processor,PixelProcessorProgressFunc progress_func,gpointer progress_data)
name|pixel_regions_do_parallel
parameter_list|(
name|PixelProcessor
modifier|*
name|processor
parameter_list|,
name|PixelProcessorProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
block|{
name|gulong
name|pixels
init|=
operator|(
name|processor
operator|->
name|PRI
operator|->
name|region_width
operator|*
name|processor
operator|->
name|PRI
operator|->
name|region_height
operator|)
decl_stmt|;
name|gulong
name|tiles
init|=
name|pixels
operator|/
operator|(
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|)
decl_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
if|if
condition|(
name|pool
operator|&&
name|tiles
operator|>
name|TILES_PER_THREAD
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|tasks
init|=
name|MIN
argument_list|(
name|tiles
operator|/
name|TILES_PER_THREAD
argument_list|,
name|g_thread_pool_get_max_threads
argument_list|(
name|pool
argument_list|)
argument_list|)
decl_stmt|;
comment|/*        * g_printerr ("pushing %d tasks into the thread pool (for %lu tiles)\n",        *             tasks, tiles);        */
name|g_mutex_lock
argument_list|(
name|pool_mutex
argument_list|)
expr_stmt|;
name|processor
operator|->
name|first
operator|=
name|TRUE
expr_stmt|;
name|processor
operator|->
name|threads
operator|=
name|tasks
expr_stmt|;
name|processor
operator|->
name|mutex
operator|=
name|g_mutex_new
argument_list|()
expr_stmt|;
while|while
condition|(
name|tasks
operator|--
condition|)
block|{
name|g_thread_pool_push
argument_list|(
name|pool
argument_list|,
name|processor
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_warning
argument_list|(
literal|"thread creation failed: %s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|processor
operator|->
name|threads
operator|--
expr_stmt|;
block|}
block|}
if|if
condition|(
name|progress_func
condition|)
block|{
while|while
condition|(
name|processor
operator|->
name|threads
operator|!=
literal|0
condition|)
block|{
name|gulong
name|progress
decl_stmt|;
name|GTimeVal
name|timeout
decl_stmt|;
name|g_get_current_time
argument_list|(
operator|&
name|timeout
argument_list|)
expr_stmt|;
name|g_time_val_add
argument_list|(
operator|&
name|timeout
argument_list|,
name|PROGRESS_TIMEOUT
operator|*
literal|1024
argument_list|)
expr_stmt|;
name|g_cond_timed_wait
argument_list|(
name|pool_cond
argument_list|,
name|pool_mutex
argument_list|,
operator|&
name|timeout
argument_list|)
expr_stmt|;
name|g_mutex_lock
argument_list|(
name|processor
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|progress
operator|=
name|processor
operator|->
name|progress
expr_stmt|;
name|g_mutex_unlock
argument_list|(
name|processor
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|progress_func
argument_list|(
name|progress_data
argument_list|,
operator|(
name|gdouble
operator|)
name|progress
operator|/
operator|(
name|gdouble
operator|)
name|pixels
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|processor
operator|->
name|threads
operator|!=
literal|0
condition|)
block|{
name|g_cond_wait
argument_list|(
name|pool_cond
argument_list|,
name|pool_mutex
argument_list|)
expr_stmt|;
block|}
block|}
name|g_mutex_unlock
argument_list|(
name|pool_mutex
argument_list|)
expr_stmt|;
name|g_mutex_free
argument_list|(
name|processor
operator|->
name|mutex
argument_list|)
expr_stmt|;
block|}
else|else
endif|#
directive|endif
block|{
name|do_parallel_regions_single
argument_list|(
name|processor
argument_list|,
name|progress_func
argument_list|,
name|progress_data
argument_list|,
name|pixels
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|progress_func
condition|)
name|progress_func
argument_list|(
name|progress_data
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pixel_regions_process_parallel_valist (PixelProcessorFunc func,gpointer data,PixelProcessorProgressFunc progress_func,gpointer progress_data,gint num_regions,va_list ap)
name|pixel_regions_process_parallel_valist
parameter_list|(
name|PixelProcessorFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|PixelProcessorProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|,
name|gint
name|num_regions
parameter_list|,
name|va_list
name|ap
parameter_list|)
block|{
name|PixelProcessor
name|processor
init|=
block|{
name|NULL
block|, }
decl_stmt|;
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
name|num_regions
condition|;
name|i
operator|++
control|)
name|processor
operator|.
name|regions
index|[
name|i
index|]
operator|=
name|va_arg
argument_list|(
name|ap
argument_list|,
name|PixelRegion
operator|*
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|num_regions
condition|)
block|{
case|case
literal|1
case|:
name|processor
operator|.
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|processor
operator|.
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|0
index|]
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|processor
operator|.
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|0
index|]
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|1
index|]
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|processor
operator|.
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|0
index|]
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|1
index|]
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|2
index|]
argument_list|,
name|processor
operator|.
name|regions
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"pixel_regions_process_parallel: "
literal|"bad number of regions (%d)"
argument_list|,
name|processor
operator|.
name|num_regions
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|processor
operator|.
name|PRI
condition|)
block|{
return|return;
block|}
name|processor
operator|.
name|func
operator|=
name|func
expr_stmt|;
name|processor
operator|.
name|data
operator|=
name|data
expr_stmt|;
name|processor
operator|.
name|num_regions
operator|=
name|num_regions
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
name|processor
operator|.
name|threads
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
name|processor
operator|.
name|progress
operator|=
literal|0
expr_stmt|;
name|pixel_regions_do_parallel
argument_list|(
operator|&
name|processor
argument_list|,
name|progress_func
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_processor_init (gint num_threads)
name|pixel_processor_init
parameter_list|(
name|gint
name|num_threads
parameter_list|)
block|{
name|pixel_processor_set_num_threads
argument_list|(
name|num_threads
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_processor_set_num_threads (gint num_threads)
name|pixel_processor_set_num_threads
parameter_list|(
name|gint
name|num_threads
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|ENABLE_MP
name|g_return_if_fail
argument_list|(
name|num_threads
operator|>
literal|0
operator|&&
name|num_threads
operator|<=
name|GIMP_MAX_NUM_THREADS
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_threads
operator|<
literal|2
condition|)
block|{
if|if
condition|(
name|pool
condition|)
block|{
name|g_thread_pool_free
argument_list|(
name|pool
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pool
operator|=
name|NULL
expr_stmt|;
name|g_cond_free
argument_list|(
name|pool_cond
argument_list|)
expr_stmt|;
name|pool_cond
operator|=
name|NULL
expr_stmt|;
name|g_mutex_free
argument_list|(
name|pool_mutex
argument_list|)
expr_stmt|;
name|pool_mutex
operator|=
name|NULL
expr_stmt|;
block|}
block|}
else|else
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|pool
condition|)
block|{
name|g_thread_pool_set_max_threads
argument_list|(
name|pool
argument_list|,
name|num_threads
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pool
operator|=
name|g_thread_pool_new
argument_list|(
operator|(
name|GFunc
operator|)
name|do_parallel_regions
argument_list|,
name|NULL
argument_list|,
name|num_threads
argument_list|,
name|TRUE
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|pool_mutex
operator|=
name|g_mutex_new
argument_list|()
expr_stmt|;
name|pool_cond
operator|=
name|g_cond_new
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|error
condition|)
block|{
name|g_warning
argument_list|(
literal|"changing the number of threads to %d failed: %s"
argument_list|,
name|num_threads
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|pixel_processor_exit (void)
name|pixel_processor_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|pixel_processor_set_num_threads
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_regions_process_parallel (PixelProcessorFunc func,gpointer data,gint num_regions,...)
name|pixel_regions_process_parallel
parameter_list|(
name|PixelProcessorFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint
name|num_regions
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|va
decl_stmt|;
name|va_start
argument_list|(
name|va
argument_list|,
name|num_regions
argument_list|)
expr_stmt|;
name|pixel_regions_process_parallel_valist
argument_list|(
name|func
argument_list|,
name|data
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|num_regions
argument_list|,
name|va
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|va
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_regions_process_parallel_progress (PixelProcessorFunc func,gpointer data,PixelProcessorProgressFunc progress_func,gpointer progress_data,gint num_regions,...)
name|pixel_regions_process_parallel_progress
parameter_list|(
name|PixelProcessorFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|PixelProcessorProgressFunc
name|progress_func
parameter_list|,
name|gpointer
name|progress_data
parameter_list|,
name|gint
name|num_regions
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|va
decl_stmt|;
name|va_start
argument_list|(
name|va
argument_list|,
name|num_regions
argument_list|)
expr_stmt|;
name|pixel_regions_process_parallel_valist
argument_list|(
name|func
argument_list|,
name|data
argument_list|,
name|progress_func
argument_list|,
name|progress_data
argument_list|,
name|num_regions
argument_list|,
name|va
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|va
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

