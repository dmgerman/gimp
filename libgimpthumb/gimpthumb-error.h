begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon290a97830103
block|{
DECL|enumerator|GIMP_THUMB_ERROR_OPEN
name|GIMP_THUMB_ERROR_OPEN
block|,
comment|/*  open failed                            */
DECL|enumerator|GIMP_THUMB_ERROR_OPEN_ENOENT
name|GIMP_THUMB_ERROR_OPEN_ENOENT
block|,
comment|/*  file does not exist                    */
DECL|enumerator|GIMP_THUMB_ERROR_MKDIR
name|GIMP_THUMB_ERROR_MKDIR
comment|/*  mkdir failed                           */
DECL|typedef|GimpThumbError
block|}
name|GimpThumbError
typedef|;
end_typedef

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_THUMB_ERROR_H__ */
end_comment

end_unit

