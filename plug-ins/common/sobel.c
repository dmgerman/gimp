begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This plugin by thorsten@arch.usyd.edu.au           */
end_comment

begin_comment
comment|/* Based on S&P's Gauss and Blur filters              */
end_comment

begin_comment
comment|/* updated 11/04/97:    don't use rint;    if gamma-channel: set to white if at least one colour channel is>15 */
end_comment

begin_comment
comment|/* Update 3/10/97:    #ifdef Max and Min,     save old values    correct 'cancel' behaviour */
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon289230560108
block|{
DECL|member|horizontal
name|gint
name|horizontal
decl_stmt|;
DECL|member|vertical
name|gint
name|vertical
decl_stmt|;
DECL|member|keep_sign
name|gint
name|keep_sign
decl_stmt|;
DECL|typedef|SobelValues
block|}
name|SobelValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon289230560208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|SobelInterface
block|}
name|SobelInterface
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
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
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
name|sobel
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|horizontal
parameter_list|,
name|gint
name|vertical
parameter_list|,
name|gint
name|keep_sign
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Sobel interface  */
end_comment

begin_function_decl
specifier|static
name|gint
name|sobel_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Sobel helper functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|sobel_ok_callback
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
name|sobel_toggle_update
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
name|sobel_prepare_row
parameter_list|(
name|GPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
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
DECL|variable|bvals
specifier|static
name|SobelValues
name|bvals
init|=
block|{
name|TRUE
block|,
comment|/*  horizontal sobel  */
name|TRUE
block|,
comment|/*  vertical sobel  */
name|TRUE
comment|/*  keep sign  */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|bint
specifier|static
name|SobelInterface
name|bint
init|=
block|{
name|FALSE
comment|/*  run  */
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
literal|"horizontal"
block|,
literal|"Sobel in horizontal direction"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"vertical"
block|,
literal|"Sobel in vertical direction"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"keep_sign"
block|,
literal|"Keep sign of result (one direction only)"
block|}
block|,   }
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
literal|"plug_in_sobel"
argument_list|,
literal|"Edge Detection with Sobel Operation"
argument_list|,
literal|"This plugin calculates the gradient with a sobel operator. The user can specify which direction to use. When both directions are used, the result is the RMS of the two gradients; if only one direction is used, the result either the absolut value of the gradient, or 127 + gradient (if the 'keep sign' switch is on). This way, information about the direction of the gradient is preserved. Resulting images are not autoscaled."
argument_list|,
literal|"Thorsten Schnier"
argument_list|,
literal|"Thorsten Schnier"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Edge-Detect/Sobel..."
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
literal|"plug_in_sobel"
argument_list|,
operator|&
name|bvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|sobel_dialog
argument_list|()
condition|)
return|return;
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
literal|6
condition|)
block|{
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|bvals
operator|.
name|horizontal
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
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|bvals
operator|.
name|vertical
operator|=
operator|(
name|param
index|[
literal|5
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
name|bvals
operator|.
name|keep_sign
operator|=
operator|(
name|param
index|[
literal|6
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
literal|"plug_in_sobel"
argument_list|,
operator|&
name|bvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
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
name|sobel
argument_list|(
name|drawable
argument_list|,
name|bvals
operator|.
name|horizontal
argument_list|,
name|bvals
operator|.
name|vertical
argument_list|,
name|bvals
operator|.
name|keep_sign
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
literal|"plug_in_sobel"
argument_list|,
operator|&
name|bvals
argument_list|,
sizeof|sizeof
argument_list|(
name|bvals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("sobel: cannot operate on indexed color images"); */
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
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
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|sobel_dialog (void)
name|sobel_dialog
parameter_list|(
name|void
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
name|vbox
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
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
literal|"sobel"
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
literal|"Sobel Edge Detection"
argument_list|)
argument_list|,
literal|"sobel"
argument_list|,
name|gimp_plugin_help_func
argument_list|,
literal|"filters/sobel.html"
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
name|sobel_ok_callback
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Sobel Horizontally"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
operator|(
name|GtkSignalFunc
operator|)
name|sobel_toggle_update
argument_list|,
operator|&
name|bvals
operator|.
name|horizontal
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|bvals
operator|.
name|horizontal
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Sobel Vertically"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
operator|(
name|GtkSignalFunc
operator|)
name|sobel_toggle_update
argument_list|,
operator|&
name|bvals
operator|.
name|vertical
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|bvals
operator|.
name|vertical
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Keep Sign of Result (one Direction only)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
operator|(
name|GtkSignalFunc
operator|)
name|sobel_toggle_update
argument_list|,
operator|&
name|bvals
operator|.
name|keep_sign
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|bvals
operator|.
name|vertical
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
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
name|bint
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|sobel_prepare_row (GPixelRgn * pixel_rgn,guchar * data,int x,int y,int w)
name|sobel_prepare_row
parameter_list|(
name|GPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|)
block|{
name|int
name|b
decl_stmt|;
if|if
condition|(
name|y
operator|==
literal|0
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
operator|(
name|y
operator|+
literal|1
operator|)
argument_list|,
name|w
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|y
operator|==
name|pixel_rgn
operator|->
name|h
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
operator|(
name|y
operator|-
literal|1
operator|)
argument_list|,
name|w
argument_list|)
expr_stmt|;
else|else
name|gimp_pixel_rgn_get_row
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|)
expr_stmt|;
comment|/*  Fill in edge pixels  */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|pixel_rgn
operator|->
name|bpp
condition|;
name|b
operator|++
control|)
block|{
name|data
index|[
operator|-
operator|(
name|int
operator|)
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
operator|=
name|data
index|[
name|b
index|]
expr_stmt|;
name|data
index|[
name|w
operator|*
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
operator|=
name|data
index|[
operator|(
name|w
operator|-
literal|1
operator|)
operator|*
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|SIGN (a)
define|#
directive|define
name|SIGN
parameter_list|(
name|a
parameter_list|)
value|(((a)> 0) ? 1 : -1)
end_define

begin_define
DECL|macro|RMS (a,b)
define|#
directive|define
name|RMS
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|(sqrt (pow ((a),2) + pow ((b), 2)))
end_define

begin_function
specifier|static
name|void
DECL|function|sobel (GDrawable * drawable,gint do_horizontal,gint do_vertical,gint keep_sign)
name|sobel
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|do_horizontal
parameter_list|,
name|gint
name|do_vertical
parameter_list|,
name|gint
name|keep_sign
parameter_list|)
block|{
name|GPixelRgn
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
name|gint
name|gradient
decl_stmt|,
name|hor_gradient
decl_stmt|,
name|ver_gradient
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
name|prev_row
decl_stmt|,
modifier|*
name|pr
decl_stmt|;
name|guchar
modifier|*
name|cur_row
decl_stmt|,
modifier|*
name|cr
decl_stmt|;
name|guchar
modifier|*
name|next_row
decl_stmt|,
modifier|*
name|nr
decl_stmt|;
name|guchar
modifier|*
name|tmp
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
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
name|alpha
decl_stmt|;
name|gint
name|counter
decl_stmt|;
comment|/* Get the input area. This is the bounding box of the selection in    *  the image (or the entire image if there is no selection). Only    *  operating on the input area is simply an optimization. It doesn't    *  need to be done for correct operation. (It simply makes it go    *  faster, since fewer pixels need to be operated on).    */
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
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Sobel Edge Detecting..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Get the size of the input image. (This will/must be the same    *  as the size of the output image.    */
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
name|alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
comment|/*  allocate row buffers  */
name|prev_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
operator|(
name|x2
operator|-
name|x1
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|cur_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
operator|(
name|x2
operator|-
name|x1
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|next_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
operator|(
name|x2
operator|-
name|x1
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*  initialize the pixel regions  */
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
name|pr
operator|=
name|prev_row
operator|+
name|bytes
expr_stmt|;
name|cr
operator|=
name|cur_row
operator|+
name|bytes
expr_stmt|;
name|nr
operator|=
name|next_row
operator|+
name|bytes
expr_stmt|;
name|sobel_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|pr
argument_list|,
name|x1
argument_list|,
name|y1
operator|-
literal|1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|sobel_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|cr
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
argument_list|)
expr_stmt|;
name|counter
operator|=
literal|0
expr_stmt|;
comment|/*  loop through the rows, applying the sobel convolution  */
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
comment|/*  prepare the next row  */
name|sobel_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|nr
argument_list|,
name|x1
argument_list|,
name|row
operator|+
literal|1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|d
operator|=
name|dest
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
condition|;
name|col
operator|++
control|)
block|{
name|hor_gradient
operator|=
operator|(
name|do_horizontal
condition|?
operator|(
operator|(
name|pr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
literal|2
operator|*
name|pr
index|[
name|col
index|]
operator|+
name|pr
index|[
name|col
operator|+
name|bytes
index|]
operator|)
operator|-
operator|(
name|nr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
literal|2
operator|*
name|nr
index|[
name|col
index|]
operator|+
name|nr
index|[
name|col
operator|+
name|bytes
index|]
operator|)
operator|)
else|:
literal|0
operator|)
expr_stmt|;
name|ver_gradient
operator|=
operator|(
name|do_vertical
condition|?
operator|(
operator|(
name|pr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
literal|2
operator|*
name|cr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
name|nr
index|[
name|col
operator|-
name|bytes
index|]
operator|)
operator|-
operator|(
name|pr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
literal|2
operator|*
name|cr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
name|nr
index|[
name|col
operator|+
name|bytes
index|]
operator|)
operator|)
else|:
literal|0
operator|)
expr_stmt|;
name|gradient
operator|=
operator|(
name|do_vertical
operator|&&
name|do_horizontal
operator|)
condition|?
operator|(
name|ROUND
argument_list|(
name|RMS
argument_list|(
name|hor_gradient
argument_list|,
name|ver_gradient
argument_list|)
argument_list|)
operator|/
literal|5.66
operator|)
comment|/* always>0 */
else|:
operator|(
name|keep_sign
condition|?
operator|(
literal|127
operator|+
operator|(
name|ROUND
argument_list|(
operator|(
name|hor_gradient
operator|+
name|ver_gradient
operator|)
operator|/
literal|8.0
argument_list|)
operator|)
operator|)
else|:
operator|(
name|ROUND
argument_list|(
name|abs
argument_list|(
name|hor_gradient
operator|+
name|ver_gradient
argument_list|)
operator|/
literal|4.0
argument_list|)
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|alpha
operator|&&
operator|(
operator|(
operator|(
name|col
operator|+
literal|1
operator|)
operator|%
name|bytes
operator|)
operator|==
literal|0
operator|)
condition|)
block|{
comment|/* the alpha channel */
operator|*
name|d
operator|++
operator|=
operator|(
name|counter
operator|==
literal|0
operator|)
condition|?
literal|0
else|:
literal|255
expr_stmt|;
name|counter
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
operator|*
name|d
operator|++
operator|=
name|gradient
expr_stmt|;
if|if
condition|(
name|gradient
operator|>
literal|10
condition|)
name|counter
operator|++
expr_stmt|;
block|}
block|}
comment|/*  store the dest  */
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
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
comment|/*  shuffle the row pointers  */
name|tmp
operator|=
name|pr
expr_stmt|;
name|pr
operator|=
name|cr
expr_stmt|;
name|cr
operator|=
name|nr
expr_stmt|;
name|nr
operator|=
name|tmp
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
name|double
operator|)
name|row
operator|/
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  update the sobeled region  */
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
name|free
argument_list|(
name|prev_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|cur_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|next_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Sobel interface functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|sobel_ok_callback (GtkWidget * widget,gpointer data)
name|sobel_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|bint
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

begin_function
specifier|static
name|void
DECL|function|sobel_toggle_update (GtkWidget * widget,gpointer data)
name|sobel_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|int
modifier|*
name|toggle_val
decl_stmt|;
name|toggle_val
operator|=
operator|(
name|int
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
operator|*
name|toggle_val
operator|=
name|TRUE
expr_stmt|;
else|else
operator|*
name|toggle_val
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

