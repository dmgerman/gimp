begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BASE_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BASE_TYPES_H__
define|#
directive|define
name|__GIMP_BASE_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolortypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpmathtypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpbase/gimpbaseenums.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpParasite
typedef|typedef
name|struct
name|_GimpParasite
name|GimpParasite
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDatafileData
typedef|typedef
name|struct
name|_GimpDatafileData
name|GimpDatafileData
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDatafileLoaderFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDatafileLoaderFunc
function_decl|)
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_type_set_translation_domain
parameter_list|(
name|GType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_type_get_translation_domain
parameter_list|(
name|GType
name|type
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
comment|/* __GIMP_BASE_TYPES_H__ */
end_comment

end_unit

