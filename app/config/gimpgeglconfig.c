begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGeglConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
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
file|"core/core-types.h"
end_include

begin_comment
comment|/* eek */
end_comment

begin_include
include|#
directive|include
file|"gimprc-blurbs.h"
end_include

begin_include
include|#
directive|include
file|"gimpgeglconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-debug.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GIMP_MAX_MEM_PROCESS
define|#
directive|define
name|GIMP_MAX_MEM_PROCESS
value|(MIN (G_MAXSIZE, GIMP_MAX_MEMSIZE))
end_define

begin_enum
enum|enum
DECL|enum|__anon277eb43b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_TEMP_PATH
name|PROP_TEMP_PATH
block|,
DECL|enumerator|PROP_SWAP_PATH
name|PROP_SWAP_PATH
block|,
DECL|enumerator|PROP_NUM_PROCESSORS
name|PROP_NUM_PROCESSORS
block|,
DECL|enumerator|PROP_TILE_CACHE_SIZE
name|PROP_TILE_CACHE_SIZE
block|,
DECL|enumerator|PROP_USE_OPENCL
name|PROP_USE_OPENCL
block|,
comment|/* ignored, only for backward compatibility: */
DECL|enumerator|PROP_STINGY_MEMORY_USE
name|PROP_STINGY_MEMORY_USE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_gegl_config_constructed
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
name|gimp_gegl_config_finalize
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
name|gimp_gegl_config_set_property
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
name|gimp_gegl_config_get_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGeglConfig,gimp_gegl_config,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGeglConfig
argument_list|,
argument|gimp_gegl_config
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_gegl_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_gegl_config_class_init
parameter_list|(
name|GimpGeglConfigClass
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
name|gint
name|n_threads
decl_stmt|;
name|gint
name|max_n_threads
decl_stmt|;
name|guint64
name|memory_size
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
name|constructed
operator|=
name|gimp_gegl_config_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_gegl_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_gegl_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_gegl_config_get_property
expr_stmt|;
name|GIMP_CONFIG_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_TEMP_PATH
argument_list|,
literal|"temp-path"
argument_list|,
literal|"Temp path"
argument_list|,
name|TEMP_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR
argument_list|,
literal|"${gimp_temp_dir}"
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_SWAP_PATH
argument_list|,
literal|"swap-path"
argument_list|,
literal|"Swap path"
argument_list|,
name|SWAP_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR
argument_list|,
literal|"${gimp_cache_dir}"
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|n_threads
operator|=
name|g_get_num_processors
argument_list|()
expr_stmt|;
name|max_n_threads
operator|=
name|G_PARAM_SPEC_INT
argument_list|(
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|gegl_config
argument_list|()
argument_list|)
argument_list|,
literal|"threads"
argument_list|)
argument_list|)
operator|->
name|maximum
expr_stmt|;
name|n_threads
operator|=
name|MIN
argument_list|(
name|n_threads
argument_list|,
name|max_n_threads
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_INT
argument_list|(
name|object_class
argument_list|,
name|PROP_NUM_PROCESSORS
argument_list|,
literal|"num-processors"
argument_list|,
literal|"Number of threads to use"
argument_list|,
name|NUM_PROCESSORS_BLURB
argument_list|,
literal|1
argument_list|,
name|max_n_threads
argument_list|,
name|n_threads
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|memory_size
operator|=
name|gimp_get_physical_memory_size
argument_list|()
expr_stmt|;
comment|/* limit to the amount one process can handle */
name|memory_size
operator|=
name|MIN
argument_list|(
name|GIMP_MAX_MEM_PROCESS
argument_list|,
name|memory_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|memory_size
operator|>
literal|0
condition|)
name|memory_size
operator|=
name|memory_size
operator|/
literal|2
expr_stmt|;
comment|/* half the memory */
else|else
name|memory_size
operator|=
literal|1
operator|<<
literal|30
expr_stmt|;
comment|/* 1GB */
name|GIMP_CONFIG_PROP_MEMSIZE
argument_list|(
name|object_class
argument_list|,
name|PROP_TILE_CACHE_SIZE
argument_list|,
literal|"tile-cache-size"
argument_list|,
literal|"Tile cache size"
argument_list|,
name|TILE_CACHE_SIZE_BLURB
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_MEM_PROCESS
argument_list|,
name|memory_size
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_CONFIRM
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_USE_OPENCL
argument_list|,
literal|"use-opencl"
argument_list|,
literal|"Use OpenCL"
argument_list|,
name|USE_OPENCL_BLURB
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
comment|/*  only for backward compatibility:  */
name|GIMP_CONFIG_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_STINGY_MEMORY_USE
argument_list|,
literal|"stingy-memory-use"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_CONFIG_PARAM_IGNORE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_init (GimpGeglConfig * config)
name|gimp_gegl_config_init
parameter_list|(
name|GimpGeglConfig
modifier|*
name|config
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_constructed (GObject * object)
name|gimp_gegl_config_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
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
name|gimp_debug_add_instance
argument_list|(
name|object
argument_list|,
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_finalize (GObject * object)
name|gimp_gegl_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGeglConfig
modifier|*
name|gegl_config
init|=
name|GIMP_GEGL_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|gegl_config
operator|->
name|temp_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gegl_config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
name|gimp_debug_remove_instance
argument_list|(
name|object
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
DECL|function|gimp_gegl_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_gegl_config_set_property
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
name|GimpGeglConfig
modifier|*
name|gegl_config
init|=
name|GIMP_GEGL_CONFIG
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
name|PROP_TEMP_PATH
case|:
name|g_free
argument_list|(
name|gegl_config
operator|->
name|temp_path
argument_list|)
expr_stmt|;
name|gegl_config
operator|->
name|temp_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SWAP_PATH
case|:
name|g_free
argument_list|(
name|gegl_config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
name|gegl_config
operator|->
name|swap_path
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NUM_PROCESSORS
case|:
name|gegl_config
operator|->
name|num_processors
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILE_CACHE_SIZE
case|:
name|gegl_config
operator|->
name|tile_cache_size
operator|=
name|g_value_get_uint64
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_OPENCL
case|:
name|gegl_config
operator|->
name|use_opencl
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STINGY_MEMORY_USE
case|:
comment|/* ignored */
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
DECL|function|gimp_gegl_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_gegl_config_get_property
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
name|GimpGeglConfig
modifier|*
name|gegl_config
init|=
name|GIMP_GEGL_CONFIG
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
name|PROP_TEMP_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gegl_config
operator|->
name|temp_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SWAP_PATH
case|:
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gegl_config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NUM_PROCESSORS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|gegl_config
operator|->
name|num_processors
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILE_CACHE_SIZE
case|:
name|g_value_set_uint64
argument_list|(
name|value
argument_list|,
name|gegl_config
operator|->
name|tile_cache_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_USE_OPENCL
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gegl_config
operator|->
name|use_opencl
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_STINGY_MEMORY_USE
case|:
comment|/* ignored */
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

