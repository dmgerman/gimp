begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcellrendererdashes.c  * Copyright (C) 2005 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<config.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdashpattern.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrendererdashes.h"
end_include

begin_define
DECL|macro|DASHES_WIDTH
define|#
directive|define
name|DASHES_WIDTH
value|96
end_define

begin_define
DECL|macro|DASHES_HEIGHT
define|#
directive|define
name|DASHES_HEIGHT
value|4
end_define

begin_define
DECL|macro|N_SEGMENTS
define|#
directive|define
name|N_SEGMENTS
value|24
end_define

begin_define
DECL|macro|BLOCK_WIDTH
define|#
directive|define
name|BLOCK_WIDTH
value|(DASHES_WIDTH / (2 * N_SEGMENTS))
end_define

begin_enum
enum|enum
DECL|enum|__anon278ae00c0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PATTERN
name|PROP_PATTERN
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_dashes_finalize
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
name|gimp_cell_renderer_dashes_get_property
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
name|gimp_cell_renderer_dashes_set_property
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
name|gimp_cell_renderer_dashes_get_size
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
name|gimp_cell_renderer_dashes_render
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
DECL|function|G_DEFINE_TYPE (GimpCellRendererDashes,gimp_cell_renderer_dashes,GTK_TYPE_CELL_RENDERER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCellRendererDashes
argument_list|,
argument|gimp_cell_renderer_dashes
argument_list|,
argument|GTK_TYPE_CELL_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cell_renderer_dashes_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_cell_renderer_dashes_class_init
parameter_list|(
name|GimpCellRendererDashesClass
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
name|finalize
operator|=
name|gimp_cell_renderer_dashes_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_cell_renderer_dashes_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_cell_renderer_dashes_set_property
expr_stmt|;
name|cell_class
operator|->
name|get_size
operator|=
name|gimp_cell_renderer_dashes_get_size
expr_stmt|;
name|cell_class
operator|->
name|render
operator|=
name|gimp_cell_renderer_dashes_render
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PATTERN
argument_list|,
name|g_param_spec_boxed
argument_list|(
literal|"pattern"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DASH_PATTERN
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
DECL|function|gimp_cell_renderer_dashes_init (GimpCellRendererDashes * dashes)
name|gimp_cell_renderer_dashes_init
parameter_list|(
name|GimpCellRendererDashes
modifier|*
name|dashes
parameter_list|)
block|{
name|dashes
operator|->
name|segments
operator|=
name|g_new0
argument_list|(
name|gboolean
argument_list|,
name|N_SEGMENTS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_dashes_finalize (GObject * object)
name|gimp_cell_renderer_dashes_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCellRendererDashes
modifier|*
name|dashes
init|=
name|GIMP_CELL_RENDERER_DASHES
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|dashes
operator|->
name|segments
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_dashes_get_property (GObject * object,guint param_id,GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_dashes_get_property
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
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|param_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_dashes_set_property (GObject * object,guint param_id,const GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_dashes_set_property
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
name|GimpCellRendererDashes
modifier|*
name|dashes
init|=
name|GIMP_CELL_RENDERER_DASHES
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
name|PROP_PATTERN
case|:
name|gimp_dash_pattern_fill_segments
argument_list|(
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
argument_list|,
name|dashes
operator|->
name|segments
argument_list|,
name|N_SEGMENTS
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
DECL|function|gimp_cell_renderer_dashes_get_size (GtkCellRenderer * cell,GtkWidget * widget,GdkRectangle * cell_area,gint * x_offset,gint * y_offset,gint * width,gint * height)
name|gimp_cell_renderer_dashes_get_size
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
if|if
condition|(
name|cell_area
condition|)
block|{
if|if
condition|(
name|x_offset
condition|)
block|{
name|gdouble
name|align
decl_stmt|;
name|align
operator|=
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
expr_stmt|;
operator|*
name|x_offset
operator|=
name|align
operator|*
operator|(
name|cell_area
operator|->
name|width
operator|-
name|DASHES_WIDTH
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
name|cell
operator|->
name|yalign
operator|*
operator|(
name|cell_area
operator|->
name|height
operator|-
name|DASHES_HEIGHT
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
operator|*
name|width
operator|=
name|DASHES_WIDTH
operator|+
literal|2
operator|*
name|cell
operator|->
name|xpad
expr_stmt|;
operator|*
name|height
operator|=
name|DASHES_HEIGHT
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
DECL|function|gimp_cell_renderer_dashes_render (GtkCellRenderer * cell,GdkWindow * window,GtkWidget * widget,GdkRectangle * background_area,GdkRectangle * cell_area,GdkRectangle * expose_area,GtkCellRendererState flags)
name|gimp_cell_renderer_dashes_render
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
name|GimpCellRendererDashes
modifier|*
name|dashes
init|=
name|GIMP_CELL_RENDERER_DASHES
argument_list|(
name|cell
argument_list|)
decl_stmt|;
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
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
if|if
condition|(
operator|!
name|cell
operator|->
name|sensitive
condition|)
block|{
name|state
operator|=
name|GTK_STATE_INSENSITIVE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|flags
operator|&
name|GTK_CELL_RENDERER_SELECTED
operator|)
operator|==
name|GTK_CELL_RENDERER_SELECTED
condition|)
block|{
if|if
condition|(
name|GTK_WIDGET_HAS_FOCUS
argument_list|(
name|widget
argument_list|)
condition|)
name|state
operator|=
name|GTK_STATE_SELECTED
expr_stmt|;
else|else
name|state
operator|=
name|GTK_STATE_ACTIVE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|flags
operator|&
name|GTK_CELL_RENDERER_PRELIT
operator|)
operator|==
name|GTK_CELL_RENDERER_PRELIT
operator|&&
name|GTK_WIDGET_STATE
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_STATE_PRELIGHT
condition|)
block|{
name|state
operator|=
name|GTK_STATE_PRELIGHT
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|GTK_WIDGET_STATE
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_STATE_INSENSITIVE
condition|)
name|state
operator|=
name|GTK_STATE_INSENSITIVE
expr_stmt|;
else|else
name|state
operator|=
name|GTK_STATE_NORMAL
expr_stmt|;
block|}
name|y
operator|=
name|cell_area
operator|->
name|y
operator|+
operator|(
name|cell_area
operator|->
name|height
operator|-
name|DASHES_HEIGHT
operator|)
operator|/
literal|2
expr_stmt|;
name|width
operator|=
name|cell_area
operator|->
name|width
operator|-
literal|2
operator|*
name|cell
operator|->
name|xpad
expr_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|gdk_cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|expose_area
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|+
name|BLOCK_WIDTH
condition|;
name|x
operator|+=
name|BLOCK_WIDTH
control|)
block|{
name|guint
name|index
init|=
operator|(
operator|(
name|guint
operator|)
name|x
operator|/
name|BLOCK_WIDTH
operator|)
operator|%
name|N_SEGMENTS
decl_stmt|;
if|if
condition|(
name|dashes
operator|->
name|segments
index|[
name|index
index|]
condition|)
block|{
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|cell_area
operator|->
name|x
operator|+
name|cell
operator|->
name|xpad
operator|+
name|x
argument_list|,
name|y
argument_list|,
name|MIN
argument_list|(
name|BLOCK_WIDTH
argument_list|,
name|width
operator|-
name|x
argument_list|)
argument_list|,
name|DASHES_HEIGHT
argument_list|)
expr_stmt|;
block|}
block|}
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|text
index|[
name|state
index|]
argument_list|)
expr_stmt|;
name|cairo_fill
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
end_function

begin_function
name|GtkCellRenderer
modifier|*
DECL|function|gimp_cell_renderer_dashes_new (void)
name|gimp_cell_renderer_dashes_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CELL_RENDERER_DASHES
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

