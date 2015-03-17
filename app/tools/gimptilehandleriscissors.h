begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TILE_HANDLER_ISCISSORS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TILE_HANDLER_ISCISSORS_H__
define|#
directive|define
name|__GIMP_TILE_HANDLER_ISCISSORS_H__
end_define

begin_include
include|#
directive|include
file|"gegl/gimptilehandlervalidate.h"
end_include

begin_comment
comment|/***  * GimpTileHandlerIscissors is a GeglTileHandler that renders the  * Iscissors tool's gradmap.  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_TILE_HANDLER_ISCISSORS
define|#
directive|define
name|GIMP_TYPE_TILE_HANDLER_ISCISSORS
value|(gimp_tile_handler_iscissors_get_type ())
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_ISCISSORS (obj)
define|#
directive|define
name|GIMP_TILE_HANDLER_ISCISSORS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TILE_HANDLER_ISCISSORS, GimpTileHandlerIscissors))
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_ISCISSORS_CLASS (klass)
define|#
directive|define
name|GIMP_TILE_HANDLER_ISCISSORS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_TILE_HANDLER_ISCISSORS, GimpTileHandlerIscissorsClass))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_HANDLER_ISCISSORS (obj)
define|#
directive|define
name|GIMP_IS_TILE_HANDLER_ISCISSORS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TILE_HANDLER_ISCISSORS))
end_define

begin_define
DECL|macro|GIMP_IS_TILE_HANDLER_ISCISSORS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TILE_HANDLER_ISCISSORS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_TILE_HANDLER_ISCISSORS))
end_define

begin_define
DECL|macro|GIMP_TILE_HANDLER_ISCISSORS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TILE_HANDLER_ISCISSORS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_TILE_HANDLER_ISCISSORS, GimpTileHandlerIscissorsClass))
end_define

begin_typedef
DECL|typedef|GimpTileHandlerIscissors
typedef|typedef
name|struct
name|_GimpTileHandlerIscissors
name|GimpTileHandlerIscissors
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTileHandlerIscissorsClass
typedef|typedef
name|struct
name|_GimpTileHandlerIscissorsClass
name|GimpTileHandlerIscissorsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTileHandlerIscissors
struct|struct
name|_GimpTileHandlerIscissors
block|{
DECL|member|parent_instance
name|GimpTileHandlerValidate
name|parent_instance
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTileHandlerIscissorsClass
struct|struct
name|_GimpTileHandlerIscissorsClass
block|{
DECL|member|parent_class
name|GimpTileHandlerValidateClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tile_handler_iscissors_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglTileHandler
modifier|*
name|gimp_tile_handler_iscissors_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TILE_HANDLER_ISCISSORS_H__ */
end_comment

end_unit

