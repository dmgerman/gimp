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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_PARAM_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimprc.h"
end_include

begin_include
include|#
directive|include
file|"base/base.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_include
include|#
directive|include
file|"dialogs/user-install-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"batch.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  local prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|app_init_update_none
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|app_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|,
name|GMainLoop
modifier|*
name|loop
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|app_libs_init (gboolean * no_interface,gint * argc,gchar *** argv)
name|app_libs_init
parameter_list|(
name|gboolean
modifier|*
name|no_interface
parameter_list|,
name|gint
modifier|*
name|argc
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|GIMP_CONSOLE_COMPILATION
operator|*
name|no_interface
operator|=
name|TRUE
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|*
name|no_interface
condition|)
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
operator|(
operator|*
name|argv
operator|)
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_set_prgname
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
return|return
name|TRUE
return|;
block|}
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
else|else
block|{
return|return
name|gui_libs_init
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|)
return|;
block|}
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|app_abort (gboolean no_interface,const gchar * abort_message)
name|app_abort
parameter_list|(
name|gboolean
name|no_interface
parameter_list|,
specifier|const
name|gchar
modifier|*
name|abort_message
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
name|no_interface
condition|)
endif|#
directive|endif
block|{
name|g_print
argument_list|(
literal|"%s\n\n"
argument_list|,
name|abort_message
argument_list|)
expr_stmt|;
block|}
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
else|else
block|{
name|gui_abort
argument_list|(
name|abort_message
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|app_exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_exit (gint status)
name|app_exit
parameter_list|(
name|gint
name|status
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* Give them time to read the message if it was printed in a    * separate console window. I would really love to have    * some way of asking for confirmation to close the console    * window.    */
name|HANDLE
name|console
decl_stmt|;
name|DWORD
name|mode
decl_stmt|;
name|console
operator|=
name|GetStdHandle
argument_list|(
name|STD_OUTPUT_HANDLE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GetConsoleMode
argument_list|(
name|console
argument_list|,
operator|&
name|mode
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_print
argument_list|(
name|_
argument_list|(
literal|"(This console window will close in ten seconds)\n"
argument_list|)
argument_list|)
expr_stmt|;
name|Sleep
argument_list|(
literal|10000
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|exit
argument_list|(
name|status
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_run (const gchar * full_prog_name,gint gimp_argc,gchar ** gimp_argv,const gchar * alternate_system_gimprc,const gchar * alternate_gimprc,const gchar * session_name,const gchar ** batch_cmds,gboolean no_interface,gboolean no_data,gboolean no_fonts,gboolean no_splash,gboolean be_verbose,gboolean use_shm,gboolean use_cpu_accel,gboolean console_messages,GimpStackTraceMode stack_trace_mode,GimpPDBCompatMode pdb_compat_mode)
name|app_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|full_prog_name
parameter_list|,
name|gint
name|gimp_argc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|gimp_argv
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_system_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|session_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_cmds
parameter_list|,
name|gboolean
name|no_interface
parameter_list|,
name|gboolean
name|no_data
parameter_list|,
name|gboolean
name|no_fonts
parameter_list|,
name|gboolean
name|no_splash
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|gboolean
name|use_shm
parameter_list|,
name|gboolean
name|use_cpu_accel
parameter_list|,
name|gboolean
name|console_messages
parameter_list|,
name|GimpStackTraceMode
name|stack_trace_mode
parameter_list|,
name|GimpPDBCompatMode
name|pdb_compat_mode
parameter_list|)
block|{
name|GimpInitStatusFunc
name|update_status_func
init|=
name|NULL
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GMainLoop
modifier|*
name|loop
decl_stmt|;
name|gboolean
name|swap_is_ok
decl_stmt|;
name|gint
name|i
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|log_domains
index|[]
init|=
block|{
literal|"Gimp"
block|,
literal|"Gimp-Actions"
block|,
literal|"Gimp-Base"
block|,
literal|"Gimp-Composite"
block|,
literal|"Gimp-Config"
block|,
literal|"Gimp-Core"
block|,
literal|"Gimp-Dialogs"
block|,
literal|"Gimp-Display"
block|,
literal|"Gimp-File"
block|,
literal|"Gimp-GUI"
block|,
literal|"Gimp-Menus"
block|,
literal|"Gimp-PDB"
block|,
literal|"Gimp-Paint-Funcs"
block|,
literal|"Gimp-Plug-In"
block|,
literal|"Gimp-Text"
block|,
literal|"Gimp-Tools"
block|,
literal|"Gimp-Vectors"
block|,
literal|"Gimp-Widgets"
block|,
literal|"Gimp-XCF"
block|}
decl_stmt|;
comment|/*  Create an instance of the "Gimp" object which is the root of the    *  core object system    */
name|gimp
operator|=
name|gimp_new
argument_list|(
name|full_prog_name
argument_list|,
name|session_name
argument_list|,
name|be_verbose
argument_list|,
name|no_data
argument_list|,
name|no_fonts
argument_list|,
name|no_interface
argument_list|,
name|use_shm
argument_list|,
name|console_messages
argument_list|,
name|stack_trace_mode
argument_list|,
name|pdb_compat_mode
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
name|G_N_ELEMENTS
argument_list|(
name|log_domains
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_log_set_handler
argument_list|(
name|log_domains
index|[
name|i
index|]
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
name|NULL
argument_list|,
name|G_LOG_LEVEL_ERROR
operator||
name|G_LOG_FLAG_FATAL
argument_list|,
name|gimp_error_log_func
argument_list|,
operator|&
name|gimp
argument_list|)
expr_stmt|;
name|units_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Check if the user's gimp_directory exists    */
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
comment|/*  not properly installed  */
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
name|no_interface
condition|)
endif|#
directive|endif
block|{
specifier|const
name|gchar
modifier|*
name|msg
decl_stmt|;
name|msg
operator|=
name|_
argument_list|(
literal|"GIMP is not properly installed for the current user.\n"
literal|"User installation was skipped because the '--no-interface' flag was used.\n"
literal|"To perform user installation, run the GIMP without the '--no-interface' flag."
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"%s\n\n"
argument_list|,
name|msg
argument_list|)
expr_stmt|;
block|}
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
else|else
block|{
name|user_install_dialog_run
argument_list|(
name|alternate_system_gimprc
argument_list|,
name|alternate_gimprc
argument_list|,
name|be_verbose
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
if|#
directive|if
name|defined
name|G_OS_WIN32
operator|&&
operator|!
name|defined
name|GIMP_CONSOLE_COMPILATION
comment|/* Common windoze apps don't have a console at all. So does Gimp    * - if appropiate. This allows to compile as console application    * with all it's benefits (like inheriting the console) but hide    * it, if the user doesn't want it.    */
if|if
condition|(
operator|!
name|no_interface
operator|&&
operator|!
name|be_verbose
operator|&&
operator|!
name|console_messages
condition|)
name|FreeConsole
argument_list|()
expr_stmt|;
endif|#
directive|endif
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|alternate_system_gimprc
argument_list|,
name|alternate_gimprc
argument_list|)
expr_stmt|;
comment|/*  initialize lowlevel stuff  */
name|swap_is_ok
operator|=
name|base_init
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
name|be_verbose
argument_list|,
name|use_cpu_accel
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
operator|!
name|no_interface
condition|)
name|update_status_func
operator|=
name|gui_init
argument_list|(
name|gimp
argument_list|,
name|no_splash
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|update_status_func
condition|)
name|update_status_func
operator|=
name|app_init_update_none
expr_stmt|;
comment|/*  Create all members of the global Gimp instance which need an already    *  parsed gimprc, e.g. the data factories    */
name|gimp_initialize
argument_list|(
name|gimp
argument_list|,
name|update_status_func
argument_list|)
expr_stmt|;
comment|/*  Load all data files    */
name|gimp_restore
argument_list|(
name|gimp
argument_list|,
name|update_status_func
argument_list|)
expr_stmt|;
comment|/* display a warning when no test swap file could be generated */
if|if
condition|(
operator|!
name|swap_is_ok
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to open a test swap file. To avoid data loss "
literal|"please check the location and permissions of the swap "
literal|"directory defined in your Preferences "
literal|"(currently \"%s\")."
argument_list|)
argument_list|,
name|GIMP_BASE_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|swap_path
argument_list|)
expr_stmt|;
comment|/*  enable autosave late so we don't autosave when the    *  monitor resolution is set in gui_init()    */
name|gimp_rc_set_autosave
argument_list|(
name|GIMP_RC
argument_list|(
name|gimp
operator|->
name|edit_config
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Parse the rest of the command line arguments as images to load    */
if|if
condition|(
name|gimp_argc
operator|>
literal|0
condition|)
block|{
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
name|gimp_argc
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|gimp_argv
index|[
name|i
index|]
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
comment|/*  first try if we got a file uri  */
name|uri
operator|=
name|g_filename_from_uri
argument_list|(
name|gimp_argv
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_strdup
argument_list|(
name|gimp_argv
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|uri
operator|=
name|file_utils_filename_to_uri
argument_list|(
name|gimp
operator|->
name|load_procs
argument_list|,
name|gimp_argv
index|[
name|i
index|]
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|uri
condition|)
block|{
name|g_printerr
argument_list|(
literal|"conversion filename -> uri failed: %s\n"
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
else|else
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|gimage
operator|=
name|file_open_with_display
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|uri
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Opening '%s' failed: %s"
argument_list|)
argument_list|,
name|filename
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
operator|!
name|no_interface
condition|)
name|gui_post_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|batch_run
argument_list|(
name|gimp
argument_list|,
name|batch_cmds
argument_list|)
expr_stmt|;
name|loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|gimp
argument_list|,
literal|"exit"
argument_list|,
name|G_CALLBACK
argument_list|(
name|app_exit_after_callback
argument_list|)
argument_list|,
name|loop
argument_list|)
expr_stmt|;
name|gimp_threads_leave
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|loop
argument_list|)
expr_stmt|;
name|gimp_threads_enter
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_main_loop_unref
argument_list|(
name|loop
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|base_exit
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|app_init_update_none (const gchar * text1,const gchar * text2,gdouble percentage)
name|app_init_update_none
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|app_exit_after_callback (Gimp * gimp,gboolean kill_it,GMainLoop * loop)
name|app_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|,
name|GMainLoop
modifier|*
name|loop
parameter_list|)
block|{
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"EXIT: app_exit_after_callback\n"
argument_list|)
expr_stmt|;
comment|/*    *  In stable releases, we simply call exit() here. This speeds up    *  the process of quitting GIMP and also works around the problem    *  that plug-ins might still be running.    *    *  In unstable releases, we shut down GIMP properly in an attempt    *  to catch possible problems in our finalizers.    */
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|g_main_loop_quit
argument_list|(
name|loop
argument_list|)
expr_stmt|;
else|#
directive|else
name|exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

end_unit

