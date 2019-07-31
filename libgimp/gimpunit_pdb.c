begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpunit_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_comment
comment|/**  * SECTION: gimpunit  * @title: gimpunit  * @short_description: Provides a collection of predefined units and functions for creating user-defined units.  *  * Provides a collection of predefined units and functions for creating  * user-defined units.  **/
end_comment

begin_comment
comment|/**  * _gimp_unit_get_number_of_units:  *  * Returns the number of units.  *  * This procedure returns the number of defined units.  *  * Returns: The number of units.  **/
end_comment

begin_function
name|gint
DECL|function|_gimp_unit_get_number_of_units (void)
name|_gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|num_units
init|=
name|GIMP_UNIT_END
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-number-of-units"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|num_units
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|num_units
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_number_of_built_in_units:  *  * Returns the number of built-in units.  *  * This procedure returns the number of defined units built-in to GIMP.  *  * Returns: The number of built-in units.  **/
end_comment

begin_function
name|gint
DECL|function|_gimp_unit_get_number_of_built_in_units (void)
name|_gimp_unit_get_number_of_built_in_units
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|num_units
init|=
name|GIMP_UNIT_END
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-number-of-built-in-units"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|num_units
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|num_units
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_new:  * @identifier: The new unit's identifier.  * @factor: The new unit's factor.  * @digits: The new unit's digits.  * @symbol: The new unit's symbol.  * @abbreviation: The new unit's abbreviation.  * @singular: The new unit's singular form.  * @plural: The new unit's plural form.  *  * Creates a new unit and returns it's integer ID.  *  * This procedure creates a new unit and returns it's integer ID. Note  * that the new unit will have it's deletion flag set to TRUE, so you  * will have to set it to FALSE with gimp_unit_set_deletion_flag() to  * make it persistent.  *  * Returns: The new unit's ID.  **/
end_comment

begin_function
name|GimpUnit
DECL|function|_gimp_unit_new (const gchar * identifier,gdouble factor,gint digits,const gchar * symbol,const gchar * abbreviation,const gchar * singular,const gchar * plural)
name|_gimp_unit_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gdouble
name|factor
parameter_list|,
name|gint
name|digits
parameter_list|,
specifier|const
name|gchar
modifier|*
name|symbol
parameter_list|,
specifier|const
name|gchar
modifier|*
name|abbreviation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|singular
parameter_list|,
specifier|const
name|gchar
modifier|*
name|plural
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpUnit
name|unit_id
init|=
name|GIMP_UNIT_INCH
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|identifier
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|factor
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|digits
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|symbol
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|abbreviation
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
argument_list|,
name|singular
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|6
argument_list|)
argument_list|,
name|plural
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-new"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|unit_id
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|unit_id
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_deletion_flag:  * @unit_id: The unit's integer ID.  *  * Returns the deletion flag of the unit.  *  * This procedure returns the deletion flag of the unit. If this value  * is TRUE the unit's definition will not be saved in the user's unitrc  * file on gimp exit.  *  * Returns: The unit's deletion flag.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_unit_get_deletion_flag (GimpUnit unit_id)
name|_gimp_unit_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|deletion_flag
init|=
name|FALSE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-deletion-flag"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|deletion_flag
operator|=
name|g_value_get_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|deletion_flag
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_set_deletion_flag:  * @unit_id: The unit's integer ID.  * @deletion_flag: The new deletion flag of the unit.  *  * Sets the deletion flag of a unit.  *  * This procedure sets the unit's deletion flag. If the deletion flag  * of a unit is TRUE on gimp exit, this unit's definition will not be  * saved in the user's unitrc.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|_gimp_unit_set_deletion_flag (GimpUnit unit_id,gboolean deletion_flag)
name|_gimp_unit_set_deletion_flag
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|g_value_set_boolean
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|deletion_flag
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-set-deletion-flag"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_identifier:  * @unit_id: The unit's integer ID.  *  * Returns the textual identifier of the unit.  *  * This procedure returns the textual identifier of the unit. For  * built-in units it will be the english singular form of the unit's  * name. For user-defined units this should equal to the singular form.  *  * Returns: The unit's textual identifier.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_unit_get_identifier (GimpUnit unit_id)
name|_gimp_unit_get_identifier
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|identifier
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-identifier"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|identifier
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|identifier
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_factor:  * @unit_id: The unit's integer ID.  *  * Returns the factor of the unit.  *  * This procedure returns the unit's factor which indicates how many  * units make up an inch. Note that asking for the factor of \"pixels\"  * will produce an error.  *  * Returns: The unit's factor.  **/
end_comment

begin_function
name|gdouble
DECL|function|_gimp_unit_get_factor (GimpUnit unit_id)
name|_gimp_unit_get_factor
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gdouble
name|factor
init|=
literal|0.0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-factor"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|factor
operator|=
name|g_value_get_double
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|factor
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_digits:  * @unit_id: The unit's integer ID.  *  * Returns the number of digits of the unit.  *  * This procedure returns the number of digits you should provide in  * input or output functions to get approximately the same accuracy as  * with two digits and inches. Note that asking for the digits of  * \"pixels\" will produce an error.  *  * Returns: The unit's number of digits.  **/
end_comment

begin_function
name|gint
DECL|function|_gimp_unit_get_digits (GimpUnit unit_id)
name|_gimp_unit_get_digits
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|digits
init|=
literal|0
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-digits"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|digits
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|digits
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_symbol:  * @unit_id: The unit's integer ID.  *  * Returns the symbol of the unit.  *  * This procedure returns the symbol of the unit (\"''\" for inches).  *  * Returns: The unit's symbol.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_unit_get_symbol (GimpUnit unit_id)
name|_gimp_unit_get_symbol
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|symbol
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-symbol"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|symbol
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|symbol
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_abbreviation:  * @unit_id: The unit's integer ID.  *  * Returns the abbreviation of the unit.  *  * This procedure returns the abbreviation of the unit (\"in\" for  * inches).  *  * Returns: The unit's abbreviation.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_unit_get_abbreviation (GimpUnit unit_id)
name|_gimp_unit_get_abbreviation
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|abbreviation
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-abbreviation"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|abbreviation
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|abbreviation
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_singular:  * @unit_id: The unit's integer ID.  *  * Returns the singular form of the unit.  *  * This procedure returns the singular form of the unit.  *  * Returns: The unit's singular form.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_unit_get_singular (GimpUnit unit_id)
name|_gimp_unit_get_singular
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|singular
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-singular"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|singular
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|singular
return|;
block|}
end_function

begin_comment
comment|/**  * _gimp_unit_get_plural:  * @unit_id: The unit's integer ID.  *  * Returns the plural form of the unit.  *  * This procedure returns the plural form of the unit.  *  * Returns: The unit's plural form.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|_gimp_unit_get_plural (GimpUnit unit_id)
name|_gimp_unit_get_plural
parameter_list|(
name|GimpUnit
name|unit_id
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gchar
modifier|*
name|plural
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_UNIT
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|unit_id
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-unit-get-plural"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|plural
operator|=
name|g_value_dup_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|plural
return|;
block|}
end_function

end_unit

