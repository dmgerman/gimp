begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpunit.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpbase-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpunit.h"
end_include

begin_comment
comment|/**  * gimp_unit_get_number_of_units:  *  * Returns the number of units which are known to the #GimpUnit system.  *  * Returns: The number of defined units.  */
end_comment

begin_function
name|gint
DECL|function|gimp_unit_get_number_of_units (void)
name|gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_number_of_units
operator|!=
name|NULL
argument_list|,
name|GIMP_UNIT_END
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_number_of_units
argument_list|()
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_number_of_built_in_units:  *  * Returns the number of #GimpUnit's which are hardcoded in the unit system  * (UNIT_INCH, UNIT_MM, UNIT_POINT, UNIT_PICA and the two "pseudo unit"  *  UNIT_PIXEL).  *  * Returns: The number of built-in units.  */
end_comment

begin_function
name|gint
DECL|function|gimp_unit_get_number_of_built_in_units (void)
name|gimp_unit_get_number_of_built_in_units
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_number_of_built_in_units
operator|!=
name|NULL
argument_list|,
name|GIMP_UNIT_END
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_number_of_built_in_units
argument_list|()
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_new:  * @identifier: The unit's identifier string.  * @factor: The unit's factor (how many units are in one inch).  * @digits: The unit's suggested number of digits (see gimp_unit_get_digits()).  * @symbol: The symbol of the unit (e.g. "''" for inch).  * @abbreviation: The abbreviation of the unit.  * @singular: The singular form of the unit.  * @plural: The plural form of the unit.  *  * Returns the integer ID of the new #GimpUnit.  *  * Note that a new unit is always created with it's deletion flag  * set to %TRUE. You will have to set it to %FALSE with  * gimp_unit_set_deletion_flag() to make the unit definition persistent.  *  * Returns: The ID of the new unit.  */
end_comment

begin_function
name|GimpUnit
DECL|function|gimp_unit_new (gchar * identifier,gdouble factor,gint digits,gchar * symbol,gchar * abbreviation,gchar * singular,gchar * plural)
name|gimp_unit_new
parameter_list|(
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
name|gchar
modifier|*
name|symbol
parameter_list|,
name|gchar
modifier|*
name|abbreviation
parameter_list|,
name|gchar
modifier|*
name|singular
parameter_list|,
name|gchar
modifier|*
name|plural
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_new
operator|!=
name|NULL
argument_list|,
name|GIMP_UNIT_INCH
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_new
argument_list|(
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
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_deletion_flag:  * @unit: The unit you want to know the @deletion_flag of.  *  * Returns: The unit's @deletion_flag.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_unit_get_deletion_flag (GimpUnit unit)
name|gimp_unit_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_deletion_flag
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_deletion_flag
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_set_deletion_flag:  * @unit: The unit you want to set the @deletion_flag for.  * @deletion_flag: The new deletion_flag.  *  * Sets a #GimpUnit's @deletion_flag. If the @deletion_flag of a unit is  * %TRUE when GIMP exits, this unit will not be saved in the uses's  * "unitrc" file.  *  * Trying to change the @deletion_flag of a built-in unit will be silently  * ignored.  */
end_comment

begin_function
name|void
DECL|function|gimp_unit_set_deletion_flag (GimpUnit unit,gboolean deletion_flag)
name|gimp_unit_set_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_set_deletion_flag
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|_gimp_unit_vtable
operator|.
name|unit_set_deletion_flag
argument_list|(
name|unit
argument_list|,
name|deletion_flag
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_factor:  * @unit: The unit you want to know the factor of.  *  * A #GimpUnit's @factor is defined to be:  *  * distance_in_units == (@factor * distance_in_inches)  *  * Returns 0 for @unit == GIMP_UNIT_PIXEL.  *  * Returns: The unit's factor.  */
end_comment

begin_function
name|gdouble
DECL|function|gimp_unit_get_factor (GimpUnit unit)
name|gimp_unit_get_factor
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_factor
operator|!=
name|NULL
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_factor
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_digits:  * @unit: The unit you want to know the digits.  *  * Returns the number of digits an entry field should provide to get  * approximately the same accuracy as an inch input field with two digits.  *  * Returns 0 for @unit == GIMP_UNIT_PIXEL.  *  * Returns: The suggested number of digits.  */
end_comment

begin_function
name|gint
DECL|function|gimp_unit_get_digits (GimpUnit unit)
name|gimp_unit_get_digits
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_digits
operator|!=
name|NULL
argument_list|,
literal|2
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_digits
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_identifier:  * @unit: The unit you want to know the identifier of.  *  * This is an unstranslated string and must not be changed or freed.  *  * Returns: The unit's identifier.  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_unit_get_identifier (GimpUnit unit)
name|gimp_unit_get_identifier
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_identifier
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_identifier
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_symbol:  * @unit: The unit you want to know the symbol of.  *  * This is e.g. "''" for UNIT_INCH.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's symbol.  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_unit_get_symbol (GimpUnit unit)
name|gimp_unit_get_symbol
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_symbol
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_symbol
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_abbreviation:  * @unit: The unit you want to know the abbreviation of.  *  * For built-in units, this function returns the translated abbreviation  * of the unit.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's abbreviation.  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_unit_get_abbreviation (GimpUnit unit)
name|gimp_unit_get_abbreviation
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_abbreviation
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_abbreviation
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_singular:  * @unit: The unit you want to know the singular form of.  *  * For built-in units, this function returns the translated singular form  * of the unit's name.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's singular form.  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_unit_get_singular (GimpUnit unit)
name|gimp_unit_get_singular
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_singular
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_singular
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_plural:  * @unit: The unit you want to know the plural form of.  *  * For built-in units, this function returns the translated plural form  * of the unit's name.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's plural form.  *  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_unit_get_plural (GimpUnit unit)
name|gimp_unit_get_plural
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|_gimp_unit_vtable
operator|.
name|unit_get_plural
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|_gimp_unit_vtable
operator|.
name|unit_get_plural
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

end_unit

