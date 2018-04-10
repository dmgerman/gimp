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
block|}
end_extern

begin_endif
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
