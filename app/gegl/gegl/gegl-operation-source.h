begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* This file is part of GEGL  *  * GEGL is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * GEGL is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with GEGL; if not, see<http://www.gnu.org/licenses/>.  *  * Copyright 2006 Ãyvind KolÃ¥s  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GEGL_OPERATION_SOURCE_H__
end_ifndef

begin_define
DECL|macro|__GEGL_OPERATION_SOURCE_H__
define|#
directive|define
name|__GEGL_OPERATION_SOURCE_H__
end_define

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl-operation.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GEGL_TYPE_OPERATION_SOURCE
define|#
directive|define
name|GEGL_TYPE_OPERATION_SOURCE
value|(gegl_operation_source_get_type ())
end_define

begin_define
DECL|macro|GEGL_OPERATION_SOURCE (obj)
define|#
directive|define
name|GEGL_OPERATION_SOURCE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GEGL_TYPE_OPERATION_SOURCE, GeglOperationSource))
end_define

begin_define
DECL|macro|GEGL_OPERATION_SOURCE_CLASS (klass)
define|#
directive|define
name|GEGL_OPERATION_SOURCE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GEGL_TYPE_OPERATION_SOURCE, GeglOperationSourceClass))
end_define

begin_define
DECL|macro|GEGL_OPERATION_SOURCE_GET_CLASS (obj)
define|#
directive|define
name|GEGL_OPERATION_SOURCE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GEGL_TYPE_OPERATION_SOURCE, GeglOperationSourceClass))
end_define

begin_typedef
DECL|typedef|GeglOperationSource
typedef|typedef
name|struct
name|_GeglOperationSource
name|GeglOperationSource
typedef|;
end_typedef

begin_struct
DECL|struct|_GeglOperationSource
struct|struct
name|_GeglOperationSource
block|{
DECL|member|parent_instance
name|GeglOperation
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GeglOperationSourceClass
typedef|typedef
name|struct
name|_GeglOperationSourceClass
name|GeglOperationSourceClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GeglOperationSourceClass
struct|struct
name|_GeglOperationSourceClass
block|{
DECL|member|parent_class
name|GeglOperationClass
name|parent_class
decl_stmt|;
DECL|member|process
name|gboolean
function_decl|(
modifier|*
name|process
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|self
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gegl_operation_source_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

end_unit

