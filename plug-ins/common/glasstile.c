begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is the Glass Tile plug-in for the GIMP 0.99  * Version 1.01  *  * Copyright (C) 1997 Karl-Johan Andersson (t96kja@student.tdb.uu.se)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_comment
comment|/*  * This filter divide the image into square "glass"-blocks in which  * the image is refracted.   *   * The alpha-channel is left unchanged.  *   * Please send any comments or suggestions to  * Karl-Johan Andersson (t96kja@student.tdb.uu.se)  *   */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
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
DECL|struct|__anon29c590af0108
typedef|typedef
struct|struct
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
DECL|struct|__anon29c590af0208
typedef|typedef
struct|struct
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
name|gint
name|glass_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|glass_close_callback
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
name|glass_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
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
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* --- Variables --- */
end_comment

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
parameter_list|()
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
literal|"tilex"
block|,
literal|"Tile width (10 - 50)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"tiley"
block|,
literal|"Tile height (10 - 50)"
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
literal|"plug_in_glasstile"
argument_list|,
name|_
argument_list|(
literal|"Divide the image into square glassblocks"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"More here later"
argument_list|)
argument_list|,
literal|"Karl-Johan Andersson"
argument_list|,
comment|/* Author */
literal|"Karl-Johan Andersson"
argument_list|,
comment|/* Copyright */
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Glass Effects/Glass Tile..."
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
DECL|function|run (gchar * name,gint nparams,GParam * param,gint * nreturn_vals,GParam ** return_vals)
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
argument_list|()
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
literal|5
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
name|STATUS_CALLING_ERROR
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
name|STATUS_CALLING_ERROR
expr_stmt|;
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
name|STATUS_SUCCESS
condition|)
block|{
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
block|}
else|else
block|{
comment|/* gimp_message ("glasstile: cannot operate on indexed color images"); */
name|status
operator|=
name|STATUS_EXECUTION_ERROR
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
DECL|function|glass_dialog ()
specifier|static
name|gint
name|glass_dialog
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|hbbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
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
name|adjustment
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
literal|"glasstile"
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
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Glass Tile"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
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
operator|(
name|GtkSignalFunc
operator|)
name|glass_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Action area  */
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|hbbox
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_button_box_set_spacing
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|hbbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|hbbox
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
name|hbbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"OK"
argument_list|)
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
name|glass_ok_callback
argument_list|,
name|dlg
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
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
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
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
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|10
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
literal|2
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* table height, width */
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|10
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
comment|/* Horizontal scale - Width */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Tile Width"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|5
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* xStart, xEnd, yStart, yEnd */
name|adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|gtvals
operator|.
name|xblock
argument_list|,
literal|10
argument_list|,
literal|50
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|glass_scale_update
argument_list|,
operator|&
operator|(
name|gtvals
operator|.
name|xblock
operator|)
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|scale
argument_list|,
literal|150
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|scale
argument_list|,
literal|1
argument_list|,
literal|2
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
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
comment|/* Horizontal scale - Height */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Tile Height"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|5
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|gtvals
operator|.
name|yblock
argument_list|,
literal|10
argument_list|,
literal|50
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|glass_scale_update
argument_list|,
operator|&
operator|(
name|gtvals
operator|.
name|yblock
operator|)
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|scale
argument_list|,
literal|150
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|scale
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
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
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
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
name|gt_int
operator|.
name|run
return|;
block|}
end_function

begin_comment
comment|/*  -  Interface functions  -  */
end_comment

begin_function
DECL|function|glass_close_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|glass_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
DECL|function|glass_ok_callback (GtkWidget * widget,gpointer data)
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

begin_function
DECL|function|glass_scale_update (GtkAdjustment * adjustment,gpointer data)
specifier|static
name|void
name|glass_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
modifier|*
name|dptr
init|=
operator|(
name|gint
operator|*
operator|)
name|data
decl_stmt|;
operator|*
name|dptr
operator|=
operator|(
name|gint
operator|)
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  -  Filter function  -  */
end_comment

begin_function
DECL|function|glasstile (GDrawable * drawable)
specifier|static
name|void
name|glasstile
parameter_list|(
name|GDrawable
modifier|*
name|drawable
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
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|,
modifier|*
name|ad
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
decl_stmt|,
name|cbytes
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
comment|/*  allocate row buffers  */
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
name|ad
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
name|cbytes
operator|%
literal|2
operator|==
literal|0
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
if|if
condition|(
name|ypixel2
operator|<
name|height
condition|)
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
else|else
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|cur_row
argument_list|,
name|x1
argument_list|,
name|y2
operator|-
literal|1
argument_list|,
name|iwidth
argument_list|)
expr_stmt|;
if|if
condition|(
name|cbytes
operator|!=
name|bytes
condition|)
comment|/* Alpha check */
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|ad
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
name|yhalv
expr_stmt|;
name|yoffs
operator|-=
name|yplus
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
operator|(
name|x2
operator|-
name|x1
operator|)
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cbytes
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
name|cbytes
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
if|if
condition|(
name|cbytes
operator|!=
name|bytes
condition|)
comment|/* Alpha channel unchanged */
name|d
index|[
name|xpixel1
operator|+
name|cbytes
index|]
operator|=
name|ad
index|[
name|xpixel1
operator|+
name|cbytes
index|]
expr_stmt|;
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
name|xhalv
expr_stmt|;
name|xoffs
operator|-=
name|xplus
expr_stmt|;
block|}
block|}
comment|/*  Store the dest  */
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
comment|/*  Update region  */
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
name|cur_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|ad
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

