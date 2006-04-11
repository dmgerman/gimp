begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawablepreview.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablepreview.h"
end_include

begin_define
DECL|macro|SELECTION_BORDER
define|#
directive|define
name|SELECTION_BORDER
value|8
end_define

begin_enum
enum|enum
DECL|enum|__anon2aa9f4150103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DRAWABLE
name|PROP_DRAWABLE
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2aa9f4150208
block|{
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
DECL|member|update
name|gboolean
name|update
decl_stmt|;
DECL|typedef|PreviewSettings
block|}
name|PreviewSettings
typedef|;
end_typedef

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_drawable_preview_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_get_property
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
name|gimp_drawable_preview_set_property
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
name|gimp_drawable_preview_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_draw_original
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_draw_thumb
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_draw_buffer
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|rowstride
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_drawable_preview_set_drawable
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpDrawablePreview
argument_list|,
name|gimp_drawable_preview
argument_list|,
name|GIMP_TYPE_SCROLLED_PREVIEW
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_drawable_preview_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_class_init (GimpDrawablePreviewClass * klass)
name|gimp_drawable_preview_class_init
parameter_list|(
name|GimpDrawablePreviewClass
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
name|GimpPreviewClass
modifier|*
name|preview_class
init|=
name|GIMP_PREVIEW_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_drawable_preview_constructor
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_drawable_preview_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_drawable_preview_set_property
expr_stmt|;
name|gtk_object_class
operator|->
name|destroy
operator|=
name|gimp_drawable_preview_destroy
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_drawable_preview_style_set
expr_stmt|;
name|preview_class
operator|->
name|draw
operator|=
name|gimp_drawable_preview_draw_original
expr_stmt|;
name|preview_class
operator|->
name|draw_thumb
operator|=
name|gimp_drawable_preview_draw_thumb
expr_stmt|;
name|preview_class
operator|->
name|draw_buffer
operator|=
name|gimp_drawable_preview_draw_buffer
expr_stmt|;
comment|/**    * GimpDrawablePreview:drawable:    *    * Since: GIMP 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DRAWABLE
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"drawable"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_init (GimpDrawablePreview * preview)
name|gimp_drawable_preview_init
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|preview
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|area
argument_list|,
literal|"check-size"
argument_list|,
name|gimp_check_size
argument_list|()
argument_list|,
literal|"check-type"
argument_list|,
name|gimp_check_type
argument_list|()
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_drawable_preview_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_drawable_preview_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|PreviewSettings
name|settings
decl_stmt|;
name|gchar
modifier|*
name|data_name
init|=
name|g_strconcat
argument_list|(
name|g_get_prgname
argument_list|()
argument_list|,
literal|"-preview"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_get_data
argument_list|(
name|data_name
argument_list|,
operator|&
name|settings
argument_list|)
condition|)
name|gimp_scrolled_preview_set_position
argument_list|(
name|GIMP_SCROLLED_PREVIEW
argument_list|(
name|object
argument_list|)
argument_list|,
name|settings
operator|.
name|x
argument_list|,
name|settings
operator|.
name|y
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data_name
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_drawable_preview_get_property
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
name|GimpDrawablePreview
modifier|*
name|preview
init|=
name|GIMP_DRAWABLE_PREVIEW
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
name|PROP_DRAWABLE
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|gimp_drawable_preview_get_drawable
argument_list|(
name|preview
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
DECL|function|gimp_drawable_preview_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_drawable_preview_set_property
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
name|GimpDrawablePreview
modifier|*
name|preview
init|=
name|GIMP_DRAWABLE_PREVIEW
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
name|PROP_DRAWABLE
case|:
name|gimp_drawable_preview_set_drawable
argument_list|(
name|preview
argument_list|,
name|g_value_get_pointer
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
DECL|function|gimp_drawable_preview_destroy (GtkObject * object)
name|gimp_drawable_preview_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
init|=
name|GIMP_PREVIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|PreviewSettings
name|settings
decl_stmt|;
name|gchar
modifier|*
name|data_name
decl_stmt|;
name|settings
operator|.
name|x
operator|=
name|preview
operator|->
name|xoff
operator|+
name|preview
operator|->
name|xmin
expr_stmt|;
name|settings
operator|.
name|y
operator|=
name|preview
operator|->
name|yoff
operator|+
name|preview
operator|->
name|ymin
expr_stmt|;
name|settings
operator|.
name|update
operator|=
name|TRUE
expr_stmt|;
name|data_name
operator|=
name|g_strconcat
argument_list|(
name|g_get_prgname
argument_list|()
argument_list|,
literal|"-preview"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_set_data
argument_list|(
name|data_name
argument_list|,
operator|&
name|settings
argument_list|,
sizeof|sizeof
argument_list|(
name|PreviewSettings
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data_name
argument_list|)
expr_stmt|;
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
DECL|function|gimp_drawable_preview_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_drawable_preview_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
init|=
name|GIMP_PREVIEW
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|width
init|=
name|preview
operator|->
name|xmax
operator|-
name|preview
operator|->
name|xmin
decl_stmt|;
name|gint
name|height
init|=
name|preview
operator|->
name|ymax
operator|-
name|preview
operator|->
name|ymin
decl_stmt|;
name|gint
name|size
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"size"
argument_list|,
operator|&
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|area
argument_list|,
name|MIN
argument_list|(
name|width
argument_list|,
name|size
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|height
argument_list|,
name|size
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_draw_original (GimpPreview * preview)
name|gimp_drawable_preview_draw_original
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpDrawablePreview
modifier|*
name|drawable_preview
init|=
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|drawable_preview
operator|->
name|drawable
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|GimpPixelRgn
name|srcPR
decl_stmt|;
name|guint
name|rowstride
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|rowstride
operator|=
name|preview
operator|->
name|width
operator|*
name|drawable
operator|->
name|bpp
expr_stmt|;
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|rowstride
operator|*
name|preview
operator|->
name|height
argument_list|)
expr_stmt|;
name|preview
operator|->
name|xoff
operator|=
name|CLAMP
argument_list|(
name|preview
operator|->
name|xoff
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|xmax
operator|-
name|preview
operator|->
name|xmin
operator|-
name|preview
operator|->
name|width
argument_list|)
expr_stmt|;
name|preview
operator|->
name|yoff
operator|=
name|CLAMP
argument_list|(
name|preview
operator|->
name|yoff
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|ymax
operator|-
name|preview
operator|->
name|ymin
operator|-
name|preview
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
name|preview
operator|->
name|xoff
operator|+
name|preview
operator|->
name|xmin
argument_list|,
name|preview
operator|->
name|yoff
operator|+
name|preview
operator|->
name|ymin
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|preview
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
name|preview
operator|->
name|xoff
operator|+
name|preview
operator|->
name|xmin
argument_list|,
name|preview
operator|->
name|yoff
operator|+
name|preview
operator|->
name|ymin
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|preview
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|preview
operator|->
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_draw_thumb (GimpPreview * preview,GimpPreviewArea * area,gint width,gint height)
name|gimp_drawable_preview_draw_thumb
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpDrawablePreview
modifier|*
name|drawable_preview
init|=
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|drawable_preview
operator|->
name|drawable
decl_stmt|;
if|if
condition|(
name|drawable
condition|)
name|_gimp_drawable_preview_area_draw_thumb
argument_list|(
name|area
argument_list|,
name|drawable
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
DECL|function|_gimp_drawable_preview_area_draw_thumb (GimpPreviewArea * area,GimpDrawable * drawable,gint width,gint height)
name|_gimp_drawable_preview_area_draw_thumb
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|size
init|=
literal|100
decl_stmt|;
name|gint
name|nav_width
decl_stmt|,
name|nav_height
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
name|drawable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|_gimp_drawable_preview_get_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
condition|)
block|{
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
block|}
else|else
block|{
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|width
operator|>
name|height
condition|)
block|{
name|nav_width
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|nav_height
operator|=
operator|(
name|height
operator|*
name|nav_width
operator|)
operator|/
name|width
expr_stmt|;
block|}
else|else
block|{
name|nav_height
operator|=
name|MIN
argument_list|(
name|height
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|nav_width
operator|=
operator|(
name|width
operator|*
name|nav_height
operator|)
operator|/
name|height
expr_stmt|;
block|}
if|if
condition|(
name|_gimp_drawable_preview_get_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
condition|)
block|{
name|buffer
operator|=
name|gimp_drawable_get_sub_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
operator|&
name|nav_width
argument_list|,
operator|&
name|nav_height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|buffer
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|nav_width
argument_list|,
operator|&
name|nav_height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|buffer
condition|)
block|{
name|GimpImageType
name|type
decl_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|,
name|nav_width
argument_list|,
name|nav_height
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|GTK_WIDGET
argument_list|(
name|area
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
name|type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
break|break;
default|default:
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_preview_area_draw
argument_list|(
name|area
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|nav_width
argument_list|,
name|nav_height
argument_list|,
name|type
argument_list|,
name|buffer
argument_list|,
name|bpp
operator|*
name|nav_width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_draw_area (GimpDrawablePreview * preview,gint x,gint y,gint width,gint height,const guchar * buf,gint rowstride)
name|gimp_drawable_preview_draw_area
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|preview
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
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|rowstride
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|gimp_preview
init|=
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|preview
operator|->
name|drawable
decl_stmt|;
name|gint32
name|image_id
decl_stmt|;
name|image_id
operator|=
name|gimp_drawable_get_image
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_selection_is_empty
argument_list|(
name|image_id
argument_list|)
condition|)
block|{
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|gimp_preview
operator|->
name|area
argument_list|)
argument_list|,
name|x
operator|-
name|gimp_preview
operator|->
name|xoff
operator|-
name|gimp_preview
operator|->
name|xmin
argument_list|,
name|y
operator|-
name|gimp_preview
operator|->
name|yoff
operator|-
name|gimp_preview
operator|->
name|ymin
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
name|buf
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpPixelRgn
name|drawable_rgn
decl_stmt|;
name|GimpPixelRgn
name|selection_rgn
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|sel
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gint
name|selection_id
decl_stmt|;
name|selection_id
operator|=
name|gimp_image_get_selection
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|drawable_rgn
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|selection_rgn
argument_list|,
name|gimp_drawable_get
argument_list|(
name|selection_id
argument_list|)
argument_list|,
name|x
operator|+
name|offset_x
argument_list|,
name|y
operator|+
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|src
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|drawable
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|sel
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|drawable_rgn
argument_list|,
name|src
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
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|selection_rgn
argument_list|,
name|sel
argument_list|,
name|x
operator|+
name|offset_x
argument_list|,
name|y
operator|+
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_preview_area_mask
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|gimp_preview
operator|->
name|area
argument_list|)
argument_list|,
name|x
operator|-
name|gimp_preview
operator|->
name|xoff
operator|-
name|gimp_preview
operator|->
name|xmin
argument_list|,
name|y
operator|-
name|gimp_preview
operator|->
name|yoff
operator|-
name|gimp_preview
operator|->
name|ymin
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
name|src
argument_list|,
name|width
operator|*
name|drawable
operator|->
name|bpp
argument_list|,
name|buf
argument_list|,
name|rowstride
argument_list|,
name|sel
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|sel
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_draw_buffer (GimpPreview * preview,const guchar * buffer,gint rowstride)
name|gimp_drawable_preview_draw_buffer
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|rowstride
parameter_list|)
block|{
name|gimp_drawable_preview_draw_area
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|preview
operator|->
name|xmin
operator|+
name|preview
operator|->
name|xoff
argument_list|,
name|preview
operator|->
name|ymin
operator|+
name|preview
operator|->
name|yoff
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|preview
operator|->
name|height
argument_list|,
name|buffer
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_set_drawable (GimpDrawablePreview * drawable_preview,GimpDrawable * drawable)
name|gimp_drawable_preview_set_drawable
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|drawable_preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
init|=
name|GIMP_PREVIEW
argument_list|(
name|drawable_preview
argument_list|)
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|drawable_preview
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|_gimp_drawable_preview_get_bounds
argument_list|(
name|drawable
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_preview_set_bounds
argument_list|(
name|preview
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
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|guint32
name|image
init|=
name|gimp_drawable_get_image
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|num_colors
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
name|gimp_preview_area_set_colormap
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|,
name|cmap
argument_list|,
name|num_colors
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|MAX3 (a,b,c)
define|#
directive|define
name|MAX3
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|)
value|(MAX (MAX ((a), (b)), (c)))
end_define

begin_define
DECL|macro|MIN3 (a,b,c)
define|#
directive|define
name|MIN3
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|)
value|(MIN (MIN ((a), (b)), (c)))
end_define

begin_function
name|gboolean
DECL|function|_gimp_drawable_preview_get_bounds (GimpDrawable * drawable,gint * xmin,gint * ymin,gint * xmax,gint * ymax)
name|_gimp_drawable_preview_get_bounds
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
modifier|*
name|xmin
parameter_list|,
name|gint
modifier|*
name|ymin
parameter_list|,
name|gint
modifier|*
name|xmax
parameter_list|,
name|gint
modifier|*
name|ymax
parameter_list|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
operator|*
name|xmin
operator|=
name|MAX3
argument_list|(
name|x1
operator|-
name|SELECTION_BORDER
argument_list|,
literal|0
argument_list|,
operator|-
name|offset_x
argument_list|)
expr_stmt|;
operator|*
name|ymin
operator|=
name|MAX3
argument_list|(
name|y1
operator|-
name|SELECTION_BORDER
argument_list|,
literal|0
argument_list|,
operator|-
name|offset_y
argument_list|)
expr_stmt|;
operator|*
name|xmax
operator|=
name|MIN3
argument_list|(
name|x2
operator|+
name|SELECTION_BORDER
argument_list|,
name|width
argument_list|,
name|width
operator|+
name|offset_x
argument_list|)
expr_stmt|;
operator|*
name|ymax
operator|=
name|MIN3
argument_list|(
name|y2
operator|+
name|SELECTION_BORDER
argument_list|,
name|height
argument_list|,
name|height
operator|+
name|offset_y
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_preview_notify_update (GimpPreview * preview,GParamSpec * pspec,gboolean * toggle)
name|gimp_drawable_preview_notify_update
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gboolean
modifier|*
name|toggle
parameter_list|)
block|{
operator|*
name|toggle
operator|=
name|gimp_preview_get_update
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_preview_new:  * @drawable: a #GimpDrawable  * @toggle:   pointer to a #gboolean variable to sync with the "Preview"  *            check-button or %NULL  *  * Creates a new #GimpDrawablePreview widget for @drawable. If  * updating the preview takes considerable time, you will want to  * store the state of the "Preview" check-button in the plug-in  * data. For convenience you can pass a pointer to the #gboolean as  * @toggle.  *  * Returns: A pointer to the new #GimpDrawablePreview widget.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_drawable_preview_new (GimpDrawable * drawable,gboolean * toggle)
name|gimp_drawable_preview_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
modifier|*
name|toggle
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|preview
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DRAWABLE_PREVIEW
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|toggle
condition|)
block|{
name|gimp_preview_set_update
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|*
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"notify::update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_drawable_preview_notify_update
argument_list|)
argument_list|,
name|toggle
argument_list|)
expr_stmt|;
block|}
return|return
name|preview
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_preview_get_drawable:  * @preview:   a #GimpDrawablePreview widget  *  * Return value: the #GimpDrawable that has been passed to  *               gimp_drawable_preview_new().  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GimpDrawable
modifier|*
DECL|function|gimp_drawable_preview_get_drawable (GimpDrawablePreview * preview)
name|gimp_drawable_preview_get_drawable
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|preview
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|preview
operator|->
name|drawable
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_preview_draw_region:  * @preview: a #GimpDrawablePreview widget  * @region:  a #GimpPixelRgn  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_drawable_preview_draw_region (GimpDrawablePreview * preview,const GimpPixelRgn * region)
name|gimp_drawable_preview_draw_region
parameter_list|(
name|GimpDrawablePreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|GimpPixelRgn
modifier|*
name|region
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|preview
operator|->
name|drawable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|region
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*  If the data field is initialized, this region is currently being    *  processed and we can access it directly.    */
if|if
condition|(
name|region
operator|->
name|data
condition|)
block|{
name|gimp_drawable_preview_draw_area
argument_list|(
name|preview
argument_list|,
name|region
operator|->
name|x
argument_list|,
name|region
operator|->
name|y
argument_list|,
name|region
operator|->
name|w
argument_list|,
name|region
operator|->
name|h
argument_list|,
name|region
operator|->
name|data
argument_list|,
name|region
operator|->
name|rowstride
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpPixelRgn
name|src
init|=
operator|*
name|region
decl_stmt|;
name|gpointer
name|iter
decl_stmt|;
name|src
operator|.
name|dirty
operator|=
name|FALSE
expr_stmt|;
comment|/* we don't dirty the tiles, just read them */
for|for
control|(
name|iter
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|src
argument_list|)
init|;
name|iter
operator|!=
name|NULL
condition|;
name|iter
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|gimp_drawable_preview_draw_area
argument_list|(
name|preview
argument_list|,
name|src
operator|.
name|x
argument_list|,
name|src
operator|.
name|y
argument_list|,
name|src
operator|.
name|w
argument_list|,
name|src
operator|.
name|h
argument_list|,
name|src
operator|.
name|data
argument_list|,
name|src
operator|.
name|rowstride
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

