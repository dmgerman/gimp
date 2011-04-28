begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_CONFIG_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_CONFIG_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpconfig/gimpconfig.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_ERROR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_ERROR_H__
define|#
directive|define
name|__GIMP_CONFIG_ERROR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * GimpConfigError:  * @GIMP_CONFIG_ERROR_OPEN:        open failed  * @GIMP_CONFIG_ERROR_OPEN_ENOENT: file does not exist  * @GIMP_CONFIG_ERROR_WRITE:       write failed  * @GIMP_CONFIG_ERROR_PARSE:       parser error  * @GIMP_CONFIG_ERROR_VERSION:     parser failed due to version mismatch  *  * The possible values of a #GError thrown by libgimpconfig.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b769f480103
block|{
DECL|enumerator|GIMP_CONFIG_ERROR_OPEN
name|GIMP_CONFIG_ERROR_OPEN
block|,
DECL|enumerator|GIMP_CONFIG_ERROR_OPEN_ENOENT
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
block|,
DECL|enumerator|GIMP_CONFIG_ERROR_WRITE
name|GIMP_CONFIG_ERROR_WRITE
block|,
DECL|enumerator|GIMP_CONFIG_ERROR_PARSE
name|GIMP_CONFIG_ERROR_PARSE
block|,
DECL|enumerator|GIMP_CONFIG_ERROR_VERSION
name|GIMP_CONFIG_ERROR_VERSION
DECL|typedef|GimpConfigError
block|}
name|GimpConfigError
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_CONFIG_ERROR
define|#
directive|define
name|GIMP_CONFIG_ERROR
value|(gimp_config_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_config_error_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_ERROR_H__ */
end_comment

end_unit

