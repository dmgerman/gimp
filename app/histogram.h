begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__HISTOGRAM_H__
end_ifndef

begin_define
DECL|macro|__HISTOGRAM_H__
define|#
directive|define
name|__HISTOGRAM_H__
end_define

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_define
DECL|macro|HISTOGRAM_VALUE
define|#
directive|define
name|HISTOGRAM_VALUE
value|0
end_define

begin_define
DECL|macro|HISTOGRAM_RED
define|#
directive|define
name|HISTOGRAM_RED
value|1
end_define

begin_define
DECL|macro|HISTOGRAM_GREEN
define|#
directive|define
name|HISTOGRAM_GREEN
value|2
end_define

begin_define
DECL|macro|HISTOGRAM_BLUE
define|#
directive|define
name|HISTOGRAM_BLUE
value|3
end_define

begin_define
DECL|macro|HISTOGRAM_ALPHA
define|#
directive|define
name|HISTOGRAM_ALPHA
value|4
end_define

begin_comment
comment|/*  Histogram information function  */
end_comment

begin_typedef
DECL|typedef|Histogram
typedef|typedef
name|struct
name|_Histogram
name|Histogram
typedef|;
end_typedef

begin_struct
DECL|struct|_Histogram
struct|struct
name|_Histogram
block|{
comment|/*  The calling procedure is responsible for showing this widget  */
DECL|member|histogram_widget
name|GtkWidget
modifier|*
name|histogram_widget
decl_stmt|;
comment|/*  Don't touch this :)  */
DECL|member|private_part
name|void
modifier|*
name|private_part
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|Values
typedef|typedef
name|double
name|Values
index|[
literal|256
index|]
typedef|;
end_typedef

begin_typedef
DECL|typedef|HistogramValues
typedef|typedef
name|Values
name|HistogramValues
index|[
literal|5
index|]
typedef|;
end_typedef

begin_typedef
DECL|typedef|HistogramInfoFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|HistogramInfoFunc
function_decl|)
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|PixelRegion
modifier|*
parameter_list|,
name|HistogramValues
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|HistogramRangeCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|HistogramRangeCallback
function_decl|)
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|HistogramValues
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  Histogram functions  */
end_comment

begin_function_decl
name|Histogram
modifier|*
name|histogram_create
parameter_list|(
name|int
parameter_list|,
name|int
parameter_list|,
name|HistogramRangeCallback
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_free
parameter_list|(
name|Histogram
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_update
parameter_list|(
name|Histogram
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|HistogramInfoFunc
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_range
parameter_list|(
name|Histogram
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_channel
parameter_list|(
name|Histogram
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|HistogramValues
modifier|*
name|histogram_values
parameter_list|(
name|Histogram
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __HISTOGRAM_H__ */
end_comment

end_unit

