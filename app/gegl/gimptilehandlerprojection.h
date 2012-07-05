begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TILE_HANDLER_PROJECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TILE_HANDLER_PROJECTION_H__
define|#
directive|define
name|__GIMP_TILE_HANDLER_PROJECTION_H__
end_define

begin_include
include|#
directive|include
file|<gegl-buffer-backend.h>
end_include

begin_comment
comment|/***  * GimpTileHandlerProjection is a GeglTileHandler that renders the  * projection.  */
end_comment

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_TILE_HANDLER_PROJECTION
define|#
directive|define
name|GIMP_TYPE_TILE_HANDLER_PROJECTION
value|(gimp_tile_handler_projection_get_type ())
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_PROJECTION (obj)
define|#
directive|define
name|GIMP_TILE_HANDLER_PROJECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TILE_HANDLER_PROJECTION, GimpTileHandlerProjection))
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_PROJECTION_CLASS (klass)
define|#
directive|define
name|GIMP_TILE_HANDLER_PROJECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_TILE_HANDLER_PROJECTION, GimpTileHandlerProjectionClass))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_HANDLER_PROJECTION (obj)
define|#
directive|define
name|GIMP_IS_TILE_HANDLER_PROJECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TILE_HANDLER_PROJECTION))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_HANDLER_PROJECTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TILE_HANDLER_PROJECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_TILE_HANDLER_PROJECTION))
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_PROJECTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TILE_HANDLER_PROJECTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_TILE_HANDLER_PROJECTION, GimpTileHandlerProjectionClass))
end_define

begin_typedef
DECL|typedef|GimpTileHandlerProjection
typedef|typedef
name|struct
name|_GimpTileHandlerProjection
name|GimpTileHandlerProjection
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTileHandlerProjectionClass
typedef|typedef
name|struct
name|_GimpTileHandlerProjectionClass
name|GimpTileHandlerProjectionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTileHandlerProjection
struct|struct
name|_GimpTileHandlerProjection
block|{
DECL|member|parent_instance
name|GeglTileHandler
name|parent_instance
decl_stmt|;
DECL|member|graph
name|GeglNode
modifier|*
name|graph
decl_stmt|;
DECL|member|dirty_region
name|cairo_region_t
modifier|*
name|dirty_region
decl_stmt|;
DECL|member|format
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
DECL|member|tile_width
name|gint
name|tile_width
decl_stmt|;
DECL|member|tile_height
name|gint
name|tile_height
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTileHandlerProjectionClass
struct|struct
name|_GimpTileHandlerProjectionClass
block|{
DECL|member|parent_class
name|GeglTileHandlerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tile_handler_projection_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglTileHandler
modifier|*
name|gimp_tile_handler_projection_new
parameter_list|(
name|GeglNode
modifier|*
name|graph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tile_handler_projection_invalidate
parameter_list|(
name|GimpTileHandlerProjection
modifier|*
name|projection
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
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
comment|/* __GIMP_TILE_HANDLER_PROJECTION_H__ */
end_comment

end_unit

