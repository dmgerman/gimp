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
file|<locale.h>
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

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

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

begin_comment
comment|/*  WAIT_ANY  */
end_comment

begin_include
include|#
directive|include
file|"libgimp/gimpfeatures.h"
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
file|"install.h"
end_include

begin_function_decl
specifier|static
name|RETSIGTYPE
name|on_signal
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|RETSIGTYPE
name|on_sig_child
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* GLOBAL data */
end_comment

begin_decl_stmt
DECL|variable|no_interface
name|int
name|no_interface
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_data
name|int
name|no_data
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_splash
name|int
name|no_splash
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|no_splash_image
name|int
name|no_splash_image
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|be_verbose
name|int
name|be_verbose
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_shm
name|int
name|use_shm
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|use_debug_handler
name|int
name|use_debug_handler
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|console_messages
name|int
name|console_messages
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|restore_session
name|int
name|restore_session
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_context
name|GimpSet
modifier|*
name|image_context
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|message_handler
name|MessageHandlerType
name|message_handler
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|prog_name
name|char
modifier|*
name|prog_name
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|prog_name
comment|/* The path name we are invoked with */
end_comment

begin_decl_stmt
DECL|variable|alternate_gimprc
name|char
modifier|*
name|alternate_gimprc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|alternate_system_gimprc
name|char
modifier|*
name|alternate_system_gimprc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|batch_cmds
name|char
modifier|*
modifier|*
name|batch_cmds
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* LOCAL data */
end_comment

begin_decl_stmt
DECL|variable|gimp_argc
specifier|static
name|int
name|gimp_argc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_argv
specifier|static
name|char
modifier|*
modifier|*
name|gimp_argv
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  *  argv processing:   *      Arguments are either switches, their associated  *      values, or image files.  As switches and their  *      associated values are processed, those slots in  *      the argv[] array are NULLed.  *  *      The GTK switches are processed first (X switches are  *      processed here, not by any X routines).  Then the  *      general GIMP switches are processed.  Any args  *      left are assumed to be image files the GIMP should  *      display.  *  *      The exception is the batch switch.  When this is  *      encountered, all remaining args are treated as batch  *      commands.  */
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
name|int
name|show_version
decl_stmt|;
name|int
name|show_help
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gchar
modifier|*
name|display_name
decl_stmt|,
modifier|*
name|display_env
decl_stmt|;
name|atexit
argument_list|(
name|g_mem_profile
argument_list|)
expr_stmt|;
comment|/* Initialize variables */
name|prog_name
operator|=
name|argv
index|[
literal|0
index|]
expr_stmt|;
comment|/* Initialize Gtk toolkit */
name|gtk_set_locale
argument_list|()
expr_stmt|;
name|setlocale
argument_list|(
name|LC_NUMERIC
argument_list|,
literal|"C"
argument_list|)
expr_stmt|;
comment|/* must use dot, not comma, as decimal separator */
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_LIBGLE
name|gle_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* !HAVE_LIBGLE */
name|display_name
operator|=
name|gdk_get_display
argument_list|()
expr_stmt|;
name|display_env
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|strlen
argument_list|(
name|display_name
argument_list|)
operator|+
literal|9
argument_list|)
expr_stmt|;
operator|*
name|display_env
operator|=
literal|0
expr_stmt|;
name|strcat
argument_list|(
name|display_env
argument_list|,
literal|"DISPLAY="
argument_list|)
expr_stmt|;
name|strcat
argument_list|(
name|display_env
argument_list|,
name|display_name
argument_list|)
expr_stmt|;
name|putenv
argument_list|(
name|display_env
argument_list|)
expr_stmt|;
name|no_interface
operator|=
name|FALSE
expr_stmt|;
name|no_data
operator|=
name|FALSE
expr_stmt|;
name|no_splash
operator|=
name|FALSE
expr_stmt|;
name|no_splash_image
operator|=
name|FALSE
expr_stmt|;
name|use_shm
operator|=
name|TRUE
expr_stmt|;
name|use_debug_handler
operator|=
name|FALSE
expr_stmt|;
name|restore_session
operator|=
name|FALSE
expr_stmt|;
name|console_messages
operator|=
name|FALSE
expr_stmt|;
name|message_handler
operator|=
name|CONSOLE
expr_stmt|;
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
name|alternate_gimprc
operator|=
name|NULL
expr_stmt|;
name|alternate_system_gimprc
operator|=
name|NULL
expr_stmt|;
name|show_version
operator|=
name|FALSE
expr_stmt|;
name|show_help
operator|=
name|FALSE
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
literal|"-n"
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
operator|&&
name|argv
index|[
name|i
index|]
index|[
literal|0
index|]
operator|!=
literal|'-'
condition|;
name|j
operator|++
operator|,
name|i
operator|++
control|)
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
if|if
condition|(
name|argv
index|[
name|i
operator|-
literal|1
index|]
index|[
literal|0
index|]
operator|!=
literal|'-'
condition|)
comment|/* Did loop end due to a new argument? */
operator|--
name|i
expr_stmt|;
comment|/* Ensure new argument gets processed */
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
literal|"--version"
argument_list|)
operator|==
literal|0
operator|||
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
condition|)
block|{
name|show_version
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
literal|"--no-data"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|no_data
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
literal|"--no-splash"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|no_splash
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
literal|"--no-splash-image"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|no_splash_image
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
literal|"--console-messages"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|console_messages
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
block|}
comment|/*  *    ANYTHING ELSE starting with a '-' is an error.  */
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
name|show_help
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|show_version
condition|)
name|g_print
argument_list|(
literal|"GIMP version "
name|GIMP_VERSION
literal|"\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_help
condition|)
block|{
name|g_print
argument_list|(
literal|"\007Usage: %s [option ...] [files ...]\n"
argument_list|,
name|argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"Valid options are:\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  -h --help                Output this help.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  -v --version             Output version info.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  -b --batch<commands>    Run in batch mode.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  -g --gimprc<gimprc>     Use an alternate gimprc file.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  -n --no-interface        Run without a user interface.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  -r --restore-session     Try to restore saved session.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --no-data                Do not load patterns, gradients, palettes, brushes.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --verbose                Show startup messages.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --no-splash              Do not show the startup window.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --no-splash-image        Do not add an image to the startup window.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --no-shm                 Do not use shared memory between GIMP and its plugins.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --no-xshm                Do not use the X Shared Memory extension.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --console-messages       Display warnings to console instead of a dialog box.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --debug-handlers         Enable debugging signal handlers.\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --display<display>      Use the designated X display.\n\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"  --system-gimprc<gimprc> Use an alternate system gimprc file.\n"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|show_version
operator|||
name|show_help
condition|)
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
name|g_set_message_handler
argument_list|(
operator|&
name|message_func
argument_list|)
expr_stmt|;
comment|/* Handle some signals */
name|signal
argument_list|(
name|SIGHUP
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGINT
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGQUIT
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGABRT
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGBUS
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGSEGV
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGPIPE
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGTERM
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
name|signal
argument_list|(
name|SIGFPE
argument_list|,
name|on_signal
argument_list|)
expr_stmt|;
comment|/* Handle child exits */
name|signal
argument_list|(
name|SIGCHLD
argument_list|,
name|on_sig_child
argument_list|)
expr_stmt|;
comment|/* Keep the command line arguments--for use in gimp_init */
name|gimp_argc
operator|=
name|argc
operator|-
literal|1
expr_stmt|;
name|gimp_argv
operator|=
name|argv
operator|+
literal|1
expr_stmt|;
comment|/* Check the installation */
name|install_verify
argument_list|(
name|init
argument_list|)
expr_stmt|;
comment|/* Main application loop */
if|if
condition|(
operator|!
name|app_exit_finish_done
argument_list|()
condition|)
name|gtk_main
argument_list|()
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|init ()
name|init
parameter_list|()
block|{
comment|/*  Continue initializing  */
name|gimp_init
argument_list|(
name|gimp_argc
argument_list|,
name|gimp_argv
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|caught_fatal_sig
specifier|static
name|int
name|caught_fatal_sig
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|RETSIGTYPE
DECL|function|on_signal (int sig_num)
name|on_signal
parameter_list|(
name|int
name|sig_num
parameter_list|)
block|{
if|if
condition|(
name|caught_fatal_sig
condition|)
comment|/*    raise (sig_num);*/
name|kill
argument_list|(
name|getpid
argument_list|()
argument_list|,
name|sig_num
argument_list|)
expr_stmt|;
name|caught_fatal_sig
operator|=
literal|1
expr_stmt|;
switch|switch
condition|(
name|sig_num
condition|)
block|{
case|case
name|SIGHUP
case|:
name|terminate
argument_list|(
literal|"sighup caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGINT
case|:
name|terminate
argument_list|(
literal|"sigint caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGQUIT
case|:
name|terminate
argument_list|(
literal|"sigquit caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGABRT
case|:
name|terminate
argument_list|(
literal|"sigabrt caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGBUS
case|:
name|fatal_error
argument_list|(
literal|"sigbus caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGSEGV
case|:
name|fatal_error
argument_list|(
literal|"sigsegv caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGPIPE
case|:
name|terminate
argument_list|(
literal|"sigpipe caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGTERM
case|:
name|terminate
argument_list|(
literal|"sigterm caught"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SIGFPE
case|:
name|fatal_error
argument_list|(
literal|"sigfpe caught"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|fatal_error
argument_list|(
literal|"unknown signal"
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|RETSIGTYPE
DECL|function|on_sig_child (int sig_num)
name|on_sig_child
parameter_list|(
name|int
name|sig_num
parameter_list|)
block|{
name|int
name|pid
decl_stmt|;
name|int
name|status
decl_stmt|;
while|while
condition|(
literal|1
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

end_unit

