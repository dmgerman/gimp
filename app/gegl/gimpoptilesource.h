begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpops.c  * Copyright (C) 2007 Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GIMP_OPERATION_TILE_SOURCE_H
end_ifndef

begin_define
DECL|macro|_GIMP_OPERATION_TILE_SOURCE_H
define|#
directive|define
name|_GIMP_OPERATION_TILE_SOURCE_H
end_define

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gegl/gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gegl-operation-source.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GIMP_TYPE_OPERATION_TILE_SOURCE
define|#
directive|define
name|GIMP_TYPE_OPERATION_TILE_SOURCE
value|(gimp_operation_tile_source_get_type ())
DECL|macro|GIMP_OPERATION_TILE_SOURCE (obj)
define|#
directive|define
name|GIMP_OPERATION_TILE_SOURCE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_TILE_SOURCE, GimpOperationTileSource))
DECL|macro|GIMP_OPERATION_TILE_SOURCE_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_TILE_SOURCE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_TILE_SOURCE, GimpOperationTileSourceClass))
DECL|macro|GIMP_OPERATION_TILE_SOURCE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_TILE_SOURCE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_TILE_SOURCE, GimpOperationTileSourceClass))
DECL|typedef|GimpOperationTileSource
typedef|typedef
name|struct
name|_GimpOperationTileSource
name|GimpOperationTileSource
typedef|;
DECL|struct|_GimpOperationTileSource
struct|struct
name|_GimpOperationTileSource
block|{
DECL|member|operation_source
name|GeglOperationSourceClass
name|operation_source
decl_stmt|;
DECL|member|tile_manager
name|gpointer
name|tile_manager
decl_stmt|;
block|}
struct|;
DECL|typedef|GimpOperationTileSourceClass
typedef|typedef
name|struct
name|_GimpOperationTileSourceClass
name|GimpOperationTileSourceClass
typedef|;
DECL|struct|_GimpOperationTileSourceClass
struct|struct
name|_GimpOperationTileSourceClass
block|{
DECL|member|operation_source_class
name|GeglOperationSourceClass
name|operation_source_class
decl_stmt|;
block|}
struct|;
name|GType
name|gimp_operation_tile_source_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

