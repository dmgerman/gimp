begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"paint-types.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_define
DECL|macro|DEFAULT_APPLICATION_MODE
define|#
directive|define
name|DEFAULT_APPLICATION_MODE
value|GIMP_PAINT_CONSTANT
end_define

begin_define
DECL|macro|DEFAULT_HARD
define|#
directive|define
name|DEFAULT_HARD
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_PRESSURE_OPACITY
define|#
directive|define
name|DEFAULT_PRESSURE_OPACITY
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_PRESSURE_HARDNESS
define|#
directive|define
name|DEFAULT_PRESSURE_HARDNESS
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_PRESSURE_RATE
define|#
directive|define
name|DEFAULT_PRESSURE_RATE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_PRESSURE_SIZE
define|#
directive|define
name|DEFAULT_PRESSURE_SIZE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_PRESSURE_COLOR
define|#
directive|define
name|DEFAULT_PRESSURE_COLOR
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_USE_FADE
define|#
directive|define
name|DEFAULT_USE_FADE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_FADE_LENGTH
define|#
directive|define
name|DEFAULT_FADE_LENGTH
value|100.0
end_define

begin_define
DECL|macro|DEFAULT_FADE_UNIT
define|#
directive|define
name|DEFAULT_FADE_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_define
DECL|macro|DEFAULT_USE_GRADIENT
define|#
directive|define
name|DEFAULT_USE_GRADIENT
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_REVERSE
define|#
directive|define
name|DEFAULT_GRADIENT_REVERSE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_REPEAT
define|#
directive|define
name|DEFAULT_GRADIENT_REPEAT
value|GIMP_REPEAT_TRIANGULAR
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_LENGTH
define|#
directive|define
name|DEFAULT_GRADIENT_LENGTH
value|100.0
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_UNIT
define|#
directive|define
name|DEFAULT_GRADIENT_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_enum
enum|enum
DECL|enum|__anon29d497060103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PAINT_INFO
name|PROP_PAINT_INFO
block|,
DECL|enumerator|PROP_APPLICATION_MODE
name|PROP_APPLICATION_MODE
block|,
DECL|enumerator|PROP_HARD
name|PROP_HARD
block|,
DECL|enumerator|PROP_PRESSURE_OPACITY
name|PROP_PRESSURE_OPACITY
block|,
DECL|enumerator|PROP_PRESSURE_HARDNESS
name|PROP_PRESSURE_HARDNESS
block|,
DECL|enumerator|PROP_PRESSURE_RATE
name|PROP_PRESSURE_RATE
block|,
DECL|enumerator|PROP_PRESSURE_SIZE
name|PROP_PRESSURE_SIZE
block|,
DECL|enumerator|PROP_PRESSURE_COLOR
name|PROP_PRESSURE_COLOR
block|,
DECL|enumerator|PROP_USE_FADE
name|PROP_USE_FADE
block|,
DECL|enumerator|PROP_FADE_LENGTH
name|PROP_FADE_LENGTH
block|,
DECL|enumerator|PROP_FADE_UNIT
name|PROP_FADE_UNIT
block|,
DECL|enumerator|PROP_USE_GRADIENT
name|PROP_USE_GRADIENT
block|,
DECL|enumerator|PROP_GRADIENT_REVERSE
name|PROP_GRADIENT_REVERSE
block|,
DECL|enumerator|PROP_GRADIENT_REPEAT
name|PROP_GRADIENT_REPEAT
block|,
DECL|enumerator|PROP_GRADIENT_LENGTH
name|PROP_GRADIENT_LENGTH
block|,
DECL|enumerator|PROP_GRADIENT_UNIT
name|PROP_GRADIENT_UNIT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_paint_options_init
parameter_list|(
name|GimpPaintOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paint_options_class_init
parameter_list|(
name|GimpPaintOptionsClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paint_options_finalize
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
name|gimp_paint_options_set_property
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
name|gimp_paint_options_get_property
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
name|gimp_paint_options_notify
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
name|GimpToolOptionsClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_paint_options_get_type (void)
name|gimp_paint_options_get_type
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
name|GimpPaintOptionsClass
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
name|gimp_paint_options_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPaintOptions
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_paint_options_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TOOL_OPTIONS
argument_list|,
literal|"GimpPaintOptions"
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
DECL|function|gimp_paint_options_class_init (GimpPaintOptionsClass * klass)
name|gimp_paint_options_class_init
parameter_list|(
name|GimpPaintOptionsClass
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
name|gimp_paint_options_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_paint_options_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_paint_options_get_property
expr_stmt|;
name|object_class
operator|->
name|notify
operator|=
name|gimp_paint_options_notify
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PAINT_INFO
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"paint-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PAINT_INFO
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_APPLICATION_MODE
argument_list|,
literal|"application-mode"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PAINT_APPLICATION_MODE
argument_list|,
name|DEFAULT_APPLICATION_MODE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_HARD
argument_list|,
literal|"hard"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_HARD
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PRESSURE_OPACITY
argument_list|,
literal|"pressure-opacity"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_PRESSURE_OPACITY
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PRESSURE_HARDNESS
argument_list|,
literal|"pressure-hardness"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_PRESSURE_HARDNESS
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PRESSURE_RATE
argument_list|,
literal|"pressure-rate"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_PRESSURE_RATE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PRESSURE_SIZE
argument_list|,
literal|"pressure-size"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_PRESSURE_SIZE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_PRESSURE_COLOR
argument_list|,
literal|"pressure-color"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_PRESSURE_COLOR
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_FADE
argument_list|,
literal|"use-fade"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_FADE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FADE_LENGTH
argument_list|,
literal|"fade-length"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|32767.0
argument_list|,
name|DEFAULT_FADE_LENGTH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_FADE_UNIT
argument_list|,
literal|"fade-unit"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|DEFAULT_FADE_UNIT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_GRADIENT
argument_list|,
literal|"use-gradient"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_USE_GRADIENT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_REVERSE
argument_list|,
literal|"gradient-reverse"
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_GRADIENT_REVERSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_REPEAT
argument_list|,
literal|"gradient-repeat"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_REPEAT_MODE
argument_list|,
name|DEFAULT_GRADIENT_REPEAT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_LENGTH
argument_list|,
literal|"gradient-length"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|32767.0
argument_list|,
name|DEFAULT_GRADIENT_LENGTH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_GRADIENT_UNIT
argument_list|,
literal|"gradient-unit"
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|DEFAULT_GRADIENT_UNIT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_options_init (GimpPaintOptions * options)
name|gimp_paint_options_init
parameter_list|(
name|GimpPaintOptions
modifier|*
name|options
parameter_list|)
block|{
name|options
operator|->
name|application_mode_save
operator|=
name|DEFAULT_APPLICATION_MODE
expr_stmt|;
name|options
operator|->
name|pressure_options
operator|=
name|g_new0
argument_list|(
name|GimpPressureOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|fade_options
operator|=
name|g_new0
argument_list|(
name|GimpFadeOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|gradient_options
operator|=
name|g_new0
argument_list|(
name|GimpGradientOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paint_options_finalize (GObject * object)
name|gimp_paint_options_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|paint_info
condition|)
name|g_object_unref
argument_list|(
name|options
operator|->
name|paint_info
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|options
operator|->
name|pressure_options
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|options
operator|->
name|fade_options
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|options
operator|->
name|gradient_options
argument_list|)
expr_stmt|;
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
DECL|function|gimp_paint_options_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_paint_options_set_property
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
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
name|GimpFadeOptions
modifier|*
name|fade_options
decl_stmt|;
name|GimpGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
name|pressure_options
operator|=
name|options
operator|->
name|pressure_options
expr_stmt|;
name|fade_options
operator|=
name|options
operator|->
name|fade_options
expr_stmt|;
name|gradient_options
operator|=
name|options
operator|->
name|gradient_options
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_PAINT_INFO
case|:
name|options
operator|->
name|paint_info
operator|=
operator|(
name|GimpPaintInfo
operator|*
operator|)
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_APPLICATION_MODE
case|:
name|options
operator|->
name|application_mode
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARD
case|:
name|options
operator|->
name|hard
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_OPACITY
case|:
name|pressure_options
operator|->
name|opacity
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_HARDNESS
case|:
name|pressure_options
operator|->
name|hardness
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_RATE
case|:
name|pressure_options
operator|->
name|rate
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_SIZE
case|:
name|pressure_options
operator|->
name|size
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_COLOR
case|:
name|pressure_options
operator|->
name|color
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FADE
case|:
name|fade_options
operator|->
name|use_fade
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_LENGTH
case|:
name|fade_options
operator|->
name|fade_length
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_UNIT
case|:
name|fade_options
operator|->
name|fade_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_GRADIENT
case|:
name|gradient_options
operator|->
name|use_gradient
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REVERSE
case|:
name|gradient_options
operator|->
name|gradient_reverse
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REPEAT
case|:
name|gradient_options
operator|->
name|gradient_repeat
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_LENGTH
case|:
name|gradient_options
operator|->
name|gradient_length
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_UNIT
case|:
name|gradient_options
operator|->
name|gradient_unit
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

begin_function
specifier|static
name|void
DECL|function|gimp_paint_options_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_paint_options_get_property
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
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
name|GimpFadeOptions
modifier|*
name|fade_options
decl_stmt|;
name|GimpGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
name|pressure_options
operator|=
name|options
operator|->
name|pressure_options
expr_stmt|;
name|fade_options
operator|=
name|options
operator|->
name|fade_options
expr_stmt|;
name|gradient_options
operator|=
name|options
operator|->
name|gradient_options
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_PAINT_INFO
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|paint_info
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_APPLICATION_MODE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|application_mode
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARD
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|hard
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_OPACITY
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|pressure_options
operator|->
name|opacity
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_HARDNESS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|pressure_options
operator|->
name|hardness
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_RATE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|pressure_options
operator|->
name|rate
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_SIZE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|pressure_options
operator|->
name|size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PRESSURE_COLOR
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|pressure_options
operator|->
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_FADE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|use_fade
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_LENGTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|fade_length
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FADE_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|fade_options
operator|->
name|fade_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_GRADIENT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gradient_options
operator|->
name|use_gradient
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REVERSE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gradient_options
operator|->
name|gradient_reverse
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_REPEAT
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|gradient_options
operator|->
name|gradient_repeat
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_LENGTH
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|gradient_options
operator|->
name|gradient_length
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GRADIENT_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|gradient_options
operator|->
name|gradient_unit
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
DECL|function|gimp_paint_options_notify (GObject * object,GParamSpec * pspec)
name|gimp_paint_options_notify
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
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|pspec
operator|->
name|param_id
operator|==
name|PROP_USE_GRADIENT
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|gradient_options
operator|->
name|use_gradient
condition|)
block|{
name|options
operator|->
name|application_mode_save
operator|=
name|options
operator|->
name|application_mode
expr_stmt|;
name|options
operator|->
name|application_mode
operator|=
name|GIMP_PAINT_INCREMENTAL
expr_stmt|;
block|}
else|else
block|{
name|options
operator|->
name|application_mode
operator|=
name|options
operator|->
name|application_mode_save
expr_stmt|;
block|}
name|g_object_notify
argument_list|(
name|object
argument_list|,
literal|"application-mode"
argument_list|)
expr_stmt|;
block|}
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
block|}
end_function

begin_function
name|GimpPaintOptions
modifier|*
DECL|function|gimp_paint_options_new (GimpPaintInfo * paint_info)
name|gimp_paint_options_new
parameter_list|(
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|options
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_INFO
argument_list|(
name|paint_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_new
argument_list|(
name|paint_info
operator|->
name|paint_options_type
argument_list|,
literal|"gimp"
argument_list|,
name|paint_info
operator|->
name|gimp
argument_list|,
literal|"paint-info"
argument_list|,
name|paint_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_paint_options_get_fade (GimpPaintOptions * paint_options,GimpImage * gimage,gdouble pixel_dist)
name|gimp_paint_options_get_fade
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|pixel_dist
parameter_list|)
block|{
name|GimpFadeOptions
modifier|*
name|fade_options
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|fade_options
operator|=
name|paint_options
operator|->
name|fade_options
expr_stmt|;
if|if
condition|(
name|fade_options
operator|->
name|use_fade
condition|)
block|{
name|gdouble
name|fade_out
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
switch|switch
condition|(
name|fade_options
operator|->
name|fade_unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
name|fade_out
operator|=
name|fade_options
operator|->
name|fade_length
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_PERCENT
case|:
name|fade_out
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
operator|*
name|fade_options
operator|->
name|fade_length
operator|/
literal|100
operator|)
expr_stmt|;
break|break;
default|default:
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|fade_options
operator|->
name|fade_unit
argument_list|)
expr_stmt|;
name|fade_out
operator|=
operator|(
name|fade_options
operator|->
name|fade_length
operator|*
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|unit_factor
operator|)
expr_stmt|;
break|break;
block|}
comment|/*  factor in the fade out value  */
if|if
condition|(
name|fade_out
operator|>
literal|0.0
condition|)
block|{
name|gdouble
name|x
decl_stmt|;
comment|/*  Model the amount of paint left as a gaussian curve  */
name|x
operator|=
name|pixel_dist
operator|/
name|fade_out
expr_stmt|;
return|return
name|exp
argument_list|(
operator|-
name|x
operator|*
name|x
operator|*
literal|5.541
argument_list|)
return|;
comment|/*  ln (1/255)  */
block|}
return|return
name|GIMP_OPACITY_TRANSPARENT
return|;
block|}
return|return
name|GIMP_OPACITY_OPAQUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_paint_options_get_gradient_color (GimpPaintOptions * paint_options,GimpImage * gimage,gdouble pressure,gdouble pixel_dist,GimpRGB * color)
name|gimp_paint_options_get_gradient_color
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gdouble
name|pressure
parameter_list|,
name|gdouble
name|pixel_dist
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
name|GimpGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pressure_options
operator|=
name|paint_options
operator|->
name|pressure_options
expr_stmt|;
name|gradient_options
operator|=
name|paint_options
operator|->
name|gradient_options
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|pressure_options
operator|->
name|color
condition|)
block|{
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|pressure
argument_list|,
name|gradient_options
operator|->
name|gradient_reverse
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
name|gradient_options
operator|->
name|use_gradient
condition|)
block|{
name|gdouble
name|gradient_length
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|gdouble
name|pos
decl_stmt|;
switch|switch
condition|(
name|gradient_options
operator|->
name|gradient_unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
name|gradient_length
operator|=
name|gradient_options
operator|->
name|gradient_length
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_PERCENT
case|:
name|gradient_length
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
operator|*
name|gradient_options
operator|->
name|gradient_length
operator|/
literal|100
operator|)
expr_stmt|;
break|break;
default|default:
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|gradient_options
operator|->
name|gradient_unit
argument_list|)
expr_stmt|;
name|gradient_length
operator|=
operator|(
name|gradient_options
operator|->
name|gradient_length
operator|*
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|unit_factor
operator|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|gradient_length
operator|>
literal|0.0
condition|)
name|pos
operator|=
name|pixel_dist
operator|/
name|gradient_length
expr_stmt|;
else|else
name|pos
operator|=
literal|1.0
expr_stmt|;
comment|/*  for no repeat, set pos close to 1.0 after the first chunk  */
if|if
condition|(
name|gradient_options
operator|->
name|gradient_repeat
operator|==
name|GIMP_REPEAT_NONE
operator|&&
name|pos
operator|>=
literal|1.0
condition|)
name|pos
operator|=
literal|0.9999999
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|gint
operator|)
name|pos
operator|&
literal|1
operator|)
operator|&&
name|gradient_options
operator|->
name|gradient_repeat
operator|!=
name|GIMP_REPEAT_SAWTOOTH
condition|)
name|pos
operator|=
literal|1.0
operator|-
operator|(
name|pos
operator|-
operator|(
name|gint
operator|)
name|pos
operator|)
expr_stmt|;
else|else
name|pos
operator|=
name|pos
operator|-
operator|(
name|gint
operator|)
name|pos
expr_stmt|;
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|pos
argument_list|,
name|gradient_options
operator|->
name|gradient_reverse
argument_list|,
name|color
argument_list|)
expr_stmt|;
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
name|GimpBrushApplicationMode
DECL|function|gimp_paint_options_get_brush_mode (GimpPaintOptions * paint_options)
name|gimp_paint_options_get_brush_mode
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|GIMP_BRUSH_SOFT
argument_list|)
expr_stmt|;
if|if
condition|(
name|paint_options
operator|->
name|hard
condition|)
return|return
name|GIMP_BRUSH_HARD
return|;
if|if
condition|(
name|paint_options
operator|->
name|pressure_options
operator|->
name|hardness
condition|)
return|return
name|GIMP_BRUSH_PRESSURE
return|;
return|return
name|GIMP_BRUSH_SOFT
return|;
block|}
end_function

end_unit

