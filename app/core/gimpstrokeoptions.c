begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpstrokeoptions.c  * Copyright (C) 2003 Simon Budig  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gimpdashpattern.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon295d007d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_METHOD
name|PROP_METHOD
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
DECL|enumerator|PROP_MITER_LIMIT
name|PROP_MITER_LIMIT
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
block|,
DECL|enumerator|PROP_PAINT_OPTIONS
name|PROP_PAINT_OPTIONS
block|,
DECL|enumerator|PROP_EMULATE_DYNAMICS
name|PROP_EMULATE_DYNAMICS
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon295d007d0203
block|{
DECL|enumerator|DASH_INFO_CHANGED
name|DASH_INFO_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpStrokeOptionsPrivate
typedef|typedef
name|struct
name|_GimpStrokeOptionsPrivate
name|GimpStrokeOptionsPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpStrokeOptionsPrivate
struct|struct
name|_GimpStrokeOptionsPrivate
block|{
DECL|member|method
name|GimpStrokeMethod
name|method
decl_stmt|;
comment|/*  options for medhod == LIBART  */
DECL|member|width
name|gdouble
name|width
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|cap_style
name|GimpCapStyle
name|cap_style
decl_stmt|;
DECL|member|join_style
name|GimpJoinStyle
name|join_style
decl_stmt|;
DECL|member|miter_limit
name|gdouble
name|miter_limit
decl_stmt|;
DECL|member|dash_offset
name|gdouble
name|dash_offset
decl_stmt|;
DECL|member|dash_info
name|GArray
modifier|*
name|dash_info
decl_stmt|;
comment|/*  options for method == PAINT_TOOL  */
DECL|member|paint_options
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
DECL|member|emulate_dynamics
name|gboolean
name|emulate_dynamics
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (options)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|options
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (options, \                                      GIMP_TYPE_STROKE_OPTIONS, \                                      GimpStrokeOptionsPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_stroke_options_config_iface_init
parameter_list|(
name|gpointer
name|iface
parameter_list|,
name|gpointer
name|iface_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_stroke_options_finalize
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

begin_function_decl
specifier|static
name|GimpConfig
modifier|*
name|gimp_stroke_options_duplicate
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpStrokeOptions
argument_list|,
argument|gimp_stroke_options
argument_list|,
argument|GIMP_TYPE_FILL_OPTIONS
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_stroke_options_config_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_stroke_options_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpConfigInterface
modifier|*
name|parent_config_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|stroke_options_signals
specifier|static
name|guint
name|stroke_options_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

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
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GParamSpec
modifier|*
name|array_spec
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_stroke_options_finalize
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
name|klass
operator|->
name|dash_info_changed
operator|=
name|NULL
expr_stmt|;
name|stroke_options_signals
index|[
name|DASH_INFO_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dash-info-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpStrokeOptionsClass
argument_list|,
name|dash_info_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_DASH_PRESET
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_METHOD
argument_list|,
literal|"method"
argument_list|,
name|_
argument_list|(
literal|"Method"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_STROKE_METHOD
argument_list|,
name|GIMP_STROKE_LINE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_WIDTH
argument_list|,
literal|"width"
argument_list|,
name|_
argument_list|(
literal|"Line width"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|6.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_UNIT
argument_list|(
name|object_class
argument_list|,
name|PROP_UNIT
argument_list|,
literal|"unit"
argument_list|,
name|_
argument_list|(
literal|"Unit"
argument_list|)
argument_list|,
name|NULL
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
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_CAP_STYLE
argument_list|,
literal|"cap-style"
argument_list|,
name|_
argument_list|(
literal|"Cap style"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CAP_STYLE
argument_list|,
name|GIMP_CAP_BUTT
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_JOIN_STYLE
argument_list|,
literal|"join-style"
argument_list|,
name|_
argument_list|(
literal|"Join style"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_JOIN_STYLE
argument_list|,
name|GIMP_JOIN_MITER
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_MITER_LIMIT
argument_list|,
literal|"miter-limit"
argument_list|,
name|_
argument_list|(
literal|"Miter limit"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Convert a mitered join to a bevelled "
literal|"join if the miter would extend to a "
literal|"distance of more than miter-limit * "
literal|"line-width from the actual join point."
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|10.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_DASH_OFFSET
argument_list|,
literal|"dash-offset"
argument_list|,
name|_
argument_list|(
literal|"Dash offset"
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|2000.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
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
name|GIMP_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DASH_INFO
argument_list|,
name|gimp_param_spec_value_array
argument_list|(
literal|"dash-info"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|array_spec
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_FLAGS
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_PAINT_OPTIONS
argument_list|,
literal|"paint-options"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_EMULATE_DYNAMICS
argument_list|,
literal|"emulate-brush-dynamics"
argument_list|,
name|_
argument_list|(
literal|"Emulate brush dynamics"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|FALSE
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
name|GimpStrokeOptionsPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_config_iface_init (gpointer iface,gpointer iface_data)
name|gimp_stroke_options_config_iface_init
parameter_list|(
name|gpointer
name|iface
parameter_list|,
name|gpointer
name|iface_data
parameter_list|)
block|{
name|GimpConfigInterface
modifier|*
name|config_iface
init|=
operator|(
name|GimpConfigInterface
operator|*
operator|)
name|iface
decl_stmt|;
name|parent_config_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|config_iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_config_iface
condition|)
name|parent_config_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_CONFIG
argument_list|)
expr_stmt|;
name|config_iface
operator|->
name|duplicate
operator|=
name|gimp_stroke_options_duplicate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_init (GimpStrokeOptions * options)
name|gimp_stroke_options_init
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_stroke_options_finalize (GObject * object)
name|gimp_stroke_options_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpStrokeOptionsPrivate
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
name|dash_info
condition|)
block|{
name|gimp_dash_pattern_free
argument_list|(
name|private
operator|->
name|dash_info
argument_list|)
expr_stmt|;
name|private
operator|->
name|dash_info
operator|=
name|NULL
expr_stmt|;
block|}
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|paint_options
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
name|GimpStrokeOptionsPrivate
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
name|PROP_METHOD
case|:
name|private
operator|->
name|method
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
name|private
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
name|PROP_CAP_STYLE
case|:
name|private
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
name|private
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
name|PROP_MITER_LIMIT
case|:
name|private
operator|->
name|miter_limit
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_OFFSET
case|:
name|private
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
name|GimpValueArray
modifier|*
name|value_array
init|=
name|g_value_get_boxed
argument_list|(
name|value
argument_list|)
decl_stmt|;
name|GArray
modifier|*
name|pattern
decl_stmt|;
name|pattern
operator|=
name|gimp_dash_pattern_from_value_array
argument_list|(
name|value_array
argument_list|)
expr_stmt|;
name|gimp_stroke_options_take_dash_pattern
argument_list|(
name|options
argument_list|,
name|GIMP_DASH_CUSTOM
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_PAINT_OPTIONS
case|:
if|if
condition|(
name|private
operator|->
name|paint_options
condition|)
name|g_object_unref
argument_list|(
name|private
operator|->
name|paint_options
argument_list|)
expr_stmt|;
name|private
operator|->
name|paint_options
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EMULATE_DYNAMICS
case|:
name|private
operator|->
name|emulate_dynamics
operator|=
name|g_value_get_boolean
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
name|GimpStrokeOptionsPrivate
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
name|PROP_METHOD
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|method
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
name|private
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
name|private
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
name|private
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
name|private
operator|->
name|join_style
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MITER_LIMIT
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|miter_limit
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
name|private
operator|->
name|dash_offset
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DASH_INFO
case|:
block|{
name|GimpValueArray
modifier|*
name|value_array
decl_stmt|;
name|value_array
operator|=
name|gimp_dash_pattern_to_value_array
argument_list|(
name|private
operator|->
name|dash_info
argument_list|)
expr_stmt|;
name|g_value_take_boxed
argument_list|(
name|value
argument_list|,
name|value_array
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|PROP_PAINT_OPTIONS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|paint_options
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EMULATE_DYNAMICS
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|emulate_dynamics
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
name|GimpConfig
modifier|*
DECL|function|gimp_stroke_options_duplicate (GimpConfig * config)
name|gimp_stroke_options_duplicate
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpStrokeOptions
modifier|*
name|options
init|=
name|GIMP_STROKE_OPTIONS
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GimpStrokeOptionsPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|GimpStrokeOptions
modifier|*
name|new_options
decl_stmt|;
name|new_options
operator|=
name|GIMP_STROKE_OPTIONS
argument_list|(
name|parent_config_iface
operator|->
name|duplicate
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|paint_options
condition|)
block|{
name|GObject
modifier|*
name|paint_options
decl_stmt|;
name|paint_options
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|private
operator|->
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|new_options
argument_list|,
literal|"paint-options"
argument_list|,
name|paint_options
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_CONFIG
argument_list|(
name|new_options
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpStrokeOptions
modifier|*
DECL|function|gimp_stroke_options_new (Gimp * gimp,GimpContext * context,gboolean use_context_color)
name|gimp_stroke_options_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|use_context_color
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
init|=
name|NULL
decl_stmt|;
name|GimpStrokeOptions
modifier|*
name|options
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
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|use_context_color
operator|==
name|FALSE
operator|||
name|context
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
condition|)
name|paint_info
operator|=
name|gimp_context_get_paint_info
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_info
condition|)
name|paint_info
operator|=
name|gimp_paint_info_get_standard
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_STROKE_OPTIONS
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"paint-info"
argument_list|,
name|paint_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_context_color
condition|)
block|{
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_FOREGROUND
operator||
name|GIMP_CONTEXT_PROP_MASK_PATTERN
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
return|return
name|options
return|;
block|}
end_function

begin_function
name|GimpStrokeMethod
DECL|function|gimp_stroke_options_get_method (GimpStrokeOptions * options)
name|gimp_stroke_options_get_method
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_STROKE_LINE
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|method
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_stroke_options_get_width (GimpStrokeOptions * options)
name|gimp_stroke_options_get_width
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|width
return|;
block|}
end_function

begin_function
name|GimpUnit
DECL|function|gimp_stroke_options_get_unit (GimpStrokeOptions * options)
name|gimp_stroke_options_get_unit
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|unit
return|;
block|}
end_function

begin_function
name|GimpCapStyle
DECL|function|gimp_stroke_options_get_cap_style (GimpStrokeOptions * options)
name|gimp_stroke_options_get_cap_style
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_CAP_BUTT
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|cap_style
return|;
block|}
end_function

begin_function
name|GimpJoinStyle
DECL|function|gimp_stroke_options_get_join_style (GimpStrokeOptions * options)
name|gimp_stroke_options_get_join_style
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_JOIN_MITER
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|join_style
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_stroke_options_get_miter_limit (GimpStrokeOptions * options)
name|gimp_stroke_options_get_miter_limit
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|miter_limit
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_stroke_options_get_dash_offset (GimpStrokeOptions * options)
name|gimp_stroke_options_get_dash_offset
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|dash_offset
return|;
block|}
end_function

begin_function
name|GArray
modifier|*
DECL|function|gimp_stroke_options_get_dash_info (GimpStrokeOptions * options)
name|gimp_stroke_options_get_dash_info
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|dash_info
return|;
block|}
end_function

begin_function
name|GimpPaintOptions
modifier|*
DECL|function|gimp_stroke_options_get_paint_options (GimpStrokeOptions * options)
name|gimp_stroke_options_get_paint_options
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|paint_options
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_stroke_options_get_emulate_dynamics (GimpStrokeOptions * options)
name|gimp_stroke_options_get_emulate_dynamics
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
operator|->
name|emulate_dynamics
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_stroke_options_take_dash_pattern:  * @options: a #GimpStrokeOptions object  * @preset: a value out of the #GimpDashPreset enum  * @pattern: a #GArray or %NULL if @preset is not %GIMP_DASH_CUSTOM  *  * Sets the dash pattern. Either a @preset is passed and @pattern is  * %NULL or @preset is %GIMP_DASH_CUSTOM and @pattern is the #GArray  * to use as the dash pattern. Note that this function takes ownership  * of the passed pattern.  */
end_comment

begin_function
name|void
DECL|function|gimp_stroke_options_take_dash_pattern (GimpStrokeOptions * options,GimpDashPreset preset,GArray * pattern)
name|gimp_stroke_options_take_dash_pattern
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpDashPreset
name|preset
parameter_list|,
name|GArray
modifier|*
name|pattern
parameter_list|)
block|{
name|GimpStrokeOptionsPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|preset
operator|==
name|GIMP_DASH_CUSTOM
operator|||
name|pattern
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
name|preset
operator|!=
name|GIMP_DASH_CUSTOM
condition|)
name|pattern
operator|=
name|gimp_dash_pattern_new_from_preset
argument_list|(
name|preset
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|dash_info
condition|)
name|gimp_dash_pattern_free
argument_list|(
name|private
operator|->
name|dash_info
argument_list|)
expr_stmt|;
name|private
operator|->
name|dash_info
operator|=
name|pattern
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"dash-info"
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|options
argument_list|,
name|stroke_options_signals
index|[
name|DASH_INFO_CHANGED
index|]
argument_list|,
literal|0
argument_list|,
name|preset
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_stroke_options_prepare (GimpStrokeOptions * options,GimpContext * context,GimpPaintOptions * paint_options)
name|gimp_stroke_options_prepare
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
block|{
name|GimpStrokeOptionsPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|paint_options
operator|==
name|NULL
operator|||
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|options
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|private
operator|->
name|method
condition|)
block|{
case|case
name|GIMP_STROKE_LINE
case|:
break|break;
case|case
name|GIMP_STROKE_PAINT_METHOD
case|:
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
init|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
operator|->
name|paint_info
decl_stmt|;
if|if
condition|(
name|paint_options
condition|)
block|{
name|g_return_if_fail
argument_list|(
name|paint_info
operator|==
name|paint_options
operator|->
name|paint_info
argument_list|)
expr_stmt|;
comment|/*  undefine the paint-relevant context properties and get them              *  from the passed context              */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_PAINT
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpCoreConfig
modifier|*
name|config
init|=
name|context
operator|->
name|gimp
operator|->
name|config
decl_stmt|;
name|GimpContextPropMask
name|global_props
init|=
literal|0
decl_stmt|;
name|paint_options
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|paint_info
operator|->
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  FG and BG are always shared between all tools  */
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_FOREGROUND
expr_stmt|;
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_brush
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_BRUSH
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_dynamics
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_DYNAMICS
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_pattern
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_PATTERN
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_palette
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_PALETTE
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_gradient
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_font
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_FONT
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|context
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|global_props
argument_list|)
expr_stmt|;
block|}
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"paint-options"
argument_list|,
name|paint_options
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_stroke_options_finish (GimpStrokeOptions * options)
name|gimp_stroke_options_finish
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"paint-options"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

