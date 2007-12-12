begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcellrenderercolor.c  * Copyright (C) 2004  Sven Neuman<sven1@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcairo-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrenderercolor.h"
end_include

begin_define
DECL|macro|DEFAULT_ICON_SIZE
define|#
directive|define
name|DEFAULT_ICON_SIZE
value|GTK_ICON_SIZE_MENU
end_define

begin_enum
enum|enum
DECL|enum|__anon2c1558890103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|,
DECL|enumerator|PROP_OPAQUE
name|PROP_OPAQUE
block|,
DECL|enumerator|PROP_SIZE
name|PROP_SIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_color_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|param_id
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
name|gimp_cell_renderer_color_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|param_id
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
name|gimp_cell_renderer_color_get_size
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkRectangle
modifier|*
name|rectangle
parameter_list|,
name|gint
modifier|*
name|x_offset
parameter_list|,
name|gint
modifier|*
name|y_offset
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_color_render
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|GdkRectangle
modifier|*
name|expose_area
parameter_list|,
name|GtkCellRendererState
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCellRendererColor,gimp_cell_renderer_color,GTK_TYPE_CELL_RENDERER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCellRendererColor
argument_list|,
argument|gimp_cell_renderer_color
argument_list|,
argument|GTK_TYPE_CELL_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cell_renderer_color_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_cell_renderer_color_class_init
parameter_list|(
name|GimpCellRendererColorClass
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
name|GtkCellRendererClass
modifier|*
name|cell_class
init|=
name|GTK_CELL_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_cell_renderer_color_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_cell_renderer_color_set_property
expr_stmt|;
name|cell_class
operator|->
name|get_size
operator|=
name|gimp_cell_renderer_color_get_size
expr_stmt|;
name|cell_class
operator|->
name|render
operator|=
name|gimp_cell_renderer_color_render
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR
argument_list|,
name|g_param_spec_boxed
argument_list|(
literal|"color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_RGB
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OPAQUE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"opaque"
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"icon-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_ICON_SIZE
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
DECL|function|gimp_cell_renderer_color_init (GimpCellRendererColor * cell)
name|gimp_cell_renderer_color_init
parameter_list|(
name|GimpCellRendererColor
modifier|*
name|cell
parameter_list|)
block|{
name|gimp_rgba_set
argument_list|(
operator|&
name|cell
operator|->
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_color_get_property (GObject * object,guint param_id,GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_color_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|param_id
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
name|GimpCellRendererColor
modifier|*
name|cell
init|=
name|GIMP_CELL_RENDERER_COLOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|param_id
condition|)
block|{
case|case
name|PROP_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|cell
operator|->
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|cell
operator|->
name|opaque
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|cell
operator|->
name|size
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|param_id
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
DECL|function|gimp_cell_renderer_color_set_property (GObject * object,guint param_id,const GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_color_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|param_id
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
name|GimpCellRendererColor
modifier|*
name|cell
init|=
name|GIMP_CELL_RENDERER_COLOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpRGB
modifier|*
name|color
decl_stmt|;
switch|switch
condition|(
name|param_id
condition|)
block|{
case|case
name|PROP_COLOR
case|:
name|color
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|cell
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
break|break;
case|case
name|PROP_OPAQUE
case|:
name|cell
operator|->
name|opaque
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIZE
case|:
name|cell
operator|->
name|size
operator|=
name|g_value_get_int
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
name|param_id
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
DECL|function|gimp_cell_renderer_color_get_size (GtkCellRenderer * cell,GtkWidget * widget,GdkRectangle * cell_area,gint * x_offset,gint * y_offset,gint * width,gint * height)
name|gimp_cell_renderer_color_get_size
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|gint
modifier|*
name|x_offset
parameter_list|,
name|gint
modifier|*
name|y_offset
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
name|GimpCellRendererColor
modifier|*
name|color
init|=
name|GIMP_CELL_RENDERER_COLOR
argument_list|(
name|cell
argument_list|)
decl_stmt|;
name|gint
name|calc_width
decl_stmt|;
name|gint
name|calc_height
decl_stmt|;
name|gtk_icon_size_lookup_for_settings
argument_list|(
name|gtk_widget_get_settings
argument_list|(
name|widget
argument_list|)
argument_list|,
name|color
operator|->
name|size
argument_list|,
operator|&
name|calc_width
argument_list|,
operator|&
name|calc_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|cell_area
operator|&&
name|calc_width
operator|>
literal|0
operator|&&
name|calc_height
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|x_offset
condition|)
block|{
operator|*
name|x_offset
operator|=
operator|(
operator|(
operator|(
name|gtk_widget_get_direction
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_TEXT_DIR_RTL
operator|)
condition|?
literal|1.0
operator|-
name|cell
operator|->
name|xalign
else|:
name|cell
operator|->
name|xalign
operator|)
operator|*
operator|(
name|cell_area
operator|->
name|width
operator|-
name|calc_width
operator|)
operator|)
expr_stmt|;
operator|*
name|x_offset
operator|=
name|MAX
argument_list|(
operator|*
name|x_offset
argument_list|,
literal|0
argument_list|)
operator|+
name|cell
operator|->
name|xpad
expr_stmt|;
block|}
if|if
condition|(
name|y_offset
condition|)
block|{
operator|*
name|y_offset
operator|=
operator|(
name|cell
operator|->
name|yalign
operator|*
operator|(
name|cell_area
operator|->
name|height
operator|-
name|calc_height
operator|)
operator|)
expr_stmt|;
operator|*
name|y_offset
operator|=
name|MAX
argument_list|(
operator|*
name|y_offset
argument_list|,
literal|0
argument_list|)
operator|+
name|cell
operator|->
name|ypad
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|x_offset
condition|)
operator|*
name|x_offset
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y_offset
condition|)
operator|*
name|y_offset
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|width
condition|)
operator|*
name|width
operator|=
name|calc_width
operator|+
literal|2
operator|*
name|cell
operator|->
name|xpad
expr_stmt|;
if|if
condition|(
name|height
condition|)
operator|*
name|height
operator|=
name|calc_height
operator|+
literal|2
operator|*
name|cell
operator|->
name|ypad
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_color_render (GtkCellRenderer * cell,GdkWindow * window,GtkWidget * widget,GdkRectangle * background_area,GdkRectangle * cell_area,GdkRectangle * expose_area,GtkCellRendererState flags)
name|gimp_cell_renderer_color_render
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|GdkRectangle
modifier|*
name|expose_area
parameter_list|,
name|GtkCellRendererState
name|flags
parameter_list|)
block|{
name|GimpCellRendererColor
modifier|*
name|color
init|=
name|GIMP_CELL_RENDERER_COLOR
argument_list|(
name|cell
argument_list|)
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|;
name|gimp_cell_renderer_color_get_size
argument_list|(
name|cell
argument_list|,
name|widget
argument_list|,
name|cell_area
argument_list|,
operator|&
name|rect
operator|.
name|x
argument_list|,
operator|&
name|rect
operator|.
name|y
argument_list|,
operator|&
name|rect
operator|.
name|width
argument_list|,
operator|&
name|rect
operator|.
name|height
argument_list|)
expr_stmt|;
name|rect
operator|.
name|x
operator|+=
name|cell_area
operator|->
name|x
operator|+
name|cell
operator|->
name|xpad
expr_stmt|;
name|rect
operator|.
name|y
operator|+=
name|cell_area
operator|->
name|y
operator|+
name|cell
operator|->
name|ypad
expr_stmt|;
name|rect
operator|.
name|width
operator|-=
literal|2
operator|*
name|cell
operator|->
name|xpad
expr_stmt|;
name|rect
operator|.
name|height
operator|-=
literal|2
operator|*
name|cell
operator|->
name|ypad
expr_stmt|;
if|if
condition|(
name|rect
operator|.
name|width
operator|>
literal|2
operator|&&
name|rect
operator|.
name|height
operator|>
literal|2
condition|)
block|{
name|cairo_t
modifier|*
name|cr
init|=
name|gdk_cairo_create
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|GtkStateType
name|state
decl_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|rect
operator|.
name|x
operator|+
literal|1
argument_list|,
name|rect
operator|.
name|y
operator|+
literal|1
argument_list|,
name|rect
operator|.
name|width
operator|-
literal|2
argument_list|,
name|rect
operator|.
name|height
operator|-
literal|2
argument_list|)
expr_stmt|;
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|color
operator|->
name|color
operator|.
name|r
argument_list|,
name|color
operator|->
name|color
operator|.
name|g
argument_list|,
name|color
operator|->
name|color
operator|.
name|b
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|color
operator|->
name|opaque
operator|&&
name|color
operator|->
name|color
operator|.
name|a
operator|!=
literal|1.0
condition|)
block|{
name|cairo_pattern_t
modifier|*
name|pattern
decl_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|rect
operator|.
name|x
operator|+
literal|1
argument_list|,
name|rect
operator|.
name|y
operator|+
name|rect
operator|.
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|rect
operator|.
name|x
operator|+
name|rect
operator|.
name|width
operator|-
literal|1
argument_list|,
name|rect
operator|.
name|y
operator|+
name|rect
operator|.
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|rect
operator|.
name|x
operator|+
name|rect
operator|.
name|width
operator|-
literal|1
argument_list|,
name|rect
operator|.
name|y
operator|+
literal|1
argument_list|)
expr_stmt|;
name|cairo_close_path
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|gimp_cairo_checkerboard_create
argument_list|(
name|cr
argument_list|,
name|GIMP_CHECK_SIZE_SM
argument_list|)
expr_stmt|;
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
name|cairo_pattern_destroy
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
name|cairo_fill_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gimp_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|color
operator|->
name|color
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
comment|/* draw border */
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|rect
operator|.
name|x
operator|+
literal|0.5
argument_list|,
name|rect
operator|.
name|y
operator|+
literal|0.5
argument_list|,
name|rect
operator|.
name|width
operator|-
literal|1
argument_list|,
name|rect
operator|.
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cell
operator|->
name|sensitive
operator|||
name|GTK_WIDGET_STATE
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_STATE_INSENSITIVE
condition|)
block|{
name|state
operator|=
name|GTK_STATE_INSENSITIVE
expr_stmt|;
block|}
else|else
block|{
name|state
operator|=
operator|(
name|flags
operator|&
name|GTK_CELL_RENDERER_SELECTED
condition|?
name|GTK_STATE_SELECTED
else|:
name|GTK_STATE_NORMAL
operator|)
expr_stmt|;
block|}
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|widget
operator|->
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
literal|1
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_cell_renderer_color_new:  *  * Creates a #GtkCellRenderer that displays a color.  *  * Return value: a new #GimpCellRendererColor  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkCellRenderer
modifier|*
DECL|function|gimp_cell_renderer_color_new (void)
name|gimp_cell_renderer_color_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CELL_RENDERER_COLOR
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

