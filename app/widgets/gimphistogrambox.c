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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"gimpcolorbar.h"
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
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  #define DEBUG_VIEW  */
end_comment

begin_define
DECL|macro|GRADIENT_HEIGHT
define|#
directive|define
name|GRADIENT_HEIGHT
value|12
end_define

begin_define
DECL|macro|CONTROL_HEIGHT
define|#
directive|define
name|CONTROL_HEIGHT
value|8
end_define

begin_define
DECL|macro|HISTOGRAM_EVENT_MASK
define|#
directive|define
name|HISTOGRAM_EVENT_MASK
value|(GDK_BUTTON_PRESS_MASK   | \                                GDK_BUTTON_RELEASE_MASK | \                                GDK_BUTTON_MOTION_MASK)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

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
name|void
name|gimp_histogram_box_channel_notify
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorBar
modifier|*
name|bar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_box_border_notify
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorBar
modifier|*
name|bar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_histogram_slider_area_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
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
name|gimp_histogram_slider_area_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
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
name|gimp_histogram_draw_slider
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkGC
modifier|*
name|border_gc
parameter_list|,
name|GdkGC
modifier|*
name|fill_gc
parameter_list|,
name|gint
name|xpos
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpHistogramBox,gimp_histogram_box,GTK_TYPE_VBOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHistogramBox
argument_list|,
argument|gimp_histogram_box
argument_list|,
argument|GTK_TYPE_VBOX
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_histogram_box_class_init
parameter_list|(
name|GimpHistogramBoxClass
modifier|*
name|klass
parameter_list|)
block|{ }
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
name|vbox
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
name|GtkWidget
modifier|*
name|bar
decl_stmt|;
name|GtkWidget
modifier|*
name|slider_area
decl_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|2
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
name|view
argument_list|,
literal|"range-changed"
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
name|view
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
name|slider_area
operator|=
name|slider_area
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|slider_area
argument_list|,
operator|-
literal|1
argument_list|,
name|GRADIENT_HEIGHT
operator|+
name|CONTROL_HEIGHT
argument_list|)
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|slider_area
argument_list|,
name|HISTOGRAM_EVENT_MASK
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|slider_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider_area
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|slider_area
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_slider_area_event
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|slider_area
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_slider_area_expose
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|slider_area
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|bar
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_BAR
argument_list|,
literal|"histogram-channel"
argument_list|,
name|box
operator|->
name|view
operator|->
name|channel
argument_list|,
literal|"xpad"
argument_list|,
name|box
operator|->
name|view
operator|->
name|border_width
argument_list|,
literal|"ypad"
argument_list|,
name|box
operator|->
name|view
operator|->
name|border_width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|bar
argument_list|,
operator|-
literal|1
argument_list|,
name|GRADIENT_HEIGHT
operator|+
literal|2
operator|*
name|box
operator|->
name|view
operator|->
name|border_width
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|bar
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
name|bar
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
argument_list|,
literal|"notify::histogram-channel"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_box_channel_notify
argument_list|)
argument_list|,
name|bar
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
argument_list|,
literal|"notify::border-width"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_box_border_notify
argument_list|)
argument_list|,
name|bar
argument_list|)
expr_stmt|;
comment|/*  The range selection */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
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
name|adjustment
argument_list|,
literal|"value-changed"
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
name|gtk_box_pack_end
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
name|adjustment
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_box_high_adj_update
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_VIEW
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|box
operator|->
name|view
argument_list|)
argument_list|,
literal|"border-width"
argument_list|,
literal|1
argument_list|,
literal|5
argument_list|,
literal|0
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
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|box
operator|->
name|view
argument_list|)
argument_list|,
literal|"subdivisions"
argument_list|,
literal|1
argument_list|,
literal|5
argument_list|,
literal|0
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
endif|#
directive|endif
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
name|view
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
name|view
argument_list|,
name|adjustment
operator|->
name|value
argument_list|,
name|box
operator|->
name|view
operator|->
name|end
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|box
operator|->
name|slider_area
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
name|view
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
name|view
argument_list|,
name|box
operator|->
name|view
operator|->
name|start
argument_list|,
name|adjustment
operator|->
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|box
operator|->
name|slider_area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_histogram_range (GimpHistogramView * view,gint start,gint end,GimpHistogramBox * box)
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
name|gtk_widget_queue_draw
argument_list|(
name|box
operator|->
name|slider_area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_channel_notify (GimpHistogramView * view,GParamSpec * pspec,GimpColorBar * bar)
name|gimp_histogram_box_channel_notify
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorBar
modifier|*
name|bar
parameter_list|)
block|{
name|gimp_color_bar_set_channel
argument_list|(
name|bar
argument_list|,
name|view
operator|->
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_box_border_notify (GimpHistogramView * view,GParamSpec * pspec,GimpColorBar * bar)
name|gimp_histogram_box_border_notify
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpColorBar
modifier|*
name|bar
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|bar
argument_list|,
literal|"xpad"
argument_list|,
name|view
operator|->
name|border_width
argument_list|,
literal|"ypad"
argument_list|,
name|view
operator|->
name|border_width
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|bar
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|GRADIENT_HEIGHT
operator|+
literal|2
operator|*
name|view
operator|->
name|border_width
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_histogram_box_new (void)
name|gimp_histogram_box_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_HISTOGRAM_BOX
argument_list|,
name|NULL
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
name|box
operator|->
name|view
condition|)
name|gimp_histogram_view_set_channel
argument_list|(
name|box
operator|->
name|view
argument_list|,
name|channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_slider_area_event (GtkWidget * widget,GdkEvent * event,GimpHistogramBox * box)
name|gimp_histogram_slider_area_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|GdkEventMotion
modifier|*
name|mevent
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|distance
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gboolean
name|update
init|=
name|FALSE
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
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
name|distance
operator|=
name|G_MAXINT
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|fabs
argument_list|(
name|bevent
operator|->
name|x
operator|-
name|box
operator|->
name|slider_pos
index|[
name|i
index|]
argument_list|)
operator|<
name|distance
condition|)
block|{
name|box
operator|->
name|active_slider
operator|=
name|i
expr_stmt|;
name|distance
operator|=
name|fabs
argument_list|(
name|bevent
operator|->
name|x
operator|-
name|box
operator|->
name|slider_pos
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|x
operator|=
name|bevent
operator|->
name|x
expr_stmt|;
name|update
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
switch|switch
condition|(
name|box
operator|->
name|active_slider
condition|)
block|{
case|case
literal|3
case|:
comment|/*  low output  */
name|gtk_adjustment_set_value
argument_list|(
name|box
operator|->
name|low_adj
argument_list|,
name|box
operator|->
name|low_slider_val
argument_list|)
expr_stmt|;
break|break;
case|case
literal|4
case|:
comment|/*  high output  */
name|gtk_adjustment_set_value
argument_list|(
name|box
operator|->
name|high_adj
argument_list|,
name|box
operator|->
name|high_slider_val
argument_list|)
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|GDK_MOTION_NOTIFY
case|:
name|mevent
operator|=
operator|(
name|GdkEventMotion
operator|*
operator|)
name|event
expr_stmt|;
name|gdk_window_get_pointer
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|x
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|update
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|update
condition|)
block|{
name|gdouble
name|value
decl_stmt|;
name|gint
name|border
init|=
name|box
operator|->
name|view
operator|->
name|border_width
decl_stmt|;
name|gint
name|width
init|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|border
decl_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
condition|)
return|return
name|FALSE
return|;
switch|switch
condition|(
name|box
operator|->
name|active_slider
condition|)
block|{
case|case
literal|0
case|:
comment|/*  low output  */
name|value
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|x
operator|-
name|border
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|width
operator|*
literal|256.0
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|box
operator|->
name|low_adj
argument_list|,
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|1
case|:
comment|/*  high output  */
name|value
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|x
operator|-
name|border
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|width
operator|*
literal|256.0
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|box
operator|->
name|high_adj
argument_list|,
name|CLAMP
argument_list|(
name|value
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_slider_area_expose (GtkWidget * widget,GdkEvent * event,GimpHistogramBox * box)
name|gimp_histogram_slider_area_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpHistogramBox
modifier|*
name|box
parameter_list|)
block|{
name|gint
name|border
init|=
name|box
operator|->
name|view
operator|->
name|border_width
decl_stmt|;
name|gint
name|width
init|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|border
decl_stmt|;
name|box
operator|->
name|slider_pos
index|[
literal|0
index|]
operator|=
name|border
operator|+
name|ROUND
argument_list|(
operator|(
name|gdouble
operator|)
name|width
operator|*
name|box
operator|->
name|high_adj
operator|->
name|lower
operator|/
literal|256.0
argument_list|)
expr_stmt|;
name|box
operator|->
name|slider_pos
index|[
literal|1
index|]
operator|=
name|border
operator|+
name|ROUND
argument_list|(
operator|(
name|gdouble
operator|)
name|width
operator|*
operator|(
name|box
operator|->
name|low_adj
operator|->
name|upper
operator|+
literal|1.0
operator|)
operator|/
literal|256.0
argument_list|)
expr_stmt|;
name|gimp_histogram_draw_slider
argument_list|(
name|widget
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|box
operator|->
name|slider_pos
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|gimp_histogram_draw_slider
argument_list|(
name|widget
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|widget
operator|->
name|style
operator|->
name|white_gc
argument_list|,
name|box
operator|->
name|slider_pos
index|[
literal|1
index|]
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
DECL|function|gimp_histogram_draw_slider (GtkWidget * widget,GdkGC * border_gc,GdkGC * fill_gc,gint xpos)
name|gimp_histogram_draw_slider
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkGC
modifier|*
name|border_gc
parameter_list|,
name|GdkGC
modifier|*
name|fill_gc
parameter_list|,
name|gint
name|xpos
parameter_list|)
block|{
name|gint
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|CONTROL_HEIGHT
condition|;
name|y
operator|++
control|)
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|fill_gc
argument_list|,
name|xpos
operator|-
name|y
operator|/
literal|2
argument_list|,
name|GRADIENT_HEIGHT
operator|+
name|y
argument_list|,
name|xpos
operator|+
name|y
operator|/
literal|2
argument_list|,
name|GRADIENT_HEIGHT
operator|+
name|y
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|border_gc
argument_list|,
name|xpos
argument_list|,
name|GRADIENT_HEIGHT
argument_list|,
name|xpos
operator|-
operator|(
name|CONTROL_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|GRADIENT_HEIGHT
operator|+
name|CONTROL_HEIGHT
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|border_gc
argument_list|,
name|xpos
argument_list|,
name|GRADIENT_HEIGHT
argument_list|,
name|xpos
operator|+
operator|(
name|CONTROL_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|GRADIENT_HEIGHT
operator|+
name|CONTROL_HEIGHT
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|border_gc
argument_list|,
name|xpos
operator|-
operator|(
name|CONTROL_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|GRADIENT_HEIGHT
operator|+
name|CONTROL_HEIGHT
operator|-
literal|1
argument_list|,
name|xpos
operator|+
operator|(
name|CONTROL_HEIGHT
operator|-
literal|1
operator|)
operator|/
literal|2
argument_list|,
name|GRADIENT_HEIGHT
operator|+
name|CONTROL_HEIGHT
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

