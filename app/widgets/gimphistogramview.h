begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__HISTOGRAM_WIDGET_H__
end_ifndef

begin_define
DECL|macro|__HISTOGRAM_WIDGET_H__
define|#
directive|define
name|__HISTOGRAM_WIDGET_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdrawingarea.h>
end_include

begin_include
include|#
directive|include
file|"gimphistogram.h"
end_include

begin_define
DECL|macro|HISTOGRAM_WIDGET_TYPE
define|#
directive|define
name|HISTOGRAM_WIDGET_TYPE
value|(histogram_widget_get_type ())
end_define

begin_define
DECL|macro|HISTOGRAM_WIDGET (obj)
define|#
directive|define
name|HISTOGRAM_WIDGET
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, histogram_widget_get_type (), HistogramWidget)
end_define

begin_define
DECL|macro|HISTOGRAM_WIDGET_CLASS (klass)
define|#
directive|define
name|HISTOGRAM_WIDGET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, histogram_widget_get_type (), HistogramWidget)
end_define

begin_define
DECL|macro|IS_HISTOGRAM_WIDGET (obj)
define|#
directive|define
name|IS_HISTOGRAM_WIDGET
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, histogram_widget_get_type ())
end_define

begin_typedef
DECL|typedef|HistogramWidget
typedef|typedef
name|struct
name|_HistogramWidget
name|HistogramWidget
typedef|;
end_typedef

begin_typedef
DECL|typedef|HistogramWidgetClass
typedef|typedef
name|struct
name|_HistogramWidgetClass
name|HistogramWidgetClass
typedef|;
end_typedef

begin_comment
comment|/* HistogramWidget signals:      range_changed */
end_comment

begin_struct
DECL|struct|_HistogramWidget
struct|struct
name|_HistogramWidget
block|{
DECL|member|drawingarea
name|GtkDrawingArea
name|drawingarea
decl_stmt|;
DECL|member|histogram
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
DECL|member|channel
name|GimpHistogramChannel
name|channel
decl_stmt|;
DECL|member|start
name|gint
name|start
decl_stmt|;
DECL|member|end
name|gint
name|end
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_HistogramWidgetClass
struct|struct
name|_HistogramWidgetClass
block|{
DECL|member|parent_class
name|GtkDrawingAreaClass
name|parent_class
decl_stmt|;
DECL|member|range_changed
name|void
function_decl|(
modifier|*
name|range_changed
function_decl|)
parameter_list|(
name|HistogramWidget
modifier|*
name|hw
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Histogram functions  */
end_comment

begin_function_decl
name|GtkType
name|histogram_widget_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|HistogramWidget
modifier|*
name|histogram_widget_new
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_widget_update
parameter_list|(
name|HistogramWidget
modifier|*
name|hw
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_widget_range
parameter_list|(
name|HistogramWidget
modifier|*
name|hw
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|histogram_widget_channel
parameter_list|(
name|HistogramWidget
modifier|*
name|hw
parameter_list|,
name|gint
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpHistogram
modifier|*
name|histogram_widget_histogram
parameter_list|(
name|HistogramWidget
modifier|*
name|hw
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __HISTOGRAM_WIDGET_H__ */
end_comment

end_unit

