begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Pixelize plug-in (ported to GIMP v1.0)  * Copyright (C) 1997 Eiichi Takamori<taka@ma1.seikyou.ne.jp>  * original pixelize.c for GIMP 0.54 by Tracy Scott  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * version 1.04  * This version requires GIMP v0.99.10 or above.  *  * This plug-in "pixelizes" the image.  *  *	Eiichi Takamori<taka@ma1.seikyou.ne.jp>  *	http://ha1.seikyou.ne.jp/home/taka/gimp/  *  * Changes from version 1.03 to version 1.04:  * - Added gtk_rc_parse  * - Added entry with scale  * - Fixed bug that large pixelwidth>=64 sometimes caused core dump  *  * Changes from gimp-0.99.9/plug-ins/pixelize.c to version 1.03:  * - Fixed comments and help strings  * - Fixed `RGB, GRAY' to `RGB*, GRAY*'  * - Fixed procedure db name `pixelize' to `plug_in_pixelize'  *  * Differences from Tracy Scott's original `pixelize' plug-in:  *  * - Algorithm is modified to work around with the tile management.  *   The way of pixelizing is switched by the value of pixelwidth.  If  *   pixelwidth is greater than (or equal to) tile width, then this  *   plug-in makes GimpPixelRgn with that width and proceeds. Otherwise,  *   it makes the region named `PixelArea', whose size is smaller than  *   tile width and is multiply of pixel width, and acts onto it.  */
end_comment

begin_comment
comment|/* pixelize filter written for the GIMP  *  -Tracy Scott  *  * This filter acts as a low pass filter on the color components of  * the provided region  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|RCSID
end_ifdef

begin_decl_stmt
DECL|variable|rcsid
specifier|static
name|char
name|rcsid
index|[]
init|=
literal|"$Id$"
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Some useful macros */
end_comment

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|16
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|125
end_define

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|50
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon290b3b420108
block|{
DECL|member|pixelwidth
name|gint
name|pixelwidth
decl_stmt|;
DECL|typedef|PixelizeValues
block|}
name|PixelizeValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon290b3b420208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|PixelizeInterface
block|}
name|PixelizeInterface
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon290b3b420308
block|{
DECL|member|x
DECL|member|y
DECL|member|w
DECL|member|h
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
DECL|typedef|PixelArea
block|}
name|PixelArea
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
name|gint
name|pixelize_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pixelize_ok_callback
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
name|pixelize
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
name|pixelize_large
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|pixelwidth
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pixelize_small
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|pixelwidth
parameter_list|,
name|gint
name|tile_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|pixelize_sub
parameter_list|(
name|gint
name|pixelwidth
parameter_list|,
name|gint
name|bpp
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
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pvals
specifier|static
name|PixelizeValues
name|pvals
init|=
block|{
literal|10
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pint
specifier|static
name|PixelizeInterface
name|pint
init|=
block|{
name|FALSE
comment|/* run */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|area
specifier|static
name|PixelArea
name|area
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
literal|"run_mode"
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
name|GIMP_PDB_INT32
block|,
literal|"pixelwidth"
block|,
literal|"Pixel width	 (the decrease in resolution)"
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
literal|"plug_in_pixelize"
argument_list|,
literal|"Pixelize the contents of the specified drawable"
argument_list|,
literal|"Pixelize the contents of the specified drawable with speficied pixelizing width."
argument_list|,
literal|"Spencer Kimball& Peter Mattis, Tracy Scott, (ported to 1.0 by) Eiichi Takamori"
argument_list|,
literal|"Spencer Kimball& Peter Mattis, Tracy Scott"
argument_list|,
literal|"1995"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Blur/Pixelize..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
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
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpRunModeType
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
name|GIMP_RUN_INTERACTIVE
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_pixelize"
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|pixelize_dialog
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
name|GIMP_RUN_NONINTERACTIVE
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|4
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|pvals
operator|.
name|pixelwidth
operator|=
operator|(
name|gdouble
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
block|}
if|if
condition|(
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
operator|&&
name|pvals
operator|.
name|pixelwidth
operator|<=
literal|0
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_pixelize"
argument_list|,
operator|&
name|pvals
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
literal|"Pixelizing..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  set the tile cache size  */
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
argument_list|)
expr_stmt|;
comment|/*  run the pixelize effect  */
name|pixelize
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
literal|"plug_in_pixelize"
argument_list|,
operator|&
name|pvals
argument_list|,
sizeof|sizeof
argument_list|(
name|PixelizeValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* g_message ("pixelize: cannot operate on indexed color images"); */
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

begin_function
specifier|static
name|gint
DECL|function|pixelize_dialog (void)
name|pixelize_dialog
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
name|adjustment
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"pixelize"
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
literal|"Pixelize"
argument_list|)
argument_list|,
literal|"pixelize"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/pixelize.html"
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
name|pixelize_ok_callback
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
name|adjustment
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
literal|"Pixel Width:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|ENTRY_WIDTH
argument_list|,
name|pvals
operator|.
name|pixelwidth
argument_list|,
literal|1
argument_list|,
literal|64
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
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
name|adjustment
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
name|pvals
operator|.
name|pixelwidth
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
name|pint
operator|.
name|run
return|;
block|}
end_function

begin_comment
comment|/*  Pixelize interface functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pixelize_ok_callback (GtkWidget * widget,gpointer data)
name|pixelize_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|pint
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
comment|/*   Pixelize Effect  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pixelize (GimpDrawable * drawable)
name|pixelize
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gint
name|tile_width
decl_stmt|;
name|gint
name|pixelwidth
decl_stmt|;
name|tile_width
operator|=
name|gimp_tile_width
argument_list|()
expr_stmt|;
name|pixelwidth
operator|=
name|pvals
operator|.
name|pixelwidth
expr_stmt|;
if|if
condition|(
name|pixelwidth
operator|<
literal|0
condition|)
name|pixelwidth
operator|=
operator|-
name|pixelwidth
expr_stmt|;
if|if
condition|(
name|pixelwidth
operator|<
literal|1
condition|)
name|pixelwidth
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|pixelwidth
operator|>=
name|tile_width
condition|)
name|pixelize_large
argument_list|(
name|drawable
argument_list|,
name|pixelwidth
argument_list|)
expr_stmt|;
else|else
name|pixelize_small
argument_list|(
name|drawable
argument_list|,
name|pixelwidth
argument_list|,
name|tile_width
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*   This function operates on the image when pixelwidth>= tile_width.   It simply sets the size of GimpPixelRgn as pixelwidth and proceeds.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pixelize_large (GimpDrawable * drawable,gint pixelwidth)
name|pixelize_large
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|pixelwidth
parameter_list|)
block|{
name|GimpPixelRgn
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
name|gulong
modifier|*
name|average
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|,
name|b
decl_stmt|,
name|bpp
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|x_step
decl_stmt|,
name|y_step
decl_stmt|;
name|gulong
name|count
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
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
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
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|average
operator|=
name|g_new
argument_list|(
name|gulong
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
comment|/* Initialize progress */
name|progress
operator|=
literal|0
expr_stmt|;
name|max_progress
operator|=
literal|2
operator|*
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
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|y
operator|+=
name|pixelwidth
operator|-
operator|(
name|y
operator|%
name|pixelwidth
operator|)
control|)
block|{
for|for
control|(
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|x
operator|+=
name|pixelwidth
operator|-
operator|(
name|x
operator|%
name|pixelwidth
operator|)
control|)
block|{
name|x_step
operator|=
name|pixelwidth
operator|-
operator|(
name|x
operator|%
name|pixelwidth
operator|)
expr_stmt|;
name|y_step
operator|=
name|pixelwidth
operator|-
operator|(
name|y
operator|%
name|pixelwidth
operator|)
expr_stmt|;
name|x_step
operator|=
name|MIN
argument_list|(
name|x_step
argument_list|,
name|x2
operator|-
name|x
argument_list|)
expr_stmt|;
name|y_step
operator|=
name|MIN
argument_list|(
name|y_step
argument_list|,
name|y2
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x_step
argument_list|,
name|y_step
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
name|bpp
condition|;
name|b
operator|++
control|)
name|average
index|[
name|b
index|]
operator|=
literal|0
expr_stmt|;
name|count
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|src_rgn
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
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bpp
condition|;
name|b
operator|++
control|)
name|average
index|[
name|b
index|]
operator|+=
name|src
index|[
name|b
index|]
expr_stmt|;
name|src
operator|+=
name|src_rgn
operator|.
name|bpp
expr_stmt|;
name|count
operator|+=
literal|1
expr_stmt|;
block|}
name|src_row
operator|+=
name|src_rgn
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
if|if
condition|(
name|count
operator|>
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
name|bpp
condition|;
name|b
operator|++
control|)
name|average
index|[
name|b
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
name|average
index|[
name|b
index|]
operator|/
name|count
argument_list|)
expr_stmt|;
block|}
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|x_step
argument_list|,
name|y_step
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
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
name|dest_rgn
operator|.
name|h
condition|;
name|row
operator|++
control|)
block|{
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
name|dest_rgn
operator|.
name|w
condition|;
name|col
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
name|bpp
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|average
index|[
name|b
index|]
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
operator|.
name|bpp
expr_stmt|;
name|count
operator|+=
literal|1
expr_stmt|;
block|}
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
name|dest_rgn
operator|.
name|w
operator|*
name|dest_rgn
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
block|}
block|}
name|g_free
argument_list|(
name|average
argument_list|)
expr_stmt|;
comment|/*  update the blurred region	 */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
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

begin_comment
comment|/*    This function operates on PixelArea, whose width and height are    multiply of pixel width, and less than the tile size (to enhance    its speed).     If any coordinates of mask boundary is not multiply of pixel width    (e.g.  x1 % pixelwidth != 0), operates on the region whose width    or height is the remainder.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|pixelize_small (GimpDrawable * drawable,gint pixelwidth,gint tile_width)
name|pixelize_small
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|pixelwidth
parameter_list|,
name|gint
name|tile_width
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|gint
name|bpp
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
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
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
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
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
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
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
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|area
operator|.
name|width
operator|=
operator|(
name|tile_width
operator|/
name|pixelwidth
operator|)
operator|*
name|pixelwidth
expr_stmt|;
name|area
operator|.
name|data
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|glong
operator|)
name|bpp
operator|*
name|area
operator|.
name|width
operator|*
name|area
operator|.
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|area
operator|.
name|y
operator|=
name|y1
init|;
name|area
operator|.
name|y
operator|<
name|y2
condition|;
name|area
operator|.
name|y
operator|+=
name|area
operator|.
name|width
operator|-
operator|(
name|area
operator|.
name|y
operator|%
name|area
operator|.
name|width
operator|)
control|)
block|{
name|area
operator|.
name|h
operator|=
name|area
operator|.
name|width
operator|-
operator|(
name|area
operator|.
name|y
operator|%
name|area
operator|.
name|width
operator|)
expr_stmt|;
name|area
operator|.
name|h
operator|=
name|MIN
argument_list|(
name|area
operator|.
name|h
argument_list|,
name|y2
operator|-
name|area
operator|.
name|y
argument_list|)
expr_stmt|;
for|for
control|(
name|area
operator|.
name|x
operator|=
name|x1
init|;
name|area
operator|.
name|x
operator|<
name|x2
condition|;
name|area
operator|.
name|x
operator|+=
name|area
operator|.
name|width
operator|-
operator|(
name|area
operator|.
name|x
operator|%
name|area
operator|.
name|width
operator|)
control|)
block|{
name|area
operator|.
name|w
operator|=
name|area
operator|.
name|width
operator|-
operator|(
name|area
operator|.
name|x
operator|%
name|area
operator|.
name|width
operator|)
expr_stmt|;
name|area
operator|.
name|w
operator|=
name|MIN
argument_list|(
name|area
operator|.
name|w
argument_list|,
name|x2
operator|-
name|area
operator|.
name|x
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|area
operator|.
name|data
argument_list|,
name|area
operator|.
name|x
argument_list|,
name|area
operator|.
name|y
argument_list|,
name|area
operator|.
name|w
argument_list|,
name|area
operator|.
name|h
argument_list|)
expr_stmt|;
name|pixelize_sub
argument_list|(
name|pixelwidth
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|area
operator|.
name|data
argument_list|,
name|area
operator|.
name|x
argument_list|,
name|area
operator|.
name|y
argument_list|,
name|area
operator|.
name|w
argument_list|,
name|area
operator|.
name|h
argument_list|)
expr_stmt|;
comment|/* Update progress */
name|progress
operator|+=
name|area
operator|.
name|w
operator|*
name|area
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
block|}
name|g_free
argument_list|(
name|area
operator|.
name|data
argument_list|)
expr_stmt|;
comment|/*  update the pixelized region  */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
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

begin_comment
comment|/*   This function acts on one PixelArea.	Since there were so many   nested FORs in pixelize_small(), I put a few of them here...   */
end_comment

begin_function
specifier|static
name|void
DECL|function|pixelize_sub (gint pixelwidth,gint bpp)
name|pixelize_sub
parameter_list|(
name|gint
name|pixelwidth
parameter_list|,
name|gint
name|bpp
parameter_list|)
block|{
name|glong
name|average
index|[
literal|4
index|]
decl_stmt|;
comment|/* bpp<= 4 */
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|guchar
modifier|*
name|buf_row
decl_stmt|,
modifier|*
name|buf
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|rowstride
operator|=
name|area
operator|.
name|w
operator|*
name|bpp
expr_stmt|;
for|for
control|(
name|y
operator|=
name|area
operator|.
name|y
init|;
name|y
operator|<
name|area
operator|.
name|y
operator|+
name|area
operator|.
name|h
condition|;
name|y
operator|+=
name|pixelwidth
operator|-
operator|(
name|y
operator|%
name|pixelwidth
operator|)
control|)
block|{
name|h
operator|=
name|pixelwidth
operator|-
operator|(
name|y
operator|%
name|pixelwidth
operator|)
expr_stmt|;
name|h
operator|=
name|MIN
argument_list|(
name|h
argument_list|,
name|area
operator|.
name|y
operator|+
name|area
operator|.
name|h
operator|-
name|y
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
name|area
operator|.
name|x
init|;
name|x
operator|<
name|area
operator|.
name|x
operator|+
name|area
operator|.
name|w
condition|;
name|x
operator|+=
name|pixelwidth
operator|-
operator|(
name|x
operator|%
name|pixelwidth
operator|)
control|)
block|{
name|w
operator|=
name|pixelwidth
operator|-
operator|(
name|x
operator|%
name|pixelwidth
operator|)
expr_stmt|;
name|w
operator|=
name|MIN
argument_list|(
name|w
argument_list|,
name|area
operator|.
name|x
operator|+
name|area
operator|.
name|w
operator|-
name|x
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
name|bpp
condition|;
name|i
operator|++
control|)
name|average
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
name|count
operator|=
literal|0
expr_stmt|;
comment|/* Read */
name|buf_row
operator|=
name|area
operator|.
name|data
operator|+
operator|(
name|y
operator|-
name|area
operator|.
name|y
operator|)
operator|*
name|rowstride
operator|+
operator|(
name|x
operator|-
name|area
operator|.
name|x
operator|)
operator|*
name|bpp
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|h
condition|;
name|row
operator|++
control|)
block|{
name|buf
operator|=
name|buf_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|w
condition|;
name|col
operator|++
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bpp
condition|;
name|i
operator|++
control|)
name|average
index|[
name|i
index|]
operator|+=
name|buf
index|[
name|i
index|]
expr_stmt|;
name|count
operator|++
expr_stmt|;
name|buf
operator|+=
name|bpp
expr_stmt|;
block|}
name|buf_row
operator|+=
name|rowstride
expr_stmt|;
block|}
comment|/* Average */
if|if
condition|(
name|count
operator|>
literal|0
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
name|bpp
condition|;
name|i
operator|++
control|)
name|average
index|[
name|i
index|]
operator|/=
name|count
expr_stmt|;
block|}
comment|/* Write */
name|buf_row
operator|=
name|area
operator|.
name|data
operator|+
operator|(
name|y
operator|-
name|area
operator|.
name|y
operator|)
operator|*
name|rowstride
operator|+
operator|(
name|x
operator|-
name|area
operator|.
name|x
operator|)
operator|*
name|bpp
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|h
condition|;
name|row
operator|++
control|)
block|{
name|buf
operator|=
name|buf_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|w
condition|;
name|col
operator|++
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bpp
condition|;
name|i
operator|++
control|)
name|buf
index|[
name|i
index|]
operator|=
name|average
index|[
name|i
index|]
expr_stmt|;
name|count
operator|++
expr_stmt|;
name|buf
operator|+=
name|bpp
expr_stmt|;
block|}
name|buf_row
operator|+=
name|rowstride
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

end_unit

