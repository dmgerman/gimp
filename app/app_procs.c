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

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|"tools/tools-types.h"
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
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui.h"
end_include

begin_include
include|#
directive|include
file|"gui/splash.h"
end_include

begin_include
include|#
directive|include
file|"gui/user-install-dialog.h"
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
file|"batch.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|app_init_update_status
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
name|app_exit_finish
parameter_list|(
name|void
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
name|void
DECL|function|app_init (gint gimp_argc,gchar ** gimp_argv)
name|app_init
parameter_list|(
name|gint
name|gimp_argc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|gimp_argv
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|gimp_dir
decl_stmt|;
name|struct
name|stat
name|stat_buf
decl_stmt|;
comment|/*  Create an instance of the "Gimp" object which is the root of the    *  core object system    */
name|the_gimp
operator|=
name|gimp_new
argument_list|(
name|be_verbose
argument_list|,
name|no_data
argument_list|,
name|no_interface
argument_list|,
name|stack_trace_mode
argument_list|)
expr_stmt|;
comment|/*  Check if the user's gimp_directory exists    */
name|gimp_dir
operator|=
name|gimp_directory
argument_list|()
expr_stmt|;
if|if
condition|(
name|stat
argument_list|(
name|gimp_dir
argument_list|,
operator|&
name|stat_buf
argument_list|)
operator|!=
literal|0
condition|)
block|{
comment|/*  not properly installed  */
if|if
condition|(
name|no_interface
condition|)
block|{
name|g_print
argument_list|(
name|_
argument_list|(
literal|"The GIMP is not properly installed for the current user\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"User installation was skipped because the '--nointerface' flag was encountered\n"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
name|_
argument_list|(
literal|"To perform user installation, run the GIMP without the '--nointerface' flag\n"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|user_install_dialog_create
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
block|}
block|}
comment|/*  The user_install dialog may have parsed unitrc and gimprc, so    *  check gimprc_init()'s return value    */
if|if
condition|(
name|gimprc_init
argument_list|(
name|the_gimp
argument_list|)
condition|)
block|{
comment|/*  this needs to be done before gimprc loading  */
name|gimp_unitrc_load
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
comment|/*  parse the local GIMP configuration file  */
name|gimprc_parse
argument_list|(
name|the_gimp
argument_list|,
name|alternate_system_gimprc
argument_list|,
name|alternate_gimprc
argument_list|)
expr_stmt|;
block|}
comment|/*  initialize lowlevel stuff  */
name|base_init
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_themes_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_splash
condition|)
name|splash_create
argument_list|(
operator|!
name|no_splash_image
argument_list|)
expr_stmt|;
block|}
comment|/*  Create all members of the global Gimp instance which need an already    *  parsed gimprc, e.g. the data factories    */
name|gimp_initialize
argument_list|(
name|the_gimp
argument_list|,
name|app_init_update_status
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|tool_manager_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
comment|/*  Load all data files    */
name|gimp_restore
argument_list|(
name|the_gimp
argument_list|,
name|app_init_update_status
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
comment|/*  Initialize the plug-in structures    */
name|plug_in_init
argument_list|(
name|the_gimp
argument_list|,
name|app_init_update_status
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
if|if
condition|(
operator|!
name|no_splash
condition|)
name|splash_destroy
argument_list|()
expr_stmt|;
comment|/*  FIXME: This needs to go in preferences  */
name|message_handler
operator|=
name|GIMP_MESSAGE_BOX
expr_stmt|;
name|gui_restore
argument_list|(
name|the_gimp
argument_list|,
name|restore_session
argument_list|)
expr_stmt|;
block|}
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
name|file_open_with_display
argument_list|(
name|the_gimp
argument_list|,
name|gimp_argv
index|[
name|i
index|]
argument_list|)
expr_stmt|;
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
operator|!
name|no_interface
condition|)
block|{
name|gui_post_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
name|gimp_main_loop
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_exit (gboolean kill_it)
name|app_exit
parameter_list|(
name|gboolean
name|kill_it
parameter_list|)
block|{
comment|/*  If it's the user's perogative, and there are dirty images  */
if|if
condition|(
operator|!
name|kill_it
operator|&&
name|gdisplays_dirty
argument_list|()
operator|&&
operator|!
name|no_interface
condition|)
name|gui_really_quit_dialog
argument_list|(
name|G_CALLBACK
argument_list|(
name|app_exit_finish
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|app_exit_finish
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
DECL|function|app_init_update_status (const gchar * text1,const gchar * text2,gdouble percentage)
name|app_init_update_status
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
if|if
condition|(
operator|!
name|no_interface
operator|&&
operator|!
name|no_splash
condition|)
block|{
name|splash_update
argument_list|(
name|text1
argument_list|,
name|text2
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|app_exit_finish (void)
name|app_exit_finish
parameter_list|(
name|void
parameter_list|)
block|{
name|message_handler
operator|=
name|GIMP_CONSOLE
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_shutdown
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
name|plug_in_kill
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|tool_manager_exit
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|gui_exit
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
name|gimp_shutdown
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
name|the_gimp
operator|=
name|NULL
expr_stmt|;
name|base_exit
argument_list|()
expr_stmt|;
comment|/*  There used to be foo_main_quit() here, but there's a chance     *  that foo_main() was never called before we reach this point. --Sven      */
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

