begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CURSORUTIL_H__
end_ifndef

begin_define
DECL|macro|__CURSORUTIL_H__
define|#
directive|define
name|__CURSORUTIL_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdktypes.h>
end_include

begin_if
if|#
directive|if
name|defined
argument_list|(
name|GDK_WINDOWING_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|GDK_WINDOWING_X11
argument_list|)
end_if

begin_comment
comment|/* Stopgap measure to detect build with current CVS GTk+ */
end_comment

begin_include
include|#
directive|include
file|<gdk/gdkcursor.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c51c74e0103
block|{
DECL|enumerator|GIMP_MOUSE_CURSOR
name|GIMP_MOUSE_CURSOR
init|=
operator|(
name|GDK_LAST_CURSOR
operator|+
literal|2
operator|)
block|,
DECL|enumerator|GIMP_MOUSE_ADD_CURSOR
name|GIMP_MOUSE_ADD_CURSOR
block|,
DECL|enumerator|GIMP_MOUSE_SUBTRACT_CURSOR
name|GIMP_MOUSE_SUBTRACT_CURSOR
block|,
DECL|enumerator|GIMP_MOUSE_INTERSECT_CURSOR
name|GIMP_MOUSE_INTERSECT_CURSOR
block|,
DECL|enumerator|GIMP_MOUSE_POINT_CURSOR
name|GIMP_MOUSE_POINT_CURSOR
block|,
DECL|enumerator|GIMP_MOUSE_RECTANGLE_CURSOR
name|GIMP_MOUSE_RECTANGLE_CURSOR
block|,
DECL|enumerator|GIMP_MOUSE_MOVE_CURSOR
name|GIMP_MOUSE_MOVE_CURSOR
block|,
DECL|enumerator|GIMP_SELECTION_CURSOR
name|GIMP_SELECTION_CURSOR
block|,
DECL|enumerator|GIMP_SELECTION_ADD_CURSOR
name|GIMP_SELECTION_ADD_CURSOR
block|,
DECL|enumerator|GIMP_SELECTION_SUBTRACT_CURSOR
name|GIMP_SELECTION_SUBTRACT_CURSOR
block|,
DECL|enumerator|GIMP_SELECTION_INTERSECT_CURSOR
name|GIMP_SELECTION_INTERSECT_CURSOR
block|,
DECL|enumerator|GIMP_BAD_CURSOR
name|GIMP_BAD_CURSOR
block|,
DECL|enumerator|GIMP_COLOR_PICKER_CURSOR
name|GIMP_COLOR_PICKER_CURSOR
block|,
DECL|enumerator|GIMP_ZOOM_IN_CURSOR
name|GIMP_ZOOM_IN_CURSOR
block|,
DECL|enumerator|GIMP_ZOOM_OUT_CURSOR
name|GIMP_ZOOM_OUT_CURSOR
block|,
DECL|enumerator|GIMP_LAST_CURSOR_ENTRY
name|GIMP_LAST_CURSOR_ENTRY
DECL|typedef|GimpCursorType
block|}
name|GimpCursorType
typedef|;
end_typedef

begin_function_decl
name|void
name|change_win_cursor
parameter_list|(
name|GdkWindow
modifier|*
name|win
parameter_list|,
name|GdkCursorType
name|curtype
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|unset_win_cursor
parameter_list|(
name|GdkWindow
modifier|*
name|win
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_add_busy_cursors_until_idle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_add_busy_cursors
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_remove_busy_cursors
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gtkutil_compress_motion
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
modifier|*
name|lastmotion_x
parameter_list|,
name|gdouble
modifier|*
name|lastmotion_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __CURSORUTIL_H__  */
end_comment

end_unit

