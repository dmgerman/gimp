begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * pixel_processor.h: Copyright (C) 1999 Jay Cox<jaycox@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PIXEL_PROCESSOR_H__
end_ifndef

begin_define
DECL|macro|__PIXEL_PROCESSOR_H__
define|#
directive|define
name|__PIXEL_PROCESSOR_H__
end_define

begin_define
DECL|macro|GIMP_MAX_NUM_THREADS
define|#
directive|define
name|GIMP_MAX_NUM_THREADS
value|16
end_define

begin_typedef
DECL|typedef|PixelProcessorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|PixelProcessorFunc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|PixelProcessorProgressFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|PixelProcessorProgressFunc
function_decl|)
parameter_list|(
name|gpointer
name|progress_data
parameter_list|,
name|gdouble
name|fraction
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|pixel_processor_init
parameter_list|(
name|gint
name|num_threads
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_processor_set_num_threads
parameter_list|(
name|gint
name|num_threads
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_processor_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PIXEL_PROCESSOR_H__ */
end_comment

end_unit

