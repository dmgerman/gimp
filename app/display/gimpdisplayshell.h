begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<gtk/gtkwindow.h>
end_include

begin_comment
comment|/*  FIXME: remove all gui/ stuff  */
end_comment

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

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
value|((gint) ceil (coord))
end_define

begin_comment
comment|/* finding the effective screen resolution (double) */
end_comment

begin_define
DECL|macro|SCREEN_XRES (s)
define|#
directive|define
name|SCREEN_XRES
parameter_list|(
name|s
parameter_list|)
value|(s->dot_for_dot ? \                            s->gdisp->gimage->xresolution : s->monitor_xres)
end_define

begin_define
DECL|macro|SCREEN_YRES (s)
define|#
directive|define
name|SCREEN_YRES
parameter_list|(
name|s
parameter_list|)
value|(s->dot_for_dot ? \                            s->gdisp->gimage->yresolution : s->monitor_yres)
end_define

begin_comment
comment|/* calculate scale factors (double) */
end_comment

begin_define
DECL|macro|SCALEFACTOR_X (s)
define|#
directive|define
name|SCALEFACTOR_X
parameter_list|(
name|s
parameter_list|)
value|(s->scale * SCREEN_XRES(s) / \ 			   s->gdisp->gimage->xresolution)
end_define

begin_define
DECL|macro|SCALEFACTOR_Y (s)
define|#
directive|define
name|SCALEFACTOR_Y
parameter_list|(
name|s
parameter_list|)
value|(s->scale * SCREEN_YRES(s) / \ 			   s->gdisp->gimage->yresolution)
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
value|PROJ_ROUND (x * SCALEFACTOR_X(s))
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
value|PROJ_ROUND (y * SCALEFACTOR_Y(s))
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
value|((gint) (x / SCALEFACTOR_X(s)))
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
value|((gint) (y / SCALEFACTOR_Y(s)))
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
value|(x / SCALEFACTOR_X(s))
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
value|(y / SCALEFACTOR_Y(s))
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
name|GtkWindow
name|parent_instance
decl_stmt|;
DECL|member|gdisp
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
DECL|member|menubar_manager
name|GimpUIManager
modifier|*
name|menubar_manager
decl_stmt|;
DECL|member|popup_manager
name|GimpUIManager
modifier|*
name|popup_manager
decl_stmt|;
DECL|member|monitor_xres
name|gdouble
name|monitor_xres
decl_stmt|;
DECL|member|monitor_yres
name|gdouble
name|monitor_yres
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
comment|/*  scale factor from original raw image    */
DECL|member|other_scale
name|gdouble
name|other_scale
decl_stmt|;
comment|/*  scale factor entered in Zoom->Other     */
DECL|member|dot_for_dot
name|gboolean
name|dot_for_dot
decl_stmt|;
comment|/*  is monitor resolution being ignored?    */
DECL|member|offset_x
name|gint
name|offset_x
decl_stmt|;
comment|/*  offset of display image into raw image  */
DECL|member|offset_y
name|gint
name|offset_y
decl_stmt|;
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
DECL|member|disp_xoffset
name|gint
name|disp_xoffset
decl_stmt|;
DECL|member|disp_yoffset
name|gint
name|disp_yoffset
decl_stmt|;
DECL|member|proximity
name|gboolean
name|proximity
decl_stmt|;
comment|/* is a device in proximity            */
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
DECL|member|select
name|Selection
modifier|*
name|select
decl_stmt|;
comment|/*  Selection object                   */
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
DECL|member|canvas
name|GtkWidget
modifier|*
name|canvas
decl_stmt|;
comment|/*  GimpCanvas widget                  */
DECL|member|grid_gc
name|GdkGC
modifier|*
name|grid_gc
decl_stmt|;
comment|/*  GC for grid drawing                */
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
DECL|member|qmask
name|GtkWidget
modifier|*
name|qmask
decl_stmt|;
comment|/*  qmask button                       */
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
comment|/*  origin button                      */
DECL|member|menubar
name|GtkWidget
modifier|*
name|menubar
decl_stmt|;
comment|/*  menubar                            */
DECL|member|statusbar
name|GtkWidget
modifier|*
name|statusbar
decl_stmt|;
comment|/*  statusbar                          */
DECL|member|render_buf
name|guchar
modifier|*
name|render_buf
decl_stmt|;
comment|/*  buffer for rendering the image     */
DECL|member|title_idle_id
name|guint
name|title_idle_id
decl_stmt|;
comment|/*  title update idle ID               */
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
DECL|member|current_cursor
name|GdkCursorType
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
name|GdkCursorType
name|override_cursor
decl_stmt|;
comment|/*  Overriding cursor                  */
DECL|member|using_override_cursor
name|gboolean
name|using_override_cursor
decl_stmt|;
comment|/*  is the cursor overridden?      */
DECL|member|draw_cursor
name|gboolean
name|draw_cursor
decl_stmt|;
comment|/* should we draw software cursor ?    */
DECL|member|have_cursor
name|gboolean
name|have_cursor
decl_stmt|;
comment|/* is cursor currently drawn ?         */
DECL|member|cursor_x
name|gint
name|cursor_x
decl_stmt|;
comment|/* software cursor X value             */
DECL|member|cursor_y
name|gint
name|cursor_y
decl_stmt|;
comment|/* software cursor Y value             */
DECL|member|padding_button
name|GtkWidget
modifier|*
name|padding_button
decl_stmt|;
comment|/* GimpColorPanel in the NE corner     */
DECL|member|nav_ebox
name|GtkWidget
modifier|*
name|nav_ebox
decl_stmt|;
comment|/* GtkEventBox on the SE corner        */
DECL|member|warning_dialog
name|GtkWidget
modifier|*
name|warning_dialog
decl_stmt|;
comment|/*  close warning dialog               */
DECL|member|info_dialog
name|InfoDialog
modifier|*
name|info_dialog
decl_stmt|;
comment|/*  image information dialog           */
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
comment|/* color display conversion stuff      */
DECL|member|filter_idle_id
name|guint
name|filter_idle_id
decl_stmt|;
DECL|member|filters_dialog
name|GtkWidget
modifier|*
name|filters_dialog
decl_stmt|;
comment|/* color display filter dialog         */
DECL|member|window_state
name|GdkWindowState
name|window_state
decl_stmt|;
comment|/* for fullscreen display              */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
DECL|member|vectors_freeze_handler
name|GQuark
name|vectors_freeze_handler
decl_stmt|;
DECL|member|vectors_thaw_handler
name|GQuark
name|vectors_thaw_handler
decl_stmt|;
DECL|member|vectors_visible_handler
name|GQuark
name|vectors_visible_handler
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
comment|/*  the state of gimp_display_shell_tool_events()  */
DECL|member|space_pressed
name|gboolean
name|space_pressed
decl_stmt|;
DECL|member|space_release_pending
name|gboolean
name|space_release_pending
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
DECL|member|button_press_before_focus
name|gboolean
name|button_press_before_focus
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
name|GtkWindowClass
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
name|gdisp
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
name|GimpUIManager
modifier|*
name|popup_manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_close
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|kill_it
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
name|GimpCoords
modifier|*
name|snapped_coords
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
name|gimp_display_shell_expose_area
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_expose_guide
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_expose_full
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
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
name|gimp_display_shell_update_icon
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_shrink_wrap
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_selection_visibility
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpSelectionControl
name|control
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

