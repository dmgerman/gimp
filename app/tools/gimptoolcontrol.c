begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_tool_control_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolControl,gimp_tool_control,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolControl
argument_list|,
argument|gimp_tool_control
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_control_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_control_class_init
parameter_list|(
name|GimpToolControlClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tool_control_finalize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_control_init (GimpToolControl * control)
name|gimp_tool_control_init
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|control
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|paused_count
operator|=
literal|0
expr_stmt|;
name|control
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|control
operator|->
name|scroll_lock
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|handle_empty_image
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|dirty_mask
operator|=
name|GIMP_DIRTY_NONE
expr_stmt|;
name|control
operator|->
name|motion_mode
operator|=
name|GIMP_MOTION_MODE_EXACT
expr_stmt|;
name|control
operator|->
name|auto_snap_to
operator|=
name|TRUE
expr_stmt|;
name|control
operator|->
name|snap_offset_x
operator|=
literal|0
expr_stmt|;
name|control
operator|->
name|snap_offset_y
operator|=
literal|0
expr_stmt|;
name|control
operator|->
name|snap_width
operator|=
literal|0
expr_stmt|;
name|control
operator|->
name|snap_height
operator|=
literal|0
expr_stmt|;
name|control
operator|->
name|precision
operator|=
name|GIMP_CURSOR_PRECISION_PIXEL_CENTER
expr_stmt|;
name|control
operator|->
name|toggled
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|wants_click
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|wants_double_click
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|wants_triple_click
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|wants_all_key_events
operator|=
name|FALSE
expr_stmt|;
name|control
operator|->
name|cursor
operator|=
name|GIMP_CURSOR_MOUSE
expr_stmt|;
name|control
operator|->
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
name|control
operator|->
name|cursor_modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
name|control
operator|->
name|toggle_cursor
operator|=
operator|-
literal|1
expr_stmt|;
name|control
operator|->
name|toggle_tool_cursor
operator|=
operator|-
literal|1
expr_stmt|;
name|control
operator|->
name|toggle_cursor_modifier
operator|=
operator|-
literal|1
expr_stmt|;
name|control
operator|->
name|action_opacity
operator|=
name|NULL
expr_stmt|;
name|control
operator|->
name|action_size
operator|=
name|NULL
expr_stmt|;
name|control
operator|->
name|action_aspect
operator|=
name|NULL
expr_stmt|;
name|control
operator|->
name|action_size
operator|=
name|NULL
expr_stmt|;
name|control
operator|->
name|action_object_1
operator|=
name|NULL
expr_stmt|;
name|control
operator|->
name|action_object_2
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_control_finalize (GObject * object)
name|gimp_tool_control_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolControl
modifier|*
name|control
init|=
name|GIMP_TOOL_CONTROL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_slist_free
argument_list|(
name|control
operator|->
name|preserve_stack
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|control
operator|->
name|action_opacity
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|control
operator|->
name|action_size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|control
operator|->
name|action_aspect
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|control
operator|->
name|action_angle
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|control
operator|->
name|action_object_1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|control
operator|->
name|action_object_2
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_tool_control_activate (GimpToolControl * control)
name|gimp_tool_control_activate
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|control
operator|->
name|active
operator|==
name|FALSE
argument_list|)
expr_stmt|;
name|control
operator|->
name|active
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_halt (GimpToolControl * control)
name|gimp_tool_control_halt
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|control
operator|->
name|active
operator|==
name|TRUE
argument_list|)
expr_stmt|;
name|control
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_is_active (GimpToolControl * control)
name|gimp_tool_control_is_active
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|active
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_pause (GimpToolControl * control)
name|gimp_tool_control_pause
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|paused_count
operator|++
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_resume (GimpToolControl * control)
name|gimp_tool_control_resume
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|control
operator|->
name|paused_count
operator|>
literal|0
argument_list|)
expr_stmt|;
name|control
operator|->
name|paused_count
operator|--
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_is_paused (GimpToolControl * control)
name|gimp_tool_control_is_paused
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|paused_count
operator|>
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_preserve (GimpToolControl * control,gboolean preserve)
name|gimp_tool_control_set_preserve
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|preserve
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|preserve
operator|=
name|preserve
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_preserve (GimpToolControl * control)
name|gimp_tool_control_get_preserve
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|preserve
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_push_preserve (GimpToolControl * control,gboolean preserve)
name|gimp_tool_control_push_preserve
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|preserve
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|preserve_stack
operator|=
name|g_slist_prepend
argument_list|(
name|control
operator|->
name|preserve_stack
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|control
operator|->
name|preserve
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|preserve
operator|=
name|preserve
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_pop_preserve (GimpToolControl * control)
name|gimp_tool_control_pop_preserve
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|control
operator|->
name|preserve_stack
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|control
operator|->
name|preserve
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|control
operator|->
name|preserve_stack
operator|->
name|data
argument_list|)
expr_stmt|;
name|control
operator|->
name|preserve_stack
operator|=
name|g_slist_delete_link
argument_list|(
name|control
operator|->
name|preserve_stack
argument_list|,
name|control
operator|->
name|preserve_stack
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_scroll_lock (GimpToolControl * control,gboolean scroll_lock)
name|gimp_tool_control_set_scroll_lock
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|scroll_lock
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|scroll_lock
operator|=
name|scroll_lock
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_scroll_lock (GimpToolControl * control)
name|gimp_tool_control_get_scroll_lock
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|scroll_lock
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_handle_empty_image (GimpToolControl * control,gboolean handle_empty)
name|gimp_tool_control_set_handle_empty_image
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|handle_empty
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|handle_empty_image
operator|=
name|handle_empty
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_handle_empty_image (GimpToolControl * control)
name|gimp_tool_control_get_handle_empty_image
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|handle_empty_image
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_dirty_mask (GimpToolControl * control,GimpDirtyMask dirty_mask)
name|gimp_tool_control_set_dirty_mask
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|dirty_mask
operator|=
name|dirty_mask
expr_stmt|;
block|}
end_function

begin_function
name|GimpDirtyMask
DECL|function|gimp_tool_control_get_dirty_mask (GimpToolControl * control)
name|gimp_tool_control_get_dirty_mask
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|GIMP_DIRTY_NONE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|dirty_mask
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_motion_mode (GimpToolControl * control,GimpMotionMode motion_mode)
name|gimp_tool_control_set_motion_mode
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpMotionMode
name|motion_mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|motion_mode
operator|=
name|motion_mode
expr_stmt|;
block|}
end_function

begin_function
name|GimpMotionMode
DECL|function|gimp_tool_control_get_motion_mode (GimpToolControl * control)
name|gimp_tool_control_get_motion_mode
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|GIMP_MOTION_MODE_EXACT
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|motion_mode
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_snap_to (GimpToolControl * control,gboolean snap_to)
name|gimp_tool_control_set_snap_to
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|snap_to
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|auto_snap_to
operator|=
name|snap_to
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_snap_to (GimpToolControl * control)
name|gimp_tool_control_get_snap_to
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|auto_snap_to
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_wants_click (GimpToolControl * control,gboolean wants_click)
name|gimp_tool_control_set_wants_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_click
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|wants_click
operator|=
name|wants_click
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_wants_click (GimpToolControl * control)
name|gimp_tool_control_get_wants_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|wants_click
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_wants_double_click (GimpToolControl * control,gboolean wants_double_click)
name|gimp_tool_control_set_wants_double_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_double_click
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|wants_double_click
operator|=
name|wants_double_click
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_wants_double_click (GimpToolControl * control)
name|gimp_tool_control_get_wants_double_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|wants_double_click
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_wants_triple_click (GimpToolControl * control,gboolean wants_triple_click)
name|gimp_tool_control_set_wants_triple_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_triple_click
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|wants_triple_click
operator|=
name|wants_triple_click
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_wants_triple_click (GimpToolControl * control)
name|gimp_tool_control_get_wants_triple_click
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|wants_triple_click
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_wants_all_key_events (GimpToolControl * control,gboolean wants_key_events)
name|gimp_tool_control_set_wants_all_key_events
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|wants_key_events
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|wants_all_key_events
operator|=
name|wants_key_events
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_wants_all_key_events (GimpToolControl * control)
name|gimp_tool_control_get_wants_all_key_events
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|wants_all_key_events
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_snap_offsets (GimpToolControl * control,gint offset_x,gint offset_y,gint width,gint height)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|snap_offset_x
operator|=
name|offset_x
expr_stmt|;
name|control
operator|->
name|snap_offset_y
operator|=
name|offset_y
expr_stmt|;
name|control
operator|->
name|snap_width
operator|=
name|width
expr_stmt|;
name|control
operator|->
name|snap_height
operator|=
name|height
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_get_snap_offsets (GimpToolControl * control,gint * offset_x,gint * offset_y,gint * width,gint * height)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset_x
condition|)
operator|*
name|offset_x
operator|=
name|control
operator|->
name|snap_offset_x
expr_stmt|;
if|if
condition|(
name|offset_y
condition|)
operator|*
name|offset_y
operator|=
name|control
operator|->
name|snap_offset_y
expr_stmt|;
if|if
condition|(
name|width
condition|)
operator|*
name|width
operator|=
name|control
operator|->
name|snap_width
expr_stmt|;
if|if
condition|(
name|height
condition|)
operator|*
name|height
operator|=
name|control
operator|->
name|snap_height
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_precision (GimpToolControl * control,GimpCursorPrecision precision)
name|gimp_tool_control_set_precision
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorPrecision
name|precision
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|precision
operator|=
name|precision
expr_stmt|;
block|}
end_function

begin_function
name|GimpCursorPrecision
DECL|function|gimp_tool_control_get_precision (GimpToolControl * control)
name|gimp_tool_control_get_precision
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|GIMP_CURSOR_PRECISION_PIXEL_CENTER
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|precision
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_toggled (GimpToolControl * control,gboolean toggled)
name|gimp_tool_control_set_toggled
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|gboolean
name|toggled
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|toggled
operator|=
name|toggled
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_control_get_toggled (GimpToolControl * control)
name|gimp_tool_control_get_toggled
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|toggled
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_cursor (GimpToolControl * control,GimpCursorType cursor)
name|gimp_tool_control_set_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorType
name|cursor
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|cursor
operator|=
name|cursor
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_tool_cursor (GimpToolControl * control,GimpToolCursorType cursor)
name|gimp_tool_control_set_tool_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpToolCursorType
name|cursor
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|tool_cursor
operator|=
name|cursor
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_cursor_modifier (GimpToolControl * control,GimpCursorModifier modifier)
name|gimp_tool_control_set_cursor_modifier
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|cursor_modifier
operator|=
name|modifier
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_toggle_cursor (GimpToolControl * control,GimpCursorType cursor)
name|gimp_tool_control_set_toggle_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorType
name|cursor
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|toggle_cursor
operator|=
name|cursor
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_toggle_tool_cursor (GimpToolControl * control,GimpToolCursorType cursor)
name|gimp_tool_control_set_toggle_tool_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpToolCursorType
name|cursor
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|toggle_tool_cursor
operator|=
name|cursor
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_toggle_cursor_modifier (GimpToolControl * control,GimpCursorModifier modifier)
name|gimp_tool_control_set_toggle_cursor_modifier
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
name|control
operator|->
name|toggle_cursor_modifier
operator|=
name|modifier
expr_stmt|;
block|}
end_function

begin_function
name|GimpCursorType
DECL|function|gimp_tool_control_get_cursor (GimpToolControl * control)
name|gimp_tool_control_get_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|control
operator|->
name|toggled
operator|&&
name|control
operator|->
name|toggle_cursor
operator|!=
operator|-
literal|1
condition|)
return|return
name|control
operator|->
name|toggle_cursor
return|;
return|return
name|control
operator|->
name|cursor
return|;
block|}
end_function

begin_function
name|GimpToolCursorType
DECL|function|gimp_tool_control_get_tool_cursor (GimpToolControl * control)
name|gimp_tool_control_get_tool_cursor
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|control
operator|->
name|toggled
operator|&&
name|control
operator|->
name|toggle_tool_cursor
operator|!=
operator|-
literal|1
condition|)
return|return
name|control
operator|->
name|toggle_tool_cursor
return|;
return|return
name|control
operator|->
name|tool_cursor
return|;
block|}
end_function

begin_function
name|GimpCursorModifier
DECL|function|gimp_tool_control_get_cursor_modifier (GimpToolControl * control)
name|gimp_tool_control_get_cursor_modifier
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|control
operator|->
name|toggled
operator|&&
name|control
operator|->
name|toggle_cursor_modifier
operator|!=
operator|-
literal|1
condition|)
return|return
name|control
operator|->
name|toggle_cursor_modifier
return|;
return|return
name|control
operator|->
name|cursor_modifier
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_action_opacity (GimpToolControl * control,const gchar * action)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
operator|!=
name|control
operator|->
name|action_opacity
condition|)
block|{
name|g_free
argument_list|(
name|control
operator|->
name|action_opacity
argument_list|)
expr_stmt|;
name|control
operator|->
name|action_opacity
operator|=
name|g_strdup
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_control_get_action_opacity (GimpToolControl * control)
name|gimp_tool_control_get_action_opacity
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|action_opacity
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_action_size (GimpToolControl * control,const gchar * action)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
operator|!=
name|control
operator|->
name|action_size
condition|)
block|{
name|g_free
argument_list|(
name|control
operator|->
name|action_size
argument_list|)
expr_stmt|;
name|control
operator|->
name|action_size
operator|=
name|g_strdup
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_control_get_action_size (GimpToolControl * control)
name|gimp_tool_control_get_action_size
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|action_size
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_action_aspect (GimpToolControl * control,const gchar * action)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
operator|!=
name|control
operator|->
name|action_aspect
condition|)
block|{
name|g_free
argument_list|(
name|control
operator|->
name|action_aspect
argument_list|)
expr_stmt|;
name|control
operator|->
name|action_aspect
operator|=
name|g_strdup
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_control_get_action_aspect (GimpToolControl * control)
name|gimp_tool_control_get_action_aspect
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|action_aspect
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_action_angle (GimpToolControl * control,const gchar * action)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
operator|!=
name|control
operator|->
name|action_angle
condition|)
block|{
name|g_free
argument_list|(
name|control
operator|->
name|action_angle
argument_list|)
expr_stmt|;
name|control
operator|->
name|action_angle
operator|=
name|g_strdup
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_control_get_action_angle (GimpToolControl * control)
name|gimp_tool_control_get_action_angle
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|action_angle
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_action_object_1 (GimpToolControl * control,const gchar * action)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
operator|!=
name|control
operator|->
name|action_object_1
condition|)
block|{
name|g_free
argument_list|(
name|control
operator|->
name|action_object_1
argument_list|)
expr_stmt|;
name|control
operator|->
name|action_object_1
operator|=
name|g_strdup
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_control_get_action_object_1 (GimpToolControl * control)
name|gimp_tool_control_get_action_object_1
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|action_object_1
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_control_set_action_object_2 (GimpToolControl * control,const gchar * action)
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
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
operator|!=
name|control
operator|->
name|action_object_2
condition|)
block|{
name|g_free
argument_list|(
name|control
operator|->
name|action_object_2
argument_list|)
expr_stmt|;
name|control
operator|->
name|action_object_2
operator|=
name|g_strdup
argument_list|(
name|action
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_tool_control_get_action_object_2 (GimpToolControl * control)
name|gimp_tool_control_get_action_object_2
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|control
operator|->
name|action_object_2
return|;
block|}
end_function

end_unit

