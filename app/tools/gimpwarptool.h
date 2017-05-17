begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpwarptool.h  * Copyright (C) 2011 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WARP_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WARP_TOOL_H__
define|#
directive|define
name|__GIMP_WARP_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_WARP_TOOL
define|#
directive|define
name|GIMP_TYPE_WARP_TOOL
value|(gimp_warp_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_WARP_TOOL (obj)
define|#
directive|define
name|GIMP_WARP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_WARP_TOOL, GimpWarpTool))
end_define

begin_define
DECL|macro|GIMP_WARP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_WARP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_WARP_TOOL, GimpWarpToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_WARP_TOOL (obj)
define|#
directive|define
name|GIMP_IS_WARP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_WARP_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_WARP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_WARP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_WARP_TOOL))
end_define

begin_define
DECL|macro|GIMP_WARP_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_WARP_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_WARP_TOOL, GimpWarpToolClass))
end_define

begin_define
DECL|macro|GIMP_WARP_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_WARP_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_WARP_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpWarpTool
typedef|typedef
name|struct
name|_GimpWarpTool
name|GimpWarpTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpWarpToolClass
typedef|typedef
name|struct
name|_GimpWarpToolClass
name|GimpWarpToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpWarpTool
struct|struct
name|_GimpWarpTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|cursor_x
name|gdouble
name|cursor_x
decl_stmt|;
comment|/* Hold the cursor x position */
DECL|member|cursor_y
name|gdouble
name|cursor_y
decl_stmt|;
comment|/* Hold the cursor y position */
DECL|member|cursor_moved
name|gboolean
name|cursor_moved
decl_stmt|;
comment|/* Did the cursor move since the last stroke? */
DECL|member|coords_buffer
name|GeglBuffer
modifier|*
name|coords_buffer
decl_stmt|;
comment|/* Buffer where coordinates are stored */
DECL|member|graph
name|GeglNode
modifier|*
name|graph
decl_stmt|;
comment|/* Top level GeglNode */
DECL|member|render_node
name|GeglNode
modifier|*
name|render_node
decl_stmt|;
comment|/* Node to render the transformation */
DECL|member|current_stroke
name|GeglPath
modifier|*
name|current_stroke
decl_stmt|;
DECL|member|stroke_timer
name|guint
name|stroke_timer
decl_stmt|;
DECL|member|filter
name|GimpDrawableFilter
modifier|*
name|filter
decl_stmt|;
DECL|member|redo_stack
name|GList
modifier|*
name|redo_stack
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpWarpToolClass
struct|struct
name|_GimpWarpToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_warp_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_warp_tool_get_type
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
comment|/*  __GIMP_WARP_TOOL_H__  */
end_comment

end_unit

