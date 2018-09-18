begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcircle.c  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * Based on code from the color-rotate plug-in  * Copyright (C) 1997-1999 Sven Anders (anderss@fmi.uni-passau.de)  *                         Based on code from Pavel Grinfeld (pavel@ml.com)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcircle.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b5429520103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SIZE
name|PROP_SIZE
block|,
DECL|enumerator|PROP_BORDER_WIDTH
name|PROP_BORDER_WIDTH
block|,
DECL|enumerator|PROP_BACKGROUND
name|PROP_BACKGROUND
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpCirclePrivate
struct|struct
name|_GimpCirclePrivate
block|{
DECL|member|size
name|gint
name|size
decl_stmt|;
DECL|member|border_width
name|gint
name|border_width
decl_stmt|;
DECL|member|background
name|GimpCircleBackground
name|background
decl_stmt|;
DECL|member|event_window
name|GdkWindow
modifier|*
name|event_window
decl_stmt|;
DECL|member|surface
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
DECL|member|has_grab
name|gboolean
name|has_grab
decl_stmt|;
DECL|member|in_widget
name|gboolean
name|in_widget
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_circle_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_realize
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
name|gimp_circle_unrealize
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
name|gimp_circle_map
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
name|gimp_circle_unmap
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
name|gimp_circle_get_preferred_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_get_preferred_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_size_allocate
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
name|gimp_circle_draw
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
name|gimp_circle_button_press_event
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
name|gimp_circle_button_release_event
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
name|gimp_circle_enter_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventCrossing
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_circle_leave_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventCrossing
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_real_reset_target
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_background_hsv
parameter_list|(
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|distance
parameter_list|,
name|guchar
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_circle_draw_background
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|size
parameter_list|,
name|GimpCircleBackground
name|background
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpCircle,gimp_circle,GTK_TYPE_WIDGET)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpCircle
argument_list|,
argument|gimp_circle
argument_list|,
argument|GTK_TYPE_WIDGET
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_circle_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_circle_class_init
parameter_list|(
name|GimpCircleClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_circle_dispose
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_circle_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_circle_set_property
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_circle_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_circle_unrealize
expr_stmt|;
name|widget_class
operator|->
name|map
operator|=
name|gimp_circle_map
expr_stmt|;
name|widget_class
operator|->
name|unmap
operator|=
name|gimp_circle_unmap
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_width
operator|=
name|gimp_circle_get_preferred_width
expr_stmt|;
name|widget_class
operator|->
name|get_preferred_height
operator|=
name|gimp_circle_get_preferred_height
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_circle_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|draw
operator|=
name|gimp_circle_draw
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_circle_button_press_event
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_circle_button_release_event
expr_stmt|;
name|widget_class
operator|->
name|enter_notify_event
operator|=
name|gimp_circle_enter_notify_event
expr_stmt|;
name|widget_class
operator|->
name|leave_notify_event
operator|=
name|gimp_circle_leave_notify_event
expr_stmt|;
name|klass
operator|->
name|reset_target
operator|=
name|gimp_circle_real_reset_target
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|32
argument_list|,
literal|1024
argument_list|,
literal|96
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BORDER_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"border-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|64
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BACKGROUND
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"background"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CIRCLE_BACKGROUND
argument_list|,
name|GIMP_CIRCLE_BACKGROUND_HSV
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_init (GimpCircle * circle)
name|gimp_circle_init
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|)
block|{
name|circle
operator|->
name|priv
operator|=
name|gimp_circle_get_instance_private
argument_list|(
name|circle
argument_list|)
expr_stmt|;
name|gtk_widget_set_has_window
argument_list|(
name|GTK_WIDGET
argument_list|(
name|circle
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|circle
argument_list|)
argument_list|,
name|GDK_POINTER_MOTION_MASK
operator||
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_dispose (GObject * object)
name|gimp_circle_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|circle
operator|->
name|priv
operator|->
name|surface
argument_list|,
name|cairo_surface_destroy
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_circle_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SIZE
case|:
name|circle
operator|->
name|priv
operator|->
name|size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|circle
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BORDER_WIDTH
case|:
name|circle
operator|->
name|priv
operator|->
name|border_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|circle
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BACKGROUND
case|:
name|circle
operator|->
name|priv
operator|->
name|background
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|circle
operator|->
name|priv
operator|->
name|surface
argument_list|,
name|cairo_surface_destroy
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|circle
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_circle_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|circle
operator|->
name|priv
operator|->
name|size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BORDER_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|circle
operator|->
name|priv
operator|->
name|border_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BACKGROUND
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|circle
operator|->
name|priv
operator|->
name|background
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_realize (GtkWidget * widget)
name|gimp_circle_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|GdkWindowAttr
name|attributes
decl_stmt|;
name|gint
name|attributes_mask
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
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|attributes
operator|.
name|window_type
operator|=
name|GDK_WINDOW_CHILD
expr_stmt|;
name|attributes
operator|.
name|x
operator|=
name|allocation
operator|.
name|x
expr_stmt|;
name|attributes
operator|.
name|y
operator|=
name|allocation
operator|.
name|y
expr_stmt|;
name|attributes
operator|.
name|width
operator|=
name|allocation
operator|.
name|width
expr_stmt|;
name|attributes
operator|.
name|height
operator|=
name|allocation
operator|.
name|height
expr_stmt|;
name|attributes
operator|.
name|wclass
operator|=
name|GDK_INPUT_ONLY
expr_stmt|;
name|attributes
operator|.
name|event_mask
operator|=
name|gtk_widget_get_events
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|attributes_mask
operator|=
name|GDK_WA_X
operator||
name|GDK_WA_Y
expr_stmt|;
name|circle
operator|->
name|priv
operator|->
name|event_window
operator|=
name|gdk_window_new
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|attributes
argument_list|,
name|attributes_mask
argument_list|)
expr_stmt|;
name|gdk_window_set_user_data
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|event_window
argument_list|,
name|circle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_unrealize (GtkWidget * widget)
name|gimp_circle_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|circle
operator|->
name|priv
operator|->
name|event_window
condition|)
block|{
name|gdk_window_set_user_data
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|event_window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_destroy
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|event_window
argument_list|)
expr_stmt|;
name|circle
operator|->
name|priv
operator|->
name|event_window
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
DECL|function|gimp_circle_map (GtkWidget * widget)
name|gimp_circle_map
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|map
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|circle
operator|->
name|priv
operator|->
name|event_window
condition|)
name|gdk_window_show
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|event_window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_unmap (GtkWidget * widget)
name|gimp_circle_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|circle
operator|->
name|priv
operator|->
name|has_grab
condition|)
block|{
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|circle
operator|->
name|priv
operator|->
name|has_grab
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|circle
operator|->
name|priv
operator|->
name|event_window
condition|)
name|gdk_window_hide
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|event_window
argument_list|)
expr_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|unmap
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_get_preferred_width (GtkWidget * widget,gint * minimum_width,gint * natural_width)
name|gimp_circle_get_preferred_width
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_width
parameter_list|,
name|gint
modifier|*
name|natural_width
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
operator|*
name|minimum_width
operator|=
operator|*
name|natural_width
operator|=
literal|2
operator|*
name|circle
operator|->
name|priv
operator|->
name|border_width
operator|+
name|circle
operator|->
name|priv
operator|->
name|size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_get_preferred_height (GtkWidget * widget,gint * minimum_height,gint * natural_height)
name|gimp_circle_get_preferred_height
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
modifier|*
name|minimum_height
parameter_list|,
name|gint
modifier|*
name|natural_height
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
operator|*
name|minimum_height
operator|=
operator|*
name|natural_height
operator|=
literal|2
operator|*
name|circle
operator|->
name|priv
operator|->
name|border_width
operator|+
name|circle
operator|->
name|priv
operator|->
name|size
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_circle_size_allocate
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
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
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
name|gtk_widget_get_realized
argument_list|(
name|widget
argument_list|)
condition|)
name|gdk_window_move_resize
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|event_window
argument_list|,
name|allocation
operator|->
name|x
argument_list|,
name|allocation
operator|->
name|y
argument_list|,
name|allocation
operator|->
name|width
argument_list|,
name|allocation
operator|->
name|height
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|circle
operator|->
name|priv
operator|->
name|surface
argument_list|,
name|cairo_surface_destroy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_circle_draw (GtkWidget * widget,cairo_t * cr)
name|gimp_circle_draw
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
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|size
init|=
name|circle
operator|->
name|priv
operator|->
name|size
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
operator|(
name|allocation
operator|.
name|width
operator|-
name|size
operator|)
operator|/
literal|2
argument_list|,
operator|(
name|allocation
operator|.
name|height
operator|-
name|size
operator|)
operator|/
literal|2
argument_list|)
expr_stmt|;
name|gimp_circle_draw_background
argument_list|(
name|circle
argument_list|,
name|cr
argument_list|,
name|size
argument_list|,
name|circle
operator|->
name|priv
operator|->
name|background
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_circle_button_press_event (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_circle_button_press_event
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
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
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
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|circle
operator|->
name|priv
operator|->
name|has_grab
operator|=
name|TRUE
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_circle_button_release_event (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_circle_button_release_event
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
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
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
condition|)
block|{
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|circle
operator|->
name|priv
operator|->
name|has_grab
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|circle
operator|->
name|priv
operator|->
name|in_widget
condition|)
name|GIMP_CIRCLE_GET_CLASS
argument_list|(
name|circle
argument_list|)
operator|->
name|reset_target
argument_list|(
name|circle
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_circle_enter_notify_event (GtkWidget * widget,GdkEventCrossing * event)
name|gimp_circle_enter_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventCrossing
modifier|*
name|event
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|circle
operator|->
name|priv
operator|->
name|in_widget
operator|=
name|TRUE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_circle_leave_notify_event (GtkWidget * widget,GdkEventCrossing * event)
name|gimp_circle_leave_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventCrossing
modifier|*
name|event
parameter_list|)
block|{
name|GimpCircle
modifier|*
name|circle
init|=
name|GIMP_CIRCLE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|circle
operator|->
name|priv
operator|->
name|in_widget
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|!
name|circle
operator|->
name|priv
operator|->
name|has_grab
condition|)
name|GIMP_CIRCLE_GET_CLASS
argument_list|(
name|circle
argument_list|)
operator|->
name|reset_target
argument_list|(
name|circle
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_real_reset_target (GimpCircle * circle)
name|gimp_circle_real_reset_target
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_circle_new (void)
name|gimp_circle_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CIRCLE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  protected functions  */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|get_angle_and_distance (gdouble center_x,gdouble center_y,gdouble radius,gdouble x,gdouble y,gdouble * distance)
name|get_angle_and_distance
parameter_list|(
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|distance
parameter_list|)
block|{
name|gdouble
name|angle
init|=
name|atan2
argument_list|(
name|center_y
operator|-
name|y
argument_list|,
name|x
operator|-
name|center_x
argument_list|)
decl_stmt|;
if|if
condition|(
name|angle
operator|<
literal|0
condition|)
name|angle
operator|+=
literal|2
operator|*
name|G_PI
expr_stmt|;
if|if
condition|(
name|distance
condition|)
operator|*
name|distance
operator|=
name|sqrt
argument_list|(
operator|(
name|SQR
argument_list|(
name|x
operator|-
name|center_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
operator|-
name|center_y
argument_list|)
operator|)
operator|/
name|SQR
argument_list|(
name|radius
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|angle
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|_gimp_circle_has_grab (GimpCircle * circle)
name|_gimp_circle_has_grab
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CIRCLE
argument_list|(
name|circle
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|circle
operator|->
name|priv
operator|->
name|has_grab
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|_gimp_circle_get_angle_and_distance (GimpCircle * circle,gdouble event_x,gdouble event_y,gdouble * distance)
name|_gimp_circle_get_angle_and_distance
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|,
name|gdouble
name|event_x
parameter_list|,
name|gdouble
name|event_y
parameter_list|,
name|gdouble
modifier|*
name|distance
parameter_list|)
block|{
name|GtkAllocation
name|allocation
decl_stmt|;
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CIRCLE
argument_list|(
name|circle
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|GTK_WIDGET
argument_list|(
name|circle
argument_list|)
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|center_x
operator|=
name|allocation
operator|.
name|width
operator|/
literal|2.0
expr_stmt|;
name|center_y
operator|=
name|allocation
operator|.
name|height
operator|/
literal|2.0
expr_stmt|;
return|return
name|get_angle_and_distance
argument_list|(
name|center_x
argument_list|,
name|center_y
argument_list|,
name|circle
operator|->
name|priv
operator|->
name|size
operator|/
literal|2.0
argument_list|,
name|event_x
argument_list|,
name|event_y
argument_list|,
name|distance
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_circle_background_hsv (gdouble angle,gdouble distance,guchar * rgb)
name|gimp_circle_background_hsv
parameter_list|(
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|distance
parameter_list|,
name|guchar
modifier|*
name|rgb
parameter_list|)
block|{
name|GimpHSV
name|hsv
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_hsv_set
argument_list|(
operator|&
name|hsv
argument_list|,
name|angle
operator|/
operator|(
literal|2.0
operator|*
name|G_PI
operator|)
argument_list|,
name|distance
argument_list|,
literal|1
operator|-
name|sqrt
argument_list|(
name|distance
argument_list|)
operator|/
literal|4
comment|/* it just looks nicer this way */
argument_list|)
expr_stmt|;
name|gimp_hsv_to_rgb
argument_list|(
operator|&
name|hsv
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|rgb
argument_list|,
name|rgb
operator|+
literal|1
argument_list|,
name|rgb
operator|+
literal|2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_circle_draw_background (GimpCircle * circle,cairo_t * cr,gint size,GimpCircleBackground background)
name|gimp_circle_draw_background
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|size
parameter_list|,
name|GimpCircleBackground
name|background
parameter_list|)
block|{
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|background
operator|==
name|GIMP_CIRCLE_BACKGROUND_PLAIN
condition|)
block|{
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
name|size
operator|/
literal|2.0
operator|-
literal|1.5
argument_list|,
literal|0.0
argument_list|,
literal|2
operator|*
name|G_PI
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|3.0
argument_list|)
expr_stmt|;
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.6
argument_list|)
expr_stmt|;
name|cairo_stroke_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.8
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|circle
operator|->
name|priv
operator|->
name|surface
condition|)
block|{
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|stride
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|circle
operator|->
name|priv
operator|->
name|surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|size
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|data
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|surface
argument_list|)
expr_stmt|;
name|stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|surface
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|size
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|size
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|distance
decl_stmt|;
name|guchar
name|rgb
index|[
literal|3
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|angle
operator|=
name|get_angle_and_distance
argument_list|(
name|size
operator|/
literal|2.0
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|distance
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|background
condition|)
block|{
case|case
name|GIMP_CIRCLE_BACKGROUND_HSV
case|:
name|gimp_circle_background_hsv
argument_list|(
name|angle
argument_list|,
name|distance
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|data
operator|+
name|y
operator|*
name|stride
operator|+
name|x
operator|*
literal|4
argument_list|,
name|rgb
index|[
literal|0
index|]
argument_list|,
name|rgb
index|[
literal|1
index|]
argument_list|,
name|rgb
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
block|}
name|cairo_surface_mark_dirty
argument_list|(
name|circle
operator|->
name|priv
operator|->
name|surface
argument_list|)
expr_stmt|;
block|}
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|circle
operator|->
name|priv
operator|->
name|surface
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
literal|0.0
argument_list|,
literal|2
operator|*
name|G_PI
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

