begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppolar.c  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * Based on code from the color-rotate plug-in  * Copyright (C) 1997-1999 Sven Anders (anderss@fmi.uni-passau.de)  *                         Based on code from Pavel Grinfeld (pavel@ml.com)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimppolar.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c64fb9c0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ANGLE
name|PROP_ANGLE
block|,
DECL|enumerator|PROP_RADIUS
name|PROP_RADIUS
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c64fb9c0203
block|{
DECL|enumerator|POLAR_TARGET_NONE
name|POLAR_TARGET_NONE
init|=
literal|0
block|,
DECL|enumerator|POLAR_TARGET_CIRCLE
name|POLAR_TARGET_CIRCLE
init|=
literal|1
operator|<<
literal|0
DECL|typedef|PolarTarget
block|}
name|PolarTarget
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPolarPrivate
struct|struct
name|_GimpPolarPrivate
block|{
DECL|member|angle
name|gdouble
name|angle
decl_stmt|;
DECL|member|radius
name|gdouble
name|radius
decl_stmt|;
DECL|member|target
name|PolarTarget
name|target
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_polar_set_property
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
name|gimp_polar_get_property
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
name|gboolean
name|gimp_polar_expose_event
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
name|gimp_polar_button_press_event
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
name|gimp_polar_motion_notify_event
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
name|void
name|gimp_polar_reset_target
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
name|gimp_polar_set_target
parameter_list|(
name|GimpPolar
modifier|*
name|polar
parameter_list|,
name|PolarTarget
name|target
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_polar_draw_circle
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|size
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|PolarTarget
name|highlight
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_polar_normalize_angle
parameter_list|(
name|gdouble
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_polar_get_angle_distance
parameter_list|(
name|gdouble
name|alpha
parameter_list|,
name|gdouble
name|beta
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPolar,gimp_polar,GIMP_TYPE_CIRCLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPolar
argument_list|,
argument|gimp_polar
argument_list|,
argument|GIMP_TYPE_CIRCLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_polar_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_polar_class_init
parameter_list|(
name|GimpPolarClass
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
name|GimpCircleClass
modifier|*
name|circle_class
init|=
name|GIMP_CIRCLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_polar_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_polar_set_property
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_polar_expose_event
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_polar_button_press_event
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_polar_motion_notify_event
expr_stmt|;
name|circle_class
operator|->
name|reset_target
operator|=
name|gimp_polar_reset_target
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ANGLE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"angle"
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
name|PROP_RADIUS
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"radius"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
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
name|GimpPolarPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polar_init (GimpPolar * polar)
name|gimp_polar_init
parameter_list|(
name|GimpPolar
modifier|*
name|polar
parameter_list|)
block|{
name|polar
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|polar
argument_list|,
name|GIMP_TYPE_POLAR
argument_list|,
name|GimpPolarPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polar_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_polar_set_property
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
name|GimpPolar
modifier|*
name|polar
init|=
name|GIMP_POLAR
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
name|PROP_ANGLE
case|:
name|polar
operator|->
name|priv
operator|->
name|angle
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
name|polar
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS
case|:
name|polar
operator|->
name|priv
operator|->
name|radius
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
name|polar
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
DECL|function|gimp_polar_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_polar_get_property
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
name|GimpPolar
modifier|*
name|polar
init|=
name|GIMP_POLAR
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
name|PROP_ANGLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|polar
operator|->
name|priv
operator|->
name|angle
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RADIUS
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|polar
operator|->
name|priv
operator|->
name|radius
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
name|gboolean
DECL|function|gimp_polar_expose_event (GtkWidget * widget,GdkEventExpose * event)
name|gimp_polar_expose_event
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
name|GimpPolar
modifier|*
name|polar
init|=
name|GIMP_POLAR
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
name|gimp_polar_draw_circle
argument_list|(
name|cr
argument_list|,
name|size
argument_list|,
name|polar
operator|->
name|priv
operator|->
name|angle
argument_list|,
name|polar
operator|->
name|priv
operator|->
name|radius
argument_list|,
name|polar
operator|->
name|priv
operator|->
name|target
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
name|gboolean
DECL|function|gimp_polar_button_press_event (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_polar_button_press_event
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
name|GimpPolar
modifier|*
name|polar
init|=
name|GIMP_POLAR
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
name|polar
operator|->
name|priv
operator|->
name|target
operator|!=
name|POLAR_TARGET_NONE
condition|)
block|{
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|radius
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press_event
argument_list|(
name|widget
argument_list|,
name|bevent
argument_list|)
expr_stmt|;
name|angle
operator|=
name|_gimp_circle_get_angle_and_distance
argument_list|(
name|GIMP_CIRCLE
argument_list|(
name|polar
argument_list|)
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|radius
argument_list|)
expr_stmt|;
name|radius
operator|=
name|MIN
argument_list|(
name|radius
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|polar
argument_list|,
literal|"angle"
argument_list|,
name|angle
argument_list|,
literal|"radius"
argument_list|,
name|radius
argument_list|,
name|NULL
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
DECL|function|gimp_polar_motion_notify_event (GtkWidget * widget,GdkEventMotion * mevent)
name|gimp_polar_motion_notify_event
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
name|GimpPolar
modifier|*
name|polar
init|=
name|GIMP_POLAR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|radius
decl_stmt|;
name|angle
operator|=
name|_gimp_circle_get_angle_and_distance
argument_list|(
name|GIMP_CIRCLE
argument_list|(
name|polar
argument_list|)
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
name|radius
argument_list|)
expr_stmt|;
if|if
condition|(
name|_gimp_circle_has_grab
argument_list|(
name|GIMP_CIRCLE
argument_list|(
name|polar
argument_list|)
argument_list|)
condition|)
block|{
name|radius
operator|=
name|MIN
argument_list|(
name|radius
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|polar
argument_list|,
literal|"angle"
argument_list|,
name|angle
argument_list|,
literal|"radius"
argument_list|,
name|radius
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|PolarTarget
name|target
decl_stmt|;
name|gdouble
name|dist_angle
decl_stmt|;
name|gdouble
name|dist_radius
decl_stmt|;
name|dist_angle
operator|=
name|gimp_polar_get_angle_distance
argument_list|(
name|polar
operator|->
name|priv
operator|->
name|angle
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|dist_radius
operator|=
name|ABS
argument_list|(
name|polar
operator|->
name|priv
operator|->
name|radius
operator|-
name|radius
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|radius
operator|<
literal|0.2
operator|&&
name|polar
operator|->
name|priv
operator|->
name|radius
operator|<
literal|0.2
operator|)
operator|||
operator|(
name|dist_angle
operator|<
operator|(
name|G_PI
operator|/
literal|12
operator|)
operator|&&
name|dist_radius
operator|<
literal|0.2
operator|)
condition|)
block|{
name|target
operator|=
name|POLAR_TARGET_CIRCLE
expr_stmt|;
block|}
else|else
block|{
name|target
operator|=
name|POLAR_TARGET_NONE
expr_stmt|;
block|}
name|gimp_polar_set_target
argument_list|(
name|polar
argument_list|,
name|target
argument_list|)
expr_stmt|;
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
name|void
DECL|function|gimp_polar_reset_target (GimpCircle * circle)
name|gimp_polar_reset_target
parameter_list|(
name|GimpCircle
modifier|*
name|circle
parameter_list|)
block|{
name|gimp_polar_set_target
argument_list|(
name|GIMP_POLAR
argument_list|(
name|circle
argument_list|)
argument_list|,
name|POLAR_TARGET_NONE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_polar_new (void)
name|gimp_polar_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_POLAR
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
DECL|function|gimp_polar_set_target (GimpPolar * polar,PolarTarget target)
name|gimp_polar_set_target
parameter_list|(
name|GimpPolar
modifier|*
name|polar
parameter_list|,
name|PolarTarget
name|target
parameter_list|)
block|{
if|if
condition|(
name|target
operator|!=
name|polar
operator|->
name|priv
operator|->
name|target
condition|)
block|{
name|polar
operator|->
name|priv
operator|->
name|target
operator|=
name|target
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|polar
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_polar_draw_circle (cairo_t * cr,gint size,gdouble angle,gdouble radius,PolarTarget highlight)
name|gimp_polar_draw_circle
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|size
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|PolarTarget
name|highlight
parameter_list|)
block|{
name|gdouble
name|r
init|=
name|size
operator|/
literal|2.0
operator|-
literal|2.0
decl_stmt|;
comment|/* half the broad line with and half a px */
name|gdouble
name|x
init|=
name|r
operator|+
name|r
operator|*
name|radius
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
decl_stmt|;
name|gdouble
name|y
init|=
name|r
operator|-
name|r
operator|*
name|radius
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
decl_stmt|;
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
name|cairo_arc
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|2
operator|*
name|G_PI
argument_list|)
expr_stmt|;
if|if
condition|(
name|highlight
operator|==
name|POLAR_TARGET_NONE
condition|)
block|{
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

begin_function
specifier|static
name|gdouble
DECL|function|gimp_polar_normalize_angle (gdouble angle)
name|gimp_polar_normalize_angle
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
DECL|function|gimp_polar_get_angle_distance (gdouble alpha,gdouble beta)
name|gimp_polar_get_angle_distance
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
name|gimp_polar_normalize_angle
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
name|gimp_polar_normalize_angle
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

end_unit

