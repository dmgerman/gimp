begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Shift --- image filter plug-in for The Gimp image manipulation program  * Copyright (C) 1997 Brian Degenhardt and Federico Mena Quintero  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * Please direct all comments, questions, bug reports  etc to Brian Degenhardt  * bdegenha@ucsd.edu  *  * You can contact Federico Mena Quintero at quartic@polloux.fciencias.unam.mx  * You can contact the original The Gimp authors at gimp@xcf.berkeley.edu  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<time.h>
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
file|<libgimp/gimpmath.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Some useful macros */
end_comment

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|200
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|16
end_define

begin_define
DECL|macro|HORIZONTAL
define|#
directive|define
name|HORIZONTAL
value|0
end_define

begin_define
DECL|macro|VERTICAL
define|#
directive|define
name|VERTICAL
value|1
end_define

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|35
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29db338d0108
block|{
DECL|member|shift_amount
name|gint
name|shift_amount
decl_stmt|;
DECL|member|orientation
name|gint
name|orientation
decl_stmt|;
DECL|typedef|ShiftValues
block|}
name|ShiftValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29db338d0208
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|ShiftInterface
block|}
name|ShiftInterface
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
name|shift
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|shift_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|shift_ok_callback
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
name|GTile
modifier|*
name|shift_pixel
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|GTile
modifier|*
name|tile
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
modifier|*
name|row
parameter_list|,
name|gint
modifier|*
name|col
parameter_list|,
name|guchar
modifier|*
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/***** Local vars *****/
end_comment

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

begin_decl_stmt
DECL|variable|shvals
specifier|static
name|ShiftValues
name|shvals
init|=
block|{
literal|5
block|,
comment|/* shift amount */
name|HORIZONTAL
comment|/* orientation  */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shint
specifier|static
name|ShiftInterface
name|shint
init|=
block|{
name|FALSE
comment|/*  run  */
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
literal|"shift_amount"
block|,
literal|"shift amount (0<= shift_amount_x<= 200)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"orientation"
block|,
literal|"vertical, horizontal orientation"
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
literal|"plug_in_shift"
argument_list|,
name|_
argument_list|(
literal|"Shift the contents of the specified drawable"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Shifts the pixels of the specified drawable. Each row will be displaced a random value of pixels."
argument_list|)
argument_list|,
literal|"Spencer Kimball and Peter Mattis, ported by Brian Degenhardt and Federico Mena Quintero"
argument_list|,
literal|"Brian Degenhardt"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Distorts/Shift..."
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
literal|"plug_in_shift"
argument_list|,
operator|&
name|shvals
argument_list|)
expr_stmt|;
comment|/*  First acquire information with a dialog  */
if|if
condition|(
operator|!
name|shift_dialog
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
name|shvals
operator|.
name|shift_amount
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
name|shvals
operator|.
name|orientation
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
name|HORIZONTAL
else|:
name|VERTICAL
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|status
operator|==
name|STATUS_SUCCESS
operator|)
operator|&&
operator|(
name|shvals
operator|.
name|shift_amount
operator|<
literal|0
operator|||
name|shvals
operator|.
name|shift_amount
operator|>
literal|200
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
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
literal|"plug_in_shift"
argument_list|,
operator|&
name|shvals
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
literal|"Shifting..."
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  set the tile cache size  */
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
argument_list|)
expr_stmt|;
comment|/*  run the shift effect  */
name|shift
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
literal|"plug_in_shift"
argument_list|,
operator|&
name|shvals
argument_list|,
sizeof|sizeof
argument_list|(
name|ShiftValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("shift: cannot operate on indexed color images"); */
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
specifier|static
name|void
DECL|function|shift (GDrawable * drawable)
name|shift
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GPixelRgn
name|dest_rgn
decl_stmt|;
name|GTile
modifier|*
name|tile
init|=
name|NULL
decl_stmt|;
name|gint
name|row
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|col
init|=
operator|-
literal|1
decl_stmt|;
name|gpointer
name|pr
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
name|destline
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guchar
modifier|*
name|otherdest
decl_stmt|;
name|guchar
name|pixel
index|[
literal|4
index|]
index|[
literal|4
index|]
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
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gint
name|seed
decl_stmt|;
name|gint
name|amount
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
name|gint
name|k
decl_stmt|;
name|gint
name|mod_value
decl_stmt|,
name|sub_value
decl_stmt|;
comment|/* Get selection area */
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
name|amount
operator|=
name|shvals
operator|.
name|shift_amount
expr_stmt|;
comment|/* Initialize random stuff */
name|mod_value
operator|=
name|amount
operator|+
literal|1
expr_stmt|;
name|sub_value
operator|=
name|mod_value
operator|/
literal|2
expr_stmt|;
name|seed
operator|=
name|time
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
comment|/* Shift the image.  It's a pretty simple algorithm.  If horizontal      is selected, then every row is shifted a random number of pixels      in the range of -shift_amount/2 to shift_amount/2.  The effect is      just reproduced with columns if vertical is selected.  Vertical      has been added since 0.54 so that the user doesn't have to rotate      the image to do a vertical shift.   */
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
if|if
condition|(
name|shvals
operator|.
name|orientation
operator|==
name|VERTICAL
condition|)
block|{
name|destline
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
name|srand
argument_list|(
name|seed
operator|+
name|dest_rgn
operator|.
name|x
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
name|dest_rgn
operator|.
name|x
init|;
name|x
operator|<
operator|(
name|dest_rgn
operator|.
name|x
operator|+
name|dest_rgn
operator|.
name|w
operator|)
condition|;
name|x
operator|++
control|)
block|{
name|dest
operator|=
name|destline
expr_stmt|;
name|ydist
operator|=
operator|(
name|rand
argument_list|()
operator|%
name|mod_value
operator|)
operator|-
name|sub_value
expr_stmt|;
for|for
control|(
name|y
operator|=
name|dest_rgn
operator|.
name|y
init|;
name|y
operator|<
operator|(
name|dest_rgn
operator|.
name|y
operator|+
name|dest_rgn
operator|.
name|h
operator|)
condition|;
name|y
operator|++
control|)
block|{
name|otherdest
operator|=
name|dest
expr_stmt|;
name|yi
operator|=
operator|(
name|y
operator|+
name|ydist
operator|+
name|height
operator|)
operator|%
name|height
expr_stmt|;
comment|/*  add width before % because % isn't a true modulo */
name|tile
operator|=
name|shift_pixel
argument_list|(
name|drawable
argument_list|,
name|tile
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|x
argument_list|,
name|yi
argument_list|,
operator|&
name|row
argument_list|,
operator|&
name|col
argument_list|,
name|pixel
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bytes
condition|;
name|k
operator|++
control|)
operator|*
name|otherdest
operator|++
operator|=
name|pixel
index|[
literal|0
index|]
index|[
name|k
index|]
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
comment|/* for */
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bytes
condition|;
name|k
operator|++
control|)
name|destline
operator|++
expr_stmt|;
block|}
comment|/* for */
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
else|else
block|{
name|destline
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
name|srand
argument_list|(
name|seed
operator|+
name|dest_rgn
operator|.
name|y
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
name|dest_rgn
operator|.
name|y
init|;
name|y
operator|<
operator|(
name|dest_rgn
operator|.
name|y
operator|+
name|dest_rgn
operator|.
name|h
operator|)
condition|;
name|y
operator|++
control|)
block|{
name|dest
operator|=
name|destline
expr_stmt|;
name|xdist
operator|=
operator|(
name|rand
argument_list|()
operator|%
name|mod_value
operator|)
operator|-
name|sub_value
expr_stmt|;
for|for
control|(
name|x
operator|=
name|dest_rgn
operator|.
name|x
init|;
name|x
operator|<
operator|(
name|dest_rgn
operator|.
name|x
operator|+
name|dest_rgn
operator|.
name|w
operator|)
condition|;
name|x
operator|++
control|)
block|{
name|xi
operator|=
operator|(
name|x
operator|+
name|xdist
operator|+
name|width
operator|)
operator|%
name|width
expr_stmt|;
comment|/*  add width before % because % isn't a true modulo */
name|tile
operator|=
name|shift_pixel
argument_list|(
name|drawable
argument_list|,
name|tile
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|xi
argument_list|,
name|y
argument_list|,
operator|&
name|row
argument_list|,
operator|&
name|col
argument_list|,
name|pixel
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bytes
condition|;
name|k
operator|++
control|)
operator|*
name|dest
operator|++
operator|=
name|pixel
index|[
literal|0
index|]
index|[
name|k
index|]
expr_stmt|;
block|}
comment|/* for */
name|destline
operator|+=
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
block|}
comment|/* for */
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
comment|/* for  */
if|if
condition|(
name|tile
condition|)
name|gimp_tile_unref
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  update the region  */
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
block|}
end_function

begin_comment
comment|/* shift */
end_comment

begin_function
specifier|static
name|gint
DECL|function|shift_dialog (void)
name|shift_dialog
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
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkObject
modifier|*
name|amount_data
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
literal|"shift"
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
literal|"Shift"
argument_list|)
argument_list|,
literal|"shift"
argument_list|,
name|gimp_plugin_help_func
argument_list|,
literal|"filters/shift.html"
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
name|shift_ok_callback
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|radio_vbox
operator|=
name|gimp_radio_group_new2
argument_list|(
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|gimp_radio_button_update
argument_list|,
operator|&
name|shvals
operator|.
name|orientation
argument_list|,
operator|(
name|gpointer
operator|)
name|shvals
operator|.
name|orientation
argument_list|,
name|_
argument_list|(
literal|"Shift Horizontally"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|HORIZONTAL
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Shift Vertically"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|VERTICAL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_vbox
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|radio_vbox
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
name|radio_vbox
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|amount_data
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
literal|"Shift Anount:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|shvals
operator|.
name|shift_amount
argument_list|,
literal|0
argument_list|,
literal|200
argument_list|,
literal|1
argument_list|,
literal|10
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
name|amount_data
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
name|shvals
operator|.
name|shift_amount
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
name|shint
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shift_ok_callback (GtkWidget * widget,gpointer data)
name|shift_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|shint
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
name|GTile
modifier|*
DECL|function|shift_pixel (GDrawable * drawable,GTile * tile,gint x1,gint y1,gint x2,gint y2,gint x,gint y,gint * row,gint * col,guchar * pixel)
name|shift_pixel
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|GTile
modifier|*
name|tile
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
modifier|*
name|row
parameter_list|,
name|gint
modifier|*
name|col
parameter_list|,
name|guchar
modifier|*
name|pixel
parameter_list|)
block|{
specifier|static
name|guchar
name|empty_pixel
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
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|x
operator|>=
name|x1
operator|&&
name|y
operator|>=
name|y1
operator|&&
name|x
operator|<
name|x2
operator|&&
name|y
operator|<
name|y2
condition|)
block|{
if|if
condition|(
operator|(
name|x
operator|>>
literal|6
operator|!=
operator|*
name|col
operator|)
operator|||
operator|(
name|y
operator|>>
literal|6
operator|!=
operator|*
name|row
operator|)
condition|)
block|{
operator|*
name|col
operator|=
name|x
operator|/
literal|64
expr_stmt|;
operator|*
name|row
operator|=
name|y
operator|/
literal|64
expr_stmt|;
if|if
condition|(
name|tile
condition|)
name|gimp_tile_unref
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tile
operator|=
name|gimp_drawable_get_tile
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|,
operator|*
name|row
argument_list|,
operator|*
name|col
argument_list|)
expr_stmt|;
name|gimp_tile_ref
argument_list|(
name|tile
argument_list|)
expr_stmt|;
block|}
name|data
operator|=
name|tile
operator|->
name|data
operator|+
name|tile
operator|->
name|bpp
operator|*
operator|(
name|tile
operator|->
name|ewidth
operator|*
operator|(
name|y
operator|%
literal|64
operator|)
operator|+
operator|(
name|x
operator|%
literal|64
operator|)
operator|)
expr_stmt|;
block|}
else|else
name|data
operator|=
name|empty_pixel
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|drawable
operator|->
name|bpp
condition|;
name|b
operator|++
control|)
name|pixel
index|[
name|b
index|]
operator|=
name|data
index|[
name|b
index|]
expr_stmt|;
return|return
name|tile
return|;
block|}
end_function

end_unit

