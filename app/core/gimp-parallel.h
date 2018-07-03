begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-parallel.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PARALLEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PARALLEL_H__
define|#
directive|define
name|__GIMP_PARALLEL_H__
end_define

begin_typedef
DECL|typedef|GimpParallelRunAsyncFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpParallelRunAsyncFunc
function_decl|)
parameter_list|(
name|GimpAsync
modifier|*
name|async
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpParallelDistributeFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpParallelDistributeFunc
function_decl|)
parameter_list|(
name|gint
name|i
parameter_list|,
name|gint
name|n
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpParallelDistributeRangeFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpParallelDistributeRangeFunc
function_decl|)
parameter_list|(
name|gsize
name|offset
parameter_list|,
name|gsize
name|size
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpParallelDistributeAreaFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpParallelDistributeAreaFunc
function_decl|)
parameter_list|(
specifier|const
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_parallel_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parallel_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAsync
modifier|*
name|gimp_parallel_run_async
parameter_list|(
name|GimpParallelRunAsyncFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAsync
modifier|*
name|gimp_parallel_run_async_full
parameter_list|(
name|gint
name|priority
parameter_list|,
name|GimpParallelRunAsyncFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GDestroyNotify
name|user_data_destroy_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAsync
modifier|*
name|gimp_parallel_run_async_independent
parameter_list|(
name|GimpParallelRunAsyncFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parallel_distribute
parameter_list|(
name|gint
name|max_n
parameter_list|,
name|GimpParallelDistributeFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parallel_distribute_range
parameter_list|(
name|gsize
name|size
parameter_list|,
name|gsize
name|min_sub_size
parameter_list|,
name|GimpParallelDistributeRangeFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parallel_distribute_area
parameter_list|(
specifier|const
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|gsize
name|min_sub_area
parameter_list|,
name|GimpParallelDistributeAreaFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C++"
block|{
include|#
directive|include
file|<new>
name|template
operator|<
name|class
name|ParallelRunAsyncFunc
operator|>
specifier|inline
name|GimpAsync
operator|*
DECL|function|gimp_parallel_run_async (ParallelRunAsyncFunc func)
name|gimp_parallel_run_async
argument_list|(
argument|ParallelRunAsyncFunc func
argument_list|)
block|{
name|ParallelRunAsyncFunc
operator|*
name|func_copy
operator|=
name|g_new
argument_list|(
name|ParallelRunAsyncFunc
argument_list|,
literal|1
argument_list|)
block|;
name|new
argument_list|(
argument|func_copy
argument_list|)
name|ParallelRunAsyncFunc
argument_list|(
name|func
argument_list|)
block|;
return|return
name|gimp_parallel_run_async_full
argument_list|(
literal|0
argument_list|,
index|[]
operator|(
name|GimpAsync
operator|*
name|async
operator|,
name|gpointer
name|user_data
operator|)
block|{
name|ParallelRunAsyncFunc
operator|*
name|func_copy
operator|=
operator|(
name|ParallelRunAsyncFunc
operator|*
operator|)
name|user_data
block|;
call|(
modifier|*
name|func_copy
call|)
argument_list|(
name|async
argument_list|)
block|;
name|func_copy
operator|->
expr|~
name|ParallelRunAsyncFunc
argument_list|()
block|;
name|g_free
argument_list|(
name|func_copy
argument_list|)
block|;                                        }
argument_list|,
name|func_copy
argument_list|,
index|[]
operator|(
name|gpointer
name|user_data
operator|)
block|{
name|ParallelRunAsyncFunc
operator|*
name|func_copy
operator|=
operator|(
name|ParallelRunAsyncFunc
operator|*
operator|)
name|user_data
block|;
name|func_copy
operator|->
expr|~
name|ParallelRunAsyncFunc
argument_list|()
block|;
name|g_free
argument_list|(
name|func_copy
argument_list|)
block|;                                        }
argument_list|)
return|;
block|}
name|template
operator|<
name|class
name|ParallelRunAsyncFunc
operator|,
name|class
name|DestroyFunc
operator|>
specifier|inline
name|GimpAsync
operator|*
DECL|function|gimp_parallel_run_async_full (gint priority,ParallelRunAsyncFunc func,DestroyFunc destroy_func)
name|gimp_parallel_run_async_full
argument_list|(
argument|gint                 priority
argument_list|,
argument|ParallelRunAsyncFunc func
argument_list|,
argument|DestroyFunc          destroy_func
argument_list|)
block|{
typedef|typedef
struct|struct
DECL|struct|__anon28d11d5d0108
block|{
DECL|member|func
name|ParallelRunAsyncFunc
name|func
decl_stmt|;
DECL|member|destroy_func
name|DestroyFunc
name|destroy_func
decl_stmt|;
DECL|typedef|Funcs
block|}
name|Funcs
expr_stmt|;
name|Funcs
modifier|*
name|funcs_copy
init|=
name|g_new
argument_list|(
name|Funcs
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|new
argument_list|(
argument|funcs_copy
argument_list|)
name|Funcs
block|{
name|func
operator|,
name|destroy_func
block|}
empty_stmt|;
return|return
name|gimp_parallel_run_async_full
argument_list|(
name|priority
argument_list|,
index|[]
operator|(
name|GimpAsync
operator|*
name|async
operator|,
name|gpointer
name|user_data
operator|)
block|{
name|Funcs
operator|*
name|funcs_copy
operator|=
operator|(
name|Funcs
operator|*
operator|)
name|user_data
block|;
name|funcs_copy
operator|->
name|func
argument_list|(
name|async
argument_list|)
block|;
name|funcs_copy
operator|->
expr|~
name|Funcs
argument_list|()
block|;
name|g_free
argument_list|(
name|funcs_copy
argument_list|)
block|;                                        }
argument_list|,
name|funcs_copy
argument_list|,
index|[]
operator|(
name|gpointer
name|user_data
operator|)
block|{
name|Funcs
operator|*
name|funcs_copy
operator|=
operator|(
name|Funcs
operator|*
operator|)
name|user_data
block|;
name|funcs_copy
operator|->
name|destroy_func
argument_list|()
block|;
name|funcs_copy
operator|->
expr|~
name|Funcs
argument_list|()
block|;
name|g_free
argument_list|(
name|funcs_copy
argument_list|)
block|;                                        }
argument_list|)
return|;
block|}
end_extern

begin_expr_stmt
name|template
operator|<
name|class
name|ParallelRunAsyncFunc
operator|>
specifier|inline
name|GimpAsync
operator|*
DECL|function|gimp_parallel_run_async_independent (ParallelRunAsyncFunc func)
name|gimp_parallel_run_async_independent
argument_list|(
argument|ParallelRunAsyncFunc func
argument_list|)
block|{
name|ParallelRunAsyncFunc
operator|*
name|func_copy
operator|=
name|g_new
argument_list|(
name|ParallelRunAsyncFunc
argument_list|,
literal|1
argument_list|)
block|;
name|new
argument_list|(
argument|func_copy
argument_list|)
name|ParallelRunAsyncFunc
argument_list|(
name|func
argument_list|)
block|;
return|return
name|gimp_parallel_run_async_independent
argument_list|(
index|[]
operator|(
name|GimpAsync
operator|*
name|async
operator|,
name|gpointer
name|user_data
operator|)
block|{
name|ParallelRunAsyncFunc
operator|*
name|func_copy
operator|=
operator|(
name|ParallelRunAsyncFunc
operator|*
operator|)
name|user_data
block|;
call|(
modifier|*
name|func_copy
call|)
argument_list|(
name|async
argument_list|)
block|;
name|func_copy
operator|->
expr|~
name|ParallelRunAsyncFunc
argument_list|()
block|;
name|g_free
argument_list|(
name|func_copy
argument_list|)
block|;                                               }
argument_list|,
name|func_copy
argument_list|)
return|;
block|}
end_expr_stmt

begin_expr_stmt
name|template
operator|<
name|class
name|ParallelDistributeFunc
operator|>
specifier|inline
name|void
DECL|function|gimp_parallel_distribute (gint max_n,ParallelDistributeFunc func)
name|gimp_parallel_distribute
argument_list|(
argument|gint                   max_n
argument_list|,
argument|ParallelDistributeFunc func
argument_list|)
block|{
name|gimp_parallel_distribute
argument_list|(
name|max_n
argument_list|,
index|[]
operator|(
name|gint
name|i
operator|,
name|gint
name|n
operator|,
name|gpointer
name|user_data
operator|)
block|{
name|ParallelDistributeFunc
name|func_copy
argument_list|(
operator|*
operator|(
specifier|const
name|ParallelDistributeFunc
operator|*
operator|)
name|user_data
argument_list|)
block|;
name|func_copy
argument_list|(
name|i
argument_list|,
name|n
argument_list|)
block|;                             }
argument_list|,
operator|&
name|func
argument_list|)
block|; }
name|template
operator|<
name|class
name|ParallelDistributeRangeFunc
operator|>
specifier|inline
name|void
DECL|function|gimp_parallel_distribute_range (gsize size,gsize min_sub_size,ParallelDistributeRangeFunc func)
name|gimp_parallel_distribute_range
argument_list|(
argument|gsize                       size
argument_list|,
argument|gsize                       min_sub_size
argument_list|,
argument|ParallelDistributeRangeFunc func
argument_list|)
block|{
name|gimp_parallel_distribute_range
argument_list|(
name|size
argument_list|,
name|min_sub_size
argument_list|,
index|[]
operator|(
name|gsize
name|offset
operator|,
name|gsize
name|size
operator|,
name|gpointer
name|user_data
operator|)
block|{
name|ParallelDistributeRangeFunc
name|func_copy
argument_list|(
operator|*
operator|(
specifier|const
name|ParallelDistributeRangeFunc
operator|*
operator|)
name|user_data
argument_list|)
block|;
name|func_copy
argument_list|(
name|offset
argument_list|,
name|size
argument_list|)
block|;                                   }
argument_list|,
operator|&
name|func
argument_list|)
block|; }
name|template
operator|<
name|class
name|ParallelDistributeAreaFunc
operator|>
specifier|inline
name|void
DECL|function|gimp_parallel_distribute_area (const GeglRectangle * area,gsize min_sub_area,ParallelDistributeAreaFunc func)
name|gimp_parallel_distribute_area
argument_list|(
argument|const GeglRectangle        *area
argument_list|,
argument|gsize                       min_sub_area
argument_list|,
argument|ParallelDistributeAreaFunc  func
argument_list|)
block|{
name|gimp_parallel_distribute_area
argument_list|(
name|area
argument_list|,
name|min_sub_area
argument_list|,
index|[]
operator|(
specifier|const
name|GeglRectangle
operator|*
name|area
operator|,
name|gpointer
name|user_data
operator|)
block|{
name|ParallelDistributeAreaFunc
name|func_copy
argument_list|(
operator|*
operator|(
specifier|const
name|ParallelDistributeAreaFunc
operator|*
operator|)
name|user_data
argument_list|)
block|;
name|func_copy
argument_list|(
name|area
argument_list|)
block|;                                  }
argument_list|,
operator|&
name|func
argument_list|)
block|; }
end_expr_stmt

begin_endif
unit|}
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PARALLEL_H__ */
end_comment

end_unit

