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

begin_function_decl
name|GimpHistogram
modifier|*
name|gimp_histogram_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpHistogram
modifier|*
name|gimp_histogram_ref
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_unref
parameter_list|(
name|GimpHistogram
modifier|*
name|histogram
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
name|gint
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
name|gimp_histogram_get_channel
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
name|gint
name|gimp_histogram_n_channels
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

