begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpunit.c  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/* internal structures */
end_comment

begin_typedef
DECL|struct|__anon2a3380340108
typedef|typedef
struct|struct
block|{
DECL|member|factor
name|float
name|factor
decl_stmt|;
DECL|member|digits
name|gint
name|digits
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
comment|/* 'pseudo' unit */
block|{
literal|0.0
block|,
literal|0
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
comment|/* 'standard' units */
block|{
literal|1.0
block|,
literal|2
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
literal|2.54
block|,
literal|2
block|,
literal|"cm"
block|,
literal|"cm"
block|,
name|N_
argument_list|(
literal|"centimeter"
argument_list|)
block|,
name|N_
argument_list|(
literal|"centimeters"
argument_list|)
block|}
block|,
comment|/* 'professional' units */
block|{
literal|72.0
block|,
literal|0
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
literal|6.0
block|,
literal|1
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
block|,
comment|/* convenience units */
block|{
literal|25.4
block|,
literal|1
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
block|{
literal|0.0254
block|,
literal|4
block|,
literal|"m"
block|,
literal|"m"
block|,
name|N_
argument_list|(
literal|"meter"
argument_list|)
block|,
name|N_
argument_list|(
literal|"meters"
argument_list|)
block|}
block|,
block|{
literal|1.0
operator|/
literal|12.0
block|,
literal|4
block|,
literal|"'"
block|,
literal|"ft"
block|,
name|N_
argument_list|(
literal|"foot"
argument_list|)
block|,
name|N_
argument_list|(
literal|"feet"
argument_list|)
block|}
block|,
block|{
literal|1.0
operator|/
literal|36.0
block|,
literal|4
block|,
literal|"yd"
block|,
literal|"yd"
block|,
name|N_
argument_list|(
literal|"yard"
argument_list|)
block|,
name|N_
argument_list|(
literal|"yards"
argument_list|)
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* public functions */
end_comment

begin_function
name|gfloat
DECL|function|gimp_unit_get_factor (GUnit unit)
name|gimp_unit_get_factor
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|>=
name|UNIT_PIXEL
operator|)
operator|&&
operator|(
name|unit
operator|<
name|UNIT_END
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|UNIT_INCH
index|]
operator|.
name|factor
argument_list|)
expr_stmt|;
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
DECL|function|gimp_unit_get_digits (GUnit unit)
name|gimp_unit_get_digits
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|>=
name|UNIT_PIXEL
operator|)
operator|&&
operator|(
name|unit
operator|<
name|UNIT_END
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|UNIT_INCH
index|]
operator|.
name|digits
argument_list|)
expr_stmt|;
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
DECL|function|gimp_unit_get_symbol (GUnit unit)
name|gimp_unit_get_symbol
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|>=
name|UNIT_PIXEL
operator|)
operator|&&
operator|(
name|unit
operator|<
name|UNIT_END
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|UNIT_INCH
index|]
operator|.
name|symbol
argument_list|)
expr_stmt|;
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
DECL|function|gimp_unit_get_abbreviation (GUnit unit)
name|gimp_unit_get_abbreviation
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|>=
name|UNIT_PIXEL
operator|)
operator|&&
operator|(
name|unit
operator|<
name|UNIT_END
operator|)
argument_list|,
name|gimp_unit_defs
index|[
name|UNIT_INCH
index|]
operator|.
name|abbreviation
argument_list|)
expr_stmt|;
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
DECL|function|gimp_unit_get_singular (GUnit unit)
name|gimp_unit_get_singular
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|>=
name|UNIT_PIXEL
operator|)
operator|&&
operator|(
name|unit
operator|<
name|UNIT_END
operator|)
argument_list|,
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|UNIT_INCH
index|]
operator|.
name|singular
argument_list|)
argument_list|)
expr_stmt|;
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
DECL|function|gimp_unit_get_plural (GUnit unit)
name|gimp_unit_get_plural
parameter_list|(
name|GUnit
name|unit
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
operator|(
name|unit
operator|>=
name|UNIT_PIXEL
operator|)
operator|&&
operator|(
name|unit
operator|<
name|UNIT_END
operator|)
argument_list|,
name|gettext
argument_list|(
name|gimp_unit_defs
index|[
name|UNIT_INCH
index|]
operator|.
name|plural
argument_list|)
argument_list|)
expr_stmt|;
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

