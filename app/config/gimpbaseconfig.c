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
file|"gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpbaseconfig.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_base_config_class_init
parameter_list|(
name|GimpBaseConfigClass
modifier|*
name|klass
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

begin_enum
enum|enum
DECL|enum|__anon2c951aa60103
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
DECL|enumerator|PROP_STINGY_MEMORY_USE
name|PROP_STINGY_MEMORY_USE
block|,
DECL|enumerator|PROP_NUM_PROCESSORS
name|PROP_NUM_PROCESSORS
block|,
DECL|enumerator|PROP_TILE_CACHE_SIZE
name|PROP_TILE_CACHE_SIZE
block|,
DECL|enumerator|PROP_INTERPOLATION_TYPE
name|PROP_INTERPOLATION_TYPE
block|, }
enum|;
end_enum

begin_function
name|GType
DECL|function|gimp_base_config_get_type (void)
name|gimp_base_config_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|config_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|config_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|config_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBaseConfigClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_base_config_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBaseConfig
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
name|config_iface_info
init|=
block|{
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|config_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_OBJECT
argument_list|,
literal|"GimpBaseConfig"
argument_list|,
operator|&
name|config_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|config_type
argument_list|,
name|GIMP_TYPE_CONFIG_INTERFACE
argument_list|,
operator|&
name|config_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|config_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_base_config_class_init (GimpBaseConfigClass * klass)
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
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
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
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
literal|"tmp"
argument_list|,
name|NULL
argument_list|)
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
name|g_strdup
argument_list|(
name|gimp_directory
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
argument_list|(
name|object_class
argument_list|,
name|PROP_STINGY_MEMORY_USE
argument_list|,
literal|"stingy-memory-use"
argument_list|,
name|FALSE
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
literal|1
argument_list|,
literal|30
argument_list|,
literal|1
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
literal|0
argument_list|,
name|G_MAXUINT
argument_list|,
literal|1
operator|<<
literal|25
argument_list|)
expr_stmt|;
name|GIMP_CONFIG_INSTALL_PROP_ENUM
argument_list|(
name|object_class
argument_list|,
name|PROP_INTERPOLATION_TYPE
argument_list|,
literal|"interpolation-type"
argument_list|,
name|GIMP_TYPE_INTERPOLATION_TYPE
argument_list|,
name|GIMP_LINEAR_INTERPOLATION
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
decl_stmt|;
name|base_config
operator|=
name|GIMP_BASE_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|PROP_STINGY_MEMORY_USE
case|:
name|base_config
operator|->
name|stingy_memory_use
operator|=
name|g_value_get_boolean
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
name|g_value_get_uint
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_INTERPOLATION_TYPE
case|:
name|base_config
operator|->
name|interpolation_type
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
decl_stmt|;
name|base_config
operator|=
name|GIMP_BASE_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|PROP_STINGY_MEMORY_USE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|base_config
operator|->
name|stingy_memory_use
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
name|g_value_set_uint
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
name|PROP_INTERPOLATION_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|base_config
operator|->
name|interpolation_type
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

