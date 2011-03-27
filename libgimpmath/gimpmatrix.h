begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmatrix.h  * Copyright (C) 1998 Jay Cox<jaycox@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MATRIX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MATRIX_H__
define|#
directive|define
name|__GIMP_MATRIX_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

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

begin_comment
comment|/*****************/
end_comment

begin_comment
comment|/*  GimpMatrix2  */
end_comment

begin_comment
comment|/*****************/
end_comment

begin_define
DECL|macro|GIMP_TYPE_MATRIX2
define|#
directive|define
name|GIMP_TYPE_MATRIX2
value|(gimp_matrix2_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_MATRIX2 (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_MATRIX2
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_MATRIX2))
end_define

begin_decl_stmt
name|GType
name|gimp_matrix2_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_TYPE_PARAM_MATRIX2
define|#
directive|define
name|GIMP_TYPE_PARAM_MATRIX2
value|(gimp_param_matrix2_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_MATRIX2 (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_MATRIX2
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_MATRIX2))
end_define

begin_decl_stmt
name|GType
name|gimp_param_matrix2_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_matrix2
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|GimpMatrix2
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix2_identity
parameter_list|(
name|GimpMatrix2
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix2_mult
parameter_list|(
specifier|const
name|GimpMatrix2
modifier|*
name|matrix1
parameter_list|,
name|GimpMatrix2
modifier|*
name|matrix2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*****************/
end_comment

begin_comment
comment|/*  GimpMatrix3  */
end_comment

begin_comment
comment|/*****************/
end_comment

begin_define
DECL|macro|GIMP_TYPE_MATRIX3
define|#
directive|define
name|GIMP_TYPE_MATRIX3
value|(gimp_matrix3_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_MATRIX3 (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_MATRIX3
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_MATRIX3))
end_define

begin_decl_stmt
name|GType
name|gimp_matrix3_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_TYPE_PARAM_MATRIX3
define|#
directive|define
name|GIMP_TYPE_PARAM_MATRIX3
value|(gimp_param_matrix3_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_MATRIX3 (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_MATRIX3
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_MATRIX3))
end_define

begin_decl_stmt
name|GType
name|gimp_param_matrix3_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_matrix3
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_identity
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_mult
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix1
parameter_list|,
name|GimpMatrix3
modifier|*
name|matrix2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_translate
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
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
name|void
name|gimp_matrix3_scale
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
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
name|void
name|gimp_matrix3_rotate
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|theta
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_xshear
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|amount
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_yshear
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|amount
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_affine
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|a
parameter_list|,
name|gdouble
name|b
parameter_list|,
name|gdouble
name|c
parameter_list|,
name|gdouble
name|d
parameter_list|,
name|gdouble
name|e
parameter_list|,
name|gdouble
name|f
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_matrix3_determinant
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_invert
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_matrix3_is_identity
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_matrix3_is_diagonal
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_matrix3_is_affine
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_matrix3_is_simple
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_matrix3_transform_point
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|newx
parameter_list|,
name|gdouble
modifier|*
name|newy
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*****************/
end_comment

begin_comment
comment|/*  GimpMatrix4  */
end_comment

begin_comment
comment|/*****************/
end_comment

begin_function_decl
name|void
name|gimp_matrix4_to_deg
parameter_list|(
specifier|const
name|GimpMatrix4
modifier|*
name|matrix
parameter_list|,
name|gdouble
modifier|*
name|a
parameter_list|,
name|gdouble
modifier|*
name|b
parameter_list|,
name|gdouble
modifier|*
name|c
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
comment|/* __GIMP_MATRIX_H__ */
end_comment

end_unit

