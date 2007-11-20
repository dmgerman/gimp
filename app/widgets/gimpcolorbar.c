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
file|<string.h>
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbar.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c25e1df0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ORIENTATION
name|PROP_ORIENTATION
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|,
DECL|enumerator|PROP_CHANNEL
name|PROP_CHANNEL
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_color_bar_set_property
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
name|gimp_color_bar_get_property
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
name|gimp_color_bar_expose
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpColorBar,gimp_color_bar,GTK_TYPE_MISC)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorBar
argument_list|,
argument|gimp_color_bar
argument_list|,
argument|GTK_TYPE_MISC
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_bar_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_color_bar_class_init
parameter_list|(
name|GimpColorBarClass
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
name|GimpRGB
name|white
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_color_bar_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_color_bar_get_property
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_color_bar_expose
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR
argument_list|,
name|gimp_param_spec_rgb
argument_list|(
literal|"color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
operator|&
name|white
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ORIENTATION
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"histogram-channel"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_HISTOGRAM_CHANNEL
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|,
name|GIMP_PARAM_WRITABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_bar_init (GimpColorBar * bar)
name|gimp_color_bar_init
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
parameter_list|)
block|{
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|bar
argument_list|,
name|GTK_NO_WINDOW
argument_list|)
expr_stmt|;
name|bar
operator|->
name|orientation
operator|=
name|GTK_ORIENTATION_HORIZONTAL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_bar_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_color_bar_set_property
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
name|GimpColorBar
modifier|*
name|bar
init|=
name|GIMP_COLOR_BAR
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
case|case
name|PROP_COLOR
case|:
name|gimp_color_bar_set_color
argument_list|(
name|bar
argument_list|,
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CHANNEL
case|:
name|gimp_color_bar_set_channel
argument_list|(
name|bar
argument_list|,
name|g_value_get_enum
argument_list|(
name|value
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
DECL|function|gimp_color_bar_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_color_bar_get_property
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
name|GimpColorBar
modifier|*
name|bar
init|=
name|GIMP_COLOR_BAR
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
DECL|function|gimp_color_bar_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_color_bar_expose
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
name|GimpColorBar
modifier|*
name|bar
init|=
name|GIMP_COLOR_BAR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|b
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
decl_stmt|,
name|j
decl_stmt|;
name|x
operator|=
name|GTK_MISC
argument_list|(
name|bar
argument_list|)
operator|->
name|xpad
expr_stmt|;
name|y
operator|=
name|GTK_MISC
argument_list|(
name|bar
argument_list|)
operator|->
name|ypad
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
name|width
operator|<
literal|1
operator|||
name|height
operator|<
literal|1
condition|)
return|return
name|TRUE
return|;
name|buf
operator|=
name|g_alloca
argument_list|(
name|width
operator|*
name|height
operator|*
literal|3
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bar
operator|->
name|orientation
condition|)
block|{
case|case
name|GTK_ORIENTATION_HORIZONTAL
case|:
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|b
operator|=
name|buf
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
operator|,
name|b
operator|+=
literal|3
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|bar
operator|->
name|buf
operator|+
literal|3
operator|*
operator|(
operator|(
name|i
operator|*
literal|256
operator|)
operator|/
name|width
operator|)
decl_stmt|;
name|b
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|b
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|b
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
name|memcpy
argument_list|(
name|buf
operator|+
name|i
operator|*
name|width
operator|*
literal|3
argument_list|,
name|buf
argument_list|,
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_ORIENTATION_VERTICAL
case|:
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|b
operator|=
name|buf
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
operator|,
name|b
operator|+=
literal|3
operator|*
name|width
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|bar
operator|->
name|buf
operator|+
literal|3
operator|*
operator|(
literal|255
operator|-
operator|(
operator|(
name|i
operator|*
literal|256
operator|)
operator|/
name|height
operator|)
operator|)
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|b
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
operator|,
name|dest
operator|+=
literal|3
control|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
block|}
block|}
break|break;
block|}
name|gdk_draw_rgb_image
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|x
operator|+
name|x
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|y
operator|+
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GDK_RGB_DITHER_NORMAL
argument_list|,
name|buf
argument_list|,
literal|3
operator|*
name|width
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_color_bar_new:  * @orientation: whether the bar should be oriented horizontally or  *               vertically  *  * Creates a new #GimpColorBar widget.  *  * Return value: The new #GimpColorBar widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_bar_new (GtkOrientation orientation)
name|gimp_color_bar_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_BAR
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

begin_comment
comment|/**  * gimp_color_bar_set_color:  * @bar:   a #GimpColorBar widget  * @color: a #GimpRGB color  *  * Makes the @bar display a gradient from black (on the left or the  * bottom), to the given @color (on the right or at the top).  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_bar_set_color (GimpColorBar * bar,const GimpRGB * color)
name|gimp_color_bar_set_color
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BAR
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|buf
operator|=
name|bar
operator|->
name|buf
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
operator|,
name|buf
operator|+=
literal|3
control|)
block|{
name|buf
index|[
literal|0
index|]
operator|=
name|ROUND
argument_list|(
name|color
operator|->
name|r
operator|*
operator|(
name|gdouble
operator|)
name|i
argument_list|)
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
name|ROUND
argument_list|(
name|color
operator|->
name|g
operator|*
operator|(
name|gdouble
operator|)
name|i
argument_list|)
expr_stmt|;
name|buf
index|[
literal|2
index|]
operator|=
name|ROUND
argument_list|(
name|color
operator|->
name|b
operator|*
operator|(
name|gdouble
operator|)
name|i
argument_list|)
expr_stmt|;
block|}
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

begin_comment
comment|/**  * gimp_color_bar_set_channel:  * @bar:     a #GimpColorBar widget  * @channel: a #GimpHistogramChannel  *  * Convenience function that calls gimp_color_bar_set_color() with the  * color that matches the @channel.  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_bar_set_channel (GimpColorBar * bar,GimpHistogramChannel channel)
name|gimp_color_bar_set_channel
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
block|{
name|GimpRGB
name|color
init|=
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BAR
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|channel
condition|)
block|{
case|case
name|GIMP_HISTOGRAM_VALUE
case|:
case|case
name|GIMP_HISTOGRAM_ALPHA
case|:
case|case
name|GIMP_HISTOGRAM_RGB
case|:
name|gimp_rgb_set
argument_list|(
operator|&
name|color
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HISTOGRAM_RED
case|:
name|gimp_rgb_set
argument_list|(
operator|&
name|color
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HISTOGRAM_GREEN
case|:
name|gimp_rgb_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HISTOGRAM_BLUE
case|:
name|gimp_rgb_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_color_bar_set_color
argument_list|(
name|bar
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_bar_set_buffers:  * @bar:   a #GimpColorBar widget  * @red:   an array of 256 values  * @green: an array of 256 values  * @blue:  an array of 256 values  *  * This function gives full control over the colors displayed by the  * @bar widget. The 3 arrays can for example be taken from a #Levels  * or a #Curves struct.  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_bar_set_buffers (GimpColorBar * bar,const guchar * red,const guchar * green,const guchar * blue)
name|gimp_color_bar_set_buffers
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
parameter_list|,
specifier|const
name|guchar
modifier|*
name|red
parameter_list|,
specifier|const
name|guchar
modifier|*
name|green
parameter_list|,
specifier|const
name|guchar
modifier|*
name|blue
parameter_list|)
block|{
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_BAR
argument_list|(
name|bar
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|red
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|green
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|blue
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|buf
operator|=
name|bar
operator|->
name|buf
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
operator|,
name|buf
operator|+=
literal|3
control|)
block|{
name|buf
index|[
literal|0
index|]
operator|=
name|red
index|[
name|i
index|]
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
name|green
index|[
name|i
index|]
expr_stmt|;
name|buf
index|[
literal|2
index|]
operator|=
name|blue
index|[
name|i
index|]
expr_stmt|;
block|}
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

