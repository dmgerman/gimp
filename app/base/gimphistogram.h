begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphistogram module Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
name|GimpBaseConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_free
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
name|historgam
parameter_list|,
name|PixelRegion
modifier|*
name|region
parameter_list|,
name|PixelRegion
modifier|*
name|mask
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
name|gimp_histogram_nchannels
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

