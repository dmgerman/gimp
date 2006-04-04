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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
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
name|GimpProcedure
name|floating_sel_remove_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_anchor_proc
specifier|static
name|GimpProcedure
name|floating_sel_anchor_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_to_layer_proc
specifier|static
name|GimpProcedure
name|floating_sel_to_layer_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_attach_proc
specifier|static
name|GimpProcedure
name|floating_sel_attach_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_rigor_proc
specifier|static
name|GimpProcedure
name|floating_sel_rigor_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|floating_sel_relax_proc
specifier|static
name|GimpProcedure
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
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * floating_sel_remove    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|floating_sel_remove_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_layer_id
argument_list|(
literal|"floating-sel"
argument_list|,
literal|"floating sel"
argument_list|,
literal|"The floating selection"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * floating_sel_anchor    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|floating_sel_anchor_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_layer_id
argument_list|(
literal|"floating-sel"
argument_list|,
literal|"floating sel"
argument_list|,
literal|"The floating selection"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * floating_sel_to_layer    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|floating_sel_to_layer_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_layer_id
argument_list|(
literal|"floating-sel"
argument_list|,
literal|"floating sel"
argument_list|,
literal|"The floating selection"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * floating_sel_attach    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|floating_sel_attach_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_layer_id
argument_list|(
literal|"layer"
argument_list|,
literal|"layer"
argument_list|,
literal|"The layer (is attached as floating selection)"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable_id
argument_list|(
literal|"drawable"
argument_list|,
literal|"drawable"
argument_list|,
literal|"The drawable (where to attach the floating selection)"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * floating_sel_rigor    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|floating_sel_rigor_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_layer_id
argument_list|(
literal|"floating-sel"
argument_list|,
literal|"floating sel"
argument_list|,
literal|"The floating selection"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"undo"
argument_list|,
literal|"undo"
argument_list|,
literal|"(TRUE or FALSE)"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * floating_sel_relax    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|floating_sel_relax_proc
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_layer_id
argument_list|(
literal|"floating-sel"
argument_list|,
literal|"floating sel"
argument_list|,
literal|"The floating selection"
argument_list|,
name|gimp
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"undo"
argument_list|,
literal|"undo"
argument_list|,
literal|"(TRUE or FALSE)"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|floating_sel_remove_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|floating_sel_remove_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|gimp_value_get_layer
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_remove_proc
specifier|static
name|GimpProcedure
name|floating_sel_remove_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-floating-sel-remove"
block|,
literal|"gimp-floating-sel-remove"
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
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
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
name|GValueArray
modifier|*
DECL|function|floating_sel_anchor_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|floating_sel_anchor_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|gimp_value_get_layer
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_anchor_proc
specifier|static
name|GimpProcedure
name|floating_sel_anchor_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-floating-sel-anchor"
block|,
literal|"gimp-floating-sel-anchor"
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
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
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
name|GValueArray
modifier|*
DECL|function|floating_sel_to_layer_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|floating_sel_to_layer_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|gimp_value_get_layer
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_to_layer_proc
specifier|static
name|GimpProcedure
name|floating_sel_to_layer_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-floating-sel-to-layer"
block|,
literal|"gimp-floating-sel-to-layer"
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
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
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
name|GValueArray
modifier|*
DECL|function|floating_sel_attach_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|floating_sel_attach_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|gimp_value_get_layer
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_value_get_drawable
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|floating_sel_attach
argument_list|(
name|layer
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_attach_proc
specifier|static
name|GimpProcedure
name|floating_sel_attach_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-floating-sel-attach"
block|,
literal|"gimp-floating-sel-attach"
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
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
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
name|GValueArray
modifier|*
DECL|function|floating_sel_rigor_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|floating_sel_rigor_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|gimp_value_get_layer
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|undo
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_rigor_proc
specifier|static
name|GimpProcedure
name|floating_sel_rigor_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-floating-sel-rigor"
block|,
literal|"gimp-floating-sel-rigor"
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
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
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
name|GValueArray
modifier|*
DECL|function|floating_sel_relax_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|floating_sel_relax_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
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
name|gimp_value_get_layer
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|undo
operator|=
name|g_value_get_boolean
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|1
index|]
argument_list|)
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
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|floating_sel_relax_proc
specifier|static
name|GimpProcedure
name|floating_sel_relax_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-floating-sel-relax"
block|,
literal|"gimp-floating-sel-relax"
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
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
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

