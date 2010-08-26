begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpvector.h  *  * The gimp_vector* functions were taken from:  * GCK - The General Convenience Kit  * Copyright (C) 1996 Tom Bech  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTOR_H__
define|#
directive|define
name|__GIMP_VECTOR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * GimpVector2:  * @x: the x axis  * @y: the y axis  *  * A two dimensional vector.  **/
end_comment

begin_struct
DECL|struct|_GimpVector2
struct|struct
name|_GimpVector2
block|{
DECL|member|x
DECL|member|y
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpVector3:  * @x: the x axis  * @y: the y axis  * @z: the z axis  *  * A three dimensional vector.  **/
end_comment

begin_struct
DECL|struct|_GimpVector3
struct|struct
name|_GimpVector3
block|{
DECL|member|x
DECL|member|y
DECL|member|z
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|,
name|z
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpVector4:  * @x: the x axis  * @y: the y axis  * @z: the z axis  * @w: the w axis  *  * A four dimensional vector.  **/
end_comment

begin_struct
DECL|struct|_GimpVector4
struct|struct
name|_GimpVector4
block|{
DECL|member|x
DECL|member|y
DECL|member|z
DECL|member|w
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|,
name|z
decl_stmt|,
name|w
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Two dimensional vector functions */
end_comment

begin_comment
comment|/* ================================ */
end_comment

begin_function_decl
name|GimpVector2
name|gimp_vector2_new
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector2_set
parameter_list|(
name|GimpVector2
modifier|*
name|vector
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector2_length
parameter_list|(
specifier|const
name|GimpVector2
modifier|*
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector2_length_val
parameter_list|(
name|GimpVector2
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector2_mul
parameter_list|(
name|GimpVector2
modifier|*
name|vector
parameter_list|,
name|gdouble
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_mul_val
parameter_list|(
name|GimpVector2
name|vector
parameter_list|,
name|gdouble
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector2_normalize
parameter_list|(
name|GimpVector2
modifier|*
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_normalize_val
parameter_list|(
name|GimpVector2
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector2_neg
parameter_list|(
name|GimpVector2
modifier|*
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_neg_val
parameter_list|(
name|GimpVector2
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector2_add
parameter_list|(
name|GimpVector2
modifier|*
name|result
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_add_val
parameter_list|(
name|GimpVector2
name|vector1
parameter_list|,
name|GimpVector2
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector2_sub
parameter_list|(
name|GimpVector2
modifier|*
name|result
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_sub_val
parameter_list|(
name|GimpVector2
name|vector1
parameter_list|,
name|GimpVector2
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector2_inner_product
parameter_list|(
specifier|const
name|GimpVector2
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector2_inner_product_val
parameter_list|(
name|GimpVector2
name|vector1
parameter_list|,
name|GimpVector2
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_cross_product
parameter_list|(
specifier|const
name|GimpVector2
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_cross_product_val
parameter_list|(
name|GimpVector2
name|vector1
parameter_list|,
name|GimpVector2
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector2_rotate
parameter_list|(
name|GimpVector2
modifier|*
name|vector
parameter_list|,
name|gdouble
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_rotate_val
parameter_list|(
name|GimpVector2
name|vector
parameter_list|,
name|gdouble
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_normal
parameter_list|(
name|GimpVector2
modifier|*
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector2
name|gimp_vector2_normal_val
parameter_list|(
name|GimpVector2
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Three dimensional vector functions */
end_comment

begin_comment
comment|/* ================================== */
end_comment

begin_function_decl
name|GimpVector3
name|gimp_vector3_new
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|z
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector3_set
parameter_list|(
name|GimpVector3
modifier|*
name|vector
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
name|z
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector3_length
parameter_list|(
specifier|const
name|GimpVector3
modifier|*
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector3_length_val
parameter_list|(
name|GimpVector3
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector3_mul
parameter_list|(
name|GimpVector3
modifier|*
name|vector
parameter_list|,
name|gdouble
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_mul_val
parameter_list|(
name|GimpVector3
name|vector
parameter_list|,
name|gdouble
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector3_normalize
parameter_list|(
name|GimpVector3
modifier|*
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_normalize_val
parameter_list|(
name|GimpVector3
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector3_neg
parameter_list|(
name|GimpVector3
modifier|*
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_neg_val
parameter_list|(
name|GimpVector3
name|vector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector3_add
parameter_list|(
name|GimpVector3
modifier|*
name|result
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_add_val
parameter_list|(
name|GimpVector3
name|vector1
parameter_list|,
name|GimpVector3
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector3_sub
parameter_list|(
name|GimpVector3
modifier|*
name|result
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_sub_val
parameter_list|(
name|GimpVector3
name|vector1
parameter_list|,
name|GimpVector3
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector3_inner_product
parameter_list|(
specifier|const
name|GimpVector3
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_vector3_inner_product_val
parameter_list|(
name|GimpVector3
name|vector1
parameter_list|,
name|GimpVector3
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_cross_product
parameter_list|(
specifier|const
name|GimpVector3
modifier|*
name|vector1
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_cross_product_val
parameter_list|(
name|GimpVector3
name|vector1
parameter_list|,
name|GimpVector3
name|vector2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector3_rotate
parameter_list|(
name|GimpVector3
modifier|*
name|vector
parameter_list|,
name|gdouble
name|alpha
parameter_list|,
name|gdouble
name|beta
parameter_list|,
name|gdouble
name|gamma
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector3_rotate_val
parameter_list|(
name|GimpVector3
name|vector
parameter_list|,
name|gdouble
name|alpha
parameter_list|,
name|gdouble
name|beta
parameter_list|,
name|gdouble
name|gamma
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* 2d<-> 3d Vector projection functions */
end_comment

begin_comment
comment|/* ===================================== */
end_comment

begin_function_decl
name|void
name|gimp_vector_2d_to_3d
parameter_list|(
name|gint
name|sx
parameter_list|,
name|gint
name|sy
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vp
parameter_list|,
name|GimpVector3
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpVector3
name|gimp_vector_2d_to_3d_val
parameter_list|(
name|gint
name|sx
parameter_list|,
name|gint
name|sy
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpVector3
name|vp
parameter_list|,
name|GimpVector3
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vector_3d_to_2d
parameter_list|(
name|gint
name|sx
parameter_list|,
name|gint
name|sy
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|vp
parameter_list|,
specifier|const
name|GimpVector3
modifier|*
name|p
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
comment|/* __GIMP_VECTOR_H__ */
end_comment

end_unit

