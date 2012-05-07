begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimptemplate.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* This file contains the definition of the image template objects.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojection.h"
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

begin_define
DECL|macro|DEFAULT_RESOLUTION
define|#
directive|define
name|DEFAULT_RESOLUTION
value|72.0
end_define

begin_enum
enum|enum
DECL|enum|__anon28a203da0103
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
DECL|enumerator|PROP_BASE_TYPE
name|PROP_BASE_TYPE
block|,
DECL|enumerator|PROP_PRECISION
name|PROP_PRECISION
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

begin_typedef
DECL|typedef|GimpTemplatePrivate
typedef|typedef
name|struct
name|_GimpTemplatePrivate
name|GimpTemplatePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTemplatePrivate
struct|struct
name|_GimpTemplatePrivate
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|xresolution
name|gdouble
name|xresolution
decl_stmt|;
DECL|member|yresolution
name|gdouble
name|yresolution
decl_stmt|;
DECL|member|resolution_unit
name|GimpUnit
name|resolution_unit
decl_stmt|;
DECL|member|base_type
name|GimpImageBaseType
name|base_type
decl_stmt|;
DECL|member|precision
name|GimpPrecision
name|precision
decl_stmt|;
DECL|member|fill_type
name|GimpFillType
name|fill_type
decl_stmt|;
DECL|member|comment
name|gchar
modifier|*
name|comment
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|initial_size
name|guint64
name|initial_size
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (template)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|template
parameter_list|)
value|G_TYPE_INSTANCE_GET_PRIVATE (template, \                                                            GIMP_TYPE_TEMPLATE, \                                                            GimpTemplatePrivate)
end_define

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

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpTemplate,gimp_template,GIMP_TYPE_VIEWABLE,G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,NULL))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpTemplate
argument_list|,
argument|gimp_template
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG, NULL)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_template_parent_class
end_define

begin_function
specifier|static
name|void
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
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
name|GIMP_DEFAULT_IMAGE_WIDTH
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
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
name|GIMP_DEFAULT_IMAGE_HEIGHT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
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
name|GIMP_PARAM_STATIC_STRINGS
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
literal|"The horizontal image resolution."
argument_list|)
argument_list|,
name|DEFAULT_RESOLUTION
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_TEMPLATE_PARAM_COPY_FIRST
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
name|DEFAULT_RESOLUTION
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_TEMPLATE_PARAM_COPY_FIRST
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
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_BASE_TYPE
argument_list|,
literal|"image-type"
argument_list|,
comment|/* serialized name */
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE_BASE_TYPE
argument_list|,
name|GIMP_RGB
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_PRECISION
argument_list|,
literal|"precision"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PRECISION
argument_list|,
name|GIMP_PRECISION_U8
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
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
name|GIMP_PARAM_STATIC_STRINGS
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
name|GIMP_PARAM_STATIC_STRINGS
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
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpTemplatePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_template_init (GimpTemplate * template)
name|gimp_template_init
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{ }
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
name|GimpTemplatePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|comment
condition|)
block|{
name|g_free
argument_list|(
name|private
operator|->
name|comment
argument_list|)
expr_stmt|;
name|private
operator|->
name|comment
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|filename
condition|)
block|{
name|g_free
argument_list|(
name|private
operator|->
name|filename
argument_list|)
expr_stmt|;
name|private
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
name|GimpTemplatePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|private
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
name|private
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
name|private
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
name|private
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
name|private
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
name|private
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
name|PROP_BASE_TYPE
case|:
name|private
operator|->
name|base_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRECISION
case|:
name|private
operator|->
name|precision
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
name|private
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
name|private
operator|->
name|comment
condition|)
name|g_free
argument_list|(
name|private
operator|->
name|comment
argument_list|)
expr_stmt|;
name|private
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
name|private
operator|->
name|filename
condition|)
name|g_free
argument_list|(
name|private
operator|->
name|filename
argument_list|)
expr_stmt|;
name|private
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
name|GimpTemplatePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|private
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
name|private
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
name|private
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
name|private
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
name|private
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
name|private
operator|->
name|resolution_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BASE_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|base_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRECISION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|precision
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
name|private
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
name|private
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
name|private
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
name|GimpTemplatePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint
name|channels
decl_stmt|;
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
name|private
operator|->
name|base_type
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
name|private
operator|->
name|fill_type
operator|==
name|GIMP_TRANSPARENT_FILL
operator|)
comment|/* alpha      */
operator|+
literal|1
comment|/* selection  */
operator|)
expr_stmt|;
comment|/* XXX todo honor precision */
name|private
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
name|private
operator|->
name|width
operator|*
operator|(
name|guint64
operator|)
name|private
operator|->
name|height
operator|)
expr_stmt|;
name|private
operator|->
name|initial_size
operator|+=
name|gimp_projection_estimate_memsize
argument_list|(
name|private
operator|->
name|base_type
argument_list|,
name|private
operator|->
name|width
argument_list|,
name|private
operator|->
name|height
argument_list|)
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
DECL|function|gimp_template_set_from_image (GimpTemplate * template,GimpImage * image)
name|gimp_template_set_from_image
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|gdouble
name|xresolution
decl_stmt|;
name|gdouble
name|yresolution
decl_stmt|;
name|GimpImageBaseType
name|base_type
decl_stmt|;
specifier|const
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
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xresolution
argument_list|,
operator|&
name|yresolution
argument_list|)
expr_stmt|;
name|base_type
operator|=
name|gimp_image_get_base_type
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|base_type
operator|==
name|GIMP_INDEXED
condition|)
name|base_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|image
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
name|image
argument_list|)
argument_list|,
literal|"height"
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
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
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
argument_list|,
literal|"image-type"
argument_list|,
name|base_type
argument_list|,
literal|"precision"
argument_list|,
name|gimp_image_get_precision
argument_list|(
name|image
argument_list|)
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
name|gint
DECL|function|gimp_template_get_width (GimpTemplate * template)
name|gimp_template_get_width
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|width
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_template_get_height (GimpTemplate * template)
name|gimp_template_get_height
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|height
return|;
block|}
end_function

begin_function
name|GimpUnit
DECL|function|gimp_template_get_unit (GimpTemplate * template)
name|gimp_template_get_unit
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|GIMP_UNIT_INCH
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|unit
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_template_get_resolution_x (GimpTemplate * template)
name|gimp_template_get_resolution_x
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|xresolution
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_template_get_resolution_y (GimpTemplate * template)
name|gimp_template_get_resolution_y
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|yresolution
return|;
block|}
end_function

begin_function
name|GimpUnit
DECL|function|gimp_template_get_resolution_unit (GimpTemplate * template)
name|gimp_template_get_resolution_unit
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|GIMP_UNIT_INCH
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|resolution_unit
return|;
block|}
end_function

begin_function
name|GimpImageBaseType
DECL|function|gimp_template_get_base_type (GimpTemplate * template)
name|gimp_template_get_base_type
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|base_type
return|;
block|}
end_function

begin_function
name|GimpPrecision
DECL|function|gimp_template_get_precision (GimpTemplate * template)
name|gimp_template_get_precision
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|GIMP_PRECISION_U8
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|precision
return|;
block|}
end_function

begin_function
name|GimpFillType
DECL|function|gimp_template_get_fill_type (GimpTemplate * template)
name|gimp_template_get_fill_type
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
name|GIMP_NO_FILL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|fill_type
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_template_get_comment (GimpTemplate * template)
name|gimp_template_get_comment
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
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
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|comment
return|;
block|}
end_function

begin_function
name|guint64
DECL|function|gimp_template_get_initial_size (GimpTemplate * template)
name|gimp_template_get_initial_size
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEMPLATE
argument_list|(
name|template
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|template
argument_list|)
operator|->
name|initial_size
return|;
block|}
end_function

end_unit

