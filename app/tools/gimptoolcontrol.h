begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpobject.h"
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

begin_typedef
DECL|typedef|GimpToolControlClass
typedef|typedef
name|struct
name|_GimpToolControlClass
name|GimpToolControlClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolControl
struct|struct
name|_GimpToolControl
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|active
name|gboolean
name|active
decl_stmt|;
comment|/*  state of tool activity               */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
comment|/*  paused control count                 */
DECL|member|scroll_lock
name|gboolean
name|scroll_lock
decl_stmt|;
comment|/*  allow scrolling or not               */
DECL|member|auto_snap_to
name|gboolean
name|auto_snap_to
decl_stmt|;
comment|/*  snap to guides automatically         */
DECL|member|snap_offset_x
name|gint
name|snap_offset_x
decl_stmt|;
DECL|member|snap_offset_y
name|gint
name|snap_offset_y
decl_stmt|;
DECL|member|snap_width
name|gint
name|snap_width
decl_stmt|;
DECL|member|snap_height
name|gint
name|snap_height
decl_stmt|;
DECL|member|preserve
name|gboolean
name|preserve
decl_stmt|;
comment|/*  Preserve this tool across drawable   *                                       *  changes                              */
DECL|member|handle_empty_image
name|gboolean
name|handle_empty_image
decl_stmt|;
comment|/*  invoke the tool on images without    *                                       *  active drawable                      */
DECL|member|motion_mode
name|GimpMotionMode
name|motion_mode
decl_stmt|;
comment|/*  how to process motion events before  *                                       *  they are forwarded to the tool       */
DECL|member|cursor
name|GimpCursorType
name|cursor
decl_stmt|;
DECL|member|tool_cursor
name|GimpToolCursorType
name|tool_cursor
decl_stmt|;
DECL|member|cursor_modifier
name|GimpCursorModifier
name|cursor_modifier
decl_stmt|;
DECL|member|toggle_cursor
name|GimpCursorType
name|toggle_cursor
decl_stmt|;
DECL|member|toggle_tool_cursor
name|GimpToolCursorType
name|toggle_tool_cursor
decl_stmt|;
DECL|member|toggle_cursor_modifier
name|GimpCursorModifier
name|toggle_cursor_modifier
decl_stmt|;
DECL|member|toggled
name|gboolean
name|toggled
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolControlClass
struct|struct
name|_GimpToolControlClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_control_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

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
name|gboolean
name|gimp_tool_control_is_toggled
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
name|gboolean
name|gimp_tool_control_preserve
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
name|gboolean
name|gimp_tool_control_scroll_lock
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_motion_mode
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpMotionMode
name|motion_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMotionMode
name|gimp_tool_control_motion_mode
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_handles_empty_image
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|handle_empty
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_handles_empty_image
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_snap_to
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|snap_to
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_auto_snap_to
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_snap_offsets
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_snap_offsets
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gint
modifier|*
name|offset_x
parameter_list|,
name|gint
modifier|*
name|offset_y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCursorType
name|gimp_tool_control_get_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
name|GimpCursorType
name|cursor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolCursorType
name|gimp_tool_control_get_tool_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
name|GimpCursorModifier
name|gimp_tool_control_get_cursor_modifier
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
name|GimpCursorType
name|gimp_tool_control_get_toggle_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
name|GimpCursorType
name|cursor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolCursorType
name|gimp_tool_control_get_toggle_tool_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
name|GimpCursorModifier
name|gimp_tool_control_get_toggle_cursor_modifier
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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
comment|/* __GIMP_TOOL_CONTROL_H__ */
end_comment

end_unit

