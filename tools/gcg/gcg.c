begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|"gcg.h"
end_include

begin_include
include|#
directive|include
file|"parse.h"
end_include

begin_include
include|#
directive|include
file|<unistd.h>
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

begin_ifndef
ifndef|#
directive|ifndef
name|CPP_PROGRAM
end_ifndef

begin_define
DECL|macro|CPP_PROGRAM
define|#
directive|define
name|CPP_PROGRAM
value|"cpp"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|header_root
name|Id
name|header_root
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|source_name
name|Id
name|source_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|collect_marshall
name|gboolean
name|collect_marshall
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cpp_cmd
name|GString
modifier|*
name|cpp_cmd
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|get_options (int argc,char * argv[])
name|void
name|get_options
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|gint
name|x
init|=
literal|0
decl_stmt|;
name|yydebug
operator|=
name|yy_flex_debug
operator|=
name|FALSE
expr_stmt|;
do|do
block|{
name|x
operator|=
name|getopt
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|,
literal|"D:i:dI:o:m"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|x
condition|)
block|{
case|case
literal|'D'
case|:
name|header_root
operator|=
name|optarg
expr_stmt|;
break|break;
case|case
literal|'I'
case|:
name|g_string_append
argument_list|(
name|cpp_cmd
argument_list|,
literal|" -I "
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|cpp_cmd
argument_list|,
name|optarg
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'d'
case|:
if|if
condition|(
operator|!
name|yydebug
condition|)
name|yydebug
operator|=
name|TRUE
expr_stmt|;
else|else
name|yy_flex_debug
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
literal|'o'
case|:
name|source_name
operator|=
name|optarg
expr_stmt|;
break|break;
case|case
literal|'m'
case|:
name|collect_marshall
operator|=
name|TRUE
expr_stmt|;
case|case
literal|'?'
case|:
case|case
literal|':'
case|:
name|g_error
argument_list|(
literal|"Bad option %c!\n"
argument_list|,
name|x
argument_list|)
expr_stmt|;
block|}
block|}
do|while
condition|(
name|x
operator|!=
name|EOF
condition|)
do|;
block|}
end_function

begin_function
DECL|function|output_cb (Def * def,gpointer out)
name|void
name|output_cb
parameter_list|(
name|Def
modifier|*
name|def
parameter_list|,
name|gpointer
name|out
parameter_list|)
block|{
name|output_def
argument_list|(
name|out
argument_list|,
name|def
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|open_out (PNode * (* func)(Module *),Id suffix,PNode * n,PRoot * out)
name|void
name|open_out
parameter_list|(
name|PNode
modifier|*
function_decl|(
modifier|*
name|func
function_decl|)
parameter_list|(
name|Module
modifier|*
parameter_list|)
parameter_list|,
name|Id
name|suffix
parameter_list|,
name|PNode
modifier|*
name|n
parameter_list|,
name|PRoot
modifier|*
name|out
parameter_list|)
block|{
name|GString
modifier|*
name|s
init|=
name|g_string_new
argument_list|(
name|header_root
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|PNode
modifier|*
name|guard
decl_stmt|;
name|FILE
modifier|*
name|f
decl_stmt|;
name|g_string_append
argument_list|(
name|s
argument_list|,
literal|"/"
argument_list|)
expr_stmt|;
name|str
operator|=
name|p_to_str
argument_list|(
name|func
argument_list|(
name|current_module
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|s
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
name|f
operator|=
name|fopen
argument_list|(
name|s
operator|->
name|str
argument_list|,
literal|"w+"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|f
condition|)
name|g_error
argument_list|(
literal|"Unable to open file %s: %s"
argument_list|,
name|s
operator|->
name|str
argument_list|,
name|strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|s
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|guard
operator|=
name|p_fmt
argument_list|(
literal|"_g_~_~_~"
argument_list|,
name|p_c_ident
argument_list|(
name|current_module
operator|->
name|package
operator|->
name|name
argument_list|)
argument_list|,
name|p_c_ident
argument_list|(
name|current_module
operator|->
name|name
argument_list|)
argument_list|,
name|p_str
argument_list|(
name|suffix
argument_list|)
argument_list|)
expr_stmt|;
name|p_write
argument_list|(
name|p_fmt
argument_list|(
literal|"#ifndef ~\n"
literal|"#define ~\n"
literal|"~"
literal|"#endif /* ~ */\n"
argument_list|,
name|guard
argument_list|,
name|guard
argument_list|,
name|n
argument_list|,
name|guard
argument_list|)
argument_list|,
name|f
argument_list|,
name|out
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|main (int argc,char * argv[])
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
comment|/*	target=stdout;*/
name|PRoot
modifier|*
name|out
init|=
name|pr_new
argument_list|()
decl_stmt|;
name|FILE
modifier|*
name|f
decl_stmt|;
name|init_db
argument_list|()
expr_stmt|;
name|cpp_cmd
operator|=
name|g_string_new
argument_list|(
name|CPP_PROGRAM
argument_list|)
expr_stmt|;
name|yydebug
operator|=
literal|0
expr_stmt|;
name|get_options
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|cpp_cmd
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|cpp_cmd
argument_list|,
name|argv
index|[
name|optind
index|]
argument_list|)
expr_stmt|;
name|yyin
operator|=
name|popen
argument_list|(
name|cpp_cmd
operator|->
name|str
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
comment|/*yyin=fopen(argv[optind], "r");*/
name|g_assert
argument_list|(
name|yyin
argument_list|)
expr_stmt|;
name|yyparse
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|source_name
condition|)
name|source_name
operator|=
name|p_to_str
argument_list|(
name|p_fmt
argument_list|(
literal|"~.c"
argument_list|,
name|p_c_ident
argument_list|(
name|current_module
operator|->
name|name
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|header_root
condition|)
if|if
condition|(
operator|!
name|current_module
operator|->
name|package
operator|->
name|headerbase
operator|||
name|current_module
operator|->
name|package
operator|->
name|headerbase
index|[
literal|0
index|]
condition|)
name|header_root
operator|=
literal|".."
expr_stmt|;
else|else
name|header_root
operator|=
literal|"."
expr_stmt|;
name|foreach_def
argument_list|(
name|output_cb
argument_list|,
name|out
argument_list|)
expr_stmt|;
name|f
operator|=
name|fopen
argument_list|(
name|source_name
argument_list|,
literal|"w+"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|f
condition|)
name|g_error
argument_list|(
literal|"Unable to open file %s: %s"
argument_list|,
name|source_name
argument_list|,
name|strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|p_write
argument_list|(
name|p_fmt
argument_list|(
literal|"~~~~"
literal|"#ifdef GCG_IMPL\n"
literal|"#\tinclude GCG_IMPL\n"
literal|"#else\n"
literal|"#\tinclude \"~\"\n"
literal|"#endif\n"
literal|"~"
argument_list|,
name|p_col
argument_list|(
literal|"source_prot_depends"
argument_list|,
name|p_prot_include
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"source_head"
argument_list|,
name|NULL
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"source_sigtypes"
argument_list|,
name|p_sigdemarsh_decl
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"source_sigtypes"
argument_list|,
name|p_demarshaller
argument_list|)
argument_list|,
name|p_fmt
argument_list|(
literal|"~.i.c"
argument_list|,
name|p_c_ident
argument_list|(
name|current_module
operator|->
name|name
argument_list|)
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"source"
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|,
name|f
argument_list|,
name|out
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
name|open_out
argument_list|(
name|p_type_header
argument_list|,
literal|"type"
argument_list|,
name|p_fmt
argument_list|(
literal|"#include<gtk/gtktypeutils.h>\n"
literal|"~"
argument_list|,
name|p_col
argument_list|(
literal|"type"
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|,
name|out
argument_list|)
expr_stmt|;
name|open_out
argument_list|(
name|p_func_header
argument_list|,
literal|"funcs"
argument_list|,
name|p_fmt
argument_list|(
literal|"~~~"
argument_list|,
name|p_col
argument_list|(
literal|"func_parent_depends"
argument_list|,
name|p_func_include
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"func_depends"
argument_list|,
name|p_type_include
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"functions"
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|,
name|out
argument_list|)
expr_stmt|;
name|open_out
argument_list|(
name|p_prot_header
argument_list|,
literal|"prot"
argument_list|,
name|p_fmt
argument_list|(
literal|"~~~~"
argument_list|,
name|p_func_include
argument_list|(
name|current_module
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"prot_parent_depends"
argument_list|,
name|p_prot_include
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"prot_depends"
argument_list|,
name|p_type_include
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"protected"
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|,
name|out
argument_list|)
expr_stmt|;
name|open_out
argument_list|(
name|p_import_header
argument_list|,
literal|"import"
argument_list|,
name|p_fmt
argument_list|(
literal|"~~~"
argument_list|,
name|p_func_include
argument_list|(
name|current_module
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"import_depends"
argument_list|,
name|p_import_include
argument_list|)
argument_list|,
name|p_col
argument_list|(
literal|"import_alias"
argument_list|,
name|NULL
argument_list|)
argument_list|)
argument_list|,
name|out
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

end_unit

