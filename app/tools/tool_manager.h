begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOL_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__TOOL_MANAGER_H__
define|#
directive|define
name|__TOOL_MANAGER_H__
end_define

begin_include
include|#
directive|include
file|"tool.h"
end_include

begin_comment
comment|/* EEEEEEEEEEK */
end_comment

begin_comment
comment|/*  Function declarations  */
end_comment

begin_function_decl
name|void
name|tool_manager_select_tool
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_manager_initialize_tool
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_manager_control_active
parameter_list|(
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_manager_register
parameter_list|(
name|GimpToolClass
modifier|*
name|tool_type
comment|/*, ToolOptions *tool_options*/
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_manager_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_manager_register_tool
parameter_list|(
name|GtkType
name|tool_type
parameter_list|,
name|gboolean
name|tool_context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_accel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|icon_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_manager_register_tool_options
parameter_list|(
name|GtkType
name|tool_type
parameter_list|,
name|ToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolInfo
modifier|*
name|tool_manager_get_info_by_type
parameter_list|(
name|GtkType
name|tool_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolInfo
modifier|*
name|tool_manager_get_info_by_tool
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|tool_manager_active_get_PDB_string
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|tool_manager_active_get_help_data
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_manager_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Global Data Structures  */
end_comment

begin_decl_stmt
specifier|extern
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpContainer
modifier|*
name|global_tool_info_list
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TOOL_MANAGER_H__  */
end_comment

end_unit

