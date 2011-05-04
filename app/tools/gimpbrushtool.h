begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_TOOL_H__
define|#
directive|define
name|__GIMP_BRUSH_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimppainttool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BRUSH_TOOL
define|#
directive|define
name|GIMP_TYPE_BRUSH_TOOL
value|(gimp_brush_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_BRUSH_TOOL (obj)
define|#
directive|define
name|GIMP_BRUSH_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BRUSH_TOOL, GimpBrushTool))
end_define

begin_define
DECL|macro|GIMP_BRUSH_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH_TOOL, GimpBrushToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_TOOL (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BRUSH_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_BRUSH_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH_TOOL))
end_define

begin_define
DECL|macro|GIMP_BRUSH_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BRUSH_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BRUSH_TOOL, GimpBrushToolClass))
end_define

begin_typedef
DECL|typedef|GimpBrushToolClass
typedef|typedef
name|struct
name|_GimpBrushToolClass
name|GimpBrushToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBrushTool
struct|struct
name|_GimpBrushTool
block|{
DECL|member|parent_instance
name|GimpPaintTool
name|parent_instance
decl_stmt|;
DECL|member|show_cursor
name|gboolean
name|show_cursor
decl_stmt|;
DECL|member|draw_brush
name|gboolean
name|draw_brush
decl_stmt|;
DECL|member|brush_x
name|gdouble
name|brush_x
decl_stmt|;
DECL|member|brush_y
name|gdouble
name|brush_y
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushToolClass
struct|struct
name|_GimpBrushToolClass
block|{
DECL|member|parent_class
name|GimpPaintToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_brush_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_brush_tool_create_outline
parameter_list|(
name|GimpBrushTool
modifier|*
name|brush_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gboolean
name|draw_fallback
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BRUSH_TOOL_H__  */
end_comment

end_unit

