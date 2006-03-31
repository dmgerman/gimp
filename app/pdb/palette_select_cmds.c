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

begin_decl_stmt
DECL|variable|palettes_popup_proc
specifier|static
name|GimpProcedure
name|palettes_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palettes_close_popup_proc
specifier|static
name|GimpProcedure
name|palettes_close_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|palettes_set_popup_proc
specifier|static
name|GimpProcedure
name|palettes_set_popup_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_palette_select_procs (Gimp * gimp)
name|register_palette_select_procs
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
comment|/*    * palettes_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|palettes_popup_proc
argument_list|,
literal|3
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
literal|"palette-callback"
argument_list|,
literal|"palette callback"
argument_list|,
literal|"The callback PDB proc to call when palette selection is made"
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
literal|"Title to give the palette popup window"
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
literal|"initial-palette"
argument_list|,
literal|"initial palette"
argument_list|,
literal|"The name of the palette to set as the first selected"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * palettes_close_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|palettes_close_popup_proc
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
literal|"palette-callback"
argument_list|,
literal|"palette callback"
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
comment|/*    * palettes_set_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|palettes_set_popup_proc
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
literal|"palette-callback"
argument_list|,
literal|"palette callback"
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
literal|"palette-name"
argument_list|,
literal|"palette name"
argument_list|,
literal|"The name of the palette to set as selected"
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
name|Argument
modifier|*
DECL|function|palettes_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|palettes_popup_invoker
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
name|palette_callback
decl_stmt|;
name|gchar
modifier|*
name|popup_title
decl_stmt|;
name|gchar
modifier|*
name|initial_palette
decl_stmt|;
name|palette_callback
operator|=
operator|(
name|gchar
operator|*
operator|)
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
operator|(
name|gchar
operator|*
operator|)
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
name|initial_palette
operator|=
operator|(
name|gchar
operator|*
operator|)
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
name|palette_callback
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
name|palette_factory
operator|->
name|container
argument_list|,
name|popup_title
argument_list|,
name|palette_callback
argument_list|,
name|initial_palette
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
DECL|variable|palettes_popup_proc
specifier|static
name|GimpProcedure
name|palettes_popup_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-palettes-popup"
block|,
literal|"gimp-palettes-popup"
block|,
literal|"Invokes the Gimp palette selection."
block|,
literal|"This procedure popups the palette selection dialog."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2002"
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
name|palettes_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palettes_close_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|palettes_close_popup_invoker
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
name|palette_callback
decl_stmt|;
name|palette_callback
operator|=
operator|(
name|gchar
operator|*
operator|)
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
name|palette_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_close
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|palette_factory
operator|->
name|container
argument_list|,
name|palette_callback
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
DECL|variable|palettes_close_popup_proc
specifier|static
name|GimpProcedure
name|palettes_close_popup_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-palettes-close-popup"
block|,
literal|"gimp-palettes-close-popup"
block|,
literal|"Popdown the Gimp palette selection."
block|,
literal|"This procedure closes an opened palette selection dialog."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2002"
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
name|palettes_close_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|palettes_set_popup_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|palettes_set_popup_invoker
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
name|palette_callback
decl_stmt|;
name|gchar
modifier|*
name|palette_name
decl_stmt|;
name|palette_callback
operator|=
operator|(
name|gchar
operator|*
operator|)
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
name|palette_name
operator|=
operator|(
name|gchar
operator|*
operator|)
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
name|palette_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_set
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|palette_factory
operator|->
name|container
argument_list|,
name|palette_callback
argument_list|,
name|palette_name
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
DECL|variable|palettes_set_popup_proc
specifier|static
name|GimpProcedure
name|palettes_set_popup_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-palettes-set-popup"
block|,
literal|"gimp-palettes-set-popup"
block|,
literal|"Sets the current palette selection in a popup."
block|,
literal|"Sets the current palette selection in a popup."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2002"
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
name|palettes_set_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

