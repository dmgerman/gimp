begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* max_rgb.c -- This is a plug-in for the GIMP (1.0's API)  * Author: Shuji Narazaki<narazaki@InetQ.or.jp>  * Time-stamp:<1997/10/23 23:40:20 narazaki@InetQ.or.jp>  * Version: 0.35  *  * Copyright (C) 1997 Shuji Narazaki<narazaki@InetQ.or.jp>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|<math.h>
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

begin_comment
comment|/* Replace them with the right ones */
end_comment

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_max_rgb"
end_define

begin_define
DECL|macro|SHORT_NAME
define|#
directive|define
name|SHORT_NAME
value|"max_rgb"
end_define

begin_define
DECL|macro|PROGRESS_NAME
define|#
directive|define
name|PROGRESS_NAME
value|"max_rgb: scanning..."
end_define

begin_define
DECL|macro|MENU_POSITION
define|#
directive|define
name|MENU_POSITION
value|"<Image>/Filters/Colors/Max RGB"
end_define

begin_define
DECL|macro|MAIN_FUNCTION
define|#
directive|define
name|MAIN_FUNCTION
value|max_rgb
end_define

begin_comment
comment|/* you need not change the following names */
end_comment

begin_define
DECL|macro|INTERFACE
define|#
directive|define
name|INTERFACE
value|max_rgb_interface
end_define

begin_define
DECL|macro|DIALOG
define|#
directive|define
name|DIALOG
value|max_rgb_dialog
end_define

begin_define
DECL|macro|ERROR_DIALOG
define|#
directive|define
name|ERROR_DIALOG
value|max_rgb_error_dialog
end_define

begin_define
DECL|macro|VALS
define|#
directive|define
name|VALS
value|max_rgb_vals
end_define

begin_define
DECL|macro|OK_CALLBACK
define|#
directive|define
name|OK_CALLBACK
value|_max_rgbok_callback
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
name|GStatusType
name|MAIN_FUNCTION
parameter_list|(
name|gint32
name|drawable_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|DIALOG
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ERROR_DIALOG
parameter_list|(
name|gint
name|gtk_was_not_initialized
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|OK_CALLBACK
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
comment|/* gtkWrapper functions */
end_comment

begin_define
DECL|macro|PROGRESS_UPDATE_NUM
define|#
directive|define
name|PROGRESS_UPDATE_NUM
value|100
end_define

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|100
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|100
end_define

begin_function_decl
specifier|static
name|void
name|gtkW_close_callback
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
name|gtkW_toggle_update
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
name|GtkWidget
modifier|*
name|gtkW_dialog_new
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|GtkSignalFunc
name|ok_callback
parameter_list|,
name|GtkSignalFunc
name|close_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gtkW_error_dialog_new
parameter_list|(
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GSList
modifier|*
name|gtkW_vbox_add_radio_button
parameter_list|(
name|GtkWidget
modifier|*
name|vbox
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|GSList
modifier|*
name|group
parameter_list|,
name|GtkSignalFunc
name|update
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtkW_check_button_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|GtkSignalFunc
name|update
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtkW_frame_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtkW_table_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gint
name|col
parameter_list|,
name|gint
name|row
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtkW_hbox_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtkW_vbox_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28b7d0db0108
block|{
DECL|member|max_p
name|gint
name|max_p
decl_stmt|;
comment|/* gint, gdouble, and so on */
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
literal|1
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28b7d0db0208
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

begin_decl_stmt
DECL|variable|hold_max
name|gint
name|hold_max
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|hold_min
name|gint
name|hold_min
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
literal|"max_p"
block|,
literal|"1 for maximizing, 0 for minimizing"
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
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
literal|"Return an image in which each pixel holds only the channel that has the maximum value in three (red, green, blue) channels, and other channels are zero-cleared"
argument_list|,
literal|"the help is not yet written for this plug-in"
argument_list|,
literal|"Shuji Narazaki (narazaki@InetQ.or.jp)"
argument_list|,
literal|"Shuji Narazaki"
argument_list|,
literal|"1997"
argument_list|,
name|MENU_POSITION
argument_list|,
literal|"RGB*"
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
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
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
name|STATUS_EXECUTION_ERROR
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
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|VALS
argument_list|)
expr_stmt|;
name|hold_max
operator|=
name|VALS
operator|.
name|max_p
expr_stmt|;
name|hold_min
operator|=
name|VALS
operator|.
name|max_p
condition|?
literal|0
else|:
literal|1
expr_stmt|;
comment|/* Since a channel might be selected, we must check wheter RGB or not. */
if|if
condition|(
operator|!
name|gimp_drawable_color
argument_list|(
name|drawable_id
argument_list|)
condition|)
block|{
name|ERROR_DIALOG
argument_list|(
literal|1
argument_list|,
literal|"RGB drawable is not selected."
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|DIALOG
argument_list|()
condition|)
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
comment|/* You must copy the values of parameters to VALS or dialog variables. */
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
name|status
operator|=
name|MAIN_FUNCTION
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
DECL|function|MAIN_FUNCTION (gint32 drawable_id)
name|MAIN_FUNCTION
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
name|gint
name|init_value
decl_stmt|,
name|flag
decl_stmt|;
name|init_value
operator|=
operator|(
name|VALS
operator|.
name|max_p
operator|>
literal|0
operator|)
condition|?
literal|0
else|:
literal|255
expr_stmt|;
name|flag
operator|=
operator|(
literal|0
operator|<
name|VALS
operator|.
name|max_p
operator|)
condition|?
literal|1
else|:
operator|-
literal|1
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|gap
operator|=
operator|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_id
argument_list|)
operator|)
condition|?
literal|1
else|:
literal|0
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
name|PROGRESS_NAME
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
name|gint
name|ch
decl_stmt|,
name|max_ch
init|=
literal|0
decl_stmt|;
name|guchar
name|max
decl_stmt|,
name|tmp_value
decl_stmt|;
name|max
operator|=
name|init_value
expr_stmt|;
for|for
control|(
name|ch
operator|=
literal|0
init|;
name|ch
operator|<
literal|3
condition|;
name|ch
operator|++
control|)
if|if
condition|(
name|flag
operator|*
name|max
operator|<=
name|flag
operator|*
operator|(
name|tmp_value
operator|=
operator|(
operator|*
name|src
operator|++
operator|)
operator|)
condition|)
block|{
if|if
condition|(
name|max
operator|==
name|tmp_value
condition|)
name|max_ch
operator|+=
literal|1
operator|<<
name|ch
expr_stmt|;
else|else
block|{
name|max_ch
operator|=
literal|1
operator|<<
name|ch
expr_stmt|;
comment|/* clear memories of old channels */
name|max
operator|=
name|tmp_value
expr_stmt|;
block|}
block|}
for|for
control|(
name|ch
operator|=
literal|0
init|;
name|ch
operator|<
literal|3
condition|;
name|ch
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
operator|(
name|max_ch
operator|&
operator|(
literal|1
operator|<<
name|ch
operator|)
operator|)
operator|>
literal|0
operator|)
condition|?
name|max
else|:
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gap
condition|)
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
operator|++
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
name|int
DECL|function|DIALOG ()
name|DIALOG
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
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
name|PLUG_IN_NAME
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
name|gtkW_dialog_new
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|OK_CALLBACK
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtkW_close_callback
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtkW_hbox_new
argument_list|(
operator|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
operator|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtkW_frame_new
argument_list|(
name|hbox
argument_list|,
literal|"Parameter Settings"
argument_list|)
expr_stmt|;
comment|/*   table = gtkW_table_new (frame, 2, 2);   gtkW_table_add_toggle (table, "Hold the maximal channel", 0, 2, 1, 			 (GtkSignalFunc) gtkW_toggle_update,&VALS.max_p);   gtk_widget_show (table);   */
name|vbox
operator|=
name|gtkW_vbox_new
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtkW_vbox_add_radio_button
argument_list|(
name|vbox
argument_list|,
literal|"Hold the maximal channels"
argument_list|,
name|group
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtkW_toggle_update
argument_list|,
operator|&
name|hold_max
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtkW_vbox_add_radio_button
argument_list|(
name|vbox
argument_list|,
literal|"Hold the minimal channels"
argument_list|,
name|group
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtkW_toggle_update
argument_list|,
operator|&
name|hold_min
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
DECL|function|ERROR_DIALOG (gint gtk_was_not_initialized,gchar * message)
name|ERROR_DIALOG
parameter_list|(
name|gint
name|gtk_was_not_initialized
parameter_list|,
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
decl_stmt|;
if|if
condition|(
name|gtk_was_not_initialized
condition|)
block|{
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
name|PLUG_IN_NAME
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
block|}
name|dlg
operator|=
name|gtkW_error_dialog_new
argument_list|(
name|PLUG_IN_NAME
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|table
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
name|message
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
operator||
name|GTK_EXPAND
argument_list|,
literal|0
argument_list|,
literal|0
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|OK_CALLBACK (GtkWidget * widget,gpointer data)
name|OK_CALLBACK
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|VALS
operator|.
name|max_p
operator|=
name|hold_max
expr_stmt|;
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

begin_comment
comment|/* VFtext interface functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gtkW_close_callback (GtkWidget * widget,gpointer data)
name|gtkW_close_callback
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
specifier|static
name|void
DECL|function|gtkW_toggle_update (GtkWidget * widget,gpointer data)
name|gtkW_toggle_update
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

begin_comment
comment|/* gtkW is the abbreviation of gtk Wrapper */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gtkW_dialog_new (char * name,GtkSignalFunc ok_callback,GtkSignalFunc close_callback)
name|gtkW_dialog_new
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|GtkSignalFunc
name|ok_callback
parameter_list|,
name|GtkSignalFunc
name|close_callback
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|,
modifier|*
name|button
decl_stmt|;
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
name|name
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
name|gtkW_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Action Area */
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
name|ok_callback
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
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
name|dlg
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gtkW_error_dialog_new (char * name)
name|gtkW_error_dialog_new
parameter_list|(
name|char
modifier|*
name|name
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|,
modifier|*
name|button
decl_stmt|;
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
name|name
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
name|gtkW_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Action Area */
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
name|gtkW_close_callback
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
return|return
name|dlg
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gtkW_table_new (GtkWidget * parent,gint col,gint row)
name|gtkW_table_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gint
name|col
parameter_list|,
name|gint
name|row
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
name|col
argument_list|,
name|row
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|parent
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
return|return
name|table
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gtkW_hbox_new (GtkWidget * parent)
name|gtkW_hbox_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
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
name|hbox
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gtkW_vbox_new (GtkWidget * parent)
name|gtkW_vbox_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
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
comment|/* gtk_box_pack_start (GTK_BOX (parent), vbox, TRUE, TRUE, 0); */
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gtkW_check_button_new (GtkWidget * parent,gchar * name,GtkSignalFunc update,gint * value)
name|gtkW_check_button_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|GtkSignalFunc
name|update
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|name
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
name|update
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
operator|*
name|value
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|parent
argument_list|)
argument_list|,
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
return|return
name|toggle
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gtkW_frame_new (GtkWidget * parent,gchar * name)
name|gtkW_frame_new
parameter_list|(
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|name
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
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|parent
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
return|return
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|GSList
modifier|*
DECL|function|gtkW_vbox_add_radio_button (GtkWidget * vbox,gchar * name,GSList * group,GtkSignalFunc update,gint * value)
name|gtkW_vbox_add_radio_button
parameter_list|(
name|GtkWidget
modifier|*
name|vbox
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|GSList
modifier|*
name|group
parameter_list|,
name|GtkSignalFunc
name|update
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|toggle
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
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
name|update
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
operator|*
name|value
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
return|return
name|group
return|;
block|}
end_function

begin_comment
comment|/* end of max_rgb.c */
end_comment

end_unit

