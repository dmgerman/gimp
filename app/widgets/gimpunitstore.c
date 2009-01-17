begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpunitstore.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpunitstore.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon292132e00103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_NUM_VALUES
name|PROP_NUM_VALUES
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_unit_store_tree_model_init
parameter_list|(
name|GtkTreeModelIface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_unit_store_finalize
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
name|gimp_unit_store_set_property
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
name|gimp_unit_store_get_property
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
name|GtkTreeModelFlags
name|gimp_unit_store_get_flags
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_unit_store_get_n_columns
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GType
name|gimp_unit_store_get_column_type
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_unit_store_get_iter
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkTreePath
modifier|*
name|gimp_unit_store_get_path
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_unit_store_tree_model_get_value
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gint
name|column
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_unit_store_iter_next
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_unit_store_iter_children
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreeIter
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_unit_store_iter_has_child
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_unit_store_iter_n_children
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_unit_store_iter_nth_child
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreeIter
modifier|*
name|parent
parameter_list|,
name|gint
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_unit_store_iter_parent
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreeIter
modifier|*
name|child
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpUnitStore
argument_list|,
argument|gimp_unit_store
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GTK_TYPE_TREE_MODEL,                                                 gimp_unit_store_tree_model_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_unit_store_parent_class
end_define

begin_decl_stmt
specifier|static
name|GType
name|column_types
index|[
name|GIMP_UNIT_STORE_UNIT_COLUMNS
index|]
init|=
block|{
name|G_TYPE_INVALID
block|,
name|G_TYPE_DOUBLE
block|,
name|G_TYPE_INT
block|,
name|G_TYPE_STRING
block|,
name|G_TYPE_STRING
block|,
name|G_TYPE_STRING
block|,
name|G_TYPE_STRING
block|,
name|G_TYPE_STRING
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_unit_store_class_init (GimpUnitStoreClass * klass)
name|gimp_unit_store_class_init
parameter_list|(
name|GimpUnitStoreClass
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
name|column_types
index|[
name|GIMP_UNIT_STORE_UNIT
index|]
operator|=
name|GIMP_TYPE_UNIT
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_unit_store_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_unit_store_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_unit_store_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_NUM_VALUES
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-values"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
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
DECL|function|gimp_unit_store_init (GimpUnitStore * store)
name|gimp_unit_store_init
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unit_store_tree_model_init (GtkTreeModelIface * iface)
name|gimp_unit_store_tree_model_init
parameter_list|(
name|GtkTreeModelIface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_flags
operator|=
name|gimp_unit_store_get_flags
expr_stmt|;
name|iface
operator|->
name|get_n_columns
operator|=
name|gimp_unit_store_get_n_columns
expr_stmt|;
name|iface
operator|->
name|get_column_type
operator|=
name|gimp_unit_store_get_column_type
expr_stmt|;
name|iface
operator|->
name|get_iter
operator|=
name|gimp_unit_store_get_iter
expr_stmt|;
name|iface
operator|->
name|get_path
operator|=
name|gimp_unit_store_get_path
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_unit_store_tree_model_get_value
expr_stmt|;
name|iface
operator|->
name|iter_next
operator|=
name|gimp_unit_store_iter_next
expr_stmt|;
name|iface
operator|->
name|iter_children
operator|=
name|gimp_unit_store_iter_children
expr_stmt|;
name|iface
operator|->
name|iter_has_child
operator|=
name|gimp_unit_store_iter_has_child
expr_stmt|;
name|iface
operator|->
name|iter_n_children
operator|=
name|gimp_unit_store_iter_n_children
expr_stmt|;
name|iface
operator|->
name|iter_nth_child
operator|=
name|gimp_unit_store_iter_nth_child
expr_stmt|;
name|iface
operator|->
name|iter_parent
operator|=
name|gimp_unit_store_iter_parent
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unit_store_finalize (GObject * object)
name|gimp_unit_store_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpUnitStore
modifier|*
name|store
init|=
name|GIMP_UNIT_STORE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|store
operator|->
name|num_values
operator|>
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|store
operator|->
name|values
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|store
operator|->
name|resolutions
argument_list|)
expr_stmt|;
name|store
operator|->
name|num_values
operator|=
literal|0
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
DECL|function|gimp_unit_store_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_unit_store_set_property
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
name|GimpUnitStore
modifier|*
name|store
init|=
name|GIMP_UNIT_STORE
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
name|PROP_NUM_VALUES
case|:
name|g_return_if_fail
argument_list|(
name|store
operator|->
name|num_values
operator|==
literal|0
argument_list|)
expr_stmt|;
name|store
operator|->
name|num_values
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|store
operator|->
name|num_values
condition|)
block|{
name|store
operator|->
name|values
operator|=
name|g_new0
argument_list|(
name|gdouble
argument_list|,
name|store
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|store
operator|->
name|resolutions
operator|=
name|g_new0
argument_list|(
name|gdouble
argument_list|,
name|store
operator|->
name|num_values
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_unit_store_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_unit_store_get_property
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
name|GimpUnitStore
modifier|*
name|store
init|=
name|GIMP_UNIT_STORE
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
name|PROP_NUM_VALUES
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|store
operator|->
name|num_values
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
name|GtkTreeModelFlags
DECL|function|gimp_unit_store_get_flags (GtkTreeModel * tree_model)
name|gimp_unit_store_get_flags
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|)
block|{
return|return
name|GTK_TREE_MODEL_ITERS_PERSIST
operator||
name|GTK_TREE_MODEL_LIST_ONLY
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_unit_store_get_n_columns (GtkTreeModel * tree_model)
name|gimp_unit_store_get_n_columns
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|)
block|{
name|GimpUnitStore
modifier|*
name|store
init|=
name|GIMP_UNIT_STORE
argument_list|(
name|tree_model
argument_list|)
decl_stmt|;
return|return
name|GIMP_UNIT_STORE_UNIT_COLUMNS
operator|+
name|store
operator|->
name|num_values
return|;
block|}
end_function

begin_function
specifier|static
name|GType
DECL|function|gimp_unit_store_get_column_type (GtkTreeModel * tree_model,gint index)
name|gimp_unit_store_get_column_type
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|index
operator|>=
literal|0
argument_list|,
name|G_TYPE_INVALID
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|<
name|GIMP_UNIT_STORE_UNIT_COLUMNS
condition|)
return|return
name|column_types
index|[
name|index
index|]
return|;
return|return
name|G_TYPE_DOUBLE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unit_store_get_iter (GtkTreeModel * tree_model,GtkTreeIter * iter,GtkTreePath * path)
name|gimp_unit_store_get_iter
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|)
block|{
name|gint
name|unit
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gtk_tree_path_get_depth
argument_list|(
name|path
argument_list|)
operator|>
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gtk_tree_path_get_indices
argument_list|(
name|path
argument_list|)
index|[
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|unit
operator|>=
literal|0
operator|&&
name|unit
operator|<
name|gimp_unit_get_number_of_units
argument_list|()
condition|)
block|{
name|iter
operator|->
name|user_data
operator|=
name|GINT_TO_POINTER
argument_list|(
name|unit
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|GtkTreePath
modifier|*
DECL|function|gimp_unit_store_get_path (GtkTreeModel * tree_model,GtkTreeIter * iter)
name|gimp_unit_store_get_path
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GtkTreePath
modifier|*
name|path
init|=
name|gtk_tree_path_new
argument_list|()
decl_stmt|;
name|gtk_tree_path_append_index
argument_list|(
name|path
argument_list|,
name|GPOINTER_TO_INT
argument_list|(
name|iter
operator|->
name|user_data
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|path
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unit_store_tree_model_get_value (GtkTreeModel * tree_model,GtkTreeIter * iter,gint column,GValue * value)
name|gimp_unit_store_tree_model_get_value
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gint
name|column
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpUnitStore
modifier|*
name|store
init|=
name|GIMP_UNIT_STORE
argument_list|(
name|tree_model
argument_list|)
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|column
operator|>=
literal|0
operator|&&
name|column
operator|<
name|GIMP_UNIT_STORE_UNIT_COLUMNS
operator|+
name|store
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
name|value
argument_list|,
name|column
operator|<
name|GIMP_UNIT_STORE_UNIT_COLUMNS
condition|?
name|column_types
index|[
name|column
index|]
else|:
name|G_TYPE_DOUBLE
argument_list|)
expr_stmt|;
name|unit
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|iter
operator|->
name|user_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|>=
literal|0
operator|&&
name|unit
operator|<
name|gimp_unit_get_number_of_units
argument_list|()
condition|)
block|{
switch|switch
condition|(
name|column
condition|)
block|{
case|case
name|GIMP_UNIT_STORE_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_STORE_UNIT_FACTOR
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_STORE_UNIT_DIGITS
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_STORE_UNIT_IDENTIFIER
case|:
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|gimp_unit_get_identifier
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_STORE_UNIT_SYMBOL
case|:
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|gimp_unit_get_symbol
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_STORE_UNIT_ABBREVIATION
case|:
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|gimp_unit_get_abbreviation
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_STORE_UNIT_SINGULAR
case|:
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|gimp_unit_get_singular
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_STORE_UNIT_PLURAL
case|:
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|gimp_unit_get_plural
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|column
operator|-=
name|GIMP_UNIT_STORE_UNIT_COLUMNS
expr_stmt|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|store
operator|->
name|values
index|[
name|column
index|]
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|store
operator|->
name|resolutions
index|[
name|column
index|]
condition|)
block|{
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|store
operator|->
name|values
index|[
name|column
index|]
operator|*
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
operator|/
name|store
operator|->
name|resolutions
index|[
name|column
index|]
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unit_store_iter_next (GtkTreeModel * tree_model,GtkTreeIter * iter)
name|gimp_unit_store_iter_next
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|gint
name|unit
init|=
name|GPOINTER_TO_INT
argument_list|(
name|iter
operator|->
name|user_data
argument_list|)
decl_stmt|;
name|unit
operator|++
expr_stmt|;
if|if
condition|(
name|unit
operator|>
literal|0
operator|&&
name|unit
operator|<
name|gimp_unit_get_number_of_units
argument_list|()
condition|)
block|{
name|iter
operator|->
name|user_data
operator|=
name|GINT_TO_POINTER
argument_list|(
name|unit
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unit_store_iter_children (GtkTreeModel * tree_model,GtkTreeIter * iter,GtkTreeIter * parent)
name|gimp_unit_store_iter_children
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreeIter
modifier|*
name|parent
parameter_list|)
block|{
comment|/* this is a list, nodes have no children */
if|if
condition|(
name|parent
condition|)
return|return
name|FALSE
return|;
name|iter
operator|->
name|user_data
operator|=
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unit_store_iter_has_child (GtkTreeModel * tree_model,GtkTreeIter * iter)
name|gimp_unit_store_iter_has_child
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_unit_store_iter_n_children (GtkTreeModel * tree_model,GtkTreeIter * iter)
name|gimp_unit_store_iter_n_children
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
if|if
condition|(
name|iter
condition|)
return|return
literal|0
return|;
return|return
name|gimp_unit_get_number_of_units
argument_list|()
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unit_store_iter_nth_child (GtkTreeModel * tree_model,GtkTreeIter * iter,GtkTreeIter * parent,gint n)
name|gimp_unit_store_iter_nth_child
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreeIter
modifier|*
name|parent
parameter_list|,
name|gint
name|n
parameter_list|)
block|{
name|GimpUnitStore
modifier|*
name|store
decl_stmt|;
if|if
condition|(
name|parent
condition|)
return|return
name|FALSE
return|;
name|store
operator|=
name|GIMP_UNIT_STORE
argument_list|(
name|tree_model
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|>=
literal|0
operator|&&
name|n
operator|<
name|gimp_unit_get_number_of_units
argument_list|()
condition|)
block|{
name|iter
operator|->
name|user_data
operator|=
name|GINT_TO_POINTER
argument_list|(
name|n
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unit_store_iter_parent (GtkTreeModel * tree_model,GtkTreeIter * iter,GtkTreeIter * child)
name|gimp_unit_store_iter_parent
parameter_list|(
name|GtkTreeModel
modifier|*
name|tree_model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GtkTreeIter
modifier|*
name|child
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GimpUnitStore
modifier|*
DECL|function|gimp_unit_store_new (gint num_values)
name|gimp_unit_store_new
parameter_list|(
name|gint
name|num_values
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNIT_STORE
argument_list|,
literal|"num-values"
argument_list|,
name|num_values
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unit_store_set_pixel_value (GimpUnitStore * store,gint index,gdouble value)
name|gimp_unit_store_set_pixel_value
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gint
name|index
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNIT_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|index
operator|>
literal|0
operator|&&
name|index
operator|<
name|store
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|store
operator|->
name|values
index|[
name|index
index|]
operator|=
name|value
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unit_store_set_pixel_values (GimpUnitStore * store,gdouble first_value,...)
name|gimp_unit_store_set_pixel_values
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gdouble
name|first_value
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNIT_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_value
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
name|store
operator|->
name|num_values
condition|;
control|)
block|{
name|store
operator|->
name|values
index|[
name|i
index|]
operator|=
name|first_value
expr_stmt|;
if|if
condition|(
operator|++
name|i
operator|<
name|store
operator|->
name|num_values
condition|)
name|first_value
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gdouble
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unit_store_set_resolution (GimpUnitStore * store,gint index,gdouble resolution)
name|gimp_unit_store_set_resolution
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gint
name|index
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNIT_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|index
operator|>
literal|0
operator|&&
name|index
operator|<
name|store
operator|->
name|num_values
argument_list|)
expr_stmt|;
name|store
operator|->
name|resolutions
index|[
name|index
index|]
operator|=
name|resolution
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unit_store_set_resolutions (GimpUnitStore * store,gdouble first_resolution,...)
name|gimp_unit_store_set_resolutions
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|gdouble
name|first_resolution
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNIT_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_resolution
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
name|store
operator|->
name|num_values
condition|;
control|)
block|{
name|store
operator|->
name|resolutions
index|[
name|i
index|]
operator|=
name|first_resolution
expr_stmt|;
if|if
condition|(
operator|++
name|i
operator|<
name|store
operator|->
name|num_values
condition|)
name|first_resolution
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gdouble
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_unit_store_get_value (GimpUnitStore * store,GimpUnit unit,gint index)
name|gimp_unit_store_get_value
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|GValue
name|value
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UNIT_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|index
operator|>=
literal|0
operator|&&
name|index
operator|<
name|store
operator|->
name|num_values
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|iter
operator|.
name|user_data
operator|=
name|GINT_TO_POINTER
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|gimp_unit_store_tree_model_get_value
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_UNIT_STORE_FIRST_VALUE
operator|+
name|index
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
return|return
name|g_value_get_double
argument_list|(
operator|&
name|value
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unit_store_get_values (GimpUnitStore * store,GimpUnit unit,gdouble * first_value,...)
name|gimp_unit_store_get_values
parameter_list|(
name|GimpUnitStore
modifier|*
name|store
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
modifier|*
name|first_value
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNIT_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_value
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
name|store
operator|->
name|num_values
condition|;
control|)
block|{
if|if
condition|(
name|first_value
condition|)
operator|*
name|first_value
operator|=
name|gimp_unit_store_get_value
argument_list|(
name|store
argument_list|,
name|unit
argument_list|,
name|i
argument_list|)
expr_stmt|;
if|if
condition|(
operator|++
name|i
operator|<
name|store
operator|->
name|num_values
condition|)
name|first_value
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gdouble
operator|*
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

