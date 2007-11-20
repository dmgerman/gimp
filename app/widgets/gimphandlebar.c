begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimphandlebar.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon292f78f30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ORIENTATION
name|PROP_ORIENTATION
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_handle_bar_set_property
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
name|gimp_handle_bar_get_property
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
name|gimp_handle_bar_expose
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
name|gimp_handle_bar_button_press
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
name|gimp_handle_bar_button_release
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
name|gimp_handle_bar_motion_notify
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
name|gimp_handle_bar_adjustment_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpHandleBar
modifier|*
name|bar
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpHandleBar,gimp_handle_bar,GTK_TYPE_EVENT_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHandleBar
argument_list|,
argument|gimp_handle_bar
argument_list|,
argument|GTK_TYPE_EVENT_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_handle_bar_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_handle_bar_class_init
parameter_list|(
name|GimpHandleBarClass
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
name|set_property
operator|=
name|gimp_handle_bar_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_handle_bar_get_property
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_handle_bar_expose
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_handle_bar_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_handle_bar_button_release
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_handle_bar_motion_notify
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ORIENTATION
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"orientation"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_ORIENTATION
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_bar_init (GimpHandleBar * bar)
name|gimp_handle_bar_init
parameter_list|(
name|GimpHandleBar
modifier|*
name|bar
parameter_list|)
block|{
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|bar
argument_list|)
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON_MOTION_MASK
argument_list|)
expr_stmt|;
name|gtk_event_box_set_visible_window
argument_list|(
name|GTK_EVENT_BOX
argument_list|(
name|bar
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|bar
operator|->
name|orientation
operator|=
name|GTK_ORIENTATION_HORIZONTAL
expr_stmt|;
name|bar
operator|->
name|lower
operator|=
literal|0.0
expr_stmt|;
name|bar
operator|->
name|upper
operator|=
literal|1.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_handle_bar_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_handle_bar_set_property
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
name|GimpHandleBar
modifier|*
name|bar
init|=
name|GIMP_HANDLE_BAR
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
name|PROP_ORIENTATION
case|:
name|bar
operator|->
name|orientation
operator|=
name|g_value_get_enum
argument_list|(
name|value
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
DECL|function|gimp_handle_bar_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_handle_bar_get_property
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
name|GimpHandleBar
modifier|*
name|bar
init|=
name|GIMP_HANDLE_BAR
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
name|PROP_ORIENTATION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|bar
operator|->
name|orientation
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
DECL|function|gimp_handle_bar_expose (GtkWidget * widget,GdkEventExpose * eevent)
name|gimp_handle_bar_expose
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
name|GimpHandleBar
modifier|*
name|bar
init|=
name|GIMP_HANDLE_BAR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|x
operator|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
expr_stmt|;
name|y
operator|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
expr_stmt|;
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|x
expr_stmt|;
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
literal|2
operator|*
name|y
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_NO_WINDOW
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|x
operator|+=
name|widget
operator|->
name|allocation
operator|.
name|x
expr_stmt|;
name|y
operator|+=
name|widget
operator|->
name|allocation
operator|.
name|y
expr_stmt|;
block|}
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_cairo_region
argument_list|(
name|cr
argument_list|,
name|eevent
operator|->
name|region
argument_list|)
expr_stmt|;
name|cairo_clip
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
name|cairo_translate
argument_list|(
name|cr
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|bar
operator|->
name|slider_adj
index|[
name|i
index|]
condition|)
block|{
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
operator|=
name|ROUND
argument_list|(
operator|(
name|gdouble
operator|)
name|width
operator|*
operator|(
name|bar
operator|->
name|slider_adj
index|[
name|i
index|]
operator|->
name|value
operator|-
name|bar
operator|->
name|lower
operator|)
operator|/
operator|(
name|bar
operator|->
name|upper
operator|-
name|bar
operator|->
name|lower
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|0.5
operator|*
name|i
argument_list|,
literal|0.5
operator|*
name|i
argument_list|,
literal|0.5
operator|*
name|i
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
operator|-
operator|(
name|height
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|y
operator|+
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
operator|+
operator|(
name|height
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|y
operator|+
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_fill_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
name|cairo_destroy
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
DECL|function|gimp_handle_bar_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_handle_bar_button_press
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
name|GimpHandleBar
modifier|*
name|bar
init|=
name|GIMP_HANDLE_BAR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|border
init|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
decl_stmt|;
name|gint
name|width
init|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|border
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|gint
name|min_dist
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
condition|)
return|return
name|FALSE
return|;
name|min_dist
operator|=
name|G_MAXINT
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
operator|!=
operator|-
literal|1
condition|)
block|{
name|gdouble
name|dist
init|=
name|bevent
operator|->
name|x
operator|-
name|bar
operator|->
name|slider_pos
index|[
name|i
index|]
operator|+
name|border
decl_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|dist
argument_list|)
operator|<
name|min_dist
operator|||
operator|(
name|fabs
argument_list|(
name|dist
argument_list|)
operator|==
name|min_dist
operator|&&
name|dist
operator|>
literal|0
operator|)
condition|)
block|{
name|bar
operator|->
name|active_slider
operator|=
name|i
expr_stmt|;
name|min_dist
operator|=
name|fabs
argument_list|(
name|dist
argument_list|)
expr_stmt|;
block|}
block|}
name|value
operator|=
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|bevent
operator|->
name|x
operator|-
name|border
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|width
operator|*
operator|(
name|bar
operator|->
name|upper
operator|-
name|bar
operator|->
name|lower
operator|+
literal|1
operator|)
operator|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|bar
operator|->
name|slider_adj
index|[
name|bar
operator|->
name|active_slider
index|]
argument_list|,
name|value
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
DECL|function|gimp_handle_bar_button_release (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_handle_bar_button_release
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
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_handle_bar_motion_notify (GtkWidget * widget,GdkEventMotion * mevent)
name|gimp_handle_bar_motion_notify
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
name|GimpHandleBar
modifier|*
name|bar
init|=
name|GIMP_HANDLE_BAR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|border
init|=
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
operator|->
name|border_width
decl_stmt|;
name|gint
name|width
init|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|border
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
condition|)
return|return
name|FALSE
return|;
name|value
operator|=
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|mevent
operator|->
name|x
operator|-
name|border
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|width
operator|*
operator|(
name|bar
operator|->
name|upper
operator|-
name|bar
operator|->
name|lower
operator|+
literal|1
operator|)
operator|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|bar
operator|->
name|slider_adj
index|[
name|bar
operator|->
name|active_slider
index|]
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_handle_bar_new:  * @orientation: whether the bar should be oriented horizontally or  *               vertically  *  * Creates a new #GimpHandleBar widget.  *  * Return value: The new #GimpHandleBar widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_handle_bar_new (GtkOrientation orientation)
name|gimp_handle_bar_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_HANDLE_BAR
argument_list|,
literal|"orientation"
argument_list|,
name|orientation
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_handle_bar_set_adjustment (GimpHandleBar * bar,gint handle_no,GtkAdjustment * adjustment)
name|gimp_handle_bar_set_adjustment
parameter_list|(
name|GimpHandleBar
modifier|*
name|bar
parameter_list|,
name|gint
name|handle_no
parameter_list|,
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HANDLE_BAR
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|handle_no
operator|>=
literal|0
operator|&&
name|handle_no
operator|<=
literal|2
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|adjustment
operator|==
name|NULL
operator|||
name|GTK_IS_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|adjustment
operator|==
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
condition|)
return|return;
if|if
condition|(
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
argument_list|,
name|gimp_handle_bar_adjustment_changed
argument_list|,
name|bar
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
argument_list|)
expr_stmt|;
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
operator|=
name|NULL
expr_stmt|;
block|}
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
operator|=
name|adjustment
expr_stmt|;
if|if
condition|(
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
condition|)
block|{
name|g_object_ref
argument_list|(
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_handle_bar_adjustment_changed
argument_list|)
argument_list|,
name|bar
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bar
operator|->
name|slider_adj
index|[
literal|0
index|]
condition|)
name|bar
operator|->
name|lower
operator|=
name|bar
operator|->
name|slider_adj
index|[
literal|0
index|]
operator|->
name|lower
expr_stmt|;
else|else
name|bar
operator|->
name|lower
operator|=
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
operator|->
name|lower
expr_stmt|;
if|if
condition|(
name|bar
operator|->
name|slider_adj
index|[
literal|2
index|]
condition|)
name|bar
operator|->
name|upper
operator|=
name|bar
operator|->
name|slider_adj
index|[
literal|2
index|]
operator|->
name|upper
expr_stmt|;
else|else
name|bar
operator|->
name|upper
operator|=
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
operator|->
name|upper
expr_stmt|;
name|gimp_handle_bar_adjustment_changed
argument_list|(
name|bar
operator|->
name|slider_adj
index|[
name|handle_no
index|]
argument_list|,
name|bar
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_handle_bar_adjustment_changed (GtkAdjustment * adjustment,GimpHandleBar * bar)
name|gimp_handle_bar_adjustment_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpHandleBar
modifier|*
name|bar
parameter_list|)
block|{
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

