begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HISTOGRAM_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HISTOGRAM_OPTIONS_H__
define|#
directive|define
name|__GIMP_HISTOGRAM_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimpcoloroptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM_OPTIONS
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM_OPTIONS
value|(gimp_histogram_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_OPTIONS (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HISTOGRAM_OPTIONS, GimpHistogramOptions))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_HISTOGRAM_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HISTOGRAM_OPTIONS, GimpHistogramOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HISTOGRAM_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HISTOGRAM_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HISTOGRAM_OPTIONS, GimpHistogramOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpHistogramOptions
typedef|typedef
name|struct
name|_GimpHistogramOptions
name|GimpHistogramOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHistogramOptionsClass
typedef|typedef
name|GimpColorOptionsClass
name|GimpHistogramOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHistogramOptions
struct|struct
name|_GimpHistogramOptions
block|{
DECL|member|parent_instance
name|GimpColorOptions
name|parent_instance
decl_stmt|;
DECL|member|scale
name|GimpHistogramScale
name|scale
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_histogram_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_histogram_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_histogram_options_connect_view
parameter_list|(
name|GimpHistogramOptions
modifier|*
name|options
parameter_list|,
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HISTOGRAM_OPTIONS_H__ */
end_comment

end_unit

