begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_decl_stmt
DECL|variable|floating_sel_remove_proc
specifier|static
name|ProcRecord
name|floating_sel_remove_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_anchor_proc
specifier|static
name|ProcRecord
name|floating_sel_anchor_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_to_layer_proc
specifier|static
name|ProcRecord
name|floating_sel_to_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_attach_proc
specifier|static
name|ProcRecord
name|floating_sel_attach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_rigor_proc
specifier|static
name|ProcRecord
name|floating_sel_rigor_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_relax_proc
specifier|static
name|ProcRecord
name|floating_sel_relax_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_floating_sel_procs (Gimp * gimp)
name|register_floating_sel_procs
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
name|floating_sel_remove_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|floating_sel_anchor_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|floating_sel_to_layer_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|floating_sel_attach_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|floating_sel_rigor_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|floating_sel_relax_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_remove_invoker (Gimp * gimp,Argument * args)
name|floating_sel_remove_invoker
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
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|floating_sel
operator|=
operator|(
name|GimpLayer
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
operator|!
name|GIMP_IS_LAYER
argument_list|(
name|floating_sel
argument_list|)
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
name|gimp_layer_is_floating_sel
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|floating_sel_remove
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|floating_sel_remove_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_remove_inargs
specifier|static
name|ProcArg
name|floating_sel_remove_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"The floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_remove_proc
specifier|static
name|ProcRecord
name|floating_sel_remove_proc
init|=
block|{
literal|"gimp_floating_sel_remove"
block|,
literal|"Remove the specified floating selection from its associated drawable."
block|,
literal|"This procedure removes the floating selection completely, without any side effects. The associated drawable is then set to active."
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
name|floating_sel_remove_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|floating_sel_remove_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_anchor_invoker (Gimp * gimp,Argument * args)
name|floating_sel_anchor_invoker
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
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|floating_sel
operator|=
operator|(
name|GimpLayer
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
operator|!
name|GIMP_IS_LAYER
argument_list|(
name|floating_sel
argument_list|)
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
name|gimp_layer_is_floating_sel
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|floating_sel_anchor
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|floating_sel_anchor_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_anchor_inargs
specifier|static
name|ProcArg
name|floating_sel_anchor_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"The floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_anchor_proc
specifier|static
name|ProcRecord
name|floating_sel_anchor_proc
init|=
block|{
literal|"gimp_floating_sel_anchor"
block|,
literal|"Anchor the specified floating selection to its associated drawable."
block|,
literal|"This procedure anchors the floating selection to its associated drawable. This is similar to merging with a merge type of ClipToBottomLayer. The floating selection layer is no longer valid after this operation."
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
name|floating_sel_anchor_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|floating_sel_anchor_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_to_layer_invoker (Gimp * gimp,Argument * args)
name|floating_sel_to_layer_invoker
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
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|floating_sel
operator|=
operator|(
name|GimpLayer
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
operator|!
name|GIMP_IS_LAYER
argument_list|(
name|floating_sel
argument_list|)
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
name|gimp_layer_is_floating_sel
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|floating_sel_to_layer
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|floating_sel_to_layer_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_to_layer_inargs
specifier|static
name|ProcArg
name|floating_sel_to_layer_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"The floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_to_layer_proc
specifier|static
name|ProcRecord
name|floating_sel_to_layer_proc
init|=
block|{
literal|"gimp_floating_sel_to_layer"
block|,
literal|"Transforms the specified floating selection into a layer."
block|,
literal|"This procedure transforms the specified floating selection into a layer with the same offsets and extents. The composited image will look precisely the same, but the floating selection layer will no longer be clipped to the extents of the drawable it was attached to. The floating selection will become the active layer. This procedure will not work if the floating selection has a different base type from the underlying image. This might be the case if the floating selection is above an auxillary channel or a layer mask."
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
name|floating_sel_to_layer_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|floating_sel_to_layer_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_attach_invoker (Gimp * gimp,Argument * args)
name|floating_sel_attach_invoker
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
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|layer
operator|=
operator|(
name|GimpLayer
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
operator|!
name|GIMP_IS_LAYER
argument_list|(
name|layer
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
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
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_DRAWABLE
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
name|success
condition|)
block|{
name|success
operator|=
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|floating_sel_attach_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_attach_inargs
specifier|static
name|ProcArg
name|floating_sel_attach_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_LAYER
block|,
literal|"layer"
block|,
literal|"The layer (is attached as floating selection)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The drawable (where to attach the floating selection)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_attach_proc
specifier|static
name|ProcRecord
name|floating_sel_attach_proc
init|=
block|{
literal|"gimp_floating_sel_attach"
block|,
literal|"Attach the specified layer as floating to the specified drawable."
block|,
literal|"This procedure attaches the layer as floating selection to the drawable."
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
name|floating_sel_attach_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|floating_sel_attach_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_rigor_invoker (Gimp * gimp,Argument * args)
name|floating_sel_rigor_invoker
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
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|gboolean
name|undo
decl_stmt|;
name|floating_sel
operator|=
operator|(
name|GimpLayer
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
operator|!
name|GIMP_IS_LAYER
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|undo
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
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|floating_sel_rigor
argument_list|(
name|floating_sel
argument_list|,
name|undo
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|floating_sel_rigor_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_rigor_inargs
specifier|static
name|ProcArg
name|floating_sel_rigor_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"The floating selection"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"undo"
block|,
literal|"TRUE or FALSE"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_rigor_proc
specifier|static
name|ProcRecord
name|floating_sel_rigor_proc
init|=
block|{
literal|"gimp_floating_sel_rigor"
block|,
literal|"Rigor the floating selection."
block|,
literal|"This procedure rigors the floating selection."
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
name|floating_sel_rigor_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|floating_sel_rigor_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_relax_invoker (Gimp * gimp,Argument * args)
name|floating_sel_relax_invoker
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
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
name|gboolean
name|undo
decl_stmt|;
name|floating_sel
operator|=
operator|(
name|GimpLayer
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
operator|!
name|GIMP_IS_LAYER
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|undo
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
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|floating_sel
argument_list|)
condition|)
name|floating_sel_relax
argument_list|(
name|floating_sel
argument_list|,
name|undo
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|floating_sel_relax_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_relax_inargs
specifier|static
name|ProcArg
name|floating_sel_relax_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"The floating selection"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"undo"
block|,
literal|"TRUE or FALSE"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_relax_proc
specifier|static
name|ProcRecord
name|floating_sel_relax_proc
init|=
block|{
literal|"gimp_floating_sel_relax"
block|,
literal|"Relax the floating selection."
block|,
literal|"This procedure relaxes the floating selection."
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
name|floating_sel_relax_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|floating_sel_relax_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

