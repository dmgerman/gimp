begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAW_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAW_TOOL_H__
define|#
directive|define
name|__GIMP_DRAW_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_comment
comment|/*  draw states  */
end_comment

begin_define
DECL|macro|INVISIBLE
define|#
directive|define
name|INVISIBLE
value|0
end_define

begin_define
DECL|macro|VISIBLE
define|#
directive|define
name|VISIBLE
value|1
end_define

begin_define
DECL|macro|GIMP_TYPE_DRAW_TOOL
define|#
directive|define
name|GIMP_TYPE_DRAW_TOOL
value|(gimp_draw_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAW_TOOL (obj)
define|#
directive|define
name|GIMP_DRAW_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DRAW_TOOL, GimpDrawTool))
end_define

begin_define
DECL|macro|GIMP_IS_DRAW_TOOL (obj)
define|#
directive|define
name|GIMP_IS_DRAW_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DRAW_TOOL))
end_define

begin_define
DECL|macro|GIMP_DRAW_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_DRAW_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAW_TOOL, GimpDrawToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAW_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAW_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAW_TOOL))
end_define

begin_typedef
DECL|typedef|GimpDrawToolClass
typedef|typedef
name|struct
name|_GimpDrawToolClass
name|GimpDrawToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawTool
struct|struct
name|_GimpDrawTool
block|{
DECL|member|parent_instance
name|GimpTool
name|parent_instance
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
comment|/*  Graphics context for draw functions  */
DECL|member|win
name|GdkWindow
modifier|*
name|win
decl_stmt|;
comment|/*  Window to draw draw operation to      */
DECL|member|draw_state
name|gint
name|draw_state
decl_stmt|;
comment|/*  Current state in the draw process    */
DECL|member|line_width
name|gint
name|line_width
decl_stmt|;
comment|/**/
DECL|member|line_style
name|gint
name|line_style
decl_stmt|;
comment|/**/
DECL|member|cap_style
name|gint
name|cap_style
decl_stmt|;
comment|/*  line attributes                         */
DECL|member|join_style
name|gint
name|join_style
decl_stmt|;
comment|/**/
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
comment|/*  count to keep track of multiple pauses  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawToolClass
struct|struct
name|_GimpDrawToolClass
block|{
DECL|member|parent_class
name|GimpToolClass
name|parent_class
decl_stmt|;
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_draw_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_start
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_stop
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_pause
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_draw_tool_resume
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAW_TOOL_H__  */
end_comment

end_unit

