begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
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
file|"gimpcurve.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamics-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamics-save.h"
end_include

begin_include
include|#
directive|include
file|"gimpdynamicsoutput.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_NAME
define|#
directive|define
name|DEFAULT_NAME
value|"Nameless dynamics"
end_define

begin_enum
enum|enum
DECL|enum|__anon28a262d10103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_NAME
name|PROP_NAME
block|,
DECL|enumerator|PROP_OPACITY_OUTPUT
name|PROP_OPACITY_OUTPUT
block|,
DECL|enumerator|PROP_SIZE_OUTPUT
name|PROP_SIZE_OUTPUT
block|,
DECL|enumerator|PROP_ANGLE_OUTPUT
name|PROP_ANGLE_OUTPUT
block|,
DECL|enumerator|PROP_COLOR_OUTPUT
name|PROP_COLOR_OUTPUT
block|,
DECL|enumerator|PROP_FORCE_OUTPUT
name|PROP_FORCE_OUTPUT
block|,
DECL|enumerator|PROP_HARDNESS_OUTPUT
name|PROP_HARDNESS_OUTPUT
block|,
DECL|enumerator|PROP_ASPECT_RATIO_OUTPUT
name|PROP_ASPECT_RATIO_OUTPUT
block|,
DECL|enumerator|PROP_SPACING_OUTPUT
name|PROP_SPACING_OUTPUT
block|,
DECL|enumerator|PROP_RATE_OUTPUT
name|PROP_RATE_OUTPUT
block|,
DECL|enumerator|PROP_FLOW_OUTPUT
name|PROP_FLOW_OUTPUT
block|,
DECL|enumerator|PROP_JITTER_OUTPUT
name|PROP_JITTER_OUTPUT
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpDynamicsPrivate
typedef|typedef
name|struct
name|_GimpDynamicsPrivate
name|GimpDynamicsPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicsPrivate
struct|struct
name|_GimpDynamicsPrivate
block|{
DECL|member|opacity_output
name|GimpDynamicsOutput
modifier|*
name|opacity_output
decl_stmt|;
DECL|member|hardness_output
name|GimpDynamicsOutput
modifier|*
name|hardness_output
decl_stmt|;
DECL|member|force_output
name|GimpDynamicsOutput
modifier|*
name|force_output
decl_stmt|;
DECL|member|rate_output
name|GimpDynamicsOutput
modifier|*
name|rate_output
decl_stmt|;
DECL|member|flow_output
name|GimpDynamicsOutput
modifier|*
name|flow_output
decl_stmt|;
DECL|member|size_output
name|GimpDynamicsOutput
modifier|*
name|size_output
decl_stmt|;
DECL|member|aspect_ratio_output
name|GimpDynamicsOutput
modifier|*
name|aspect_ratio_output
decl_stmt|;
DECL|member|color_output
name|GimpDynamicsOutput
modifier|*
name|color_output
decl_stmt|;
DECL|member|angle_output
name|GimpDynamicsOutput
modifier|*
name|angle_output
decl_stmt|;
DECL|member|jitter_output
name|GimpDynamicsOutput
modifier|*
name|jitter_output
decl_stmt|;
DECL|member|spacing_output
name|GimpDynamicsOutput
modifier|*
name|spacing_output
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (output)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|output
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (output, \                                      GIMP_TYPE_DYNAMICS, \                                      GimpDynamicsPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_finalize
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
name|gimp_dynamics_set_property
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
name|gimp_dynamics_get_property
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
name|gimp_dynamics_dispatch_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_dynamics_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpData
modifier|*
name|gimp_dynamics_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpDynamicsOutput
modifier|*
name|gimp_dynamics_create_output
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDynamicsOutputType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_output_notify
parameter_list|(
name|GObject
modifier|*
name|output
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDynamics,gimp_dynamics,GIMP_TYPE_DATA)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDynamics
argument_list|,
argument|gimp_dynamics
argument_list|,
argument|GIMP_TYPE_DATA
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dynamics_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_dynamics_class_init
parameter_list|(
name|GimpDynamicsClass
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
name|GimpDataClass
modifier|*
name|data_class
init|=
name|GIMP_DATA_CLASS
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
name|gimp_dynamics_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_dynamics_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_dynamics_get_property
expr_stmt|;
name|object_class
operator|->
name|dispatch_properties_changed
operator|=
name|gimp_dynamics_dispatch_properties_changed
expr_stmt|;
name|viewable_class
operator|->
name|default_icon_name
operator|=
literal|"gimp-dynamics"
expr_stmt|;
name|data_class
operator|->
name|save
operator|=
name|gimp_dynamics_save
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_dynamics_get_extension
expr_stmt|;
name|data_class
operator|->
name|duplicate
operator|=
name|gimp_dynamics_duplicate
expr_stmt|;
name|GIMP_CONFIG_PROP_STRING
argument_list|(
name|object_class
argument_list|,
name|PROP_NAME
argument_list|,
literal|"name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|DEFAULT_NAME
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_OPACITY_OUTPUT
argument_list|,
literal|"opacity-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_FORCE_OUTPUT
argument_list|,
literal|"force-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_HARDNESS_OUTPUT
argument_list|,
literal|"hardness-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_RATE_OUTPUT
argument_list|,
literal|"rate-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_FLOW_OUTPUT
argument_list|,
literal|"flow-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_SIZE_OUTPUT
argument_list|,
literal|"size-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_ASPECT_RATIO_OUTPUT
argument_list|,
literal|"aspect-ratio-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_COLOR_OUTPUT
argument_list|,
literal|"color-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_ANGLE_OUTPUT
argument_list|,
literal|"angle-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_JITTER_OUTPUT
argument_list|,
literal|"jitter-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_OBJECT
argument_list|(
name|object_class
argument_list|,
name|PROP_SPACING_OUTPUT
argument_list|,
literal|"spacing-output"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DYNAMICS_OUTPUT
argument_list|,
name|GIMP_CONFIG_PARAM_AGGREGATE
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpDynamicsPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_init (GimpDynamics * dynamics)
name|gimp_dynamics_init
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|)
block|{
name|GimpDynamicsPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|dynamics
argument_list|)
decl_stmt|;
name|private
operator|->
name|opacity_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"opacity-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_OPACITY
argument_list|)
expr_stmt|;
name|private
operator|->
name|force_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"force-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FORCE
argument_list|)
expr_stmt|;
name|private
operator|->
name|hardness_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"hardness-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_HARDNESS
argument_list|)
expr_stmt|;
name|private
operator|->
name|rate_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"rate-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_RATE
argument_list|)
expr_stmt|;
name|private
operator|->
name|flow_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"flow-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_FLOW
argument_list|)
expr_stmt|;
name|private
operator|->
name|size_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"size-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_SIZE
argument_list|)
expr_stmt|;
name|private
operator|->
name|aspect_ratio_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"aspect-ratio-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_ASPECT_RATIO
argument_list|)
expr_stmt|;
name|private
operator|->
name|color_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"color-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_COLOR
argument_list|)
expr_stmt|;
name|private
operator|->
name|angle_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"angle-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_ANGLE
argument_list|)
expr_stmt|;
name|private
operator|->
name|jitter_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"jitter-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_JITTER
argument_list|)
expr_stmt|;
name|private
operator|->
name|spacing_output
operator|=
name|gimp_dynamics_create_output
argument_list|(
name|dynamics
argument_list|,
literal|"spacing-output"
argument_list|,
name|GIMP_DYNAMICS_OUTPUT_SPACING
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_finalize (GObject * object)
name|gimp_dynamics_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDynamicsPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|opacity_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|force_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|hardness_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|rate_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|flow_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|size_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|aspect_ratio_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|color_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|angle_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|jitter_output
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|spacing_output
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
DECL|function|gimp_dynamics_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_dynamics_set_property
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
name|GimpDynamicsPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpDynamicsOutput
modifier|*
name|src_output
init|=
name|NULL
decl_stmt|;
name|GimpDynamicsOutput
modifier|*
name|dest_output
init|=
name|NULL
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_NAME
case|:
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|g_value_get_string
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPACITY_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|opacity_output
expr_stmt|;
break|break;
case|case
name|PROP_FORCE_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|force_output
expr_stmt|;
break|break;
case|case
name|PROP_HARDNESS_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|hardness_output
expr_stmt|;
break|break;
case|case
name|PROP_RATE_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|rate_output
expr_stmt|;
break|break;
case|case
name|PROP_FLOW_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|flow_output
expr_stmt|;
break|break;
case|case
name|PROP_SIZE_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|size_output
expr_stmt|;
break|break;
case|case
name|PROP_ASPECT_RATIO_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|aspect_ratio_output
expr_stmt|;
break|break;
case|case
name|PROP_COLOR_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|color_output
expr_stmt|;
break|break;
case|case
name|PROP_ANGLE_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|angle_output
expr_stmt|;
break|break;
case|case
name|PROP_JITTER_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|jitter_output
expr_stmt|;
break|break;
case|case
name|PROP_SPACING_OUTPUT
case|:
name|src_output
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|dest_output
operator|=
name|private
operator|->
name|spacing_output
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
if|if
condition|(
name|src_output
operator|&&
name|dest_output
condition|)
block|{
name|gimp_config_copy
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|src_output
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|dest_output
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_dynamics_get_property
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
name|GimpDynamicsPrivate
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
name|PROP_NAME
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_OPACITY_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|opacity_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FORCE_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|force_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HARDNESS_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|hardness_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RATE_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|rate_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FLOW_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|flow_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SIZE_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|size_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ASPECT_RATIO_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|aspect_ratio_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_COLOR_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|color_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ANGLE_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|angle_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_JITTER_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|jitter_output
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SPACING_OUTPUT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|spacing_output
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
DECL|function|gimp_dynamics_dispatch_properties_changed (GObject * object,guint n_pspecs,GParamSpec ** pspecs)
name|gimp_dynamics_dispatch_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispatch_properties_changed
argument_list|(
name|object
argument_list|,
name|n_pspecs
argument_list|,
name|pspecs
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
name|n_pspecs
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|pspecs
index|[
name|i
index|]
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
condition|)
block|{
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_dynamics_get_extension (GimpData * data)
name|gimp_dynamics_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_DYNAMICS_FILE_EXTENSION
return|;
block|}
end_function

begin_function
specifier|static
name|GimpData
modifier|*
DECL|function|gimp_dynamics_duplicate (GimpData * data)
name|gimp_dynamics_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpData
modifier|*
name|dest
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DYNAMICS
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gimp_config_copy
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|dest
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpData
modifier|*
DECL|function|gimp_dynamics_new (GimpContext * context,const gchar * name)
name|gimp_dynamics_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
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
name|g_return_val_if_fail
argument_list|(
name|name
index|[
literal|0
index|]
operator|!=
literal|'\0'
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DYNAMICS
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
name|GimpData
modifier|*
DECL|function|gimp_dynamics_get_standard (GimpContext * context)
name|gimp_dynamics_get_standard
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
specifier|static
name|GimpData
modifier|*
name|standard_dynamics
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_dynamics
condition|)
block|{
name|standard_dynamics
operator|=
name|gimp_dynamics_new
argument_list|(
name|context
argument_list|,
literal|"Standard dynamics"
argument_list|)
expr_stmt|;
name|gimp_data_clean
argument_list|(
name|standard_dynamics
argument_list|)
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|standard_dynamics
argument_list|,
literal|"gimp-dynamics-standard"
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|standard_dynamics
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|standard_dynamics
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_dynamics
return|;
block|}
end_function

begin_function
name|GimpDynamicsOutput
modifier|*
DECL|function|gimp_dynamics_get_output (GimpDynamics * dynamics,GimpDynamicsOutputType type_id)
name|gimp_dynamics_get_output
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type_id
parameter_list|)
block|{
name|GimpDynamicsPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS
argument_list|(
name|dynamics
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|dynamics
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type_id
condition|)
block|{
case|case
name|GIMP_DYNAMICS_OUTPUT_OPACITY
case|:
return|return
name|private
operator|->
name|opacity_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_FORCE
case|:
return|return
name|private
operator|->
name|force_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_HARDNESS
case|:
return|return
name|private
operator|->
name|hardness_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_RATE
case|:
return|return
name|private
operator|->
name|rate_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_FLOW
case|:
return|return
name|private
operator|->
name|flow_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_SIZE
case|:
return|return
name|private
operator|->
name|size_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_ASPECT_RATIO
case|:
return|return
name|private
operator|->
name|aspect_ratio_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_COLOR
case|:
return|return
name|private
operator|->
name|color_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_ANGLE
case|:
return|return
name|private
operator|->
name|angle_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_JITTER
case|:
return|return
name|private
operator|->
name|jitter_output
return|;
break|break;
case|case
name|GIMP_DYNAMICS_OUTPUT_SPACING
case|:
return|return
name|private
operator|->
name|spacing_output
return|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_dynamics_is_output_enabled (GimpDynamics * dynamics,GimpDynamicsOutputType type)
name|gimp_dynamics_is_output_enabled
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
parameter_list|)
block|{
name|GimpDynamicsOutput
modifier|*
name|output
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS
argument_list|(
name|dynamics
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|dynamics
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return
name|gimp_dynamics_output_is_enabled
argument_list|(
name|output
argument_list|)
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_dynamics_get_linear_value (GimpDynamics * dynamics,GimpDynamicsOutputType type,const GimpCoords * coords,GimpPaintOptions * options,gdouble fade_point)
name|gimp_dynamics_get_linear_value
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
block|{
name|GimpDynamicsOutput
modifier|*
name|output
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS
argument_list|(
name|dynamics
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|dynamics
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|output
argument_list|,
name|coords
argument_list|,
name|options
argument_list|,
name|fade_point
argument_list|)
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_dynamics_get_angular_value (GimpDynamics * dynamics,GimpDynamicsOutputType type,const GimpCoords * coords,GimpPaintOptions * options,gdouble fade_point)
name|gimp_dynamics_get_angular_value
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
block|{
name|GimpDynamicsOutput
modifier|*
name|output
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS
argument_list|(
name|dynamics
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|dynamics
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return
name|gimp_dynamics_output_get_angular_value
argument_list|(
name|output
argument_list|,
name|coords
argument_list|,
name|options
argument_list|,
name|fade_point
argument_list|)
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_dynamics_get_aspect_value (GimpDynamics * dynamics,GimpDynamicsOutputType type,const GimpCoords * coords,GimpPaintOptions * options,gdouble fade_point)
name|gimp_dynamics_get_aspect_value
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
block|{
name|GimpDynamicsOutput
modifier|*
name|output
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DYNAMICS
argument_list|(
name|dynamics
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|output
operator|=
name|gimp_dynamics_get_output
argument_list|(
name|dynamics
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return
name|gimp_dynamics_output_get_aspect_value
argument_list|(
name|output
argument_list|,
name|coords
argument_list|,
name|options
argument_list|,
name|fade_point
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpDynamicsOutput
modifier|*
DECL|function|gimp_dynamics_create_output (GimpDynamics * dynamics,const gchar * name,GimpDynamicsOutputType type)
name|gimp_dynamics_create_output
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDynamicsOutputType
name|type
parameter_list|)
block|{
name|GimpDynamicsOutput
modifier|*
name|output
init|=
name|gimp_dynamics_output_new
argument_list|(
name|name
argument_list|,
name|type
argument_list|)
decl_stmt|;
name|g_signal_connect
argument_list|(
name|output
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dynamics_output_notify
argument_list|)
argument_list|,
name|dynamics
argument_list|)
expr_stmt|;
return|return
name|output
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_output_notify (GObject * output,const GParamSpec * pspec,GimpDynamics * dynamics)
name|gimp_dynamics_output_notify
parameter_list|(
name|GObject
modifier|*
name|output
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|)
block|{
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dynamics
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|output
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

