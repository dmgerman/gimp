begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_struct
DECL|struct|_GimpSignalType
struct|struct
name|_GimpSignalType
block|{
DECL|member|marshaller
name|GtkSignalMarshaller
name|marshaller
decl_stmt|;
DECL|member|return_type
name|GtkType
name|return_type
decl_stmt|;
DECL|member|nparams
name|guint
name|nparams
decl_stmt|;
DECL|member|param_types
specifier|const
name|GtkType
modifier|*
name|param_types
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|TypeArr
typedef|typedef
specifier|const
name|GtkType
name|TypeArr
index|[]
typedef|;
end_typedef

begin_function
DECL|function|gimp_signal_new (const gchar * name,GtkSignalRunType signal_flags,GtkType object_type,guint function_offset,GimpSignalType * sig_type)
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
block|{
return|return
name|gtk_signal_newv
argument_list|(
name|name
argument_list|,
name|signal_flags
argument_list|,
name|object_type
argument_list|,
name|function_offset
argument_list|,
name|sig_type
operator|->
name|marshaller
argument_list|,
name|sig_type
operator|->
name|return_type
argument_list|,
name|sig_type
operator|->
name|nparams
argument_list|,
comment|/* Bah. We try to be const correct, but  				  gtk isn't.. */
operator|(
name|GtkType
operator|*
operator|)
name|sig_type
operator|->
name|param_types
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|sigtype_void
specifier|static
name|GimpSignalType
name|sigtype_void
init|=
block|{
name|gtk_signal_default_marshaller
block|,
name|GTK_TYPE_NONE
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_sigtype_void
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_void
init|=
operator|&
name|sigtype_void
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_marshaller_pointer (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshaller_pointer
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|(
operator|*
operator|(
name|GimpHandlerPointer
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_POINTER
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|pointer_types
specifier|static
name|TypeArr
name|pointer_types
init|=
block|{
name|GTK_TYPE_POINTER
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sigtype_pointer
specifier|static
name|GimpSignalType
name|sigtype_pointer
init|=
block|{
name|gimp_marshaller_pointer
block|,
name|GTK_TYPE_NONE
block|,
literal|1
block|,
name|pointer_types
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_sigtype_pointer
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_pointer
init|=
operator|&
name|sigtype_pointer
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_marshaller_int (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshaller_int
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|(
operator|*
operator|(
name|GimpHandlerInt
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|int_types
specifier|static
name|TypeArr
name|int_types
init|=
block|{
name|GTK_TYPE_INT
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sigtype_int
specifier|static
name|GimpSignalType
name|sigtype_int
init|=
block|{
name|gimp_marshaller_int
block|,
name|GTK_TYPE_NONE
block|,
literal|1
block|,
name|int_types
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_sigtype_int
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_int
init|=
operator|&
name|sigtype_int
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_marshaller_int_int_int_int (GtkObject * object,GtkSignalFunc func,gpointer func_data,GtkArg * args)
name|gimp_marshaller_int_int_int_int
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|,
name|gpointer
name|func_data
parameter_list|,
name|GtkArg
modifier|*
name|args
parameter_list|)
block|{
operator|(
operator|*
operator|(
name|GimpHandlerIntIntIntInt
operator|)
name|func
operator|)
operator|(
name|object
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|1
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|2
index|]
argument_list|)
operator|,
name|GTK_VALUE_INT
argument_list|(
name|args
index|[
literal|3
index|]
argument_list|)
operator|,
name|func_data
operator|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|int_int_int_int_types
specifier|static
name|TypeArr
name|int_int_int_int_types
init|=
block|{
name|GTK_TYPE_INT
block|,
name|GTK_TYPE_INT
block|,
name|GTK_TYPE_INT
block|,
name|GTK_TYPE_INT
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sigtype_int_int_int_int
specifier|static
name|GimpSignalType
name|sigtype_int_int_int_int
init|=
block|{
name|gimp_marshaller_int_int_int_int
block|,
name|GTK_TYPE_NONE
block|,
literal|4
block|,
name|int_int_int_int_types
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_sigtype_int_int_int_int
name|GimpSignalType
modifier|*
specifier|const
name|gimp_sigtype_int_int_int_int
init|=
operator|&
name|sigtype_int_int_int_int
decl_stmt|;
end_decl_stmt

end_unit

