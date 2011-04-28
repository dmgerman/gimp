begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_THUMB_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_THUMB_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpthumb/gimpthumb.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THUMB_ERROR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THUMB_ERROR_H__
define|#
directive|define
name|__GIMP_THUMB_ERROR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/**  * GimpThumbError:  * @GIMP_THUMB_ERROR_OPEN:         there was a problem opening the file  * @GIMP_THUMB_ERROR_OPEN_ENOENT:  the file doesn't exist  * @GIMP_THUMB_ERROR_MKDIR:        there was a problem creating a directory  *  * These are the possible error codes used when a #GError is set by  * libgimpthumb.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c122e550103
block|{
DECL|enumerator|GIMP_THUMB_ERROR_OPEN
name|GIMP_THUMB_ERROR_OPEN
block|,
DECL|enumerator|GIMP_THUMB_ERROR_OPEN_ENOENT
name|GIMP_THUMB_ERROR_OPEN_ENOENT
block|,
DECL|enumerator|GIMP_THUMB_ERROR_MKDIR
name|GIMP_THUMB_ERROR_MKDIR
DECL|typedef|GimpThumbError
block|}
name|GimpThumbError
typedef|;
end_typedef

begin_comment
comment|/**  * GIMP_THUMB_ERROR:  *  * Identifier for the libgimpthumb error domain.  **/
end_comment

begin_define
DECL|macro|GIMP_THUMB_ERROR
define|#
directive|define
name|GIMP_THUMB_ERROR
value|(gimp_thumb_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_thumb_error_quark
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
comment|/* __GIMP_THUMB_ERROR_H__ */
end_comment

end_unit

