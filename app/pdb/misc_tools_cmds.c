begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2000 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"base/base-enums.h"
end_include

begin_include
include|#
directive|include
file|"core/core-enums.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-blend.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-pick-color.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_decl_stmt
DECL|variable|blend_proc
specifier|static
name|ProcRecord
name|blend_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|bucket_fill_proc
specifier|static
name|ProcRecord
name|bucket_fill_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_picker_proc
specifier|static
name|ProcRecord
name|color_picker_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_misc_tools_procs (Gimp * gimp)
name|register_misc_tools_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|blend_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|bucket_fill_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|color_picker_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|blend_invoker (Gimp * gimp,Argument * args)
name|blend_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|blend_mode
decl_stmt|;
name|gint32
name|paint_mode
decl_stmt|;
name|gint32
name|gradient_type
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|offset
decl_stmt|;
name|gint32
name|repeat
decl_stmt|;
name|gboolean
name|supersample
decl_stmt|;
name|gint32
name|max_depth
decl_stmt|;
name|gdouble
name|threshold
decl_stmt|;
name|gdouble
name|x1
decl_stmt|;
name|gdouble
name|y1
decl_stmt|;
name|gdouble
name|x2
decl_stmt|;
name|gdouble
name|y2
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|blend_mode
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
if|if
condition|(
name|blend_mode
operator|<
name|GIMP_FG_BG_RGB_MODE
operator|||
name|blend_mode
operator|>
name|GIMP_CUSTOM_MODE
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|paint_mode
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|paint_mode
operator|<
name|GIMP_NORMAL_MODE
operator|||
name|paint_mode
operator|>
name|GIMP_COLOR_ERASE_MODE
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|gradient_type
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|gradient_type
operator|<
name|GIMP_LINEAR
operator|||
name|gradient_type
operator|>
name|GIMP_SPIRAL_ANTICLOCKWISE
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|opacity
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|opacity
operator|<
literal|0.0
operator|||
name|opacity
operator|>
literal|100.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|offset
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|offset
operator|<
literal|0.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|repeat
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|repeat
operator|<
name|GIMP_REPEAT_NONE
operator|||
name|repeat
operator|>
name|GIMP_REPEAT_TRIANGULAR
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|supersample
operator|=
name|args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|max_depth
operator|=
name|args
index|[
literal|8
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|supersample
operator|&&
operator|(
name|max_depth
operator|<
literal|1
operator|||
name|max_depth
operator|>
literal|9
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|threshold
operator|=
name|args
index|[
literal|9
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|supersample
operator|&&
operator|(
name|threshold
operator|<
literal|0.0
operator|||
name|threshold
operator|>
literal|4.0
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|x1
operator|=
name|args
index|[
literal|10
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|y1
operator|=
name|args
index|[
literal|11
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|x2
operator|=
name|args
index|[
literal|12
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|y2
operator|=
name|args
index|[
literal|13
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_blend
argument_list|(
name|drawable
argument_list|,
name|blend_mode
argument_list|,
name|paint_mode
argument_list|,
name|gradient_type
argument_list|,
name|opacity
operator|/
literal|100.0
argument_list|,
name|offset
argument_list|,
name|repeat
argument_list|,
name|supersample
argument_list|,
name|max_depth
argument_list|,
name|threshold
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|blend_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|blend_inargs
specifier|static
name|ProcArg
name|blend_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"blend_mode"
block|,
literal|"The type of blend: { GIMP_FG_BG_RGB (0), GIMP_FG_BG_HSV (1), GIMP_FG_TRANS (2), GIMP_CUSTOM (3) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"The paint application mode: { GIMP_NORMAL_MODE (0), GIMP_DISSOLVE_MODE (1), GIMP_BEHIND_MODE (2), GIMP_MULTIPLY_MODE (3), GIMP_SCREEN_MODE (4), GIMP_OVERLAY_MODE (5), GIMP_DIFFERENCE_MODE (6), GIMP_ADDITION_MODE (7), GIMP_SUBTRACT_MODE (8), GIMP_DARKEN_ONLY_MODE (9), GIMP_LIGHTEN_ONLY_MODE (10), GIMP_HUE_MODE (11), GIMP_SATURATION_MODE (12), GIMP_COLOR_MODE (13), GIMP_VALUE_MODE (14), GIMP_DIVIDE_MODE (15), GIMP_DODGE_MODE (16), GIMP_BURN_MODE (17), GIMP_HARDLIGHT_MODE (18), GIMP_COLOR_ERASE_MODE (19) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"gradient_type"
block|,
literal|"The type of gradient: { GIMP_LINEAR (0), GIMP_BILINEAR (1), GIMP_RADIAL (2), GIMP_SQUARE (3), GIMP_CONICAL_SYMMETRIC (4), GIMP_CONICAL_ASYMMETRIC (5), GIMP_SHAPEBURST_ANGULAR (6), GIMP_SHAPEBURST_SPHERICAL (7), GIMP_SHAPEBURST_DIMPLED (8), GIMP_SPIRAL_CLOCKWISE (9), GIMP_SPIRAL_ANTICLOCKWISE (10) }"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"The opacity of the final blend (0<= opacity<= 100)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"offset"
block|,
literal|"Offset relates to the starting and ending coordinates specified for the blend. This parameter is mode dependent (0<= offset)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"repeat"
block|,
literal|"Repeat mode: { GIMP_REPEAT_NONE (0), GIMP_REPEAT_SAWTOOTH (1), GIMP_REPEAT_TRIANGULAR (2) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"supersample"
block|,
literal|"Do adaptive supersampling (TRUE or FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"max_depth"
block|,
literal|"Maximum recursion levels for supersampling"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"threshold"
block|,
literal|"Supersampling threshold"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x1"
block|,
literal|"The x coordinate of this blend's starting point"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y1"
block|,
literal|"The y coordinate of this blend's starting point"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x2"
block|,
literal|"The x coordinate of this blend's ending point"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y2"
block|,
literal|"The y coordinate of this blend's ending point"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|blend_proc
specifier|static
name|ProcRecord
name|blend_proc
init|=
block|{
literal|"gimp_blend"
block|,
literal|"Blend between the starting and ending coordinates with the specified blend mode and gradient type."
block|,
literal|"This tool requires information on the paint application mode, the blend mode, and the gradient type. It creates the specified variety of blend using the starting and ending coordinates as defined for each gradient type."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|14
block|,
name|blend_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|blend_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|bucket_fill_invoker (Gimp * gimp,Argument * args)
name|bucket_fill_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|fill_mode
decl_stmt|;
name|gint32
name|paint_mode
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gdouble
name|threshold
decl_stmt|;
name|gboolean
name|sample_merged
decl_stmt|;
name|gdouble
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
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
name|fill_mode
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
if|if
condition|(
name|fill_mode
operator|<
name|FG_BUCKET_FILL
operator|||
name|fill_mode
operator|>
name|PATTERN_BUCKET_FILL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|paint_mode
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|paint_mode
operator|<
name|GIMP_NORMAL_MODE
operator|||
name|paint_mode
operator|>
name|GIMP_COLOR_ERASE_MODE
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|opacity
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|opacity
operator|<
literal|0.0
operator|||
name|opacity
operator|>
literal|100.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|threshold
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|threshold
operator|<
literal|0.0
operator|||
name|threshold
operator|>
literal|255.0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|sample_merged
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|x
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|y
operator|=
name|args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_drawable_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_bucket_fill
argument_list|(
name|drawable
argument_list|,
name|fill_mode
argument_list|,
name|paint_mode
argument_list|,
name|opacity
operator|/
literal|100.0
argument_list|,
name|FALSE
comment|/* don't fill transparent */
argument_list|,
name|threshold
argument_list|,
name|sample_merged
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|bucket_fill_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|bucket_fill_inargs
specifier|static
name|ProcArg
name|bucket_fill_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"fill_mode"
block|,
literal|"The type of fill: { FG_BUCKET_FILL (0), BG_BUCKET_FILL (1), PATTERN_BUCKET_FILL (2) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"The paint application mode: { GIMP_NORMAL_MODE (0), GIMP_DISSOLVE_MODE (1), GIMP_BEHIND_MODE (2), GIMP_MULTIPLY_MODE (3), GIMP_SCREEN_MODE (4), GIMP_OVERLAY_MODE (5), GIMP_DIFFERENCE_MODE (6), GIMP_ADDITION_MODE (7), GIMP_SUBTRACT_MODE (8), GIMP_DARKEN_ONLY_MODE (9), GIMP_LIGHTEN_ONLY_MODE (10), GIMP_HUE_MODE (11), GIMP_SATURATION_MODE (12), GIMP_COLOR_MODE (13), GIMP_VALUE_MODE (14), GIMP_DIVIDE_MODE (15), GIMP_DODGE_MODE (16), GIMP_BURN_MODE (17), GIMP_HARDLIGHT_MODE (18), GIMP_COLOR_ERASE_MODE (19) }"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"The opacity of the final bucket fill (0<= opacity<= 100)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"threshold"
block|,
literal|"The threshold determines how extensive the seed fill will be. It's value is specified in terms of intensity levels (0<= threshold<= 255). This parameter is only valid when there is no selection in the specified image."
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"sample_merged"
block|,
literal|"Use the composite image, not the drawable"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x"
block|,
literal|"The x coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image."
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y"
block|,
literal|"The y coordinate of this bucket fill's application. This parameter is only valid when there is no selection in the specified image."
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|bucket_fill_proc
specifier|static
name|ProcRecord
name|bucket_fill_proc
init|=
block|{
literal|"gimp_bucket_fill"
block|,
literal|"Fill the area specified either by the current selection if there is one, or by a seed fill starting at the specified coordinates."
block|,
literal|"This tool requires information on the paint application mode, and the fill mode, which can either be in the foreground color, or in the currently active pattern. If there is no selection, a seed fill is executed at the specified coordinates and extends outward in keeping with the threshold parameter. If there is a selection in the target image, the threshold, sample merged, x, and y arguments are unused. If the sample_merged parameter is non-zero, the data of the composite image will be used instead of that for the specified drawable. This is equivalent to sampling for colors after merging all visible layers. In the case of merged sampling, the x,y coordinates are relative to the image's origin; otherwise, they are relative to the drawable's origin."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|8
block|,
name|bucket_fill_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|bucket_fill_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|color_picker_invoker (Gimp * gimp,Argument * args)
name|color_picker_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gdouble
name|x
decl_stmt|;
name|gdouble
name|y
decl_stmt|;
name|gboolean
name|sample_merged
decl_stmt|;
name|gboolean
name|sample_average
decl_stmt|;
name|gdouble
name|average_radius
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimage
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
name|x
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|y
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|sample_merged
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|sample_average
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|average_radius
operator|=
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|sample_average
operator|&&
operator|(
name|average_radius
operator|<=
literal|0.0
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
operator|!
name|sample_merged
condition|)
if|if
condition|(
operator|!
name|drawable
operator|||
operator|(
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|!=
name|gimage
operator|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|gimp_image_pick_color
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|sample_merged
argument_list|,
operator|(
name|gint
operator|)
name|x
argument_list|,
operator|(
name|gint
operator|)
name|y
argument_list|,
name|sample_average
argument_list|,
name|average_radius
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|color_picker_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_color
operator|=
name|color
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|color_picker_inargs
specifier|static
name|ProcArg
name|color_picker_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The affected drawable"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x"
block|,
literal|"x coordinate of upper-left corner of rectangle"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y"
block|,
literal|"y coordinate of upper-left corner of rectangle"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"sample_merged"
block|,
literal|"Use the composite image, not the drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"sample_average"
block|,
literal|"Average the color of all the pixels in a specified radius"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"average_radius"
block|,
literal|"The radius of pixels to average"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_picker_outargs
specifier|static
name|ProcArg
name|color_picker_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"color"
block|,
literal|"The return color"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_picker_proc
specifier|static
name|ProcRecord
name|color_picker_proc
init|=
block|{
literal|"gimp_color_picker"
block|,
literal|"Determine the color at the given drawable coordinates"
block|,
literal|"This tool determines the color at the specified coordinates. The returned color is an RGB triplet even for grayscale and indexed drawables. If the coordinates lie outside of the extents of the specified drawable, then an error is returned. If the drawable has an alpha channel, the algorithm examines the alpha value of the drawable at the coordinates. If the alpha value is completely transparent (0), then an error is returned. If the sample_merged parameter is non-zero, the data of the composite image will be used instead of that for the specified drawable. This is equivalent to sampling for colors after merging all visible layers. In the case of a merged sampling, the supplied drawable is ignored."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|7
block|,
name|color_picker_inargs
block|,
literal|1
block|,
name|color_picker_outargs
block|,
block|{
block|{
name|color_picker_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

