begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_include
include|#
directive|include
file|"gimpsetP.h"
end_include

begin_comment
comment|/* Yep, this can be optimized quite a lot */
end_comment

begin_typedef
DECL|struct|_GimpSetHandler
typedef|typedef
struct|struct
name|_GimpSetHandler
block|{
DECL|member|signame
specifier|const
name|gchar
modifier|*
name|signame
decl_stmt|;
DECL|member|func
name|GtkSignalFunc
name|func
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|typedef|GimpSetHandler
block|}
name|GimpSetHandler
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b99f3160108
block|{
DECL|member|object
name|gpointer
name|object
decl_stmt|;
DECL|member|handlers
name|GArray
modifier|*
name|handlers
decl_stmt|;
DECL|member|destroy_handler
name|guint
name|destroy_handler
decl_stmt|;
DECL|typedef|Node
block|}
name|Node
typedef|;
end_typedef

begin_enum
enum|enum
DECL|enum|__anon2b99f3160203
block|{
DECL|enumerator|ADD
name|ADD
block|,
DECL|enumerator|REMOVE
name|REMOVE
block|,
DECL|enumerator|ACTIVE_CHANGED
name|ACTIVE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|Node
modifier|*
name|gimp_set_find_node
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Node
modifier|*
name|gimp_set_node_new
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|obbject
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_set_node_free
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|Node
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_set_signals
specifier|static
name|guint
name|gimp_set_signals
index|[
name|LAST_SIGNAL
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_set_destroy (GtkObject * object)
name|gimp_set_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSet
modifier|*
name|set
init|=
name|GIMP_SET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|set
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|gimp_set_node_free
argument_list|(
name|set
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|set
operator|->
name|list
argument_list|)
expr_stmt|;
name|g_array_free
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
operator|)
operator|(
name|object
operator|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_init (GimpSet * set)
name|gimp_set_init
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|)
block|{
name|set
operator|->
name|list
operator|=
name|NULL
expr_stmt|;
name|set
operator|->
name|type
operator|=
name|GTK_TYPE_OBJECT
expr_stmt|;
name|set
operator|->
name|handlers
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpSetHandler
argument_list|)
argument_list|)
expr_stmt|;
name|set
operator|->
name|active_element
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_class_init (GimpSetClass * klass)
name|gimp_set_class_init
parameter_list|(
name|GimpSetClass
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
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gimp_object_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_set_signals
index|[
name|ADD
index|]
operator|=
name|gimp_signal_new
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
name|GimpSetClass
argument_list|,
name|add
argument_list|)
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gimp_set_signals
index|[
name|REMOVE
index|]
operator|=
name|gimp_signal_new
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
name|GimpSetClass
argument_list|,
name|remove
argument_list|)
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gimp_set_signals
index|[
name|ACTIVE_CHANGED
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"active_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpSetClass
argument_list|,
name|active_changed
argument_list|)
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_set_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_set_destroy
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
name|klass
operator|->
name|active_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_set_get_type (void)
name|gimp_set_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|gimpset_type
init|=
literal|0
decl_stmt|;
name|GIMP_TYPE_INIT
argument_list|(
name|gimpset_type
argument_list|,
name|GimpSet
argument_list|,
name|GimpSetClass
argument_list|,
name|gimp_set_init
argument_list|,
name|gimp_set_class_init
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
return|return
name|gimpset_type
return|;
block|}
end_function

begin_function
name|GimpSet
modifier|*
DECL|function|gimp_set_new (GtkType type,gboolean weak)
name|gimp_set_new
parameter_list|(
name|GtkType
name|type
parameter_list|,
name|gboolean
name|weak
parameter_list|)
block|{
name|GimpSet
modifier|*
name|set
decl_stmt|;
comment|/*  untyped sets must not be weak, since we can't attach a    *  destroy handler    */
name|g_assert
argument_list|(
operator|!
operator|(
name|type
operator|==
name|GTK_TYPE_NONE
operator|&&
name|weak
operator|==
name|TRUE
operator|)
argument_list|)
expr_stmt|;
name|set
operator|=
name|gtk_type_new
argument_list|(
name|gimp_set_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|set
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|set
operator|->
name|weak
operator|=
name|weak
expr_stmt|;
return|return
name|set
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_destroy_cb (GtkObject * object,gpointer data)
name|gimp_set_destroy_cb
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpSet
modifier|*
name|set
init|=
name|GIMP_SET
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_set_remove
argument_list|(
name|set
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Node
modifier|*
DECL|function|gimp_set_find_node (GimpSet * set,gpointer object)
name|gimp_set_find_node
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
name|GSList
modifier|*
name|list
init|=
name|set
operator|->
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|set
operator|->
name|list
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
name|Node
modifier|*
name|node
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|node
operator|->
name|object
operator|==
name|object
condition|)
return|return
name|node
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|Node
modifier|*
DECL|function|gimp_set_node_new (GimpSet * set,gpointer object)
name|gimp_set_node_new
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|Node
modifier|*
name|node
init|=
name|g_new
argument_list|(
name|Node
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|node
operator|->
name|object
operator|=
name|object
expr_stmt|;
name|node
operator|->
name|handlers
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|guint
argument_list|)
argument_list|)
expr_stmt|;
name|g_array_set_size
argument_list|(
name|node
operator|->
name|handlers
argument_list|,
name|set
operator|->
name|handlers
operator|->
name|len
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
name|node
operator|->
name|handlers
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpSetHandler
modifier|*
name|handler
init|=
operator|&
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|handler
operator|->
name|signame
condition|)
name|g_array_index
argument_list|(
name|node
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|i
argument_list|)
operator|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|handler
operator|->
name|signame
argument_list|,
name|handler
operator|->
name|func
argument_list|,
name|handler
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|set
operator|->
name|weak
condition|)
name|node
operator|->
name|destroy_handler
operator|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_set_destroy_cb
argument_list|)
argument_list|,
name|set
argument_list|)
expr_stmt|;
return|return
name|node
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_node_free (GimpSet * set,Node * node)
name|gimp_set_node_free
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|Node
modifier|*
name|node
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|GimpObject
modifier|*
name|object
init|=
name|node
operator|->
name|object
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|set
operator|->
name|handlers
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpSetHandler
modifier|*
name|handler
init|=
operator|&
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|handler
operator|->
name|signame
condition|)
name|gtk_signal_disconnect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|g_array_index
argument_list|(
name|node
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|set
operator|->
name|weak
condition|)
name|gtk_signal_disconnect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|node
operator|->
name|destroy_handler
argument_list|)
expr_stmt|;
name|g_array_free
argument_list|(
name|node
operator|->
name|handlers
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|node
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_set_add (GimpSet * set,gpointer val)
name|gimp_set_add
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|set
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|set
operator|->
name|type
operator|!=
name|GTK_TYPE_NONE
condition|)
name|g_return_val_if_fail
argument_list|(
name|GTK_CHECK_TYPE
argument_list|(
name|val
argument_list|,
name|set
operator|->
name|type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_set_find_node
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|set
operator|->
name|list
operator|=
name|g_slist_prepend
argument_list|(
name|set
operator|->
name|list
argument_list|,
name|gimp_set_node_new
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|set
argument_list|)
argument_list|,
name|gimp_set_signals
index|[
name|ADD
index|]
argument_list|,
name|val
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_set_remove (GimpSet * set,gpointer val)
name|gimp_set_remove
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
name|Node
modifier|*
name|node
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|set
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|node
operator|=
name|gimp_set_find_node
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|node
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|set
argument_list|)
argument_list|,
name|gimp_set_signals
index|[
name|REMOVE
index|]
argument_list|,
name|val
argument_list|)
expr_stmt|;
name|gimp_set_node_free
argument_list|(
name|set
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|set
operator|->
name|list
operator|=
name|g_slist_remove
argument_list|(
name|set
operator|->
name|list
argument_list|,
name|node
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_set_have (GimpSet * set,gpointer val)
name|gimp_set_have
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
return|return
operator|!
operator|!
name|gimp_set_find_node
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_foreach (GimpSet * set,GFunc func,gpointer user_data)
name|gimp_set_foreach
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|set
operator|->
name|list
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
name|Node
modifier|*
name|node
init|=
name|list
operator|->
name|data
decl_stmt|;
name|func
argument_list|(
name|node
operator|->
name|object
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_set_type (GimpSet * set)
name|gimp_set_type
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|)
block|{
return|return
name|set
operator|->
name|type
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_set_active (GimpSet * set,gpointer object)
name|gimp_set_set_active
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
if|if
condition|(
name|object
operator|!=
name|set
operator|->
name|active_element
operator|&&
name|gimp_set_have
argument_list|(
name|set
argument_list|,
name|object
argument_list|)
condition|)
block|{
name|set
operator|->
name|active_element
operator|=
name|object
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|set
argument_list|)
argument_list|,
name|gimp_set_signals
index|[
name|ACTIVE_CHANGED
index|]
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gpointer
DECL|function|gimp_set_get_active (GimpSet * set)
name|gimp_set_get_active
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|)
block|{
if|if
condition|(
name|gimp_set_have
argument_list|(
name|set
argument_list|,
name|set
operator|->
name|active_element
argument_list|)
condition|)
return|return
name|set
operator|->
name|active_element
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpSetHandlerId
DECL|function|gimp_set_add_handler (GimpSet * set,const gchar * signame,GtkSignalFunc handler,gpointer user_data)
name|gimp_set_add_handler
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signame
parameter_list|,
name|GtkSignalFunc
name|handler
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpSetHandler
name|set_handler
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|guint
name|a
decl_stmt|;
name|g_assert
argument_list|(
name|signame
argument_list|)
expr_stmt|;
comment|/*  you can't set a handler on something that's not a GTK object  */
name|g_assert
argument_list|(
name|set
operator|->
name|type
operator|!=
name|GTK_TYPE_NONE
argument_list|)
expr_stmt|;
name|set_handler
operator|.
name|signame
operator|=
name|signame
expr_stmt|;
name|set_handler
operator|.
name|func
operator|=
name|handler
expr_stmt|;
name|set_handler
operator|.
name|user_data
operator|=
name|user_data
expr_stmt|;
for|for
control|(
name|a
operator|=
literal|0
init|;
name|a
operator|<
name|set
operator|->
name|handlers
operator|->
name|len
condition|;
name|a
operator|++
control|)
if|if
condition|(
operator|!
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|a
argument_list|)
operator|.
name|signame
condition|)
break|break;
if|if
condition|(
name|a
operator|<
name|set
operator|->
name|handlers
operator|->
name|len
condition|)
block|{
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|a
argument_list|)
operator|=
name|set_handler
expr_stmt|;
for|for
control|(
name|list
operator|=
name|set
operator|->
name|list
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
name|Node
modifier|*
name|node
init|=
name|list
operator|->
name|data
decl_stmt|;
name|guint
name|i
init|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|node
operator|->
name|object
argument_list|)
argument_list|,
name|signame
argument_list|,
name|handler
argument_list|,
name|user_data
argument_list|)
decl_stmt|;
name|g_array_index
argument_list|(
name|node
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|a
argument_list|)
operator|=
name|i
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_array_append_val
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|set_handler
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|set
operator|->
name|list
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
name|Node
modifier|*
name|node
init|=
name|list
operator|->
name|data
decl_stmt|;
name|guint
name|i
init|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|node
operator|->
name|object
argument_list|)
argument_list|,
name|signame
argument_list|,
name|handler
argument_list|,
name|user_data
argument_list|)
decl_stmt|;
name|g_array_append_val
argument_list|(
name|node
operator|->
name|handlers
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|a
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_remove_handler (GimpSet * set,GimpSetHandlerId id)
name|gimp_set_remove_handler
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|GimpSetHandlerId
name|id
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
comment|/*  you can't remove a signal handler on something that's not a GTK object  */
name|g_return_if_fail
argument_list|(
name|set
operator|->
name|type
operator|!=
name|GTK_TYPE_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|set
operator|->
name|list
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
name|Node
modifier|*
name|node
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gtk_signal_disconnect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|node
operator|->
name|object
argument_list|)
argument_list|,
name|g_array_index
argument_list|(
name|node
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|id
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|id
argument_list|)
operator|.
name|signame
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

