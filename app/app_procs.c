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

begin_include
include|#
directive|include
file|"tools/gimp-tools.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui.h"
end_include

begin_include
include|#
directive|include
file|"gui/user-install-dialog.h"
end_include

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
file|"gimp-intl.h"
end_include

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
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|the_gimp
name|Gimp
modifier|*
name|the_gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|app_gui_libs_init (gint * argc,gchar *** argv)
name|app_gui_libs_init
parameter_list|(
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
return|return
name|gui_libs_init
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|app_init (const gchar * full_prog_name,gint gimp_argc,gchar ** gimp_argv,const gchar * alternate_system_gimprc,const gchar * alternate_gimprc,const gchar * session_name,const gchar ** batch_cmds,gboolean no_interface,gboolean no_data,gboolean no_fonts,gboolean no_splash,gboolean no_splash_image,gboolean be_verbose,gboolean use_shm,gboolean use_mmx,gboolean console_messages,GimpStackTraceMode stack_trace_mode)
name|app_init
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
name|no_splash_image
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|gboolean
name|use_shm
parameter_list|,
name|gboolean
name|use_mmx
parameter_list|,
name|gboolean
name|console_messages
parameter_list|,
name|GimpStackTraceMode
name|stack_trace_mode
parameter_list|)
block|{
name|GimpInitStatusFunc
name|update_status_func
init|=
name|NULL
decl_stmt|;
comment|/*  Create an instance of the "Gimp" object which is the root of the    *  core object system    */
name|the_gimp
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
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Base"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Paint-Funcs"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Config"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Core"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-PDB"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Plug-In"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-File"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-XCF"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Widgets"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Display"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Tools"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-Text"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
argument_list|)
expr_stmt|;
name|g_log_set_handler
argument_list|(
literal|"Gimp-GUI"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
operator|&
name|the_gimp
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
name|the_gimp
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
if|if
condition|(
name|no_interface
condition|)
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
name|g_print
argument_list|(
literal|"%s\n\n"
argument_list|,
name|msg
argument_list|)
expr_stmt|;
block|}
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
block|}
name|gimp_load_config
argument_list|(
name|the_gimp
argument_list|,
name|alternate_system_gimprc
argument_list|,
name|alternate_gimprc
argument_list|,
name|use_mmx
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
name|update_status_func
operator|=
name|gui_init
argument_list|(
name|the_gimp
argument_list|,
name|no_splash
argument_list|,
name|no_splash_image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|update_status_func
condition|)
name|update_status_func
operator|=
name|app_init_update_none
expr_stmt|;
comment|/*  connect our "exit" callbacks after gui_init() so they are    *  invoked after the GUI's "exit" callbacks    */
name|g_signal_connect_after
argument_list|(
name|the_gimp
argument_list|,
literal|"exit"
argument_list|,
name|G_CALLBACK
argument_list|(
name|app_exit_after_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Create all members of the global Gimp instance which need an already    *  parsed gimprc, e.g. the data factories    */
name|gimp_initialize
argument_list|(
name|the_gimp
argument_list|,
name|update_status_func
argument_list|)
expr_stmt|;
comment|/*  Load all data files    */
name|gimp_restore
argument_list|(
name|the_gimp
argument_list|,
name|update_status_func
argument_list|)
expr_stmt|;
comment|/*  enable autosave late so we don't autosave when the    *  monitor resolution is set in gui_init()    */
name|gimp_rc_set_autosave
argument_list|(
name|GIMP_RC
argument_list|(
name|the_gimp
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
name|the_gimp
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
name|the_gimp
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
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
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
name|batch_init
argument_list|(
name|the_gimp
argument_list|,
name|batch_cmds
argument_list|)
expr_stmt|;
if|if
condition|(
name|no_interface
condition|)
block|{
name|GMainLoop
modifier|*
name|loop
decl_stmt|;
name|loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_threads_leave
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|loop
argument_list|)
expr_stmt|;
name|gimp_threads_enter
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|g_main_loop_unref
argument_list|(
name|loop
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gui_post_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
block|}
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
DECL|function|app_exit_after_callback (Gimp * gimp,gboolean kill_it)
name|app_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
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
name|g_object_unref
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|the_gimp
operator|=
name|NULL
expr_stmt|;
comment|/*  There used to be foo_main_quit() here, but there's a chance    *  that foo_main() was never called before we reach this point. --Sven    */
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

