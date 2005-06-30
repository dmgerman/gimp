begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Shift --- image filter plug-in for The Gimp image manipulation program  * Copyright (C) 1997 Brian Degenhardt and Federico Mena Quintero  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * Please direct all comments, questions, bug reports  etc to Brian Degenhardt  * bdegenha@ucsd.edu  *  * You can contact Federico Mena Quintero at quartic@polloux.fciencias.unam.mx  * You can contact the original The Gimp authors at gimp@xcf.berkeley.edu  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
comment|/* Some useful macros */
end_comment

begin_define
DECL|macro|SPIN_BUTTON_WIDTH
define|#
directive|define
name|SPIN_BUTTON_WIDTH
value|8
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|16
end_define

begin_define
DECL|macro|HORIZONTAL
define|#
directive|define
name|HORIZONTAL
value|0
end_define

begin_define
DECL|macro|VERTICAL
define|#
directive|define
name|VERTICAL
value|1
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2911f6510108
block|{
DECL|member|shift_amount
name|gint
name|shift_amount
decl_stmt|;
DECL|member|orientation
name|gint
name|orientation
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|ShiftValues
block|}
name|ShiftValues
typedef|;
end_typedef

begin_comment
comment|/* Declare local functions.  */
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
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
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
name|void
name|shift
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|shift_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shift_amount_callback
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

begin_comment
comment|/***** Local vars *****/
end_comment

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shvals
specifier|static
name|ShiftValues
name|shvals
init|=
block|{
literal|5
block|,
comment|/* shift amount */
name|HORIZONTAL
block|,
comment|/* orientation  */
name|TRUE
comment|/* preview */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***** Functions *****/
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
literal|"shift_amount"
block|,
literal|"shift amount (0<= shift_amount_x<= 200)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"orientation"
block|,
literal|"vertical, horizontal orientation"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_shift"
argument_list|,
literal|"Shift the contents of the specified drawable"
argument_list|,
literal|"Shifts the pixels of the specified drawable. "
literal|"Each row will be displaced a random value of pixels."
argument_list|,
literal|"Spencer Kimball and Peter Mattis, ported by Brian "
literal|"Degenhardt and Federico Mena Quintero"
argument_list|,
literal|"Brian Degenhardt"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Shift..."
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
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_shift"
argument_list|,
literal|"<Image>/Filters/Distorts"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
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
name|gint32
name|image_ID
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
name|image_ID
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|INIT_I18N
argument_list|()
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
comment|/*  set the tile cache size  */
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
argument_list|)
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_shift"
argument_list|,
operator|&
name|shvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|shift_dialog
argument_list|(
name|image_ID
argument_list|,
name|drawable
argument_list|)
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|5
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|shvals
operator|.
name|shift_amount
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|shvals
operator|.
name|orientation
operator|=
operator|(
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
operator|)
condition|?
name|HORIZONTAL
else|:
name|VERTICAL
expr_stmt|;
if|if
condition|(
name|shvals
operator|.
name|shift_amount
operator|<
literal|0
operator|||
name|shvals
operator|.
name|shift_amount
operator|>
literal|200
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_shift"
argument_list|,
operator|&
name|shvals
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
literal|"Shifting..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  run the shift effect  */
name|shift
argument_list|(
name|drawable
argument_list|,
name|NULL
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
name|gimp_set_data
argument_list|(
literal|"plug_in_shift"
argument_list|,
operator|&
name|shvals
argument_list|,
sizeof|sizeof
argument_list|(
name|ShiftValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("shift: cannot operate on indexed color images"); */
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
name|void
DECL|function|shift (GimpDrawable * drawable,GimpPreview * preview)
name|shift
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpPixelRgn
name|dest_rgn
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|GimpPixelFetcher
modifier|*
name|pft
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
name|destline
decl_stmt|;
name|guchar
modifier|*
name|dest
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
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|n
init|=
literal|0
decl_stmt|;
name|gint
modifier|*
name|offsets
decl_stmt|;
name|GRand
modifier|*
name|gr
decl_stmt|;
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
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
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
block|}
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
name|width
operator|*
name|height
expr_stmt|;
comment|/* Shift the image.  It's a pretty simple algorithm.  If horizontal      is selected, then every row is shifted a random number of pixels      in the range of -shift_amount/2 to shift_amount/2.  The effect is      just reproduced with columns if vertical is selected.    */
name|n
operator|=
operator|(
name|shvals
operator|.
name|orientation
operator|==
name|HORIZONTAL
operator|)
condition|?
name|height
else|:
name|width
expr_stmt|;
name|offsets
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|n
argument_list|)
expr_stmt|;
name|gr
operator|=
name|g_rand_new
argument_list|()
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
name|offsets
index|[
name|i
index|]
operator|=
name|g_rand_int_range
argument_list|(
name|gr
argument_list|,
operator|-
operator|(
name|shvals
operator|.
name|shift_amount
operator|+
literal|1
operator|)
operator|/
literal|2.0
argument_list|,
operator|+
operator|(
name|shvals
operator|.
name|shift_amount
operator|+
literal|1
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|g_rand_free
argument_list|(
name|gr
argument_list|)
expr_stmt|;
name|pft
operator|=
name|gimp_pixel_fetcher_new
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_fetcher_set_edge_mode
argument_list|(
name|pft
argument_list|,
name|GIMP_PIXEL_FETCHER_EDGE_WRAP
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|preview
operator|==
name|NULL
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|dest_rgn
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|destline
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
switch|switch
condition|(
name|shvals
operator|.
name|orientation
condition|)
block|{
case|case
name|HORIZONTAL
case|:
for|for
control|(
name|y
operator|=
name|dest_rgn
operator|.
name|y
init|;
name|y
operator|<
name|dest_rgn
operator|.
name|y
operator|+
name|dest_rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|dest
operator|=
name|destline
expr_stmt|;
for|for
control|(
name|x
operator|=
name|dest_rgn
operator|.
name|x
init|;
name|x
operator|<
name|dest_rgn
operator|.
name|x
operator|+
name|dest_rgn
operator|.
name|w
condition|;
name|x
operator|++
control|)
block|{
name|gimp_pixel_fetcher_get_pixel
argument_list|(
name|pft
argument_list|,
name|x
operator|+
name|offsets
index|[
name|y
operator|-
name|y1
index|]
argument_list|,
name|y
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|bytes
expr_stmt|;
block|}
name|destline
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
break|break;
case|case
name|VERTICAL
case|:
for|for
control|(
name|x
operator|=
name|dest_rgn
operator|.
name|x
init|;
name|x
operator|<
name|dest_rgn
operator|.
name|x
operator|+
name|dest_rgn
operator|.
name|w
condition|;
name|x
operator|++
control|)
block|{
name|dest
operator|=
name|destline
expr_stmt|;
for|for
control|(
name|y
operator|=
name|dest_rgn
operator|.
name|y
init|;
name|y
operator|<
name|dest_rgn
operator|.
name|y
operator|+
name|dest_rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|gimp_pixel_fetcher_get_pixel
argument_list|(
name|pft
argument_list|,
name|x
argument_list|,
name|y
operator|+
name|offsets
index|[
name|x
operator|-
name|x1
index|]
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
name|destline
operator|+=
name|bytes
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_drawable_preview_draw_region
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|dest_rgn
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|progress
operator|+=
name|dest_rgn
operator|.
name|w
operator|*
name|dest_rgn
operator|.
name|h
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|progress
operator|/
operator|(
name|double
operator|)
name|max_progress
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_pixel_fetcher_destroy
argument_list|(
name|pft
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|offsets
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
block|{
comment|/*  update the region  */
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
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|shift_dialog (gint32 image_ID,GimpDrawable * drawable)
name|shift_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|size_entry
decl_stmt|;
name|GtkWidget
modifier|*
name|vertical
decl_stmt|;
name|GtkWidget
modifier|*
name|horizontal
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"shift"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Shift"
argument_list|)
argument_list|,
literal|"shift"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-shift"
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_drawable_preview_new
argument_list|(
name|drawable
argument_list|,
operator|&
name|shvals
operator|.
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|shift
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|shvals
operator|.
name|orientation
argument_list|,
name|shvals
operator|.
name|orientation
argument_list|,
name|_
argument_list|(
literal|"Shift _horizontally"
argument_list|)
argument_list|,
name|HORIZONTAL
argument_list|,
operator|&
name|horizontal
argument_list|,
name|_
argument_list|(
literal|"Shift _vertically"
argument_list|)
argument_list|,
name|VERTICAL
argument_list|,
operator|&
name|vertical
argument_list|,
name|NULL
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
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|horizontal
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|vertical
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
comment|/*  Get the image resolution and unit  */
name|gimp_image_get_resolution
argument_list|(
name|image_ID
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|size_entry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|unit
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|SPIN_BUTTON_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|,
literal|200.0
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|(
name|gdouble
operator|)
name|shvals
operator|.
name|shift_amount
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Shift _amount:"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|size_entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|shift_amount_callback
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|size_entry
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
name|size_entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shift_amount_callback (GtkWidget * widget,gpointer data)
name|shift_amount_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
init|=
name|GIMP_PREVIEW
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|shvals
operator|.
name|shift_amount
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_preview_invalidate
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

