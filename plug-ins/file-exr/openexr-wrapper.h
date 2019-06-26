begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__OPENEXR_WRAPPER_H__
end_ifndef

begin_define
DECL|macro|__OPENEXR_WRAPPER_H__
define|#
directive|define
name|__OPENEXR_WRAPPER_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* This is fully opaque on purpose, as the calling C code must not be  * exposed to more than this.  */
end_comment

begin_typedef
DECL|typedef|EXRLoader
typedef|typedef
name|struct
name|_EXRLoader
name|EXRLoader
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b5d5f9c0103
block|{
DECL|enumerator|PREC_UINT
name|PREC_UINT
block|,
DECL|enumerator|PREC_HALF
name|PREC_HALF
block|,
DECL|enumerator|PREC_FLOAT
name|PREC_FLOAT
DECL|typedef|EXRPrecision
block|}
name|EXRPrecision
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b5d5f9c0203
block|{
DECL|enumerator|IMAGE_TYPE_RGB
name|IMAGE_TYPE_RGB
block|,
DECL|enumerator|IMAGE_TYPE_GRAY
name|IMAGE_TYPE_GRAY
DECL|typedef|EXRImageType
block|}
name|EXRImageType
typedef|;
end_typedef

begin_function_decl
name|EXRLoader
modifier|*
name|exr_loader_new
parameter_list|(
specifier|const
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|EXRLoader
modifier|*
name|exr_loader_ref
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|exr_loader_unref
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|exr_loader_get_width
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|exr_loader_get_height
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|EXRPrecision
name|exr_loader_get_precision
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|EXRImageType
name|exr_loader_get_image_type
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|exr_loader_has_alpha
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|exr_loader_get_profile
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|exr_loader_get_comment
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|exr_loader_get_exif
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|,
name|guint
modifier|*
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|exr_loader_get_xmp
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|,
name|guint
modifier|*
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|exr_loader_read_pixel_row
parameter_list|(
name|EXRLoader
modifier|*
name|loader
parameter_list|,
name|char
modifier|*
name|pixels
parameter_list|,
name|int
name|bpp
parameter_list|,
name|int
name|row
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
comment|/* __OPENEXR_WRAPPER_H__ */
end_comment

end_unit

