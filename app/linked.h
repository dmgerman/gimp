begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LINKED_H__
end_ifndef

begin_define
DECL|macro|__LINKED_H__
define|#
directive|define
name|__LINKED_H__
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|USE_GSLIST_VERSION
end_ifndef

begin_typedef
DECL|struct|_link
typedef|typedef
struct|struct
name|_link
block|{
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|next
name|struct
name|_link
modifier|*
name|next
decl_stmt|;
DECL|typedef|link_ptr
block|}
typedef|*
name|link_ptr
typedef|;
end_typedef

begin_function_decl
specifier|extern
name|link_ptr
name|alloc_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|link_ptr
name|free_list
parameter_list|(
name|link_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|link_ptr
name|add_to_list
parameter_list|(
name|link_ptr
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|link_ptr
name|append_to_list
parameter_list|(
name|link_ptr
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|link_ptr
name|insert_in_list
parameter_list|(
name|link_ptr
parameter_list|,
name|void
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|link_ptr
name|remove_from_list
parameter_list|(
name|link_ptr
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|link_ptr
name|next_item
parameter_list|(
name|link_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|link_ptr
name|nth_item
parameter_list|(
name|link_ptr
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|list_length
parameter_list|(
name|link_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* USE_GSLIST_VERSION */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_typedef
DECL|typedef|link_ptr
typedef|typedef
name|GSList
modifier|*
name|link_ptr
typedef|;
end_typedef

begin_define
DECL|macro|alloc_list ()
define|#
directive|define
name|alloc_list
parameter_list|()
value|g_slist_alloc()
end_define

begin_define
DECL|macro|free_list (x)
define|#
directive|define
name|free_list
parameter_list|(
name|x
parameter_list|)
value|g_slist_free((x)), NULL
end_define

begin_define
DECL|macro|add_to_list (x,y)
define|#
directive|define
name|add_to_list
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|)
value|g_slist_prepend((x), (y))
end_define

begin_define
DECL|macro|append_to_list (x,y)
define|#
directive|define
name|append_to_list
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|)
value|g_slist_append((x), (y))
end_define

begin_define
DECL|macro|insert_in_list (x,y,z)
define|#
directive|define
name|insert_in_list
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|g_slist_insert((x), (y), (z))
end_define

begin_define
DECL|macro|remove_from_list (x,y)
define|#
directive|define
name|remove_from_list
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|)
value|g_slist_remove((x), (y))
end_define

begin_define
DECL|macro|next_item (x)
define|#
directive|define
name|next_item
parameter_list|(
name|x
parameter_list|)
value|(x)?g_slist_next((x)):NULL
end_define

begin_define
DECL|macro|nth_item (x,y)
define|#
directive|define
name|nth_item
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|)
value|g_slist_nth((x), (y))
end_define

begin_define
DECL|macro|list_length (x)
define|#
directive|define
name|list_length
parameter_list|(
name|x
parameter_list|)
value|g_slist_length((x))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* USE_GSLIST_VERSION */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

