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
file|"core/gimpcontainer-filter.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"text/gimp-fonts.h"
end_include

begin_decl_stmt
DECL|variable|fonts_refresh_proc
specifier|static
name|GimpProcedure
name|fonts_refresh_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fonts_get_list_proc
specifier|static
name|GimpProcedure
name|fonts_get_list_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_fonts_procs (Gimp * gimp)
name|register_fonts_procs
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
comment|/*    * fonts_refresh    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|fonts_refresh_proc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * fonts_get_list    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|fonts_get_list_proc
argument_list|,
literal|1
argument_list|,
literal|2
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
literal|"filter"
argument_list|,
literal|"filter"
argument_list|,
literal|"An optional regular expression used to filter the list"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"num-fonts"
argument_list|,
literal|"num fonts"
argument_list|,
literal|"The number of available fonts"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRINGARRAY
argument_list|,
name|gimp_param_spec_string_array
argument_list|(
literal|"font-list"
argument_list|,
literal|"font list"
argument_list|,
literal|"The list of font names"
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
DECL|function|fonts_refresh_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpArgument * args)
name|fonts_refresh_invoker
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
name|GimpArgument
modifier|*
name|args
parameter_list|)
block|{
name|gimp_fonts_load
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|fonts_refresh_proc
specifier|static
name|GimpProcedure
name|fonts_refresh_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-fonts-refresh"
block|,
literal|"gimp-fonts-refresh"
block|,
literal|"Refresh current fonts. This function always succeeds."
block|,
literal|"This procedure retrieves all fonts currently in the user's font path and updates the font dialogs accordingly."
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"Sven Neumann"
block|,
literal|"2003"
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
name|fonts_refresh_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpArgument
modifier|*
DECL|function|fonts_get_list_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpArgument * args)
name|fonts_get_list_invoker
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
name|GimpArgument
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|filter
decl_stmt|;
name|gint32
name|num_fonts
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|font_list
init|=
name|NULL
decl_stmt|;
name|filter
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
name|font_list
operator|=
name|gimp_container_get_filtered_name_array
argument_list|(
name|gimp
operator|->
name|fonts
argument_list|,
name|filter
argument_list|,
operator|&
name|num_fonts
argument_list|)
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|num_fonts
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
index|[
literal|2
index|]
operator|.
name|value
argument_list|,
name|font_list
argument_list|,
name|num_fonts
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|fonts_get_list_proc
specifier|static
name|GimpProcedure
name|fonts_get_list_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-fonts-get-list"
block|,
literal|"gimp-fonts-get-list"
block|,
literal|"Retrieve the list of loaded fonts."
block|,
literal|"This procedure returns a list of the fonts that are currently available."
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"Sven Neumann"
block|,
literal|"2003"
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
name|fonts_get_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

