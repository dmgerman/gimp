begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Selective gaussian blur filter for the GIMP, version 0.1  * Adapted from the original gaussian blur filter by Spencer Kimball and  * Peter Mattis.  *  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Thom van Os<thom@vanos.com>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Changelog:  *  * v0.1 	990202, TVO  * 	First release  *  * To do:  *	- support for horizontal or vertical only blur  *	- use memory more efficiently, smaller regions at a time  *	- integrating with other convolution matrix based filters ?  *	- create more selective and adaptive filters  *	- threading  *	- optimization  *  */
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
file|<string.h>
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

begin_include
include|#
directive|include
file|"libgimp/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|100
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a55e3280108
block|{
DECL|member|radius
name|gdouble
name|radius
decl_stmt|;
DECL|member|maxdelta
name|gint
name|maxdelta
decl_stmt|;
DECL|typedef|BlurValues
block|}
name|BlurValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2a55e3280208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|BlurInterface
block|}
name|BlurInterface
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
name|sel_gauss
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|gint
name|maxdelta
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Gaussian blur interface  */
end_comment

begin_function_decl
specifier|static
name|gint
name|sel_gauss_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Gaussian blur helper functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|sel_gauss_close_callback
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
name|sel_gauss_ok_callback
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
name|sel_gauss_entry_callback
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
name|sel_gauss_delta_callback
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
DECL|variable|bvals
specifier|static
name|BlurValues
name|bvals
init|=
block|{
literal|5.0
block|,
comment|/*  radius  */
literal|50
comment|/* maxdelta */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|bint
specifier|static
name|BlurInterface
name|bint
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
name|PARAM_FLOAT
block|,
literal|"radius"
block|,
literal|"Radius of gaussian blur (in pixels> 1.0)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"maxdelta"
block|,
literal|"Maximum delta"
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
name|gint
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
name|gint
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_sel_gauss"
argument_list|,
name|_
argument_list|(
literal|"Applies a selective gaussian blur to the specified drawable."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"This filter functions similar to the regular gaussian blur filter except that neighbouring pixels that differ more than the given maxdelta parameter will not be blended with. This way with the correct parameters, an image can be smoothed out without losing details. However, this filter can be rather slow."
argument_list|)
argument_list|,
literal|"Thom van Os"
argument_list|,
literal|"Thom van Os"
argument_list|,
literal|"1999"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Blur/Selective Gaussian Blur..."
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
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|gdouble
name|radius
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
name|INIT_I18N_UI
argument_list|()
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
comment|/* Possibly retrieve data */
name|gimp_get_data
argument_list|(
literal|"plug_in_sel_gauss"
argument_list|,
operator|&
name|bvals
argument_list|)
expr_stmt|;
comment|/* First acquire information with a dialog */
if|if
condition|(
operator|!
name|sel_gauss_dialog
argument_list|()
condition|)
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
comment|/* Make sure all the arguments are there! */
if|if
condition|(
name|nparams
operator|!=
literal|7
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
name|bvals
operator|.
name|radius
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|bvals
operator|.
name|maxdelta
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
expr_stmt|;
if|if
condition|(
name|bvals
operator|.
name|maxdelta
operator|<
literal|0
condition|)
name|bvals
operator|.
name|maxdelta
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|bvals
operator|.
name|maxdelta
operator|>
literal|255
condition|)
name|bvals
operator|.
name|maxdelta
operator|=
literal|255
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
operator|&&
operator|(
name|bvals
operator|.
name|radius
operator|<
literal|1.0
operator|)
condition|)
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
comment|/* Possibly retrieve data */
name|gimp_get_data
argument_list|(
literal|"plug_in_sel_gauss"
argument_list|,
operator|&
name|bvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|!=
name|STATUS_SUCCESS
condition|)
block|{
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
return|return;
block|}
comment|/* Get the specified drawable */
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
comment|/* Make sure that the drawable is gray or RGB color */
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
literal|"Selective Gaussian Blur"
argument_list|)
argument_list|)
expr_stmt|;
name|radius
operator|=
name|fabs
argument_list|(
name|bvals
operator|.
name|radius
argument_list|)
operator|+
literal|1.0
expr_stmt|;
comment|/* run the gaussian blur */
name|sel_gauss
argument_list|(
name|drawable
argument_list|,
name|radius
argument_list|,
name|bvals
operator|.
name|maxdelta
argument_list|)
expr_stmt|;
comment|/* Store data */
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_sel_gauss"
argument_list|,
operator|&
name|bvals
argument_list|,
sizeof|sizeof
argument_list|(
name|BlurValues
argument_list|)
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
block|}
else|else
block|{
name|gimp_message
argument_list|(
name|_
argument_list|(
literal|"sel_gauss: Cannot operate on indexed color images"
argument_list|)
argument_list|)
expr_stmt|;
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
DECL|function|sel_gauss_dialog ()
specifier|static
name|gint
name|sel_gauss_dialog
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
name|entry
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|gchar
name|buffer
index|[
literal|12
index|]
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
literal|"gauss"
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
literal|"Selective Gaussian Blur"
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
name|sel_gauss_close_callback
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
name|sel_gauss_ok_callback
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
comment|/* parameter settings */
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
name|vbox
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
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Blur Radius: "
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
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
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|entry
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|entry
argument_list|,
name|ENTRY_WIDTH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"%f"
argument_list|,
name|bvals
operator|.
name|radius
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|sel_gauss_entry_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Max. delta: "
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
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
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|entry
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|entry
argument_list|,
name|ENTRY_WIDTH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|buffer
argument_list|,
literal|"%d"
argument_list|,
name|bvals
operator|.
name|maxdelta
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|sel_gauss_delta_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
DECL|function|init_matrix (gdouble radius,gdouble ** mat,gint num)
name|void
name|init_matrix
parameter_list|(
name|gdouble
name|radius
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|mat
parameter_list|,
name|gint
name|num
parameter_list|)
block|{
name|int
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|gdouble
name|sd
decl_stmt|,
name|c1
decl_stmt|,
name|c2
decl_stmt|;
comment|/* This formula isn't really correct, but it'll do */
name|sd
operator|=
name|radius
operator|/
literal|3.329042969
expr_stmt|;
name|c1
operator|=
literal|1.0
operator|/
name|sqrt
argument_list|(
literal|2.0
operator|*
name|G_PI
operator|*
name|sd
argument_list|)
expr_stmt|;
name|c2
operator|=
operator|-
literal|2.0
operator|*
operator|(
name|sd
operator|*
name|sd
operator|)
expr_stmt|;
for|for
control|(
name|dy
operator|=
literal|0
init|;
name|dy
operator|<
name|num
condition|;
name|dy
operator|++
control|)
block|{
for|for
control|(
name|dx
operator|=
name|dy
init|;
name|dx
operator|<
name|num
condition|;
name|dx
operator|++
control|)
block|{
name|mat
index|[
name|dx
index|]
index|[
name|dy
index|]
operator|=
name|c1
operator|*
name|exp
argument_list|(
operator|(
operator|(
name|dx
operator|*
name|dx
operator|)
operator|+
operator|(
name|dy
operator|*
name|dy
operator|)
operator|)
operator|/
name|c2
argument_list|)
expr_stmt|;
name|mat
index|[
name|dy
index|]
index|[
name|dx
index|]
operator|=
name|mat
index|[
name|dx
index|]
index|[
name|dy
index|]
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
DECL|function|matrixmult (guchar * src,guchar * dest,gint width,gint height,gdouble ** mat,gint numrad,gint bytes,gint has_alpha,gint maxdelta)
specifier|static
name|void
name|matrixmult
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|mat
parameter_list|,
name|gint
name|numrad
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|gint
name|has_alpha
parameter_list|,
name|gint
name|maxdelta
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|b
decl_stmt|,
name|nb
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|six
decl_stmt|,
name|dix
decl_stmt|,
name|tmp
decl_stmt|;
name|gdouble
name|sum
decl_stmt|,
name|fact
decl_stmt|,
name|d
decl_stmt|,
name|alpha
init|=
literal|1.0
decl_stmt|;
name|nb
operator|=
name|bytes
operator|-
operator|(
name|has_alpha
condition|?
literal|1
else|:
literal|0
operator|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
name|dix
operator|=
operator|(
name|bytes
operator|*
operator|(
operator|(
name|width
operator|*
name|y
operator|)
operator|+
name|x
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|dest
index|[
name|dix
operator|+
name|nb
index|]
operator|=
name|src
index|[
name|dix
operator|+
name|nb
index|]
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|nb
condition|;
name|b
operator|++
control|)
block|{
name|sum
operator|=
literal|0.0
expr_stmt|;
name|fact
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
operator|-
name|numrad
init|;
name|i
operator|<
name|numrad
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|(
operator|(
name|x
operator|+
name|i
operator|)
operator|<
literal|0
operator|)
operator|||
operator|(
operator|(
name|x
operator|+
name|i
operator|)
operator|>=
name|width
operator|)
condition|)
continue|continue;
for|for
control|(
name|j
operator|=
literal|1
operator|-
name|numrad
init|;
name|j
operator|<
name|numrad
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
operator|(
operator|(
name|y
operator|+
name|j
operator|)
operator|<
literal|0
operator|)
operator|||
operator|(
operator|(
name|y
operator|+
name|j
operator|)
operator|>=
name|height
operator|)
condition|)
continue|continue;
name|six
operator|=
operator|(
name|bytes
operator|*
operator|(
operator|(
name|width
operator|*
operator|(
name|y
operator|+
name|j
operator|)
operator|)
operator|+
name|x
operator|+
name|i
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
if|if
condition|(
operator|!
name|src
index|[
name|six
operator|+
name|nb
index|]
condition|)
continue|continue;
name|alpha
operator|=
operator|(
name|double
operator|)
name|src
index|[
name|six
operator|+
name|nb
index|]
operator|/
literal|255.0
expr_stmt|;
block|}
name|tmp
operator|=
name|src
index|[
name|dix
operator|+
name|b
index|]
operator|-
name|src
index|[
name|six
operator|+
name|b
index|]
expr_stmt|;
if|if
condition|(
operator|(
name|tmp
operator|>
name|maxdelta
operator|)
operator|||
operator|(
name|tmp
operator|<
operator|-
name|maxdelta
operator|)
condition|)
continue|continue;
name|d
operator|=
name|mat
index|[
name|ABS
argument_list|(
name|i
argument_list|)
index|]
index|[
name|ABS
argument_list|(
name|j
argument_list|)
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|d
operator|*=
name|alpha
expr_stmt|;
block|}
name|sum
operator|+=
name|d
operator|*
name|src
index|[
name|six
operator|+
name|b
index|]
expr_stmt|;
name|fact
operator|+=
name|d
expr_stmt|;
block|}
block|}
if|if
condition|(
name|fact
operator|==
literal|0.0
condition|)
name|dest
index|[
name|dix
operator|+
name|b
index|]
operator|=
name|src
index|[
name|dix
operator|+
name|b
index|]
expr_stmt|;
else|else
name|dest
index|[
name|dix
operator|+
name|b
index|]
operator|=
name|sum
operator|/
name|fact
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
operator|(
name|y
operator|%
literal|5
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|sel_gauss (GDrawable * drawable,gdouble radius,gint maxdelta)
specifier|static
name|void
name|sel_gauss
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|radius
parameter_list|,
name|gint
name|maxdelta
parameter_list|)
block|{
name|GPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
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
name|has_alpha
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guchar
modifier|*
name|src
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
name|i
decl_stmt|;
name|gdouble
modifier|*
modifier|*
name|mat
decl_stmt|;
name|gint
name|numrad
decl_stmt|;
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
name|width
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
expr_stmt|;
name|height
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|width
operator|<
literal|1
operator|)
operator|||
operator|(
name|height
operator|<
literal|1
operator|)
operator|||
operator|(
name|bytes
operator|<
literal|1
operator|)
condition|)
return|return;
name|numrad
operator|=
call|(
name|gint
call|)
argument_list|(
name|radius
operator|+
literal|1.0
argument_list|)
expr_stmt|;
name|mat
operator|=
operator|(
name|gdouble
operator|*
operator|*
operator|)
name|g_malloc
argument_list|(
name|numrad
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
operator|*
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|numrad
condition|;
name|i
operator|++
control|)
name|mat
index|[
name|i
index|]
operator|=
operator|(
name|gdouble
operator|*
operator|)
name|g_malloc
argument_list|(
name|numrad
operator|*
sizeof|sizeof
argument_list|(
name|gdouble
argument_list|)
argument_list|)
expr_stmt|;
name|init_matrix
argument_list|(
name|radius
argument_list|,
name|mat
argument_list|,
name|numrad
argument_list|)
expr_stmt|;
name|src
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|width
operator|*
name|height
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
name|g_malloc
argument_list|(
name|width
operator|*
name|height
operator|*
name|bytes
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
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src
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
name|matrixmult
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|mat
argument_list|,
name|numrad
argument_list|,
name|bytes
argument_list|,
name|has_alpha
argument_list|,
name|maxdelta
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
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|dest
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
comment|/*  merge the shadow, update the drawable  */
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
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/* free up buffers */
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|numrad
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|mat
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|mat
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Gauss interface functions  */
end_comment

begin_function
DECL|function|sel_gauss_close_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|sel_gauss_close_callback
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
DECL|function|sel_gauss_ok_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|sel_gauss_ok_callback
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
DECL|function|sel_gauss_entry_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|sel_gauss_entry_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|bvals
operator|.
name|radius
operator|=
name|atof
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|bvals
operator|.
name|radius
operator|<
literal|1.0
condition|)
name|bvals
operator|.
name|radius
operator|=
literal|1.0
expr_stmt|;
block|}
end_function

begin_function
DECL|function|sel_gauss_delta_callback (GtkWidget * widget,gpointer data)
specifier|static
name|void
name|sel_gauss_delta_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|bvals
operator|.
name|maxdelta
operator|=
name|atoi
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|bvals
operator|.
name|maxdelta
operator|<
literal|0
condition|)
name|bvals
operator|.
name|maxdelta
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|bvals
operator|.
name|maxdelta
operator|>
literal|255
condition|)
name|bvals
operator|.
name|maxdelta
operator|=
literal|255
expr_stmt|;
block|}
end_function

end_unit

