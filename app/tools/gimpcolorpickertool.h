begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_PICKER_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_PICKER_TOOL_H__
define|#
directive|define
name|__GIMP_COLOR_PICKER_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_PICKER_TOOL
define|#
directive|define
name|GIMP_TYPE_COLOR_PICKER_TOOL
value|(gimp_color_picker_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER_TOOL (obj)
define|#
directive|define
name|GIMP_COLOR_PICKER_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_PICKER_TOOL, GimpColorPickerTool))
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_PICKER_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_PICKER_TOOL, GimpColorPickerToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PICKER_TOOL (obj)
define|#
directive|define
name|GIMP_IS_COLOR_PICKER_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_PICKER_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PICKER_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_PICKER_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_PICKER_TOOL))
end_define

begin_define
DECL|macro|GIMP_COLOR_PICKER_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_PICKER_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_PICKER_TOOL, GimpColorPickerToolClass))
end_define

begin_typedef
DECL|typedef|GimpColorPickerTool
typedef|typedef
name|struct
name|_GimpColorPickerTool
name|GimpColorPickerTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorPickerToolClass
typedef|typedef
name|struct
name|_GimpColorPickerToolClass
name|GimpColorPickerToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorPickerTool
struct|struct
name|_GimpColorPickerTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|centerx
name|gint
name|centerx
decl_stmt|;
comment|/*  starting x coord    */
DECL|member|centery
name|gint
name|centery
decl_stmt|;
comment|/*  starting y coord    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorPickerToolClass
struct|struct
name|_GimpColorPickerToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpColorPickerToolOptions
typedef|typedef
name|struct
name|_GimpColorPickerToolOptions
name|GimpColorPickerToolOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorPickerToolOptions
struct|struct
name|_GimpColorPickerToolOptions
block|{
DECL|member|tool_options
name|GimpToolOptions
name|tool_options
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

begin_function_decl
name|void
name|gimp_color_picker_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_color_picker_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COLOR_PICKER_TOOL_H__  */
end_comment

end_unit

