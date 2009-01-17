begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase-private.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
end_include

begin_decl_stmt
DECL|variable|the_unit_gimp
specifier|static
name|Gimp
modifier|*
name|the_unit_gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|gint
DECL|function|units_get_number_of_units (void)
name|units_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|_gimp_unit_get_number_of_units
argument_list|(
name|the_unit_gimp
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|units_get_number_of_built_in_units (void)
name|units_get_number_of_built_in_units
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|GIMP_UNIT_END
return|;
block|}
end_function

begin_function
specifier|static
name|GimpUnit
DECL|function|units_unit_new (gchar * identifier,gdouble factor,gint digits,gchar * symbol,gchar * abbreviation,gchar * singular,gchar * plural)
name|units_unit_new
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
return|return
name|_gimp_unit_new
argument_list|(
name|the_unit_gimp
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
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|units_unit_get_deletion_flag (GimpUnit unit)
name|units_unit_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_deletion_flag
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|units_unit_set_deletion_flag (GimpUnit unit,gboolean deletion_flag)
name|units_unit_set_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
block|{
name|_gimp_unit_set_deletion_flag
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|,
name|deletion_flag
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|units_unit_get_factor (GimpUnit unit)
name|units_unit_get_factor
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_factor
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|units_unit_get_digits (GimpUnit unit)
name|units_unit_get_digits
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_digits
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|units_unit_get_identifier (GimpUnit unit)
name|units_unit_get_identifier
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_identifier
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|units_unit_get_symbol (GimpUnit unit)
name|units_unit_get_symbol
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_symbol
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|units_unit_get_abbreviation (GimpUnit unit)
name|units_unit_get_abbreviation
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_abbreviation
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|units_unit_get_singular (GimpUnit unit)
name|units_unit_get_singular
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_singular
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|units_unit_get_plural (GimpUnit unit)
name|units_unit_get_plural
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_plural
argument_list|(
name|the_unit_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|units_init (Gimp * gimp)
name|units_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpUnitVtable
name|vtable
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|the_unit_gimp
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|the_unit_gimp
operator|=
name|gimp
expr_stmt|;
name|vtable
operator|.
name|unit_get_number_of_units
operator|=
name|units_get_number_of_units
expr_stmt|;
name|vtable
operator|.
name|unit_get_number_of_built_in_units
operator|=
name|units_get_number_of_built_in_units
expr_stmt|;
name|vtable
operator|.
name|unit_new
operator|=
name|units_unit_new
expr_stmt|;
name|vtable
operator|.
name|unit_get_deletion_flag
operator|=
name|units_unit_get_deletion_flag
expr_stmt|;
name|vtable
operator|.
name|unit_set_deletion_flag
operator|=
name|units_unit_set_deletion_flag
expr_stmt|;
name|vtable
operator|.
name|unit_get_factor
operator|=
name|units_unit_get_factor
expr_stmt|;
name|vtable
operator|.
name|unit_get_digits
operator|=
name|units_unit_get_digits
expr_stmt|;
name|vtable
operator|.
name|unit_get_identifier
operator|=
name|units_unit_get_identifier
expr_stmt|;
name|vtable
operator|.
name|unit_get_symbol
operator|=
name|units_unit_get_symbol
expr_stmt|;
name|vtable
operator|.
name|unit_get_abbreviation
operator|=
name|units_unit_get_abbreviation
expr_stmt|;
name|vtable
operator|.
name|unit_get_singular
operator|=
name|units_unit_get_singular
expr_stmt|;
name|vtable
operator|.
name|unit_get_plural
operator|=
name|units_unit_get_plural
expr_stmt|;
name|gimp_base_init
argument_list|(
operator|&
name|vtable
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

