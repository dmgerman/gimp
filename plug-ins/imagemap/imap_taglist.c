begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"imap_string.h"
end_include

begin_include
include|#
directive|include
file|"imap_taglist.h"
end_include

begin_function
specifier|static
name|Tag_t
modifier|*
DECL|function|tag_create (const gchar * name,const gchar * value)
name|tag_create
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
name|Tag_t
modifier|*
name|tag
init|=
name|g_new
argument_list|(
name|Tag_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|tag
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|tag
operator|->
name|value
operator|=
name|g_strdup
argument_list|(
name|value
argument_list|)
expr_stmt|;
return|return
name|tag
return|;
block|}
end_function

begin_function
specifier|static
name|Tag_t
modifier|*
DECL|function|tag_clone (Tag_t * src)
name|tag_clone
parameter_list|(
name|Tag_t
modifier|*
name|src
parameter_list|)
block|{
return|return
name|tag_create
argument_list|(
name|src
operator|->
name|name
argument_list|,
name|src
operator|->
name|value
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tag_destruct (Tag_t * tag)
name|tag_destruct
parameter_list|(
name|Tag_t
modifier|*
name|tag
parameter_list|)
block|{
name|g_free
argument_list|(
name|tag
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tag
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tag
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tag_write (Tag_t * tag)
name|tag_write
parameter_list|(
name|Tag_t
modifier|*
name|tag
parameter_list|)
block|{
name|printf
argument_list|(
literal|"\"%s\"=\"%s\"\n"
argument_list|,
name|tag
operator|->
name|name
argument_list|,
name|tag
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|TagList_t
modifier|*
DECL|function|taglist_create (void)
name|taglist_create
parameter_list|(
name|void
parameter_list|)
block|{
name|TagList_t
modifier|*
name|tlist
init|=
name|g_new
argument_list|(
name|TagList_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|tlist
operator|->
name|list
operator|=
name|NULL
expr_stmt|;
return|return
name|tlist
return|;
block|}
end_function

begin_function
name|TagList_t
modifier|*
DECL|function|taglist_clone (TagList_t * src)
name|taglist_clone
parameter_list|(
name|TagList_t
modifier|*
name|src
parameter_list|)
block|{
return|return
name|taglist_copy
argument_list|(
name|src
argument_list|,
name|taglist_create
argument_list|()
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|taglist_remove_all (TagList_t * tlist)
name|taglist_remove_all
parameter_list|(
name|TagList_t
modifier|*
name|tlist
parameter_list|)
block|{
name|GList
modifier|*
name|p
decl_stmt|;
for|for
control|(
name|p
operator|=
name|tlist
operator|->
name|list
init|;
name|p
condition|;
name|p
operator|=
name|p
operator|->
name|next
control|)
name|tag_destruct
argument_list|(
operator|(
name|Tag_t
operator|*
operator|)
name|p
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|tlist
operator|->
name|list
argument_list|)
expr_stmt|;
name|tlist
operator|->
name|list
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|TagList_t
modifier|*
DECL|function|taglist_copy (TagList_t * src,TagList_t * des)
name|taglist_copy
parameter_list|(
name|TagList_t
modifier|*
name|src
parameter_list|,
name|TagList_t
modifier|*
name|des
parameter_list|)
block|{
name|GList
modifier|*
name|p
decl_stmt|;
name|taglist_remove_all
argument_list|(
name|des
argument_list|)
expr_stmt|;
for|for
control|(
name|p
operator|=
name|src
operator|->
name|list
init|;
name|p
condition|;
name|p
operator|=
name|p
operator|->
name|next
control|)
name|des
operator|->
name|list
operator|=
name|g_list_append
argument_list|(
name|des
operator|->
name|list
argument_list|,
name|tag_clone
argument_list|(
operator|(
name|Tag_t
operator|*
operator|)
name|p
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|des
return|;
block|}
end_function

begin_function
name|void
DECL|function|taglist_destruct (TagList_t * tlist)
name|taglist_destruct
parameter_list|(
name|TagList_t
modifier|*
name|tlist
parameter_list|)
block|{
name|taglist_remove_all
argument_list|(
name|tlist
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tlist
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|taglist_set (TagList_t * tlist,const gchar * name,const gchar * value)
name|taglist_set
parameter_list|(
name|TagList_t
modifier|*
name|tlist
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
block|{
name|GList
modifier|*
name|p
decl_stmt|;
name|Tag_t
modifier|*
name|tag
decl_stmt|;
for|for
control|(
name|p
operator|=
name|tlist
operator|->
name|list
init|;
name|p
condition|;
name|p
operator|=
name|p
operator|->
name|next
control|)
block|{
name|tag
operator|=
operator|(
name|Tag_t
operator|*
operator|)
name|p
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|g_ascii_strcasecmp
argument_list|(
name|tag
operator|->
name|name
argument_list|,
name|name
argument_list|)
condition|)
block|{
name|g_strreplace
argument_list|(
operator|&
name|tag
operator|->
name|value
argument_list|,
name|value
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
comment|/* Tag not found, add a new tag */
name|tlist
operator|->
name|list
operator|=
name|g_list_append
argument_list|(
name|tlist
operator|->
name|list
argument_list|,
name|tag_create
argument_list|(
name|name
argument_list|,
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|taglist_write (TagList_t * tlist)
name|taglist_write
parameter_list|(
name|TagList_t
modifier|*
name|tlist
parameter_list|)
block|{
name|GList
modifier|*
name|p
decl_stmt|;
for|for
control|(
name|p
operator|=
name|tlist
operator|->
name|list
init|;
name|p
condition|;
name|p
operator|=
name|p
operator|->
name|next
control|)
name|tag_write
argument_list|(
operator|(
name|Tag_t
operator|*
operator|)
name|p
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

