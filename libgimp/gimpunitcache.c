begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpunitcache.c  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"gimpunitcache.h"
end_include

begin_include
include|#
directive|include
file|"gimpunit_pdb.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_comment
comment|/*  internal structures  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27a6b5760108
block|{
DECL|member|factor
name|gdouble
name|factor
decl_stmt|;
DECL|member|digits
name|gint
name|digits
decl_stmt|;
DECL|member|identifier
specifier|const
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|symbol
specifier|const
name|gchar
modifier|*
name|symbol
decl_stmt|;
DECL|member|abbreviation
specifier|const
name|gchar
modifier|*
name|abbreviation
decl_stmt|;
DECL|member|singular
specifier|const
name|gchar
modifier|*
name|singular
decl_stmt|;
DECL|member|plural
specifier|const
name|gchar
modifier|*
name|plural
decl_stmt|;
DECL|typedef|GimpUnitDef
block|}
name|GimpUnitDef
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|gimp_unit_defs
specifier|static
name|GimpUnitDef
modifier|*
name|gimp_unit_defs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_units_initialized
specifier|static
name|GimpUnit
name|gimp_units_initialized
init|=
literal|0
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

begin_function_decl
specifier|static
name|void
name|gimp_unit_def_init
parameter_list|(
name|GimpUnitDef
modifier|*
name|unit_def
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unit_init (GimpUnit unit)
name|gimp_unit_init
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|n
decl_stmt|;
if|if
condition|(
name|unit
operator|<
name|gimp_units_initialized
condition|)
return|return
name|TRUE
return|;
name|n
operator|=
name|_gimp_unit_get_number_of_units
argument_list|()
expr_stmt|;
if|if
condition|(
name|unit
operator|>=
name|n
condition|)
return|return
name|FALSE
return|;
name|gimp_unit_defs
operator|=
name|g_renew
argument_list|(
name|GimpUnitDef
argument_list|,
name|gimp_unit_defs
argument_list|,
name|n
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|gimp_units_initialized
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|gimp_unit_def_init
argument_list|(
operator|&
name|gimp_unit_defs
index|[
name|i
index|]
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
name|gimp_units_initialized
operator|=
name|n
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unit_def_init (GimpUnitDef * unit_def,GimpUnit unit)
name|gimp_unit_def_init
parameter_list|(
name|GimpUnitDef
modifier|*
name|unit_def
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|unit_def
operator|->
name|factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|unit_def
operator|->
name|digits
operator|=
name|_gimp_unit_get_digits
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|unit_def
operator|->
name|identifier
operator|=
name|_gimp_unit_get_identifier
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|unit_def
operator|->
name|symbol
operator|=
name|_gimp_unit_get_symbol
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|unit_def
operator|->
name|abbreviation
operator|=
name|_gimp_unit_get_abbreviation
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|unit_def
operator|->
name|singular
operator|=
name|_gimp_unit_get_singular
argument_list|(
name|unit
argument_list|)
expr_stmt|;
name|unit_def
operator|->
name|plural
operator|=
name|_gimp_unit_get_plural
argument_list|(
name|unit
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|_gimp_unit_cache_get_number_of_units (void)
name|_gimp_unit_cache_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|_gimp_unit_get_number_of_units
argument_list|()
return|;
block|}
end_function

begin_function
name|gint
DECL|function|_gimp_unit_cache_get_number_of_built_in_units (void)
name|_gimp_unit_cache_get_number_of_built_in_units
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
DECL|function|_gimp_unit_cache_new (gchar * identifier,gdouble factor,gint digits,gchar * symbol,gchar * abbreviation,gchar * singular,gchar * plural)
name|_gimp_unit_cache_new
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
DECL|function|_gimp_unit_cache_get_deletion_flag (GimpUnit unit)
name|_gimp_unit_cache_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
argument_list|,
name|TRUE
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
name|_gimp_unit_get_deletion_flag
argument_list|(
name|unit
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|_gimp_unit_cache_set_deletion_flag (GimpUnit unit,gboolean deletion_flag)
name|_gimp_unit_cache_set_deletion_flag
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
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|GIMP_UNIT_END
condition|)
return|return;
name|_gimp_unit_set_deletion_flag
argument_list|(
name|unit
argument_list|,
name|deletion_flag
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|_gimp_unit_cache_get_factor (GimpUnit unit)
name|_gimp_unit_cache_get_factor
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_INCH
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
condition|)
return|return
name|gimp_unit_percent
operator|.
name|factor
return|;
if|if
condition|(
operator|!
name|gimp_unit_init
argument_list|(
name|unit
argument_list|)
condition|)
return|return
literal|1.0
return|;
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|factor
return|;
block|}
end_function

begin_function
name|gint
DECL|function|_gimp_unit_cache_get_digits (GimpUnit unit)
name|_gimp_unit_cache_get_digits
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_INCH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PERCENT
condition|)
return|return
name|gimp_unit_percent
operator|.
name|digits
return|;
if|if
condition|(
operator|!
name|gimp_unit_init
argument_list|(
name|unit
argument_list|)
condition|)
return|return
literal|0
return|;
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|digits
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_cache_get_identifier (GimpUnit unit)
name|_gimp_unit_cache_get_identifier
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|gimp_unit_init
argument_list|(
name|unit
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|identifier
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_cache_get_symbol (GimpUnit unit)
name|_gimp_unit_cache_get_symbol
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|gimp_unit_init
argument_list|(
name|unit
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|symbol
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_cache_get_abbreviation (GimpUnit unit)
name|_gimp_unit_cache_get_abbreviation
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|gimp_unit_init
argument_list|(
name|unit
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|abbreviation
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_cache_get_singular (GimpUnit unit)
name|_gimp_unit_cache_get_singular
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|gimp_unit_init
argument_list|(
name|unit
argument_list|)
condition|)
return|return
name|NULL
return|;
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
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|_gimp_unit_cache_get_plural (GimpUnit unit)
name|_gimp_unit_cache_get_plural
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|GIMP_UNIT_PIXEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|gimp_unit_init
argument_list|(
name|unit
argument_list|)
condition|)
return|return
name|NULL
return|;
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
block|}
end_function

end_unit

