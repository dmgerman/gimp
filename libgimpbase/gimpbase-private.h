begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbase-private.h  * Copyright (C) 2003 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BASE_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BASE_PRIVATE_H__
define|#
directive|define
name|__GIMP_BASE_PRIVATE_H__
end_define

begin_typedef
DECL|typedef|GimpUnitVtable
typedef|typedef
name|struct
name|_GimpUnitVtable
name|GimpUnitVtable
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUnitVtable
struct|struct
name|_GimpUnitVtable
block|{
DECL|member|unit_get_number_of_units
name|gint
function_decl|(
modifier|*
name|unit_get_number_of_units
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|unit_get_number_of_built_in_units
name|gint
function_decl|(
modifier|*
name|unit_get_number_of_built_in_units
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|unit_new
name|GimpUnit
function_decl|(
modifier|*
name|unit_new
function_decl|)
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
DECL|member|unit_get_deletion_flag
name|gboolean
function_decl|(
modifier|*
name|unit_get_deletion_flag
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|unit_set_deletion_flag
name|void
function_decl|(
modifier|*
name|unit_set_deletion_flag
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
function_decl|;
DECL|member|unit_get_factor
name|gdouble
function_decl|(
modifier|*
name|unit_get_factor
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|unit_get_digits
name|gint
function_decl|(
modifier|*
name|unit_get_digits
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|unit_get_identifier
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|unit_get_identifier
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|unit_get_symbol
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|unit_get_symbol
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|unit_get_abbreviation
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|unit_get_abbreviation
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|unit_get_singular
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|unit_get_singular
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|unit_get_plural
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|unit_get_plural
function_decl|)
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
DECL|member|_reserved_1
name|void
function_decl|(
modifier|*
name|_reserved_1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_reserved_2
name|void
function_decl|(
modifier|*
name|_reserved_2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_reserved_3
name|void
function_decl|(
modifier|*
name|_reserved_3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_reserved_4
name|void
function_decl|(
modifier|*
name|_reserved_4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|GimpUnitVtable
name|_gimp_unit_vtable
decl_stmt|;
end_decl_stmt

begin_function_decl
name|G_BEGIN_DECLS
name|void
name|gimp_base_init
parameter_list|(
name|GimpUnitVtable
modifier|*
name|vtable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_base_compat_enums_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BASE_PRIVATE_H__ */
end_comment

end_unit

