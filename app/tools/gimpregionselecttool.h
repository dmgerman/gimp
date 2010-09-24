begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpregionselecttool.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_REGION_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_REGION_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_REGION_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_REGION_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_REGION_SELECT_TOOL
value|(gimp_region_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_REGION_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_REGION_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_REGION_SELECT_TOOL, GimpRegionSelectTool))
end_define

begin_define
DECL|macro|GIMP_REGION_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_REGION_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_REGION_SELECT_TOOL, GimpRegionSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_REGION_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_REGION_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_REGION_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_REGION_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_REGION_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_REGION_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_REGION_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_REGION_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_REGION_SELECT_TOOL, GimpRegionSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_REGION_SELECT_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_REGION_SELECT_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_REGION_SELECT_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpRegionSelectTool
typedef|typedef
name|struct
name|_GimpRegionSelectTool
name|GimpRegionSelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRegionSelectToolClass
typedef|typedef
name|struct
name|_GimpRegionSelectToolClass
name|GimpRegionSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRegionSelectTool
struct|struct
name|_GimpRegionSelectTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
DECL|member|saved_threshold
name|gdouble
name|saved_threshold
decl_stmt|;
DECL|member|region_mask
name|GimpChannel
modifier|*
name|region_mask
decl_stmt|;
DECL|member|segs
name|BoundSeg
modifier|*
name|segs
decl_stmt|;
DECL|member|n_segs
name|gint
name|n_segs
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpRegionSelectToolClass
struct|struct
name|_GimpRegionSelectToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
DECL|member|undo_desc
specifier|const
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
DECL|member|get_mask
name|GimpChannel
modifier|*
function_decl|(
modifier|*
name|get_mask
function_decl|)
parameter_list|(
name|GimpRegionSelectTool
modifier|*
name|region_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_region_select_tool_get_type
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
comment|/* __GIMP_REGION_SELECT_TOOL_H__ */
end_comment

end_unit

