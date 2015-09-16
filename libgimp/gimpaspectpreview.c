begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpaspectpreview.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"gimpaspectpreview.h"
end_include

begin_comment
comment|/**  * SECTION: gimpaspectpreview  * @title: GimpAspectPreview  * @short_description: A widget providing a preview with fixed aspect ratio.  *  * A widget providing a preview with fixed aspect ratio.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2c5b47740103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DRAWABLE
name|PROP_DRAWABLE
block|,
DECL|enumerator|PROP_DRAWABLE_ID
name|PROP_DRAWABLE_ID
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c5b47740208
block|{
DECL|member|drawable_ID
name|gint32
name|drawable_ID
decl_stmt|;
DECL|typedef|GimpAspectPreviewPrivate
block|}
name|GimpAspectPreviewPrivate
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c5b47740308
block|{
DECL|member|update
name|gboolean
name|update
decl_stmt|;
DECL|typedef|PreviewSettings
block|}
name|PreviewSettings
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_ASPECT_PREVIEW_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (preview, \                                GIMP_TYPE_ASPECT_PREVIEW, \                                GimpAspectPreviewPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_aspect_preview_constructed
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
name|gimp_aspect_preview_dispose
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
name|gimp_aspect_preview_get_property
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
name|gimp_aspect_preview_set_property
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
name|gimp_aspect_preview_style_set
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
name|gimp_aspect_preview_draw
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
name|gimp_aspect_preview_draw_buffer
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
name|gimp_aspect_preview_transform
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_aspect_preview_untransform
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_aspect_preview_set_drawable
parameter_list|(
name|GimpAspectPreview
modifier|*
name|preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_aspect_preview_set_drawable_id
parameter_list|(
name|GimpAspectPreview
modifier|*
name|preview
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAspectPreview
argument_list|,
argument|gimp_aspect_preview
argument_list|,
argument|GIMP_TYPE_PREVIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_aspect_preview_parent_class
end_define

begin_decl_stmt
specifier|static
name|gint
name|gimp_aspect_preview_counter
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_class_init (GimpAspectPreviewClass * klass)
name|gimp_aspect_preview_class_init
parameter_list|(
name|GimpAspectPreviewClass
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
name|constructed
operator|=
name|gimp_aspect_preview_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_aspect_preview_dispose
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_aspect_preview_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_aspect_preview_set_property
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_aspect_preview_style_set
expr_stmt|;
name|preview_class
operator|->
name|draw
operator|=
name|gimp_aspect_preview_draw
expr_stmt|;
name|preview_class
operator|->
name|draw_buffer
operator|=
name|gimp_aspect_preview_draw_buffer
expr_stmt|;
name|preview_class
operator|->
name|transform
operator|=
name|gimp_aspect_preview_transform
expr_stmt|;
name|preview_class
operator|->
name|untransform
operator|=
name|gimp_aspect_preview_untransform
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpAspectPreviewPrivate
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpAspectPreview:drawable:    *    * Deprecated: use the drawable-id property instead.    *    * Since: 2.4    */
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
comment|/**    * GimpAspectPreview:drawable-id:    *    * The drawable the #GimpAspectPreview is attached to.    *    * Since: 2.10    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DRAWABLE_ID
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"drawable-id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|,
name|G_MAXINT
argument_list|,
operator|-
literal|1
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
DECL|function|gimp_aspect_preview_init (GimpAspectPreview * preview)
name|gimp_aspect_preview_init
parameter_list|(
name|GimpAspectPreview
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
name|void
DECL|function|gimp_aspect_preview_constructed (GObject * object)
name|gimp_aspect_preview_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|gchar
modifier|*
name|data_name
decl_stmt|;
name|PreviewSettings
name|settings
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|data_name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-aspect-preview-%d"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|gimp_aspect_preview_counter
operator|++
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
block|{
name|gimp_preview_set_update
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|object
argument_list|)
argument_list|,
name|settings
operator|.
name|update
argument_list|)
expr_stmt|;
block|}
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
literal|"gimp-aspect-preview-data-name"
argument_list|,
name|data_name
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_dispose (GObject * object)
name|gimp_aspect_preview_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|data_name
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"gimp-aspect-preview-data-name"
argument_list|)
decl_stmt|;
if|if
condition|(
name|data_name
condition|)
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
name|settings
operator|.
name|update
operator|=
name|gimp_preview_get_update
argument_list|(
name|preview
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
block|}
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
DECL|function|gimp_aspect_preview_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_aspect_preview_get_property
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
name|GimpAspectPreview
modifier|*
name|preview
init|=
name|GIMP_ASPECT_PREVIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
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
name|preview
operator|->
name|drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DRAWABLE_ID
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|drawable_ID
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
DECL|function|gimp_aspect_preview_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_aspect_preview_set_property
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
name|GimpAspectPreview
modifier|*
name|preview
init|=
name|GIMP_ASPECT_PREVIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
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
name|g_return_if_fail
argument_list|(
name|priv
operator|->
name|drawable_ID
operator|<
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
condition|)
name|gimp_aspect_preview_set_drawable
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
case|case
name|PROP_DRAWABLE_ID
case|:
name|gimp_aspect_preview_set_drawable_id
argument_list|(
name|preview
argument_list|,
name|g_value_get_int
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
DECL|function|gimp_aspect_preview_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_aspect_preview_style_set
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
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
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
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|>
name|height
condition|)
block|{
name|preview
operator|->
name|width
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|preview
operator|->
name|height
operator|=
operator|(
name|height
operator|*
name|preview
operator|->
name|width
operator|)
operator|/
name|width
expr_stmt|;
block|}
else|else
block|{
name|preview
operator|->
name|height
operator|=
name|MIN
argument_list|(
name|height
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|preview
operator|->
name|width
operator|=
operator|(
name|width
operator|*
name|preview
operator|->
name|height
operator|)
operator|/
name|height
expr_stmt|;
block|}
name|gtk_widget_set_size_request
argument_list|(
name|preview
operator|->
name|area
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_draw (GimpPreview * preview)
name|gimp_aspect_preview_draw
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ASPECT_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_preview_area_fill
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
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_draw_buffer (GimpPreview * preview,const guchar * buffer,gint rowstride)
name|gimp_aspect_preview_draw_buffer
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
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|image_ID
operator|=
name|gimp_item_get_image
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_selection_is_empty
argument_list|(
name|image_ID
argument_list|)
condition|)
block|{
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
name|priv
operator|->
name|drawable_ID
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|guchar
modifier|*
name|sel
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|gint
name|selection_ID
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|selection_ID
operator|=
name|gimp_image_get_selection
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|width
operator|=
name|preview
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|preview
operator|->
name|height
expr_stmt|;
name|src
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
name|sel
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|selection_ID
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
name|gimp_preview_area_mask
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
name|priv
operator|->
name|drawable_ID
argument_list|)
argument_list|,
name|src
argument_list|,
name|width
operator|*
name|gimp_drawable_bpp
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
argument_list|,
name|buffer
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
DECL|function|gimp_aspect_preview_transform (GimpPreview * preview,gint src_x,gint src_y,gint * dest_x,gint * dest_y)
name|gimp_aspect_preview_transform
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
block|{
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
operator|*
name|dest_x
operator|=
operator|(
name|gdouble
operator|)
name|src_x
operator|*
name|preview
operator|->
name|width
operator|/
name|gimp_drawable_width
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
expr_stmt|;
operator|*
name|dest_y
operator|=
operator|(
name|gdouble
operator|)
name|src_y
operator|*
name|preview
operator|->
name|height
operator|/
name|gimp_drawable_height
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_untransform (GimpPreview * preview,gint src_x,gint src_y,gint * dest_x,gint * dest_y)
name|gimp_aspect_preview_untransform
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
block|{
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
operator|*
name|dest_x
operator|=
operator|(
name|gdouble
operator|)
name|src_x
operator|*
name|gimp_drawable_width
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
operator|/
name|preview
operator|->
name|width
expr_stmt|;
operator|*
name|dest_y
operator|=
operator|(
name|gdouble
operator|)
name|src_y
operator|*
name|gimp_drawable_height
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
operator|/
name|preview
operator|->
name|height
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_set_drawable (GimpAspectPreview * preview,GimpDrawable * drawable)
name|gimp_aspect_preview_set_drawable
parameter_list|(
name|GimpAspectPreview
modifier|*
name|preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|preview
operator|->
name|drawable
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|priv
operator|->
name|drawable_ID
operator|<
literal|1
argument_list|)
expr_stmt|;
name|preview
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|gimp_aspect_preview_set_drawable_id
argument_list|(
name|preview
argument_list|,
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_set_drawable_id (GimpAspectPreview * preview,gint32 drawable_ID)
name|gimp_aspect_preview_set_drawable_id
parameter_list|(
name|GimpAspectPreview
modifier|*
name|preview
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpAspectPreviewPrivate
modifier|*
name|priv
init|=
name|GIMP_ASPECT_PREVIEW_GET_PRIVATE
argument_list|(
name|preview
argument_list|)
decl_stmt|;
name|gint
name|d_width
decl_stmt|;
name|gint
name|d_height
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|priv
operator|->
name|drawable_ID
operator|<
literal|1
argument_list|)
expr_stmt|;
name|priv
operator|->
name|drawable_ID
operator|=
name|drawable_ID
expr_stmt|;
name|d_width
operator|=
name|gimp_drawable_width
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
expr_stmt|;
name|d_height
operator|=
name|gimp_drawable_height
argument_list|(
name|priv
operator|->
name|drawable_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|d_width
operator|>
name|d_height
condition|)
block|{
name|width
operator|=
name|MIN
argument_list|(
name|d_width
argument_list|,
literal|512
argument_list|)
expr_stmt|;
name|height
operator|=
operator|(
name|d_height
operator|*
name|width
operator|)
operator|/
name|d_width
expr_stmt|;
block|}
else|else
block|{
name|height
operator|=
name|MIN
argument_list|(
name|d_height
argument_list|,
literal|512
argument_list|)
expr_stmt|;
name|width
operator|=
operator|(
name|d_width
operator|*
name|height
operator|)
operator|/
name|d_height
expr_stmt|;
block|}
name|gimp_preview_set_bounds
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|height
operator|>
literal|0
condition|)
name|g_object_set
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|frame
argument_list|,
literal|"ratio"
argument_list|,
operator|(
name|gdouble
operator|)
name|d_width
operator|/
operator|(
name|gdouble
operator|)
name|d_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_aspect_preview_new_from_drawable_id:  * @drawable_ID: a drawable ID  *  * Creates a new #GimpAspectPreview widget for @drawable_ID. See also  * gimp_drawable_preview_new_from_drawable_id().  *  * Since: 2.10  *  * Returns: a new #GimpAspectPreview.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_aspect_preview_new_from_drawable_id (gint32 drawable_ID)
name|gimp_aspect_preview_new_from_drawable_id
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_valid
argument_list|(
name|drawable_ID
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_drawable
argument_list|(
name|drawable_ID
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ASPECT_PREVIEW
argument_list|,
literal|"drawable-id"
argument_list|,
name|drawable_ID
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_aspect_preview_new:  * @drawable: a #GimpDrawable  * @toggle:   unused  *  * Creates a new #GimpAspectPreview widget for @drawable. See also  * gimp_drawable_preview_new().  *  * In GIMP 2.2 the @toggle parameter was provided to conviently access  * the state of the "Preview" check-button. This is not any longer  * necessary as the preview itself now stores this state, as well as  * the scroll offset.  *  * Since: 2.2  *  * Returns: a new #GimpAspectPreview.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_aspect_preview_new (GimpDrawable * drawable,gboolean * toggle)
name|gimp_aspect_preview_new
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
name|g_return_val_if_fail
argument_list|(
name|drawable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ASPECT_PREVIEW
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

