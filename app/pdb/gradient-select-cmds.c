begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
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

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"internal-procs.h"
end_include

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gradients_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gint
name|sample_size
decl_stmt|;
name|gradient_callback
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|popup_title
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|initial_gradient
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
name|sample_size
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
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
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
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
name|progress
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
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
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gradients_close_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
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
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|gradient_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_close
argument_list|(
name|gimp
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
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
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gradients_set_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
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
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|gradient_name
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
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
name|gimp_pdb_lookup_procedure
argument_list|(
name|gimp
operator|->
name|pdb
argument_list|,
name|gradient_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_set
argument_list|(
name|gimp
argument_list|,
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
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
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_gradient_select_procs (GimpPDB * pdb)
name|register_gradient_select_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimp-gradients-popup    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_popup_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-popup"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Invokes the Gimp gradients selection."
argument_list|,
literal|"This procedure opens the gradient selection dialog."
argument_list|,
name|NULL
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1998"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
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
name|gimp_param_spec_string
argument_list|(
literal|"popup-title"
argument_list|,
literal|"popup title"
argument_list|,
literal|"Title of the gradient selection dialog"
argument_list|,
name|FALSE
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
name|gimp_param_spec_string
argument_list|(
literal|"initial-gradient"
argument_list|,
literal|"initial gradient"
argument_list|,
literal|"The name of the gradient to set as the first selected"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
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
name|g_param_spec_int
argument_list|(
literal|"sample-size"
argument_list|,
literal|"sample size"
argument_list|,
literal|"Size of the sample to return when the gradient is changed"
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
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-gradients-close-popup    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_close_popup_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-close-popup"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Close the gradient selection dialog."
argument_list|,
literal|"This procedure closes an opened gradient selection dialog."
argument_list|,
name|NULL
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1998"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"gradient-callback"
argument_list|,
literal|"gradient callback"
argument_list|,
literal|"The name of the callback registered for this pop-up"
argument_list|,
name|FALSE
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
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-gradients-set-popup    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|gradients_set_popup_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-gradients-set-popup"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Sets the current gradient in a gradient selection dialog."
argument_list|,
literal|"Sets the current gradient in a gradient selection dialog."
argument_list|,
name|NULL
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1998"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"gradient-callback"
argument_list|,
literal|"gradient callback"
argument_list|,
literal|"The name of the callback registered for this pop-up"
argument_list|,
name|FALSE
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
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

