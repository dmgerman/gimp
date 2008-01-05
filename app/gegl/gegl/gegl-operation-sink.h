begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* This file is part of GEGL  *  * GEGL is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * GEGL is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with GEGL; if not, see<http://www.gnu.org/licenses/>.  *  * Copyright 2006 Ãyvind KolÃ¥s  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GEGL_OPERATION_SINK_H
end_ifndef

begin_define
DECL|macro|_GEGL_OPERATION_SINK_H
define|#
directive|define
name|_GEGL_OPERATION_SINK_H
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
DECL|macro|GEGL_TYPE_OPERATION_SINK
define|#
directive|define
name|GEGL_TYPE_OPERATION_SINK
value|(gegl_operation_sink_get_type ())
end_define

begin_define
DECL|macro|GEGL_OPERATION_SINK (obj)
define|#
directive|define
name|GEGL_OPERATION_SINK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GEGL_TYPE_OPERATION_SINK, GeglOperationSink))
end_define

begin_define
DECL|macro|GEGL_OPERATION_SINK_CLASS (klass)
define|#
directive|define
name|GEGL_OPERATION_SINK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GEGL_TYPE_OPERATION_SINK, GeglOperationSinkClass))
end_define

begin_define
DECL|macro|GEGL_OPERATION_SINK_GET_CLASS (obj)
define|#
directive|define
name|GEGL_OPERATION_SINK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GEGL_TYPE_OPERATION_SINK, GeglOperationSinkClass))
end_define

begin_define
DECL|macro|GEGL_IS_OPERATION_SINK (obj)
define|#
directive|define
name|GEGL_IS_OPERATION_SINK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEGL_TYPE_OPERATION_SINK))
end_define

begin_define
DECL|macro|GEGL_IS_OPERATION_SINK_CLASS (klass)
define|#
directive|define
name|GEGL_IS_OPERATION_SINK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GEGL_TYPE_OPERATION_SINK))
end_define

begin_typedef
DECL|typedef|GeglOperationSink
typedef|typedef
name|struct
name|_GeglOperationSink
name|GeglOperationSink
typedef|;
end_typedef

begin_struct
DECL|struct|_GeglOperationSink
struct|struct
name|_GeglOperationSink
block|{
DECL|member|parent_instance
name|GeglOperation
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GeglOperationSinkClass
typedef|typedef
name|struct
name|_GeglOperationSinkClass
name|GeglOperationSinkClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GeglOperationSinkClass
struct|struct
name|_GeglOperationSinkClass
block|{
DECL|member|parent_class
name|GeglOperationClass
name|parent_class
decl_stmt|;
DECL|member|needs_full
name|gboolean
name|needs_full
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
name|GeglNodeContext
modifier|*
name|context
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
name|gegl_operation_sink_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gegl_operation_sink_needs_full
parameter_list|(
name|GeglOperation
modifier|*
name|operation
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

end_unit

