begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * pixel_processor.h: Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_typedef
DECL|typedef|PixelProcessor
typedef|typedef
name|struct
name|_PixelProcessor
name|PixelProcessor
typedef|;
end_typedef

begin_typedef
DECL|typedef|p_func
typedef|typedef
name|void
function_decl|(
modifier|*
name|p_func
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ProgressReportFunc
typedef|typedef
name|int
function_decl|(
modifier|*
name|ProgressReportFunc
function_decl|)
parameter_list|(
name|void
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|PixelProcessor
modifier|*
name|pixel_process_progress
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_processor_free
parameter_list|(
name|PixelProcessor
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_processor_stop
parameter_list|(
name|PixelProcessor
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PixelProcessor
modifier|*
name|pixel_processor_cont
parameter_list|(
name|PixelProcessor
modifier|*
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

