begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GUIDE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GUIDE_TOOL_H__
define|#
directive|define
name|__GIMP_GUIDE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_GUIDE_TOOL
define|#
directive|define
name|GIMP_TYPE_GUIDE_TOOL
value|(gimp_guide_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_GUIDE_TOOL (obj)
define|#
directive|define
name|GIMP_GUIDE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GUIDE_TOOL, GimpGuideTool))
end_define

begin_define
DECL|macro|GIMP_GUIDE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_GUIDE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GUIDE_TOOL, GimpGuideToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_GUIDE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_GUIDE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GUIDE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_GUIDE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GUIDE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GUIDE_TOOL))
end_define

begin_define
DECL|macro|GIMP_GUIDE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_GUIDE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_GUIDE_TOOL, GimpGuideToolClass))
end_define

begin_typedef
DECL|typedef|GimpGuideTool
typedef|typedef
name|struct
name|_GimpGuideTool
name|GimpGuideTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGuideToolClass
typedef|typedef
name|struct
name|_GimpGuideToolClass
name|GimpGuideToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGuideTool
struct|struct
name|_GimpGuideTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|guide
name|GimpGuide
modifier|*
name|guide
decl_stmt|;
DECL|member|guide_position
name|gint
name|guide_position
decl_stmt|;
DECL|member|guide_orientation
name|GimpOrientationType
name|guide_orientation
decl_stmt|;
comment|/* for live-moving custom guides */
DECL|member|guide_custom
name|gboolean
name|guide_custom
decl_stmt|;
DECL|member|guide_old_position
name|gint
name|guide_old_position
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpGuideToolClass
struct|struct
name|_GimpGuideToolClass
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
name|gimp_guide_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_guide_tool_start_new
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_guide_tool_start_edit
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_GUIDE_TOOL_H__  */
end_comment

end_unit

