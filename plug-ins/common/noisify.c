begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plugin for the GIMP.  *  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1996 Torsten Martinsen  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_comment
comment|/*  * This filter adds random noise to an image.  * The amount of noise can be set individually for each RGB channel.  * This filter does not operate on indexed images.  */
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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
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

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|125
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|16
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28aaabae0108
block|{
DECL|member|independent
name|gint
name|independent
decl_stmt|;
DECL|member|noise
name|gdouble
name|noise
index|[
literal|4
index|]
decl_stmt|;
comment|/*  per channel  */
DECL|typedef|NoisifyVals
block|}
name|NoisifyVals
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28aaabae0208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|NoisifyInterface
block|}
name|NoisifyInterface
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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|noisify
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|noisify_dialog
parameter_list|(
name|gint
name|channels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gauss
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|noisify_ok_callback
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

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
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
DECL|variable|nvals
specifier|static
name|NoisifyVals
name|nvals
init|=
block|{
name|TRUE
block|,
block|{
literal|0.20
block|,
literal|0.20
block|,
literal|0.20
block|,
literal|0.20
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|noise_int
specifier|static
name|NoisifyInterface
name|noise_int
init|=
block|{
name|FALSE
comment|/* run */
block|}
decl_stmt|;
end_decl_stmt

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
name|GParamDef
name|args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (unused)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"independent"
block|,
literal|"Noise in channels independent"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"noise_1"
block|,
literal|"Noise in the first channel (red, gray)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"noise_2"
block|,
literal|"Noise in the second channel (green, gray_alpha)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"noise_3"
block|,
literal|"Noise in the third channel (blue)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"noise_4"
block|,
literal|"Noise in the fourth channel (alpha)"
block|}
block|}
decl_stmt|;
specifier|static
name|GParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
name|nargs
init|=
sizeof|sizeof
argument_list|(
name|args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_noisify"
argument_list|,
literal|"Adds random noise to a drawable's channels"
argument_list|,
literal|"More here later"
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"Torsten Martinsen"
argument_list|,
literal|"1996"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Noise/Noisify..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
argument_list|,
name|nreturn_vals
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GParam * param,gint * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
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
name|PARAM_STATUS
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
name|RUN_INTERACTIVE
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_noisify"
argument_list|,
operator|&
name|nvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|noisify_dialog
argument_list|(
name|drawable
operator|->
name|bpp
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
name|RUN_NONINTERACTIVE
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|8
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|nvals
operator|.
name|independent
operator|=
operator|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|2
index|]
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|nvals
operator|.
name|noise
index|[
literal|3
index|]
operator|=
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
block|}
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_noisify"
argument_list|,
operator|&
name|nvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
comment|/*  Make sure that the drawable is gray or RGB color  */
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Adding Noise..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
argument_list|)
expr_stmt|;
comment|/*  seed the random number generator  */
name|srand
argument_list|(
name|time
argument_list|(
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  compute the luminosity which exceeds the luminosity threshold  */
name|noisify
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
comment|/*  Store data  */
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_noisify"
argument_list|,
operator|&
name|nvals
argument_list|,
sizeof|sizeof
argument_list|(
name|NoisifyVals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("blur: cannot operate on indexed color images"); */
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
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
DECL|function|noisify (GDrawable * drawable)
name|noisify
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|p
decl_stmt|;
name|gint
name|noise
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
comment|/* initialize */
name|noise
operator|=
literal|0
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
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
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
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
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* Initialize progress */
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|2
argument_list|,
operator|&
name|src_rgn
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
name|src_row
operator|=
name|src_rgn
operator|.
name|data
expr_stmt|;
name|dest_row
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|src_rgn
operator|.
name|h
condition|;
name|row
operator|++
control|)
block|{
name|src
operator|=
name|src_row
expr_stmt|;
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|src_rgn
operator|.
name|w
condition|;
name|col
operator|++
control|)
block|{
if|if
condition|(
name|nvals
operator|.
name|independent
operator|==
name|FALSE
condition|)
name|noise
operator|=
call|(
name|gint
call|)
argument_list|(
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
operator|*
name|gauss
argument_list|()
operator|*
literal|127
argument_list|)
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|src_rgn
operator|.
name|bpp
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
name|nvals
operator|.
name|independent
operator|==
name|TRUE
condition|)
name|noise
operator|=
call|(
name|gint
call|)
argument_list|(
name|nvals
operator|.
name|noise
index|[
name|b
index|]
operator|*
name|gauss
argument_list|()
operator|*
literal|127
argument_list|)
expr_stmt|;
if|if
condition|(
name|nvals
operator|.
name|noise
index|[
name|b
index|]
operator|>
literal|0.0
condition|)
block|{
name|p
operator|=
name|src
index|[
name|b
index|]
operator|+
name|noise
expr_stmt|;
if|if
condition|(
name|p
operator|<
literal|0
condition|)
name|p
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|p
operator|>
literal|255
condition|)
name|p
operator|=
literal|255
expr_stmt|;
name|dest
index|[
name|b
index|]
operator|=
name|p
expr_stmt|;
block|}
else|else
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
name|b
index|]
expr_stmt|;
block|}
name|src
operator|+=
name|src_rgn
operator|.
name|bpp
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
operator|.
name|bpp
expr_stmt|;
block|}
name|src_row
operator|+=
name|src_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest_row
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
comment|/* Update progress */
name|progress
operator|+=
name|src_rgn
operator|.
name|w
operator|*
name|src_rgn
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
comment|/*  update the blurred region  */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|id
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
end_function

begin_function
specifier|static
name|gint
DECL|function|noisify_dialog (gint channels)
name|noisify_dialog
parameter_list|(
name|gint
name|channels
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
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
name|gchar
modifier|*
name|buffer
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|argc
operator|=
literal|1
expr_stmt|;
name|argv
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|argv
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
literal|"noisify"
argument_list|)
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Noisify"
argument_list|)
argument_list|,
literal|"noisify"
argument_list|,
name|gimp_plugin_help_func
argument_list|,
literal|"filters/noisify.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|noisify_ok_callback
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
name|_
argument_list|(
literal|"Cancel"
argument_list|)
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
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  parameter settings  */
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
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
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
name|channels
operator|+
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
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
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Independent"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|toggle
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|independent
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|nvals
operator|.
name|independent
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
if|if
condition|(
name|channels
operator|==
literal|1
condition|)
block|{
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
literal|"Gray:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|channels
operator|==
literal|2
condition|)
block|{
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
literal|"Gray:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
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
literal|2
argument_list|,
name|_
argument_list|(
literal|"Alpha:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|channels
operator|==
literal|3
condition|)
block|{
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
literal|"Red:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
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
literal|2
argument_list|,
name|_
argument_list|(
literal|"Green:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
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
literal|3
argument_list|,
name|_
argument_list|(
literal|"Blue:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|2
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|channels
operator|==
literal|4
condition|)
block|{
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
literal|"Red:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
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
literal|2
argument_list|,
name|_
argument_list|(
literal|"Green:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
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
literal|3
argument_list|,
name|_
argument_list|(
literal|"Blue:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|2
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
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
literal|4
argument_list|,
name|_
argument_list|(
literal|"Alpha:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
literal|3
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
literal|3
index|]
argument_list|)
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
name|channels
condition|;
name|i
operator|++
control|)
block|{
name|buffer
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Channel #%d:"
argument_list|)
argument_list|,
name|i
argument_list|)
expr_stmt|;
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
name|i
operator|+
literal|1
argument_list|,
name|buffer
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|nvals
operator|.
name|noise
index|[
name|i
index|]
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|nvals
operator|.
name|noise
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
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
name|noise_int
operator|.
name|run
return|;
block|}
end_function

begin_comment
comment|/*  * Return a Gaussian (aka normal) random variable.  *  * Adapted from ppmforge.c, which is part of PBMPLUS.  * The algorithm comes from:  * 'The Science Of Fractal Images'. Peitgen, H.-O., and Saupe, D. eds.  * Springer Verlag, New York, 1988.  */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|gauss (void)
name|gauss
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gdouble
name|sum
init|=
literal|0.0
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
name|sum
operator|+=
name|rand
argument_list|()
operator|&
literal|0x7FFF
expr_stmt|;
return|return
name|sum
operator|*
literal|5.28596089837e-5
operator|-
literal|3.46410161514
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|noisify_ok_callback (GtkWidget * widget,gpointer data)
name|noisify_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|noise_int
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

end_unit

