begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"output.h"
end_include

begin_function
DECL|function|pr_object_member (File * s,Member * m)
name|void
name|pr_object_member
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|Member
modifier|*
name|m
parameter_list|)
block|{
name|DataMember
modifier|*
name|d
decl_stmt|;
if|if
condition|(
name|m
operator|->
name|membertype
operator|!=
name|MEMBER_DATA
operator|||
name|m
operator|->
name|kind
operator|!=
name|KIND_DIRECT
condition|)
return|return;
name|d
operator|=
operator|(
name|DataMember
operator|*
operator|)
name|m
expr_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"\t%1 %1;\n"
argument_list|,
name|pr_type
argument_list|,
operator|&
name|d
operator|->
name|type
argument_list|,
name|pr_low
argument_list|,
name|m
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_object_body (File * s,ObjectDef * o)
name|void
name|pr_object_body
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|GSList
modifier|*
name|l
decl_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"struct _%1 {\n"
literal|"\t%1 parent;\n"
literal|"%3"
literal|"};\n"
argument_list|,
name|pr_primtype
argument_list|,
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|,
name|pr_primtype
argument_list|,
name|o
operator|->
name|parent
argument_list|,
name|pr_list_foreach
argument_list|,
name|o
operator|->
name|members
argument_list|,
name|pr_object_member
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_object_decl (File * s,ObjectDef * o)
name|void
name|pr_object_decl
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|PrimType
modifier|*
name|n
init|=
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
decl_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"#ifdef STRICT_OBJECT_TYPES\n"
literal|"typedef struct _%1 %1;\n"
literal|"#else\n"
literal|"typedef struct _GenericObject %1;\n"
literal|"#endif\n"
argument_list|,
name|pr_primtype
argument_list|,
name|n
argument_list|,
name|pr_primtype
argument_list|,
name|n
argument_list|,
name|pr_primtype
argument_list|,
name|n
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_class_member (File * s,Member * m)
name|void
name|pr_class_member
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|Member
modifier|*
name|m
parameter_list|)
block|{
name|ParamOptions
name|o
init|=
name|PARAMS_TYPES
decl_stmt|;
if|if
condition|(
name|m
operator|->
name|kind
operator|!=
name|KIND_ABSTRACT
condition|)
return|return;
if|if
condition|(
name|m
operator|->
name|membertype
operator|==
name|MEMBER_DATA
condition|)
block|{
name|DataMember
modifier|*
name|d
init|=
operator|(
name|DataMember
operator|*
operator|)
name|m
decl_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"\t%1 %s;\n"
argument_list|,
name|pr_type
argument_list|,
operator|&
name|d
operator|->
name|type
argument_list|,
name|m
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|m
operator|->
name|membertype
operator|==
name|MEMBER_METHOD
condition|)
block|{
name|Method
modifier|*
name|d
init|=
operator|(
name|Method
operator|*
operator|)
name|m
decl_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"\t%1 (*%s) (%1%2);\n"
argument_list|,
name|pr_type
argument_list|,
operator|&
name|d
operator|->
name|ret_type
argument_list|,
name|m
operator|->
name|name
argument_list|,
name|pr_type
argument_list|,
operator|&
name|m
operator|->
name|my_class
operator|->
name|self_type
index|[
name|d
operator|->
name|self_const
index|]
argument_list|,
name|pr_params
argument_list|,
name|d
operator|->
name|params
argument_list|,
operator|&
name|o
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|pr_class_name (File * s,PrimType * o)
name|void
name|pr_class_name
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|PrimType
modifier|*
name|o
parameter_list|)
block|{
name|pr
argument_list|(
name|s
argument_list|,
literal|"%1Class"
argument_list|,
name|pr_primtype
argument_list|,
name|o
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_impl_name (File * s,ObjectDef * o)
name|void
name|pr_impl_name
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|pr
argument_list|(
name|s
argument_list|,
literal|"%1Impl"
argument_list|,
name|pr_type
argument_list|,
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_class_body (File * s,ObjectDef * o)
name|void
name|pr_class_body
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|pr
argument_list|(
name|s
argument_list|,
literal|"struct _%1 {\n"
literal|"\t%1 parent_class;\n"
literal|"%3"
literal|"};\n"
argument_list|,
name|pr_class_name
argument_list|,
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|,
name|pr_class_name
argument_list|,
name|o
operator|->
name|parent
argument_list|,
name|pr_list_foreach
argument_list|,
name|o
operator|->
name|members
argument_list|,
name|pr_class_member
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|pr_class_decl (File * s,ObjectDef * o)
name|void
name|pr_class_decl
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|pr
argument_list|(
name|s
argument_list|,
literal|"typedef struct _%1 %1;\n"
argument_list|,
name|pr_class_name
argument_list|,
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|,
name|pr_class_name
argument_list|,
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_abstract_method (Method * m)
name|void
name|output_abstract_method
parameter_list|(
name|Method
modifier|*
name|m
parameter_list|)
block|{
name|PrimType
modifier|*
name|t
init|=
name|DEF
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
argument_list|)
operator|->
name|type
decl_stmt|;
name|Id
name|name
init|=
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
decl_stmt|;
name|ParamOptions
name|o
init|=
name|PARAMS_NAMES
decl_stmt|;
name|output_func
argument_list|(
name|t
argument_list|,
name|name
argument_list|,
name|m
operator|->
name|params
argument_list|,
operator|&
name|m
operator|->
name|ret_type
argument_list|,
name|m
operator|->
name|prot
operator|==
name|METH_PUBLIC
condition|?
name|func_hdr
else|:
name|prot_hdr
argument_list|,
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
argument_list|,
name|m
operator|->
name|self_const
argument_list|,
name|FALSE
argument_list|,
literal|"\t%?s%3(GTK_OBJECT(self)->klass)->%s(self%2);\n"
argument_list|,
operator|!
operator|!
name|m
operator|->
name|ret_type
operator|.
name|prim
argument_list|,
literal|"return "
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
name|NULL
argument_list|,
literal|"CLASS"
argument_list|,
name|name
argument_list|,
name|pr_params
argument_list|,
name|m
operator|->
name|params
argument_list|,
operator|&
name|o
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_data_member (DataMember * m)
name|void
name|output_data_member
parameter_list|(
name|DataMember
modifier|*
name|m
parameter_list|)
block|{
name|Id
name|name
init|=
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
decl_stmt|;
name|PrimType
modifier|*
name|t
init|=
name|DEF
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
argument_list|)
operator|->
name|type
decl_stmt|;
switch|switch
condition|(
name|m
operator|->
name|prot
condition|)
block|{
case|case
name|DATA_READWRITE
case|:
block|{
name|Id
name|set_name
init|=
name|g_strconcat
argument_list|(
literal|"set_"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|Param
name|p
decl_stmt|;
name|GSList
name|l
decl_stmt|;
name|p
operator|.
name|type
operator|=
name|m
operator|->
name|type
expr_stmt|;
name|p
operator|.
name|name
operator|=
literal|"value"
expr_stmt|;
name|l
operator|.
name|data
operator|=
operator|&
name|p
expr_stmt|;
name|l
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
name|output_func
argument_list|(
name|t
argument_list|,
name|set_name
argument_list|,
operator|&
name|l
argument_list|,
name|NULL
argument_list|,
name|func_hdr
argument_list|,
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|"\tself->%s=value;\n"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|set_name
argument_list|)
expr_stmt|;
block|}
comment|/* fall through */
case|case
name|DATA_READONLY
case|:
name|output_func
argument_list|(
name|t
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|,
operator|&
name|m
operator|->
name|type
argument_list|,
name|func_hdr
argument_list|,
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|"\treturn self->%s;\n"
argument_list|,
name|name
argument_list|)
expr_stmt|;
case|case
name|DATA_PROTECTED
case|:
block|}
block|}
end_function

begin_function
DECL|function|output_member (Member * m,gpointer dummy)
name|void
name|output_member
parameter_list|(
name|Member
modifier|*
name|m
parameter_list|,
name|gpointer
name|dummy
parameter_list|)
block|{
switch|switch
condition|(
name|m
operator|->
name|membertype
condition|)
block|{
case|case
name|MEMBER_METHOD
case|:
if|if
condition|(
name|m
operator|->
name|kind
operator|==
name|KIND_ABSTRACT
condition|)
name|output_abstract_method
argument_list|(
operator|(
name|Method
operator|*
operator|)
name|m
argument_list|)
expr_stmt|;
break|break;
case|case
name|MEMBER_DATA
case|:
if|if
condition|(
name|m
operator|->
name|kind
operator|==
name|KIND_DIRECT
condition|)
name|output_data_member
argument_list|(
operator|(
name|DataMember
operator|*
operator|)
name|m
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
DECL|function|pr_class_macros (File * s,ObjectDef * o)
name|void
name|pr_class_macros
parameter_list|(
name|File
modifier|*
name|s
parameter_list|,
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|PrimType
modifier|*
name|t
init|=
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
decl_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"#define %3(o) GTK_CHECK_CAST(o, %3, %1)\n"
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
literal|"TYPE"
argument_list|,
name|NULL
argument_list|,
name|pr_primtype
argument_list|,
name|t
argument_list|)
expr_stmt|;
name|pr
argument_list|(
name|s
argument_list|,
literal|"#define %3(o) GTK_CHECK_TYPE(o, %3)\n"
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
literal|"IS"
argument_list|,
name|NULL
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
literal|"TYPE"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_object_type_init (ObjectDef * o)
name|void
name|output_object_type_init
parameter_list|(
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|PrimType
modifier|*
name|t
init|=
name|DEF
argument_list|(
name|o
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
literal|"\tstatic GtkTypeInfo info = {\n"
literal|"\t\t\"%1\",\n"
literal|"\t\tsizeof (%1),\n"
literal|"\t\tsizeof (%1),\n"
literal|"\t\t(GtkClassInitFunc) %2,\n"
literal|"\t\t(GtkObjectInitFunc) %2,\n"
literal|"\t\tNULL,\n"
literal|"\t\tNULL,\n"
literal|"\t\tNULL,\n"
literal|"\t};\n"
literal|"\t%2 = gtk_type_unique (%3,&info);\n"
literal|"\treturn %2;\n"
argument_list|,
name|pr_primtype
argument_list|,
name|t
argument_list|,
name|pr_primtype
argument_list|,
name|t
argument_list|,
name|pr_class_name
argument_list|,
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|,
name|pr_varname
argument_list|,
name|t
argument_list|,
literal|"class_init"
argument_list|,
name|pr_varname
argument_list|,
name|t
argument_list|,
literal|"init"
argument_list|,
name|pr_internal_varname
argument_list|,
name|t
argument_list|,
literal|"type"
argument_list|,
name|pr_macro_name
argument_list|,
name|o
operator|->
name|parent
argument_list|,
literal|"TYPE"
argument_list|,
name|NULL
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
DECL|function|output_object (ObjectDef * o)
name|void
name|output_object
parameter_list|(
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
name|output_def
argument_list|(
name|DEF
argument_list|(
name|o
argument_list|)
argument_list|)
expr_stmt|;
name|output_object_type_init
argument_list|(
name|o
argument_list|)
expr_stmt|;
name|pr_class_body
argument_list|(
name|prot_hdr
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|pr_class_decl
argument_list|(
name|prot_hdr
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|pr_object_decl
argument_list|(
name|type_hdr
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|pr_object_body
argument_list|(
name|prot_hdr
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
name|o
operator|->
name|members
argument_list|,
name|output_member
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|object_class
name|DefClass
name|object_class
init|=
block|{
name|output_object
block|}
decl_stmt|;
end_decl_stmt

end_unit

