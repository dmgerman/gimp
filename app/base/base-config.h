begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BASE_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__BASE_CONFIG_H__
define|#
directive|define
name|__BASE_CONFIG_H__
end_define

begin_typedef
DECL|typedef|GimpBaseConfig
typedef|typedef
name|struct
name|_GimpBaseConfig
name|GimpBaseConfig
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBaseConfig
struct|struct
name|_GimpBaseConfig
block|{
DECL|member|temp_path
name|gchar
modifier|*
name|temp_path
decl_stmt|;
DECL|member|swap_path
name|gchar
modifier|*
name|swap_path
decl_stmt|;
DECL|member|tile_cache_size
name|guint
name|tile_cache_size
decl_stmt|;
DECL|member|stingy_memory_use
name|gboolean
name|stingy_memory_use
decl_stmt|;
DECL|member|interpolation_type
name|InterpolationType
name|interpolation_type
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|GimpBaseConfig
modifier|*
name|base_config
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BASE_CONFIG_H__  */
end_comment

end_unit

