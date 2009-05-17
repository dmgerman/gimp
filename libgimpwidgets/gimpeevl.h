begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpeevl.h  * Copyright (C) 2008-2009 Fredrik Alstromer<roe@excu.se>  * Copyright (C) 2008-2009 Martin Nordholts<martinn@svn.gnome.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EEVL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EEVL_H__
define|#
directive|define
name|__GIMP_EEVL_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/**  * GimpEevlQuantity:  * @value:     In reference units.  * @dimension: in has a dimension of 1, in^2 has a dimension of 2 etc  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8372ff0108
block|{
DECL|member|value
name|gdouble
name|value
decl_stmt|;
DECL|member|dimension
name|gint
name|dimension
decl_stmt|;
DECL|typedef|GimpEevlQuantity
block|}
name|GimpEevlQuantity
typedef|;
end_typedef

begin_comment
comment|/**  * GimpEevlUnitResolverProc:  * @identifier: Identifier of unit to resolve or %NULL if default unit  *              should be resolved.  * @result:     Units per reference unit. For example, in GIMP the  *              reference unit is inches so resolving "mm" should  *              return 25.4 since there are 25.4 millimeters per inch.  * @data:       Data given to gimp_eevl_evaluate().  *  * Returns: If the unit was successfully resolved or not.  *  */
end_comment

begin_typedef
DECL|typedef|GimpEevlUnitResolverProc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpEevlUnitResolverProc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|GimpEevlQuantity
modifier|*
name|result
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|gboolean
name|gimp_eevl_evaluate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|GimpEevlUnitResolverProc
name|unit_resolver_proc
parameter_list|,
name|GimpEevlQuantity
modifier|*
name|result
parameter_list|,
name|gpointer
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|error_pos
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
comment|/* __GIMP_EEVL_H__ */
end_comment

end_unit

