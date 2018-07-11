begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
comment|/*  state of tool activity          */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
comment|/*  paused control count            */
DECL|member|preserve
name|gboolean
name|preserve
decl_stmt|;
comment|/*  Preserve this tool across       *                                             *  drawable changes                */
DECL|member|preserve_stack
name|GSList
modifier|*
name|preserve_stack
decl_stmt|;
comment|/*  for push/pop preserve           */
DECL|member|scroll_lock
name|gboolean
name|scroll_lock
decl_stmt|;
comment|/*  allow scrolling or not          */
DECL|member|handle_empty_image
name|gboolean
name|handle_empty_image
decl_stmt|;
comment|/*  invoke the tool on images       *                                             *  without active drawable         */
DECL|member|dirty_mask
name|GimpDirtyMask
name|dirty_mask
decl_stmt|;
comment|/*  if preserve is FALSE, cancel    *                                             *  the tool on these events        */
DECL|member|motion_mode
name|GimpMotionMode
name|motion_mode
decl_stmt|;
comment|/*  how to process motion events    *                                             *  before they go to the tool      */
DECL|member|auto_snap_to
name|gboolean
name|auto_snap_to
decl_stmt|;
comment|/*  snap to guides automatically    */
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
DECL|member|precision
name|GimpCursorPrecision
name|precision
decl_stmt|;
DECL|member|wants_click
name|gboolean
name|wants_click
decl_stmt|;
comment|/*  wants click detection           */
DECL|member|wants_double_click
name|gboolean
name|wants_double_click
decl_stmt|;
DECL|member|wants_triple_click
name|gboolean
name|wants_triple_click
decl_stmt|;
DECL|member|wants_all_key_events
name|gboolean
name|wants_all_key_events
decl_stmt|;
DECL|member|active_modifiers
name|GimpToolActiveModifiers
name|active_modifiers
decl_stmt|;
DECL|member|toggled
name|gboolean
name|toggled
decl_stmt|;
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
DECL|member|action_opacity
name|gchar
modifier|*
name|action_opacity
decl_stmt|;
DECL|member|action_size
name|gchar
modifier|*
name|action_size
decl_stmt|;
DECL|member|action_aspect
name|gchar
modifier|*
name|action_aspect
decl_stmt|;
DECL|member|action_angle
name|gchar
modifier|*
name|action_angle
decl_stmt|;
DECL|member|action_spacing
name|gchar
modifier|*
name|action_spacing
decl_stmt|;
DECL|member|action_hardness
name|gchar
modifier|*
name|action_hardness
decl_stmt|;
DECL|member|action_force
name|gchar
modifier|*
name|action_force
decl_stmt|;
DECL|member|action_object_1
name|gchar
modifier|*
name|action_object_1
decl_stmt|;
DECL|member|action_object_2
name|gchar
modifier|*
name|action_object_2
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
name|gimp_tool_control_get_preserve
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_push_preserve
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
name|gimp_tool_control_pop_preserve
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
name|gimp_tool_control_get_scroll_lock
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_handle_empty_image
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
name|gimp_tool_control_get_handle_empty_image
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_dirty_mask
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDirtyMask
name|gimp_tool_control_get_dirty_mask
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
name|gimp_tool_control_get_motion_mode
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
name|gimp_tool_control_get_snap_to
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_wants_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_click
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_get_wants_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_wants_double_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_double_click
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_get_wants_double_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_wants_triple_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_double_click
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_get_wants_triple_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_wants_all_key_events
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_key_events
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_control_get_wants_all_key_events
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_active_modifiers
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpToolActiveModifiers
name|active_modifiers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpToolActiveModifiers
name|gimp_tool_control_get_active_modifiers
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
name|gimp_tool_control_get_snap_offsets
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
name|void
name|gimp_tool_control_set_precision
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorPrecision
name|precision
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCursorPrecision
name|gimp_tool_control_get_precision
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_toggled
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
name|gimp_tool_control_get_toggled
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
name|modifier
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
name|modifier
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
name|gimp_tool_control_set_action_opacity
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_opacity
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_size
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_size
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_aspect
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_aspect
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_angle
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_angle
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_spacing
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_spacing
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_hardness
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_hardness
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_force
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_force
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_object_1
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_object_1
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control_set_action_object_2
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_control_get_action_object_2
parameter_list|(
name|GimpToolControl
modifier|*
name|control
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

