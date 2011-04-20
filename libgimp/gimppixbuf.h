begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppixbuf.h  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b264c910103
block|{
DECL|enumerator|GIMP_PIXBUF_KEEP_ALPHA
name|GIMP_PIXBUF_KEEP_ALPHA
block|,
DECL|enumerator|GIMP_PIXBUF_SMALL_CHECKS
name|GIMP_PIXBUF_SMALL_CHECKS
block|,
DECL|enumerator|GIMP_PIXBUF_LARGE_CHECKS
name|GIMP_PIXBUF_LARGE_CHECKS
DECL|typedef|GimpPixbufTransparency
block|}
name|GimpPixbufTransparency
typedef|;
end_typedef

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_image_get_thumbnail
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_drawable_get_thumbnail
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_drawable_get_sub_thumbnail
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
name|src_width
parameter_list|,
name|gint
name|src_height
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
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

