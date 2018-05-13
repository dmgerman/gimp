begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-atomic.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-atomic.h"
end_include

begin_comment
comment|/*  GSList  */
end_comment

begin_decl_stmt
DECL|variable|gimp_atomic_slist_sentinel
specifier|static
name|GSList
name|gimp_atomic_slist_sentinel
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_atomic_slist_push_head (GSList ** list,gpointer data)
name|gimp_atomic_slist_push_head
parameter_list|(
name|GSList
modifier|*
modifier|*
name|list
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GSList
modifier|*
name|old_head
decl_stmt|;
name|GSList
modifier|*
name|new_head
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|new_head
operator|=
name|g_slist_alloc
argument_list|()
expr_stmt|;
name|new_head
operator|->
name|data
operator|=
name|data
expr_stmt|;
do|do
block|{
do|do
block|{
name|old_head
operator|=
name|g_atomic_pointer_get
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|old_head
operator|==
operator|&
name|gimp_atomic_slist_sentinel
condition|)
do|;
name|new_head
operator|->
name|next
operator|=
name|old_head
expr_stmt|;
block|}
do|while
condition|(
operator|!
name|g_atomic_pointer_compare_and_exchange
argument_list|(
name|list
argument_list|,
name|old_head
argument_list|,
name|new_head
argument_list|)
condition|)
do|;
block|}
end_function

begin_function
name|gpointer
DECL|function|gimp_atomic_slist_pop_head (GSList ** list)
name|gimp_atomic_slist_pop_head
parameter_list|(
name|GSList
modifier|*
modifier|*
name|list
parameter_list|)
block|{
name|GSList
modifier|*
name|old_head
decl_stmt|;
name|GSList
modifier|*
name|new_head
decl_stmt|;
name|gpointer
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|list
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
do|do
block|{
do|do
block|{
name|old_head
operator|=
name|g_atomic_pointer_get
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|old_head
operator|==
operator|&
name|gimp_atomic_slist_sentinel
condition|)
do|;
if|if
condition|(
operator|!
name|old_head
condition|)
return|return
name|NULL
return|;
block|}
do|while
condition|(
operator|!
name|g_atomic_pointer_compare_and_exchange
argument_list|(
name|list
argument_list|,
name|old_head
argument_list|,
operator|&
name|gimp_atomic_slist_sentinel
argument_list|)
condition|)
do|;
name|new_head
operator|=
name|old_head
operator|->
name|next
expr_stmt|;
name|data
operator|=
name|old_head
operator|->
name|data
expr_stmt|;
name|g_atomic_pointer_set
argument_list|(
name|list
argument_list|,
name|new_head
argument_list|)
expr_stmt|;
name|g_slist_free1
argument_list|(
name|old_head
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

end_unit

