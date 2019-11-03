begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimageproxy.c  * Copyright (C) 2019 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-loops.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-color-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-preview.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageproxy.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojectable.h"
end_include

begin_include
include|#
directive|include
file|"gimptempbuf.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon296641820103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|,
DECL|enumerator|PROP_SHOW_ALL
name|PROP_SHOW_ALL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpImageProxyPrivate
struct|struct
name|_GimpImageProxyPrivate
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|show_all
name|gboolean
name|show_all
decl_stmt|;
DECL|member|bounding_box
name|GeglRectangle
name|bounding_box
decl_stmt|;
DECL|member|frozen
name|gboolean
name|frozen
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_finalize
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
name|gimp_image_proxy_set_property
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
name|gimp_image_proxy_get_property
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
name|gimp_image_proxy_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|is_popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_image_proxy_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpTempBuf
modifier|*
name|gimp_image_proxy_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|GdkPixbuf
modifier|*
name|gimp_image_proxy_get_new_pixbuf
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gchar
modifier|*
name|gimp_image_proxy_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_image_frozen_notify
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_image_invalidate_preview
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_image_size_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_image_bounds_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|old_x
parameter_list|,
name|gint
name|old_y
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_set_image
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_update_bounding_box
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_proxy_update_frozen
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpImageProxy
argument_list|,
argument|gimp_image_proxy
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_proxy_parent_class
end_define

begin_comment
comment|/*  private functions  */
end_comment

begin_expr_stmt
specifier|static
name|void
operator|-
name|gimp_image_proxy_class_init
argument_list|(
argument|GimpImageProxyClass *klass
argument_list|)
block|{
name|GObjectClass
operator|*
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
block|;
name|GimpViewableClass
operator|*
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
block|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_image_proxy_finalize
block|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_image_proxy_set_property
block|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_image_proxy_get_property
block|;
name|viewable_class
operator|->
name|default_icon_name
operator|=
literal|"gimp-image"
block|;
name|viewable_class
operator|->
name|get_size
operator|=
name|gimp_image_proxy_get_size
block|;
name|viewable_class
operator|->
name|get_preview_size
operator|=
name|gimp_image_proxy_get_preview_size
block|;
name|viewable_class
operator|->
name|get_popup_size
operator|=
name|gimp_image_proxy_get_popup_size
block|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_image_proxy_get_new_preview
block|;
name|viewable_class
operator|->
name|get_new_pixbuf
operator|=
name|gimp_image_proxy_get_new_pixbuf
block|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_image_proxy_get_description
block|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
block|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SHOW_ALL
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"show-all"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
block|; }
specifier|static
name|void
DECL|function|gimp_image_proxy_init (GimpImageProxy * image_proxy)
name|gimp_image_proxy_init
argument_list|(
argument|GimpImageProxy *image_proxy
argument_list|)
block|{
name|image_proxy
operator|->
name|priv
operator|=
name|gimp_image_proxy_get_instance_private
argument_list|(
name|image_proxy
argument_list|)
block|; }
specifier|static
name|void
DECL|function|gimp_image_proxy_finalize (GObject * object)
name|gimp_image_proxy_finalize
argument_list|(
argument|GObject *object
argument_list|)
block|{
name|GimpImageProxy
operator|*
name|image_proxy
operator|=
name|GIMP_IMAGE_PROXY
argument_list|(
name|object
argument_list|)
block|;
name|gimp_image_proxy_set_image
argument_list|(
name|image_proxy
argument_list|,
name|NULL
argument_list|)
block|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
block|; }
specifier|static
name|void
DECL|function|gimp_image_proxy_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_image_proxy_set_property
argument_list|(
argument|GObject      *object
argument_list|,
argument|guint         property_id
argument_list|,
argument|const GValue *value
argument_list|,
argument|GParamSpec   *pspec
argument_list|)
block|{
name|GimpImageProxy
operator|*
name|image_proxy
operator|=
name|GIMP_IMAGE_PROXY
argument_list|(
name|object
argument_list|)
block|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_IMAGE
case|:
name|gimp_image_proxy_set_image
argument_list|(
name|image_proxy
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_ALL
case|:
name|gimp_image_proxy_set_show_all
argument_list|(
name|image_proxy
argument_list|,
name|g_value_get_boolean
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
end_expr_stmt

begin_function
unit|}  static
name|void
DECL|function|gimp_image_proxy_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_image_proxy_get_property
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
name|GimpImageProxy
modifier|*
name|image_proxy
init|=
name|GIMP_IMAGE_PROXY
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
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|gimp_image_proxy_get_image
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHOW_ALL
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gimp_image_proxy_get_show_all
argument_list|(
name|image_proxy
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
name|gboolean
DECL|function|gimp_image_proxy_get_size (GimpViewable * viewable,gint * width,gint * height)
name|gimp_image_proxy_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpImageProxy
modifier|*
name|image_proxy
init|=
name|GIMP_IMAGE_PROXY
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
operator|*
name|width
operator|=
name|image_proxy
operator|->
name|priv
operator|->
name|bounding_box
operator|.
name|width
expr_stmt|;
operator|*
name|height
operator|=
name|image_proxy
operator|->
name|priv
operator|->
name|bounding_box
operator|.
name|height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_get_preview_size (GimpViewable * viewable,gint size,gboolean is_popup,gboolean dot_for_dot,gint * width,gint * height)
name|gimp_image_proxy_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|is_popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpImageProxy
modifier|*
name|image_proxy
init|=
name|GIMP_IMAGE_PROXY
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|image_proxy
operator|->
name|priv
operator|->
name|image
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gint
name|viewable_width
decl_stmt|;
name|gint
name|viewable_height
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|gimp_viewable_get_size
argument_list|(
name|viewable
argument_list|,
operator|&
name|viewable_width
argument_list|,
operator|&
name|viewable_height
argument_list|)
expr_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|viewable_width
argument_list|,
name|viewable_height
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
name|dot_for_dot
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_proxy_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_image_proxy_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
block|{
name|gint
name|viewable_width
decl_stmt|;
name|gint
name|viewable_height
decl_stmt|;
name|gimp_viewable_get_size
argument_list|(
name|viewable
argument_list|,
operator|&
name|viewable_width
argument_list|,
operator|&
name|viewable_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable_width
operator|>
name|width
operator|||
name|viewable_height
operator|>
name|height
condition|)
block|{
name|gboolean
name|scaling_up
decl_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|viewable_width
argument_list|,
name|viewable_height
argument_list|,
name|width
operator|*
literal|2
argument_list|,
name|height
operator|*
literal|2
argument_list|,
name|dot_for_dot
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|popup_width
argument_list|,
name|popup_height
argument_list|,
operator|&
name|scaling_up
argument_list|)
expr_stmt|;
if|if
condition|(
name|scaling_up
condition|)
block|{
operator|*
name|popup_width
operator|=
name|viewable_width
expr_stmt|;
operator|*
name|popup_height
operator|=
name|viewable_height
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|GimpTempBuf
modifier|*
DECL|function|gimp_image_proxy_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_image_proxy_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpImageProxy
modifier|*
name|image_proxy
init|=
name|GIMP_IMAGE_PROXY
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|image_proxy
operator|->
name|priv
operator|->
name|image
decl_stmt|;
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|GeglRectangle
name|bounding_box
decl_stmt|;
name|GimpTempBuf
modifier|*
name|buf
decl_stmt|;
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
if|if
condition|(
operator|!
name|image_proxy
operator|->
name|priv
operator|->
name|show_all
condition|)
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
expr_stmt|;
else|else
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|bounding_box
operator|=
name|gimp_image_proxy_get_bounding_box
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
name|scale_x
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|bounding_box
operator|.
name|width
expr_stmt|;
name|scale_y
operator|=
operator|(
name|gdouble
operator|)
name|height
operator|/
operator|(
name|gdouble
operator|)
name|bounding_box
operator|.
name|height
expr_stmt|;
name|scale
operator|=
name|MIN
argument_list|(
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|format
operator|=
name|gimp_image_get_preview_format
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|buf
operator|=
name|gimp_temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|bounding_box
operator|.
name|x
operator|*
name|scale
argument_list|,
name|bounding_box
operator|.
name|y
operator|*
name|scale
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|scale
argument_list|,
name|gimp_temp_buf_get_format
argument_list|(
name|buf
argument_list|)
argument_list|,
name|gimp_temp_buf_get_data
argument_list|(
name|buf
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
expr_stmt|;
return|return
name|buf
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|gimp_image_proxy_get_new_pixbuf (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_image_proxy_get_new_pixbuf
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpImageProxy
modifier|*
name|image_proxy
init|=
name|GIMP_IMAGE_PROXY
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|image_proxy
operator|->
name|priv
operator|->
name|image
decl_stmt|;
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
name|GeglRectangle
name|bounding_box
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|GimpColorTransform
modifier|*
name|transform
decl_stmt|;
if|if
condition|(
operator|!
name|image_proxy
operator|->
name|priv
operator|->
name|show_all
condition|)
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
expr_stmt|;
else|else
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|bounding_box
operator|=
name|gimp_image_proxy_get_bounding_box
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
name|scale_x
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|bounding_box
operator|.
name|width
expr_stmt|;
name|scale_y
operator|=
operator|(
name|gdouble
operator|)
name|height
operator|/
operator|(
name|gdouble
operator|)
name|bounding_box
operator|.
name|height
expr_stmt|;
name|scale
operator|=
name|MIN
argument_list|(
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|TRUE
argument_list|,
literal|8
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|transform
operator|=
name|gimp_image_get_color_transform_to_srgb_u8
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|transform
condition|)
block|{
name|GimpTempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|GeglBuffer
modifier|*
name|src_buf
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buf
decl_stmt|;
name|temp_buf
operator|=
name|gimp_temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|gimp_pickable_get_format
argument_list|(
name|pickable
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|bounding_box
operator|.
name|x
operator|*
name|scale
argument_list|,
name|bounding_box
operator|.
name|y
operator|*
name|scale
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|scale
argument_list|,
name|gimp_temp_buf_get_format
argument_list|(
name|temp_buf
argument_list|)
argument_list|,
name|gimp_temp_buf_get_data
argument_list|(
name|temp_buf
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
expr_stmt|;
name|src_buf
operator|=
name|gimp_temp_buf_create_buffer
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|dest_buf
operator|=
name|gimp_pixbuf_create_buffer
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gimp_temp_buf_unref
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|gimp_color_transform_process_buffer
argument_list|(
name|transform
argument_list|,
name|src_buf
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|dest_buf
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_buf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buf
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_buffer_get
argument_list|(
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|bounding_box
operator|.
name|x
operator|*
name|scale
argument_list|,
name|bounding_box
operator|.
name|y
operator|*
name|scale
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|scale
argument_list|,
name|gimp_pixbuf_get_format
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
expr_stmt|;
block|}
return|return
name|pixbuf
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_image_proxy_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_image_proxy_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpImageProxy
modifier|*
name|image_proxy
init|=
name|GIMP_IMAGE_PROXY
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|image_proxy
operator|->
name|priv
operator|->
name|image
decl_stmt|;
if|if
condition|(
name|tooltip
condition|)
operator|*
name|tooltip
operator|=
name|g_strdup
argument_list|(
name|gimp_image_get_display_path
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s-%d"
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_image_frozen_notify (GimpImage * image,const GParamSpec * pspec,GimpImageProxy * image_proxy)
name|gimp_image_proxy_image_frozen_notify
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|gimp_image_proxy_update_frozen
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_image_invalidate_preview (GimpImage * image,GimpImageProxy * image_proxy)
name|gimp_image_proxy_image_invalidate_preview
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_image_size_changed (GimpImage * image,GimpImageProxy * image_proxy)
name|gimp_image_proxy_image_size_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|gimp_image_proxy_update_bounding_box
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_image_bounds_changed (GimpImage * image,gint old_x,gint old_y,GimpImageProxy * image_proxy)
name|gimp_image_proxy_image_bounds_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|old_x
parameter_list|,
name|gint
name|old_y
parameter_list|,
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|gimp_image_proxy_update_bounding_box
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_set_image (GimpImageProxy * image_proxy,GimpImage * image)
name|gimp_image_proxy_set_image
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
if|if
condition|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
name|gimp_image_proxy_image_frozen_notify
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
name|gimp_image_proxy_image_invalidate_preview
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
name|gimp_image_proxy_image_size_changed
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
name|gimp_image_proxy_image_bounds_changed
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
name|image_proxy
operator|->
name|priv
operator|->
name|image
operator|=
name|image
expr_stmt|;
if|if
condition|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
condition|)
block|{
name|g_object_ref
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
literal|"notify::frozen"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_proxy_image_frozen_notify
argument_list|)
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
literal|"invalidate-preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_proxy_image_invalidate_preview
argument_list|)
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
literal|"size-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_proxy_image_size_changed
argument_list|)
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|,
literal|"bounds-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_proxy_image_bounds_changed
argument_list|)
argument_list|,
name|image_proxy
argument_list|)
expr_stmt|;
name|gimp_image_proxy_update_bounding_box
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
name|gimp_image_proxy_update_frozen
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_update_bounding_box (GimpImageProxy * image_proxy)
name|gimp_image_proxy_update_bounding_box
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|image_proxy
operator|->
name|priv
operator|->
name|image
decl_stmt|;
name|GeglRectangle
name|bounding_box
decl_stmt|;
if|if
condition|(
name|gimp_viewable_preview_is_frozen
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
condition|)
return|return;
if|if
condition|(
operator|!
name|image_proxy
operator|->
name|priv
operator|->
name|show_all
condition|)
block|{
name|bounding_box
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|bounding_box
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|bounding_box
operator|.
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|bounding_box
operator|.
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|bounding_box
operator|=
name|gimp_projectable_get_bounding_box
argument_list|(
name|GIMP_PROJECTABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gegl_rectangle_equal
argument_list|(
operator|&
name|bounding_box
argument_list|,
operator|&
name|image_proxy
operator|->
name|priv
operator|->
name|bounding_box
argument_list|)
condition|)
block|{
name|image_proxy
operator|->
name|priv
operator|->
name|bounding_box
operator|=
name|bounding_box
expr_stmt|;
name|gimp_viewable_size_changed
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_proxy_update_frozen (GimpImageProxy * image_proxy)
name|gimp_image_proxy_update_frozen
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|gboolean
name|frozen
decl_stmt|;
name|frozen
operator|=
name|gimp_viewable_preview_is_frozen
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_proxy
operator|->
name|priv
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|frozen
operator|!=
name|image_proxy
operator|->
name|priv
operator|->
name|frozen
condition|)
block|{
name|image_proxy
operator|->
name|priv
operator|->
name|frozen
operator|=
name|frozen
expr_stmt|;
if|if
condition|(
name|frozen
condition|)
block|{
name|gimp_viewable_preview_freeze
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_viewable_preview_thaw
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_proxy_update_bounding_box
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpImageProxy
modifier|*
DECL|function|gimp_image_proxy_new (GimpImage * image)
name|gimp_image_proxy_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_PROXY
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_proxy_get_image (GimpImageProxy * image_proxy)
name|gimp_image_proxy_get_image
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_PROXY
argument_list|(
name|image_proxy
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|image_proxy
operator|->
name|priv
operator|->
name|image
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_proxy_set_show_all (GimpImageProxy * image_proxy,gboolean show_all)
name|gimp_image_proxy_set_show_all
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|,
name|gboolean
name|show_all
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_PROXY
argument_list|(
name|image_proxy
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_all
operator|!=
name|image_proxy
operator|->
name|priv
operator|->
name|show_all
condition|)
block|{
name|image_proxy
operator|->
name|priv
operator|->
name|show_all
operator|=
name|show_all
expr_stmt|;
name|gimp_image_proxy_update_bounding_box
argument_list|(
name|image_proxy
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_image_proxy_get_show_all (GimpImageProxy * image_proxy)
name|gimp_image_proxy_get_show_all
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_PROXY
argument_list|(
name|image_proxy
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|image_proxy
operator|->
name|priv
operator|->
name|show_all
return|;
block|}
end_function

begin_function
name|GeglRectangle
DECL|function|gimp_image_proxy_get_bounding_box (GimpImageProxy * image_proxy)
name|gimp_image_proxy_get_bounding_box
parameter_list|(
name|GimpImageProxy
modifier|*
name|image_proxy
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE_PROXY
argument_list|(
name|image_proxy
argument_list|)
argument_list|,
operator|*
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|image_proxy
operator|->
name|priv
operator|->
name|bounding_box
return|;
block|}
end_function

end_unit

