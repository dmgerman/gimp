begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Colorify. Changes the pixel's luminosity to a specified color  * Copyright (C) 1997 Francisco Bustamante  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_comment
comment|/* Changes:      1.1     -Corrected small bug when calling color selection dialog     -Added LUTs to speed things a little bit up      1.0     -First release */
end_comment

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

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"Colorify"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"1.1"
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

begin_typedef
DECL|struct|__anon295aca7a0108
typedef|typedef
struct|struct
block|{
DECL|member|color
name|guchar
name|color
index|[
literal|3
index|]
decl_stmt|;
DECL|typedef|ColorifyVals
block|}
name|ColorifyVals
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon295aca7a0208
typedef|typedef
struct|struct
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|ColorifyInterface
block|}
name|ColorifyInterface
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon295aca7a0308
typedef|typedef
struct|struct
block|{
DECL|member|red
name|guchar
name|red
decl_stmt|;
DECL|member|green
name|guchar
name|green
decl_stmt|;
DECL|member|blue
name|guchar
name|blue
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|button_num
name|gint
name|button_num
decl_stmt|;
DECL|typedef|ButtonInformation
block|}
name|ButtonInformation
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|cint
specifier|static
name|ColorifyInterface
name|cint
init|=
block|{
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cvals
specifier|static
name|ColorifyVals
name|cvals
init|=
block|{
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|button_info
specifier|static
name|ButtonInformation
name|button_info
index|[]
init|=
block|{
block|{
literal|255
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|255
block|,
literal|255
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|0
block|,
literal|255
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|0
block|,
literal|255
block|,
literal|255
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|0
block|,
literal|0
block|,
literal|255
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|255
block|,
literal|0
block|,
literal|255
block|,
name|NULL
block|,
literal|0
block|}
block|,
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|,
name|NULL
block|,
literal|0
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
name|NULL
block|,
name|query
block|,
name|run
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|lum_red_lookup
DECL|variable|lum_green_lookup
DECL|variable|lum_blue_lookup
name|gint
name|lum_red_lookup
index|[
literal|256
index|]
decl_stmt|,
name|lum_green_lookup
index|[
literal|256
index|]
decl_stmt|,
name|lum_blue_lookup
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|final_red_lookup
DECL|variable|final_green_lookup
DECL|variable|final_blue_lookup
name|gint
name|final_red_lookup
index|[
literal|256
index|]
decl_stmt|,
name|final_green_lookup
index|[
literal|256
index|]
decl_stmt|,
name|final_blue_lookup
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_macro
name|MAIN
argument_list|()
end_macro

begin_function_decl
specifier|static
name|int
name|colorify_dialog
parameter_list|(
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorify
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|set_preview_color
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|query ()
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
literal|"Input image"
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
name|PARAM_COLOR
block|,
literal|"color"
block|,
literal|"Color to apply"
block|}
block|, 	}
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
decl_stmt|,
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_colorify"
argument_list|,
literal|"Similar to the \"Color\" mode for layers."
argument_list|,
literal|"Makes an average of the RGB channels and uses it to set the color"
argument_list|,
literal|"Francisco Bustamante"
argument_list|,
literal|"Francisco Bustamante"
argument_list|,
literal|"0.0.1"
argument_list|,
literal|"<Image>/Filters/Colors/Colorify"
argument_list|,
literal|"RGB"
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

begin_decl_stmt
DECL|variable|sel_x1
DECL|variable|sel_x2
DECL|variable|sel_y1
DECL|variable|sel_y2
DECL|variable|sel_width
DECL|variable|sel_height
name|gint
name|sel_x1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_y2
decl_stmt|,
name|sel_width
decl_stmt|,
name|sel_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|c_dialog
name|GtkWidget
modifier|*
name|c_dialog
decl_stmt|;
end_decl_stmt

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
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
decl_stmt|;
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
name|status
operator|=
name|STATUS_SUCCESS
expr_stmt|;
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
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
operator|&
name|sel_x1
argument_list|,
operator|&
name|sel_y1
argument_list|,
operator|&
name|sel_x2
argument_list|,
operator|&
name|sel_y2
argument_list|)
expr_stmt|;
name|sel_width
operator|=
name|sel_x2
operator|-
name|sel_x1
expr_stmt|;
name|sel_height
operator|=
name|sel_y2
operator|-
name|sel_y1
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
name|cvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|colorify_dialog
argument_list|(
name|cvals
operator|.
name|color
index|[
literal|0
index|]
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|1
index|]
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|2
index|]
argument_list|)
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
name|cvals
operator|.
name|color
index|[
literal|0
index|]
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|red
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|1
index|]
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|green
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|2
index|]
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|blue
expr_stmt|;
block|}
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|cvals
argument_list|)
expr_stmt|;
break|break;
default|default :
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|gimp_progress_init
argument_list|(
literal|"Colorifying..."
argument_list|)
expr_stmt|;
name|colorify
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|cvals
argument_list|,
sizeof|sizeof
argument_list|(
name|ColorifyVals
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
block|{
name|gimp_displays_flush
argument_list|()
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
block|}
end_function

begin_function_decl
specifier|static
name|void
name|colorify_row
parameter_list|(
name|guchar
modifier|*
name|row
parameter_list|,
name|gint
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|close_callback
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
name|colorify_ok_callback
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
name|custom_color_callback
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
name|predefined_color_callback
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
name|color_changed
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

begin_function
specifier|static
name|void
DECL|function|colorify (GDrawable * drawable)
name|colorify
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GPixelRgn
name|source_region
decl_stmt|,
name|dest_region
decl_stmt|;
name|guchar
modifier|*
name|row
decl_stmt|;
name|gint
name|y
init|=
literal|0
decl_stmt|;
name|gint
name|progress
init|=
literal|0
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|lum_red_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
literal|0.30
expr_stmt|;
name|lum_green_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
literal|0.59
expr_stmt|;
name|lum_blue_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
literal|0.11
expr_stmt|;
name|final_red_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|cvals
operator|.
name|color
index|[
literal|0
index|]
operator|/
literal|255
expr_stmt|;
name|final_green_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|cvals
operator|.
name|color
index|[
literal|1
index|]
operator|/
literal|255
expr_stmt|;
name|final_blue_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|cvals
operator|.
name|color
index|[
literal|2
index|]
operator|/
literal|255
expr_stmt|;
block|}
name|row
operator|=
name|g_malloc
argument_list|(
name|sel_width
operator|*
literal|3
operator|*
sizeof|sizeof
argument_list|(
name|guchar
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|source_region
argument_list|,
name|drawable
argument_list|,
name|sel_x1
argument_list|,
name|sel_y1
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_region
argument_list|,
name|drawable
argument_list|,
name|sel_x1
argument_list|,
name|sel_y1
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
name|sel_y1
init|;
name|y
operator|<
name|sel_y2
condition|;
name|y
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|source_region
argument_list|,
name|row
argument_list|,
name|sel_x1
argument_list|,
name|y
argument_list|,
name|sel_width
argument_list|)
expr_stmt|;
name|colorify_row
argument_list|(
name|row
argument_list|,
name|sel_width
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dest_region
argument_list|,
name|row
argument_list|,
name|sel_x1
argument_list|,
name|y
argument_list|,
name|sel_width
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
operator|++
name|progress
operator|/
name|sel_height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|row
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
name|sel_x1
argument_list|,
name|sel_y1
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorify_row (guchar * row,gint width)
name|colorify_row
parameter_list|(
name|guchar
modifier|*
name|row
parameter_list|,
name|gint
name|width
parameter_list|)
block|{
name|gint
name|cur_x
decl_stmt|;
name|gint
name|lum
decl_stmt|;
comment|/* luminosity */
name|guchar
modifier|*
name|current
init|=
name|row
decl_stmt|;
for|for
control|(
name|cur_x
operator|=
literal|0
init|;
name|cur_x
operator|<
name|width
condition|;
name|cur_x
operator|++
control|)
block|{
name|lum
operator|=
name|lum_red_lookup
index|[
name|current
index|[
literal|0
index|]
index|]
operator|+
name|lum_green_lookup
index|[
name|current
index|[
literal|1
index|]
index|]
operator|+
name|lum_blue_lookup
index|[
name|current
index|[
literal|2
index|]
index|]
expr_stmt|;
name|current
index|[
literal|0
index|]
operator|=
name|final_red_lookup
index|[
name|lum
index|]
expr_stmt|;
name|current
index|[
literal|1
index|]
operator|=
name|final_green_lookup
index|[
name|lum
index|]
expr_stmt|;
name|current
index|[
literal|2
index|]
operator|=
name|final_blue_lookup
index|[
name|lum
index|]
expr_stmt|;
name|current
operator|+=
literal|3
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|colorify_dialog (guchar red,guchar green,guchar blue)
name|colorify_dialog
parameter_list|(
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|label
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
name|table
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
name|GSList
modifier|*
name|group
init|=
name|NULL
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
literal|"colorify"
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
literal|"Colorify"
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|"Ok"
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
name|colorify_ok_callback
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
name|dialog
argument_list|)
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
name|frame
operator|=
name|gtk_frame_new
argument_list|(
literal|"Color"
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
name|dialog
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
literal|7
argument_list|,
name|TRUE
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
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Custom Color: "
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
literal|4
argument_list|,
literal|6
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
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
name|button
operator|=
name|gtk_radio_button_new
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_mode
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|button
argument_list|,
literal|35
argument_list|,
literal|35
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|custom_color_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
literal|6
argument_list|,
literal|7
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|30
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|set_preview_color
argument_list|(
name|preview
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|0
index|]
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|1
index|]
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|7
condition|;
name|i
operator|++
control|)
block|{
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_radio_button_new
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_mode
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|button_info
index|[
name|i
index|]
operator|.
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|button_info
index|[
name|i
index|]
operator|.
name|preview
argument_list|)
argument_list|,
literal|30
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|button_info
index|[
name|i
index|]
operator|.
name|preview
argument_list|)
expr_stmt|;
name|set_preview_color
argument_list|(
name|button_info
index|[
name|i
index|]
operator|.
name|preview
argument_list|,
name|button_info
index|[
name|i
index|]
operator|.
name|red
argument_list|,
name|button_info
index|[
name|i
index|]
operator|.
name|green
argument_list|,
name|button_info
index|[
name|i
index|]
operator|.
name|blue
argument_list|)
expr_stmt|;
name|button_info
index|[
name|i
index|]
operator|.
name|button_num
operator|=
name|i
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
name|predefined_color_callback
argument_list|,
operator|&
name|button_info
index|[
name|i
index|]
operator|.
name|button_num
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button_info
index|[
name|i
index|]
operator|.
name|preview
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
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
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
name|cint
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|close_callback (GtkWidget * widget,gpointer data)
name|close_callback
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
DECL|function|colorify_ok_callback (GtkWidget * widget,gpointer data)
name|colorify_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|cint
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|set_preview_color (GtkWidget * preview,guchar red,guchar green,guchar blue)
name|set_preview_color
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|guchar
name|buf
index|[
literal|3
operator|*
literal|30
index|]
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|30
condition|;
name|i
operator|++
control|)
block|{
name|buf
index|[
literal|3
operator|*
name|i
index|]
operator|=
name|red
expr_stmt|;
name|buf
index|[
literal|3
operator|*
name|i
operator|+
literal|1
index|]
operator|=
name|green
expr_stmt|;
name|buf
index|[
literal|3
operator|*
name|i
operator|+
literal|2
index|]
operator|=
name|blue
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|30
condition|;
name|i
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|gtk_widget_draw
argument_list|(
name|preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|custom_color_callback (GtkWidget * widget,gpointer data)
name|custom_color_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkColorSelectionDialog
modifier|*
name|csd
decl_stmt|;
name|gdouble
name|colour
index|[
literal|3
index|]
decl_stmt|;
name|c_dialog
operator|=
name|gtk_color_selection_dialog_new
argument_list|(
literal|"Colorify Custom Color"
argument_list|)
expr_stmt|;
name|csd
operator|=
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|c_dialog
argument_list|)
expr_stmt|;
name|gtk_color_selection_set_update_policy
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|csd
operator|->
name|colorsel
argument_list|)
argument_list|,
name|GTK_UPDATE_DISCONTINUOUS
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|csd
operator|->
name|help_button
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|csd
operator|->
name|cancel_button
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|csd
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|color_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|colour
index|[
literal|0
index|]
operator|=
name|cvals
operator|.
name|color
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|colour
index|[
literal|1
index|]
operator|=
name|cvals
operator|.
name|color
index|[
literal|1
index|]
operator|/
literal|255.0
expr_stmt|;
name|colour
index|[
literal|2
index|]
operator|=
name|cvals
operator|.
name|color
index|[
literal|2
index|]
operator|/
literal|255.0
expr_stmt|;
name|gtk_color_selection_set_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|csd
operator|->
name|colorsel
argument_list|)
argument_list|,
name|colour
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|c_dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|c_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|predefined_color_callback (GtkWidget * widget,gpointer data)
name|predefined_color_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
modifier|*
name|num
decl_stmt|;
name|num
operator|=
operator|(
name|gint
operator|*
operator|)
name|data
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|0
index|]
operator|=
name|button_info
index|[
operator|*
name|num
index|]
operator|.
name|red
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|1
index|]
operator|=
name|button_info
index|[
operator|*
name|num
index|]
operator|.
name|green
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|2
index|]
operator|=
name|button_info
index|[
operator|*
name|num
index|]
operator|.
name|blue
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_changed (GtkWidget * widget,gpointer data)
name|color_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gdouble
name|colour
index|[
literal|3
index|]
decl_stmt|;
name|gtk_color_selection_get_color
argument_list|(
name|GTK_COLOR_SELECTION
argument_list|(
name|GTK_COLOR_SELECTION_DIALOG
argument_list|(
name|c_dialog
argument_list|)
operator|->
name|colorsel
argument_list|)
argument_list|,
name|colour
argument_list|)
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|0
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|colour
index|[
literal|0
index|]
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|1
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|colour
index|[
literal|1
index|]
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|cvals
operator|.
name|color
index|[
literal|2
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|colour
index|[
literal|2
index|]
operator|*
literal|255.0
argument_list|)
expr_stmt|;
name|set_preview_color
argument_list|(
name|preview
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|0
index|]
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|1
index|]
argument_list|,
name|cvals
operator|.
name|color
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|c_dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

