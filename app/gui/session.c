begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Session-managment stuff  * Copyright (C) 1998 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

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
file|<glib/gstdio.h>
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
file|"libgimpconfig/gimpconfig.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-file.h"
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
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27a58fd00103
block|{
DECL|enumerator|SESSION_INFO
name|SESSION_INFO
init|=
literal|1
block|,
DECL|enumerator|LAST_TIP_SHOWN
name|LAST_TIP_SHOWN
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|gchar
modifier|*
name|session_filename
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|sessionrc_deleted
specifier|static
name|gboolean
name|sessionrc_deleted
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

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
name|session_filename
argument_list|(
name|gimp
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
literal|"sessionrc"
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
literal|"last-tip-shown"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|LAST_TIP_SHOWN
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
name|GimpDialogFactory
modifier|*
name|factory
init|=
name|NULL
decl_stmt|;
name|GimpSessionInfo
modifier|*
name|info
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|factory_name
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|entry_name
init|=
name|NULL
decl_stmt|;
name|GimpDialogFactoryEntry
modifier|*
name|entry
init|=
name|NULL
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
break|break;
comment|/* In versions<= GIMP 2.6 there was a "toolbox", a                * "dock", a "display" and a "toplevel" factory. These                * are now merged to a single gimp_dialog_factory_get_singleton (). We                * need the legacy name though, so keep it around.                */
name|factory
operator|=
name|gimp_dialog_factory_get_singleton
argument_list|()
expr_stmt|;
name|info
operator|=
name|gimp_session_info_new
argument_list|()
expr_stmt|;
comment|/* GIMP 2.6 has the entry name as part of the                * session-info header, so try to get it                */
name|gimp_scanner_parse_string
argument_list|(
name|scanner
argument_list|,
operator|&
name|entry_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry_name
condition|)
block|{
comment|/* Previously, GimpDock was a toplevel. That is why                    * versions<= GIMP 2.6 has "dock" as the entry name. We                    * want "dock" to be interpreted as 'dock window'                    * however so have some special-casing for that. When                    * the entry name is "dock" the factory name is either                    * "dock" or "toolbox".                    */
if|if
condition|(
name|strcmp
argument_list|(
name|entry_name
argument_list|,
literal|"dock"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|entry
operator|=
name|gimp_dialog_factory_find_entry
argument_list|(
name|factory
argument_list|,
operator|(
name|strcmp
argument_list|(
name|factory_name
argument_list|,
literal|"toolbox"
argument_list|)
operator|==
literal|0
condition|?
literal|"gimp-toolbox-window"
else|:
literal|"gimp-dock-window"
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|entry
operator|=
name|gimp_dialog_factory_find_entry
argument_list|(
name|factory
argument_list|,
name|entry_name
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* We're done with these now */
name|g_free
argument_list|(
name|factory_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry_name
argument_list|)
expr_stmt|;
comment|/* We can get the factory entry either now (the GIMP<=                * 2.6 way), or when we deserialize (the GIMP 2.8 way)                */
if|if
condition|(
name|entry
condition|)
block|{
name|gimp_session_info_set_factory_entry
argument_list|(
name|info
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
comment|/* Always try to deserialize */
if|if
condition|(
name|gimp_config_deserialize
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|info
argument_list|)
argument_list|,
name|scanner
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
comment|/* Make sure we got a factory entry either the 2.6                    * or 2.8 way                    */
if|if
condition|(
name|gimp_session_info_get_factory_entry
argument_list|(
name|info
argument_list|)
condition|)
block|{
name|GIMP_LOG
argument_list|(
name|DIALOG_FACTORY
argument_list|,
literal|"successfully parsed and added session info %p"
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_add_session_info
argument_list|(
name|factory
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GIMP_LOG
argument_list|(
name|DIALOG_FACTORY
argument_list|,
literal|"failed to parse session info %p, not adding"
argument_list|,
name|info
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
break|break;
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
name|gimp_config_file_backup_on_error
argument_list|(
name|filename
argument_list|,
literal|"sessionrc"
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
name|dialogs_load_recent_docks
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|session_exit (Gimp * gimp)
name|session_exit
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
name|gimp_dialog_factory_restore
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|session_save (Gimp * gimp,gboolean always_save)
name|session_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|always_save
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
if|if
condition|(
name|sessionrc_deleted
operator|&&
operator|!
name|always_save
condition|)
return|return;
name|filename
operator|=
name|session_filename
argument_list|(
name|gimp
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
literal|"GIMP sessionrc\n\n"
literal|"This file takes session-specific info "
literal|"(that is info, you want to keep between "
literal|"two GIMP sessions).  You are not supposed "
literal|"to edit it manually, but of course you "
literal|"can do.  The sessionrc will be entirely "
literal|"rewritten every time you quit GIMP.  "
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
name|gimp_dialog_factory_save
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
comment|/* save last tip shown    *    * FIXME: Make last-tip-shown increment only when used within the    * session    */
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
argument_list|)
expr_stmt|;
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_writer_finish
argument_list|(
name|writer
argument_list|,
literal|"end of sessionrc"
argument_list|,
operator|&
name|error
argument_list|)
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
name|dialogs_save_recent_docks
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|sessionrc_deleted
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|session_clear (Gimp * gimp,GError ** error)
name|session_clear
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
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
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|filename
operator|=
name|session_filename
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_unlink
argument_list|(
name|filename
argument_list|)
operator|!=
literal|0
operator|&&
name|errno
operator|!=
name|ENOENT
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Deleting \"%s\" failed: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|sessionrc_deleted
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|session_filename (Gimp * gimp)
name|session_filename
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|gimp_personal_rc_file
argument_list|(
literal|"sessionrc"
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp
operator|->
name|session_name
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|g_strconcat
argument_list|(
name|filename
argument_list|,
literal|"."
argument_list|,
name|gimp
operator|->
name|session_name
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|tmp
expr_stmt|;
block|}
return|return
name|filename
return|;
block|}
end_function

end_unit

