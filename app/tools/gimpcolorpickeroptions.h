begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_PICKER_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_PICKER_OPTIONS_H__
define|#
directive|define
name|__GIMP_COLOR_PICKER_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_PICKER_OPTIONS
define|#
directive|define
name|GIMP_TYPE_COLOR_PICKER_OPTIONS
value|(gimp_color_picker_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER_OPTIONS (obj)
define|#
directive|define
name|GIMP_COLOR_PICKER_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_PICKER_OPTIONS, GimpColorPickerOptions))
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_PICKER_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_PICKER_OPTIONS, GimpColorPickerOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PICKER_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_COLOR_PICKER_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_PICKER_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PICKER_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_PICKER_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_PICKER_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_PICKER_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_PICKER_OPTIONS, GimpColorPickerOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpColorPickerOptions
typedef|typedef
name|struct
name|_GimpColorPickerOptions
name|GimpColorPickerOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorPickerOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpColorPickerOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorPickerOptions
struct|struct
name|_GimpColorPickerOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
DECL|member|sample_merged
name|gboolean
name|sample_merged
decl_stmt|;
DECL|member|sample_merged_d
name|gboolean
name|sample_merged_d
decl_stmt|;
DECL|member|sample_merged_w
name|GtkWidget
modifier|*
name|sample_merged_w
decl_stmt|;
DECL|member|sample_average
name|gboolean
name|sample_average
decl_stmt|;
DECL|member|sample_average_d
name|gboolean
name|sample_average_d
decl_stmt|;
DECL|member|sample_average_w
name|GtkWidget
modifier|*
name|sample_average_w
decl_stmt|;
DECL|member|average_radius
name|gdouble
name|average_radius
decl_stmt|;
DECL|member|average_radius_d
name|gdouble
name|average_radius_d
decl_stmt|;
DECL|member|average_radius_w
name|GtkObject
modifier|*
name|average_radius_w
decl_stmt|;
DECL|member|update_active
name|gboolean
name|update_active
decl_stmt|;
DECL|member|update_active_d
name|gboolean
name|update_active_d
decl_stmt|;
DECL|member|update_active_w
name|GtkWidget
modifier|*
name|update_active_w
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_picker_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_color_picker_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COLOR_PICKER_OPTIONS_H__  */
end_comment

end_unit

