begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"print-preview.h"
end_include

begin_define
DECL|macro|DRAWING_AREA_SIZE
define|#
directive|define
name|DRAWING_AREA_SIZE
value|200
end_define

begin_enum
enum|enum
DECL|enum|__anon28d1ad0a0103
block|{
DECL|enumerator|OFFSETS_CHANGED
name|OFFSETS_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_print_preview_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_print_preview_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_print_preview_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_print_preview_get_scale
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_print_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_print_preview_get_page_margins
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
modifier|*
name|left_margin
parameter_list|,
name|gdouble
modifier|*
name|right_margin
parameter_list|,
name|gdouble
modifier|*
name|top_margin
parameter_list|,
name|gdouble
modifier|*
name|bottom_margin
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPrintPreview
argument_list|,
argument|gimp_print_preview
argument_list|,
argument|GTK_TYPE_ASPECT_FRAME
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_print_preview_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_print_preview_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|g_marshal_value_peek_double (v)
define|#
directive|define
name|g_marshal_value_peek_double
parameter_list|(
name|v
parameter_list|)
value|(v)->data[0].v_double
end_define

begin_function
specifier|static
name|void
DECL|function|marshal_VOID__DOUBLE_DOUBLE (GClosure * closure,GValue * return_value,guint n_param_values,const GValue * param_values,gpointer invocation_hint,gpointer marshal_data)
name|marshal_VOID__DOUBLE_DOUBLE
parameter_list|(
name|GClosure
modifier|*
name|closure
parameter_list|,
name|GValue
modifier|*
name|return_value
parameter_list|,
name|guint
name|n_param_values
parameter_list|,
specifier|const
name|GValue
modifier|*
name|param_values
parameter_list|,
name|gpointer
name|invocation_hint
parameter_list|,
name|gpointer
name|marshal_data
parameter_list|)
block|{
DECL|typedef|GMarshalFunc_VOID__DOUBLE_DOUBLE
typedef|typedef
name|void
function_decl|(
modifier|*
name|GMarshalFunc_VOID__DOUBLE_DOUBLE
function_decl|)
parameter_list|(
name|gpointer
name|data1
parameter_list|,
name|gdouble
name|arg_1
parameter_list|,
name|gdouble
name|arg_2
parameter_list|,
name|gpointer
name|data2
parameter_list|)
function_decl|;
specifier|register
name|GMarshalFunc_VOID__DOUBLE_DOUBLE
name|callback
decl_stmt|;
specifier|register
name|GCClosure
modifier|*
name|cc
init|=
operator|(
name|GCClosure
operator|*
operator|)
name|closure
decl_stmt|;
specifier|register
name|gpointer
name|data1
decl_stmt|,
name|data2
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|n_param_values
operator|==
literal|3
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_CCLOSURE_SWAP_DATA
argument_list|(
name|closure
argument_list|)
condition|)
block|{
name|data1
operator|=
name|closure
operator|->
name|data
expr_stmt|;
name|data2
operator|=
name|g_value_peek_pointer
argument_list|(
name|param_values
operator|+
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|data1
operator|=
name|g_value_peek_pointer
argument_list|(
name|param_values
operator|+
literal|0
argument_list|)
expr_stmt|;
name|data2
operator|=
name|closure
operator|->
name|data
expr_stmt|;
block|}
name|callback
operator|=
call|(
name|GMarshalFunc_VOID__DOUBLE_DOUBLE
call|)
argument_list|(
name|marshal_data
condition|?
name|marshal_data
else|:
name|cc
operator|->
name|callback
argument_list|)
expr_stmt|;
name|callback
argument_list|(
name|data1
argument_list|,
name|g_marshal_value_peek_double
argument_list|(
name|param_values
operator|+
literal|1
argument_list|)
argument_list|,
name|g_marshal_value_peek_double
argument_list|(
name|param_values
operator|+
literal|2
argument_list|)
argument_list|,
name|data2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_print_preview_class_init (GimpPrintPreviewClass * klass)
name|gimp_print_preview_class_init
parameter_list|(
name|GimpPrintPreviewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|gobject_class
decl_stmt|;
name|gobject_class
operator|=
operator|(
name|GObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|gimp_print_preview_signals
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
name|GimpPrintPreviewClass
argument_list|,
name|offsets_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|marshal_VOID__DOUBLE_DOUBLE
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|gobject_class
operator|->
name|finalize
operator|=
name|gimp_print_preview_finalize
expr_stmt|;
name|klass
operator|->
name|offsets_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_print_preview_init (GimpPrintPreview * preview)
name|gimp_print_preview_init
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
block|{
name|preview
operator|->
name|page
operator|=
name|NULL
expr_stmt|;
name|preview
operator|->
name|pixbuf
operator|=
name|NULL
expr_stmt|;
name|preview
operator|->
name|image_offset_x
operator|=
literal|0.0
expr_stmt|;
name|preview
operator|->
name|image_offset_y
operator|=
literal|0.0
expr_stmt|;
name|preview
operator|->
name|image_offset_x_max
operator|=
literal|0.0
expr_stmt|;
name|preview
operator|->
name|image_offset_y_max
operator|=
literal|0.0
expr_stmt|;
name|preview
operator|->
name|image_xres
operator|=
literal|1.0
expr_stmt|;
name|preview
operator|->
name|image_yres
operator|=
literal|1.0
expr_stmt|;
name|preview
operator|->
name|use_full_page
operator|=
name|FALSE
expr_stmt|;
name|preview
operator|->
name|area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|preview
argument_list|)
argument_list|,
name|preview
operator|->
name|area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
operator|->
name|area
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|,
name|GDK_EXPOSURE_MASK
operator||
name|GDK_BUTTON_PRESS_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_print_preview_finalize (GObject * object)
name|gimp_print_preview_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPrintPreview
modifier|*
name|preview
init|=
name|GIMP_PRINT_PREVIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|preview
operator|->
name|pixbuf
condition|)
block|{
name|g_object_unref
argument_list|(
name|preview
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|preview
operator|->
name|pixbuf
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|preview
operator|->
name|page
condition|)
block|{
name|g_object_unref
argument_list|(
name|preview
operator|->
name|page
argument_list|)
expr_stmt|;
name|preview
operator|->
name|page
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|gimp_print_preview_parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_print_preview_new:  * @page: page setup  * @drawable_id: the drawable to print  *  * Creates a new #GimpPrintPreview widget.  *  * Return value: the new #GimpPrintPreview widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_print_preview_new (GtkPageSetup * page,gint32 drawable_id)
name|gimp_print_preview_new
parameter_list|(
name|GtkPageSetup
modifier|*
name|page
parameter_list|,
name|gint32
name|drawable_id
parameter_list|)
block|{
name|GimpPrintPreview
modifier|*
name|preview
decl_stmt|;
name|gfloat
name|ratio
decl_stmt|;
name|preview
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PRINT_PREVIEW
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|page
operator|!=
name|NULL
condition|)
name|preview
operator|->
name|page
operator|=
name|gtk_page_setup_copy
argument_list|(
name|page
argument_list|)
expr_stmt|;
else|else
name|preview
operator|->
name|page
operator|=
name|gtk_page_setup_new
argument_list|()
expr_stmt|;
name|ratio
operator|=
operator|(
name|gtk_page_setup_get_paper_width
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
operator|/
name|gtk_page_setup_get_paper_height
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
operator|)
expr_stmt|;
name|gtk_aspect_frame_set
argument_list|(
name|GTK_ASPECT_FRAME
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
name|ratio
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
operator|->
name|area
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_print_preview_event
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
operator|->
name|area
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_print_preview_expose_event
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
operator|->
name|area
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_print_preview_size_allocate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|preview
operator|->
name|area
argument_list|,
name|DRAWING_AREA_SIZE
argument_list|,
name|DRAWING_AREA_SIZE
argument_list|)
expr_stmt|;
name|preview
operator|->
name|drawable_id
operator|=
name|drawable_id
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_print_preview_set_image_dpi:  * @preview: a #GimpPrintPreview.  * @xres: the X resolution  * @yres: the Y resolution  *  * Sets the resolution of the image/drawable displayed by the  * #GimpPrintPreview.  **/
end_comment

begin_function
name|void
DECL|function|gimp_print_preview_set_image_dpi (GimpPrintPreview * preview,gdouble xres,gdouble yres)
name|gimp_print_preview_set_image_dpi
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PRINT_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
operator|->
name|image_xres
operator|!=
name|xres
operator|||
name|preview
operator|->
name|image_yres
operator|!=
name|yres
condition|)
block|{
name|preview
operator|->
name|image_xres
operator|=
name|xres
expr_stmt|;
name|preview
operator|->
name|image_yres
operator|=
name|yres
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_print_preview_set_page_setup:  * @preview: a #GimpPrintPreview.  * @page: the page setup to use  *  * Sets the page setup to use by the #GimpPrintPreview.  **/
end_comment

begin_function
name|void
DECL|function|gimp_print_preview_set_page_setup (GimpPrintPreview * preview,GtkPageSetup * page)
name|gimp_print_preview_set_page_setup
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|,
name|GtkPageSetup
modifier|*
name|page
parameter_list|)
block|{
name|gfloat
name|ratio
decl_stmt|;
if|if
condition|(
name|preview
operator|->
name|page
condition|)
name|g_object_unref
argument_list|(
name|preview
operator|->
name|page
argument_list|)
expr_stmt|;
name|preview
operator|->
name|page
operator|=
name|gtk_page_setup_copy
argument_list|(
name|page
argument_list|)
expr_stmt|;
name|ratio
operator|=
operator|(
name|gtk_page_setup_get_paper_width
argument_list|(
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
operator|/
name|gtk_page_setup_get_paper_height
argument_list|(
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
operator|)
expr_stmt|;
name|gtk_aspect_frame_set
argument_list|(
name|GTK_ASPECT_FRAME
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
name|ratio
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_print_preview_set_image_offsets:  * @preview: a #GimpPrintPreview.  * @offset_x: the X offset  * @offset_y: the Y offset  *  * Sets the offsets of the image/drawable displayed by the #GimpPrintPreview.  * It does not emit the "offsets-changed" signal.  **/
end_comment

begin_function
name|void
DECL|function|gimp_print_preview_set_image_offsets (GimpPrintPreview * preview,gdouble offset_x,gdouble offset_y)
name|gimp_print_preview_set_image_offsets
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PRINT_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|preview
operator|->
name|image_offset_x
operator|=
name|offset_x
expr_stmt|;
name|preview
operator|->
name|image_offset_y
operator|=
name|offset_y
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_print_preview_set_image_offsets_max:  * @preview: a #GimpPrintPreview.  * @offset_x_max: the maximum X offset allowed  * @offset_y_max: the maximum Y offset allowed  *  * Sets the maximum offsets of the image/drawable displayed by the #GimpPrintPreview.  * It does not emit the "offsets-changed" signal.  **/
end_comment

begin_function
name|void
DECL|function|gimp_print_preview_set_image_offsets_max (GimpPrintPreview * preview,gdouble offset_x_max,gdouble offset_y_max)
name|gimp_print_preview_set_image_offsets_max
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
name|offset_x_max
parameter_list|,
name|gdouble
name|offset_y_max
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PRINT_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|preview
operator|->
name|image_offset_x_max
operator|=
name|offset_x_max
expr_stmt|;
name|preview
operator|->
name|image_offset_y_max
operator|=
name|offset_y_max
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_print_preview_set_use_full_page:  * @preview: a #GimpPrintPreview.  * @full_page: TRUE to ignore the page margins  *  * If @full_page is TRUE, the page margins are ignored and the full page  * can be used to setup printing.  **/
end_comment

begin_function
name|void
DECL|function|gimp_print_preview_set_use_full_page (GimpPrintPreview * preview,gboolean full_page)
name|gimp_print_preview_set_use_full_page
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|,
name|gboolean
name|full_page
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PRINT_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|preview
operator|->
name|use_full_page
operator|=
name|full_page
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_print_preview_event (GtkWidget * widget,GdkEvent * event,GimpPrintPreview * preview)
name|gimp_print_preview_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
block|{
specifier|static
name|gdouble
name|orig_offset_x
init|=
literal|0.0
decl_stmt|;
specifier|static
name|gdouble
name|orig_offset_y
init|=
literal|0.0
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
name|gdouble
name|offset_x
decl_stmt|;
name|gdouble
name|offset_y
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
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
name|gdk_pointer_grab
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
operator|(
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|event
operator|->
name|button
operator|.
name|time
argument_list|)
expr_stmt|;
name|orig_offset_x
operator|=
name|preview
operator|->
name|image_offset_x
expr_stmt|;
name|orig_offset_y
operator|=
name|preview
operator|->
name|image_offset_y
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
break|break;
case|case
name|GDK_MOTION_NOTIFY
case|:
name|scale
operator|=
name|gimp_print_preview_get_scale
argument_list|(
name|preview
argument_list|)
expr_stmt|;
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
name|scale
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
name|scale
operator|)
expr_stmt|;
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|offset_x
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|image_offset_x_max
argument_list|)
expr_stmt|;
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|offset_y
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|image_offset_y_max
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
operator|->
name|image_offset_x
operator|!=
name|offset_x
operator|||
name|preview
operator|->
name|image_offset_y
operator|!=
name|offset_y
condition|)
block|{
name|preview
operator|->
name|image_offset_x
operator|=
name|offset_x
expr_stmt|;
name|preview
operator|->
name|image_offset_y
operator|=
name|offset_y
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|preview
argument_list|,
name|gimp_print_preview_signals
index|[
name|OFFSETS_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|image_offset_x
argument_list|,
name|preview
operator|->
name|image_offset_y
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
name|gdk_display_pointer_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
argument_list|,
name|event
operator|->
name|button
operator|.
name|time
argument_list|)
expr_stmt|;
name|start_x
operator|=
name|start_y
operator|=
literal|0
expr_stmt|;
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
name|gboolean
DECL|function|gimp_print_preview_expose_event (GtkWidget * widget,GdkEventExpose * eevent,GimpPrintPreview * preview)
name|gimp_print_preview_expose_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|eevent
parameter_list|,
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
block|{
name|gdouble
name|paper_width
decl_stmt|;
name|gdouble
name|paper_height
decl_stmt|;
name|gdouble
name|left_margin
decl_stmt|;
name|gdouble
name|right_margin
decl_stmt|;
name|gdouble
name|top_margin
decl_stmt|;
name|gdouble
name|bottom_margin
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|paper_width
operator|=
name|gtk_page_setup_get_paper_width
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
expr_stmt|;
name|paper_height
operator|=
name|gtk_page_setup_get_paper_height
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
expr_stmt|;
name|gimp_print_preview_get_page_margins
argument_list|(
name|preview
argument_list|,
operator|&
name|left_margin
argument_list|,
operator|&
name|right_margin
argument_list|,
operator|&
name|top_margin
argument_list|,
operator|&
name|bottom_margin
argument_list|)
expr_stmt|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_print_preview_get_scale
argument_list|(
name|preview
argument_list|)
expr_stmt|;
comment|/* draw background */
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|scale
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
operator|(
name|widget
operator|->
name|style
operator|->
name|white
operator|)
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|paper_width
argument_list|,
name|paper_height
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* draw page_margins */
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
operator|(
name|widget
operator|->
name|style
operator|->
name|black
operator|)
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|left_margin
argument_list|,
name|top_margin
argument_list|,
name|paper_width
operator|-
name|left_margin
operator|-
name|right_margin
argument_list|,
name|paper_height
operator|-
name|top_margin
operator|-
name|bottom_margin
argument_list|)
expr_stmt|;
name|cairo_stroke_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_new_path
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* draw image */
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|left_margin
operator|+
name|preview
operator|->
name|image_offset_x
argument_list|,
name|top_margin
operator|+
name|preview
operator|->
name|image_offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
operator|->
name|pixbuf
operator|==
name|NULL
condition|)
block|{
name|gint
name|width
init|=
name|MIN
argument_list|(
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
literal|1024
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|MIN
argument_list|(
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|,
literal|1024
argument_list|)
decl_stmt|;
name|preview
operator|->
name|pixbuf
operator|=
name|gimp_drawable_get_thumbnail
argument_list|(
name|preview
operator|->
name|drawable_id
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_PIXBUF_KEEP_ALPHA
argument_list|)
expr_stmt|;
block|}
name|scale_x
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|gimp_drawable_width
argument_list|(
name|preview
operator|->
name|drawable_id
argument_list|)
operator|/
name|gdk_pixbuf_get_width
argument_list|(
name|preview
operator|->
name|pixbuf
argument_list|)
operator|)
expr_stmt|;
name|scale_y
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|gimp_drawable_height
argument_list|(
name|preview
operator|->
name|drawable_id
argument_list|)
operator|/
name|gdk_pixbuf_get_height
argument_list|(
name|preview
operator|->
name|pixbuf
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|scale_x
operator|<
name|scale_y
condition|)
name|scale_x
operator|=
name|scale_y
expr_stmt|;
else|else
name|scale_y
operator|=
name|scale_x
expr_stmt|;
name|scale_x
operator|=
name|scale_x
operator|*
literal|72.0
operator|/
name|preview
operator|->
name|image_xres
expr_stmt|;
name|scale_y
operator|=
name|scale_y
operator|*
literal|72.0
operator|/
name|preview
operator|->
name|image_yres
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_pixbuf
argument_list|(
name|cr
argument_list|,
name|preview
operator|->
name|pixbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_print_preview_get_scale (GimpPrintPreview * preview)
name|gimp_print_preview_get_scale
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
block|{
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|scale_x
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|preview
operator|->
name|area
operator|->
name|allocation
operator|.
name|width
operator|/
name|gtk_page_setup_get_paper_width
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
operator|)
expr_stmt|;
name|scale_y
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|preview
operator|->
name|area
operator|->
name|allocation
operator|.
name|height
operator|/
name|gtk_page_setup_get_paper_height
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
operator|)
expr_stmt|;
return|return
name|MIN
argument_list|(
name|scale_x
argument_list|,
name|scale_y
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_print_preview_size_allocate (GtkWidget * widget,GtkAllocation * allocation,GimpPrintPreview * preview)
name|gimp_print_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|)
block|{
if|if
condition|(
name|preview
operator|->
name|pixbuf
operator|!=
name|NULL
condition|)
block|{
name|g_object_unref
argument_list|(
name|preview
operator|->
name|pixbuf
argument_list|)
expr_stmt|;
name|preview
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
DECL|function|gimp_print_preview_get_page_margins (GimpPrintPreview * preview,gdouble * left_margin,gdouble * right_margin,gdouble * top_margin,gdouble * bottom_margin)
name|gimp_print_preview_get_page_margins
parameter_list|(
name|GimpPrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
modifier|*
name|left_margin
parameter_list|,
name|gdouble
modifier|*
name|right_margin
parameter_list|,
name|gdouble
modifier|*
name|top_margin
parameter_list|,
name|gdouble
modifier|*
name|bottom_margin
parameter_list|)
block|{
if|if
condition|(
name|preview
operator|->
name|use_full_page
condition|)
block|{
operator|*
name|left_margin
operator|=
literal|0.0
expr_stmt|;
operator|*
name|right_margin
operator|=
literal|0.0
expr_stmt|;
operator|*
name|top_margin
operator|=
literal|0.0
expr_stmt|;
operator|*
name|bottom_margin
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
operator|*
name|left_margin
operator|=
name|gtk_page_setup_get_left_margin
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
expr_stmt|;
operator|*
name|right_margin
operator|=
name|gtk_page_setup_get_right_margin
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
expr_stmt|;
operator|*
name|top_margin
operator|=
name|gtk_page_setup_get_top_margin
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
expr_stmt|;
operator|*
name|bottom_margin
operator|=
name|gtk_page_setup_get_bottom_margin
argument_list|(
name|preview
operator|->
name|page
argument_list|,
name|GTK_UNIT_POINTS
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

