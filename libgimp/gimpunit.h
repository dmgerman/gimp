begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball   *  * gimpunit.h  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE:  *  * This file serves as header for both app/gimpunit.c and libgimp/gimpunit.c  * because the unit functions are needed by widgets which are used by both  * the gimp app and plugins.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPUNIT_H__
end_ifndef

begin_define
DECL|macro|__GIMPUNIT_H__
define|#
directive|define
name|__GIMPUNIT_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
typedef|typedef
enum|enum
DECL|enum|__anon28ee48820103
block|{
DECL|enumerator|GIMP_UNIT_PIXEL
name|GIMP_UNIT_PIXEL
init|=
literal|0
block|,
DECL|enumerator|GIMP_UNIT_INCH
name|GIMP_UNIT_INCH
init|=
literal|1
block|,
DECL|enumerator|GIMP_UNIT_MM
name|GIMP_UNIT_MM
init|=
literal|2
block|,
DECL|enumerator|GIMP_UNIT_POINT
name|GIMP_UNIT_POINT
init|=
literal|3
block|,
DECL|enumerator|GIMP_UNIT_PICA
name|GIMP_UNIT_PICA
init|=
literal|4
block|,
DECL|enumerator|GIMP_UNIT_END
name|GIMP_UNIT_END
init|=
literal|5
block|,
DECL|enumerator|GIMP_UNIT_PERCENT
name|GIMP_UNIT_PERCENT
init|=
literal|65536
DECL|typedef|GimpUnit
block|}
name|GimpUnit
typedef|;
comment|/* For information look into the C source or the html documentation */
name|gint
name|gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|gint
name|gimp_unit_get_number_of_built_in_units
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GimpUnit
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
function_decl|;
name|gboolean
name|gimp_unit_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|void
name|gimp_unit_set_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
function_decl|;
name|gdouble
name|gimp_unit_get_factor
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|gint
name|gimp_unit_get_digits
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_identifier
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_symbol
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_abbreviation
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_singular
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_unit_get_plural
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMPUNIT_H__  */
end_comment

end_unit

