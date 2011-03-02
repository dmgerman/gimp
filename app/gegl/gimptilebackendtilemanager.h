begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptilebackendtilemanager.h  * Copyright (C) 2011 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TILE_BACKEND_TILE_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TILE_BACKEND_TILE_MANAGER_H__
define|#
directive|define
name|__GIMP_TILE_BACKEND_TILE_MANAGER_H__
end_define

begin_include
include|#
directive|include
file|"gegl-buffer-backend.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_TILE_BACKEND_TILE_MANAGER
define|#
directive|define
name|GIMP_TYPE_TILE_BACKEND_TILE_MANAGER
value|(gimp_tile_backend_tile_manager_get_type ())
end_define

begin_define
DECL|macro|GIMP_TILE_BACKEND_TILE_MANAGER (obj)
define|#
directive|define
name|GIMP_TILE_BACKEND_TILE_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TILE_BACKEND_TILE_MANAGER, GimpTileBackendTileManager))
end_define

begin_define
DECL|macro|GIMP_TILE_BACKEND_TILE_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_TILE_BACKEND_TILE_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_TILE_BACKEND_TILE_MANAGER, GimpTileBackendTileManagerClass))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_BACKEND_TILE_MANAGER (obj)
define|#
directive|define
name|GIMP_IS_TILE_BACKEND_TILE_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TILE_BACKEND_TILE_MANAGER))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_BACKEND_TILE_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TILE_BACKEND_TILE_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_TILE_BACKEND_TILE_MANAGER))
end_define

begin_define
DECL|macro|GIMP_TILE_BACKEND_TILE_MANAGER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TILE_BACKEND_TILE_MANAGER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_TILE_BACKEND_TILE_MANAGER, GimpTileBackendTileManagerClass))
end_define

begin_typedef
DECL|typedef|GimpTileBackendTileManager
typedef|typedef
name|struct
name|_GimpTileBackendTileManager
name|GimpTileBackendTileManager
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTileBackendTileManagerClass
typedef|typedef
name|struct
name|_GimpTileBackendTileManagerClass
name|GimpTileBackendTileManagerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTileBackendTileManager
struct|struct
name|_GimpTileBackendTileManager
block|{
DECL|member|parent_instance
name|GeglTileBackend
name|parent_instance
decl_stmt|;
DECL|member|entries
name|GHashTable
modifier|*
name|entries
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTileBackendTileManagerClass
struct|struct
name|_GimpTileBackendTileManagerClass
block|{
DECL|member|parent_class
name|GeglTileBackendClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tile_backend_tile_manager_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglTileBackend
modifier|*
name|gimp_tile_backend_tile_manager_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tile_backend_tile_manager_stats
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TILE_BACKEND_TILE_MANAGER_H__ */
end_comment

end_unit

