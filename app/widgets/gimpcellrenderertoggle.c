begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcellrenderertoggle.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpcellrenderertoggle.h"
end_include

begin_define
DECL|macro|DEFAULT_ICON_SIZE
define|#
directive|define
name|DEFAULT_ICON_SIZE
value|GTK_ICON_SIZE_BUTTON
end_define

begin_enum
enum|enum
DECL|enum|__anon2989f0dd0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_STOCK_ID
name|PROP_STOCK_ID
block|,
DECL|enumerator|PROP_STOCK_SIZE
name|PROP_STOCK_SIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_toggle_class_init
parameter_list|(
name|GimpCellRendererToggleClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_toggle_init
parameter_list|(
name|GimpCellRendererToggle
modifier|*
name|toggle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_toggle_finalize
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
name|gimp_cell_renderer_toggle_get_property
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
name|gimp_cell_renderer_toggle_set_property
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
name|gimp_cell_renderer_toggle_get_size
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
name|gimp_cell_renderer_toggle_render
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

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_toggle_create_pixbuf
parameter_list|(
name|GimpCellRendererToggle
modifier|*
name|toggle
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkCellRendererToggleClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_cell_renderer_toggle_get_type (void)
name|gimp_cell_renderer_toggle_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|cell_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|cell_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|cell_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpCellRendererToggleClass
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
name|gimp_cell_renderer_toggle_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpCellRendererToggle
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_cell_renderer_toggle_init
block|,       }
decl_stmt|;
name|cell_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_CELL_RENDERER_TOGGLE
argument_list|,
literal|"GimpCellRendererToggle"
argument_list|,
operator|&
name|cell_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|cell_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_class_init (GimpCellRendererToggleClass * klass)
name|gimp_cell_renderer_toggle_class_init
parameter_list|(
name|GimpCellRendererToggleClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkCellRendererClass
modifier|*
name|cell_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|cell_class
operator|=
name|GTK_CELL_RENDERER_CLASS
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
name|finalize
operator|=
name|gimp_cell_renderer_toggle_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_cell_renderer_toggle_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_cell_renderer_toggle_set_property
expr_stmt|;
name|cell_class
operator|->
name|get_size
operator|=
name|gimp_cell_renderer_toggle_get_size
expr_stmt|;
name|cell_class
operator|->
name|render
operator|=
name|gimp_cell_renderer_toggle_render
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_STOCK_ID
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"stock_id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_STOCK_SIZE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"stock_size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_ICON_SIZE
argument_list|,
name|DEFAULT_ICON_SIZE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_init (GimpCellRendererToggle * cell)
name|gimp_cell_renderer_toggle_init
parameter_list|(
name|GimpCellRendererToggle
modifier|*
name|cell
parameter_list|)
block|{
name|GTK_CELL_RENDERER
argument_list|(
name|cell
argument_list|)
operator|->
name|xpad
operator|=
literal|0
expr_stmt|;
name|GTK_CELL_RENDERER
argument_list|(
name|cell
argument_list|)
operator|->
name|ypad
operator|=
literal|0
expr_stmt|;
name|cell
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
name|cell
operator|->
name|stock_size
operator|=
name|DEFAULT_ICON_SIZE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_finalize (GObject * object)
name|gimp_cell_renderer_toggle_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCellRendererToggle
modifier|*
name|toggle
decl_stmt|;
name|toggle
operator|=
name|GIMP_CELL_RENDERER_TOGGLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|toggle
operator|->
name|stock_id
condition|)
block|{
name|g_free
argument_list|(
name|toggle
operator|->
name|stock_id
argument_list|)
expr_stmt|;
name|toggle
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|toggle
operator|->
name|pixbuf
condition|)
block|{
name|g_object_unref
argument_list|(
name|toggle
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|toggle
operator|->
name|pixbuf
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_cell_renderer_toggle_get_property (GObject * object,guint param_id,GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_toggle_get_property
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
name|GimpCellRendererToggle
modifier|*
name|toggle
decl_stmt|;
name|toggle
operator|=
name|GIMP_CELL_RENDERER_TOGGLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|param_id
condition|)
block|{
case|case
name|PROP_STOCK_ID
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|toggle
operator|->
name|stock_id
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STOCK_SIZE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|toggle
operator|->
name|stock_size
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
DECL|function|gimp_cell_renderer_toggle_set_property (GObject * object,guint param_id,const GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_toggle_set_property
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
name|GimpCellRendererToggle
modifier|*
name|toggle
decl_stmt|;
name|toggle
operator|=
name|GIMP_CELL_RENDERER_TOGGLE
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|param_id
condition|)
block|{
case|case
name|PROP_STOCK_ID
case|:
if|if
condition|(
name|toggle
operator|->
name|stock_id
condition|)
name|g_free
argument_list|(
name|toggle
operator|->
name|stock_id
argument_list|)
expr_stmt|;
name|toggle
operator|->
name|stock_id
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STOCK_SIZE
case|:
name|toggle
operator|->
name|stock_size
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
name|param_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|toggle
operator|->
name|pixbuf
condition|)
block|{
name|g_object_unref
argument_list|(
name|toggle
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|toggle
operator|->
name|pixbuf
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_get_size (GtkCellRenderer * cell,GtkWidget * widget,GdkRectangle * cell_area,gint * x_offset,gint * y_offset,gint * width,gint * height)
name|gimp_cell_renderer_toggle_get_size
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
name|GimpCellRendererToggle
modifier|*
name|toggle
decl_stmt|;
name|gint
name|calc_width
decl_stmt|;
name|gint
name|calc_height
decl_stmt|;
name|gint
name|pixbuf_width
decl_stmt|;
name|gint
name|pixbuf_height
decl_stmt|;
name|toggle
operator|=
name|GIMP_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|toggle
operator|->
name|stock_id
condition|)
block|{
name|GTK_CELL_RENDERER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_size
argument_list|(
name|cell
argument_list|,
name|widget
argument_list|,
name|cell_area
argument_list|,
name|x_offset
argument_list|,
name|y_offset
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|toggle
operator|->
name|pixbuf
condition|)
name|gimp_cell_renderer_toggle_create_pixbuf
argument_list|(
name|toggle
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|pixbuf_width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|toggle
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|pixbuf_height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|toggle
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|calc_width
operator|=
operator|(
name|pixbuf_width
operator|+
operator|(
name|gint
operator|)
name|cell
operator|->
name|xpad
operator|*
literal|2
operator|+
name|widget
operator|->
name|style
operator|->
name|xthickness
operator|*
literal|2
operator|)
expr_stmt|;
name|calc_height
operator|=
operator|(
name|pixbuf_height
operator|+
operator|(
name|gint
operator|)
name|cell
operator|->
name|ypad
operator|*
literal|2
operator|+
name|widget
operator|->
name|style
operator|->
name|ythickness
operator|*
literal|2
operator|)
expr_stmt|;
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
operator|(
literal|1.0
operator|-
name|cell
operator|->
name|xalign
operator|)
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
name|calc_height
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
expr_stmt|;
block|}
block|}
if|if
condition|(
name|width
condition|)
operator|*
name|width
operator|=
name|calc_width
expr_stmt|;
if|if
condition|(
name|height
condition|)
operator|*
name|height
operator|=
name|calc_height
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_render (GtkCellRenderer * cell,GdkWindow * window,GtkWidget * widget,GdkRectangle * background_area,GdkRectangle * cell_area,GdkRectangle * expose_area,GtkCellRendererState flags)
name|gimp_cell_renderer_toggle_render
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
name|GimpCellRendererToggle
modifier|*
name|toggle
decl_stmt|;
name|GdkRectangle
name|toggle_rect
decl_stmt|;
name|GdkRectangle
name|draw_rect
decl_stmt|;
name|GtkStateType
name|state
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|toggle
operator|=
name|GIMP_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|toggle
operator|->
name|stock_id
condition|)
block|{
name|GTK_CELL_RENDERER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|render
argument_list|(
name|cell
argument_list|,
name|window
argument_list|,
name|widget
argument_list|,
name|background_area
argument_list|,
name|cell_area
argument_list|,
name|expose_area
argument_list|,
name|flags
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_cell_renderer_toggle_get_size
argument_list|(
name|cell
argument_list|,
name|widget
argument_list|,
name|cell_area
argument_list|,
operator|&
name|toggle_rect
operator|.
name|x
argument_list|,
operator|&
name|toggle_rect
operator|.
name|y
argument_list|,
operator|&
name|toggle_rect
operator|.
name|width
argument_list|,
operator|&
name|toggle_rect
operator|.
name|height
argument_list|)
expr_stmt|;
name|toggle_rect
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
name|toggle_rect
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
name|toggle_rect
operator|.
name|width
operator|-=
name|cell
operator|->
name|xpad
operator|*
literal|2
expr_stmt|;
name|toggle_rect
operator|.
name|height
operator|-=
name|cell
operator|->
name|ypad
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|toggle_rect
operator|.
name|width
operator|<=
literal|0
operator|||
name|toggle_rect
operator|.
name|height
operator|<=
literal|0
condition|)
return|return;
name|active
operator|=
name|gtk_cell_renderer_toggle_get_active
argument_list|(
name|GTK_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
argument_list|)
expr_stmt|;
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
else|else
block|{
if|if
condition|(
name|GTK_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
operator|->
name|activatable
condition|)
name|state
operator|=
name|GTK_STATE_NORMAL
expr_stmt|;
else|else
name|state
operator|=
name|GTK_STATE_INSENSITIVE
expr_stmt|;
block|}
if|if
condition|(
name|gdk_rectangle_intersect
argument_list|(
name|expose_area
argument_list|,
name|cell_area
argument_list|,
operator|&
name|draw_rect
argument_list|)
operator|&&
operator|(
name|flags
operator|&
name|GTK_CELL_RENDERER_PRELIT
operator|)
condition|)
name|gtk_paint_shadow
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|window
argument_list|,
name|state
argument_list|,
name|active
condition|?
name|GTK_SHADOW_IN
else|:
name|GTK_SHADOW_OUT
argument_list|,
operator|&
name|draw_rect
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
name|toggle_rect
operator|.
name|x
argument_list|,
name|toggle_rect
operator|.
name|y
argument_list|,
name|toggle_rect
operator|.
name|width
argument_list|,
name|toggle_rect
operator|.
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
block|{
name|toggle_rect
operator|.
name|x
operator|+=
name|widget
operator|->
name|style
operator|->
name|xthickness
expr_stmt|;
name|toggle_rect
operator|.
name|y
operator|+=
name|widget
operator|->
name|style
operator|->
name|ythickness
expr_stmt|;
name|toggle_rect
operator|.
name|width
operator|-=
name|widget
operator|->
name|style
operator|->
name|xthickness
operator|*
literal|2
expr_stmt|;
name|toggle_rect
operator|.
name|height
operator|-=
name|widget
operator|->
name|style
operator|->
name|ythickness
operator|*
literal|2
expr_stmt|;
if|if
condition|(
name|gdk_rectangle_intersect
argument_list|(
operator|&
name|draw_rect
argument_list|,
operator|&
name|toggle_rect
argument_list|,
operator|&
name|draw_rect
argument_list|)
condition|)
name|gdk_draw_pixbuf
argument_list|(
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|toggle
operator|->
name|pixbuf
argument_list|,
comment|/* pixbuf 0, 0 is at toggle_rect.x, toggle_rect.y */
name|draw_rect
operator|.
name|x
operator|-
name|toggle_rect
operator|.
name|x
argument_list|,
name|draw_rect
operator|.
name|y
operator|-
name|toggle_rect
operator|.
name|y
argument_list|,
name|draw_rect
operator|.
name|x
argument_list|,
name|draw_rect
operator|.
name|y
argument_list|,
name|draw_rect
operator|.
name|width
argument_list|,
name|draw_rect
operator|.
name|height
argument_list|,
name|GDK_RGB_DITHER_NORMAL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_create_pixbuf (GimpCellRendererToggle * toggle,GtkWidget * widget)
name|gimp_cell_renderer_toggle_create_pixbuf
parameter_list|(
name|GimpCellRendererToggle
modifier|*
name|toggle
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
if|if
condition|(
name|toggle
operator|->
name|pixbuf
condition|)
name|g_object_unref
argument_list|(
name|toggle
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|toggle
operator|->
name|pixbuf
operator|=
name|gtk_widget_render_icon
argument_list|(
name|widget
argument_list|,
name|toggle
operator|->
name|stock_id
argument_list|,
name|toggle
operator|->
name|stock_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkCellRenderer
modifier|*
DECL|function|gimp_cell_renderer_toggle_new (const gchar * stock_id)
name|gimp_cell_renderer_toggle_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CELL_RENDERER_TOGGLE
argument_list|,
literal|"stock_id"
argument_list|,
name|stock_id
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

