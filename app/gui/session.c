begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Session-managment stuff  * Copyright (C) 1998 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"color-history.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GTokenType
name|session_info_deserialize
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

begin_function_decl
specifier|static
name|GTokenType
name|session_info_dock_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_enum
enum|enum
DECL|enum|__anon296ea8530103
block|{
DECL|enumerator|SESSION_INFO
name|SESSION_INFO
init|=
literal|1
block|,
DECL|enumerator|COLOR_HISTORY
name|COLOR_HISTORY
block|,
DECL|enumerator|LAST_TIP_SHOWN
name|LAST_TIP_SHOWN
block|,
DECL|enumerator|SESSION_INFO_POSITION
name|SESSION_INFO_POSITION
block|,
DECL|enumerator|SESSION_INFO_SIZE
name|SESSION_INFO_SIZE
block|,
DECL|enumerator|SESSION_INFO_OPEN
name|SESSION_INFO_OPEN
block|,
DECL|enumerator|SESSION_INFO_AUX
name|SESSION_INFO_AUX
block|,
DECL|enumerator|SESSION_INFO_DOCK
name|SESSION_INFO_DOCK
block|,
DECL|enumerator|SESSION_INFO_DOCK_BOOK
name|SESSION_INFO_DOCK_BOOK
block|}
enum|;
end_enum

begin_function
name|void
DECL|function|session_init (Gimp * gimp)
name|session_init
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
literal|"sessionrc"
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scanner
condition|)
block|{
comment|/*  always show L&C&P, Tool Options and Brushes on first invocation  */
comment|/* TODO */
return|return;
block|}
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"session-info"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"color-history"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|COLOR_HISTORY
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
literal|0
argument_list|,
literal|"last-tip-shown"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|LAST_TIP_SHOWN
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO
argument_list|,
literal|"position"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_POSITION
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO
argument_list|,
literal|"size"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_SIZE
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO
argument_list|,
literal|"open-on-exit"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_OPEN
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO
argument_list|,
literal|"aux-info"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_AUX
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO
argument_list|,
literal|"dock"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_DOCK
argument_list|)
argument_list|)
expr_stmt|;
name|g_scanner_scope_add_symbol
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO_DOCK
argument_list|,
literal|"book"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|SESSION_INFO_DOCK_BOOK
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
name|SESSION_INFO
argument_list|)
condition|)
block|{
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO
argument_list|)
expr_stmt|;
name|token
operator|=
name|session_info_deserialize
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
else|else
break|break;
block|}
elseif|else
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
name|COLOR_HISTORY
argument_list|)
condition|)
block|{
while|while
condition|(
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_color
argument_list|(
name|scanner
argument_list|,
operator|&
name|color
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|color_history_add_from_rc
argument_list|(
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
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
name|LAST_TIP_SHOWN
argument_list|)
condition|)
block|{
name|GimpGuiConfig
modifier|*
name|config
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
decl_stmt|;
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
name|config
operator|->
name|last_tip
argument_list|)
condition|)
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
block|}
name|error
label|:
if|if
condition|(
name|error
condition|)
block|{
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
block|}
end_function

begin_function
name|void
DECL|function|session_restore (Gimp * gimp)
name|session_restore
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
name|gimp_dialog_factories_session_restore
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|session_save (Gimp * gimp)
name|session_save
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
literal|"sessionrc"
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
literal|"GIMP sessionrc\n\n"
literal|"This file takes session-specific info "
literal|"(that is info, you want to keep between "
literal|"two GIMP sessions). You are not supposed "
literal|"to edit it manually, but of course you "
literal|"can do. The sessionrc will be entirely "
literal|"rewritten every time you quit The GIMP. "
literal|"If this file isn't found, defaults are "
literal|"used."
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
name|gimp_dialog_factories_session_save
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
comment|/* save last tip shown */
name|gimp_config_writer_open
argument_list|(
name|writer
argument_list|,
literal|"last-tip-shown"
argument_list|)
expr_stmt|;
name|gimp_config_writer_printf
argument_list|(
name|writer
argument_list|,
literal|"%d"
argument_list|,
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|last_tip
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|color_history_write
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
literal|"end of sessionrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|session_clear (Gimp * gimp)
name|session_clear
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
name|g_print
argument_list|(
literal|"TODO: implement session_clear()\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GTokenType
DECL|function|session_info_deserialize (GScanner * scanner,Gimp * gimp)
name|session_info_deserialize
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
name|GimpDialogFactory
modifier|*
name|factory
decl_stmt|;
name|GimpSessionInfo
modifier|*
name|info
init|=
name|NULL
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
name|gchar
modifier|*
name|factory_name
decl_stmt|;
name|gchar
modifier|*
name|entry_name
decl_stmt|;
name|gchar
modifier|*
name|string
decl_stmt|;
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
name|factory_name
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
name|factory_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|factory_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|factory
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|entry_name
argument_list|)
condition|)
goto|goto
name|error
goto|;
name|info
operator|=
name|g_new0
argument_list|(
name|GimpSessionInfo
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|entry_name
argument_list|,
literal|"dock"
argument_list|)
condition|)
block|{
name|info
operator|->
name|toplevel_entry
operator|=
name|gimp_dialog_factory_find_entry
argument_list|(
name|factory
argument_list|,
name|entry_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|info
operator|->
name|toplevel_entry
condition|)
goto|goto
name|error
goto|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|entry_name
argument_list|)
expr_stmt|;
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
name|SESSION_INFO_POSITION
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
name|info
operator|->
name|x
argument_list|)
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|y
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_SIZE
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
name|info
operator|->
name|width
argument_list|)
condition|)
goto|goto
name|error
goto|;
if|if
condition|(
operator|!
name|gimp_scanner_parse_int
argument_list|(
name|scanner
argument_list|,
operator|&
name|info
operator|->
name|height
argument_list|)
condition|)
goto|goto
name|error
goto|;
break|break;
case|case
name|SESSION_INFO_OPEN
case|:
name|info
operator|->
name|open
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|SESSION_INFO_AUX
case|:
while|while
condition|(
operator|(
name|token
operator|=
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|)
operator|==
name|G_TOKEN_STRING
condition|)
block|{
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
name|info
operator|->
name|aux_info
operator|=
name|g_list_append
argument_list|(
name|info
operator|->
name|aux_info
argument_list|,
name|string
argument_list|)
expr_stmt|;
else|else
break|break;
block|}
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_RIGHT_PAREN
condition|)
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
break|break;
case|case
name|SESSION_INFO_DOCK
case|:
if|if
condition|(
name|info
operator|->
name|toplevel_entry
condition|)
goto|goto
name|error
goto|;
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO_DOCK
argument_list|)
expr_stmt|;
name|token
operator|=
name|session_info_dock_deserialize
argument_list|(
name|scanner
argument_list|,
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|==
name|G_TOKEN_LEFT_PAREN
condition|)
name|g_scanner_set_scope
argument_list|(
name|scanner
argument_list|,
name|SESSION_INFO
argument_list|)
expr_stmt|;
else|else
goto|goto
name|error
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
name|factory
operator|->
name|session_infos
operator|=
name|g_list_append
argument_list|(
name|factory
operator|->
name|session_infos
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|token
return|;
block|}
name|error
label|:
if|if
condition|(
name|info
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|info
operator|->
name|sub_dialogs
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|g_list_foreach
argument_list|(
name|list
operator|->
name|data
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|info
operator|->
name|sub_dialogs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|token
return|;
block|}
end_function

begin_function
specifier|static
name|GTokenType
DECL|function|session_info_dock_deserialize (GScanner * scanner,GimpSessionInfo * info)
name|session_info_dock_deserialize
parameter_list|(
name|GScanner
modifier|*
name|scanner
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|string
decl_stmt|;
name|GTokenType
name|token
decl_stmt|;
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
name|SESSION_INFO_DOCK_BOOK
case|:
name|list
operator|=
name|NULL
expr_stmt|;
while|while
condition|(
operator|(
name|token
operator|=
name|g_scanner_peek_next_token
argument_list|(
name|scanner
argument_list|)
operator|)
operator|==
name|G_TOKEN_STRING
condition|)
block|{
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
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|string
argument_list|)
expr_stmt|;
else|else
break|break;
block|}
if|if
condition|(
name|list
condition|)
name|info
operator|->
name|sub_dialogs
operator|=
name|g_list_append
argument_list|(
name|info
operator|->
name|sub_dialogs
argument_list|,
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|token
operator|!=
name|G_TOKEN_RIGHT_PAREN
condition|)
name|token
operator|=
name|G_TOKEN_STRING
expr_stmt|;
break|break;
default|default:
return|return
name|token
return|;
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
return|return
name|token
return|;
block|}
end_function

end_unit

