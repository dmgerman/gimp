begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is the Struc plug-in for the GIMP 0.99  * Version 1.01  *  * Copyright (C) 1997 Karl-Johan Andersson (t96kja@student.tdb.uu.se)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_comment
comment|/* Don't ask me why its called "Struc". The first .c-file  * just happend to be called struc.c  *   * Some code for the dialog was taken from Motion Blur plug-in for   * GIMP 0.99 by Daniel Skarda (0rfelyus@atrey.karlin.mff.cuni.cz)   *   * Please send any comments or suggestions to me,  * Karl-Johan Andersson (t96kja@student.tdb.uu.se)  *   */
end_comment

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
file|"struc.h"
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* --- Typedefs --- */
end_comment

begin_typedef
DECL|struct|__anon2b425ed30108
typedef|typedef
struct|struct
block|{
DECL|member|direction
name|gint
name|direction
decl_stmt|;
DECL|member|depth
name|gint
name|depth
decl_stmt|;
DECL|typedef|StrucValues
block|}
name|StrucValues
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b425ed30208
typedef|typedef
struct|struct
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|StructInterface
block|}
name|StructInterface
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
name|struc_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|struc_close_callback
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
name|struc_ok_callback
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
name|struc_scale_update
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
name|struc_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint32
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|strucpi
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
DECL|variable|svals
specifier|static
name|StrucValues
name|svals
init|=
block|{
literal|0
block|,
comment|/* direction*/
literal|4
comment|/* depth */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|s_int
specifier|static
name|StructInterface
name|s_int
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
literal|"direction"
block|,
literal|"Light direction (0 - 3)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"depth"
block|,
literal|"Texture depth (1 - 50)"
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
name|gimp_install_procedure
argument_list|(
literal|"plug_in_apply_canvas"
argument_list|,
literal|"Adds a canvas texture map to the picture"
argument_list|,
literal|"This function applies a canvas texture map to the drawable."
argument_list|,
literal|"Karl-Johan Andersson"
argument_list|,
comment|/* Author */
literal|"Karl-Johan Andersson"
argument_list|,
comment|/* Copyright */
literal|"1997"
argument_list|,
literal|"<Image>/Filters/Artistic/Apply Canvas"
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
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_struc"
argument_list|,
operator|&
name|svals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|struc_dialog
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
name|svals
operator|.
name|direction
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
name|svals
operator|.
name|depth
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
name|svals
operator|.
name|direction
operator|<
literal|0
operator|||
name|svals
operator|.
name|direction
operator|>
literal|4
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|svals
operator|.
name|depth
operator|<
literal|1
operator|||
name|svals
operator|.
name|depth
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
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_struc"
argument_list|,
operator|&
name|svals
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
name|gimp_drawable_color
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_gray
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
literal|"struc"
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
name|strucpi
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
literal|"plug_in_struc"
argument_list|,
operator|&
name|svals
argument_list|,
sizeof|sizeof
argument_list|(
name|StrucValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("struc: cannot operate on indexed color images"); */
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
DECL|function|struc_dialog (void)
specifier|static
name|gint
name|struc_dialog
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
name|oframe
decl_stmt|,
modifier|*
name|iframe
decl_stmt|;
name|GtkWidget
modifier|*
name|abox
decl_stmt|,
modifier|*
name|bbox
decl_stmt|,
modifier|*
name|cbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|,
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
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
literal|"struc"
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
literal|"Struc"
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
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|0
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
name|struc_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Action area */
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"OK"
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
name|struc_ok_callback
argument_list|,
name|dlg
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
literal|"Cancel"
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
name|GTK_DIALOG
argument_list|(
name|dlg
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
comment|/* Parameter settings */
name|abox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
literal|5
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
name|abox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|oframe
operator|=
name|gtk_frame_new
argument_list|(
literal|"Filter options"
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|oframe
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|abox
argument_list|)
argument_list|,
name|oframe
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|bbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|bbox
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|oframe
argument_list|)
argument_list|,
name|bbox
argument_list|)
expr_stmt|;
comment|/* Radio buttons */
name|iframe
operator|=
name|gtk_frame_new
argument_list|(
literal|"Direction"
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|iframe
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|bbox
argument_list|)
argument_list|,
name|iframe
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|cbox
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|iframe
argument_list|)
argument_list|,
name|cbox
argument_list|)
expr_stmt|;
block|{
name|int
name|i
decl_stmt|;
name|char
modifier|*
name|name
index|[
literal|4
index|]
init|=
block|{
literal|"Top-right"
block|,
literal|"Top-left"
block|,
literal|"Bottom-left"
block|,
literal|"Bottom-right"
block|}
decl_stmt|;
name|button
operator|=
name|NULL
expr_stmt|;
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
block|{
name|button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
operator|(
name|button
operator|==
name|NULL
operator|)
condition|?
name|NULL
else|:
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
argument_list|,
name|name
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|(
name|svals
operator|.
name|direction
operator|==
name|i
operator|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|struc_toggle_update
argument_list|,
operator|(
name|gpointer
operator|)
name|i
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|cbox
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
block|}
block|}
name|gtk_widget_show
argument_list|(
name|cbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|iframe
argument_list|)
expr_stmt|;
comment|/* Horizontal scale */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Depth"
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|bbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|svals
operator|.
name|depth
argument_list|,
literal|1
argument_list|,
literal|50
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|adjustment
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|struc_scale_update
argument_list|,
operator|&
operator|(
name|svals
operator|.
name|depth
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
name|GTK_WIDGET
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|150
argument_list|,
literal|30
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|bbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|bbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|oframe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
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
name|s_int
operator|.
name|run
return|;
block|}
end_function

begin_comment
comment|/* Interface functions */
end_comment

begin_function
DECL|function|struc_close_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|struc_close_callback
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
DECL|function|struc_ok_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|struc_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|s_int
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
DECL|function|struc_scale_update (GtkAdjustment * adjustment,gpointer data)
specifier|static
name|void
name|struc_scale_update
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

begin_function
DECL|function|struc_toggle_update (GtkWidget * widget,gint32 value)
specifier|static
name|void
name|struc_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint32
name|value
parameter_list|)
block|{
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
name|svals
operator|.
name|direction
operator|=
name|value
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Filter function */
end_comment

begin_function
DECL|function|strucpi (GDrawable * drawable)
specifier|static
name|void
name|strucpi
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
name|rrow
decl_stmt|,
name|rcol
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
name|varde
decl_stmt|;
name|gint
name|xm
decl_stmt|,
name|ym
decl_stmt|,
name|offs
decl_stmt|;
name|gfloat
name|mult
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
name|mult
operator|=
operator|(
name|gfloat
operator|)
name|svals
operator|.
name|depth
operator|*
literal|0.25
expr_stmt|;
switch|switch
condition|(
name|svals
operator|.
name|direction
condition|)
block|{
case|case
literal|0
case|:
name|xm
operator|=
literal|1
expr_stmt|;
name|ym
operator|=
literal|128
expr_stmt|;
name|offs
operator|=
literal|0
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|xm
operator|=
operator|-
literal|1
expr_stmt|;
name|ym
operator|=
literal|128
expr_stmt|;
name|offs
operator|=
literal|127
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|xm
operator|=
literal|128
expr_stmt|;
name|ym
operator|=
literal|1
expr_stmt|;
name|offs
operator|=
literal|0
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|xm
operator|=
literal|128
expr_stmt|;
name|ym
operator|=
operator|-
literal|1
expr_stmt|;
name|offs
operator|=
literal|128
expr_stmt|;
break|break;
default|default:
name|xm
operator|=
literal|1
expr_stmt|;
name|ym
operator|=
literal|128
expr_stmt|;
name|offs
operator|=
literal|0
expr_stmt|;
break|break;
block|}
comment|/*  Loop through the rows */
name|rrow
operator|=
literal|0
expr_stmt|;
name|rcol
operator|=
literal|0
expr_stmt|;
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
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|cur_row
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
name|d
operator|=
name|dest
expr_stmt|;
name|rcol
operator|=
literal|0
expr_stmt|;
switch|switch
condition|(
name|bytes
condition|)
block|{
case|case
literal|1
case|:
comment|/* Grayscale */
case|case
literal|2
case|:
comment|/* Grayscale alpha */
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
operator|+=
name|bytes
control|)
block|{
name|varde
operator|=
name|cur_row
index|[
name|col
index|]
operator|+
name|mult
operator|*
name|sdata
index|[
name|rcol
operator|*
name|xm
operator|+
name|rrow
operator|*
name|ym
operator|+
name|offs
index|]
expr_stmt|;
if|if
condition|(
name|varde
operator|>
literal|255
condition|)
name|varde
operator|=
literal|255
expr_stmt|;
if|if
condition|(
name|varde
operator|<
literal|0
condition|)
name|varde
operator|=
literal|0
expr_stmt|;
operator|*
name|d
operator|++
operator|=
operator|(
name|guchar
operator|)
name|varde
expr_stmt|;
if|if
condition|(
name|bytes
operator|==
literal|2
condition|)
operator|*
name|d
operator|++
operator|=
name|cur_row
index|[
name|col
operator|+
literal|1
index|]
expr_stmt|;
name|rcol
operator|++
expr_stmt|;
if|if
condition|(
name|rcol
operator|==
literal|128
condition|)
name|rcol
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
comment|/* RGB */
case|case
literal|4
case|:
comment|/* RGB alpha */
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
operator|+=
name|bytes
control|)
block|{
name|varde
operator|=
name|cur_row
index|[
name|col
index|]
operator|+
name|mult
operator|*
name|sdata
index|[
name|rcol
operator|*
name|xm
operator|+
name|rrow
operator|*
name|ym
operator|+
name|offs
index|]
expr_stmt|;
if|if
condition|(
name|varde
operator|>
literal|255
condition|)
name|varde
operator|=
literal|255
expr_stmt|;
if|if
condition|(
name|varde
operator|<
literal|0
condition|)
name|varde
operator|=
literal|0
expr_stmt|;
operator|*
name|d
operator|++
operator|=
operator|(
name|guchar
operator|)
name|varde
expr_stmt|;
name|varde
operator|=
name|cur_row
index|[
name|col
operator|+
literal|1
index|]
operator|+
name|mult
operator|*
name|sdata
index|[
name|rcol
operator|*
name|xm
operator|+
name|rrow
operator|*
name|ym
operator|+
name|offs
index|]
expr_stmt|;
if|if
condition|(
name|varde
operator|>
literal|255
condition|)
name|varde
operator|=
literal|255
expr_stmt|;
if|if
condition|(
name|varde
operator|<
literal|0
condition|)
name|varde
operator|=
literal|0
expr_stmt|;
operator|*
name|d
operator|++
operator|=
operator|(
name|guchar
operator|)
name|varde
expr_stmt|;
name|varde
operator|=
name|cur_row
index|[
name|col
operator|+
literal|2
index|]
operator|+
name|mult
operator|*
name|sdata
index|[
name|rcol
operator|*
name|xm
operator|+
name|rrow
operator|*
name|ym
operator|+
name|offs
index|]
expr_stmt|;
if|if
condition|(
name|varde
operator|>
literal|255
condition|)
name|varde
operator|=
literal|255
expr_stmt|;
if|if
condition|(
name|varde
operator|<
literal|0
condition|)
name|varde
operator|=
literal|0
expr_stmt|;
operator|*
name|d
operator|++
operator|=
operator|(
name|guchar
operator|)
name|varde
expr_stmt|;
if|if
condition|(
name|bytes
operator|==
literal|4
condition|)
operator|*
name|d
operator|++
operator|=
name|cur_row
index|[
name|col
operator|+
literal|3
index|]
expr_stmt|;
name|rcol
operator|++
expr_stmt|;
if|if
condition|(
name|rcol
operator|==
literal|128
condition|)
name|rcol
operator|=
literal|0
expr_stmt|;
block|}
break|break;
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
name|rrow
operator|++
expr_stmt|;
if|if
condition|(
name|rrow
operator|==
literal|128
condition|)
name|rrow
operator|=
literal|0
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
comment|/*  update the textured region  */
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
block|}
end_function

end_unit

