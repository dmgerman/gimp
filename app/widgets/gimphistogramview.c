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
file|"libgimpmath/gimpmath.h"
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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogramview.h"
end_include

begin_define
DECL|macro|MIN_WIDTH
define|#
directive|define
name|MIN_WIDTH
value|64
end_define

begin_define
DECL|macro|MIN_HEIGHT
define|#
directive|define
name|MIN_HEIGHT
value|64
end_define

begin_enum
enum|enum
DECL|enum|__anon2a17561f0103
block|{
DECL|enumerator|RANGE_CHANGED
name|RANGE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a17561f0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CHANNEL
name|PROP_CHANNEL
block|,
DECL|enumerator|PROP_SCALE
name|PROP_SCALE
block|,
DECL|enumerator|PROP_BORDER_WIDTH
name|PROP_BORDER_WIDTH
block|,
DECL|enumerator|PROP_SUBDIVISIONS
name|PROP_SUBDIVISIONS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_histogram_view_class_init
parameter_list|(
name|GimpHistogramViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_view_init
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_view_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
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
name|gimp_histogram_view_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
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
name|gimp_histogram_view_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_histogram_view_expose
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
name|gboolean
name|gimp_histogram_view_button_press
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
name|gimp_histogram_view_button_release
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
name|gimp_histogram_view_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|histogram_view_signals
specifier|static
name|guint
name|histogram_view_signals
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
DECL|function|gimp_histogram_view_get_type (void)
name|gimp_histogram_view_get_type
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
name|GimpHistogramViewClass
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
name|gimp_histogram_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpHistogramView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_histogram_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_DRAWING_AREA
argument_list|,
literal|"GimpHistogramView"
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
DECL|function|gimp_histogram_view_class_init (GimpHistogramViewClass * klass)
name|gimp_histogram_view_class_init
parameter_list|(
name|GimpHistogramViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
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
name|histogram_view_signals
index|[
name|RANGE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"range_changed"
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
name|GimpHistogramViewClass
argument_list|,
name|range_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT_INT
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
name|object_class
operator|->
name|get_property
operator|=
name|gimp_histogram_view_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_histogram_view_set_property
expr_stmt|;
name|widget_class
operator|->
name|size_request
operator|=
name|gimp_histogram_view_size_request
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_histogram_view_expose
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_histogram_view_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_histogram_view_button_release
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_histogram_view_motion_notify
expr_stmt|;
name|klass
operator|->
name|range_changed
operator|=
name|NULL
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CHANNEL
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"histogram-channel"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_HISTOGRAM_CHANNEL
argument_list|,
name|GIMP_HISTOGRAM_VALUE
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SCALE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"histogram-scale"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_HISTOGRAM_SCALE
argument_list|,
name|GIMP_HISTOGRAM_SCALE_LINEAR
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BORDER_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"border-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|32
argument_list|,
literal|1
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SUBDIVISIONS
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"subdivisions"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
literal|64
argument_list|,
literal|5
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_view_init (GimpHistogramView * view)
name|gimp_histogram_view_init
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
block|{
name|view
operator|->
name|histogram
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|start
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|end
operator|=
literal|255
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_view_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_histogram_view_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
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
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CHANNEL
case|:
name|view
operator|->
name|channel
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SCALE
case|:
name|view
operator|->
name|scale
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BORDER_WIDTH
case|:
name|view
operator|->
name|border_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUBDIVISIONS
case|:
name|view
operator|->
name|subdivisions
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
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
DECL|function|gimp_histogram_view_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_histogram_view_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
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
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CHANNEL
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|channel
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SCALE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|scale
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BORDER_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|border_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SUBDIVISIONS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|subdivisions
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
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
DECL|function|gimp_histogram_view_size_request (GtkWidget * widget,GtkRequisition * requisition)
name|gimp_histogram_view_size_request
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkRequisition
modifier|*
name|requisition
parameter_list|)
block|{
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|requisition
operator|->
name|width
operator|=
name|MIN_WIDTH
operator|+
literal|2
operator|*
name|view
operator|->
name|border_width
expr_stmt|;
name|requisition
operator|->
name|height
operator|=
name|MIN_HEIGHT
operator|+
literal|2
operator|*
name|view
operator|->
name|border_width
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_view_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_histogram_view_expose
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
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|;
name|gint
name|border
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|max
decl_stmt|;
name|gint
name|xstop
decl_stmt|;
if|if
condition|(
operator|!
name|view
operator|->
name|histogram
condition|)
return|return
name|FALSE
return|;
name|border
operator|=
name|view
operator|->
name|border_width
expr_stmt|;
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|border
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
operator|*
name|border
expr_stmt|;
comment|/*  find the maximum value  */
name|max
operator|=
name|gimp_histogram_get_maximum
argument_list|(
name|view
operator|->
name|histogram
argument_list|,
name|view
operator|->
name|channel
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|view
operator|->
name|scale
condition|)
block|{
case|case
name|GIMP_HISTOGRAM_SCALE_LINEAR
case|:
break|break;
case|case
name|GIMP_HISTOGRAM_SCALE_LOGARITHMIC
case|:
if|if
condition|(
name|max
operator|>
literal|0.0
condition|)
name|max
operator|=
name|log
argument_list|(
name|max
argument_list|)
expr_stmt|;
else|else
name|max
operator|=
literal|1.0
expr_stmt|;
break|break;
block|}
name|x1
operator|=
name|CLAMP
argument_list|(
name|MIN
argument_list|(
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|MAX
argument_list|(
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
comment|/*  Draw the background  */
name|gdk_draw_rectangle
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|base_gc
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
comment|/*  Draw the outer border  */
name|gdk_draw_rectangle
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|text_aa_gc
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|FALSE
argument_list|,
name|border
argument_list|,
name|border
argument_list|,
name|width
operator|-
literal|1
argument_list|,
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*  Draw the spikes  */
name|xstop
operator|=
literal|1
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
name|gdouble
name|value
init|=
literal|0.0
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gboolean
name|in_selection
init|=
name|FALSE
decl_stmt|;
name|GdkGC
modifier|*
name|spike_gc
decl_stmt|;
name|i
operator|=
operator|(
name|x
operator|*
literal|256
operator|)
operator|/
name|width
expr_stmt|;
name|j
operator|=
operator|(
operator|(
name|x
operator|+
literal|1
operator|)
operator|*
literal|256
operator|)
operator|/
name|width
expr_stmt|;
do|do
block|{
name|gdouble
name|v
decl_stmt|;
if|if
condition|(
operator|!
name|in_selection
condition|)
name|in_selection
operator|=
operator|(
operator|(
name|x1
operator|!=
literal|0
operator|||
name|x2
operator|!=
literal|255
operator|)
operator|&&
name|x1
operator|<=
name|i
operator|&&
name|i
operator|<=
name|x2
operator|)
expr_stmt|;
name|v
operator|=
name|gimp_histogram_get_value
argument_list|(
name|view
operator|->
name|histogram
argument_list|,
name|view
operator|->
name|channel
argument_list|,
name|i
operator|++
argument_list|)
expr_stmt|;
if|if
condition|(
name|v
operator|>
name|value
condition|)
name|value
operator|=
name|v
expr_stmt|;
block|}
do|while
condition|(
name|i
operator|<
name|j
condition|)
do|;
if|if
condition|(
name|view
operator|->
name|subdivisions
operator|>
literal|1
operator|&&
name|x
operator|>=
operator|(
name|xstop
operator|*
name|width
operator|/
name|view
operator|->
name|subdivisions
operator|)
condition|)
block|{
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|text_aa_gc
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|x
operator|+
name|border
argument_list|,
name|border
argument_list|,
name|x
operator|+
name|border
argument_list|,
name|border
operator|+
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|xstop
operator|++
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_selection
condition|)
block|{
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|base_gc
index|[
name|GTK_STATE_SELECTED
index|]
argument_list|,
name|x
operator|+
name|border
argument_list|,
name|border
argument_list|,
name|x
operator|+
name|border
argument_list|,
name|border
operator|+
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|value
operator|<=
literal|0.0
condition|)
continue|continue;
switch|switch
condition|(
name|view
operator|->
name|scale
condition|)
block|{
case|case
name|GIMP_HISTOGRAM_SCALE_LINEAR
case|:
name|y
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
operator|(
name|height
operator|-
literal|1
operator|)
operator|*
name|value
operator|)
operator|/
name|max
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_HISTOGRAM_SCALE_LOGARITHMIC
case|:
name|y
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
operator|(
name|height
operator|-
literal|1
operator|)
operator|*
name|log
argument_list|(
name|value
argument_list|)
operator|)
operator|/
name|max
argument_list|)
expr_stmt|;
break|break;
default|default:
name|y
operator|=
literal|0
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|in_selection
condition|)
block|{
if|if
condition|(
name|view
operator|->
name|light_histogram
condition|)
name|spike_gc
operator|=
name|widget
operator|->
name|style
operator|->
name|mid_gc
index|[
name|GTK_STATE_SELECTED
index|]
expr_stmt|;
else|else
name|spike_gc
operator|=
name|widget
operator|->
name|style
operator|->
name|text_gc
index|[
name|GTK_STATE_SELECTED
index|]
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|view
operator|->
name|light_histogram
condition|)
name|spike_gc
operator|=
name|widget
operator|->
name|style
operator|->
name|mid_gc
index|[
name|GTK_STATE_NORMAL
index|]
expr_stmt|;
else|else
name|spike_gc
operator|=
name|widget
operator|->
name|style
operator|->
name|text_gc
index|[
name|GTK_STATE_NORMAL
index|]
expr_stmt|;
block|}
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|spike_gc
argument_list|,
name|x
operator|+
name|border
argument_list|,
name|height
operator|+
name|border
operator|-
literal|1
argument_list|,
name|x
operator|+
name|border
argument_list|,
name|height
operator|+
name|border
operator|-
name|y
operator|-
literal|1
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
DECL|function|gimp_histogram_view_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_histogram_view_button_press
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
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gint
name|width
decl_stmt|;
name|gdk_pointer_grab
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|view
operator|->
name|border_width
expr_stmt|;
name|view
operator|->
name|start
operator|=
name|CLAMP
argument_list|(
operator|(
operator|(
operator|(
name|bevent
operator|->
name|x
operator|-
name|view
operator|->
name|border_width
operator|)
operator|*
literal|256
operator|)
operator|/
name|width
operator|)
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|view
operator|->
name|end
operator|=
name|view
operator|->
name|start
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_view_button_release (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_histogram_view_button_release
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
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|gint
name|start
decl_stmt|,
name|end
decl_stmt|;
name|gdk_display_pointer_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|start
operator|=
name|view
operator|->
name|start
expr_stmt|;
name|end
operator|=
name|view
operator|->
name|end
expr_stmt|;
name|view
operator|->
name|start
operator|=
name|MIN
argument_list|(
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|view
operator|->
name|end
operator|=
name|MAX
argument_list|(
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|histogram_view_signals
index|[
name|RANGE_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_view_motion_notify (GtkWidget * widget,GdkEventMotion * mevent)
name|gimp_histogram_view_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|)
block|{
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_VIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|width
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
operator|*
name|view
operator|->
name|border_width
expr_stmt|;
name|view
operator|->
name|start
operator|=
name|CLAMP
argument_list|(
operator|(
operator|(
operator|(
name|mevent
operator|->
name|x
operator|-
name|view
operator|->
name|border_width
operator|)
operator|*
literal|256
operator|)
operator|/
name|width
operator|)
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|widget
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
DECL|function|gimp_histogram_view_new (gboolean range)
name|gimp_histogram_view_new
parameter_list|(
name|gboolean
name|range
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|view
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_HISTOGRAM_VIEW
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|range
condition|)
name|gtk_widget_add_events
argument_list|(
name|view
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
argument_list|)
expr_stmt|;
return|return
name|view
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_view_set_histogram (GimpHistogramView * view,GimpHistogram * histogram)
name|gimp_histogram_view_set_histogram
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|histogram
operator|!=
name|histogram
condition|)
block|{
name|view
operator|->
name|histogram
operator|=
name|histogram
expr_stmt|;
if|if
condition|(
name|histogram
operator|&&
name|view
operator|->
name|channel
operator|>=
name|gimp_histogram_nchannels
argument_list|(
name|histogram
argument_list|)
condition|)
name|gimp_histogram_view_set_channel
argument_list|(
name|view
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpHistogram
modifier|*
DECL|function|gimp_histogram_view_get_histogram (GimpHistogramView * view)
name|gimp_histogram_view_get_histogram
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|view
operator|->
name|histogram
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_view_set_channel (GimpHistogramView * view,GimpHistogramChannel channel)
name|gimp_histogram_view_set_channel
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|view
argument_list|,
literal|"histogram-channel"
argument_list|,
name|channel
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpHistogramChannel
DECL|function|gimp_histogram_view_get_channel (GimpHistogramView * view)
name|gimp_histogram_view_get_channel
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|view
operator|->
name|channel
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_view_set_scale (GimpHistogramView * view,GimpHistogramScale scale)
name|gimp_histogram_view_set_scale
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|GimpHistogramScale
name|scale
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|view
argument_list|,
literal|"histogram-scale"
argument_list|,
name|scale
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpHistogramScale
DECL|function|gimp_histogram_view_get_scale (GimpHistogramView * view)
name|gimp_histogram_view_get_scale
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|view
operator|->
name|scale
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_view_set_range (GimpHistogramView * view,gint start,gint end)
name|gimp_histogram_view_set_range
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
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|start
operator|=
name|MIN
argument_list|(
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|view
operator|->
name|end
operator|=
name|MAX
argument_list|(
name|start
argument_list|,
name|end
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|view
argument_list|,
name|histogram_view_signals
index|[
name|RANGE_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_histogram_view_get_range (GimpHistogramView * view,gint * start,gint * end)
name|gimp_histogram_view_get_range
parameter_list|(
name|GimpHistogramView
modifier|*
name|view
parameter_list|,
name|gint
modifier|*
name|start
parameter_list|,
name|gint
modifier|*
name|end
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_HISTOGRAM_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|start
condition|)
operator|*
name|start
operator|=
name|view
operator|->
name|start
expr_stmt|;
if|if
condition|(
name|end
condition|)
operator|*
name|end
operator|=
name|view
operator|->
name|end
expr_stmt|;
block|}
end_function

end_unit

