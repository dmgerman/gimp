begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__HISTOGRAM_TOOL_H__
end_ifndef

begin_define
DECL|macro|__HISTOGRAM_TOOL_H__
define|#
directive|define
name|__HISTOGRAM_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"histogramwidget.h"
end_include

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_define
DECL|macro|HISTOGRAM_WIDTH
define|#
directive|define
name|HISTOGRAM_WIDTH
value|256
end_define

begin_define
DECL|macro|HISTOGRAM_HEIGHT
define|#
directive|define
name|HISTOGRAM_HEIGHT
value|150
end_define

begin_typedef
DECL|typedef|HistogramToolDialog
typedef|typedef
name|struct
name|_HistogramToolDialog
name|HistogramToolDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_HistogramToolDialog
struct|struct
name|_HistogramToolDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|info_labels
name|GtkWidget
modifier|*
name|info_labels
index|[
literal|7
index|]
decl_stmt|;
DECL|member|channel_menu
name|GtkWidget
modifier|*
name|channel_menu
decl_stmt|;
DECL|member|histogram
name|HistogramWidget
modifier|*
name|histogram
decl_stmt|;
DECL|member|hist
name|GimpHistogram
modifier|*
name|hist
decl_stmt|;
DECL|member|mean
name|gdouble
name|mean
decl_stmt|;
DECL|member|std_dev
name|gdouble
name|std_dev
decl_stmt|;
DECL|member|median
name|gdouble
name|median
decl_stmt|;
DECL|member|pixels
name|gdouble
name|pixels
decl_stmt|;
DECL|member|count
name|gdouble
name|count
decl_stmt|;
DECL|member|percentile
name|gdouble
name|percentile
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
name|image_map
decl_stmt|;
DECL|member|channel
name|gint
name|channel
decl_stmt|;
DECL|member|color
name|gint
name|color
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  histogram_tool functions  */
end_comment

begin_function_decl
name|Tool
modifier|*
name|tools_new_histogram_tool
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_histogram_tool
parameter_list|(
name|Tool
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_tool_initialize
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_tool_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_tool_histogram_range
parameter_list|(
name|HistogramWidget
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __HISTOGRAM_TOOL_H__ */
end_comment

end_unit

