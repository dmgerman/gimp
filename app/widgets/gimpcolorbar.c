begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbar.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c41d9340103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ORIENTATION
name|PROP_ORIENTATION
block|,
DECL|enumerator|PROP_INPUT
name|PROP_INPUT
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
name|gimp_color_bar_class_init
parameter_list|(
name|GimpColorBarClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_bar_init
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_color_bar_size_allocate
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
name|void
name|gimp_color_bar_realize
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
name|gimp_color_bar_unrealize
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
name|gimp_color_bar_map
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
name|gimp_color_bar_unmap
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkMiscClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_color_bar_get_type (void)
name|gimp_color_bar_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|bar_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorBarClass
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
name|gimp_color_bar_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpColorBar
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_bar_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_MISC
argument_list|,
literal|"GimpColorBar"
argument_list|,
operator|&
name|bar_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_bar_class_init (GimpColorBarClass * klass)
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
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
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
operator|=
name|G_OBJECT_CLASS
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_color_bar_set_property
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
name|G_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_INPUT
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"input"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_WRITABLE
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
name|gimp_param_spec_color
argument_list|(
literal|"color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|white
argument_list|,
name|G_PARAM_WRITABLE
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
literal|"channel"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_HISTOGRAM_CHANNEL
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|,
name|G_PARAM_WRITABLE
argument_list|)
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_color_bar_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_color_bar_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_color_bar_unrealize
expr_stmt|;
name|widget_class
operator|->
name|map
operator|=
name|gimp_color_bar_map
expr_stmt|;
name|widget_class
operator|->
name|unmap
operator|=
name|gimp_color_bar_unmap
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_color_bar_expose
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
name|bar
operator|->
name|input
operator|=
name|FALSE
expr_stmt|;
name|bar
operator|->
name|input_window
operator|=
name|NULL
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
name|PROP_INPUT
case|:
name|bar
operator|->
name|input
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_color_bar_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_color_bar_size_allocate
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
name|GimpColorBar
modifier|*
name|bar
init|=
name|GIMP_COLOR_BAR
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
name|bar
operator|->
name|input_window
condition|)
name|gdk_window_move_resize
argument_list|(
name|bar
operator|->
name|input_window
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|x
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|y
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_bar_realize (GtkWidget * widget)
name|gimp_color_bar_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
if|if
condition|(
name|bar
operator|->
name|input
operator|&&
operator|!
name|bar
operator|->
name|input_window
condition|)
block|{
name|GdkWindowAttr
name|attributes
decl_stmt|;
name|attributes
operator|.
name|x
operator|=
name|widget
operator|->
name|allocation
operator|.
name|x
expr_stmt|;
name|attributes
operator|.
name|y
operator|=
name|widget
operator|->
name|allocation
operator|.
name|y
expr_stmt|;
name|attributes
operator|.
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|attributes
operator|.
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|attributes
operator|.
name|window_type
operator|=
name|GDK_WINDOW_TEMP
expr_stmt|;
name|attributes
operator|.
name|wclass
operator|=
name|GDK_INPUT_ONLY
expr_stmt|;
name|attributes
operator|.
name|override_redirect
operator|=
name|TRUE
expr_stmt|;
name|attributes
operator|.
name|event_mask
operator|=
operator|(
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON_MOTION_MASK
operator||
name|gtk_widget_get_events
argument_list|(
name|widget
argument_list|)
operator|)
expr_stmt|;
name|bar
operator|->
name|input_window
operator|=
name|gdk_window_new
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|attributes
argument_list|,
operator|(
name|GDK_WA_X
operator||
name|GDK_WA_Y
operator||
name|GDK_WA_NOREDIR
operator|)
argument_list|)
expr_stmt|;
name|gdk_window_set_user_data
argument_list|(
name|bar
operator|->
name|input_window
argument_list|,
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_bar_unrealize (GtkWidget * widget)
name|gimp_color_bar_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
if|if
condition|(
name|bar
operator|->
name|input_window
condition|)
block|{
name|gdk_window_set_user_data
argument_list|(
name|bar
operator|->
name|input_window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_window_destroy
argument_list|(
name|bar
operator|->
name|input_window
argument_list|)
expr_stmt|;
name|bar
operator|->
name|input_window
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
DECL|function|gimp_color_bar_map (GtkWidget * widget)
name|gimp_color_bar_map
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|bar
operator|->
name|input_window
condition|)
name|gdk_window_show
argument_list|(
name|bar
operator|->
name|input_window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_bar_unmap (GtkWidget * widget)
name|gimp_color_bar_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
if|if
condition|(
name|bar
operator|->
name|input_window
condition|)
name|gdk_window_hide
argument_list|(
name|bar
operator|->
name|input_window
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
literal|0
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

