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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_class_init
parameter_list|(
name|GimpCanvasClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_init
parameter_list|(
name|GimpCanvas
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_realize
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
name|gimp_canvas_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkGC
modifier|*
name|gimp_canvas_gc_new
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkGC
modifier|*
name|gimp_canvas_guides_gc_new
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|,
name|GdkColor
modifier|*
name|fg
parameter_list|,
name|GdkColor
modifier|*
name|bg
parameter_list|)
function_decl|;
end_function_decl

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
DECL|function|gimp_canvas_get_type (void)
name|gimp_canvas_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|canvas_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|canvas_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|canvas_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpCanvasClass
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
name|gimp_canvas_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpCanvas
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_canvas_init
block|,       }
decl_stmt|;
name|canvas_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_DRAWING_AREA
argument_list|,
literal|"GimpCanvas"
argument_list|,
operator|&
name|canvas_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|canvas_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_class_init (GimpCanvasClass * klass)
name|gimp_canvas_class_init
parameter_list|(
name|GimpCanvasClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_canvas_realize
expr_stmt|;
name|widget_class
operator|->
name|unrealize
operator|=
name|gimp_canvas_unrealize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_init (GimpCanvas * canvas)
name|gimp_canvas_init
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|GIMP_CANVAS_NUM_STYLES
condition|;
name|i
operator|++
control|)
name|canvas
operator|->
name|gc
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_realize (GtkWidget * widget)
name|gimp_canvas_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCanvas
modifier|*
name|canvas
init|=
name|GIMP_CANVAS
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
name|canvas
operator|->
name|gc
index|[
name|GIMP_CANVAS_STYLE_RENDER
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|GIMP_CANVAS_STYLE_RENDER
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_unrealize (GtkWidget * widget)
name|gimp_canvas_unrealize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCanvas
modifier|*
name|canvas
init|=
name|GIMP_CANVAS
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|GIMP_CANVAS_NUM_STYLES
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|canvas
operator|->
name|gc
index|[
name|i
index|]
condition|)
block|{
name|g_object_unref
argument_list|(
name|canvas
operator|->
name|gc
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|canvas
operator|->
name|gc
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
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
name|GdkGC
modifier|*
DECL|function|gimp_canvas_gc_new (GtkWidget * widget,GimpCanvasStyle style)
name|gimp_canvas_gc_new
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|)
block|{
name|GdkGC
modifier|*
name|gc
init|=
name|NULL
decl_stmt|;
name|GdkColor
name|fg
decl_stmt|;
name|GdkColor
name|bg
decl_stmt|;
switch|switch
condition|(
name|style
condition|)
block|{
case|case
name|GIMP_CANVAS_STYLE_XOR
case|:
case|case
name|GIMP_CANVAS_STYLE_XOR_DASHED
case|:
name|fg
operator|.
name|pixel
operator|=
literal|0xFFFFFFFF
expr_stmt|;
name|bg
operator|.
name|pixel
operator|=
literal|0x00000000
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_STYLE_HGUIDE_NORMAL
case|:
case|case
name|GIMP_CANVAS_STYLE_VGUIDE_NORMAL
case|:
name|fg
operator|.
name|red
operator|=
literal|0x0
expr_stmt|;
name|fg
operator|.
name|green
operator|=
literal|0x0
expr_stmt|;
name|fg
operator|.
name|blue
operator|=
literal|0x0
expr_stmt|;
name|bg
operator|.
name|red
operator|=
literal|0x0
expr_stmt|;
name|bg
operator|.
name|green
operator|=
literal|0x7f7f
expr_stmt|;
name|bg
operator|.
name|blue
operator|=
literal|0xffff
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_STYLE_HGUIDE_ACTIVE
case|:
case|case
name|GIMP_CANVAS_STYLE_VGUIDE_ACTIVE
case|:
name|fg
operator|.
name|red
operator|=
literal|0x0
expr_stmt|;
name|fg
operator|.
name|green
operator|=
literal|0x0
expr_stmt|;
name|fg
operator|.
name|blue
operator|=
literal|0x0
expr_stmt|;
name|bg
operator|.
name|red
operator|=
literal|0xffff
expr_stmt|;
name|bg
operator|.
name|green
operator|=
literal|0x0
expr_stmt|;
name|bg
operator|.
name|blue
operator|=
literal|0x0
expr_stmt|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|style
condition|)
block|{
case|case
name|GIMP_CANVAS_STYLE_RENDER
case|:
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_gc_set_exposures
argument_list|(
name|gc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_STYLE_XOR
case|:
case|case
name|GIMP_CANVAS_STYLE_XOR_DASHED
case|:
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
name|gc
argument_list|,
name|GDK_INVERT
argument_list|)
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|gc
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gdk_gc_set_background
argument_list|(
name|gc
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
name|gdk_gc_set_line_attributes
argument_list|(
name|gc
argument_list|,
literal|0
argument_list|,
operator|(
name|style
operator|==
name|GIMP_CANVAS_STYLE_XOR
condition|?
name|GDK_LINE_SOLID
else|:
name|GDK_LINE_ON_OFF_DASH
operator|)
argument_list|,
name|GDK_CAP_NOT_LAST
argument_list|,
name|GDK_JOIN_MITER
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_STYLE_HGUIDE_NORMAL
case|:
case|case
name|GIMP_CANVAS_STYLE_HGUIDE_ACTIVE
case|:
name|gc
operator|=
name|gimp_canvas_guides_gc_new
argument_list|(
name|widget
argument_list|,
name|GIMP_ORIENTATION_HORIZONTAL
argument_list|,
operator|&
name|fg
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_STYLE_VGUIDE_NORMAL
case|:
case|case
name|GIMP_CANVAS_STYLE_VGUIDE_ACTIVE
case|:
name|gc
operator|=
name|gimp_canvas_guides_gc_new
argument_list|(
name|widget
argument_list|,
name|GIMP_ORIENTATION_VERTICAL
argument_list|,
operator|&
name|fg
argument_list|,
operator|&
name|bg
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_STYLE_CUSTOM
case|:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
default|default:
break|break;
block|}
return|return
name|gc
return|;
block|}
end_function

begin_function
specifier|static
name|GdkGC
modifier|*
DECL|function|gimp_canvas_guides_gc_new (GtkWidget * widget,GimpOrientationType orient,GdkColor * fg,GdkColor * bg)
name|gimp_canvas_guides_gc_new
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpOrientationType
name|orient
parameter_list|,
name|GdkColor
modifier|*
name|fg
parameter_list|,
name|GdkColor
modifier|*
name|bg
parameter_list|)
block|{
specifier|const
name|guchar
name|stipple
index|[]
init|=
block|{
literal|0xF0
block|,
comment|/*  ####----  */
literal|0xE1
block|,
comment|/*  ###----#  */
literal|0xC3
block|,
comment|/*  ##----##  */
literal|0x87
block|,
comment|/*  #----###  */
literal|0x0F
block|,
comment|/*  ----####  */
literal|0x1E
block|,
comment|/*  ---####-  */
literal|0x3C
block|,
comment|/*  --####--  */
literal|0x78
block|,
comment|/*  -####---  */
block|}
decl_stmt|;
name|GdkGC
modifier|*
name|gc
decl_stmt|;
name|GdkGCValues
name|values
decl_stmt|;
name|values
operator|.
name|fill
operator|=
name|GDK_OPAQUE_STIPPLED
expr_stmt|;
name|values
operator|.
name|stipple
operator|=
name|gdk_bitmap_create_from_data
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|stipple
argument_list|,
name|orient
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|?
literal|8
else|:
literal|1
argument_list|,
name|orient
operator|==
name|GIMP_ORIENTATION_VERTICAL
condition|?
literal|8
else|:
literal|1
argument_list|)
expr_stmt|;
name|gc
operator|=
name|gdk_gc_new_with_values
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|values
argument_list|,
name|GDK_GC_FILL
operator||
name|GDK_GC_STIPPLE
argument_list|)
expr_stmt|;
name|gdk_gc_set_rgb_fg_color
argument_list|(
name|gc
argument_list|,
name|fg
argument_list|)
expr_stmt|;
name|gdk_gc_set_rgb_bg_color
argument_list|(
name|gc
argument_list|,
name|bg
argument_list|)
expr_stmt|;
return|return
name|gc
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_canvas_new (void)
name|gimp_canvas_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS
argument_list|,
literal|"name"
argument_list|,
literal|"gimp-canvas"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_cursor (GimpCanvas * canvas,gint x,gint y)
name|gimp_canvas_draw_cursor
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
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
name|white_gc
argument_list|,
name|x
operator|-
literal|7
argument_list|,
name|y
operator|-
literal|1
argument_list|,
name|x
operator|+
literal|7
argument_list|,
name|y
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
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|x
operator|-
literal|7
argument_list|,
name|y
argument_list|,
name|x
operator|+
literal|7
argument_list|,
name|y
argument_list|)
expr_stmt|;
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
name|white_gc
argument_list|,
name|x
operator|-
literal|7
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|x
operator|+
literal|7
argument_list|,
name|y
operator|+
literal|1
argument_list|)
expr_stmt|;
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
name|white_gc
argument_list|,
name|x
operator|-
literal|1
argument_list|,
name|y
operator|-
literal|7
argument_list|,
name|x
operator|-
literal|1
argument_list|,
name|y
operator|+
literal|7
argument_list|)
expr_stmt|;
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
name|black_gc
argument_list|,
name|x
argument_list|,
name|y
operator|-
literal|7
argument_list|,
name|x
argument_list|,
name|y
operator|+
literal|7
argument_list|)
expr_stmt|;
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
name|white_gc
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|y
operator|-
literal|7
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|y
operator|+
literal|7
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_point (GimpCanvas * canvas,GimpCanvasStyle style,gint x,gint y)
name|gimp_canvas_draw_point
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_point
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_line (GimpCanvas * canvas,GimpCanvasStyle style,gint x1,gint y1,gint x2,gint y2)
name|gimp_canvas_draw_line
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_line
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_lines (GimpCanvas * canvas,GimpCanvasStyle style,GdkPoint * points,gint num_points)
name|gimp_canvas_draw_lines
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|GdkPoint
modifier|*
name|points
parameter_list|,
name|gint
name|num_points
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_lines
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|points
argument_list|,
name|num_points
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_rectangle (GimpCanvas * canvas,GimpCanvasStyle style,gboolean filled,gint x,gint y,gint width,gint height)
name|gimp_canvas_draw_rectangle
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|filled
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_arc (GimpCanvas * canvas,GimpCanvasStyle style,gboolean filled,gint x,gint y,gint width,gint height,gint angle1,gint angle2)
name|gimp_canvas_draw_arc
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|angle1
parameter_list|,
name|gint
name|angle2
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_arc
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|filled
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|angle1
argument_list|,
name|angle2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_polygon (GimpCanvas * canvas,GimpCanvasStyle style,gboolean filled,GdkPoint * points,gint num_points)
name|gimp_canvas_draw_polygon
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gboolean
name|filled
parameter_list|,
name|GdkPoint
modifier|*
name|points
parameter_list|,
name|gint
name|num_points
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_polygon
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|filled
argument_list|,
name|points
argument_list|,
name|num_points
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_segments (GimpCanvas * canvas,GimpCanvasStyle style,GdkSegment * segments,gint num_segments)
name|gimp_canvas_draw_segments
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|GdkSegment
modifier|*
name|segments
parameter_list|,
name|gint
name|num_segments
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_segments
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|segments
argument_list|,
name|num_segments
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_draw_rgb (GimpCanvas * canvas,GimpCanvasStyle style,gint x,gint y,gint width,gint height,guchar * rgb_buf,gint rowstride,gint xdith,gint ydith)
name|gimp_canvas_draw_rgb
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpCanvasStyle
name|style
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|guchar
modifier|*
name|rgb_buf
parameter_list|,
name|gint
name|rowstride
parameter_list|,
name|gint
name|xdith
parameter_list|,
name|gint
name|ydith
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|canvas
operator|->
name|gc
index|[
name|style
index|]
condition|)
name|canvas
operator|->
name|gc
index|[
name|style
index|]
operator|=
name|gimp_canvas_gc_new
argument_list|(
name|widget
argument_list|,
name|style
argument_list|)
expr_stmt|;
name|gdk_draw_rgb_image_dithalign
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|canvas
operator|->
name|gc
index|[
name|style
index|]
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GDK_RGB_DITHER_MAX
argument_list|,
name|rgb_buf
argument_list|,
name|rowstride
argument_list|,
name|xdith
argument_list|,
name|ydith
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_set_bg_color (GimpCanvas * canvas,GimpRGB * color)
name|gimp_canvas_set_bg_color
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|canvas
argument_list|)
decl_stmt|;
name|GdkColormap
modifier|*
name|colormap
decl_stmt|;
name|GdkColor
name|gdk_color
decl_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_REALIZED
argument_list|(
name|widget
argument_list|)
condition|)
return|return;
name|gimp_rgb_get_gdk_color
argument_list|(
name|color
argument_list|,
operator|&
name|gdk_color
argument_list|)
expr_stmt|;
name|colormap
operator|=
name|gdk_drawable_get_colormap
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|colormap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gdk_colormap_alloc_color
argument_list|(
name|colormap
argument_list|,
operator|&
name|gdk_color
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gdk_window_set_background
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|gdk_color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_set_custom_gc (GimpCanvas * canvas,GdkGC * gc)
name|gimp_canvas_set_custom_gc
parameter_list|(
name|GimpCanvas
modifier|*
name|canvas
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|)
block|{
if|if
condition|(
name|canvas
operator|->
name|gc
index|[
name|GIMP_CANVAS_STYLE_CUSTOM
index|]
condition|)
name|g_object_unref
argument_list|(
name|canvas
operator|->
name|gc
index|[
name|GIMP_CANVAS_STYLE_CUSTOM
index|]
argument_list|)
expr_stmt|;
name|canvas
operator|->
name|gc
index|[
name|GIMP_CANVAS_STYLE_CUSTOM
index|]
operator|=
name|gc
expr_stmt|;
if|if
condition|(
name|gc
condition|)
name|g_object_ref
argument_list|(
name|gc
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

