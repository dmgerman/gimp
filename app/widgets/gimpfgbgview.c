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
file|<gegl.h>
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
DECL|enum|__anon29783d060103
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
name|gimp_fg_bg_view_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

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

begin_function_decl
specifier|static
name|void
name|gimp_fg_bg_view_config_notify
parameter_list|(
name|GimpColorConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpFgBgView
modifier|*
name|view
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
name|dispose
operator|=
name|gimp_fg_bg_view_dispose
expr_stmt|;
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
DECL|function|gimp_fg_bg_view_dispose (GObject * object)
name|gimp_fg_bg_view_dispose
parameter_list|(
name|GObject
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
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
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
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|GtkAllocation
name|allocation
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
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|eevent
operator|->
name|window
argument_list|)
expr_stmt|;
name|gdk_cairo_region
argument_list|(
name|cr
argument_list|,
name|eevent
operator|->
name|region
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|allocation
operator|.
name|x
argument_list|,
name|allocation
operator|.
name|y
argument_list|)
expr_stmt|;
name|rect_w
operator|=
name|allocation
operator|.
name|width
operator|*
literal|3
operator|/
literal|4
expr_stmt|;
name|rect_h
operator|=
name|allocation
operator|.
name|height
operator|*
literal|3
operator|/
literal|4
expr_stmt|;
if|if
condition|(
operator|!
name|view
operator|->
name|transform
condition|)
block|{
specifier|static
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|profile
argument_list|)
condition|)
name|profile
operator|=
name|gimp_color_profile_new_rgb_srgb
argument_list|()
expr_stmt|;
name|view
operator|->
name|transform
operator|=
name|gimp_widget_get_color_transform
argument_list|(
name|widget
argument_list|,
name|view
operator|->
name|color_config
argument_list|,
name|profile
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|view
operator|->
name|transform
condition|)
name|gimp_color_transform_process_pixels
argument_list|(
name|view
operator|->
name|transform
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|allocation
operator|.
name|width
operator|-
name|rect_w
operator|+
literal|1
argument_list|,
name|allocation
operator|.
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
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
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
name|allocation
operator|.
name|x
operator|+
name|allocation
operator|.
name|width
operator|-
name|rect_w
argument_list|,
name|allocation
operator|.
name|y
operator|+
name|allocation
operator|.
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
if|if
condition|(
name|view
operator|->
name|transform
condition|)
name|gimp_color_transform_process_pixels
argument_list|(
name|view
operator|->
name|transform
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
name|rect_w
operator|-
literal|2
argument_list|,
name|rect_h
operator|-
literal|2
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
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
name|allocation
operator|.
name|x
argument_list|,
name|allocation
operator|.
name|y
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fg_bg_view_config_notify (GimpColorConfig * config,const GParamSpec * pspec,GimpFgBgView * view)
name|gimp_fg_bg_view_config_notify
parameter_list|(
name|GimpColorConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpFgBgView
modifier|*
name|view
parameter_list|)
block|{
if|if
condition|(
name|view
operator|->
name|transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|view
operator|->
name|transform
argument_list|)
expr_stmt|;
name|view
operator|->
name|transform
operator|=
name|NULL
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
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|view
operator|->
name|color_config
argument_list|,
name|gimp_fg_bg_view_config_notify
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|view
operator|->
name|color_config
argument_list|)
expr_stmt|;
name|view
operator|->
name|color_config
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
name|view
operator|->
name|color_config
operator|=
name|g_object_ref
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|config
operator|->
name|color_management
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
operator|->
name|color_config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_fg_bg_view_config_notify
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
name|gimp_fg_bg_view_config_notify
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|view
argument_list|)
expr_stmt|;
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

