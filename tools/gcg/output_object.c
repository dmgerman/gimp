begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"output.h"
end_include

begin_include
include|#
directive|include
file|"marshall.h"
end_include

begin_function
DECL|function|p_self_name (Member * o)
name|PNode
modifier|*
name|p_self_name
parameter_list|(
name|Member
modifier|*
name|o
parameter_list|)
block|{
return|return
name|p_c_ident
argument_list|(
name|DEF
argument_list|(
name|o
operator|->
name|my_class
argument_list|)
operator|->
name|type
operator|->
name|name
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_object_member (Member * m)
name|PNode
modifier|*
name|p_object_member
parameter_list|(
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
condition|)
return|return
name|p_nil
return|;
name|d
operator|=
operator|(
name|DataMember
operator|*
operator|)
name|m
expr_stmt|;
if|if
condition|(
name|d
operator|->
name|kind
operator|!=
name|DATA_DIRECT
condition|)
return|return
name|p_nil
return|;
return|return
name|p_fmt
argument_list|(
literal|"\t~ ~;\n"
argument_list|,
name|p_type
argument_list|(
operator|&
name|d
operator|->
name|type
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|m
operator|->
name|name
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_object_body (ObjectDef * o)
name|PNode
modifier|*
name|p_object_body
parameter_list|(
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"struct _~ {\n"
literal|"\t~ parent;\n"
literal|"~"
literal|"};\n"
argument_list|,
name|p_primtype
argument_list|(
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|)
argument_list|,
name|p_primtype
argument_list|(
name|o
operator|->
name|parent
argument_list|)
argument_list|,
name|p_for
argument_list|(
name|o
operator|->
name|members
argument_list|,
name|p_object_member
argument_list|,
name|p_nil
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_object_decl (ObjectDef * o)
name|PNode
modifier|*
name|p_object_decl
parameter_list|(
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
return|return
name|p_fmt
argument_list|(
literal|"typedef struct _~ ~;\n"
argument_list|,
name|p_primtype
argument_list|(
name|n
argument_list|)
argument_list|,
name|p_primtype
argument_list|(
name|n
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_class_member (Member * m)
name|PNode
modifier|*
name|p_class_member
parameter_list|(
name|Member
modifier|*
name|m
parameter_list|)
block|{
name|ParamOptions
name|o
init|=
block|{
name|TRUE
block|,
name|FALSE
block|,
name|TRUE
block|}
decl_stmt|;
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
if|if
condition|(
name|d
operator|->
name|kind
operator|!=
name|DATA_STATIC_VIRTUAL
condition|)
return|return
name|p_nil
return|;
else|else
return|return
name|p_fmt
argument_list|(
literal|"\t~ ~;\n"
argument_list|,
name|p_type
argument_list|(
operator|&
name|d
operator|->
name|type
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|m
operator|->
name|name
argument_list|)
argument_list|)
return|;
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
name|FunParams
modifier|*
name|p
decl_stmt|;
name|PNode
modifier|*
name|parnode
decl_stmt|;
if|if
condition|(
name|d
operator|->
name|kind
operator|==
name|METH_STATIC
operator|||
name|d
operator|->
name|kind
operator|==
name|METH_DIRECT
condition|)
return|return
name|p_nil
return|;
name|p
operator|=
name|fparams
argument_list|(
literal|"tp"
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
name|p_nil
argument_list|,
name|p_nil
argument_list|,
name|d
operator|->
name|params
argument_list|)
expr_stmt|;
name|parnode
operator|=
name|p_params
argument_list|(
name|p
argument_list|,
operator|&
name|o
argument_list|)
expr_stmt|;
name|fparams_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
return|return
name|p_fmt
argument_list|(
literal|"\t~ (*~) (~);\n"
argument_list|,
name|p_type
argument_list|(
operator|&
name|d
operator|->
name|ret_type
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|m
operator|->
name|name
argument_list|)
argument_list|,
name|parnode
argument_list|)
return|;
block|}
else|else
return|return
name|p_nil
return|;
block|}
end_function

begin_function
DECL|function|p_class_name (PrimType * o)
name|PNode
modifier|*
name|p_class_name
parameter_list|(
name|PrimType
modifier|*
name|o
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"~Class"
argument_list|,
name|p_primtype
argument_list|(
name|o
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_impl_name (ObjectDef * o)
name|PNode
modifier|*
name|p_impl_name
parameter_list|(
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"~Impl"
argument_list|,
name|p_primtype
argument_list|(
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_class_body (ObjectDef * o)
name|PNode
modifier|*
name|p_class_body
parameter_list|(
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"struct _~ {\n"
literal|"\t~ parent_class;\n"
literal|"~"
literal|"};\n"
argument_list|,
name|p_class_name
argument_list|(
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|)
argument_list|,
name|p_class_name
argument_list|(
name|o
operator|->
name|parent
argument_list|)
argument_list|,
name|p_for
argument_list|(
name|o
operator|->
name|members
argument_list|,
name|p_class_member
argument_list|,
name|p_nil
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_class_decl (ObjectDef * o)
name|PNode
modifier|*
name|p_class_decl
parameter_list|(
name|ObjectDef
modifier|*
name|o
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"typedef struct _~ ~;\n"
argument_list|,
name|p_class_name
argument_list|(
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|)
argument_list|,
name|p_class_name
argument_list|(
name|DEF
argument_list|(
name|o
argument_list|)
operator|->
name|type
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_real_varname (PrimType * t,PNode * name)
name|PNode
modifier|*
name|p_real_varname
parameter_list|(
name|PrimType
modifier|*
name|t
parameter_list|,
name|PNode
modifier|*
name|name
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"~_real"
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|name
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_signal_handler_type (Method * s)
name|PNode
modifier|*
name|p_signal_handler_type
parameter_list|(
name|Method
modifier|*
name|s
parameter_list|)
block|{
name|Member
modifier|*
name|m
init|=
name|MEMBER
argument_list|(
name|s
argument_list|)
decl_stmt|;
return|return
name|p_fmt
argument_list|(
literal|"~Handler_~"
argument_list|,
name|p_primtype
argument_list|(
name|DEF
argument_list|(
name|m
operator|->
name|my_class
argument_list|)
operator|->
name|type
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|m
operator|->
name|name
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|output_connector (PRoot * out,Method * m)
name|void
name|output_connector
parameter_list|(
name|PRoot
modifier|*
name|out
parameter_list|,
name|Method
modifier|*
name|m
parameter_list|)
block|{
name|FunParams
modifier|*
name|par
init|=
name|fparams
argument_list|(
literal|"t"
argument_list|,
operator|&
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
operator|->
name|self_type
index|[
name|m
operator|->
name|self_const
index|]
argument_list|,
name|p_self_name
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
argument_list|)
argument_list|,
name|p_nil
argument_list|)
decl_stmt|;
name|output_func
argument_list|(
name|out
argument_list|,
literal|"functions"
argument_list|,
operator|&
name|m
operator|->
name|ret_type
argument_list|,
name|p_varname
argument_list|(
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
argument_list|,
name|p_fmt
argument_list|(
literal|"connect_~"
argument_list|,
name|p_c_ident
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|p_fmt
argument_list|(
literal|"\n\t~ handler,\n\tgpointer user_data"
argument_list|,
name|p_signal_handler_type
argument_list|(
name|m
argument_list|)
argument_list|)
argument_list|,
name|par
argument_list|,
name|p_fmt
argument_list|(
literal|"\t~gtk_signal_connect((GtkObject*)~,\n"
literal|"\t\t\"~\",\n"
literal|"\t\t(GtkSignalFunc)handler,\n"
literal|"\t\tuser_data);\n"
argument_list|,
name|m
operator|->
name|ret_type
operator|.
name|prim
condition|?
name|p_str
argument_list|(
literal|"return "
argument_list|)
else|:
name|p_nil
argument_list|,
name|p_self_name
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|output_var_import
argument_list|(
name|out
argument_list|,
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
argument_list|,
name|p_fmt
argument_list|(
literal|"connect_~"
argument_list|,
name|p_c_ident
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|p_param_marshtype (gpointer p)
name|PNode
modifier|*
name|p_param_marshtype
parameter_list|(
name|gpointer
name|p
parameter_list|)
block|{
name|Param
modifier|*
name|param
init|=
name|p
decl_stmt|;
return|return
name|p_fmt
argument_list|(
literal|",\n\t\t~"
argument_list|,
name|p_gtktype
argument_list|(
operator|&
name|param
operator|->
name|type
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|output_method (PRoot * out,Method * m)
name|void
name|output_method
parameter_list|(
name|PRoot
modifier|*
name|out
parameter_list|,
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
name|PNode
modifier|*
name|name
init|=
name|p_c_ident
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
decl_stmt|;
name|MethodKind
name|k
init|=
name|m
operator|->
name|kind
decl_stmt|;
name|ParamOptions
name|o
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
name|FALSE
block|}
decl_stmt|;
name|FunParams
modifier|*
name|par
decl_stmt|;
name|PNode
modifier|*
name|dispatch
decl_stmt|;
name|GSList
modifier|*
name|params
decl_stmt|;
if|if
condition|(
name|k
operator|==
name|METH_STATIC
condition|)
name|par
operator|=
name|fparams
argument_list|(
literal|"p"
argument_list|,
name|m
operator|->
name|params
argument_list|)
expr_stmt|;
else|else
name|par
operator|=
name|fparams
argument_list|(
literal|"tp"
argument_list|,
operator|&
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
operator|->
name|self_type
index|[
name|m
operator|->
name|self_const
index|]
argument_list|,
name|p_self_name
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
argument_list|)
argument_list|,
name|p_nil
argument_list|,
name|m
operator|->
name|params
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|k
condition|)
block|{
name|SignalType
modifier|*
name|sig
decl_stmt|;
case|case
name|METH_EMIT_PRE
case|:
case|case
name|METH_EMIT_POST
case|:
case|case
name|METH_EMIT_BOTH
case|:
name|sig
operator|=
name|sig_type
argument_list|(
name|m
argument_list|)
expr_stmt|;
name|output_var
argument_list|(
name|out
argument_list|,
name|NULL
argument_list|,
name|p_str
argument_list|(
literal|"guint"
argument_list|)
argument_list|,
name|p_signal_id
argument_list|(
name|m
argument_list|)
argument_list|)
expr_stmt|;
name|o
operator|.
name|names
operator|=
name|FALSE
expr_stmt|;
name|o
operator|.
name|types
operator|=
name|TRUE
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"source_sigtypes"
argument_list|,
name|sig
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"member_class_init"
argument_list|,
name|p_fmt
argument_list|(
literal|"\t~ =\n"
literal|"\tgtk_signal_new(\"~\",\n"
literal|"\t\tGTK_RUN_~,\n"
literal|"\t\tobklass->type,\n"
literal|"\t\tGTK_SIGNAL_OFFSET (~, ~),\n"
literal|"\t\t~,\n"
literal|"\t\t~,\n"
literal|"\t\t~"
literal|"~);\n"
literal|"\tgtk_object_class_add_signals(obklass,\n"
literal|"\t\t&~,\n"
literal|"\t\t1);\n"
argument_list|,
name|p_signal_id
argument_list|(
name|m
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|m
operator|->
name|kind
operator|==
name|METH_EMIT_PRE
condition|?
literal|"FIRST"
else|:
name|m
operator|->
name|kind
operator|==
name|METH_EMIT_POST
condition|?
literal|"LAST"
else|:
literal|"BOTH"
argument_list|)
argument_list|,
name|p_class_name
argument_list|(
name|t
argument_list|)
argument_list|,
name|name
argument_list|,
name|p_signal_demarshaller_name
argument_list|(
name|sig
argument_list|)
argument_list|,
name|p_gtktype
argument_list|(
operator|&
name|m
operator|->
name|ret_type
argument_list|)
argument_list|,
name|p_prf
argument_list|(
literal|"%d"
argument_list|,
name|g_slist_length
argument_list|(
name|m
operator|->
name|params
argument_list|)
argument_list|)
argument_list|,
name|p_for
argument_list|(
name|m
operator|->
name|params
argument_list|,
name|p_param_marshtype
argument_list|,
name|p_nil
argument_list|)
argument_list|,
name|p_signal_id
argument_list|(
name|m
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"functions"
argument_list|,
name|p_fmt
argument_list|(
literal|"typedef ~ (*~)("
literal|"~,\n"
literal|"\tgpointer);\n"
argument_list|,
name|p_type
argument_list|(
operator|&
name|m
operator|->
name|ret_type
argument_list|)
argument_list|,
name|p_signal_handler_type
argument_list|(
name|m
argument_list|)
argument_list|,
name|p_params
argument_list|(
name|par
argument_list|,
operator|&
name|o
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|output_connector
argument_list|(
name|out
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|o
operator|.
name|names
operator|=
name|TRUE
expr_stmt|;
name|o
operator|.
name|types
operator|=
name|FALSE
expr_stmt|;
name|dispatch
operator|=
name|p_sig_marshalling
argument_list|(
name|m
argument_list|)
expr_stmt|;
break|break;
case|case
name|METH_STATIC
case|:
case|case
name|METH_DIRECT
case|:
block|{
name|PNode
modifier|*
name|impl_name
decl_stmt|;
name|o
operator|.
name|names
operator|=
name|TRUE
expr_stmt|;
name|o
operator|.
name|types
operator|=
name|FALSE
expr_stmt|;
name|impl_name
operator|=
name|p_fmt
argument_list|(
literal|"~_~"
argument_list|,
name|p_c_macro
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|p_c_macro
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|dispatch
operator|=
name|p_fmt
argument_list|(
literal|"#ifdef ~\n"
literal|"\t~~ (~);\n"
literal|"#else\n"
literal|"\tg_error(\"Not implemented: ~.~.~\");\n"
literal|"#endif\n"
argument_list|,
name|impl_name
argument_list|,
name|m
operator|->
name|ret_type
operator|.
name|prim
condition|?
name|p_str
argument_list|(
literal|"return "
argument_list|)
else|:
name|p_nil
argument_list|,
name|impl_name
argument_list|,
name|p_params
argument_list|(
name|par
argument_list|,
operator|&
name|o
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|t
operator|->
name|module
operator|->
name|package
operator|->
name|name
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
case|case
name|METH_VIRTUAL
case|:
name|dispatch
operator|=
name|p_fmt
argument_list|(
literal|"\t~((~*)((GtkObject*) ~)->klass)->~ (~);\n"
argument_list|,
name|m
operator|->
name|ret_type
operator|.
name|prim
condition|?
name|p_str
argument_list|(
literal|"return "
argument_list|)
else|:
name|p_nil
argument_list|,
name|p_class_name
argument_list|(
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
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|name
argument_list|,
name|p_params
argument_list|(
name|par
argument_list|,
operator|&
name|o
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|output_func
argument_list|(
name|out
argument_list|,
name|m
operator|->
name|prot
operator|==
name|METH_PUBLIC
condition|?
literal|"functions"
else|:
literal|"protected"
argument_list|,
operator|&
name|m
operator|->
name|ret_type
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|name
argument_list|)
argument_list|,
name|p_nil
argument_list|,
name|par
argument_list|,
name|dispatch
argument_list|)
expr_stmt|;
name|output_var_import
argument_list|(
name|out
argument_list|,
name|t
argument_list|,
name|name
argument_list|)
expr_stmt|;
for|for
control|(
name|params
operator|=
name|m
operator|->
name|params
init|;
name|params
condition|;
name|params
operator|=
name|params
operator|->
name|next
control|)
name|pr_put
argument_list|(
name|out
argument_list|,
name|m
operator|->
name|prot
operator|==
name|METH_PUBLIC
condition|?
literal|"func_depends"
else|:
literal|"prot_depends"
argument_list|,
operator|(
operator|(
name|Param
operator|*
operator|)
operator|(
name|params
operator|->
name|data
operator|)
operator|)
operator|->
name|type
operator|.
name|prim
operator|->
name|module
argument_list|)
expr_stmt|;
name|fparams_free
argument_list|(
name|par
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_data_member (PRoot * out,DataMember * m)
name|void
name|output_data_member
parameter_list|(
name|PRoot
modifier|*
name|out
parameter_list|,
name|DataMember
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
name|PNode
modifier|*
name|name
init|=
name|p_c_ident
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|name
argument_list|)
decl_stmt|;
name|PNode
modifier|*
name|self
init|=
name|p_self_name
argument_list|(
name|MEMBER
argument_list|(
name|m
argument_list|)
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|m
operator|->
name|prot
condition|)
block|{
name|FunParams
modifier|*
name|par
decl_stmt|;
case|case
name|DATA_READWRITE
case|:
block|{
name|par
operator|=
name|fparams
argument_list|(
literal|"tt"
argument_list|,
operator|&
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
operator|->
name|self_type
index|[
name|FALSE
index|]
argument_list|,
name|self
argument_list|,
name|p_nil
argument_list|,
operator|&
name|m
operator|->
name|type
argument_list|,
name|name
argument_list|,
name|p_nil
argument_list|)
expr_stmt|;
name|output_var_import
argument_list|(
name|out
argument_list|,
name|t
argument_list|,
name|p_fmt
argument_list|(
literal|"set_~"
argument_list|,
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|output_func
argument_list|(
name|out
argument_list|,
literal|"functions"
argument_list|,
name|NULL
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|p_fmt
argument_list|(
literal|"set_~"
argument_list|,
name|name
argument_list|)
argument_list|)
argument_list|,
name|p_nil
argument_list|,
name|par
argument_list|,
name|p_fmt
argument_list|(
literal|"~"
literal|"\t~->~ = ~;\n"
argument_list|,
operator|(
name|m
operator|->
name|type
operator|.
name|prim
operator|->
name|kind
operator|==
name|TYPE_OBJECT
operator|&&
name|m
operator|->
name|type
operator|.
name|indirection
operator|==
literal|1
operator|)
condition|?
name|m
operator|->
name|type
operator|.
name|notnull
condition|?
name|p_fmt
argument_list|(
literal|"\tgtk_object_ref "
literal|"((GtkObject*) ~);\n"
literal|"\tgtk_object_unref "
literal|"((GtkObject*) ~->~);\n"
argument_list|,
name|name
argument_list|,
name|self
argument_list|,
name|name
argument_list|)
else|:
name|p_fmt
argument_list|(
literal|"\tif(~)\n"
literal|"\t\tgtk_object_ref "
literal|"((GtkObject*) ~);\n"
literal|"\tif(~->~)\n"
literal|"\t\tgtk_object_unref "
literal|"((GtkObject*) ~->~);\n"
argument_list|,
name|name
argument_list|,
name|name
argument_list|,
name|self
argument_list|,
name|name
argument_list|,
name|self
argument_list|,
name|name
argument_list|)
else|:
name|p_nil
argument_list|,
name|self
argument_list|,
name|name
argument_list|,
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|fparams_free
argument_list|(
name|par
argument_list|)
expr_stmt|;
block|}
comment|/* fall through */
case|case
name|DATA_READONLY
case|:
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"func_depends"
argument_list|,
name|m
operator|->
name|type
operator|.
name|prim
operator|->
name|module
argument_list|)
expr_stmt|;
name|par
operator|=
name|fparams
argument_list|(
literal|"t"
argument_list|,
operator|&
name|MEMBER
argument_list|(
name|m
argument_list|)
operator|->
name|my_class
operator|->
name|self_type
index|[
name|TRUE
index|]
argument_list|,
name|self
argument_list|,
name|p_nil
argument_list|)
expr_stmt|;
name|output_var_import
argument_list|(
name|out
argument_list|,
name|t
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|output_func
argument_list|(
name|out
argument_list|,
literal|"functions"
argument_list|,
operator|&
name|m
operator|->
name|type
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|name
argument_list|)
argument_list|,
name|p_nil
argument_list|,
name|par
argument_list|,
name|p_fmt
argument_list|(
literal|"\treturn ~->~;\n"
argument_list|,
name|self
argument_list|,
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|fparams_free
argument_list|(
name|par
argument_list|)
expr_stmt|;
comment|/* fall through */
case|case
name|DATA_PROTECTED
case|:
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"prot_depends"
argument_list|,
name|m
operator|->
name|type
operator|.
name|prim
operator|->
name|module
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|output_member (PRoot * out,Member * m)
name|void
name|output_member
parameter_list|(
name|PRoot
modifier|*
name|out
parameter_list|,
name|Member
modifier|*
name|m
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
name|output_method
argument_list|(
name|out
argument_list|,
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
name|output_data_member
argument_list|(
name|out
argument_list|,
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
DECL|function|output_member_cb (gpointer a,gpointer b)
name|void
name|output_member_cb
parameter_list|(
name|gpointer
name|a
parameter_list|,
name|gpointer
name|b
parameter_list|)
block|{
name|output_member
argument_list|(
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_class_macros (PRoot * out,ObjectDef * o)
name|void
name|output_class_macros
parameter_list|(
name|PRoot
modifier|*
name|out
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
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"type"
argument_list|,
name|p_fmt
argument_list|(
literal|"#define ~(o) GTK_CHECK_TYPE(o, ~)\n"
literal|"#define ~(o) GTK_CHECK_CAST(o, ~, ~)\n"
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
literal|"is"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
literal|"type"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
literal|"type"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|p_primtype
argument_list|(
name|t
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|output_macro_import
argument_list|(
name|out
argument_list|,
name|t
argument_list|,
literal|"is"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|output_macro_import
argument_list|(
name|out
argument_list|,
name|t
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_object_type_init (PRoot * out,ObjectDef * o)
name|void
name|output_object_type_init
parameter_list|(
name|PRoot
modifier|*
name|out
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
name|PNode
modifier|*
name|type_var
init|=
name|p_internal_varname
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"type"
argument_list|)
argument_list|)
decl_stmt|;
name|output_func
argument_list|(
name|out
argument_list|,
literal|"type"
argument_list|,
name|NULL
argument_list|,
name|p_internal_varname
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"init_type"
argument_list|)
argument_list|)
argument_list|,
name|p_nil
argument_list|,
name|NULL
argument_list|,
name|p_fmt
argument_list|(
literal|"\tstatic GtkTypeInfo info = {\n"
literal|"\t\t\"~\",\n"
literal|"\t\tsizeof (~),\n"
literal|"\t\tsizeof (~),\n"
literal|"\t\t(GtkClassInitFunc) ~,\n"
literal|"\t\t(GtkObjectInitFunc) ~,\n"
literal|"\t\tNULL,\n"
literal|"\t\tNULL,\n"
literal|"\t\tNULL,\n"
literal|"\t};\n"
literal|"\tif (!~)\n"
literal|"\t\t~ = gtk_type_unique (~,&info);\n"
argument_list|,
name|p_primtype
argument_list|(
name|t
argument_list|)
argument_list|,
name|p_primtype
argument_list|(
name|t
argument_list|)
argument_list|,
name|p_class_name
argument_list|(
name|t
argument_list|)
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"class_init"
argument_list|)
argument_list|)
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"init"
argument_list|)
argument_list|)
argument_list|,
name|type_var
argument_list|,
name|type_var
argument_list|,
name|p_macro_name
argument_list|(
name|o
operator|->
name|parent
argument_list|,
literal|"type"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|type_var
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_object_init (PRoot * out,ObjectDef * o)
name|void
name|output_object_init
parameter_list|(
name|PRoot
modifier|*
name|out
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
name|output_func
argument_list|(
name|out
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"init"
argument_list|)
argument_list|)
argument_list|,
name|p_fmt
argument_list|(
literal|"~ ~"
argument_list|,
name|p_type
argument_list|(
operator|&
name|o
operator|->
name|self_type
index|[
name|FALSE
index|]
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|p_fmt
argument_list|(
literal|"\t(void) ~;\n"
literal|"#ifdef ~_INIT\n"
literal|"\t~_INIT (~);\n"
literal|"#endif\n"
argument_list|,
name|p_c_ident
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|p_c_macro
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|p_c_macro
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_class_init (PRoot * out,ObjectDef * o)
name|void
name|output_class_init
parameter_list|(
name|PRoot
modifier|*
name|out
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
name|output_func
argument_list|(
name|out
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|p_varname
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"class_init"
argument_list|)
argument_list|)
argument_list|,
name|p_fmt
argument_list|(
literal|"~* klass"
argument_list|,
name|p_class_name
argument_list|(
name|t
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|p_fmt
argument_list|(
literal|"\tGtkObjectClass* obklass = "
literal|"(GtkObjectClass*) klass;\n"
literal|"~"
literal|"\t(void) obklass;\n"
literal|"~"
literal|"#ifdef ~_CLASS_INIT\n"
literal|"\t~_CLASS_INIT (klass);\n"
literal|"#endif\n"
argument_list|,
name|p_col
argument_list|(
literal|"class_init_head"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"member_class_init"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|p_c_macro
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|p_c_macro
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_object (PRoot * out,Def * d)
name|void
name|output_object
parameter_list|(
name|PRoot
modifier|*
name|out
parameter_list|,
name|Def
modifier|*
name|d
parameter_list|)
block|{
name|ObjectDef
modifier|*
name|o
init|=
operator|(
name|ObjectDef
operator|*
operator|)
name|d
decl_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"func_depends"
argument_list|,
name|d
operator|->
name|type
operator|->
name|module
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"func_parent_depends"
argument_list|,
name|o
operator|->
name|parent
operator|->
name|module
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"prot_parent_depends"
argument_list|,
name|o
operator|->
name|parent
operator|->
name|module
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"source_prot_depends"
argument_list|,
name|d
operator|->
name|type
operator|->
name|module
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"import_depends"
argument_list|,
name|o
operator|->
name|parent
operator|->
name|module
argument_list|)
expr_stmt|;
name|output_object_type_init
argument_list|(
name|out
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|output_class_init
argument_list|(
name|out
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|output_object_init
argument_list|(
name|out
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"protected"
argument_list|,
name|p_class_decl
argument_list|(
name|o
argument_list|)
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"protected"
argument_list|,
name|p_class_body
argument_list|(
name|o
argument_list|)
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"type"
argument_list|,
name|p_object_decl
argument_list|(
name|o
argument_list|)
argument_list|)
expr_stmt|;
name|output_class_macros
argument_list|(
name|out
argument_list|,
name|o
argument_list|)
expr_stmt|;
name|pr_put
argument_list|(
name|out
argument_list|,
literal|"protected"
argument_list|,
name|p_object_body
argument_list|(
name|o
argument_list|)
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
name|o
operator|->
name|members
argument_list|,
name|output_member_cb
argument_list|,
name|out
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

