begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
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
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel_cmds.h"
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

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  FLOATING_SEL_REMOVE  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_remove_invoker (Argument * args)
name|floating_sel_remove_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Layer
modifier|*
name|floating_sel
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
name|floating_sel
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
block|}
comment|/*  Make sure it's a floating selection  */
if|if
condition|(
name|success
condition|)
if|if
condition|(
operator|!
name|layer_is_floating_sel
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
name|floating_sel_remove
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
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

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|floating_sel_remove_args
name|ProcArg
name|floating_sel_remove_args
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"the floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_remove_proc
name|ProcRecord
name|floating_sel_remove_proc
init|=
block|{
literal|"gimp_floating_sel_remove"
block|,
literal|"Remove the specified floating selection from its associated drawable"
block|,
literal|"This procedure removes the floating selection completely, without any side effects.  The associated drawable is then set to active."
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
name|floating_sel_remove_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|floating_sel_remove_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/*  FLOATING_SEL_ANCHOR  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_anchor_invoker (Argument * args)
name|floating_sel_anchor_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Layer
modifier|*
name|floating_sel
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
name|floating_sel
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
block|}
comment|/*  Make sure it's a floating selection  */
if|if
condition|(
name|success
condition|)
if|if
condition|(
operator|!
name|layer_is_floating_sel
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
name|floating_sel_anchor
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
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

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|floating_sel_anchor_args
name|ProcArg
name|floating_sel_anchor_args
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"the floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_anchor_proc
name|ProcRecord
name|floating_sel_anchor_proc
init|=
block|{
literal|"gimp_floating_sel_anchor"
block|,
literal|"Anchor the specified floating selection to its associated drawable"
block|,
literal|"This procedure anchors the floating selection to its associated drawable.  This is similar to merging with a merge type of ClipToBottomLayer.  The floating selection layer is no longer valid after this operation."
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
name|floating_sel_anchor_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|floating_sel_anchor_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  FLOATING_SEL_TO_LAYER  */
end_comment

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|floating_sel_to_layer_invoker (Argument * args)
name|floating_sel_to_layer_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Layer
modifier|*
name|floating_sel
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
name|floating_sel
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
block|}
comment|/*  Make sure it's a floating selection  */
if|if
condition|(
name|success
condition|)
if|if
condition|(
operator|!
name|layer_is_floating_sel
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
name|floating_sel_to_layer
argument_list|(
name|floating_sel
argument_list|)
expr_stmt|;
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

begin_comment
comment|/*  The procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|floating_sel_to_layer_args
name|ProcArg
name|floating_sel_to_layer_args
index|[]
init|=
block|{
block|{
name|PDB_LAYER
block|,
literal|"floating_sel"
block|,
literal|"the floating selection"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_to_layer_proc
name|ProcRecord
name|floating_sel_to_layer_proc
init|=
block|{
literal|"gimp_floating_sel_to_layer"
block|,
literal|"Transforms the specified floating selection into a layer"
block|,
literal|"This procedure transforms the specified floating selection into a layer with the same offsets and extents.  The composited image will look precisely the same, but the floating selection layer will no longer be clipped to the extents of the drawable it was attached to.  The floating selection will become the active layer.  This procedure will not work if the floating selection has a different base type from the underlying image.  This might be the case if the floating selection is above an auxillary channel or a layer mask."
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
name|floating_sel_to_layer_args
block|,
comment|/*  Output arguments  */
literal|0
block|,
name|NULL
block|,
comment|/*  Exec method  */
block|{
block|{
name|floating_sel_to_layer_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

end_unit

