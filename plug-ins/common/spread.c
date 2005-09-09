begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Spread --- image filter plug-in for The Gimp image manipulation program  * Copyright (C) 1997 Brian Degenhardt and Federico Mena Quintero  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-spread"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"spread"
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
DECL|struct|__anon2b997fdf0108
block|{
DECL|member|spread_amount_x
name|gdouble
name|spread_amount_x
decl_stmt|;
DECL|member|spread_amount_y
name|gdouble
name|spread_amount_y
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|SpreadValues
block|}
name|SpreadValues
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
name|spread
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|spread_preview_update
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GtkWidget
modifier|*
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|spread_dialog
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
DECL|variable|spvals
specifier|static
name|SpreadValues
name|spvals
init|=
block|{
literal|5
block|,
comment|/*  horizontal spread amount  */
literal|5
block|,
comment|/*  vertical spread amount    */
name|TRUE
comment|/*  preview                   */
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
literal|"run-mode"
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
name|GIMP_PDB_FLOAT
block|,
literal|"spread-amount-x"
block|,
literal|"Horizontal spread amount (0<= spread_amount_x<= 200)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"spread-amount-y"
block|,
literal|"Vertical spread amount (0<= spread_amount_y<= 200)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"Spread the contents of the specified drawable"
argument_list|,
literal|"Spreads the pixels of the specified drawable.  "
literal|"Pixels are randomly moved to another location whose "
literal|"distance varies from the original by the horizontal "
literal|"and vertical spread amounts "
argument_list|,
literal|"Spencer Kimball and Peter Mattis, ported by Brian "
literal|"Degenhardt and Federico Mena Quintero"
argument_list|,
literal|"Federico Mena Quintero and Brian Degenhardt"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Sp_read..."
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
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Filters/Noise"
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
name|gint32
name|image_ID
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
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
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Get the specified image and drawable  */
name|image_ID
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
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
name|PLUG_IN_PROC
argument_list|,
operator|&
name|spvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|spread_dialog
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
name|spvals
operator|.
name|spread_amount_x
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
name|spvals
operator|.
name|spread_amount_y
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
block|}
if|if
condition|(
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
operator|&&
operator|(
name|spvals
operator|.
name|spread_amount_x
operator|<
literal|0
operator|||
name|spvals
operator|.
name|spread_amount_x
operator|>
literal|200
operator|)
operator|&&
operator|(
name|spvals
operator|.
name|spread_amount_y
operator|<
literal|0
operator|||
name|spvals
operator|.
name|spread_amount_y
operator|>
literal|200
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|spvals
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
literal|"Spreading..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  run the spread effect  */
name|spread
argument_list|(
name|drawable
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
name|PLUG_IN_PROC
argument_list|,
operator|&
name|spvals
argument_list|,
sizeof|sizeof
argument_list|(
name|SpreadValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("spread: cannot operate on indexed color images"); */
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b997fdf0208
block|{
DECL|member|pft
name|GimpPixelFetcher
modifier|*
name|pft
decl_stmt|;
DECL|member|gr
name|GRand
modifier|*
name|gr
decl_stmt|;
DECL|member|x_amount
name|gint
name|x_amount
decl_stmt|;
DECL|member|y_amount
name|gint
name|y_amount
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|typedef|SpreadParam_t
block|}
name|SpreadParam_t
typedef|;
end_typedef

begin_comment
comment|/* Spread the image.  This is done by going through every pixel    in the source image and swapping it with some other random    pixel.  The random pixel is located within an ellipse that is    as high as the spread_amount_y parameter and as wide as the    spread_amount_x parameter.  This is done by randomly selecting    an angle and then multiplying the sine of the angle to a random    number whose range is between -spread_amount_x/2 and spread_amount_x/2.    The y coordinate is found by multiplying the cosine of the angle    to the random value generated from spread_amount_y.  The reason    that the spread is done this way is to make the end product more    random looking.  To see a result of this, compare spreading a    square with gimp 0.54 to spreading a square with this filter.    The corners are less sharp with this algorithm. */
end_comment

begin_function
specifier|static
name|void
DECL|function|spread_func (gint x,gint y,guchar * dest,gint bpp,gpointer data)
name|spread_func
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|SpreadParam_t
modifier|*
name|param
init|=
operator|(
name|SpreadParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
name|gint
name|xdist
decl_stmt|,
name|ydist
decl_stmt|;
name|gint
name|xi
decl_stmt|,
name|yi
decl_stmt|;
comment|/* get random angle, x distance, and y distance */
name|xdist
operator|=
operator|(
name|param
operator|->
name|x_amount
operator|>
literal|0
condition|?
name|g_rand_int_range
argument_list|(
name|param
operator|->
name|gr
argument_list|,
operator|-
name|param
operator|->
name|x_amount
argument_list|,
name|param
operator|->
name|x_amount
argument_list|)
else|:
literal|0
operator|)
expr_stmt|;
name|ydist
operator|=
operator|(
name|param
operator|->
name|y_amount
operator|>
literal|0
condition|?
name|g_rand_int_range
argument_list|(
name|param
operator|->
name|gr
argument_list|,
operator|-
name|param
operator|->
name|y_amount
argument_list|,
name|param
operator|->
name|y_amount
argument_list|)
else|:
literal|0
operator|)
expr_stmt|;
name|angle
operator|=
name|g_rand_double_range
argument_list|(
name|param
operator|->
name|gr
argument_list|,
operator|-
name|G_PI
argument_list|,
name|G_PI
argument_list|)
expr_stmt|;
name|xi
operator|=
name|x
operator|+
name|floor
argument_list|(
name|sin
argument_list|(
name|angle
argument_list|)
operator|*
name|xdist
argument_list|)
expr_stmt|;
name|yi
operator|=
name|y
operator|+
name|floor
argument_list|(
name|cos
argument_list|(
name|angle
argument_list|)
operator|*
name|ydist
argument_list|)
expr_stmt|;
comment|/* Only displace the pixel if it's within the bounds of the image. */
if|if
condition|(
name|xi
operator|>=
literal|0
operator|&&
name|xi
operator|<
name|param
operator|->
name|width
operator|&&
name|yi
operator|>=
literal|0
operator|&&
name|yi
operator|<
name|param
operator|->
name|height
condition|)
block|{
name|gimp_pixel_fetcher_get_pixel
argument_list|(
name|param
operator|->
name|pft
argument_list|,
name|xi
argument_list|,
name|yi
argument_list|,
name|dest
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* Else just copy it */
block|{
name|gimp_pixel_fetcher_get_pixel
argument_list|(
name|param
operator|->
name|pft
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|dest
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|spread (GimpDrawable * drawable)
name|spread
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpRgnIterator
modifier|*
name|iter
decl_stmt|;
name|SpreadParam_t
name|param
decl_stmt|;
name|param
operator|.
name|pft
operator|=
name|gimp_pixel_fetcher_new
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|param
operator|.
name|gr
operator|=
name|g_rand_new
argument_list|()
expr_stmt|;
name|param
operator|.
name|x_amount
operator|=
operator|(
name|spvals
operator|.
name|spread_amount_x
operator|+
literal|1
operator|)
operator|/
literal|2
expr_stmt|;
name|param
operator|.
name|y_amount
operator|=
operator|(
name|spvals
operator|.
name|spread_amount_y
operator|+
literal|1
operator|)
operator|/
literal|2
expr_stmt|;
name|param
operator|.
name|width
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|param
operator|.
name|height
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
name|iter
operator|=
name|gimp_rgn_iterator_new
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_dest
argument_list|(
name|iter
argument_list|,
name|spread_func
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_free
argument_list|(
name|iter
argument_list|)
expr_stmt|;
name|g_rand_free
argument_list|(
name|param
operator|.
name|gr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|spread_preview_update (GimpPreview * preview,GtkWidget * size)
name|spread_preview_update
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GtkWidget
modifier|*
name|size
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|SpreadParam_t
name|param
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|bpp
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|x_off
decl_stmt|,
name|y_off
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_preview_get_drawable
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|param
operator|.
name|pft
operator|=
name|gimp_pixel_fetcher_new
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|param
operator|.
name|gr
operator|=
name|g_rand_new
argument_list|()
expr_stmt|;
name|param
operator|.
name|x_amount
operator|=
operator|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|0
argument_list|)
operator|+
literal|1
operator|)
operator|/
literal|2
expr_stmt|;
name|param
operator|.
name|y_amount
operator|=
operator|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|1
argument_list|)
operator|+
literal|1
operator|)
operator|/
literal|2
expr_stmt|;
name|param
operator|.
name|width
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|param
operator|.
name|height
operator|=
name|drawable
operator|->
name|height
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
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|dest
operator|=
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x_off
argument_list|,
operator|&
name|y_off
argument_list|)
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
name|spread_func
argument_list|(
name|x
operator|+
name|x_off
argument_list|,
name|y
operator|+
name|y_off
argument_list|,
name|dest
argument_list|,
name|bpp
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|bpp
expr_stmt|;
block|}
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|buffer
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_rand_free
argument_list|(
name|param
operator|.
name|gr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|spread_dialog (gint32 image_ID,GimpDrawable * drawable)
name|spread_dialog
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
name|size
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
name|PLUG_IN_BINARY
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
literal|"Spread"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
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
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
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
name|spvals
operator|.
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
name|preview
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
name|preview
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Spread Amount"
argument_list|)
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
comment|/* sizeentries */
name|size
operator|=
name|gimp_coordinates_new
argument_list|(
name|unit
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|spvals
operator|.
name|spread_amount_x
operator|==
name|spvals
operator|.
name|spread_amount_y
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"_Horizontal:"
argument_list|)
argument_list|,
name|spvals
operator|.
name|spread_amount_x
argument_list|,
name|xres
argument_list|,
literal|0
argument_list|,
name|MAX
argument_list|(
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Vertical:"
argument_list|)
argument_list|,
name|spvals
operator|.
name|spread_amount_y
argument_list|,
name|yres
argument_list|,
literal|0
argument_list|,
name|MAX
argument_list|(
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|spread_preview_update
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|size
argument_list|,
literal|"refval-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|spread_preview_update
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|size
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
if|if
condition|(
name|run
condition|)
block|{
name|spvals
operator|.
name|spread_amount_x
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spvals
operator|.
name|spread_amount_y
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
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

end_unit

