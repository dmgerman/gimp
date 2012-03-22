begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptilebackendtilemanager.h  * Copyright (C) 2011 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TILE_BACKEND_PLUGIN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TILE_BACKEND_PLUGIN_H__
define|#
directive|define
name|__GIMP_TILE_BACKEND_PLUGIN_H__
end_define

begin_include
include|#
directive|include
file|<gegl-buffer-backend.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_TILE_BACKEND_PLUGIN
define|#
directive|define
name|GIMP_TYPE_TILE_BACKEND_PLUGIN
value|(_gimp_tile_backend_plugin_get_type ())
end_define

begin_define
DECL|macro|GIMP_TILE_BACKEND_PLUGIN (obj)
define|#
directive|define
name|GIMP_TILE_BACKEND_PLUGIN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TILE_BACKEND_PLUGIN, GimpTileBackendPlugin))
end_define

begin_define
DECL|macro|GIMP_TILE_BACKEND_PLUGIN_CLASS (klass)
define|#
directive|define
name|GIMP_TILE_BACKEND_PLUGIN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_TILE_BACKEND_PLUGIN, GimpTileBackendPluginClass))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_BACKEND_PLUGIN (obj)
define|#
directive|define
name|GIMP_IS_TILE_BACKEND_PLUGIN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TILE_BACKEND_PLUGIN))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_BACKEND_PLUGIN_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TILE_BACKEND_PLUGIN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_TILE_BACKEND_PLUGIN))
end_define

begin_define
DECL|macro|GIMP_TILE_BACKEND_PLUGIN_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TILE_BACKEND_PLUGIN_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_TILE_BACKEND_PLUGIN, GimpTileBackendPluginClass))
end_define

begin_typedef
DECL|typedef|GimpTileBackendPlugin
typedef|typedef
name|struct
name|_GimpTileBackendPlugin
name|GimpTileBackendPlugin
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTileBackendPluginClass
typedef|typedef
name|struct
name|_GimpTileBackendPluginClass
name|GimpTileBackendPluginClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTileBackendPluginPrivate
typedef|typedef
name|struct
name|_GimpTileBackendPluginPrivate
name|GimpTileBackendPluginPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTileBackendPlugin
struct|struct
name|_GimpTileBackendPlugin
block|{
DECL|member|parent_instance
name|GeglTileBackend
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpTileBackendPluginPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTileBackendPluginClass
struct|struct
name|_GimpTileBackendPluginClass
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
name|_gimp_tile_backend_plugin_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglTileBackend
modifier|*
name|_gimp_tile_backend_plugin_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|shadow
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
comment|/* __GIMP_TILE_BACKEND_plugin_H__ */
end_comment

end_unit

