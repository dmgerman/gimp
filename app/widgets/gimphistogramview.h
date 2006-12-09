begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HISTOGRAM_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HISTOGRAM_VIEW_H__
define|#
directive|define
name|__GIMP_HISTOGRAM_VIEW_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdrawingarea.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM_VIEW
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM_VIEW
value|(gimp_histogram_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_VIEW (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HISTOGRAM_VIEW, GimpHistogramView))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_HISTOGRAM_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HISTOGRAM_VIEW, GimpHistogramViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_VIEW (obj)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HISTOGRAM_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HISTOGRAM_VIEW))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HISTOGRAM_VIEW, GimpHistogramView))
end_define

begin_typedef
DECL|typedef|GimpHistogramViewClass
typedef|typedef
name|struct
name|_GimpHistogramViewClass
name|GimpHistogramViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHistogramView
struct|struct
name|_GimpHistogramView
block|{
DECL|member|parent_instance
name|GtkDrawingArea
name|parent_instance
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
DECL|member|scale
name|GimpHistogramScale
name|scale
decl_stmt|;
DECL|member|start
name|gint
name|start
decl_stmt|;
DECL|member|end
name|gint
name|end
decl_stmt|;
DECL|member|border_width
name|gint
name|border_width
decl_stmt|;
DECL|member|subdivisions
name|gint
name|subdivisions
decl_stmt|;
comment|/* hack */
DECL|member|light_histogram
name|gboolean
name|light_histogram
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHistogramViewClass
struct|struct
name|_GimpHistogramViewClass
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
name|GimpHistogramView
modifier|*
name|view
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

begin_decl_stmt
name|GType
name|gimp_histogram_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_histogram_view_new
parameter_list|(
name|gboolean
name|range
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_view_set_histogram
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpHistogram
modifier|*
name|gimp_histogram_view_get_histogram
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_view_set_channel
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpHistogramChannel
name|gimp_histogram_view_get_channel
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_view_set_scale
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GimpHistogramScale
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpHistogramScale
name|gimp_histogram_view_get_scale
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_view_set_range
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
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
name|gimp_histogram_view_get_range
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|gint
modifier|*
name|start
parameter_list|,
name|gint
modifier|*
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HISTOGRAM_VIEW_H__ */
end_comment

end_unit

