begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
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

begin_enum
enum|enum
DECL|enum|__anon2c035bae0103
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
DECL|enumerator|PROP_SIZE
name|PROP_SIZE
block|,
DECL|enumerator|PROP_BORDER
name|PROP_BORDER
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_LETTER_SPACING
name|PROP_LETTER_SPACING
block|,
DECL|enumerator|PROP_LINE_SPACING
name|PROP_LINE_SPACING
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
name|set_property
operator|=
name|gimp_text_set_property
expr_stmt|;
name|param_spec
operator|=
name|g_param_spec_string
argument_list|(
literal|"text"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|PROP_TEXT
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|param_spec
operator|=
name|g_param_spec_string
argument_list|(
literal|"font"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"Sans"
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
name|PROP_FONT
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|param_spec
operator|=
name|g_param_spec_double
argument_list|(
literal|"size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
name|G_MAXFLOAT
argument_list|,
literal|18.0
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
name|PROP_SIZE
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|param_spec
operator|=
name|g_param_spec_double
argument_list|(
literal|"border"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
name|G_MAXFLOAT
argument_list|,
literal|0.0
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
name|param_spec
operator|=
name|gimp_param_spec_unit
argument_list|(
literal|"unit"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_UNIT_PIXEL
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
name|PROP_UNIT
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|param_spec
operator|=
name|g_param_spec_double
argument_list|(
literal|"letter-spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|64.0
argument_list|,
literal|1.0
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
name|PROP_LETTER_SPACING
argument_list|,
name|param_spec
argument_list|)
expr_stmt|;
name|param_spec
operator|=
name|g_param_spec_double
argument_list|(
literal|"line-spacing"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|64.0
argument_list|,
literal|1.0
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
name|PROP_LINE_SPACING
argument_list|,
name|param_spec
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
name|str
condition|)
block|{
name|g_free
argument_list|(
name|text
operator|->
name|str
argument_list|)
expr_stmt|;
name|text
operator|->
name|str
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
name|str
argument_list|)
expr_stmt|;
name|text
operator|->
name|str
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
name|PROP_SIZE
case|:
name|text
operator|->
name|size
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
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|text
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

end_unit

