begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * Brush selection tool by Nathan Summers  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_BRUSH_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_comment
comment|/* GTypeModules use a static variable instead of a function call to get the GType.  See http://www.gtk.org/~otaylor/gtk/2.0/theme-engines.html for the rationale. */
end_comment

begin_decl_stmt
specifier|extern
name|GType
name|gimp_type_brush_select_tool
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_TYPE_BRUSH_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_BRUSH_SELECT_TOOL
value|gimp_type_brush_select_tool
end_define

begin_define
DECL|macro|GIMP_BRUSH_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_BRUSH_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BRUSH_SELECT_TOOL, GimpBrushSelectTool))
end_define

begin_define
DECL|macro|GIMP_BRUSH_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH_SELECT_TOOL, GimpBrushSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BRUSH_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_BRUSH_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BRUSH_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BRUSH_SELECT_TOOL, GimpBrushSelectToolClass))
end_define

begin_typedef
DECL|typedef|GimpBrushSelectTool
typedef|typedef
name|struct
name|_GimpBrushSelectTool
name|GimpBrushSelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBrushSelectToolClass
typedef|typedef
name|struct
name|_GimpBrushSelectToolClass
name|GimpBrushSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushSelectTool
struct|struct
name|_GimpBrushSelectTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|points
name|GimpVector2
modifier|*
name|points
decl_stmt|;
DECL|member|num_points
name|gint
name|num_points
decl_stmt|;
DECL|member|max_segs
name|gint
name|max_segs
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushSelectToolClass
struct|struct
name|_GimpBrushSelectToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_brush_select_tool_register
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

begin_function_decl
name|GType
name|gimp_brush_select_tool_get_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BRUSH_SELECT_TOOL_H__  */
end_comment

end_unit

