begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppaletteview.c  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
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
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimppaletteview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererpalette.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bf1d4720103
block|{
DECL|enumerator|ENTRY_CLICKED
name|ENTRY_CLICKED
block|,
DECL|enumerator|ENTRY_SELECTED
name|ENTRY_SELECTED
block|,
DECL|enumerator|ENTRY_ACTIVATED
name|ENTRY_ACTIVATED
block|,
DECL|enumerator|ENTRY_CONTEXT
name|ENTRY_CONTEXT
block|,
DECL|enumerator|COLOR_DROPPED
name|COLOR_DROPPED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|gboolean
name|gimp_palette_view_expose
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
name|gimp_palette_view_button_press
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
name|gimp_palette_view_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_palette_view_focus
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkDirectionType
name|direction
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_set_viewable
parameter_list|(
name|GimpView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|old_viewable
parameter_list|,
name|GimpViewable
modifier|*
name|new_viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpPaletteEntry
modifier|*
name|gimp_palette_view_find_entry
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_expose_entry
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_invalidate
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|GimpPaletteView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_drag_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPaletteView
argument_list|,
argument|gimp_palette_view
argument_list|,
argument|GIMP_TYPE_VIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_palette_view_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|view_signals
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
DECL|function|gimp_palette_view_class_init (GimpPaletteViewClass * klass)
name|gimp_palette_view_class_init
parameter_list|(
name|GimpPaletteViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewClass
modifier|*
name|view_class
init|=
name|GIMP_VIEW_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|view_signals
index|[
name|ENTRY_CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"entry-clicked"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPaletteViewClass
argument_list|,
name|entry_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER_ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|GDK_TYPE_MODIFIER_TYPE
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|ENTRY_SELECTED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"entry-selected"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPaletteViewClass
argument_list|,
name|entry_selected
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|ENTRY_ACTIVATED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"entry-activated"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPaletteViewClass
argument_list|,
name|entry_activated
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|ENTRY_CONTEXT
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"entry-context"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPaletteViewClass
argument_list|,
name|entry_context
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|view_signals
index|[
name|COLOR_DROPPED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color-dropped"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPaletteViewClass
argument_list|,
name|color_dropped
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__POINTER_BOXED
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_POINTER
argument_list|,
name|GIMP_TYPE_RGB
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_palette_view_expose
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_palette_view_button_press
expr_stmt|;
name|widget_class
operator|->
name|key_press_event
operator|=
name|gimp_palette_view_key_press
expr_stmt|;
name|widget_class
operator|->
name|focus
operator|=
name|gimp_palette_view_focus
expr_stmt|;
name|view_class
operator|->
name|set_viewable
operator|=
name|gimp_palette_view_set_viewable
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_view_init (GimpPaletteView * view)
name|gimp_palette_view_init
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|)
block|{
name|gtk_widget_set_can_focus
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|view
operator|->
name|selected
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|dnd_entry
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_palette_view_expose (GtkWidget * widget,GdkEventExpose * eevent)
name|gimp_palette_view_expose
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
name|GimpPaletteView
modifier|*
name|pal_view
init|=
name|GIMP_PALETTE_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpView
modifier|*
name|view
init|=
name|GIMP_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_is_drawable
argument_list|(
name|widget
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|expose_event
argument_list|(
name|widget
argument_list|,
name|eevent
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|renderer
operator|->
name|viewable
operator|&&
name|pal_view
operator|->
name|selected
condition|)
block|{
name|GimpViewRendererPalette
modifier|*
name|renderer
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
name|GtkAllocation
name|allocation
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|renderer
operator|=
name|GIMP_VIEW_RENDERER_PALETTE
argument_list|(
name|view
operator|->
name|renderer
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
name|row
operator|=
name|pal_view
operator|->
name|selected
operator|->
name|position
operator|/
name|renderer
operator|->
name|columns
expr_stmt|;
name|col
operator|=
name|pal_view
operator|->
name|selected
operator|->
name|position
operator|%
name|renderer
operator|->
name|columns
expr_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
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
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|allocation
operator|.
name|x
argument_list|,
name|allocation
operator|.
name|y
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|col
operator|*
name|renderer
operator|->
name|cell_width
operator|+
literal|0.5
argument_list|,
name|row
operator|*
name|renderer
operator|->
name|cell_height
operator|+
literal|0.5
argument_list|,
name|renderer
operator|->
name|cell_width
argument_list|,
name|renderer
operator|->
name|cell_height
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|fg
index|[
name|GTK_STATE_SELECTED
index|]
argument_list|)
expr_stmt|;
name|cairo_stroke_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_cairo_set_focus_line_pattern
argument_list|(
name|cr
argument_list|,
name|widget
argument_list|)
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
name|GTK_STATE_NORMAL
index|]
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
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_palette_view_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_palette_view_button_press
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
name|GimpPaletteView
modifier|*
name|view
init|=
name|GIMP_PALETTE_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
if|if
condition|(
name|gtk_widget_get_can_focus
argument_list|(
name|widget
argument_list|)
operator|&&
operator|!
name|gtk_widget_has_focus
argument_list|(
name|widget
argument_list|)
condition|)
name|gtk_widget_grab_focus
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_palette_view_find_entry
argument_list|(
name|view
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
name|view
operator|->
name|dnd_entry
operator|=
name|entry
expr_stmt|;
if|if
condition|(
operator|!
name|entry
operator|||
name|bevent
operator|->
name|button
operator|==
literal|2
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|ENTRY_CLICKED
index|]
argument_list|,
literal|0
argument_list|,
name|entry
argument_list|,
name|bevent
operator|->
name|state
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bevent
operator|->
name|button
condition|)
block|{
case|case
literal|1
case|:
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
name|gimp_palette_view_select_entry
argument_list|(
name|view
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
operator|&&
name|entry
operator|==
name|view
operator|->
name|selected
condition|)
block|{
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|ENTRY_ACTIVATED
index|]
argument_list|,
literal|0
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
if|if
condition|(
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
if|if
condition|(
name|entry
operator|!=
name|view
operator|->
name|selected
condition|)
name|gimp_palette_view_select_entry
argument_list|(
name|view
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|ENTRY_CONTEXT
index|]
argument_list|,
literal|0
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_palette_view_key_press (GtkWidget * widget,GdkEventKey * kevent)
name|gimp_palette_view_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
block|{
name|GimpPaletteView
modifier|*
name|view
init|=
name|GIMP_PALETTE_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|selected
operator|&&
operator|(
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_space
operator|||
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_KP_Space
operator|||
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_Return
operator|||
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_KP_Enter
operator|||
name|kevent
operator|->
name|keyval
operator|==
name|GDK_KEY_ISO_Enter
operator|)
condition|)
block|{
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|ENTRY_CLICKED
index|]
argument_list|,
literal|0
argument_list|,
name|view
operator|->
name|selected
argument_list|,
name|kevent
operator|->
name|state
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
DECL|function|gimp_palette_view_focus (GtkWidget * widget,GtkDirectionType direction)
name|gimp_palette_view_focus
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkDirectionType
name|direction
parameter_list|)
block|{
name|GimpPaletteView
modifier|*
name|view
init|=
name|GIMP_PALETTE_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_get_can_focus
argument_list|(
name|widget
argument_list|)
operator|&&
operator|!
name|gtk_widget_has_focus
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|gtk_widget_grab_focus
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
operator|->
name|selected
operator|&&
name|palette
operator|&&
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|>
literal|0
condition|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|gimp_palette_get_entry
argument_list|(
name|palette
argument_list|,
literal|0
argument_list|)
decl_stmt|;
name|gimp_palette_view_select_entry
argument_list|(
name|view
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|view
operator|->
name|selected
condition|)
block|{
name|GimpViewRendererPalette
modifier|*
name|renderer
decl_stmt|;
name|gint
name|skip
init|=
literal|0
decl_stmt|;
name|renderer
operator|=
name|GIMP_VIEW_RENDERER_PALETTE
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|direction
condition|)
block|{
case|case
name|GTK_DIR_UP
case|:
name|skip
operator|=
operator|-
name|renderer
operator|->
name|columns
expr_stmt|;
break|break;
case|case
name|GTK_DIR_DOWN
case|:
name|skip
operator|=
name|renderer
operator|->
name|columns
expr_stmt|;
break|break;
case|case
name|GTK_DIR_LEFT
case|:
name|skip
operator|=
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GTK_DIR_RIGHT
case|:
name|skip
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GTK_DIR_TAB_FORWARD
case|:
case|case
name|GTK_DIR_TAB_BACKWARD
case|:
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|skip
operator|!=
literal|0
condition|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|gint
name|position
decl_stmt|;
name|position
operator|=
name|view
operator|->
name|selected
operator|->
name|position
operator|+
name|skip
expr_stmt|;
name|entry
operator|=
name|gimp_palette_get_entry
argument_list|(
name|palette
argument_list|,
name|position
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
condition|)
name|gimp_palette_view_select_entry
argument_list|(
name|view
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_palette_view_set_viewable (GimpView * view,GimpViewable * old_viewable,GimpViewable * new_viewable)
name|gimp_palette_view_set_viewable
parameter_list|(
name|GimpView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|old_viewable
parameter_list|,
name|GimpViewable
modifier|*
name|new_viewable
parameter_list|)
block|{
name|GimpPaletteView
modifier|*
name|pal_view
init|=
name|GIMP_PALETTE_VIEW
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|pal_view
operator|->
name|dnd_entry
operator|=
name|NULL
expr_stmt|;
name|gimp_palette_view_select_entry
argument_list|(
name|pal_view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_viewable
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|old_viewable
argument_list|,
name|gimp_palette_view_invalidate
argument_list|,
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|new_viewable
condition|)
block|{
name|gimp_dnd_color_source_remove
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_remove
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|GIMP_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_viewable
argument_list|(
name|view
argument_list|,
name|old_viewable
argument_list|,
name|new_viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_viewable
condition|)
block|{
name|g_signal_connect
argument_list|(
name|new_viewable
argument_list|,
literal|"invalidate-preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_palette_view_invalidate
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
comment|/*  unset the palette drag handler set by GimpView  */
name|gimp_dnd_viewable_source_remove
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|GIMP_TYPE_PALETTE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|old_viewable
condition|)
block|{
name|gimp_dnd_color_source_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|gimp_palette_view_drag_color
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|gimp_palette_view_drop_color
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_palette_view_select_entry (GimpPaletteView * view,GimpPaletteEntry * entry)
name|gimp_palette_view_select_entry
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|==
name|view
operator|->
name|selected
condition|)
return|return;
if|if
condition|(
name|view
operator|->
name|selected
condition|)
name|gimp_palette_view_expose_entry
argument_list|(
name|view
argument_list|,
name|view
operator|->
name|selected
argument_list|)
expr_stmt|;
name|view
operator|->
name|selected
operator|=
name|entry
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|selected
condition|)
name|gimp_palette_view_expose_entry
argument_list|(
name|view
argument_list|,
name|view
operator|->
name|selected
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|ENTRY_SELECTED
index|]
argument_list|,
literal|0
argument_list|,
name|view
operator|->
name|selected
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private funcions  */
end_comment

begin_function
specifier|static
name|GimpPaletteEntry
modifier|*
DECL|function|gimp_palette_view_find_entry (GimpPaletteView * view,gint x,gint y)
name|gimp_palette_view_find_entry
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GimpViewRendererPalette
modifier|*
name|renderer
decl_stmt|;
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|NULL
decl_stmt|;
name|gint
name|col
decl_stmt|,
name|row
decl_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|GIMP_VIEW_RENDERER_PALETTE
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|palette
condition|)
return|return
name|NULL
return|;
name|col
operator|=
name|x
operator|/
name|renderer
operator|->
name|cell_width
expr_stmt|;
name|row
operator|=
name|y
operator|/
name|renderer
operator|->
name|cell_height
expr_stmt|;
if|if
condition|(
name|col
operator|>=
literal|0
operator|&&
name|col
operator|<
name|renderer
operator|->
name|columns
operator|&&
name|row
operator|>=
literal|0
operator|&&
name|row
operator|<
name|renderer
operator|->
name|rows
condition|)
block|{
name|entry
operator|=
name|gimp_palette_get_entry
argument_list|(
name|palette
argument_list|,
name|row
operator|*
name|renderer
operator|->
name|columns
operator|+
name|col
argument_list|)
expr_stmt|;
block|}
return|return
name|entry
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_view_expose_entry (GimpPaletteView * view,GimpPaletteEntry * entry)
name|gimp_palette_view_expose_entry
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GimpViewRendererPalette
modifier|*
name|renderer
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|renderer
operator|=
name|GIMP_VIEW_RENDERER_PALETTE
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
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
name|row
operator|=
name|entry
operator|->
name|position
operator|/
name|renderer
operator|->
name|columns
expr_stmt|;
name|col
operator|=
name|entry
operator|->
name|position
operator|%
name|renderer
operator|->
name|columns
expr_stmt|;
name|gtk_widget_queue_draw_area
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|allocation
operator|.
name|x
operator|+
name|col
operator|*
name|renderer
operator|->
name|cell_width
argument_list|,
name|allocation
operator|.
name|y
operator|+
name|row
operator|*
name|renderer
operator|->
name|cell_height
argument_list|,
name|renderer
operator|->
name|cell_width
operator|+
literal|1
argument_list|,
name|renderer
operator|->
name|cell_height
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_view_invalidate (GimpPalette * palette,GimpPaletteView * view)
name|gimp_palette_view_invalidate
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|GimpPaletteView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|dnd_entry
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|selected
operator|&&
operator|!
name|g_list_find
argument_list|(
name|gimp_palette_get_colors
argument_list|(
name|palette
argument_list|)
argument_list|,
name|view
operator|->
name|selected
argument_list|)
condition|)
block|{
name|gimp_palette_view_select_entry
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_view_drag_color (GtkWidget * widget,GimpRGB * color,gpointer data)
name|gimp_palette_view_drag_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteView
modifier|*
name|view
init|=
name|GIMP_PALETTE_VIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|dnd_entry
condition|)
operator|*
name|color
operator|=
name|view
operator|->
name|dnd_entry
operator|->
name|color
expr_stmt|;
else|else
name|gimp_rgba_set
argument_list|(
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
DECL|function|gimp_palette_view_drop_color (GtkWidget * widget,gint x,gint y,const GimpRGB * color,gpointer data)
name|gimp_palette_view_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaletteView
modifier|*
name|view
init|=
name|GIMP_PALETTE_VIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|entry
operator|=
name|gimp_palette_view_find_entry
argument_list|(
name|view
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|view_signals
index|[
name|COLOR_DROPPED
index|]
argument_list|,
literal|0
argument_list|,
name|entry
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

