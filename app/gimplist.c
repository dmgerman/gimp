begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_include
include|#
directive|include
file|"gimplistP.h"
end_include

begin_comment
comment|/*  code mostly ripped from nether's gimpset class  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon2961bc910103
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

begin_decl_stmt
DECL|variable|gimp_list_signals
specifier|static
name|guint
name|gimp_list_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_list_add_func
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_list_remove_func
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|gimp_list_destroy (GtkObject * object)
name|gimp_list_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
init|=
name|GIMP_LIST
argument_list|(
name|object
argument_list|)
decl_stmt|;
while|while
condition|(
name|list
operator|->
name|list
condition|)
comment|/* ought to put a sanity check in here... */
block|{
name|gimp_list_remove
argument_list|(
name|list
argument_list|,
name|list
operator|->
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|list
operator|->
name|list
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
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_init (GimpList * list)
name|gimp_list_init
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|)
block|{
name|list
operator|->
name|list
operator|=
name|NULL
expr_stmt|;
name|list
operator|->
name|type
operator|=
name|GTK_TYPE_OBJECT
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_class_init (GimpListClass * klass)
name|gimp_list_class_init
parameter_list|(
name|GimpListClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkType
name|type
init|=
name|object_class
operator|->
name|type
decl_stmt|;
name|parent_class
operator|=
name|gtk_type_parent_class
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_list_destroy
expr_stmt|;
name|gimp_list_signals
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
name|type
argument_list|,
literal|0
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gimp_list_signals
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
name|type
argument_list|,
literal|0
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_list_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|klass
operator|->
name|add
operator|=
name|gimp_list_add_func
expr_stmt|;
name|klass
operator|->
name|remove
operator|=
name|gimp_list_remove_func
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_list_get_type (void)
name|gimp_list_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
decl_stmt|;
name|GIMP_TYPE_INIT
argument_list|(
name|type
argument_list|,
name|GimpList
argument_list|,
name|GimpListClass
argument_list|,
name|gimp_list_init
argument_list|,
name|gimp_list_class_init
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_function
name|GimpList
modifier|*
DECL|function|gimp_list_new (GtkType type,gboolean weak)
name|gimp_list_new
parameter_list|(
name|GtkType
name|type
parameter_list|,
name|gboolean
name|weak
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|gtk_type_new
argument_list|(
name|gimp_list_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|list
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|list
operator|->
name|weak
operator|=
name|weak
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_destroy_cb (GtkObject * object,gpointer data)
name|gimp_list_destroy_cb
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
decl_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_list_remove
argument_list|(
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_add_func (GimpList * list,gpointer object)
name|gimp_list_add_func
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
name|list
operator|->
name|list
operator|=
name|g_slist_prepend
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_list_remove_func (GimpList * list,gpointer object)
name|gimp_list_remove_func
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
name|list
operator|->
name|list
operator|=
name|g_slist_remove
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_list_add (GimpList * list,gpointer object)
name|gimp_list_add
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|list
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_CHECK_TYPE
argument_list|(
name|object
argument_list|,
name|list
operator|->
name|type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_slist_find
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|list
operator|->
name|weak
condition|)
block|{
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
name|gimp_list_destroy_cb
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|GIMP_LIST_CLASS
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
argument_list|)
operator|->
name|klass
argument_list|)
operator|->
name|add
argument_list|(
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
name|gimp_list_signals
index|[
name|ADD
index|]
argument_list|,
name|object
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_list_remove (GimpList * list,gpointer object)
name|gimp_list_remove
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|list
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_slist_find
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_list_remove: can't find val"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|GIMP_LIST_CLASS
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
argument_list|)
operator|->
name|klass
argument_list|)
operator|->
name|remove
argument_list|(
name|list
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|list
argument_list|)
argument_list|,
name|gimp_list_signals
index|[
name|REMOVE
index|]
argument_list|,
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
operator|->
name|weak
condition|)
block|{
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_list_destroy_cb
argument_list|)
argument_list|,
name|list
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_list_have (GimpList * list,gpointer object)
name|gimp_list_have
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|gpointer
name|object
parameter_list|)
block|{
return|return
name|g_slist_find
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|object
argument_list|)
condition|?
name|TRUE
else|:
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_list_foreach (GimpList * list,GFunc func,gpointer user_data)
name|gimp_list_foreach
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|,
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|g_slist_foreach
argument_list|(
name|list
operator|->
name|list
argument_list|,
name|func
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_list_type (GimpList * list)
name|gimp_list_type
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|)
block|{
return|return
name|list
operator|->
name|type
return|;
block|}
end_function

end_unit

