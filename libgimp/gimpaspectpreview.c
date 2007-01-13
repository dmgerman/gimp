begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpaspectpreview.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"gimpaspectpreview.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b0f4cb30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DRAWABLE
name|PROP_DRAWABLE
block|}
enum|;
end_enum

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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpAspectPreview,gimp_aspect_preview,GIMP_TYPE_PREVIEW)
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

begin_function
specifier|static
name|void
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
comment|/**    * GimpAspectPreview:drawable:    *    * Since: GIMP 2.4    */
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
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_DRAWABLE
case|:
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_ASPECT_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|drawable
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
if|if
condition|(
name|drawable
operator|->
name|width
operator|>
name|drawable
operator|->
name|height
condition|)
block|{
name|preview
operator|->
name|width
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
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
name|drawable
operator|->
name|height
operator|*
name|preview
operator|->
name|width
operator|)
operator|/
name|drawable
operator|->
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
name|drawable
operator|->
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
name|drawable
operator|->
name|width
operator|*
name|preview
operator|->
name|height
operator|)
operator|/
name|drawable
operator|->
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_ASPECT_PREVIEW
argument_list|(
name|preview
argument_list|)
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
name|selection_id
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|selection_id
operator|=
name|gimp_image_get_selection
argument_list|(
name|image_id
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
name|drawable
operator|->
name|drawable_id
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
name|selection_id
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_ASPECT_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|drawable
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
name|drawable
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
name|preview
operator|->
name|height
operator|/
name|drawable
operator|->
name|height
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
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_ASPECT_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|drawable
decl_stmt|;
operator|*
name|dest_x
operator|=
operator|(
name|gdouble
operator|)
name|src_x
operator|*
name|drawable
operator|->
name|width
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
name|drawable
operator|->
name|height
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
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|preview
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
if|if
condition|(
name|drawable
operator|->
name|width
operator|>
name|drawable
operator|->
name|height
condition|)
block|{
name|width
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|width
argument_list|,
literal|512
argument_list|)
expr_stmt|;
name|height
operator|=
operator|(
name|drawable
operator|->
name|height
operator|*
name|width
operator|)
operator|/
name|drawable
operator|->
name|width
expr_stmt|;
block|}
else|else
block|{
name|height
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|height
argument_list|,
literal|512
argument_list|)
expr_stmt|;
name|width
operator|=
operator|(
name|drawable
operator|->
name|width
operator|*
name|height
operator|)
operator|/
name|drawable
operator|->
name|height
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
name|drawable
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|drawable
operator|->
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_aspect_preview_notify_update (GimpPreview * preview,GParamSpec * pspec,gboolean * toggle)
name|gimp_aspect_preview_notify_update
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
comment|/**  * gimp_aspect_preview_new:  * @drawable: a #GimpDrawable  * @toggle:   pointer to a #gboolean variable to sync with the "Preview"  *            check-button or %NULL  *  * Creates a new #GimpAspectPreview widget for @drawable. See also  * gimp_drawable_preview_new().  *  * Since: GIMP 2.2  **/
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
name|GIMP_TYPE_ASPECT_PREVIEW
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
name|gimp_aspect_preview_notify_update
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

end_unit

