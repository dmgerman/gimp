begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpink-blob.h"
end_include

begin_include
include|#
directive|include
file|"gimpblobeditor.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon298955bb0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TYPE
name|PROP_TYPE
block|,
DECL|enumerator|PROP_ASPECT
name|PROP_ASPECT
block|,
DECL|enumerator|PROP_ANGLE
name|PROP_ANGLE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_blob_editor_set_property
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
name|gimp_blob_editor_get_property
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
name|gimp_blob_editor_expose
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
name|gimp_blob_editor_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_blob_editor_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_blob_editor_motion_notify
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
name|gimp_blob_editor_get_handle
parameter_list|(
name|GimpBlobEditor
modifier|*
name|editor
parameter_list|,
name|GdkRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_blob_editor_draw_blob
parameter_list|(
name|GimpBlobEditor
modifier|*
name|editor
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|xc
parameter_list|,
name|gdouble
name|yc
parameter_list|,
name|gdouble
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBlobEditor,gimp_blob_editor,GTK_TYPE_DRAWING_AREA)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBlobEditor
argument_list|,
argument|gimp_blob_editor
argument_list|,
argument|GTK_TYPE_DRAWING_AREA
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_blob_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_blob_editor_class_init
parameter_list|(
name|GimpBlobEditorClass
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
name|set_property
operator|=
name|gimp_blob_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_blob_editor_get_property
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_blob_editor_expose
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_blob_editor_button_press
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_blob_editor_button_release
expr_stmt|;
name|widget_class
operator|->
name|motion_notify_event
operator|=
name|gimp_blob_editor_motion_notify
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TYPE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"blob-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_INK_BLOB_TYPE
argument_list|,
name|GIMP_INK_BLOB_TYPE_CIRCLE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ASPECT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"blob-aspect"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1.0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ANGLE
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"blob-angle"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|90.0
argument_list|,
literal|90.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_READWRITE
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
DECL|function|gimp_blob_editor_init (GimpBlobEditor * editor)
name|gimp_blob_editor_init
parameter_list|(
name|GimpBlobEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|active
operator|=
name|FALSE
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
operator||
name|GDK_POINTER_MOTION_MASK
operator||
name|GDK_EXPOSURE_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_blob_editor_new (GimpInkBlobType type,gdouble aspect,gdouble angle)
name|gimp_blob_editor_new
parameter_list|(
name|GimpInkBlobType
name|type
parameter_list|,
name|gdouble
name|aspect
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_BLOB_EDITOR
argument_list|,
literal|"blob-type"
argument_list|,
name|type
argument_list|,
literal|"blob-aspect"
argument_list|,
name|aspect
argument_list|,
literal|"blob-angle"
argument_list|,
name|angle
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blob_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_blob_editor_set_property
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
name|GimpBlobEditor
modifier|*
name|editor
init|=
name|GIMP_BLOB_EDITOR
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
name|PROP_TYPE
case|:
name|editor
operator|->
name|type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ASPECT
case|:
name|editor
operator|->
name|aspect
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANGLE
case|:
name|editor
operator|->
name|angle
operator|=
name|g_value_get_double
argument_list|(
name|value
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
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blob_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_blob_editor_get_property
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
name|GimpBlobEditor
modifier|*
name|editor
init|=
name|GIMP_BLOB_EDITOR
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
name|PROP_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ASPECT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|aspect
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANGLE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|angle
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
DECL|function|gimp_blob_editor_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_blob_editor_expose
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
name|GimpBlobEditor
modifier|*
name|editor
init|=
name|GIMP_BLOB_EDITOR
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
name|GtkStateType
name|state
init|=
name|gtk_widget_get_state
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|;
name|gint
name|r0
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|r0
operator|=
name|MIN
argument_list|(
name|allocation
operator|.
name|width
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|r0
operator|<
literal|2
condition|)
return|return
name|TRUE
return|;
name|cr
operator|=
name|gdk_cairo_create
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_blob_editor_draw_blob
argument_list|(
name|editor
argument_list|,
name|cr
argument_list|,
name|allocation
operator|.
name|width
operator|/
literal|2.0
argument_list|,
name|allocation
operator|.
name|height
operator|/
literal|2.0
argument_list|,
literal|0.9
operator|*
name|r0
argument_list|)
expr_stmt|;
name|gimp_blob_editor_get_handle
argument_list|(
name|editor
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|rect
operator|.
name|x
operator|+
literal|0.5
argument_list|,
name|rect
operator|.
name|y
operator|+
literal|0.5
argument_list|,
name|rect
operator|.
name|width
operator|-
literal|1
argument_list|,
name|rect
operator|.
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|light
index|[
name|state
index|]
argument_list|)
expr_stmt|;
name|cairo_fill_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|dark
index|[
name|state
index|]
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cairo_stroke
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
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_blob_editor_button_press (GtkWidget * widget,GdkEventButton * event)
name|gimp_blob_editor_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
block|{
name|GimpBlobEditor
modifier|*
name|editor
init|=
name|GIMP_BLOB_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|;
name|gimp_blob_editor_get_handle
argument_list|(
name|editor
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|event
operator|->
name|x
operator|>=
name|rect
operator|.
name|x
operator|)
operator|&&
operator|(
name|event
operator|->
name|x
operator|-
name|rect
operator|.
name|x
operator|<
name|rect
operator|.
name|width
operator|)
operator|&&
operator|(
name|event
operator|->
name|y
operator|>=
name|rect
operator|.
name|y
operator|)
operator|&&
operator|(
name|event
operator|->
name|y
operator|-
name|rect
operator|.
name|y
operator|<
name|rect
operator|.
name|height
operator|)
condition|)
block|{
name|editor
operator|->
name|active
operator|=
name|TRUE
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
DECL|function|gimp_blob_editor_button_release (GtkWidget * widget,GdkEventButton * event)
name|gimp_blob_editor_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
block|{
name|GimpBlobEditor
modifier|*
name|editor
init|=
name|GIMP_BLOB_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|editor
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_blob_editor_motion_notify (GtkWidget * widget,GdkEventMotion * event)
name|gimp_blob_editor_motion_notify
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
name|GimpBlobEditor
modifier|*
name|editor
init|=
name|GIMP_BLOB_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|active
condition|)
block|{
name|GtkAllocation
name|allocation
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|rsquare
decl_stmt|;
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
name|event
operator|->
name|x
operator|-
name|allocation
operator|.
name|width
operator|/
literal|2
expr_stmt|;
name|y
operator|=
name|event
operator|->
name|y
operator|-
name|allocation
operator|.
name|height
operator|/
literal|2
expr_stmt|;
name|rsquare
operator|=
name|SQR
argument_list|(
name|x
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|rsquare
operator|>
literal|0
condition|)
block|{
name|gint
name|r0
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gdouble
name|aspect
decl_stmt|;
name|r0
operator|=
name|MIN
argument_list|(
name|allocation
operator|.
name|width
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
operator|/
literal|2
expr_stmt|;
name|angle
operator|=
name|atan2
argument_list|(
name|y
argument_list|,
name|x
argument_list|)
expr_stmt|;
name|aspect
operator|=
literal|10.0
operator|*
name|sqrt
argument_list|(
operator|(
name|gdouble
operator|)
name|rsquare
operator|/
operator|(
name|r0
operator|*
name|r0
operator|)
argument_list|)
operator|/
literal|0.85
expr_stmt|;
name|aspect
operator|=
name|CLAMP
argument_list|(
name|aspect
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|editor
argument_list|,
literal|"blob-angle"
argument_list|,
name|angle
argument_list|,
literal|"blob-aspect"
argument_list|,
name|aspect
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blob_editor_get_handle (GimpBlobEditor * editor,GdkRectangle * rect)
name|gimp_blob_editor_get_handle
parameter_list|(
name|GimpBlobEditor
modifier|*
name|editor
parameter_list|,
name|GdkRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|editor
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
name|r
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|r
operator|=
name|MIN
argument_list|(
name|allocation
operator|.
name|width
argument_list|,
name|allocation
operator|.
name|height
argument_list|)
operator|/
literal|2
expr_stmt|;
name|x
operator|=
operator|(
name|allocation
operator|.
name|width
operator|/
literal|2
operator|+
literal|0.85
operator|*
name|r
operator|*
name|editor
operator|->
name|aspect
operator|/
literal|10.0
operator|*
name|cos
argument_list|(
name|editor
operator|->
name|angle
argument_list|)
operator|)
expr_stmt|;
name|y
operator|=
operator|(
name|allocation
operator|.
name|height
operator|/
literal|2
operator|+
literal|0.85
operator|*
name|r
operator|*
name|editor
operator|->
name|aspect
operator|/
literal|10.0
operator|*
name|sin
argument_list|(
name|editor
operator|->
name|angle
argument_list|)
operator|)
expr_stmt|;
name|rect
operator|->
name|x
operator|=
name|x
operator|-
literal|5
expr_stmt|;
name|rect
operator|->
name|y
operator|=
name|y
operator|-
literal|5
expr_stmt|;
name|rect
operator|->
name|width
operator|=
literal|10
expr_stmt|;
name|rect
operator|->
name|height
operator|=
literal|10
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blob_editor_draw_blob (GimpBlobEditor * editor,cairo_t * cr,gdouble xc,gdouble yc,gdouble radius)
name|gimp_blob_editor_draw_blob
parameter_list|(
name|GimpBlobEditor
modifier|*
name|editor
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gdouble
name|xc
parameter_list|,
name|gdouble
name|yc
parameter_list|,
name|gdouble
name|radius
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|editor
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
name|Blob
modifier|*
name|blob
decl_stmt|;
name|BlobFunc
name|function
init|=
name|blob_ellipse
decl_stmt|;
name|gint
name|i
decl_stmt|;
switch|switch
condition|(
name|editor
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_INK_BLOB_TYPE_CIRCLE
case|:
name|function
operator|=
name|blob_ellipse
expr_stmt|;
break|break;
case|case
name|GIMP_INK_BLOB_TYPE_SQUARE
case|:
name|function
operator|=
name|blob_square
expr_stmt|;
break|break;
case|case
name|GIMP_INK_BLOB_TYPE_DIAMOND
case|:
name|function
operator|=
name|blob_diamond
expr_stmt|;
break|break;
block|}
comment|/*  to get a nice antialiased outline, render the blob at double size  */
name|radius
operator|*=
literal|2.0
expr_stmt|;
name|blob
operator|=
name|function
argument_list|(
literal|2.0
operator|*
name|xc
argument_list|,
literal|2.0
operator|*
name|yc
argument_list|,
name|radius
operator|*
name|cos
argument_list|(
name|editor
operator|->
name|angle
argument_list|)
argument_list|,
name|radius
operator|*
name|sin
argument_list|(
name|editor
operator|->
name|angle
argument_list|)
argument_list|,
operator|(
operator|-
operator|(
name|radius
operator|/
name|editor
operator|->
name|aspect
operator|)
operator|*
name|sin
argument_list|(
name|editor
operator|->
name|angle
argument_list|)
operator|)
argument_list|,
operator|(
operator|(
name|radius
operator|/
name|editor
operator|->
name|aspect
operator|)
operator|*
name|cos
argument_list|(
name|editor
operator|->
name|angle
argument_list|)
operator|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|blob
operator|->
name|height
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|left
operator|<=
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|right
condition|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|left
operator|/
literal|2.0
argument_list|,
operator|(
name|blob
operator|->
name|y
operator|+
name|i
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
break|break;
block|}
for|for
control|(
name|i
operator|=
name|i
operator|+
literal|1
init|;
name|i
operator|<
name|blob
operator|->
name|height
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|left
operator|>
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|right
condition|)
break|break;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|left
operator|/
literal|2.0
argument_list|,
operator|(
name|blob
operator|->
name|y
operator|+
name|i
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
name|i
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
if|if
condition|(
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|left
operator|>
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|right
condition|)
break|break;
name|cairo_line_to
argument_list|(
name|cr
argument_list|,
name|blob
operator|->
name|data
index|[
name|i
index|]
operator|.
name|right
operator|/
literal|2.0
argument_list|,
operator|(
name|blob
operator|->
name|y
operator|+
name|i
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
block|}
name|cairo_close_path
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|blob
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_color
argument_list|(
name|cr
argument_list|,
operator|&
name|style
operator|->
name|fg
index|[
name|gtk_widget_get_state
argument_list|(
name|widget
argument_list|)
index|]
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

