begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_CONTROL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_CONTROL_H__
define|#
directive|define
name|__GIMP_TOOL_CONTROL_H__
end_define

begin_include
include|#
directive|include
file|"app/core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_CONTROL
define|#
directive|define
name|GIMP_TYPE_TOOL_CONTROL
value|(gimp_tool_control_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_CONTROL (obj)
define|#
directive|define
name|GIMP_TOOL_CONTROL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_CONTROL, GimpToolControl))
end_define

begin_define
DECL|macro|GIMP_TOOL_CONTROL_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_CONTROL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_CONTROL, GimpToolControlClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_CONTROL (obj)
define|#
directive|define
name|GIMP_IS_TOOL_CONTROL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_CONTROL))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_CONTROL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_CONTROL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_CONTROL))
end_define

begin_define
DECL|macro|GIMP_TOOL_CONTROL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_CONTROL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_CONTROL, GimpToolControlClass))
end_define

begin_function_decl
name|GimpToolControl
modifier|*
name|gimp_tool_control_new
parameter_list|(
name|gboolean
name|scroll_lock
parameter_list|,
name|gboolean
name|auto_snap_to
parameter_list|,
name|gboolean
name|preserve
parameter_list|,
name|gboolean
name|handle_empty_image
parameter_list|,
name|gboolean
name|perfectmouse
parameter_list|,
comment|/* are all these necessary? */
name|GdkCursorType
name|cursor
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|cursor_modifier
parameter_list|,
name|GdkCursorType
name|toggle_cursor
parameter_list|,
name|GimpToolCursorType
name|toggle_tool_cursor
parameter_list|,
name|GimpCursorModifier
name|toggle_cursor_modifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_pause
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_resume
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_is_paused
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_activate
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_halt
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_is_active
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_toggle
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|toggled
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_preserve
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|preserve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_scroll_lock
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|scroll_lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GdkCursorType
name|cursor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_tool_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpToolCursorType
name|cursor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_cursor_modifier
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorModifier
name|cmodifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_toggle_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GdkCursorType
name|cursor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_toggle_tool_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpToolCursorType
name|cursor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_toggle_cursor_modifier
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorModifier
name|cmodifier
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TOOL_CONTROL_H__  */
end_comment

end_unit

