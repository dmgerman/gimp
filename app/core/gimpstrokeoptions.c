begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpstrokeoptions.c  * Copyright (C) 2003 Simon Budig  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"config/gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpstrokeoptions.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29fbfb3d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_STYLE
name|PROP_STYLE
block|,
DECL|enumerator|PROP_WIDTH
name|PROP_WIDTH
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_CAP_STYLE
name|PROP_CAP_STYLE
block|,
DECL|enumerator|PROP_JOIN_STYLE
name|PROP_JOIN_STYLE
block|,
DECL|enumerator|PROP_MITER
name|PROP_MITER
block|,
DECL|enumerator|PROP_ANTIALIAS
name|PROP_ANTIALIAS
block|,
DECL|enumerator|PROP_DASH_UNIT
name|PROP_DASH_UNIT
block|,
DECL|enumerator|PROP_DASH_OFFSET
name|PROP_DASH_OFFSET
block|,
DECL|enumerator|PROP_DASH_INFO
name|PROP_DASH_INFO
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_stroke_options_class_init
parameter_list|(
name|GimpStrokeOptionsClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_stroke_options_set_property
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
name|gimp_stroke_options_get_property
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpContextClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_stroke_options_get_type (void)
name|gimp_stroke_options_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpStrokeOptionsClass
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
name|gimp_stroke_options_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpStrokeOptions
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_CONTEXT
argument_list|,
literal|"GimpStrokeOptions"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_class_init (GimpStrokeOptionsClass * klass)
name|gimp_stroke_options_class_init
parameter_list|(
name|GimpStrokeOptionsClass
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
name|array_spec
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
name|set_property
operator|=
name|gimp_stroke_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_stroke_options_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_STYLE
argument_list|,
literal|"style"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_STROKE_STYLE
argument_list|,
name|GIMP_STROKE_STYLE_SOLID
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_WIDTH
argument_list|,
literal|"width"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|5.0
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
name|NULL
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
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CAP_STYLE
argument_list|,
literal|"cap-style"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CAP_STYLE
argument_list|,
name|GIMP_CAP_BUTT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_JOIN_STYLE
argument_list|,
literal|"join-style"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_JOIN_STYLE
argument_list|,
name|GIMP_JOIN_MITER
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_MITER
argument_list|,
literal|"miter"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ANTIALIAS
argument_list|,
literal|"antialias"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_DASH_OFFSET
argument_list|,
literal|"dash-offset"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|array_spec
operator|=
name|g_param_spec_double
argument_list|(
literal|"dash-length"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|1.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DASH_INFO
argument_list|,
name|g_param_spec_value_array
argument_list|(
literal|"dash-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|array_spec
argument_list|,
name|GIMP_CONFIG_PARAM_FLAGS
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_stroke_options_set_property
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
name|GimpStrokeOptions
modifier|*
name|options
init|=
name|GIMP_STROKE_OPTIONS
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
name|PROP_STYLE
case|:
name|options
operator|->
name|style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|options
operator|->
name|width
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
name|options
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
name|PROP_CAP_STYLE
case|:
name|options
operator|->
name|cap_style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JOIN_STYLE
case|:
name|options
operator|->
name|join_style
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MITER
case|:
name|options
operator|->
name|miter
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANTIALIAS
case|:
name|options
operator|->
name|antialias
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_OFFSET
case|:
name|options
operator|->
name|dash_offset
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_INFO
case|:
block|{
name|GValueArray
modifier|*
name|val_array
decl_stmt|;
name|GValue
modifier|*
name|item
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gdouble
name|val
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|dash_info
condition|)
name|g_array_free
argument_list|(
name|options
operator|->
name|dash_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|val_array
operator|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|val_array
operator|==
name|NULL
operator|||
name|val_array
operator|->
name|n_values
operator|==
literal|0
condition|)
block|{
name|options
operator|->
name|dash_info
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|options
operator|->
name|dash_info
operator|=
name|g_array_sized_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|,
name|val_array
operator|->
name|n_values
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
name|val_array
operator|->
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|item
operator|=
name|g_value_array_get_nth
argument_list|(
name|val_array
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_VALUE_HOLDS_DOUBLE
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|val
operator|=
name|g_value_get_double
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|options
operator|->
name|dash_info
operator|=
name|g_array_append_val
argument_list|(
name|options
operator|->
name|dash_info
argument_list|,
name|val
argument_list|)
expr_stmt|;
block|}
block|}
block|}
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
DECL|function|gimp_stroke_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_stroke_options_get_property
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
name|GimpStrokeOptions
modifier|*
name|options
init|=
name|GIMP_STROKE_OPTIONS
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
name|PROP_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_WIDTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|width
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
name|options
operator|->
name|unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CAP_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|cap_style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JOIN_STYLE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|join_style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MITER
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|miter
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANTIALIAS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|antialias
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_OFFSET
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|dash_offset
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_INFO
case|:
block|{
name|GValueArray
modifier|*
name|val_array
decl_stmt|;
name|GValue
name|item
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|dash_info
condition|)
name|g_array_free
argument_list|(
name|options
operator|->
name|dash_info
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|dash_info
operator|==
name|NULL
operator|||
name|options
operator|->
name|dash_info
operator|->
name|len
operator|==
literal|0
condition|)
block|{
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|val_array
operator|=
name|g_value_array_new
argument_list|(
name|options
operator|->
name|dash_info
operator|->
name|len
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
name|options
operator|->
name|dash_info
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|g_value_set_double
argument_list|(
operator|&
name|item
argument_list|,
name|g_array_index
argument_list|(
name|options
operator|->
name|dash_info
argument_list|,
name|gdouble
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_array_append
argument_list|(
name|val_array
argument_list|,
operator|&
name|item
argument_list|)
expr_stmt|;
block|}
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|val_array
argument_list|)
expr_stmt|;
block|}
block|}
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

