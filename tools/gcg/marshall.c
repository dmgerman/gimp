begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"gcg.h"
end_include

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

begin_typedef
DECL|enum|__anon2b7794fc0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|MARSHALL_INT
name|MARSHALL_INT
block|,
DECL|enumerator|MARSHALL_DOUBLE
name|MARSHALL_DOUBLE
block|,
DECL|enumerator|MARSHALL_POINTER
name|MARSHALL_POINTER
block|,
DECL|enumerator|MARSHALL_VOID
name|MARSHALL_VOID
block|,
DECL|enumerator|MARSHALL_LONG
name|MARSHALL_LONG
DECL|typedef|MarshallType
block|}
name|MarshallType
typedef|;
end_typedef

begin_struct
DECL|struct|_SignalType
struct|struct
name|_SignalType
block|{
DECL|member|package
name|Id
name|package
decl_stmt|;
DECL|member|rettype
name|MarshallType
name|rettype
decl_stmt|;
DECL|member|argtypes
name|GSList
modifier|*
name|argtypes
decl_stmt|;
block|}
struct|;
end_struct

begin_function
DECL|function|marshalling_type (Type * t)
name|MarshallType
name|marshalling_type
parameter_list|(
name|Type
modifier|*
name|t
parameter_list|)
block|{
if|if
condition|(
operator|!
name|t
condition|)
return|return
name|MARSHALL_VOID
return|;
if|if
condition|(
name|t
operator|->
name|indirection
condition|)
return|return
name|MARSHALL_POINTER
return|;
if|if
condition|(
operator|!
name|t
operator|->
name|prim
condition|)
return|return
name|MARSHALL_VOID
return|;
switch|switch
condition|(
name|t
operator|->
name|prim
operator|->
name|kind
condition|)
block|{
case|case
name|TYPE_INT
case|:
case|case
name|TYPE_FLAGS
case|:
case|case
name|TYPE_ENUM
case|:
return|return
name|MARSHALL_INT
return|;
case|case
name|TYPE_LONG
case|:
return|return
name|MARSHALL_LONG
return|;
case|case
name|TYPE_DOUBLE
case|:
return|return
name|MARSHALL_DOUBLE
return|;
case|case
name|TYPE_NONE
case|:
return|return
name|MARSHALL_VOID
return|;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
return|return
name|MARSHALL_VOID
return|;
block|}
block|}
end_function

begin_function
DECL|function|sig_type (Method * m)
name|SignalType
modifier|*
name|sig_type
parameter_list|(
name|Method
modifier|*
name|m
parameter_list|)
block|{
name|SignalType
modifier|*
name|t
init|=
name|g_new
argument_list|(
name|SignalType
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GSList
modifier|*
name|p
init|=
name|m
operator|->
name|params
decl_stmt|,
modifier|*
name|a
init|=
name|NULL
decl_stmt|;
name|t
operator|->
name|package
operator|=
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
operator|->
name|module
operator|->
name|package
operator|->
name|name
expr_stmt|;
name|t
operator|->
name|rettype
operator|=
name|marshalling_type
argument_list|(
operator|&
name|m
operator|->
name|ret_type
argument_list|)
expr_stmt|;
while|while
condition|(
name|p
condition|)
block|{
name|Param
modifier|*
name|param
init|=
name|p
operator|->
name|data
decl_stmt|;
name|MarshallType
modifier|*
name|t
init|=
name|g_new
argument_list|(
name|MarshallType
argument_list|,
literal|1
argument_list|)
decl_stmt|;
operator|*
name|t
operator|=
name|marshalling_type
argument_list|(
operator|&
name|param
operator|->
name|type
argument_list|)
expr_stmt|;
name|a
operator|=
name|g_slist_prepend
argument_list|(
name|a
argument_list|,
name|t
argument_list|)
expr_stmt|;
name|p
operator|=
name|p
operator|->
name|next
expr_stmt|;
block|}
name|a
operator|=
name|g_slist_reverse
argument_list|(
name|a
argument_list|)
expr_stmt|;
name|t
operator|->
name|argtypes
operator|=
name|a
expr_stmt|;
return|return
name|t
return|;
block|}
end_function

begin_function
DECL|function|sig_type_free (SignalType * t)
name|void
name|sig_type_free
parameter_list|(
name|SignalType
modifier|*
name|t
parameter_list|)
block|{
name|GSList
modifier|*
name|l
init|=
name|t
operator|->
name|argtypes
decl_stmt|;
while|while
condition|(
name|l
condition|)
block|{
name|g_free
argument_list|(
name|l
operator|->
name|data
argument_list|)
expr_stmt|;
name|l
operator|=
name|l
operator|->
name|next
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|t
operator|->
name|argtypes
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|t
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|p_gtype_name (MarshallType t,gboolean abbr)
name|PNode
modifier|*
name|p_gtype_name
parameter_list|(
name|MarshallType
name|t
parameter_list|,
name|gboolean
name|abbr
parameter_list|)
block|{
DECL|struct|GTypeName
specifier|static
specifier|const
struct|struct
name|GTypeName
block|{
DECL|member|type
name|MarshallType
name|type
decl_stmt|;
DECL|member|name
name|Id
name|name
decl_stmt|;
DECL|member|aname
name|Id
name|aname
decl_stmt|;
block|}
name|names
index|[]
init|=
block|{
block|{
name|MARSHALL_POINTER
block|,
literal|"POINTER"
block|,
literal|"P"
block|}
block|,
block|{
name|MARSHALL_INT
block|,
literal|"INT"
block|,
literal|"I"
block|}
block|,
block|{
name|MARSHALL_DOUBLE
block|,
literal|"DOUBLE"
block|,
literal|"D"
block|}
block|,
block|{
name|MARSHALL_LONG
block|,
literal|"LONG"
block|,
literal|"L"
block|}
block|,
block|{
name|MARSHALL_VOID
block|,
literal|"NONE"
block|,
literal|"0"
block|}
block|, 	}
struct|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
call|(
name|gint
call|)
argument_list|(
sizeof|sizeof
argument_list|(
name|names
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|names
index|[
literal|0
index|]
argument_list|)
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|names
index|[
name|i
index|]
operator|.
name|type
operator|==
name|t
condition|)
return|return
name|p_str
argument_list|(
name|abbr
condition|?
name|names
index|[
name|i
index|]
operator|.
name|aname
else|:
name|names
index|[
name|i
index|]
operator|.
name|name
argument_list|)
return|;
name|g_assert_not_reached
argument_list|()
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|p_gtabbr (gpointer p)
name|PNode
modifier|*
name|p_gtabbr
parameter_list|(
name|gpointer
name|p
parameter_list|)
block|{
name|MarshallType
modifier|*
name|t
init|=
name|p
decl_stmt|;
return|return
name|p_gtype_name
argument_list|(
operator|*
name|t
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_gtktype (Type * t)
name|PNode
modifier|*
name|p_gtktype
parameter_list|(
name|Type
modifier|*
name|t
parameter_list|)
block|{
if|if
condition|(
name|t
operator|->
name|indirection
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|t
operator|->
name|prim
condition|)
return|return
name|p_str
argument_list|(
literal|"GTK_TYPE_NONE"
argument_list|)
return|;
switch|switch
condition|(
name|t
operator|->
name|prim
operator|->
name|kind
condition|)
block|{
case|case
name|TYPE_INT
case|:
return|return
name|p_str
argument_list|(
literal|"GTK_TYPE_INT"
argument_list|)
return|;
case|case
name|TYPE_DOUBLE
case|:
return|return
name|p_str
argument_list|(
literal|"GTK_TYPE_DOUBLE"
argument_list|)
return|;
case|case
name|TYPE_ENUM
case|:
case|case
name|TYPE_FLAGS
case|:
return|return
name|p_macro_name
argument_list|(
name|t
operator|->
name|prim
argument_list|,
literal|"TYPE"
argument_list|,
name|NULL
argument_list|)
return|;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
return|return
name|p_str
argument_list|(
literal|"GTK_TYPE_NONE"
argument_list|)
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|t
operator|->
name|indirection
operator|==
literal|1
operator|&&
name|t
operator|->
name|prim
operator|&&
operator|(
name|t
operator|->
name|prim
operator|->
name|kind
operator|==
name|TYPE_FOREIGN
operator|||
name|t
operator|->
name|prim
operator|->
name|kind
operator|==
name|TYPE_OBJECT
operator|)
condition|)
return|return
name|p_macro_name
argument_list|(
name|t
operator|->
name|prim
argument_list|,
literal|"TYPE"
argument_list|,
name|NULL
argument_list|)
return|;
else|else
return|return
name|p_str
argument_list|(
literal|"GTK_TYPE_POINTER"
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_signal_func_name (SignalType * t,PNode * basename)
name|PNode
modifier|*
name|p_signal_func_name
parameter_list|(
name|SignalType
modifier|*
name|t
parameter_list|,
name|PNode
modifier|*
name|basename
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"_~_~_~_~"
argument_list|,
name|p_c_ident
argument_list|(
name|t
operator|->
name|package
argument_list|)
argument_list|,
name|basename
argument_list|,
name|p_gtype_name
argument_list|(
name|t
operator|->
name|rettype
argument_list|,
name|TRUE
argument_list|)
argument_list|,
name|p_for
argument_list|(
name|t
operator|->
name|argtypes
argument_list|,
name|p_gtabbr
argument_list|,
name|p_nil
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_signal_marshaller_name (SignalType * t)
name|PNode
modifier|*
name|p_signal_marshaller_name
parameter_list|(
name|SignalType
modifier|*
name|t
parameter_list|)
block|{
return|return
name|p_signal_func_name
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"marshall"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_signal_demarshaller_name (SignalType * t)
name|PNode
modifier|*
name|p_signal_demarshaller_name
parameter_list|(
name|SignalType
modifier|*
name|t
parameter_list|)
block|{
return|return
name|p_signal_func_name
argument_list|(
name|t
argument_list|,
name|p_str
argument_list|(
literal|"demarshall"
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_handler_type (SignalType * t)
name|PNode
modifier|*
name|p_handler_type
parameter_list|(
name|SignalType
modifier|*
name|t
parameter_list|)
block|{
return|return
name|p_fmt
argument_list|(
literal|"_~Handler_~_~"
argument_list|,
name|p_str
argument_list|(
name|t
operator|->
name|package
argument_list|)
argument_list|,
name|p_gtype_name
argument_list|(
name|t
operator|->
name|rettype
argument_list|,
name|TRUE
argument_list|)
argument_list|,
name|p_for
argument_list|(
name|t
operator|->
name|argtypes
argument_list|,
name|p_gtabbr
argument_list|,
name|p_nil
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_signal_id (Method * s)
name|PNode
modifier|*
name|p_signal_id
parameter_list|(
name|Method
modifier|*
name|s
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
name|s
argument_list|)
operator|->
name|my_class
argument_list|)
operator|->
name|type
decl_stmt|;
return|return
name|p_fmt
argument_list|(
literal|"_~_~_signal_~"
argument_list|,
name|p_c_ident
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
name|p_c_ident
argument_list|(
name|t
operator|->
name|name
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|MEMBER
argument_list|(
name|s
argument_list|)
operator|->
name|name
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_typedef
DECL|struct|__anon2b7794fc0208
typedef|typedef
struct|struct
block|{
DECL|member|args
name|PNode
modifier|*
name|args
decl_stmt|;
DECL|member|idx
name|gint
name|idx
decl_stmt|;
DECL|typedef|ArgMarshData
block|}
name|ArgMarshData
typedef|;
end_typedef

begin_function
DECL|function|p_arg_marsh (gpointer p,gpointer d)
name|PNode
modifier|*
name|p_arg_marsh
parameter_list|(
name|gpointer
name|p
parameter_list|,
name|gpointer
name|d
parameter_list|)
block|{
name|Param
modifier|*
name|par
init|=
name|p
decl_stmt|;
name|gint
modifier|*
name|idx
init|=
name|d
decl_stmt|;
operator|(
operator|*
name|idx
operator|)
operator|++
expr_stmt|;
return|return
name|p_fmt
argument_list|(
comment|/* "\targs[~].type=~;\n" unnecessary... */
literal|"\tGTK_VALUE_~(args[~]) = ~;\n"
argument_list|,
comment|/* p_prf("%d", *idx), 			p_gtktype(&par->type), */
name|p_gtype_name
argument_list|(
name|marshalling_type
argument_list|(
operator|&
name|par
operator|->
name|type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
argument_list|,
name|p_prf
argument_list|(
literal|"%d"
argument_list|,
operator|*
name|idx
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|par
operator|->
name|name
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_sig_marshalling (Method * m)
name|PNode
modifier|*
name|p_sig_marshalling
parameter_list|(
name|Method
modifier|*
name|m
parameter_list|)
block|{
name|gint
name|idx
init|=
operator|-
literal|1
decl_stmt|;
name|gboolean
name|ret
init|=
name|marshalling_type
argument_list|(
operator|&
name|m
operator|->
name|ret_type
argument_list|)
operator|!=
name|MARSHALL_VOID
decl_stmt|;
return|return
name|p_fmt
argument_list|(
literal|"\t{\n"
literal|"\tGtkArg args[~];\n"
literal|"~"
literal|"~"
literal|"~"
literal|"\tgtk_signal_emitv((GtkObject*)~, ~, args);\n"
literal|"~"
literal|"\t}\n"
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
operator|+
name|ret
argument_list|)
argument_list|,
name|ret
condition|?
name|p_fmt
argument_list|(
literal|"\t~ retval;\n"
argument_list|,
name|p_type
argument_list|(
operator|&
name|m
operator|->
name|ret_type
argument_list|)
argument_list|)
else|:
name|p_nil
argument_list|,
name|p_for
argument_list|(
name|m
operator|->
name|params
argument_list|,
name|p_arg_marsh
argument_list|,
operator|&
name|idx
argument_list|)
argument_list|,
name|ret
comment|/* cannot use retloc here, ansi forbids casted lvalues */
condition|?
name|p_fmt
argument_list|(
literal|"\tGTK_VALUE_POINTER(args[~]) =&retval;\n"
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
argument_list|)
else|:
name|p_nil
argument_list|,
name|p_c_ident
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
operator|->
name|name
argument_list|)
argument_list|,
name|p_signal_id
argument_list|(
name|m
argument_list|)
argument_list|,
name|ret
condition|?
name|p_str
argument_list|(
literal|"\treturn retval;\n"
argument_list|)
else|:
name|p_nil
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_arg_demarsh (gpointer p,gpointer d)
name|PNode
modifier|*
name|p_arg_demarsh
parameter_list|(
name|gpointer
name|p
parameter_list|,
name|gpointer
name|d
parameter_list|)
block|{
name|MarshallType
modifier|*
name|t
init|=
name|p
decl_stmt|;
name|ArgMarshData
modifier|*
name|data
init|=
name|d
decl_stmt|;
return|return
name|p_fmt
argument_list|(
literal|"\t\tGTK_VALUE_~(~[~]),\n"
argument_list|,
name|p_gtype_name
argument_list|(
operator|*
name|t
argument_list|,
name|FALSE
argument_list|)
argument_list|,
name|data
operator|->
name|args
argument_list|,
name|p_fmt
argument_list|(
literal|"%d"
argument_list|,
name|data
operator|->
name|idx
operator|++
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|p_demarshaller (SignalType * t)
name|PNode
modifier|*
name|p_demarshaller
parameter_list|(
name|SignalType
modifier|*
name|t
parameter_list|)
block|{
name|gint
name|idx
init|=
literal|0
decl_stmt|;
return|return
name|p_fmt
argument_list|(
literal|"~~"
argument_list|,
operator|(
name|t
operator|->
name|rettype
operator|==
name|TYPE_NONE
operator|)
condition|?
name|p_fmt
argument_list|(
literal|"\t*(GTK_RETLOC_~(args[~])) =\n"
argument_list|,
name|p_gtype_name
argument_list|(
name|t
operator|->
name|rettype
argument_list|,
name|FALSE
argument_list|)
argument_list|,
name|p_prf
argument_list|(
literal|"%d"
argument_list|,
name|g_slist_length
argument_list|(
name|t
operator|->
name|argtypes
argument_list|)
argument_list|)
argument_list|)
else|:
name|p_nil
argument_list|,
name|p_fmt
argument_list|(
literal|"\t~(object,\n"
literal|"~"
literal|"\tuser_data);\n"
argument_list|,
name|p_cast
argument_list|(
name|p_handler_type
argument_list|(
name|t
argument_list|)
argument_list|,
name|p_str
argument_list|(
literal|"func"
argument_list|)
argument_list|)
argument_list|,
name|p_for
argument_list|(
name|t
operator|->
name|argtypes
argument_list|,
name|p_arg_demarsh
argument_list|,
operator|&
name|idx
argument_list|)
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

