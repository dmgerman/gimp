begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcellrendererviewable.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrendererviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpview-popup.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b2c5c4e0103
block|{
DECL|enumerator|PRE_CLICKED
name|PRE_CLICKED
block|,
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
DECL|enum|__anon2b2c5c4e0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_RENDERER
name|PROP_RENDERER
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_cell_renderer_viewable_finalize
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
name|gimp_cell_renderer_viewable_get_property
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
name|gimp_cell_renderer_viewable_set_property
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
name|gimp_cell_renderer_viewable_get_size
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
name|gimp_cell_renderer_viewable_render
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
name|gboolean
name|gimp_cell_renderer_viewable_activate
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
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|GtkCellRendererState
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCellRendererViewable
argument_list|,
argument|gimp_cell_renderer_viewable
argument_list|,
argument|GTK_TYPE_CELL_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cell_renderer_viewable_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|viewable_cell_signals
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
DECL|function|gimp_cell_renderer_viewable_class_init (GimpCellRendererViewableClass * klass)
name|gimp_cell_renderer_viewable_class_init
parameter_list|(
name|GimpCellRendererViewableClass
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
comment|/**    * GimpCellRendererViewable::pre-clicked:    * @cell:    * @path:    * @state:    *    * Called early on a viewable cell when it is clicked, typically    * before selection code is invoked for example.    *    * Returns: %TRUE if the signal handled the event and event    *          propagation should stop, for example preventing a    *          selection from happening, %FALSE to continue as normal    **/
name|viewable_cell_signals
index|[
name|PRE_CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"pre-clicked"
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
name|GimpCellRendererViewableClass
argument_list|,
name|pre_clicked
argument_list|)
argument_list|,
name|g_signal_accumulator_true_handled
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_BOOLEAN__STRING_FLAGS
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
literal|2
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|GDK_TYPE_MODIFIER_TYPE
argument_list|)
expr_stmt|;
comment|/**    * GimpCellRendererViewable::clicked:    * @cell:    * @path:    * @state:    *    * Called late on a viewable cell when it is clicked, typically    * after selection code has been invoked for example.    **/
name|viewable_cell_signals
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
name|GimpCellRendererViewableClass
argument_list|,
name|clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__STRING_FLAGS
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
name|gimp_cell_renderer_viewable_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_cell_renderer_viewable_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_cell_renderer_viewable_set_property
expr_stmt|;
name|cell_class
operator|->
name|get_size
operator|=
name|gimp_cell_renderer_viewable_get_size
expr_stmt|;
name|cell_class
operator|->
name|render
operator|=
name|gimp_cell_renderer_viewable_render
expr_stmt|;
name|cell_class
operator|->
name|activate
operator|=
name|gimp_cell_renderer_viewable_activate
expr_stmt|;
name|klass
operator|->
name|clicked
operator|=
name|NULL
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_RENDERER
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"renderer"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW_RENDERER
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_viewable_init (GimpCellRendererViewable * cellviewable)
name|gimp_cell_renderer_viewable_init
parameter_list|(
name|GimpCellRendererViewable
modifier|*
name|cellviewable
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|cellviewable
argument_list|,
literal|"mode"
argument_list|,
name|GTK_CELL_RENDERER_MODE_ACTIVATABLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cell_renderer_viewable_finalize (GObject * object)
name|gimp_cell_renderer_viewable_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCellRendererViewable
modifier|*
name|cell
init|=
name|GIMP_CELL_RENDERER_VIEWABLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|cell
operator|->
name|renderer
condition|)
block|{
name|g_object_unref
argument_list|(
name|cell
operator|->
name|renderer
argument_list|)
expr_stmt|;
name|cell
operator|->
name|renderer
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
DECL|function|gimp_cell_renderer_viewable_get_property (GObject * object,guint param_id,GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_viewable_get_property
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
name|GimpCellRendererViewable
modifier|*
name|cell
init|=
name|GIMP_CELL_RENDERER_VIEWABLE
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
name|PROP_RENDERER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|cell
operator|->
name|renderer
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
DECL|function|gimp_cell_renderer_viewable_set_property (GObject * object,guint param_id,const GValue * value,GParamSpec * pspec)
name|gimp_cell_renderer_viewable_set_property
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
name|GimpCellRendererViewable
modifier|*
name|cell
init|=
name|GIMP_CELL_RENDERER_VIEWABLE
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
name|PROP_RENDERER
case|:
block|{
name|GimpViewRenderer
modifier|*
name|renderer
init|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
decl_stmt|;
if|if
condition|(
name|cell
operator|->
name|renderer
condition|)
name|g_object_unref
argument_list|(
name|cell
operator|->
name|renderer
argument_list|)
expr_stmt|;
name|cell
operator|->
name|renderer
operator|=
name|renderer
expr_stmt|;
block|}
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
DECL|function|gimp_cell_renderer_viewable_get_size (GtkCellRenderer * cell,GtkWidget * widget,GdkRectangle * cell_area,gint * x_offset,gint * y_offset,gint * width,gint * height)
name|gimp_cell_renderer_viewable_get_size
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
name|GimpCellRendererViewable
modifier|*
name|cellviewable
decl_stmt|;
name|gfloat
name|xalign
decl_stmt|,
name|yalign
decl_stmt|;
name|gint
name|xpad
decl_stmt|,
name|ypad
decl_stmt|;
name|gint
name|view_width
init|=
literal|0
decl_stmt|;
name|gint
name|view_height
init|=
literal|0
decl_stmt|;
name|gint
name|calc_width
decl_stmt|;
name|gint
name|calc_height
decl_stmt|;
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
name|cellviewable
operator|=
name|GIMP_CELL_RENDERER_VIEWABLE
argument_list|(
name|cell
argument_list|)
expr_stmt|;
if|if
condition|(
name|cellviewable
operator|->
name|renderer
condition|)
block|{
name|view_width
operator|=
operator|(
name|cellviewable
operator|->
name|renderer
operator|->
name|width
operator|+
literal|2
operator|*
name|cellviewable
operator|->
name|renderer
operator|->
name|border_width
operator|)
expr_stmt|;
name|view_height
operator|=
operator|(
name|cellviewable
operator|->
name|renderer
operator|->
name|height
operator|+
literal|2
operator|*
name|cellviewable
operator|->
name|renderer
operator|->
name|border_width
operator|)
expr_stmt|;
block|}
name|calc_width
operator|=
operator|(
name|gint
operator|)
name|xpad
operator|*
literal|2
operator|+
name|view_width
expr_stmt|;
name|calc_height
operator|=
operator|(
name|gint
operator|)
name|ypad
operator|*
literal|2
operator|+
name|view_height
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
operator|&&
name|view_width
operator|>
literal|0
operator|&&
name|view_height
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
name|xalign
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
operator|-
literal|2
operator|*
name|xpad
operator|)
operator|)
expr_stmt|;
operator|*
name|x_offset
operator|=
operator|(
name|MAX
argument_list|(
operator|*
name|x_offset
argument_list|,
literal|0
argument_list|)
operator|+
name|xpad
operator|)
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
name|yalign
operator|*
operator|(
name|cell_area
operator|->
name|height
operator|-
name|calc_height
operator|-
literal|2
operator|*
name|ypad
operator|)
operator|)
expr_stmt|;
operator|*
name|y_offset
operator|=
operator|(
name|MAX
argument_list|(
operator|*
name|y_offset
argument_list|,
literal|0
argument_list|)
operator|+
name|ypad
operator|)
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
DECL|function|gimp_cell_renderer_viewable_render (GtkCellRenderer * cell,GdkWindow * window,GtkWidget * widget,GdkRectangle * background_area,GdkRectangle * cell_area,GdkRectangle * expose_area,GtkCellRendererState flags)
name|gimp_cell_renderer_viewable_render
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
name|GimpCellRendererViewable
modifier|*
name|cellviewable
decl_stmt|;
name|cellviewable
operator|=
name|GIMP_CELL_RENDERER_VIEWABLE
argument_list|(
name|cell
argument_list|)
expr_stmt|;
if|if
condition|(
name|cellviewable
operator|->
name|renderer
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|flags
operator|&
name|GTK_CELL_RENDERER_SELECTED
operator|)
condition|)
block|{
comment|/* this is an ugly hack. The cell state should be passed to            * the view renderer, so that it can adjust its border.            * (or something like this) */
if|if
condition|(
name|cellviewable
operator|->
name|renderer
operator|->
name|border_type
operator|==
name|GIMP_VIEW_BORDER_WHITE
condition|)
name|gimp_view_renderer_set_border_type
argument_list|(
name|cellviewable
operator|->
name|renderer
argument_list|,
name|GIMP_VIEW_BORDER_BLACK
argument_list|)
expr_stmt|;
name|gimp_view_renderer_remove_idle
argument_list|(
name|cellviewable
operator|->
name|renderer
argument_list|)
expr_stmt|;
block|}
name|gimp_view_renderer_draw
argument_list|(
name|cellviewable
operator|->
name|renderer
argument_list|,
name|window
argument_list|,
name|widget
argument_list|,
name|cell_area
argument_list|,
name|expose_area
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_cell_renderer_viewable_activate (GtkCellRenderer * cell,GdkEvent * event,GtkWidget * widget,const gchar * path,GdkRectangle * background_area,GdkRectangle * cell_area,GtkCellRendererState flags)
name|gimp_cell_renderer_viewable_activate
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
name|GdkRectangle
modifier|*
name|background_area
parameter_list|,
name|GdkRectangle
modifier|*
name|cell_area
parameter_list|,
name|GtkCellRendererState
name|flags
parameter_list|)
block|{
name|GimpCellRendererViewable
modifier|*
name|cellviewable
decl_stmt|;
name|cellviewable
operator|=
name|GIMP_CELL_RENDERER_VIEWABLE
argument_list|(
name|cell
argument_list|)
expr_stmt|;
if|if
condition|(
name|cellviewable
operator|->
name|renderer
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
if|if
condition|(
operator|!
name|event
operator|||
operator|(
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
operator|&&
operator|(
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
operator|)
operator|->
name|button
operator|==
literal|1
operator|)
condition|)
block|{
name|gimp_cell_renderer_viewable_clicked
argument_list|(
name|cellviewable
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
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GtkCellRenderer
modifier|*
DECL|function|gimp_cell_renderer_viewable_new (void)
name|gimp_cell_renderer_viewable_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CELL_RENDERER_VIEWABLE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_cell_renderer_viewable_pre_clicked (GimpCellRendererViewable * cell,const gchar * path,GdkModifierType state)
name|gimp_cell_renderer_viewable_pre_clicked
parameter_list|(
name|GimpCellRendererViewable
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
name|gboolean
name|handled
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CELL_RENDERER_VIEWABLE
argument_list|(
name|cell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|cell
argument_list|,
name|viewable_cell_signals
index|[
name|PRE_CLICKED
index|]
argument_list|,
literal|0
comment|/*detail*/
argument_list|,
name|path
argument_list|,
name|state
argument_list|,
operator|&
name|handled
argument_list|)
expr_stmt|;
return|return
name|handled
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cell_renderer_viewable_clicked (GimpCellRendererViewable * cell,const gchar * path,GdkModifierType state)
name|gimp_cell_renderer_viewable_clicked
parameter_list|(
name|GimpCellRendererViewable
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
name|GdkEvent
modifier|*
name|event
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CELL_RENDERER_VIEWABLE
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
name|viewable_cell_signals
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
name|event
operator|=
name|gtk_get_current_event
argument_list|()
expr_stmt|;
if|if
condition|(
name|event
condition|)
block|{
name|GdkEventButton
modifier|*
name|bevent
init|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
decl_stmt|;
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
operator|&&
operator|(
name|bevent
operator|->
name|button
operator|==
literal|1
operator|||
name|bevent
operator|->
name|button
operator|==
literal|2
operator|)
condition|)
block|{
name|gimp_view_popup_show
argument_list|(
name|gtk_get_event_widget
argument_list|(
name|event
argument_list|)
argument_list|,
name|bevent
argument_list|,
name|cell
operator|->
name|renderer
operator|->
name|context
argument_list|,
name|cell
operator|->
name|renderer
operator|->
name|viewable
argument_list|,
name|cell
operator|->
name|renderer
operator|->
name|width
argument_list|,
name|cell
operator|->
name|renderer
operator|->
name|height
argument_list|,
name|cell
operator|->
name|renderer
operator|->
name|dot_for_dot
argument_list|)
expr_stmt|;
block|}
name|gdk_event_free
argument_list|(
name|event
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

