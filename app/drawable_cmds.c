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
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"drawable_cmds.h"
end_include

begin_include
include|#
directive|include
file|"tile.h"
end_include

begin_comment
comment|/* ick. */
end_comment

begin_decl_stmt
DECL|variable|int_value
specifier|static
name|int
name|int_value
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|success
specifier|static
name|int
name|success
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  DRAWABLE_MERGE_SHADOW  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_merge_shadow_invoker (Argument * args)
name|drawable_merge_shadow_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|undo
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|(
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|undo
operator|=
operator|(
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_merge_shadow
argument_list|(
name|drawable
argument_list|,
name|undo
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_merge_shadow_proc
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
DECL|variable|drawable_merge_shadow_args
name|ProcArg
name|drawable_merge_shadow_args
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
literal|"undo"
block|,
literal|"push merge to undo stack?"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_merge_shadow_proc
name|ProcRecord
name|drawable_merge_shadow_proc
init|=
block|{
literal|"gimp_drawable_merge_shadow"
block|,
literal|"Merge the shadow buffer with the specified drawable"
block|,
literal|"This procedure combines the contents of the image's shadow buffer (for temporary processing) with the specified drawable.  The \"undo\" parameter specifies whether to add an undo step for the operation.  Requesting no undo is useful for such applications as 'auto-apply'."
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
name|drawable_merge_shadow_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_merge_shadow_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*******************/
end_comment

begin_comment
comment|/*  DRAWABLE_FILL  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_fill_invoker (Argument * args)
name|drawable_fill_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|fill_type
decl_stmt|;
name|fill_type
operator|=
name|WHITE_FILL
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
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
switch|switch
condition|(
name|int_value
condition|)
block|{
case|case
literal|0
case|:
name|fill_type
operator|=
name|FOREGROUND_FILL
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|fill_type
operator|=
name|BACKGROUND_FILL
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|fill_type
operator|=
name|WHITE_FILL
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|fill_type
operator|=
name|TRANSPARENT_FILL
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|fill_type
operator|=
name|NO_FILL
expr_stmt|;
break|break;
default|default:
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|success
condition|)
name|drawable_fill
argument_list|(
name|drawable
argument_list|,
name|fill_type
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_fill_proc
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
DECL|variable|drawable_fill_args
name|ProcArg
name|drawable_fill_args
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
literal|"fill_type"
block|,
literal|"type of fill: { BG-IMAGE-FILL (0), WHITE-IMAGE-FILL (1), TRANS-IMAGE-FILL (2) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_fill_proc
name|ProcRecord
name|drawable_fill_proc
init|=
block|{
literal|"gimp_drawable_fill"
block|,
literal|"Fill the drawable with the specified fill mode."
block|,
literal|"This procedure fills the drawable with the fill mode.  If the fill mode is foreground the current foreground color is used.  If the fill mode is background, the current background color is used.  If the fill type is white, then white is used.  Transparent fill only affects layers with an alpha channel, in which case the alpha channel is set to transparent.  If the drawable has no alpha channel, it is filled to white.  No fill leaves the drawable's contents undefined.  This procedure is unlike the bucket fill tool because it fills regardless of a selection"
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
name|drawable_fill_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_fill_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  DRAWABLE_UPDATE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_update_invoker (Argument * args)
name|drawable_update_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|w
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
name|h
operator|=
name|args
index|[
literal|4
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
name|drawable_update
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_update_proc
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
DECL|variable|drawable_update_args
name|ProcArg
name|drawable_update_args
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
literal|"x"
block|,
literal|"x coordinate of upper left corner of update region"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"y"
block|,
literal|"y coordinate of upper left corner of update region"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"w"
block|,
literal|"width of update region"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"h"
block|,
literal|"height of update region"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_update_proc
name|ProcRecord
name|drawable_update_proc
init|=
block|{
literal|"gimp_drawable_update"
block|,
literal|"Update the specified region of the drawable."
block|,
literal|"This procedure updates the specified region of the drawable.  The (x, y) coordinate pair is relative to the drawable's origin, not to the image origin.  Therefore, the entire drawable can be updated with: {x->0, y->0, w->width, h->height}."
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
literal|5
block|,
name|drawable_update_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_update_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  DRAWABLE_MASK_BOUNDS  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_mask_bounds_invoker (Argument * args)
name|drawable_mask_bounds_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|non_empty
operator|=
name|drawable_mask_bounds
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
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
name|drawable_mask_bounds_proc
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
DECL|variable|drawable_mask_bounds_args
name|ProcArg
name|drawable_mask_bounds_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_mask_bounds_out_args
name|ProcArg
name|drawable_mask_bounds_out_args
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
DECL|variable|drawable_mask_bounds_proc
name|ProcRecord
name|drawable_mask_bounds_proc
init|=
block|{
literal|"gimp_drawable_mask_bounds"
block|,
literal|"Find the bounding box of the current selection in relation to the specified drawable"
block|,
literal|"This procedure returns the whether there is a selection.  If there is one, the upper left and lower righthand corners of its bounding box are returned.  These coordinates are specified relative to the drawable's origin, and bounded by the drawable's extents."
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
name|drawable_mask_bounds_args
block|,
comment|/*  Output arguments  */
literal|5
block|,
name|drawable_mask_bounds_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_mask_bounds_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  DRAWABLE_GIMAGE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_gimage_invoker (Argument * args)
name|drawable_gimage_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|success
operator|=
operator|(
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
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
name|drawable_gimage_proc
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
name|pdb_image_to_id
argument_list|(
name|gimage
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
DECL|variable|drawable_gimage_args
name|ProcArg
name|drawable_gimage_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_gimage_out_args
name|ProcArg
name|drawable_gimage_out_args
index|[]
init|=
block|{
block|{
name|PDB_IMAGE
block|,
literal|"image"
block|,
literal|"the drawable's image"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_gimage_proc
name|ProcRecord
name|drawable_gimage_proc
init|=
block|{
literal|"gimp_drawable_image"
block|,
literal|"Returns the drawable's image"
block|,
literal|"This procedure returns the drawable's image."
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
name|drawable_gimage_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_gimage_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_gimage_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*******************/
end_comment

begin_comment
comment|/*  DRAWABLE_TYPE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_type_invoker (Argument * args)
name|drawable_type_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|type
init|=
operator|-
literal|1
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|(
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|type
operator|=
name|drawable_type
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_type_proc
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
name|type
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
DECL|variable|drawable_type_args
name|ProcArg
name|drawable_type_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_type_out_args
name|ProcArg
name|drawable_type_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"type"
block|,
literal|"the drawable's type: { RGB (0), RGBA (1), GRAY (2), GRAYA (3), INDEXED (4), INDEXEDA (5) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_type_proc
name|ProcRecord
name|drawable_type_proc
init|=
block|{
literal|"gimp_drawable_type"
block|,
literal|"Returns the drawable's type"
block|,
literal|"This procedure returns the drawable's type."
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
name|drawable_type_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_type_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_type_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/************************/
end_comment

begin_comment
comment|/*  DRAWABLE_HAS_ALPHA  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_has_alpha_invoker (Argument * args)
name|drawable_has_alpha_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|has_alpha
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|has_alpha
operator|=
name|drawable_has_alpha
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_has_alpha_proc
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
name|has_alpha
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
DECL|variable|drawable_has_alpha_args
name|ProcArg
name|drawable_has_alpha_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_has_alpha_out_args
name|ProcArg
name|drawable_has_alpha_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"has_alpha"
block|,
literal|"does the drawable have an alpha channel?"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_has_alpha_proc
name|ProcRecord
name|drawable_has_alpha_proc
init|=
block|{
literal|"gimp_drawable_has_alpha"
block|,
literal|"Returns non-zero if the drawable has an alpha channel"
block|,
literal|"This procedure returns whether the specified drawable has an alpha channel.  This can only be true for layers, and the associated type will be one of: { RGBA, GRAYA, INDEXEDA }."
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
name|drawable_has_alpha_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_has_alpha_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_has_alpha_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/******************************/
end_comment

begin_comment
comment|/*  DRAWABLE_TYPE_WITH_ALPHA  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_type_with_alpha_invoker (Argument * args)
name|drawable_type_with_alpha_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|type_with_alpha
init|=
operator|-
literal|1
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|(
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
operator|)
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|type_with_alpha
operator|=
name|drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_type_with_alpha_proc
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
name|type_with_alpha
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
DECL|variable|drawable_type_with_alpha_args
name|ProcArg
name|drawable_type_with_alpha_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_type_with_alpha_out_args
name|ProcArg
name|drawable_type_with_alpha_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"type_with_alpha"
block|,
literal|"the drawable's type with alpha: { RGBA (0), GRAYA (1), INDEXEDA (2) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_type_with_alpha_proc
name|ProcRecord
name|drawable_type_with_alpha_proc
init|=
block|{
literal|"gimp_drawable_type_with_alpha"
block|,
literal|"Returns the drawable's type with alpha"
block|,
literal|"This procedure returns the drawable's type if an alpha channel were added.  If the type is currently Gray, for instance, the returned type would be GrayA.  If the drawable already has an alpha channel, the drawable's type is simply returned."
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
name|drawable_type_with_alpha_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_type_with_alpha_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_type_with_alpha_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/********************/
end_comment

begin_comment
comment|/*  DRAWABLE_COLOR  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_color_invoker (Argument * args)
name|drawable_color_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|color
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|color
operator|=
name|drawable_color
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_color_proc
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
name|color
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
DECL|variable|drawable_color_args
name|ProcArg
name|drawable_color_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_color_out_args
name|ProcArg
name|drawable_color_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"color"
block|,
literal|"non-zero if the drawable is an RGB type"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_color_proc
name|ProcRecord
name|drawable_color_proc
init|=
block|{
literal|"gimp_drawable_color"
block|,
literal|"Returns whether the drawable is an RGB based type"
block|,
literal|"This procedure returns non-zero if the specified drawable is of type { RGB, RGBA }."
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
name|drawable_color_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_color_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_color_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/********************/
end_comment

begin_comment
comment|/*  DRAWABLE_GRAY  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_gray_invoker (Argument * args)
name|drawable_gray_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|gray
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|gray
operator|=
name|drawable_gray
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_gray_proc
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
name|gray
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
DECL|variable|drawable_gray_args
name|ProcArg
name|drawable_gray_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_gray_out_args
name|ProcArg
name|drawable_gray_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"gray"
block|,
literal|"non-zero if the drawable is a grayscale type"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_gray_proc
name|ProcRecord
name|drawable_gray_proc
init|=
block|{
literal|"gimp_drawable_gray"
block|,
literal|"Returns whether the drawable is an grayscale type"
block|,
literal|"This procedure returns non-zero if the specified drawable is of type { Gray, GrayA }."
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
name|drawable_gray_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_gray_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_gray_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  DRAWABLE_INDEXED  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_indexed_invoker (Argument * args)
name|drawable_indexed_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|indexed
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|indexed
operator|=
name|drawable_indexed
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_indexed_proc
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
name|indexed
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
DECL|variable|drawable_indexed_args
name|ProcArg
name|drawable_indexed_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_indexed_out_args
name|ProcArg
name|drawable_indexed_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"indexed"
block|,
literal|"non-zero if the drawable is a indexed type"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_indexed_proc
name|ProcRecord
name|drawable_indexed_proc
init|=
block|{
literal|"gimp_drawable_indexed"
block|,
literal|"Returns whether the drawable is an indexed type"
block|,
literal|"This procedure returns non-zero if the specified drawable is of type { Indexed, IndexedA }."
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
name|drawable_indexed_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_indexed_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_indexed_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/********************/
end_comment

begin_comment
comment|/*  DRAWABLE_BYTES  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_bytes_invoker (Argument * args)
name|drawable_bytes_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|bytes
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|bytes
operator|=
name|drawable_bytes
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_bytes_proc
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
name|bytes
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
DECL|variable|drawable_bytes_args
name|ProcArg
name|drawable_bytes_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_bytes_out_args
name|ProcArg
name|drawable_bytes_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"bytes"
block|,
literal|"bytes per pixel"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_bytes_proc
name|ProcRecord
name|drawable_bytes_proc
init|=
block|{
literal|"gimp_drawable_bytes"
block|,
literal|"Returns the bytes per pixel"
block|,
literal|"This procedure returns the number of bytes per pixel (or the number of channels) for the specified drawable."
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
name|drawable_bytes_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_bytes_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_bytes_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/********************/
end_comment

begin_comment
comment|/*  DRAWABLE_WIDTH  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_width_invoker (Argument * args)
name|drawable_width_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|width
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|width
operator|=
name|drawable_width
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_width_proc
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
name|width
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
DECL|variable|drawable_width_args
name|ProcArg
name|drawable_width_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_width_out_args
name|ProcArg
name|drawable_width_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"width"
block|,
literal|"width of drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_width_proc
name|ProcRecord
name|drawable_width_proc
init|=
block|{
literal|"gimp_drawable_width"
block|,
literal|"Returns the width of the drawable"
block|,
literal|"This procedure returns the specified drawable's width in pixels."
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
name|drawable_width_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_width_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_width_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/********************/
end_comment

begin_comment
comment|/*  DRAWABLE_HEIGHT  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_height_invoker (Argument * args)
name|drawable_height_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|height
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|height
operator|=
name|drawable_height
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_height_proc
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
name|height
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
DECL|variable|drawable_height_args
name|ProcArg
name|drawable_height_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_height_out_args
name|ProcArg
name|drawable_height_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"height"
block|,
literal|"height of drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_height_proc
name|ProcRecord
name|drawable_height_proc
init|=
block|{
literal|"gimp_drawable_height"
block|,
literal|"Returns the height of the drawable"
block|,
literal|"This procedure returns the height of the specified drawable in pixels"
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
name|drawable_height_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_height_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_height_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  DRAWABLE_OFFSETS  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_offsets_invoker (Argument * args)
name|drawable_offsets_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|offset_x
decl_stmt|;
name|int
name|offset_y
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|drawable_offsets
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_offsets_proc
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
name|offset_x
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
name|offset_y
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
DECL|variable|drawable_offsets_args
name|ProcArg
name|drawable_offsets_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_offsets_out_args
name|ProcArg
name|drawable_offsets_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"offset_x"
block|,
literal|"x offset of drawable"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"offset_y"
block|,
literal|"y offset of drawable"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_offsets_proc
name|ProcRecord
name|drawable_offsets_proc
init|=
block|{
literal|"gimp_drawable_offsets"
block|,
literal|"Returns the offsets for the drawable"
block|,
literal|"This procedure returns the specified drawable's offsets.  This only makes sense if the drawable is a layer since channels are anchored.  The offsets of a channel will be returned as 0."
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
name|drawable_offsets_args
block|,
comment|/*  Output arguments  */
literal|2
block|,
name|drawable_offsets_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_offsets_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/********************/
end_comment

begin_comment
comment|/*  DRAWABLE_LAYER  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_layer_invoker (Argument * args)
name|drawable_layer_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|layer
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|layer
operator|=
operator|(
name|drawable_layer
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_layer_proc
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
name|layer
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
DECL|variable|drawable_layer_args
name|ProcArg
name|drawable_layer_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_layer_out_args
name|ProcArg
name|drawable_layer_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"layer"
block|,
literal|"non-zero if the drawable is a layer"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_layer_proc
name|ProcRecord
name|drawable_layer_proc
init|=
block|{
literal|"gimp_drawable_layer"
block|,
literal|"Returns whether the drawable is a layer"
block|,
literal|"This procedure returns non-zero if the specified drawable is a layer."
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
name|drawable_layer_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_layer_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_layer_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  DRAWABLE_LAYER_MASK  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_layer_mask_invoker (Argument * args)
name|drawable_layer_mask_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|layer_mask
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|layer_mask
operator|=
operator|(
name|drawable_layer_mask
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_layer_mask_proc
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
name|layer_mask
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
DECL|variable|drawable_layer_mask_args
name|ProcArg
name|drawable_layer_mask_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_layer_mask_out_args
name|ProcArg
name|drawable_layer_mask_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"layer_mask"
block|,
literal|"non-zero if the drawable is a layer mask"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_layer_mask_proc
name|ProcRecord
name|drawable_layer_mask_proc
init|=
block|{
literal|"gimp_drawable_layer_mask"
block|,
literal|"Returns whether the drawable is a layer mask"
block|,
literal|"This procedure returns non-zero if the specified drawable is a layer mask."
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
name|drawable_layer_mask_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_layer_mask_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_layer_mask_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  DRAWABLE_CHANNEL  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_channel_invoker (Argument * args)
name|drawable_channel_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|int
name|channel
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|drawable_id
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
name|success
condition|)
name|channel
operator|=
operator|(
name|drawable_channel
argument_list|(
name|drawable_get_ID
argument_list|(
name|drawable_id
argument_list|)
argument_list|)
operator|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_channel_proc
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
name|channel
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
DECL|variable|drawable_channel_args
name|ProcArg
name|drawable_channel_args
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
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_channel_out_args
name|ProcArg
name|drawable_channel_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"channel"
block|,
literal|"non-zero if the drawable is a channel"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_channel_proc
name|ProcRecord
name|drawable_channel_proc
init|=
block|{
literal|"gimp_drawable_channel"
block|,
literal|"Returns whether the drawable is a channel"
block|,
literal|"This procedure returns non-zero if the specified drawable is a channel.  Even though a layer mask is technically considered a channel, this call will return 0 on a layer mask."
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
name|drawable_channel_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|drawable_channel_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_channel_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  SET/GET PIXEL     */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_set_pixel_invoker (Argument * args)
name|drawable_set_pixel_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|int
name|num_channels
decl_stmt|;
name|unsigned
name|char
modifier|*
name|pixel
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|int
name|b
decl_stmt|;
name|Tile
modifier|*
name|tile
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
operator|||
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
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
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>=
name|drawable_width
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|drawable_height
argument_list|(
name|drawable
argument_list|)
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
name|num_channels
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
name|num_channels
operator|!=
name|drawable_bytes
argument_list|(
name|drawable
argument_list|)
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
name|pixel
operator|=
operator|(
name|unsigned
name|char
operator|*
operator|)
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|x
operator|%=
name|TILE_WIDTH
expr_stmt|;
name|y
operator|%=
name|TILE_HEIGHT
expr_stmt|;
name|p
operator|=
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|y
argument_list|,
name|x
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
name|num_channels
condition|;
name|b
operator|++
control|)
operator|*
name|p
operator|++
operator|=
operator|*
name|pixel
operator|++
expr_stmt|;
name|tile_release
argument_list|(
name|tile
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_set_pixel_proc
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
DECL|variable|drawable_set_pixel_args
name|ProcArg
name|drawable_set_pixel_args
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
literal|"x coordinate"
block|,
literal|"the x coordinate"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"y coordinate"
block|,
literal|"the y coordinate"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"num_channels"
block|,
literal|"the number of channels for the pixel"
block|}
block|,
block|{
name|PDB_INT8ARRAY
block|,
literal|"pixel"
block|,
literal|"the pixel value"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_set_pixel_proc
name|ProcRecord
name|drawable_set_pixel_proc
init|=
block|{
literal|"gimp_drawable_set_pixel"
block|,
literal|"Sets the value of the pixel at the specified coordinates"
block|,
literal|"This procedure sets the pixel value at the specified coordinates.  The 'num_channels' argument must always be equal to the bytes-per-pixel value for the specified drawable."
block|,
literal|"Spencer Kimball& Peter Mattis& Josh MacDonald"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|5
block|,
name|drawable_set_pixel_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_set_pixel_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|drawable_get_pixel_invoker (Argument * args)
name|drawable_get_pixel_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|drawable_id
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
name|int
name|num_channels
decl_stmt|;
name|unsigned
name|char
modifier|*
name|pixel
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|Tile
modifier|*
name|tile
decl_stmt|;
name|int
name|b
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|num_channels
operator|=
literal|0
expr_stmt|;
name|pixel
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
name|drawable_id
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
comment|/*  Make sure the drawable exists  */
if|if
condition|(
name|success
condition|)
block|{
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|drawable_id
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
name|num_channels
operator|=
name|drawable_bytes
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
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>=
name|drawable_width
argument_list|(
name|drawable
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
operator|||
name|y
operator|>=
name|drawable_height
argument_list|(
name|drawable
argument_list|)
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
name|pixel
operator|=
operator|(
name|unsigned
name|char
operator|*
operator|)
name|g_new
argument_list|(
argument|unsigned char
argument_list|,
argument|num_channels
argument_list|)
expr_stmt|;
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|x
operator|%=
name|TILE_WIDTH
expr_stmt|;
name|y
operator|%=
name|TILE_HEIGHT
expr_stmt|;
name|p
operator|=
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|x
argument_list|,
name|y
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
name|num_channels
condition|;
name|b
operator|++
control|)
name|pixel
index|[
name|b
index|]
operator|=
name|p
index|[
name|b
index|]
expr_stmt|;
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|drawable_get_pixel_proc
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
name|num_channels
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|pixel
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
DECL|variable|drawable_get_pixel_args
name|ProcArg
name|drawable_get_pixel_args
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
literal|"x coordinate"
block|,
literal|"the x coordinate"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"y coordinate"
block|,
literal|"the y coordinate"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_get_pixel_out_args
name|ProcArg
name|drawable_get_pixel_out_args
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_channels"
block|,
literal|"the number of channels for the pixel"
block|}
block|,
block|{
name|PDB_INT8ARRAY
block|,
literal|"pixel"
block|,
literal|"the pixel value"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_get_pixel_proc
name|ProcRecord
name|drawable_get_pixel_proc
init|=
block|{
literal|"gimp_drawable_get_pixel"
block|,
literal|"Gets the value of the pixel at the specified coordinates"
block|,
literal|"This procedure gets the pixel value at the specified coordinates.  The 'num_channels' argument must always be equal to the bytes-per-pixel value for the specified drawable."
block|,
literal|"Spencer Kimball& Peter Mattis& Josh MacDonald"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|3
block|,
name|drawable_get_pixel_args
block|,
comment|/*  Output arguments  */
literal|2
block|,
name|drawable_get_pixel_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|drawable_get_pixel_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

