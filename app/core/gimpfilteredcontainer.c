begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpfilteredcontainer.c  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *               2011 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilteredcontainer.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon297f0aa20103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SRC_CONTAINER
name|PROP_SRC_CONTAINER
block|,
DECL|enumerator|PROP_FILTER_FUNC
name|PROP_FILTER_FUNC
block|,
DECL|enumerator|PROP_FILTER_DATA
name|PROP_FILTER_DATA
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_constructed
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
name|gimp_filtered_container_dispose
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
name|gimp_filtered_container_finalize
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
name|gimp_filtered_container_set_property
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
name|gimp_filtered_container_get_property
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
name|gimp_filtered_container_real_src_add
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_real_src_remove
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_real_src_freeze
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_real_src_thaw
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_filtered_container_object_matches
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_src_add
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpObject
modifier|*
name|obj
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_src_remove
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpObject
modifier|*
name|obj
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_src_freeze
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_filtered_container_src_thaw
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFilteredContainer,gimp_filtered_container,GIMP_TYPE_LIST)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFilteredContainer
argument_list|,
argument|gimp_filtered_container
argument_list|,
argument|GIMP_TYPE_LIST
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_filtered_container_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_filtered_container_class_init
parameter_list|(
name|GimpFilteredContainerClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|g_object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpFilteredContainerClass
modifier|*
name|filtered_class
init|=
name|GIMP_FILTERED_CONTAINER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|g_object_class
operator|->
name|constructed
operator|=
name|gimp_filtered_container_constructed
expr_stmt|;
name|g_object_class
operator|->
name|dispose
operator|=
name|gimp_filtered_container_dispose
expr_stmt|;
name|g_object_class
operator|->
name|finalize
operator|=
name|gimp_filtered_container_finalize
expr_stmt|;
name|g_object_class
operator|->
name|set_property
operator|=
name|gimp_filtered_container_set_property
expr_stmt|;
name|g_object_class
operator|->
name|get_property
operator|=
name|gimp_filtered_container_get_property
expr_stmt|;
name|filtered_class
operator|->
name|src_add
operator|=
name|gimp_filtered_container_real_src_add
expr_stmt|;
name|filtered_class
operator|->
name|src_remove
operator|=
name|gimp_filtered_container_real_src_remove
expr_stmt|;
name|filtered_class
operator|->
name|src_freeze
operator|=
name|gimp_filtered_container_real_src_freeze
expr_stmt|;
name|filtered_class
operator|->
name|src_thaw
operator|=
name|gimp_filtered_container_real_src_thaw
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|g_object_class
argument_list|,
name|PROP_SRC_CONTAINER
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"src-container"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTAINER
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|g_object_class
argument_list|,
name|PROP_FILTER_FUNC
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"filter-func"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|g_object_class
argument_list|,
name|PROP_FILTER_DATA
argument_list|,
name|g_param_spec_pointer
argument_list|(
literal|"filter-data"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_init (GimpFilteredContainer * filtered_container)
name|gimp_filtered_container_init
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_constructed (GObject * object)
name|gimp_filtered_container_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFilteredContainer
modifier|*
name|filtered_container
init|=
name|GIMP_FILTERED_CONTAINER
argument_list|(
name|object
argument_list|)
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
name|gimp_assert
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_container_frozen
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|)
condition|)
block|{
comment|/*  a freeze/thaw can't hurt on a newly created container because        *  we can't have any views yet. This way we get away without        *  having a virtual function for initializing the container.        */
name|gimp_filtered_container_src_freeze
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
name|gimp_filtered_container_src_thaw
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_dispose (GObject * object)
name|gimp_filtered_container_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFilteredContainer
modifier|*
name|filtered_container
init|=
name|GIMP_FILTERED_CONTAINER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|filtered_container
operator|->
name|src_container
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
name|gimp_filtered_container_src_add
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
name|gimp_filtered_container_src_remove
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
name|gimp_filtered_container_src_freeze
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
name|gimp_filtered_container_src_thaw
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_finalize (GObject * object)
name|gimp_filtered_container_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFilteredContainer
modifier|*
name|filtered_container
init|=
name|GIMP_FILTERED_CONTAINER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|filtered_container
operator|->
name|src_container
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
DECL|function|gimp_filtered_container_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_filtered_container_set_property
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
name|GimpFilteredContainer
modifier|*
name|filtered_container
init|=
name|GIMP_FILTERED_CONTAINER
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
name|PROP_SRC_CONTAINER
case|:
name|filtered_container
operator|->
name|src_container
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_filtered_container_src_add
argument_list|)
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_filtered_container_src_remove
argument_list|)
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
literal|"freeze"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_filtered_container_src_freeze
argument_list|)
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|,
literal|"thaw"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_filtered_container_src_thaw
argument_list|)
argument_list|,
name|filtered_container
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILTER_FUNC
case|:
name|filtered_container
operator|->
name|filter_func
operator|=
name|g_value_get_pointer
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILTER_DATA
case|:
name|filtered_container
operator|->
name|filter_data
operator|=
name|g_value_get_pointer
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
DECL|function|gimp_filtered_container_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_filtered_container_get_property
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
name|GimpFilteredContainer
modifier|*
name|filtered_container
init|=
name|GIMP_FILTERED_CONTAINER
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
name|PROP_SRC_CONTAINER
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|filtered_container
operator|->
name|src_container
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILTER_FUNC
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|filtered_container
operator|->
name|filter_func
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_FILTER_DATA
case|:
name|g_value_set_pointer
argument_list|(
name|value
argument_list|,
name|filtered_container
operator|->
name|filter_data
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
DECL|function|gimp_filtered_container_real_src_add (GimpFilteredContainer * filtered_container,GimpObject * object)
name|gimp_filtered_container_real_src_add
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|gimp_filtered_container_object_matches
argument_list|(
name|filtered_container
argument_list|,
name|object
argument_list|)
condition|)
block|{
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|filtered_container
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_real_src_remove (GimpFilteredContainer * filtered_container,GimpObject * object)
name|gimp_filtered_container_real_src_remove
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|gimp_filtered_container_object_matches
argument_list|(
name|filtered_container
argument_list|,
name|object
argument_list|)
condition|)
block|{
name|gimp_container_remove
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|filtered_container
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_real_src_freeze (GimpFilteredContainer * filtered_container)
name|gimp_filtered_container_real_src_freeze
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
block|{
name|gimp_container_clear
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|filtered_container
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_real_src_thaw (GimpFilteredContainer * filtered_container)
name|gimp_filtered_container_real_src_thaw
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
block|{
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
name|filtered_container
operator|->
name|src_container
argument_list|)
operator|->
name|queue
operator|->
name|head
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
name|GimpObject
modifier|*
name|object
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|gimp_filtered_container_object_matches
argument_list|(
name|filtered_container
argument_list|,
name|object
argument_list|)
condition|)
block|{
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|filtered_container
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_filtered_container_new:  * @src_container: container to be filtered.  *  * Creates a new #GimpFilteredContainer object which creates filtered  * data view of #GimpTagged objects. It filters @src_container for objects  * containing all of the filtering tags. Synchronization with @src_container  * data is performed automatically.  *  * Returns: a new #GimpFilteredContainer object.  **/
end_comment

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_filtered_container_new (GimpContainer * src_container,GimpObjectFilterFunc filter_func,gpointer filter_data)
name|gimp_filtered_container_new
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpObjectFilterFunc
name|filter_func
parameter_list|,
name|gpointer
name|filter_data
parameter_list|)
block|{
name|GType
name|children_type
decl_stmt|;
name|GCompareFunc
name|sort_func
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LIST
argument_list|(
name|src_container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|children_type
operator|=
name|gimp_container_get_children_type
argument_list|(
name|src_container
argument_list|)
expr_stmt|;
name|sort_func
operator|=
name|GIMP_LIST
argument_list|(
name|src_container
argument_list|)
operator|->
name|sort_func
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILTERED_CONTAINER
argument_list|,
literal|"sort-func"
argument_list|,
name|sort_func
argument_list|,
literal|"children-type"
argument_list|,
name|children_type
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_WEAK
argument_list|,
literal|"unique-names"
argument_list|,
name|FALSE
argument_list|,
literal|"src-container"
argument_list|,
name|src_container
argument_list|,
literal|"filter-func"
argument_list|,
name|filter_func
argument_list|,
literal|"filter-data"
argument_list|,
name|filter_data
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_filtered_container_object_matches (GimpFilteredContainer * filtered_container,GimpObject * object)
name|gimp_filtered_container_object_matches
parameter_list|(
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
return|return
operator|(
operator|!
name|filtered_container
operator|->
name|filter_func
operator|||
name|filtered_container
operator|->
name|filter_func
argument_list|(
name|object
argument_list|,
name|filtered_container
operator|->
name|filter_data
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_src_add (GimpContainer * src_container,GimpObject * object,GimpFilteredContainer * filtered_container)
name|gimp_filtered_container_src_add
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_container_frozen
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|)
condition|)
block|{
name|GIMP_FILTERED_CONTAINER_GET_CLASS
argument_list|(
name|filtered_container
argument_list|)
operator|->
name|src_add
argument_list|(
name|filtered_container
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_src_remove (GimpContainer * src_container,GimpObject * object,GimpFilteredContainer * filtered_container)
name|gimp_filtered_container_src_remove
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_container_frozen
argument_list|(
name|filtered_container
operator|->
name|src_container
argument_list|)
condition|)
block|{
name|GIMP_FILTERED_CONTAINER_GET_CLASS
argument_list|(
name|filtered_container
argument_list|)
operator|->
name|src_remove
argument_list|(
name|filtered_container
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_src_freeze (GimpContainer * src_container,GimpFilteredContainer * filtered_container)
name|gimp_filtered_container_src_freeze
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
block|{
name|gimp_container_freeze
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|filtered_container
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_FILTERED_CONTAINER_GET_CLASS
argument_list|(
name|filtered_container
argument_list|)
operator|->
name|src_freeze
argument_list|(
name|filtered_container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filtered_container_src_thaw (GimpContainer * src_container,GimpFilteredContainer * filtered_container)
name|gimp_filtered_container_src_thaw
parameter_list|(
name|GimpContainer
modifier|*
name|src_container
parameter_list|,
name|GimpFilteredContainer
modifier|*
name|filtered_container
parameter_list|)
block|{
name|GIMP_FILTERED_CONTAINER_GET_CLASS
argument_list|(
name|filtered_container
argument_list|)
operator|->
name|src_thaw
argument_list|(
name|filtered_container
argument_list|)
expr_stmt|;
name|gimp_container_thaw
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|filtered_container
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

