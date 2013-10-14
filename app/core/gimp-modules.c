begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmodules.c  * (C) 1999 Austin Donnelly<austin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-modules.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_modules_init (Gimp * gimp)
name|gimp_modules_init
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
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
block|{
name|gimp
operator|->
name|module_db
operator|=
name|gimp_module_db_new
argument_list|(
name|gimp
operator|->
name|be_verbose
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|write_modulerc
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_modules_exit (Gimp * gimp)
name|gimp_modules_exit
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
if|if
condition|(
name|gimp
operator|->
name|module_db
condition|)
block|{
name|g_object_unref
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|module_db
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_modules_load (Gimp * gimp)
name|gimp_modules_load
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
name|gchar
modifier|*
name|path
decl_stmt|;
name|GScanner
modifier|*
name|scanner
decl_stmt|;
name|gchar
modifier|*
name|module_load_inhibit
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
if|if
condition|(
name|gimp
operator|->
name|no_interface
condition|)
return|return;
comment|/* FIXME, gimp->be_verbose is not yet initialized in init() */
name|gimp
operator|->
name|module_db
operator|->
name|verbose
operator|=
name|gimp
operator|->
name|be_verbose
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"modulerc"
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
name|scanner
condition|)
block|{
name|GTokenType
name|token
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
DECL|macro|MODULE_LOAD_INHIBIT
define|#
directive|define
name|MODULE_LOAD_INHIBIT
value|1
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"module-load-inhibit"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|MODULE_LOAD_INHIBIT
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
name|MODULE_LOAD_INHIBIT
argument_list|)
condition|)
block|{
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string_no_validate
argument_list|(
name|scanner
argument_list|,
operator|&
name|module_load_inhibit
argument_list|)
condition|)
goto|goto
name|error
goto|;
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
comment|/* do nothing */
break|break;
block|}
block|}
undef|#
directive|undef
name|MODULE_LOAD_INHIBIT
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
block|}
name|error
label|:
if|if
condition|(
name|error
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
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
name|gimp_scanner_destroy
argument_list|(
name|scanner
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|module_load_inhibit
condition|)
block|{
name|gimp_module_db_set_load_inhibit
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
name|module_load_inhibit
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|module_load_inhibit
argument_list|)
expr_stmt|;
block|}
name|path
operator|=
name|gimp_config_path_expand
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|module_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_module_db_load
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_to_inhibit_string (gpointer data,gpointer user_data)
name|add_to_inhibit_string
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpModule
modifier|*
name|module
init|=
name|data
decl_stmt|;
name|GString
modifier|*
name|str
init|=
name|user_data
decl_stmt|;
if|if
condition|(
name|module
operator|->
name|load_inhibit
condition|)
block|{
name|g_string_append_c
argument_list|(
name|str
argument_list|,
name|G_SEARCHPATH_SEPARATOR
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
name|module
operator|->
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_modules_unload (Gimp * gimp)
name|gimp_modules_unload
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
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
operator|&&
name|gimp
operator|->
name|write_modulerc
condition|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|GString
modifier|*
name|str
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|str
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|gimp
operator|->
name|module_db
operator|->
name|modules
argument_list|,
name|add_to_inhibit_string
argument_list|,
name|str
argument_list|)
expr_stmt|;
if|if
condition|(
name|str
operator|->
name|len
operator|>
literal|0
condition|)
name|p
operator|=
name|str
operator|->
name|str
operator|+
literal|1
expr_stmt|;
else|else
name|p
operator|=
literal|""
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"modulerc"
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
literal|"GIMP modulerc"
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
condition|)
block|{
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"module-load-inhibit"
argument_list|)
expr_stmt|;
name|gimp_config_writer_string
argument_list|(
name|writer
argument_list|,
name|p
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
literal|"end of modulerc"
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|write_modulerc
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_string_free
argument_list|(
name|str
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_modules_refresh (Gimp * gimp)
name|gimp_modules_refresh
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
if|if
condition|(
operator|!
name|gimp
operator|->
name|no_interface
condition|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|path
operator|=
name|gimp_config_path_expand
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|module_path
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_module_db_refresh
argument_list|(
name|gimp
operator|->
name|module_db
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

