begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_TOOL_H__
define|#
directive|define
name|__GIMP_COLOR_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_TOOL
define|#
directive|define
name|GIMP_TYPE_COLOR_TOOL
value|(gimp_color_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_TOOL (obj)
define|#
directive|define
name|GIMP_COLOR_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_TOOL, GimpColorTool))
end_define

begin_define
DECL|macro|GIMP_COLOR_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_TOOL, GimpColorToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_TOOL (obj)
define|#
directive|define
name|GIMP_IS_COLOR_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_TOOL))
end_define

begin_define
DECL|macro|GIMP_COLOR_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_TOOL, GimpColorToolClass))
end_define

begin_define
DECL|macro|GIMP_COLOR_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_COLOR_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_COLOR_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpColorToolClass
typedef|typedef
name|struct
name|_GimpColorToolClass
name|GimpColorToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorTool
struct|struct
name|_GimpColorTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|enabled
name|gboolean
name|enabled
decl_stmt|;
DECL|member|center_x
name|gint
name|center_x
decl_stmt|;
DECL|member|center_y
name|gint
name|center_y
decl_stmt|;
DECL|member|pick_mode
name|GimpColorPickMode
name|pick_mode
decl_stmt|;
DECL|member|options
name|GimpColorOptions
modifier|*
name|options
decl_stmt|;
DECL|member|sample_point
name|GimpSamplePoint
modifier|*
name|sample_point
decl_stmt|;
DECL|member|moving_sample_point
name|gboolean
name|moving_sample_point
decl_stmt|;
DECL|member|sample_point_x
name|gint
name|sample_point_x
decl_stmt|;
DECL|member|sample_point_y
name|gint
name|sample_point_y
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorToolClass
struct|struct
name|_GimpColorToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|pick
name|gboolean
function_decl|(
modifier|*
name|pick
function_decl|)
parameter_list|(
name|GimpColorTool
modifier|*
name|tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImageType
modifier|*
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|picked
name|void
function_decl|(
modifier|*
name|picked
function_decl|)
parameter_list|(
name|GimpColorTool
modifier|*
name|tool
parameter_list|,
name|GimpColorPickState
name|pick_state
parameter_list|,
name|GimpImageType
name|sample_type
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_color_tool_enable
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|GimpColorOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_tool_disable
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_tool_is_enabled
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_tool_start_sample_point
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COLOR_TOOL_H__  */
end_comment

end_unit

