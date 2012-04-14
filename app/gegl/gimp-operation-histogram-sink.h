begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*   * Copyright 2012 Ãyvind KolÃ¥s  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_HISTOGRAM_SINK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_HISTOGRAM_SINK_H__
define|#
directive|define
name|__GIMP_OPERATION_HISTOGRAM_SINK_H__
end_define

begin_include
include|#
directive|include
file|"gegl-operation-sink.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM_SINK
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM_SINK
value|(gimp_operation_histogram_sink_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_HISTOGRAM_SINK (obj)
define|#
directive|define
name|GIMP_OPERATION_HISTOGRAM_SINK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HISTOGRAM_SINK, GimpOperationHistogramSink))
end_define

begin_define
DECL|macro|GIMP_OPERATION_HISTOGRAM_SINK_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_HISTOGRAM_SINK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_HISTOGRAM_SINK, GimpOperationHistogramSinkClass))
end_define

begin_define
DECL|macro|GEGL_IS_OPERATION_HISTOGRAM_SINK (obj)
define|#
directive|define
name|GEGL_IS_OPERATION_HISTOGRAM_SINK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HISTOGRAM_SINK))
end_define

begin_define
DECL|macro|GEGL_IS_OPERATION_HISTOGRAM_SINK_CLASS (klass)
define|#
directive|define
name|GEGL_IS_OPERATION_HISTOGRAM_SINK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_HISTOGRAM_SINK))
end_define

begin_define
DECL|macro|GIMP_OPERATION_HISTOGRAM_SINK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_HISTOGRAM_SINK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_HISTOGRAM_SINK, GimpOperationHistogramSinkClass))
end_define

begin_typedef
DECL|typedef|GimpOperationHistogramSink
typedef|typedef
name|struct
name|_GimpOperationHistogramSink
name|GimpOperationHistogramSink
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationHistogramSink
struct|struct
name|_GimpOperationHistogramSink
block|{
DECL|member|parent_instance
name|GeglOperation
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpOperationHistogramSinkClass
typedef|typedef
name|struct
name|_GimpOperationHistogramSinkClass
name|GimpOperationHistogramSinkClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationHistogramSinkClass
struct|struct
name|_GimpOperationHistogramSinkClass
block|{
DECL|member|parent_class
name|GeglOperationSinkClass
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
name|GeglBuffer
modifier|*
name|input
parameter_list|,
name|GeglBuffer
modifier|*
name|aux
parameter_list|,
name|GeglBuffer
modifier|*
name|output
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
DECL|member|pad
name|gpointer
name|pad
index|[
literal|4
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_histogram_sink_get_type
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

