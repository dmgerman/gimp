begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DISP_CALLBACKS_H__
end_ifndef

begin_define
DECL|macro|__DISP_CALLBACKS_H__
define|#
directive|define
name|__DISP_CALLBACKS_H__
end_define

begin_define
DECL|macro|CANVAS_EVENT_MASK
define|#
directive|define
name|CANVAS_EVENT_MASK
value|(GDK_EXPOSURE_MASK | \ 			   GDK_POINTER_MOTION_MASK | \ 			   GDK_POINTER_MOTION_HINT_MASK | \ 			   GDK_BUTTON_PRESS_MASK | \ 			   GDK_BUTTON_RELEASE_MASK | \ 			   GDK_STRUCTURE_MASK | \ 			   GDK_ENTER_NOTIFY_MASK | \ 			   GDK_LEAVE_NOTIFY_MASK | \ 			   GDK_KEY_PRESS_MASK | \ 			   GDK_KEY_RELEASE_MASK | \ 			   GDK_PROXIMITY_OUT_MASK)
end_define

begin_function_decl
name|gint
name|gdisplay_shell_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gdisplay_canvas_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gdisplay_hruler_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|dtata
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gdisplay_vruler_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gdisplay_origin_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gdisplay_drag_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guint
name|time
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdisplay_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GPattern
modifier|*
name|pattern
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DISP_CALLBACKS_H__ */
end_comment

end_unit

