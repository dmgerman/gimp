begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * pixel_processor.c: Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"pixel_processor.h"
end_include

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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

begin_define
DECL|macro|IF_THREAD (statement)
define|#
directive|define
name|IF_THREAD
parameter_list|(
name|statement
parameter_list|)
value|statement
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !USE_PTHREADS */
end_comment

begin_define
DECL|macro|IF_THREAD (statement)
define|#
directive|define
name|IF_THREAD
parameter_list|(
name|statement
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !USE_PTHREADS */
end_comment

begin_typedef
DECL|typedef|p1_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p1_func
function_decl|)
parameter_list|(
name|void
modifier|*
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
name|void
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
DECL|typedef|p3_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p3_func
function_decl|)
parameter_list|(
name|void
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

begin_typedef
DECL|typedef|p4_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p4_func
function_decl|)
parameter_list|(
name|void
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
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|PixelRegionIterator
typedef|typedef
name|struct
name|_PixelRegionIterator
name|PixelRegionIterator
typedef|;
end_typedef

begin_struct
DECL|struct|_PixelProcessor
struct|struct
name|_PixelProcessor
block|{
DECL|member|data
name|void
modifier|*
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
name|IF_THREAD
argument_list|(
argument|pthread_mutex_t mutex;
argument_list|)
name|int
name|nthreads
decl_stmt|;
DECL|member|n_regions
name|int
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
name|int
name|ntiles
init|=
literal|0
decl_stmt|;
name|int
name|i
decl_stmt|;
name|int
name|cont
init|=
literal|1
decl_stmt|;
name|IF_THREAD
argument_list|(
argument|pthread_mutex_lock(&p_s->mutex);
argument_list|)
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
operator|(
name|PixelRegionIterator
operator|*
operator|)
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
name|IF_THREAD
argument_list|(
argument|pthread_mutex_unlock(&p_s->mutex);
argument_list|)
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
name|IF_THREAD
argument_list|(
argument|pthread_mutex_unlock(&p_s->mutex);
argument_list|)
name|ntiles
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
name|g_message
argument_list|(
literal|"do_parallel_regions: Bad number of regions %d\n"
argument_list|,
name|p_s
operator|->
name|n_regions
argument_list|)
expr_stmt|;
block|}
name|IF_THREAD
argument_list|(
argument|pthread_mutex_lock(&p_s->mutex);
argument_list|)
if|if
condition|(
name|p_s
operator|->
name|progress_report_func
condition|)
if|if
condition|(
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
operator|(
name|PixelRegionIterator
operator|*
operator|)
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
comment|/*  fprintf(stderr, "processed %d tiles\n", ntiles); */
name|IF_THREAD
argument_list|(
argument|pthread_mutex_unlock(&p_s->mutex);
argument_list|)
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
name|IF_THREAD
argument_list|(
argument|int i;
argument_list|)
name|IF_THREAD
argument_list|(
argument|int nthreads;
argument_list|)
name|IF_THREAD
argument_list|(
argument|pthread_t threads[MAX_THREADS];
argument_list|)
name|IF_THREAD
argument_list|(
argument|pthread_attr_t pthread_attr;
argument_list|)
comment|/*		 (p_s->PRI->region_width * p_s->PRI->region_height) /(64*64)); */
name|IF_THREAD
argument_list|(
argument|nthreads = MIN(num_processors,
literal|5
argument|);     if (nthreads>
literal|1
argument|)     {       pthread_attr_init (&pthread_attr);       for (i =
literal|0
argument|; i< nthreads; i++)       { 	pthread_create (&threads[i],&pthread_attr, 			(void *(*)(void *)) do_parallel_regions, 			p_s);       }       for (i =
literal|0
argument|; i< nthreads; i++)       { 	pthread_join(threads[i], NULL);       }     }     else
argument_list|)
name|do_parallel_regions
argument_list|(
name|p_s
argument_list|)
expr_stmt|;
if|if
condition|(
name|p_s
operator|->
name|nthreads
operator|!=
literal|0
condition|)
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Ack, we lost a thread\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|PixelProcessor
modifier|*
DECL|function|pixel_regions_real_process_parallel (p_func f,void * data,ProgressReportFunc report_func,void * report_data,int num_regions,va_list ap)
name|pixel_regions_real_process_parallel
parameter_list|(
name|p_func
name|f
parameter_list|,
name|void
modifier|*
name|data
parameter_list|,
name|ProgressReportFunc
name|report_func
parameter_list|,
name|void
modifier|*
name|report_data
parameter_list|,
name|int
name|num_regions
parameter_list|,
name|va_list
name|ap
parameter_list|)
block|{
name|int
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
literal|200
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
operator|(
name|PixelRegionIterator
operator|*
operator|)
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
operator|(
name|PixelRegionIterator
operator|*
operator|)
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
operator|(
name|PixelRegionIterator
operator|*
operator|)
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
operator|(
name|PixelRegionIterator
operator|*
operator|)
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
name|g_message
argument_list|(
literal|"pixel_regions_real_process_parallel: Bad number of regions %d\n"
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
name|IF_THREAD
argument_list|(
argument|pthread_mutex_init(&(p_s->mutex), NULL);
argument_list|)
name|p_s
operator|->
name|nthreads
operator|=
literal|0
expr_stmt|;
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
DECL|function|pixel_regions_process_parallel (p_func f,void * data,int num_regions,...)
name|pixel_regions_process_parallel
parameter_list|(
name|p_func
name|f
parameter_list|,
name|void
modifier|*
name|data
parameter_list|,
name|int
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
DECL|function|pixel_regions_process_parallel_progress (p_func f,void * data,ProgressReportFunc progress_func,void * progress_data,int num_regions,...)
name|pixel_regions_process_parallel_progress
parameter_list|(
name|p_func
name|f
parameter_list|,
name|void
modifier|*
name|data
parameter_list|,
name|ProgressReportFunc
name|progress_func
parameter_list|,
name|void
modifier|*
name|progress_data
parameter_list|,
name|int
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

