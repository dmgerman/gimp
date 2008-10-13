begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_comment
comment|/* get_osfhandle */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_include
include|#
directive|include
file|<gdk/gdk.h>
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/tile.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-dump.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"about.h"
end_include

begin_include
include|#
directive|include
file|"app.h"
end_include

begin_include
include|#
directive|include
file|"sanity.h"
end_include

begin_include
include|#
directive|include
file|"signals.h"
end_include

begin_include
include|#
directive|include
file|"unique.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
end_include

begin_include
include|#
directive|include
file|"version.h"
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
file|<conio.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_function_decl
specifier|static
name|gboolean
name|gimp_option_fatal_warnings
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

begin_decl_stmt
specifier|static
name|void
name|gimp_show_version_and_exit
argument_list|(
name|void
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|static
name|void
name|gimp_show_license_and_exit
argument_list|(
name|void
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|gimp_init_i18n
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_init_malloc
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

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

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_CONSOLE_COMPILATION
argument_list|)
end_if

begin_function_decl
specifier|static
name|void
name|gimp_open_console_window
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|gimp_open_console_window ()
define|#
directive|define
name|gimp_open_console_window
parameter_list|()
end_define

begin_comment
DECL|macro|gimp_open_console_window ()
comment|/* as nothing */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|system_gimprc
specifier|static
specifier|const
name|gchar
modifier|*
name|system_gimprc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|user_gimprc
specifier|static
specifier|const
name|gchar
modifier|*
name|user_gimprc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|session_name
specifier|static
specifier|const
name|gchar
modifier|*
name|session_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|batch_interpreter
specifier|static
specifier|const
name|gchar
modifier|*
name|batch_interpreter
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|batch_commands
specifier|static
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|filenames
specifier|static
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|as_new
specifier|static
name|gboolean
name|as_new
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_interface
specifier|static
name|gboolean
name|no_interface
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_data
specifier|static
name|gboolean
name|no_data
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_fonts
specifier|static
name|gboolean
name|no_fonts
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_splash
specifier|static
name|gboolean
name|no_splash
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|be_verbose
specifier|static
name|gboolean
name|be_verbose
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|new_instance
specifier|static
name|gboolean
name|new_instance
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_if
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
end_if

begin_decl_stmt
DECL|variable|use_shm
specifier|static
name|gboolean
name|use_shm
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

begin_decl_stmt
DECL|variable|use_shm
specifier|static
name|gboolean
name|use_shm
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|use_cpu_accel
specifier|static
name|gboolean
name|use_cpu_accel
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|console_messages
specifier|static
name|gboolean
name|console_messages
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_debug_handler
specifier|static
name|gboolean
name|use_debug_handler
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

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

begin_decl_stmt
DECL|variable|main_entries
specifier|static
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
name|G_OPTION_FLAG_NO_ARG
block|,
name|G_OPTION_ARG_CALLBACK
block|,
operator|(
name|GOptionArgFunc
operator|)
name|gimp_show_version_and_exit
block|,
name|N_
argument_list|(
literal|"Show version information and exit"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"license"
block|,
literal|0
block|,
name|G_OPTION_FLAG_NO_ARG
block|,
name|G_OPTION_ARG_CALLBACK
block|,
operator|(
name|GOptionArgFunc
operator|)
name|gimp_show_license_and_exit
block|,
name|N_
argument_list|(
literal|"Show license information and exit"
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
literal|"Be more verbose"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"new-instance"
block|,
literal|'n'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|new_instance
block|,
name|N_
argument_list|(
literal|"Start a new GIMP instance"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"as-new"
block|,
literal|'a'
block|,
literal|0
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|as_new
block|,
name|N_
argument_list|(
literal|"Open images as new"
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
literal|"Run without a user interface"
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
literal|"Do not load brushes, gradients, patterns, ..."
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
literal|"Do not load any fonts"
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
literal|"Do not show a startup window"
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
literal|"Do not use shared memory between GIMP and plugins"
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
literal|"Do not use special CPU acceleration functions"
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
literal|"Use an alternate sessionrc file"
argument_list|)
block|,
literal|"<name>"
block|}
block|,
block|{
literal|"gimprc"
block|,
literal|'g'
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
literal|"Use an alternate user gimprc file"
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
literal|"Use an alternate system gimprc file"
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
literal|"Batch command to run (can be used multiple times)"
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
literal|"The procedure to process batch commands with"
argument_list|)
block|,
literal|"<proc>"
block|}
block|,
block|{
literal|"console-messages"
block|,
literal|'c'
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
literal|"Send messages to console instead of using a dialog"
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
comment|/*  don't translate the mode names (off|on|warn)  */
name|N_
argument_list|(
literal|"PDB compatibility mode (off|on|warn)"
argument_list|)
block|,
literal|"<mode>"
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
comment|/*  don't translate the mode names (never|query|always)  */
name|N_
argument_list|(
literal|"Debug in case of a crash (never|query|always)"
argument_list|)
block|,
literal|"<mode>"
block|}
block|,
block|{
literal|"debug-handlers"
block|,
literal|0
block|,
name|G_OPTION_FLAG_NO_ARG
block|,
name|G_OPTION_ARG_NONE
block|,
operator|&
name|use_debug_handler
block|,
name|N_
argument_list|(
literal|"Enable non-fatal debugging signal handlers"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"g-fatal-warnings"
block|,
literal|0
block|,
name|G_OPTION_FLAG_NO_ARG
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|gimp_option_fatal_warnings
block|,
name|N_
argument_list|(
literal|"Make all warnings fatal"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
literal|"dump-gimprc"
block|,
literal|0
block|,
name|G_OPTION_FLAG_NO_ARG
block|,
name|G_OPTION_ARG_CALLBACK
block|,
name|gimp_option_dump_gimprc
block|,
name|N_
argument_list|(
literal|"Output a gimprc file with default settings"
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
name|G_OPTION_FLAG_NO_ARG
operator||
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
name|G_OPTION_FLAG_NO_ARG
operator||
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
name|G_OPTION_REMAINING
block|,
literal|0
block|,
literal|0
block|,
name|G_OPTION_ARG_FILENAME_ARRAY
block|,
operator|&
name|filenames
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
end_decl_stmt

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
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|abort_message
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|__GNUC__
argument_list|)
operator|&&
name|defined
argument_list|(
name|_WIN64
argument_list|)
comment|/* mingw-w64, at least the unstable build from late July 2008,    * starts subsystem:windows programs in main(), but passes them    * bogus argc and argv. __argc and __argv are OK, though, so just    * use them.    */
name|argc
operator|=
name|__argc
expr_stmt|;
name|argv
operator|=
name|__argv
expr_stmt|;
endif|#
directive|endif
name|g_thread_init
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|gimp_open_console_window
argument_list|()
expr_stmt|;
endif|#
directive|endif
name|gimp_init_malloc
argument_list|()
expr_stmt|;
name|gimp_env_init
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_log_init
argument_list|()
expr_stmt|;
name|gimp_init_i18n
argument_list|()
expr_stmt|;
name|g_set_application_name
argument_list|(
name|GIMP_NAME
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|argv
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
comment|/* Check argv[] for "--verbose" first */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|argc
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|gchar
modifier|*
name|arg
init|=
name|argv
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|arg
index|[
literal|0
index|]
operator|!=
literal|'-'
condition|)
continue|continue;
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--verbose"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-v"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|be_verbose
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
comment|/* Check argv[] for "--no-interface" before trying to initialize gtk+. */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|argc
condition|;
name|i
operator|++
control|)
block|{
specifier|const
name|gchar
modifier|*
name|arg
init|=
name|argv
index|[
name|i
index|]
decl_stmt|;
if|if
condition|(
name|arg
index|[
literal|0
index|]
operator|!=
literal|'-'
condition|)
continue|continue;
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--no-interface"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-i"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|no_interface
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--version"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-v"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|gimp_show_version_and_exit
argument_list|()
expr_stmt|;
block|}
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_CONSOLE_COMPILATION
argument_list|)
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"--help"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|arg
argument_list|,
literal|"-?"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strncmp
argument_list|(
name|arg
argument_list|,
literal|"--help-"
argument_list|,
literal|7
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|gimp_open_console_window
argument_list|()
expr_stmt|;
block|}
endif|#
directive|endif
block|}
ifdef|#
directive|ifdef
name|GIMP_CONSOLE_COMPILATION
name|no_interface
operator|=
name|TRUE
expr_stmt|;
endif|#
directive|endif
name|context
operator|=
name|g_option_context_new
argument_list|(
name|_
argument_list|(
literal|"[FILE|URI...]"
argument_list|)
argument_list|)
expr_stmt|;
name|g_option_context_set_summary
argument_list|(
name|context
argument_list|,
name|GIMP_NAME
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
name|app_libs_init
argument_list|(
name|context
argument_list|,
name|no_interface
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|error
condition|)
block|{
name|gimp_open_console_window
argument_list|()
expr_stmt|;
name|g_print
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
block|}
else|else
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|_
argument_list|(
literal|"GIMP could not initialize the graphical user interface.\n"
literal|"Make sure a proper setup for your display environment "
literal|"exists."
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|app_exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|no_interface
operator|||
name|be_verbose
operator|||
name|console_messages
operator|||
name|batch_commands
operator|!=
name|NULL
condition|)
name|gimp_open_console_window
argument_list|()
expr_stmt|;
if|if
condition|(
name|no_interface
condition|)
name|new_instance
operator|=
name|TRUE
expr_stmt|;
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
operator|!
name|new_instance
operator|&&
name|gimp_unique_open
argument_list|(
name|filenames
argument_list|,
name|as_new
argument_list|)
condition|)
block|{
if|if
condition|(
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|_
argument_list|(
literal|"Another GIMP instance is already running."
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_notify_startup_complete
argument_list|()
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
endif|#
directive|endif
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
name|gimp_init_signal_handlers
argument_list|(
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
name|filenames
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
name|as_new
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
name|use_debug_handler
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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_comment
comment|/* Provide WinMain in case we build GIMP as a subsystem:windows  * application. Well, we do. When built with mingw, though, user code  * execution still starts in main() in that case. So WinMain() gets  * used on MSVC builds only.  */
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

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_function
specifier|static
name|void
DECL|function|wait_console_window (void)
name|wait_console_window
parameter_list|(
name|void
parameter_list|)
block|{
name|FILE
modifier|*
name|console
init|=
name|fopen
argument_list|(
literal|"CONOUT$"
argument_list|,
literal|"w"
argument_list|)
decl_stmt|;
name|SetConsoleTitleW
argument_list|(
name|g_utf8_to_utf16
argument_list|(
name|_
argument_list|(
literal|"GIMP output. Type any character to close this window."
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|console
argument_list|,
name|_
argument_list|(
literal|"(Type any character to close this window)\n"
argument_list|)
argument_list|)
expr_stmt|;
name|fflush
argument_list|(
name|console
argument_list|)
expr_stmt|;
name|_getch
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_open_console_window (void)
name|gimp_open_console_window
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|(
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|stdout
argument_list|)
argument_list|)
operator|==
name|INVALID_HANDLE_VALUE
operator|||
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|stderr
argument_list|)
argument_list|)
operator|==
name|INVALID_HANDLE_VALUE
operator|)
operator|&&
name|AllocConsole
argument_list|()
condition|)
block|{
if|if
condition|(
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|stdout
argument_list|)
argument_list|)
operator|==
name|INVALID_HANDLE_VALUE
condition|)
name|freopen
argument_list|(
literal|"CONOUT$"
argument_list|,
literal|"w"
argument_list|,
name|stdout
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|stderr
argument_list|)
argument_list|)
operator|==
name|INVALID_HANDLE_VALUE
condition|)
name|freopen
argument_list|(
literal|"CONOUT$"
argument_list|,
literal|"w"
argument_list|,
name|stderr
argument_list|)
expr_stmt|;
name|SetConsoleTitleW
argument_list|(
name|g_utf8_to_utf16
argument_list|(
name|_
argument_list|(
literal|"GIMP output. You can minimize this window, but don't close it."
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|atexit
argument_list|(
name|wait_console_window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* G_OS_WIN32 */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_option_fatal_warnings (const gchar * option_name,const gchar * value,gpointer data,GError ** error)
name|gimp_option_fatal_warnings
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
return|return
name|TRUE
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
name|gimp_open_console_window
argument_list|()
expr_stmt|;
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
DECL|function|gimp_show_version_and_exit (void)
name|gimp_show_version_and_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|gimp_open_console_window
argument_list|()
expr_stmt|;
name|gimp_version_show
argument_list|(
name|be_verbose
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_show_license_and_exit (void)
name|gimp_show_license_and_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|gimp_open_console_window
argument_list|()
expr_stmt|;
name|gimp_version_show
argument_list|(
name|be_verbose
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|GIMP_LICENSE
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n\n"
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_init_malloc (void)
name|gimp_init_malloc
parameter_list|(
name|void
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|GIMP_GLIB_MEM_PROFILER
name|g_mem_set_vtable
argument_list|(
name|glib_mem_profiler_table
argument_list|)
expr_stmt|;
name|g_atexit
argument_list|(
name|g_mem_profile
argument_list|)
expr_stmt|;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|__GLIBC__
comment|/* Tweak memory allocation so that memory allocated in chunks>= 4k    * (64x64 pixel 1bpp tile) gets returned to the system when free()'d.    *    * The default value for M_MMAP_THRESHOLD in glibc-2.3 is 128k.    * This is said to be an empirically derived value that works well    * in most systems. Lowering it to 4k is thus probably not the ideal    * solution.    *    * An alternative to tuning this parameter would be to use    * malloc_trim(), for example after releasing a large tile-manager.    */
name|mallopt
argument_list|(
name|M_MMAP_THRESHOLD
argument_list|,
name|TILE_WIDTH
operator|*
name|TILE_HEIGHT
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_init_i18n (void)
name|gimp_init_i18n
parameter_list|(
name|void
parameter_list|)
block|{
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
block|}
end_function

end_unit

