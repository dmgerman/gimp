begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfgbgview.c  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpcontext.h"
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
file|"gimpfgbgview.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon289488150103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_fg_bg_view_set_property
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
name|gimp_fg_bg_view_get_property
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
name|gimp_fg_bg_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_fg_bg_view_expose
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFgBgView,gimp_fg_bg_view,GTK_TYPE_WIDGET)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFgBgView
argument_list|,
argument|gimp_fg_bg_view
argument_list|,
argument|GTK_TYPE_WIDGET
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_fg_bg_view_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_fg_bg_view_class_init
parameter_list|(
name|GimpFgBgViewClass
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
name|GtkObjectClass
modifier|*
name|gtk_object_class
init|=
name|GTK_OBJECT_CLASS
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_fg_bg_view_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_fg_bg_view_get_property
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_fg_bg_view_destroy
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_fg_bg_view_expose
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fg_bg_view_init (GimpFgBgView * view)
name|gimp_fg_bg_view_init
parameter_list|(
name|GimpFgBgView
modifier|*
name|view
parameter_list|)
block|{
name|gtk_widget_set_has_window
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|view
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fg_bg_view_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_fg_bg_view_set_property
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
name|GimpFgBgView
modifier|*
name|view
init|=
name|GIMP_FG_BG_VIEW
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
name|PROP_CONTEXT
case|:
name|gimp_fg_bg_view_set_context
argument_list|(
name|view
argument_list|,
name|g_value_get_object
argument_list|(
name|value
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
DECL|function|gimp_fg_bg_view_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_fg_bg_view_get_property
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
name|GimpFgBgView
modifier|*
name|view
init|=
name|GIMP_FG_BG_VIEW
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
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|view
operator|->
name|context
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
DECL|function|gimp_fg_bg_view_destroy (GtkObject * object)
name|gimp_fg_bg_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFgBgView
modifier|*
name|view
init|=
name|GIMP_FG_BG_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|context
condition|)
name|gimp_fg_bg_view_set_context
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|render_buf
condition|)
block|{
name|g_free
argument_list|(
name|view
operator|->
name|render_buf
argument_list|)
expr_stmt|;
name|view
operator|->
name|render_buf
operator|=
name|NULL
expr_stmt|;
name|view
operator|->
name|render_buf_size
operator|=
literal|0
expr_stmt|;
block|}
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
DECL|function|gimp_fg_bg_view_draw_rect (GimpFgBgView * view,GdkDrawable * drawable,GdkGC * gc,gint x,gint y,gint width,gint height,const GimpRGB * color)
name|gimp_fg_bg_view_draw_rect
parameter_list|(
name|GimpFgBgView
modifier|*
name|view
parameter_list|,
name|GdkDrawable
modifier|*
name|drawable
parameter_list|,
name|GdkGC
modifier|*
name|gc
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
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|gint
name|rowstride
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|xx
decl_stmt|,
name|yy
decl_stmt|;
name|guchar
modifier|*
name|bp
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|width
operator|>
literal|0
operator|&&
name|height
operator|>
literal|0
operator|)
condition|)
return|return;
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|rowstride
operator|=
literal|3
operator|*
operator|(
operator|(
name|width
operator|+
literal|3
operator|)
operator|&
operator|-
literal|4
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|view
operator|->
name|render_buf
operator|||
name|view
operator|->
name|render_buf_size
operator|<
name|height
operator|*
name|rowstride
condition|)
block|{
name|view
operator|->
name|render_buf_size
operator|=
name|rowstride
operator|*
name|height
expr_stmt|;
name|g_free
argument_list|(
name|view
operator|->
name|render_buf
argument_list|)
expr_stmt|;
name|view
operator|->
name|render_buf
operator|=
name|g_malloc
argument_list|(
name|view
operator|->
name|render_buf_size
argument_list|)
expr_stmt|;
block|}
name|bp
operator|=
name|view
operator|->
name|render_buf
expr_stmt|;
for|for
control|(
name|xx
operator|=
literal|0
init|;
name|xx
operator|<
name|width
condition|;
name|xx
operator|++
control|)
block|{
operator|*
name|bp
operator|++
operator|=
name|r
expr_stmt|;
operator|*
name|bp
operator|++
operator|=
name|g
expr_stmt|;
operator|*
name|bp
operator|++
operator|=
name|b
expr_stmt|;
block|}
name|bp
operator|=
name|view
operator|->
name|render_buf
expr_stmt|;
for|for
control|(
name|yy
operator|=
literal|1
init|;
name|yy
operator|<
name|height
condition|;
name|yy
operator|++
control|)
block|{
name|bp
operator|+=
name|rowstride
expr_stmt|;
name|memcpy
argument_list|(
name|bp
argument_list|,
name|view
operator|->
name|render_buf
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
name|gdk_draw_rgb_image
argument_list|(
name|drawable
argument_list|,
name|gc
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
name|view
operator|->
name|render_buf
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_fg_bg_view_expose (GtkWidget * widget,GdkEventExpose * eevent)
name|gimp_fg_bg_view_expose
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
name|GimpFgBgView
modifier|*
name|view
init|=
name|GIMP_FG_BG_VIEW
argument_list|(
name|widget
argument_list|)
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
name|GdkWindow
modifier|*
name|window
init|=
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
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
name|rect_w
decl_stmt|,
name|rect_h
decl_stmt|;
name|GimpRGB
name|color
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
name|allocation
operator|.
name|x
expr_stmt|;
name|y
operator|=
name|allocation
operator|.
name|y
expr_stmt|;
name|width
operator|=
name|allocation
operator|.
name|width
expr_stmt|;
name|height
operator|=
name|allocation
operator|.
name|height
expr_stmt|;
name|rect_w
operator|=
name|width
operator|*
literal|3
operator|/
literal|4
expr_stmt|;
name|rect_h
operator|=
name|height
operator|*
literal|3
operator|/
literal|4
expr_stmt|;
comment|/*  draw the background area  */
if|if
condition|(
name|view
operator|->
name|context
condition|)
block|{
name|gimp_context_get_background
argument_list|(
name|view
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_fg_bg_view_draw_rect
argument_list|(
name|view
argument_list|,
name|window
argument_list|,
name|style
operator|->
name|fg_gc
index|[
literal|0
index|]
argument_list|,
name|x
operator|+
name|width
operator|-
name|rect_w
operator|+
literal|1
argument_list|,
name|y
operator|+
name|height
operator|-
name|rect_h
operator|+
literal|1
argument_list|,
name|rect_w
operator|-
literal|2
argument_list|,
name|rect_h
operator|-
literal|2
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
name|gtk_paint_shadow
argument_list|(
name|style
argument_list|,
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_IN
argument_list|,
name|NULL
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
name|x
operator|+
name|width
operator|-
name|rect_w
argument_list|,
name|y
operator|+
name|height
operator|-
name|rect_h
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
comment|/*  draw the foreground area  */
if|if
condition|(
name|view
operator|->
name|context
condition|)
block|{
name|gimp_context_get_foreground
argument_list|(
name|view
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_fg_bg_view_draw_rect
argument_list|(
name|view
argument_list|,
name|window
argument_list|,
name|style
operator|->
name|fg_gc
index|[
literal|0
index|]
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|rect_w
operator|-
literal|2
argument_list|,
name|rect_h
operator|-
literal|2
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
name|gtk_paint_shadow
argument_list|(
name|style
argument_list|,
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_OUT
argument_list|,
name|NULL
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_fg_bg_view_new (GimpContext * context)
name|gimp_fg_bg_view_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_FG_BG_VIEW
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fg_bg_view_set_context (GimpFgBgView * view,GimpContext * context)
name|gimp_fg_bg_view_set_context
parameter_list|(
name|GimpFgBgView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FG_BG_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
operator|==
name|view
operator|->
name|context
condition|)
return|return;
if|if
condition|(
name|view
operator|->
name|context
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|view
operator|->
name|context
argument_list|,
name|gtk_widget_queue_draw
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
name|view
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
name|view
operator|->
name|context
operator|=
name|context
expr_stmt|;
if|if
condition|(
name|context
condition|)
block|{
name|g_object_ref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|context
argument_list|,
literal|"foreground-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_queue_draw
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|context
argument_list|,
literal|"background-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_queue_draw
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"context"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

