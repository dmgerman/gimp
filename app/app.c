begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|<locale.h>
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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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

begin_include
include|#
directive|include
file|<winnls.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"gegl/gimp-gegl.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-batch.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-user-install.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
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
file|"app.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"language.h"
end_include

begin_include
include|#
directive|include
file|"gimp-debug.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|app_init_update_noop
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
name|void
name|app_restore_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
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
modifier|*
name|loop
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|initial_screen
specifier|static
name|GObject
modifier|*
name|initial_screen
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|initial_monitor
specifier|static
name|gint
name|initial_monitor
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|app_libs_init (GOptionContext * context,gboolean no_interface)
name|app_libs_init
parameter_list|(
name|GOptionContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|no_interface
parameter_list|)
block|{
comment|/* disable OpenCL before GEGL is even initialized; this way we only    * enable if wanted in gimprc, instead of always enabling, and then    * disabling again if wanted in gimprc    */
name|g_object_set
argument_list|(
name|gegl_config
argument_list|()
argument_list|,
literal|"use-opencl"
argument_list|,
name|FALSE
argument_list|,
literal|"application-license"
argument_list|,
literal|"GPL3"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_option_context_add_group
argument_list|(
name|context
argument_list|,
name|gegl_get_option_group
argument_list|()
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
block|{
name|gui_libs_init
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
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
name|exit
argument_list|(
name|status
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_run (const gchar * full_prog_name,const gchar ** filenames,GFile * alternate_system_gimprc,GFile * alternate_gimprc,const gchar * session_name,const gchar * batch_interpreter,const gchar ** batch_commands,gboolean as_new,gboolean no_interface,gboolean no_data,gboolean no_fonts,gboolean no_splash,gboolean be_verbose,gboolean use_shm,gboolean use_cpu_accel,gboolean console_messages,gboolean use_debug_handler,gboolean show_playground,GimpStackTraceMode stack_trace_mode,GimpPDBCompatMode pdb_compat_mode)
name|app_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|full_prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
parameter_list|,
name|GFile
modifier|*
name|alternate_system_gimprc
parameter_list|,
name|GFile
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
name|batch_interpreter
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
parameter_list|,
name|gboolean
name|as_new
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
name|gboolean
name|use_debug_handler
parameter_list|,
name|gboolean
name|show_playground
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
name|GMainLoop
modifier|*
name|run_loop
decl_stmt|;
name|GFile
modifier|*
name|default_folder
init|=
name|NULL
decl_stmt|;
name|GFile
modifier|*
name|gimpdir
decl_stmt|;
if|if
condition|(
name|filenames
operator|&&
name|filenames
index|[
literal|0
index|]
operator|&&
operator|!
name|filenames
index|[
literal|1
index|]
operator|&&
name|g_file_test
argument_list|(
name|filenames
index|[
literal|0
index|]
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_path_is_absolute
argument_list|(
name|filenames
index|[
literal|0
index|]
argument_list|)
condition|)
block|{
name|default_folder
operator|=
name|g_file_new_for_path
argument_list|(
name|filenames
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|absolute
init|=
name|g_build_path
argument_list|(
name|G_DIR_SEPARATOR_S
argument_list|,
name|g_get_current_dir
argument_list|()
argument_list|,
name|filenames
index|[
literal|0
index|]
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|default_folder
operator|=
name|g_file_new_for_path
argument_list|(
name|absolute
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|absolute
argument_list|)
expr_stmt|;
block|}
name|filenames
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  Create an instance of the "Gimp" object which is the root of the    *  core object system    */
name|gimp
operator|=
name|gimp_new
argument_list|(
name|full_prog_name
argument_list|,
name|session_name
argument_list|,
name|default_folder
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
name|use_cpu_accel
argument_list|,
name|console_messages
argument_list|,
name|show_playground
argument_list|,
name|stack_trace_mode
argument_list|,
name|pdb_compat_mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|default_folder
condition|)
name|g_object_unref
argument_list|(
name|default_folder
argument_list|)
expr_stmt|;
name|gimp_cpu_accel_set_use
argument_list|(
name|use_cpu_accel
argument_list|)
expr_stmt|;
name|errors_init
argument_list|(
name|gimp
argument_list|,
name|full_prog_name
argument_list|,
name|use_debug_handler
argument_list|,
name|stack_trace_mode
argument_list|)
expr_stmt|;
comment|/*  Check if the user's gimp_directory exists    */
name|gimpdir
operator|=
name|gimp_directory_file
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_query_file_type
argument_list|(
name|gimpdir
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|)
operator|!=
name|G_FILE_TYPE_DIRECTORY
condition|)
block|{
name|GimpUserInstall
modifier|*
name|install
init|=
name|gimp_user_install_new
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|be_verbose
argument_list|)
decl_stmt|;
ifdef|#
directive|ifdef
name|GIMP_CONSOLE_COMPILATION
name|gimp_user_install_run
argument_list|(
name|install
argument_list|)
expr_stmt|;
else|#
directive|else
if|if
condition|(
operator|!
operator|(
name|no_interface
condition|?
name|gimp_user_install_run
argument_list|(
name|install
argument_list|)
else|:
name|user_install_dialog_run
argument_list|(
name|install
argument_list|)
operator|)
condition|)
name|exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_user_install_free
argument_list|(
name|install
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|gimpdir
argument_list|)
expr_stmt|;
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|alternate_system_gimprc
argument_list|,
name|alternate_gimprc
argument_list|)
expr_stmt|;
comment|/*  change the locale if a language if specified  */
name|language_init
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|language
argument_list|)
expr_stmt|;
comment|/*  initialize lowlevel stuff  */
name|gimp_gegl_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Connect our restore_after callback before gui_init() connects    *  theirs, so ours runs first and can grab the initial monitor    *  before the GUI's restore_after callback resets it.    */
name|g_signal_connect_after
argument_list|(
name|gimp
argument_list|,
literal|"restore"
argument_list|,
name|G_CALLBACK
argument_list|(
name|app_restore_after_callback
argument_list|)
argument_list|,
name|NULL
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
name|app_init_update_noop
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
name|loop
operator|=
name|run_loop
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
operator|&
name|run_loop
argument_list|)
expr_stmt|;
comment|/*  Load the images given on the command-line.    */
if|if
condition|(
name|filenames
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
name|filenames
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|run_loop
condition|)
block|{
name|GFile
modifier|*
name|file
init|=
name|g_file_new_for_commandline_arg
argument_list|(
name|filenames
index|[
name|i
index|]
argument_list|)
decl_stmt|;
name|file_open_from_command_line
argument_list|(
name|gimp
argument_list|,
name|file
argument_list|,
name|as_new
argument_list|,
name|initial_screen
argument_list|,
name|initial_monitor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|run_loop
condition|)
name|gimp_batch_run
argument_list|(
name|gimp
argument_list|,
name|batch_interpreter
argument_list|,
name|batch_commands
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_loop
condition|)
block|{
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
block|}
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
name|gimp_debug_instances
argument_list|()
expr_stmt|;
name|errors_exit
argument_list|()
expr_stmt|;
name|gegl_exit
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
DECL|function|app_init_update_noop (const gchar * text1,const gchar * text2,gdouble percentage)
name|app_init_update_noop
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
block|{
comment|/*  deliberately do nothing  */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|app_restore_after_callback (Gimp * gimp,GimpInitStatusFunc status_callback)
name|app_restore_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
block|{
comment|/*  Getting the display name for a -1 display returns the initial    *  monitor during startup. Need to call this from a restore_after    *  callback, because before restore(), the GUI can't return anything,    *  after after restore() the initial monitor gets reset.    */
name|g_free
argument_list|(
name|gimp_get_display_name
argument_list|(
name|gimp
argument_list|,
operator|-
literal|1
argument_list|,
operator|&
name|initial_screen
argument_list|,
operator|&
name|initial_monitor
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|app_exit_after_callback (Gimp * gimp,gboolean kill_it,GMainLoop ** loop)
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
literal|"EXIT: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
comment|/*    *  In stable releases, we simply call exit() here. This speeds up    *  the process of quitting GIMP and also works around the problem    *  that plug-ins might still be running.    *    *  In unstable releases, we shut down GIMP properly in an attempt    *  to catch possible problems in our finalizers.    */
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
if|if
condition|(
name|g_main_loop_is_running
argument_list|(
operator|*
name|loop
argument_list|)
condition|)
name|g_main_loop_quit
argument_list|(
operator|*
name|loop
argument_list|)
expr_stmt|;
operator|*
name|loop
operator|=
name|NULL
expr_stmt|;
else|#
directive|else
name|gegl_exit
argument_list|()
expr_stmt|;
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

