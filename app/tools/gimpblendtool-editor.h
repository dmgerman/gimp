begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BLEND_TOOL_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BLEND_TOOL_EDITOR_H__
define|#
directive|define
name|__GIMP_BLEND_TOOL_EDITOR_H__
end_define

begin_function_decl
name|void
name|gimp_blend_tool_editor_options_notify
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_blend_tool_editor_start
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_blend_tool_editor_halt
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_blend_tool_editor_line_changed
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_blend_tool_editor_fg_bg_changed
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_blend_tool_editor_gradient_dirty
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_blend_tool_editor_gradient_changed
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_blend_tool_editor_can_undo
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_blend_tool_editor_can_redo
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_blend_tool_editor_undo
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_blend_tool_editor_redo
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_blend_tool_editor_start_edit
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_blend_tool_editor_end_edit
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|,
name|gboolean
name|cancel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BLEND_TOOL_EDITOR_H__  */
end_comment

end_unit

