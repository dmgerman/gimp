begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"libgimpbase/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"text/text-types.h"
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
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bb68c010103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TEXT
name|PROP_TEXT
block|,
DECL|enumerator|PROP_FONT
name|PROP_FONT
block|,
DECL|enumerator|PROP_FONT_SIZE
name|PROP_FONT_SIZE
block|,
DECL|enumerator|PROP_FONT_SIZE_UNIT
name|PROP_FONT_SIZE_UNIT
block|,
DECL|enumerator|PROP_LANGUAGE
name|PROP_LANGUAGE
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
block|,
DECL|enumerator|PROP_FIXED_WIDTH
name|PROP_FIXED_WIDTH
block|,
DECL|enumerator|PROP_JUSTIFICATION
name|PROP_JUSTIFICATION
block|,
DECL|enumerator|PROP_INDENTATION
name|PROP_INDENTATION
block|,
DECL|enumerator|PROP_LINE_SPACING
name|PROP_LINE_SPACING
block|,
DECL|enumerator|PROP_LETTER_SPACING
name|PROP_LETTER_SPACING
block|,
DECL|enumerator|PROP_BORDER
name|PROP_BORDER
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_text_class_init
parameter_list|(
name|GimpTextClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_finalize
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
name|gimp_text_get_property
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
name|gimp_text_set_property
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
name|gchar
modifier|*
name|gimp_text_get_default_language
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_text_get_type (void)
name|gimp_text_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|text_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|text_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|text_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpTextClass
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
name|gimp_text_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpText
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
name|text_iface_info
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
name|text_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_OBJECT
argument_list|,
literal|"GimpText"
argument_list|,
operator|&
name|text_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|text_type
argument_list|,
name|GIMP_TYPE_CONFIG_INTERFACE
argument_list|,
operator|&
name|text_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|text_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_class_init (GimpTextClass * klass)
name|gimp_text_class_init
parameter_list|(
name|GimpTextClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GParamSpec
modifier|*
name|param_spec
decl_stmt|;
name|GimpRGB
name|black
decl_stmt|;
name|gchar
modifier|*
name|language
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
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
name|gimp_text_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_text_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_text_set_property
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|black
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|language
operator|=
name|gimp_text_get_default_language
argument_list|()
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_TEXT
argument_list|,
literal|"text"
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
name|PROP_FONT
argument_list|,
literal|"font"
argument_list|,
name|NULL
argument_list|,
literal|"Sans"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FONT_SIZE
argument_list|,
literal|"font-size"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|8192.0
argument_list|,
literal|18.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_FONT_SIZE_UNIT
argument_list|,
literal|"font-size-unit"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_LANGUAGE
argument_list|,
literal|"language"
argument_list|,
name|NULL
argument_list|,
name|language
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_COLOR
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR
argument_list|,
literal|"color"
argument_list|,
name|NULL
argument_list|,
operator|&
name|black
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_FIXED_WIDTH
argument_list|,
literal|"fixed-width"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_JUSTIFICATION
argument_list|,
literal|"justify"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TEXT_JUSTIFICATION
argument_list|,
name|GIMP_TEXT_JUSTIFY_LEFT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_INDENTATION
argument_list|,
literal|"indent"
argument_list|,
name|N_
argument_list|(
literal|"How many pixels the "
literal|"first line should be shorter"
argument_list|)
argument_list|,
operator|-
literal|8192.0
argument_list|,
literal|8192.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_LINE_SPACING
argument_list|,
literal|"line-spacing"
argument_list|,
name|N_
argument_list|(
literal|"Additional line spacing (in pixels)"
argument_list|)
argument_list|,
operator|-
literal|8192.0
argument_list|,
literal|8192.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_LETTER_SPACING
argument_list|,
literal|"letter-spacing"
argument_list|,
name|NULL
argument_list|,
operator|-
literal|8192.0
argument_list|,
literal|8192.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  border does only exist to implement the old text API  */
name|param_spec
operator|=
name|g_param_spec_int
argument_list|(
literal|"border"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|G_PARAM_CONSTRUCT
operator||
name|G_PARAM_WRITABLE
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_BORDER
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|language
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_finalize (GObject * object)
name|gimp_text_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|text
operator|->
name|text
condition|)
block|{
name|g_free
argument_list|(
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
name|text
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|text
operator|->
name|font
condition|)
block|{
name|g_free
argument_list|(
name|text
operator|->
name|font
argument_list|)
expr_stmt|;
name|text
operator|->
name|font
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|text
operator|->
name|language
condition|)
block|{
name|g_free
argument_list|(
name|text
operator|->
name|language
argument_list|)
expr_stmt|;
name|text
operator|->
name|language
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
DECL|function|gimp_text_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_text_get_property
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
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
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
name|PROP_TEXT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|font
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT_SIZE
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|font_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT_SIZE_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|font_size_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LANGUAGE
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|language
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
operator|&
name|text
operator|->
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FIXED_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|fixed_width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JUSTIFICATION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|justify
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INDENTATION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|indent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LINE_SPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|line_spacing
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LETTER_SPACING
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|text
operator|->
name|letter_spacing
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
DECL|function|gimp_text_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_text_set_property
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
name|GimpText
modifier|*
name|text
init|=
name|GIMP_TEXT
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpRGB
modifier|*
name|color
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_TEXT
case|:
name|g_free
argument_list|(
name|text
operator|->
name|text
argument_list|)
expr_stmt|;
name|text
operator|->
name|text
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT
case|:
name|g_free
argument_list|(
name|text
operator|->
name|font
argument_list|)
expr_stmt|;
name|text
operator|->
name|font
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT_SIZE
case|:
name|text
operator|->
name|font_size
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FONT_SIZE_UNIT
case|:
name|text
operator|->
name|font_size_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LANGUAGE
case|:
name|g_free
argument_list|(
name|text
operator|->
name|language
argument_list|)
expr_stmt|;
name|text
operator|->
name|language
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR
case|:
name|color
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|text
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
break|break;
case|case
name|PROP_FIXED_WIDTH
case|:
name|text
operator|->
name|fixed_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JUSTIFICATION
case|:
name|text
operator|->
name|justify
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INDENTATION
case|:
name|text
operator|->
name|indent
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LINE_SPACING
case|:
name|text
operator|->
name|line_spacing
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LETTER_SPACING
case|:
name|text
operator|->
name|letter_spacing
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_BORDER
case|:
name|text
operator|->
name|border
operator|=
name|g_value_get_int
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

begin_comment
comment|/*   *  basically copied from gtk_get_default_language()  */
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_text_get_default_language (void)
name|gimp_text_get_default_language
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|lang
decl_stmt|;
name|gchar
modifier|*
name|p
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|p
operator|=
name|getenv
argument_list|(
literal|"LC_ALL"
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
name|lang
operator|=
name|g_strdup
argument_list|(
name|p
argument_list|)
expr_stmt|;
else|else
block|{
name|p
operator|=
name|getenv
argument_list|(
literal|"LANG"
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
name|lang
operator|=
name|g_strdup
argument_list|(
name|p
argument_list|)
expr_stmt|;
else|else
block|{
name|p
operator|=
name|getenv
argument_list|(
literal|"LC_CTYPE"
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|!=
name|NULL
condition|)
name|lang
operator|=
name|g_strdup
argument_list|(
name|p
argument_list|)
expr_stmt|;
else|else
name|lang
operator|=
name|g_win32_getlocale
argument_list|()
expr_stmt|;
block|}
block|}
else|#
directive|else
name|lang
operator|=
name|g_strdup
argument_list|(
name|setlocale
argument_list|(
name|LC_CTYPE
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|p
operator|=
name|strchr
argument_list|(
name|lang
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|p
operator|=
name|strchr
argument_list|(
name|lang
argument_list|,
literal|'@'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
return|return
name|lang
return|;
block|}
end_function

end_unit

