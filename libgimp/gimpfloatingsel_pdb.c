begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpfloatingsel_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|void
DECL|function|gimp_floating_sel_remove (gint32 floating_sel_ID)
name|gimp_floating_sel_remove
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_floating_sel_remove"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_floating_sel_anchor (gint32 floating_sel_ID)
name|gimp_floating_sel_anchor
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_floating_sel_anchor"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_floating_sel_to_layer (gint32 floating_sel_ID)
name|gimp_floating_sel_to_layer
parameter_list|(
name|gint32
name|floating_sel_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_floating_sel_to_layer"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
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
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_floating_sel_attach"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_LAYER
argument_list|,
name|layer_ID
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
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
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_floating_sel_rigor"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|undo
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
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
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_floating_sel_relax"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_LAYER
argument_list|,
name|floating_sel_ID
argument_list|,
name|PARAM_INT32
argument_list|,
name|undo
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

