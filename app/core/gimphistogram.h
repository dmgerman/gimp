begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphistogram module Copyright (C) 1999 Jay Cox<jaycox@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HISTOGRAM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HISTOGRAM_H__
define|#
directive|define
name|__GIMP_HISTOGRAM_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM
value|(gimp_histogram_get_type ())
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM (obj)
define|#
directive|define
name|GIMP_HISTOGRAM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HISTOGRAM, GimpHistogram))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_CLASS (klass)
define|#
directive|define
name|GIMP_HISTOGRAM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HISTOGRAM, GimpHistogramClass))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM (obj)
define|#
directive|define
name|GIMP_IS_HISTOGRAM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HISTOGRAM))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HISTOGRAM))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HISTOGRAM, GimpHistogramClass))
end_define

begin_typedef
DECL|typedef|GimpHistogramPrivate
typedef|typedef
name|struct
name|_GimpHistogramPrivate
name|GimpHistogramPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHistogramClass
typedef|typedef
name|struct
name|_GimpHistogramClass
name|GimpHistogramClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHistogram
struct|struct
name|_GimpHistogram
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpHistogramPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHistogramClass
struct|struct
name|_GimpHistogramClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_histogram_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpHistogram
modifier|*
name|gimp_histogram_new
parameter_list|(
name|gboolean
name|linear
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpHistogram
modifier|*
name|gimp_histogram_duplicate
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_calculate
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|buffer_rect
parameter_list|,
name|GeglBuffer
modifier|*
name|mask
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|mask_rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_clear_values
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_histogram_get_maximum
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_histogram_get_count
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
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
name|gdouble
name|gimp_histogram_get_mean
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
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
name|gdouble
name|gimp_histogram_get_median
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
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
name|gdouble
name|gimp_histogram_get_std_dev
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
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
name|gdouble
name|gimp_histogram_get_threshold
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
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
name|gdouble
name|gimp_histogram_get_value
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
name|gint
name|bin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_histogram_get_component
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|gint
name|component
parameter_list|,
name|gint
name|bin
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_histogram_n_channels
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_histogram_n_bins
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HISTOGRAM_H__ */
end_comment

end_unit

