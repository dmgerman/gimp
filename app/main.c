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
file|"gui/gui.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
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
file|"libgimp/gimpintl.h"
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

begin_function_decl
specifier|static
name|void
name|gimp_sigfatal_handler
parameter_list|(
name|gint
name|sig_num
parameter_list|)
function_decl|;
end_function_decl

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

begin_comment
comment|/*  command line options  */
end_comment

begin_decl_stmt
DECL|variable|no_interface
name|gboolean
name|no_interface
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_data
name|gboolean
name|no_data
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_splash
name|gboolean
name|no_splash
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_splash_image
name|gboolean
name|no_splash_image
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|be_verbose
name|gboolean
name|be_verbose
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_shm
name|gboolean
name|use_shm
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_debug_handler
name|gboolean
name|use_debug_handler
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|console_messages
name|gboolean
name|console_messages
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|restore_session
name|gboolean
name|restore_session
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_mmx
name|gboolean
name|use_mmx
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|stack_trace_mode
name|GimpStackTraceMode
name|stack_trace_mode
init|=
name|GIMP_STACK_TRACE_QUERY
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|alternate_gimprc
name|gchar
modifier|*
name|alternate_gimprc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|alternate_system_gimprc
name|gchar
modifier|*
name|alternate_system_gimprc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|batch_cmds
name|gchar
modifier|*
modifier|*
name|batch_cmds
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  other global variables  */
end_comment

begin_decl_stmt
DECL|variable|prog_name
name|gchar
modifier|*
name|prog_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|prog_name
comment|/* our executable name */
end_comment

begin_comment
comment|/*  *  argv processing:   *      Arguments are either switches, their associated  *      values, or image files.  As switches and their  *      associated values are processed, those slots in  *      the argv[] array are NULLed. We do this because  *      unparsed args are treated as images to load on  *      startup.  *  *      The GTK switches are processed first (X switches are  *      processed here, not by any X routines).  Then the  *      general GIMP switches are processed.  Any args  *      left are assumed to be image files the GIMP should  *      display.  *  *      The exception is the batch switch.  When this is  *      encountered, all remaining args are treated as batch  *      commands.  */
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
name|gboolean
name|show_version
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|show_help
init|=
name|FALSE
decl_stmt|;
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
name|prog_name
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
name|bind_textdomain_codeset
argument_list|(
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
name|bindtextdomain
argument_list|(
name|GETTEXT_PACKAGE
argument_list|,
name|gimp_locale_directory
argument_list|()
argument_list|)
expr_stmt|;
name|bind_textdomain_codeset
argument_list|(
name|GETTEXT_PACKAGE
argument_list|,
literal|"UTF-8"
argument_list|)
expr_stmt|;
name|textdomain
argument_list|(
name|GETTEXT_PACKAGE
argument_list|)
expr_stmt|;
comment|/*  check argv[] for "--no-interface" before trying to initialize gtk+  */
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
block|}
block|}
if|if
condition|(
name|no_interface
condition|)
block|{
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|gui_libs_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
name|defined
argument_list|(
name|HAVE_SHM_H
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
name|batch_cmds
operator|=
name|g_new
argument_list|(
name|char
operator|*
argument_list|,
name|argc
argument_list|)
expr_stmt|;
name|batch_cmds
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
name|batch_cmds
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
name|batch_cmds
index|[
name|j
index|]
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|batch_cmds
index|[
literal|0
index|]
operator|==
name|NULL
condition|)
comment|/* We need at least one batch command */
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
literal|"--help"
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
literal|"-h"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
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
literal|"--version"
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
literal|"-v"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|show_version
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
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--no-splash-image"
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
literal|"-S"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|no_splash_image
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
literal|"--no-mmx"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|use_mmx
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
operator|(
name|strcmp
argument_list|(
name|argv
index|[
name|i
index|]
argument_list|,
literal|"--restore-session"
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
literal|"-r"
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|restore_session
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
literal|"--enable-stack-trace"
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
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* Common windoze apps don't have a console at all. So does Gimp     * - if appropiate. This allows to compile as console application    * with all it's benfits (like inheriting the console) but hide    * it, if the user doesn't want it.    */
if|if
condition|(
operator|!
name|show_help
operator|&&
operator|!
name|show_version
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
if|if
condition|(
name|show_version
operator|||
name|show_help
condition|)
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
if|if
condition|(
name|show_help
condition|)
block|{
name|g_print
argument_list|(
name|_
argument_list|(
literal|"\nUsage: %s [option ... ] [file ... ]\n\n"
argument_list|)
argument_list|,
name|argv
index|[
literal|0
index|]
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
literal|"  -b, --batch<commands>   Run in batch mode.\n"
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
literal|"  -d, --no-data            Do not load brushes, gradients, palettes, patterns.\n"
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
literal|"  -g, --gimprc<gimprc>    Use an alternate gimprc file.\n"
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
literal|"  -r, --restore-session    Try to restore saved session.\n"
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
literal|"  -S, --no-splash-image    Do not add an image to the startup window.\n"
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
literal|"  --no-mmx                 Do not use MMX routines.\n"
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
literal|"  --display<display>      Use the designated X display.\n"
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
literal|"  --enable-stack-trace<never | query | always>\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"                           Debugging mode for fatal signals.\n\n"
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|show_version
operator|||
name|show_help
condition|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* Give them time to read the message if it was printed in a        * separate console window. I would really love to have        * some way of asking for confirmation to close the console        * window.        */
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
literal|0
argument_list|)
expr_stmt|;
block|}
name|g_log_set_handler
argument_list|(
literal|"Gimp"
argument_list|,
name|G_LOG_LEVEL_MESSAGE
argument_list|,
name|gimp_message_log_func
argument_list|,
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
comment|/* No use catching these on Win32, the user won't get any     * stack trace from glib anyhow. It's better to let Windows inform    * about the program error, and offer debugging (if the user    * has installed MSVC or some other compiler that knows how to    * install itself as a handler for program errors).    */
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
name|STACK_TRACE_NEVER
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
comment|/* Initialize the application */
name|app_init
argument_list|(
name|argc
operator|-
literal|1
argument_list|,
name|argv
operator|+
literal|1
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
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

