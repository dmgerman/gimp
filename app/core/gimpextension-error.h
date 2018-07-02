begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpextension-error.h  * Copyright (C) 2018 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EXTENSION_ERROR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EXTENSION_ERROR_H__
define|#
directive|define
name|__GIMP_EXTENSION_ERROR_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a2c306f0103
block|{
comment|/* Generic error condition. */
DECL|enumerator|GIMP_EXTENSION_FAILED
name|GIMP_EXTENSION_FAILED
block|,
DECL|enumerator|GIMP_EXTENSION_BAD_APPDATA
name|GIMP_EXTENSION_BAD_APPDATA
block|,
DECL|enumerator|GIMP_EXTENSION_BAD_ID
name|GIMP_EXTENSION_BAD_ID
block|,
DECL|enumerator|GIMP_EXTENSION_NO_VERSION
name|GIMP_EXTENSION_NO_VERSION
block|,
DECL|enumerator|GIMP_EXTENSION_BAD_PATH
name|GIMP_EXTENSION_BAD_PATH
DECL|typedef|GimpExtensionErrorCode
block|}
name|GimpExtensionErrorCode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_EXTENSION_ERROR
define|#
directive|define
name|GIMP_EXTENSION_ERROR
value|(gimp_extension_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_extension_error_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_EXTENSION_ERROR_H__ */
end_comment

end_unit

