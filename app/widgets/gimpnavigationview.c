begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpNavigationView Widget  * Copyright (C) 2001-2002 Michael Natterer<mitch@gimp.org>  *  * partly based on app/nav_window  * Copyright (C) 1999 Andy Thomas<alt@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpnavigationview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_define
DECL|macro|BORDER_WIDTH
define|#
directive|define
name|BORDER_WIDTH
value|2
end_define

begin_enum
enum|enum
DECL|enum|__anon29e9da8f0103
block|{
DECL|enumerator|MARKER_CHANGED
name|MARKER_CHANGED
block|,
DECL|enumerator|ZOOM
name|ZOOM
block|,
DECL|enumerator|SCROLL
name|SCROLL
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpNavigationView
struct|struct
name|_GimpNavigationView
block|{
DECL|member|parent_instance
name|GimpView
name|parent_instance
decl_stmt|;
comment|/*  values in image coordinates  */
DECL|member|center_x
name|gdouble
name|center_x
decl_stmt|;
DECL|member|center_y
name|gdouble
name|center_y
decl_stmt|;
DECL|member|width
name|gdouble
name|width
decl_stmt|;
DECL|member|height
name|gdouble
name|height
decl_stmt|;
DECL|member|flip_horizontally
name|gboolean
name|flip_horizontally
decl_stmt|;
DECL|member|flip_vertically
name|gboolean
name|flip_vertically
decl_stmt|;
DECL|member|rotate_angle
name|gdouble
name|rotate_angle
decl_stmt|;
comment|/*  values in view coordinates  */
DECL|member|p_center_x
name|gint
name|p_center_x
decl_stmt|;
DECL|member|p_center_y
name|gint
name|p_center_y
decl_stmt|;
DECL|member|p_width
name|gint
name|p_width
decl_stmt|;
DECL|member|p_height
name|gint
name|p_height
decl_stmt|;
DECL|member|motion_offset_x
name|gint
name|motion_offset_x
decl_stmt|;
DECL|member|motion_offset_y
name|gint
name|motion_offset_y
decl_stmt|;
DECL|member|has_grab
name|gboolean
name|has_grab
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_navigation_view_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_view_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_view_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_view_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_view_scroll
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventScroll
modifier|*
name|sevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_view_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_view_key_press
parameter_list|(
name|GtkWidget
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
specifier|static
name|void
name|gimp_navigation_view_transform
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_view_draw_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_view_move_to
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|gint
name|tx
parameter_list|,
name|gint
name|ty
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_view_get_ratio
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|gdouble
modifier|*
name|ratiox
parameter_list|,
name|gdouble
modifier|*
name|ratioy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_view_point_in_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpNavigationView
argument_list|,
argument|gimp_navigation_view
argument_list|,
argument|GIMP_TYPE_VIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_navigation_view_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|view_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_class_init (GimpNavigationViewClass * klass)
name|gimp_navigation_view_class_init
parameter_list|(
name|GimpNavigationViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|view_signals
index|[
name|MARKER_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"marker-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpNavigationViewClass
argument_list|,
name|marker_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__DOUBLE_DOUBLE_DOUBLE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|4
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|ZOOM
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"zoom"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpNavigationViewClass
argument_list|,
name|zoom
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_ZOOM_TYPE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|SCROLL
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"scroll"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpNavigationViewClass
argument_list|,
name|scroll
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__BOXED
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GDK_TYPE_EVENT
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_navigation_view_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|draw
operator|=
name|gimp_navigation_view_draw
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_navigation_view_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_navigation_view_button_release
expr_stmt|;
name|widget_class
operator|->
name|scroll_event
operator|=
name|gimp_navigation_view_scroll
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_navigation_view_motion_notify
expr_stmt|;
name|widget_class
operator|->
name|key_press_event
operator|=
name|gimp_navigation_view_key_press
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_init (GimpNavigationView * view)
name|gimp_navigation_view_init
parameter_list|(
name|GimpNavigationView
modifier|*
name|view
parameter_list|)
block|{
name|gtk_widget_set_can_focus
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|GDK_SCROLL_MASK
operator||
name|GDK_SMOOTH_SCROLL_MASK
operator||
name|GDK_POINTER_MOTION_MASK
operator||
name|GDK_KEY_PRESS_MASK
argument_list|)
expr_stmt|;
name|view
operator|->
name|center_x
operator|=
literal|0.0
expr_stmt|;
name|view
operator|->
name|center_y
operator|=
literal|0.0
expr_stmt|;
name|view
operator|->
name|width
operator|=
literal|0.0
expr_stmt|;
name|view
operator|->
name|height
operator|=
literal|0.0
expr_stmt|;
name|view
operator|->
name|flip_horizontally
operator|=
name|FALSE
expr_stmt|;
name|view
operator|->
name|flip_vertically
operator|=
name|FALSE
expr_stmt|;
name|view
operator|->
name|rotate_angle
operator|=
literal|0.0
expr_stmt|;
name|view
operator|->
name|p_center_x
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|p_center_y
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|p_width
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|p_height
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|motion_offset_x
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|motion_offset_y
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|has_grab
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_navigation_view_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VIEW
argument_list|(
name|widget
argument_list|)
operator|->
name|renderer
operator|->
name|viewable
condition|)
name|gimp_navigation_view_transform
argument_list|(
name|GIMP_NAVIGATION_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_navigation_view_draw (GtkWidget * widget,cairo_t * cr)
name|gimp_navigation_view_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|draw
argument_list|(
name|widget
argument_list|,
name|cr
argument_list|)
expr_stmt|;
name|gimp_navigation_view_draw_marker
argument_list|(
name|GIMP_NAVIGATION_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|cr
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_navigation_view_grab_pointer (GimpNavigationView * nav_view,GdkEvent * event)
name|gimp_navigation_view_grab_pointer
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|nav_view
argument_list|)
decl_stmt|;
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|nav_view
operator|->
name|has_grab
operator|=
name|TRUE
expr_stmt|;
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_FLEUR
argument_list|)
expr_stmt|;
name|window
operator|=
name|GIMP_VIEW
argument_list|(
name|nav_view
argument_list|)
operator|->
name|event_window
expr_stmt|;
name|gdk_seat_grab
argument_list|(
name|gdk_event_get_seat
argument_list|(
name|event
argument_list|)
argument_list|,
name|window
argument_list|,
name|GDK_SEAT_CAPABILITY_ALL
argument_list|,
name|FALSE
argument_list|,
name|cursor
argument_list|,
name|event
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_navigation_view_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_navigation_view_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
name|GimpNavigationView
modifier|*
name|nav_view
init|=
name|GIMP_NAVIGATION_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|tx
operator|=
name|bevent
operator|->
name|x
expr_stmt|;
name|ty
operator|=
name|bevent
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
operator|&&
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_navigation_view_point_in_marker
argument_list|(
name|nav_view
argument_list|,
name|tx
argument_list|,
name|ty
argument_list|)
condition|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|nav_view
operator|->
name|motion_offset_x
operator|=
literal|0
expr_stmt|;
name|nav_view
operator|->
name|motion_offset_y
operator|=
literal|0
expr_stmt|;
name|gimp_navigation_view_move_to
argument_list|(
name|nav_view
argument_list|,
name|tx
argument_list|,
name|ty
argument_list|)
expr_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_FLEUR
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|GIMP_VIEW
argument_list|(
name|widget
argument_list|)
operator|->
name|event_window
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|nav_view
operator|->
name|motion_offset_x
operator|=
name|tx
operator|-
name|nav_view
operator|->
name|p_center_x
expr_stmt|;
name|nav_view
operator|->
name|motion_offset_y
operator|=
name|ty
operator|-
name|nav_view
operator|->
name|p_center_y
expr_stmt|;
block|}
name|gimp_navigation_view_grab_pointer
argument_list|(
name|nav_view
argument_list|,
operator|(
name|GdkEvent
operator|*
operator|)
name|bevent
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_navigation_view_button_release (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_navigation_view_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
name|GimpNavigationView
modifier|*
name|nav_view
init|=
name|GIMP_NAVIGATION_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
operator|&&
name|nav_view
operator|->
name|has_grab
condition|)
block|{
name|nav_view
operator|->
name|has_grab
operator|=
name|FALSE
expr_stmt|;
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gdk_seat_ungrab
argument_list|(
name|gdk_event_get_seat
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|bevent
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_navigation_view_scroll (GtkWidget * widget,GdkEventScroll * sevent)
name|gimp_navigation_view_scroll
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventScroll
modifier|*
name|sevent
parameter_list|)
block|{
if|if
condition|(
name|sevent
operator|->
name|state
operator|&
name|gimp_get_toggle_behavior_mask
argument_list|()
condition|)
block|{
name|gdouble
name|delta
decl_stmt|;
switch|switch
condition|(
name|sevent
operator|->
name|direction
condition|)
block|{
case|case
name|GDK_SCROLL_UP
case|:
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|view_signals
index|[
name|ZOOM
index|]
argument_list|,
literal|0
argument_list|,
name|GIMP_ZOOM_IN
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_SCROLL_DOWN
case|:
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|view_signals
index|[
name|ZOOM
index|]
argument_list|,
literal|0
argument_list|,
name|GIMP_ZOOM_OUT
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_SCROLL_SMOOTH
case|:
name|gdk_event_get_scroll_deltas
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|sevent
argument_list|,
name|NULL
argument_list|,
operator|&
name|delta
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|view_signals
index|[
name|ZOOM
index|]
argument_list|,
literal|0
argument_list|,
name|GIMP_ZOOM_SMOOTH
argument_list|,
name|delta
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
else|else
block|{
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|view_signals
index|[
name|SCROLL
index|]
argument_list|,
literal|0
argument_list|,
name|sevent
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_navigation_view_motion_notify (GtkWidget * widget,GdkEventMotion * mevent)
name|gimp_navigation_view_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|)
block|{
name|GimpNavigationView
modifier|*
name|nav_view
init|=
name|GIMP_NAVIGATION_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpView
modifier|*
name|view
init|=
name|GIMP_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|nav_view
operator|->
name|has_grab
condition|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
if|if
condition|(
name|nav_view
operator|->
name|p_center_x
operator|==
name|view
operator|->
name|renderer
operator|->
name|width
operator|/
literal|2
operator|&&
name|nav_view
operator|->
name|p_center_y
operator|==
name|view
operator|->
name|renderer
operator|->
name|height
operator|/
literal|2
operator|&&
name|nav_view
operator|->
name|p_width
operator|==
name|view
operator|->
name|renderer
operator|->
name|width
operator|&&
name|nav_view
operator|->
name|p_height
operator|==
name|view
operator|->
name|renderer
operator|->
name|height
condition|)
block|{
name|gdk_window_set_cursor
argument_list|(
name|view
operator|->
name|event_window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|gimp_navigation_view_point_in_marker
argument_list|(
name|nav_view
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|)
condition|)
block|{
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_FLEUR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_HAND2
argument_list|)
expr_stmt|;
block|}
name|gdk_window_set_cursor
argument_list|(
name|view
operator|->
name|event_window
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_navigation_view_move_to
argument_list|(
name|nav_view
argument_list|,
name|mevent
operator|->
name|x
operator|-
name|nav_view
operator|->
name|motion_offset_x
argument_list|,
name|mevent
operator|->
name|y
operator|-
name|nav_view
operator|->
name|motion_offset_y
argument_list|)
expr_stmt|;
name|gdk_event_request_motions
argument_list|(
name|mevent
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_navigation_view_key_press (GtkWidget * widget,GdkEventKey * kevent)
name|gimp_navigation_view_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
block|{
name|GimpNavigationView
modifier|*
name|nav_view
init|=
name|GIMP_NAVIGATION_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|scroll_x
init|=
literal|0
decl_stmt|;
name|gint
name|scroll_y
init|=
literal|0
decl_stmt|;
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_KEY_Up
case|:
name|scroll_y
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_KEY_Left
case|:
name|scroll_x
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_KEY_Right
case|:
name|scroll_x
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_KEY_Down
case|:
name|scroll_y
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|scroll_x
operator|||
name|scroll_y
condition|)
block|{
name|gimp_navigation_view_move_to
argument_list|(
name|nav_view
argument_list|,
name|nav_view
operator|->
name|p_center_x
operator|+
name|scroll_x
argument_list|,
name|nav_view
operator|->
name|p_center_y
operator|+
name|scroll_y
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_navigation_view_set_marker (GimpNavigationView * nav_view,gdouble center_x,gdouble center_y,gdouble width,gdouble height,gboolean flip_horizontally,gboolean flip_vertically,gdouble rotate_angle)
name|gimp_navigation_view_set_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|gdouble
name|height
parameter_list|,
name|gboolean
name|flip_horizontally
parameter_list|,
name|gboolean
name|flip_vertically
parameter_list|,
name|gdouble
name|rotate_angle
parameter_list|)
block|{
name|GimpView
modifier|*
name|view
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_NAVIGATION_VIEW
argument_list|(
name|nav_view
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_VIEW
argument_list|(
name|nav_view
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|view
operator|->
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|center_x
operator|=
name|center_x
expr_stmt|;
name|nav_view
operator|->
name|center_y
operator|=
name|center_y
expr_stmt|;
name|nav_view
operator|->
name|width
operator|=
name|MAX
argument_list|(
literal|1.0
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|height
operator|=
name|MAX
argument_list|(
literal|1.0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|flip_horizontally
operator|=
name|flip_horizontally
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|nav_view
operator|->
name|flip_vertically
operator|=
name|flip_vertically
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|nav_view
operator|->
name|rotate_angle
operator|=
name|rotate_angle
expr_stmt|;
name|gimp_navigation_view_transform
argument_list|(
name|nav_view
argument_list|)
expr_stmt|;
comment|/* Marker changed, redraw */
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_navigation_view_set_motion_offset (GimpNavigationView * view,gint motion_offset_x,gint motion_offset_y)
name|gimp_navigation_view_set_motion_offset
parameter_list|(
name|GimpNavigationView
modifier|*
name|view
parameter_list|,
name|gint
name|motion_offset_x
parameter_list|,
name|gint
name|motion_offset_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_NAVIGATION_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|motion_offset_x
operator|=
name|motion_offset_x
expr_stmt|;
name|view
operator|->
name|motion_offset_y
operator|=
name|motion_offset_y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_navigation_view_get_local_marker (GimpNavigationView * view,gint * center_x,gint * center_y,gint * width,gint * height)
name|gimp_navigation_view_get_local_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|view
parameter_list|,
name|gint
modifier|*
name|center_x
parameter_list|,
name|gint
modifier|*
name|center_y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_NAVIGATION_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|center_x
condition|)
operator|*
name|center_x
operator|=
name|view
operator|->
name|p_center_x
expr_stmt|;
if|if
condition|(
name|center_y
condition|)
operator|*
name|center_y
operator|=
name|view
operator|->
name|p_center_y
expr_stmt|;
if|if
condition|(
name|width
condition|)
operator|*
name|width
operator|=
name|view
operator|->
name|p_width
expr_stmt|;
if|if
condition|(
name|height
condition|)
operator|*
name|height
operator|=
name|view
operator|->
name|p_height
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_transform (GimpNavigationView * nav_view)
name|gimp_navigation_view_transform
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|)
block|{
name|gdouble
name|ratiox
decl_stmt|,
name|ratioy
decl_stmt|;
name|gimp_navigation_view_get_ratio
argument_list|(
name|nav_view
argument_list|,
operator|&
name|ratiox
argument_list|,
operator|&
name|ratioy
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|p_center_x
operator|=
name|RINT
argument_list|(
name|nav_view
operator|->
name|center_x
operator|*
name|ratiox
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|p_center_y
operator|=
name|RINT
argument_list|(
name|nav_view
operator|->
name|center_y
operator|*
name|ratioy
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|p_width
operator|=
name|ceil
argument_list|(
name|nav_view
operator|->
name|width
operator|*
name|ratiox
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|p_height
operator|=
name|ceil
argument_list|(
name|nav_view
operator|->
name|height
operator|*
name|ratioy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_draw_marker (GimpNavigationView * nav_view,cairo_t * cr)
name|gimp_navigation_view_draw_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpView
modifier|*
name|view
init|=
name|GIMP_VIEW
argument_list|(
name|nav_view
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|renderer
operator|->
name|viewable
operator|&&
name|nav_view
operator|->
name|width
operator|&&
name|nav_view
operator|->
name|height
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|p_width_2
decl_stmt|;
name|gint
name|p_height_2
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|p_width_2
operator|=
name|nav_view
operator|->
name|p_width
operator|/
literal|2
expr_stmt|;
name|p_height_2
operator|=
name|nav_view
operator|->
name|p_height
operator|/
literal|2
expr_stmt|;
name|angle
operator|=
name|G_PI
operator|*
name|nav_view
operator|->
name|rotate_angle
operator|/
literal|180.0
expr_stmt|;
if|if
condition|(
name|nav_view
operator|->
name|flip_horizontally
operator|!=
name|nav_view
operator|->
name|flip_vertically
condition|)
name|angle
operator|=
operator|-
name|angle
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|allocation
operator|.
name|width
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|nav_view
operator|->
name|p_center_x
argument_list|,
name|nav_view
operator|->
name|p_center_y
argument_list|)
expr_stmt|;
name|cairo_rotate
argument_list|(
name|cr
argument_list|,
operator|-
name|angle
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
operator|-
name|p_width_2
argument_list|,
operator|-
name|p_height_2
argument_list|,
name|nav_view
operator|->
name|p_width
argument_list|,
name|nav_view
operator|->
name|p_height
argument_list|)
expr_stmt|;
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|cairo_set_fill_rule
argument_list|(
name|cr
argument_list|,
name|CAIRO_FILL_RULE_EVEN_ODD
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
operator|-
name|p_width_2
argument_list|,
operator|-
name|p_height_2
argument_list|,
name|nav_view
operator|->
name|p_width
argument_list|,
name|nav_view
operator|->
name|p_height
argument_list|)
expr_stmt|;
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
name|BORDER_WIDTH
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_move_to (GimpNavigationView * nav_view,gint tx,gint ty)
name|gimp_navigation_view_move_to
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|gint
name|tx
parameter_list|,
name|gint
name|ty
parameter_list|)
block|{
name|GimpView
modifier|*
name|view
init|=
name|GIMP_VIEW
argument_list|(
name|nav_view
argument_list|)
decl_stmt|;
name|gdouble
name|ratiox
decl_stmt|,
name|ratioy
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
if|if
condition|(
operator|!
name|view
operator|->
name|renderer
operator|->
name|viewable
condition|)
return|return;
name|gimp_navigation_view_get_ratio
argument_list|(
name|nav_view
argument_list|,
operator|&
name|ratiox
argument_list|,
operator|&
name|ratioy
argument_list|)
expr_stmt|;
name|x
operator|=
name|tx
operator|/
name|ratiox
expr_stmt|;
name|y
operator|=
name|ty
operator|/
name|ratioy
expr_stmt|;
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|MARKER_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|nav_view
operator|->
name|width
argument_list|,
name|nav_view
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_get_ratio (GimpNavigationView * nav_view,gdouble * ratiox,gdouble * ratioy)
name|gimp_navigation_view_get_ratio
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|gdouble
modifier|*
name|ratiox
parameter_list|,
name|gdouble
modifier|*
name|ratioy
parameter_list|)
block|{
name|GimpView
modifier|*
name|view
init|=
name|GIMP_VIEW
argument_list|(
name|nav_view
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|view
operator|->
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
operator|*
name|ratiox
operator|=
operator|(
name|gdouble
operator|)
name|view
operator|->
name|renderer
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
operator|*
name|ratioy
operator|=
operator|(
name|gdouble
operator|)
name|view
operator|->
name|renderer
operator|->
name|height
operator|/
operator|(
name|gdouble
operator|)
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_navigation_view_point_in_marker (GimpNavigationView * nav_view,gint x,gint y)
name|gimp_navigation_view_point_in_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|p_width_2
decl_stmt|,
name|p_height_2
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|p_width_2
operator|=
name|nav_view
operator|->
name|p_width
operator|/
literal|2
expr_stmt|;
name|p_height_2
operator|=
name|nav_view
operator|->
name|p_height
operator|/
literal|2
expr_stmt|;
name|angle
operator|=
name|G_PI
operator|*
name|nav_view
operator|->
name|rotate_angle
operator|/
literal|180.0
expr_stmt|;
if|if
condition|(
name|nav_view
operator|->
name|flip_horizontally
operator|!=
name|nav_view
operator|->
name|flip_vertically
condition|)
name|angle
operator|=
operator|-
name|angle
expr_stmt|;
name|x
operator|-=
name|nav_view
operator|->
name|p_center_x
expr_stmt|;
name|y
operator|-=
name|nav_view
operator|->
name|p_center_y
expr_stmt|;
name|tx
operator|=
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|x
operator|-
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|y
expr_stmt|;
name|ty
operator|=
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|x
operator|+
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|y
expr_stmt|;
return|return
name|tx
operator|>=
operator|-
name|p_width_2
operator|&&
name|tx
operator|<
name|p_width_2
operator|&&
name|ty
operator|>=
operator|-
name|p_height_2
operator|&&
name|ty
operator|<
name|p_height_2
return|;
block|}
end_function

end_unit

