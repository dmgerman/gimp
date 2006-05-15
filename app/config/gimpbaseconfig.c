begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpBaseConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-processor.h"
end_include

begin_include
include|#
directive|include
file|"gimprc-blurbs.h"
end_include

begin_include
include|#
directive|include
file|"gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27c9ad3a0103
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
comment|/* ignored, only for backward compatibility: */
DECL|enumerator|PROP_STINGY_MEMORY_USE
name|PROP_STINGY_MEMORY_USE
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_base_config_finalize
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
name|gimp_base_config_set_property
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
name|gimp_base_config_get_property
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
DECL|function|G_DEFINE_TYPE (GimpBaseConfig,gimp_base_config,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBaseConfig
argument_list|,
argument|gimp_base_config
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_base_config_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_base_config_class_init
parameter_list|(
name|GimpBaseConfigClass
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
name|finalize
operator|=
name|gimp_base_config_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_base_config_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_base_config_get_property
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_TEMP_PATH
argument_list|,
literal|"temp-path"
argument_list|,
name|TEMP_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR
argument_list|,
literal|"${gimp_dir}"
name|G_DIR_SEPARATOR_S
literal|"tmp"
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_PATH
argument_list|(
name|object_class
argument_list|,
name|PROP_SWAP_PATH
argument_list|,
literal|"swap-path"
argument_list|,
name|SWAP_PATH_BLURB
argument_list|,
name|GIMP_CONFIG_PATH_DIR
argument_list|,
literal|"${gimp_dir}"
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_RESTART
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_UINT
argument_list|(
name|object_class
argument_list|,
name|PROP_NUM_PROCESSORS
argument_list|,
literal|"num-processors"
argument_list|,
name|NUM_PROCESSORS_BLURB
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_NUM_THREADS
argument_list|,
literal|2
argument_list|,
name|GIMP_PARAM_STATIC_STRINGS
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_MEMSIZE
argument_list|(
name|object_class
argument_list|,
name|PROP_TILE_CACHE_SIZE
argument_list|,
literal|"tile-cache-size"
argument_list|,
name|TILE_CACHE_SIZE_BLURB
argument_list|,
literal|0
argument_list|,
name|MIN
argument_list|(
name|G_MAXULONG
argument_list|,
name|GIMP_MAX_MEMSIZE
argument_list|)
argument_list|,
literal|1
operator|<<
literal|28
argument_list|,
comment|/* 256MB */
name|GIMP_PARAM_STATIC_STRINGS
operator||
name|GIMP_CONFIG_PARAM_CONFIRM
argument_list|)
expr_stmt|;
comment|/*  only for backward compatibility:  */
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_STINGY_MEMORY_USE
argument_list|,
literal|"stingy-memory-use"
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
DECL|function|gimp_base_config_init (GimpBaseConfig * config)
name|gimp_base_config_init
parameter_list|(
name|GimpBaseConfig
modifier|*
name|config
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_base_config_finalize (GObject * object)
name|gimp_base_config_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBaseConfig
modifier|*
name|base_config
init|=
name|GIMP_BASE_CONFIG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|base_config
operator|->
name|temp_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|base_config
operator|->
name|swap_path
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
DECL|function|gimp_base_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_base_config_set_property
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
name|GimpBaseConfig
modifier|*
name|base_config
init|=
name|GIMP_BASE_CONFIG
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
name|base_config
operator|->
name|temp_path
argument_list|)
expr_stmt|;
name|base_config
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
name|base_config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
name|base_config
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
name|base_config
operator|->
name|num_processors
operator|=
name|g_value_get_uint
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TILE_CACHE_SIZE
case|:
name|base_config
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
DECL|function|gimp_base_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_base_config_get_property
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
name|GimpBaseConfig
modifier|*
name|base_config
init|=
name|GIMP_BASE_CONFIG
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
name|base_config
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
name|base_config
operator|->
name|swap_path
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_NUM_PROCESSORS
case|:
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|base_config
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
name|base_config
operator|->
name|tile_cache_size
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

