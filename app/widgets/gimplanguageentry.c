begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplanguageentry.c  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* GimpLanguageEntry is an entry widget that provides completion on  * translated language names. It is suited for specifying the language  * a text is written in.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimplanguageentry.h"
end_include

begin_include
include|#
directive|include
file|"gimplanguagestore.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2871a7920103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MODEL
name|PROP_MODEL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpLanguageEntry
struct|struct
name|_GimpLanguageEntry
block|{
DECL|member|parent_instance
name|GtkEntry
name|parent_instance
decl_stmt|;
DECL|member|store
name|GtkListStore
modifier|*
name|store
decl_stmt|;
DECL|member|code
name|gchar
modifier|*
name|code
decl_stmt|;
comment|/*  ISO 639-1 language code  */
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_language_entry_constructed
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
name|gimp_language_entry_finalize
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
name|gimp_language_entry_set_property
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
name|gimp_language_entry_get_property
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
name|gimp_language_entry_language_selected
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|completion
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpLanguageEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpLanguageEntry,gimp_language_entry,GTK_TYPE_ENTRY)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLanguageEntry
argument_list|,
argument|gimp_language_entry
argument_list|,
argument|GTK_TYPE_ENTRY
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_language_entry_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_language_entry_class_init
parameter_list|(
name|GimpLanguageEntryClass
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
name|gimp_language_entry_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_language_entry_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_language_entry_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_language_entry_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MODEL
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"model"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_LANGUAGE_STORE
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
DECL|function|gimp_language_entry_init (GimpLanguageEntry * entry)
name|gimp_language_entry_init
parameter_list|(
name|GimpLanguageEntry
modifier|*
name|entry
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_language_entry_constructed (GObject * object)
name|gimp_language_entry_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpLanguageEntry
modifier|*
name|entry
init|=
name|GIMP_LANGUAGE_ENTRY
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
if|if
condition|(
name|entry
operator|->
name|store
condition|)
block|{
name|GtkEntryCompletion
modifier|*
name|completion
decl_stmt|;
name|completion
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_ENTRY_COMPLETION
argument_list|,
literal|"model"
argument_list|,
name|entry
operator|->
name|store
argument_list|,
literal|"inline-selection"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Note that we must use this function to set the text column,        * otherwise we won't get a cell renderer for free.        */
name|gtk_entry_completion_set_text_column
argument_list|(
name|completion
argument_list|,
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|)
expr_stmt|;
name|gtk_entry_set_completion
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|completion
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|completion
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|completion
argument_list|,
literal|"match-selected"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_language_entry_language_selected
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_language_entry_finalize (GObject * object)
name|gimp_language_entry_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpLanguageEntry
modifier|*
name|entry
init|=
name|GIMP_LANGUAGE_ENTRY
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|entry
operator|->
name|store
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|entry
operator|->
name|code
argument_list|,
name|g_free
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
DECL|function|gimp_language_entry_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_language_entry_set_property
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
name|GimpLanguageEntry
modifier|*
name|entry
init|=
name|GIMP_LANGUAGE_ENTRY
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
name|PROP_MODEL
case|:
name|g_return_if_fail
argument_list|(
name|entry
operator|->
name|store
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|->
name|store
operator|=
name|g_value_dup_object
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
DECL|function|gimp_language_entry_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_language_entry_get_property
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
name|GimpLanguageEntry
modifier|*
name|entry
init|=
name|GIMP_LANGUAGE_ENTRY
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
name|PROP_MODEL
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|entry
operator|->
name|store
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
name|gboolean
DECL|function|gimp_language_entry_language_selected (GtkEntryCompletion * completion,GtkTreeModel * model,GtkTreeIter * iter,GimpLanguageEntry * entry)
name|gimp_language_entry_language_selected
parameter_list|(
name|GtkEntryCompletion
modifier|*
name|completion
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|GimpLanguageEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_free
argument_list|(
name|entry
operator|->
name|code
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_LANGUAGE_STORE_CODE
argument_list|,
operator|&
name|entry
operator|->
name|code
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_language_entry_new (void)
name|gimp_language_entry_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|store
operator|=
name|gimp_language_store_new
argument_list|()
expr_stmt|;
name|entry
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LANGUAGE_ENTRY
argument_list|,
literal|"model"
argument_list|,
name|store
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
return|return
name|entry
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_language_entry_get_code (GimpLanguageEntry * entry)
name|gimp_language_entry_get_code
parameter_list|(
name|GimpLanguageEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LANGUAGE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|entry
operator|->
name|code
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_language_entry_set_code (GimpLanguageEntry * entry,const gchar * code)
name|gimp_language_entry_set_code
parameter_list|(
name|GimpLanguageEntry
modifier|*
name|entry
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LANGUAGE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|entry
operator|->
name|code
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|code
operator|||
operator|!
name|strlen
argument_list|(
name|code
argument_list|)
condition|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|""
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|gimp_language_store_lookup
argument_list|(
name|GIMP_LANGUAGE_STORE
argument_list|(
name|entry
operator|->
name|store
argument_list|)
argument_list|,
name|code
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|label
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|entry
operator|->
name|store
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|,
operator|&
name|label
argument_list|,
name|GIMP_LANGUAGE_STORE_CODE
argument_list|,
operator|&
name|entry
operator|->
name|code
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
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

end_unit

