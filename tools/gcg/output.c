begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"output.h"
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_function
DECL|function|p_c_ident (Id id)
name|PNode
modifier|*
name|p_c_ident
parameter_list|(
name|Id
name|id
parameter_list|)
block|{
name|PNode
modifier|*
name|n
decl_stmt|;
name|gchar
modifier|*
name|c
decl_stmt|;
name|gchar
modifier|*
name|s
decl_stmt|;
name|c
operator|=
name|s
operator|=
name|g_strdup
argument_list|(
name|id
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|c
condition|)
block|{
operator|*
name|c
operator|=
name|tolower
argument_list|(
operator|*
name|c
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|isalnum
argument_list|(
operator|*
name|c
argument_list|)
condition|)
operator|*
name|c
operator|=
literal|'_'
expr_stmt|;
name|c
operator|++
expr_stmt|;
block|}
name|n
operator|=
name|p_str
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|s
argument_list|)
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_function
DECL|function|p_c_macro (Id id)
name|PNode
modifier|*
name|p_c_macro
parameter_list|(
name|Id
name|id
parameter_list|)
block|{
name|PNode
modifier|*
name|n
decl_stmt|;
name|gchar
modifier|*
name|c
decl_stmt|;
name|gchar
modifier|*
name|s
decl_stmt|;
name|c
operator|=
name|s
operator|=
name|g_strdup
argument_list|(
name|id
argument_list|)
expr_stmt|;
while|while
condition|(
operator|*
name|c
condition|)
block|{
operator|*
name|c
operator|=
name|toupper
argument_list|(
operator|*
name|c
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|isalnum
argument_list|(
operator|*
name|c
argument_list|)
condition|)
operator|*
name|c
operator|=
literal|'_'
expr_stmt|;
name|c
operator|++
expr_stmt|;
block|}
name|n
operator|=
name|p_str
argument_list|(
name|s
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|s
argument_list|)
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_function
DECL|function|p_param (FunParams * p,ParamOptions * opt)
name|PNode
modifier|*
name|p_param
parameter_list|(
name|FunParams
modifier|*
name|p
parameter_list|,
name|ParamOptions
modifier|*
name|opt
parameter_list|)
block|{
return|return
name|p_lst
argument_list|(
name|opt
operator|->
name|first
condition|?
name|p_nil
else|:
name|p_str
argument_list|(
literal|", "
argument_list|)
argument_list|,
name|opt
operator|->
name|types
condition|?
name|p_type
argument_list|(
operator|&
name|p
operator|->
name|type
argument_list|)
else|:
name|p_nil
argument_list|,
name|opt
operator|->
name|types
operator|&&
name|opt
operator|->
name|names
condition|?
name|p_str
argument_list|(
literal|" "
argument_list|)
else|:
name|p_nil
argument_list|,
name|opt
operator|->
name|names
condition|?
name|p
operator|->
name|name
else|:
name|p_nil
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_params (FunParams * args,ParamOptions * opt)
name|PNode
modifier|*
name|p_params
parameter_list|(
name|FunParams
modifier|*
name|args
parameter_list|,
name|ParamOptions
modifier|*
name|opt
parameter_list|)
block|{
name|ParamOptions
name|o
init|=
operator|*
name|opt
decl_stmt|;
name|PNode
modifier|*
name|n
init|=
name|p_nil
decl_stmt|;
while|while
condition|(
name|args
condition|)
block|{
name|n
operator|=
name|p_lst
argument_list|(
name|n
argument_list|,
name|p_param
argument_list|(
name|args
argument_list|,
operator|&
name|o
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|args
operator|=
name|args
operator|->
name|next
expr_stmt|;
name|o
operator|.
name|first
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|n
operator|==
name|p_nil
condition|)
if|if
condition|(
name|opt
operator|->
name|first
condition|)
return|return
name|p_str
argument_list|(
literal|"void"
argument_list|)
return|;
else|else
return|return
name|p_nil
return|;
else|else
return|return
name|n
return|;
block|}
end_function

begin_function
DECL|function|p_primtype (PrimType * t)
name|PNode
modifier|*
name|p_primtype
parameter_list|(
name|PrimType
modifier|*
name|t
parameter_list|)
block|{
return|return
name|p_lst
argument_list|(
name|p_str
argument_list|(
name|t
operator|->
name|module
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
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_cast (PNode * force_type,PNode * expression)
name|PNode
modifier|*
name|p_cast
parameter_list|(
name|PNode
modifier|*
name|force_type
parameter_list|,
name|PNode
modifier|*
name|expression
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"((~)~)"
argument_list|,
name|force_type
argument_list|,
name|expression
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_type (Type * t)
name|PNode
modifier|*
name|p_type
parameter_list|(
name|Type
modifier|*
name|t
parameter_list|)
block|{
if|if
condition|(
name|t
operator|&&
name|t
operator|->
name|prim
condition|)
block|{
name|PNode
modifier|*
name|node
decl_stmt|;
name|gint
name|i
init|=
name|t
operator|->
name|indirection
decl_stmt|;
name|node
operator|=
name|p_fmt
argument_list|(
literal|"~~"
argument_list|,
name|t
operator|->
name|is_const
condition|?
name|p_str
argument_list|(
literal|"const "
argument_list|)
else|:
name|p_nil
argument_list|,
name|p_primtype
argument_list|(
name|t
operator|->
name|prim
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|i
operator|--
condition|)
name|node
operator|=
name|p_lst
argument_list|(
name|node
argument_list|,
name|p_str
argument_list|(
literal|"*"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* file_add_dep(s, t->prim->decl_header);*/
return|return
name|node
return|;
block|}
else|else
return|return
name|p_str
argument_list|(
literal|"void"
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_self_type (ObjectDef * o,PBool const_self)
name|PNode
modifier|*
name|p_self_type
parameter_list|(
name|ObjectDef
modifier|*
name|o
parameter_list|,
name|PBool
name|const_self
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"~~*"
argument_list|,
operator|(
name|const_self
condition|?
name|p_str
argument_list|(
literal|"const "
argument_list|)
else|:
name|p_nil
operator|)
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
DECL|function|p_varname (PrimType * t,PNode * name)
name|PNode
modifier|*
name|p_varname
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
literal|"~_~_~"
argument_list|,
name|p_c_ident
argument_list|(
name|t
operator|->
name|module
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
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_internal_varname (PrimType * t,PNode * name)
name|PNode
modifier|*
name|p_internal_varname
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
literal|"_~"
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
DECL|function|p_type_guard (Type * t,PNode * var)
name|PNode
modifier|*
name|p_type_guard
parameter_list|(
name|Type
modifier|*
name|t
parameter_list|,
name|PNode
modifier|*
name|var
parameter_list|)
block|{
name|PrimType
modifier|*
name|p
init|=
name|t
operator|->
name|prim
decl_stmt|;
comment|/* 	if(t->notnull&& (p->indirection>1 || p->kind!=GTK_TYPE_OBJECT)) 		return p_fmt("\tg_assert (~);\n", var); 	else if(p->kind==GTK_TYPE_OBJECT) 		return p_fmt("\tg_assert (~ 	 		kind != 	*/
return|return
name|p_lst
argument_list|(
operator|(
name|t
operator|->
name|indirection
operator|&&
name|t
operator|->
name|notnull
condition|?
name|p_fmt
argument_list|(
literal|"\tg_assert (~);\n"
argument_list|,
name|var
argument_list|)
else|:
name|p_nil
operator|)
argument_list|,
operator|(
operator|(
name|t
operator|->
name|indirection
operator|==
literal|1
operator|&&
name|p
operator|->
name|kind
operator|==
name|GTK_TYPE_OBJECT
operator|)
condition|?
operator|(
name|t
operator|->
name|notnull
condition|?
name|p_fmt
argument_list|(
literal|"\tg_assert (~(~));\n"
argument_list|,
name|p_macro_name
argument_list|(
name|p
argument_list|,
literal|"IS"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|var
argument_list|)
else|:
name|p_fmt
argument_list|(
literal|"\tg_assert (!~ || ~(~));\n"
argument_list|,
name|var
argument_list|,
name|p_macro_name
argument_list|(
name|p
argument_list|,
literal|"IS"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|var
argument_list|)
operator|)
else|:
operator|(
name|t
operator|->
name|indirection
operator|==
literal|0
condition|?
operator|(
operator|(
name|p
operator|->
name|kind
operator|==
name|GTK_TYPE_ENUM
operator|)
condition|?
name|p_fmt
argument_list|(
literal|"\tg_assert (~<= ~);\n"
argument_list|,
name|var
argument_list|,
name|p_macro_name
argument_list|(
name|p
argument_list|,
name|NULL
argument_list|,
literal|"LAST"
argument_list|)
argument_list|)
else|:
operator|(
operator|(
name|p
operator|->
name|kind
operator|==
name|GTK_TYPE_FLAGS
operator|)
condition|?
name|p_fmt
argument_list|(
literal|"\tg_assert ((~<< 1)< ~);\n"
argument_list|,
name|var
argument_list|,
name|p_macro_name
argument_list|(
name|p
argument_list|,
name|NULL
argument_list|,
literal|"LAST"
argument_list|)
argument_list|)
else|:
name|p_nil
operator|)
operator|)
else|:
name|p_nil
operator|)
operator|)
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_type_guards (FunParams * args)
name|PNode
modifier|*
name|p_type_guards
parameter_list|(
name|FunParams
modifier|*
name|args
parameter_list|)
block|{
name|PNode
modifier|*
name|p
init|=
name|p_nil
decl_stmt|;
while|while
condition|(
name|args
condition|)
block|{
name|p
operator|=
name|p_lst
argument_list|(
name|p
argument_list|,
name|p_type_guard
argument_list|(
operator|&
name|args
operator|->
name|type
argument_list|,
name|args
operator|->
name|name
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|args
operator|=
name|args
operator|->
name|next
expr_stmt|;
block|}
return|return
name|p
return|;
block|}
end_function

begin_function
DECL|function|p_prototype (Type * rettype,PNode * name,PNode * args1,FunParams * args2)
name|PNode
modifier|*
name|p_prototype
parameter_list|(
name|Type
modifier|*
name|rettype
parameter_list|,
name|PNode
modifier|*
name|name
parameter_list|,
name|PNode
modifier|*
name|args1
parameter_list|,
name|FunParams
modifier|*
name|args2
parameter_list|)
block|{
name|ParamOptions
name|o
init|=
block|{
operator|(
operator|!
name|args1
operator|||
name|args1
operator|==
name|p_nil
operator|)
block|,
name|TRUE
block|,
name|TRUE
block|}
decl_stmt|;
return|return
name|p_fmt
argument_list|(
literal|"~ ~ (~~)"
argument_list|,
name|p_type
argument_list|(
name|rettype
argument_list|)
argument_list|,
name|name
argument_list|,
name|args1
argument_list|,
name|p_params
argument_list|(
name|args2
argument_list|,
operator|&
name|o
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|output_func (PRoot * out,Id tag,Type * rettype,PNode * name,PNode * args1,FunParams * args2,PNode * body)
name|void
name|output_func
parameter_list|(
name|PRoot
modifier|*
name|out
parameter_list|,
name|Id
name|tag
parameter_list|,
name|Type
modifier|*
name|rettype
parameter_list|,
name|PNode
modifier|*
name|name
parameter_list|,
name|PNode
modifier|*
name|args1
parameter_list|,
name|FunParams
modifier|*
name|args2
parameter_list|,
name|PNode
modifier|*
name|body
parameter_list|)
block|{
name|pr_add
argument_list|(
name|out
argument_list|,
name|tag
condition|?
name|tag
else|:
literal|"source_head"
argument_list|,
name|p_fmt
argument_list|(
literal|"~~;\n"
argument_list|,
name|tag
condition|?
name|p_nil
else|:
name|p_str
argument_list|(
literal|"static "
argument_list|)
argument_list|,
name|p_prototype
argument_list|(
name|rettype
argument_list|,
name|name
argument_list|,
name|args1
argument_list|,
name|args2
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|pr_add
argument_list|(
name|out
argument_list|,
literal|"source"
argument_list|,
name|p_fmt
argument_list|(
literal|"~~{\n"
literal|"~"
literal|"~"
literal|"}\n\n"
argument_list|,
name|tag
condition|?
name|p_nil
else|:
name|p_str
argument_list|(
literal|"static "
argument_list|)
argument_list|,
name|p_prototype
argument_list|(
name|rettype
argument_list|,
name|name
argument_list|,
name|args1
argument_list|,
name|args2
argument_list|)
argument_list|,
name|p_type_guards
argument_list|(
name|args2
argument_list|)
argument_list|,
name|body
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|p_macro_name (PrimType * t,Id mid,Id post)
name|PNode
modifier|*
name|p_macro_name
parameter_list|(
name|PrimType
modifier|*
name|t
parameter_list|,
name|Id
name|mid
parameter_list|,
name|Id
name|post
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"~~_~~"
argument_list|,
name|p_c_macro
argument_list|(
name|t
operator|->
name|module
operator|->
name|name
argument_list|)
argument_list|,
name|mid
condition|?
name|p_lst
argument_list|(
name|p_str
argument_list|(
literal|"_"
argument_list|)
argument_list|,
name|p_c_macro
argument_list|(
name|mid
argument_list|)
argument_list|,
name|NULL
argument_list|)
else|:
name|p_nil
argument_list|,
name|p_c_macro
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|post
condition|?
name|p_lst
argument_list|(
name|p_str
argument_list|(
literal|"_"
argument_list|)
argument_list|,
name|p_c_macro
argument_list|(
name|post
argument_list|)
argument_list|,
name|NULL
argument_list|)
else|:
name|p_nil
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|output_var (PRoot * out,Id tag,PNode * type,PNode * name)
name|void
name|output_var
parameter_list|(
name|PRoot
modifier|*
name|out
parameter_list|,
name|Id
name|tag
parameter_list|,
name|PNode
modifier|*
name|type
parameter_list|,
name|PNode
modifier|*
name|name
parameter_list|)
block|{
if|if
condition|(
name|tag
condition|)
name|pr_add
argument_list|(
name|out
argument_list|,
name|tag
argument_list|,
name|p_fmt
argument_list|(
literal|"extern ~ ~;\n"
argument_list|,
name|type
argument_list|,
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|pr_add
argument_list|(
name|out
argument_list|,
literal|"source_head"
argument_list|,
name|p_fmt
argument_list|(
literal|"~~ ~;\n"
argument_list|,
name|tag
condition|?
name|p_nil
else|:
name|p_str
argument_list|(
literal|"static "
argument_list|)
argument_list|,
name|type
argument_list|,
name|name
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|output_def (PRoot * out,Def * d)
name|void
name|output_def
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
name|PrimType
modifier|*
name|t
init|=
name|d
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
comment|/* GTK_TYPE_FOO macro */
name|pr_add
argument_list|(
name|out
argument_list|,
literal|"type"
argument_list|,
name|p_str
argument_list|(
literal|"\n\n"
argument_list|)
argument_list|)
expr_stmt|;
name|pr_add
argument_list|(
name|out
argument_list|,
literal|"source"
argument_list|,
name|p_str
argument_list|(
literal|"\n"
argument_list|)
argument_list|)
expr_stmt|;
name|pr_add
argument_list|(
name|out
argument_list|,
literal|"protected"
argument_list|,
name|p_str
argument_list|(
literal|"\n\n"
argument_list|)
argument_list|)
expr_stmt|;
name|pr_add
argument_list|(
name|out
argument_list|,
literal|"source_head"
argument_list|,
name|p_str
argument_list|(
literal|"\n"
argument_list|)
argument_list|)
expr_stmt|;
name|pr_add
argument_list|(
name|out
argument_list|,
literal|"type"
argument_list|,
name|p_fmt
argument_list|(
literal|"#define ~ \\\n"
literal|" (~ ? ~ : ~())\n"
argument_list|,
name|p_macro_name
argument_list|(
name|t
argument_list|,
literal|"TYPE"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|type_var
argument_list|,
name|type_var
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
argument_list|)
argument_list|)
expr_stmt|;
name|output_var
argument_list|(
name|out
argument_list|,
literal|"type"
argument_list|,
name|p_str
argument_list|(
literal|"GtkType"
argument_list|)
argument_list|,
name|type_var
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|d
operator|->
name|type
operator|->
name|kind
condition|)
block|{
case|case
name|GTK_TYPE_OBJECT
case|:
name|output_object
argument_list|(
name|out
argument_list|,
name|d
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_TYPE_ENUM
case|:
name|output_enum
argument_list|(
name|out
argument_list|,
name|d
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_TYPE_FLAGS
case|:
name|output_flags
argument_list|(
name|out
argument_list|,
name|d
argument_list|)
expr_stmt|;
break|break;
default|default:
empty_stmt|;
block|}
block|}
end_function

end_unit

