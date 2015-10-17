begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_TOOL_H__
define|#
directive|define
name|__GIMP_PAINT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpcolortool.h"
end_include

begin_define
DECL|macro|GIMP_PAINT_TOOL_LINE_MASK
define|#
directive|define
name|GIMP_PAINT_TOOL_LINE_MASK
value|(gimp_get_extend_selection_mask ())
end_define

begin_define
DECL|macro|GIMP_TYPE_PAINT_TOOL
define|#
directive|define
name|GIMP_TYPE_PAINT_TOOL
value|(gimp_paint_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_PAINT_TOOL (obj)
define|#
directive|define
name|GIMP_PAINT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PAINT_TOOL, GimpPaintTool))
end_define

begin_define
DECL|macro|GIMP_PAINT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_PAINT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PAINT_TOOL, GimpPaintToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_PAINT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PAINT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PAINT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PAINT_TOOL))
end_define

begin_define
DECL|macro|GIMP_PAINT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PAINT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PAINT_TOOL, GimpPaintToolClass))
end_define

begin_define
DECL|macro|GIMP_PAINT_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_PAINT_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_PAINT_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpPaintToolClass
typedef|typedef
name|struct
name|_GimpPaintToolClass
name|GimpPaintToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaintTool
struct|struct
name|_GimpPaintTool
block|{
DECL|member|parent_instance
name|GimpColorTool
name|parent_instance
decl_stmt|;
DECL|member|pick_colors
name|gboolean
name|pick_colors
decl_stmt|;
comment|/*  pick color if ctrl is pressed   */
DECL|member|draw_line
name|gboolean
name|draw_line
decl_stmt|;
DECL|member|show_cursor
name|gboolean
name|show_cursor
decl_stmt|;
DECL|member|draw_brush
name|gboolean
name|draw_brush
decl_stmt|;
DECL|member|draw_fallback
name|gboolean
name|draw_fallback
decl_stmt|;
DECL|member|fallback_size
name|gint
name|fallback_size
decl_stmt|;
DECL|member|draw_circle
name|gboolean
name|draw_circle
decl_stmt|;
DECL|member|circle_size
name|gint
name|circle_size
decl_stmt|;
DECL|member|status
specifier|const
name|gchar
modifier|*
name|status
decl_stmt|;
comment|/* status message */
DECL|member|status_line
specifier|const
name|gchar
modifier|*
name|status_line
decl_stmt|;
comment|/* status message when drawing a line */
DECL|member|status_ctrl
specifier|const
name|gchar
modifier|*
name|status_ctrl
decl_stmt|;
comment|/* additional message for the ctrl modifier */
DECL|member|core
name|GimpPaintCore
modifier|*
name|core
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaintToolClass
struct|struct
name|_GimpPaintToolClass
block|{
DECL|member|parent_class
name|GimpColorToolClass
name|parent_class
decl_stmt|;
DECL|member|get_outline
name|GimpCanvasItem
modifier|*
function_decl|(
modifier|*
name|get_outline
function_decl|)
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
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
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_paint_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_paint_tool_enable_color_picker
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|GimpColorPickMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_set_draw_fallback
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|gboolean
name|draw_fallback
parameter_list|,
name|gint
name|fallback_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_tool_set_draw_circle
parameter_list|(
name|GimpPaintTool
modifier|*
name|tool
parameter_list|,
name|gboolean
name|draw_circle
parameter_list|,
name|gint
name|circle_size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PAINT_TOOL_H__  */
end_comment

end_unit

