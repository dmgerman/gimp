begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimptemplate.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28d9d8a80103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_WIDTH
name|PROP_WIDTH
block|,
DECL|enumerator|PROP_HEIGHT
name|PROP_HEIGHT
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_XRESOLUTION
name|PROP_XRESOLUTION
block|,
DECL|enumerator|PROP_YRESOLUTION
name|PROP_YRESOLUTION
block|,
DECL|enumerator|PROP_RESOLUTION_UNIT
name|PROP_RESOLUTION_UNIT
block|,
DECL|enumerator|PROP_IMAGE_TYPE
name|PROP_IMAGE_TYPE
block|,
DECL|enumerator|PROP_FILL_TYPE
name|PROP_FILL_TYPE
block|,
DECL|enumerator|PROP_COMMENT
name|PROP_COMMENT
block|,
DECL|enumerator|PROP_FILENAME
name|PROP_FILENAME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_template_class_init
parameter_list|(
name|GimpTemplateClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_template_finalize
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
name|gimp_template_set_property
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
name|gimp_template_get_property
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
name|gimp_template_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_template_get_type (void)
name|gimp_template_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|template_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|template_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|template_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpTemplateClass
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
name|gimp_template_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpTemplate
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|config_iface_info
init|=
block|{
name|NULL
block|,
comment|/* iface_init     */
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|template_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
literal|"GimpTemplate"
argument_list|,
operator|&
name|template_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|template_type
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|,
operator|&
name|config_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|template_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_class_init (GimpTemplateClass * klass)
name|gimp_template_class_init
parameter_list|(
name|GimpTemplateClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|gimp_template_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_template_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_template_get_property
expr_stmt|;
name|object_class
operator|->
name|notify
operator|=
name|gimp_template_notify
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-template"
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_WIDTH
argument_list|,
literal|"width"
argument_list|,
name|NULL
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|256
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_HEIGHT
argument_list|,
literal|"height"
argument_list|,
name|NULL
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|256
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_UNIT
argument_list|,
literal|"unit"
argument_list|,
name|N_
argument_list|(
literal|"The unit used for coordinate display "
literal|"when not in dot-for-dot mode."
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_RESOLUTION
argument_list|(
name|object_class
argument_list|,
name|PROP_XRESOLUTION
argument_list|,
literal|"xresolution"
argument_list|,
name|N_
argument_list|(
literal|"The horizonal image resolution."
argument_list|)
argument_list|,
literal|72.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_RESOLUTION
argument_list|(
name|object_class
argument_list|,
name|PROP_YRESOLUTION
argument_list|,
literal|"yresolution"
argument_list|,
name|N_
argument_list|(
literal|"The vertical image resolution."
argument_list|)
argument_list|,
literal|72.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_RESOLUTION_UNIT
argument_list|,
literal|"resolution-unit"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_INCH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE_TYPE
argument_list|,
literal|"image-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_BASE_TYPE
argument_list|,
name|GIMP_RGB
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_FILL_TYPE
argument_list|,
literal|"fill-type"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_FILL_TYPE
argument_list|,
name|GIMP_BACKGROUND_FILL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_COMMENT
argument_list|,
literal|"comment"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_FILENAME
argument_list|,
literal|"filename"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_finalize (GObject * object)
name|gimp_template_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
init|=
name|GIMP_TEMPLATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|template
operator|->
name|comment
condition|)
block|{
name|g_free
argument_list|(
name|template
operator|->
name|comment
argument_list|)
expr_stmt|;
name|template
operator|->
name|comment
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|template
operator|->
name|filename
condition|)
block|{
name|g_free
argument_list|(
name|template
operator|->
name|filename
argument_list|)
expr_stmt|;
name|template
operator|->
name|filename
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
DECL|function|gimp_template_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_template_set_property
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
name|GimpTemplate
modifier|*
name|template
init|=
name|GIMP_TEMPLATE
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
name|PROP_WIDTH
case|:
name|template
operator|->
name|width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|template
operator|->
name|height
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|template
operator|->
name|unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XRESOLUTION
case|:
name|template
operator|->
name|xresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YRESOLUTION
case|:
name|template
operator|->
name|yresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESOLUTION_UNIT
case|:
name|template
operator|->
name|resolution_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE_TYPE
case|:
name|template
operator|->
name|image_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_TYPE
case|:
name|template
operator|->
name|fill_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COMMENT
case|:
if|if
condition|(
name|template
operator|->
name|comment
condition|)
name|g_free
argument_list|(
name|template
operator|->
name|comment
argument_list|)
expr_stmt|;
name|template
operator|->
name|comment
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILENAME
case|:
if|if
condition|(
name|template
operator|->
name|filename
condition|)
name|g_free
argument_list|(
name|template
operator|->
name|filename
argument_list|)
expr_stmt|;
name|template
operator|->
name|filename
operator|=
name|g_value_dup_string
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_template_get_property
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
name|GimpTemplate
modifier|*
name|template
init|=
name|GIMP_TEMPLATE
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
name|PROP_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|xresolution
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|yresolution
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESOLUTION_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|resolution_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|image_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILL_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|fill_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COMMENT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|comment
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILENAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|template
operator|->
name|filename
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
DECL|function|gimp_template_notify (GObject * object,GParamSpec * pspec)
name|gimp_template_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|gint
name|channels
decl_stmt|;
name|template
operator|=
name|GIMP_TEMPLATE
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|notify
condition|)
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|notify
argument_list|(
name|object
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
name|channels
operator|=
operator|(
operator|(
name|template
operator|->
name|image_type
operator|==
name|GIMP_RGB
condition|?
literal|3
else|:
literal|1
operator|)
comment|/* color      */
operator|+
operator|(
name|template
operator|->
name|fill_type
operator|==
name|GIMP_TRANSPARENT_FILL
operator|)
comment|/* alpha      */
operator|+
literal|1
comment|/* selection  */
operator|+
operator|(
name|template
operator|->
name|image_type
operator|==
name|GIMP_RGB
condition|?
literal|4
else|:
literal|2
operator|)
comment|/* projection */
operator|)
expr_stmt|;
name|template
operator|->
name|initial_size
operator|=
operator|(
operator|(
name|guint64
operator|)
name|channels
operator|*
operator|(
name|guint64
operator|)
name|template
operator|->
name|width
operator|*
operator|(
name|guint64
operator|)
name|template
operator|->
name|height
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"stock-id"
argument_list|)
condition|)
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpTemplate
modifier|*
DECL|function|gimp_template_new (const gchar * name)
name|gimp_template_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEMPLATE
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_template_set_from_image (GimpTemplate * template,GimpImage * gimage)
name|gimp_template_set_from_image
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|gdouble
name|xresolution
decl_stmt|;
name|gdouble
name|yresolution
decl_stmt|;
name|GimpImageBaseType
name|image_type
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gchar
modifier|*
name|comment
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|gimage
argument_list|,
operator|&
name|xresolution
argument_list|,
operator|&
name|yresolution
argument_list|)
expr_stmt|;
name|image_type
operator|=
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_type
operator|==
name|GIMP_INDEXED
condition|)
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|gimage
argument_list|,
literal|"gimp-comment"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
name|comment
operator|=
name|g_strndup
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|template
argument_list|,
literal|"width"
argument_list|,
name|gimp_image_get_width
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"height"
argument_list|,
name|gimp_image_get_height
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"unit"
argument_list|,
name|gimp_image_get_unit
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"xresolution"
argument_list|,
name|xresolution
argument_list|,
literal|"yresolution"
argument_list|,
name|yresolution
argument_list|,
literal|"resolution-unit"
argument_list|,
name|gimage
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_image
operator|->
name|resolution_unit
argument_list|,
literal|"image-type"
argument_list|,
name|image_type
argument_list|,
literal|"comment"
argument_list|,
name|comment
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|comment
condition|)
name|g_free
argument_list|(
name|comment
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_template_create_image (Gimp * gimp,GimpTemplate * template,GimpContext * context)
name|gimp_template_create_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpImageType
name|type
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_create_image
argument_list|(
name|gimp
argument_list|,
name|template
operator|->
name|width
argument_list|,
name|template
operator|->
name|height
argument_list|,
name|template
operator|->
name|image_type
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
operator|->
name|comment
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|template
operator|->
name|comment
argument_list|)
operator|+
literal|1
argument_list|,
name|template
operator|->
name|comment
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|gimage
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
name|gimp_image_set_resolution
argument_list|(
name|gimage
argument_list|,
name|template
operator|->
name|xresolution
argument_list|,
name|template
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|gimage
argument_list|,
name|template
operator|->
name|unit
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|template
operator|->
name|fill_type
condition|)
block|{
case|case
name|GIMP_TRANSPARENT_FILL
case|:
name|type
operator|=
operator|(
operator|(
name|template
operator|->
name|image_type
operator|==
name|GIMP_RGB
operator|)
condition|?
name|GIMP_RGBA_IMAGE
else|:
name|GIMP_GRAYA_IMAGE
operator|)
expr_stmt|;
break|break;
default|default:
name|type
operator|=
operator|(
operator|(
name|template
operator|->
name|image_type
operator|==
name|GIMP_RGB
operator|)
condition|?
name|GIMP_RGB_IMAGE
else|:
name|GIMP_GRAY_IMAGE
operator|)
expr_stmt|;
break|break;
block|}
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|gimage
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_by_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|context
argument_list|,
name|template
operator|->
name|fill_type
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_clean_all
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|gimage
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|gimage
return|;
block|}
end_function

end_unit

