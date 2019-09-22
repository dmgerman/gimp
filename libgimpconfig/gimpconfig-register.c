begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpconfig-register.c  * Copyright (C) 2008-2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_config_class_init
parameter_list|(
name|GObjectClass
modifier|*
name|klass
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
name|void
name|gimp_config_config_iface_init
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
name|gimp_config_set_property
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
name|gimp_config_get_property
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
name|gboolean
name|gimp_config_equal
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GValue
modifier|*
name|gimp_config_value_get
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

begin_function_decl
specifier|static
name|GValue
modifier|*
name|gimp_config_value_new
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_config_value_free
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_config_type_register:  * @parent_type: type from which this type will be derived  * @type_name:   string used as the name of the new type  * @pspecs:      array of #GParamSpec to install as properties on the new type  * @n_pspecs:    the number of param specs in @pspecs  *  * This function is a fancy wrapper around g_type_register_static().  * It creates a new object type as subclass of @parent_type, installs  * @pspecs on it and makes the new type implement the #GimpConfig  * interface.  *  * Returns: the newly registered #GType  *  * Since: 3.0  **/
end_comment

begin_function
name|GType
DECL|function|gimp_config_type_register (GType parent_type,const gchar * type_name,GParamSpec ** pspecs,gint n_pspecs)
name|gimp_config_type_register
parameter_list|(
name|GType
name|parent_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|type_name
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|,
name|gint
name|n_pspecs
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|terminated_pspecs
decl_stmt|;
name|GTypeQuery
name|query
decl_stmt|;
name|GType
name|config_type
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|parent_type
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|type_name
operator|!=
name|NULL
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|(
name|pspecs
operator|==
name|NULL
operator|&&
name|n_pspecs
operator|==
literal|0
operator|)
operator|||
operator|(
name|pspecs
operator|!=
name|NULL
operator|&&
name|n_pspecs
operator|>
literal|0
operator|)
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|terminated_pspecs
operator|=
name|g_new0
argument_list|(
name|GParamSpec
operator|*
argument_list|,
name|n_pspecs
operator|+
literal|1
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|terminated_pspecs
argument_list|,
name|pspecs
argument_list|,
sizeof|sizeof
argument_list|(
name|GParamSpec
operator|*
argument_list|)
operator|*
name|n_pspecs
argument_list|)
expr_stmt|;
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
name|gimp_config_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|terminated_pspecs
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
block|,     }
decl_stmt|;
specifier|const
name|GInterfaceInfo
name|config_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_config_config_iface_init
block|,
name|NULL
block|,
comment|/* interface_finalize */
name|NULL
comment|/* interface_data     */
block|}
decl_stmt|;
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
block|}
return|return
name|config_type
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_config_class_init (GObjectClass * klass,GParamSpec ** pspecs)
name|gimp_config_class_init
parameter_list|(
name|GObjectClass
modifier|*
name|klass
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
name|klass
operator|->
name|set_property
operator|=
name|gimp_config_set_property
expr_stmt|;
name|klass
operator|->
name|get_property
operator|=
name|gimp_config_get_property
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|pspecs
index|[
name|i
index|]
operator|!=
name|NULL
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
name|GParamSpec
modifier|*
name|copy
init|=
name|gimp_config_param_spec_duplicate
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
elseif|else
if|if
condition|(
operator|!
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|pspec
argument_list|)
operator|&&
operator|!
name|G_IS_PARAM_SPEC_POINTER
argument_list|(
name|pspec
argument_list|)
condition|)
block|{
comment|/*  silently ignore object properties  */
name|g_warning
argument_list|(
literal|"%s: not supported: %s (%s)\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|pspec
argument_list|)
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_config_iface_init (GimpConfigInterface * iface)
name|gimp_config_config_iface_init
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
name|gimp_config_equal
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_config_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_config_set_property
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
name|gimp_config_value_get
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
DECL|function|gimp_config_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_config_get_property
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
name|gimp_config_value_get
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
name|gboolean
DECL|function|gimp_config_equal (GimpConfig * a,GimpConfig * b)
name|gimp_config_equal
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
name|GValue
modifier|*
DECL|function|gimp_config_value_get (GObject * object,GParamSpec * pspec)
name|gimp_config_value_get
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
decl_stmt|;
name|GValue
modifier|*
name|value
decl_stmt|;
name|properties
operator|=
name|g_object_get_data
argument_list|(
name|object
argument_list|,
literal|"gimp-config-properties"
argument_list|)
expr_stmt|;
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
name|gimp_config_value_free
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|object
argument_list|,
literal|"gimp-config-properties"
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
name|gimp_config_value_new
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
name|GValue
modifier|*
DECL|function|gimp_config_value_new (GParamSpec * pspec)
name|gimp_config_value_new
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
name|g_param_value_set_default
argument_list|(
name|pspec
argument_list|,
name|value
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
DECL|function|gimp_config_value_free (GValue * value)
name|gimp_config_value_free
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

end_unit
