begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextTool  * Copyright (C) 2002-2010  Sven Neumann<sven@gimp.org>  *                          Daniel Eddeland<danedde@svn.gnome.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_TOOL_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_TOOL_EDITOR_H__
define|#
directive|define
name|__GIMP_TEXT_TOOL_EDITOR_H__
end_define

begin_function_decl
name|void
name|gimp_text_tool_editor_init
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_editor_finalize
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_editor_start
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_tool_editor_halt
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_tool_editor_key_press
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_text_tool_editor_key_release
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_text_tool_editor_get_text
parameter_list|(
name|GimpTextTool
modifier|*
name|text_tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_TOOL_EDITOR_H__ */
end_comment

end_unit

