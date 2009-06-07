begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/****************************************************************************  * This is a plugin for GIMP v 0.99.8 or later.  Documentation is  * available at http://www.rru.com/~meo/gimp/ .  *  * Copyright (C) 1997-98 Miles O'Neal<meo@rru.com>  http://www.rru.com/~meo/  * Blur code Copyright (C) 1995 Spencer Kimball and Peter Mattis  * GUI based on GTK code from:  *    alienmap (Copyright (C) 1996, 1997 Daniel Cotting)  *    plasma   (Copyright (C) 1996 Stephen Norris),  *    oilify   (Copyright (C) 1996 Torsten Martinsen),  *    ripple   (Copyright (C) 1997 Brian Degenhardt) and  *    whirl    (Copyright (C) 1997 Federico Mena Quintero).  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  ****************************************************************************/
end_comment

begin_comment
comment|/****************************************************************************  * Blur:  *  * blur version 2.1 (10 June 2004 WES)  * history  *     2.1 - 10 June 2004 WES  *         removed dialog along with randomization and repeat options  *     2.0 -  1 May 1998 MEO  *         based on randomize 1.7  *  * Please send any patches or suggestions to the author: meo@rru.com .  *  * Blur applies a 3x3 blurring convolution kernel to the specified drawable.  *  * For each pixel in the selection or image,  * whether to change the pixel is decided by picking a  * random number, weighted by the user's "randomization" percentage.  * If the random number is in range, the pixel is modified.  For  * blurring, an average is determined from the current and adjacent  * pixels. *(Except for the random factor, the blur code came  * straight from the original S&P blur plug-in.)*  *  * This works only with RGB and grayscale images.  *  ****************************************************************************/
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/*********************************  *  *  PLUGIN-SPECIFIC CONSTANTS  *  ********************************/
end_comment

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-blur"
end_define

begin_comment
comment|/*********************************  *  *  LOCAL FUNCTIONS  *  ********************************/
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

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
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

begin_function_decl
specifier|static
name|void
name|blur
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|inline
name|void
name|blur_prepare_row
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/************************************ Guts ***********************************/
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_comment
comment|/*********************************  *  *  query() - query_proc  *  *      called by GIMP to learn about this plug-in  *  ********************************/
end_comment

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
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
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
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
block|,   }
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Simple blur, fast but not very strong"
argument_list|)
argument_list|,
literal|"This plug-in blurs the specified drawable, using "
literal|"a 3x3 blur. Indexed images are not supported."
argument_list|,
literal|"Miles O'Neal<meo@rru.com>"
argument_list|,
literal|"Miles O'Neal, Spencer Kimball, Peter Mattis, "
literal|"Torsten Martinsen, Brian Degenhardt, "
literal|"Federico Mena Quintero, Stephen Norris, "
literal|"Daniel Cotting"
argument_list|,
literal|"1995-1998"
argument_list|,
name|N_
argument_list|(
literal|"_Blur"
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
literal|"<Image>/Filters/Blur"
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
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|INIT_I18N
argument_list|()
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
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
operator|!=
literal|0
operator|||
name|nparams
operator|<
literal|3
condition|)
block|{
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
return|return;
block|}
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
comment|/*    *  Make sure the drawable type is appropriate.    */
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
literal|"Blurring"
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
name|blur
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
block|{
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*********************************  *  *  blur_prepare_row()  *  *  Get a row of pixels.  If the requested row  *  is off the edge, clone the edge row.  *  ********************************/
end_comment

begin_function
specifier|static
specifier|inline
name|void
DECL|function|blur_prepare_row (GimpPixelRgn * pixel_rgn,guchar * data,gint x,gint y,gint w)
name|blur_prepare_row
parameter_list|(
name|GimpPixelRgn
modifier|*
name|pixel_rgn
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|)
block|{
name|gint
name|b
decl_stmt|;
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|pixel_rgn
operator|->
name|h
operator|-
literal|1
argument_list|)
expr_stmt|;
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
comment|/*    *  Fill in edge pixels    */
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
name|data
index|[
operator|-
operator|(
name|gint
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
end_function

begin_comment
comment|/*********************************  *  *  blur()  *  *  Actually mess with the image.  *  ********************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|blur (GimpDrawable * drawable)
name|blur
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelRgn
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
name|ind
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
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
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|height
expr_stmt|;
comment|/*    *  Get the size of the input image. (This will/must be the same    *  as the size of the output image.  Also get alpha info.    */
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
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
comment|/*    *  allocate row buffers    */
name|prev_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
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
name|g_new
argument_list|(
name|guchar
argument_list|,
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
name|g_new
argument_list|(
name|guchar
argument_list|,
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
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*    *  initialize the pixel regions    */
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
comment|/*    *  prepare the first row and previous row    */
name|blur_prepare_row
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
name|blur_prepare_row
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
comment|/*    *  loop through the rows, applying the selected convolution    */
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
name|blur_prepare_row
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
name|ind
operator|=
literal|0
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
name|ind
operator|++
expr_stmt|;
if|if
condition|(
name|ind
operator|==
name|bytes
operator|||
operator|!
name|has_alpha
condition|)
block|{
comment|/*                *  If no alpha channel,                *   or if there is one and this is it...                */
operator|*
name|d
operator|++
operator|=
operator|(
operator|(
name|gint
operator|)
name|pr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|pr
index|[
name|col
index|]
operator|+
operator|(
name|gint
operator|)
name|pr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|cr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|cr
index|[
name|col
index|]
operator|+
operator|(
name|gint
operator|)
name|cr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|nr
index|[
name|col
operator|-
name|bytes
index|]
operator|+
operator|(
name|gint
operator|)
name|nr
index|[
name|col
index|]
operator|+
operator|(
name|gint
operator|)
name|nr
index|[
name|col
operator|+
name|bytes
index|]
operator|+
literal|4
operator|)
operator|/
literal|9
expr_stmt|;
name|ind
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
comment|/*                *  otherwise we have an alpha channel,                *   but this is a color channel                */
operator|*
name|d
operator|++
operator|=
name|ROUND
argument_list|(
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|pr
index|[
name|col
operator|-
name|bytes
index|]
operator|*
name|pr
index|[
name|col
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|pr
index|[
name|col
index|]
operator|*
name|pr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|pr
index|[
name|col
operator|+
name|bytes
index|]
operator|*
name|pr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|cr
index|[
name|col
operator|-
name|bytes
index|]
operator|*
name|cr
index|[
name|col
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|cr
index|[
name|col
index|]
operator|*
name|cr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|cr
index|[
name|col
operator|+
name|bytes
index|]
operator|*
name|cr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|nr
index|[
name|col
operator|-
name|bytes
index|]
operator|*
name|nr
index|[
name|col
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|nr
index|[
name|col
index|]
operator|*
name|nr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|+
call|(
name|gdouble
call|)
argument_list|(
name|nr
index|[
name|col
operator|+
name|bytes
index|]
operator|*
name|nr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
argument_list|)
operator|)
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|pr
index|[
name|col
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|pr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|pr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|cr
index|[
name|col
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|cr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|cr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|nr
index|[
name|col
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|nr
index|[
name|col
operator|+
name|bytes
operator|-
name|ind
index|]
operator|+
operator|(
name|gdouble
operator|)
name|nr
index|[
name|col
operator|+
literal|2
operator|*
name|bytes
operator|-
name|ind
index|]
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*        *  Save the modified row, shuffle the row pointers, and every        *  so often, update the progress meter.        */
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
literal|32
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|row
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
comment|/*    *  update the blurred region    */
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
comment|/*    *  clean up after ourselves.    */
name|g_free
argument_list|(
name|prev_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cur_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|next_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

