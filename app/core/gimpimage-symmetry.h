begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimage-symmetry.h  * Copyright (C) 2015 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_SYMMETRY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_SYMMETRY_H__
define|#
directive|define
name|__GIMP_IMAGE_SYMMETRY_H__
end_define

begin_function_decl
name|GList
modifier|*
name|gimp_image_symmetry_list
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSymmetry
modifier|*
name|gimp_image_symmetry_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_symmetry_add
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_symmetry_remove
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_image_symmetry_get
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_set_active_symmetry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSymmetry
modifier|*
name|gimp_image_get_active_symmetry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_IMAGE_SYMMETRY_H__  */
end_comment

end_unit

