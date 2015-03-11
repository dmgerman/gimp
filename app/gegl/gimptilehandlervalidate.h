begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TILE_HANDLER_VALIDATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TILE_HANDLER_VALIDATE_H__
define|#
directive|define
name|__GIMP_TILE_HANDLER_VALIDATE_H__
end_define

begin_include
include|#
directive|include
file|<gegl-buffer-backend.h>
end_include

begin_comment
comment|/***  * GimpTileHandlerValidate is a GeglTileHandler that renders the  * projection.  */
end_comment

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_TILE_HANDLER_VALIDATE
define|#
directive|define
name|GIMP_TYPE_TILE_HANDLER_VALIDATE
value|(gimp_tile_handler_validate_get_type ())
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_VALIDATE (obj)
define|#
directive|define
name|GIMP_TILE_HANDLER_VALIDATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TILE_HANDLER_VALIDATE, GimpTileHandlerValidate))
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_VALIDATE_CLASS (klass)
define|#
directive|define
name|GIMP_TILE_HANDLER_VALIDATE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_TILE_HANDLER_VALIDATE, GimpTileHandlerValidateClass))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_HANDLER_VALIDATE (obj)
define|#
directive|define
name|GIMP_IS_TILE_HANDLER_VALIDATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TILE_HANDLER_VALIDATE))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_HANDLER_VALIDATE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TILE_HANDLER_VALIDATE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_TILE_HANDLER_VALIDATE))
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_VALIDATE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TILE_HANDLER_VALIDATE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_TILE_HANDLER_VALIDATE, GimpTileHandlerValidateClass))
end_define

begin_typedef
DECL|typedef|GimpTileHandlerValidate
typedef|typedef
name|struct
name|_GimpTileHandlerValidate
name|GimpTileHandlerValidate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTileHandlerValidateClass
typedef|typedef
name|struct
name|_GimpTileHandlerValidateClass
name|GimpTileHandlerValidateClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTileHandlerValidate
struct|struct
name|_GimpTileHandlerValidate
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
DECL|member|max_z
name|gint
name|max_z
decl_stmt|;
DECL|member|whole_tile
name|gboolean
name|whole_tile
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTileHandlerValidateClass
struct|struct
name|_GimpTileHandlerValidateClass
block|{
DECL|member|parent_class
name|GeglTileHandlerClass
name|parent_class
decl_stmt|;
DECL|member|validate
name|void
function_decl|(
modifier|*
name|validate
function_decl|)
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|dest_buf
parameter_list|,
name|gint
name|dest_stride
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tile_handler_validate_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglTileHandler
modifier|*
name|gimp_tile_handler_validate_new
parameter_list|(
name|GeglNode
modifier|*
name|graph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tile_handler_validate_assign
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
parameter_list|,
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tile_handler_validate_invalidate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
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

begin_function_decl
name|void
name|gimp_tile_handler_validate_undo_invalidate
parameter_list|(
name|GimpTileHandlerValidate
modifier|*
name|validate
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
comment|/* __GIMP_TILE_HANDLER_VALIDATE_H__ */
end_comment

end_unit

