begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcellrenderertoggle.c  * Copyright (C) 2003-2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrenderertoggle.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcellrenderertoggle  * @title: GimpCellRendererToggle  * @short_description: A #GtkCellRendererToggle that displays icons instead  *                     of a checkbox.  *  * A #GtkCellRendererToggle that displays icons instead of a checkbox.  **/
end_comment

begin_define
DECL|macro|DEFAULT_ICON_SIZE
define|#
directive|define
name|DEFAULT_ICON_SIZE
value|16
end_define

begin_enum
enum|enum
DECL|enum|__anon2a24a06b0103
block|{
DECL|enumerator|CLICKED
name|CLICKED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a24a06b0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ICON_NAME
name|PROP_ICON_NAME
block|,
DECL|enumerator|PROP_ICON_SIZE
name|PROP_ICON_SIZE
block|,
DECL|enumerator|PROP_OVERRIDE_BACKGROUND
name|PROP_OVERRIDE_BACKGROUND
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpCellRendererTogglePrivate
struct|struct
name|_GimpCellRendererTogglePrivate
block|{
DECL|member|icon_name
name|gchar
modifier|*
name|icon_name
decl_stmt|;
DECL|member|icon_size
name|gint
name|icon_size
decl_stmt|;
DECL|member|override_background
name|gboolean
name|override_background
decl_stmt|;
DECL|member|pixbuf
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(((GimpCellRendererToggle *) (obj))->priv)
end_define

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
specifier|const
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
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|GtkCellRendererState
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_cell_renderer_toggle_activate
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|cell_area
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

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCellRendererToggle
argument_list|,
argument|gimp_cell_renderer_toggle
argument_list|,
argument|GTK_TYPE_CELL_RENDERER_TOGGLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cell_renderer_toggle_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|toggle_cell_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

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
name|toggle_cell_signals
index|[
name|CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"clicked"
argument_list|,
name|G_OBJECT_CLASS_TYPE
argument_list|(
name|object_class
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpCellRendererToggleClass
argument_list|,
name|clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__STRING_FLAGS
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|GDK_TYPE_MODIFIER_TYPE
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
name|cell_class
operator|->
name|activate
operator|=
name|gimp_cell_renderer_toggle_activate
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ICON_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"icon-name"
argument_list|,
literal|"Icon Name"
argument_list|,
literal|"The icon to display"
argument_list|,
name|NULL
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
name|PROP_ICON_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"icon-size"
argument_list|,
literal|"Icon Size"
argument_list|,
literal|"The desired icon size to use in pixel (before applying scaling factor)"
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OVERRIDE_BACKGROUND
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"override-background"
argument_list|,
literal|"Override Background"
argument_list|,
literal|"Draw the background if the row is selected"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCellRendererTogglePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_init (GimpCellRendererToggle * toggle)
name|gimp_cell_renderer_toggle_init
parameter_list|(
name|GimpCellRendererToggle
modifier|*
name|toggle
parameter_list|)
block|{
name|toggle
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|toggle
argument_list|,
name|GIMP_TYPE_CELL_RENDERER_TOGGLE
argument_list|,
name|GimpCellRendererTogglePrivate
argument_list|)
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
name|GimpCellRendererTogglePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|priv
operator|->
name|icon_name
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|priv
operator|->
name|pixbuf
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
name|GimpCellRendererTogglePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
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
name|PROP_ICON_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|icon_name
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ICON_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|icon_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OVERRIDE_BACKGROUND
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|override_background
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
name|GimpCellRendererTogglePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
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
name|PROP_ICON_NAME
case|:
if|if
condition|(
name|priv
operator|->
name|icon_name
condition|)
name|g_free
argument_list|(
name|priv
operator|->
name|icon_name
argument_list|)
expr_stmt|;
name|priv
operator|->
name|icon_name
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ICON_SIZE
case|:
name|priv
operator|->
name|icon_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OVERRIDE_BACKGROUND
case|:
name|priv
operator|->
name|override_background
operator|=
name|g_value_get_boolean
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
name|g_clear_object
argument_list|(
operator|&
name|priv
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_get_size (GtkCellRenderer * cell,GtkWidget * widget,const GdkRectangle * cell_area,gint * x_offset,gint * y_offset,gint * width,gint * height)
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
specifier|const
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
init|=
name|GIMP_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
decl_stmt|;
name|GimpCellRendererTogglePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|cell
argument_list|)
decl_stmt|;
name|GtkStyleContext
modifier|*
name|context
init|=
name|gtk_widget_get_style_context
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkBorder
name|border
decl_stmt|;
name|gint
name|scale_factor
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
name|gfloat
name|xalign
decl_stmt|;
name|gfloat
name|yalign
decl_stmt|;
name|gint
name|xpad
decl_stmt|;
name|gint
name|ypad
decl_stmt|;
name|scale_factor
operator|=
name|gtk_widget_get_scale_factor
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|priv
operator|->
name|icon_name
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
name|gtk_style_context_save
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gtk_cell_renderer_get_alignment
argument_list|(
name|cell
argument_list|,
operator|&
name|xalign
argument_list|,
operator|&
name|yalign
argument_list|)
expr_stmt|;
name|gtk_cell_renderer_get_padding
argument_list|(
name|cell
argument_list|,
operator|&
name|xpad
argument_list|,
operator|&
name|ypad
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|priv
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
name|priv
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|pixbuf_height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|priv
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
comment|/* The pixbuf size may be bigger than the logical size. */
name|calc_width
operator|=
name|pixbuf_width
operator|/
name|scale_factor
operator|+
operator|(
name|gint
operator|)
name|xpad
operator|*
literal|2
expr_stmt|;
name|calc_height
operator|=
name|pixbuf_height
operator|/
name|scale_factor
operator|+
operator|(
name|gint
operator|)
name|ypad
operator|*
literal|2
expr_stmt|;
name|gtk_style_context_add_class
argument_list|(
name|context
argument_list|,
name|GTK_STYLE_CLASS_BUTTON
argument_list|)
expr_stmt|;
name|gtk_style_context_get_border
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
operator|&
name|border
argument_list|)
expr_stmt|;
name|calc_width
operator|+=
name|border
operator|.
name|left
operator|+
name|border
operator|.
name|right
expr_stmt|;
name|calc_height
operator|+=
name|border
operator|.
name|top
operator|+
name|border
operator|.
name|bottom
expr_stmt|;
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
name|xalign
operator|)
else|:
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
name|gtk_style_context_restore
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_toggle_render (GtkCellRenderer * cell,cairo_t * cr,GtkWidget * widget,const GdkRectangle * background_area,const GdkRectangle * cell_area,GtkCellRendererState flags)
name|gimp_cell_renderer_toggle_render
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|GtkCellRendererState
name|flags
parameter_list|)
block|{
name|GimpCellRendererTogglePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|cell
argument_list|)
decl_stmt|;
name|GtkStyleContext
modifier|*
name|context
init|=
name|gtk_widget_get_style_context
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GdkRectangle
name|toggle_rect
decl_stmt|;
name|GtkStateFlags
name|state
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|gint
name|scale_factor
decl_stmt|;
name|gint
name|xpad
decl_stmt|;
name|gint
name|ypad
decl_stmt|;
name|scale_factor
operator|=
name|gtk_widget_get_scale_factor
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|priv
operator|->
name|icon_name
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
name|cr
argument_list|,
name|widget
argument_list|,
name|background_area
argument_list|,
name|cell_area
argument_list|,
name|flags
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|(
name|flags
operator|&
name|GTK_CELL_RENDERER_SELECTED
operator|)
operator|&&
name|priv
operator|->
name|override_background
condition|)
block|{
name|gboolean
name|background_set
decl_stmt|;
name|g_object_get
argument_list|(
name|cell
argument_list|,
literal|"cell-background-set"
argument_list|,
operator|&
name|background_set
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|background_set
condition|)
block|{
name|GdkRGBA
modifier|*
name|color
decl_stmt|;
name|g_object_get
argument_list|(
name|cell
argument_list|,
literal|"cell-background-rgba"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|background_area
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gdk_rgba_free
argument_list|(
name|color
argument_list|)
expr_stmt|;
block|}
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
name|gtk_style_context_save
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gtk_style_context_add_class
argument_list|(
name|context
argument_list|,
name|GTK_STYLE_CLASS_BUTTON
argument_list|)
expr_stmt|;
name|gtk_cell_renderer_get_padding
argument_list|(
name|cell
argument_list|,
operator|&
name|xpad
argument_list|,
operator|&
name|ypad
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
name|ypad
expr_stmt|;
name|toggle_rect
operator|.
name|width
operator|-=
name|xpad
operator|*
literal|2
expr_stmt|;
name|toggle_rect
operator|.
name|height
operator|-=
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
name|state
operator|=
name|gtk_cell_renderer_get_state
argument_list|(
name|cell
argument_list|,
name|widget
argument_list|,
name|flags
argument_list|)
expr_stmt|;
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
name|active
condition|)
name|state
operator||=
name|GTK_STATE_FLAG_ACTIVE
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_cell_renderer_toggle_get_activatable
argument_list|(
name|GTK_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
argument_list|)
condition|)
name|state
operator||=
name|GTK_STATE_FLAG_INSENSITIVE
expr_stmt|;
name|gtk_style_context_set_state
argument_list|(
name|context
argument_list|,
name|state
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|&
name|GTK_STATE_FLAG_PRELIGHT
condition|)
name|gtk_render_frame
argument_list|(
name|context
argument_list|,
name|cr
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
name|GtkBorder
name|border
decl_stmt|;
name|gboolean
name|inconsistent
decl_stmt|;
name|gtk_style_context_get_border
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
operator|&
name|border
argument_list|)
expr_stmt|;
name|toggle_rect
operator|.
name|x
operator|+=
name|border
operator|.
name|left
expr_stmt|;
name|toggle_rect
operator|.
name|x
operator|*=
name|scale_factor
expr_stmt|;
name|toggle_rect
operator|.
name|y
operator|+=
name|border
operator|.
name|top
expr_stmt|;
name|toggle_rect
operator|.
name|y
operator|*=
name|scale_factor
expr_stmt|;
name|toggle_rect
operator|.
name|width
operator|-=
name|border
operator|.
name|left
operator|+
name|border
operator|.
name|right
expr_stmt|;
name|toggle_rect
operator|.
name|height
operator|-=
name|border
operator|.
name|top
operator|+
name|border
operator|.
name|bottom
expr_stmt|;
comment|/* For high DPI displays, pixbuf size is bigger than logical size. */
name|cairo_scale
argument_list|(
name|cr
argument_list|,
operator|(
name|gdouble
operator|)
literal|1.0
operator|/
name|scale_factor
argument_list|,
operator|(
name|gdouble
operator|)
literal|1.0
operator|/
name|scale_factor
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_pixbuf
argument_list|(
name|cr
argument_list|,
name|priv
operator|->
name|pixbuf
argument_list|,
name|toggle_rect
operator|.
name|x
argument_list|,
name|toggle_rect
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|cell
argument_list|,
literal|"inconsistent"
argument_list|,
operator|&
name|inconsistent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|inconsistent
condition|)
block|{
name|GdkRGBA
name|color
decl_stmt|;
name|gtk_style_context_get_color
argument_list|(
name|context
argument_list|,
name|state
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.5
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|toggle_rect
operator|.
name|x
operator|+
name|toggle_rect
operator|.
name|width
operator|-
literal|1
argument_list|,
name|toggle_rect
operator|.
name|y
operator|+
literal|1
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|toggle_rect
operator|.
name|x
operator|+
literal|1
argument_list|,
name|toggle_rect
operator|.
name|y
operator|+
name|toggle_rect
operator|.
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_style_context_restore
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_cell_renderer_toggle_activate (GtkCellRenderer * cell,GdkEvent * event,GtkWidget * widget,const gchar * path,const GdkRectangle * background_area,const GdkRectangle * cell_area,GtkCellRendererState flags)
name|gimp_cell_renderer_toggle_activate
parameter_list|(
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|GtkCellRendererState
name|flags
parameter_list|)
block|{
name|GtkCellRendererToggle
modifier|*
name|toggle
init|=
name|GTK_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_cell_renderer_toggle_get_activatable
argument_list|(
name|toggle
argument_list|)
condition|)
block|{
name|GdkModifierType
name|state
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|event
operator|&&
operator|(
operator|(
name|GdkEventAny
operator|*
operator|)
name|event
operator|)
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
name|state
operator|=
operator|(
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
operator|)
operator|->
name|state
expr_stmt|;
name|gimp_cell_renderer_toggle_clicked
argument_list|(
name|GIMP_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
argument_list|,
name|path
argument_list|,
name|state
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
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
name|GimpCellRendererTogglePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|toggle
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|priv
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|icon_name
condition|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GtkIconTheme
modifier|*
name|icon_theme
decl_stmt|;
name|GtkIconInfo
modifier|*
name|icon_info
decl_stmt|;
name|gchar
modifier|*
name|icon_name
decl_stmt|;
name|gint
name|scale_factor
decl_stmt|;
name|scale_factor
operator|=
name|gtk_widget_get_scale_factor
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|icon_theme
operator|=
name|gtk_icon_theme_get_for_screen
argument_list|(
name|screen
argument_list|)
expr_stmt|;
comment|/* Look for symbolic and fallback to color icon. */
name|icon_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-symbolic"
argument_list|,
name|priv
operator|->
name|icon_name
argument_list|)
expr_stmt|;
name|icon_info
operator|=
name|gtk_icon_theme_lookup_icon_for_scale
argument_list|(
name|icon_theme
argument_list|,
name|icon_name
argument_list|,
name|priv
operator|->
name|icon_size
argument_list|,
name|scale_factor
argument_list|,
name|GTK_ICON_LOOKUP_GENERIC_FALLBACK
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|icon_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|icon_info
condition|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|pixbuf
operator|=
name|gtk_icon_info_load_symbolic_for_context
argument_list|(
name|icon_info
argument_list|,
name|gtk_widget_get_style_context
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|->
name|pixbuf
operator|=
name|pixbuf
expr_stmt|;
name|g_object_unref
argument_list|(
name|icon_info
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_cell_renderer_toggle_new:  * @icon_name: the icon name of the icon to use for the active state  *  * Creates a custom version of the #GtkCellRendererToggle. Instead of  * showing the standard toggle button, it shows a named icon if the  * cell is active and no icon otherwise. This cell renderer is for  * example used in the Layers treeview to indicate and control the  * layer's visibility by showing %GIMP_STOCK_VISIBLE.  *  * Return value: a new #GimpCellRendererToggle  *  * Since: 2.2  **/
end_comment

begin_function
name|GtkCellRenderer
modifier|*
DECL|function|gimp_cell_renderer_toggle_new (const gchar * icon_name)
name|gimp_cell_renderer_toggle_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CELL_RENDERER_TOGGLE
argument_list|,
literal|"icon-name"
argument_list|,
name|icon_name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_cell_renderer_toggle_clicked:  * @cell:  a #GimpCellRendererToggle  * @path:  the path to the clicked row  * @state: the modifier state  *  * Emits the "clicked" signal from a #GimpCellRendererToggle.  *  * Since: 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_cell_renderer_toggle_clicked (GimpCellRendererToggle * cell,const gchar * path,GdkModifierType state)
name|gimp_cell_renderer_toggle_clicked
parameter_list|(
name|GimpCellRendererToggle
modifier|*
name|cell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CELL_RENDERER_TOGGLE
argument_list|(
name|cell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|cell
argument_list|,
name|toggle_cell_signals
index|[
name|CLICKED
index|]
argument_list|,
literal|0
argument_list|,
name|path
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

