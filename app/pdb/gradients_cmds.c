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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gradients.h"
end_include

begin_decl_stmt
DECL|variable|gradients_get_list_proc
specifier|static
name|ProcRecord
name|gradients_get_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_get_active_proc
specifier|static
name|ProcRecord
name|gradients_get_active_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_set_active_proc
specifier|static
name|ProcRecord
name|gradients_set_active_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_sample_uniform_proc
specifier|static
name|ProcRecord
name|gradients_sample_uniform_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_sample_custom_proc
specifier|static
name|ProcRecord
name|gradients_sample_custom_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_gradients_procs (void)
name|register_gradients_procs
parameter_list|(
name|void
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
operator|&
name|gradients_get_list_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|gradients_get_active_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|gradients_set_active_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|gradients_sample_uniform_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
operator|&
name|gradients_sample_custom_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_get_list_invoker (Argument * args)
name|gradients_get_list_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gint32
name|num_gradients
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|gradients
decl_stmt|;
name|GimpGradient
modifier|*
name|grad
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|int
name|i
init|=
literal|0
decl_stmt|;
name|num_gradients
operator|=
name|gimp_container_num_children
argument_list|(
name|global_gradient_list
argument_list|)
expr_stmt|;
name|gradients
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|num_gradients
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_gradients
condition|)
block|{
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|global_gradient_list
argument_list|)
operator|->
name|list
expr_stmt|;
block|}
name|success
operator|=
operator|(
name|list
operator|!=
name|NULL
operator|)
expr_stmt|;
while|while
condition|(
name|list
condition|)
block|{
name|grad
operator|=
name|list
operator|->
name|data
expr_stmt|;
name|gradients
index|[
name|i
operator|++
index|]
operator|=
name|g_strdup
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|grad
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|list
operator|=
name|list
operator|->
name|next
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gradients_get_list_proc
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
name|num_gradients
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
name|gradients
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_get_list_outargs
specifier|static
name|ProcArg
name|gradients_get_list_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_gradients"
block|,
literal|"The number of loaded gradients"
block|}
block|,
block|{
name|PDB_STRINGARRAY
block|,
literal|"gradient_names"
block|,
literal|"The list of gradient names"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_get_list_proc
specifier|static
name|ProcRecord
name|gradients_get_list_proc
init|=
block|{
literal|"gimp_gradients_get_list"
block|,
literal|"Retrieve the list of loaded gradients."
block|,
literal|"This procedure returns a list of the gradients that are currently loaded in the gradient editor. You can later use the gimp_gradients_set_active function to set the active gradient."
block|,
literal|"Federico Mena Quintero"
block|,
literal|"Federico Mena Quintero"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|2
block|,
name|gradients_get_list_outargs
block|,
block|{
block|{
name|gradients_get_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_get_active_invoker (Argument * args)
name|gradients_get_active_invoker
parameter_list|(
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
name|success
operator|=
name|gimp_context_get_gradient
argument_list|(
name|NULL
argument_list|)
operator|!=
name|NULL
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gradients_get_active_proc
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
name|pdb_pointer
operator|=
name|g_strdup
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|NULL
argument_list|)
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_get_active_outargs
specifier|static
name|ProcArg
name|gradients_get_active_outargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the active gradient"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_get_active_proc
specifier|static
name|ProcRecord
name|gradients_get_active_proc
init|=
block|{
literal|"gimp_gradients_get_active"
block|,
literal|"Retrieve the name of the active gradient."
block|,
literal|"This procedure returns the name of the active gradient in the gradient editor."
block|,
literal|"Federico Mena Quintero"
block|,
literal|"Federico Mena Quintero"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|gradients_get_active_outargs
block|,
block|{
block|{
name|gradients_get_active_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_set_active_invoker (Argument * args)
name|gradients_set_active_invoker
parameter_list|(
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
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|name
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
name|gradient
operator|=
operator|(
name|GimpGradient
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|global_gradient_list
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|gradient
condition|)
block|{
name|gimp_context_set_gradient
argument_list|(
name|NULL
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|gradients_set_active_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_set_active_inargs
specifier|static
name|ProcArg
name|gradients_set_active_inargs
index|[]
init|=
block|{
block|{
name|PDB_STRING
block|,
literal|"name"
block|,
literal|"The name of the gradient to set"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_set_active_proc
specifier|static
name|ProcRecord
name|gradients_set_active_proc
init|=
block|{
literal|"gimp_gradients_set_active"
block|,
literal|"Sets the specified gradient as the active gradient."
block|,
literal|"This procedure lets you set the specified gradient as the active or \"current\" one. The name is simply a string which corresponds to one of the loaded gradients in the gradient editor. If no matching gradient is found, this procedure will return an error. Otherwise, the specified gradient will become active and will be used for subsequent custom gradient operations."
block|,
literal|"Federico Mena Quintero"
block|,
literal|"Federico Mena Quintero"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|gradients_set_active_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|gradients_set_active_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_sample_uniform_invoker (Argument * args)
name|gradients_sample_uniform_invoker
parameter_list|(
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
name|gint32
name|i
decl_stmt|;
name|gint32
name|array_length
init|=
literal|0
decl_stmt|;
name|gdouble
modifier|*
name|color_samples
init|=
name|NULL
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|gdouble
name|pos
decl_stmt|,
name|delta
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gdouble
modifier|*
name|pv
decl_stmt|;
name|i
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
name|i
operator|<
literal|2
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
name|pos
operator|=
literal|0.0
expr_stmt|;
name|delta
operator|=
literal|1.0
operator|/
operator|(
name|i
operator|-
literal|1
operator|)
expr_stmt|;
name|array_length
operator|=
name|i
operator|*
literal|4
expr_stmt|;
name|pv
operator|=
name|color_samples
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
name|i
operator|--
condition|)
block|{
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|pos
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|a
expr_stmt|;
name|pos
operator|+=
name|delta
expr_stmt|;
block|}
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gradients_sample_uniform_proc
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
name|array_length
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
name|color_samples
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_sample_uniform_inargs
specifier|static
name|ProcArg
name|gradients_sample_uniform_inargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_samples"
block|,
literal|"The number of samples to take"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_sample_uniform_outargs
specifier|static
name|ProcArg
name|gradients_sample_uniform_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"array_length"
block|,
literal|"Length of the color_samples array (4 * num_samples)"
block|}
block|,
block|{
name|PDB_FLOATARRAY
block|,
literal|"color_samples"
block|,
literal|"Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_sample_uniform_proc
specifier|static
name|ProcRecord
name|gradients_sample_uniform_proc
init|=
block|{
literal|"gimp_gradients_sample_uniform"
block|,
literal|"Sample the active gradient in uniform parts."
block|,
literal|"This procedure samples the active gradient from the gradient editor in the specified number of uniform parts. It returns a list of floating-point values which correspond to the RGBA values for each sample. The minimum number of samples to take is 2, in which case the returned colors will correspond to the { 0.0, 1.0 } positions in the gradient. For example, if the number of samples is 3, the procedure will return the colors at positions { 0.0, 0.5, 1.0 }."
block|,
literal|"Federico Mena Quintero"
block|,
literal|"Federico Mena Quintero"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|1
block|,
name|gradients_sample_uniform_inargs
block|,
literal|2
block|,
name|gradients_sample_uniform_outargs
block|,
block|{
block|{
name|gradients_sample_uniform_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|gradients_sample_custom_invoker (Argument * args)
name|gradients_sample_custom_invoker
parameter_list|(
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
name|gint32
name|i
decl_stmt|;
name|gdouble
modifier|*
name|pos
decl_stmt|;
name|gint32
name|array_length
init|=
literal|0
decl_stmt|;
name|gdouble
modifier|*
name|color_samples
init|=
name|NULL
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gdouble
modifier|*
name|pv
decl_stmt|;
name|i
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
name|i
operator|<=
literal|0
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|pos
operator|=
operator|(
name|gdouble
operator|*
operator|)
name|args
index|[
literal|1
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
name|array_length
operator|=
name|i
operator|*
literal|4
expr_stmt|;
name|pv
operator|=
name|color_samples
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|array_length
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
name|i
operator|--
condition|)
block|{
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
operator|*
name|pos
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|r
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|g
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|b
expr_stmt|;
operator|*
name|pv
operator|++
operator|=
name|color
operator|.
name|a
expr_stmt|;
name|pos
operator|++
expr_stmt|;
block|}
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|gradients_sample_custom_proc
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
name|array_length
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
name|color_samples
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gradients_sample_custom_inargs
specifier|static
name|ProcArg
name|gradients_sample_custom_inargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"num_samples"
block|,
literal|"The number of samples to take"
block|}
block|,
block|{
name|PDB_FLOATARRAY
block|,
literal|"positions"
block|,
literal|"The list of positions to sample along the gradient"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_sample_custom_outargs
specifier|static
name|ProcArg
name|gradients_sample_custom_outargs
index|[]
init|=
block|{
block|{
name|PDB_INT32
block|,
literal|"array_length"
block|,
literal|"Length of the color_samples array (4 * num_samples)"
block|}
block|,
block|{
name|PDB_FLOATARRAY
block|,
literal|"color_samples"
block|,
literal|"Color samples: { R1, G1, B1, A1, ..., Rn, Gn, Bn, An }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_sample_custom_proc
specifier|static
name|ProcRecord
name|gradients_sample_custom_proc
init|=
block|{
literal|"gimp_gradients_sample_custom"
block|,
literal|"Sample the active gradient in custom positions."
block|,
literal|"This procedure samples the active gradient from the gradient editor in the specified number of points. The procedure will sample the gradient in the specified positions from the list. The left endpoint of the gradient corresponds to position 0.0, and the right endpoint corresponds to 1.0. The procedure returns a list of floating-point values which correspond to the RGBA values for each sample."
block|,
literal|"Federico Mena Quintero"
block|,
literal|"Federico Mena Quintero"
block|,
literal|"1997"
block|,
name|PDB_INTERNAL
block|,
literal|2
block|,
name|gradients_sample_custom_inargs
block|,
literal|2
block|,
name|gradients_sample_custom_outargs
block|,
block|{
block|{
name|gradients_sample_custom_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

