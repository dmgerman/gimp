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

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"info_dialog.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
end_include

begin_comment
comment|/*  *  Global variables  *  */
end_comment

begin_comment
comment|/*  some useful macros  */
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

begin_define
DECL|macro|SCALE (g,x)
define|#
directive|define
name|SCALE
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|((x * SCALEDEST(g)) / SCALESRC(g))
end_define

begin_define
DECL|macro|UNSCALE (g,x)
define|#
directive|define
name|UNSCALE
parameter_list|(
name|g
parameter_list|,
name|x
parameter_list|)
value|((x * SCALESRC(g)) / SCALEDEST(g))
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

begin_define
DECL|macro|HIGHPASS (x,y)
define|#
directive|define
name|HIGHPASS
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|)
value|((x>y) ? y : x)
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon296c6c510103
block|{
DECL|enumerator|SelectionOff
name|SelectionOff
block|,
DECL|enumerator|SelectionLayerOff
name|SelectionLayerOff
block|,
DECL|enumerator|SelectionOn
name|SelectionOn
block|,
DECL|enumerator|SelectionPause
name|SelectionPause
block|,
DECL|enumerator|SelectionResume
name|SelectionResume
DECL|typedef|SelectionControl
block|}
name|SelectionControl
typedef|;
end_typedef

begin_typedef
DECL|typedef|GDisplay
typedef|typedef
name|struct
name|_GDisplay
name|GDisplay
typedef|;
end_typedef

begin_struct
DECL|struct|_GDisplay
struct|struct
name|_GDisplay
block|{
DECL|member|ID
name|int
name|ID
decl_stmt|;
comment|/*  unique identifier for this gdisplay     */
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
DECL|member|vsb
name|GtkWidget
modifier|*
name|hsb
decl_stmt|,
modifier|*
name|vsb
decl_stmt|;
comment|/*  widgets for scroll bars                 */
DECL|member|hrule
DECL|member|vrule
name|GtkWidget
modifier|*
name|hrule
decl_stmt|,
modifier|*
name|vrule
decl_stmt|;
comment|/*  widgets for rulers                      */
DECL|member|origin
name|GtkWidget
modifier|*
name|origin
decl_stmt|;
comment|/*  widgets for rulers                      */
DECL|member|popup
name|GtkWidget
modifier|*
name|popup
decl_stmt|;
comment|/*  widget for popup menu                   */
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
comment|/*  dialog box for image information        */
DECL|member|color_type
name|int
name|color_type
decl_stmt|;
comment|/*  is this an RGB or GRAY colormap         */
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
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
comment|/*  pointer to the associated gimage struct */
DECL|member|instance
name|int
name|instance
decl_stmt|;
comment|/*  the instance # of this gdisplay as      */
comment|/*  taken from the gimage at creation       */
DECL|member|depth
name|int
name|depth
decl_stmt|;
comment|/*  depth of our drawables                  */
DECL|member|disp_width
name|int
name|disp_width
decl_stmt|;
comment|/*  width of drawing area in the window     */
DECL|member|disp_height
name|int
name|disp_height
decl_stmt|;
comment|/*  height of drawing area in the window    */
DECL|member|disp_xoffset
name|int
name|disp_xoffset
decl_stmt|;
DECL|member|disp_yoffset
name|int
name|disp_yoffset
decl_stmt|;
DECL|member|offset_x
DECL|member|offset_y
name|int
name|offset_x
decl_stmt|,
name|offset_y
decl_stmt|;
comment|/*  offset of display image into raw image  */
DECL|member|scale
name|int
name|scale
decl_stmt|;
comment|/*  scale factor from original raw image    */
DECL|member|draw_guides
name|short
name|draw_guides
decl_stmt|;
comment|/*  should the guides be drawn?             */
DECL|member|snap_to_guides
name|short
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
comment|/*  GC for scrolling */
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
comment|/*  Currently installed cursor              */
DECL|member|draw_cursor
name|short
name|draw_cursor
decl_stmt|;
comment|/* should we draw software cursor ? */
DECL|member|cursor_x
name|int
name|cursor_x
decl_stmt|;
comment|/* software cursor X value */
DECL|member|cursor_y
name|int
name|cursor_y
decl_stmt|;
comment|/* software cursor Y value */
DECL|member|proximity
name|short
name|proximity
decl_stmt|;
comment|/* is a device in proximity of gdisplay ? */
DECL|member|have_cursor
name|short
name|have_cursor
decl_stmt|;
comment|/* is cursor currently drawn ? */
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
parameter_list|,
name|unsigned
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_remove_and_delete
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gdisplay_mask_value
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gdisplay_mask_bounds
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_transform_coords
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_untransform_coords
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_transform_coords_f
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_untransform_coords_f
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_install_tool_cursor
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|GdkCursorType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_remove_tool_cursor
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_set_menu_sensitivity
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_expose_area
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_expose_guide
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_expose_full
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_flush
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_draw_guides
parameter_list|(
name|GDisplay
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_draw_guide
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Guide
modifier|*
name|gdisplay_find_guide
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_snap_point
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_snap_rectangle
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_update_cursor
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  function declarations  */
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
name|gdisplay_get_ID
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_update_title
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_update_area
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_expose_guides
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_expose_guide
parameter_list|(
name|GimpImage
modifier|*
parameter_list|,
name|Guide
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_update_full
parameter_list|(
name|GimpImage
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplays_shrink_wrap
parameter_list|(
name|GimpImage
modifier|*
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
parameter_list|,
name|SelectionControl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GDISPLAY_H__  */
end_comment

end_unit

