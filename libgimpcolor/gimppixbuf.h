begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppixbuf.h  * Copyright (C) 2012  Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_COLOR_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COLOR_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpcolor/gimpcolor.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PIXBUF_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PIXBUF_H__
define|#
directive|define
name|__GIMP_PIXBUF_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
specifier|const
name|Babl
modifier|*
name|gimp_pixbuf_get_format
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_pixbuf_create_buffer
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint8
modifier|*
name|gimp_pixbuf_get_icc_profile
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gsize
modifier|*
name|length
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
comment|/* __GIMP_PIXBUF_H__ */
end_comment

end_unit

