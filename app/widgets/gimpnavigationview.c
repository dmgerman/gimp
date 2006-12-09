begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpNavigationView Widget  * Copyright (C) 2001-2002 Michael Natterer<mitch@gimp.org>  *  * partly based on app/nav_window  * Copyright (C) 1999 Andy Thomas<alt@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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

begin_define
DECL|macro|BORDER_PEN_WIDTH
define|#
directive|define
name|BORDER_PEN_WIDTH
value|3
end_define

begin_enum
enum|enum
DECL|enum|__anon27f163bd0103
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

begin_function_decl
specifier|static
name|void
name|gimp_navigation_view_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_view_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_navigation_view_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
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
name|GdkRectangle
modifier|*
name|area
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
name|gimp_marshal_VOID__DOUBLE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
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
name|gimp_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_ZOOM_TYPE
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
name|gimp_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GDK_TYPE_SCROLL_DIRECTION
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_navigation_view_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_navigation_view_unrealize
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_navigation_view_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_navigation_view_expose
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
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|view
argument_list|,
name|GTK_CAN_FOCUS
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
operator|(
name|GDK_POINTER_MOTION_MASK
operator||
name|GDK_KEY_PRESS_MASK
operator|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|x
operator|=
literal|0.0
expr_stmt|;
name|view
operator|->
name|y
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
name|p_x
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|p_y
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
name|view
operator|->
name|gc
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_realize (GtkWidget * widget)
name|gimp_navigation_view_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_gc_set_function
argument_list|(
name|nav_view
operator|->
name|gc
argument_list|,
name|GDK_INVERT
argument_list|)
expr_stmt|;
name|gdk_gc_set_line_attributes
argument_list|(
name|nav_view
operator|->
name|gc
argument_list|,
name|BORDER_PEN_WIDTH
argument_list|,
name|GDK_LINE_SOLID
argument_list|,
name|GDK_CAP_BUTT
argument_list|,
name|GDK_JOIN_ROUND
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_view_unrealize (GtkWidget * widget)
name|gimp_navigation_view_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|nav_view
operator|->
name|gc
condition|)
block|{
name|g_object_unref
argument_list|(
name|nav_view
operator|->
name|gc
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|gc
operator|=
name|NULL
expr_stmt|;
block|}
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|unrealize
argument_list|(
name|widget
argument_list|)
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
DECL|function|gimp_navigation_view_expose (GtkWidget * widget,GdkEventExpose * eevent)
name|gimp_navigation_view_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|)
block|{
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|expose_event
argument_list|(
name|widget
argument_list|,
name|eevent
argument_list|)
expr_stmt|;
name|gimp_navigation_view_draw_marker
argument_list|(
name|GIMP_NAVIGATION_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|eevent
operator|->
name|area
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
name|GimpImage
modifier|*
name|image
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
name|tx
operator|=
name|CLAMP
argument_list|(
name|tx
argument_list|,
literal|0
argument_list|,
name|view
operator|->
name|renderer
operator|->
name|width
operator|-
name|nav_view
operator|->
name|p_width
argument_list|)
expr_stmt|;
name|ty
operator|=
name|CLAMP
argument_list|(
name|ty
argument_list|,
literal|0
argument_list|,
name|view
operator|->
name|renderer
operator|->
name|height
operator|-
name|nav_view
operator|->
name|p_height
argument_list|)
expr_stmt|;
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
comment|/*  transform to image coordinates  */
if|if
condition|(
name|view
operator|->
name|renderer
operator|->
name|width
operator|!=
name|nav_view
operator|->
name|p_width
condition|)
name|ratiox
operator|=
operator|(
operator|(
name|image
operator|->
name|width
operator|-
name|nav_view
operator|->
name|width
operator|+
literal|1.0
operator|)
operator|/
operator|(
name|view
operator|->
name|renderer
operator|->
name|width
operator|-
name|nav_view
operator|->
name|p_width
operator|)
operator|)
expr_stmt|;
else|else
name|ratiox
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|renderer
operator|->
name|height
operator|!=
name|nav_view
operator|->
name|p_height
condition|)
name|ratioy
operator|=
operator|(
operator|(
name|image
operator|->
name|height
operator|-
name|nav_view
operator|->
name|height
operator|+
literal|1.0
operator|)
operator|/
operator|(
name|view
operator|->
name|renderer
operator|->
name|height
operator|-
name|nav_view
operator|->
name|p_height
operator|)
operator|)
expr_stmt|;
else|else
name|ratioy
operator|=
literal|1.0
expr_stmt|;
name|x
operator|=
name|tx
operator|*
name|ratiox
expr_stmt|;
name|y
operator|=
name|ty
operator|*
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
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_navigation_view_grab_pointer (GimpNavigationView * nav_view)
name|gimp_navigation_view_grab_pointer
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
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
name|gdk_pointer_grab
argument_list|(
name|window
argument_list|,
name|TRUE
argument_list|,
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON_MOTION_MASK
operator||
name|GDK_EXTENSION_EVENTS_ALL
argument_list|,
name|window
argument_list|,
name|cursor
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
name|gdk_cursor_unref
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
switch|switch
condition|(
name|bevent
operator|->
name|button
condition|)
block|{
case|case
literal|1
case|:
if|if
condition|(
operator|!
operator|(
name|tx
operator|>
name|nav_view
operator|->
name|p_x
operator|&&
name|tx
operator|<
operator|(
name|nav_view
operator|->
name|p_x
operator|+
name|nav_view
operator|->
name|p_width
operator|)
operator|&&
name|ty
operator|>
name|nav_view
operator|->
name|p_y
operator|&&
name|ty
operator|<
operator|(
name|nav_view
operator|->
name|p_y
operator|+
name|nav_view
operator|->
name|p_height
operator|)
operator|)
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
name|nav_view
operator|->
name|p_width
operator|/
literal|2
expr_stmt|;
name|nav_view
operator|->
name|motion_offset_y
operator|=
name|nav_view
operator|->
name|p_height
operator|/
literal|2
expr_stmt|;
name|tx
operator|-=
name|nav_view
operator|->
name|motion_offset_x
expr_stmt|;
name|ty
operator|-=
name|nav_view
operator|->
name|motion_offset_y
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
name|gdk_cursor_unref
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
name|p_x
expr_stmt|;
name|nav_view
operator|->
name|motion_offset_y
operator|=
name|ty
operator|-
name|nav_view
operator|->
name|p_y
expr_stmt|;
block|}
name|gimp_navigation_view_grab_pointer
argument_list|(
name|nav_view
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
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
switch|switch
condition|(
name|bevent
operator|->
name|button
condition|)
block|{
case|case
literal|1
case|:
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
name|gdk_display_pointer_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
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
name|GDK_CONTROL_MASK
condition|)
block|{
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
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
else|else
block|{
name|GdkScrollDirection
name|direction
init|=
name|sevent
operator|->
name|direction
decl_stmt|;
if|if
condition|(
name|sevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
switch|switch
condition|(
name|direction
condition|)
block|{
case|case
name|GDK_SCROLL_UP
case|:
name|direction
operator|=
name|GDK_SCROLL_LEFT
expr_stmt|;
break|break;
case|case
name|GDK_SCROLL_DOWN
case|:
name|direction
operator|=
name|GDK_SCROLL_RIGHT
expr_stmt|;
break|break;
case|case
name|GDK_SCROLL_LEFT
case|:
name|direction
operator|=
name|GDK_SCROLL_UP
expr_stmt|;
break|break;
case|case
name|GDK_SCROLL_RIGHT
case|:
name|direction
operator|=
name|GDK_SCROLL_DOWN
expr_stmt|;
break|break;
block|}
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
name|direction
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
name|gint
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|GdkModifierType
name|mask
decl_stmt|;
if|if
condition|(
operator|!
name|nav_view
operator|->
name|has_grab
condition|)
block|{
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|nav_view
operator|->
name|p_x
operator|==
literal|0
operator|&&
name|nav_view
operator|->
name|p_y
operator|==
literal|0
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
name|mevent
operator|->
name|x
operator|>=
name|nav_view
operator|->
name|p_x
operator|&&
name|mevent
operator|->
name|y
operator|>=
name|nav_view
operator|->
name|p_y
operator|&&
name|mevent
operator|->
name|x
operator|<
name|nav_view
operator|->
name|p_x
operator|+
name|nav_view
operator|->
name|p_width
operator|&&
name|mevent
operator|->
name|y
operator|<
name|nav_view
operator|->
name|p_y
operator|+
name|nav_view
operator|->
name|p_height
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
name|gdk_cursor_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gdk_window_get_pointer
argument_list|(
name|view
operator|->
name|event_window
argument_list|,
operator|&
name|tx
argument_list|,
operator|&
name|ty
argument_list|,
operator|&
name|mask
argument_list|)
expr_stmt|;
name|tx
operator|-=
name|nav_view
operator|->
name|motion_offset_x
expr_stmt|;
name|ty
operator|-=
name|nav_view
operator|->
name|motion_offset_y
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
name|GDK_Up
case|:
name|scroll_y
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_Left
case|:
name|scroll_x
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_Right
case|:
name|scroll_x
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GDK_Down
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
name|p_x
operator|+
name|scroll_x
argument_list|,
name|nav_view
operator|->
name|p_y
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
name|gdouble
name|ratiox
decl_stmt|,
name|ratioy
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
name|ratiox
operator|=
operator|(
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
name|image
operator|->
name|width
operator|)
expr_stmt|;
name|ratioy
operator|=
operator|(
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
name|image
operator|->
name|height
operator|)
expr_stmt|;
name|nav_view
operator|->
name|p_x
operator|=
name|RINT
argument_list|(
name|nav_view
operator|->
name|x
operator|*
name|ratiox
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|p_y
operator|=
name|RINT
argument_list|(
name|nav_view
operator|->
name|y
operator|*
name|ratioy
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|p_width
operator|=
name|RINT
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
name|RINT
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
DECL|function|gimp_navigation_view_draw_marker (GimpNavigationView * nav_view,GdkRectangle * area)
name|gimp_navigation_view_draw_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
parameter_list|,
name|GdkRectangle
modifier|*
name|area
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
if|if
condition|(
name|nav_view
operator|->
name|x
operator|>
literal|0
operator|||
name|nav_view
operator|->
name|y
operator|>
literal|0
operator|||
name|nav_view
operator|->
name|width
operator|<
name|image
operator|->
name|width
operator|||
name|nav_view
operator|->
name|height
operator|<
name|image
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
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|nav_view
operator|->
name|gc
argument_list|,
name|area
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|nav_view
operator|->
name|gc
argument_list|,
name|FALSE
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|x
operator|+
name|nav_view
operator|->
name|p_x
operator|+
literal|1
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|y
operator|+
name|nav_view
operator|->
name|p_y
operator|+
literal|1
argument_list|,
name|MAX
argument_list|(
literal|1
argument_list|,
name|nav_view
operator|->
name|p_width
operator|-
name|BORDER_PEN_WIDTH
argument_list|)
argument_list|,
name|MAX
argument_list|(
literal|1
argument_list|,
name|nav_view
operator|->
name|p_height
operator|-
name|BORDER_PEN_WIDTH
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|nav_view
operator|->
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_navigation_view_set_marker (GimpNavigationView * nav_view,gdouble x,gdouble y,gdouble width,gdouble height)
name|gimp_navigation_view_set_marker
parameter_list|(
name|GimpNavigationView
modifier|*
name|nav_view
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
parameter_list|)
block|{
name|GimpView
modifier|*
name|view
decl_stmt|;
name|GimpImage
modifier|*
name|image
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
comment|/*  remove old marker  */
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|view
argument_list|)
condition|)
name|gimp_navigation_view_draw_marker
argument_list|(
name|nav_view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0.0
argument_list|,
name|image
operator|->
name|width
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0.0
argument_list|,
name|image
operator|->
name|height
operator|-
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|<
literal|0.0
condition|)
name|width
operator|=
name|image
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|height
operator|<
literal|0.0
condition|)
name|height
operator|=
name|image
operator|->
name|height
expr_stmt|;
name|nav_view
operator|->
name|width
operator|=
name|CLAMP
argument_list|(
name|width
argument_list|,
literal|1.0
argument_list|,
name|image
operator|->
name|width
operator|-
name|nav_view
operator|->
name|x
argument_list|)
expr_stmt|;
name|nav_view
operator|->
name|height
operator|=
name|CLAMP
argument_list|(
name|height
argument_list|,
literal|1.0
argument_list|,
name|image
operator|->
name|height
operator|-
name|nav_view
operator|->
name|y
argument_list|)
expr_stmt|;
name|gimp_navigation_view_transform
argument_list|(
name|nav_view
argument_list|)
expr_stmt|;
comment|/*  draw new marker  */
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|view
argument_list|)
condition|)
name|gimp_navigation_view_draw_marker
argument_list|(
name|nav_view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

