begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpunit.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
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
comment|/**  * SECTION: gimpunit  * @title: gimpunit  * @short_description: Provides a collection of predefined units and  *                     functions for creating user-defined units.  * @see_also: #GimpUnitMenu, #GimpSizeEntry.  *  * Provides a collection of predefined units and functions for  * creating user-defined units.  **/
end_comment

begin_function_decl
specifier|static
name|void
name|unit_to_string
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|string_to_unit
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_unit_get_type (void)
name|gimp_unit_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|unit_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|unit_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|unit_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INT
argument_list|,
literal|"GimpUnit"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_value_register_transform_func
argument_list|(
name|unit_type
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|unit_to_string
argument_list|)
expr_stmt|;
name|g_value_register_transform_func
argument_list|(
name|G_TYPE_STRING
argument_list|,
name|unit_type
argument_list|,
name|string_to_unit
argument_list|)
expr_stmt|;
block|}
return|return
name|unit_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|unit_to_string (const GValue * src_value,GValue * dest_value)
name|unit_to_string
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
block|{
name|GimpUnit
name|unit
init|=
operator|(
name|GimpUnit
operator|)
name|g_value_get_int
argument_list|(
name|src_value
argument_list|)
decl_stmt|;
name|g_value_set_string
argument_list|(
name|dest_value
argument_list|,
name|gimp_unit_get_identifier
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|string_to_unit (const GValue * src_value,GValue * dest_value)
name|string_to_unit
parameter_list|(
specifier|const
name|GValue
modifier|*
name|src_value
parameter_list|,
name|GValue
modifier|*
name|dest_value
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|gint
name|num_units
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|str
operator|=
name|g_value_get_string
argument_list|(
name|src_value
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|str
operator|||
operator|!
operator|*
name|str
condition|)
goto|goto
name|error
goto|;
name|num_units
operator|=
name|gimp_unit_get_number_of_units
argument_list|()
expr_stmt|;
for|for
control|(
name|i
operator|=
name|GIMP_UNIT_PIXEL
init|;
name|i
operator|<
name|num_units
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|strcmp
argument_list|(
name|str
argument_list|,
name|gimp_unit_get_identifier
argument_list|(
name|i
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
break|break;
if|if
condition|(
name|i
operator|==
name|num_units
condition|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|str
argument_list|,
name|gimp_unit_get_identifier
argument_list|(
name|GIMP_UNIT_PERCENT
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
name|i
operator|=
name|GIMP_UNIT_PERCENT
expr_stmt|;
else|else
goto|goto
name|error
goto|;
block|}
name|g_value_set_int
argument_list|(
name|dest_value
argument_list|,
name|i
argument_list|)
expr_stmt|;
return|return;
name|error
label|:
name|g_warning
argument_list|(
literal|"Can't convert string '%s' to GimpUnit."
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_number_of_units:  *  * Returns the number of units which are known to the #GimpUnit system.  *  * Returns: The number of defined units.  **/
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
comment|/**  * gimp_unit_get_number_of_built_in_units:  *  * Returns the number of #GimpUnit's which are hardcoded in the unit system  * (UNIT_INCH, UNIT_MM, UNIT_POINT, UNIT_PICA and the two "pseudo unit"  *  UNIT_PIXEL).  *  * Returns: The number of built-in units.  **/
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
comment|/**  * gimp_unit_new:  * @identifier: The unit's identifier string.  * @factor: The unit's factor (how many units are in one inch).  * @digits: The unit's suggested number of digits (see gimp_unit_get_digits()).  * @symbol: The symbol of the unit (e.g. "''" for inch).  * @abbreviation: The abbreviation of the unit.  * @singular: The singular form of the unit.  * @plural: The plural form of the unit.  *  * Returns the integer ID of the new #GimpUnit.  *  * Note that a new unit is always created with its deletion flag  * set to %TRUE. You will have to set it to %FALSE with  * gimp_unit_set_deletion_flag() to make the unit definition persistent.  *  * Returns: The ID of the new unit.  **/
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
comment|/**  * gimp_unit_get_deletion_flag:  * @unit: The unit you want to know the @deletion_flag of.  *  * Returns: The unit's @deletion_flag.  **/
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
comment|/**  * gimp_unit_set_deletion_flag:  * @unit: The unit you want to set the @deletion_flag for.  * @deletion_flag: The new deletion_flag.  *  * Sets a #GimpUnit's @deletion_flag. If the @deletion_flag of a unit is  * %TRUE when GIMP exits, this unit will not be saved in the users's  * "unitrc" file.  *  * Trying to change the @deletion_flag of a built-in unit will be silently  * ignored.  **/
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
comment|/**  * gimp_unit_get_factor:  * @unit: The unit you want to know the factor of.  *  * A #GimpUnit's @factor is defined to be:  *  * distance_in_units == (@factor * distance_in_inches)  *  * Returns 0 for @unit == GIMP_UNIT_PIXEL.  *  * Returns: The unit's factor.  **/
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
comment|/**  * gimp_unit_get_digits:  * @unit: The unit you want to know the digits.  *  * Returns the number of digits set for @unit.  * Built-in units' accuracy is approximately the same as an inch with  * two digits. User-defined units can suggest a different accuracy.  *  * Note: the value is as-set by defaults or by the user and does not  * necessary provide enough precision on high-resolution images.  * When the information is needed for a specific image, the use of  * gimp_unit_get_scaled_digits() may be more appropriate.  *  * Returns 0 for @unit == GIMP_UNIT_PIXEL.  *  * Returns: The suggested number of digits.  **/
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
comment|/**  * gimp_unit_get_scaled_digits:  * @unit: The unit you want to know the digits.  * @resolution: the resolution in PPI.  *  * Returns the number of digits a @unit field should provide to get  * enough accuracy so that every pixel position shows a different  * value from neighboring pixels.  *  * Note: when needing digit accuracy to display a diagonal distance,  * the @resolution may not correspond to the image's horizontal or  * vertical resolution, but instead to the result of:  * `distance_in_pixel / distance_in_inch`.  *  * Returns: The suggested number of digits.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_unit_get_scaled_digits (GimpUnit unit,gdouble resolution)
name|gimp_unit_get_scaled_digits
parameter_list|(
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
block|{
name|gint
name|digits
decl_stmt|;
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
name|digits
operator|=
name|ceil
argument_list|(
name|log10
argument_list|(
literal|1.0
operator|/
name|gimp_pixels_to_units
argument_list|(
literal|1.0
argument_list|,
name|unit
argument_list|,
name|resolution
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|MAX
argument_list|(
name|digits
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|unit
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_get_identifier:  * @unit: The unit you want to know the identifier of.  *  * This is an untranslated string and must not be changed or freed.  *  * Returns: The unit's identifier.  **/
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
comment|/**  * gimp_unit_get_symbol:  * @unit: The unit you want to know the symbol of.  *  * This is e.g. "''" for UNIT_INCH.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's symbol.  **/
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
comment|/**  * gimp_unit_get_abbreviation:  * @unit: The unit you want to know the abbreviation of.  *  * For built-in units, this function returns the translated abbreviation  * of the unit.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's abbreviation.  **/
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
comment|/**  * gimp_unit_get_singular:  * @unit: The unit you want to know the singular form of.  *  * For built-in units, this function returns the translated singular form  * of the unit's name.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's singular form.  **/
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
comment|/**  * gimp_unit_get_plural:  * @unit: The unit you want to know the plural form of.  *  * For built-in units, this function returns the translated plural form  * of the unit's name.  *  * NOTE: This string must not be changed or freed.  *  * Returns: The unit's plural form.  **/
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

begin_function_decl
specifier|static
name|gint
name|print
parameter_list|(
name|gchar
modifier|*
name|buf
parameter_list|,
name|gint
name|len
parameter_list|,
name|gint
name|start
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|4
operator|,
function_decl|5
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function
specifier|static
name|gint
DECL|function|print (gchar * buf,gint len,gint start,const gchar * fmt,...)
name|print
parameter_list|(
name|gchar
modifier|*
name|buf
parameter_list|,
name|gint
name|len
parameter_list|,
name|gint
name|start
parameter_list|,
specifier|const
name|gchar
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|gint
name|printed
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|printed
operator|=
name|g_vsnprintf
argument_list|(
name|buf
operator|+
name|start
argument_list|,
name|len
operator|-
name|start
argument_list|,
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|printed
operator|<
literal|0
condition|)
name|printed
operator|=
name|len
operator|-
name|start
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|printed
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_format_string:  * @format: A printf-like format string which is used to create the unit  *          string.  * @unit:   A unit.  *  * The @format string supports the following percent expansions:  *  *<informaltable pgwide="1" frame="none" role="enum">  *<tgroup cols="2"><colspec colwidth="1*"/><colspec colwidth="8*"/>  *<tbody>  *<row>  *<entry>% f</entry>  *<entry>Factor (how many units make up an inch)</entry>  *</row>  *<row>  *<entry>% y</entry>  *<entry>Symbol (e.g. "''" for GIMP_UNIT_INCH)</entry>  *</row>  *<row>  *<entry>% a</entry>  *<entry>Abbreviation</entry>  *</row>  *<row>  *<entry>% s</entry>  *<entry>Singular</entry>  *</row>  *<row>  *<entry>% p</entry>  *<entry>Plural</entry>  *</row>  *<row>  *<entry>%%</entry>  *<entry>Literal percent</entry>  *</row>  *</tbody>  *</tgroup>  *</informaltable>  *  * Returns: A newly allocated string with above percent expressions  *          replaced with the resp. strings for @unit.  *  * Since: 2.8  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_unit_format_string (const gchar * format,GimpUnit unit)
name|gimp_unit_format_string
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|gchar
name|buffer
index|[
literal|1024
index|]
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
operator|||
operator|(
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
operator|&&
name|unit
operator|<
name|gimp_unit_get_number_of_units
argument_list|()
operator|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
name|i
operator|<
operator|(
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
operator|-
literal|1
operator|)
operator|&&
operator|*
name|format
condition|)
block|{
switch|switch
condition|(
operator|*
name|format
condition|)
block|{
case|case
literal|'%'
case|:
name|format
operator|++
expr_stmt|;
switch|switch
condition|(
operator|*
name|format
condition|)
block|{
case|case
literal|0
case|:
name|g_warning
argument_list|(
literal|"%s: unit-menu-format string ended within %%-sequence"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'%'
case|:
name|buffer
index|[
name|i
operator|++
index|]
operator|=
literal|'%'
expr_stmt|;
break|break;
case|case
literal|'f'
case|:
comment|/* factor (how many units make up an inch) */
name|i
operator|+=
name|print
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|i
argument_list|,
literal|"%f"
argument_list|,
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'y'
case|:
comment|/* symbol ("''" for inch) */
name|i
operator|+=
name|print
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|gimp_unit_get_symbol
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'a'
case|:
comment|/* abbreviation */
name|i
operator|+=
name|print
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|gimp_unit_get_abbreviation
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'s'
case|:
comment|/* singular */
name|i
operator|+=
name|print
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|gimp_unit_get_singular
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'p'
case|:
comment|/* plural */
name|i
operator|+=
name|print
argument_list|(
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|i
argument_list|,
literal|"%s"
argument_list|,
name|gimp_unit_get_plural
argument_list|(
name|unit
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"%s: unit-menu-format contains unknown format "
literal|"sequence '%%%c'"
argument_list|,
name|G_STRFUNC
argument_list|,
operator|*
name|format
argument_list|)
expr_stmt|;
break|break;
block|}
break|break;
default|default:
name|buffer
index|[
name|i
operator|++
index|]
operator|=
operator|*
name|format
expr_stmt|;
break|break;
block|}
name|format
operator|++
expr_stmt|;
block|}
name|buffer
index|[
name|MIN
argument_list|(
name|i
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
operator|-
literal|1
argument_list|)
index|]
operator|=
literal|0
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|buffer
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_UNIT  */
end_comment

begin_define
DECL|macro|GIMP_PARAM_SPEC_UNIT (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_UNIT
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_UNIT, GimpParamSpecUnit))
end_define

begin_typedef
DECL|typedef|GimpParamSpecUnit
typedef|typedef
name|struct
name|_GimpParamSpecUnit
name|GimpParamSpecUnit
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecUnit
struct|struct
name|_GimpParamSpecUnit
block|{
DECL|member|parent_instance
name|GParamSpecInt
name|parent_instance
decl_stmt|;
DECL|member|allow_percent
name|gboolean
name|allow_percent
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_param_unit_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_param_unit_value_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_param_unit_get_type:  *  * Reveals the object type  *  * Returns: the #GType for a unit param object  *  * Since: 2.4  **/
end_comment

begin_function
name|GType
DECL|function|gimp_param_unit_get_type (void)
name|gimp_param_unit_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|spec_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|spec_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|type_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_unit_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecUnit
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|spec_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_INT
argument_list|,
literal|"GimpParamUnit"
argument_list|,
operator|&
name|type_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|spec_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_unit_class_init (GParamSpecClass * class)
name|gimp_param_unit_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|class
parameter_list|)
block|{
name|class
operator|->
name|value_type
operator|=
name|GIMP_TYPE_UNIT
expr_stmt|;
name|class
operator|->
name|value_validate
operator|=
name|gimp_param_unit_value_validate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_param_unit_value_validate (GParamSpec * pspec,GValue * value)
name|gimp_param_unit_value_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GParamSpecInt
modifier|*
name|ispec
init|=
name|G_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GimpParamSpecUnit
modifier|*
name|uspec
init|=
name|GIMP_PARAM_SPEC_UNIT
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|gint
name|oval
init|=
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|uspec
operator|->
name|allow_percent
operator|&&
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
operator|==
name|GIMP_UNIT_PERCENT
operator|)
condition|)
block|{
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
operator|=
name|CLAMP
argument_list|(
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
argument_list|,
name|ispec
operator|->
name|minimum
argument_list|,
name|gimp_unit_get_number_of_units
argument_list|()
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
return|return
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_int
operator|!=
name|oval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_param_spec_unit:  * @name:          Canonical name of the param  * @nick:          Nickname of the param  * @blurb:         Brief description of param.  * @allow_pixels:  Whether "pixels" is an allowed unit.  * @allow_percent: Whether "percent" is an allowed unit.  * @default_value: Unit to use if none is assigned.  * @flags:         a combination of #GParamFlags  *  * Creates a param spec to hold a units param.  * See g_param_spec_internal() for more information.  *  * Returns: a newly allocated #GParamSpec instance  *  * Since: 2.4  **/
end_comment

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_unit (const gchar * name,const gchar * nick,const gchar * blurb,gboolean allow_pixels,gboolean allow_percent,GimpUnit default_value,GParamFlags flags)
name|gimp_param_spec_unit
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gboolean
name|allow_pixels
parameter_list|,
name|gboolean
name|allow_percent
parameter_list|,
name|GimpUnit
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpParamSpecUnit
modifier|*
name|pspec
decl_stmt|;
name|GParamSpecInt
modifier|*
name|ispec
decl_stmt|;
name|pspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_UNIT
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|ispec
operator|=
name|G_PARAM_SPEC_INT
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
name|ispec
operator|->
name|default_value
operator|=
name|default_value
expr_stmt|;
name|ispec
operator|->
name|minimum
operator|=
name|allow_pixels
condition|?
name|GIMP_UNIT_PIXEL
else|:
name|GIMP_UNIT_INCH
expr_stmt|;
name|ispec
operator|->
name|maximum
operator|=
name|GIMP_UNIT_PERCENT
operator|-
literal|1
expr_stmt|;
name|pspec
operator|->
name|allow_percent
operator|=
name|allow_percent
expr_stmt|;
return|return
name|G_PARAM_SPEC
argument_list|(
name|pspec
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixels_to_units:  * @pixels:     value in pixels  * @unit:       unit to convert to  * @resolution: resolution in DPI  *  * Converts a @value specified in pixels to @unit.  *  * Returns: @pixels converted to units.  *  * Since: 2.8  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_pixels_to_units (gdouble pixels,GimpUnit unit,gdouble resolution)
name|gimp_pixels_to_units
parameter_list|(
name|gdouble
name|pixels
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
block|{
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
return|return
name|pixels
return|;
return|return
name|pixels
operator|*
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
operator|/
name|resolution
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_units_to_pixels:  * @value:      value in units  * @unit:       unit of @value  * @resolution: resloution in DPI  *  * Converts a @value specified in @unit to pixels.  *  * Returns: @value converted to pixels.  *  * Since: 2.8  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_units_to_pixels (gdouble value,GimpUnit unit,gdouble resolution)
name|gimp_units_to_pixels
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
block|{
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
return|return
name|value
return|;
return|return
name|value
operator|*
name|resolution
operator|/
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_units_to_points:  * @value:      value in units  * @unit:       unit of @value  * @resolution: resloution in DPI  *  * Converts a @value specified in @unit to points.  *  * Returns: @value converted to points.  *  * Since: 2.8  **/
end_comment

begin_function
name|gdouble
DECL|function|gimp_units_to_points (gdouble value,GimpUnit unit,gdouble resolution)
name|gimp_units_to_points
parameter_list|(
name|gdouble
name|value
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
block|{
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_POINT
condition|)
return|return
name|value
return|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
return|return
operator|(
name|value
operator|*
name|gimp_unit_get_factor
argument_list|(
name|GIMP_UNIT_POINT
argument_list|)
operator|/
name|resolution
operator|)
return|;
return|return
operator|(
name|value
operator|*
name|gimp_unit_get_factor
argument_list|(
name|GIMP_UNIT_POINT
argument_list|)
operator|/
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
operator|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_unit_is_metric:  * @unit: The unit  *  * Checks if the given @unit is metric. A simplistic test is used  * that looks at the unit's factor and checks if it is 2.54 multiplied  * by some common powers of 10. Currently it checks for mm, cm, dm, m.  *  * See also: gimp_unit_get_factor()  *  * Returns: %TRUE if the @unit is metric.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_unit_is_metric (GimpUnit unit)
name|gimp_unit_is_metric
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|gdouble
name|factor
decl_stmt|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_MM
condition|)
return|return
name|TRUE
return|;
name|factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
expr_stmt|;
if|if
condition|(
name|factor
operator|==
literal|0.0
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
operator|(
name|ABS
argument_list|(
name|factor
operator|-
literal|0.0254
argument_list|)
operator|<
literal|1e-7
operator|)
operator|||
comment|/* m  */
operator|(
name|ABS
argument_list|(
name|factor
operator|-
literal|0.254
argument_list|)
operator|<
literal|1e-6
operator|)
operator|||
comment|/* dm */
operator|(
name|ABS
argument_list|(
name|factor
operator|-
literal|2.54
argument_list|)
operator|<
literal|1e-5
operator|)
operator|||
comment|/* cm */
operator|(
name|ABS
argument_list|(
name|factor
operator|-
literal|25.4
argument_list|)
operator|<
literal|1e-4
operator|)
operator|)
return|;
comment|/* mm */
block|}
end_function

end_unit

