begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasitelist.c: Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"parasitelist.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29e333330103
block|{
DECL|enumerator|ADD
name|ADD
block|,
DECL|enumerator|REMOVE
name|REMOVE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|parasite_list_destroy
parameter_list|(
name|GtkObject
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|parasite_list_init
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|parasite_list_class_init
parameter_list|(
name|ParasiteListClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|free_a_parasite
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|parasite
parameter_list|,
name|gpointer
name|unused
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parasite_list_signals
specifier|static
name|guint
name|parasite_list_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|parasite_list_init (ParasiteList * list)
name|parasite_list_init
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|list
operator|->
name|table
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parasite_list_class_init (ParasiteListClass * klass)
name|parasite_list_class_init
parameter_list|(
name|ParasiteListClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parasite_list_signals
index|[
name|ADD
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"add"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|ParasiteListClass
argument_list|,
name|add
argument_list|)
argument_list|,
name|gtk_marshal_NONE__POINTER
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GTK_TYPE_POINTER
argument_list|)
expr_stmt|;
name|parasite_list_signals
index|[
name|REMOVE
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"remove"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|ParasiteListClass
argument_list|,
name|remove
argument_list|)
argument_list|,
name|gtk_marshal_NONE__POINTER
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GTK_TYPE_POINTER
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|parasite_list_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|parasite_list_destroy
expr_stmt|;
name|klass
operator|->
name|add
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|remove
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|parasite_list_get_type (void)
name|parasite_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|GtkTypeInfo
name|info
init|=
block|{
literal|"ParasiteList"
block|,
sizeof|sizeof
argument_list|(
name|ParasiteList
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|ParasiteListClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|parasite_list_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|parasite_list_init
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|ParasiteList
modifier|*
DECL|function|parasite_list_new (void)
name|parasite_list_new
parameter_list|(
name|void
parameter_list|)
block|{
name|ParasiteList
modifier|*
name|list
init|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_PARASITE_LIST
argument_list|)
decl_stmt|;
name|list
operator|->
name|table
operator|=
name|NULL
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|free_a_parasite (void * key,void * parasite,void * unused)
name|free_a_parasite
parameter_list|(
name|void
modifier|*
name|key
parameter_list|,
name|void
modifier|*
name|parasite
parameter_list|,
name|void
modifier|*
name|unused
parameter_list|)
block|{
name|gimp_parasite_free
argument_list|(
operator|(
name|GimpParasite
operator|*
operator|)
name|parasite
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parasite_list_destroy (GtkObject * obj)
name|parasite_list_destroy
parameter_list|(
name|GtkObject
modifier|*
name|obj
parameter_list|)
block|{
name|ParasiteList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|obj
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|obj
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
operator|(
name|ParasiteList
operator|*
operator|)
name|obj
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
block|{
name|g_hash_table_foreach_remove
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|free_a_parasite
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_hash_table_destroy
argument_list|(
name|list
operator|->
name|table
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|parasite_copy_one (void * key,void * p,void * data)
name|parasite_copy_one
parameter_list|(
name|void
modifier|*
name|key
parameter_list|,
name|void
modifier|*
name|p
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|ParasiteList
modifier|*
name|list
init|=
operator|(
name|ParasiteList
operator|*
operator|)
name|data
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
operator|(
name|GimpParasite
operator|*
operator|)
name|p
decl_stmt|;
name|parasite_list_add
argument_list|(
name|list
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ParasiteList
modifier|*
DECL|function|parasite_list_copy (const ParasiteList * list)
name|parasite_list_copy
parameter_list|(
specifier|const
name|ParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|ParasiteList
modifier|*
name|newlist
decl_stmt|;
name|newlist
operator|=
name|parasite_list_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
name|g_hash_table_foreach
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|parasite_copy_one
argument_list|,
name|newlist
argument_list|)
expr_stmt|;
return|return
name|newlist
return|;
block|}
end_function

begin_function
name|void
DECL|function|parasite_list_add (ParasiteList * list,GimpParasite * p)
name|parasite_list_add
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
name|GimpParasite
modifier|*
name|p
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
operator|==
name|NULL
condition|)
name|list
operator|->
name|table
operator|=
name|g_hash_table_new
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|p
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|p
operator|->
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|parasite_list_remove
argument_list|(
name|list
argument_list|,
name|p
operator|->
name|name
argument_list|)
expr_stmt|;
name|p
operator|=
name|gimp_parasite_copy
argument_list|(
name|p
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|p
operator|->
name|name
argument_list|,
name|p
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
name|parasite_list_signals
index|[
name|ADD
index|]
argument_list|,
name|p
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|parasite_list_remove (ParasiteList * list,const gchar * name)
name|parasite_list_remove
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|p
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
block|{
name|p
operator|=
name|parasite_list_find
argument_list|(
name|list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
block|{
name|g_hash_table_remove
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
name|parasite_list_signals
index|[
name|REMOVE
index|]
argument_list|,
name|p
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|gint
DECL|function|parasite_list_length (ParasiteList * list)
name|parasite_list_length
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
operator|->
name|table
condition|)
return|return
literal|0
return|;
return|return
name|g_hash_table_size
argument_list|(
name|list
operator|->
name|table
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ppcount_func (gchar * key,GimpParasite * p,gint * count)
name|ppcount_func
parameter_list|(
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|p
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
block|{
if|if
condition|(
name|gimp_parasite_is_persistent
argument_list|(
name|p
argument_list|)
condition|)
operator|*
name|count
operator|=
operator|*
name|count
operator|+
literal|1
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|parasite_list_persistent_length (ParasiteList * list)
name|parasite_list_persistent_length
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|)
block|{
name|gint
name|ppcount
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
operator|->
name|table
condition|)
return|return
literal|0
return|;
name|parasite_list_foreach
argument_list|(
name|list
argument_list|,
operator|(
name|GHFunc
operator|)
name|ppcount_func
argument_list|,
operator|&
name|ppcount
argument_list|)
expr_stmt|;
return|return
name|ppcount
return|;
block|}
end_function

begin_function
name|void
DECL|function|parasite_list_foreach (ParasiteList * list,GHFunc function,gpointer user_data)
name|parasite_list_foreach
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
name|GHFunc
name|function
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|list
operator|->
name|table
condition|)
return|return;
name|g_hash_table_foreach
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|function
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpParasite
modifier|*
DECL|function|parasite_list_find (ParasiteList * list,const gchar * name)
name|parasite_list_find
parameter_list|(
name|ParasiteList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|table
condition|)
return|return
operator|(
name|GimpParasite
operator|*
operator|)
name|g_hash_table_lookup
argument_list|(
name|list
operator|->
name|table
argument_list|,
name|name
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|parasite_shift_parent (GimpParasite * p)
name|parasite_shift_parent
parameter_list|(
name|GimpParasite
modifier|*
name|p
parameter_list|)
block|{
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
return|return;
name|p
operator|->
name|flags
operator|=
operator|(
name|p
operator|->
name|flags
operator|>>
literal|8
operator|)
expr_stmt|;
block|}
end_function

end_unit

