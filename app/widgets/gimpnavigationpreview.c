begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpNavigationPreview Widget  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/temp-buf.h"
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
file|"gimpnavigationpreview.h"
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
DECL|enum|__anon29d2b9ca0103
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
name|gimp_navigation_preview_class_init
parameter_list|(
name|GimpNavigationPreviewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_preview_init
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_preview_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_preview_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_navigation_preview_expose
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
name|gimp_navigation_preview_button_press
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
name|gimp_navigation_preview_button_release
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
name|gimp_navigation_preview_scroll
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
name|gimp_navigation_preview_motion_notify
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
name|gimp_navigation_preview_key_press
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
name|gimp_navigation_preview_render
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_navigation_preview_draw_marker
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|nav_preview
parameter_list|,
name|GdkRectangle
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|preview_signals
specifier|static
name|guint
name|preview_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImagePreviewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_navigation_preview_get_type (void)
name|gimp_navigation_preview_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|preview_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|preview_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|preview_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpNavigationPreviewClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_navigation_preview_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpNavigationPreview
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_navigation_preview_init
block|,       }
decl_stmt|;
name|preview_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_PREVIEW
argument_list|,
literal|"GimpNavigationPreview"
argument_list|,
operator|&
name|preview_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|preview_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_preview_class_init (GimpNavigationPreviewClass * klass)
name|gimp_navigation_preview_class_init
parameter_list|(
name|GimpNavigationPreviewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|GimpPreviewClass
modifier|*
name|preview_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|preview_class
operator|=
name|GIMP_PREVIEW_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|preview_signals
index|[
name|MARKER_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"marker_changed"
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
name|GimpNavigationPreviewClass
argument_list|,
name|marker_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|preview_signals
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
name|GimpNavigationPreviewClass
argument_list|,
name|zoom
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|preview_signals
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
name|GimpNavigationPreviewClass
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
name|object_class
operator|->
name|destroy
operator|=
name|gimp_navigation_preview_destroy
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_navigation_preview_realize
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_navigation_preview_expose
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_navigation_preview_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_navigation_preview_button_release
expr_stmt|;
name|widget_class
operator|->
name|scroll_event
operator|=
name|gimp_navigation_preview_scroll
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_navigation_preview_motion_notify
expr_stmt|;
name|widget_class
operator|->
name|key_press_event
operator|=
name|gimp_navigation_preview_key_press
expr_stmt|;
name|preview_class
operator|->
name|render
operator|=
name|gimp_navigation_preview_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_preview_init (GimpNavigationPreview * preview)
name|gimp_navigation_preview_init
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|preview
argument_list|,
name|GTK_CAN_FOCUS
argument_list|)
expr_stmt|;
name|preview
operator|->
name|x
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|y
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|p_x
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|p_y
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|p_width
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|p_height
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|motion_offset_x
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|motion_offset_y
operator|=
literal|0
expr_stmt|;
name|preview
operator|->
name|has_grab
operator|=
name|FALSE
expr_stmt|;
name|preview
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
DECL|function|gimp_navigation_preview_destroy (GtkObject * object)
name|gimp_navigation_preview_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpNavigationPreview
modifier|*
name|nav_preview
decl_stmt|;
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|nav_preview
operator|->
name|gc
condition|)
block|{
name|g_object_unref
argument_list|(
name|nav_preview
operator|->
name|gc
argument_list|)
expr_stmt|;
name|nav_preview
operator|->
name|gc
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_preview_realize (GtkWidget * widget)
name|gimp_navigation_preview_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpNavigationPreview
modifier|*
name|nav_preview
decl_stmt|;
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
condition|)
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
name|nav_preview
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
name|nav_preview
operator|->
name|gc
argument_list|,
name|GDK_INVERT
argument_list|)
expr_stmt|;
name|gdk_gc_set_line_attributes
argument_list|(
name|nav_preview
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
name|gboolean
DECL|function|gimp_navigation_preview_expose (GtkWidget * widget,GdkEventExpose * eevent)
name|gimp_navigation_preview_expose
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
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|expose_event
condition|)
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
name|gimp_navigation_preview_draw_marker
argument_list|(
name|GIMP_NAVIGATION_PREVIEW
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
DECL|function|gimp_navigation_preview_move_to (GimpNavigationPreview * nav_preview,gint tx,gint ty)
name|gimp_navigation_preview_move_to
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|nav_preview
parameter_list|,
name|gint
name|tx
parameter_list|,
name|gint
name|ty
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gdouble
name|ratiox
decl_stmt|,
name|ratioy
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|preview
operator|=
name|GIMP_PREVIEW
argument_list|(
name|nav_preview
argument_list|)
expr_stmt|;
name|tx
operator|=
name|CLAMP
argument_list|(
name|tx
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|width
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
name|preview
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|tx
operator|+
name|nav_preview
operator|->
name|p_width
operator|)
operator|>=
name|preview
operator|->
name|width
condition|)
block|{
name|tx
operator|=
name|preview
operator|->
name|width
operator|-
name|nav_preview
operator|->
name|p_width
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|ty
operator|+
name|nav_preview
operator|->
name|p_height
operator|)
operator|>=
name|preview
operator|->
name|height
condition|)
block|{
name|ty
operator|=
name|preview
operator|->
name|height
operator|-
name|nav_preview
operator|->
name|p_height
expr_stmt|;
block|}
if|if
condition|(
name|nav_preview
operator|->
name|p_x
operator|==
name|tx
operator|&&
name|nav_preview
operator|->
name|p_y
operator|==
name|ty
condition|)
return|return;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
comment|/*  transform to image coordinates  */
name|ratiox
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|preview
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|gimage
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
name|preview
operator|->
name|height
operator|/
operator|(
name|gdouble
operator|)
name|gimage
operator|->
name|height
operator|)
expr_stmt|;
name|x
operator|=
name|RINT
argument_list|(
name|tx
operator|/
name|ratiox
argument_list|)
expr_stmt|;
name|y
operator|=
name|RINT
argument_list|(
name|ty
operator|/
name|ratioy
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
name|preview_signals
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
specifier|static
name|void
DECL|function|gimp_navigation_preview_grab_pointer (GimpNavigationPreview * nav_preview)
name|gimp_navigation_preview_grab_pointer
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|nav_preview
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|nav_preview
argument_list|)
expr_stmt|;
name|nav_preview
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
name|cursor
operator|=
name|gdk_cursor_new
argument_list|(
name|GDK_CROSSHAIR
argument_list|)
expr_stmt|;
name|gdk_pointer_grab
argument_list|(
name|widget
operator|->
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
name|widget
operator|->
name|window
argument_list|,
name|cursor
argument_list|,
literal|0
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
DECL|function|gimp_navigation_preview_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_navigation_preview_button_press
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
name|GimpNavigationPreview
modifier|*
name|nav_preview
decl_stmt|;
name|gint
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|widget
argument_list|)
expr_stmt|;
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
name|nav_preview
operator|->
name|p_x
operator|&&
name|tx
operator|<
operator|(
name|nav_preview
operator|->
name|p_x
operator|+
name|nav_preview
operator|->
name|p_width
operator|)
operator|&&
name|ty
operator|>
name|nav_preview
operator|->
name|p_y
operator|&&
name|ty
operator|<
operator|(
name|nav_preview
operator|->
name|p_y
operator|+
name|nav_preview
operator|->
name|p_height
operator|)
operator|)
condition|)
block|{
name|nav_preview
operator|->
name|motion_offset_x
operator|=
name|nav_preview
operator|->
name|p_width
operator|/
literal|2
expr_stmt|;
name|nav_preview
operator|->
name|motion_offset_y
operator|=
name|nav_preview
operator|->
name|p_height
operator|/
literal|2
expr_stmt|;
name|tx
operator|-=
name|nav_preview
operator|->
name|motion_offset_x
expr_stmt|;
name|ty
operator|-=
name|nav_preview
operator|->
name|motion_offset_y
expr_stmt|;
name|gimp_navigation_preview_move_to
argument_list|(
name|nav_preview
argument_list|,
name|tx
argument_list|,
name|ty
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|nav_preview
operator|->
name|motion_offset_x
operator|=
name|tx
operator|-
name|nav_preview
operator|->
name|p_x
expr_stmt|;
name|nav_preview
operator|->
name|motion_offset_y
operator|=
name|ty
operator|-
name|nav_preview
operator|->
name|p_y
expr_stmt|;
block|}
name|gimp_navigation_preview_grab_pointer
argument_list|(
name|nav_preview
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
DECL|function|gimp_navigation_preview_button_release (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_navigation_preview_button_release
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
name|GimpNavigationPreview
modifier|*
name|nav_preview
decl_stmt|;
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|widget
argument_list|)
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
name|nav_preview
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
name|gdk_pointer_ungrab
argument_list|(
literal|0
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
DECL|function|gimp_navigation_preview_scroll (GtkWidget * widget,GdkEventScroll * sevent)
name|gimp_navigation_preview_scroll
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
name|GimpNavigationPreview
modifier|*
name|nav_preview
decl_stmt|;
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"gimp_navigation_preview_scroll(%d)\n"
argument_list|,
name|sevent
operator|->
name|direction
argument_list|)
expr_stmt|;
if|if
condition|(
name|sevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
if|if
condition|(
name|sevent
operator|->
name|direction
operator|==
name|GDK_SCROLL_UP
condition|)
block|{
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|preview_signals
index|[
name|ZOOM
index|]
argument_list|,
literal|0
argument_list|,
name|GIMP_ZOOM_IN
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|preview_signals
index|[
name|ZOOM
index|]
argument_list|,
literal|0
argument_list|,
name|GIMP_ZOOM_OUT
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GdkScrollDirection
name|direction
decl_stmt|;
if|if
condition|(
name|sevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
if|if
condition|(
name|sevent
operator|->
name|direction
operator|==
name|GDK_SCROLL_UP
condition|)
name|direction
operator|=
name|GDK_SCROLL_LEFT
expr_stmt|;
else|else
name|direction
operator|=
name|GDK_SCROLL_RIGHT
expr_stmt|;
block|}
else|else
block|{
name|direction
operator|=
name|sevent
operator|->
name|direction
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|preview_signals
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
DECL|function|gimp_navigation_preview_motion_notify (GtkWidget * widget,GdkEventMotion * mevent)
name|gimp_navigation_preview_motion_notify
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
name|GimpNavigationPreview
modifier|*
name|nav_preview
decl_stmt|;
name|gint
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|GdkModifierType
name|mask
decl_stmt|;
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|nav_preview
operator|->
name|has_grab
condition|)
return|return
name|FALSE
return|;
name|gdk_window_get_pointer
argument_list|(
name|widget
operator|->
name|window
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
name|nav_preview
operator|->
name|motion_offset_x
expr_stmt|;
name|ty
operator|-=
name|nav_preview
operator|->
name|motion_offset_y
expr_stmt|;
name|gimp_navigation_preview_move_to
argument_list|(
name|nav_preview
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
DECL|function|gimp_navigation_preview_key_press (GtkWidget * widget,GdkEventKey * kevent)
name|gimp_navigation_preview_key_press
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
name|GimpNavigationPreview
modifier|*
name|nav_preview
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
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|widget
argument_list|)
expr_stmt|;
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
name|gimp_navigation_preview_move_to
argument_list|(
name|nav_preview
argument_list|,
name|nav_preview
operator|->
name|p_x
operator|+
name|scroll_x
argument_list|,
name|nav_preview
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
DECL|function|gimp_navigation_preview_render (GimpPreview * preview)
name|gimp_navigation_preview_render
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpNavigationPreview
modifier|*
name|nav_preview
decl_stmt|;
name|nav_preview
operator|=
name|GIMP_NAVIGATION_PREVIEW
argument_list|(
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_PREVIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|render
condition|)
name|GIMP_PREVIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|render
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_navigation_preview_draw_marker (GimpNavigationPreview * nav_preview,GdkRectangle * area)
name|gimp_navigation_preview_draw_marker
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|nav_preview
parameter_list|,
name|GdkRectangle
modifier|*
name|area
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|preview
operator|=
name|GIMP_PREVIEW
argument_list|(
name|nav_preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
operator|->
name|viewable
operator|&&
name|nav_preview
operator|->
name|width
operator|&&
name|nav_preview
operator|->
name|height
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|nav_preview
operator|->
name|x
operator|>
literal|0
operator|||
name|nav_preview
operator|->
name|y
operator|>
literal|0
operator|||
name|nav_preview
operator|->
name|width
operator|<
name|gimage
operator|->
name|width
operator|||
name|nav_preview
operator|->
name|height
operator|<
name|gimage
operator|->
name|height
condition|)
block|{
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|nav_preview
operator|->
name|gc
argument_list|,
name|area
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
operator|->
name|window
argument_list|,
name|nav_preview
operator|->
name|gc
argument_list|,
name|FALSE
argument_list|,
name|nav_preview
operator|->
name|p_x
argument_list|,
name|nav_preview
operator|->
name|p_y
argument_list|,
name|nav_preview
operator|->
name|p_width
operator|-
name|BORDER_PEN_WIDTH
operator|+
literal|1
argument_list|,
name|nav_preview
operator|->
name|p_height
operator|-
name|BORDER_PEN_WIDTH
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|nav_preview
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
name|GtkWidget
modifier|*
DECL|function|gimp_navigation_preview_new (GimpImage * gimage,gint size)
name|gimp_navigation_preview_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|>
literal|0
operator|&&
name|size
operator|<=
literal|256
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|preview
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_NAVIGATION_PREVIEW
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|preview
operator|->
name|is_popup
operator|=
name|TRUE
expr_stmt|;
name|gimp_preview_set_viewable
argument_list|(
name|preview
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_preview_set_size
argument_list|(
name|preview
argument_list|,
name|size
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_navigation_preview_set_marker (GimpNavigationPreview * nav_preview,gint x,gint y,gint width,gint height)
name|gimp_navigation_preview_set_marker
parameter_list|(
name|GimpNavigationPreview
modifier|*
name|nav_preview
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
block|{
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gdouble
name|ratiox
decl_stmt|,
name|ratioy
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|nav_preview
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_NAVIGATION_PREVIEW
argument_list|(
name|nav_preview
argument_list|)
argument_list|)
expr_stmt|;
name|preview
operator|=
name|GIMP_PREVIEW
argument_list|(
name|nav_preview
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
comment|/*  remove old marker  */
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|preview
argument_list|)
condition|)
name|gimp_navigation_preview_draw_marker
argument_list|(
name|nav_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|nav_preview
operator|->
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|nav_preview
operator|->
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|==
operator|-
literal|1
condition|)
name|width
operator|=
name|gimage
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|height
operator|==
operator|-
literal|1
condition|)
name|height
operator|=
name|gimage
operator|->
name|height
expr_stmt|;
name|nav_preview
operator|->
name|width
operator|=
name|CLAMP
argument_list|(
name|width
argument_list|,
literal|1
argument_list|,
name|gimage
operator|->
name|width
operator|-
name|nav_preview
operator|->
name|x
argument_list|)
expr_stmt|;
name|nav_preview
operator|->
name|height
operator|=
name|CLAMP
argument_list|(
name|height
argument_list|,
literal|1
argument_list|,
name|gimage
operator|->
name|height
operator|-
name|nav_preview
operator|->
name|y
argument_list|)
expr_stmt|;
comment|/*  transform to preview coordinates  */
name|ratiox
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|preview
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|gimage
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
name|preview
operator|->
name|height
operator|/
operator|(
name|gdouble
operator|)
name|gimage
operator|->
name|height
operator|)
expr_stmt|;
name|nav_preview
operator|->
name|p_x
operator|=
name|RINT
argument_list|(
name|nav_preview
operator|->
name|x
operator|*
name|ratiox
argument_list|)
expr_stmt|;
name|nav_preview
operator|->
name|p_y
operator|=
name|RINT
argument_list|(
name|nav_preview
operator|->
name|y
operator|*
name|ratioy
argument_list|)
expr_stmt|;
name|nav_preview
operator|->
name|p_width
operator|=
name|RINT
argument_list|(
name|nav_preview
operator|->
name|width
operator|*
name|ratiox
argument_list|)
expr_stmt|;
name|nav_preview
operator|->
name|p_height
operator|=
name|RINT
argument_list|(
name|nav_preview
operator|->
name|height
operator|*
name|ratioy
argument_list|)
expr_stmt|;
comment|/*  draw new marker  */
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|preview
argument_list|)
condition|)
name|gimp_navigation_preview_draw_marker
argument_list|(
name|nav_preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

