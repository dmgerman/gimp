begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpunit.c  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|"gimpunit.h"
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
DECL|struct|__anon2a0aa46a0108
typedef|typedef
struct|struct
block|{
DECL|member|delete_on_exit
name|guint
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

begin_decl_stmt
DECL|variable|gimp_unit_defs
specifier|static
name|GimpUnitDef
name|gimp_unit_defs
index|[
name|UNIT_END
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
comment|/*  public functions  */
end_comment

begin_function
name|gint
DECL|function|gimp_unit_get_number_of_units (void)
name|gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|int
name|number
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_number_of_units"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|number
operator|=
name|UNIT_END
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|number
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|number
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
name|UNIT_END
return|;
block|}
end_function

begin_function
name|GUnit
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
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|GUnit
name|unit
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_STRING
argument_list|,
name|g_strdup
argument_list|(
name|identifier
argument_list|)
argument_list|,
name|PARAM_FLOAT
argument_list|,
name|factor
argument_list|,
name|PARAM_INT32
argument_list|,
name|digits
argument_list|,
name|PARAM_STRING
argument_list|,
name|g_strdup
argument_list|(
name|symbol
argument_list|)
argument_list|,
name|PARAM_STRING
argument_list|,
name|g_strdup
argument_list|(
name|abbreviation
argument_list|)
argument_list|,
name|PARAM_STRING
argument_list|,
name|g_strdup
argument_list|(
name|singular
argument_list|)
argument_list|,
name|PARAM_STRING
argument_list|,
name|g_strdup
argument_list|(
name|plural
argument_list|)
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|unit
operator|=
name|UNIT_INCH
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|unit
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|unit
return|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_unit_get_deletion_flag (GUnit unit)
name|gimp_unit_get_deletion_flag
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|guint
name|flag
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_PIXEL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|FALSE
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_deletion_flag"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|flag
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|flag
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|flag
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unit_set_deletion_flag (GUnit unit,guint deletion_flag)
name|gimp_unit_set_deletion_flag
parameter_list|(
name|GUnit
name|unit
parameter_list|,
name|guint
name|deletion_flag
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_PIXEL
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_set_deletion_flag"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_INT32
argument_list|,
name|deletion_flag
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_unit_get_factor (GUnit unit)
name|gimp_unit_get_factor
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_INCH
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|factor
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_factor"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|factor
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|factor
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|factor
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_unit_get_digits (GUnit unit)
name|gimp_unit_get_digits
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gint
name|digits
decl_stmt|;
if|if
condition|(
name|unit
operator|<
literal|0
condition|)
return|return
literal|0
return|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|digits
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_digits"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|digits
operator|=
name|gimp_unit_defs
index|[
name|UNIT_INCH
index|]
operator|.
name|digits
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|digits
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|digits
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_unit_get_identifier (GUnit unit)
name|gimp_unit_get_identifier
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_PIXEL
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|g_strdup
argument_list|(
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|identifier
argument_list|)
return|;
if|if
condition|(
name|unit
operator|==
name|UNIT_PERCENT
condition|)
return|return
name|g_strdup
argument_list|(
name|gimp_unit_percent
operator|.
name|identifier
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_identifier"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|identifier
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|identifier
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|identifier
condition|?
name|identifier
else|:
name|g_strdup
argument_list|(
literal|""
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_unit_get_symbol (GUnit unit)
name|gimp_unit_get_symbol
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|symbol
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_PIXEL
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|g_strdup
argument_list|(
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|symbol
argument_list|)
return|;
if|if
condition|(
name|unit
operator|==
name|UNIT_PERCENT
condition|)
return|return
name|g_strdup
argument_list|(
name|gimp_unit_percent
operator|.
name|symbol
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_symbol"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|symbol
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|symbol
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|symbol
condition|?
name|symbol
else|:
name|g_strdup
argument_list|(
literal|""
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_unit_get_abbreviation (GUnit unit)
name|gimp_unit_get_abbreviation
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|abbreviation
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_PIXEL
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|g_strdup
argument_list|(
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|abbreviation
argument_list|)
return|;
if|if
condition|(
name|unit
operator|==
name|UNIT_PERCENT
condition|)
return|return
name|g_strdup
argument_list|(
name|gimp_unit_percent
operator|.
name|abbreviation
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_abbreviation"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|abbreviation
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|abbreviation
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|abbreviation
condition|?
name|abbreviation
else|:
name|g_strdup
argument_list|(
literal|""
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_unit_get_singular (GUnit unit)
name|gimp_unit_get_singular
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|singular
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_PIXEL
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|g_strdup
argument_list|(
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|singular
argument_list|)
argument_list|)
return|;
if|if
condition|(
name|unit
operator|==
name|UNIT_PERCENT
condition|)
return|return
name|g_strdup
argument_list|(
name|gettext
argument_list|(
name|gimp_unit_percent
operator|.
name|singular
argument_list|)
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_singular"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|singular
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|singular
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|singular
condition|?
name|singular
else|:
name|g_strdup
argument_list|(
literal|""
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_unit_get_plural (GUnit unit)
name|gimp_unit_get_plural
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|plural
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|unit
operator|>=
name|UNIT_PIXEL
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|<
name|UNIT_END
condition|)
return|return
name|g_strdup
argument_list|(
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|unit
index|]
operator|.
name|plural
argument_list|)
argument_list|)
return|;
if|if
condition|(
name|unit
operator|==
name|UNIT_PERCENT
condition|)
return|return
name|g_strdup
argument_list|(
name|gettext
argument_list|(
name|gimp_unit_percent
operator|.
name|plural
argument_list|)
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_unit_get_plural"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_INT32
argument_list|,
name|unit
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|plural
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|plural
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|plural
condition|?
name|plural
else|:
name|g_strdup
argument_list|(
literal|""
argument_list|)
return|;
block|}
end_function

end_unit

