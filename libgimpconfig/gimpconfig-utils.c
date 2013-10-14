begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Utitility functions for GimpConfig.  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigtypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigwriter.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-iface.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-params.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
end_include

begin_comment
comment|/**  * SECTION: gimpconfig-utils  * @title: GimpConfig-utils  * @short_description: Miscellaneous utility functions for libgimpconfig.  *  * Miscellaneous utility functions for libgimpconfig.  **/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_diff_property (GObject * a,GObject * b,GParamSpec * prop_spec)
name|gimp_config_diff_property
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|,
name|GParamSpec
modifier|*
name|prop_spec
parameter_list|)
block|{
name|GValue
name|a_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GValue
name|b_value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|a_value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
operator|&
name|b_value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|a
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|a_value
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|b
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|b_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_param_values_cmp
argument_list|(
name|prop_spec
argument_list|,
operator|&
name|a_value
argument_list|,
operator|&
name|b_value
argument_list|)
condition|)
block|{
if|if
condition|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_AGGREGATE
operator|)
operator|&&
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|prop_spec
argument_list|)
operator|&&
name|g_type_interface_peek
argument_list|(
name|g_type_class_peek
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_config_is_equal_to
argument_list|(
name|g_value_get_object
argument_list|(
operator|&
name|a_value
argument_list|)
argument_list|,
name|g_value_get_object
argument_list|(
operator|&
name|b_value
argument_list|)
argument_list|)
condition|)
block|{
name|retval
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
else|else
block|{
name|retval
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|g_value_unset
argument_list|(
operator|&
name|a_value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|b_value
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_config_diff_same (GObject * a,GObject * b,GParamFlags flags)
name|gimp_config_diff_same
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|param_specs
decl_stmt|;
name|guint
name|n_param_specs
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|param_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|a
argument_list|)
argument_list|,
operator|&
name|n_param_specs
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
name|n_param_specs
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|prop_spec
init|=
name|param_specs
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
operator|!
name|flags
operator|||
operator|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|flags
operator|)
operator|==
name|flags
operator|)
condition|)
block|{
if|if
condition|(
name|gimp_config_diff_property
argument_list|(
name|a
argument_list|,
name|b
argument_list|,
name|prop_spec
argument_list|)
condition|)
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|prop_spec
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|param_specs
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_config_diff_other (GObject * a,GObject * b,GParamFlags flags)
name|gimp_config_diff_other
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GParamSpec
modifier|*
modifier|*
name|param_specs
decl_stmt|;
name|guint
name|n_param_specs
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|param_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|a
argument_list|)
argument_list|,
operator|&
name|n_param_specs
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
name|n_param_specs
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|a_spec
init|=
name|param_specs
index|[
name|i
index|]
decl_stmt|;
name|GParamSpec
modifier|*
name|b_spec
init|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|b
argument_list|)
argument_list|,
name|a_spec
operator|->
name|name
argument_list|)
decl_stmt|;
if|if
condition|(
name|b_spec
operator|&&
operator|(
name|a_spec
operator|->
name|value_type
operator|==
name|b_spec
operator|->
name|value_type
operator|)
operator|&&
operator|(
operator|!
name|flags
operator|||
operator|(
name|a_spec
operator|->
name|flags
operator|&
name|b_spec
operator|->
name|flags
operator|&
name|flags
operator|)
operator|==
name|flags
operator|)
condition|)
block|{
if|if
condition|(
name|gimp_config_diff_property
argument_list|(
name|a
argument_list|,
name|b
argument_list|,
name|b_spec
argument_list|)
condition|)
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|b_spec
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|param_specs
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_diff:  * @a: a #GObject  * @b: another #GObject object  * @flags: a mask of GParamFlags  *  * Compares all properties of @a and @b that have all @flags set. If  * @flags is 0, all properties are compared.  *  * If the two objects are not of the same type, only properties that  * exist in both object classes and are of the same value_type are  * compared.  *  * Return value: a GList of differing GParamSpecs.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_config_diff (GObject * a,GObject * b,GParamFlags flags)
name|gimp_config_diff
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GList
modifier|*
name|diff
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|a
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|b
argument_list|)
argument_list|,
name|NULL
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
name|diff
operator|=
name|gimp_config_diff_same
argument_list|(
name|a
argument_list|,
name|b
argument_list|,
name|flags
argument_list|)
expr_stmt|;
else|else
name|diff
operator|=
name|gimp_config_diff_other
argument_list|(
name|a
argument_list|,
name|b
argument_list|,
name|flags
argument_list|)
expr_stmt|;
return|return
name|g_list_reverse
argument_list|(
name|diff
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_sync:  * @src: a #GObject  * @dest: another #GObject  * @flags: a mask of GParamFlags  *  * Compares all read- and write-able properties from @src and @dest  * that have all @flags set. Differing values are then copied from  * @src to @dest. If @flags is 0, all differing read/write properties.  *  * Properties marked as "construct-only" are not touched.  *  * If the two objects are not of the same type, only properties that  * exist in both object classes and are of the same value_type are  * synchronized  *  * Return value: %TRUE if @dest was modified, %FALSE otherwise  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_sync (GObject * src,GObject * dest,GParamFlags flags)
name|gimp_config_sync
parameter_list|(
name|GObject
modifier|*
name|src
parameter_list|,
name|GObject
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GList
modifier|*
name|diff
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|src
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* we use the internal versions here for a number of reasons:    *  - it saves a g_list_reverse()    *  - it avoids duplicated parameter checks    */
if|if
condition|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|src
argument_list|)
operator|==
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|dest
argument_list|)
condition|)
name|diff
operator|=
name|gimp_config_diff_same
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
operator|(
name|flags
operator||
name|G_PARAM_READWRITE
operator|)
argument_list|)
expr_stmt|;
else|else
name|diff
operator|=
name|gimp_config_diff_other
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|diff
condition|)
return|return
name|FALSE
return|;
name|g_object_freeze_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|)
expr_stmt|;
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
name|list
operator|->
name|next
control|)
block|{
name|GParamSpec
modifier|*
name|prop_spec
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_CONSTRUCT_ONLY
operator|)
condition|)
block|{
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|src
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|dest
argument_list|,
name|prop_spec
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
name|g_object_thaw_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|diff
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_reset_properties:  * @object: a #GObject  *  * Resets all writable properties of @object to the default values as  * defined in their #GParamSpec. Properties marked as "construct-only"  * are not touched.  *  * If you want to reset a #GimpConfig object, please use gimp_config_reset().  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_reset_properties (GObject * object)
name|gimp_config_reset_properties
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|klass
decl_stmt|;
name|GParamSpec
modifier|*
modifier|*
name|property_specs
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|guint
name|n_property_specs
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|property_specs
operator|=
name|g_object_class_list_properties
argument_list|(
name|klass
argument_list|,
operator|&
name|n_property_specs
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|property_specs
condition|)
return|return;
name|g_object_freeze_notify
argument_list|(
name|object
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
name|n_property_specs
condition|;
name|i
operator|++
control|)
block|{
name|GParamSpec
modifier|*
name|prop_spec
decl_stmt|;
name|prop_spec
operator|=
name|property_specs
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_WRITABLE
operator|)
operator|&&
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_CONSTRUCT_ONLY
operator|)
condition|)
block|{
if|if
condition|(
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|prop_spec
argument_list|)
condition|)
block|{
if|if
condition|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
operator|&&
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_AGGREGATE
operator|)
operator|&&
name|g_type_interface_peek
argument_list|(
name|g_type_class_peek
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|)
condition|)
block|{
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|object
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|gimp_config_reset
argument_list|(
name|g_value_get_object
argument_list|(
operator|&
name|value
argument_list|)
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
else|else
block|{
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_param_value_set_default
argument_list|(
name|prop_spec
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|object
argument_list|,
name|prop_spec
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
block|}
name|g_object_thaw_notify
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|property_specs
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_reset_property:  * @object: a #GObject  * @property_name: name of the property to reset  *  * Resets the property named @property_name to its default value.  The  * property must be writable and must not be marked as "construct-only".  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_reset_property (GObject * object,const gchar * property_name)
name|gimp_config_reset_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|klass
decl_stmt|;
name|GParamSpec
modifier|*
name|prop_spec
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|property_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|klass
operator|=
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|prop_spec
operator|=
name|g_object_class_find_property
argument_list|(
name|klass
argument_list|,
name|property_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|prop_spec
condition|)
return|return;
if|if
condition|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_WRITABLE
operator|)
operator|&&
operator|!
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|G_PARAM_CONSTRUCT_ONLY
operator|)
condition|)
block|{
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
if|if
condition|(
name|G_IS_PARAM_SPEC_OBJECT
argument_list|(
name|prop_spec
argument_list|)
condition|)
block|{
if|if
condition|(
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_SERIALIZE
operator|)
operator|&&
operator|(
name|prop_spec
operator|->
name|flags
operator|&
name|GIMP_CONFIG_PARAM_AGGREGATE
operator|)
operator|&&
name|g_type_interface_peek
argument_list|(
name|g_type_class_peek
argument_list|(
name|prop_spec
operator|->
name|value_type
argument_list|)
argument_list|,
name|GIMP_TYPE_CONFIG
argument_list|)
condition|)
block|{
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|object
argument_list|,
name|prop_spec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|gimp_config_reset
argument_list|(
name|g_value_get_object
argument_list|(
operator|&
name|value
argument_list|)
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
else|else
block|{
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|prop_spec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_param_value_set_default
argument_list|(
name|prop_spec
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|object
argument_list|,
name|prop_spec
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
block|}
end_function

begin_comment
comment|/*  * GimpConfig string utilities  */
end_comment

begin_comment
comment|/**  * gimp_config_string_append_escaped:  * @string: pointer to a #GString  * @val: a string to append or %NULL  *  * Escapes and quotes @val and appends it to @string. The escape  * algorithm is different from the one used by g_strescape() since it  * leaves non-ASCII characters intact and thus preserves UTF-8  * strings. Only control characters and quotes are being escaped.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_string_append_escaped (GString * string,const gchar * val)
name|gimp_config_string_append_escaped
parameter_list|(
name|GString
modifier|*
name|string
parameter_list|,
specifier|const
name|gchar
modifier|*
name|val
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|string
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|val
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|p
decl_stmt|;
name|gchar
name|buf
index|[
literal|4
index|]
init|=
block|{
literal|'\\'
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gint
name|len
decl_stmt|;
name|g_string_append_c
argument_list|(
name|string
argument_list|,
literal|'\"'
argument_list|)
expr_stmt|;
for|for
control|(
name|p
operator|=
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|val
operator|,
name|len
operator|=
literal|0
init|;
operator|*
name|p
condition|;
name|p
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|p
operator|<
literal|' '
operator|||
operator|*
name|p
operator|==
literal|'\\'
operator|||
operator|*
name|p
operator|==
literal|'\"'
condition|)
block|{
name|g_string_append_len
argument_list|(
name|string
argument_list|,
name|val
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|len
operator|=
literal|2
expr_stmt|;
switch|switch
condition|(
operator|*
name|p
condition|)
block|{
case|case
literal|'\b'
case|:
name|buf
index|[
literal|1
index|]
operator|=
literal|'b'
expr_stmt|;
break|break;
case|case
literal|'\f'
case|:
name|buf
index|[
literal|1
index|]
operator|=
literal|'f'
expr_stmt|;
break|break;
case|case
literal|'\n'
case|:
name|buf
index|[
literal|1
index|]
operator|=
literal|'n'
expr_stmt|;
break|break;
case|case
literal|'\r'
case|:
name|buf
index|[
literal|1
index|]
operator|=
literal|'r'
expr_stmt|;
break|break;
case|case
literal|'\t'
case|:
name|buf
index|[
literal|1
index|]
operator|=
literal|'t'
expr_stmt|;
break|break;
case|case
literal|'\\'
case|:
case|case
literal|'"'
case|:
name|buf
index|[
literal|1
index|]
operator|=
operator|*
name|p
expr_stmt|;
break|break;
default|default:
name|len
operator|=
literal|4
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
literal|'0'
operator|+
operator|(
operator|(
operator|(
operator|*
name|p
operator|)
operator|>>
literal|6
operator|)
operator|&
literal|07
operator|)
expr_stmt|;
name|buf
index|[
literal|2
index|]
operator|=
literal|'0'
operator|+
operator|(
operator|(
operator|(
operator|*
name|p
operator|)
operator|>>
literal|3
operator|)
operator|&
literal|07
operator|)
expr_stmt|;
name|buf
index|[
literal|3
index|]
operator|=
literal|'0'
operator|+
operator|(
operator|(
operator|*
name|p
operator|)
operator|&
literal|07
operator|)
expr_stmt|;
break|break;
block|}
name|g_string_append_len
argument_list|(
name|string
argument_list|,
name|buf
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|val
operator|=
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|p
operator|+
literal|1
expr_stmt|;
name|len
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|len
operator|++
expr_stmt|;
block|}
block|}
name|g_string_append_len
argument_list|(
name|string
argument_list|,
name|val
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|string
argument_list|,
literal|'\"'
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_string_append_len
argument_list|(
name|string
argument_list|,
literal|"\"\""
argument_list|,
literal|2
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

