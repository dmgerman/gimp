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
file|"gimpargument.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_decl_stmt
DECL|variable|gradients_popup_proc
specifier|static
name|GimpProcedure
name|gradients_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_close_popup_proc
specifier|static
name|GimpProcedure
name|gradients_close_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradients_set_popup_proc
specifier|static
name|GimpProcedure
name|gradients_set_popup_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_gradient_select_procs (Gimp * gimp)
name|register_gradient_select_procs
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
comment|/*    * gradients_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|gradients_popup_proc
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"gradient-callback"
argument_list|,
literal|"gradient callback"
argument_list|,
literal|"The callback PDB proc to call when gradient selection is made"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"popup-title"
argument_list|,
literal|"popup title"
argument_list|,
literal|"Title to give the gradient popup window"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"initial-gradient"
argument_list|,
literal|"initial gradient"
argument_list|,
literal|"The name of the pattern to set as the first selected"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"sample-size"
argument_list|,
literal|"sample size"
argument_list|,
literal|"Size of the sample to return when the gradient is changed: (1<= sample_size<= 10000)"
argument_list|,
literal|1
argument_list|,
literal|10000
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|GIMP_PARAM_NO_VALIDATE
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
comment|/*    * gradients_close_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|gradients_close_popup_proc
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
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"gradient-callback"
argument_list|,
literal|"gradient callback"
argument_list|,
literal|"The name of the callback registered for this popup"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
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
comment|/*    * gradients_set_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|gradients_set_popup_proc
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
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"gradient-callback"
argument_list|,
literal|"gradient callback"
argument_list|,
literal|"The name of the callback registered for this popup"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"gradient-name"
argument_list|,
literal|"gradient name"
argument_list|,
literal|"The name of the gradient to set as selected"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
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
name|GimpArgument
modifier|*
DECL|function|gradients_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|gradients_popup_invoker
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
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|gradient_callback
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|popup_title
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|initial_gradient
decl_stmt|;
name|gint32
name|sample_size
decl_stmt|;
name|gradient_callback
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|popup_title
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|initial_gradient
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|2
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|sample_size
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
literal|3
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|sample_size
operator|<
literal|1
operator|||
name|sample_size
operator|>
literal|10000
condition|)
name|sample_size
operator|=
name|GIMP_GRADIENT_DEFAULT_SAMPLE_SIZE
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|gradient_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_new
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|popup_title
argument_list|,
name|gradient_callback
argument_list|,
name|initial_gradient
argument_list|,
literal|"sample-size"
argument_list|,
name|sample_size
argument_list|,
name|NULL
argument_list|)
condition|)
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
DECL|variable|gradients_popup_proc
specifier|static
name|GimpProcedure
name|gradients_popup_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-gradients-popup"
block|,
literal|"gimp-gradients-popup"
block|,
literal|"Invokes the Gimp gradients selection."
block|,
literal|"This procedure popups the gradients selection dialog."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
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
name|gradients_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|gradients_close_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|gradients_close_popup_invoker
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
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|gradient_callback
decl_stmt|;
name|gradient_callback
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|gradient_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_close
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|gradient_callback
argument_list|)
condition|)
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
DECL|variable|gradients_close_popup_proc
specifier|static
name|GimpProcedure
name|gradients_close_popup_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-gradients-close-popup"
block|,
literal|"gimp-gradients-close-popup"
block|,
literal|"Popdown the Gimp gradient selection."
block|,
literal|"This procedure closes an opened gradient selection dialog."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
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
name|gradients_close_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|gradients_set_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpArgument * args)
name|gradients_set_popup_invoker
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
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|gradient_callback
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
name|gradient_callback
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|gradient_name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|gradient_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_set
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|gradient_callback
argument_list|,
name|gradient_name
argument_list|,
name|NULL
argument_list|)
condition|)
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
DECL|variable|gradients_set_popup_proc
specifier|static
name|GimpProcedure
name|gradients_set_popup_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-gradients-set-popup"
block|,
literal|"gimp-gradients-set-popup"
block|,
literal|"Sets the current gradient selection in a popup."
block|,
literal|"Sets the current gradient selection in a popup."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
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
name|gradients_set_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

