begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpunit.c  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-units.h"
end_include

begin_include
include|#
directive|include
file|"gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-file.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  *  All deserialize functions return G_TOKEN_LEFT_PAREN on success,  *  or the GTokenType they would have expected but didn't get.  */
end_comment

begin_function_decl
specifier|static
name|GTokenType
name|gimp_unitrc_unit_info_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_units_init (Gimp * gimp)
name|gimp_units_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|user_units
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|n_user_units
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_units_exit (Gimp * gimp)
name|gimp_units_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_user_units_free
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  unitrc functions  **********/
end_comment

begin_enum
enum|enum
DECL|enum|__anon279db64e0103
block|{
DECL|enumerator|UNIT_INFO
name|UNIT_INFO
init|=
literal|1
block|,
DECL|enumerator|UNIT_FACTOR
name|UNIT_FACTOR
block|,
DECL|enumerator|UNIT_DIGITS
name|UNIT_DIGITS
block|,
DECL|enumerator|UNIT_SYMBOL
name|UNIT_SYMBOL
block|,
DECL|enumerator|UNIT_ABBREV
name|UNIT_ABBREV
block|,
DECL|enumerator|UNIT_SINGULAR
name|UNIT_SINGULAR
block|,
DECL|enumerator|UNIT_PLURAL
name|UNIT_PLURAL
block|}
enum|;
end_enum

begin_function
name|void
DECL|function|gimp_unitrc_load (Gimp * gimp)
name|gimp_unitrc_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"unitrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
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
operator|&&
name|error
operator|->
name|code
operator|==
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
block|{
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_sysconf_directory
argument_list|()
argument_list|,
literal|"unitrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|scanner
operator|=
name|gimp_scanner_new_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|scanner
condition|)
block|{
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"unit-info"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|UNIT_INFO
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|UNIT_INFO
argument_list|,
literal|"factor"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|UNIT_FACTOR
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|UNIT_INFO
argument_list|,
literal|"digits"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|UNIT_DIGITS
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|UNIT_INFO
argument_list|,
literal|"symbol"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|UNIT_SYMBOL
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|UNIT_INFO
argument_list|,
literal|"abbreviation"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|UNIT_ABBREV
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|UNIT_INFO
argument_list|,
literal|"singular"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|UNIT_SINGULAR
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|UNIT_INFO
argument_list|,
literal|"plural"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|UNIT_PLURAL
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
name|UNIT_INFO
argument_list|)
condition|)
block|{
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|UNIT_INFO
argument_list|)
expr_stmt|;
name|token
operator|=
name|gimp_unitrc_unit_info_deserialize
argument_list|(
name|scanner
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_RIGHT_PAREN
condition|)
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
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
argument_list|,
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
name|gimp_config_file_backup_on_error
argument_list|(
name|filename
argument_list|,
literal|"unitrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unitrc_save (Gimp * gimp)
name|gimp_unitrc_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"unitrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_file
argument_list|(
name|filename
argument_list|,
name|TRUE
argument_list|,
literal|"GIMP units\n\n"
literal|"This file contains the user unit database. "
literal|"You can edit this list with the unit "
literal|"editor. You are not supposed to edit it "
literal|"manually, but of course you can do.\n"
literal|"This file will be entirely rewritten every "
literal|"time you quit the gimp."
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|writer
condition|)
return|return;
comment|/*  save user defined units  */
for|for
control|(
name|i
operator|=
name|_gimp_unit_get_number_of_built_in_units
argument_list|(
name|gimp
argument_list|)
init|;
name|i
operator|<
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|_gimp_unit_get_deletion_flag
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
operator|==
name|FALSE
condition|)
block|{
name|gchar
name|buf
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"unit-info"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|_gimp_unit_get_identifier
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"factor"
argument_list|)
expr_stmt|;
name|gimp_config_writer_print
argument_list|(
name|writer
argument_list|,
name|g_ascii_formatd
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%f"
argument_list|,
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"digits"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|_gimp_unit_get_digits
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"symbol"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|_gimp_unit_get_symbol
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"abbreviation"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|_gimp_unit_get_abbreviation
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"singular"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|_gimp_unit_get_singular
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"plural"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|_gimp_unit_get_plural
argument_list|(
name|gimp
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
literal|"end of units"
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
argument_list|,
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
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GTokenType
DECL|function|gimp_unitrc_unit_info_deserialize (GScanner * scanner,Gimp * gimp)
name|gimp_unitrc_unit_info_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|identifier
init|=
name|NULL
decl_stmt|;
name|gdouble
name|factor
init|=
literal|1.0
decl_stmt|;
name|gint
name|digits
init|=
literal|2.0
decl_stmt|;
name|gchar
modifier|*
name|symbol
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|abbreviation
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|singular
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|plural
init|=
name|NULL
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
name|identifier
argument_list|)
condition|)
return|return
name|G_TOKEN_STRING
return|;
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
name|UNIT_FACTOR
case|:
name|token
operator|=
name|G_TOKEN_FLOAT
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_float
argument_list|(
name|scanner
argument_list|,
operator|&
name|factor
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
break|break;
case|case
name|UNIT_DIGITS
case|:
name|token
operator|=
name|G_TOKEN_INT
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|digits
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
break|break;
case|case
name|UNIT_SYMBOL
case|:
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|symbol
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
break|break;
case|case
name|UNIT_ABBREV
case|:
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|abbreviation
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
break|break;
case|case
name|UNIT_SINGULAR
case|:
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|singular
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
break|break;
case|case
name|UNIT_PLURAL
case|:
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|plural
argument_list|)
condition|)
goto|goto
name|cleanup
goto|;
break|break;
default|default:
break|break;
block|}
name|token
operator|=
name|G_TOKEN_RIGHT_PAREN
expr_stmt|;
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
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|token
condition|)
block|{
name|GimpUnit
name|unit
init|=
name|_gimp_unit_new
argument_list|(
name|gimp
argument_list|,
name|identifier
argument_list|,
name|factor
argument_list|,
name|digits
argument_list|,
name|symbol
argument_list|,
name|abbreviation
argument_list|,
name|singular
argument_list|,
name|plural
argument_list|)
decl_stmt|;
comment|/*  make the unit definition persistent  */
name|_gimp_unit_set_deletion_flag
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
name|cleanup
label|:
name|g_free
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|symbol
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|abbreviation
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|singular
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plural
argument_list|)
expr_stmt|;
return|return
name|token
return|;
block|}
end_function

end_unit

