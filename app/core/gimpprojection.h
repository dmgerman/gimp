begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GDISPLAY_H__
end_ifndef

begin_define
DECL|macro|__GDISPLAY_H__
define|#
directive|define
name|__GDISPLAY_H__
end_define

begin_comment
comment|/* FIXME: don't include gdisplay.h from core/ */
end_comment

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c72994d0103
block|{
DECL|enumerator|SELECTION_OFF
name|SELECTION_OFF
block|,
DECL|enumerator|SELECTION_LAYER_OFF
name|SELECTION_LAYER_OFF
block|,
DECL|enumerator|SELECTION_ON
name|SELECTION_ON
block|,
DECL|enumerator|SELECTION_PAUSE
name|SELECTION_PAUSE
block|,
DECL|enumerator|SELECTION_RESUME
name|SELECTION_RESUME
DECL|typedef|SelectionControl
block|}
name|SelectionControl
typedef|;
end_typedef

begin_comment
comment|/*  some useful macros  */
end_comment

begin_comment
comment|/* unpacking the user scale level (char) */
end_comment

begin_define
DECL|macro|SCALESRC (g)
define|#
directive|define
name|SCALESRC
parameter_list|(
name|g
parameter_list|)
value|(g->scale& 0x00ff)
end_define

begin_define
DECL|macro|SCALEDEST (g)
define|#
directive|define
name|SCALEDEST
parameter_list|(
name|g
parameter_list|)
value|(g->scale>> 8)
end_define

begin_comment
comment|/* finding the effective screen resolution (double) */
end_comment

begin_define
DECL|macro|SCREEN_XRES (g)
define|#
directive|define
name|SCREEN_XRES
parameter_list|(
name|g
parameter_list|)
value|(g->dot_for_dot? g->gimage->xresolution : gimprc.monitor_xres)
end_define

begin_define
DECL|macro|SCREEN_YRES (g)
define|#
directive|define
name|SCREEN_YRES
parameter_list|(
name|g
parameter_list|)
value|(g->dot_for_dot? g->gimage->yresolution : gimprc.monitor_yres)
end_define

begin_comment
comment|/* calculate scale factors (double) */
end_comment

begin_define
DECL|macro|SCALEFACTOR_X (g)
define|#
directive|define
name|SCALEFACTOR_X
parameter_list|(
name|g
parameter_list|)
value|((SCALEDEST(g) * SCREEN_XRES(g)) /          \ 			    (SCALESRC(g) * g->gimage->xresolution))
end_define

begin_define
DECL|macro|SCALEFACTOR_Y (g)
define|#
directive|define
name|SCALEFACTOR_Y
parameter_list|(
name|g
parameter_list|)
value|((SCALEDEST(g) * SCREEN_YRES(g)) /          \ 			    (SCALESRC(g) * g->gimage->yresolution))
end_define

begin_comment
comment|/* scale values */
end_comment

begin_define
DECL|macro|SCALEX (g,x)
define|#
directive|define
name|SCALEX
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|((int)(x * SCALEFACTOR_X(g)))
end_define

begin_define
DECL|macro|SCALEY (g,y)
define|#
directive|define
name|SCALEY
parameter_list|(
name|g
parameter_list|,
name|y
parameter_list|)
value|((int)(y * SCALEFACTOR_Y(g)))
end_define

begin_comment
comment|/* unscale values */
end_comment

begin_define
DECL|macro|UNSCALEX (g,x)
define|#
directive|define
name|UNSCALEX
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|((int)(x / SCALEFACTOR_X(g)))
end_define

begin_define
DECL|macro|UNSCALEY (g,y)
define|#
directive|define
name|UNSCALEY
parameter_list|(
name|g
parameter_list|,
name|y
parameter_list|)
value|((int)(y / SCALEFACTOR_Y(g)))
end_define

begin_comment
comment|/* (and float-returning versions) */
end_comment

begin_define
DECL|macro|FUNSCALEX (g,x)
define|#
directive|define
name|FUNSCALEX
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|((x / SCALEFACTOR_X(g)))
end_define

begin_define
DECL|macro|FUNSCALEY (g,y)
define|#
directive|define
name|FUNSCALEY
parameter_list|(
name|g
parameter_list|,
name|y
parameter_list|)
value|((y / SCALEFACTOR_Y(g)))
end_define

begin_define
DECL|macro|LOWPASS (x)
define|#
directive|define
name|LOWPASS
parameter_list|(
name|x
parameter_list|)
value|((x>0) ? x : 0)
end_define

begin_comment
comment|/* #define HIGHPASS(x,y) ((x>y) ? y : x) */
end_comment

begin_comment
comment|/* unused - == MIN */
end_comment

begin_comment
comment|/* maximal width of the string holding the cursor-coordinates for    the status line */
end_comment

begin_define
DECL|macro|CURSOR_STR_LENGTH
define|#
directive|define
name|CURSOR_STR_LENGTH
value|256
end_define

begin_comment
comment|/* maximal length of the format string for the cursor-coordinates */
end_comment

begin_define
DECL|macro|CURSOR_FORMAT_LENGTH
define|#
directive|define
name|CURSOR_FORMAT_LENGTH
value|32
end_define

begin_typedef
DECL|typedef|IdleRenderStruct
typedef|typedef
name|struct
name|_IdleRenderStruct
name|IdleRenderStruct
typedef|;
end_typedef

begin_struct
DECL|struct|_IdleRenderStruct
struct|struct
name|_IdleRenderStruct
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|basex
name|gint
name|basex
decl_stmt|;
DECL|member|basey
name|gint
name|basey
decl_stmt|;
DECL|member|idleid
name|guint
name|idleid
decl_stmt|;
DECL|member|active
name|gboolean
name|active
decl_stmt|;
DECL|member|update_areas
name|GSList
modifier|*
name|update_areas
decl_stmt|;
comment|/*  flushed update areas */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GDisplay
struct|struct
name|_GDisplay
block|{
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  unique identifier for this gdisplay     */
DECL|member|ifactory
name|GtkItemFactory
modifier|*
name|ifactory
decl_stmt|;
comment|/*  factory for popup menu                  */
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
comment|/*  shell widget for this gdisplay          */
DECL|member|canvas
name|GtkWidget
modifier|*
name|canvas
decl_stmt|;
comment|/*  canvas widget for this gdisplay         */
DECL|member|hsb
name|GtkWidget
modifier|*
name|hsb
decl_stmt|;
comment|/*  widgets for scroll bars                 */
DECL|member|vsb
name|GtkWidget
modifier|*
name|vsb
decl_stmt|;
DECL|member|qmaskoff
name|GtkWidget
modifier|*
name|qmaskoff
decl_stmt|;
comment|/*  widgets for qmask buttons               */
DECL|member|qmaskon
name|GtkWidget
modifier|*
name|qmaskon
decl_stmt|;
DECL|member|hrule
name|GtkWidget
modifier|*
name|hrule
decl_stmt|;
comment|/*  widgets for rulers                      */
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
comment|/*  widgets for rulers                      */
DECL|member|statusarea
name|GtkWidget
modifier|*
name|statusarea
decl_stmt|;
comment|/*  hbox holding the statusbar and stuff    */
DECL|member|statusbar
name|GtkWidget
modifier|*
name|statusbar
decl_stmt|;
comment|/*  widget for statusbar                    */
DECL|member|progressbar
name|GtkWidget
modifier|*
name|progressbar
decl_stmt|;
comment|/*  widget for progressbar                  */
DECL|member|cursor_label
name|GtkWidget
modifier|*
name|cursor_label
decl_stmt|;
comment|/*  widget for cursor position              */
DECL|member|cursor_format_str
name|gchar
name|cursor_format_str
index|[
name|CURSOR_FORMAT_LENGTH
index|]
decl_stmt|;
comment|/* we need a variable format string because 				   * different units have different number 				   * of decimals 				   */
DECL|member|cancelbutton
name|GtkWidget
modifier|*
name|cancelbutton
decl_stmt|;
comment|/*  widget for cancel button                */
DECL|member|progressid
name|guint
name|progressid
decl_stmt|;
comment|/*  id of statusbar message for progress    */
DECL|member|window_info_dialog
name|InfoDialog
modifier|*
name|window_info_dialog
decl_stmt|;
comment|/*  dialog box for image information  */
DECL|member|window_nav_dialog
name|NavigationDialog
modifier|*
name|window_nav_dialog
decl_stmt|;
comment|/*  dialog box for image navigation   */
DECL|member|nav_popup
name|NavigationDialog
modifier|*
name|nav_popup
decl_stmt|;
comment|/*  the popup navigation window       */
DECL|member|warning_dialog
name|GtkWidget
modifier|*
name|warning_dialog
decl_stmt|;
comment|/* "Changes were made to %s. Close anyway?" */
DECL|member|hsbdata
name|GtkAdjustment
modifier|*
name|hsbdata
decl_stmt|;
comment|/*  horizontal data information             */
DECL|member|vsbdata
name|GtkAdjustment
modifier|*
name|vsbdata
decl_stmt|;
comment|/*  vertical data information               */
DECL|member|icon
name|GdkPixmap
modifier|*
name|icon
decl_stmt|;
comment|/*  Pixmap for the icon                     */
DECL|member|iconmask
name|GdkBitmap
modifier|*
name|iconmask
decl_stmt|;
comment|/*  Bitmap for the icon mask                */
DECL|member|iconsize
name|guint
name|iconsize
decl_stmt|;
comment|/*  The size of the icon pixmap             */
DECL|member|icon_needs_update
name|gboolean
name|icon_needs_update
decl_stmt|;
comment|/*  Do we need to render a new icon?        */
DECL|member|icon_timeout_id
name|guint
name|icon_timeout_id
decl_stmt|;
comment|/*  The ID of the timeout-function          */
DECL|member|icon_idle_id
name|guint
name|icon_idle_id
decl_stmt|;
comment|/*  The ID of the idle-function             */
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/*  pointer to the associated gimage struct */
DECL|member|instance
name|gint
name|instance
decl_stmt|;
comment|/*  the instance # of this gdisplay as      */
comment|/*  taken from the gimage at creation       */
DECL|member|disp_width
name|gint
name|disp_width
decl_stmt|;
comment|/*  width of drawing area in the window     */
DECL|member|disp_height
name|gint
name|disp_height
decl_stmt|;
comment|/*  height of drawing area in the window    */
DECL|member|disp_xoffset
name|gint
name|disp_xoffset
decl_stmt|;
DECL|member|disp_yoffset
name|gint
name|disp_yoffset
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
DECL|member|scale
name|gint
name|scale
decl_stmt|;
comment|/*  scale factor from original raw image    */
DECL|member|dot_for_dot
name|gboolean
name|dot_for_dot
decl_stmt|;
comment|/*  is monitor resolution being ignored?    */
DECL|member|draw_guides
name|gboolean
name|draw_guides
decl_stmt|;
comment|/*  should the guides be drawn?             */
DECL|member|snap_to_guides
name|gboolean
name|snap_to_guides
decl_stmt|;
comment|/*  should the guides be snapped to?        */
DECL|member|select
name|Selection
modifier|*
name|select
decl_stmt|;
comment|/*  Selection object                        */
DECL|member|scroll_gc
name|GdkGC
modifier|*
name|scroll_gc
decl_stmt|;
comment|/*  GC for scrolling                        */
DECL|member|update_areas
name|GSList
modifier|*
name|update_areas
decl_stmt|;
comment|/*  Update areas list                       */
DECL|member|display_areas
name|GSList
modifier|*
name|display_areas
decl_stmt|;
comment|/*  Display areas list                      */
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
comment|/*  Overriding cursor (ie. hourglass)       */
DECL|member|using_override_cursor
name|gboolean
name|using_override_cursor
decl_stmt|;
comment|/* is the cursor overridden? (ie. hourglass)*/
DECL|member|draw_cursor
name|gboolean
name|draw_cursor
decl_stmt|;
comment|/* should we draw software cursor ?         */
DECL|member|cursor_x
name|gint
name|cursor_x
decl_stmt|;
comment|/* software cursor X value                  */
DECL|member|cursor_y
name|gint
name|cursor_y
decl_stmt|;
comment|/* software cursor Y value                  */
DECL|member|proximity
name|gboolean
name|proximity
decl_stmt|;
comment|/* is a device in proximity of gdisplay ?   */
DECL|member|have_cursor
name|gboolean
name|have_cursor
decl_stmt|;
comment|/* is cursor currently drawn ?              */
DECL|member|idle_render
name|IdleRenderStruct
name|idle_render
decl_stmt|;
comment|/* state of this gdisplay's render thread   */
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
DECL|member|cd_list
name|GList
modifier|*
name|cd_list
decl_stmt|;
comment|/* color display conversion stuff           */
DECL|member|cd_ui
name|GtkWidget
modifier|*
name|cd_ui
decl_stmt|;
comment|/* color display filter dialog              */
endif|#
directive|endif
comment|/* DISPLAY_FILTERS */
block|}
struct|;
end_struct

begin_comment
comment|/* member function declarations */
end_comment

begin_function_decl
name|GDisplay
modifier|*
name|gdisplay_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guint
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_reconnect
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_remove_and_delete
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gdisplay_mask_value
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|gint
name|gdisplay_mask_bounds
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|gdisplay_transform_coords
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_untransform_coords
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|,
name|gboolean
name|round
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_transform_coords_f
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_untransform_coords_f
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_real_install_tool_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|,
name|gboolean
name|always_install
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_install_tool_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|gdisplay_remove_tool_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_install_override_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkCursorType
name|cursor_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_remove_override_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_set_menu_sensitivity
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_expose_area
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|gdisplay_expose_guide
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_expose_full
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_selection_visibility
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|SelectionControl
name|function
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_flush
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_flush_now
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_update_icon
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gdisplay_update_icon_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gdisplay_update_icon_invoker
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_update_icon_scheduler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_draw_guides
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_draw_guide
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|GimpGuide
modifier|*
name|gdisplay_find_guide
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|double
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gdisplay_snap_point
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|void
name|gdisplay_snap_rectangle
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|void
name|gdisplay_update_cursor
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|gdisplay_set_dot_for_dot
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_resize_cursor_label
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_update_title
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_flush_displays_only
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* no rerender! */
end_comment

begin_function_decl
name|GDisplay
modifier|*
name|gdisplay_active
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GDisplay
modifier|*
name|gdisplay_get_by_ID
parameter_list|(
name|gint
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  function declarations  */
end_comment

begin_function_decl
name|GDisplay
modifier|*
name|gdisplays_check_valid
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_reconnect
parameter_list|(
name|GimpImage
modifier|*
name|old
parameter_list|,
name|GimpImage
modifier|*
name|new
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_update_title
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_resize_cursor_label
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_setup_scale
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_update_area
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|gdisplays_expose_guides
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_expose_guide
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_update_full
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_shrink_wrap
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_expose_full
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_selection_visibility
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|SelectionControl
name|function
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gdisplays_dirty
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_delete
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_flush
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_flush_now
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_finish_draw
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_nav_preview_resized
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_foreach
parameter_list|(
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GDISPLAY_H__  */
end_comment

end_unit

