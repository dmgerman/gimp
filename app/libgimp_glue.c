begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_define
DECL|macro|__LIBGIMP_GLUE_C__
define|#
directive|define
name|__LIBGIMP_GLUE_C__
end_define

begin_include
include|#
directive|include
file|"libgimp_glue.h"
end_include

begin_function
name|gint
DECL|function|gimp_unit_get_number_of_units (void)
name|gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|_gimp_unit_get_number_of_units
argument_list|(
name|the_gimp
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_unit_get_number_of_built_in_units (void)
name|gimp_unit_get_number_of_built_in_units
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
return|return
name|_gimp_unit_new
argument_list|(
name|the_gimp
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
name|gboolean
DECL|function|gimp_unit_get_deletion_flag (GimpUnit unit)
name|gimp_unit_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_deletion_flag
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

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
name|_gimp_unit_set_deletion_flag
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|,
name|deletion_flag
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_unit_get_factor (GimpUnit unit)
name|gimp_unit_get_factor
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_factor
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_unit_get_digits (GimpUnit unit)
name|gimp_unit_get_digits
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|_gimp_unit_get_digits
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

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
return|return
name|_gimp_unit_get_identifier
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

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
return|return
name|_gimp_unit_get_symbol
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

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
return|return
name|_gimp_unit_get_abbreviation
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

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
return|return
name|_gimp_unit_get_singular
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

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
return|return
name|_gimp_unit_get_plural
argument_list|(
name|the_gimp
argument_list|,
name|unit
argument_list|)
return|;
block|}
end_function

end_unit

