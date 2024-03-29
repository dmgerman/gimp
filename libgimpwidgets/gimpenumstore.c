begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenumstore.c  * Copyright (C) 2004-2007  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpenumstore.h"
end_include

begin_comment
comment|/**  * SECTION: gimpenumstore  * @title: GimpEnumStore  * @short_description: A #GimpIntStore subclass that keeps enum values.  *  * A #GimpIntStore subclass that keeps enum values.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon27596e380103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ENUM_TYPE
name|PROP_ENUM_TYPE
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpEnumStorePrivate
struct|struct
name|_GimpEnumStorePrivate
block|{
DECL|member|enum_class
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(((GimpEnumStore *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_enum_store_finalize
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
name|gimp_enum_store_set_property
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
name|gimp_enum_store_get_property
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
name|gimp_enum_store_add_value
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|GEnumValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpEnumStore,gimp_enum_store,GIMP_TYPE_INT_STORE)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpEnumStore
argument_list|,
argument|gimp_enum_store
argument_list|,
argument|GIMP_TYPE_INT_STORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_enum_store_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_enum_store_class_init
parameter_list|(
name|GimpEnumStoreClass
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
name|gimp_enum_store_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_enum_store_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_enum_store_get_property
expr_stmt|;
comment|/**    * GimpEnumStore:enum-type:    *    * Sets the #GType of the enum to be used in the store.    *    * Since: 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ENUM_TYPE
argument_list|,
name|g_param_spec_gtype
argument_list|(
literal|"enum-type"
argument_list|,
literal|"Enum Type"
argument_list|,
literal|"The type of the enum"
argument_list|,
name|G_TYPE_ENUM
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_init (GimpEnumStore * store)
name|gimp_enum_store_init
parameter_list|(
name|GimpEnumStore
modifier|*
name|store
parameter_list|)
block|{
name|store
operator|->
name|priv
operator|=
name|gimp_enum_store_get_instance_private
argument_list|(
name|store
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_finalize (GObject * object)
name|gimp_enum_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpEnumStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|priv
operator|->
name|enum_class
argument_list|,
name|g_type_class_unref
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
DECL|function|gimp_enum_store_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_enum_store_set_property
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
name|GimpEnumStorePrivate
modifier|*
name|priv
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
name|PROP_ENUM_TYPE
case|:
name|g_return_if_fail
argument_list|(
name|priv
operator|->
name|enum_class
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|->
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|g_value_get_gtype
argument_list|(
name|value
argument_list|)
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
DECL|function|gimp_enum_store_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_enum_store_get_property
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
name|GimpEnumStorePrivate
modifier|*
name|priv
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
name|PROP_ENUM_TYPE
case|:
name|g_value_set_gtype
argument_list|(
name|value
argument_list|,
operator|(
name|priv
operator|->
name|enum_class
condition|?
name|G_TYPE_FROM_CLASS
argument_list|(
name|priv
operator|->
name|enum_class
argument_list|)
else|:
name|G_TYPE_NONE
operator|)
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
DECL|function|gimp_enum_store_add_value (GtkListStore * store,GEnumValue * value)
name|gimp_enum_store_add_value
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|GEnumValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpEnumStorePrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
init|=
block|{
literal|0
block|, }
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|abbrev
decl_stmt|;
name|gchar
modifier|*
name|stripped
decl_stmt|;
name|desc
operator|=
name|gimp_enum_value_get_desc
argument_list|(
name|priv
operator|->
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|abbrev
operator|=
name|gimp_enum_value_get_abbrev
argument_list|(
name|priv
operator|->
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
comment|/* no mnemonics in combo boxes */
name|stripped
operator|=
name|gimp_strip_uline
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
name|value
operator|->
name|value
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|stripped
argument_list|,
name|GIMP_INT_STORE_ABBREV
argument_list|,
name|abbrev
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|stripped
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_store_new:  * @enum_type: the #GType of an enum.  *  * Creates a new #GimpEnumStore, derived from #GtkListStore and fills  * it with enum values. The enum needs to be registered to the type  * system and should have translatable value names.  *  * Returns: a new #GimpEnumStore.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new (GType enum_type)
name|gimp_enum_store_new
parameter_list|(
name|GType
name|enum_type
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_enum_store_new_with_range
argument_list|(
name|enum_type
argument_list|,
name|enum_class
operator|->
name|minimum
argument_list|,
name|enum_class
operator|->
name|maximum
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
return|return
name|store
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_store_new_with_range:  * @enum_type: the #GType of an enum.  * @minimum: the minimum value to include  * @maximum: the maximum value to include  *  * Creates a new #GimpEnumStore like gimp_enum_store_new() but allows  * to limit the enum values to a certain range. Values smaller than  * @minimum or larger than @maximum are not added to the store.  *  * Returns: a new #GimpEnumStore.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new_with_range (GType enum_type,gint minimum,gint maximum)
name|gimp_enum_store_new_with_range
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|minimum
parameter_list|,
name|gint
name|maximum
parameter_list|)
block|{
name|GimpEnumStorePrivate
modifier|*
name|priv
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_STORE
argument_list|,
literal|"enum-type"
argument_list|,
name|enum_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
expr_stmt|;
for|for
control|(
name|value
operator|=
name|priv
operator|->
name|enum_class
operator|->
name|values
init|;
name|value
operator|->
name|value_name
condition|;
name|value
operator|++
control|)
block|{
if|if
condition|(
name|value
operator|->
name|value
operator|<
name|minimum
operator|||
name|value
operator|->
name|value
operator|>
name|maximum
condition|)
continue|continue;
name|gimp_enum_store_add_value
argument_list|(
name|store
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|store
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_store_new_with_values  * @enum_type: the #GType of an enum.  * @n_values:  the number of enum values to include  * @...:       a list of enum values (exactly @n_values)  *  * Creates a new #GimpEnumStore like gimp_enum_store_new() but allows  * to explicitly list the enum values that should be added to the  * store.  *  * Returns: a new #GimpEnumStore.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new_with_values (GType enum_type,gint n_values,...)
name|gimp_enum_store_new_with_values
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|n_values
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|n_values
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_enum_store_new_with_values_valist
argument_list|(
name|enum_type
argument_list|,
name|n_values
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|store
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_store_new_with_values_valist:  * @enum_type: the #GType of an enum.  * @n_values:  the number of enum values to include  * @args:      a va_list of enum values (exactly @n_values)  *  * See gimp_enum_store_new_with_values().  *  * Returns: a new #GimpEnumStore.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_enum_store_new_with_values_valist (GType enum_type,gint n_values,va_list args)
name|gimp_enum_store_new_with_values_valist
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|n_values
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GimpEnumStorePrivate
modifier|*
name|priv
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GEnumValue
modifier|*
name|value
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_TYPE_IS_ENUM
argument_list|(
name|enum_type
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_values
operator|>
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_STORE
argument_list|,
literal|"enum-type"
argument_list|,
name|enum_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|store
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
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|value
operator|=
name|g_enum_get_value
argument_list|(
name|priv
operator|->
name|enum_class
argument_list|,
name|va_arg
argument_list|(
name|args
argument_list|,
name|gint
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
name|gimp_enum_store_add_value
argument_list|(
name|store
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|store
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_store_set_icon_prefix:  * @store:       a #GimpEnumStore  * @icon_prefix: a prefix to create icon names from enum values  *  * Creates an icon name for each enum value in the @store by appending  * the value's nick to the given @icon_prefix, separated by a hyphen.  *  * See also: gimp_enum_combo_box_set_icon_prefix().  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_enum_store_set_icon_prefix (GimpEnumStore * store,const gchar * icon_prefix)
name|gimp_enum_store_set_icon_prefix
parameter_list|(
name|GimpEnumStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_prefix
parameter_list|)
block|{
name|GimpEnumStorePrivate
modifier|*
name|priv
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GET_PRIVATE
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|model
operator|=
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|gchar
modifier|*
name|icon_name
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|icon_prefix
condition|)
block|{
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
operator|&
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|priv
operator|->
name|enum_class
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
block|{
name|icon_name
operator|=
name|g_strconcat
argument_list|(
name|icon_prefix
argument_list|,
literal|"-"
argument_list|,
name|enum_value
operator|->
name|value_nick
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_ICON_NAME
argument_list|,
name|icon_name
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|icon_name
condition|)
name|g_free
argument_list|(
name|icon_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

