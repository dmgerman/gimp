begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"imap_mru.h"
end_include

begin_define
DECL|macro|DEFAULT_MRU_SIZE
define|#
directive|define
name|DEFAULT_MRU_SIZE
value|4
end_define

begin_function
name|MRU_t
modifier|*
DECL|function|mru_create (void)
name|mru_create
parameter_list|(
name|void
parameter_list|)
block|{
name|MRU_t
modifier|*
name|mru
init|=
name|g_new
argument_list|(
name|MRU_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|mru
operator|->
name|list
operator|=
name|NULL
expr_stmt|;
name|mru
operator|->
name|max_size
operator|=
name|DEFAULT_MRU_SIZE
expr_stmt|;
return|return
name|mru
return|;
block|}
end_function

begin_function
name|void
DECL|function|mru_destruct (MRU_t * mru)
name|mru_destruct
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|)
block|{
name|g_list_foreach
argument_list|(
name|mru
operator|->
name|list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|mru
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|mru_remove_link (MRU_t * mru,GList * link)
name|mru_remove_link
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
name|GList
modifier|*
name|link
parameter_list|)
block|{
name|g_free
argument_list|(
name|link
operator|->
name|data
argument_list|)
expr_stmt|;
name|mru
operator|->
name|list
operator|=
name|g_list_remove_link
argument_list|(
name|mru
operator|->
name|list
argument_list|,
name|link
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|mru_find_link (MRU_t * mru,const gchar * filename)
name|mru_find_link
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
return|return
name|g_list_find_custom
argument_list|(
name|mru
operator|->
name|list
argument_list|,
operator|(
name|gpointer
operator|)
name|filename
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|strcmp
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|mru_add (MRU_t * mru,const gchar * filename)
name|mru_add
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
if|if
condition|(
name|g_list_length
argument_list|(
name|mru
operator|->
name|list
argument_list|)
operator|==
name|mru
operator|->
name|max_size
condition|)
name|mru_remove_link
argument_list|(
name|mru
argument_list|,
name|g_list_last
argument_list|(
name|mru
operator|->
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|mru
operator|->
name|list
operator|=
name|g_list_prepend
argument_list|(
name|mru
operator|->
name|list
argument_list|,
name|g_strdup
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|mru_remove (MRU_t * mru,const gchar * filename)
name|mru_remove
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|mru_remove_link
argument_list|(
name|mru
argument_list|,
name|mru_find_link
argument_list|(
name|mru
argument_list|,
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|mru_set_first (MRU_t * mru,const gchar * filename)
name|mru_set_first
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GList
modifier|*
name|link
init|=
name|mru_find_link
argument_list|(
name|mru
argument_list|,
name|filename
argument_list|)
decl_stmt|;
if|if
condition|(
name|link
condition|)
name|mru
operator|->
name|list
operator|=
name|g_list_prepend
argument_list|(
name|g_list_remove_link
argument_list|(
name|mru
operator|->
name|list
argument_list|,
name|link
argument_list|)
argument_list|,
name|link
operator|->
name|data
argument_list|)
expr_stmt|;
else|else
name|mru_add
argument_list|(
name|mru
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|mru_set_size (MRU_t * mru,gint size)
name|mru_set_size
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
if|if
condition|(
name|size
operator|<
name|mru
operator|->
name|max_size
condition|)
block|{
comment|/* fix me */
block|}
name|mru
operator|->
name|max_size
operator|=
name|size
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|mru_write (MRU_t * mru,FILE * out)
name|mru_write
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
name|FILE
modifier|*
name|out
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
name|mru
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
name|fprintf
argument_list|(
name|out
argument_list|,
literal|"(mru-entry %s)\n"
argument_list|,
operator|(
name|gchar
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

