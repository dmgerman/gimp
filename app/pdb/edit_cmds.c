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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpedit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_decl_stmt
DECL|variable|edit_cut_proc
specifier|static
name|ProcRecord
name|edit_cut_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_copy_proc
specifier|static
name|ProcRecord
name|edit_copy_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_paste_proc
specifier|static
name|ProcRecord
name|edit_paste_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_clear_proc
specifier|static
name|ProcRecord
name|edit_clear_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_fill_proc
specifier|static
name|ProcRecord
name|edit_fill_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_stroke_proc
specifier|static
name|ProcRecord
name|edit_stroke_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_edit_procs (Gimp * gimp)
name|register_edit_procs
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
name|edit_cut_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|edit_copy_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|edit_paste_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|edit_clear_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|edit_fill_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|edit_stroke_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_cut_invoker (Gimp * gimp,Argument * args)
name|edit_cut_invoker
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
if|if
condition|(
name|success
condition|)
block|{
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_edit_cut
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
operator|!=
name|NULL
expr_stmt|;
block|}
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

begin_decl_stmt
DECL|variable|edit_cut_inargs
specifier|static
name|ProcArg
name|edit_cut_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable to cut from"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_cut_proc
specifier|static
name|ProcRecord
name|edit_cut_proc
init|=
block|{
literal|"gimp_edit_cut"
block|,
literal|"Cut from the specified drawable."
block|,
literal|"If there is a selection in the image, then the area specified by the selection is cut from the specified drawable and placed in an internal GIMP edit buffer. It can subsequently be retrieved using the 'gimp-edit-paste' command. If there is no selection, then the specified drawable will be removed and its contents stored in the internal GIMP edit buffer. The drawable MUST belong to the specified image, or an error is returned."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|edit_cut_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|edit_cut_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_copy_invoker (Gimp * gimp,Argument * args)
name|edit_copy_invoker
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
if|if
condition|(
name|success
condition|)
block|{
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_edit_copy
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
operator|!=
name|NULL
expr_stmt|;
block|}
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

begin_decl_stmt
DECL|variable|edit_copy_inargs
specifier|static
name|ProcArg
name|edit_copy_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable to copy from"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_copy_proc
specifier|static
name|ProcRecord
name|edit_copy_proc
init|=
block|{
literal|"gimp_edit_copy"
block|,
literal|"Copy from the specified drawable."
block|,
literal|"If there is a selection in the image, then the area specified by the selection is copied from the specified drawable and placed in an internal GIMP edit buffer. It can subsequently be retrieved using the 'gimp-edit-paste' command. If there is no selection, then the specified drawable's contents will be stored in the internal GIMP edit buffer. The drawable MUST belong to the specified image, or an error is returned."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|edit_copy_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|edit_copy_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_paste_invoker (Gimp * gimp,Argument * args)
name|edit_paste_invoker
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gboolean
name|paste_into
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
name|paste_into
operator|=
name|args
index|[
literal|1
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
if|if
condition|(
name|success
condition|)
block|{
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_edit_paste
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|gimp
operator|->
name|global_buffer
argument_list|,
name|paste_into
argument_list|)
expr_stmt|;
name|success
operator|=
name|layer
operator|!=
name|NULL
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|edit_paste_proc
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
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

begin_decl_stmt
DECL|variable|edit_paste_inargs
specifier|static
name|ProcArg
name|edit_paste_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable to paste to"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"paste_into"
block|,
literal|"Clear selection, or paste behind it?"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_paste_outargs
specifier|static
name|ProcArg
name|edit_paste_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"The new floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_paste_proc
specifier|static
name|ProcRecord
name|edit_paste_proc
init|=
block|{
literal|"gimp_edit_paste"
block|,
literal|"Paste buffer to the specified drawable."
block|,
literal|"This procedure pastes a copy of the internal GIMP edit buffer to the specified drawable. The GIMP edit buffer will be empty unless a call was previously made to either 'gimp-edit-cut' or 'gimp-edit-copy'. The \"paste_into\" option specifies whether to clear the current image selection, or to paste the buffer \"behind\" the selection. This allows the selection to act as a mask for the pasted buffer. Anywhere that the selection mask is non-zero, the pasted buffer will show through. The pasted buffer will be a new layer in the image which is designated as the image floating selection. If the image has a floating selection at the time of pasting, the old floating selection will be anchored to it's drawable before the new floating selection is added. This procedure returns the new floating layer. The resulting floating selection will already be attached to the specified drawable, and a subsequent call to floating_sel_attach is not needed."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|edit_paste_inargs
block|,
literal|1
block|,
name|edit_paste_outargs
block|,
block|{
block|{
name|edit_paste_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_clear_invoker (Gimp * gimp,Argument * args)
name|edit_clear_invoker
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
if|if
condition|(
name|success
condition|)
block|{
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_edit_clear
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
block|}
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

begin_decl_stmt
DECL|variable|edit_clear_inargs
specifier|static
name|ProcArg
name|edit_clear_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
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
specifier|static
name|ProcRecord
name|edit_clear_proc
init|=
block|{
literal|"gimp_edit_clear"
block|,
literal|"Clear selected area of drawable."
block|,
literal|"This procedure clears the specified drawable. If the drawable has an alpha channel, the cleared pixels will become transparent. If the drawable does not have an alpha channel, cleared pixels will be set to the background color. This procedure only affects regions within a selection if there is a selection active."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|edit_clear_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|edit_clear_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_fill_invoker (Gimp * gimp,Argument * args)
name|edit_fill_invoker
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
name|fill_type
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
name|fill_type
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
name|fill_type
operator|<
name|FOREGROUND_FILL
operator|||
name|fill_type
operator|>
name|NO_FILL
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
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_edit_fill
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|(
name|GimpFillType
operator|)
name|fill_type
argument_list|)
expr_stmt|;
block|}
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

begin_decl_stmt
DECL|variable|edit_fill_inargs
specifier|static
name|ProcArg
name|edit_fill_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable to fill to"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"fill_type"
block|,
literal|"The type of fill: FG_IMAGE_FILL (0), BG_IMAGE_FILL (1), WHITE_IMAGE_FILL (2), TRANS_IMAGE_FILL (3), NO_IMAGE_FILL (4)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_fill_proc
specifier|static
name|ProcRecord
name|edit_fill_proc
init|=
block|{
literal|"gimp_edit_fill"
block|,
literal|"Fill selected area of drawable."
block|,
literal|"This procedure fills the specified drawable with the fill mode. If the fill mode is foreground, the current foreground color is used. If the fill mode is background, the current background color is used. Other fill modes should not be used. This procedure only affects regions within a selection if there is a selection active."
block|,
literal|"Spencer Kimball& Peter Mattis& Raphael Quinet"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-2000"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|edit_fill_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|edit_fill_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|edit_stroke_invoker (Gimp * gimp,Argument * args)
name|edit_stroke_invoker
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_item_get_by_ID
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
if|if
condition|(
name|success
condition|)
block|{
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_image_mask_stroke
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
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

begin_decl_stmt
DECL|variable|edit_stroke_inargs
specifier|static
name|ProcArg
name|edit_stroke_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable to stroke to"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_stroke_proc
specifier|static
name|ProcRecord
name|edit_stroke_proc
init|=
block|{
literal|"gimp_edit_stroke"
block|,
literal|"Stroke the current selection"
block|,
literal|"This procedure strokes the current selection, painting along the selection boundary with the active brush and foreground color. The paint is applied to the specified drawable regardless of the active selection."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|edit_stroke_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|edit_stroke_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

