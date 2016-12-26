begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SAMPLE_POINT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SAMPLE_POINT_TOOL_H__
define|#
directive|define
name|__GIMP_SAMPLE_POINT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SAMPLE_POINT_TOOL
define|#
directive|define
name|GIMP_TYPE_SAMPLE_POINT_TOOL
value|(gimp_sample_point_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_SAMPLE_POINT_TOOL (obj)
define|#
directive|define
name|GIMP_SAMPLE_POINT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SAMPLE_POINT_TOOL, GimpSamplePointTool))
end_define

begin_define
DECL|macro|GIMP_SAMPLE_POINT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_SAMPLE_POINT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SAMPLE_POINT_TOOL, GimpSamplePointToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_SAMPLE_POINT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_SAMPLE_POINT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SAMPLE_POINT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_SAMPLE_POINT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SAMPLE_POINT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SAMPLE_POINT_TOOL))
end_define

begin_define
DECL|macro|GIMP_SAMPLE_POINT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SAMPLE_POINT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SAMPLE_POINT_TOOL, GimpSamplePointToolClass))
end_define

begin_typedef
DECL|typedef|GimpSamplePointTool
typedef|typedef
name|struct
name|_GimpSamplePointTool
name|GimpSamplePointTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSamplePointToolClass
typedef|typedef
name|struct
name|_GimpSamplePointToolClass
name|GimpSamplePointToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSamplePointTool
struct|struct
name|_GimpSamplePointTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|sample_point
name|GimpSamplePoint
modifier|*
name|sample_point
decl_stmt|;
DECL|member|sample_point_old_x
name|gint
name|sample_point_old_x
decl_stmt|;
DECL|member|sample_point_old_y
name|gint
name|sample_point_old_y
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
DECL|struct|_GimpSamplePointToolClass
struct|struct
name|_GimpSamplePointToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_sample_point_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_sample_point_tool_start_new
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_sample_point_tool_start_edit
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SAMPLE_POINT_TOOL_H__  */
end_comment

end_unit

