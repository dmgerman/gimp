begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Color Enhance 0.10 --- image filter plug-in for The Gimp image  * manipulation program  *  * Copyright (C) 1999 Martin Weber  * Copyright (C) 1996 Federico Mena Quintero  *  * You can contact me at martin.weber@usa.net  * You can contact the original The Gimp authors at gimp@xcf.berkeley.edu  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This simple plug-in does an automatic Saturation stretch.  For each    channel in the image, it finds the minimum and maximum values... it    uses those values to stretch the individual histograms to the full    range.  For some images it may do just what you want; for others    it may be total crap :) This version operates in HSV space    and preserves hue. Most code is taken from autostretch_hsv */
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
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
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
name|Color_Enhance
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
name|indexed_Color_Enhance
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|calc_rgb_to_hsv
parameter_list|(
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|double
modifier|*
name|h
parameter_list|,
name|double
modifier|*
name|s
parameter_list|,
name|double
modifier|*
name|v
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|calc_hsv_to_rgb
parameter_list|(
name|gint
modifier|*
name|r
parameter_list|,
name|gint
modifier|*
name|g
parameter_list|,
name|gint
modifier|*
name|b
parameter_list|,
name|double
name|h
parameter_list|,
name|double
name|s
parameter_list|,
name|double
name|v
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
literal|"plug_in_Color_Enhance"
argument_list|,
name|_
argument_list|(
literal|"Automatically stretch the saturation of the specified drawable to cover all possible ranges."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"This simple plug-in does an automatic saturation stretch.  For each channel in the image, it finds the minimum and maximum values... it uses those values to stretch the individual histograms to the full range.  For some images it may do just what you want; for others it may be total crap :).  This version differs from Contrast Autostretch in that it works in HSV space, and preserves hue."
argument_list|)
argument_list|,
literal|"Martin Weber"
argument_list|,
literal|"Martin Weber"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Image/Colors/Auto/Color Enhance"
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*"
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
name|gint32
name|image_ID
decl_stmt|;
name|INIT_I18N
argument_list|()
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
literal|"Color Enhance..."
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
name|Color_Enhance
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
elseif|else
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|indexed_Color_Enhance
argument_list|(
name|image_ID
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
comment|/* gimp_message ("Color_Enhance: cannot operate on indexed color images"); */
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
DECL|function|indexed_Color_Enhance (gint32 image_ID)
name|indexed_Color_Enhance
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
comment|/* a.d.m. */
block|{
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|ncols
decl_stmt|,
name|i
decl_stmt|;
name|double
name|vhi
init|=
literal|0.0
decl_stmt|,
name|vlo
init|=
literal|1.0
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmap
operator|==
name|NULL
condition|)
block|{
name|printf
argument_list|(
name|_
argument_list|(
literal|"Color_Enhance: cmap was NULL!  Quitting...\n"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
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
name|ncols
condition|;
name|i
operator|++
control|)
block|{
name|double
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|double
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|;
name|double
name|k
decl_stmt|;
name|c
operator|=
literal|255
operator|-
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|m
operator|=
literal|255
operator|-
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|y
operator|=
literal|255
operator|-
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
name|k
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|m
operator|<
name|k
condition|)
name|k
operator|=
name|m
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|k
condition|)
name|k
operator|=
name|y
expr_stmt|;
name|calc_rgb_to_hsv
argument_list|(
name|c
operator|-
name|k
argument_list|,
name|m
operator|-
name|k
argument_list|,
name|y
operator|-
name|k
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|v
operator|>
name|vhi
condition|)
name|vhi
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|v
operator|<
name|vlo
condition|)
name|vlo
operator|=
name|v
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
name|ncols
condition|;
name|i
operator|++
control|)
block|{
name|double
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|;
name|double
name|k
decl_stmt|;
name|c
operator|=
literal|255
operator|-
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|m
operator|=
literal|255
operator|-
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|y
operator|=
literal|255
operator|-
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
name|k
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|m
operator|<
name|k
condition|)
name|k
operator|=
name|m
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|k
condition|)
name|k
operator|=
name|y
expr_stmt|;
name|calc_rgb_to_hsv
argument_list|(
name|c
operator|-
name|k
argument_list|,
name|m
operator|-
name|k
argument_list|,
name|y
operator|-
name|k
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|vhi
operator|!=
name|vlo
condition|)
name|v
operator|=
operator|(
name|v
operator|-
name|vlo
operator|)
operator|/
operator|(
name|vhi
operator|-
name|vlo
operator|)
expr_stmt|;
name|calc_hsv_to_rgb
argument_list|(
operator|&
name|c
argument_list|,
operator|&
name|m
argument_list|,
operator|&
name|y
argument_list|,
name|h
argument_list|,
name|s
argument_list|,
name|v
argument_list|)
expr_stmt|;
name|c
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|c
operator|>
literal|255
condition|)
name|c
operator|=
literal|255
expr_stmt|;
name|m
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|m
operator|>
literal|255
condition|)
name|m
operator|=
literal|255
expr_stmt|;
name|y
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|y
operator|>
literal|255
condition|)
name|y
operator|=
literal|255
expr_stmt|;
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
literal|255
operator|-
name|c
expr_stmt|;
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
literal|255
operator|-
name|m
expr_stmt|;
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
literal|255
operator|-
name|y
expr_stmt|;
block|}
name|gimp_image_set_cmap
argument_list|(
name|image_ID
argument_list|,
name|cmap
argument_list|,
name|ncols
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|Color_Enhance (GDrawable * drawable)
name|Color_Enhance
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
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
name|s
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|double
name|vhi
init|=
literal|0.0
decl_stmt|,
name|vlo
init|=
literal|1.0
decl_stmt|;
name|gint
name|progress
decl_stmt|,
name|max_progress
decl_stmt|;
name|gint
name|has_alpha
decl_stmt|,
name|alpha
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
name|gpointer
name|pr
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
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|alpha
operator|=
operator|(
name|has_alpha
operator|)
condition|?
name|drawable
operator|->
name|bpp
operator|-
literal|1
else|:
name|drawable
operator|->
name|bpp
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
operator|*
literal|2
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
name|src
operator|=
name|src_rgn
operator|.
name|data
expr_stmt|;
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
name|s
operator|=
name|src
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
if|if
condition|(
operator|!
name|has_alpha
operator|||
operator|(
name|has_alpha
operator|&&
name|s
index|[
name|alpha
index|]
operator|)
condition|)
block|{
name|double
name|h
decl_stmt|,
name|z
decl_stmt|,
name|v
decl_stmt|;
name|double
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|;
name|double
name|k
decl_stmt|;
name|c
operator|=
literal|255
operator|-
name|s
index|[
literal|0
index|]
expr_stmt|;
name|m
operator|=
literal|255
operator|-
name|s
index|[
literal|1
index|]
expr_stmt|;
name|y
operator|=
literal|255
operator|-
name|s
index|[
literal|2
index|]
expr_stmt|;
name|k
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|m
operator|<
name|k
condition|)
name|k
operator|=
name|m
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|k
condition|)
name|k
operator|=
name|y
expr_stmt|;
name|calc_rgb_to_hsv
argument_list|(
name|c
operator|-
name|k
argument_list|,
name|m
operator|-
name|k
argument_list|,
name|y
operator|-
name|k
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|z
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|v
operator|>
name|vhi
condition|)
name|vhi
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|v
operator|<
name|vlo
condition|)
name|vlo
operator|=
name|v
expr_stmt|;
block|}
name|s
operator|+=
name|src_rgn
operator|.
name|bpp
expr_stmt|;
block|}
name|src
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
comment|/* Now substitute pixel vales */
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
for|for
control|(
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
name|src
operator|=
name|src_rgn
operator|.
name|data
expr_stmt|;
name|dest
operator|=
name|dest_rgn
operator|.
name|data
expr_stmt|;
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
name|s
operator|=
name|src
expr_stmt|;
name|d
operator|=
name|dest
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
name|double
name|h
decl_stmt|,
name|z
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|;
name|double
name|k
decl_stmt|;
name|c
operator|=
literal|255
operator|-
name|s
index|[
literal|0
index|]
expr_stmt|;
name|m
operator|=
literal|255
operator|-
name|s
index|[
literal|1
index|]
expr_stmt|;
name|y
operator|=
literal|255
operator|-
name|s
index|[
literal|2
index|]
expr_stmt|;
name|k
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|m
operator|<
name|k
condition|)
name|k
operator|=
name|m
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|k
condition|)
name|k
operator|=
name|y
expr_stmt|;
name|calc_rgb_to_hsv
argument_list|(
name|c
operator|-
name|k
argument_list|,
name|m
operator|-
name|k
argument_list|,
name|y
operator|-
name|k
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|z
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|vhi
operator|!=
name|vlo
condition|)
name|v
operator|=
operator|(
name|v
operator|-
name|vlo
operator|)
operator|/
operator|(
name|vhi
operator|-
name|vlo
operator|)
expr_stmt|;
name|calc_hsv_to_rgb
argument_list|(
operator|&
name|c
argument_list|,
operator|&
name|m
argument_list|,
operator|&
name|y
argument_list|,
name|h
argument_list|,
name|z
argument_list|,
name|v
argument_list|)
expr_stmt|;
name|c
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|c
operator|>
literal|255
condition|)
name|c
operator|=
literal|255
expr_stmt|;
name|m
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|m
operator|>
literal|255
condition|)
name|m
operator|=
literal|255
expr_stmt|;
name|y
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|y
operator|>
literal|255
condition|)
name|y
operator|=
literal|255
expr_stmt|;
name|d
index|[
literal|0
index|]
operator|=
literal|255
operator|-
name|c
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
literal|255
operator|-
name|m
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
literal|255
operator|-
name|y
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|d
index|[
name|alpha
index|]
operator|=
name|s
index|[
name|alpha
index|]
expr_stmt|;
name|s
operator|+=
name|src_rgn
operator|.
name|bpp
expr_stmt|;
name|d
operator|+=
name|dest_rgn
operator|.
name|bpp
expr_stmt|;
block|}
name|src
operator|+=
name|src_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
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

begin_function
specifier|static
name|void
DECL|function|calc_rgb_to_hsv (gint r,gint g,gint b,double * hue,double * sat,double * val)
name|calc_rgb_to_hsv
parameter_list|(
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|double
modifier|*
name|hue
parameter_list|,
name|double
modifier|*
name|sat
parameter_list|,
name|double
modifier|*
name|val
parameter_list|)
block|{
name|double
name|red
decl_stmt|,
name|green
decl_stmt|,
name|blue
decl_stmt|;
name|double
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|double
name|min
decl_stmt|,
name|max
decl_stmt|;
name|double
name|delta
decl_stmt|;
name|red
operator|=
operator|(
name|double
operator|)
name|r
operator|/
literal|255.0
expr_stmt|;
name|green
operator|=
operator|(
name|double
operator|)
name|g
operator|/
literal|255.0
expr_stmt|;
name|blue
operator|=
operator|(
name|double
operator|)
name|b
operator|/
literal|255.0
expr_stmt|;
name|h
operator|=
literal|0.0
expr_stmt|;
comment|/* Shut up -Wall */
if|if
condition|(
name|red
operator|>
name|green
condition|)
block|{
if|if
condition|(
name|red
operator|>
name|blue
condition|)
name|max
operator|=
name|red
expr_stmt|;
else|else
name|max
operator|=
name|blue
expr_stmt|;
if|if
condition|(
name|green
operator|<
name|blue
condition|)
name|min
operator|=
name|green
expr_stmt|;
else|else
name|min
operator|=
name|blue
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|green
operator|>
name|blue
condition|)
name|max
operator|=
name|green
expr_stmt|;
else|else
name|max
operator|=
name|blue
expr_stmt|;
if|if
condition|(
name|red
operator|<
name|blue
condition|)
name|min
operator|=
name|red
expr_stmt|;
else|else
name|min
operator|=
name|blue
expr_stmt|;
block|}
name|v
operator|=
name|max
expr_stmt|;
if|if
condition|(
name|max
operator|!=
literal|0.0
condition|)
name|s
operator|=
operator|(
name|max
operator|-
name|min
operator|)
operator|/
name|max
expr_stmt|;
else|else
name|s
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|s
operator|==
literal|0.0
condition|)
name|h
operator|=
literal|0.0
expr_stmt|;
else|else
block|{
name|delta
operator|=
name|max
operator|-
name|min
expr_stmt|;
if|if
condition|(
name|red
operator|==
name|max
condition|)
name|h
operator|=
operator|(
name|green
operator|-
name|blue
operator|)
operator|/
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|green
operator|==
name|max
condition|)
name|h
operator|=
literal|2
operator|+
operator|(
name|blue
operator|-
name|red
operator|)
operator|/
name|delta
expr_stmt|;
elseif|else
if|if
condition|(
name|blue
operator|==
name|max
condition|)
name|h
operator|=
literal|4
operator|+
operator|(
name|red
operator|-
name|green
operator|)
operator|/
name|delta
expr_stmt|;
name|h
operator|/=
literal|6.0
expr_stmt|;
if|if
condition|(
name|h
operator|<
literal|0.0
condition|)
name|h
operator|+=
literal|1.0
expr_stmt|;
elseif|else
if|if
condition|(
name|h
operator|>
literal|1.0
condition|)
name|h
operator|-=
literal|1.0
expr_stmt|;
block|}
operator|*
name|hue
operator|=
name|h
expr_stmt|;
operator|*
name|sat
operator|=
name|s
expr_stmt|;
operator|*
name|val
operator|=
name|v
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|calc_hsv_to_rgb (gint * r,gint * g,gint * b,double h,double s,double v)
name|calc_hsv_to_rgb
parameter_list|(
name|gint
modifier|*
name|r
parameter_list|,
name|gint
modifier|*
name|g
parameter_list|,
name|gint
modifier|*
name|b
parameter_list|,
name|double
name|h
parameter_list|,
name|double
name|s
parameter_list|,
name|double
name|v
parameter_list|)
block|{
name|double
name|hue
decl_stmt|,
name|saturation
decl_stmt|,
name|value
decl_stmt|;
name|double
name|f
decl_stmt|,
name|p
decl_stmt|,
name|q
decl_stmt|,
name|t
decl_stmt|;
if|if
condition|(
name|s
operator|==
literal|0.0
condition|)
block|{
name|h
operator|=
name|v
expr_stmt|;
name|s
operator|=
name|v
expr_stmt|;
name|v
operator|=
name|v
expr_stmt|;
comment|/* heh */
block|}
else|else
block|{
name|hue
operator|=
name|h
operator|*
literal|6.0
expr_stmt|;
name|saturation
operator|=
name|s
expr_stmt|;
name|value
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|hue
operator|==
literal|6.0
condition|)
name|hue
operator|=
literal|0.0
expr_stmt|;
name|f
operator|=
name|hue
operator|-
operator|(
name|int
operator|)
name|hue
expr_stmt|;
name|p
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|)
expr_stmt|;
name|q
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|*
name|f
operator|)
expr_stmt|;
name|t
operator|=
name|value
operator|*
operator|(
literal|1.0
operator|-
name|saturation
operator|*
operator|(
literal|1.0
operator|-
name|f
operator|)
operator|)
expr_stmt|;
switch|switch
condition|(
operator|(
name|int
operator|)
name|hue
condition|)
block|{
case|case
literal|0
case|:
name|h
operator|=
name|value
expr_stmt|;
name|s
operator|=
name|t
expr_stmt|;
name|v
operator|=
name|p
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|h
operator|=
name|q
expr_stmt|;
name|s
operator|=
name|value
expr_stmt|;
name|v
operator|=
name|p
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|h
operator|=
name|p
expr_stmt|;
name|s
operator|=
name|value
expr_stmt|;
name|v
operator|=
name|t
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|h
operator|=
name|p
expr_stmt|;
name|s
operator|=
name|q
expr_stmt|;
name|v
operator|=
name|value
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|h
operator|=
name|t
expr_stmt|;
name|s
operator|=
name|p
expr_stmt|;
name|v
operator|=
name|value
expr_stmt|;
break|break;
case|case
literal|5
case|:
name|h
operator|=
name|value
expr_stmt|;
name|s
operator|=
name|p
expr_stmt|;
name|v
operator|=
name|q
expr_stmt|;
break|break;
block|}
block|}
operator|*
name|r
operator|=
name|h
operator|*
literal|255
expr_stmt|;
operator|*
name|g
operator|=
name|s
operator|*
literal|255
expr_stmt|;
operator|*
name|b
operator|=
name|v
operator|*
literal|255
expr_stmt|;
block|}
end_function

end_unit

