begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program   * Copyright (C) 1995 Spencer Kimball and Peter Mattis   *   * This program is free software; you can redistribute it and/or modify   * it under the terms of the GNU General Public License as published by   * the Free Software Foundation; either version 2 of the License, or   * (at your option) any later version.   *  * This program is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   * GNU General Public License for more details.   *   * You should have received a copy of the GNU General Public License   * along with this program; if not, write to the Free Software   * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.   */
end_comment

begin_comment
comment|/* Original plug-in coded by Tim Newsome.   *   * Changed to make use of real-life units by Sven Neumann<sven@gimp.org>.  *   * The interface code is heavily commented in the hope that it will  * help other plug-in developers to adapt their plug-ins to make use  * of the gimp_size_entry functionality.  *  * For more info see libgimp/gimpsizeentry.h  */
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
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpchainbutton.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpsizeentry.h"
end_include

begin_comment
comment|/* Declare local functions. */
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
name|dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|doit
parameter_list|(
name|GDrawable
modifier|*
name|drawable
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
DECL|variable|bytes
name|gint
name|bytes
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sx1
DECL|variable|sy1
DECL|variable|sx2
DECL|variable|sy2
name|gint
name|sx1
decl_stmt|,
name|sy1
decl_stmt|,
name|sx2
decl_stmt|,
name|sy2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_flag
name|int
name|run_flag
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28bff1160108
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|x_offset
name|gint
name|x_offset
decl_stmt|;
DECL|member|y_offset
name|gint
name|y_offset
decl_stmt|;
block|}
DECL|typedef|config
name|config
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|my_config
name|config
name|my_config
init|=
block|{
literal|16
block|,
literal|16
block|,
comment|/* width, height */
literal|0
block|,
literal|0
block|,
comment|/* x_offset, y_offset */
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
name|PARAM_INT32
block|,
literal|"width"
block|,
literal|"Width"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"height"
block|,
literal|"Height"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"x_offset"
block|,
literal|"X Offset"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"y_offset"
block|,
literal|"Y Offset"
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
literal|"plug_in_grid"
argument_list|,
literal|"Draws a grid."
argument_list|,
literal|""
argument_list|,
literal|"Tim Newsome"
argument_list|,
literal|"Tim Newsome, Sven Neumann"
argument_list|,
literal|"1997, 1999"
argument_list|,
literal|"<Image>/Filters/Render/Grid"
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
DECL|function|run (char * name,int n_params,GParam * param,int * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|n_params
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
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
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
if|if
condition|(
name|run_mode
operator|==
name|RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
name|n_params
operator|!=
literal|7
condition|)
block|{
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|my_config
operator|.
name|width
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
name|my_config
operator|.
name|height
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|my_config
operator|.
name|x_offset
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|my_config
operator|.
name|y_offset
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_grid"
argument_list|,
operator|&
name|my_config
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
condition|)
block|{
if|if
condition|(
operator|!
name|dialog
argument_list|(
name|image_ID
argument_list|,
name|drawable
argument_list|)
condition|)
block|{
comment|/* The dialog was closed, or something similarly evil happened. */
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|my_config
operator|.
name|width
operator|<=
literal|0
operator|||
name|my_config
operator|.
name|height
operator|<=
literal|0
condition|)
block|{
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
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
name|_
argument_list|(
literal|"Drawing Grid..."
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
name|doit
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
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_grid"
argument_list|,
operator|&
name|my_config
argument_list|,
sizeof|sizeof
argument_list|(
name|my_config
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|void
DECL|function|doit (GDrawable * drawable)
name|doit
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
name|int
name|w
decl_stmt|,
name|h
decl_stmt|,
name|b
decl_stmt|;
name|guchar
modifier|*
name|copybuf
decl_stmt|;
name|guchar
name|color
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
comment|/* Get the input area. This is the bounding box of the selection in    *  the image (or the entire image if there is no selection). Only    *  operating on the input area is simply an optimization. It doesn't    *  need to be done for correct operation. (It simply makes it go    *  faster, since fewer pixels need to be operated on).    */
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
operator|&
name|sx1
argument_list|,
operator|&
name|sy1
argument_list|,
operator|&
name|sx2
argument_list|,
operator|&
name|sy2
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
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|color
index|[
name|bytes
operator|-
literal|1
index|]
operator|=
literal|0xff
expr_stmt|;
block|}
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
comment|/* First off, copy the old one to the new one. */
name|copybuf
operator|=
name|malloc
argument_list|(
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
for|for
control|(
name|h
operator|=
name|sy1
init|;
name|h
operator|<
name|sy2
condition|;
name|h
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|copybuf
argument_list|,
name|sx1
argument_list|,
name|h
argument_list|,
operator|(
name|sx2
operator|-
name|sx1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|h
operator|-
name|my_config
operator|.
name|y_offset
operator|)
operator|%
name|my_config
operator|.
name|height
operator|==
literal|0
condition|)
block|{
comment|/* Draw row */
for|for
control|(
name|w
operator|=
name|sx1
init|;
name|w
operator|<
name|sx2
condition|;
name|w
operator|++
control|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
name|copybuf
index|[
operator|(
name|w
operator|-
name|sx1
operator|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|=
name|color
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
for|for
control|(
name|w
operator|=
name|sx1
init|;
name|w
operator|<
name|sx2
condition|;
name|w
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|w
operator|-
name|my_config
operator|.
name|x_offset
operator|)
operator|%
name|my_config
operator|.
name|width
operator|==
literal|0
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
name|copybuf
index|[
operator|(
name|w
operator|-
name|sx1
operator|)
operator|*
name|bytes
operator|+
name|b
index|]
operator|=
name|color
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
block|}
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|copybuf
argument_list|,
name|sx1
argument_list|,
name|h
argument_list|,
operator|(
name|sx2
operator|-
name|sx1
operator|)
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|h
operator|/
call|(
name|double
call|)
argument_list|(
name|sy2
operator|-
name|sy1
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|free
argument_list|(
name|copybuf
argument_list|)
expr_stmt|;
comment|/*  update the timred region  */
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
name|sx1
argument_list|,
name|sy1
argument_list|,
name|sx2
operator|-
name|sx1
argument_list|,
name|sy2
operator|-
name|sy1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/***************************************************  * GUI stuff  */
end_comment

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
DECL|function|ok_callback (GtkWidget * widget,gpointer data)
name|ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|run_flag
operator|=
literal|1
expr_stmt|;
name|entry
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"size"
argument_list|)
expr_stmt|;
name|my_config
operator|.
name|width
operator|=
call|(
name|int
call|)
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|my_config
operator|.
name|height
operator|=
call|(
name|int
call|)
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|)
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"offset"
argument_list|)
expr_stmt|;
name|my_config
operator|.
name|x_offset
operator|=
call|(
name|int
call|)
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|)
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|my_config
operator|.
name|y_offset
operator|=
call|(
name|int
call|)
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|1
argument_list|)
operator|+
literal|0.5
argument_list|)
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
DECL|function|entry_callback (GtkWidget * widget,gpointer data)
name|entry_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|gdouble
name|x
init|=
operator|-
literal|1.0
decl_stmt|;
specifier|static
name|gdouble
name|y
init|=
operator|-
literal|1.0
decl_stmt|;
name|gdouble
name|new_x
decl_stmt|;
name|gdouble
name|new_y
decl_stmt|;
name|new_x
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
name|new_y
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_chain_button_get_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|data
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|new_x
operator|!=
name|x
condition|)
block|{
name|y
operator|=
name|new_y
operator|=
name|x
operator|=
name|new_x
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|1
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|new_y
operator|!=
name|y
condition|)
block|{
name|x
operator|=
name|new_x
operator|=
name|y
operator|=
name|new_y
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|,
name|x
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|new_x
operator|!=
name|x
condition|)
name|x
operator|=
name|new_x
expr_stmt|;
if|if
condition|(
name|new_y
operator|!=
name|y
condition|)
name|y
operator|=
name|new_y
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|dialog (gint32 image_ID,GDrawable * drawable)
name|dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GDrawable
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
name|hbbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|size
decl_stmt|;
name|GtkWidget
modifier|*
name|offset
decl_stmt|;
name|GUnit
name|unit
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
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
literal|"grid"
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
literal|"Grid"
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
name|close_callback
argument_list|,
name|NULL
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
name|ok_callback
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
comment|/*  The size entries  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
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
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|size
operator|=
name|gimp_size_entry_new
argument_list|(
literal|2
argument_list|,
comment|/*  number_of_fields  */
name|unit
argument_list|,
comment|/*  unit              */
literal|"%a"
argument_list|,
comment|/*  unit_format       */
name|TRUE
argument_list|,
comment|/*  menu_show_pixels  */
name|TRUE
argument_list|,
comment|/*  menu_show_percent */
name|FALSE
argument_list|,
comment|/*  show_refval       */
literal|75
argument_list|,
comment|/*  spinbutton_usize  */
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
comment|/*  update_policy     */
comment|/*  set the resolution to the image resolution  */
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|1
argument_list|,
name|yres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  set the size (in pixels) that will be treated as 0% and 100%  */
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|width
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  set upper and lower limits (in pixels)  */
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|width
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  initialize the values  */
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|(
name|gdouble
operator|)
name|my_config
operator|.
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|1
argument_list|,
operator|(
name|gdouble
operator|)
name|my_config
operator|.
name|height
argument_list|)
expr_stmt|;
comment|/*  attach labels  */
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"X"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Y"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Size: "
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
comment|/*  put a chain_button under the size_entries  */
name|button
operator|=
name|gimp_chain_button_new
argument_list|(
name|GIMP_CHAIN_BOTTOM
argument_list|)
expr_stmt|;
if|if
condition|(
name|my_config
operator|.
name|width
operator|==
name|my_config
operator|.
name|height
condition|)
name|gimp_chain_button_set_active
argument_list|(
name|GIMP_CHAIN_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|size
argument_list|)
argument_list|,
name|button
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
comment|/*  connect to the 'value_changed' and "unit_changed" signals because we have to        take care of keeping the entries in sync when the chainbutton is active        */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|size
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|entry_callback
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|size
argument_list|)
argument_list|,
literal|"unit_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|entry_callback
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|size
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/*  the offset entries  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
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
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|offset
operator|=
name|gimp_size_entry_new
argument_list|(
literal|2
argument_list|,
name|unit
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|75
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|1
argument_list|,
name|yres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|width
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|width
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|drawable
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|(
name|gdouble
operator|)
name|my_config
operator|.
name|x_offset
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
literal|1
argument_list|,
operator|(
name|gdouble
operator|)
name|my_config
operator|.
name|y_offset
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|offset
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Offset: "
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|offset
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|offset
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"size"
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"offset"
argument_list|,
name|offset
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|run_flag
return|;
block|}
end_function

end_unit

