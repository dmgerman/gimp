begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1999 Andy Thomas alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_CACHE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_CACHE_H__
define|#
directive|define
name|__GIMP_PREVIEW_CACHE_H__
end_define

begin_define
DECL|macro|PREVIEW_CACHE_PRIME_WIDTH
define|#
directive|define
name|PREVIEW_CACHE_PRIME_WIDTH
value|112
end_define

begin_define
DECL|macro|PREVIEW_CACHE_PRIME_HEIGHT
define|#
directive|define
name|PREVIEW_CACHE_PRIME_HEIGHT
value|112
end_define

begin_function_decl
name|TempBuf
modifier|*
name|gimp_preview_cache_get
parameter_list|(
name|GSList
modifier|*
modifier|*
name|plist
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
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
name|plist
parameter_list|,
name|TempBuf
modifier|*
name|buf
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
name|plist
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gsize
name|gimp_preview_cache_get_memsize
parameter_list|(
name|GSList
modifier|*
name|cache
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PREVIEW_CACHE_H__ */
end_comment

end_unit

