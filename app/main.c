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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_WAIT_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/wait.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|__GLIBC__
end_ifdef

begin_include
include|#
directive|include
file|<malloc.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|WAIT_ANY
end_ifndef

begin_define
DECL|macro|WAIT_ANY
define|#
directive|define
name|WAIT_ANY
value|-1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<locale.h>
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
file|"config/gimpconfig-dump.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"sanity.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
end_ifdef

begin_decl_stmt
DECL|variable|stack_trace_mode
specifier|static
name|GimpStackTraceMode
name|stack_trace_mode
init|=
name|GIMP_STACK_TRACE_QUERY
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pdb_compat_mode
specifier|static
name|GimpPDBCompatMode
name|pdb_compat_mode
init|=
name|GIMP_PDB_COMPAT_WARN
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

begin_decl_stmt
DECL|variable|stack_trace_mode
specifier|static
name|GimpStackTraceMode
name|stack_trace_mode
init|=
name|GIMP_STACK_TRACE_NEVER
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pdb_compat_mode
specifier|static
name|GimpPDBCompatMode
name|pdb_compat_mode
init|=
name|GIMP_PDB_COMPAT_ON
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|G_OS_WIN32
end_ifndef

begin_decl_stmt
specifier|static
name|void
name|gimp_sigfatal_handler
argument_list|(
name|gint
name|sig_num
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_sigchld_handler
parameter_list|(
name|gint
name|sig_num
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|gboolean
name|gimp_option_stack_trace_mode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_option_pdb_compat_mode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_option_dump_gimprc
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_show_version
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  argv processing:  *      Arguments are either switches, their associated  *      values, or image files.  As switches and their  *      associated values are processed, those slots in  *      the argv[] array are NULLed. We do this because  *      unparsed args are treated as images to load on  *      startup.  *  *      The GTK switches are processed first (X switches are  *      processed here, not by any X routines).  Then the  *      general GIMP switches are processed.  Any args  *      left are assumed to be image files the GIMP should  *      display.  *  *      The exception is the batch switch.  When this is  *      encountered, all remaining args are treated as batch  *      commands.  */
end_comment

begin_function
name|int
DECL|function|main (int argc,char ** argv)
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|GOptionContext
modifier|*
name|context
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|abort_message
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|system_gimprc
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|user_gimprc
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|session_name
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|batch_interpreter
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
init|=
name|NULL
decl_stmt|;
name|gboolean
name|fatal_warnings
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|no_interface
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|no_data
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|no_fonts
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|no_splash
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|be_verbose
init|=
name|FALSE
decl_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|USE_SYSV_SHM
argument_list|)
operator|||
name|defined
argument_list|(
name|USE_POSIX_SHM
argument_list|)
operator|||
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
name|gboolean
name|use_shm
init|=
name|TRUE
decl_stmt|;
else|#
directive|else
name|gboolean
name|use_shm
init|=
name|FALSE
decl_stmt|;
endif|#
directive|endif
name|gboolean
name|use_cpu_accel
init|=
name|TRUE
decl_stmt|;
name|gboolean
name|console_messages
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|use_debug_handler
init|=
name|FALSE
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
specifier|const
name|GOptionEntry
name|main_entries
index|[]
init|=
block|{
block|{
literal|"version"
block|,
literal|'v'
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
operator|(
name|GOptionArgFunc
operator|)
name|gimp_show_version
block|,
name|N_
argument_list|(
literal|"Show version information and exit."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"verbose"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|be_verbose
block|,
name|N_
argument_list|(
literal|"Be more verbose."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"no-interface"
block|,
literal|'i'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|no_interface
block|,
name|N_
argument_list|(
literal|"Run without a user interface."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"no-data"
block|,
literal|'d'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|no_data
block|,
name|N_
argument_list|(
literal|"Do not load brushes, gradients, palettes, patterns."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"no-fonts"
block|,
literal|'f'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|no_fonts
block|,
name|N_
argument_list|(
literal|"Do not load any fonts."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"no-splash"
block|,
literal|'s'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|no_splash
block|,
name|N_
argument_list|(
literal|"Do not show a startup window."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"no-shm"
block|,
literal|0
block|,
name|G_OPTION_FLAG_REVERSE
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|use_shm
block|,
name|N_
argument_list|(
literal|"Do not use shared memory between GIMP and plugins."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"no-cpu-accel"
block|,
literal|0
block|,
name|G_OPTION_FLAG_REVERSE
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|use_cpu_accel
block|,
name|N_
argument_list|(
literal|"Do not use special CPU acceleration functions."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"session"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_FILENAME
block|,
operator|&
name|session_name
block|,
name|N_
argument_list|(
literal|"Use an alternate sessionrc file."
argument_list|)
block|,
literal|"<name>"
block|}
block|,
block|{
literal|"gimprc"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_FILENAME
block|,
operator|&
name|user_gimprc
block|,
name|N_
argument_list|(
literal|"Use an alternate user gimprc file."
argument_list|)
block|,
literal|"<filename>"
block|}
block|,
block|{
literal|"system-gimprc"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_FILENAME
block|,
operator|&
name|system_gimprc
block|,
name|N_
argument_list|(
literal|"Use an alternate system gimprc file."
argument_list|)
block|,
literal|"<filename>"
block|}
block|,
block|{
literal|"batch"
block|,
literal|'b'
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING_ARRAY
block|,
operator|&
name|batch_commands
block|,
name|N_
argument_list|(
literal|"Batch command to run (can be used multiple times)."
argument_list|)
block|,
literal|"<command>"
block|}
block|,
block|{
literal|"batch-interpreter"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_STRING
block|,
operator|&
name|batch_interpreter
block|,
name|N_
argument_list|(
literal|"The procedure to process batch commands with."
argument_list|)
block|,
literal|"<procedure>"
block|}
block|,
block|{
literal|"console-messages"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|console_messages
block|,
name|N_
argument_list|(
literal|"Send messages to console instead of using a dialog box."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"pdb-compat-mode"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|gimp_option_pdb_compat_mode
block|,
name|N_
argument_list|(
literal|"Procedural Database compatibility mode."
argument_list|)
block|,
literal|"<never | query | always>"
block|}
block|,
block|{
literal|"stack-trace-mode"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|gimp_option_stack_trace_mode
block|,
name|N_
argument_list|(
literal|"Debugging mode for fatal signals."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"debug-handlers"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|use_debug_handler
block|,
name|N_
argument_list|(
literal|"Enable non-fatal debugging signal handlers."
argument_list|)
block|,
name|NULL
block|}
block|,
comment|/*  GTK+ also looks for --g-fatal-warnings, but we want it for        *  non-interactive use also.        */
block|{
literal|"g-fatal-warnings"
block|,
literal|0
block|,
name|G_OPTION_FLAG_HIDDEN
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|fatal_warnings
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"dump-gimprc"
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|gimp_option_dump_gimprc
block|,
name|N_
argument_list|(
literal|"Output a gimprc file with default settings."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"dump-gimprc-system"
block|,
literal|0
block|,
name|G_OPTION_FLAG_HIDDEN
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|gimp_option_dump_gimprc
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
literal|"dump-gimprc-manpage"
block|,
literal|0
block|,
name|G_OPTION_FLAG_HIDDEN
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|gimp_option_dump_gimprc
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|}
block|}
decl_stmt|;
specifier|const
name|GOptionEntry
name|pre_entries
index|[]
init|=
block|{
block|{
literal|"no-interface"
block|,
literal|'i'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|no_interface
block|,
name|N_
argument_list|(
literal|"Run without a user interface."
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|NULL
block|}
block|}
decl_stmt|;
if|#
directive|if
literal|0
block|g_mem_set_vtable (glib_mem_profiler_table);   g_atexit (g_mem_profile);
endif|#
directive|endif
ifdef|#
directive|ifdef
name|__GLIBC__
comment|/* Tweak memory allocation so that memory allocated in chunks>= 4k    * (64x64 pixel 1bpp tile) gets returned to the system when free'd ().    */
name|mallopt
argument_list|(
name|M_MMAP_THRESHOLD
argument_list|,
literal|64
operator|*
literal|64
operator|-
literal|1
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* Initialize i18n support */
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|bindtextdomain
argument_list|(
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|,
name|gimp_locale_directory
argument_list|()
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_BIND_TEXTDOMAIN_CODESET
name|bind_textdomain_codeset
argument_list|(
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|bindtextdomain
argument_list|(
name|GETTEXT_PACKAGE
argument_list|,
name|gimp_locale_directory
argument_list|()
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_BIND_TEXTDOMAIN_CODESET
name|bind_textdomain_codeset
argument_list|(
name|GETTEXT_PACKAGE
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|textdomain
argument_list|(
name|GETTEXT_PACKAGE
argument_list|)
expr_stmt|;
comment|/* set the application name */
name|g_set_application_name
argument_list|(
name|_
argument_list|(
literal|"The GIMP"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Check argv[] for "--no-interface" before trying to initialize gtk+. */
name|context
operator|=
name|g_option_context_new
argument_list|(
literal|"[FILE ...]"
argument_list|)
expr_stmt|;
name|g_option_context_add_main_entries
argument_list|(
name|context
argument_list|,
name|pre_entries
argument_list|,
name|GETTEXT_PACKAGE
argument_list|)
expr_stmt|;
name|g_option_context_set_help_enabled
argument_list|(
name|context
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_option_context_set_ignore_unknown_options
argument_list|(
name|context
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_option_context_parse
argument_list|(
name|context
argument_list|,
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_option_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
comment|/* initialize some libraries (depending on the --no-interface option) */
if|if
condition|(
operator|!
name|app_libs_init
argument_list|(
operator|&
name|no_interface
argument_list|,
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
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
literal|"GIMP could not initialize the graphical user interface.\n"
literal|"Make sure a proper setup for your display environment exists."
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%s\n\n"
argument_list|,
name|msg
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
comment|/* do some sanity checks */
name|abort_message
operator|=
name|sanity_check
argument_list|()
expr_stmt|;
if|if
condition|(
name|abort_message
condition|)
name|app_abort
argument_list|(
name|no_interface
argument_list|,
name|abort_message
argument_list|)
expr_stmt|;
comment|/* parse the command-line options */
name|context
operator|=
name|g_option_context_new
argument_list|(
literal|"[FILE ...]"
argument_list|)
expr_stmt|;
name|g_option_context_add_main_entries
argument_list|(
name|context
argument_list|,
name|main_entries
argument_list|,
name|GETTEXT_PACKAGE
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: add this code as soon as we depend on gtk+-2.6
endif|#
directive|endif
comment|/* g_option_context_add_group (context, gtk_get_option_group (TRUE));    */
if|if
condition|(
operator|!
name|g_option_context_parse
argument_list|(
name|context
argument_list|,
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
ifndef|#
directive|ifndef
name|G_OS_WIN32
comment|/* No use catching these on Win32, the user won't get any    * stack trace from glib anyhow. It's better to let Windows inform    * about the program error, and offer debugging (if the user    * has installed MSVC or some other compiler that knows how to    * install itself as a handler for program errors).    */
comment|/* Handle fatal signals */
comment|/* these are handled by gimp_terminate() */
name|gimp_signal_private
argument_list|(
name|SIGHUP
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGINT
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGQUIT
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGABRT
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGTERM
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|stack_trace_mode
operator|!=
name|GIMP_STACK_TRACE_NEVER
condition|)
block|{
comment|/* these are handled by gimp_fatal_error() */
name|gimp_signal_private
argument_list|(
name|SIGBUS
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGSEGV
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_signal_private
argument_list|(
name|SIGFPE
argument_list|,
name|gimp_sigfatal_handler
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
comment|/* Ignore SIGPIPE because plug_in.c handles broken pipes */
name|gimp_signal_private
argument_list|(
name|SIGPIPE
argument_list|,
name|SIG_IGN
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Collect dead children */
name|gimp_signal_private
argument_list|(
name|SIGCHLD
argument_list|,
name|gimp_sigchld_handler
argument_list|,
name|SA_RESTART
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* G_OS_WIN32 */
if|if
condition|(
name|fatal_warnings
condition|)
block|{
name|GLogLevelFlags
name|fatal_mask
decl_stmt|;
name|fatal_mask
operator|=
name|g_log_set_always_fatal
argument_list|(
name|G_LOG_FATAL_MASK
argument_list|)
expr_stmt|;
name|fatal_mask
operator||=
name|G_LOG_LEVEL_WARNING
operator||
name|G_LOG_LEVEL_CRITICAL
expr_stmt|;
name|g_log_set_always_fatal
argument_list|(
name|fatal_mask
argument_list|)
expr_stmt|;
block|}
name|gimp_errors_init
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
name|use_debug_handler
argument_list|,
name|stack_trace_mode
argument_list|)
expr_stmt|;
name|app_run
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
name|argc
operator|-
literal|1
argument_list|,
name|argv
operator|+
literal|1
argument_list|,
name|system_gimprc
argument_list|,
name|user_gimprc
argument_list|,
name|session_name
argument_list|,
name|batch_interpreter
argument_list|,
name|batch_commands
argument_list|,
name|no_interface
argument_list|,
name|no_data
argument_list|,
name|no_fonts
argument_list|,
name|no_splash
argument_list|,
name|be_verbose
argument_list|,
name|use_shm
argument_list|,
name|use_cpu_accel
argument_list|,
name|console_messages
argument_list|,
name|stack_trace_mode
argument_list|,
name|pdb_compat_mode
argument_list|)
expr_stmt|;
name|g_option_context_free
argument_list|(
name|context
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_option_stack_trace_mode (const gchar * option_name,const gchar * value,gpointer data,GError ** error)
name|gimp_option_stack_trace_mode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"never"
argument_list|)
operator|==
literal|0
condition|)
name|stack_trace_mode
operator|=
name|GIMP_STACK_TRACE_NEVER
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"query"
argument_list|)
operator|==
literal|0
condition|)
name|stack_trace_mode
operator|=
name|GIMP_STACK_TRACE_QUERY
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"always"
argument_list|)
operator|==
literal|0
condition|)
name|stack_trace_mode
operator|=
name|GIMP_STACK_TRACE_ALWAYS
expr_stmt|;
else|else
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_option_pdb_compat_mode (const gchar * option_name,const gchar * value,gpointer data,GError ** error)
name|gimp_option_pdb_compat_mode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"off"
argument_list|)
condition|)
name|pdb_compat_mode
operator|=
name|GIMP_PDB_COMPAT_OFF
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"on"
argument_list|)
condition|)
name|pdb_compat_mode
operator|=
name|GIMP_PDB_COMPAT_ON
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|value
argument_list|,
literal|"warn"
argument_list|)
condition|)
name|pdb_compat_mode
operator|=
name|GIMP_PDB_COMPAT_WARN
expr_stmt|;
else|else
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_option_dump_gimprc (const gchar * option_name,const gchar * value,gpointer data,GError ** error)
name|gimp_option_dump_gimprc
parameter_list|(
specifier|const
name|gchar
modifier|*
name|option_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpConfigDumpFormat
name|format
init|=
name|GIMP_CONFIG_DUMP_NONE
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|option_name
argument_list|,
literal|"--dump-gimprc"
argument_list|)
operator|==
literal|0
condition|)
name|format
operator|=
name|GIMP_CONFIG_DUMP_GIMPRC
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|option_name
argument_list|,
literal|"--dump-gimprc-system"
argument_list|)
operator|==
literal|0
condition|)
name|format
operator|=
name|GIMP_CONFIG_DUMP_GIMPRC_SYSTEM
expr_stmt|;
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|option_name
argument_list|,
literal|"--dump-gimprc-manpage"
argument_list|)
operator|==
literal|0
condition|)
name|format
operator|=
name|GIMP_CONFIG_DUMP_GIMPRC_MANPAGE
expr_stmt|;
if|if
condition|(
name|format
condition|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|gimp
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GIMP
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|units_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_dump
argument_list|(
name|format
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
name|success
condition|?
name|EXIT_SUCCESS
else|:
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_show_version (void)
name|gimp_show_version
parameter_list|(
name|void
parameter_list|)
block|{
name|g_print
argument_list|(
name|_
argument_list|(
literal|"GIMP version %s"
argument_list|)
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_comment
comment|/* In case we build this as a windowed application */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_ifndef
ifndef|#
directive|ifndef
name|_stdcall
end_ifndef

begin_define
DECL|macro|_stdcall
define|#
directive|define
name|_stdcall
value|__attribute__((stdcall))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|int
name|_stdcall
DECL|function|WinMain (struct HINSTANCE__ * hInstance,struct HINSTANCE__ * hPrevInstance,char * lpszCmdLine,int nCmdShow)
name|WinMain
parameter_list|(
name|struct
name|HINSTANCE__
modifier|*
name|hInstance
parameter_list|,
name|struct
name|HINSTANCE__
modifier|*
name|hPrevInstance
parameter_list|,
name|char
modifier|*
name|lpszCmdLine
parameter_list|,
name|int
name|nCmdShow
parameter_list|)
block|{
return|return
name|main
argument_list|(
name|__argc
argument_list|,
name|__argv
argument_list|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* G_OS_WIN32 */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|G_OS_WIN32
end_ifndef

begin_comment
comment|/* gimp core signal handler for fatal signals */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_sigfatal_handler (gint sig_num)
name|gimp_sigfatal_handler
parameter_list|(
name|gint
name|sig_num
parameter_list|)
block|{
switch|switch
condition|(
name|sig_num
condition|)
block|{
case|case
name|SIGHUP
case|:
case|case
name|SIGINT
case|:
case|case
name|SIGQUIT
case|:
case|case
name|SIGABRT
case|:
case|case
name|SIGTERM
case|:
name|gimp_terminate
argument_list|(
name|g_strsignal
argument_list|(
name|sig_num
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGBUS
case|:
case|case
name|SIGSEGV
case|:
case|case
name|SIGFPE
case|:
default|default:
name|gimp_fatal_error
argument_list|(
name|g_strsignal
argument_list|(
name|sig_num
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/* gimp core signal handler for death-of-child signals */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_sigchld_handler (gint sig_num)
name|gimp_sigchld_handler
parameter_list|(
name|gint
name|sig_num
parameter_list|)
block|{
name|gint
name|pid
decl_stmt|;
name|gint
name|status
decl_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
name|pid
operator|=
name|waitpid
argument_list|(
name|WAIT_ANY
argument_list|,
operator|&
name|status
argument_list|,
name|WNOHANG
argument_list|)
expr_stmt|;
if|if
condition|(
name|pid
operator|<=
literal|0
condition|)
break|break;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! G_OS_WIN32 */
end_comment

end_unit

