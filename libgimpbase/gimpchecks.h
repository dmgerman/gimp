begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_BASE_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_BASE_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpbase/gimpbase.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHECKS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHECKS_H__
define|#
directive|define
name|__GIMP_CHECKS_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/**  * GIMP_CHECK_SIZE:  *  * The default checkerboard size in pixels. This is configurable in  * the core but GIMP plug-ins can't access the user preference and  * should use this constant instead.  **/
DECL|macro|GIMP_CHECK_SIZE
define|#
directive|define
name|GIMP_CHECK_SIZE
value|8
comment|/**  * GIMP_CHECK_SIZE_SM:  *  * The default small checkerboard size in pixels.  **/
DECL|macro|GIMP_CHECK_SIZE_SM
define|#
directive|define
name|GIMP_CHECK_SIZE_SM
value|4
comment|/**  * GIMP_CHECK_DARK:  *  * The dark gray value for the default checkerboard pattern.  **/
DECL|macro|GIMP_CHECK_DARK
define|#
directive|define
name|GIMP_CHECK_DARK
value|0.4
comment|/**  * GIMP_CHECK_LIGHT:  *  * The dark light value for the default checkerboard pattern.  **/
DECL|macro|GIMP_CHECK_LIGHT
define|#
directive|define
name|GIMP_CHECK_LIGHT
value|0.6
name|void
name|gimp_checks_get_shades
parameter_list|(
name|GimpCheckType
name|type
parameter_list|,
name|guchar
modifier|*
name|light
parameter_list|,
name|guchar
modifier|*
name|dark
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
comment|/* __GIMP_CHECKS_H__ */
end_comment

end_unit

