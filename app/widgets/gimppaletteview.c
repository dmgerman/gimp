begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppaletteview.c  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimppaletteview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererpalette.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28ff9b120103
block|{
DECL|enumerator|ENTRY_SELECTED
name|ENTRY_SELECTED
block|,
DECL|enumerator|ENTRY_ACTIVATED
name|ENTRY_ACTIVATED
block|,
DECL|enumerator|ENTRY_CONTEXT
name|ENTRY_CONTEXT
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_class_init
parameter_list|(
name|GimpPaletteViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_init
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_view_realize
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
name|gimp_palette_view_unrealize
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
name|gimp_palette_view_draw_selected
parameter_list|(
name|GimpPaletteView
modifier|*
name|view
parameter_list|,
name|GdkRectangle
modifier|*
name|area
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

begin_decl_stmt
DECL|variable|view_signals
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_palette_view_get_type (void)
name|gimp_palette_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPaletteViewClass
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
name|gimp_palette_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpPaletteView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_palette_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEW
argument_list|,
literal|"GimpPaletteView"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
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
name|widget_class
operator|->
name|realize
operator|=
name|gimp_palette_view_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_palette_view_unrealize
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
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|view
argument_list|,
name|GTK_CAN_FOCUS
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
name|view
operator|->
name|gc
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_view_realize (GtkWidget * widget)
name|gimp_palette_view_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|view
operator|->
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_gc_set_function
argument_list|(
name|view
operator|->
name|gc
argument_list|,
name|GDK_INVERT
argument_list|)
expr_stmt|;
name|gdk_gc_set_line_attributes
argument_list|(
name|view
operator|->
name|gc
argument_list|,
literal|1
argument_list|,
name|GDK_LINE_SOLID
argument_list|,
name|GDK_CAP_BUTT
argument_list|,
name|GDK_JOIN_ROUND
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_view_unrealize (GtkWidget * widget)
name|gimp_palette_view_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gc
condition|)
block|{
name|g_object_unref
argument_list|(
name|view
operator|->
name|gc
argument_list|)
expr_stmt|;
name|view
operator|->
name|gc
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
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
condition|)
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
name|selected
condition|)
name|gimp_palette_view_draw_selected
argument_list|(
name|view
argument_list|,
operator|&
name|eevent
operator|->
name|area
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
name|row
decl_stmt|,
name|col
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
name|col
operator|=
name|bevent
operator|->
name|x
operator|/
name|renderer
operator|->
name|cell_width
expr_stmt|;
name|row
operator|=
name|bevent
operator|->
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
name|g_list_nth_data
argument_list|(
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
operator|->
name|colors
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
name|FALSE
return|;
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
name|pal_view
operator|->
name|selected
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|old_viewable
condition|)
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|old_viewable
argument_list|,
name|gimp_palette_view_invalidate
argument_list|,
name|view
argument_list|)
expr_stmt|;
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
name|widget
operator|->
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
name|widget
operator|->
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
DECL|function|gimp_palette_view_draw_selected (GimpPaletteView * pal_view,GdkRectangle * area)
name|gimp_palette_view_draw_selected
parameter_list|(
name|GimpPaletteView
modifier|*
name|pal_view
parameter_list|,
name|GdkRectangle
modifier|*
name|area
parameter_list|)
block|{
name|GimpView
modifier|*
name|view
init|=
name|GIMP_VIEW
argument_list|(
name|pal_view
argument_list|)
decl_stmt|;
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
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpViewRendererPalette
modifier|*
name|renderer
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
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|pal_view
operator|->
name|gc
argument_list|,
name|area
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|pal_view
operator|->
name|gc
argument_list|,
name|FALSE
argument_list|,
name|widget
operator|->
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
name|widget
operator|->
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
argument_list|,
name|renderer
operator|->
name|cell_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|pal_view
operator|->
name|gc
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
name|palette
operator|->
name|colors
argument_list|,
name|view
operator|->
name|selected
argument_list|)
condition|)
name|view
operator|->
name|selected
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

