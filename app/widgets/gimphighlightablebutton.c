begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphighlightablebutton.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimphighlightablebutton.h"
end_include

begin_define
DECL|macro|DEFAULT_HIGHLIGHT_COLOR
define|#
directive|define
name|DEFAULT_HIGHLIGHT_COLOR
value|{0.20, 0.70, 0.20, 0.65}
end_define

begin_define
DECL|macro|PADDING
define|#
directive|define
name|PADDING
value|1
end_define

begin_define
DECL|macro|BORDER_WIDTH
define|#
directive|define
name|BORDER_WIDTH
value|1
end_define

begin_define
DECL|macro|CORNER_RADIUS
define|#
directive|define
name|CORNER_RADIUS
value|2
end_define

begin_define
DECL|macro|REV
define|#
directive|define
name|REV
value|(2.0 * G_PI)
end_define

begin_enum
enum|enum
DECL|enum|__anon27faba8f0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_HIGHLIGHT
name|PROP_HIGHLIGHT
block|,
DECL|enumerator|PROP_HIGHLIGHT_COLOR
name|PROP_HIGHLIGHT_COLOR
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpHighlightableButtonPrivate
struct|struct
name|_GimpHighlightableButtonPrivate
block|{
DECL|member|highlight
name|gboolean
name|highlight
decl_stmt|;
DECL|member|highlight_color
name|GimpRGB
name|highlight_color
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_highlightable_button_set_property
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
name|gimp_highlightable_button_get_property
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
name|gimp_highlightable_button_expose_event
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
DECL|function|G_DEFINE_TYPE (GimpHighlightableButton,gimp_highlightable_button,GIMP_TYPE_BUTTON)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHighlightableButton
argument_list|,
argument|gimp_highlightable_button
argument_list|,
argument|GIMP_TYPE_BUTTON
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_highlightable_button_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_highlightable_button_class_init
parameter_list|(
name|GimpHighlightableButtonClass
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
name|gimp_highlightable_button_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_highlightable_button_set_property
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_highlightable_button_expose_event
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HIGHLIGHT
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"highlight"
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
name|PROP_HIGHLIGHT_COLOR
argument_list|,
name|gimp_param_spec_rgb
argument_list|(
literal|"highlight-color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
operator|&
operator|(
name|GimpRGB
operator|)
name|DEFAULT_HIGHLIGHT_COLOR
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
name|GimpHighlightableButtonPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_highlightable_button_init (GimpHighlightableButton * button)
name|gimp_highlightable_button_init
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|)
block|{
name|button
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|button
argument_list|,
name|GIMP_TYPE_HIGHLIGHTABLE_BUTTON
argument_list|,
name|GimpHighlightableButtonPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_highlightable_button_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_highlightable_button_set_property
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
name|GimpHighlightableButton
modifier|*
name|button
init|=
name|GIMP_HIGHLIGHTABLE_BUTTON
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
name|PROP_HIGHLIGHT
case|:
name|gimp_highlightable_button_set_highlight
argument_list|(
name|button
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGHLIGHT_COLOR
case|:
name|gimp_highlightable_button_set_highlight_color
argument_list|(
name|button
argument_list|,
name|g_value_get_boxed
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
DECL|function|gimp_highlightable_button_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_highlightable_button_get_property
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
name|GimpHighlightableButton
modifier|*
name|button
init|=
name|GIMP_HIGHLIGHTABLE_BUTTON
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
name|PROP_HIGHLIGHT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|button
operator|->
name|priv
operator|->
name|highlight
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HIGHLIGHT_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|button
operator|->
name|priv
operator|->
name|highlight_color
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
DECL|function|gimp_highlightable_button_expose_event (GtkWidget * widget,GdkEventExpose * event)
name|gimp_highlightable_button_expose_event
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
name|GimpHighlightableButton
modifier|*
name|button
init|=
name|GIMP_HIGHLIGHTABLE_BUTTON
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|highlight
condition|)
block|{
if|if
condition|(
name|gtk_widget_is_drawable
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|GtkStyle
modifier|*
name|style
init|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkStateType
name|state
init|=
name|gtk_widget_get_state
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|gboolean
name|border
decl_stmt|;
name|gdouble
name|lightness
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gdouble
name|width
decl_stmt|;
name|gdouble
name|height
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|border
operator|=
operator|(
name|state
operator|==
name|GTK_STATE_ACTIVE
operator|||
name|state
operator|==
name|GTK_STATE_PRELIGHT
operator|||
name|gtk_button_get_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
operator|==
name|GTK_RELIEF_NORMAL
operator|)
expr_stmt|;
name|lightness
operator|=
literal|1.00
expr_stmt|;
name|opacity
operator|=
literal|1.00
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|GTK_STATE_ACTIVE
case|:
name|lightness
operator|=
literal|0.80
expr_stmt|;
break|break;
case|case
name|GTK_STATE_PRELIGHT
case|:
name|lightness
operator|=
literal|1.25
expr_stmt|;
break|break;
case|case
name|GTK_STATE_INSENSITIVE
case|:
name|opacity
operator|=
literal|0.50
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|x
operator|=
name|allocation
operator|.
name|x
operator|+
name|PADDING
expr_stmt|;
name|y
operator|=
name|allocation
operator|.
name|y
operator|+
name|PADDING
expr_stmt|;
name|width
operator|=
name|allocation
operator|.
name|width
operator|-
literal|2.0
operator|*
name|PADDING
expr_stmt|;
name|height
operator|=
name|allocation
operator|.
name|height
operator|-
literal|2.0
operator|*
name|PADDING
expr_stmt|;
if|if
condition|(
name|border
condition|)
block|{
name|x
operator|+=
name|BORDER_WIDTH
operator|/
literal|2.0
expr_stmt|;
name|y
operator|+=
name|BORDER_WIDTH
operator|/
literal|2.0
expr_stmt|;
name|width
operator|-=
name|BORDER_WIDTH
expr_stmt|;
name|height
operator|-=
name|BORDER_WIDTH
expr_stmt|;
block|}
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
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
name|button
operator|->
name|priv
operator|->
name|highlight_color
operator|.
name|r
operator|*
name|lightness
argument_list|,
name|button
operator|->
name|priv
operator|->
name|highlight_color
operator|.
name|g
operator|*
name|lightness
argument_list|,
name|button
operator|->
name|priv
operator|->
name|highlight_color
operator|.
name|b
operator|*
name|lightness
argument_list|,
name|button
operator|->
name|priv
operator|->
name|highlight_color
operator|.
name|a
operator|*
name|opacity
argument_list|)
expr_stmt|;
name|gimp_cairo_rounded_rectangle
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|CORNER_RADIUS
argument_list|)
expr_stmt|;
name|cairo_fill_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|border
condition|)
block|{
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|fg
index|[
name|state
index|]
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
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_has_focus
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gboolean
name|interior_focus
decl_stmt|;
name|gint
name|focus_width
decl_stmt|;
name|gint
name|focus_pad
decl_stmt|;
name|gint
name|child_displacement_x
decl_stmt|;
name|gint
name|child_displacement_y
decl_stmt|;
name|gboolean
name|displace_focus
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"interior-focus"
argument_list|,
operator|&
name|interior_focus
argument_list|,
literal|"focus-line-width"
argument_list|,
operator|&
name|focus_width
argument_list|,
literal|"focus-padding"
argument_list|,
operator|&
name|focus_pad
argument_list|,
literal|"child-displacement-y"
argument_list|,
operator|&
name|child_displacement_y
argument_list|,
literal|"child-displacement-x"
argument_list|,
operator|&
name|child_displacement_x
argument_list|,
literal|"displace-focus"
argument_list|,
operator|&
name|displace_focus
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|x
operator|=
name|allocation
operator|.
name|x
operator|+
name|PADDING
expr_stmt|;
name|y
operator|=
name|allocation
operator|.
name|y
operator|+
name|PADDING
expr_stmt|;
name|width
operator|=
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|PADDING
expr_stmt|;
name|height
operator|=
name|allocation
operator|.
name|height
operator|-
literal|2
operator|*
name|PADDING
expr_stmt|;
if|if
condition|(
name|interior_focus
condition|)
block|{
name|x
operator|+=
name|style
operator|->
name|xthickness
operator|+
name|focus_pad
expr_stmt|;
name|y
operator|+=
name|style
operator|->
name|ythickness
operator|+
name|focus_pad
expr_stmt|;
name|width
operator|-=
literal|2
operator|*
operator|(
name|style
operator|->
name|xthickness
operator|+
name|focus_pad
operator|)
expr_stmt|;
name|height
operator|-=
literal|2
operator|*
operator|(
name|style
operator|->
name|ythickness
operator|+
name|focus_pad
operator|)
expr_stmt|;
block|}
else|else
block|{
name|x
operator|-=
name|focus_width
operator|+
name|focus_pad
expr_stmt|;
name|y
operator|-=
name|focus_width
operator|+
name|focus_pad
expr_stmt|;
name|width
operator|+=
literal|2
operator|*
operator|(
name|focus_width
operator|+
name|focus_pad
operator|)
expr_stmt|;
name|height
operator|+=
literal|2
operator|*
operator|(
name|focus_width
operator|+
name|focus_pad
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|state
operator|==
name|GTK_STATE_ACTIVE
operator|&&
name|displace_focus
condition|)
block|{
name|x
operator|+=
name|child_displacement_x
expr_stmt|;
name|y
operator|+=
name|child_displacement_y
expr_stmt|;
block|}
name|gtk_paint_focus
argument_list|(
name|style
argument_list|,
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|state
argument_list|,
operator|&
name|event
operator|->
name|area
argument_list|,
name|widget
argument_list|,
literal|"button"
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
name|gtk_container_propagate_expose
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|button
argument_list|)
argument_list|)
argument_list|,
name|event
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
else|else
block|{
return|return
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
return|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_highlightable_button_new (void)
name|gimp_highlightable_button_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_HIGHLIGHTABLE_BUTTON
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_highlightable_button_set_highlight (GimpHighlightableButton * button,gboolean highlight)
name|gimp_highlightable_button_set_highlight
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|,
name|gboolean
name|highlight
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HIGHLIGHTABLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|highlight
operator|!=
name|highlight
condition|)
block|{
name|button
operator|->
name|priv
operator|->
name|highlight
operator|=
name|highlight
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"highlight"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_highlightable_button_get_highlight (GimpHighlightableButton * button)
name|gimp_highlightable_button_get_highlight
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_HIGHLIGHTABLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|button
operator|->
name|priv
operator|->
name|highlight
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_highlightable_button_set_highlight_color (GimpHighlightableButton * button,const GimpRGB * color)
name|gimp_highlightable_button_set_highlight_color
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HIGHLIGHTABLE_BUTTON
argument_list|(
name|button
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
if|if
condition|(
name|memcmp
argument_list|(
operator|&
name|button
operator|->
name|priv
operator|->
name|highlight_color
argument_list|,
name|color
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpRGB
argument_list|)
argument_list|)
condition|)
block|{
name|button
operator|->
name|priv
operator|->
name|highlight_color
operator|=
operator|*
name|color
expr_stmt|;
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|highlight
condition|)
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"highlight-color"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_highlightable_button_get_highlight_color (GimpHighlightableButton * button,GimpRGB * color)
name|gimp_highlightable_button_get_highlight_color
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HIGHLIGHTABLE_BUTTON
argument_list|(
name|button
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
operator|*
name|color
operator|=
name|button
operator|->
name|priv
operator|->
name|highlight_color
expr_stmt|;
block|}
end_function

end_unit

