begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpmatrix.h  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPMATRIX_H__
end_ifndef

begin_define
DECL|macro|__GIMPMATRIX_H__
define|#
directive|define
name|__GIMPMATRIX_H__
end_define

begin_typedef
DECL|typedef|GimpMatrix
typedef|typedef
name|double
name|GimpMatrix
index|[
literal|3
index|]
index|[
literal|3
index|]
typedef|;
end_typedef

begin_function_decl
name|void
name|gimp_matrix_transform_point
parameter_list|(
specifier|const
name|GimpMatrix
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|,
name|double
modifier|*
parameter_list|,
name|double
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_mult
parameter_list|(
specifier|const
name|GimpMatrix
parameter_list|,
name|GimpMatrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_identity
parameter_list|(
name|GimpMatrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_translate
parameter_list|(
name|GimpMatrix
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_scale
parameter_list|(
name|GimpMatrix
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_rotate
parameter_list|(
name|GimpMatrix
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_xshear
parameter_list|(
name|GimpMatrix
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_yshear
parameter_list|(
name|GimpMatrix
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|double
name|gimp_matrix_determinant
parameter_list|(
specifier|const
name|GimpMatrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix_invert
parameter_list|(
specifier|const
name|GimpMatrix
name|m
parameter_list|,
name|GimpMatrix
name|m_inv
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMPMATRIX_H__  */
end_comment

end_unit

