begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimphruler.h"
end_include

begin_define
DECL|macro|RULER_HEIGHT
define|#
directive|define
name|RULER_HEIGHT
value|13
end_define

begin_define
DECL|macro|MINIMUM_INCR
define|#
directive|define
name|MINIMUM_INCR
value|5
end_define

begin_define
DECL|macro|MAXIMUM_SUBDIVIDE
define|#
directive|define
name|MAXIMUM_SUBDIVIDE
value|5
end_define

begin_define
DECL|macro|MAXIMUM_SCALES
define|#
directive|define
name|MAXIMUM_SCALES
value|10
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon275b2ddd0108
block|{
DECL|member|xsrc
name|gint
name|xsrc
decl_stmt|;
DECL|member|ysrc
name|gint
name|ysrc
decl_stmt|;
DECL|typedef|GimpHRulerPrivate
block|}
name|GimpHRulerPrivate
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gint
name|gimp_hruler_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_hruler_draw_ticks
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_hruler_draw_pos
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpHRuler,gimp_hruler,GIMP_TYPE_RULER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHRuler
argument_list|,
argument|gimp_hruler
argument_list|,
argument|GIMP_TYPE_RULER
argument_list|)
end_macro

begin_define
DECL|macro|GIMP_HRULER_GET_PRIVATE (ruler)
define|#
directive|define
name|GIMP_HRULER_GET_PRIVATE
parameter_list|(
name|ruler
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (ruler, GIMP_TYPE_HRULER, GimpHRulerPrivate)
end_define

begin_function
specifier|static
name|void
name|gimp_hruler_class_init
parameter_list|(
name|GimpHRulerClass
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
name|GimpRulerClass
modifier|*
name|ruler_class
init|=
name|GIMP_RULER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_hruler_motion_notify
expr_stmt|;
name|ruler_class
operator|->
name|draw_ticks
operator|=
name|gimp_hruler_draw_ticks
expr_stmt|;
name|ruler_class
operator|->
name|draw_pos
operator|=
name|gimp_hruler_draw_pos
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpHRulerPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_hruler_init (GimpHRuler * hruler)
name|gimp_hruler_init
parameter_list|(
name|GimpHRuler
modifier|*
name|hruler
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|hruler
argument_list|)
decl_stmt|;
name|widget
operator|->
name|requisition
operator|.
name|width
operator|=
name|widget
operator|->
name|style
operator|->
name|xthickness
operator|*
literal|2
operator|+
literal|1
expr_stmt|;
name|widget
operator|->
name|requisition
operator|.
name|height
operator|=
name|widget
operator|->
name|style
operator|->
name|ythickness
operator|*
literal|2
operator|+
name|RULER_HEIGHT
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_hruler_new (void)
name|gimp_hruler_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_HRULER
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_hruler_motion_notify (GtkWidget * widget,GdkEventMotion * event)
name|gimp_hruler_motion_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventMotion
modifier|*
name|event
parameter_list|)
block|{
name|GimpRuler
modifier|*
name|ruler
init|=
name|GIMP_RULER
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gdouble
name|lower
decl_stmt|;
name|gdouble
name|upper
decl_stmt|;
name|gdouble
name|position
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gdk_event_request_motions
argument_list|(
name|event
argument_list|)
expr_stmt|;
name|x
operator|=
name|event
operator|->
name|x
expr_stmt|;
name|gimp_ruler_get_range
argument_list|(
name|ruler
argument_list|,
operator|&
name|lower
argument_list|,
operator|&
name|upper
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|position
operator|=
name|lower
operator|+
operator|(
operator|(
name|upper
operator|-
name|lower
operator|)
operator|*
name|x
operator|)
operator|/
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|g_object_set
argument_list|(
name|ruler
argument_list|,
literal|"position"
argument_list|,
name|position
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_ruler_draw_pos
argument_list|(
name|ruler
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
DECL|function|gimp_hruler_draw_ticks (GimpRuler * ruler)
name|gimp_hruler_draw_ticks
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
specifier|const
name|GimpRulerMetric
modifier|*
name|metric
decl_stmt|;
name|GdkDrawable
modifier|*
name|backing_store
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|xthickness
decl_stmt|;
name|gint
name|ythickness
decl_stmt|;
name|gint
name|length
decl_stmt|,
name|ideal_length
decl_stmt|;
name|gdouble
name|lower
decl_stmt|,
name|upper
decl_stmt|;
comment|/* Upper and lower limits, in ruler units */
name|gdouble
name|increment
decl_stmt|;
comment|/* Number of pixels per unit */
name|gint
name|scale
decl_stmt|;
comment|/* Number of units per major unit */
name|gdouble
name|start
decl_stmt|,
name|end
decl_stmt|,
name|cur
decl_stmt|;
name|gchar
name|unit_str
index|[
literal|32
index|]
decl_stmt|;
name|gint
name|digit_height
decl_stmt|;
name|gint
name|digit_offset
decl_stmt|;
name|gint
name|text_width
decl_stmt|;
name|gint
name|pos
decl_stmt|;
name|gdouble
name|max_size
decl_stmt|;
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
name|PangoRectangle
name|logical_rect
decl_stmt|,
name|ink_rect
decl_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
condition|)
return|return;
name|backing_store
operator|=
name|_gimp_ruler_get_backing_store
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
name|xthickness
operator|=
name|widget
operator|->
name|style
operator|->
name|xthickness
expr_stmt|;
name|ythickness
operator|=
name|widget
operator|->
name|style
operator|->
name|ythickness
expr_stmt|;
name|layout
operator|=
name|_gimp_ruler_create_pango_layout
argument_list|(
name|widget
argument_list|,
literal|"012456789"
argument_list|)
expr_stmt|;
name|pango_layout_get_extents
argument_list|(
name|layout
argument_list|,
operator|&
name|ink_rect
argument_list|,
operator|&
name|logical_rect
argument_list|)
expr_stmt|;
name|digit_height
operator|=
name|PANGO_PIXELS
argument_list|(
name|ink_rect
operator|.
name|height
argument_list|)
operator|+
literal|2
expr_stmt|;
name|digit_offset
operator|=
name|ink_rect
operator|.
name|y
expr_stmt|;
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
name|ythickness
operator|*
literal|2
expr_stmt|;
name|gtk_paint_box
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|backing_store
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_OUT
argument_list|,
name|NULL
argument_list|,
name|widget
argument_list|,
literal|"hruler"
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
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|backing_store
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|widget
operator|->
name|style
operator|->
name|fg
index|[
name|widget
operator|->
name|state
index|]
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|xthickness
argument_list|,
name|height
operator|+
name|ythickness
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
literal|2
operator|*
name|xthickness
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_ruler_get_range
argument_list|(
name|ruler
argument_list|,
operator|&
name|lower
argument_list|,
operator|&
name|upper
argument_list|,
name|NULL
argument_list|,
operator|&
name|max_size
argument_list|)
expr_stmt|;
name|metric
operator|=
name|_gimp_ruler_get_metric
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
name|upper
operator|=
name|upper
operator|/
name|metric
operator|->
name|pixels_per_unit
expr_stmt|;
name|lower
operator|=
name|lower
operator|/
name|metric
operator|->
name|pixels_per_unit
expr_stmt|;
if|if
condition|(
operator|(
name|upper
operator|-
name|lower
operator|)
operator|==
literal|0
condition|)
goto|goto
name|out
goto|;
name|increment
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|upper
operator|-
name|lower
operator|)
expr_stmt|;
comment|/* determine the scale    *  We calculate the text size as for the vruler instead of using    *  text_width = gdk_string_width(font, unit_str), so that the result    *  for the scale looks consistent with an accompanying vruler    */
name|scale
operator|=
name|ceil
argument_list|(
name|max_size
operator|/
name|metric
operator|->
name|pixels_per_unit
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|unit_str
argument_list|,
sizeof|sizeof
argument_list|(
name|unit_str
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|text_width
operator|=
name|strlen
argument_list|(
name|unit_str
argument_list|)
operator|*
name|digit_height
operator|+
literal|1
expr_stmt|;
for|for
control|(
name|scale
operator|=
literal|0
init|;
name|scale
operator|<
name|MAXIMUM_SCALES
condition|;
name|scale
operator|++
control|)
if|if
condition|(
name|metric
operator|->
name|ruler_scale
index|[
name|scale
index|]
operator|*
name|fabs
argument_list|(
name|increment
argument_list|)
operator|>
literal|2
operator|*
name|text_width
condition|)
break|break;
if|if
condition|(
name|scale
operator|==
name|MAXIMUM_SCALES
condition|)
name|scale
operator|=
name|MAXIMUM_SCALES
operator|-
literal|1
expr_stmt|;
comment|/* drawing starts here */
name|length
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
name|MAXIMUM_SUBDIVIDE
operator|-
literal|1
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
block|{
name|gdouble
name|subd_incr
init|=
operator|(
operator|(
name|gdouble
operator|)
name|metric
operator|->
name|ruler_scale
index|[
name|scale
index|]
operator|/
operator|(
name|gdouble
operator|)
name|metric
operator|->
name|subdivide
index|[
name|i
index|]
operator|)
decl_stmt|;
if|if
condition|(
name|subd_incr
operator|*
name|fabs
argument_list|(
name|increment
argument_list|)
operator|<=
name|MINIMUM_INCR
condition|)
continue|continue;
comment|/* Calculate the length of the tickmarks. Make sure that        * this length increases for each set of ticks        */
name|ideal_length
operator|=
name|height
operator|/
operator|(
name|i
operator|+
literal|1
operator|)
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|ideal_length
operator|>
operator|++
name|length
condition|)
name|length
operator|=
name|ideal_length
expr_stmt|;
if|if
condition|(
name|lower
operator|<
name|upper
condition|)
block|{
name|start
operator|=
name|floor
argument_list|(
name|lower
operator|/
name|subd_incr
argument_list|)
operator|*
name|subd_incr
expr_stmt|;
name|end
operator|=
name|ceil
argument_list|(
name|upper
operator|/
name|subd_incr
argument_list|)
operator|*
name|subd_incr
expr_stmt|;
block|}
else|else
block|{
name|start
operator|=
name|floor
argument_list|(
name|upper
operator|/
name|subd_incr
argument_list|)
operator|*
name|subd_incr
expr_stmt|;
name|end
operator|=
name|ceil
argument_list|(
name|lower
operator|/
name|subd_incr
argument_list|)
operator|*
name|subd_incr
expr_stmt|;
block|}
for|for
control|(
name|cur
operator|=
name|start
init|;
name|cur
operator|<=
name|end
condition|;
name|cur
operator|+=
name|subd_incr
control|)
block|{
name|pos
operator|=
name|ROUND
argument_list|(
operator|(
name|cur
operator|-
name|lower
operator|)
operator|*
name|increment
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|pos
argument_list|,
name|height
operator|+
name|ythickness
operator|-
name|length
argument_list|,
literal|1
argument_list|,
name|length
argument_list|)
expr_stmt|;
comment|/* draw label */
if|if
condition|(
name|i
operator|==
literal|0
condition|)
block|{
name|g_snprintf
argument_list|(
name|unit_str
argument_list|,
sizeof|sizeof
argument_list|(
name|unit_str
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
operator|(
name|int
operator|)
name|cur
argument_list|)
expr_stmt|;
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|unit_str
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_extents
argument_list|(
name|layout
argument_list|,
operator|&
name|logical_rect
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_paint_layout
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|backing_store
argument_list|,
name|GTK_WIDGET_STATE
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|widget
argument_list|,
literal|"hruler"
argument_list|,
name|pos
operator|+
literal|2
argument_list|,
name|ythickness
operator|+
name|PANGO_PIXELS
argument_list|(
name|logical_rect
operator|.
name|y
operator|-
name|digit_offset
argument_list|)
argument_list|,
name|layout
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|out
label|:
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_hruler_draw_pos (GimpRuler * ruler)
name|gimp_hruler_draw_pos
parameter_list|(
name|GimpRuler
modifier|*
name|ruler
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|ruler
argument_list|)
condition|)
block|{
name|GimpHRulerPrivate
modifier|*
name|priv
init|=
name|GIMP_HRULER_GET_PRIVATE
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bs_width
decl_stmt|,
name|bs_height
decl_stmt|;
name|gint
name|xthickness
decl_stmt|;
name|gint
name|ythickness
decl_stmt|;
name|xthickness
operator|=
name|widget
operator|->
name|style
operator|->
name|xthickness
expr_stmt|;
name|ythickness
operator|=
name|widget
operator|->
name|style
operator|->
name|ythickness
expr_stmt|;
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
name|ythickness
operator|*
literal|2
expr_stmt|;
name|bs_width
operator|=
name|height
operator|/
literal|2
operator|+
literal|2
expr_stmt|;
name|bs_width
operator||=
literal|1
expr_stmt|;
comment|/* make sure it's odd */
name|bs_height
operator|=
name|bs_width
operator|/
literal|2
operator|+
literal|1
expr_stmt|;
if|if
condition|(
operator|(
name|bs_width
operator|>
literal|0
operator|)
operator|&&
operator|(
name|bs_height
operator|>
literal|0
operator|)
condition|)
block|{
name|GdkDrawable
modifier|*
name|backing_store
init|=
name|_gimp_ruler_get_backing_store
argument_list|(
name|ruler
argument_list|)
decl_stmt|;
name|cairo_t
modifier|*
name|cr
init|=
name|gdk_cairo_create
argument_list|(
name|widget
operator|->
name|window
argument_list|)
decl_stmt|;
name|gdouble
name|lower
decl_stmt|;
name|gdouble
name|upper
decl_stmt|;
name|gdouble
name|position
decl_stmt|;
name|gdouble
name|increment
decl_stmt|;
comment|/*  If a backing store exists, restore the ruler  */
if|if
condition|(
name|backing_store
condition|)
name|gdk_draw_drawable
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
name|backing_store
argument_list|,
name|priv
operator|->
name|xsrc
argument_list|,
name|priv
operator|->
name|ysrc
argument_list|,
name|priv
operator|->
name|xsrc
argument_list|,
name|priv
operator|->
name|ysrc
argument_list|,
name|bs_width
argument_list|,
name|bs_height
argument_list|)
expr_stmt|;
name|gimp_ruler_get_range
argument_list|(
name|ruler
argument_list|,
operator|&
name|lower
argument_list|,
operator|&
name|upper
argument_list|,
operator|&
name|position
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|increment
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|upper
operator|-
name|lower
operator|)
expr_stmt|;
name|x
operator|=
name|ROUND
argument_list|(
operator|(
name|position
operator|-
name|lower
operator|)
operator|*
name|increment
argument_list|)
operator|+
operator|(
name|xthickness
operator|-
name|bs_width
operator|)
operator|/
literal|2
operator|-
literal|1
expr_stmt|;
name|y
operator|=
operator|(
name|height
operator|+
name|bs_height
operator|)
operator|/
literal|2
operator|+
name|ythickness
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|widget
operator|->
name|style
operator|->
name|fg
index|[
name|widget
operator|->
name|state
index|]
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|bs_width
operator|/
literal|2.
argument_list|,
name|y
operator|+
name|bs_height
argument_list|)
expr_stmt|;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|x
operator|+
name|bs_width
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|priv
operator|->
name|xsrc
operator|=
name|x
expr_stmt|;
name|priv
operator|->
name|ysrc
operator|=
name|y
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

