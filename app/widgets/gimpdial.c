begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdial.c  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * Based on code from the color-rotate plug-in  * Copyright (C) 1997-1999 Sven Anders (anderss@fmi.uni-passau.de)  *                         Based on code from Pavel Grinfeld (pavel@ml.com)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimp-cairo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdial.h"
end_include

begin_define
DECL|macro|SEGMENT_FRACTION
define|#
directive|define
name|SEGMENT_FRACTION
value|0.3
end_define

begin_enum
enum|enum
DECL|enum|__anon2c15c7870103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DRAW_BETA
name|PROP_DRAW_BETA
block|,
DECL|enumerator|PROP_ALPHA
name|PROP_ALPHA
block|,
DECL|enumerator|PROP_BETA
name|PROP_BETA
block|,
DECL|enumerator|PROP_CLOCKWISE
name|PROP_CLOCKWISE
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c15c7870203
block|{
DECL|enumerator|DIAL_TARGET_NONE
name|DIAL_TARGET_NONE
init|=
literal|0
block|,
DECL|enumerator|DIAL_TARGET_ALPHA
name|DIAL_TARGET_ALPHA
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|DIAL_TARGET_BETA
name|DIAL_TARGET_BETA
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|DIAL_TARGET_BOTH
name|DIAL_TARGET_BOTH
init|=
name|DIAL_TARGET_ALPHA
operator||
name|DIAL_TARGET_BETA
DECL|typedef|DialTarget
block|}
name|DialTarget
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDialPrivate
struct|struct
name|_GimpDialPrivate
block|{
DECL|member|alpha
name|gdouble
name|alpha
decl_stmt|;
DECL|member|beta
name|gdouble
name|beta
decl_stmt|;
DECL|member|clockwise
name|gboolean
name|clockwise
decl_stmt|;
DECL|member|draw_beta
name|gboolean
name|draw_beta
decl_stmt|;
DECL|member|target
name|DialTarget
name|target
decl_stmt|;
DECL|member|last_angle
name|gdouble
name|last_angle
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
name|gimp_dial_set_property
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
name|gimp_dial_get_property
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
name|gimp_dial_unmap
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
name|gimp_dial_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dial_button_press_event
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
name|gimp_dial_button_release_event
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
name|gimp_dial_motion_notify_event
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
name|gimp_dial_enter_notify_event
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
name|gimp_dial_leave_notify_event
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
name|gimp_dial_draw_arrows
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|size
parameter_list|,
name|gdouble
name|alpha
parameter_list|,
name|gdouble
name|beta
parameter_list|,
name|gboolean
name|clockwise
parameter_list|,
name|DialTarget
name|highlight
parameter_list|,
name|gboolean
name|draw_beta
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDial,gimp_dial,GIMP_TYPE_CIRCLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDial
argument_list|,
argument|gimp_dial
argument_list|,
argument|GIMP_TYPE_CIRCLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dial_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dial_class_init
parameter_list|(
name|GimpDialClass
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
name|get_property
operator|=
name|gimp_dial_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dial_set_property
expr_stmt|;
name|widget_class
operator|->
name|unmap
operator|=
name|gimp_dial_unmap
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_dial_expose_event
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_dial_button_press_event
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_dial_button_release_event
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_dial_motion_notify_event
expr_stmt|;
name|widget_class
operator|->
name|enter_notify_event
operator|=
name|gimp_dial_enter_notify_event
expr_stmt|;
name|widget_class
operator|->
name|leave_notify_event
operator|=
name|gimp_dial_leave_notify_event
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ALPHA
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"alpha"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2
operator|*
name|G_PI
argument_list|,
literal|0.0
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
name|PROP_BETA
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"beta"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2
operator|*
name|G_PI
argument_list|,
name|G_PI
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
name|PROP_CLOCKWISE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"clockwise"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
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
name|PROP_DRAW_BETA
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"draw-beta"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDialPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dial_init (GimpDial * dial)
name|gimp_dial_init
parameter_list|(
name|GimpDial
modifier|*
name|dial
parameter_list|)
block|{
name|dial
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|dial
argument_list|,
name|GIMP_TYPE_DIAL
argument_list|,
name|GimpDialPrivate
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dial
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
DECL|function|gimp_dial_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dial_set_property
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
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
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
name|PROP_ALPHA
case|:
name|dial
operator|->
name|priv
operator|->
name|alpha
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dial
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BETA
case|:
name|dial
operator|->
name|priv
operator|->
name|beta
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dial
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CLOCKWISE
case|:
name|dial
operator|->
name|priv
operator|->
name|clockwise
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dial
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DRAW_BETA
case|:
name|dial
operator|->
name|priv
operator|->
name|draw_beta
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dial
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
DECL|function|gimp_dial_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dial_get_property
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
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
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
name|PROP_ALPHA
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|alpha
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BETA
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|beta
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CLOCKWISE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|clockwise
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DRAW_BETA
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|draw_beta
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
DECL|function|gimp_dial_unmap (GtkWidget * widget)
name|gimp_dial_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|dial
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
name|dial
operator|->
name|priv
operator|->
name|has_grab
operator|=
name|FALSE
expr_stmt|;
block|}
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
name|gboolean
DECL|function|gimp_dial_expose_event (GtkWidget * widget,GdkEventExpose * event)
name|gimp_dial_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|expose_event
argument_list|(
name|widget
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_is_drawable
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|size
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|g_object_get
argument_list|(
name|widget
argument_list|,
literal|"size"
argument_list|,
operator|&
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|event
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_cairo_region
argument_list|(
name|cr
argument_list|,
name|event
operator|->
name|region
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
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
name|cairo_translate
argument_list|(
name|cr
argument_list|,
operator|(
name|gdouble
operator|)
name|allocation
operator|.
name|x
operator|+
operator|(
name|allocation
operator|.
name|width
operator|-
name|size
operator|)
operator|/
literal|2.0
argument_list|,
operator|(
name|gdouble
operator|)
name|allocation
operator|.
name|y
operator|+
operator|(
name|allocation
operator|.
name|height
operator|-
name|size
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|gimp_dial_draw_arrows
argument_list|(
name|cr
argument_list|,
name|size
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|alpha
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|beta
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|clockwise
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|target
argument_list|,
name|dial
operator|->
name|priv
operator|->
name|draw_beta
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
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
name|gdouble
DECL|function|normalize_angle (gdouble angle)
name|normalize_angle
parameter_list|(
name|gdouble
name|angle
parameter_list|)
block|{
if|if
condition|(
name|angle
operator|<
literal|0
condition|)
return|return
name|angle
operator|+
literal|2
operator|*
name|G_PI
return|;
elseif|else
if|if
condition|(
name|angle
operator|>
literal|2
operator|*
name|G_PI
condition|)
return|return
name|angle
operator|-
literal|2
operator|*
name|G_PI
return|;
else|else
return|return
name|angle
return|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|get_angle_distance (gdouble alpha,gdouble beta)
name|get_angle_distance
parameter_list|(
name|gdouble
name|alpha
parameter_list|,
name|gdouble
name|beta
parameter_list|)
block|{
return|return
name|ABS
argument_list|(
name|MIN
argument_list|(
name|normalize_angle
argument_list|(
name|alpha
operator|-
name|beta
argument_list|)
argument_list|,
literal|2
operator|*
name|G_PI
operator|-
name|normalize_angle
argument_list|(
name|alpha
operator|-
name|beta
argument_list|)
argument_list|)
argument_list|)
return|;
block|}
end_function

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
specifier|static
name|gboolean
DECL|function|gimp_dial_button_press_event (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_dial_button_press_event
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
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
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
operator|&&
name|dial
operator|->
name|priv
operator|->
name|target
operator|!=
name|DIAL_TARGET_NONE
condition|)
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
name|gdouble
name|angle
decl_stmt|;
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|dial
operator|->
name|priv
operator|->
name|has_grab
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
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
name|angle
operator|=
name|get_angle_and_distance
argument_list|(
name|center_x
argument_list|,
name|center_y
argument_list|,
literal|1.0
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dial
operator|->
name|priv
operator|->
name|last_angle
operator|=
name|angle
expr_stmt|;
switch|switch
condition|(
name|dial
operator|->
name|priv
operator|->
name|target
condition|)
block|{
case|case
name|DIAL_TARGET_ALPHA
case|:
name|g_object_set
argument_list|(
name|dial
argument_list|,
literal|"alpha"
argument_list|,
name|angle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|DIAL_TARGET_BETA
case|:
name|g_object_set
argument_list|(
name|dial
argument_list|,
literal|"beta"
argument_list|,
name|angle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dial_button_release_event (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_dial_button_release_event
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
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
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
name|dial
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
name|dial
operator|->
name|priv
operator|->
name|in_widget
condition|)
block|{
name|dial
operator|->
name|priv
operator|->
name|target
operator|=
name|DIAL_TARGET_NONE
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dial_motion_notify_event (GtkWidget * widget,GdkEventMotion * mevent)
name|gimp_dial_motion_notify_event
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
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|gint
name|size
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|distance
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
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
name|g_object_get
argument_list|(
name|widget
argument_list|,
literal|"size"
argument_list|,
operator|&
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|angle
operator|=
name|get_angle_and_distance
argument_list|(
name|center_x
argument_list|,
name|center_y
argument_list|,
name|size
operator|/
literal|2.0
argument_list|,
name|mevent
operator|->
name|x
argument_list|,
name|mevent
operator|->
name|y
argument_list|,
operator|&
name|distance
argument_list|)
expr_stmt|;
if|if
condition|(
name|dial
operator|->
name|priv
operator|->
name|has_grab
condition|)
block|{
name|gdouble
name|delta
decl_stmt|;
name|delta
operator|=
name|angle
operator|-
name|dial
operator|->
name|priv
operator|->
name|last_angle
expr_stmt|;
name|dial
operator|->
name|priv
operator|->
name|last_angle
operator|=
name|angle
expr_stmt|;
if|if
condition|(
name|delta
operator|!=
literal|0.0
condition|)
block|{
switch|switch
condition|(
name|dial
operator|->
name|priv
operator|->
name|target
condition|)
block|{
case|case
name|DIAL_TARGET_ALPHA
case|:
name|g_object_set
argument_list|(
name|dial
argument_list|,
literal|"alpha"
argument_list|,
name|angle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|DIAL_TARGET_BETA
case|:
name|g_object_set
argument_list|(
name|dial
argument_list|,
literal|"beta"
argument_list|,
name|angle
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|DIAL_TARGET_BOTH
case|:
name|g_object_set
argument_list|(
name|dial
argument_list|,
literal|"alpha"
argument_list|,
name|normalize_angle
argument_list|(
name|dial
operator|->
name|priv
operator|->
name|alpha
operator|+
name|delta
argument_list|)
argument_list|,
literal|"beta"
argument_list|,
name|normalize_angle
argument_list|(
name|dial
operator|->
name|priv
operator|->
name|beta
operator|+
name|delta
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
else|else
block|{
name|DialTarget
name|target
decl_stmt|;
if|if
condition|(
name|dial
operator|->
name|priv
operator|->
name|draw_beta
operator|&&
name|distance
operator|>
name|SEGMENT_FRACTION
operator|&&
name|MIN
argument_list|(
name|get_angle_distance
argument_list|(
name|dial
operator|->
name|priv
operator|->
name|alpha
argument_list|,
name|angle
argument_list|)
argument_list|,
name|get_angle_distance
argument_list|(
name|dial
operator|->
name|priv
operator|->
name|beta
argument_list|,
name|angle
argument_list|)
argument_list|)
operator|<
name|G_PI
operator|/
literal|12
condition|)
block|{
if|if
condition|(
name|get_angle_distance
argument_list|(
name|dial
operator|->
name|priv
operator|->
name|alpha
argument_list|,
name|angle
argument_list|)
operator|<
name|get_angle_distance
argument_list|(
name|dial
operator|->
name|priv
operator|->
name|beta
argument_list|,
name|angle
argument_list|)
condition|)
block|{
name|target
operator|=
name|DIAL_TARGET_ALPHA
expr_stmt|;
block|}
else|else
block|{
name|target
operator|=
name|DIAL_TARGET_BETA
expr_stmt|;
block|}
block|}
else|else
block|{
name|target
operator|=
name|DIAL_TARGET_BOTH
expr_stmt|;
block|}
if|if
condition|(
name|target
operator|!=
name|dial
operator|->
name|priv
operator|->
name|target
condition|)
block|{
name|dial
operator|->
name|priv
operator|->
name|target
operator|=
name|target
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
name|gdk_event_request_motions
argument_list|(
name|mevent
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
DECL|function|gimp_dial_enter_notify_event (GtkWidget * widget,GdkEventCrossing * event)
name|gimp_dial_enter_notify_event
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
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|dial
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
DECL|function|gimp_dial_leave_notify_event (GtkWidget * widget,GdkEventCrossing * event)
name|gimp_dial_leave_notify_event
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
name|GimpDial
modifier|*
name|dial
init|=
name|GIMP_DIAL
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|dial
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
name|dial
operator|->
name|priv
operator|->
name|has_grab
condition|)
block|{
name|dial
operator|->
name|priv
operator|->
name|target
operator|=
name|DIAL_TARGET_NONE
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
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
name|GtkWidget
modifier|*
DECL|function|gimp_dial_new (void)
name|gimp_dial_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DIAL
argument_list|,
name|NULL
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
DECL|function|gimp_dial_draw_arrow (cairo_t * cr,gdouble radius,gdouble angle)
name|gimp_dial_draw_arrow
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
DECL|macro|REL
define|#
directive|define
name|REL
value|0.8
DECL|macro|DEL
define|#
directive|define
name|DEL
value|0.1
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|radius
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|radius
operator|+
name|radius
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
argument_list|,
name|radius
operator|-
name|radius
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|radius
operator|+
name|radius
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
argument_list|,
name|radius
operator|-
name|radius
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|radius
operator|+
name|radius
operator|*
name|REL
operator|*
name|cos
argument_list|(
name|angle
operator|-
name|DEL
argument_list|)
argument_list|,
name|radius
operator|-
name|radius
operator|*
name|REL
operator|*
name|sin
argument_list|(
name|angle
operator|-
name|DEL
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|radius
operator|+
name|radius
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
argument_list|,
name|radius
operator|-
name|radius
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|radius
operator|+
name|radius
operator|*
name|REL
operator|*
name|cos
argument_list|(
name|angle
operator|+
name|DEL
argument_list|)
argument_list|,
name|radius
operator|-
name|radius
operator|*
name|REL
operator|*
name|sin
argument_list|(
name|angle
operator|+
name|DEL
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dial_draw_segment (cairo_t * cr,gdouble radius,gdouble alpha,gdouble beta,gboolean clockwise)
name|gimp_dial_draw_segment
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|gdouble
name|alpha
parameter_list|,
name|gdouble
name|beta
parameter_list|,
name|gboolean
name|clockwise
parameter_list|)
block|{
name|gint
name|direction
init|=
name|clockwise
condition|?
operator|-
literal|1
else|:
literal|1
decl_stmt|;
name|gint
name|segment_dist
decl_stmt|;
name|gint
name|tick
decl_stmt|;
name|gdouble
name|slice
decl_stmt|;
name|segment_dist
operator|=
name|radius
operator|*
name|SEGMENT_FRACTION
expr_stmt|;
name|tick
operator|=
name|MIN
argument_list|(
literal|10
argument_list|,
name|segment_dist
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|radius
operator|+
name|segment_dist
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
argument_list|,
name|radius
operator|-
name|segment_dist
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|radius
operator|+
name|segment_dist
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
operator|+
name|direction
operator|*
name|tick
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
argument_list|,
name|radius
operator|-
name|segment_dist
operator|*
name|sin
argument_list|(
name|beta
argument_list|)
operator|+
name|direction
operator|*
name|tick
operator|*
name|cos
argument_list|(
name|beta
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_new_sub_path
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|clockwise
condition|)
name|slice
operator|=
operator|-
name|normalize_angle
argument_list|(
name|alpha
operator|-
name|beta
argument_list|)
expr_stmt|;
else|else
name|slice
operator|=
name|normalize_angle
argument_list|(
name|beta
operator|-
name|alpha
argument_list|)
expr_stmt|;
name|gimp_cairo_add_arc
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|radius
argument_list|,
name|segment_dist
argument_list|,
name|alpha
argument_list|,
name|slice
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dial_draw_arrows (cairo_t * cr,gint size,gdouble alpha,gdouble beta,gboolean clockwise,DialTarget highlight,gboolean draw_beta)
name|gimp_dial_draw_arrows
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|size
parameter_list|,
name|gdouble
name|alpha
parameter_list|,
name|gdouble
name|beta
parameter_list|,
name|gboolean
name|clockwise
parameter_list|,
name|DialTarget
name|highlight
parameter_list|,
name|gboolean
name|draw_beta
parameter_list|)
block|{
name|gdouble
name|radius
init|=
name|size
operator|/
literal|2.0
operator|-
literal|2.0
decl_stmt|;
comment|/* half the broad line with and half a px */
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
literal|2.0
argument_list|,
literal|2.0
argument_list|)
expr_stmt|;
comment|/* half the broad line width and half a px*/
name|cairo_set_line_cap
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_CAP_ROUND
argument_list|)
expr_stmt|;
name|cairo_set_line_join
argument_list|(
name|cr
argument_list|,
name|CAIRO_LINE_JOIN_ROUND
argument_list|)
expr_stmt|;
if|if
condition|(
name|highlight
operator|!=
name|DIAL_TARGET_BOTH
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|highlight
operator|&
name|DIAL_TARGET_ALPHA
operator|)
condition|)
name|gimp_dial_draw_arrow
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
if|if
condition|(
name|draw_beta
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|highlight
operator|&
name|DIAL_TARGET_BETA
operator|)
condition|)
name|gimp_dial_draw_arrow
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|beta
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|highlight
operator|&
name|DIAL_TARGET_BOTH
operator|)
operator|!=
name|DIAL_TARGET_BOTH
condition|)
name|gimp_dial_draw_segment
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|alpha
argument_list|,
name|beta
argument_list|,
name|clockwise
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|highlight
operator|!=
name|DIAL_TARGET_NONE
condition|)
block|{
if|if
condition|(
name|highlight
operator|&
name|DIAL_TARGET_ALPHA
condition|)
name|gimp_dial_draw_arrow
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
if|if
condition|(
name|draw_beta
condition|)
block|{
if|if
condition|(
name|highlight
operator|&
name|DIAL_TARGET_BETA
condition|)
name|gimp_dial_draw_arrow
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|beta
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|highlight
operator|&
name|DIAL_TARGET_BOTH
operator|)
operator|==
name|DIAL_TARGET_BOTH
condition|)
name|gimp_dial_draw_segment
argument_list|(
name|cr
argument_list|,
name|radius
argument_list|,
name|alpha
argument_list|,
name|beta
argument_list|,
name|clockwise
argument_list|)
expr_stmt|;
block|}
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
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
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
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
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
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

