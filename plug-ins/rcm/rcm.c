begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Colormap-Rotation plug-in. Exchanges two color ranges.  *  * Copyright (C) 1999 Sven Anders (anderss@fmi.uni-passau.de)  *                    Based on code from Pavel Grinfeld (pavel@ml.com)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------  * Change log:  *   * Version 2.0, 04 April 1999.  *  Nearly complete rewrite, made plug-in stable.  *  (Works with GIMP 1.1 and GTK+ 1.2)  *  * Version 1.0, 27 March 1997.  *  Initial (unstable) release by Pavel Grinfeld  *  *-----------------------------------------------------------------------------------*/
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
file|<math.h>
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
file|<libgimp/gimpintl.h>
end_include

begin_include
include|#
directive|include
file|"rcm.h"
end_include

begin_include
include|#
directive|include
file|"rcm_misc.h"
end_include

begin_include
include|#
directive|include
file|"rcm_dialog.h"
end_include

begin_include
include|#
directive|include
file|"rcm_callback.h"
end_include

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Forward declarations */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_function_decl
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Global variables */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_decl_stmt
DECL|variable|Current
name|RcmParams
name|Current
init|=
block|{
name|SELECTION
block|,
comment|/* SELECTION ONLY */
name|TRUE
block|,
comment|/* REAL TIME */
name|FALSE
block|,
comment|/* SUCCESS */
name|RADIANS_OVER_PI
block|,
comment|/* START IN RADIANS OVER PI */
name|GRAY_TO
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Local variables */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
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

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Dummy function */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Query plug-in */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_function
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
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
literal|"Input image (used for indexed images)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,   }
decl_stmt|;
name|GParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
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
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"Colormap rotation plug-in"
argument_list|,
literal|"Colormap rotation as in xv"
argument_list|,
literal|"Exchanges two color ranges. "
expr|\
literal|"Based on code from Pavel Grinfeld (pavel@ml.com). "
expr|\
literal|"This version written by Sven Anders (anderss@fmi.uni-passau.de)."
argument_list|,
literal|"Sven Anders (anderss@fmi.uni-passau.de) and Pavel Grinfeld (pavel@ml.com)"
argument_list|,
literal|"Sven Anders (anderss@fmi.uni-passau.de)"
argument_list|,
literal|"04th April 1999"
argument_list|,
literal|"<Image>/Filters/Darkroom/Colormap Rotation"
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

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Rotate colormap of a single row */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_function
DECL|function|rcm_row (const guchar * src_row,guchar * dest_row,gint row,gint row_width,gint bytes)
name|void
name|rcm_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src_row
parameter_list|,
name|guchar
modifier|*
name|dest_row
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|row_width
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|gint
name|col
decl_stmt|,
name|bytenum
decl_stmt|,
name|skip
decl_stmt|;
name|hsv
name|H
decl_stmt|,
name|S
decl_stmt|,
name|V
decl_stmt|,
name|R
decl_stmt|,
name|G
decl_stmt|,
name|B
decl_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|row_width
condition|;
name|col
operator|++
control|)
block|{
name|skip
operator|=
literal|0
expr_stmt|;
name|R
operator|=
operator|(
name|float
operator|)
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|G
operator|=
operator|(
name|float
operator|)
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
operator|/
literal|255.0
expr_stmt|;
name|B
operator|=
operator|(
name|float
operator|)
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
operator|/
literal|255.0
expr_stmt|;
name|rgb_to_hsv
argument_list|(
name|R
argument_list|,
name|G
argument_list|,
name|B
argument_list|,
operator|&
name|H
argument_list|,
operator|&
name|S
argument_list|,
operator|&
name|V
argument_list|)
expr_stmt|;
if|if
condition|(
name|rcm_is_gray
argument_list|(
name|S
argument_list|)
condition|)
block|{
if|if
condition|(
name|Current
operator|.
name|Gray_to_from
operator|==
name|GRAY_FROM
condition|)
block|{
if|if
condition|(
name|rcm_angle_inside_slice
argument_list|(
name|Current
operator|.
name|Gray
operator|->
name|hue
argument_list|,
name|Current
operator|.
name|From
operator|->
name|angle
argument_list|)
operator|<=
literal|1
condition|)
block|{
name|H
operator|=
name|Current
operator|.
name|Gray
operator|->
name|hue
operator|/
name|TP
expr_stmt|;
name|S
operator|=
name|Current
operator|.
name|Gray
operator|->
name|satur
expr_stmt|;
block|}
else|else
block|{
name|skip
operator|=
literal|1
expr_stmt|;
block|}
block|}
else|else
block|{
name|skip
operator|=
literal|1
expr_stmt|;
name|hsv_to_rgb
argument_list|(
name|Current
operator|.
name|Gray
operator|->
name|hue
operator|/
name|TP
argument_list|,
name|Current
operator|.
name|Gray
operator|->
name|satur
argument_list|,
name|V
argument_list|,
operator|&
name|R
argument_list|,
operator|&
name|G
argument_list|,
operator|&
name|B
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|skip
condition|)
block|{
name|H
operator|=
name|rcm_linear
argument_list|(
name|rcm_left_end
argument_list|(
name|Current
operator|.
name|From
operator|->
name|angle
argument_list|)
argument_list|,
name|rcm_right_end
argument_list|(
name|Current
operator|.
name|From
operator|->
name|angle
argument_list|)
argument_list|,
name|rcm_left_end
argument_list|(
name|Current
operator|.
name|To
operator|->
name|angle
argument_list|)
argument_list|,
name|rcm_right_end
argument_list|(
name|Current
operator|.
name|To
operator|->
name|angle
argument_list|)
argument_list|,
name|H
operator|*
name|TP
argument_list|)
expr_stmt|;
name|H
operator|=
name|angle_mod_2PI
argument_list|(
name|H
argument_list|)
operator|/
name|TP
expr_stmt|;
name|hsv_to_rgb
argument_list|(
name|H
argument_list|,
name|S
argument_list|,
name|V
argument_list|,
operator|&
name|R
argument_list|,
operator|&
name|G
argument_list|,
operator|&
name|B
argument_list|)
expr_stmt|;
block|}
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|0
index|]
operator|=
name|R
operator|*
literal|255
expr_stmt|;
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
name|G
operator|*
literal|255
expr_stmt|;
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
name|B
operator|*
literal|255
expr_stmt|;
if|if
condition|(
name|bytes
operator|>
literal|3
condition|)
block|{
for|for
control|(
name|bytenum
operator|=
literal|3
init|;
name|bytenum
operator|<
name|bytes
condition|;
name|bytenum
operator|++
control|)
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
name|bytenum
index|]
operator|=
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
name|bytenum
index|]
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* Rotate colormap row by row ... */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_function
DECL|function|rcm (GDrawable * drawable)
name|void
name|rcm
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
name|src_row
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|;
name|gint
name|row
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
name|src_row
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
name|dest_row
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
name|src_row
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
name|rcm_row
argument_list|(
name|src_row
argument_list|,
name|dest_row
argument_list|,
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_row
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
if|if
condition|(
operator|(
name|row
operator|%
literal|10
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
comment|/*  update the processed region  */
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
name|src_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|dest_row
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_comment
comment|/* STANDARD RUN */
end_comment

begin_comment
comment|/*-----------------------------------------------------------------------------------*/
end_comment

begin_function
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
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
block|{
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
name|Current
operator|.
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
name|Current
operator|.
name|mask
operator|=
name|gimp_drawable_get
argument_list|(
name|gimp_image_get_selection
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|)
argument_list|)
expr_stmt|;
comment|/* works not on INDEXED images */
if|if
condition|(
name|gimp_drawable_indexed
argument_list|(
name|Current
operator|.
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_gray
argument_list|(
name|Current
operator|.
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
comment|/* call dialog and rotate the colormap */
if|if
condition|(
name|gimp_drawable_color
argument_list|(
name|Current
operator|.
name|drawable
operator|->
name|id
argument_list|)
operator|&&
name|rcm_dialog
argument_list|()
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Rotating the colormap..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|Current
operator|.
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
name|rcm
argument_list|(
name|Current
operator|.
name|drawable
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
else|else
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
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
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
name|gimp_drawable_detach
argument_list|(
name|Current
operator|.
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

