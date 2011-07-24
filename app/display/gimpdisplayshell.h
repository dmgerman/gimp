begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_SHELL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_SHELL_H__
define|#
directive|define
name|__GIMP_DISPLAY_SHELL_H__
end_define

begin_comment
comment|/* Apply to a float the same rounding mode used in the renderer */
end_comment

begin_define
DECL|macro|PROJ_ROUND (coord)
define|#
directive|define
name|PROJ_ROUND
parameter_list|(
name|coord
parameter_list|)
value|((gint) RINT (coord))
end_define

begin_define
DECL|macro|PROJ_ROUND64 (coord)
define|#
directive|define
name|PROJ_ROUND64
parameter_list|(
name|coord
parameter_list|)
value|((gint64) RINT (coord))
end_define

begin_comment
comment|/* scale values */
end_comment

begin_define
DECL|macro|SCALEX (s,x)
define|#
directive|define
name|SCALEX
parameter_list|(
name|s
parameter_list|,
name|x
parameter_list|)
value|PROJ_ROUND ((x) * (s)->scale_x)
end_define

begin_define
DECL|macro|SCALEY (s,y)
define|#
directive|define
name|SCALEY
parameter_list|(
name|s
parameter_list|,
name|y
parameter_list|)
value|PROJ_ROUND ((y) * (s)->scale_y)
end_define

begin_comment
comment|/* unscale values */
end_comment

begin_define
DECL|macro|UNSCALEX (s,x)
define|#
directive|define
name|UNSCALEX
parameter_list|(
name|s
parameter_list|,
name|x
parameter_list|)
value|((gint) ((x) / (s)->scale_x))
end_define

begin_define
DECL|macro|UNSCALEY (s,y)
define|#
directive|define
name|UNSCALEY
parameter_list|(
name|s
parameter_list|,
name|y
parameter_list|)
value|((gint) ((y) / (s)->scale_y))
end_define

begin_comment
comment|/* (and float-returning versions) */
end_comment

begin_define
DECL|macro|FUNSCALEX (s,x)
define|#
directive|define
name|FUNSCALEX
parameter_list|(
name|s
parameter_list|,
name|x
parameter_list|)
value|((x) / (s)->scale_x)
end_define

begin_define
DECL|macro|FUNSCALEY (s,y)
define|#
directive|define
name|FUNSCALEY
parameter_list|(
name|s
parameter_list|,
name|y
parameter_list|)
value|((y) / (s)->scale_y)
end_define

begin_define
DECL|macro|GIMP_TYPE_DISPLAY_SHELL
define|#
directive|define
name|GIMP_TYPE_DISPLAY_SHELL
value|(gimp_display_shell_get_type ())
end_define

begin_define
DECL|macro|GIMP_DISPLAY_SHELL (obj)
define|#
directive|define
name|GIMP_DISPLAY_SHELL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DISPLAY_SHELL, GimpDisplayShell))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_SHELL_CLASS (klass)
define|#
directive|define
name|GIMP_DISPLAY_SHELL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DISPLAY_SHELL, GimpDisplayShellClass))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_SHELL (obj)
define|#
directive|define
name|GIMP_IS_DISPLAY_SHELL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DISPLAY_SHELL))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_SHELL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DISPLAY_SHELL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DISPLAY_SHELL))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_SHELL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DISPLAY_SHELL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DISPLAY_SHELL, GimpDisplayShellClass))
end_define

begin_typedef
DECL|typedef|GimpDisplayShellClass
typedef|typedef
name|struct
name|_GimpDisplayShellClass
name|GimpDisplayShellClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDisplayShell
struct|struct
name|_GimpDisplayShell
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|display
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
DECL|member|popup_manager
name|GimpUIManager
modifier|*
name|popup_manager
decl_stmt|;
DECL|member|options
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
DECL|member|fullscreen_options
name|GimpDisplayOptions
modifier|*
name|fullscreen_options
decl_stmt|;
DECL|member|no_image_options
name|GimpDisplayOptions
modifier|*
name|no_image_options
decl_stmt|;
DECL|member|snap_to_guides
name|gboolean
name|snap_to_guides
decl_stmt|;
comment|/*  should the guides be snapped to?   */
DECL|member|snap_to_grid
name|gboolean
name|snap_to_grid
decl_stmt|;
comment|/*  should the grid be snapped to?     */
DECL|member|snap_to_canvas
name|gboolean
name|snap_to_canvas
decl_stmt|;
comment|/*  should the canvas be snapped to?   */
DECL|member|snap_to_vectors
name|gboolean
name|snap_to_vectors
decl_stmt|;
comment|/*  should the active path be snapped  */
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|offset_x
name|gint
name|offset_x
decl_stmt|;
comment|/*  offset of display image            */
DECL|member|offset_y
name|gint
name|offset_y
decl_stmt|;
DECL|member|scale_x
name|gdouble
name|scale_x
decl_stmt|;
comment|/*  horizontal scale factor            */
DECL|member|scale_y
name|gdouble
name|scale_y
decl_stmt|;
comment|/*  vertical scale factor              */
DECL|member|monitor_xres
name|gdouble
name|monitor_xres
decl_stmt|;
DECL|member|monitor_yres
name|gdouble
name|monitor_yres
decl_stmt|;
DECL|member|dot_for_dot
name|gboolean
name|dot_for_dot
decl_stmt|;
comment|/*  ignore monitor resolution          */
DECL|member|x_src_dec
name|gint
name|x_src_dec
decl_stmt|;
comment|/*  increments for the bresenham style */
DECL|member|y_src_dec
name|gint
name|y_src_dec
decl_stmt|;
comment|/*  image --> display transformation   */
DECL|member|x_dest_inc
name|gint
name|x_dest_inc
decl_stmt|;
DECL|member|y_dest_inc
name|gint
name|y_dest_inc
decl_stmt|;
DECL|member|zoom
name|GimpZoomModel
modifier|*
name|zoom
decl_stmt|;
DECL|member|last_scale
name|gdouble
name|last_scale
decl_stmt|;
comment|/*  scale used when reverting zoom     */
DECL|member|last_scale_time
name|guint
name|last_scale_time
decl_stmt|;
comment|/*  time when last_scale was set       */
DECL|member|last_offset_x
name|gint
name|last_offset_x
decl_stmt|;
comment|/*  offsets used when reverting zoom   */
DECL|member|last_offset_y
name|gint
name|last_offset_y
decl_stmt|;
DECL|member|other_scale
name|gdouble
name|other_scale
decl_stmt|;
comment|/*  scale factor entered in Zoom->Other*/
DECL|member|disp_width
name|gint
name|disp_width
decl_stmt|;
comment|/*  width of drawing area              */
DECL|member|disp_height
name|gint
name|disp_height
decl_stmt|;
comment|/*  height of drawing area             */
DECL|member|proximity
name|gboolean
name|proximity
decl_stmt|;
comment|/*  is a device in proximity           */
DECL|member|selection
name|Selection
modifier|*
name|selection
decl_stmt|;
comment|/*  Selection (marching ants)          */
DECL|member|children
name|GList
modifier|*
name|children
decl_stmt|;
DECL|member|canvas
name|GtkWidget
modifier|*
name|canvas
decl_stmt|;
comment|/*  GimpCanvas widget                  */
DECL|member|hsbdata
name|GtkAdjustment
modifier|*
name|hsbdata
decl_stmt|;
comment|/*  adjustments                        */
DECL|member|vsbdata
name|GtkAdjustment
modifier|*
name|vsbdata
decl_stmt|;
DECL|member|hsb
name|GtkWidget
modifier|*
name|hsb
decl_stmt|;
comment|/*  scroll bars                        */
DECL|member|vsb
name|GtkWidget
modifier|*
name|vsb
decl_stmt|;
DECL|member|hrule
name|GtkWidget
modifier|*
name|hrule
decl_stmt|;
comment|/*  rulers                             */
DECL|member|vrule
name|GtkWidget
modifier|*
name|vrule
decl_stmt|;
DECL|member|origin
name|GtkWidget
modifier|*
name|origin
decl_stmt|;
comment|/*  NW: origin                         */
DECL|member|quick_mask_button
name|GtkWidget
modifier|*
name|quick_mask_button
decl_stmt|;
comment|/*  SW: quick mask button              */
DECL|member|zoom_button
name|GtkWidget
modifier|*
name|zoom_button
decl_stmt|;
comment|/*  NE: zoom toggle button             */
DECL|member|nav_ebox
name|GtkWidget
modifier|*
name|nav_ebox
decl_stmt|;
comment|/*  SE: navigation event box           */
DECL|member|statusbar
name|GtkWidget
modifier|*
name|statusbar
decl_stmt|;
comment|/*  statusbar                          */
DECL|member|render_surface
name|cairo_surface_t
modifier|*
name|render_surface
decl_stmt|;
comment|/*  buffer for rendering the image     */
DECL|member|mask_surface
name|cairo_surface_t
modifier|*
name|mask_surface
decl_stmt|;
comment|/*  buffer for rendering the mask      */
DECL|member|checkerboard
name|cairo_pattern_t
modifier|*
name|checkerboard
decl_stmt|;
comment|/*  checkerboard pattern               */
DECL|member|canvas_item
name|GimpCanvasItem
modifier|*
name|canvas_item
decl_stmt|;
comment|/*  items drawn on the canvas          */
DECL|member|passe_partout
name|GimpCanvasItem
modifier|*
name|passe_partout
decl_stmt|;
comment|/*  item for the highlight             */
DECL|member|vectors
name|GimpCanvasItem
modifier|*
name|vectors
decl_stmt|;
comment|/*  item proxy of vectors              */
DECL|member|grid
name|GimpCanvasItem
modifier|*
name|grid
decl_stmt|;
comment|/*  item proxy of the grid             */
DECL|member|guides
name|GimpCanvasItem
modifier|*
name|guides
decl_stmt|;
comment|/*  item proxies of guides             */
DECL|member|sample_points
name|GimpCanvasItem
modifier|*
name|sample_points
decl_stmt|;
comment|/*  item proxies of sample points      */
DECL|member|layer_boundary
name|GimpCanvasItem
modifier|*
name|layer_boundary
decl_stmt|;
comment|/*  item for the layer boundary        */
DECL|member|cursor
name|GimpCanvasItem
modifier|*
name|cursor
decl_stmt|;
comment|/*  item for the software cursor       */
DECL|member|title_idle_id
name|guint
name|title_idle_id
decl_stmt|;
comment|/*  title update idle ID               */
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
comment|/*  current title                      */
DECL|member|status
name|gchar
modifier|*
name|status
decl_stmt|;
comment|/*  current default statusbar content  */
DECL|member|icon_size
name|gint
name|icon_size
decl_stmt|;
comment|/*  size of the icon pixmap            */
DECL|member|icon_idle_id
name|guint
name|icon_idle_id
decl_stmt|;
comment|/*  ID of the idle-function            */
DECL|member|icon
name|GdkPixbuf
modifier|*
name|icon
decl_stmt|;
comment|/*  icon                               */
DECL|member|fill_idle_id
name|guint
name|fill_idle_id
decl_stmt|;
comment|/*  display_shell_fill() idle ID       */
DECL|member|cursor_format
name|GimpCursorFormat
name|cursor_format
decl_stmt|;
comment|/*  Currently used cursor format       */
DECL|member|cursor_handedness
name|GimpHandedness
name|cursor_handedness
decl_stmt|;
comment|/*  Handedness for cursor display      */
DECL|member|current_cursor
name|GimpCursorType
name|current_cursor
decl_stmt|;
comment|/*  Currently installed main cursor    */
DECL|member|tool_cursor
name|GimpToolCursorType
name|tool_cursor
decl_stmt|;
comment|/*  Current Tool cursor                */
DECL|member|cursor_modifier
name|GimpCursorModifier
name|cursor_modifier
decl_stmt|;
comment|/*  Cursor modifier (plus, minus, ...) */
DECL|member|override_cursor
name|GimpCursorType
name|override_cursor
decl_stmt|;
comment|/*  Overriding cursor                  */
DECL|member|using_override_cursor
name|gboolean
name|using_override_cursor
decl_stmt|;
DECL|member|draw_cursor
name|gboolean
name|draw_cursor
decl_stmt|;
comment|/* should we draw software cursor ?    */
DECL|member|close_dialog
name|GtkWidget
modifier|*
name|close_dialog
decl_stmt|;
comment|/*  close dialog                       */
DECL|member|scale_dialog
name|GtkWidget
modifier|*
name|scale_dialog
decl_stmt|;
comment|/*  scale (zoom) dialog                */
DECL|member|nav_popup
name|GtkWidget
modifier|*
name|nav_popup
decl_stmt|;
comment|/*  navigation popup                   */
DECL|member|grid_dialog
name|GtkWidget
modifier|*
name|grid_dialog
decl_stmt|;
comment|/*  grid configuration dialog          */
DECL|member|filter_stack
name|GimpColorDisplayStack
modifier|*
name|filter_stack
decl_stmt|;
comment|/* color display conversion stuff    */
DECL|member|filter_idle_id
name|guint
name|filter_idle_id
decl_stmt|;
DECL|member|filters_dialog
name|GtkWidget
modifier|*
name|filters_dialog
decl_stmt|;
comment|/* color display filter dialog       */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
DECL|member|vectors_freeze_handler
name|GimpTreeHandler
modifier|*
name|vectors_freeze_handler
decl_stmt|;
DECL|member|vectors_thaw_handler
name|GimpTreeHandler
modifier|*
name|vectors_thaw_handler
decl_stmt|;
DECL|member|vectors_visible_handler
name|GimpTreeHandler
modifier|*
name|vectors_visible_handler
decl_stmt|;
DECL|member|zoom_on_resize
name|gboolean
name|zoom_on_resize
decl_stmt|;
DECL|member|size_allocate_from_configure_event
name|gboolean
name|size_allocate_from_configure_event
decl_stmt|;
comment|/*  the state of gimp_display_shell_tool_events()  */
DECL|member|pointer_grabbed
name|gboolean
name|pointer_grabbed
decl_stmt|;
DECL|member|keyboard_grabbed
name|gboolean
name|keyboard_grabbed
decl_stmt|;
DECL|member|space_pressed
name|gboolean
name|space_pressed
decl_stmt|;
DECL|member|space_release_pending
name|gboolean
name|space_release_pending
decl_stmt|;
DECL|member|space_shaded_tool
specifier|const
name|gchar
modifier|*
name|space_shaded_tool
decl_stmt|;
DECL|member|scrolling
name|gboolean
name|scrolling
decl_stmt|;
DECL|member|scroll_start_x
name|gint
name|scroll_start_x
decl_stmt|;
DECL|member|scroll_start_y
name|gint
name|scroll_start_y
decl_stmt|;
DECL|member|scroll_info
name|gpointer
name|scroll_info
decl_stmt|;
DECL|member|mask
name|GimpDrawable
modifier|*
name|mask
decl_stmt|;
DECL|member|mask_color
name|GimpRGB
name|mask_color
decl_stmt|;
DECL|member|motion_buffer
name|GimpMotionBuffer
modifier|*
name|motion_buffer
decl_stmt|;
DECL|member|zoom_focus_pointer_queue
name|GQueue
modifier|*
name|zoom_focus_pointer_queue
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDisplayShellClass
struct|struct
name|_GimpDisplayShellClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|scaled
name|void
function_decl|(
modifier|*
name|scaled
function_decl|)
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
DECL|member|scrolled
name|void
function_decl|(
modifier|*
name|scrolled
function_decl|)
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
DECL|member|reconnect
name|void
function_decl|(
modifier|*
name|reconnect
function_decl|)
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_display_shell_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_display_shell_new
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|GimpUIManager
modifier|*
name|popup_manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_add_overlay
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gdouble
name|image_x
parameter_list|,
name|gdouble
name|image_y
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gint
name|spacing_x
parameter_list|,
name|gint
name|spacing_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_move_overlay
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gdouble
name|image_x
parameter_list|,
name|gdouble
name|image_y
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|,
name|gint
name|spacing_x
parameter_list|,
name|gint
name|spacing_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageWindow
modifier|*
name|gimp_display_shell_get_window
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStatusbar
modifier|*
name|gimp_display_shell_get_statusbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_present
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_reconnect
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_empty
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_fill
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_changed
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scaled
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scrolled
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_unit
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_display_shell_get_unit
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_snap_coords
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|snap_offset_x
parameter_list|,
name|gint
name|snap_offset_y
parameter_list|,
name|gint
name|snap_width
parameter_list|,
name|gint
name|snap_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_mask_bounds
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_flush
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|now
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_pause
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_resume
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_highlight
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|highlight
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_mask
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DISPLAY_SHELL_H__ */
end_comment

end_unit

