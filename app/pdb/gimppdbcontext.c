begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimppdbcontext.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpbrushcore.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimppdbcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28eb049c0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ANTIALIAS
name|PROP_ANTIALIAS
block|,
DECL|enumerator|PROP_FEATHER
name|PROP_FEATHER
block|,
DECL|enumerator|PROP_FEATHER_RADIUS_X
name|PROP_FEATHER_RADIUS_X
block|,
DECL|enumerator|PROP_FEATHER_RADIUS_Y
name|PROP_FEATHER_RADIUS_Y
block|,
DECL|enumerator|PROP_SAMPLE_MERGED
name|PROP_SAMPLE_MERGED
block|,
DECL|enumerator|PROP_SAMPLE_CRITERION
name|PROP_SAMPLE_CRITERION
block|,
DECL|enumerator|PROP_SAMPLE_THRESHOLD
name|PROP_SAMPLE_THRESHOLD
block|,
DECL|enumerator|PROP_SAMPLE_TRANSPARENT
name|PROP_SAMPLE_TRANSPARENT
block|,
DECL|enumerator|PROP_INTERPOLATION
name|PROP_INTERPOLATION
block|,
DECL|enumerator|PROP_TRANSFORM_DIRECTION
name|PROP_TRANSFORM_DIRECTION
block|,
DECL|enumerator|PROP_TRANSFORM_RESIZE
name|PROP_TRANSFORM_RESIZE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_pdb_context_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_context_constructed
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
name|gimp_pdb_context_finalize
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
name|gimp_pdb_context_set_property
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
name|gimp_pdb_context_get_property
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
name|gimp_pdb_context_reset
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
argument|GimpPDBContext
argument_list|,
argument|gimp_pdb_context
argument_list|,
argument|GIMP_TYPE_CONTEXT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_CONFIG,                                                 gimp_pdb_context_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_pdb_context_parent_class
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

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_context_class_init (GimpPDBContextClass * klass)
name|gimp_pdb_context_class_init
parameter_list|(
name|GimpPDBContextClass
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_pdb_context_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_pdb_context_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_pdb_context_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_pdb_context_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_ANTIALIAS
argument_list|,
literal|"antialias"
argument_list|,
name|N_
argument_list|(
literal|"Smooth edges"
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_FEATHER
argument_list|,
literal|"feather"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FEATHER_RADIUS_X
argument_list|,
literal|"feather-radius-x"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1000.0
argument_list|,
literal|10.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_FEATHER_RADIUS_Y
argument_list|,
literal|"feather-radius-y"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1000.0
argument_list|,
literal|10.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_MERGED
argument_list|,
literal|"sample-merged"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_CRITERION
argument_list|,
literal|"sample-criterion"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_SELECT_CRITERION
argument_list|,
name|GIMP_SELECT_CRITERION_COMPOSITE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_THRESHOLD
argument_list|,
literal|"sample-threshold"
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_TRANSPARENT
argument_list|,
literal|"sample-transparent"
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_INTERPOLATION
argument_list|,
literal|"interpolation"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_INTERPOLATION_TYPE
argument_list|,
name|GIMP_INTERPOLATION_CUBIC
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSFORM_DIRECTION
argument_list|,
literal|"transform-direction"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_DIRECTION
argument_list|,
name|GIMP_TRANSFORM_FORWARD
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_TRANSFORM_RESIZE
argument_list|,
literal|"transform-resize"
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_TRANSFORM_RESIZE
argument_list|,
name|GIMP_TRANSFORM_RESIZE_ADJUST
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_context_iface_init (GimpConfigInterface * iface)
name|gimp_pdb_context_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_config_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
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
name|iface
operator|->
name|reset
operator|=
name|gimp_pdb_context_reset
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_context_init (GimpPDBContext * context)
name|gimp_pdb_context_init
parameter_list|(
name|GimpPDBContext
modifier|*
name|context
parameter_list|)
block|{
name|context
operator|->
name|paint_options_list
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_context_constructed (GObject * object)
name|gimp_pdb_context_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPDBContext
modifier|*
name|context
init|=
name|GIMP_PDB_CONTEXT
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpInterpolationType
name|interpolation
decl_stmt|;
name|gint
name|threshold
decl_stmt|;
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|context
operator|->
name|stroke_options
operator|=
name|gimp_stroke_options_new
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|context
argument_list|)
operator|->
name|gimp
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* keep the stroke options in sync with the context */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_ALL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|)
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
comment|/* preserve the traditional PDB default */
name|g_object_set
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|,
literal|"method"
argument_list|,
name|GIMP_STROKE_PAINT_METHOD
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_bind_property
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"antialias"
argument_list|,
name|G_OBJECT
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|)
argument_list|,
literal|"antialias"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
comment|/* get default interpolation from gimprc */
name|interpolation
operator|=
name|GIMP_CONTEXT
argument_list|(
name|object
argument_list|)
operator|->
name|gimp
operator|->
name|config
operator|->
name|interpolation_type
expr_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"interpolation"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspec
condition|)
name|G_PARAM_SPEC_ENUM
argument_list|(
name|pspec
argument_list|)
operator|->
name|default_value
operator|=
name|interpolation
expr_stmt|;
name|g_object_set
argument_list|(
name|object
argument_list|,
literal|"interpolation"
argument_list|,
name|interpolation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* get default threshold from gimprc */
name|threshold
operator|=
name|GIMP_CONTEXT
argument_list|(
name|object
argument_list|)
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_threshold
expr_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"sample-threshold"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pspec
condition|)
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
operator|->
name|default_value
operator|=
name|threshold
operator|/
literal|255.0
expr_stmt|;
name|g_object_set
argument_list|(
name|object
argument_list|,
literal|"sample-threshold"
argument_list|,
name|threshold
operator|/
literal|255.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_context_finalize (GObject * object)
name|gimp_pdb_context_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPDBContext
modifier|*
name|context
init|=
name|GIMP_PDB_CONTEXT
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|context
operator|->
name|paint_options_list
condition|)
block|{
name|g_object_unref
argument_list|(
name|context
operator|->
name|paint_options_list
argument_list|)
expr_stmt|;
name|context
operator|->
name|paint_options_list
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|context
operator|->
name|stroke_options
condition|)
block|{
name|g_object_unref
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|)
expr_stmt|;
name|context
operator|->
name|stroke_options
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
DECL|function|gimp_pdb_context_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_pdb_context_set_property
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
name|GimpPDBContext
modifier|*
name|options
init|=
name|GIMP_PDB_CONTEXT
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
name|PROP_FEATHER
case|:
name|options
operator|->
name|feather
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_X
case|:
name|options
operator|->
name|feather_radius_x
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_Y
case|:
name|options
operator|->
name|feather_radius_y
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_MERGED
case|:
name|options
operator|->
name|sample_merged
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_CRITERION
case|:
name|options
operator|->
name|sample_criterion
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_THRESHOLD
case|:
name|options
operator|->
name|sample_threshold
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_TRANSPARENT
case|:
name|options
operator|->
name|sample_transparent
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INTERPOLATION
case|:
name|options
operator|->
name|interpolation
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSFORM_DIRECTION
case|:
name|options
operator|->
name|transform_direction
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSFORM_RESIZE
case|:
name|options
operator|->
name|transform_resize
operator|=
name|g_value_get_enum
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
DECL|function|gimp_pdb_context_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_pdb_context_get_property
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
name|GimpPDBContext
modifier|*
name|options
init|=
name|GIMP_PDB_CONTEXT
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
name|PROP_FEATHER
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|feather
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_X
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|feather_radius_x
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FEATHER_RADIUS_Y
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|feather_radius_y
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_MERGED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_CRITERION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sample_criterion
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_THRESHOLD
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sample_threshold
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SAMPLE_TRANSPARENT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|sample_transparent
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INTERPOLATION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|interpolation
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSFORM_DIRECTION
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|transform_direction
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TRANSFORM_RESIZE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|options
operator|->
name|transform_resize
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
DECL|function|gimp_pdb_context_reset (GimpConfig * config)
name|gimp_pdb_context_reset
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpPDBContext
modifier|*
name|context
init|=
name|GIMP_PDB_CONTEXT
argument_list|(
name|config
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|context
operator|->
name|paint_options_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gimp_config_reset
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|)
argument_list|)
expr_stmt|;
comment|/* preserve the traditional PDB default */
name|g_object_set
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|,
literal|"method"
argument_list|,
name|GIMP_STROKE_PAINT_METHOD
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parent_config_iface
operator|->
name|reset
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"antialias"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpContext
modifier|*
DECL|function|gimp_pdb_context_new (Gimp * gimp,GimpContext * parent,gboolean set_parent)
name|gimp_pdb_context_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|parent
parameter_list|,
name|gboolean
name|set_parent
parameter_list|)
block|{
name|GimpPDBContext
modifier|*
name|context
decl_stmt|;
name|GList
modifier|*
name|list
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
name|GIMP_IS_CONTEXT
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|context
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PDB_CONTEXT
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"name"
argument_list|,
literal|"PDB Context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|set_parent
condition|)
block|{
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|GIMP_CONTEXT_PROP_MASK_ALL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_paint_info_iter
argument_list|(
name|gimp
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPaintInfo
modifier|*
name|info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_container_add
argument_list|(
name|context
operator|->
name|paint_options_list
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|info
operator|->
name|paint_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|GIMP_PDB_CONTEXT
argument_list|(
name|parent
argument_list|)
operator|->
name|paint_options_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPaintOptions
modifier|*
name|options
init|=
name|gimp_config_duplicate
argument_list|(
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|gimp_container_add
argument_list|(
name|context
operator|->
name|paint_options_list
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|options
argument_list|)
expr_stmt|;
block|}
name|gimp_config_copy
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|GIMP_PDB_CONTEXT
argument_list|(
name|parent
argument_list|)
operator|->
name|stroke_options
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|context
operator|->
name|stroke_options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
comment|/*  copy the context properties last, they might have been    *  overwritten by the above copying of stroke options, which have    *  the pdb context as parent    */
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|parent
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GIMP_CONTEXT
argument_list|(
name|context
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPaintOptions
modifier|*
DECL|function|gimp_pdb_context_get_paint_options (GimpPDBContext * context,const gchar * name)
name|gimp_pdb_context_get_paint_options
parameter_list|(
name|GimpPDBContext
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
name|GIMP_IS_PDB_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|gimp_context_get_paint_info
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|(
name|GimpPaintOptions
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|context
operator|->
name|paint_options_list
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_pdb_context_get_brush_options (GimpPDBContext * context)
name|gimp_pdb_context_get_brush_options
parameter_list|(
name|GimpPDBContext
modifier|*
name|context
parameter_list|)
block|{
name|GList
modifier|*
name|brush_options
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|context
operator|->
name|paint_options_list
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPaintOptions
modifier|*
name|options
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|g_type_is_a
argument_list|(
name|options
operator|->
name|paint_info
operator|->
name|paint_type
argument_list|,
name|GIMP_TYPE_BRUSH_CORE
argument_list|)
condition|)
name|brush_options
operator|=
name|g_list_prepend
argument_list|(
name|brush_options
argument_list|,
name|options
argument_list|)
expr_stmt|;
block|}
return|return
name|g_list_reverse
argument_list|(
name|brush_options
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpStrokeOptions
modifier|*
DECL|function|gimp_pdb_context_get_stroke_options (GimpPDBContext * context)
name|gimp_pdb_context_get_stroke_options
parameter_list|(
name|GimpPDBContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|context
operator|->
name|stroke_options
return|;
block|}
end_function

end_unit

