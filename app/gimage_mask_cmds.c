begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask_cmds.h"
end_include

begin_decl_stmt
DECL|variable|int_value
specifier|static
name|int
name|int_value
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fp_value
specifier|static
name|double
name|fp_value
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|success
specifier|static
name|int
name|success
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|return_args
specifier|static
name|Argument
modifier|*
name|return_args
decl_stmt|;
end_decl_stmt

begin_comment
comment|/************************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_BOUNDS  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_bounds_invoker (Argument * args)
name|gimage_mask_bounds_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
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
name|int
name|non_empty
decl_stmt|;
name|non_empty
operator|=
name|FALSE
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|non_empty
operator|=
name|gimage_mask_bounds
argument_list|(
name|gimage
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
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_bounds_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|non_empty
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|x1
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|y1
expr_stmt|;
name|return_args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|x2
expr_stmt|;
name|return_args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|y2
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_bounds_args
name|ProcArg
name|gimage_mask_bounds_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_bounds_out_args
name|ProcArg
name|gimage_mask_bounds_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"non-empty"
block|,
literal|"true if there is a selection"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"x1"
block|,
literal|"x coordinate of upper left corner of selection bounds"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"y1"
block|,
literal|"y coordinate of upper left corner of selection bounds"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"x2"
block|,
literal|"x coordinate of lower right corner of selection bounds"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"y2"
block|,
literal|"y coordinate of lower right corner of selection bounds"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_bounds_proc
name|ProcRecord
name|gimage_mask_bounds_proc
init|=
block|{
literal|"gimp_selection_bounds"
block|,
literal|"Find the bounding box of the current selection"
block|,
literal|"This procedure returns whether there is a selection for the specified image.  If there is one, the upper left and lower right corners of the bounding box are returned.  These coordinates are relative to the image."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_bounds_args
block|,
comment|/*  Output arguments  */
literal|5
block|,
name|gimage_mask_bounds_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_bounds_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_VALUE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_value_invoker (Argument * args)
name|gimage_mask_value_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|int
name|value
decl_stmt|;
name|value
operator|=
literal|0
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
block|{
name|x
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
name|y
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
block|}
if|if
condition|(
name|success
condition|)
name|value
operator|=
name|gimage_mask_value
argument_list|(
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_value_proc
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
name|pdb_int
operator|=
name|value
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_value_args
name|ProcArg
name|gimage_mask_value_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"x"
block|,
literal|"x coordinate of value"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"y"
block|,
literal|"y coordinate of value"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_value_out_args
name|ProcArg
name|gimage_mask_value_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"value"
block|,
literal|"value of the selection: (0<= value<= 255)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_value_proc
name|ProcRecord
name|gimage_mask_value_proc
init|=
block|{
literal|"gimp_selection_value"
block|,
literal|"Find the value of the selection at the specified coordinates"
block|,
literal|"This procedure returns the value of the selection at the specified coordinates.  If the coordinates lie out of bounds, 0 is returned."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|3
block|,
name|gimage_mask_value_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|gimage_mask_value_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_value_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_IS_EMPTY  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_is_empty_invoker (Argument * args)
name|gimage_mask_is_empty_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|is_empty
decl_stmt|;
name|is_empty
operator|=
name|TRUE
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|is_empty
operator|=
name|gimage_mask_is_empty
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_is_empty_proc
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
name|pdb_int
operator|=
name|is_empty
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_is_empty_args
name|ProcArg
name|gimage_mask_is_empty_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_is_empty_out_args
name|ProcArg
name|gimage_mask_is_empty_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"is_empty"
block|,
literal|"is the selection empty?"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_is_empty_proc
name|ProcRecord
name|gimage_mask_is_empty_proc
init|=
block|{
literal|"gimp_selection_is_empty"
block|,
literal|"Determine whether the selection in empty"
block|,
literal|"This procedure returns non-zero if the selection for the specified image is not empty."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_is_empty_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|gimage_mask_is_empty_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_is_empty_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_TRANSLATE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_translate_invoker (Argument * args)
name|gimage_mask_translate_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
block|{
name|offx
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
name|offy
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
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_translate
argument_list|(
name|gimage
argument_list|,
name|offx
argument_list|,
name|offy
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_translate_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_translate_args
name|ProcArg
name|gimage_mask_translate_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"offset_x"
block|,
literal|"x offset for translation"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"offset_y"
block|,
literal|"y offset for translation"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_translate_proc
name|ProcRecord
name|gimage_mask_translate_proc
init|=
block|{
literal|"gimp_selection_translate"
block|,
literal|"Translate the selection by the specified offsets"
block|,
literal|"This procedure actually translates the selection for the specified image by the specified offsets.  Regions that are translated from beyond the bounds of the image are set to empty.  Valid regions of the selection which are translated beyond the bounds of the image because of this call are lost."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|3
block|,
name|gimage_mask_translate_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_translate_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_FLOAT  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_float_invoker (Argument * args)
name|gimage_mask_float_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
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
name|offx
decl_stmt|,
name|offy
decl_stmt|;
name|Layer
modifier|*
name|layer
decl_stmt|;
name|layer
operator|=
name|NULL
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
name|success
condition|)
block|{
name|offx
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
name|offy
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
block|}
if|if
condition|(
name|success
condition|)
name|success
operator|=
operator|(
operator|(
name|layer
operator|=
name|gimage_mask_float
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|offx
argument_list|,
name|offy
argument_list|)
operator|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_float_proc
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
name|pdb_int
operator|=
name|drawable_ID
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_float_args
name|ProcArg
name|gimage_mask_float_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable from which to float selection"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"offset_x"
block|,
literal|"x offset for translation"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"offset_y"
block|,
literal|"y offset for translation"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_float_out_args
name|ProcArg
name|gimage_mask_float_out_args
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"layer"
block|,
literal|"the floated layer"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_float_proc
name|ProcRecord
name|gimage_mask_float_proc
init|=
block|{
literal|"gimp_selection_float"
block|,
literal|"Float the selection from the specified drawable with initial offsets as specified"
block|,
literal|"This procedure determines the region of the specified drawable that lies beneath the current selection.  The region is then cut from the drawable and the resulting data is made into a new layer which is instantiated as a floating selection.  The offsets allow initial positioning of the new floating selection."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|3
block|,
name|gimage_mask_float_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|gimage_mask_float_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_float_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_CLEAR  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_clear_invoker (Argument * args)
name|gimage_mask_clear_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_clear
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_clear_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_clear_args
name|ProcArg
name|gimage_mask_clear_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_clear_proc
name|ProcRecord
name|gimage_mask_clear_proc
init|=
block|{
literal|"gimp_selection_clear"
block|,
literal|"Set the selection to none, clearing all previous content"
block|,
literal|"This procedure sets the selection mask to empty, assigning the value 0 to every pixel in the selection channel."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_clear_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_clear_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_INVERT  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_invert_invoker (Argument * args)
name|gimage_mask_invert_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_invert
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_invert_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_invert_args
name|ProcArg
name|gimage_mask_invert_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_invert_proc
name|ProcRecord
name|gimage_mask_invert_proc
init|=
block|{
literal|"gimp_selection_invert"
block|,
literal|"Invert the selection mask"
block|,
literal|"This procedure inverts the selection mask.  For every pixel in the selection channel, its new value is calculated as (255 - old_value)."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_invert_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_invert_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_SHARPEN  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_sharpen_invoker (Argument * args)
name|gimage_mask_sharpen_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_sharpen
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_sharpen_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_sharpen_args
name|ProcArg
name|gimage_mask_sharpen_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_sharpen_proc
name|ProcRecord
name|gimage_mask_sharpen_proc
init|=
block|{
literal|"gimp_selection_sharpen"
block|,
literal|"Sharpen the selection mask"
block|,
literal|"This procedure sharpens the selection mask.  For every pixel in the selection channel, if the value is> 0, the new pixel is assigned a value of 255.  This removes any \"anti-aliasing\" that might exist in the selection mask's boundary."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_sharpen_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_sharpen_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_ALL  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_all_invoker (Argument * args)
name|gimage_mask_all_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_all
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_all_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_all_args
name|ProcArg
name|gimage_mask_all_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_all_proc
name|ProcRecord
name|gimage_mask_all_proc
init|=
block|{
literal|"gimp_selection_all"
block|,
literal|"Select all of the image"
block|,
literal|"This procedure sets the selection mask to completely encompass the image.  Every pixel in the selection channel is set to 255."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_all_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_all_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_NONE */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_none_invoker (Argument * args)
name|gimage_mask_none_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_none
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_none_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_none_args
name|ProcArg
name|gimage_mask_none_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_none_proc
name|ProcRecord
name|gimage_mask_none_proc
init|=
block|{
literal|"gimp_selection_none"
block|,
literal|"Deselect the entire image"
block|,
literal|"This procedure deselects the entire image.  Every pixel in the selection channel is set to 0."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_none_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_none_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/************************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_FEATHER */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_feather_invoker (Argument * args)
name|gimage_mask_feather_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|double
name|radius
decl_stmt|;
name|radius
operator|=
literal|0.0
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
block|{
name|fp_value
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
if|if
condition|(
name|fp_value
operator|>
literal|0
condition|)
name|radius
operator|=
name|fp_value
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_feather
argument_list|(
name|gimage
argument_list|,
name|radius
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_feather_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_feather_args
name|ProcArg
name|gimage_mask_feather_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|,
block|{
name|PDB_FLOAT
block|,
literal|"radius"
block|,
literal|"radius of feather (in pixels)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_feather_proc
name|ProcRecord
name|gimage_mask_feather_proc
init|=
block|{
literal|"gimp_selection_feather"
block|,
literal|"Feather the image's selection"
block|,
literal|"This procedure feathers the selection.  Feathering is implemented using a gaussian blur."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|2
block|,
name|gimage_mask_feather_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_feather_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_BORDER */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_border_invoker (Argument * args)
name|gimage_mask_border_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|radius
decl_stmt|;
name|radius
operator|=
literal|0
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
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
if|if
condition|(
name|int_value
operator|>
literal|0
condition|)
name|radius
operator|=
name|int_value
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_border
argument_list|(
name|gimage
argument_list|,
name|radius
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_border_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_border_args
name|ProcArg
name|gimage_mask_border_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"radius"
block|,
literal|"radius of border (pixels)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_border_proc
name|ProcRecord
name|gimage_mask_border_proc
init|=
block|{
literal|"gimp_selection_border"
block|,
literal|"Border the image's selection"
block|,
literal|"This procedure borders the selection.  Bordering creates a new selection which is defined along the boundary of the previous selection at every point within the specified radius."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|2
block|,
name|gimage_mask_border_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_border_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_GROW */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_grow_invoker (Argument * args)
name|gimage_mask_grow_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|steps
init|=
literal|0
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
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
if|if
condition|(
name|int_value
operator|>
literal|0
condition|)
name|steps
operator|=
name|int_value
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_grow
argument_list|(
name|gimage
argument_list|,
name|steps
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_grow_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_grow_args
name|ProcArg
name|gimage_mask_grow_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"steps"
block|,
literal|"steps of grow (pixels)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_grow_proc
name|ProcRecord
name|gimage_mask_grow_proc
init|=
block|{
literal|"gimp_selection_grow"
block|,
literal|"Grow the image's selection"
block|,
literal|"This procedure grows the selection.  Growing involves expanding the boundary in all directions by the specified pixel amount."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|2
block|,
name|gimage_mask_grow_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_grow_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_SHRINK */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_shrink_invoker (Argument * args)
name|gimage_mask_shrink_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|int
name|steps
init|=
literal|0
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
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
if|if
condition|(
name|int_value
operator|<
literal|0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
else|else
name|steps
operator|=
name|int_value
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_shrink
argument_list|(
name|gimage
argument_list|,
name|steps
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_shrink_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_shrink_args
name|ProcArg
name|gimage_mask_shrink_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"radius"
block|,
literal|"radius of shrink (pixels)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_shrink_proc
name|ProcRecord
name|gimage_mask_shrink_proc
init|=
block|{
literal|"gimp_selection_shrink"
block|,
literal|"Shrink the image's selection"
block|,
literal|"This procedure shrinks the selection.  Shrinking invovles trimming the existing selection boundary on all sides by the specified number of pixels."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|2
block|,
name|gimage_mask_shrink_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_shrink_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/****************************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_LAYER_ALPHA */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_layer_alpha_invoker (Argument * args)
name|gimage_mask_layer_alpha_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|Layer
modifier|*
name|layer
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|layer
operator|=
name|layer_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
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
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_layer_alpha
argument_list|(
name|gimage
argument_list|,
name|layer
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_layer_alpha_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_layer_alpha_args
name|ProcArg
name|gimage_mask_layer_alpha_args
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"layer"
block|,
literal|"layer with alpha"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_layer_alpha_proc
name|ProcRecord
name|gimage_mask_layer_alpha_proc
init|=
block|{
literal|"gimp_selection_layer_alpha"
block|,
literal|"Transfer the specified layer's alpha channel to the selection mask"
block|,
literal|"This procedure requires a layer with an alpha channel.  The alpha channel information is used to create a selection mask such that for any pixel in the image defined in the specified layer, that layer pixel's alpha value is transferred to the selection mask.  If the layer is undefined at a particular image pixel, the associated selection mask value is set to 0."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_layer_alpha_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_layer_alpha_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_LOAD  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_load_invoker (Argument * args)
name|gimage_mask_load_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|Channel
modifier|*
name|channel
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|channel
operator|=
name|channel_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
else|else
block|{
name|success
operator|=
operator|(
name|drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
operator|==
name|gimage
operator|->
name|width
operator|&&
name|drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
operator|==
name|gimage
operator|->
name|height
operator|)
expr_stmt|;
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|success
condition|)
name|gimage_mask_load
argument_list|(
name|gimage
argument_list|,
name|channel
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_load_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_load_args
name|ProcArg
name|gimage_mask_load_args
index|[]
init|=
block|{
block|{
name|PDB_CHANNEL
block|,
literal|"channel"
block|,
literal|"the channel"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_load_proc
name|ProcRecord
name|gimage_mask_load_proc
init|=
block|{
literal|"gimp_selection_load"
block|,
literal|"Transfer the specified channel to the selection mask"
block|,
literal|"This procedure loads the specified channel into the selection mask.  This essentially involves a copy of the channel's content in to the selection mask.  Therefore, the channel must have the same width and height of the image, or an error is returned."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_load_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_load_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  GIMAGE_MASK_SAVE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gimage_mask_save_invoker (Argument * args)
name|gimage_mask_save_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|Channel
modifier|*
name|channel
decl_stmt|;
name|channel
operator|=
name|NULL
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
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
if|if
condition|(
operator|(
name|gimage
operator|=
name|gimage_get_ID
argument_list|(
name|int_value
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
name|success
operator|=
operator|(
operator|(
name|channel
operator|=
name|gimage_mask_save
argument_list|(
name|gimage
argument_list|)
operator|)
operator|!=
name|NULL
operator|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gimage_mask_save_proc
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
name|pdb_int
operator|=
name|drawable_ID
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|gimage_mask_save_args
name|ProcArg
name|gimage_mask_save_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_save_out_args
name|ProcArg
name|gimage_mask_save_out_args
index|[]
init|=
block|{
block|{
name|PDB_CHANNEL
block|,
literal|"channel"
block|,
literal|"the new channel"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimage_mask_save_proc
name|ProcRecord
name|gimage_mask_save_proc
init|=
block|{
literal|"gimp_selection_save"
block|,
literal|"Copy the selection mask to a new channel"
block|,
literal|"This procedure copies the selection mask and stores the content in a new channel.  The new channel is automatically inserted into the image's list of channels."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|1
block|,
name|gimage_mask_save_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|gimage_mask_save_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|gimage_mask_save_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

