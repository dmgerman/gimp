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

begin_else
else|#
directive|else
end_else

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
name|void
name|gimp_show_version
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_show_help
parameter_list|(
specifier|const
name|gchar
modifier|*
name|progname
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
name|full_prog_name
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|alternate_system_gimprc
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|alternate_gimprc
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
name|show_help
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
name|gboolean
name|use_shm
init|=
name|FALSE
decl_stmt|;
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
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|GimpStackTraceMode
name|stack_trace_mode
init|=
name|GIMP_STACK_TRACE_QUERY
decl_stmt|;
name|GimpPDBCompatMode
name|pdb_compat_mode
init|=
name|GIMP_PDB_COMPAT_WARN
decl_stmt|;
else|#
directive|else
name|GimpStackTraceMode
name|stack_trace_mode
init|=
name|GIMP_STACK_TRACE_NEVER
decl_stmt|;
name|GimpPDBCompatMode
name|pdb_compat_mode
init|=
name|GIMP_PDB_COMPAT_ON
decl_stmt|;
endif|#
directive|endif
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
if|#
directive|if
literal|0
block|g_mem_set_vtable (glib_mem_profiler_table);   g_atexit (g_mem_profile);
endif|#
directive|endif
comment|/* Initialize variables */
name|full_prog_name
operator|=
name|argv
index|[
literal|0
index|]
expr_stmt|;
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
comment|/* Check argv[] for "--no-interface" before trying to initialize gtk+.    * We also check for "--help" or "--version" here since those shouldn't    * require gui libs either.    */
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
name|gimp_show_version
argument_list|()
expr_stmt|;
name|app_exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
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
literal|"-h"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|gimp_show_help
argument_list|(
name|full_prog_name
argument_list|)
expr_stmt|;
name|app_exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|arg
argument_list|,
literal|"--dump-gimprc"
argument_list|,
literal|13
argument_list|)
operator|==
literal|0
condition|)
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
name|arg
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
name|arg
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
name|arg
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
name|g_type_init
argument_list|()
expr_stmt|;
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
block|}
block|}
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
name|g_set_application_name
argument_list|(
name|_
argument_list|(
literal|"The GIMP"
argument_list|)
argument_list|)
expr_stmt|;
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
name|use_shm
operator|=
name|TRUE
expr_stmt|;
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
name|batch_commands
operator|=
name|g_new
argument_list|(
specifier|const
name|gchar
operator|*
argument_list|,
name|argc
argument_list|)
expr_stmt|;
name|batch_commands
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
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
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--g-fatal-warnings"
argument_list|)
operator|==
literal|0
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
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
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
name|argv
index|[
name|i
index|]
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
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--batch-interpreter"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|argc
operator|<=
operator|++
name|i
condition|)
block|{
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|batch_interpreter
operator|=
name|argv
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--batch"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"-b"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
operator|,
name|i
operator|++
init|;
name|i
operator|<
name|argc
condition|;
name|j
operator|++
operator|,
name|i
operator|++
control|)
block|{
name|batch_commands
index|[
name|j
index|]
operator|=
name|argv
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
name|batch_commands
index|[
name|j
index|]
operator|=
name|NULL
expr_stmt|;
comment|/* We need at least one batch command */
if|if
condition|(
name|batch_commands
index|[
literal|0
index|]
operator|==
name|NULL
condition|)
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--system-gimprc"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|argc
operator|<=
operator|++
name|i
condition|)
block|{
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|alternate_system_gimprc
operator|=
name|argv
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--gimprc"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"-g"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|argc
operator|<=
operator|++
name|i
condition|)
block|{
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|alternate_gimprc
operator|=
name|argv
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--no-data"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"-d"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|no_data
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--no-fonts"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"-f"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|no_fonts
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--no-splash"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"-s"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|no_splash
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--verbose"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|be_verbose
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--no-shm"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|use_shm
operator|=
name|FALSE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--no-cpu-accel"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|use_cpu_accel
operator|=
name|FALSE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--debug-handlers"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|use_debug_handler
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--console-messages"
argument_list|)
operator|==
literal|0
operator|)
operator|||
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"-c"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|console_messages
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--session"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|argc
operator|<=
operator|++
name|i
condition|)
block|{
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|session_name
operator|=
name|argv
index|[
name|i
index|]
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--stack-trace-mode"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|argc
operator|<=
operator|++
name|i
condition|)
block|{
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"never"
argument_list|)
condition|)
name|stack_trace_mode
operator|=
name|GIMP_STACK_TRACE_NEVER
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"query"
argument_list|)
condition|)
name|stack_trace_mode
operator|=
name|GIMP_STACK_TRACE_QUERY
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"always"
argument_list|)
condition|)
name|stack_trace_mode
operator|=
name|GIMP_STACK_TRACE_ALWAYS
expr_stmt|;
else|else
name|show_help
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--pdb-compat-mode"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|argc
operator|<=
operator|++
name|i
condition|)
block|{
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
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
name|argv
index|[
name|i
index|]
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
name|argv
index|[
name|i
index|]
argument_list|,
literal|"warn"
argument_list|)
condition|)
name|pdb_compat_mode
operator|=
name|GIMP_PDB_COMPAT_WARN
expr_stmt|;
else|else
name|show_help
operator|=
name|TRUE
expr_stmt|;
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*            *  everything after "--" is a parameter (i.e. image to load)            */
name|argv
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
elseif|else
if|if
condition|(
name|argv
index|[
name|i
index|]
index|[
literal|0
index|]
operator|==
literal|'-'
condition|)
block|{
comment|/*            *  anything else starting with a '-' is an error.            */
name|g_print
argument_list|(
name|_
argument_list|(
literal|"\nInvalid option \"%s\"\n"
argument_list|)
argument_list|,
name|argv
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|show_help
condition|)
block|{
name|gimp_show_help
argument_list|(
name|full_prog_name
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
name|gimp_errors_init
argument_list|(
name|full_prog_name
argument_list|,
name|use_debug_handler
argument_list|,
name|stack_trace_mode
argument_list|)
expr_stmt|;
name|app_run
argument_list|(
name|full_prog_name
argument_list|,
name|argc
operator|-
literal|1
argument_list|,
name|argv
operator|+
literal|1
argument_list|,
name|alternate_system_gimprc
argument_list|,
name|alternate_gimprc
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
name|g_free
argument_list|(
name|batch_commands
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
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
literal|"%s %s\n"
argument_list|,
name|_
argument_list|(
literal|"GIMP version"
argument_list|)
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_show_help (const gchar * progname)
name|gimp_show_help
parameter_list|(
specifier|const
name|gchar
modifier|*
name|progname
parameter_list|)
block|{
name|gimp_show_version
argument_list|()
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"\nUsage: %s [option ... ] [file ... ]\n\n"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|progname
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Options:\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -h, --help               Output this help.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -v, --version            Output version information.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --verbose                Show startup messages.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --no-shm                 Do not use shared memory between GIMP and plugins.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --no-cpu-accel           Do not use special CPU accelerations.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -d, --no-data            Do not load brushes, gradients, palettes, patterns.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -f, --no-fonts           Do not load any fonts.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -i, --no-interface       Run without a user interface.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --display<display>      Use the designated X display.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -s, --no-splash          Do not show the startup window.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --session<name>         Use an alternate sessionrc file.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -g, --gimprc<gimprc>    Use an alternate gimprc file.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --system-gimprc<gimprc> Use an alternate system gimprc file.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --dump-gimprc            Output a gimprc file with default settings.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -c, --console-messages   Display warnings to console instead of a dialog box.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --debug-handlers         Enable non-fatal debugging signal handlers.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --stack-trace-mode<never | query | always>\n"
literal|"                           Debugging mode for fatal signals.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --pdb-compat-mode<off | on | warn>\n"
literal|"                           Procedural Database compatibility mode.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  --batch-interpreter<procedure>\n"
literal|"                           The procedure to process batch commands with.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"  -b, --batch<commands>   Process commands in batch mode.\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
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

