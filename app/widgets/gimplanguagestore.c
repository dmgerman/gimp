begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplanguagestore.c  * Copyright (C) 2008, 2009  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimplanguagestore.h"
end_include

begin_include
include|#
directive|include
file|"gimplanguagestore-parser.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_language_store_constructed
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
name|gimp_language_store_real_add
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_language_store_sort
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|a
parameter_list|,
name|GtkTreeIter
modifier|*
name|b
parameter_list|,
name|gpointer
name|userdata
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpLanguageStore,gimp_language_store,GTK_TYPE_LIST_STORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLanguageStore
argument_list|,
argument|gimp_language_store
argument_list|,
argument|GTK_TYPE_LIST_STORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_language_store_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_language_store_class_init
parameter_list|(
name|GimpLanguageStoreClass
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
name|gimp_language_store_constructed
expr_stmt|;
name|klass
operator|->
name|add
operator|=
name|gimp_language_store_real_add
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_language_store_init (GimpLanguageStore * store)
name|gimp_language_store_init
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|)
block|{
name|GType
name|column_types
index|[
literal|2
index|]
init|=
block|{
name|G_TYPE_STRING
block|,
name|G_TYPE_STRING
block|}
decl_stmt|;
name|gtk_list_store_set_column_types
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|column_types
argument_list|)
argument_list|,
name|column_types
argument_list|)
expr_stmt|;
name|gtk_tree_sortable_set_sort_func
argument_list|(
name|GTK_TREE_SORTABLE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|,
name|gimp_language_store_sort
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_sortable_set_sort_column_id
argument_list|(
name|GTK_TREE_SORTABLE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|,
name|GTK_SORT_ASCENDING
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_language_store_constructed (GObject * object)
name|gimp_language_store_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GHashTable
modifier|*
name|lang_list
decl_stmt|;
name|GHashTableIter
name|lang_iter
decl_stmt|;
name|gpointer
name|code
decl_stmt|;
name|gpointer
name|name
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
name|lang_list
operator|=
name|gimp_language_store_parser_get_languages
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|lang_list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_iter_init
argument_list|(
operator|&
name|lang_iter
argument_list|,
name|lang_list
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_hash_table_iter_next
argument_list|(
operator|&
name|lang_iter
argument_list|,
operator|&
name|code
argument_list|,
operator|&
name|name
argument_list|)
condition|)
name|GIMP_LANGUAGE_STORE_GET_CLASS
argument_list|(
name|object
argument_list|)
operator|->
name|add
argument_list|(
name|GIMP_LANGUAGE_STORE
argument_list|(
name|object
argument_list|)
argument_list|,
name|name
argument_list|,
name|code
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_language_store_real_add (GimpLanguageStore * store,const gchar * label,const gchar * code)
name|gimp_language_store_real_add
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|gtk_list_store_append
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
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
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|,
name|label
argument_list|,
name|GIMP_LANGUAGE_STORE_CODE
argument_list|,
name|code
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_language_store_sort (GtkTreeModel * model,GtkTreeIter * a,GtkTreeIter * b,gpointer userdata)
name|gimp_language_store_sort
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|a
parameter_list|,
name|GtkTreeIter
modifier|*
name|b
parameter_list|,
name|gpointer
name|userdata
parameter_list|)
block|{
name|GValue
name|avalue
init|=
name|G_VALUE_INIT
decl_stmt|;
name|GValue
name|bvalue
init|=
name|G_VALUE_INIT
decl_stmt|;
name|gint
name|cmp
init|=
literal|0
decl_stmt|;
comment|/*  keep system language at the top of the list  */
name|gtk_tree_model_get_value
argument_list|(
name|model
argument_list|,
name|a
argument_list|,
name|GIMP_LANGUAGE_STORE_CODE
argument_list|,
operator|&
name|avalue
argument_list|)
expr_stmt|;
name|gtk_tree_model_get_value
argument_list|(
name|model
argument_list|,
name|b
argument_list|,
name|GIMP_LANGUAGE_STORE_CODE
argument_list|,
operator|&
name|bvalue
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_strcmp0
argument_list|(
literal|""
argument_list|,
name|g_value_get_string
argument_list|(
operator|&
name|avalue
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
name|cmp
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|g_strcmp0
argument_list|(
literal|""
argument_list|,
name|g_value_get_string
argument_list|(
operator|&
name|bvalue
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
name|cmp
operator|=
literal|1
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|avalue
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|bvalue
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmp
condition|)
return|return
name|cmp
return|;
comment|/*  sort labels alphabetically  */
name|gtk_tree_model_get_value
argument_list|(
name|model
argument_list|,
name|a
argument_list|,
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|,
operator|&
name|avalue
argument_list|)
expr_stmt|;
name|gtk_tree_model_get_value
argument_list|(
name|model
argument_list|,
name|b
argument_list|,
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|,
operator|&
name|bvalue
argument_list|)
expr_stmt|;
name|cmp
operator|=
name|g_utf8_collate
argument_list|(
name|g_value_get_string
argument_list|(
operator|&
name|avalue
argument_list|)
argument_list|,
name|g_value_get_string
argument_list|(
operator|&
name|bvalue
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|avalue
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|bvalue
argument_list|)
expr_stmt|;
return|return
name|cmp
return|;
block|}
end_function

begin_function
name|GtkListStore
modifier|*
DECL|function|gimp_language_store_new (void)
name|gimp_language_store_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_LANGUAGE_STORE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_language_store_lookup (GimpLanguageStore * store,const gchar * code,GtkTreeIter * iter)
name|gimp_language_store_lookup
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|hyphen
decl_stmt|;
name|gint
name|len
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LANGUAGE_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|code
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|iter
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  We accept the code in RFC-3066 format here and only look at what's    *  before the first hyphen.    */
name|hyphen
operator|=
name|strchr
argument_list|(
name|code
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
if|if
condition|(
name|hyphen
condition|)
name|len
operator|=
name|hyphen
operator|-
name|code
expr_stmt|;
else|else
name|len
operator|=
name|strlen
argument_list|(
name|code
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
name|iter
argument_list|)
control|)
block|{
name|gchar
modifier|*
name|value
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_LANGUAGE_STORE_CODE
argument_list|,
operator|&
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|&&
name|strncmp
argument_list|(
name|code
argument_list|,
name|value
argument_list|,
name|len
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|iter_valid
return|;
block|}
end_function

end_unit

