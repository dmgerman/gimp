begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolwidget.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_WIDGET_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_WIDGET_H__
define|#
directive|define
name|__GIMP_TOOL_WIDGET_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TOOL_WIDGET_RESPONSE_CONFIRM
define|#
directive|define
name|GIMP_TOOL_WIDGET_RESPONSE_CONFIRM
value|-1
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET_RESPONSE_CANCEL
define|#
directive|define
name|GIMP_TOOL_WIDGET_RESPONSE_CANCEL
value|-2
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET_RESPONSE_RESET
define|#
directive|define
name|GIMP_TOOL_WIDGET_RESPONSE_RESET
value|-3
end_define

begin_define
DECL|macro|GIMP_TYPE_TOOL_WIDGET
define|#
directive|define
name|GIMP_TYPE_TOOL_WIDGET
value|(gimp_tool_widget_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET (obj)
define|#
directive|define
name|GIMP_TOOL_WIDGET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_WIDGET, GimpToolWidget))
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_WIDGET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_WIDGET, GimpToolWidgetClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_WIDGET (obj)
define|#
directive|define
name|GIMP_IS_TOOL_WIDGET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_WIDGET))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_WIDGET_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_WIDGET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_WIDGET))
end_define

begin_define
DECL|macro|GIMP_TOOL_WIDGET_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_WIDGET_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_WIDGET, GimpToolWidgetClass))
end_define

begin_typedef
DECL|typedef|GimpToolWidgetPrivate
typedef|typedef
name|struct
name|_GimpToolWidgetPrivate
name|GimpToolWidgetPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolWidgetClass
typedef|typedef
name|struct
name|_GimpToolWidgetClass
name|GimpToolWidgetClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolWidget
struct|struct
name|_GimpToolWidget
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolWidgetPrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolWidgetClass
struct|struct
name|_GimpToolWidgetClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
DECL|member|response
name|void
function_decl|(
modifier|*
name|response
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
DECL|member|snap_offsets
name|void
function_decl|(
modifier|*
name|snap_offsets
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
DECL|member|status
name|void
function_decl|(
modifier|*
name|status
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|status
parameter_list|)
function_decl|;
DECL|member|status_coords
name|void
function_decl|(
modifier|*
name|status_coords
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
comment|/*  virtual functions  */
DECL|member|button_press
name|gint
function_decl|(
modifier|*
name|button_press
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
name|GimpButtonPressType
name|press_type
parameter_list|)
function_decl|;
DECL|member|button_release
name|void
function_decl|(
modifier|*
name|button_release
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
parameter_list|)
function_decl|;
DECL|member|motion
name|void
function_decl|(
modifier|*
name|motion
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
parameter_list|)
function_decl|;
DECL|member|hover
name|void
function_decl|(
modifier|*
name|hover
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
parameter_list|)
function_decl|;
DECL|member|key_press
name|gboolean
function_decl|(
modifier|*
name|key_press
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
function_decl|;
DECL|member|key_release
name|gboolean
function_decl|(
modifier|*
name|key_release
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
function_decl|;
DECL|member|motion_modifier
name|void
function_decl|(
modifier|*
name|motion_modifier
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
DECL|member|hover_modifier
name|void
function_decl|(
modifier|*
name|hover_modifier
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
DECL|member|get_cursor
name|gboolean
function_decl|(
modifier|*
name|get_cursor
function_decl|)
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpCursorType
modifier|*
name|cursor
parameter_list|,
name|GimpToolCursorType
modifier|*
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
modifier|*
name|cursor_modifier
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_widget_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDisplayShell
modifier|*
name|gimp_tool_widget_get_shell
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_get_item
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  for subclasses, to notify the handling tool  */
end_comment

begin_function_decl
name|void
name|gimp_tool_widget_response
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_set_snap_offsets
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
name|gimp_tool_widget_get_snap_offsets
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
name|gimp_tool_widget_set_status
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_set_status_coords
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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

begin_comment
comment|/*  for subclasses, to add and manage their items  */
end_comment

begin_function_decl
name|void
name|gimp_tool_widget_add_item
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_remove_item
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasGroup
modifier|*
name|gimp_tool_widget_add_stroke_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasGroup
modifier|*
name|gimp_tool_widget_add_fill_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_push_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_pop_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  for subclasses, convenience functions to add specific items  */
end_comment

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_line
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_rectangle
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|gboolean
name|filled
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_polygon
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|filled
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_polygon_from_coords
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|filled
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_path
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpBezierDesc
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_handle
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpHandleType
name|type
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_corner
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gint
name|corner_width
parameter_list|,
name|gint
name|corner_height
parameter_list|,
name|gboolean
name|outside
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_rectangle_guides
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCanvasItem
modifier|*
name|gimp_tool_widget_add_transform_guides
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|,
name|gint
name|n_guides
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  for tools, to be called from the respective GimpTool method  *  implementations  */
end_comment

begin_function_decl
name|gint
name|gimp_tool_widget_button_press
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
name|GimpButtonPressType
name|press_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_button_release
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_motion
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_hover
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_widget_key_press
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_widget_key_release
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_motion_modifier
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_widget_hover_modifier
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tool_widget_get_cursor
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpCursorType
modifier|*
name|cursor
parameter_list|,
name|GimpToolCursorType
modifier|*
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
modifier|*
name|cursor_modifier
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_WIDGET_H__ */
end_comment

end_unit

