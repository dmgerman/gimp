begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help Browser  * Copyright (C) 1999-2005 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitschel@cs.tu-berlin.de>  *  * queue.c - a history queue  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"queue.h"
end_include

begin_struct
DECL|struct|_Queue
struct|struct
name|_Queue
block|{
DECL|member|queue
name|GList
modifier|*
name|queue
decl_stmt|;
DECL|member|current
name|GList
modifier|*
name|current
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bab59080108
block|{
DECL|member|uri
name|gchar
modifier|*
name|uri
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|typedef|Item
block|}
name|Item
typedef|;
end_typedef

begin_function
specifier|static
name|Item
modifier|*
DECL|function|item_new (const gchar * uri)
name|item_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|Item
modifier|*
name|item
init|=
name|g_new0
argument_list|(
name|Item
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|item
operator|->
name|uri
operator|=
name|g_strdup
argument_list|(
name|uri
argument_list|)
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|item_free (Item * item)
name|item_free
parameter_list|(
name|Item
modifier|*
name|item
parameter_list|)
block|{
name|g_free
argument_list|(
name|item
operator|->
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item
operator|->
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Queue
modifier|*
DECL|function|queue_new (void)
name|queue_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_new0
argument_list|(
name|Queue
argument_list|,
literal|1
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|queue_free (Queue * h)
name|queue_free
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|h
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* needs to free data in list as well! */
if|if
condition|(
name|h
operator|->
name|queue
condition|)
block|{
name|g_list_foreach
argument_list|(
name|h
operator|->
name|queue
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|h
operator|->
name|queue
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|h
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|queue_move_prev (Queue * h,gint skip)
name|queue_move_prev
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gint
name|skip
parameter_list|)
block|{
if|if
condition|(
operator|!
name|h
operator|||
operator|!
name|h
operator|->
name|queue
operator|||
operator|(
name|h
operator|->
name|current
operator|==
name|g_list_first
argument_list|(
name|h
operator|->
name|queue
argument_list|)
operator|)
condition|)
return|return;
name|h
operator|->
name|current
operator|=
name|g_list_previous
argument_list|(
name|h
operator|->
name|current
argument_list|)
expr_stmt|;
while|while
condition|(
name|h
operator|->
name|current
operator|&&
name|skip
operator|--
condition|)
name|h
operator|->
name|current
operator|=
name|g_list_previous
argument_list|(
name|h
operator|->
name|current
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|queue_move_next (Queue * h,gint skip)
name|queue_move_next
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gint
name|skip
parameter_list|)
block|{
if|if
condition|(
operator|!
name|h
operator|||
operator|!
name|h
operator|->
name|queue
operator|||
operator|(
name|h
operator|->
name|current
operator|==
name|g_list_last
argument_list|(
name|h
operator|->
name|queue
argument_list|)
operator|)
condition|)
return|return;
name|h
operator|->
name|current
operator|=
name|g_list_next
argument_list|(
name|h
operator|->
name|current
argument_list|)
expr_stmt|;
while|while
condition|(
name|h
operator|->
name|current
operator|&&
name|skip
operator|--
condition|)
name|h
operator|->
name|current
operator|=
name|g_list_next
argument_list|(
name|h
operator|->
name|current
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|queue_prev (Queue * h,gint skip)
name|queue_prev
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gint
name|skip
parameter_list|)
block|{
name|GList
modifier|*
name|p
decl_stmt|;
name|Item
modifier|*
name|item
decl_stmt|;
if|if
condition|(
operator|!
name|h
operator|||
operator|!
name|h
operator|->
name|queue
operator|||
operator|(
name|h
operator|->
name|current
operator|==
name|g_list_first
argument_list|(
name|h
operator|->
name|queue
argument_list|)
operator|)
condition|)
return|return
name|NULL
return|;
name|p
operator|=
name|g_list_previous
argument_list|(
name|h
operator|->
name|current
argument_list|)
expr_stmt|;
while|while
condition|(
name|p
operator|&&
name|skip
operator|--
condition|)
name|p
operator|=
name|g_list_previous
argument_list|(
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p
condition|)
return|return
name|NULL
return|;
name|item
operator|=
name|p
operator|->
name|data
expr_stmt|;
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|item
operator|->
name|uri
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|queue_next (Queue * h,gint skip)
name|queue_next
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
name|gint
name|skip
parameter_list|)
block|{
name|GList
modifier|*
name|p
decl_stmt|;
name|Item
modifier|*
name|item
decl_stmt|;
if|if
condition|(
operator|!
name|h
operator|||
operator|!
name|h
operator|->
name|queue
operator|||
operator|(
name|h
operator|->
name|current
operator|==
name|g_list_last
argument_list|(
name|h
operator|->
name|queue
argument_list|)
operator|)
condition|)
return|return
name|NULL
return|;
name|p
operator|=
name|g_list_next
argument_list|(
name|h
operator|->
name|current
argument_list|)
expr_stmt|;
while|while
condition|(
name|p
operator|&&
name|skip
operator|--
condition|)
name|p
operator|=
name|g_list_next
argument_list|(
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p
condition|)
return|return
name|NULL
return|;
name|item
operator|=
name|p
operator|->
name|data
expr_stmt|;
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|item
operator|->
name|uri
return|;
block|}
end_function

begin_function
name|void
DECL|function|queue_add (Queue * h,const gchar * uri)
name|queue_add
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|GList
modifier|*
name|trash
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|h
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|h
operator|->
name|current
condition|)
block|{
name|trash
operator|=
name|h
operator|->
name|current
operator|->
name|next
expr_stmt|;
name|h
operator|->
name|current
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
name|h
operator|->
name|queue
operator|=
name|g_list_append
argument_list|(
name|h
operator|->
name|queue
argument_list|,
name|item_new
argument_list|(
name|uri
argument_list|)
argument_list|)
expr_stmt|;
name|h
operator|->
name|current
operator|=
name|g_list_last
argument_list|(
name|h
operator|->
name|queue
argument_list|)
expr_stmt|;
if|if
condition|(
name|trash
condition|)
block|{
name|g_list_foreach
argument_list|(
name|trash
argument_list|,
operator|(
name|GFunc
operator|)
name|item_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|trash
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|queue_set_title (Queue * h,const gchar * title)
name|queue_set_title
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|Item
modifier|*
name|item
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|h
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|h
operator|->
name|current
operator|||
operator|!
name|h
operator|->
name|current
operator|->
name|data
condition|)
return|return;
name|item
operator|=
name|h
operator|->
name|current
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|item
operator|->
name|title
condition|)
name|g_free
argument_list|(
name|item
operator|->
name|title
argument_list|)
expr_stmt|;
name|item
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|queue_has_next (Queue * h)
name|queue_has_next
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
block|{
if|if
condition|(
operator|!
name|h
operator|||
operator|!
name|h
operator|->
name|queue
operator|||
operator|(
name|h
operator|->
name|current
operator|==
name|g_list_last
argument_list|(
name|h
operator|->
name|queue
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|g_list_next
argument_list|(
name|h
operator|->
name|current
argument_list|)
operator|!=
name|NULL
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|queue_has_prev (Queue * h)
name|queue_has_prev
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
block|{
if|if
condition|(
operator|!
name|h
operator|||
operator|!
name|h
operator|->
name|queue
operator|||
operator|(
name|h
operator|->
name|current
operator|==
name|g_list_first
argument_list|(
name|h
operator|->
name|queue
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|g_list_previous
argument_list|(
name|h
operator|->
name|current
argument_list|)
operator|!=
name|NULL
operator|)
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|queue_list_next (Queue * h)
name|queue_list_next
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
block|{
name|GList
modifier|*
name|result
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|queue_has_next
argument_list|(
name|h
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|g_list_next
argument_list|(
name|h
operator|->
name|current
argument_list|)
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
name|Item
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|result
operator|=
name|g_list_prepend
argument_list|(
name|result
argument_list|,
name|item
operator|->
name|title
condition|?
name|item
operator|->
name|title
else|:
name|item
operator|->
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|g_list_reverse
argument_list|(
name|result
argument_list|)
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|queue_list_prev (Queue * h)
name|queue_list_prev
parameter_list|(
name|Queue
modifier|*
name|h
parameter_list|)
block|{
name|GList
modifier|*
name|result
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|queue_has_prev
argument_list|(
name|h
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|g_list_previous
argument_list|(
name|h
operator|->
name|current
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_previous
argument_list|(
name|list
argument_list|)
control|)
block|{
name|Item
modifier|*
name|item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|result
operator|=
name|g_list_prepend
argument_list|(
name|result
argument_list|,
name|item
operator|->
name|title
condition|?
name|item
operator|->
name|title
else|:
name|item
operator|->
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|g_list_reverse
argument_list|(
name|result
argument_list|)
return|;
block|}
end_function

end_unit

