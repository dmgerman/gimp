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
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"unitrc.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpunit.h"
end_include

begin_decl_stmt
DECL|variable|unit_get_number_of_units_proc
specifier|static
name|ProcRecord
name|unit_get_number_of_units_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_number_of_built_in_units_proc
specifier|static
name|ProcRecord
name|unit_get_number_of_built_in_units_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_new_proc
specifier|static
name|ProcRecord
name|unit_new_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_deletion_flag_proc
specifier|static
name|ProcRecord
name|unit_get_deletion_flag_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_set_deletion_flag_proc
specifier|static
name|ProcRecord
name|unit_set_deletion_flag_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_identifier_proc
specifier|static
name|ProcRecord
name|unit_get_identifier_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_factor_proc
specifier|static
name|ProcRecord
name|unit_get_factor_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_digits_proc
specifier|static
name|ProcRecord
name|unit_get_digits_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_symbol_proc
specifier|static
name|ProcRecord
name|unit_get_symbol_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_abbreviation_proc
specifier|static
name|ProcRecord
name|unit_get_abbreviation_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_singular_proc
specifier|static
name|ProcRecord
name|unit_get_singular_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_plural_proc
specifier|static
name|ProcRecord
name|unit_get_plural_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_unit_procs (Gimp * gimp)
name|register_unit_procs
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
name|unit_get_number_of_units_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_number_of_built_in_units_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_new_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_deletion_flag_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_set_deletion_flag_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_identifier_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_factor_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_digits_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_symbol_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_abbreviation_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_singular_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|unit_get_plural_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_number_of_units_invoker (Gimp * gimp,Argument * args)
name|unit_get_number_of_units_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_number_of_units_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_number_of_units_outargs
specifier|static
name|ProcArg
name|unit_get_number_of_units_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_units"
block|,
literal|"The number of units"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_number_of_units_proc
specifier|static
name|ProcRecord
name|unit_get_number_of_units_proc
init|=
block|{
literal|"gimp_unit_get_number_of_units"
block|,
literal|"Returns the number of units."
block|,
literal|"This procedure returns the number of defined units."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|unit_get_number_of_units_outargs
block|,
block|{
block|{
name|unit_get_number_of_units_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_number_of_built_in_units_invoker (Gimp * gimp,Argument * args)
name|unit_get_number_of_built_in_units_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_number_of_built_in_units_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_number_of_built_in_units_outargs
specifier|static
name|ProcArg
name|unit_get_number_of_built_in_units_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_units"
block|,
literal|"The number of built-in units"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_number_of_built_in_units_proc
specifier|static
name|ProcRecord
name|unit_get_number_of_built_in_units_proc
init|=
block|{
literal|"gimp_unit_get_number_of_built_in_units"
block|,
literal|"Returns the number of built-in units."
block|,
literal|"This procedure returns the number of defined units built-in to the GIMP."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|unit_get_number_of_built_in_units_outargs
block|,
block|{
block|{
name|unit_get_number_of_built_in_units_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_new_invoker (Gimp * gimp,Argument * args)
name|unit_new_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|gint32
name|digits
decl_stmt|;
name|gchar
modifier|*
name|symbol
decl_stmt|;
name|gchar
modifier|*
name|abbreviation
decl_stmt|;
name|gchar
modifier|*
name|singular
decl_stmt|;
name|gchar
modifier|*
name|plural
decl_stmt|;
name|GimpUnit
name|unit
init|=
literal|0
decl_stmt|;
name|identifier
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
name|identifier
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|factor
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|digits
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|symbol
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|symbol
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|abbreviation
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|abbreviation
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|singular
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|singular
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|plural
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|plural
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
name|unit
operator|=
name|_gimp_unit_new
argument_list|(
name|gimp
argument_list|,
name|identifier
argument_list|,
name|factor
argument_list|,
name|digits
argument_list|,
name|symbol
argument_list|,
name|abbreviation
argument_list|,
name|singular
argument_list|,
name|plural
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_new_proc
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
name|pdb_int
operator|=
name|unit
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_new_inargs
specifier|static
name|ProcArg
name|unit_new_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"identifier"
block|,
literal|"The new unit's identifier"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"factor"
block|,
literal|"The new unit's factor"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"digits"
block|,
literal|"The new unit's digits"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"symbol"
block|,
literal|"The new unit's symbol"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"abbreviation"
block|,
literal|"The new unit's abbreviation"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"singular"
block|,
literal|"The new unit's singular form"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"plural"
block|,
literal|"The new unit's plural form"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_new_outargs
specifier|static
name|ProcArg
name|unit_new_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The new unit's ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_new_proc
specifier|static
name|ProcRecord
name|unit_new_proc
init|=
block|{
literal|"gimp_unit_new"
block|,
literal|"Creates a new unit and returns it's integer ID."
block|,
literal|"This procedure creates a new unit and returns it's integer ID. Note that the new unit will have it's deletion flag set to TRUE, so you will have to set it to FALSE with gimp_unit_set_deletion_flag to make it persistent."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|7
block|,
name|unit_new_inargs
block|,
literal|1
block|,
name|unit_new_outargs
block|,
block|{
block|{
name|unit_new_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_deletion_flag_invoker (Gimp * gimp,Argument * args)
name|unit_get_deletion_flag_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_deletion_flag_proc
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
name|pdb_int
operator|=
name|_gimp_unit_get_deletion_flag
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_deletion_flag_inargs
specifier|static
name|ProcArg
name|unit_get_deletion_flag_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_deletion_flag_outargs
specifier|static
name|ProcArg
name|unit_get_deletion_flag_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"deletion_flag"
block|,
literal|"The unit's deletion flag"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_deletion_flag_proc
specifier|static
name|ProcRecord
name|unit_get_deletion_flag_proc
init|=
block|{
literal|"gimp_unit_get_deletion_flag"
block|,
literal|"Returns the deletion flag of the unit."
block|,
literal|"This procedure returns the deletion flag of the unit. If this value is TRUE the unit's definition will not be saved in the user's unitrc file on gimp exit."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_deletion_flag_inargs
block|,
literal|1
block|,
name|unit_get_deletion_flag_outargs
block|,
block|{
block|{
name|unit_get_deletion_flag_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_set_deletion_flag_invoker (Gimp * gimp,Argument * args)
name|unit_set_deletion_flag_invoker
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
name|GimpUnit
name|unit
decl_stmt|;
name|gboolean
name|deletion_flag
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|deletion_flag
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
name|_gimp_unit_set_deletion_flag
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|,
name|deletion_flag
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_set_deletion_flag_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_set_deletion_flag_inargs
specifier|static
name|ProcArg
name|unit_set_deletion_flag_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"deletion_flag"
block|,
literal|"The new deletion flag of the unit"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_set_deletion_flag_proc
specifier|static
name|ProcRecord
name|unit_set_deletion_flag_proc
init|=
block|{
literal|"gimp_unit_set_deletion_flag"
block|,
literal|"Sets the deletion flag of a unit."
block|,
literal|"This procedure sets the unit's deletion flag. If the deletion flag of a unit is TRUE on gimp exit, this unit's definition will not be saved in the user's unitrc."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|2
block|,
name|unit_set_deletion_flag_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|unit_set_deletion_flag_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_identifier_invoker (Gimp * gimp,Argument * args)
name|unit_get_identifier_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_identifier_proc
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
name|_gimp_unit_get_identifier
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_identifier_inargs
specifier|static
name|ProcArg
name|unit_get_identifier_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_identifier_outargs
specifier|static
name|ProcArg
name|unit_get_identifier_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"identifier"
block|,
literal|"The unit's textual identifier"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_identifier_proc
specifier|static
name|ProcRecord
name|unit_get_identifier_proc
init|=
block|{
literal|"gimp_unit_get_identifier"
block|,
literal|"Returns the textual identifier of the unit."
block|,
literal|"This procedure returns the textual identifier of the unit. For built-in units it will be the english singular form of the unit's name. For user-defined units this should equal to the singular form."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_identifier_inargs
block|,
literal|1
block|,
name|unit_get_identifier_outargs
block|,
block|{
block|{
name|unit_get_identifier_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_factor_invoker (Gimp * gimp,Argument * args)
name|unit_get_factor_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_factor_proc
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
name|pdb_float
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_factor_inargs
specifier|static
name|ProcArg
name|unit_get_factor_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_factor_outargs
specifier|static
name|ProcArg
name|unit_get_factor_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"factor"
block|,
literal|"The unit's factor"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_factor_proc
specifier|static
name|ProcRecord
name|unit_get_factor_proc
init|=
block|{
literal|"gimp_unit_get_factor"
block|,
literal|"Returns the factor of the unit."
block|,
literal|"This procedure returns the unit's factor which indicates how many units make up an inch. Note that asking for the factor of \"pixels\" will produce an error."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_factor_inargs
block|,
literal|1
block|,
name|unit_get_factor_outargs
block|,
block|{
block|{
name|unit_get_factor_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_digits_invoker (Gimp * gimp,Argument * args)
name|unit_get_digits_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_digits_proc
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
name|pdb_int
operator|=
name|_gimp_unit_get_digits
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_digits_inargs
specifier|static
name|ProcArg
name|unit_get_digits_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_digits_outargs
specifier|static
name|ProcArg
name|unit_get_digits_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"digits"
block|,
literal|"The unit's number of digits"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_digits_proc
specifier|static
name|ProcRecord
name|unit_get_digits_proc
init|=
block|{
literal|"gimp_unit_get_digits"
block|,
literal|"Returns the number of digits of the unit."
block|,
literal|"This procedure returns the number of digits you should provide in input or output functions to get approximately the same accuracy as with two digits and inches. Note that asking for the digits of \"pixels\" will produce an error."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_digits_inargs
block|,
literal|1
block|,
name|unit_get_digits_outargs
block|,
block|{
block|{
name|unit_get_digits_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_symbol_invoker (Gimp * gimp,Argument * args)
name|unit_get_symbol_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_symbol_proc
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
name|_gimp_unit_get_symbol
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_symbol_inargs
specifier|static
name|ProcArg
name|unit_get_symbol_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_symbol_outargs
specifier|static
name|ProcArg
name|unit_get_symbol_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"symbol"
block|,
literal|"The unit's symbol"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_symbol_proc
specifier|static
name|ProcRecord
name|unit_get_symbol_proc
init|=
block|{
literal|"gimp_unit_get_symbol"
block|,
literal|"Returns the symbol of the unit."
block|,
literal|"This procedure returns the symbol of the unit (\"''\" for inches)."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_symbol_inargs
block|,
literal|1
block|,
name|unit_get_symbol_outargs
block|,
block|{
block|{
name|unit_get_symbol_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_abbreviation_invoker (Gimp * gimp,Argument * args)
name|unit_get_abbreviation_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_abbreviation_proc
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
name|_gimp_unit_get_abbreviation
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_abbreviation_inargs
specifier|static
name|ProcArg
name|unit_get_abbreviation_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_abbreviation_outargs
specifier|static
name|ProcArg
name|unit_get_abbreviation_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"abbreviation"
block|,
literal|"The unit's abbreviation"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_abbreviation_proc
specifier|static
name|ProcRecord
name|unit_get_abbreviation_proc
init|=
block|{
literal|"gimp_unit_get_abbreviation"
block|,
literal|"Returns the abbreviation of the unit."
block|,
literal|"This procedure returns the abbreviation of the unit (\"in\" for inches)."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_abbreviation_inargs
block|,
literal|1
block|,
name|unit_get_abbreviation_outargs
block|,
block|{
block|{
name|unit_get_abbreviation_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_singular_invoker (Gimp * gimp,Argument * args)
name|unit_get_singular_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_singular_proc
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
name|_gimp_unit_get_singular
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_singular_inargs
specifier|static
name|ProcArg
name|unit_get_singular_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_singular_outargs
specifier|static
name|ProcArg
name|unit_get_singular_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"singular"
block|,
literal|"The unit's singular form"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_singular_proc
specifier|static
name|ProcRecord
name|unit_get_singular_proc
init|=
block|{
literal|"gimp_unit_get_singular"
block|,
literal|"Returns the singular form of the unit."
block|,
literal|"This procedure returns the singular form of the unit."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_singular_inargs
block|,
literal|1
block|,
name|unit_get_singular_outargs
block|,
block|{
block|{
name|unit_get_singular_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|unit_get_plural_invoker (Gimp * gimp,Argument * args)
name|unit_get_plural_invoker
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
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|unit
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
name|unit
operator|<
name|GIMP_UNIT_PIXEL
operator|||
name|unit
operator|>=
name|_gimp_unit_get_number_of_units
argument_list|(
name|gimp
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|unit_get_plural_proc
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
name|_gimp_unit_get_plural
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|unit_get_plural_inargs
specifier|static
name|ProcArg
name|unit_get_plural_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"unit_id"
block|,
literal|"The unit's integer ID"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_plural_outargs
specifier|static
name|ProcArg
name|unit_get_plural_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"plural"
block|,
literal|"The unit's plural form"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|unit_get_plural_proc
specifier|static
name|ProcRecord
name|unit_get_plural_proc
init|=
block|{
literal|"gimp_unit_get_plural"
block|,
literal|"Returns the plural form of the unit."
block|,
literal|"This procedure returns the plural form of the unit."
block|,
literal|"Michael Natterer"
block|,
literal|"Michael Natterer"
block|,
literal|"1999"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|unit_get_plural_inargs
block|,
literal|1
block|,
name|unit_get_plural_outargs
block|,
block|{
block|{
name|unit_get_plural_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

