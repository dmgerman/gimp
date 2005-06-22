begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2892963b0103
block|{
DECL|enumerator|GIMP_CONFIG_ERROR_OPEN
name|GIMP_CONFIG_ERROR_OPEN
block|,
comment|/*  open failed                            */
DECL|enumerator|GIMP_CONFIG_ERROR_OPEN_ENOENT
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
block|,
comment|/*  file does not exist                    */
DECL|enumerator|GIMP_CONFIG_ERROR_WRITE
name|GIMP_CONFIG_ERROR_WRITE
block|,
comment|/*  write failed                           */
DECL|enumerator|GIMP_CONFIG_ERROR_PARSE
name|GIMP_CONFIG_ERROR_PARSE
block|,
comment|/*  parser error                           */
DECL|enumerator|GIMP_CONFIG_ERROR_VERSION
name|GIMP_CONFIG_ERROR_VERSION
comment|/*  parser failed due to version mismatch  */
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

