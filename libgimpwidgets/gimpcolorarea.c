begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpcolorarea.c  * Copyright (C) 2001 Sven Neumann  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorarea.h"
end_include

begin_define
DECL|macro|DRAG_PREVIEW_SIZE
define|#
directive|define
name|DRAG_PREVIEW_SIZE
value|32
end_define

begin_define
DECL|macro|DRAG_ICON_OFFSET
define|#
directive|define
name|DRAG_ICON_OFFSET
value|-8
end_define

begin_enum
enum|enum
DECL|enum|__anon2c4220e30103
block|{
DECL|enumerator|COLOR_CHANGED
name|COLOR_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_color_area_class_init
parameter_list|(
name|GimpColorAreaClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_area_init
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_area_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_area_size_allocate
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
name|gimp_color_area_expose
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

begin_function_decl
specifier|static
name|void
name|gimp_color_area_update
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_area_idle_update
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_area_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_area_drag_end
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_area_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection_data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_area_drag_data_get
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection_data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|targets
specifier|static
specifier|const
name|GtkTargetEntry
name|targets
index|[]
init|=
block|{
block|{
literal|"application/x-color"
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_color_area_signals
specifier|static
name|guint
name|gimp_color_area_signals
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
name|GtkDrawingAreaClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_color_area_get_type (void)
name|gimp_color_area_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|gca_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|gca_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|gca_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorAreaClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_color_area_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorArea
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_area_init
block|,       }
decl_stmt|;
name|gca_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_DRAWING_AREA
argument_list|,
literal|"GimpColorArea"
argument_list|,
operator|&
name|gca_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|gca_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_class_init (GimpColorAreaClass * klass)
name|gimp_color_area_class_init
parameter_list|(
name|GimpColorAreaClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
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
name|gimp_color_area_signals
index|[
name|COLOR_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color_changed"
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
name|GimpColorAreaClass
argument_list|,
name|color_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_color_area_destroy
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_color_area_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_color_area_expose
expr_stmt|;
name|widget_class
operator|->
name|drag_begin
operator|=
name|gimp_color_area_drag_begin
expr_stmt|;
name|widget_class
operator|->
name|drag_end
operator|=
name|gimp_color_area_drag_end
expr_stmt|;
name|widget_class
operator|->
name|drag_data_received
operator|=
name|gimp_color_area_drag_data_received
expr_stmt|;
name|widget_class
operator|->
name|drag_data_get
operator|=
name|gimp_color_area_drag_data_get
expr_stmt|;
name|klass
operator|->
name|color_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_init (GimpColorArea * gca)
name|gimp_color_area_init
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|)
block|{
name|gimp_rgba_set
argument_list|(
operator|&
name|gca
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
name|gca
operator|->
name|buf
operator|=
name|NULL
expr_stmt|;
name|gca
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|gca
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|gca
operator|->
name|rowstride
operator|=
literal|0
expr_stmt|;
name|gca
operator|->
name|type
operator|=
name|GIMP_COLOR_AREA_FLAT
expr_stmt|;
name|gca
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_destroy (GtkObject * object)
name|gimp_color_area_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorArea
modifier|*
name|gca
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_AREA
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|gca
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|gca
operator|->
name|buf
condition|)
block|{
name|g_free
argument_list|(
name|gca
operator|->
name|buf
argument_list|)
expr_stmt|;
name|gca
operator|->
name|buf
operator|=
name|NULL
expr_stmt|;
name|gca
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|gca
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|gca
operator|->
name|rowstride
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|gca
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|gca
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|gca
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_color_area_size_allocate
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
name|GimpColorArea
modifier|*
name|gca
decl_stmt|;
name|gca
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
condition|)
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
name|widget
operator|->
name|allocation
operator|.
name|width
operator|!=
name|gca
operator|->
name|width
operator|||
name|widget
operator|->
name|allocation
operator|.
name|height
operator|!=
name|gca
operator|->
name|height
condition|)
block|{
name|gca
operator|->
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|gca
operator|->
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
name|gca
operator|->
name|rowstride
operator|=
operator|(
name|gca
operator|->
name|width
operator|*
literal|3
operator|+
literal|3
operator|)
operator|&
operator|~
literal|0x3
expr_stmt|;
name|g_free
argument_list|(
name|gca
operator|->
name|buf
argument_list|)
expr_stmt|;
name|gca
operator|->
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|gca
operator|->
name|rowstride
operator|*
name|gca
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_color_area_update
argument_list|(
name|gca
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_area_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_color_area_expose
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
name|GimpColorArea
modifier|*
name|gca
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gca
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
operator|||
operator|!
name|gca
operator|->
name|buf
operator|||
name|gca
operator|->
name|idle_id
condition|)
return|return
name|FALSE
return|;
name|buf
operator|=
name|gca
operator|->
name|buf
operator|+
name|event
operator|->
name|area
operator|.
name|y
operator|*
name|gca
operator|->
name|rowstride
operator|+
name|event
operator|->
name|area
operator|.
name|x
operator|*
literal|3
expr_stmt|;
name|gdk_draw_rgb_image_dithalign
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
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|event
operator|->
name|area
operator|.
name|y
argument_list|,
name|event
operator|->
name|area
operator|.
name|width
argument_list|,
name|event
operator|->
name|area
operator|.
name|height
argument_list|,
name|GDK_RGB_DITHER_MAX
argument_list|,
name|buf
argument_list|,
name|gca
operator|->
name|rowstride
argument_list|,
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|event
operator|->
name|area
operator|.
name|y
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_area_new:  * @color:     A pointer to a #GimpRGB struct.  * @type:      The type of color area to create.  * @drag_mask: The event_mask that should trigger drags.  *   * Creates a new #GimpColorArea widget.  *  * This returns a preview area showing the color. It handles color  * DND. If the color changes, the "color_changed" signal is emitted.  *   * Returns: Pointer to the new #GimpColorArea widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_area_new (const GimpRGB * color,GimpColorAreaType type,GdkModifierType drag_mask)
name|gimp_color_area_new
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|,
name|GdkModifierType
name|drag_mask
parameter_list|)
block|{
name|GimpColorArea
modifier|*
name|gca
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gca
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_AREA
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gca
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
name|gca
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|gca
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|targets
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
comment|/*  do we need this ??  */
name|drag_mask
operator|&=
operator|(
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
operator||
name|GDK_BUTTON3_MASK
operator|)
expr_stmt|;
if|if
condition|(
name|drag_mask
condition|)
name|gtk_drag_source_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|gca
argument_list|)
argument_list|,
name|drag_mask
argument_list|,
name|targets
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
operator||
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|gca
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_area_set_color:  * @gca: Pointer to a #GimpColorArea.  * @color:  *   **/
end_comment

begin_function
name|void
DECL|function|gimp_color_area_set_color (GimpColorArea * gca,const GimpRGB * color)
name|gimp_color_area_set_color
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_AREA
argument_list|(
name|gca
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
name|gimp_rgba_distance
argument_list|(
operator|&
name|gca
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|>
literal|0.000001
condition|)
block|{
name|gca
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
name|gimp_color_area_update
argument_list|(
name|gca
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|gca
argument_list|)
argument_list|,
name|gimp_color_area_signals
index|[
name|COLOR_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_area_get_color (GimpColorArea * gca,GimpRGB * color)
name|gimp_color_area_get_color
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_AREA
argument_list|(
name|gca
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
name|gca
operator|->
name|color
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_color_area_has_alpha (GimpColorArea * gca)
name|gimp_color_area_has_alpha
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_AREA
argument_list|(
name|gca
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gca
operator|->
name|type
operator|!=
name|GIMP_COLOR_AREA_FLAT
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_area_set_type (GimpColorArea * gca,GimpColorAreaType type)
name|gimp_color_area_set_type
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_AREA
argument_list|(
name|gca
argument_list|)
argument_list|)
expr_stmt|;
name|gca
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|gimp_color_area_update
argument_list|(
name|gca
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_update (GimpColorArea * gca)
name|gimp_color_area_update
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_AREA
argument_list|(
name|gca
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gca
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|gca
operator|->
name|idle_id
argument_list|)
expr_stmt|;
block|}
name|gca
operator|->
name|idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_color_area_idle_update
argument_list|,
name|gca
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_area_idle_update (gpointer data)
name|gimp_color_area_idle_update
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpColorArea
modifier|*
name|gca
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|guint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|guint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|guint
name|check_size
init|=
literal|0
decl_stmt|;
name|guchar
name|light
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|dark
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|opaque
index|[
literal|3
index|]
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
name|gdouble
name|frac
decl_stmt|;
name|gca
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gca
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_REALIZED
argument_list|(
name|widget
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
name|gca
operator|->
name|buf
condition|)
return|return
name|FALSE
return|;
name|width
operator|=
name|gca
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|gca
operator|->
name|height
expr_stmt|;
switch|switch
condition|(
name|gca
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_COLOR_AREA_FLAT
case|:
name|check_size
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_AREA_SMALL_CHECKS
case|:
name|check_size
operator|=
name|GIMP_CHECK_SIZE_SM
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_AREA_LARGE_CHECKS
case|:
name|check_size
operator|=
name|GIMP_CHECK_SIZE
expr_stmt|;
break|break;
block|}
name|opaque
index|[
literal|0
index|]
operator|=
name|gca
operator|->
name|color
operator|.
name|r
operator|*
literal|255.999
expr_stmt|;
name|opaque
index|[
literal|1
index|]
operator|=
name|gca
operator|->
name|color
operator|.
name|g
operator|*
literal|255.999
expr_stmt|;
name|opaque
index|[
literal|2
index|]
operator|=
name|gca
operator|->
name|color
operator|.
name|b
operator|*
literal|255.999
expr_stmt|;
if|if
condition|(
name|check_size
operator|&&
name|gca
operator|->
name|color
operator|.
name|a
operator|<
literal|1.0
condition|)
block|{
name|light
index|[
literal|0
index|]
operator|=
operator|(
name|GIMP_CHECK_LIGHT
operator|+
operator|(
name|gca
operator|->
name|color
operator|.
name|r
operator|-
name|GIMP_CHECK_LIGHT
operator|)
operator|*
name|gca
operator|->
name|color
operator|.
name|a
operator|)
operator|*
literal|255.999
expr_stmt|;
name|dark
index|[
literal|0
index|]
operator|=
operator|(
name|GIMP_CHECK_DARK
operator|+
operator|(
name|gca
operator|->
name|color
operator|.
name|r
operator|-
name|GIMP_CHECK_DARK
operator|)
operator|*
name|gca
operator|->
name|color
operator|.
name|a
operator|)
operator|*
literal|255.999
expr_stmt|;
name|light
index|[
literal|1
index|]
operator|=
operator|(
name|GIMP_CHECK_LIGHT
operator|+
operator|(
name|gca
operator|->
name|color
operator|.
name|g
operator|-
name|GIMP_CHECK_LIGHT
operator|)
operator|*
name|gca
operator|->
name|color
operator|.
name|a
operator|)
operator|*
literal|255.999
expr_stmt|;
name|dark
index|[
literal|1
index|]
operator|=
operator|(
name|GIMP_CHECK_DARK
operator|+
operator|(
name|gca
operator|->
name|color
operator|.
name|g
operator|-
name|GIMP_CHECK_DARK
operator|)
operator|*
name|gca
operator|->
name|color
operator|.
name|a
operator|)
operator|*
literal|255.999
expr_stmt|;
name|light
index|[
literal|2
index|]
operator|=
operator|(
name|GIMP_CHECK_LIGHT
operator|+
operator|(
name|gca
operator|->
name|color
operator|.
name|b
operator|-
name|GIMP_CHECK_LIGHT
operator|)
operator|*
name|gca
operator|->
name|color
operator|.
name|a
operator|)
operator|*
literal|255.999
expr_stmt|;
name|dark
index|[
literal|2
index|]
operator|=
operator|(
name|GIMP_CHECK_DARK
operator|+
operator|(
name|gca
operator|->
name|color
operator|.
name|b
operator|-
name|GIMP_CHECK_DARK
operator|)
operator|*
name|gca
operator|->
name|color
operator|.
name|a
operator|)
operator|*
literal|255.999
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|p
operator|=
name|gca
operator|->
name|buf
operator|+
name|y
operator|*
name|gca
operator|->
name|rowstride
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
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|width
operator|-
name|x
operator|)
operator|*
name|height
operator|>
name|y
operator|*
name|width
condition|)
block|{
operator|*
name|p
operator|++
operator|=
name|opaque
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|opaque
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|opaque
index|[
literal|2
index|]
expr_stmt|;
continue|continue;
block|}
name|frac
operator|=
name|y
operator|-
call|(
name|gdouble
call|)
argument_list|(
operator|(
name|width
operator|-
name|x
operator|)
operator|*
name|height
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|width
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|x
operator|/
name|check_size
operator|)
operator|^
operator|(
name|y
operator|/
name|check_size
operator|)
operator|)
operator|&
literal|1
condition|)
block|{
if|if
condition|(
operator|(
name|gint
operator|)
name|frac
condition|)
block|{
operator|*
name|p
operator|++
operator|=
name|light
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|light
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|light
index|[
literal|2
index|]
expr_stmt|;
block|}
else|else
block|{
operator|*
name|p
operator|++
operator|=
operator|(
name|gdouble
operator|)
name|light
index|[
literal|0
index|]
operator|*
name|frac
operator|+
operator|(
name|gdouble
operator|)
name|opaque
index|[
literal|0
index|]
operator|*
operator|(
literal|1.0
operator|-
name|frac
operator|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
operator|(
name|gdouble
operator|)
name|light
index|[
literal|1
index|]
operator|*
name|frac
operator|+
operator|(
name|gdouble
operator|)
name|opaque
index|[
literal|1
index|]
operator|*
operator|(
literal|1.0
operator|-
name|frac
operator|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
operator|(
name|gdouble
operator|)
name|light
index|[
literal|2
index|]
operator|*
name|frac
operator|+
operator|(
name|gdouble
operator|)
name|opaque
index|[
literal|2
index|]
operator|*
operator|(
literal|1.0
operator|-
name|frac
operator|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
operator|(
name|gint
operator|)
name|frac
condition|)
block|{
operator|*
name|p
operator|++
operator|=
name|dark
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|dark
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|dark
index|[
literal|2
index|]
expr_stmt|;
block|}
else|else
block|{
operator|*
name|p
operator|++
operator|=
operator|(
name|gdouble
operator|)
name|dark
index|[
literal|0
index|]
operator|*
name|frac
operator|+
operator|(
name|gdouble
operator|)
name|opaque
index|[
literal|0
index|]
operator|*
operator|(
literal|1.0
operator|-
name|frac
operator|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
operator|(
name|gdouble
operator|)
name|dark
index|[
literal|1
index|]
operator|*
name|frac
operator|+
operator|(
name|gdouble
operator|)
name|opaque
index|[
literal|1
index|]
operator|*
operator|(
literal|1.0
operator|-
name|frac
operator|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
operator|(
name|gdouble
operator|)
name|dark
index|[
literal|2
index|]
operator|*
name|frac
operator|+
operator|(
name|gdouble
operator|)
name|opaque
index|[
literal|2
index|]
operator|*
operator|(
literal|1.0
operator|-
name|frac
operator|)
expr_stmt|;
block|}
block|}
block|}
block|}
block|}
else|else
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|p
operator|=
name|gca
operator|->
name|buf
operator|+
name|y
operator|*
name|gca
operator|->
name|rowstride
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
condition|;
name|x
operator|++
control|)
block|{
operator|*
name|p
operator|++
operator|=
name|opaque
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|opaque
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|opaque
index|[
literal|2
index|]
expr_stmt|;
block|}
block|}
block|}
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|gca
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_drag_begin (GtkWidget * widget,GdkDragContext * context)
name|gimp_color_area_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|color_area
decl_stmt|;
name|window
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|window
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gimp_color_area_get_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|color_area
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|color
argument_list|,
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
operator|->
name|type
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|color_area
argument_list|,
name|DRAG_PREVIEW_SIZE
argument_list|,
name|DRAG_PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|color_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|color_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-color-area-drag-window"
argument_list|,
name|window
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gtk_widget_destroy
argument_list|)
expr_stmt|;
name|gtk_drag_set_icon_widget
argument_list|(
name|context
argument_list|,
name|window
argument_list|,
name|DRAG_ICON_OFFSET
argument_list|,
name|DRAG_ICON_OFFSET
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_drag_end (GtkWidget * widget,GdkDragContext * context)
name|gimp_color_area_drag_end
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-color-area-drag-window"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_drag_data_received (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection_data,guint info,guint time)
name|gimp_color_area_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection_data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|GimpColorArea
modifier|*
name|gca
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|guint16
modifier|*
name|vals
decl_stmt|;
name|gca
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection_data
operator|->
name|length
operator|<
literal|0
condition|)
return|return;
if|if
condition|(
operator|(
name|selection_data
operator|->
name|format
operator|!=
literal|16
operator|)
operator|||
operator|(
name|selection_data
operator|->
name|length
operator|!=
literal|8
operator|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"Received invalid color data"
argument_list|)
expr_stmt|;
return|return;
block|}
name|vals
operator|=
operator|(
name|guint16
operator|*
operator|)
name|selection_data
operator|->
name|data
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
operator|(
name|gdouble
operator|)
name|vals
index|[
literal|0
index|]
operator|/
literal|0xffff
argument_list|,
operator|(
name|gdouble
operator|)
name|vals
index|[
literal|1
index|]
operator|/
literal|0xffff
argument_list|,
operator|(
name|gdouble
operator|)
name|vals
index|[
literal|2
index|]
operator|/
literal|0xffff
argument_list|,
operator|(
name|gdouble
operator|)
name|vals
index|[
literal|3
index|]
operator|/
literal|0xffff
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|gca
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_area_drag_data_get (GtkWidget * widget,GdkDragContext * context,GtkSelectionData * selection_data,guint info,guint time)
name|gimp_color_area_drag_data_get
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection_data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|GimpColorArea
modifier|*
name|gca
decl_stmt|;
name|guint16
name|vals
index|[
literal|4
index|]
decl_stmt|;
name|gca
operator|=
name|GIMP_COLOR_AREA
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|vals
index|[
literal|0
index|]
operator|=
name|gca
operator|->
name|color
operator|.
name|r
operator|*
literal|0xffff
expr_stmt|;
name|vals
index|[
literal|1
index|]
operator|=
name|gca
operator|->
name|color
operator|.
name|g
operator|*
literal|0xffff
expr_stmt|;
name|vals
index|[
literal|2
index|]
operator|=
name|gca
operator|->
name|color
operator|.
name|b
operator|*
literal|0xffff
expr_stmt|;
if|if
condition|(
name|gca
operator|->
name|type
operator|==
name|GIMP_COLOR_AREA_FLAT
condition|)
name|vals
index|[
literal|3
index|]
operator|=
literal|0xffff
expr_stmt|;
else|else
name|vals
index|[
literal|3
index|]
operator|=
name|gca
operator|->
name|color
operator|.
name|a
operator|*
literal|0xffff
expr_stmt|;
name|gtk_selection_data_set
argument_list|(
name|selection_data
argument_list|,
name|gdk_atom_intern
argument_list|(
literal|"application/x-color"
argument_list|,
name|FALSE
argument_list|)
argument_list|,
literal|16
argument_list|,
operator|(
name|guchar
operator|*
operator|)
name|vals
argument_list|,
literal|8
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

