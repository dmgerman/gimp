begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogrambox.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogramview.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|GRADIENT_HEIGHT
define|#
directive|define
name|GRADIENT_HEIGHT
value|15
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_histogram_box_class_init
parameter_list|(
name|GimpHistogramBoxClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_box_init
parameter_list|(
name|GimpHistogramBox
modifier|*
name|histogram_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_box_low_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_box_high_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_box_histogram_range
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_histogram_box_gradient_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkVBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_histogram_box_get_type (void)
name|gimp_histogram_box_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|box_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|box_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|box_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpHistogramBoxClass
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
name|gimp_histogram_box_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpHistogramBox
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_histogram_box_init
block|,       }
decl_stmt|;
name|box_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_VBOX
argument_list|,
literal|"GimpHistogramBox"
argument_list|,
operator|&
name|box_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|box_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_class_init (GimpHistogramBoxClass * klass)
name|gimp_histogram_box_class_init
parameter_list|(
name|GimpHistogramBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_init (GimpHistogramBox * box)
name|gimp_histogram_box_init
parameter_list|(
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|box
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|box
operator|->
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
operator|->
name|label
argument_list|)
expr_stmt|;
comment|/*  low spinbutton  */
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|255.0
argument_list|,
literal|1.0
argument_list|,
literal|16.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|box
operator|->
name|low_adj
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_box_low_adj_update
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
comment|/*  high spinbutton  */
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
literal|255.0
argument_list|,
literal|0.0
argument_list|,
literal|255.0
argument_list|,
literal|1.0
argument_list|,
literal|16.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|box
operator|->
name|high_adj
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_box_high_adj_update
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
comment|/*  The histogram  */
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
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_histogram_view_new
argument_list|(
name|GIMP_HISTOGRAM_VIEW_WIDTH
argument_list|,
name|GIMP_HISTOGRAM_VIEW_HEIGHT
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"range_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_box_histogram_range
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|box
operator|->
name|histogram
operator|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
comment|/*  The gradient below the histogram */
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
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|box
operator|->
name|gradient
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|box
operator|->
name|gradient
argument_list|,
name|GIMP_HISTOGRAM_VIEW_WIDTH
argument_list|,
name|GRADIENT_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|box
operator|->
name|gradient
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
operator|->
name|gradient
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|box
operator|->
name|gradient
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_box_gradient_expose
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_low_adj_update (GtkAdjustment * adjustment,GimpHistogramBox * box)
name|gimp_histogram_box_low_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
block|{
if|if
condition|(
operator|(
name|gdouble
operator|)
name|box
operator|->
name|histogram
operator|->
name|start
operator|==
name|adjustment
operator|->
name|value
condition|)
return|return;
name|box
operator|->
name|high_adj
operator|->
name|lower
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gtk_adjustment_changed
argument_list|(
name|box
operator|->
name|high_adj
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_range
argument_list|(
name|box
operator|->
name|histogram
argument_list|,
name|adjustment
operator|->
name|value
argument_list|,
name|box
operator|->
name|histogram
operator|->
name|end
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_high_adj_update (GtkAdjustment * adjustment,GimpHistogramBox * box)
name|gimp_histogram_box_high_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
block|{
if|if
condition|(
operator|(
name|gdouble
operator|)
name|box
operator|->
name|histogram
operator|->
name|end
operator|==
name|adjustment
operator|->
name|value
condition|)
return|return;
name|box
operator|->
name|low_adj
operator|->
name|upper
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gtk_adjustment_changed
argument_list|(
name|box
operator|->
name|low_adj
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_range
argument_list|(
name|box
operator|->
name|histogram
argument_list|,
name|box
operator|->
name|histogram
operator|->
name|start
argument_list|,
name|adjustment
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_histogram_range (GimpHistogramView * widget,gint start,gint end,GimpHistogramBox * box)
name|gimp_histogram_box_histogram_range
parameter_list|(
name|GimpHistogramView
modifier|*
name|widget
parameter_list|,
name|gint
name|start
parameter_list|,
name|gint
name|end
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
block|{
name|box
operator|->
name|high_adj
operator|->
name|lower
operator|=
name|start
expr_stmt|;
name|box
operator|->
name|low_adj
operator|->
name|upper
operator|=
name|end
expr_stmt|;
name|gtk_adjustment_changed
argument_list|(
name|box
operator|->
name|high_adj
argument_list|)
expr_stmt|;
name|gtk_adjustment_changed
argument_list|(
name|box
operator|->
name|low_adj
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|box
operator|->
name|low_adj
argument_list|,
name|start
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|box
operator|->
name|high_adj
argument_list|,
name|end
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_box_gradient_expose (GtkWidget * widget,GdkEventExpose * event,gpointer data)
name|gimp_histogram_box_gradient_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpHistogramBox
modifier|*
name|box
init|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpHistogramChannel
name|channel
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
expr_stmt|;
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
literal|2
expr_stmt|;
if|if
condition|(
name|width
operator|<=
literal|0
operator|||
name|height
operator|<=
literal|0
condition|)
return|return
name|TRUE
return|;
comment|/* FIXME: should probably reallocate on size_allocate */
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
literal|3
operator|*
name|width
operator|*
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|histogram
condition|)
name|channel
operator|=
name|box
operator|->
name|histogram
operator|->
name|channel
expr_stmt|;
else|else
name|channel
operator|=
name|GIMP_HISTOGRAM_VALUE
expr_stmt|;
switch|switch
condition|(
name|channel
condition|)
block|{
case|case
name|GIMP_HISTOGRAM_VALUE
case|:
case|case
name|GIMP_HISTOGRAM_ALPHA
case|:
name|r
operator|=
name|g
operator|=
name|b
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_HISTOGRAM_RED
case|:
name|r
operator|=
literal|1
expr_stmt|;
name|g
operator|=
name|b
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GIMP_HISTOGRAM_GREEN
case|:
name|g
operator|=
literal|1
expr_stmt|;
name|r
operator|=
name|b
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GIMP_HISTOGRAM_BLUE
case|:
name|b
operator|=
literal|1
expr_stmt|;
name|r
operator|=
name|g
operator|=
literal|0
expr_stmt|;
break|break;
default|default:
name|r
operator|=
name|g
operator|=
name|b
operator|=
literal|0
expr_stmt|;
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|x
init|=
operator|(
name|i
operator|*
literal|256
operator|)
operator|/
name|width
decl_stmt|;
name|buffer
index|[
literal|3
operator|*
name|i
operator|+
literal|0
index|]
operator|=
name|x
operator|*
name|r
expr_stmt|;
name|buffer
index|[
literal|3
operator|*
name|i
operator|+
literal|1
index|]
operator|=
name|x
operator|*
name|g
expr_stmt|;
name|buffer
index|[
literal|3
operator|*
name|i
operator|+
literal|2
index|]
operator|=
name|x
operator|*
name|b
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
name|memcpy
argument_list|(
name|buffer
operator|+
literal|3
operator|*
name|i
operator|*
name|width
argument_list|,
name|buffer
argument_list|,
literal|3
operator|*
name|width
argument_list|)
expr_stmt|;
name|gdk_draw_rgb_image
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
literal|1
argument_list|,
literal|1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GDK_RGB_DITHER_NORMAL
argument_list|,
name|buffer
argument_list|,
literal|3
operator|*
name|width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_histogram_box_new (const gchar * label)
name|gimp_histogram_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
block|{
name|GimpHistogramBox
modifier|*
name|box
decl_stmt|;
name|box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_HISTOGRAM_BOX
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|box
operator|->
name|label
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_box_set_channel (GimpHistogramBox * box,GimpHistogramChannel channel)
name|gimp_histogram_box_set_channel
parameter_list|(
name|GimpHistogramBox
modifier|*
name|box
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|box
operator|->
name|histogram
condition|)
return|return;
name|gimp_histogram_view_set_channel
argument_list|(
name|box
operator|->
name|histogram
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|box
operator|->
name|gradient
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

