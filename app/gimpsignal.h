begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPSIGNAL_H__
end_ifndef

begin_define
DECL|macro|__GIMPSIGNAL_H__
define|#
directive|define
name|__GIMPSIGNAL_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtksignal.h>
end_include

begin_comment
comment|/* This is the gtk "signal id" */
end_comment

begin_typedef
DECL|typedef|GimpSignalID
typedef|typedef
name|guint
name|GimpSignalID
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSignalType
typedef|typedef
specifier|const
name|struct
name|_GimpSignalType
name|GimpSignalType
typedef|;
end_typedef

begin_comment
comment|/* The arguments are encoded in the names.. */
end_comment

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_void
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerVoid
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerVoid
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_pointer
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerPointer
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerPointer
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
parameter_list|,
name|gpointer
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_int
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerInt
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerInt
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_int_int_int_int
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|typedef|GimpHandlerIntIntIntInt
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHandlerIntIntIntInt
function_decl|)
parameter_list|(
name|GtkObject
modifier|*
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GimpSignalID
name|gimp_signal_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GtkSignalRunType
name|signal_flags
parameter_list|,
name|GtkType
name|object_type
parameter_list|,
name|guint
name|function_offset
parameter_list|,
name|GimpSignalType
modifier|*
name|sig_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

