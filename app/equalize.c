begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"equalize.h"
end_include

begin_include
include|#
directive|include
file|"interface.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_struct
DECL|struct|hist_lut_struct
struct|struct
name|hist_lut_struct
block|{
DECL|member|histogram
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
DECL|member|part
name|int
name|part
index|[
literal|5
index|]
index|[
literal|257
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|float
name|equalize_lut_func
parameter_list|(
name|struct
name|hist_lut_struct
modifier|*
name|hlut
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|equalize
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Argument
modifier|*
name|equalize_invoker
parameter_list|(
name|Argument
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpLut
modifier|*
name|eq_histogram_lut
parameter_list|(
name|GimpHistogram
modifier|*
name|hist
parameter_list|,
name|int
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|image_equalize (gimage_ptr)
name|image_equalize
parameter_list|(
name|gimage_ptr
parameter_list|)
name|void
modifier|*
name|gimage_ptr
decl_stmt|;
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|mask_only
init|=
name|TRUE
decl_stmt|;
name|gimage
operator|=
operator|(
name|GImage
operator|*
operator|)
name|gimage_ptr
expr_stmt|;
name|drawable
operator|=
name|gimage_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Equalize does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|equalize
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|mask_only
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|equalize (gimage,drawable,mask_only)
name|equalize
parameter_list|(
name|gimage
parameter_list|,
name|drawable
parameter_list|,
name|mask_only
parameter_list|)
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|mask_only
decl_stmt|;
block|{
name|Channel
modifier|*
name|sel_mask
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|maskPR
decl_stmt|,
modifier|*
name|sel_maskPR
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dest
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|unsigned
name|char
modifier|*
name|mask
decl_stmt|,
modifier|*
name|m
decl_stmt|;
name|int
name|no_mask
decl_stmt|;
name|int
name|h
decl_stmt|,
name|j
decl_stmt|,
name|b
decl_stmt|;
name|int
name|has_alpha
decl_stmt|;
name|int
name|alpha
decl_stmt|,
name|bytes
decl_stmt|;
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|void
modifier|*
name|pr
decl_stmt|;
name|GimpHistogram
modifier|*
name|hist
decl_stmt|;
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|mask
operator|=
name|NULL
expr_stmt|;
name|bytes
operator|=
name|drawable_bytes
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|alpha
operator|=
name|has_alpha
condition|?
operator|(
name|bytes
operator|-
literal|1
operator|)
else|:
name|bytes
expr_stmt|;
name|hist
operator|=
name|gimp_histogram_new
argument_list|()
expr_stmt|;
name|gimp_histogram_calculate_drawable
argument_list|(
name|hist
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/* Build equalization LUT */
name|lut
operator|=
name|eq_histogram_lut
argument_list|(
name|hist
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
comment|/*  Apply the histogram  */
name|drawable_mask_bounds
argument_list|(
name|drawable
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
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable_data
argument_list|(
name|drawable
argument_list|)
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
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable_shadow
argument_list|(
name|drawable
argument_list|)
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
argument_list|)
expr_stmt|;
name|pixel_regions_process_parallel
argument_list|(
operator|(
name|p_func
operator|)
name|gimp_lut_process
argument_list|,
name|lut
argument_list|,
literal|2
argument_list|,
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|gimp_lut_free
argument_list|(
name|lut
argument_list|)
expr_stmt|;
name|gimp_histogram_free
argument_list|(
name|hist
argument_list|)
expr_stmt|;
name|drawable_merge_shadow
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|drawable_update
argument_list|(
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
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*****/
end_comment

begin_function
specifier|static
name|GimpLut
modifier|*
DECL|function|eq_histogram_lut (GimpHistogram * hist,int bytes)
name|eq_histogram_lut
parameter_list|(
name|GimpHistogram
modifier|*
name|hist
parameter_list|,
name|int
name|bytes
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|k
decl_stmt|,
name|j
decl_stmt|;
name|struct
name|hist_lut_struct
name|hlut
decl_stmt|;
name|double
name|pixels_per_value
decl_stmt|;
name|double
name|desired
decl_stmt|;
name|GimpLut
modifier|*
name|lut
decl_stmt|;
name|double
name|sum
decl_stmt|,
name|dif
decl_stmt|;
comment|/* Find partition points */
name|pixels_per_value
operator|=
name|gimp_histogram_get_count
argument_list|(
name|hist
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
operator|/
literal|256.0
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
block|{
comment|/* First and last points in partition */
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
literal|256
index|]
operator|=
literal|256
expr_stmt|;
comment|/* Find intermediate points */
name|j
operator|=
literal|0
expr_stmt|;
name|sum
operator|=
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
literal|0
argument_list|)
operator|+
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|desired
operator|=
name|i
operator|*
name|pixels_per_value
expr_stmt|;
while|while
condition|(
name|sum
operator|<=
name|desired
condition|)
block|{
name|j
operator|++
expr_stmt|;
name|sum
operator|+=
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
name|j
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
comment|/* Nearest sum */
name|dif
operator|=
name|sum
operator|-
name|gimp_histogram_get_channel
argument_list|(
name|hist
argument_list|,
name|k
argument_list|,
name|j
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|sum
operator|-
name|desired
operator|)
operator|>
operator|(
name|dif
operator|/
literal|2.0
operator|)
condition|)
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
name|i
index|]
operator|=
name|j
expr_stmt|;
else|else
name|hlut
operator|.
name|part
index|[
name|k
index|]
index|[
name|i
index|]
operator|=
name|j
operator|+
literal|1
expr_stmt|;
block|}
block|}
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|gimp_lut_setup
argument_list|(
name|lut
argument_list|,
operator|(
name|GimpLutFunc
operator|)
name|equalize_lut_func
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|&
name|hlut
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
return|return
name|lut
return|;
block|}
end_function

begin_function
specifier|static
name|float
DECL|function|equalize_lut_func (struct hist_lut_struct * hlut,int nchannels,int channel,float value)
name|equalize_lut_func
parameter_list|(
name|struct
name|hist_lut_struct
modifier|*
name|hlut
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
block|{
name|int
name|i
init|=
literal|0
decl_stmt|,
name|j
decl_stmt|;
name|j
operator|=
call|(
name|int
call|)
argument_list|(
name|value
operator|*
literal|255.0
operator|+
literal|0.5
argument_list|)
expr_stmt|;
while|while
condition|(
name|hlut
operator|->
name|part
index|[
name|channel
index|]
index|[
name|i
operator|+
literal|1
index|]
operator|<=
name|j
condition|)
name|i
operator|++
expr_stmt|;
return|return
name|i
operator|/
literal|255.0
return|;
block|}
end_function

begin_comment
comment|/*  The equalize procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|equalize_args
name|ProcArg
name|equalize_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"mask_only"
block|,
literal|"equalization option"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|equalize_proc
name|ProcRecord
name|equalize_proc
init|=
block|{
literal|"gimp_equalize"
block|,
literal|"Equalize the contents of the specified drawable"
block|,
literal|"This procedure equalizes the contents of the specified drawable.  Each intensity channel is equalizeed independently.  The equalizeed intensity is given as inten' = (255 - inten).  Indexed color drawables are not valid for this operation.  The 'mask_only' option specifies whether to adjust only the area of the image within the selection bounds, or the entire image based on the histogram of the selected area.  If there is no selection, the entire image is adjusted based on the histogram for the entire image."
block|,
literal|"Federico Mena Quintero& Spencer Kimball& Peter Mattis"
block|,
literal|"Federico Mena Quintero& Spencer Kimball& Peter Mattis"
block|,
literal|"1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|2
block|,
name|equalize_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|equalize_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|equalize_invoker (args)
name|equalize_invoker
parameter_list|(
name|args
parameter_list|)
name|Argument
modifier|*
name|args
decl_stmt|;
block|{
name|int
name|success
init|=
name|TRUE
decl_stmt|;
name|int
name|int_value
decl_stmt|;
name|int
name|mask_only
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable
operator|=
name|NULL
expr_stmt|;
comment|/*  the drawable  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|int_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
else|else
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
comment|/*  the mask only option  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|mask_only
operator|=
operator|(
name|int_value
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
comment|/*  make sure the drawable is not indexed color  */
if|if
condition|(
name|success
condition|)
name|success
operator|=
operator|!
name|drawable_indexed
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|equalize
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|mask_only
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|equalize_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

end_unit

