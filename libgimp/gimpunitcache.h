begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpunitcache.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UNIT_CACHE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNIT_CACHE_H__
define|#
directive|define
name|__GIMP_UNIT_CACHE_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
name|G_GNUC_INTERNAL
name|gint
name|_gimp_unit_cache_get_number_of_units
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|G_GNUC_INTERNAL
name|gint
name|_gimp_unit_cache_get_number_of_built_in_units
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|G_GNUC_INTERNAL
name|GimpUnit
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
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gboolean
name|_gimp_unit_cache_get_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|void
name|_gimp_unit_cache_set_deletion_flag
parameter_list|(
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gdouble
name|_gimp_unit_cache_get_factor
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gint
name|_gimp_unit_cache_get_digits
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
specifier|const
name|gchar
modifier|*
name|_gimp_unit_cache_get_identifier
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
specifier|const
name|gchar
modifier|*
name|_gimp_unit_cache_get_symbol
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
specifier|const
name|gchar
modifier|*
name|_gimp_unit_cache_get_abbreviation
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
specifier|const
name|gchar
modifier|*
name|_gimp_unit_cache_get_singular
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
specifier|const
name|gchar
modifier|*
name|_gimp_unit_cache_get_plural
parameter_list|(
name|GimpUnit
name|unit
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
comment|/*  __GIMP_UNIT_CACHE_H__ */
end_comment

end_unit

