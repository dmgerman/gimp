begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplanguagestore.c  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_function
specifier|static
name|void
name|gimp_language_store_class_init
parameter_list|(
name|GimpLanguageStoreClass
modifier|*
name|klass
parameter_list|)
block|{ }
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
name|gimp_language_store_populate
argument_list|(
name|store
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|void
DECL|function|gimp_language_store_add (GimpLanguageStore * store,const gchar * lang,const gchar * code)
name|gimp_language_store_add
parameter_list|(
name|GimpLanguageStore
modifier|*
name|store
parameter_list|,
specifier|const
name|gchar
modifier|*
name|lang
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_LANGUAGE_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|lang
operator|!=
name|NULL
operator|&&
name|code
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|GIMP_LANGUAGE_STORE_LANGUAGE
argument_list|,
name|lang
argument_list|,
name|GIMP_LANGUAGE_STORE_ISO_639_1
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
name|GIMP_LANGUAGE_STORE_ISO_639_1
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

