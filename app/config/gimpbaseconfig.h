begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpBaseConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BASE_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BASE_CONFIG_H__
define|#
directive|define
name|__GIMP_BASE_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"base/base-enums.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BASE_CONFIG
define|#
directive|define
name|GIMP_TYPE_BASE_CONFIG
value|(gimp_base_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_BASE_CONFIG (obj)
define|#
directive|define
name|GIMP_BASE_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BASE_CONFIG, GimpBaseConfig))
end_define

begin_define
DECL|macro|GIMP_BASE_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_BASE_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BASE_CONFIG, GimpBaseConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_BASE_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_BASE_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BASE_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_BASE_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BASE_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BASE_CONFIG))
end_define

begin_typedef
DECL|typedef|GimpBaseConfigClass
typedef|typedef
name|struct
name|_GimpBaseConfigClass
name|GimpBaseConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBaseConfig
struct|struct
name|_GimpBaseConfig
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
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
DECL|member|stingy_memory_use
name|gboolean
name|stingy_memory_use
decl_stmt|;
comment|/*  unused  */
DECL|member|num_processors
name|guint
name|num_processors
decl_stmt|;
DECL|member|tile_cache_size
name|guint64
name|tile_cache_size
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBaseConfigClass
struct|struct
name|_GimpBaseConfigClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_base_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_BASE_CONFIG_H__ */
end_comment

end_unit

