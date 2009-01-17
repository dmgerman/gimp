begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_H__
define|#
directive|define
name|__GIMP_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL
define|#
directive|define
name|GIMP_TYPE_TOOL
value|(gimp_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL (obj)
define|#
directive|define
name|GIMP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL, GimpTool))
end_define

begin_define
DECL|macro|GIMP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL, GimpToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL))
end_define

begin_define
DECL|macro|GIMP_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL, GimpToolClass))
end_define

begin_define
DECL|macro|GIMP_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(gimp_tool_get_options (GIMP_TOOL (t)))
end_define

begin_typedef
DECL|typedef|GimpToolClass
typedef|typedef
name|struct
name|_GimpToolClass
name|GimpToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTool
struct|struct
name|_GimpTool
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|tool_info
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  unique tool ID                         */
DECL|member|control
name|GimpToolControl
modifier|*
name|control
decl_stmt|;
DECL|member|display
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
comment|/*  pointer to currently active display    */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/*  pointer to the tool's current drawable */
DECL|member|max_coord_smooth
name|gdouble
name|max_coord_smooth
decl_stmt|;
comment|/*  private state of gimp_tool_set_focus_display() and    *  gimp_tool_set_[active_]modifier_state()    */
DECL|member|focus_display
name|GimpDisplay
modifier|*
name|focus_display
decl_stmt|;
DECL|member|modifier_state
name|GdkModifierType
name|modifier_state
decl_stmt|;
DECL|member|button_press_state
name|GdkModifierType
name|button_press_state
decl_stmt|;
DECL|member|active_modifier_state
name|GdkModifierType
name|active_modifier_state
decl_stmt|;
comment|/*  private state for click detection    */
DECL|member|in_click_distance
name|gboolean
name|in_click_distance
decl_stmt|;
DECL|member|got_motion_event
name|gboolean
name|got_motion_event
decl_stmt|;
DECL|member|button_press_coords
name|GimpCoords
name|button_press_coords
decl_stmt|;
DECL|member|button_press_time
name|guint32
name|button_press_time
decl_stmt|;
comment|/*  private list of displays which have a status message from this tool    */
DECL|member|status_displays
name|GList
modifier|*
name|status_displays
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolClass
struct|struct
name|_GimpToolClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|has_display
name|gboolean
function_decl|(
modifier|*
name|has_display
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|has_image
name|GimpDisplay
modifier|*
function_decl|(
modifier|*
name|has_image
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|initialize
name|gboolean
function_decl|(
modifier|*
name|initialize
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
DECL|member|control
name|void
function_decl|(
modifier|*
name|control
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|button_press
name|void
function_decl|(
modifier|*
name|button_press
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|button_release
name|void
function_decl|(
modifier|*
name|button_release
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|motion
name|void
function_decl|(
modifier|*
name|motion
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|key_press
name|gboolean
function_decl|(
modifier|*
name|key_press
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
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
DECL|member|modifier_key
name|void
function_decl|(
modifier|*
name|modifier_key
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|active_modifier_key
name|void
function_decl|(
modifier|*
name|active_modifier_key
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|oper_update
name|void
function_decl|(
modifier|*
name|oper_update
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|cursor_update
name|void
function_decl|(
modifier|*
name|cursor_update
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|get_popup
name|GimpUIManager
modifier|*
function_decl|(
modifier|*
name|get_popup
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolOptions
modifier|*
name|gimp_tool_get_options
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_has_display
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplay
modifier|*
name|gimp_tool_has_image
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
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
name|void
name|gimp_tool_set_focus_display
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_set_modifier_state
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_set_active_modifier_state
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_tool_get_popup
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_push_status
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|3
operator|,
function_decl|4
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_tool_push_status_coords
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpCursorPrecision
name|precision
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
name|x
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separator
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_push_status_length
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpOrientationType
name|axis
parameter_list|,
name|gdouble
name|value
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_replace_status
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|3
operator|,
function_decl|4
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_tool_pop_status
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_message
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|3
operator|,
function_decl|4
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_tool_message_literal
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_set_cursor
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpCursorType
name|cursor
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TOOL_H__  */
end_comment

end_unit

