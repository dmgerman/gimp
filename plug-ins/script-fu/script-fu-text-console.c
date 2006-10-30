begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_if
if|#
directive|if
name|HAVE_UNISTD_H
end_if

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"scheme-wrapper.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-text-console.h"
end_include

begin_include
include|#
directive|include
file|"script-fu-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|script_fu_text_console_interface
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|script_fu_text_console_run (const gchar * name,gint nparams,const GimpParam * params,gint * nreturn_vals,GimpParam ** return_vals)
name|script_fu_text_console_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
comment|/*  Enable Script-Fu output  */
name|ts_set_output_file
argument_list|(
name|stdout
argument_list|)
expr_stmt|;
name|ts_set_verbose_level
argument_list|(
literal|2
argument_list|)
expr_stmt|;
name|ts_print_welcome
argument_list|()
expr_stmt|;
comment|/*  Run the interface  */
name|script_fu_text_console_interface
argument_list|()
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|read_command (GString * command)
name|read_command
parameter_list|(
name|GString
modifier|*
name|command
parameter_list|)
block|{
name|gint
name|next
decl_stmt|;
name|gint
name|level
init|=
literal|0
decl_stmt|;
name|g_string_truncate
argument_list|(
name|command
argument_list|,
literal|0
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|next
operator|=
name|fgetc
argument_list|(
name|stdin
argument_list|)
operator|)
operator|!=
name|EOF
condition|)
block|{
name|guchar
name|c
init|=
operator|(
name|guchar
operator|)
name|next
decl_stmt|;
switch|switch
condition|(
name|c
condition|)
block|{
case|case
literal|'\n'
case|:
if|if
condition|(
name|level
operator|==
literal|0
condition|)
return|return
name|TRUE
return|;
name|c
operator|=
literal|' '
expr_stmt|;
break|break;
case|case
literal|'('
case|:
name|level
operator|++
expr_stmt|;
break|break;
case|case
literal|')'
case|:
name|level
operator|--
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|g_string_append_c
argument_list|(
name|command
argument_list|,
name|c
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|errno
condition|)
name|g_printerr
argument_list|(
literal|"error reading from stdin: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|script_fu_text_console_interface (void)
name|script_fu_text_console_interface
parameter_list|(
name|void
parameter_list|)
block|{
name|GString
modifier|*
name|command
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
while|while
condition|(
name|read_command
argument_list|(
name|command
argument_list|)
condition|)
block|{
if|if
condition|(
name|command
operator|->
name|len
operator|>
literal|0
condition|)
name|ts_interpret_string
argument_list|(
name|command
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
name|g_string_free
argument_list|(
name|command
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

