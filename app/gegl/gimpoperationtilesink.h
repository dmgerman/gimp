begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationtilesink.h  * Copyright (C) 2007 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_TILE_SINK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_TILE_SINK_H__
define|#
directive|define
name|__GIMP_OPERATION_TILE_SINK_H__
end_define

begin_include
include|#
directive|include
file|"gegl/gegl-operation-sink.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_TILE_SINK
define|#
directive|define
name|GIMP_TYPE_OPERATION_TILE_SINK
value|(gimp_operation_tile_sink_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_TILE_SINK (obj)
define|#
directive|define
name|GIMP_OPERATION_TILE_SINK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_TILE_SINK, GimpOperationTileSink))
end_define

begin_define
DECL|macro|GIMP_OPERATION_TILE_SINK_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_TILE_SINK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_TILE_SINK, GimpOperationTileSinkClass))
end_define

begin_define
DECL|macro|GIMP_OPERATION_TILE_SINK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_TILE_SINK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_TILE_SINK, GimpOperationTileSinkClass))
end_define

begin_typedef
DECL|typedef|GimpOperationTileSinkClass
typedef|typedef
name|struct
name|_GimpOperationTileSinkClass
name|GimpOperationTileSinkClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationTileSink
struct|struct
name|_GimpOperationTileSink
block|{
DECL|member|parent_instance
name|GeglOperationSink
name|parent_instance
decl_stmt|;
DECL|member|tile_manager
name|TileManager
modifier|*
name|tile_manager
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationTileSinkClass
struct|struct
name|_GimpOperationTileSinkClass
block|{
DECL|member|operation_sink_class
name|GeglOperationSinkClass
name|operation_sink_class
decl_stmt|;
DECL|member|data_written
name|void
function_decl|(
modifier|*
name|data_written
function_decl|)
parameter_list|(
name|GimpOperationTileSink
modifier|*
name|sink
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|extent
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_tile_sink_get_type
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
comment|/* __GIMP_OPERATION_TILE_SINK_H__ */
end_comment

end_unit

