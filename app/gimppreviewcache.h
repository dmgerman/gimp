begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Andy Thomas alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPPREVIEWCACHE_H__
end_ifndef

begin_define
DECL|macro|__GIMPPREVIEWCACHE_H__
define|#
directive|define
name|__GIMPPREVIEWCACHE_H__
end_define

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_typedef
DECL|struct|_PreviewCache
typedef|typedef
struct|struct
name|_PreviewCache
block|{
DECL|member|preview
name|TempBuf
modifier|*
name|preview
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|typedef|PreviewCache
block|}
name|PreviewCache
typedef|;
end_typedef

begin_typedef
DECL|struct|_PreviewNearest
typedef|typedef
struct|struct
name|_PreviewNearest
block|{
DECL|member|pc
name|PreviewCache
modifier|*
name|pc
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|typedef|PreviewNearest
block|}
name|PreviewNearest
typedef|;
end_typedef

begin_define
DECL|macro|MAX_CACHE_PREVIEWS
define|#
directive|define
name|MAX_CACHE_PREVIEWS
value|5
end_define

begin_function_decl
name|TempBuf
modifier|*
name|gimp_preview_cache_get
parameter_list|(
name|GSList
modifier|*
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_cache_add
parameter_list|(
name|GSList
modifier|*
modifier|*
parameter_list|,
name|TempBuf
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_cache_invalidate
parameter_list|(
name|GSList
modifier|*
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPPREVIEWCACHE_H__ */
end_comment

end_unit

