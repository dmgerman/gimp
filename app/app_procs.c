begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

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

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
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
file|"brushes.h"
end_include

begin_include
include|#
directive|include
file|"color_transfer.h"
end_include

begin_include
include|#
directive|include
file|"curves.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"fileops.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"global_edit.h"
end_include

begin_include
include|#
directive|include
file|"gradient.h"
end_include

begin_include
include|#
directive|include
file|"gximage.h"
end_include

begin_include
include|#
directive|include
file|"hue_saturation.h"
end_include

begin_include
include|#
directive|include
file|"image_render.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"internal_procs.h"
end_include

begin_include
include|#
directive|include
file|"layers_dialog.h"
end_include

begin_include
include|#
directive|include
file|"levels.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"patterns.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
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
file|"tips_dialog.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"xcf.h"
end_include

begin_comment
comment|/*  Function prototype for affirmation dialog when exiting application  */
end_comment

begin_function_decl
specifier|static
name|void
name|app_exit_finish
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|really_quit_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Argument
modifier|*
name|quit_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|quit_args
specifier|static
name|ProcArg
name|quit_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"kill"
block|,
literal|"Flag specifying whether to kill the gimp process or exit normally"
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|quit_proc
specifier|static
name|ProcRecord
name|quit_proc
init|=
block|{
literal|"gimp_quit"
block|,
literal|"Causes the gimp to exit gracefully"
block|,
literal|"The internal procedure which can either be used to make the gimp quit normally, or to have the gimp clean up its resources and exit immediately. The normaly shutdown process allows for querying the user to save any dirty images."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|quit_args
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|quit_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_init (int gimp_argc,char ** gimp_argv)
name|gimp_init
parameter_list|(
name|int
name|gimp_argc
parameter_list|,
name|char
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
block|}
end_function

begin_function
name|void
DECL|function|app_init ()
name|app_init
parameter_list|()
block|{
name|char
name|filename
index|[
name|MAXPATHLEN
index|]
decl_stmt|;
name|char
modifier|*
name|gimp_dir
decl_stmt|;
name|char
modifier|*
name|path
decl_stmt|;
comment|/*    *  Initialize the procedural database    *    We need to do this first because any of the init    *    procedures might install or query it as needed.    */
name|procedural_db_init
argument_list|()
expr_stmt|;
name|internal_procs_init
argument_list|()
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|quit_proc
argument_list|)
expr_stmt|;
name|gimp_dir
operator|=
name|gimp_directory
argument_list|()
expr_stmt|;
if|if
condition|(
name|gimp_dir
index|[
literal|0
index|]
operator|!=
literal|'\000'
condition|)
block|{
name|sprintf
argument_list|(
name|filename
argument_list|,
literal|"%s/gtkrc"
argument_list|,
name|gimp_dir
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"parsing \"%s\"\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|file_ops_pre_init
argument_list|()
expr_stmt|;
comment|/*  pre-initialize the file types  */
name|xcf_init
argument_list|()
expr_stmt|;
comment|/*  initialize the xcf file format routines */
name|parse_gimprc
argument_list|()
expr_stmt|;
comment|/*  parse the local GIMP configuration file  */
if|if
condition|(
name|no_data
operator|==
name|FALSE
condition|)
block|{
name|brushes_init
argument_list|()
expr_stmt|;
comment|/*  initialize the list of gimp brushes  */
name|patterns_init
argument_list|()
expr_stmt|;
comment|/*  initialize the list of gimp patterns  */
name|palettes_init
argument_list|()
expr_stmt|;
comment|/*  initialize the list of gimp palettes  */
name|gradients_init
argument_list|()
expr_stmt|;
comment|/*  initialize the list of gimp gradients  */
block|}
name|plug_in_init
argument_list|()
expr_stmt|;
comment|/*  initialize the plug in structures  */
name|file_ops_post_init
argument_list|()
expr_stmt|;
comment|/*  post-initialize the file types  */
comment|/* Add the swap file  */
if|if
condition|(
name|swap_path
operator|==
name|NULL
condition|)
name|swap_path
operator|=
literal|"/tmp"
expr_stmt|;
name|path
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|strlen
argument_list|(
name|swap_path
argument_list|)
operator|+
literal|32
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|path
argument_list|,
literal|"%s/gimpswap.%ld"
argument_list|,
name|swap_path
argument_list|,
operator|(
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
comment|/*  Things to do only if there is an interface  */
if|if
condition|(
name|no_interface
operator|==
name|FALSE
condition|)
block|{
name|get_standard_colormaps
argument_list|()
expr_stmt|;
name|create_toolbox
argument_list|()
expr_stmt|;
name|gximage_init
argument_list|()
expr_stmt|;
name|render_setup
argument_list|(
name|transparency_type
argument_list|,
name|transparency_size
argument_list|)
expr_stmt|;
name|tools_options_dialog_new
argument_list|()
expr_stmt|;
name|tools_select
argument_list|(
name|RECT_SELECT
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_tips
condition|)
name|tips_dialog_create
argument_list|()
expr_stmt|;
block|}
name|color_transfer_init
argument_list|()
expr_stmt|;
name|get_active_brush
argument_list|()
expr_stmt|;
name|get_active_pattern
argument_list|()
expr_stmt|;
name|paint_funcs_setup
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|app_exit_finish ()
name|app_exit_finish
parameter_list|()
block|{
name|lc_dialog_free
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
name|brushes_free
argument_list|()
expr_stmt|;
name|patterns_free
argument_list|()
expr_stmt|;
name|palettes_free
argument_list|()
expr_stmt|;
name|gradients_free
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
name|brush_select_dialog_free
argument_list|()
expr_stmt|;
name|pattern_select_dialog_free
argument_list|()
expr_stmt|;
name|palette_free
argument_list|()
expr_stmt|;
name|paint_funcs_free
argument_list|()
expr_stmt|;
name|procedural_db_free
argument_list|()
expr_stmt|;
name|plug_in_kill
argument_list|()
expr_stmt|;
name|menus_quit
argument_list|()
expr_stmt|;
name|tile_swap_exit
argument_list|()
expr_stmt|;
comment|/*  Things to do only if there is an interface  */
if|if
condition|(
name|no_interface
operator|==
name|FALSE
condition|)
block|{
name|gximage_free
argument_list|()
expr_stmt|;
name|render_free
argument_list|()
expr_stmt|;
name|tools_options_dialog_free
argument_list|()
expr_stmt|;
block|}
name|gtk_exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_exit (int kill_it)
name|app_exit
parameter_list|(
name|int
name|kill_it
parameter_list|)
block|{
comment|/*  If it's the user's perogative, and there are dirty images  */
if|if
condition|(
name|kill_it
operator|==
literal|0
operator|&&
name|gdisplays_dirty
argument_list|()
operator|&&
name|no_interface
operator|==
name|FALSE
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

begin_comment
comment|/********************************************************  *   Routines to query exiting the application          *  ********************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|really_quit_callback (GtkButton * button,GtkWidget * dialog)
name|really_quit_callback
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|app_exit_finish
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|really_quit_cancel_callback (GtkButton * button,GtkWidget * dialog)
name|really_quit_cancel_callback
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|menus_set_sensitive
argument_list|(
literal|"<Toolbox>/File/Quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|really_quit_delete_callback (GtkWidget * widget,GdkEvent * event,gpointer client_data)
name|really_quit_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|really_quit_cancel_callback
argument_list|(
name|GTK_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|(
name|GtkWidget
operator|*
operator|)
name|client_data
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|really_quit_dialog ()
name|really_quit_dialog
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Toolbox>/File/Quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"Really Quit?"
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|really_quit_delete_callback
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Yes"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|really_quit_callback
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"No"
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|really_quit_cancel_callback
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Some files unsaved.  Quit the GIMP?"
argument_list|)
expr_stmt|;
name|gtk_misc_set_padding
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|quit_invoker (Argument * args)
name|quit_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|int
name|kill_it
decl_stmt|;
name|kill_it
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|app_exit
argument_list|(
name|kill_it
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|quit_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

end_unit

