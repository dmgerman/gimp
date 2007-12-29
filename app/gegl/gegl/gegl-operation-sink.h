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
DECL|macro|GEGL_TYPE_OPERATION_SINK
define|#
directive|define
name|GEGL_TYPE_OPERATION_SINK
value|(gegl_operation_sink_get_type ())
DECL|macro|GEGL_OPERATION_SINK (obj)
define|#
directive|define
name|GEGL_OPERATION_SINK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GEGL_TYPE_OPERATION_SINK, GeglOperationSink))
DECL|macro|GEGL_OPERATION_SINK_CLASS (klass)
define|#
directive|define
name|GEGL_OPERATION_SINK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GEGL_TYPE_OPERATION_SINK, GeglOperationSinkClass))
DECL|macro|GEGL_OPERATION_SINK_GET_CLASS (obj)
define|#
directive|define
name|GEGL_OPERATION_SINK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GEGL_TYPE_OPERATION_SINK, GeglOperationSinkClass))
DECL|typedef|GeglOperationSink
typedef|typedef
name|struct
name|_GeglOperationSink
name|GeglOperationSink
typedef|;
DECL|struct|_GeglOperationSink
struct|struct
name|_GeglOperationSink
block|{
DECL|member|operation
name|GeglOperation
name|operation
decl_stmt|;
block|}
struct|;
DECL|typedef|GeglOperationSinkClass
typedef|typedef
name|struct
name|_GeglOperationSinkClass
name|GeglOperationSinkClass
typedef|;
DECL|struct|_GeglOperationSinkClass
struct|struct
name|_GeglOperationSinkClass
block|{
DECL|member|operation_class
name|GeglOperationClass
name|operation_class
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
parameter_list|)
function_decl|;
block|}
struct|;
name|GType
name|gegl_operation_sink_get_type
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

