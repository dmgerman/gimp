begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_TAGLIST_H
end_ifndef

begin_define
DECL|macro|_IMAP_TAGLIST_H
define|#
directive|define
name|_IMAP_TAGLIST_H
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_typedef
DECL|struct|__anon2b16188c0108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|value
name|gchar
modifier|*
name|value
decl_stmt|;
DECL|typedef|Tag_t
block|}
name|Tag_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b16188c0208
typedef|typedef
struct|struct
block|{
DECL|member|list
name|GList
modifier|*
name|list
decl_stmt|;
DECL|typedef|TagList_t
block|}
name|TagList_t
typedef|;
end_typedef

begin_function_decl
name|TagList_t
modifier|*
name|taglist_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TagList_t
modifier|*
name|taglist_clone
parameter_list|(
name|TagList_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TagList_t
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|taglist_destruct
parameter_list|(
name|TagList_t
modifier|*
name|tlist
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|taglist_set
parameter_list|(
name|TagList_t
modifier|*
name|tlist
parameter_list|,
specifier|const
name|gchar
modifier|*
name|id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|taglist_write
parameter_list|(
name|TagList_t
modifier|*
name|tlist
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_TAGLIST_H */
end_comment

end_unit

