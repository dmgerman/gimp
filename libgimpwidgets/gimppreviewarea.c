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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewarea.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ad631110103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CHECK_SIZE
name|PROP_CHECK_SIZE
block|,
DECL|enumerator|PROP_CHECK_TYPE
name|PROP_CHECK_TYPE
block|}
enum|;
end_enum

begin_define
DECL|macro|DEFAULT_CHECK_SIZE
define|#
directive|define
name|DEFAULT_CHECK_SIZE
value|GIMP_CHECK_SIZE_MEDIUM_CHECKS
end_define

begin_define
DECL|macro|DEFAULT_CHECK_TYPE
define|#
directive|define
name|DEFAULT_CHECK_TYPE
value|GIMP_CHECK_TYPE_GRAY_CHECKS
end_define

begin_function_decl
specifier|static
name|void
name|gimp_preview_area_class_init
parameter_list|(
name|GimpPreviewAreaClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_area_init
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_area_finalize
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
name|gimp_preview_area_set_property
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
name|gimp_preview_area_get_property
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
name|gimp_preview_area_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_preview_area_expose
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
DECL|function|gimp_preview_area_get_type (void)
name|gimp_preview_area_get_type
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
name|GimpPreviewAreaClass
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
name|gimp_preview_area_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpPreviewArea
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_preview_area_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_DRAWING_AREA
argument_list|,
literal|"GimpPreviewArea"
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
DECL|function|gimp_preview_area_class_init (GimpPreviewAreaClass * klass)
name|gimp_preview_area_class_init
parameter_list|(
name|GimpPreviewAreaClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_preview_area_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_preview_area_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_preview_area_get_property
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_preview_area_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|expose_event
operator|=
name|gimp_preview_area_expose
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CHECK_SIZE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"check-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CHECK_SIZE
argument_list|,
name|DEFAULT_CHECK_SIZE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CHECK_TYPE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"check-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CHECK_TYPE
argument_list|,
name|DEFAULT_CHECK_TYPE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_area_init (GimpPreviewArea * area)
name|gimp_preview_area_init
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|)
block|{
name|area
operator|->
name|check_size
operator|=
name|DEFAULT_CHECK_SIZE
expr_stmt|;
name|area
operator|->
name|check_type
operator|=
name|DEFAULT_CHECK_TYPE
expr_stmt|;
name|area
operator|->
name|buf
operator|=
name|NULL
expr_stmt|;
name|area
operator|->
name|cmap
operator|=
name|NULL
expr_stmt|;
name|area
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|area
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
name|area
operator|->
name|width
operator|=
literal|0
expr_stmt|;
name|area
operator|->
name|height
operator|=
literal|0
expr_stmt|;
name|area
operator|->
name|rowstride
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_area_finalize (GObject * object)
name|gimp_preview_area_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPreviewArea
modifier|*
name|area
init|=
name|GIMP_PREVIEW_AREA
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|area
operator|->
name|buf
condition|)
block|{
name|g_free
argument_list|(
name|area
operator|->
name|buf
argument_list|)
expr_stmt|;
name|area
operator|->
name|buf
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|area
operator|->
name|cmap
condition|)
block|{
name|g_free
argument_list|(
name|area
operator|->
name|cmap
argument_list|)
expr_stmt|;
name|area
operator|->
name|cmap
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_area_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_preview_area_set_property
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
name|GimpPreviewArea
modifier|*
name|area
init|=
name|GIMP_PREVIEW_AREA
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
name|PROP_CHECK_SIZE
case|:
name|area
operator|->
name|check_size
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
name|area
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CHECK_TYPE
case|:
name|area
operator|->
name|check_type
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
name|area
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
DECL|function|gimp_preview_area_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_preview_area_get_property
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
name|GimpPreviewArea
modifier|*
name|area
init|=
name|GIMP_PREVIEW_AREA
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
name|PROP_CHECK_SIZE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|area
operator|->
name|check_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CHECK_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|area
operator|->
name|check_type
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
DECL|function|gimp_preview_area_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_preview_area_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GimpPreviewArea
modifier|*
name|area
init|=
name|GIMP_PREVIEW_AREA
argument_list|(
name|widget
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
operator|->
name|allocation
operator|.
name|width
operator|!=
name|area
operator|->
name|width
operator|||
name|widget
operator|->
name|allocation
operator|.
name|height
operator|!=
name|area
operator|->
name|height
condition|)
block|{
if|if
condition|(
name|area
operator|->
name|buf
condition|)
block|{
name|g_free
argument_list|(
name|area
operator|->
name|buf
argument_list|)
expr_stmt|;
name|area
operator|->
name|buf
operator|=
name|NULL
expr_stmt|;
name|area
operator|->
name|rowstride
operator|=
literal|0
expr_stmt|;
block|}
name|area
operator|->
name|width
operator|=
name|widget
operator|->
name|allocation
operator|.
name|width
expr_stmt|;
name|area
operator|->
name|height
operator|=
name|widget
operator|->
name|allocation
operator|.
name|height
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_preview_area_expose (GtkWidget * widget,GdkEventExpose * event)
name|gimp_preview_area_expose
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
name|GimpPreviewArea
modifier|*
name|area
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PREVIEW_AREA
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|area
operator|=
name|GIMP_PREVIEW_AREA
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|area
operator|->
name|buf
condition|)
return|return
name|FALSE
return|;
name|buf
operator|=
name|area
operator|->
name|buf
operator|+
name|event
operator|->
name|area
operator|.
name|x
operator|*
literal|3
operator|+
name|event
operator|->
name|area
operator|.
name|y
operator|*
name|area
operator|->
name|rowstride
expr_stmt|;
name|gdk_draw_rgb_image_dithalign
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|fg_gc
index|[
name|widget
operator|->
name|state
index|]
argument_list|,
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|event
operator|->
name|area
operator|.
name|y
argument_list|,
name|event
operator|->
name|area
operator|.
name|width
argument_list|,
name|event
operator|->
name|area
operator|.
name|height
argument_list|,
name|GDK_RGB_DITHER_MAX
argument_list|,
name|buf
argument_list|,
name|area
operator|->
name|rowstride
argument_list|,
name|area
operator|->
name|offset_x
operator|-
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|area
operator|->
name|offset_y
operator|-
name|event
operator|->
name|area
operator|.
name|y
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|guint
DECL|function|gimp_preview_area_get_check_size (GimpPreviewArea * area)
name|gimp_preview_area_get_check_size
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|)
block|{
return|return
operator|(
literal|1
operator|<<
operator|(
literal|2
operator|+
name|area
operator|->
name|check_size
operator|)
operator|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_preview_area_new:  *  * Return value: a new #GimpPreviewArea widget.  *  * Since GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_preview_area_new (void)
name|gimp_preview_area_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PREVIEW_AREA
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_preview_area_draw:  * @area:      a #GimpPreviewArea widget.  * @x:         x offset in preview  * @y:         y offset in preview  * @width:     buffer width  * @height:    buffer height  * @type:      the #GimpImageType of @buf  * @buf:       a #guchar buffer that contains the preview pixel data.  * @rowstride: rowstride of @buf  *  * Draws @buf on @area and queues a redraw on the rectangle that  * changed.  *  * Since GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_preview_area_draw (GimpPreviewArea * area,gint x,gint y,gint width,gint height,GimpImageType type,const guchar * buf,gint rowstride)
name|gimp_preview_area_draw
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
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
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|rowstride
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guint
name|size
decl_stmt|;
name|guchar
name|light
decl_stmt|;
name|guchar
name|dark
decl_stmt|;
name|gint
name|row
decl_stmt|;
name|gint
name|col
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PREVIEW_AREA
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
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
name|g_return_if_fail
argument_list|(
name|buf
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rowstride
operator|>
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|+
name|width
operator|<
literal|0
operator|||
name|x
operator|>=
name|area
operator|->
name|width
condition|)
return|return;
if|if
condition|(
name|y
operator|+
name|height
operator|<
literal|0
operator|||
name|y
operator|>=
name|area
operator|->
name|height
condition|)
return|return;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
block|{
name|gint
name|bpp
decl_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_GRAY_IMAGE
case|:
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|bpp
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|bpp
operator|=
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_RGB_IMAGE
case|:
name|bpp
operator|=
literal|3
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|bpp
operator|=
literal|4
expr_stmt|;
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
name|buf
operator|+=
name|x
operator|*
name|bpp
expr_stmt|;
name|width
operator|-=
name|x
expr_stmt|;
name|x
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|+
name|width
operator|>
name|area
operator|->
name|width
condition|)
name|width
operator|=
name|area
operator|->
name|width
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
condition|)
block|{
name|buf
operator|+=
name|y
operator|*
name|rowstride
expr_stmt|;
name|height
operator|-=
name|y
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|+
name|height
operator|>
name|area
operator|->
name|height
condition|)
name|height
operator|=
name|area
operator|->
name|height
operator|-
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|area
operator|->
name|buf
condition|)
block|{
name|area
operator|->
name|rowstride
operator|=
operator|(
operator|(
name|area
operator|->
name|width
operator|*
literal|3
operator|)
operator|+
literal|3
operator|)
operator|&
operator|~
literal|3
expr_stmt|;
name|area
operator|->
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|area
operator|->
name|rowstride
operator|*
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
name|size
operator|=
literal|1
operator|<<
operator|(
literal|2
operator|+
name|area
operator|->
name|check_size
operator|)
expr_stmt|;
name|gimp_checks_get_shades
argument_list|(
name|area
operator|->
name|check_type
argument_list|,
operator|&
name|light
argument_list|,
operator|&
name|dark
argument_list|)
expr_stmt|;
DECL|macro|CHECK_COLOR (area,row,col)
define|#
directive|define
name|CHECK_COLOR
parameter_list|(
name|area
parameter_list|,
name|row
parameter_list|,
name|col
parameter_list|)
define|\
value|(((((area)->offset_y + (row))& size) ^  \     (((area)->offset_x + (col))& size)) ? dark : light)
name|src
operator|=
name|buf
expr_stmt|;
name|dest
operator|=
name|area
operator|->
name|buf
operator|+
name|x
operator|*
literal|3
operator|+
name|y
operator|*
name|area
operator|->
name|rowstride
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|height
condition|;
name|row
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|src
argument_list|,
literal|3
operator|*
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|area
operator|->
name|rowstride
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
for|for
control|(
name|row
operator|=
name|y
init|;
name|row
operator|<
name|y
operator|+
name|height
condition|;
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|col
operator|=
name|x
init|;
name|col
operator|<
name|x
operator|+
name|width
condition|;
name|col
operator|++
operator|,
name|s
operator|+=
literal|4
operator|,
name|d
operator|+=
literal|3
control|)
block|{
switch|switch
condition|(
name|s
index|[
literal|3
index|]
condition|)
block|{
case|case
literal|0
case|:
name|d
index|[
literal|0
index|]
operator|=
name|d
index|[
literal|1
index|]
operator|=
name|d
index|[
literal|2
index|]
operator|=
name|CHECK_COLOR
argument_list|(
name|area
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
expr_stmt|;
break|break;
case|case
literal|255
case|:
name|d
index|[
literal|0
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
name|s
index|[
literal|1
index|]
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|s
index|[
literal|2
index|]
expr_stmt|;
break|break;
default|default:
block|{
specifier|register
name|guint
name|alpha
init|=
name|s
index|[
literal|3
index|]
operator|+
literal|1
decl_stmt|;
specifier|register
name|guint
name|check
init|=
name|CHECK_COLOR
argument_list|(
name|area
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
decl_stmt|;
name|d
index|[
literal|0
index|]
operator|=
operator|(
operator|(
name|check
operator|<<
literal|8
operator|)
operator|+
operator|(
name|s
index|[
literal|0
index|]
operator|-
name|check
operator|)
operator|*
name|alpha
operator|)
operator|>>
literal|8
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
operator|(
operator|(
name|check
operator|<<
literal|8
operator|)
operator|+
operator|(
name|s
index|[
literal|1
index|]
operator|-
name|check
operator|)
operator|*
name|alpha
operator|)
operator|>>
literal|8
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
operator|(
operator|(
name|check
operator|<<
literal|8
operator|)
operator|+
operator|(
name|s
index|[
literal|2
index|]
operator|-
name|check
operator|)
operator|*
name|alpha
operator|)
operator|>>
literal|8
expr_stmt|;
block|}
break|break;
block|}
block|}
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|area
operator|->
name|rowstride
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|height
condition|;
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|width
condition|;
name|col
operator|++
operator|,
name|s
operator|++
operator|,
name|d
operator|+=
literal|3
control|)
block|{
name|d
index|[
literal|0
index|]
operator|=
name|d
index|[
literal|1
index|]
operator|=
name|d
index|[
literal|2
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
block|}
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|area
operator|->
name|rowstride
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
for|for
control|(
name|row
operator|=
name|y
init|;
name|row
operator|<
name|y
operator|+
name|height
condition|;
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|col
operator|=
name|x
init|;
name|col
operator|<
name|x
operator|+
name|width
condition|;
name|col
operator|++
operator|,
name|s
operator|+=
literal|2
operator|,
name|d
operator|+=
literal|3
control|)
block|{
switch|switch
condition|(
name|s
index|[
literal|1
index|]
condition|)
block|{
case|case
literal|0
case|:
name|d
index|[
literal|0
index|]
operator|=
name|d
index|[
literal|1
index|]
operator|=
name|d
index|[
literal|2
index|]
operator|=
name|CHECK_COLOR
argument_list|(
name|area
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
expr_stmt|;
break|break;
case|case
literal|255
case|:
name|d
index|[
literal|0
index|]
operator|=
name|d
index|[
literal|1
index|]
operator|=
name|d
index|[
literal|2
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
break|break;
default|default:
block|{
specifier|register
name|guint
name|alpha
init|=
name|s
index|[
literal|1
index|]
operator|+
literal|1
decl_stmt|;
specifier|register
name|guint
name|check
init|=
name|CHECK_COLOR
argument_list|(
name|area
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
decl_stmt|;
name|d
index|[
literal|0
index|]
operator|=
name|d
index|[
literal|1
index|]
operator|=
name|d
index|[
literal|2
index|]
operator|=
operator|(
operator|(
name|check
operator|<<
literal|8
operator|)
operator|+
operator|(
name|s
index|[
literal|0
index|]
operator|-
name|check
operator|)
operator|*
name|alpha
operator|)
operator|>>
literal|8
expr_stmt|;
block|}
break|break;
block|}
block|}
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|area
operator|->
name|rowstride
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|g_return_if_fail
argument_list|(
name|area
operator|->
name|cmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|height
condition|;
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|width
condition|;
name|col
operator|++
operator|,
name|s
operator|++
operator|,
name|d
operator|+=
literal|3
control|)
block|{
specifier|const
name|guchar
modifier|*
name|cmap
init|=
name|area
operator|->
name|cmap
operator|+
literal|3
operator|*
name|s
index|[
literal|0
index|]
decl_stmt|;
name|d
index|[
literal|0
index|]
operator|=
name|cmap
index|[
literal|0
index|]
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
name|cmap
index|[
literal|1
index|]
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|cmap
index|[
literal|2
index|]
expr_stmt|;
block|}
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|area
operator|->
name|rowstride
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|g_return_if_fail
argument_list|(
name|area
operator|->
name|cmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|row
operator|=
name|y
init|;
name|row
operator|<
name|y
operator|+
name|height
condition|;
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|col
operator|=
name|x
init|;
name|col
operator|<
name|x
operator|+
name|width
condition|;
name|col
operator|++
operator|,
name|s
operator|+=
literal|2
operator|,
name|d
operator|+=
literal|3
control|)
block|{
specifier|const
name|guchar
modifier|*
name|cmap
init|=
name|area
operator|->
name|cmap
operator|+
literal|3
operator|*
name|s
index|[
literal|0
index|]
decl_stmt|;
switch|switch
condition|(
name|s
index|[
literal|1
index|]
condition|)
block|{
case|case
literal|0
case|:
name|d
index|[
literal|0
index|]
operator|=
name|d
index|[
literal|1
index|]
operator|=
name|d
index|[
literal|2
index|]
operator|=
name|CHECK_COLOR
argument_list|(
name|area
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
expr_stmt|;
break|break;
case|case
literal|255
case|:
name|d
index|[
literal|0
index|]
operator|=
name|cmap
index|[
literal|0
index|]
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
name|cmap
index|[
literal|1
index|]
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|cmap
index|[
literal|2
index|]
expr_stmt|;
break|break;
default|default:
block|{
specifier|register
name|guint
name|alpha
init|=
name|s
index|[
literal|3
index|]
operator|+
literal|1
decl_stmt|;
specifier|register
name|guint
name|check
init|=
name|CHECK_COLOR
argument_list|(
name|area
argument_list|,
name|row
argument_list|,
name|col
argument_list|)
decl_stmt|;
name|d
index|[
literal|0
index|]
operator|=
operator|(
operator|(
name|check
operator|<<
literal|8
operator|)
operator|+
operator|(
name|cmap
index|[
literal|0
index|]
operator|-
name|check
operator|)
operator|*
name|alpha
operator|)
operator|>>
literal|8
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
operator|(
operator|(
name|check
operator|<<
literal|8
operator|)
operator|+
operator|(
name|cmap
index|[
literal|1
index|]
operator|-
name|check
operator|)
operator|*
name|alpha
operator|)
operator|>>
literal|8
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
operator|(
operator|(
name|check
operator|<<
literal|8
operator|)
operator|+
operator|(
name|cmap
index|[
literal|2
index|]
operator|-
name|check
operator|)
operator|*
name|alpha
operator|)
operator|>>
literal|8
expr_stmt|;
block|}
break|break;
block|}
block|}
name|src
operator|+=
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|area
operator|->
name|rowstride
expr_stmt|;
block|}
break|break;
block|}
name|gtk_widget_queue_draw_area
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
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

begin_comment
comment|/**  * gimp_preview_area_fill:  * @area:   a #GimpPreviewArea widget.  * @x:      x offset in preview  * @y:      y offset in preview  * @width:  buffer width  * @height: buffer height  * @red:  * @green:  * @blue:  *  * Fills the @area in the given color.  *  * Since GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_preview_area_fill (GimpPreviewArea * area,gint x,gint y,gint width,gint height,guchar red,guchar green,guchar blue)
name|gimp_preview_area_fill
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
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
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
block|{
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|row
decl_stmt|;
name|gint
name|col
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PREVIEW_AREA
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|x
operator|+
name|width
operator|<
literal|0
operator|||
name|x
operator|>=
name|area
operator|->
name|width
condition|)
return|return;
if|if
condition|(
name|y
operator|+
name|height
operator|<
literal|0
operator|||
name|y
operator|>=
name|area
operator|->
name|height
condition|)
return|return;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
block|{
name|width
operator|-=
name|x
expr_stmt|;
name|x
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|+
name|width
operator|>
name|area
operator|->
name|width
condition|)
name|width
operator|=
name|area
operator|->
name|width
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
condition|)
block|{
name|height
operator|-=
name|y
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|+
name|height
operator|>
name|area
operator|->
name|height
condition|)
name|height
operator|=
name|area
operator|->
name|height
operator|-
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|area
operator|->
name|buf
condition|)
block|{
name|area
operator|->
name|rowstride
operator|=
operator|(
operator|(
name|area
operator|->
name|width
operator|*
literal|3
operator|)
operator|+
literal|3
operator|)
operator|&
operator|~
literal|3
expr_stmt|;
name|area
operator|->
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|area
operator|->
name|rowstride
operator|*
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
name|dest
operator|=
name|area
operator|->
name|buf
operator|+
name|x
operator|*
literal|3
operator|+
name|y
operator|*
name|area
operator|->
name|rowstride
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|height
condition|;
name|row
operator|++
control|)
block|{
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|width
condition|;
name|col
operator|++
operator|,
name|d
operator|+=
literal|3
control|)
block|{
name|d
index|[
literal|0
index|]
operator|=
name|red
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
name|green
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|blue
expr_stmt|;
block|}
name|dest
operator|+=
name|area
operator|->
name|rowstride
expr_stmt|;
block|}
name|gtk_widget_queue_draw_area
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
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

begin_comment
comment|/**  * gimp_preview_area_set_offsets:  * @area: a #GimpPreviewArea  * @x:    horizontal offset  * @y:    vertical offset  *  * Sets the offsets of the previewed area. This information is used  * when drawing the checkerboard and to determine the dither offsets.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_preview_area_set_offsets (GimpPreviewArea * area,gint x,gint y)
name|gimp_preview_area_set_offsets
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PREVIEW_AREA
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|area
operator|->
name|offset_x
operator|=
name|x
expr_stmt|;
name|area
operator|->
name|offset_y
operator|=
name|y
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_preview_area_set_cmap:  * @area:       a #GimpPreviewArea  * @cmap:       a #guchar buffer that contains the colormap  * @num_colors: the number of colors in the colormap  *  * Sets the colormap for the #GimpPreviewArea widget. You need to  * call this function before you use gimp_preview_area_draw() with  * an image type of %GIMP_INDEXED_IMAGE or %GIMP_INDEXEDA_IMAGE.  *  * Since GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_preview_area_set_cmap (GimpPreviewArea * area,const guchar * cmap,gint num_colors)
name|gimp_preview_area_set_cmap
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PREVIEW_AREA
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cmap
operator|!=
name|NULL
operator|||
name|num_colors
operator|==
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|num_colors
operator|>=
literal|0
operator|&&
name|num_colors
operator|<=
literal|256
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_colors
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|area
operator|->
name|cmap
condition|)
name|area
operator|->
name|cmap
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
literal|3
operator|*
literal|256
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|area
operator|->
name|cmap
argument_list|,
name|cmap
argument_list|,
literal|3
operator|*
name|num_colors
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|area
operator|->
name|cmap
argument_list|)
expr_stmt|;
name|area
operator|->
name|cmap
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

end_unit

