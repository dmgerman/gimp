begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpoffsetarea.c  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpoffsetarea.h"
end_include

begin_comment
comment|/**  * SECTION: gimpoffsetarea  * @title: GimpOffsetArea  * @short_description: Widget to control image offsets.  *  * Widget to control image offsets.  **/
end_comment

begin_define
DECL|macro|DRAWING_AREA_SIZE
define|#
directive|define
name|DRAWING_AREA_SIZE
value|200
end_define

begin_enum
enum|enum
DECL|enum|__anon29b3ea270103
block|{
DECL|enumerator|OFFSETS_CHANGED
name|OFFSETS_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpOffsetAreaPrivate
typedef|typedef
name|struct
name|_GimpOffsetAreaPrivate
name|GimpOffsetAreaPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOffsetAreaPrivate
struct|struct
name|_GimpOffsetAreaPrivate
block|{
DECL|member|orig_width
name|gint
name|orig_width
decl_stmt|;
DECL|member|orig_height
name|gint
name|orig_height
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|offset_x
name|gint
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gint
name|offset_y
decl_stmt|;
DECL|member|display_ratio_x
name|gdouble
name|display_ratio_x
decl_stmt|;
DECL|member|display_ratio_y
name|gdouble
name|display_ratio_y
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
value|G_TYPE_INSTANCE_GET_PRIVATE (obj, \                                                       GIMP_TYPE_OFFSET_AREA, \                                                       GimpOffsetAreaPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_offset_area_resize
parameter_list|(
name|GimpOffsetArea
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_offset_area_realize
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
name|gimp_offset_area_size_allocate
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
name|gboolean
name|gimp_offset_area_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_offset_area_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOffsetArea
argument_list|,
argument|gimp_offset_area
argument_list|,
argument|GTK_TYPE_DRAWING_AREA
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_offset_area_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_offset_area_signals
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
DECL|function|gimp_offset_area_class_init (GimpOffsetAreaClass * klass)
name|gimp_offset_area_class_init
parameter_list|(
name|GimpOffsetAreaClass
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
name|gimp_offset_area_signals
index|[
name|OFFSETS_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"offsets-changed"
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
name|GimpOffsetAreaClass
argument_list|,
name|offsets_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_gimp_widgets_marshal_VOID__INT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_offset_area_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_offset_area_realize
expr_stmt|;
name|widget_class
operator|->
name|event
operator|=
name|gimp_offset_area_event
expr_stmt|;
name|widget_class
operator|->
name|draw
operator|=
name|gimp_offset_area_draw
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpOffsetAreaPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_offset_area_init (GimpOffsetArea * area)
name|gimp_offset_area_init
parameter_list|(
name|GimpOffsetArea
modifier|*
name|area
parameter_list|)
block|{
name|GimpOffsetAreaPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|area
argument_list|)
decl_stmt|;
name|private
operator|->
name|orig_width
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|orig_height
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|display_ratio_x
operator|=
literal|1.0
expr_stmt|;
name|private
operator|->
name|display_ratio_y
operator|=
literal|1.0
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_offset_area_new:  * @orig_width: the original width  * @orig_height: the original height  *  * Creates a new #GimpOffsetArea widget. A #GimpOffsetArea can be used  * when resizing an image or a drawable to allow the user to interactively  * specify the new offsets.  *  * Return value: the new #GimpOffsetArea widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_offset_area_new (gint orig_width,gint orig_height)
name|gimp_offset_area_new
parameter_list|(
name|gint
name|orig_width
parameter_list|,
name|gint
name|orig_height
parameter_list|)
block|{
name|GimpOffsetArea
modifier|*
name|area
decl_stmt|;
name|GimpOffsetAreaPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|orig_width
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|orig_height
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|area
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_OFFSET_AREA
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|area
argument_list|)
expr_stmt|;
name|private
operator|->
name|orig_width
operator|=
name|private
operator|->
name|width
operator|=
name|orig_width
expr_stmt|;
name|private
operator|->
name|orig_height
operator|=
name|private
operator|->
name|height
operator|=
name|orig_height
expr_stmt|;
name|gimp_offset_area_resize
argument_list|(
name|area
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_offset_area_set_pixbuf:  * @offset_area: a #GimpOffsetArea.  * @pixbuf: a #GdkPixbuf.  *  * Sets the pixbuf which represents the original image/drawable which  * is being offset.  *  * Since: 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_offset_area_set_pixbuf (GimpOffsetArea * area,GdkPixbuf * pixbuf)
name|gimp_offset_area_set_pixbuf
parameter_list|(
name|GimpOffsetArea
modifier|*
name|area
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OFFSET_AREA
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GDK_IS_PIXBUF
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|area
argument_list|)
argument_list|,
literal|"pixbuf"
argument_list|,
name|gdk_pixbuf_copy
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_offset_area_set_size:  * @offset_area: a #GimpOffsetArea.  * @width: the new width  * @height: the new height  *  * Sets the size of the image/drawable displayed by the #GimpOffsetArea.  * If the offsets change as a result of this change, the "offsets-changed"  * signal is emitted.  **/
end_comment

begin_function
name|void
DECL|function|gimp_offset_area_set_size (GimpOffsetArea * area,gint width,gint height)
name|gimp_offset_area_set_size
parameter_list|(
name|GimpOffsetArea
modifier|*
name|area
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpOffsetAreaPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OFFSET_AREA
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|area
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|width
operator|!=
name|width
operator|||
name|private
operator|->
name|height
operator|!=
name|height
condition|)
block|{
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|private
operator|->
name|width
operator|=
name|width
expr_stmt|;
name|private
operator|->
name|height
operator|=
name|height
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|orig_width
operator|<=
name|private
operator|->
name|width
condition|)
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|private
operator|->
name|offset_x
argument_list|,
literal|0
argument_list|,
name|private
operator|->
name|width
operator|-
name|private
operator|->
name|orig_width
argument_list|)
expr_stmt|;
else|else
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|private
operator|->
name|offset_x
argument_list|,
name|private
operator|->
name|width
operator|-
name|private
operator|->
name|orig_width
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|orig_height
operator|<=
name|private
operator|->
name|height
condition|)
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|private
operator|->
name|offset_y
argument_list|,
literal|0
argument_list|,
name|private
operator|->
name|height
operator|-
name|private
operator|->
name|orig_height
argument_list|)
expr_stmt|;
else|else
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|private
operator|->
name|offset_y
argument_list|,
name|private
operator|->
name|height
operator|-
name|private
operator|->
name|orig_height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset_x
operator|!=
name|private
operator|->
name|offset_x
operator|||
name|offset_y
operator|!=
name|private
operator|->
name|offset_y
condition|)
block|{
name|private
operator|->
name|offset_x
operator|=
name|offset_x
expr_stmt|;
name|private
operator|->
name|offset_y
operator|=
name|offset_y
expr_stmt|;
name|g_signal_emit
argument_list|(
name|area
argument_list|,
name|gimp_offset_area_signals
index|[
name|OFFSETS_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
block|}
name|gimp_offset_area_resize
argument_list|(
name|area
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_offset_area_set_offsets:  * @offset_area: a #GimpOffsetArea.  * @offset_x: the X offset  * @offset_y: the Y offset  *  * Sets the offsets of the image/drawable displayed by the #GimpOffsetArea.  * It does not emit the "offsets-changed" signal.  **/
end_comment

begin_function
name|void
DECL|function|gimp_offset_area_set_offsets (GimpOffsetArea * area,gint offset_x,gint offset_y)
name|gimp_offset_area_set_offsets
parameter_list|(
name|GimpOffsetArea
modifier|*
name|area
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GimpOffsetAreaPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OFFSET_AREA
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|area
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|offset_x
operator|!=
name|offset_x
operator|||
name|private
operator|->
name|offset_y
operator|!=
name|offset_y
condition|)
block|{
if|if
condition|(
name|private
operator|->
name|orig_width
operator|<=
name|private
operator|->
name|width
condition|)
name|private
operator|->
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|offset_x
argument_list|,
literal|0
argument_list|,
name|private
operator|->
name|width
operator|-
name|private
operator|->
name|orig_width
argument_list|)
expr_stmt|;
else|else
name|private
operator|->
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|offset_x
argument_list|,
name|private
operator|->
name|width
operator|-
name|private
operator|->
name|orig_width
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|orig_height
operator|<=
name|private
operator|->
name|height
condition|)
name|private
operator|->
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|offset_y
argument_list|,
literal|0
argument_list|,
name|private
operator|->
name|height
operator|-
name|private
operator|->
name|orig_height
argument_list|)
expr_stmt|;
else|else
name|private
operator|->
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|offset_y
argument_list|,
name|private
operator|->
name|height
operator|-
name|private
operator|->
name|orig_height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_offset_area_resize (GimpOffsetArea * area)
name|gimp_offset_area_resize
parameter_list|(
name|GimpOffsetArea
modifier|*
name|area
parameter_list|)
block|{
name|GimpOffsetAreaPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|area
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gdouble
name|ratio
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|orig_width
operator|==
literal|0
operator|||
name|private
operator|->
name|orig_height
operator|==
literal|0
condition|)
return|return;
if|if
condition|(
name|private
operator|->
name|orig_width
operator|<=
name|private
operator|->
name|width
condition|)
name|width
operator|=
name|private
operator|->
name|width
expr_stmt|;
else|else
name|width
operator|=
name|private
operator|->
name|orig_width
operator|*
literal|2
operator|-
name|private
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|orig_height
operator|<=
name|private
operator|->
name|height
condition|)
name|height
operator|=
name|private
operator|->
name|height
expr_stmt|;
else|else
name|height
operator|=
name|private
operator|->
name|orig_height
operator|*
literal|2
operator|-
name|private
operator|->
name|height
expr_stmt|;
name|ratio
operator|=
operator|(
name|gdouble
operator|)
name|DRAWING_AREA_SIZE
operator|/
operator|(
name|gdouble
operator|)
name|MAX
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|width
operator|=
name|ratio
operator|*
operator|(
name|gdouble
operator|)
name|width
expr_stmt|;
name|height
operator|=
name|ratio
operator|*
operator|(
name|gdouble
operator|)
name|height
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_offset_area_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_offset_area_size_allocate
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
name|GimpOffsetArea
modifier|*
name|area
init|=
name|GIMP_OFFSET_AREA
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpOffsetAreaPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|area
argument_list|)
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
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
name|private
operator|->
name|display_ratio_x
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|allocation
operator|->
name|width
operator|/
operator|(
operator|(
name|private
operator|->
name|orig_width
operator|<=
name|private
operator|->
name|width
operator|)
condition|?
name|private
operator|->
name|width
else|:
name|private
operator|->
name|orig_width
operator|*
literal|2
operator|-
name|private
operator|->
name|width
operator|)
operator|)
expr_stmt|;
name|private
operator|->
name|display_ratio_y
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|allocation
operator|->
name|height
operator|/
operator|(
operator|(
name|private
operator|->
name|orig_height
operator|<=
name|private
operator|->
name|height
operator|)
condition|?
name|private
operator|->
name|height
else|:
name|private
operator|->
name|orig_height
operator|*
literal|2
operator|-
name|private
operator|->
name|height
operator|)
operator|)
expr_stmt|;
name|pixbuf
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|area
argument_list|)
argument_list|,
literal|"pixbuf"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|GdkPixbuf
modifier|*
name|copy
decl_stmt|;
name|gint
name|pixbuf_width
decl_stmt|;
name|gint
name|pixbuf_height
decl_stmt|;
name|pixbuf_width
operator|=
name|private
operator|->
name|display_ratio_x
operator|*
name|private
operator|->
name|orig_width
expr_stmt|;
name|pixbuf_width
operator|=
name|MAX
argument_list|(
name|pixbuf_width
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pixbuf_height
operator|=
name|private
operator|->
name|display_ratio_y
operator|*
name|private
operator|->
name|orig_height
expr_stmt|;
name|pixbuf_height
operator|=
name|MAX
argument_list|(
name|pixbuf_height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|copy
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|area
argument_list|)
argument_list|,
literal|"pixbuf-copy"
argument_list|)
expr_stmt|;
if|if
condition|(
name|copy
operator|&&
operator|(
name|pixbuf_width
operator|!=
name|gdk_pixbuf_get_width
argument_list|(
name|copy
argument_list|)
operator|||
name|pixbuf_height
operator|!=
name|gdk_pixbuf_get_height
argument_list|(
name|copy
argument_list|)
operator|)
condition|)
block|{
name|copy
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|copy
condition|)
block|{
name|copy
operator|=
name|gdk_pixbuf_scale_simple
argument_list|(
name|pixbuf
argument_list|,
name|pixbuf_width
argument_list|,
name|pixbuf_height
argument_list|,
name|GDK_INTERP_NEAREST
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|area
argument_list|)
argument_list|,
literal|"pixbuf-copy"
argument_list|,
name|copy
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_offset_area_realize (GtkWidget * widget)
name|gimp_offset_area_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkCursor
modifier|*
name|cursor
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
name|cursor
operator|=
name|gdk_cursor_new_for_display
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GDK_FLEUR
argument_list|)
expr_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_offset_area_event (GtkWidget * widget,GdkEvent * event)
name|gimp_offset_area_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
specifier|static
name|gint
name|orig_offset_x
init|=
literal|0
decl_stmt|;
specifier|static
name|gint
name|orig_offset_y
init|=
literal|0
decl_stmt|;
specifier|static
name|gint
name|start_x
init|=
literal|0
decl_stmt|;
specifier|static
name|gint
name|start_y
init|=
literal|0
decl_stmt|;
name|GimpOffsetArea
modifier|*
name|area
init|=
name|GIMP_OFFSET_AREA
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpOffsetAreaPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|area
argument_list|)
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|orig_width
operator|==
literal|0
operator|||
name|private
operator|->
name|orig_height
operator|==
literal|0
condition|)
return|return
name|FALSE
return|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_BUTTON_PRESS
case|:
if|if
condition|(
name|event
operator|->
name|button
operator|.
name|button
operator|==
literal|1
condition|)
block|{
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|orig_offset_x
operator|=
name|private
operator|->
name|offset_x
expr_stmt|;
name|orig_offset_y
operator|=
name|private
operator|->
name|offset_y
expr_stmt|;
name|start_x
operator|=
name|event
operator|->
name|button
operator|.
name|x
expr_stmt|;
name|start_y
operator|=
name|event
operator|->
name|button
operator|.
name|y
expr_stmt|;
block|}
break|break;
case|case
name|GDK_MOTION_NOTIFY
case|:
name|offset_x
operator|=
operator|(
name|orig_offset_x
operator|+
operator|(
name|event
operator|->
name|motion
operator|.
name|x
operator|-
name|start_x
operator|)
operator|/
name|private
operator|->
name|display_ratio_x
operator|)
expr_stmt|;
name|offset_y
operator|=
operator|(
name|orig_offset_y
operator|+
operator|(
name|event
operator|->
name|motion
operator|.
name|y
operator|-
name|start_y
operator|)
operator|/
name|private
operator|->
name|display_ratio_y
operator|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|offset_x
operator|!=
name|offset_x
operator|||
name|private
operator|->
name|offset_y
operator|!=
name|offset_y
condition|)
block|{
name|gimp_offset_area_set_offsets
argument_list|(
name|area
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|area
argument_list|,
name|gimp_offset_area_signals
index|[
name|OFFSETS_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|private
operator|->
name|offset_x
argument_list|,
name|private
operator|->
name|offset_y
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
if|if
condition|(
name|event
operator|->
name|button
operator|.
name|button
operator|==
literal|1
condition|)
block|{
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|start_x
operator|=
name|start_y
operator|=
literal|0
expr_stmt|;
block|}
break|break;
default|default:
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_offset_area_draw (GtkWidget * widget,cairo_t * cr)
name|gimp_offset_area_draw
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpOffsetArea
modifier|*
name|area
init|=
name|GIMP_OFFSET_AREA
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpOffsetAreaPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|area
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
name|GtkAllocation
name|allocation
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|x
operator|=
operator|(
name|private
operator|->
name|display_ratio_x
operator|*
operator|(
operator|(
name|private
operator|->
name|orig_width
operator|<=
name|private
operator|->
name|width
operator|)
condition|?
name|private
operator|->
name|offset_x
else|:
name|private
operator|->
name|offset_x
operator|+
name|private
operator|->
name|orig_width
operator|-
name|private
operator|->
name|width
operator|)
operator|)
expr_stmt|;
name|y
operator|=
operator|(
name|private
operator|->
name|display_ratio_y
operator|*
operator|(
operator|(
name|private
operator|->
name|orig_height
operator|<=
name|private
operator|->
name|height
operator|)
condition|?
name|private
operator|->
name|offset_y
else|:
name|private
operator|->
name|offset_y
operator|+
name|private
operator|->
name|orig_height
operator|-
name|private
operator|->
name|height
operator|)
operator|)
expr_stmt|;
name|w
operator|=
name|private
operator|->
name|display_ratio_x
operator|*
name|private
operator|->
name|orig_width
expr_stmt|;
name|w
operator|=
name|MAX
argument_list|(
name|w
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|h
operator|=
name|private
operator|->
name|display_ratio_y
operator|*
name|private
operator|->
name|orig_height
expr_stmt|;
name|h
operator|=
name|MAX
argument_list|(
name|h
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"pixbuf-copy"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|gdk_cairo_set_source_pixbuf
argument_list|(
name|cr
argument_list|,
name|pixbuf
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
operator|+
literal|0.5
argument_list|,
name|y
operator|+
literal|0.5
argument_list|,
name|w
operator|-
literal|1
argument_list|,
name|h
operator|-
literal|1
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_render_frame
argument_list|(
name|context
argument_list|,
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|orig_width
operator|>
name|private
operator|->
name|width
operator|||
name|private
operator|->
name|orig_height
operator|>
name|private
operator|->
name|height
condition|)
block|{
name|gint
name|line_width
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|orig_width
operator|>
name|private
operator|->
name|width
condition|)
block|{
name|x
operator|=
name|private
operator|->
name|display_ratio_x
operator|*
operator|(
name|private
operator|->
name|orig_width
operator|-
name|private
operator|->
name|width
operator|)
expr_stmt|;
name|w
operator|=
name|private
operator|->
name|display_ratio_x
operator|*
name|private
operator|->
name|width
expr_stmt|;
block|}
else|else
block|{
name|x
operator|=
operator|-
literal|1
expr_stmt|;
name|w
operator|=
name|allocation
operator|.
name|width
operator|+
literal|2
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|orig_height
operator|>
name|private
operator|->
name|height
condition|)
block|{
name|y
operator|=
name|private
operator|->
name|display_ratio_y
operator|*
operator|(
name|private
operator|->
name|orig_height
operator|-
name|private
operator|->
name|height
operator|)
expr_stmt|;
name|h
operator|=
name|private
operator|->
name|display_ratio_y
operator|*
name|private
operator|->
name|height
expr_stmt|;
block|}
else|else
block|{
name|y
operator|=
operator|-
literal|1
expr_stmt|;
name|h
operator|=
name|allocation
operator|.
name|height
operator|+
literal|2
expr_stmt|;
block|}
name|w
operator|=
name|MAX
argument_list|(
name|w
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|h
operator|=
name|MAX
argument_list|(
name|h
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|line_width
operator|=
name|MIN
argument_list|(
literal|3
argument_list|,
name|MIN
argument_list|(
name|w
argument_list|,
name|h
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|line_width
operator|/
literal|2.0
argument_list|,
name|y
operator|+
name|line_width
operator|/
literal|2.0
argument_list|,
name|MAX
argument_list|(
name|w
operator|-
name|line_width
argument_list|,
literal|1
argument_list|)
argument_list|,
name|MAX
argument_list|(
name|h
operator|-
name|line_width
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
name|line_width
argument_list|)
expr_stmt|;
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.6
argument_list|)
expr_stmt|;
name|cairo_stroke_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.8
argument_list|)
expr_stmt|;
name|cairo_stroke
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

end_unit

