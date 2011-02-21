begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_MRU_H
end_ifndef

begin_define
DECL|macro|_IMAP_MRU_H
define|#
directive|define
name|_IMAP_MRU_H
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_define
DECL|macro|DEFAULT_MRU_SIZE
define|#
directive|define
name|DEFAULT_MRU_SIZE
value|4
end_define

begin_typedef
DECL|struct|__anon29e2775e0108
typedef|typedef
struct|struct
block|{
DECL|member|list
name|GList
modifier|*
name|list
decl_stmt|;
DECL|member|max_size
name|gint
name|max_size
decl_stmt|;
DECL|typedef|MRU_t
block|}
name|MRU_t
typedef|;
end_typedef

begin_function_decl
name|MRU_t
modifier|*
name|mru_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mru_destruct
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mru_set_size
parameter_list|(
name|MRU_t
modifier|*
name|mru
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_define
DECL|macro|mru_empty (mru)
define|#
directive|define
name|mru_empty
parameter_list|(
name|mru
parameter_list|)
value|((mru)->list == NULL)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_MRU_H */
end_comment

end_unit

