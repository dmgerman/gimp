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
file|<string.h>
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
file|"global_edit.h"
end_include

begin_include
include|#
directive|include
file|"edit_cmds.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

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

begin_decl_stmt
DECL|variable|return_args
specifier|static
name|Argument
modifier|*
name|return_args
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|TileManager
modifier|*
name|global_buf
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************/
end_comment

begin_comment
comment|/*  EDIT_CUT  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_cut_invoker (Argument * args)
name|edit_cut_invoker
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
name|drawable
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
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  create the new image  */
if|if
condition|(
name|success
condition|)
name|success
operator|=
operator|(
name|edit_cut
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|edit_cut_proc
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
DECL|variable|edit_cut_args
name|ProcArg
name|edit_cut_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable to cut from"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_cut_proc
name|ProcRecord
name|edit_cut_proc
init|=
block|{
literal|"gimp_edit_cut"
block|,
literal|"Cut from the specified drawable"
block|,
literal|"If there is a selection in the image, then the area specified by the selection is cut from the specified drawable and placed in an internal GIMP edit buffer.  It can subsequently be retrieved using the 'gimp-edit-paste' command.  If there is no selection, then the specified drawable will be removed and its contents stored in the internal GIMP edit buffer.  The drawable MUST belong to the specified image, or an error is returned."
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
name|edit_cut_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|edit_cut_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***************/
end_comment

begin_comment
comment|/*  EDIT_COPY  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_copy_invoker (Argument * args)
name|edit_copy_invoker
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
name|drawable
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
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  create the new image  */
if|if
condition|(
name|success
condition|)
name|success
operator|=
operator|(
name|edit_copy
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|edit_copy_proc
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
DECL|variable|edit_copy_args
name|ProcArg
name|edit_copy_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable to copy from"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_copy_proc
name|ProcRecord
name|edit_copy_proc
init|=
block|{
literal|"gimp_edit_copy"
block|,
literal|"Copy from the specified drawable"
block|,
literal|"If there is a selection in the image, then the area specified by the selection is copied from the specified drawable and placed in an internal GIMP edit buffer.  It can subsequently be retrieved using the 'gimp-edit-paste' command.  If there is no selection, then the specified drawable's contents will be stored in the internal GIMP edit buffer.  The drawable MUST belong to the specified image, or an error is returned."
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
name|edit_copy_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|edit_copy_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/****************/
end_comment

begin_comment
comment|/*  EDIT_PASTE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_paste_invoker (Argument * args)
name|edit_paste_invoker
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
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|int
name|paste_into
decl_stmt|;
name|drawable
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
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
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
name|paste_into
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
comment|/*  create the new image  */
if|if
condition|(
name|success
condition|)
name|layer
operator|=
name|edit_paste
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|global_buf
argument_list|,
name|paste_into
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|edit_paste_proc
argument_list|,
operator|!
operator|!
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
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
DECL|variable|edit_paste_args
name|ProcArg
name|edit_paste_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable to paste from"
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"paste_into"
block|,
literal|"clear selection, or paste behind it?"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_paste_out_args
name|ProcArg
name|edit_paste_out_args
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"the new floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_paste_proc
name|ProcRecord
name|edit_paste_proc
init|=
block|{
literal|"gimp_edit_paste"
block|,
literal|"Paste buffer to the specified drawable"
block|,
literal|"This procedure pastes a copy of the internal GIMP edit buffer to the specified drawable.  The GIMP edit buffer will be empty unless a call was previously made to either 'gimp-edit-cut' or 'gimp-edit-copy'.  The \"paste_into\" option specifies whether to clear the current image selection, or to paste the buffer \"behind\" the selection.  This allows the selection to act as a mask for the pasted buffer.  Anywhere that the selection mask is non-zero, the pasted buffer will show through.  The pasted buffer will be a new layer in the image which is designated as the image floating selection.  If the image has a floating selection at the time of pasting, the old floating selection will be anchored to it's drawable before the new floating selection is added.  This procedure returns the new floating layer.  The resulting floating selection will already be attached to the specified drawable, and a subsequent call to floating_sel_attach is not needed."
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
name|edit_paste_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|edit_paste_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|edit_paste_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/****************/
end_comment

begin_comment
comment|/*  EDIT_CLEAR  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_clear_invoker (Argument * args)
name|edit_clear_invoker
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
name|drawable
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
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  create the new image  */
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|edit_clear
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|edit_clear_proc
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
DECL|variable|edit_clear_args
name|ProcArg
name|edit_clear_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable to clear from"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_clear_proc
name|ProcRecord
name|edit_clear_proc
init|=
block|{
literal|"gimp_edit_clear"
block|,
literal|"Clear selected area of drawable"
block|,
literal|"This procedure clears the specified drawable.  If the drawable has an alpha channel, the cleared pixels will become transparent.  If the drawable does not have an alpha channel, cleared pixels will be set to the background color.  This procedure only affects regions within a selection if there is a selection active."
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
name|edit_clear_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|edit_clear_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***************/
end_comment

begin_comment
comment|/*  EDIT_FILL  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_fill_invoker (Argument * args)
name|edit_fill_invoker
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
name|drawable
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
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  create the new image  */
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|edit_fill
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|edit_fill_proc
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
DECL|variable|edit_fill_args
name|ProcArg
name|edit_fill_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable to fill from"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_fill_proc
name|ProcRecord
name|edit_fill_proc
init|=
block|{
literal|"gimp_edit_fill"
block|,
literal|"Fill selected area of drawable"
block|,
literal|"This procedure fills the specified drawable with the background color.  This procedure only affects regions within a selection if there is a selection active."
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
name|edit_fill_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|edit_fill_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*****************/
end_comment

begin_comment
comment|/*  EDIT_STROKE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_stroke_invoker (Argument * args)
name|edit_stroke_invoker
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
name|drawable
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
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  create the new image  */
if|if
condition|(
name|success
condition|)
name|success
operator|=
name|gimage_mask_stroke
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|edit_stroke_proc
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
DECL|variable|edit_stroke_args
name|ProcArg
name|edit_stroke_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"the drawable to stroke to"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_stroke_proc
name|ProcRecord
name|edit_stroke_proc
init|=
block|{
literal|"gimp_edit_stroke"
block|,
literal|"Stroke the current selection"
block|,
literal|"This procedure strokes the current selection, painting along the selection boundary with the active brush and foreground color.  The paint is applied to the specified drawable regardless of the active selection."
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
name|edit_stroke_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|edit_stroke_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

