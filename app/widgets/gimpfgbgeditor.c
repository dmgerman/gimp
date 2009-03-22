begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfgbgeditor.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpfgbgeditor.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b98d91a0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_ACTIVE_COLOR
name|PROP_ACTIVE_COLOR
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b98d91a0203
block|{
DECL|enumerator|COLOR_CLICKED
name|COLOR_CLICKED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b98d91a0303
block|{
DECL|enumerator|INVALID_AREA
name|INVALID_AREA
block|,
DECL|enumerator|FOREGROUND_AREA
name|FOREGROUND_AREA
block|,
DECL|enumerator|BACKGROUND_AREA
name|BACKGROUND_AREA
block|,
DECL|enumerator|SWAP_AREA
name|SWAP_AREA
block|,
DECL|enumerator|DEFAULT_AREA
name|DEFAULT_AREA
DECL|typedef|FgBgTarget
block|}
name|FgBgTarget
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_fg_bg_editor_set_property
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
name|gimp_fg_bg_editor_get_property
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
name|gimp_fg_bg_editor_destroy
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
name|gimp_fg_bg_editor_expose
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
name|gboolean
name|gimp_fg_bg_editor_button_press
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
name|gimp_fg_bg_editor_button_release
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
name|gimp_fg_bg_editor_drag_motion
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
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_fg_bg_editor_drag_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_fg_bg_editor_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFgBgEditor
argument_list|,
argument|gimp_fg_bg_editor
argument_list|,
argument|GTK_TYPE_DRAWING_AREA
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_fg_bg_editor_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|editor_signals
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
DECL|function|gimp_fg_bg_editor_class_init (GimpFgBgEditorClass * klass)
name|gimp_fg_bg_editor_class_init
parameter_list|(
name|GimpFgBgEditorClass
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
name|editor_signals
index|[
name|COLOR_CLICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color-clicked"
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
name|GimpFgBgEditorClass
argument_list|,
name|color_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_ACTIVE_COLOR
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_fg_bg_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_fg_bg_editor_get_property
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_fg_bg_editor_destroy
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_fg_bg_editor_expose
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_fg_bg_editor_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_fg_bg_editor_button_release
expr_stmt|;
name|widget_class
operator|->
name|drag_motion
operator|=
name|gimp_fg_bg_editor_drag_motion
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
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ACTIVE_COLOR
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"active-color"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_ACTIVE_COLOR
argument_list|,
name|GIMP_ACTIVE_COLOR_FOREGROUND
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
DECL|function|gimp_fg_bg_editor_init (GimpFgBgEditor * editor)
name|gimp_fg_bg_editor_init
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|active_color
operator|=
name|GIMP_ACTIVE_COLOR_FOREGROUND
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|)
expr_stmt|;
name|gimp_dnd_color_source_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimp_fg_bg_editor_drag_color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimp_fg_bg_editor_drop_color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fg_bg_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_fg_bg_editor_set_property
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
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
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
name|gimp_fg_bg_editor_set_context
argument_list|(
name|editor
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE_COLOR
case|:
name|gimp_fg_bg_editor_set_active
argument_list|(
name|editor
argument_list|,
name|g_value_get_enum
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
DECL|function|gimp_fg_bg_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_fg_bg_editor_get_property
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
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
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
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ACTIVE_COLOR
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|active_color
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
DECL|function|gimp_fg_bg_editor_destroy (GtkObject * object)
name|gimp_fg_bg_editor_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
name|gimp_fg_bg_editor_set_context
argument_list|(
name|editor
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|render_buf
condition|)
block|{
name|g_free
argument_list|(
name|editor
operator|->
name|render_buf
argument_list|)
expr_stmt|;
name|editor
operator|->
name|render_buf
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|render_buf_size
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|editor
operator|->
name|default_icon
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|default_icon
argument_list|)
expr_stmt|;
name|editor
operator|->
name|default_icon
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|editor
operator|->
name|swap_icon
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|swap_icon
argument_list|)
expr_stmt|;
name|editor
operator|->
name|swap_icon
operator|=
name|NULL
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
DECL|function|gimp_fg_bg_editor_draw_rect (GimpFgBgEditor * editor,GdkDrawable * drawable,GdkGC * gc,gint x,gint y,gint width,gint height,const GimpRGB * color)
name|gimp_fg_bg_editor_draw_rect
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
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
name|editor
operator|->
name|render_buf
operator|||
name|editor
operator|->
name|render_buf_size
operator|<
name|height
operator|*
name|rowstride
condition|)
block|{
name|editor
operator|->
name|render_buf_size
operator|=
name|rowstride
operator|*
name|height
expr_stmt|;
name|g_free
argument_list|(
name|editor
operator|->
name|render_buf
argument_list|)
expr_stmt|;
name|editor
operator|->
name|render_buf
operator|=
name|g_malloc
argument_list|(
name|editor
operator|->
name|render_buf_size
argument_list|)
expr_stmt|;
block|}
name|bp
operator|=
name|editor
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
name|editor
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
name|editor
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
name|editor
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
DECL|function|gimp_fg_bg_editor_expose (GtkWidget * widget,GdkEventExpose * eevent)
name|gimp_fg_bg_editor_expose
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
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
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
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|default_w
decl_stmt|,
name|default_h
decl_stmt|;
name|gint
name|swap_w
decl_stmt|,
name|swap_h
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
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
condition|)
return|return
name|FALSE
return|;
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
expr_stmt|;
comment|/*  draw the default colors pixbuf  */
if|if
condition|(
operator|!
name|editor
operator|->
name|default_icon
condition|)
name|editor
operator|->
name|default_icon
operator|=
name|gtk_widget_render_icon
argument_list|(
name|widget
argument_list|,
name|GIMP_STOCK_DEFAULT_COLORS
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|default_w
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|editor
operator|->
name|default_icon
argument_list|)
expr_stmt|;
name|default_h
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|editor
operator|->
name|default_icon
argument_list|)
expr_stmt|;
if|if
condition|(
name|default_w
operator|<
name|width
operator|/
literal|2
operator|&&
name|default_h
operator|<
name|height
operator|/
literal|2
condition|)
name|gdk_draw_pixbuf
argument_list|(
name|window
argument_list|,
name|NULL
argument_list|,
name|editor
operator|->
name|default_icon
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|height
operator|-
name|default_h
argument_list|,
name|default_w
argument_list|,
name|default_h
argument_list|,
name|GDK_RGB_DITHER_NORMAL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|default_w
operator|=
name|default_h
operator|=
literal|0
expr_stmt|;
comment|/*  draw the swap colors pixbuf  */
if|if
condition|(
operator|!
name|editor
operator|->
name|swap_icon
condition|)
name|editor
operator|->
name|swap_icon
operator|=
name|gtk_widget_render_icon
argument_list|(
name|widget
argument_list|,
name|GIMP_STOCK_SWAP_COLORS
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|swap_w
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|editor
operator|->
name|swap_icon
argument_list|)
expr_stmt|;
name|swap_h
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|editor
operator|->
name|swap_icon
argument_list|)
expr_stmt|;
if|if
condition|(
name|swap_w
operator|<
name|width
operator|/
literal|2
operator|&&
name|swap_h
operator|<
name|height
operator|/
literal|2
condition|)
name|gdk_draw_pixbuf
argument_list|(
name|window
argument_list|,
name|NULL
argument_list|,
name|editor
operator|->
name|swap_icon
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
operator|-
name|swap_w
argument_list|,
literal|0
argument_list|,
name|swap_w
argument_list|,
name|swap_h
argument_list|,
name|GDK_RGB_DITHER_NORMAL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|swap_w
operator|=
name|swap_h
operator|=
literal|0
expr_stmt|;
name|rect_h
operator|=
name|height
operator|-
name|MAX
argument_list|(
name|default_h
argument_list|,
name|swap_h
argument_list|)
operator|-
literal|2
expr_stmt|;
name|rect_w
operator|=
name|width
operator|-
name|MAX
argument_list|(
name|default_w
argument_list|,
name|swap_w
argument_list|)
operator|-
literal|4
expr_stmt|;
if|if
condition|(
name|rect_h
operator|>
operator|(
name|height
operator|*
literal|3
operator|/
literal|4
operator|)
condition|)
name|rect_w
operator|=
name|MAX
argument_list|(
name|rect_w
operator|-
operator|(
name|rect_h
operator|-
operator|(
operator|(
name|height
operator|*
literal|3
operator|/
literal|4
operator|)
operator|)
operator|)
argument_list|,
name|width
operator|*
literal|2
operator|/
literal|3
argument_list|)
expr_stmt|;
name|editor
operator|->
name|rect_width
operator|=
name|rect_w
expr_stmt|;
name|editor
operator|->
name|rect_height
operator|=
name|rect_h
expr_stmt|;
comment|/*  draw the background area  */
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
name|gimp_context_get_background
argument_list|(
name|editor
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_fg_bg_editor_draw_rect
argument_list|(
name|editor
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
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
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
name|editor
operator|->
name|active_color
operator|==
name|GIMP_ACTIVE_COLOR_FOREGROUND
condition|?
name|GTK_SHADOW_OUT
else|:
name|GTK_SHADOW_IN
argument_list|,
name|NULL
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
comment|/*  draw the foreground area  */
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
name|gimp_context_get_foreground
argument_list|(
name|editor
operator|->
name|context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_fg_bg_editor_draw_rect
argument_list|(
name|editor
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
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
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
name|editor
operator|->
name|active_color
operator|==
name|GIMP_ACTIVE_COLOR_BACKGROUND
condition|?
name|GTK_SHADOW_OUT
else|:
name|GTK_SHADOW_IN
argument_list|,
name|NULL
argument_list|,
name|widget
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
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

begin_function
specifier|static
name|FgBgTarget
DECL|function|gimp_fg_bg_editor_target (GimpFgBgEditor * editor,gint x,gint y)
name|gimp_fg_bg_editor_target
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|width
init|=
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
operator|->
name|allocation
operator|.
name|width
decl_stmt|;
name|gint
name|height
init|=
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
operator|->
name|allocation
operator|.
name|height
decl_stmt|;
name|gint
name|rect_w
init|=
name|editor
operator|->
name|rect_width
decl_stmt|;
name|gint
name|rect_h
init|=
name|editor
operator|->
name|rect_height
decl_stmt|;
if|if
condition|(
name|x
operator|>
literal|0
operator|&&
name|x
operator|<
name|rect_w
operator|&&
name|y
operator|>
literal|0
operator|&&
name|y
operator|<
name|rect_h
condition|)
return|return
name|FOREGROUND_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
operator|(
name|width
operator|-
name|rect_w
operator|)
operator|&&
name|x
operator|<
name|width
operator|&&
name|y
operator|>
operator|(
name|height
operator|-
name|rect_h
operator|)
operator|&&
name|y
operator|<
name|height
condition|)
return|return
name|BACKGROUND_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
literal|0
operator|&&
name|x
operator|<
operator|(
name|width
operator|-
name|rect_w
operator|)
operator|&&
name|y
operator|>
name|rect_h
operator|&&
name|y
operator|<
name|height
condition|)
return|return
name|DEFAULT_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
name|rect_w
operator|&&
name|x
operator|<
name|width
operator|&&
name|y
operator|>
literal|0
operator|&&
name|y
operator|<
operator|(
name|height
operator|-
name|rect_h
operator|)
condition|)
return|return
name|SWAP_AREA
return|;
return|return
name|INVALID_AREA
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_fg_bg_editor_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_fg_bg_editor_button_press
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
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
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
operator|&&
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
block|{
name|FgBgTarget
name|target
init|=
name|gimp_fg_bg_editor_target
argument_list|(
name|editor
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
decl_stmt|;
name|editor
operator|->
name|click_target
operator|=
name|INVALID_AREA
expr_stmt|;
switch|switch
condition|(
name|target
condition|)
block|{
case|case
name|FOREGROUND_AREA
case|:
if|if
condition|(
name|editor
operator|->
name|active_color
operator|!=
name|GIMP_ACTIVE_COLOR_FOREGROUND
condition|)
name|gimp_fg_bg_editor_set_active
argument_list|(
name|editor
argument_list|,
name|GIMP_ACTIVE_COLOR_FOREGROUND
argument_list|)
expr_stmt|;
name|editor
operator|->
name|click_target
operator|=
name|FOREGROUND_AREA
expr_stmt|;
break|break;
case|case
name|BACKGROUND_AREA
case|:
if|if
condition|(
name|editor
operator|->
name|active_color
operator|!=
name|GIMP_ACTIVE_COLOR_BACKGROUND
condition|)
name|gimp_fg_bg_editor_set_active
argument_list|(
name|editor
argument_list|,
name|GIMP_ACTIVE_COLOR_BACKGROUND
argument_list|)
expr_stmt|;
name|editor
operator|->
name|click_target
operator|=
name|BACKGROUND_AREA
expr_stmt|;
break|break;
case|case
name|SWAP_AREA
case|:
if|if
condition|(
name|editor
operator|->
name|context
condition|)
name|gimp_context_swap_colors
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|DEFAULT_AREA
case|:
if|if
condition|(
name|editor
operator|->
name|context
condition|)
name|gimp_context_set_default_colors
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
default|default:
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
DECL|function|gimp_fg_bg_editor_button_release (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_fg_bg_editor_button_release
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
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
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
name|FgBgTarget
name|target
init|=
name|gimp_fg_bg_editor_target
argument_list|(
name|editor
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
decl_stmt|;
if|if
condition|(
name|target
operator|==
name|editor
operator|->
name|click_target
condition|)
block|{
switch|switch
condition|(
name|target
condition|)
block|{
case|case
name|FOREGROUND_AREA
case|:
name|g_signal_emit
argument_list|(
name|editor
argument_list|,
name|editor_signals
index|[
name|COLOR_CLICKED
index|]
argument_list|,
literal|0
argument_list|,
name|GIMP_ACTIVE_COLOR_FOREGROUND
argument_list|)
expr_stmt|;
break|break;
case|case
name|BACKGROUND_AREA
case|:
name|g_signal_emit
argument_list|(
name|editor
argument_list|,
name|editor_signals
index|[
name|COLOR_CLICKED
index|]
argument_list|,
literal|0
argument_list|,
name|GIMP_ACTIVE_COLOR_BACKGROUND
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
name|editor
operator|->
name|click_target
operator|=
name|INVALID_AREA
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
DECL|function|gimp_fg_bg_editor_drag_motion (GtkWidget * widget,GdkDragContext * context,gint x,gint y,guint time)
name|gimp_fg_bg_editor_drag_motion
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
name|guint
name|time
parameter_list|)
block|{
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|FgBgTarget
name|target
init|=
name|gimp_fg_bg_editor_target
argument_list|(
name|editor
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
decl_stmt|;
if|if
condition|(
name|target
operator|==
name|FOREGROUND_AREA
operator|||
name|target
operator|==
name|BACKGROUND_AREA
condition|)
block|{
name|gdk_drag_status
argument_list|(
name|context
argument_list|,
name|GDK_ACTION_COPY
argument_list|,
name|time
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|gdk_drag_status
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
name|time
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_fg_bg_editor_new (GimpContext * context)
name|gimp_fg_bg_editor_new
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
name|GIMP_TYPE_FG_BG_EDITOR
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
DECL|function|gimp_fg_bg_editor_set_context (GimpFgBgEditor * editor,GimpContext * context)
name|gimp_fg_bg_editor_set_context
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FG_BG_EDITOR
argument_list|(
name|editor
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
name|editor
operator|->
name|context
condition|)
return|return;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|gtk_widget_queue_draw
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|editor
operator|->
name|context
argument_list|)
expr_stmt|;
name|editor
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
name|editor
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
name|editor
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
name|editor
argument_list|)
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"context"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fg_bg_editor_set_active (GimpFgBgEditor * editor,GimpActiveColor active)
name|gimp_fg_bg_editor_set_active
parameter_list|(
name|GimpFgBgEditor
modifier|*
name|editor
parameter_list|,
name|GimpActiveColor
name|active
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FG_BG_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|editor
operator|->
name|active_color
operator|=
name|active
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"active-color"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_fg_bg_editor_drag_color (GtkWidget * widget,GimpRGB * color,gpointer data)
name|gimp_fg_bg_editor_drag_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
switch|switch
condition|(
name|editor
operator|->
name|active_color
condition|)
block|{
case|case
name|GIMP_ACTIVE_COLOR_FOREGROUND
case|:
name|gimp_context_get_foreground
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ACTIVE_COLOR_BACKGROUND
case|:
name|gimp_context_get_background
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fg_bg_editor_drop_color (GtkWidget * widget,gint x,gint y,const GimpRGB * color,gpointer data)
name|gimp_fg_bg_editor_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpFgBgEditor
modifier|*
name|editor
init|=
name|GIMP_FG_BG_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|context
condition|)
block|{
switch|switch
condition|(
name|gimp_fg_bg_editor_target
argument_list|(
name|editor
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
condition|)
block|{
case|case
name|FOREGROUND_AREA
case|:
name|gimp_context_set_foreground
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|BACKGROUND_AREA
case|:
name|gimp_context_set_background
argument_list|(
name|editor
operator|->
name|context
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

end_unit

