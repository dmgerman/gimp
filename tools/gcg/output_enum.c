begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"output.h"
end_include

begin_function
DECL|function|p_enum_member (Id id,PrimType * t)
name|PNode
modifier|*
name|p_enum_member
parameter_list|(
name|Id
name|id
parameter_list|,
name|PrimType
modifier|*
name|t
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"\t~,\n"
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
name|NULL
argument_list|,
name|id
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_enum_decl (EnumDef * e)
name|PNode
modifier|*
name|p_enum_decl
parameter_list|(
name|EnumDef
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
return|return
name|p_fmt
argument_list|(
literal|"typedef enum {\n"
literal|"~"
literal|"\t~ = ~\n"
literal|"} ~;\n"
argument_list|,
name|p_for
argument_list|(
name|e
operator|->
name|alternatives
argument_list|,
name|p_enum_member
argument_list|,
name|t
argument_list|)
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
name|NULL
argument_list|,
literal|"LAST"
argument_list|)
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
name|NULL
argument_list|,
name|g_slist_last
argument_list|(
name|e
operator|->
name|alternatives
argument_list|)
operator|->
name|data
argument_list|)
argument_list|,
name|p_primtype
argument_list|(
name|t
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_enum_value (Id i,PrimType * t)
name|PNode
modifier|*
name|p_enum_value
parameter_list|(
name|Id
name|i
parameter_list|,
name|PrimType
modifier|*
name|t
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"\t\t{~,\n"
literal|"\t\t\"~\",\n"
literal|"\t\t\"~\"},\n"
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
name|NULL
argument_list|,
name|i
argument_list|)
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
name|NULL
argument_list|,
name|i
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|i
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|output_enum_type_init (OutCtx * out,EnumDef * e)
name|void
name|output_enum_type_init
parameter_list|(
name|OutCtx
modifier|*
name|out
parameter_list|,
name|EnumDef
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
name|out
argument_list|,
name|t
argument_list|,
literal|"init_type"
argument_list|,
name|NULL
argument_list|,
name|type_gtk_type
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|p_fmt
argument_list|(
literal|"\tstatic GtkEnumValue values[~] = {\n"
literal|"~"
literal|"\t\t{0, NULL, NULL}\n"
literal|"\t};\n"
literal|"\t%2 = gtk_type_register_enum (\"%1\", values);\n"
literal|"\treturn %2;\n"
argument_list|,
name|p_prf
argument_list|(
literal|"%d"
argument_list|,
name|g_slist_length
argument_list|(
name|e
operator|->
name|alternatives
argument_list|)
operator|+
literal|1
argument_list|)
argument_list|,
name|p_for
argument_list|(
name|e
operator|->
name|alternatives
argument_list|,
name|p_enum_value
argument_list|,
name|t
argument_list|)
argument_list|,
name|p_internal_varname
argument_list|(
name|t
argument_list|,
literal|"type"
argument_list|)
argument_list|,
name|p_primtype
argument_list|(
name|t
argument_list|)
argument_list|,
name|p_internal_varname
argument_list|(
name|t
argument_list|,
literal|"type"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_enum (OutCtx * out,EnumDef * e)
name|void
name|output_enum
parameter_list|(
name|OutCtx
modifier|*
name|out
parameter_list|,
name|EnumDef
modifier|*
name|e
parameter_list|)
block|{
name|output_enum_type_init
argument_list|(
name|out
argument_list|,
name|e
argument_list|)
expr_stmt|;
name|pr_add
argument_list|(
name|out
operator|->
name|type_hdr
argument_list|,
name|p_enum_decl
argument_list|(
name|e
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

