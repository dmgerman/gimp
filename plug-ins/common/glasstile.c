begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is the Glass Tile plug-in for the GIMP 1.2  * Version 1.02  *  * Copyright (C) 1997 Karl-Johan Andersson (t96kja@student.tdb.uu.se)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_comment
comment|/*  * This filter divide the image into square "glass"-blocks in which  * the image is refracted.   *   * The alpha-channel is left unchanged.  *   * Please send any comments or suggestions to  * Karl-Johan Andersson (t96kja@student.tdb.uu.se)  *  * May 2000 - tim copperfield [timecop@japan.co.jp]  * Added preview mode.  * Noticed there is an issue with the algorithm if odd number of rows or  * columns is requested.  Dunno why.  I am not a graphics expert :(  *    * May 2000 alt@gimp.org Made preview work and removed some boundary   * conditions that caused "streaks" to appear when using some tile spaces.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* --- Typedefs --- */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bd198770108
block|{
DECL|member|xblock
name|gint
name|xblock
decl_stmt|;
DECL|member|yblock
name|gint
name|yblock
decl_stmt|;
DECL|typedef|GlassValues
block|}
name|GlassValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bd198770208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|GlassInterface
block|}
name|GlassInterface
typedef|;
end_typedef

begin_comment
comment|/* --- Declare local functions --- */
end_comment

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|glass_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|glass_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|glasstile
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|preview_mode
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* --- Variables --- */
end_comment

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gtvals
specifier|static
name|GlassValues
name|gtvals
init|=
block|{
literal|20
block|,
comment|/* tile width  */
literal|20
comment|/* tile height */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gt_int
specifier|static
name|GlassInterface
name|gt_int
init|=
block|{
name|FALSE
comment|/* run */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview
specifier|static
name|GimpFixMePreview
modifier|*
name|preview
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* --- Functions --- */
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (unused)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"tilex"
block|,
literal|"Tile width (10 - 50)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"tiley"
block|,
literal|"Tile height (10 - 50)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_glasstile"
argument_list|,
literal|"Divide the image into square glassblocks"
argument_list|,
literal|"Divide the image into square glassblocks in "
literal|"which the image is refracted."
argument_list|,
literal|"Karl-Johan Andersson"
argument_list|,
comment|/* Author */
literal|"Karl-Johan Andersson"
argument_list|,
comment|/* Copyright */
literal|"May 2000"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Glass Effects/Glass Tile..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
comment|/*  Get the specified drawable  */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_glasstile"
argument_list|,
operator|&
name|gtvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|glass_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|5
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gtvals
operator|.
name|xblock
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gtvals
operator|.
name|yblock
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
if|if
condition|(
name|gtvals
operator|.
name|xblock
operator|<
literal|10
operator|||
name|gtvals
operator|.
name|xblock
operator|>
literal|50
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|gtvals
operator|.
name|yblock
operator|<
literal|10
operator|||
name|gtvals
operator|.
name|yblock
operator|>
literal|50
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_glasstile"
argument_list|,
operator|&
name|gtvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
comment|/*  Make sure that the drawable is gray or RGB color  */
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Glass Tile..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|drawable
operator|->
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|glasstile
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
comment|/*  Store data  */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|gimp_set_data
argument_list|(
literal|"plug_in_glasstile"
argument_list|,
operator|&
name|gtvals
argument_list|,
sizeof|sizeof
argument_list|(
name|GlassValues
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_fixme_preview_free
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|glass_dialog (GimpDrawable * drawable)
name|glass_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"glasstile"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Glass Tile"
argument_list|)
argument_list|,
literal|"glasstile"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/glasstile.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|glass_ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dlg
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
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
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_fixme_preview_new
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
operator|->
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
expr_stmt|;
name|glasstile
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* filter routine, initial pass */
comment|/*  Parameter settings  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Parameter Settings"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/* Horizontal scale - Width */
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Tile _Width:"
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|0
argument_list|,
name|gtvals
operator|.
name|xblock
argument_list|,
literal|10
argument_list|,
literal|50
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|gtvals
operator|.
name|xblock
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|glasstile
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/* Horizontal scale - Height */
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Tile _Height:"
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|0
argument_list|,
name|gtvals
operator|.
name|yblock
argument_list|,
literal|10
argument_list|,
literal|50
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|gtvals
operator|.
name|yblock
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|glasstile
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|gt_int
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|glass_ok_callback (GtkWidget * widget,gpointer data)
name|glass_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gt_int
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  -  Filter function  -  I wish all filter functions had a pmode :) */
end_comment

begin_function
specifier|static
name|void
DECL|function|glasstile (GimpDrawable * drawable,gboolean preview_mode)
name|glasstile
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|preview_mode
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|guchar
modifier|*
name|cur_row
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|,
name|i
decl_stmt|,
name|iwidth
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|rutbredd
decl_stmt|,
name|xpixel1
decl_stmt|,
name|xpixel2
decl_stmt|;
name|gint
name|ruthojd
decl_stmt|,
name|ypixel2
decl_stmt|;
name|gint
name|xhalv
decl_stmt|,
name|xoffs
decl_stmt|,
name|xmitt
decl_stmt|,
name|xplus
decl_stmt|;
name|gint
name|yhalv
decl_stmt|,
name|yoffs
decl_stmt|,
name|ymitt
decl_stmt|,
name|yplus
decl_stmt|;
name|gint
name|cbytes
decl_stmt|;
if|if
condition|(
name|preview_mode
condition|)
block|{
name|width
operator|=
name|preview
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|preview
operator|->
name|height
expr_stmt|;
name|bytes
operator|=
name|preview
operator|->
name|bpp
expr_stmt|;
name|x1
operator|=
name|y1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|width
expr_stmt|;
name|y2
operator|=
name|height
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|width
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
block|}
name|cur_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*  initialize the pixel regions  */
if|if
condition|(
name|preview_mode
condition|)
block|{
name|rutbredd
operator|=
name|gtvals
operator|.
name|xblock
operator|*
name|preview
operator|->
name|scale_x
expr_stmt|;
name|ruthojd
operator|=
name|gtvals
operator|.
name|yblock
operator|*
name|preview
operator|->
name|scale_y
expr_stmt|;
block|}
else|else
block|{
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|rutbredd
operator|=
name|gtvals
operator|.
name|xblock
expr_stmt|;
name|ruthojd
operator|=
name|gtvals
operator|.
name|yblock
expr_stmt|;
block|}
name|xhalv
operator|=
name|rutbredd
operator|/
literal|2
expr_stmt|;
name|yhalv
operator|=
name|ruthojd
operator|/
literal|2
expr_stmt|;
name|cbytes
operator|=
name|bytes
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|cbytes
operator|&
literal|1
operator|)
condition|)
name|cbytes
operator|--
expr_stmt|;
name|iwidth
operator|=
name|width
operator|-
name|x1
expr_stmt|;
name|xplus
operator|=
name|rutbredd
operator|%
literal|2
expr_stmt|;
name|yplus
operator|=
name|ruthojd
operator|%
literal|2
expr_stmt|;
name|ymitt
operator|=
name|y1
expr_stmt|;
name|yoffs
operator|=
literal|0
expr_stmt|;
comment|/*  Loop through the rows */
for|for
control|(
name|row
operator|=
name|y1
init|;
name|row
operator|<
name|y2
condition|;
name|row
operator|++
control|)
block|{
name|d
operator|=
name|dest
expr_stmt|;
name|ypixel2
operator|=
name|ymitt
operator|+
name|yoffs
operator|*
literal|2
expr_stmt|;
name|ypixel2
operator|=
name|CLAMP
argument_list|(
name|ypixel2
argument_list|,
literal|0
argument_list|,
name|y2
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview_mode
condition|)
block|{
name|memcpy
argument_list|(
name|cur_row
argument_list|,
name|preview
operator|->
name|cache
operator|+
name|ypixel2
operator|*
name|preview
operator|->
name|rowstride
argument_list|,
name|preview
operator|->
name|rowstride
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|cur_row
argument_list|,
name|x1
argument_list|,
name|ypixel2
argument_list|,
name|iwidth
argument_list|)
expr_stmt|;
block|}
name|yoffs
operator|++
expr_stmt|;
if|if
condition|(
name|yoffs
operator|==
name|yhalv
condition|)
block|{
name|ymitt
operator|+=
name|ruthojd
expr_stmt|;
name|yoffs
operator|=
operator|-
operator|(
name|yhalv
operator|+
name|yplus
operator|)
expr_stmt|;
block|}
name|xmitt
operator|=
literal|0
expr_stmt|;
name|xoffs
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|x2
operator|-
name|x1
condition|;
name|col
operator|++
control|)
comment|/* one pixel */
block|{
name|xpixel1
operator|=
operator|(
name|xmitt
operator|+
name|xoffs
operator|)
operator|*
name|bytes
expr_stmt|;
name|xpixel2
operator|=
operator|(
name|xmitt
operator|+
name|xoffs
operator|*
literal|2
operator|)
operator|*
name|bytes
expr_stmt|;
if|if
condition|(
name|xpixel2
operator|<
operator|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
operator|)
condition|)
block|{
if|if
condition|(
name|xpixel2
operator|<
literal|0
condition|)
name|xpixel2
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
control|)
name|d
index|[
name|xpixel1
operator|+
name|i
index|]
operator|=
name|cur_row
index|[
name|xpixel2
operator|+
name|i
index|]
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
control|)
name|d
index|[
name|xpixel1
operator|+
name|i
index|]
operator|=
name|cur_row
index|[
name|xpixel1
operator|+
name|i
index|]
expr_stmt|;
block|}
name|xoffs
operator|++
expr_stmt|;
if|if
condition|(
name|xoffs
operator|==
name|xhalv
condition|)
block|{
name|xmitt
operator|+=
name|rutbredd
expr_stmt|;
name|xoffs
operator|=
operator|-
operator|(
name|xhalv
operator|+
name|xplus
operator|)
expr_stmt|;
block|}
block|}
comment|/*  Store the dest  */
if|if
condition|(
name|preview_mode
condition|)
block|{
name|gimp_fixme_preview_do_row
argument_list|(
name|preview
argument_list|,
name|row
argument_list|,
name|width
argument_list|,
name|dest
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest
argument_list|,
name|x1
argument_list|,
name|row
argument_list|,
name|iwidth
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|row
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|row
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  Update region  */
if|if
condition|(
name|preview_mode
condition|)
block|{
name|gtk_widget_queue_draw
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|cur_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

