begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * PlugInRc  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfigwriter.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpscanner.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-def.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-rc.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*    *  All deserialize functions return G_TOKEN_LEFT_PAREN on success,  *  or the GTokenType they would have expected but didn't get.  */
end_comment

begin_function_decl
specifier|static
name|GTokenType
name|plug_in_def_deserialize
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|plug_in_proc_def_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|plug_in_proc_arg_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|ProcArg
modifier|*
name|arg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|plug_in_locale_def_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|plug_in_help_def_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GTokenType
name|plug_in_has_init_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
function_decl|;
end_function_decl

begin_enum
enum|enum
DECL|enum|__anon2b79bc670103
block|{
DECL|enumerator|PLUG_IN_DEF
name|PLUG_IN_DEF
init|=
literal|1
block|,
DECL|enumerator|PROC_DEF
name|PROC_DEF
block|,
DECL|enumerator|LOCALE_DEF
name|LOCALE_DEF
block|,
DECL|enumerator|HELP_DEF
name|HELP_DEF
block|,
DECL|enumerator|HAS_INIT
name|HAS_INIT
block|,
DECL|enumerator|PROC_ARG
name|PROC_ARG
block|}
enum|;
end_enum

begin_function
name|gboolean
DECL|function|plug_in_rc_parse (Gimp * gimp,const gchar * filename)
name|plug_in_rc_parse
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new_file
argument_list|(
name|filename
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner
condition|)
return|return
name|TRUE
return|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"plug-in-def"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|PLUG_IN_DEF
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|PLUG_IN_DEF
argument_list|,
literal|"proc-def"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|PROC_DEF
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|PLUG_IN_DEF
argument_list|,
literal|"locale-def"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|LOCALE_DEF
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|PLUG_IN_DEF
argument_list|,
literal|"help-def"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|HELP_DEF
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|PLUG_IN_DEF
argument_list|,
literal|"has-init"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|HAS_INIT
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|PLUG_IN_DEF
argument_list|,
literal|"proc-arg"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|PROC_ARG
argument_list|)
argument_list|)
expr_stmt|;
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
if|if
condition|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
operator|==
name|GINT_TO_POINTER
argument_list|(
name|PLUG_IN_DEF
argument_list|)
condition|)
block|{
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|PLUG_IN_DEF
argument_list|)
expr_stmt|;
name|token
operator|=
name|plug_in_def_deserialize
argument_list|(
name|gimp
argument_list|,
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
break|break;
default|default:
comment|/* do nothing */
break|break;
block|}
block|}
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_scanner_unexp_token
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"fatal parse error"
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
return|return
operator|(
name|token
operator|!=
name|G_TOKEN_EOF
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|plug_in_def_deserialize (Gimp * gimp,GScanner * scanner)
name|plug_in_def_deserialize
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GScanner
modifier|*
name|scanner
parameter_list|)
block|{
name|gchar
modifier|*
name|name
decl_stmt|;
name|PlugInDef
modifier|*
name|plug_in_def
decl_stmt|;
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|name
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
name|plug_in_def
operator|=
name|plug_in_def_new
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|plug_in_def
operator|->
name|mtime
argument_list|)
condition|)
block|{
name|plug_in_def_free
argument_list|(
name|plug_in_def
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_INT
return|;
block|}
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|token
operator|=
name|g_scanner_get_next_token
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|token
condition|)
block|{
case|case
name|G_TOKEN_LEFT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_SYMBOL
expr_stmt|;
break|break;
case|case
name|G_TOKEN_SYMBOL
case|:
switch|switch
condition|(
name|GPOINTER_TO_INT
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
argument_list|)
condition|)
block|{
case|case
name|PROC_DEF
case|:
name|proc_def
operator|=
name|plug_in_proc_def_new
argument_list|()
expr_stmt|;
name|token
operator|=
name|plug_in_proc_def_deserialize
argument_list|(
name|scanner
argument_list|,
name|proc_def
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
name|plug_in_def_add_proc_def
argument_list|(
name|plug_in_def
argument_list|,
name|proc_def
argument_list|)
expr_stmt|;
else|else
name|plug_in_proc_def_free
argument_list|(
name|proc_def
argument_list|)
expr_stmt|;
break|break;
case|case
name|LOCALE_DEF
case|:
name|token
operator|=
name|plug_in_locale_def_deserialize
argument_list|(
name|scanner
argument_list|,
name|plug_in_def
argument_list|)
expr_stmt|;
break|break;
case|case
name|HELP_DEF
case|:
name|token
operator|=
name|plug_in_help_def_deserialize
argument_list|(
name|scanner
argument_list|,
name|plug_in_def
argument_list|)
expr_stmt|;
break|break;
case|case
name|HAS_INIT
case|:
name|token
operator|=
name|plug_in_has_init_deserialize
argument_list|(
name|scanner
argument_list|,
name|plug_in_def
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
break|break;
case|case
name|G_TOKEN_RIGHT_PAREN
case|:
name|token
operator|=
name|G_TOKEN_LEFT_PAREN
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
if|if
condition|(
name|token
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
if|if
condition|(
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|token
argument_list|)
condition|)
block|{
name|plug_ins_def_add_from_rc
argument_list|(
name|gimp
argument_list|,
name|plug_in_def
argument_list|)
expr_stmt|;
return|return
name|G_TOKEN_LEFT_PAREN
return|;
block|}
block|}
name|plug_in_def_free
argument_list|(
name|plug_in_def
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|plug_in_proc_def_deserialize (GScanner * scanner,PlugInProcDef * proc_def)
name|plug_in_proc_def_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
block|{
name|GTokenType
name|token
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|proc_type
argument_list|)
condition|)
return|return
name|G_TOKEN_INT
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|blurb
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|help
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|author
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|copyright
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|date
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|menu_path
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|extensions
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|prefixes
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string_no_validate
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|magics
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|image_types
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
name|proc_def
operator|->
name|image_types_val
operator|=
name|plug_ins_image_types_parse
argument_list|(
name|proc_def
operator|->
name|image_types
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|num_args
argument_list|)
condition|)
return|return
name|G_TOKEN_INT
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|num_values
argument_list|)
condition|)
return|return
name|G_TOKEN_INT
return|;
if|if
condition|(
name|proc_def
operator|->
name|db_info
operator|.
name|num_args
operator|>
literal|0
condition|)
name|proc_def
operator|->
name|db_info
operator|.
name|args
operator|=
name|g_new0
argument_list|(
name|ProcArg
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|num_args
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|proc_def
operator|->
name|db_info
operator|.
name|num_args
condition|;
name|i
operator|++
control|)
block|{
name|token
operator|=
name|plug_in_proc_arg_deserialize
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|args
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_PAREN
condition|)
return|return
name|token
return|;
block|}
if|if
condition|(
name|proc_def
operator|->
name|db_info
operator|.
name|num_values
operator|>
literal|0
condition|)
name|proc_def
operator|->
name|db_info
operator|.
name|values
operator|=
name|g_new0
argument_list|(
name|ProcArg
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|num_values
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|proc_def
operator|->
name|db_info
operator|.
name|num_values
condition|;
name|i
operator|++
control|)
block|{
name|token
operator|=
name|plug_in_proc_arg_deserialize
argument_list|(
name|scanner
argument_list|,
operator|&
name|proc_def
operator|->
name|db_info
operator|.
name|values
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_LEFT_PAREN
condition|)
return|return
name|token
return|;
block|}
if|if
condition|(
operator|!
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_RIGHT_PAREN
argument_list|)
condition|)
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
return|return
name|G_TOKEN_LEFT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|plug_in_proc_arg_deserialize (GScanner * scanner,ProcArg * arg)
name|plug_in_proc_arg_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|ProcArg
modifier|*
name|arg
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_LEFT_PAREN
argument_list|)
condition|)
return|return
name|G_TOKEN_LEFT_PAREN
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_SYMBOL
argument_list|)
operator|||
name|GPOINTER_TO_INT
argument_list|(
name|scanner
operator|->
name|value
operator|.
name|v_symbol
argument_list|)
operator|!=
name|PROC_ARG
condition|)
return|return
name|G_TOKEN_SYMBOL
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|(
name|gint
operator|*
operator|)
operator|&
name|arg
operator|->
name|arg_type
argument_list|)
condition|)
return|return
name|G_TOKEN_INT
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|arg
operator|->
name|name
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|arg
operator|->
name|description
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_RIGHT_PAREN
argument_list|)
condition|)
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
return|return
name|G_TOKEN_LEFT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|plug_in_locale_def_deserialize (GScanner * scanner,PlugInDef * plug_in_def)
name|plug_in_locale_def_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
block|{
name|gchar
modifier|*
name|string
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|string
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
name|plug_in_def_set_locale_domain_name
argument_list|(
name|plug_in_def
argument_list|,
name|string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|string
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|string
argument_list|)
condition|)
block|{
name|plug_in_def_set_locale_domain_path
argument_list|(
name|plug_in_def
argument_list|,
name|string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|string
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_RIGHT_PAREN
argument_list|)
condition|)
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
return|return
name|G_TOKEN_LEFT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|plug_in_help_def_deserialize (GScanner * scanner,PlugInDef * plug_in_def)
name|plug_in_help_def_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
block|{
name|gchar
modifier|*
name|string
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|string
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
name|plug_in_def_set_help_domain_name
argument_list|(
name|plug_in_def
argument_list|,
name|string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|string
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|string
argument_list|)
condition|)
block|{
name|plug_in_def_set_help_domain_uri
argument_list|(
name|plug_in_def
argument_list|,
name|string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|string
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_RIGHT_PAREN
argument_list|)
condition|)
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
return|return
name|G_TOKEN_LEFT_PAREN
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|plug_in_has_init_deserialize (GScanner * scanner,PlugInDef * plug_in_def)
name|plug_in_has_init_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|PlugInDef
modifier|*
name|plug_in_def
parameter_list|)
block|{
name|plug_in_def_set_has_init
argument_list|(
name|plug_in_def
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_token
argument_list|(
name|scanner
argument_list|,
name|G_TOKEN_RIGHT_PAREN
argument_list|)
condition|)
return|return
name|G_TOKEN_RIGHT_PAREN
return|;
return|return
name|G_TOKEN_LEFT_PAREN
return|;
block|}
end_function

begin_comment
comment|/* serialize functions */
end_comment

begin_function
name|gboolean
DECL|function|plug_in_rc_write (GSList * plug_in_defs,const gchar * filename,GError ** error)
name|plug_in_rc_write
parameter_list|(
name|GSList
modifier|*
name|plug_in_defs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|PlugInDef
modifier|*
name|plug_in_def
decl_stmt|;
name|PlugInProcDef
modifier|*
name|proc_def
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|list2
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_file
argument_list|(
name|filename
argument_list|,
name|FALSE
argument_list|,
literal|"GIMP plug-ins\n\n"
literal|"This file can safely be removed and "
literal|"will be automatically regenerated by "
literal|"querying the installed plugins."
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|writer
condition|)
return|return
name|FALSE
return|;
for|for
control|(
name|list
operator|=
name|plug_in_defs
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|plug_in_def
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|proc_defs
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"plug-in-def"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|plug_in_def
operator|->
name|prog
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%ld"
argument_list|,
name|plug_in_def
operator|->
name|mtime
argument_list|)
expr_stmt|;
for|for
control|(
name|list2
operator|=
name|plug_in_def
operator|->
name|proc_defs
init|;
name|list2
condition|;
name|list2
operator|=
name|list2
operator|->
name|next
control|)
block|{
name|proc_def
operator|=
name|list2
operator|->
name|data
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"proc-def"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"\"%s\" %d"
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|name
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|proc_type
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|blurb
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|help
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|author
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|copyright
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|date
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|extensions
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|prefixes
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|magics
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|image_types
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d %d"
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|num_args
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|num_values
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|proc_def
operator|->
name|db_info
operator|.
name|num_args
condition|;
name|i
operator|++
control|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"proc-arg"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|args
index|[
name|i
index|]
operator|.
name|arg_type
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|args
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|args
index|[
name|i
index|]
operator|.
name|description
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|proc_def
operator|->
name|db_info
operator|.
name|num_values
condition|;
name|i
operator|++
control|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"proc-arg"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|values
index|[
name|i
index|]
operator|.
name|arg_type
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|values
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|proc_def
operator|->
name|db_info
operator|.
name|values
index|[
name|i
index|]
operator|.
name|description
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|plug_in_def
operator|->
name|locale_domain_name
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"locale-def"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|plug_in_def
operator|->
name|locale_domain_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|locale_domain_path
condition|)
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|plug_in_def
operator|->
name|locale_domain_path
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|plug_in_def
operator|->
name|help_domain_name
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"help-def"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|plug_in_def
operator|->
name|help_domain_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|help_domain_uri
condition|)
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|plug_in_def
operator|->
name|help_domain_uri
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|plug_in_def
operator|->
name|has_init
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"has-init"
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
literal|"end of plug-ins"
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

end_unit

