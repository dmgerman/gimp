begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* threshold_alpha.c -- This is a plug-in for the GIMP (1.0's API)  * Author: Shuji Narazaki<narazaki@InetQ.or.jp>  * Time-stamp:<2000-01-09 13:25:30 yasuhiro>  * Version: 0.13A (the 'A' is for Adam who hacked in greyscale  *                 support - don't know if there's a more recent official  *                 version)  *  * Copyright (C) 1997 Shuji Narazaki<narazaki@InetQ.or.jp>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_threshold_alpha"
end_define

begin_define
DECL|macro|SHORT_NAME
define|#
directive|define
name|SHORT_NAME
value|"threshold_alpha"
end_define

begin_define
DECL|macro|PROGRESS_UPDATE_NUM
define|#
directive|define
name|PROGRESS_UPDATE_NUM
value|100
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|120
end_define

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
name|GStatusType
name|threshold_alpha
parameter_list|(
name|gint32
name|drawable_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|threshold_alpha_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|threshold_alpha_ok_callback
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b425ca30108
block|{
DECL|member|threshold
name|gint
name|threshold
decl_stmt|;
DECL|typedef|ValueType
block|}
name|ValueType
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|VALS
specifier|static
name|ValueType
name|VALS
init|=
block|{
literal|127
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b425ca30208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|Interface
block|}
name|Interface
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|INTERFACE
specifier|static
name|Interface
name|INTERFACE
init|=
block|{
name|FALSE
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
literal|"Input image (not used)"
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
literal|"threshold"
block|,
literal|"Threshold"
block|}
block|}
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
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"Shuji Narazaki (narazaki@InetQ.or.jp)"
argument_list|,
literal|"Shuji Narazaki"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Image/Alpha/Threshold Alpha..."
argument_list|)
argument_list|,
literal|"RGBA,GRAYA"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
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
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|gint
name|drawable_id
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
name|drawable_id
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|RUN_INTERACTIVE
condition|)
block|{
name|INIT_I18N
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
block|}
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
comment|/* Since a channel might be selected, we must check wheter RGB or not. */
if|if
condition|(
name|gimp_layer_get_preserve_transparency
argument_list|(
name|drawable_id
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"The layer preserves transparency."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable_id
argument_list|)
operator|&&
operator|!
name|gimp_drawable_is_gray
argument_list|(
name|drawable_id
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"RGBA/GRAYA drawable is not selected."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|VALS
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|threshold_alpha_dialog
argument_list|()
condition|)
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|4
condition|)
block|{
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|VALS
operator|.
name|threshold
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
block|}
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|VALS
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|status
operator|=
name|threshold_alpha
argument_list|(
name|drawable_id
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
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
operator|&&
name|status
operator|==
name|STATUS_SUCCESS
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|VALS
argument_list|,
sizeof|sizeof
argument_list|(
name|ValueType
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
block|}
end_function

begin_function
specifier|static
name|GStatusType
DECL|function|threshold_alpha (gint32 drawable_id)
name|threshold_alpha
parameter_list|(
name|gint32
name|drawable_id
parameter_list|)
block|{
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|gap
decl_stmt|,
name|total
decl_stmt|,
name|processed
init|=
literal|0
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_id
argument_list|)
condition|)
return|return
name|STATUS_EXECUTION_ERROR
return|;
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable_id
argument_list|)
condition|)
name|gap
operator|=
literal|3
expr_stmt|;
else|else
name|gap
operator|=
literal|1
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
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
name|total
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
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Threshold Alpha: Coloring Transparency..."
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
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
name|gint
name|offset
decl_stmt|,
name|index
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|src_rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|src
operator|=
name|src_rgn
operator|.
name|data
operator|+
name|y
operator|*
name|src_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest
operator|=
name|dest_rgn
operator|.
name|data
operator|+
name|y
operator|*
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
name|offset
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|src_rgn
operator|.
name|w
condition|;
name|x
operator|++
control|)
block|{
for|for
control|(
name|index
operator|=
literal|0
init|;
name|index
operator|<
name|gap
condition|;
name|index
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|(
name|VALS
operator|.
name|threshold
operator|<
operator|*
name|src
operator|++
operator|)
condition|?
literal|255
else|:
literal|0
expr_stmt|;
if|if
condition|(
operator|(
operator|++
name|processed
operator|%
operator|(
name|total
operator|/
name|PROGRESS_UPDATE_NUM
operator|)
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|processed
operator|/
operator|(
name|double
operator|)
name|total
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|STATUS_SUCCESS
return|;
block|}
end_function

begin_comment
comment|/* dialog stuff */
end_comment

begin_function
specifier|static
name|gint
DECL|function|threshold_alpha_dialog (void)
name|threshold_alpha_dialog
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
literal|"threshold_alpha"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Threshold Alpha"
argument_list|)
argument_list|,
literal|"threshold_alpha"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/threshold_alpha.html"
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
name|threshold_alpha_ok_callback
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
name|table
operator|=
name|gtk_table_new
argument_list|(
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
name|gtk_widget_show
argument_list|(
name|table
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
literal|0
argument_list|,
name|_
argument_list|(
literal|"Threshold:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|VALS
operator|.
name|threshold
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|,
literal|1
argument_list|,
literal|8
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
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|VALS
operator|.
name|threshold
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
name|INTERFACE
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|threshold_alpha_ok_callback (GtkWidget * widget,gpointer data)
name|threshold_alpha_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|INTERFACE
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

