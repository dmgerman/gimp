begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmathtypes.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MATH_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MATH_TYPES_H__
define|#
directive|define
name|__GIMP_MATH_TYPES_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpMatrix2
typedef|typedef
name|struct
name|_GimpMatrix2
name|GimpMatrix2
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMatrix3
typedef|typedef
name|struct
name|_GimpMatrix3
name|GimpMatrix3
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMatrix4
typedef|typedef
name|struct
name|_GimpMatrix4
name|GimpMatrix4
typedef|;
end_typedef

begin_comment
comment|/**  * GimpMatrix2  * @coeff: the coefficients  *  * A two by two matrix.  **/
end_comment

begin_struct
DECL|struct|_GimpMatrix2
struct|struct
name|_GimpMatrix2
block|{
DECL|member|coeff
name|gdouble
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpMatrix3  * @coeff: the coefficients  *  * A three by three matrix.  **/
end_comment

begin_struct
DECL|struct|_GimpMatrix3
struct|struct
name|_GimpMatrix3
block|{
DECL|member|coeff
name|gdouble
name|coeff
index|[
literal|3
index|]
index|[
literal|3
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpMatrix4  * @coeff: the coefficients  *  * A four by four matrix.  **/
end_comment

begin_struct
DECL|struct|_GimpMatrix4
struct|struct
name|_GimpMatrix4
block|{
DECL|member|coeff
name|gdouble
name|coeff
index|[
literal|4
index|]
index|[
literal|4
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpVector2
typedef|typedef
name|struct
name|_GimpVector2
name|GimpVector2
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVector3
typedef|typedef
name|struct
name|_GimpVector3
name|GimpVector3
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVector4
typedef|typedef
name|struct
name|_GimpVector4
name|GimpVector4
typedef|;
end_typedef

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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MATH_TYPES_H__ */
end_comment

end_unit

