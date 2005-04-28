begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpunit.c  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* internal structures */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27c1b5160108
block|{
DECL|member|delete_on_exit
name|gboolean
name|delete_on_exit
decl_stmt|;
DECL|member|factor
name|gdouble
name|factor
decl_stmt|;
DECL|member|digits
name|gint
name|digits
decl_stmt|;
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|symbol
name|gchar
modifier|*
name|symbol
decl_stmt|;
DECL|member|abbreviation
name|gchar
modifier|*
name|abbreviation
decl_stmt|;
DECL|member|singular
name|gchar
modifier|*
name|singular
decl_stmt|;
DECL|member|plural
name|gchar
modifier|*
name|plural
decl_stmt|;
DECL|typedef|GimpUnitDef
block|}
name|GimpUnitDef
typedef|;
end_typedef

begin_comment
comment|/*  these are the built-in units  */
end_comment

begin_decl_stmt
DECL|variable|gimp_unit_defs
specifier|static
specifier|const
name|GimpUnitDef
name|gimp_unit_defs
index|[
name|GIMP_UNIT_END
index|]
init|=
block|{
comment|/* pseudo unit */
block|{
name|FALSE
block|,
literal|0.0
block|,
literal|0
block|,
literal|"pixels"
block|,
literal|"px"
block|,
literal|"px"
block|,
name|N_
argument_list|(
literal|"pixel"
argument_list|)
block|,
name|N_
argument_list|(
literal|"pixels"
argument_list|)
block|}
block|,
comment|/* standard units */
block|{
name|FALSE
block|,
literal|1.0
block|,
literal|2
block|,
literal|"inches"
block|,
literal|"''"
block|,
literal|"in"
block|,
name|N_
argument_list|(
literal|"inch"
argument_list|)
block|,
name|N_
argument_list|(
literal|"inches"
argument_list|)
block|}
block|,
block|{
name|FALSE
block|,
literal|25.4
block|,
literal|1
block|,
literal|"millimeters"
block|,
literal|"mm"
block|,
literal|"mm"
block|,
name|N_
argument_list|(
literal|"millimeter"
argument_list|)
block|,
name|N_
argument_list|(
literal|"millimeters"
argument_list|)
block|}
block|,
comment|/* professional units */
block|{
name|FALSE
block|,
literal|72.0
block|,
literal|0
block|,
literal|"points"
block|,
literal|"pt"
block|,
literal|"pt"
block|,
name|N_
argument_list|(
literal|"point"
argument_list|)
block|,
name|N_
argument_list|(
literal|"points"
argument_list|)
block|}
block|,
block|{
name|FALSE
block|,
literal|6.0
block|,
literal|1
block|,
literal|"picas"
block|,
literal|"pc"
block|,
literal|"pc"
block|,
name|N_
argument_list|(
literal|"pica"
argument_list|)
block|,
name|N_
argument_list|(
literal|"picas"
argument_list|)
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  not a unit at all but kept here to have the strings in one place  */
end_comment

begin_decl_stmt
DECL|variable|gimp_unit_percent
specifier|static
specifier|const
name|GimpUnitDef
name|gimp_unit_percent
init|=
block|{
name|FALSE
block|,
literal|0.0
block|,
literal|0
block|,
literal|"percent"
block|,
literal|"%"
block|,
literal|"%"
block|,
name|N_
argument_list|(
literal|"percent"
argument_list|)
block|,
name|N_
argument_list|(
literal|"percent"
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* private functions */
end_comment

begin_function
specifier|static
name|GimpUnitDef
modifier|*
DECL|function|_gimp_unit_get_user_unit (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_user_unit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
return|return
name|g_list_nth_data
argument_list|(
name|gimp
operator|->
name|user_units
argument_list|,
name|unit
operator|-
name|GIMP_UNIT_END
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* public functions */
end_comment

begin_function
name|gint
DECL|function|_gimp_unit_get_number_of_units (Gimp * gimp)
name|_gimp_unit_get_number_of_units
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
return|;
block|}
end_function

begin_function
name|gint
DECL|function|_gimp_unit_get_number_of_built_in_units (Gimp * gimp)
name|_gimp_unit_get_number_of_built_in_units
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|GIMP_UNIT_END
return|;
block|}
end_function

begin_function
name|GimpUnit
DECL|function|_gimp_unit_new (Gimp * gimp,gchar * identifier,gdouble factor,gint digits,gchar * symbol,gchar * abbreviation,gchar * singular,gchar * plural)
name|_gimp_unit_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
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
name|GimpUnitDef
modifier|*
name|user_unit
decl_stmt|;
name|user_unit
operator|=
name|g_new0
argument_list|(
name|GimpUnitDef
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|user_unit
operator|->
name|delete_on_exit
operator|=
name|TRUE
expr_stmt|;
name|user_unit
operator|->
name|factor
operator|=
name|factor
expr_stmt|;
name|user_unit
operator|->
name|digits
operator|=
name|digits
expr_stmt|;
name|user_unit
operator|->
name|identifier
operator|=
name|g_strdup
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|user_unit
operator|->
name|symbol
operator|=
name|g_strdup
argument_list|(
name|symbol
argument_list|)
expr_stmt|;
name|user_unit
operator|->
name|abbreviation
operator|=
name|g_strdup
argument_list|(
name|abbreviation
argument_list|)
expr_stmt|;
name|user_unit
operator|->
name|singular
operator|=
name|g_strdup
argument_list|(
name|singular
argument_list|)
expr_stmt|;
name|user_unit
operator|->
name|plural
operator|=
name|g_strdup
argument_list|(
name|plural
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|user_units
operator|=
name|g_list_append
argument_list|(
name|gimp
operator|->
name|user_units
argument_list|,
name|user_unit
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|n_user_units
operator|++
expr_stmt|;
return|return
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|_gimp_unit_get_deletion_flag (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_deletion_flag
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|FALSE
return|;
return|return
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|delete_on_exit
return|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_unit_set_deletion_flag (Gimp * gimp,GimpUnit unit,gboolean deletion_flag)
name|_gimp_unit_set_deletion_flag
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
operator|(
name|unit
operator|>=
name|GIMP_UNIT_END
operator|)
operator|&&
operator|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
operator|)
argument_list|)
expr_stmt|;
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|delete_on_exit
operator|=
name|deletion_flag
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|_gimp_unit_get_factor (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_factor
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|GIMP_UNIT_INCH
index|]
operator|.
name|factor
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|factor
return|;
return|return
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|factor
return|;
block|}
end_function

begin_function
name|gint
DECL|function|_gimp_unit_get_digits (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_digits
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|GIMP_UNIT_INCH
index|]
operator|.
name|digits
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|digits
return|;
return|return
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|digits
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_get_identifier (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_identifier
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
operator|)
operator|||
operator|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|GIMP_UNIT_INCH
index|]
operator|.
name|identifier
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|identifier
return|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
condition|)
return|return
name|gimp_unit_percent
operator|.
name|identifier
return|;
return|return
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|identifier
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_get_symbol (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_symbol
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
operator|)
operator|||
operator|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|GIMP_UNIT_INCH
index|]
operator|.
name|symbol
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|symbol
return|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
condition|)
return|return
name|gimp_unit_percent
operator|.
name|symbol
return|;
return|return
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|symbol
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_get_abbreviation (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_abbreviation
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
operator|)
operator|||
operator|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|GIMP_UNIT_INCH
index|]
operator|.
name|abbreviation
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|abbreviation
return|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
condition|)
return|return
name|gimp_unit_percent
operator|.
name|abbreviation
return|;
return|return
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|abbreviation
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_get_singular (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_singular
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
operator|)
operator|||
operator|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
operator|)
argument_list|,
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|GIMP_UNIT_INCH
index|]
operator|.
name|singular
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|singular
argument_list|)
return|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
condition|)
return|return
name|gettext
argument_list|(
name|gimp_unit_percent
operator|.
name|singular
argument_list|)
return|;
return|return
name|gettext
argument_list|(
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|singular
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_get_plural (Gimp * gimp,GimpUnit unit)
name|_gimp_unit_get_plural
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|<
operator|(
name|GIMP_UNIT_END
operator|+
name|gimp
operator|->
name|n_user_units
operator|)
operator|)
operator|||
operator|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
operator|)
argument_list|,
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|GIMP_UNIT_INCH
index|]
operator|.
name|plural
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|plural
argument_list|)
return|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
condition|)
return|return
name|gettext
argument_list|(
name|gimp_unit_percent
operator|.
name|plural
argument_list|)
return|;
return|return
name|gettext
argument_list|(
name|_gimp_unit_get_user_unit
argument_list|(
name|gimp
argument_list|,
name|unit
argument_list|)
operator|->
name|plural
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/* The sole purpose of this function is to release the allocated  * memory. It must only be used from gimp_units_exit().  */
end_comment

begin_function
name|void
DECL|function|gimp_user_units_free (Gimp * gimp)
name|gimp_user_units_free
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|user_units
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpUnitDef
modifier|*
name|user_unit
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_free
argument_list|(
name|user_unit
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|user_unit
operator|->
name|symbol
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|user_unit
operator|->
name|abbreviation
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|user_unit
operator|->
name|singular
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|user_unit
operator|->
name|plural
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|user_unit
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|gimp
operator|->
name|user_units
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|user_units
operator|=
name|NULL
expr_stmt|;
name|gimp
operator|->
name|n_user_units
operator|=
literal|0
expr_stmt|;
block|}
end_function

end_unit

