begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Normalize 1.00 --- image filter plug-in for The GIMP  *  * Copyright (C) 1997 Adam D. Moss (adam@foxbox.org)  * Very largely based on Quartic's "Contrast Autostretch"  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This plugin performs almost the same operation as the 'contrast  * autostretch' plugin, except that it won't allow the colour channels  * to normalize independently.  This is actually what most people probably  * want instead of contrast-autostretch; use c-a only if you wish to remove  * an undesirable colour-tint from a source image which is supposed to  * contain pure-white and pure-black.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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
file|<libgimp/gimp.h>
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
name|norma
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
name|indexed_norma
parameter_list|(
name|gint32
name|image_ID
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
literal|"plug_in_normalize"
argument_list|,
literal|"Normalize the contrast of the specified drawable to "
literal|"cover all possible ranges."
argument_list|,
literal|"This plugin performs almost the same operation as "
literal|"the 'contrast autostretch' plugin, except that it "
literal|"won't allow the color channels to normalize "
literal|"independently.  This is actually what most people "
literal|"probably want instead of contrast-autostretch; use "
literal|"c-a only if you wish to remove an undesirable "
literal|"color-tint from a source image which is supposed to "
literal|"contain pure-white and pure-black."
argument_list|,
literal|"Adam D. Moss, Federico Mena Quintero"
argument_list|,
literal|"Adam D. Moss, Federico Mena Quintero"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Image/Colors/Auto/Normalize"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|,
name|PROC_PLUG_IN
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
literal|"Normalizing..."
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
name|norma
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
name|indexed_norma
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
comment|/* gimp_message ("normalize: cannot operate on indexed color images"); */
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
DECL|function|indexed_norma (gint32 image_ID)
name|indexed_norma
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
name|gint
name|hi
init|=
literal|0
decl_stmt|,
name|lo
init|=
literal|255
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
literal|"normalize: cmap was NULL!  Quitting...\n"
argument_list|)
expr_stmt|;
return|return;
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
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|>
name|hi
condition|)
name|hi
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|>
name|hi
condition|)
name|hi
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|>
name|hi
condition|)
name|hi
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|<
name|lo
condition|)
name|lo
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|<
name|lo
condition|)
name|lo
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|<
name|lo
condition|)
name|lo
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
block|}
if|if
condition|(
name|hi
operator|!=
name|lo
condition|)
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
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
operator|(
literal|255
operator|*
operator|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|-
name|lo
operator|)
operator|)
operator|/
operator|(
name|hi
operator|-
name|lo
operator|)
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
operator|(
literal|255
operator|*
operator|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|-
name|lo
operator|)
operator|)
operator|/
operator|(
name|hi
operator|-
name|lo
operator|)
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
operator|(
literal|255
operator|*
operator|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|-
name|lo
operator|)
operator|)
operator|/
operator|(
name|hi
operator|-
name|lo
operator|)
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
DECL|function|norma (GDrawable * drawable)
name|norma
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
name|guchar
name|min
decl_stmt|,
name|max
decl_stmt|;
name|guchar
name|range
decl_stmt|;
name|guchar
name|lut
index|[
literal|256
index|]
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
decl_stmt|,
name|b
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
comment|/* Get minimum and maximum values for each channel */
name|min
operator|=
literal|255
expr_stmt|;
name|max
operator|=
literal|0
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
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
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
if|if
condition|(
name|s
index|[
name|b
index|]
operator|<
name|min
condition|)
name|min
operator|=
name|s
index|[
name|b
index|]
expr_stmt|;
if|if
condition|(
name|s
index|[
name|b
index|]
operator|>
name|max
condition|)
name|max
operator|=
name|s
index|[
name|b
index|]
expr_stmt|;
block|}
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
comment|/* Calculate LUT */
name|range
operator|=
name|max
operator|-
name|min
expr_stmt|;
if|if
condition|(
name|range
operator|!=
literal|0
condition|)
for|for
control|(
name|x
operator|=
name|min
init|;
name|x
operator|<=
name|max
condition|;
name|x
operator|++
control|)
name|lut
index|[
name|x
index|]
operator|=
literal|255
operator|*
operator|(
name|x
operator|-
name|min
operator|)
operator|/
name|range
expr_stmt|;
else|else
name|lut
index|[
name|min
index|]
operator|=
name|min
expr_stmt|;
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
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|d
index|[
name|b
index|]
operator|=
name|lut
index|[
name|s
index|[
name|b
index|]
index|]
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

end_unit

