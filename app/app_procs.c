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
file|"pdb/internal_procs.h"
end_include

begin_include
include|#
directive|include
file|"xcf/xcf.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gui/color-notebook.h"
end_include

begin_include
include|#
directive|include
file|"gui/file-open-dialog.h"
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
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay_ops.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_include
include|#
directive|include
file|"module_db.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"unitrc.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"docindex.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
end_ifdef

begin_include
include|#
directive|include
file|"gdisplay_color.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* DISPLAY_FILTERS */
end_comment

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

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
comment|/* FIXME: gimp_busy HACK */
end_comment

begin_decl_stmt
DECL|variable|gimp_busy
name|gboolean
name|gimp_busy
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|is_app_exit_finish_done
specifier|static
name|gboolean
name|is_app_exit_finish_done
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
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

begin_comment
comment|/* #define RESET_BAR() app_init_update_status("", "", 0) */
end_comment

begin_define
DECL|macro|RESET_BAR ()
define|#
directive|define
name|RESET_BAR
parameter_list|()
end_define

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
name|gtkrc
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
comment|/*  parse the systemwide gtkrc  */
name|gtkrc
operator|=
name|gimp_gtkrc
argument_list|()
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"parsing \"%s\"\n"
argument_list|)
argument_list|,
name|gtkrc
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gtkrc
argument_list|)
expr_stmt|;
comment|/*  parse the user gtkrc  */
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"gtkrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"parsing \"%s\"\n"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimprc_init
argument_list|()
condition|)
block|{
name|parse_unitrc
argument_list|()
expr_stmt|;
comment|/*  this needs to be done before gimprc loading  */
name|parse_gimprc
argument_list|()
expr_stmt|;
comment|/*  parse the local GIMP configuration file      */
block|}
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|get_standard_colormaps
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|no_splash
condition|)
name|splash_create
argument_list|()
expr_stmt|;
block|}
comment|/*  initialize lowlevel stuff  */
name|base_init
argument_list|()
expr_stmt|;
comment|/*  Create an instance of the "Gimp" object which is the root of the    *  core object system    */
name|the_gimp
operator|=
name|gimp_new
argument_list|()
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
comment|/*  Initialize the procedural database    *    We need to do this first because any of the init    *    procedures might install or query it as needed.    */
name|app_init_update_status
argument_list|(
name|_
argument_list|(
literal|"Procedural Database"
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|internal_procs_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
name|color_display_init
argument_list|()
expr_stmt|;
endif|#
directive|endif
comment|/* DISPLAY_FILTERS */
name|RESET_BAR
argument_list|()
expr_stmt|;
if|if
condition|(
name|gimprc
operator|.
name|always_restore_session
condition|)
name|restore_session
operator|=
name|TRUE
expr_stmt|;
comment|/* Now we are ready to draw the splash-screen-image to the start-up window */
if|if
condition|(
operator|!
name|no_interface
operator|&&
operator|!
name|no_splash_image
condition|)
block|{
name|splash_logo_load
argument_list|()
expr_stmt|;
block|}
name|RESET_BAR
argument_list|()
expr_stmt|;
name|xcf_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
comment|/*  initialize the xcf file format routines */
comment|/*  load all data files  */
name|gimp_restore
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|plug_in_init
argument_list|()
expr_stmt|;
comment|/*  initialize the plug in structures  */
name|module_db_init
argument_list|()
expr_stmt|;
comment|/*  load any modules we need           */
name|RESET_BAR
argument_list|()
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
name|gui_init
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
comment|/*  FIXME: This needs to go in preferences  */
name|message_handler
operator|=
name|MESSAGE_BOX
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_restore
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
comment|/* Parse the rest of the command line arguments as images to load */
if|if
condition|(
name|gimp_argc
operator|>
literal|0
condition|)
while|while
condition|(
name|gimp_argc
operator|--
condition|)
block|{
if|if
condition|(
operator|*
name|gimp_argv
condition|)
name|file_open_with_display
argument_list|(
operator|*
name|gimp_argv
argument_list|)
expr_stmt|;
name|gimp_argv
operator|++
expr_stmt|;
block|}
name|batch_init
argument_list|(
name|the_gimp
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
argument_list|()
expr_stmt|;
else|else
name|app_exit_finish
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_exit_finish (void)
name|app_exit_finish
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|app_exit_finish_done
argument_list|()
condition|)
return|return;
name|is_app_exit_finish_done
operator|=
name|TRUE
expr_stmt|;
name|message_handler
operator|=
name|CONSOLE
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
name|module_db_free
argument_list|()
expr_stmt|;
name|gdisplays_delete
argument_list|()
expr_stmt|;
name|plug_in_kill
argument_list|()
expr_stmt|;
name|save_unitrc
argument_list|()
expr_stmt|;
name|tool_manager_exit
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_exit
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
name|xcf_exit
argument_list|()
expr_stmt|;
name|gimp_shutdown
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
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
comment|/*  There used to be gtk_main_quit() here, but there's a chance     *  that gtk_main() was never called before we reach this point. --Sven      */
name|gtk_exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|app_exit_finish_done (void)
name|app_exit_finish_done
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|is_app_exit_finish_done
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_busy (void)
name|gimp_set_busy
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* FIXME: gimp_busy HACK */
name|gimp_busy
operator|=
name|TRUE
expr_stmt|;
name|gui_set_busy
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_idle_unset_busy (gpointer data)
name|gimp_idle_unset_busy
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_unset_busy
argument_list|()
expr_stmt|;
operator|*
operator|(
operator|(
name|guint
operator|*
operator|)
name|data
operator|)
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_busy_until_idle (void)
name|gimp_set_busy_until_idle
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|guint
name|busy_idle_id
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|busy_idle_id
condition|)
block|{
name|gimp_set_busy
argument_list|()
expr_stmt|;
name|busy_idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_HIGH
argument_list|,
name|gimp_idle_unset_busy
argument_list|,
operator|&
name|busy_idle_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_unset_busy (void)
name|gimp_unset_busy
parameter_list|(
name|void
parameter_list|)
block|{
name|gui_unset_busy
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
comment|/* FIXME: gimp_busy HACK */
name|gimp_busy
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

