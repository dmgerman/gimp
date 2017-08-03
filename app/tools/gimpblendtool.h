begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BLEND_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BLEND_TOOL_H__
define|#
directive|define
name|__GIMP_BLEND_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BLEND_TOOL
define|#
directive|define
name|GIMP_TYPE_BLEND_TOOL
value|(gimp_blend_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_BLEND_TOOL (obj)
define|#
directive|define
name|GIMP_BLEND_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BLEND_TOOL, GimpBlendTool))
end_define

begin_define
DECL|macro|GIMP_BLEND_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_BLEND_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BLEND_TOOL, GimpBlendToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_BLEND_TOOL (obj)
define|#
directive|define
name|GIMP_IS_BLEND_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BLEND_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_BLEND_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BLEND_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BLEND_TOOL))
end_define

begin_define
DECL|macro|GIMP_BLEND_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BLEND_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BLEND_TOOL, GimpBlendToolClass))
end_define

begin_define
DECL|macro|GIMP_BLEND_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_BLEND_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_BLEND_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpBlendTool
typedef|typedef
name|struct
name|_GimpBlendTool
name|GimpBlendTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBlendToolClass
typedef|typedef
name|struct
name|_GimpBlendToolClass
name|GimpBlendToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBlendTool
struct|struct
name|_GimpBlendTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|gradient
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
DECL|member|tentative_gradient
name|GimpGradient
modifier|*
name|tentative_gradient
decl_stmt|;
DECL|member|start_x
name|gdouble
name|start_x
decl_stmt|;
comment|/*  starting x coord  */
DECL|member|start_y
name|gdouble
name|start_y
decl_stmt|;
comment|/*  starting y coord  */
DECL|member|end_x
name|gdouble
name|end_x
decl_stmt|;
comment|/*  ending x coord    */
DECL|member|end_y
name|gdouble
name|end_y
decl_stmt|;
comment|/*  ending y coord    */
DECL|member|undo_stack
name|GList
modifier|*
name|undo_stack
decl_stmt|;
DECL|member|redo_stack
name|GList
modifier|*
name|redo_stack
decl_stmt|;
DECL|member|widget
name|GimpToolWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|grab_widget
name|GimpToolWidget
modifier|*
name|grab_widget
decl_stmt|;
DECL|member|graph
name|GeglNode
modifier|*
name|graph
decl_stmt|;
DECL|member|render_node
name|GeglNode
modifier|*
name|render_node
decl_stmt|;
if|#
directive|if
literal|0
block|GeglNode           *subtract_node;   GeglNode           *divide_node;
endif|#
directive|endif
DECL|member|dist_node
name|GeglNode
modifier|*
name|dist_node
decl_stmt|;
DECL|member|dist_buffer
name|GeglBuffer
modifier|*
name|dist_buffer
decl_stmt|;
DECL|member|filter
name|GimpDrawableFilter
modifier|*
name|filter
decl_stmt|;
comment|/*  editor  */
DECL|member|block_handlers_count
name|gint
name|block_handlers_count
decl_stmt|;
DECL|member|gui
name|GimpToolGui
modifier|*
name|gui
decl_stmt|;
DECL|member|endpoint_editor
name|GtkWidget
modifier|*
name|endpoint_editor
decl_stmt|;
DECL|member|endpoint_se
name|GtkWidget
modifier|*
name|endpoint_se
decl_stmt|;
DECL|member|endpoint_color_panel
name|GtkWidget
modifier|*
name|endpoint_color_panel
decl_stmt|;
DECL|member|endpoint_type_combo
name|GtkWidget
modifier|*
name|endpoint_type_combo
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBlendToolClass
struct|struct
name|_GimpBlendToolClass
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
name|gimp_blend_tool_register
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
name|gimp_blend_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  protected functions  */
end_comment

begin_function_decl
name|void
name|gimp_blend_tool_set_tentative_gradient
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BLEND_TOOL_H__  */
end_comment

end_unit

