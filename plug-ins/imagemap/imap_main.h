begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_MAIN_H
end_ifndef

begin_define
DECL|macro|_IMAP_MAIN_H
define|#
directive|define
name|_IMAP_MAIN_H
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"imap_mru.h"
end_include

begin_include
include|#
directive|include
file|"imap_object.h"
end_include

begin_include
include|#
directive|include
file|"imap_preferences.h"
end_include

begin_include
include|#
directive|include
file|"imap_preview.h"
end_include

begin_typedef
DECL|enum|__anon2ba92bf40103
DECL|enumerator|NCSA
DECL|enumerator|CERN
DECL|enumerator|CSIM
DECL|typedef|MapFormat_t
typedef|typedef
enum|enum
block|{
name|NCSA
block|,
name|CERN
block|,
name|CSIM
block|}
name|MapFormat_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2ba92bf40208
typedef|typedef
struct|struct
block|{
DECL|member|map_format
name|MapFormat_t
name|map_format
decl_stmt|;
DECL|member|image_name
name|gchar
modifier|*
name|image_name
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
DECL|member|default_url
name|gchar
modifier|*
name|default_url
decl_stmt|;
DECL|member|description
name|gchar
modifier|*
name|description
decl_stmt|;
DECL|member|old_image_width
name|gint
name|old_image_width
decl_stmt|;
DECL|member|old_image_height
name|gint
name|old_image_height
decl_stmt|;
DECL|member|color
name|gboolean
name|color
decl_stmt|;
comment|/* Color (TRUE) or Gray (FALSE) */
DECL|member|show_gray
name|gboolean
name|show_gray
decl_stmt|;
DECL|typedef|MapInfo_t
block|}
name|MapInfo_t
typedef|;
end_typedef

begin_function_decl
name|void
name|main_set_dimension
parameter_list|(
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
name|main_clear_dimension
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|save_as
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dump_output
parameter_list|(
name|gpointer
name|param
parameter_list|,
name|OutputFunc_t
name|output
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkColor
modifier|*
name|get_yellow
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|MRU_t
modifier|*
name|get_mru
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|MapInfo_t
modifier|*
name|get_map_info
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PreferencesData_t
modifier|*
name|get_preferences
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|get_top_widget
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|get_image_width
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|get_image_height
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_busy_cursor
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|remove_busy_cursor
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|main_toolbar_set_grid
parameter_list|(
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_zoom
parameter_list|(
name|gint
name|zoom_factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|get_real_coord
parameter_list|(
name|gint
name|coord
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_line
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_rectangle
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
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
name|draw_arc
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|angle1
parameter_list|,
name|gint
name|angle2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_circle
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_polygon
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|GList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|char
modifier|*
name|get_filename
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_arrow_func
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_rectangle_func
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_circle_func
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_polygon_func
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ObjectList_t
modifier|*
name|get_shapes
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_shape
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|update_shape
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|select_shape
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|edit_shape
parameter_list|(
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
name|do_popup_menu
parameter_list|(
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_shapes
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|redraw_preview
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|show_url
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|hide_url
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
comment|/* _IMAP_MAIN_H */
end_comment

end_unit

