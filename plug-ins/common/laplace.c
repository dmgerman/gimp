begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This plugin by thorsten@arch.usyd.edu.au           */
end_comment

begin_comment
comment|/* Based on S&P's Gauss and Laplace filters              */
end_comment

begin_comment
comment|/* updated 11/04/97:    Use 8-pixel neighbourhood to create outline,    use min-max operation for local gradient,    don't use rint;    if gamma-channel: set to white if at least one colour channel is>15 */
end_comment

begin_comment
comment|/* update 03/10/97    #ifdef MAX and MIN */
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
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

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
name|void
name|laplace
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
name|laplace_prepare_row
parameter_list|(
name|GPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_laplace"
argument_list|,
name|_
argument_list|(
literal|"Edge Detection with Laplace Operation"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"This plugin creates one-pixel wide edges from the image, with the value proportional to the gradient. It uses the Laplace operator (a 3x3 kernel with -8 in the middle)The image has to be laplacered to get usefull results, a gauss_iir with 1.5 - 5.0 depending on the noise in the image is best"
argument_list|)
argument_list|,
literal|"Thorsten Schnier"
argument_list|,
literal|"Thorsten Schnier"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Edge-Detect/Laplace"
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
name|INIT_I18N
argument_list|()
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
name|laplace
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
block|}
else|else
block|{
comment|/* gimp_message ("laplace: cannot operate on indexed color images"); */
name|status
operator|=
name|STATUS_EXECUTION_ERROR
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
DECL|function|laplace_prepare_row (GPixelRgn * pixel_rgn,guchar * data,int x,int y,int w)
name|laplace_prepare_row
parameter_list|(
name|GPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|w
parameter_list|)
block|{
name|int
name|b
decl_stmt|;
if|if
condition|(
name|y
operator|==
literal|0
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
operator|(
name|y
operator|+
literal|1
operator|)
argument_list|,
name|w
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|y
operator|==
name|pixel_rgn
operator|->
name|h
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
operator|(
name|y
operator|-
literal|1
operator|)
argument_list|,
name|w
argument_list|)
expr_stmt|;
else|else
name|gimp_pixel_rgn_get_row
argument_list|(
name|pixel_rgn
argument_list|,
name|data
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|)
expr_stmt|;
comment|/*  Fill in edge pixels  */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|pixel_rgn
operator|->
name|bpp
condition|;
name|b
operator|++
control|)
block|{
name|data
index|[
operator|-
operator|(
name|int
operator|)
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
operator|=
name|data
index|[
name|b
index|]
expr_stmt|;
name|data
index|[
name|w
operator|*
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
operator|=
name|data
index|[
operator|(
name|w
operator|-
literal|1
operator|)
operator|*
name|pixel_rgn
operator|->
name|bpp
operator|+
name|b
index|]
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|SIGN (a)
define|#
directive|define
name|SIGN
parameter_list|(
name|a
parameter_list|)
value|(((a)> 0) ? 1 : -1)
end_define

begin_define
DECL|macro|RMS (a,b)
define|#
directive|define
name|RMS
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|(sqrt (pow ((a),2) + pow ((b), 2)))
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|MAX
end_ifndef

begin_define
DECL|macro|MAX (a,b)
define|#
directive|define
name|MAX
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|(((a)> (b)) ? (a) : (b))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|MIN
end_ifndef

begin_define
DECL|macro|MIN (a,b)
define|#
directive|define
name|MIN
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|(((a)< (b)) ? (a) : (b))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|BLACK_REGION (val)
define|#
directive|define
name|BLACK_REGION
parameter_list|(
name|val
parameter_list|)
value|((val)> 128)
end_define

begin_define
DECL|macro|WHITE_REGION (val)
define|#
directive|define
name|WHITE_REGION
parameter_list|(
name|val
parameter_list|)
value|((val)<= 128)
end_define

begin_function
DECL|function|minmax (gint x1,gint x2,gint x3,gint x4,gint x5,gint * min_result,gint * max_result)
specifier|static
name|void
name|minmax
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|x3
parameter_list|,
name|gint
name|x4
parameter_list|,
name|gint
name|x5
parameter_list|,
name|gint
modifier|*
name|min_result
parameter_list|,
name|gint
modifier|*
name|max_result
parameter_list|)
block|{
name|gint
name|min1
decl_stmt|,
name|min2
decl_stmt|,
name|max1
decl_stmt|,
name|max2
decl_stmt|;
if|if
condition|(
name|x1
operator|>
name|x2
condition|)
block|{
name|max1
operator|=
name|x1
expr_stmt|;
name|min1
operator|=
name|x2
expr_stmt|;
block|}
else|else
block|{
name|max1
operator|=
name|x2
expr_stmt|;
name|min1
operator|=
name|x1
expr_stmt|;
block|}
if|if
condition|(
name|x3
operator|>
name|x4
condition|)
block|{
name|max2
operator|=
name|x3
expr_stmt|;
name|min2
operator|=
name|x4
expr_stmt|;
block|}
else|else
block|{
name|max2
operator|=
name|x4
expr_stmt|;
name|min2
operator|=
name|x3
expr_stmt|;
block|}
if|if
condition|(
name|min1
operator|<
name|min2
condition|)
operator|*
name|min_result
operator|=
name|MIN
argument_list|(
name|min1
argument_list|,
name|x5
argument_list|)
expr_stmt|;
else|else
operator|*
name|min_result
operator|=
name|MIN
argument_list|(
name|min2
argument_list|,
name|x5
argument_list|)
expr_stmt|;
if|if
condition|(
name|max1
operator|>
name|max2
condition|)
operator|*
name|max_result
operator|=
name|MAX
argument_list|(
name|max1
argument_list|,
name|x5
argument_list|)
expr_stmt|;
else|else
operator|*
name|max_result
operator|=
name|MAX
argument_list|(
name|max2
argument_list|,
name|x5
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|laplace (GDrawable * drawable)
name|laplace
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
name|gint
name|current
decl_stmt|;
name|gint
name|gradient
decl_stmt|;
name|gint
name|max_gradient
init|=
literal|0
decl_stmt|;
name|gint
name|alpha
decl_stmt|;
name|gint
name|counter
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
name|prev_row
decl_stmt|,
modifier|*
name|pr
decl_stmt|;
name|guchar
modifier|*
name|cur_row
decl_stmt|,
modifier|*
name|cr
decl_stmt|;
name|guchar
modifier|*
name|next_row
decl_stmt|,
modifier|*
name|nr
decl_stmt|;
name|guchar
modifier|*
name|tmp
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
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
name|minval
decl_stmt|,
name|maxval
decl_stmt|;
name|float
name|scale
init|=
literal|1.0
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
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Laplace..."
argument_list|)
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
name|alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
comment|/*  allocate row buffers  */
name|prev_row
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
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
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
operator|+
literal|2
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|next_row
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
operator|+
literal|2
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
name|pr
operator|=
name|prev_row
operator|+
name|bytes
expr_stmt|;
name|cr
operator|=
name|cur_row
operator|+
name|bytes
expr_stmt|;
name|nr
operator|=
name|next_row
operator|+
name|bytes
expr_stmt|;
name|laplace_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|pr
argument_list|,
name|x1
argument_list|,
name|y1
operator|-
literal|1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|laplace_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|cr
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
argument_list|)
expr_stmt|;
comment|/*  loop through the rows, applying the laplace convolution  */
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
comment|/*  prepare the next row  */
name|laplace_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|nr
argument_list|,
name|x1
argument_list|,
name|row
operator|+
literal|1
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
operator|++
control|)
if|if
condition|(
name|alpha
operator|&&
operator|(
operator|(
operator|(
name|col
operator|+
literal|1
operator|)
operator|%
name|bytes
operator|)
operator|==
literal|0
operator|)
condition|)
comment|/* the alpha channel */
operator|*
name|d
operator|++
operator|=
name|cr
index|[
name|col
index|]
expr_stmt|;
else|else
block|{
name|minmax
argument_list|(
name|pr
index|[
name|col
index|]
argument_list|,
name|cr
index|[
name|col
operator|-
name|bytes
index|]
argument_list|,
name|cr
index|[
name|col
index|]
argument_list|,
name|cr
index|[
name|col
operator|+
name|bytes
index|]
argument_list|,
name|nr
index|[
name|col
index|]
argument_list|,
operator|&
name|minval
argument_list|,
operator|&
name|maxval
argument_list|)
expr_stmt|;
comment|/* four-neighbourhood */
name|gradient
operator|=
operator|(
literal|0.5
operator|*
name|MIN
argument_list|(
operator|(
name|maxval
operator|-
name|cr
index|[
name|col
index|]
operator|)
argument_list|,
operator|(
name|cr
index|[
name|col
index|]
operator|-
name|minval
operator|)
argument_list|)
operator|)
expr_stmt|;
name|max_gradient
operator|=
name|MAX
argument_list|(
name|abs
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|max_gradient
argument_list|)
expr_stmt|;
operator|*
name|d
operator|++
operator|=
operator|(
operator|(
name|pr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
name|pr
index|[
name|col
index|]
operator|+
name|pr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
name|cr
index|[
name|col
operator|-
name|bytes
index|]
operator|-
operator|(
literal|8
operator|*
name|cr
index|[
name|col
index|]
operator|)
operator|+
name|cr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
name|nr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
name|nr
index|[
name|col
index|]
operator|+
name|nr
index|[
name|col
operator|+
name|bytes
index|]
operator|)
operator|>
literal|0
operator|)
condition|?
name|gradient
else|:
operator|(
literal|128
operator|+
name|gradient
operator|)
expr_stmt|;
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
comment|/*  shuffle the row pointers  */
name|tmp
operator|=
name|pr
expr_stmt|;
name|pr
operator|=
name|cr
expr_stmt|;
name|cr
operator|=
name|nr
expr_stmt|;
name|nr
operator|=
name|tmp
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
comment|/* now clean up: leave only edges, but keep gradient value */
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
name|TRUE
argument_list|)
expr_stmt|;
name|pr
operator|=
name|prev_row
operator|+
name|bytes
expr_stmt|;
name|cr
operator|=
name|cur_row
operator|+
name|bytes
expr_stmt|;
name|nr
operator|=
name|next_row
operator|+
name|bytes
expr_stmt|;
name|laplace_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|pr
argument_list|,
name|x1
argument_list|,
name|y1
operator|-
literal|1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|laplace_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|cr
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
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Cleanup..."
argument_list|)
argument_list|)
expr_stmt|;
name|scale
operator|=
operator|(
literal|255.0
operator|/
operator|(
name|float
operator|)
name|max_gradient
operator|)
expr_stmt|;
name|counter
operator|=
literal|0
expr_stmt|;
comment|/*  loop through the rows, applying the laplace convolution  */
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
comment|/*  prepare the next row  */
name|laplace_prepare_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|nr
argument_list|,
name|x1
argument_list|,
name|row
operator|+
literal|1
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
operator|++
control|)
block|{
name|current
operator|=
name|cr
index|[
name|col
index|]
expr_stmt|;
name|current
operator|=
operator|(
name|WHITE_REGION
argument_list|(
name|current
argument_list|)
operator|&&
operator|(
name|BLACK_REGION
argument_list|(
name|pr
index|[
name|col
operator|-
name|bytes
index|]
argument_list|)
operator|||
name|BLACK_REGION
argument_list|(
name|pr
index|[
name|col
index|]
argument_list|)
operator|||
name|BLACK_REGION
argument_list|(
name|pr
index|[
name|col
operator|+
name|bytes
index|]
argument_list|)
operator|||
name|BLACK_REGION
argument_list|(
name|cr
index|[
name|col
operator|-
name|bytes
index|]
argument_list|)
operator|||
name|BLACK_REGION
argument_list|(
name|cr
index|[
name|col
operator|+
name|bytes
index|]
argument_list|)
operator|||
name|BLACK_REGION
argument_list|(
name|nr
index|[
name|col
operator|-
name|bytes
index|]
argument_list|)
operator|||
name|BLACK_REGION
argument_list|(
name|nr
index|[
name|col
index|]
argument_list|)
operator|||
name|BLACK_REGION
argument_list|(
name|nr
index|[
name|col
operator|+
name|bytes
index|]
argument_list|)
operator|)
operator|)
condition|?
call|(
name|gint
call|)
argument_list|(
name|scale
operator|*
operator|(
call|(
name|float
call|)
argument_list|(
operator|(
name|current
operator|>=
literal|128
operator|)
condition|?
operator|(
name|current
operator|-
literal|128
operator|)
else|:
name|current
argument_list|)
operator|)
argument_list|)
else|:
literal|0
expr_stmt|;
if|if
condition|(
name|alpha
operator|&&
operator|(
operator|(
operator|(
name|col
operator|+
literal|1
operator|)
operator|%
name|bytes
operator|)
operator|==
literal|0
operator|)
condition|)
block|{
comment|/* the alpha channel */
operator|*
name|d
operator|++
operator|=
operator|(
name|counter
operator|==
literal|0
operator|)
condition|?
literal|0
else|:
literal|255
expr_stmt|;
name|counter
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
operator|*
name|d
operator|++
operator|=
name|current
expr_stmt|;
if|if
condition|(
name|current
operator|>
literal|15
condition|)
name|counter
operator|++
expr_stmt|;
block|}
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
comment|/*  shuffle the row pointers  */
name|tmp
operator|=
name|pr
expr_stmt|;
name|pr
operator|=
name|cr
expr_stmt|;
name|cr
operator|=
name|nr
expr_stmt|;
name|nr
operator|=
name|tmp
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
comment|/*  update the laplaced region  */
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
name|prev_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|cur_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|next_row
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

