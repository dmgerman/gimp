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
file|<pthread.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_MP
end_ifdef

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|FIXME: extern GimpBaseConfig *base_config;
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|GimpBaseConfig
modifier|*
name|base_config
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
parameter_list|,
name|PixelRegion
modifier|*
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
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
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
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
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
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|_PixelProcessor
struct|struct
name|_PixelProcessor
block|{
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|f
name|p_func
name|f
decl_stmt|;
DECL|member|PRI
name|PixelRegionIterator
modifier|*
name|PRI
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
endif|#
directive|endif
DECL|member|n_regions
name|gint
name|n_regions
decl_stmt|;
DECL|member|r
name|PixelRegion
modifier|*
name|r
index|[
literal|4
index|]
decl_stmt|;
DECL|member|progress_report_data
name|void
modifier|*
name|progress_report_data
decl_stmt|;
DECL|member|progress_report_func
name|ProgressReportFunc
name|progress_report_func
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
modifier|*
DECL|function|do_parallel_regions (PixelProcessor * p_s)
name|do_parallel_regions
parameter_list|(
name|PixelProcessor
modifier|*
name|p_s
parameter_list|)
block|{
name|PixelRegion
name|tr
index|[
literal|4
index|]
decl_stmt|;
name|gint
name|n_tiles
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|cont
init|=
literal|1
decl_stmt|;
name|pthread_mutex_lock
argument_list|(
operator|&
name|p_s
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|p_s
operator|->
name|nthreads
operator|!=
literal|0
operator|&&
name|p_s
operator|->
name|PRI
condition|)
name|p_s
operator|->
name|PRI
operator|=
name|pixel_regions_process
argument_list|(
name|p_s
operator|->
name|PRI
argument_list|)
expr_stmt|;
if|if
condition|(
name|p_s
operator|->
name|PRI
operator|==
name|NULL
condition|)
block|{
name|pthread_mutex_unlock
argument_list|(
operator|&
name|p_s
operator|->
name|mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|p_s
operator|->
name|nthreads
operator|++
expr_stmt|;
do|do
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|p_s
operator|->
name|n_regions
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|r
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
name|pthread_mutex_unlock
argument_list|(
operator|&
name|p_s
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|n_tiles
operator|++
expr_stmt|;
switch|switch
condition|(
name|p_s
operator|->
name|n_regions
condition|)
block|{
case|case
literal|1
case|:
operator|(
operator|(
name|p1_func
operator|)
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|n_regions
argument_list|)
expr_stmt|;
break|break;
block|}
name|pthread_mutex_lock
argument_list|(
operator|&
name|p_s
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
name|p_s
operator|->
name|n_regions
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|p_s
operator|->
name|r
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
if|if
condition|(
name|p_s
operator|->
name|progress_report_func
operator|&&
operator|!
name|p_s
operator|->
name|progress_report_func
argument_list|(
name|p_s
operator|->
name|progress_report_data
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|x
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|y
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|w
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|h
argument_list|)
condition|)
name|cont
operator|=
literal|0
expr_stmt|;
block|}
do|while
condition|(
name|cont
operator|&&
name|p_s
operator|->
name|PRI
operator|&&
operator|(
name|p_s
operator|->
name|PRI
operator|=
name|pixel_regions_process
argument_list|(
name|p_s
operator|->
name|PRI
argument_list|)
operator|)
condition|)
do|;
name|p_s
operator|->
name|nthreads
operator|--
expr_stmt|;
name|pthread_mutex_unlock
argument_list|(
operator|&
name|p_s
operator|->
name|mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  do_parallel_regions_single is just like do_parallel_regions   *   except that all the mutex and tile locks have been removed  *  * If we are processing with only a single thread we don't need to do the  * mutex locks etc. and aditional tile locks even if we were  * configured --with-mp  */
end_comment

begin_function
specifier|static
name|gpointer
DECL|function|do_parallel_regions_single (PixelProcessor * p_s)
name|do_parallel_regions_single
parameter_list|(
name|PixelProcessor
modifier|*
name|p_s
parameter_list|)
block|{
name|gint
name|cont
init|=
literal|1
decl_stmt|;
do|do
block|{
switch|switch
condition|(
name|p_s
operator|->
name|n_regions
condition|)
block|{
case|case
literal|1
case|:
operator|(
operator|(
name|p1_func
operator|)
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|,
name|p_s
operator|->
name|r
index|[
literal|1
index|]
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|f
operator|)
operator|(
name|p_s
operator|->
name|data
operator|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|,
name|p_s
operator|->
name|r
index|[
literal|1
index|]
operator|,
name|p_s
operator|->
name|r
index|[
literal|2
index|]
operator|,
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|n_regions
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|p_s
operator|->
name|progress_report_func
operator|&&
operator|!
name|p_s
operator|->
name|progress_report_func
argument_list|(
name|p_s
operator|->
name|progress_report_data
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|x
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|y
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|w
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
operator|->
name|h
argument_list|)
condition|)
name|cont
operator|=
literal|0
expr_stmt|;
block|}
do|while
condition|(
name|cont
operator|&&
name|p_s
operator|->
name|PRI
operator|&&
operator|(
name|p_s
operator|->
name|PRI
operator|=
name|pixel_regions_process
argument_list|(
name|p_s
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

begin_define
DECL|macro|MAX_THREADS
define|#
directive|define
name|MAX_THREADS
value|30
end_define

begin_function
specifier|static
name|void
DECL|function|pixel_regions_do_parallel (PixelProcessor * p_s)
name|pixel_regions_do_parallel
parameter_list|(
name|PixelProcessor
modifier|*
name|p_s
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|ENABLE_MP
name|gint
name|nthreads
decl_stmt|;
name|nthreads
operator|=
name|MIN
argument_list|(
name|base_config
operator|->
name|num_processors
argument_list|,
name|MAX_THREADS
argument_list|)
expr_stmt|;
comment|/* make sure we have at least one tile per thread */
name|nthreads
operator|=
name|MIN
argument_list|(
name|nthreads
argument_list|,
operator|(
name|p_s
operator|->
name|PRI
operator|->
name|region_width
operator|*
name|p_s
operator|->
name|PRI
operator|->
name|region_height
operator|)
operator|/
operator|(
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|nthreads
operator|>
literal|1
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|pthread_t
name|threads
index|[
name|MAX_THREADS
index|]
decl_stmt|;
name|pthread_attr_t
name|pthread_attr
decl_stmt|;
name|pthread_attr_init
argument_list|(
operator|&
name|pthread_attr
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
name|nthreads
condition|;
name|i
operator|++
control|)
block|{
name|pthread_create
argument_list|(
operator|&
name|threads
index|[
name|i
index|]
argument_list|,
operator|&
name|pthread_attr
argument_list|,
operator|(
name|void
operator|*
call|(
modifier|*
call|)
argument_list|(
name|void
operator|*
argument_list|)
operator|)
name|do_parallel_regions
argument_list|,
name|p_s
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nthreads
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|ret
decl_stmt|;
if|if
condition|(
operator|(
name|ret
operator|=
name|pthread_join
argument_list|(
name|threads
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|)
operator|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"pixel_regions_do_parallel: "
literal|"pthread_join returned: %d\n"
argument_list|,
name|ret
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|p_s
operator|->
name|nthreads
operator|!=
literal|0
condition|)
name|g_printerr
argument_list|(
literal|"pixel_regions_do_prarallel: we lost a thread\n"
argument_list|)
expr_stmt|;
block|}
else|else
endif|#
directive|endif
name|do_parallel_regions_single
argument_list|(
name|p_s
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|PixelProcessor
modifier|*
DECL|function|pixel_regions_real_process_parallel (p_func f,gpointer data,ProgressReportFunc report_func,gpointer report_data,gint num_regions,va_list ap)
name|pixel_regions_real_process_parallel
parameter_list|(
name|p_func
name|f
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|ProgressReportFunc
name|report_func
parameter_list|,
name|gpointer
name|report_data
parameter_list|,
name|gint
name|num_regions
parameter_list|,
name|va_list
name|ap
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|PixelProcessor
modifier|*
name|p_s
decl_stmt|;
name|p_s
operator|=
name|g_new
argument_list|(
name|PixelProcessor
argument_list|,
literal|1
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
name|num_regions
condition|;
name|i
operator|++
control|)
name|p_s
operator|->
name|r
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
name|p_s
operator|->
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|p_s
operator|->
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|p_s
operator|->
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|1
index|]
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|p_s
operator|->
name|PRI
operator|=
name|pixel_regions_register
argument_list|(
name|num_regions
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|0
index|]
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|1
index|]
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|2
index|]
argument_list|,
name|p_s
operator|->
name|r
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"pixel_regions_real_process_parallel:"
literal|"Bad number of regions %d\n"
argument_list|,
name|p_s
operator|->
name|n_regions
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|p_s
operator|->
name|PRI
condition|)
block|{
name|pixel_processor_free
argument_list|(
name|p_s
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|p_s
operator|->
name|f
operator|=
name|f
expr_stmt|;
name|p_s
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|p_s
operator|->
name|n_regions
operator|=
name|num_regions
expr_stmt|;
ifdef|#
directive|ifdef
name|ENABLE_MP
name|pthread_mutex_init
argument_list|(
operator|&
name|p_s
operator|->
name|mutex
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|p_s
operator|->
name|nthreads
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
name|p_s
operator|->
name|progress_report_data
operator|=
name|report_data
expr_stmt|;
name|p_s
operator|->
name|progress_report_func
operator|=
name|report_func
expr_stmt|;
name|pixel_regions_do_parallel
argument_list|(
name|p_s
argument_list|)
expr_stmt|;
if|if
condition|(
name|p_s
operator|->
name|PRI
condition|)
return|return
name|p_s
return|;
ifdef|#
directive|ifdef
name|ENABLE_MP
name|pthread_mutex_destroy
argument_list|(
operator|&
name|p_s
operator|->
name|mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|pixel_processor_free
argument_list|(
name|p_s
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_regions_process_parallel (p_func f,gpointer data,gint num_regions,...)
name|pixel_regions_process_parallel
parameter_list|(
name|p_func
name|f
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
name|pixel_regions_real_process_parallel
argument_list|(
name|f
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
name|PixelProcessor
modifier|*
DECL|function|pixel_regions_process_parallel_progress (p_func f,gpointer data,ProgressReportFunc progress_func,gpointer progress_data,gint num_regions,...)
name|pixel_regions_process_parallel_progress
parameter_list|(
name|p_func
name|f
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|ProgressReportFunc
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
name|PixelProcessor
modifier|*
name|ret
decl_stmt|;
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
name|ret
operator|=
name|pixel_regions_real_process_parallel
argument_list|(
name|f
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
return|return
name|ret
return|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_processor_stop (PixelProcessor * pp)
name|pixel_processor_stop
parameter_list|(
name|PixelProcessor
modifier|*
name|pp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|pp
condition|)
return|return;
if|if
condition|(
name|pp
operator|->
name|PRI
condition|)
block|{
name|pixel_regions_process_stop
argument_list|(
name|pp
operator|->
name|PRI
argument_list|)
expr_stmt|;
name|pp
operator|->
name|PRI
operator|=
name|NULL
expr_stmt|;
block|}
name|pixel_processor_free
argument_list|(
name|pp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|PixelProcessor
modifier|*
DECL|function|pixel_processor_cont (PixelProcessor * pp)
name|pixel_processor_cont
parameter_list|(
name|PixelProcessor
modifier|*
name|pp
parameter_list|)
block|{
name|pixel_regions_do_parallel
argument_list|(
name|pp
argument_list|)
expr_stmt|;
if|if
condition|(
name|pp
operator|->
name|PRI
condition|)
return|return
name|pp
return|;
name|pixel_processor_free
argument_list|(
name|pp
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|pixel_processor_free (PixelProcessor * pp)
name|pixel_processor_free
parameter_list|(
name|PixelProcessor
modifier|*
name|pp
parameter_list|)
block|{
if|if
condition|(
name|pp
operator|->
name|PRI
condition|)
name|pixel_processor_stop
argument_list|(
name|pp
argument_list|)
expr_stmt|;
else|else
name|g_free
argument_list|(
name|pp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

