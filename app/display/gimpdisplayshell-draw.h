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
comment|/* FIXME remmove all gui/ stuff */
end_comment

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

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
DECL|member|item_factory
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
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
comment|/*  width of drawing area   */
DECL|member|disp_height
name|gint
name|disp_height
decl_stmt|;
comment|/*  height of drawing area  */
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
comment|/* is a device in proximity           */
DECL|member|select
name|Selection
modifier|*
name|select
decl_stmt|;
comment|/*  Selection object    */
DECL|member|display_areas
name|GSList
modifier|*
name|display_areas
decl_stmt|;
comment|/*  display areas list  */
DECL|member|hsbdata
name|GtkAdjustment
modifier|*
name|hsbdata
decl_stmt|;
comment|/*  adjustments         */
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
comment|/*  canvas widget       */
DECL|member|hsb
name|GtkWidget
modifier|*
name|hsb
decl_stmt|;
comment|/*  scroll bars         */
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
comment|/*  qmask button        */
DECL|member|hrule
name|GtkWidget
modifier|*
name|hrule
decl_stmt|;
comment|/*  rulers              */
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
comment|/*  origin button       */
DECL|member|statusbar
name|GtkWidget
modifier|*
name|statusbar
decl_stmt|;
comment|/*  statusbar           */
DECL|member|render_buf
name|guchar
modifier|*
name|render_buf
decl_stmt|;
comment|/*  buffer for rendering the image     */
DECL|member|render_gc
name|GdkGC
modifier|*
name|render_gc
decl_stmt|;
comment|/*  GC for rendering the image         */
DECL|member|title_dirty
name|gboolean
name|title_dirty
decl_stmt|;
comment|/*  checked by _flush()                */
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
DECL|member|padding_color
name|GimpRGB
name|padding_color
decl_stmt|;
comment|/* color of the empty around the image */
DECL|member|padding_gc
name|GdkGC
modifier|*
name|padding_gc
decl_stmt|;
comment|/* GC with padding_color as BG         */
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
DECL|member|nav_popup
name|GtkWidget
modifier|*
name|nav_popup
decl_stmt|;
comment|/*  navigation popup                   */
DECL|member|filters
name|GList
modifier|*
name|filters
decl_stmt|;
comment|/* color display conversion stuff      */
DECL|member|filters_dialog
name|GtkWidget
modifier|*
name|filters_dialog
decl_stmt|;
comment|/* color display filter dialog         */
comment|/*  the state of gimp_display_shell_tool_events()  */
DECL|member|space_pressed
name|gboolean
name|space_pressed
decl_stmt|;
DECL|member|space_release_pending
name|gboolean
name|space_release_pending
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
name|void
name|gimp_display_shell_transform_coords
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|image_coords
parameter_list|,
name|GimpCoords
modifier|*
name|display_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_untransform_coords
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|display_coords
parameter_list|,
name|GimpCoords
modifier|*
name|image_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_menu_sensitivity
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGuide
modifier|*
name|gimp_display_shell_find_guide
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_snap_point
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|tx
parameter_list|,
name|gdouble
modifier|*
name|ty
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_snap_rectangle
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
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
name|gdouble
modifier|*
name|tx1
parameter_list|,
name|gdouble
modifier|*
name|ty1
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_display_shell_mask_value
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
name|gimp_display_shell_add_expose_area
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GdkCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_override_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GdkCursorType
name|cursor_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_unset_override_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_update_cursor
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_update_title
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
name|gimp_display_shell_draw_guide
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_draw_guides
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

