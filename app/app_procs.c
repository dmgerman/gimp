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
file|<signal.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_DIRENT_H
end_ifdef

begin_include
include|#
directive|include
file|<dirent.h>
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
file|<gdk/gdktypes.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_comment
comment|/* For _getpid() */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimp/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpfeatures.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"pdb/internal_procs.h"
end_include

begin_include
include|#
directive|include
file|"tools/curves.h"
end_include

begin_include
include|#
directive|include
file|"tools/hue_saturation.h"
end_include

begin_include
include|#
directive|include
file|"tools/levels.h"
end_include

begin_include
include|#
directive|include
file|"gui/color-notebook.h"
end_include

begin_include
include|#
directive|include
file|"gui/color-select.h"
end_include

begin_include
include|#
directive|include
file|"gui/colormap-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/brush-select.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui.h"
end_include

begin_include
include|#
directive|include
file|"gui/gradient-select.h"
end_include

begin_include
include|#
directive|include
file|"gui/palette-editor.h"
end_include

begin_include
include|#
directive|include
file|"gui/pattern-select.h"
end_include

begin_include
include|#
directive|include
file|"gui/splash.h"
end_include

begin_include
include|#
directive|include
file|"gui/tips-dialog.h"
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
file|"color_transfer.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"errorconsole.h"
end_include

begin_include
include|#
directive|include
file|"file-open.h"
end_include

begin_include
include|#
directive|include
file|"file-save.h"
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
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasite.h"
end_include

begin_include
include|#
directive|include
file|"global_edit.h"
end_include

begin_include
include|#
directive|include
file|"lc_dialog.h"
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
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tile_swap.h"
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
file|"xcf.h"
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
file|"gimpparasite.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|toast_old_temp_files
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|is_app_exit_finish_done
specifier|static
name|gboolean
name|is_app_exit_finish_done
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|we_are_exiting
name|gboolean
name|we_are_exiting
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_init (gint gimp_argc,gchar ** gimp_argv)
name|gimp_init
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
comment|/* Initialize the application */
name|app_init
argument_list|()
expr_stmt|;
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
name|file_open
argument_list|(
operator|*
name|gimp_argv
argument_list|,
operator|*
name|gimp_argv
argument_list|)
expr_stmt|;
name|gimp_argv
operator|++
expr_stmt|;
block|}
name|batch_init
argument_list|()
expr_stmt|;
comment|/* Handle showing dialogs with gdk_quit_adds here  */
if|if
condition|(
operator|!
name|no_interface
operator|&&
name|show_tips
condition|)
name|tips_dialog_create
argument_list|()
expr_stmt|;
block|}
end_function

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
DECL|function|app_init (void)
name|app_init
parameter_list|(
name|void
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
name|gchar
modifier|*
name|path
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
name|parse_buffers_init
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
comment|/*  Initialize the context system before loading any data  */
name|context_manager_init
argument_list|()
expr_stmt|;
comment|/*  Initialize the procedural database    *    We need to do this first because any of the init    *    procedures might install or query it as needed.    */
name|procedural_db_init
argument_list|()
expr_stmt|;
name|RESET_BAR
argument_list|()
expr_stmt|;
name|internal_procs_init
argument_list|()
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
name|always_restore_session
condition|)
name|restore_session
operator|=
name|TRUE
expr_stmt|;
comment|/* make sure the monitor resolution is valid */
if|if
condition|(
name|monitor_xres
operator|<
name|GIMP_MIN_RESOLUTION
operator|||
name|monitor_yres
operator|<
name|GIMP_MIN_RESOLUTION
condition|)
block|{
name|gdisplay_xserver_resolution
argument_list|(
operator|&
name|monitor_xres
argument_list|,
operator|&
name|monitor_yres
argument_list|)
expr_stmt|;
name|using_xserver_resolution
operator|=
name|TRUE
expr_stmt|;
block|}
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
name|file_open_pre_init
argument_list|()
expr_stmt|;
comment|/*  pre-initialize the file types     */
name|file_save_pre_init
argument_list|()
expr_stmt|;
name|RESET_BAR
argument_list|()
expr_stmt|;
name|xcf_init
argument_list|()
expr_stmt|;
comment|/*  initialize the xcf file format routines */
comment|/*  initialize  the global parasite table  */
name|app_init_update_status
argument_list|(
name|_
argument_list|(
literal|"Looking for data files"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Parasites"
argument_list|)
argument_list|,
literal|0.00
argument_list|)
expr_stmt|;
name|gimp_init_parasites
argument_list|()
expr_stmt|;
comment|/*  initialize the list of gimp brushes    */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Brushes"
argument_list|)
argument_list|,
literal|0.20
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|global_brush_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp patterns   */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Patterns"
argument_list|)
argument_list|,
literal|0.40
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|global_pattern_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp palettes   */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Palettes"
argument_list|)
argument_list|,
literal|0.60
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|global_palette_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
comment|/*  initialize the list of gimp gradients  */
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Gradients"
argument_list|)
argument_list|,
literal|0.80
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_init
argument_list|(
name|global_gradient_factory
argument_list|,
name|no_data
argument_list|)
expr_stmt|;
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1.00
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
name|file_open_post_init
argument_list|()
expr_stmt|;
comment|/*  post-initialize the file types     */
name|file_save_post_init
argument_list|()
expr_stmt|;
comment|/* Add the swap file  */
if|if
condition|(
name|swap_path
operator|==
name|NULL
condition|)
name|swap_path
operator|=
name|g_get_tmp_dir
argument_list|()
expr_stmt|;
name|toast_old_temp_files
argument_list|()
expr_stmt|;
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s"
name|G_DIR_SEPARATOR_S
literal|"gimpswap.%lu"
argument_list|,
name|swap_path
argument_list|,
operator|(
name|unsigned
name|long
operator|)
name|getpid
argument_list|()
argument_list|)
expr_stmt|;
name|tile_swap_add
argument_list|(
name|path
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
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
name|gui_init
argument_list|()
expr_stmt|;
comment|/*  FIXME: This needs to go in preferences  */
name|message_handler
operator|=
name|MESSAGE_BOX
expr_stmt|;
block|}
name|color_transfer_init
argument_list|()
expr_stmt|;
name|paint_funcs_setup
argument_list|()
expr_stmt|;
comment|/* register internal color selectors */
name|color_select_init
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_restore
argument_list|()
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
name|really_quit_dialog
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
name|we_are_exiting
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_shutdown
argument_list|()
expr_stmt|;
block|}
name|module_db_free
argument_list|()
expr_stmt|;
name|gdisplays_delete
argument_list|()
expr_stmt|;
name|global_edit_free
argument_list|()
expr_stmt|;
name|named_buffers_free
argument_list|()
expr_stmt|;
name|swapping_free
argument_list|()
expr_stmt|;
name|brush_dialog_free
argument_list|()
expr_stmt|;
name|pattern_dialog_free
argument_list|()
expr_stmt|;
name|palette_dialog_free
argument_list|()
expr_stmt|;
name|gradient_dialog_free
argument_list|()
expr_stmt|;
name|context_manager_free
argument_list|()
expr_stmt|;
name|hue_saturation_free
argument_list|()
expr_stmt|;
name|curves_free
argument_list|()
expr_stmt|;
name|levels_free
argument_list|()
expr_stmt|;
name|paint_funcs_free
argument_list|()
expr_stmt|;
name|plug_in_kill
argument_list|()
expr_stmt|;
name|procedural_db_free
argument_list|()
expr_stmt|;
name|error_console_free
argument_list|()
expr_stmt|;
name|tile_swap_exit
argument_list|()
expr_stmt|;
name|save_unitrc
argument_list|()
expr_stmt|;
name|gimp_parasiterc_save
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_exit
argument_list|()
expr_stmt|;
block|}
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
specifier|static
name|void
DECL|function|toast_old_temp_files (void)
name|toast_old_temp_files
parameter_list|(
name|void
parameter_list|)
block|{
name|DIR
modifier|*
name|dir
decl_stmt|;
name|struct
name|dirent
modifier|*
name|entry
decl_stmt|;
name|GString
modifier|*
name|filename
init|=
name|g_string_new
argument_list|(
literal|""
argument_list|)
decl_stmt|;
name|dir
operator|=
name|opendir
argument_list|(
name|swap_path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
return|return;
while|while
condition|(
operator|(
name|entry
operator|=
name|readdir
argument_list|(
name|dir
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
if|if
condition|(
operator|!
name|strncmp
argument_list|(
name|entry
operator|->
name|d_name
argument_list|,
literal|"gimpswap."
argument_list|,
literal|9
argument_list|)
condition|)
block|{
comment|/* don't try to kill swap files of running processes          * yes, I know they might not all be gimp processes, and when you          * unlink, it's refcounted, but lets not confuse the user by          * "where did my disk space go?" cause the filename is gone          * if the kill succeeds, and there running process isn't gimp          * we'll probably get it the next time around          */
name|gint
name|pid
init|=
name|atoi
argument_list|(
name|entry
operator|->
name|d_name
operator|+
literal|9
argument_list|)
decl_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
if|if
condition|(
name|kill
argument_list|(
name|pid
argument_list|,
literal|0
argument_list|)
condition|)
endif|#
directive|endif
block|{
comment|/*  On Windows, you can't remove open files anyhow, 	     *  so no harm trying. 	     */
name|g_string_sprintf
argument_list|(
name|filename
argument_list|,
literal|"%s"
name|G_DIR_SEPARATOR_S
literal|"%s"
argument_list|,
name|swap_path
argument_list|,
name|entry
operator|->
name|d_name
argument_list|)
expr_stmt|;
name|unlink
argument_list|(
name|filename
operator|->
name|str
argument_list|)
expr_stmt|;
block|}
block|}
name|closedir
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|filename
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

