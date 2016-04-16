begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs-duplicate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-config.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-utils.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_gegl_config_config_sync
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|gimp_pspec
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gegl_config_config_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|gimp_pspec
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gegl_config_node_notify
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|gegl_pspec
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|static
name|GHashTable
modifier|*
DECL|function|gimp_gegl_config_get_type_table (void)
name|gimp_gegl_config_get_type_table
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GHashTable
modifier|*
name|config_types
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|config_types
condition|)
name|config_types
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|config_types
return|;
block|}
end_function

begin_function
specifier|static
name|GHashTable
modifier|*
DECL|function|gimp_gegl_config_get_container_table (void)
name|gimp_gegl_config_get_container_table
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GHashTable
modifier|*
name|config_containers
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|config_containers
condition|)
name|config_containers
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_direct_hash
argument_list|,
name|g_direct_equal
argument_list|,
name|NULL
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
return|return
name|config_containers
return|;
block|}
end_function

begin_function
specifier|static
name|GValue
modifier|*
DECL|function|gimp_gegl_config_value_new (GParamSpec * pspec)
name|gimp_gegl_config_value_new
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GValue
modifier|*
name|value
init|=
name|g_slice_new0
argument_list|(
name|GValue
argument_list|)
decl_stmt|;
name|g_value_init
argument_list|(
name|value
argument_list|,
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
return|return
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_value_free (GValue * value)
name|gimp_gegl_config_value_free
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|g_value_unset
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GValue
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GHashTable
modifier|*
DECL|function|gimp_gegl_config_get_properties (GObject * object)
name|gimp_gegl_config_get_properties
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GHashTable
modifier|*
name|properties
init|=
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"properties"
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|properties
condition|)
block|{
name|properties
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_gegl_config_value_free
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
literal|"properties"
argument_list|,
name|properties
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_hash_table_unref
argument_list|)
expr_stmt|;
block|}
return|return
name|properties
return|;
block|}
end_function

begin_function
specifier|static
name|GValue
modifier|*
DECL|function|gimp_gegl_config_value_get (GObject * object,GParamSpec * pspec)
name|gimp_gegl_config_value_get
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
name|GHashTable
modifier|*
name|properties
init|=
name|gimp_gegl_config_get_properties
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GValue
modifier|*
name|value
decl_stmt|;
name|value
operator|=
name|g_hash_table_lookup
argument_list|(
name|properties
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|value
condition|)
block|{
name|value
operator|=
name|gimp_gegl_config_value_new
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|properties
argument_list|,
name|g_strdup
argument_list|(
name|pspec
operator|->
name|name
argument_list|)
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|value
return|;
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
name|GValue
modifier|*
name|val
init|=
name|gimp_gegl_config_value_get
argument_list|(
name|object
argument_list|,
name|pspec
argument_list|)
decl_stmt|;
name|g_value_copy
argument_list|(
name|value
argument_list|,
name|val
argument_list|)
expr_stmt|;
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
name|GValue
modifier|*
name|val
init|=
name|gimp_gegl_config_value_get
argument_list|(
name|object
argument_list|,
name|pspec
argument_list|)
decl_stmt|;
name|g_value_copy
argument_list|(
name|val
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_class_init (GObjectClass * klass,const gchar * operation)
name|gimp_gegl_config_class_init
parameter_list|(
name|GObjectClass
modifier|*
name|klass
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|pspecs
decl_stmt|;
name|guint
name|n_pspecs
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|klass
operator|->
name|set_property
operator|=
name|gimp_gegl_config_set_property
expr_stmt|;
name|klass
operator|->
name|get_property
operator|=
name|gimp_gegl_config_get_property
expr_stmt|;
name|pspecs
operator|=
name|gegl_operation_list_properties
argument_list|(
name|operation
argument_list|,
operator|&
name|n_pspecs
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|pspecs
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
operator|(
name|pspec
operator|->
name|flags
operator|&
name|G_PARAM_READABLE
operator|)
operator|&&
operator|(
name|pspec
operator|->
name|flags
operator|&
name|G_PARAM_WRITABLE
operator|)
operator|&&
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"input"
argument_list|)
operator|&&
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"output"
argument_list|)
condition|)
block|{
name|GParamSpec
modifier|*
name|copy
init|=
name|gimp_param_spec_duplicate
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
name|copy
condition|)
block|{
name|g_object_class_install_property
argument_list|(
name|klass
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|copy
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_gegl_config_equal (GimpConfig * a,GimpConfig * b)
name|gimp_gegl_config_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
block|{
name|GList
modifier|*
name|diff
decl_stmt|;
name|gboolean
name|equal
init|=
name|TRUE
decl_stmt|;
name|diff
operator|=
name|gimp_config_diff
argument_list|(
name|G_OBJECT
argument_list|(
name|a
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|b
argument_list|)
argument_list|,
name|GIMP_CONFIG_PARAM_SERIALIZE
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|a
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|b
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|diff
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|pspec
operator|->
name|owner_type
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|a
argument_list|)
condition|)
block|{
name|equal
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|diff
condition|)
block|{
name|equal
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|diff
argument_list|)
expr_stmt|;
return|return
name|equal
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_config_iface_init (GimpConfigInterface * iface)
name|gimp_gegl_config_config_iface_init
parameter_list|(
name|GimpConfigInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|equal
operator|=
name|gimp_gegl_config_equal
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_gegl_config_register (const gchar * operation,GType config_type)
name|gimp_gegl_config_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
name|GType
name|config_type
parameter_list|)
block|{
name|GHashTable
modifier|*
name|config_types
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|config_type
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
argument_list|)
expr_stmt|;
name|config_types
operator|=
name|gimp_gegl_config_get_type_table
argument_list|()
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|config_types
argument_list|,
name|g_strdup
argument_list|(
name|operation
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|config_type
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|gimp_gegl_config_new (const gchar * operation,const gchar * icon_name,GType parent_type)
name|gimp_gegl_config_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|GType
name|parent_type
parameter_list|)
block|{
name|GHashTable
modifier|*
name|config_types
decl_stmt|;
name|GType
name|config_type
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|parent_type
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|config_types
operator|=
name|gimp_gegl_config_get_type_table
argument_list|()
expr_stmt|;
name|config_type
operator|=
operator|(
name|GType
operator|)
name|g_hash_table_lookup
argument_list|(
name|config_types
argument_list|,
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|config_type
condition|)
block|{
name|GTypeQuery
name|query
decl_stmt|;
name|g_type_query
argument_list|(
name|parent_type
argument_list|,
operator|&
name|query
argument_list|)
expr_stmt|;
block|{
name|GTypeInfo
name|info
init|=
block|{
name|query
operator|.
name|class_size
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
name|gimp_gegl_config_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|operation
block|,
name|query
operator|.
name|instance_size
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|NULL
block|,           }
decl_stmt|;
specifier|const
name|GInterfaceInfo
name|config_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_gegl_config_config_iface_init
block|,
name|NULL
block|,
comment|/* interface_finalize */
name|NULL
comment|/* interface_data     */
block|}
decl_stmt|;
name|gchar
modifier|*
name|type_name
init|=
name|g_strdup_printf
argument_list|(
literal|"GimpGegl-%s-config"
argument_list|,
name|operation
argument_list|)
decl_stmt|;
name|g_strcanon
argument_list|(
argument|type_name
argument_list|,
argument|G_CSET_DIGITS
literal|"-"
argument|G_CSET_a_2_z G_CSET_A_2_Z
argument_list|,
literal|'-'
argument_list|)
empty_stmt|;
name|config_type
operator|=
name|g_type_register_static
argument_list|(
name|parent_type
argument_list|,
name|type_name
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|type_name
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|config_type
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|,
operator|&
name|config_info
argument_list|)
expr_stmt|;
if|if
condition|(
name|icon_name
operator|&&
name|g_type_is_a
argument_list|(
name|config_type
argument_list|,
name|GIMP_TYPE_VIEWABLE
argument_list|)
condition|)
block|{
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|g_type_class_ref
argument_list|(
name|config_type
argument_list|)
decl_stmt|;
name|viewable_class
operator|->
name|default_icon_name
operator|=
name|g_strdup
argument_list|(
name|icon_name
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|viewable_class
argument_list|)
expr_stmt|;
block|}
name|gimp_gegl_config_register
argument_list|(
name|operation
argument_list|,
name|config_type
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|g_object_new
argument_list|(
name|config_type
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_gegl_config_get_container (GType config_type)
name|gimp_gegl_config_get_container
parameter_list|(
name|GType
name|config_type
parameter_list|)
block|{
name|GHashTable
modifier|*
name|config_containers
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|config_type
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|config_containers
operator|=
name|gimp_gegl_config_get_container_table
argument_list|()
expr_stmt|;
name|container
operator|=
name|g_hash_table_lookup
argument_list|(
name|config_containers
argument_list|,
operator|(
name|gpointer
operator|)
name|config_type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|container
condition|)
block|{
name|container
operator|=
name|gimp_list_new
argument_list|(
name|config_type
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|config_containers
argument_list|,
operator|(
name|gpointer
operator|)
name|config_type
argument_list|,
name|container
argument_list|)
expr_stmt|;
block|}
return|return
name|container
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_config_sync_node (GimpObject * config,GeglNode * node)
name|gimp_gegl_config_sync_node
parameter_list|(
name|GimpObject
modifier|*
name|config
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|pspecs
decl_stmt|;
name|gchar
modifier|*
name|operation
decl_stmt|;
name|guint
name|n_pspecs
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|node
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_node_get
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
operator|&
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pspecs
operator|=
name|gegl_operation_list_properties
argument_list|(
name|operation
argument_list|,
operator|&
name|n_pspecs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|operation
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|pspecs
index|[
name|i
index|]
decl_stmt|;
comment|/*  if the operation has an object property of the config's        *  type, set it and done        */
if|if
condition|(
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|pspec
argument_list|)
operator|&&
name|pspec
operator|->
name|value_type
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|config
argument_list|)
condition|)
block|{
name|gegl_node_set
argument_list|(
name|node
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|config
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
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
name|GParamSpec
modifier|*
name|gegl_pspec
init|=
name|pspecs
index|[
name|i
index|]
decl_stmt|;
name|GParamSpec
modifier|*
name|gimp_pspec
init|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
name|gegl_pspec
operator|->
name|name
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_pspec
condition|)
block|{
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|gimp_pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|G_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|gimp_pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_COLOR
argument_list|(
name|gegl_pspec
argument_list|)
condition|)
block|{
name|GimpRGB
name|gimp_color
decl_stmt|;
name|GeglColor
modifier|*
name|gegl_color
decl_stmt|;
name|gimp_value_get_rgb
argument_list|(
operator|&
name|value
argument_list|,
operator|&
name|gimp_color
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
name|gegl_color
operator|=
name|gimp_gegl_color_new
argument_list|(
operator|&
name|gimp_color
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|gegl_pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_value_take_object
argument_list|(
operator|&
name|value
argument_list|,
name|gegl_color
argument_list|)
expr_stmt|;
block|}
name|gegl_node_set_property
argument_list|(
name|node
argument_list|,
name|gegl_pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_gegl_config_connect_node (GimpObject * config,GeglNode * node)
name|gimp_gegl_config_connect_node
parameter_list|(
name|GimpObject
modifier|*
name|config
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|pspecs
decl_stmt|;
name|gchar
modifier|*
name|operation
decl_stmt|;
name|guint
name|n_pspecs
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GEGL_IS_NODE
argument_list|(
name|node
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_node_get
argument_list|(
name|node
argument_list|,
literal|"operation"
argument_list|,
operator|&
name|operation
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pspecs
operator|=
name|gegl_operation_list_properties
argument_list|(
name|operation
argument_list|,
operator|&
name|n_pspecs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|operation
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
name|GParamSpec
modifier|*
name|pspec
init|=
name|pspecs
index|[
name|i
index|]
decl_stmt|;
comment|/*  if the operation has an object property of the config's        *  type, connect it to a special callback and done        */
if|if
condition|(
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|pspec
argument_list|)
operator|&&
name|pspec
operator|->
name|value_type
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|config
argument_list|)
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_config_config_sync
argument_list|)
argument_list|,
name|node
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
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
name|GParamSpec
modifier|*
name|gegl_pspec
init|=
name|pspecs
index|[
name|i
index|]
decl_stmt|;
name|GParamSpec
modifier|*
name|gimp_pspec
init|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
name|gegl_pspec
operator|->
name|name
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_pspec
condition|)
block|{
name|gchar
modifier|*
name|notify_name
init|=
name|g_strconcat
argument_list|(
literal|"notify::"
argument_list|,
name|gimp_pspec
operator|->
name|name
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_signal_connect_object
argument_list|(
name|config
argument_list|,
name|notify_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_config_config_notify
argument_list|)
argument_list|,
name|node
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|node
argument_list|,
name|notify_name
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_gegl_config_node_notify
argument_list|)
argument_list|,
name|config
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|notify_name
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|pspecs
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_config_sync (GObject * config,const GParamSpec * gimp_pspec,GeglNode * node)
name|gimp_gegl_config_config_sync
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|gimp_pspec
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
block|{
name|gimp_gegl_config_sync_node
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|config
argument_list|)
argument_list|,
name|node
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_config_notify (GObject * config,const GParamSpec * gimp_pspec,GeglNode * node)
name|gimp_gegl_config_config_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|gimp_pspec
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|gegl_pspec
init|=
name|gegl_node_find_property
argument_list|(
name|node
argument_list|,
name|gimp_pspec
operator|->
name|name
argument_list|)
decl_stmt|;
if|if
condition|(
name|gegl_pspec
condition|)
block|{
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|gulong
name|handler
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|gimp_pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|config
argument_list|,
name|gimp_pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_COLOR
argument_list|(
name|gegl_pspec
argument_list|)
condition|)
block|{
name|GimpRGB
name|gimp_color
decl_stmt|;
name|GeglColor
modifier|*
name|gegl_color
decl_stmt|;
name|gimp_value_get_rgb
argument_list|(
operator|&
name|value
argument_list|,
operator|&
name|gimp_color
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
name|gegl_color
operator|=
name|gimp_gegl_color_new
argument_list|(
operator|&
name|gimp_color
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|gegl_pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_value_take_object
argument_list|(
operator|&
name|value
argument_list|,
name|gegl_color
argument_list|)
expr_stmt|;
block|}
name|handler
operator|=
name|g_signal_handler_find
argument_list|(
name|node
argument_list|,
name|G_SIGNAL_MATCH_DETAIL
operator||
name|G_SIGNAL_MATCH_FUNC
operator||
name|G_SIGNAL_MATCH_DATA
argument_list|,
literal|0
argument_list|,
name|g_quark_from_string
argument_list|(
name|gegl_pspec
operator|->
name|name
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|gimp_gegl_config_node_notify
argument_list|,
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
name|handler
condition|)
name|g_signal_handler_block
argument_list|(
name|node
argument_list|,
name|handler
argument_list|)
expr_stmt|;
name|gegl_node_set_property
argument_list|(
name|node
argument_list|,
name|gegl_pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|handler
condition|)
name|g_signal_handler_unblock
argument_list|(
name|node
argument_list|,
name|handler
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_config_node_notify (GeglNode * node,const GParamSpec * gegl_pspec,GObject * config)
name|gimp_gegl_config_node_notify
parameter_list|(
name|GeglNode
modifier|*
name|node
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|gegl_pspec
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|gimp_pspec
init|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|config
argument_list|)
argument_list|,
name|gegl_pspec
operator|->
name|name
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_pspec
condition|)
block|{
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|gulong
name|handler
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|gegl_pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|gegl_node_get_property
argument_list|(
name|node
argument_list|,
name|gegl_pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|GEGL_IS_PARAM_SPEC_COLOR
argument_list|(
name|gegl_pspec
argument_list|)
condition|)
block|{
name|GeglColor
modifier|*
name|gegl_color
decl_stmt|;
name|GimpRGB
name|gimp_color
decl_stmt|;
name|gegl_color
operator|=
name|g_value_dup_object
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|gegl_color
condition|)
block|{
name|gegl_color_get_rgba
argument_list|(
name|gegl_color
argument_list|,
operator|&
name|gimp_color
operator|.
name|r
argument_list|,
operator|&
name|gimp_color
operator|.
name|g
argument_list|,
operator|&
name|gimp_color
operator|.
name|b
argument_list|,
operator|&
name|gimp_color
operator|.
name|a
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gegl_color
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_rgba_set
argument_list|(
operator|&
name|gimp_color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|gimp_pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|gimp_value_set_rgb
argument_list|(
operator|&
name|value
argument_list|,
operator|&
name|gimp_color
argument_list|)
expr_stmt|;
block|}
name|handler
operator|=
name|g_signal_handler_find
argument_list|(
name|config
argument_list|,
name|G_SIGNAL_MATCH_DETAIL
operator||
name|G_SIGNAL_MATCH_FUNC
operator||
name|G_SIGNAL_MATCH_DATA
argument_list|,
literal|0
argument_list|,
name|g_quark_from_string
argument_list|(
name|gimp_pspec
operator|->
name|name
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|gimp_gegl_config_config_notify
argument_list|,
name|node
argument_list|)
expr_stmt|;
if|if
condition|(
name|handler
condition|)
name|g_signal_handler_block
argument_list|(
name|config
argument_list|,
name|handler
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|config
argument_list|,
name|gimp_pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|handler
condition|)
name|g_signal_handler_unblock
argument_list|(
name|config
argument_list|,
name|handler
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

