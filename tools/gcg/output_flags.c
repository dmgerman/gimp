begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"output.h"
end_include

begin_typedef
DECL|struct|__anon289fd8050108
typedef|typedef
struct|struct
block|{
DECL|member|i
name|gint
name|i
decl_stmt|;
DECL|member|t
name|PrimType
modifier|*
name|t
decl_stmt|;
DECL|typedef|FlagData
block|}
name|FlagData
typedef|;
end_typedef

begin_function
DECL|function|pr_flags_member (File * s,Id id,FlagData * d)
name|void
name|pr_flags_member
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|Id
name|id
parameter_list|,
name|FlagData
modifier|*
name|d
parameter_list|)
block|{
name|pr
argument_list|(
name|s
argument_list|,
literal|"\t%3 = 1<< %d,\n"
argument_list|,
name|pr_macro_name
argument_list|,
name|d
operator|->
name|t
argument_list|,
name|NULL
argument_list|,
name|id
argument_list|,
name|d
operator|->
name|i
argument_list|)
expr_stmt|;
name|d
operator|->
name|i
operator|++
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_flags_decl (File * s,FlagsDef * e)
name|void
name|pr_flags_decl
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|FlagsDef
modifier|*
name|e
parameter_list|)
block|{
name|FlagData
name|d
init|=
block|{
literal|0
block|,
name|DEF
argument_list|(
name|e
argument_list|)
operator|->
name|type
block|}
decl_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"typedef enum {\n"
literal|"%3"
literal|"} %1;\n"
argument_list|,
name|pr_list_foreach
argument_list|,
name|e
operator|->
name|flags
argument_list|,
name|pr_flags_member
argument_list|,
operator|&
name|d
argument_list|,
name|pr_primtype
argument_list|,
name|d
operator|.
name|t
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_flags_value (File * s,Id i,PrimType * t)
name|void
name|pr_flags_value
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|Id
name|i
parameter_list|,
name|PrimType
modifier|*
name|t
parameter_list|)
block|{
name|pr
argument_list|(
name|s
argument_list|,
literal|"\t\t{%3,\n"
literal|"\t\t\"%3\",\n"
literal|"\t\t\"%s\"},\n"
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
name|NULL
argument_list|,
name|i
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
name|NULL
argument_list|,
name|i
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_flags_type_init (FlagsDef * e)
name|void
name|output_flags_type_init
parameter_list|(
name|FlagsDef
modifier|*
name|e
parameter_list|)
block|{
name|PrimType
modifier|*
name|t
init|=
name|DEF
argument_list|(
name|e
argument_list|)
operator|->
name|type
decl_stmt|;
name|output_func
argument_list|(
name|t
argument_list|,
literal|"init_type"
argument_list|,
name|NULL
argument_list|,
name|type_gtk_type
argument_list|,
name|type_hdr
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|"\tstatic GtkFlagValue values[%d] = {\n"
literal|"%3"
literal|"\t\t{0, NULL, NULL}\n"
literal|"\t};\n"
literal|"\t%2 = gtk_type_register_flags (\"%1\", values);\n"
literal|"\treturn %2;\n"
argument_list|,
name|g_slist_length
argument_list|(
name|e
operator|->
name|flags
argument_list|)
operator|+
literal|1
argument_list|,
name|pr_list_foreach
argument_list|,
name|e
operator|->
name|flags
argument_list|,
name|pr_flags_value
argument_list|,
name|t
argument_list|,
name|pr_internal_varname
argument_list|,
name|t
argument_list|,
literal|"type"
argument_list|,
name|pr_primtype
argument_list|,
name|t
argument_list|,
name|pr_internal_varname
argument_list|,
name|t
argument_list|,
literal|"type"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_flags (FlagsDef * e)
name|void
name|output_flags
parameter_list|(
name|FlagsDef
modifier|*
name|e
parameter_list|)
block|{
name|output_def
argument_list|(
name|DEF
argument_list|(
name|e
argument_list|)
argument_list|)
expr_stmt|;
name|pr_flags_decl
argument_list|(
name|type_hdr
argument_list|,
name|e
argument_list|)
expr_stmt|;
name|output_flags_type_init
argument_list|(
name|e
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|flags_class
name|DefClass
name|flags_class
init|=
block|{
name|output_flags
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|type_gtk_type
name|Type
modifier|*
name|type_gtk_type
decl_stmt|;
end_decl_stmt

end_unit

