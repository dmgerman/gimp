begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpfloatingsel_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_undef
undef|#
directive|undef
name|__GIMP_FLOATING_SEL_PDB_H__
end_undef

begin_include
include|#
directive|include
file|"gimpfloatingsel_pdb.h"
end_include

begin_comment
comment|/**  * SECTION: gimpfloatingsel  * @title: gimpfloatingsel  * @short_description: Functions for removing or attaching floating selections.  *  * Functions for removing or attaching floating selections.  **/
end_comment

begin_comment
comment|/**  * gimp_floating_sel_remove:  * @floating_sel_ID: The floating selection.  *  * Remove the specified floating selection from its associated  * drawable.  *  * This procedure removes the floating selection completely, without  * any side effects. The associated drawable is then set to active.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_floating_sel_remove (gint32 floating_sel_ID)
name|gimp_floating_sel_remove
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-floating-sel-remove"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_floating_sel_anchor:  * @floating_sel_ID: The floating selection.  *  * Anchor the specified floating selection to its associated drawable.  *  * This procedure anchors the floating selection to its associated  * drawable. This is similar to merging with a merge type of  * ClipToBottomLayer. The floating selection layer is no longer valid  * after this operation.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_floating_sel_anchor (gint32 floating_sel_ID)
name|gimp_floating_sel_anchor
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-floating-sel-anchor"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_floating_sel_to_layer:  * @floating_sel_ID: The floating selection.  *  * Transforms the specified floating selection into a layer.  *  * This procedure transforms the specified floating selection into a  * layer with the same offsets and extents. The composited image will  * look precisely the same, but the floating selection layer will no  * longer be clipped to the extents of the drawable it was attached to.  * The floating selection will become the active layer. This procedure  * will not work if the floating selection has a different base type  * from the underlying image. This might be the case if the floating  * selection is above an auxillary channel or a layer mask.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_floating_sel_to_layer (gint32 floating_sel_ID)
name|gimp_floating_sel_to_layer
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-floating-sel-to-layer"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_floating_sel_attach:  * @layer_ID: The layer (is attached as floating selection).  * @drawable_ID: The drawable (where to attach the floating selection).  *  * Attach the specified layer as floating to the specified drawable.  *  * This procedure attaches the layer as floating selection to the  * drawable.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_floating_sel_attach (gint32 layer_ID,gint32 drawable_ID)
name|gimp_floating_sel_attach
parameter_list|(
name|gint32
name|layer_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-floating-sel-attach"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_LAYER
argument_list|,
name|layer_ID
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_floating_sel_rigor:  * @floating_sel_ID: The floating selection.  * @undo: .  *  * Deprecated: There is no replacement for this procedure.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_floating_sel_rigor (gint32 floating_sel_ID,gboolean undo)
name|gimp_floating_sel_rigor
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|,
name|gboolean
name|undo
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-floating-sel-rigor"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|undo
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_floating_sel_relax:  * @floating_sel_ID: The floating selection.  * @undo: .  *  * Deprecated: There is no replacement for this procedure.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_floating_sel_relax (gint32 floating_sel_ID,gboolean undo)
name|gimp_floating_sel_relax
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|,
name|gboolean
name|undo
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-floating-sel-relax"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|undo
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

