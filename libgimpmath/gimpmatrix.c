begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmatrix.c  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimpmath.h"
end_include

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|1e-6
end_define

begin_comment
comment|/**  * gimp_matrix2_identity:  * @matrix: A matrix.  *   * Sets the matrix to the identity matrix.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix2_identity (GimpMatrix2 * matrix)
name|gimp_matrix2_identity
parameter_list|(
name|GimpMatrix2
modifier|*
name|matrix
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpMatrix2
name|identity
init|=
block|{
block|{
block|{
literal|1.0
block|,
literal|0.0
block|}
block|,
block|{
literal|0.0
block|,
literal|1.0
block|}
block|}
block|}
decl_stmt|;
operator|*
name|matrix
operator|=
name|identity
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_transform_point:  * @matrix: The transformation matrix.  * @x: The source X coordinate.  * @y: The source Y coordinate.  * @newx: The transformed X coordinate.  * @newy: The transformed Y coordinate.  *   * Transforms a point in 2D as specified by the transformation matrix.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_transform_point (const GimpMatrix3 * matrix,gdouble x,gdouble y,gdouble * newx,gdouble * newy)
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
block|{
name|gdouble
name|w
decl_stmt|;
name|w
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|x
operator|+
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|y
operator|+
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|w
operator|==
literal|0.0
condition|)
name|w
operator|=
literal|1.0
expr_stmt|;
else|else
name|w
operator|=
literal|1.0
operator|/
name|w
expr_stmt|;
operator|*
name|newx
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|x
operator|+
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|y
operator|+
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|)
operator|*
name|w
expr_stmt|;
operator|*
name|newy
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
name|x
operator|+
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|y
operator|+
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|)
operator|*
name|w
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_mult:  * @matrix1: The first input matrix.  * @matrix2: The second input matrix which will be oeverwritten by the result.  *   * Multiplies two matrices and puts the result into the second one.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_mult (const GimpMatrix3 * matrix1,GimpMatrix3 * matrix2)
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
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|GimpMatrix3
name|tmp
decl_stmt|;
name|gdouble
name|t1
decl_stmt|,
name|t2
decl_stmt|,
name|t3
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
name|t1
operator|=
name|matrix1
operator|->
name|coeff
index|[
name|i
index|]
index|[
literal|0
index|]
expr_stmt|;
name|t2
operator|=
name|matrix1
operator|->
name|coeff
index|[
name|i
index|]
index|[
literal|1
index|]
expr_stmt|;
name|t3
operator|=
name|matrix1
operator|->
name|coeff
index|[
name|i
index|]
index|[
literal|2
index|]
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
block|{
name|tmp
operator|.
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
operator|=
name|t1
operator|*
name|matrix2
operator|->
name|coeff
index|[
literal|0
index|]
index|[
name|j
index|]
expr_stmt|;
name|tmp
operator|.
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
operator|+=
name|t2
operator|*
name|matrix2
operator|->
name|coeff
index|[
literal|1
index|]
index|[
name|j
index|]
expr_stmt|;
name|tmp
operator|.
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
operator|+=
name|t3
operator|*
name|matrix2
operator|->
name|coeff
index|[
literal|2
index|]
index|[
name|j
index|]
expr_stmt|;
block|}
block|}
operator|*
name|matrix2
operator|=
name|tmp
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_identity:  * @matrix: A matrix.  *   * Sets the matrix to the identity matrix.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_identity (GimpMatrix3 * matrix)
name|gimp_matrix3_identity
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpMatrix3
name|identity
init|=
block|{
block|{
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|0.0
block|}
block|,
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|0.0
block|}
block|,
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|}
block|}
decl_stmt|;
operator|*
name|matrix
operator|=
name|identity
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_translate:  * @matrix: The matrix that is to be translated.  * @x: Translation in X direction.  * @y: Translation in Y direction.  *   * Translates the matrix by x and y.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_translate (GimpMatrix3 * matrix,gdouble x,gdouble y)
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
block|{
name|gdouble
name|g
decl_stmt|,
name|h
decl_stmt|,
name|i
decl_stmt|;
name|g
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
expr_stmt|;
name|h
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
expr_stmt|;
name|i
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|+=
name|x
operator|*
name|g
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|+=
name|x
operator|*
name|h
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|+=
name|x
operator|*
name|i
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|+=
name|y
operator|*
name|g
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|+=
name|y
operator|*
name|h
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|+=
name|y
operator|*
name|i
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_scale:  * @matrix: The matrix that is to be scaled.  * @x: X scale factor.  * @y: Y scale factor.  *   * Scales the matrix by x and y   */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_scale (GimpMatrix3 * matrix,gdouble x,gdouble y)
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
block|{
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*=
name|x
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*=
name|x
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*=
name|x
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*=
name|y
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*=
name|y
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|*=
name|y
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_rotate:  * @matrix: The matrix that is to be rotated.  * @theta: The angle of rotation (in radians).  *   * Rotates the matrix by theta degrees.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_rotate (GimpMatrix3 * matrix,gdouble theta)
name|gimp_matrix3_rotate
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|theta
parameter_list|)
block|{
name|gdouble
name|t1
decl_stmt|,
name|t2
decl_stmt|;
name|gdouble
name|cost
decl_stmt|,
name|sint
decl_stmt|;
name|cost
operator|=
name|cos
argument_list|(
name|theta
argument_list|)
expr_stmt|;
name|sint
operator|=
name|sin
argument_list|(
name|theta
argument_list|)
expr_stmt|;
name|t1
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|t2
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|cost
operator|*
name|t1
operator|-
name|sint
operator|*
name|t2
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|sint
operator|*
name|t1
operator|+
name|cost
operator|*
name|t2
expr_stmt|;
name|t1
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
name|t2
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|cost
operator|*
name|t1
operator|-
name|sint
operator|*
name|t2
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|sint
operator|*
name|t1
operator|+
name|cost
operator|*
name|t2
expr_stmt|;
name|t1
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
name|t2
operator|=
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|cost
operator|*
name|t1
operator|-
name|sint
operator|*
name|t2
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|sint
operator|*
name|t1
operator|+
name|cost
operator|*
name|t2
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_xshear:  * @matrix: The matrix that is to be sheared.  * @amount: X shear amount.  *   * Shears the matrix in the X direction.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_xshear (GimpMatrix3 * matrix,gdouble amount)
name|gimp_matrix3_xshear
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|amount
parameter_list|)
block|{
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|+=
name|amount
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|+=
name|amount
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|+=
name|amount
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_yshear:  * @matrix: The matrix that is to be sheared.  * @amount: Y shear amount.  *   * Shears the matrix in the Y direction.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_yshear (GimpMatrix3 * matrix,gdouble amount)
name|gimp_matrix3_yshear
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|amount
parameter_list|)
block|{
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|+=
name|amount
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|+=
name|amount
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|+=
name|amount
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_determinant:  * @matrix: The input matrix.   *   * Calculates the determinant of the given matrix.  *   * Returns: The determinant.  */
end_comment

begin_function
name|gdouble
DECL|function|gimp_matrix3_determinant (const GimpMatrix3 * matrix)
name|gimp_matrix3_determinant
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
name|gdouble
name|determinant
decl_stmt|;
name|determinant
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
operator|)
expr_stmt|;
name|determinant
operator|-=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
operator|)
expr_stmt|;
name|determinant
operator|+=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|)
operator|)
expr_stmt|;
return|return
name|determinant
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_invert:  * @matrix: The matrix that is to be inverted.  *   * Inverts the given matrix.  */
end_comment

begin_function
name|void
DECL|function|gimp_matrix3_invert (GimpMatrix3 * matrix)
name|gimp_matrix3_invert
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
name|GimpMatrix3
name|inv
decl_stmt|;
name|gdouble
name|det
decl_stmt|;
name|det
operator|=
name|gimp_matrix3_determinant
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
if|if
condition|(
name|det
operator|==
literal|0.0
condition|)
return|return;
name|det
operator|=
literal|1.0
operator|/
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
operator|-
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
operator|-
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
operator|-
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
operator|-
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det
expr_stmt|;
name|inv
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
operator|(
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|-
name|matrix
operator|->
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det
expr_stmt|;
operator|*
name|matrix
operator|=
name|inv
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  functions to test for matrix properties  */
end_comment

begin_comment
comment|/**  * gimp_matrix3_is_diagonal:  * @matrix: The matrix that is to be tested.  *   * Checks if the given matrix is diagonal.  *   * Returns: TRUE if the matrix is diagonal.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_matrix3_is_diagonal (const GimpMatrix3 * matrix)
name|gimp_matrix3_is_diagonal
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|!=
name|j
operator|&&
name|fabs
argument_list|(
name|matrix
operator|->
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
operator|>
name|EPSILON
condition|)
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_matrix3_is_identity:  * @matrix: The matrix that is to be tested.  *   * Checks if the given matrix is the identity matrix.  *   * Returns: TRUE if the matrix is the identity matrix.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_matrix3_is_identity (const GimpMatrix3 * matrix)
name|gimp_matrix3_is_identity
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|==
name|j
condition|)
block|{
if|if
condition|(
name|fabs
argument_list|(
name|matrix
operator|->
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
operator|-
literal|1.0
argument_list|)
operator|>
name|EPSILON
condition|)
return|return
name|FALSE
return|;
block|}
else|else
block|{
if|if
condition|(
name|fabs
argument_list|(
name|matrix
operator|->
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
operator|>
name|EPSILON
condition|)
return|return
name|FALSE
return|;
block|}
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  Check if we'll need to interpolate when applying this matrix.      This function returns TRUE if all entries of the upper left      2x2 matrix are either 0 or 1   */
end_comment

begin_comment
comment|/**  * gimp_matrix3_is_simple:  * @matrix: The matrix that is to be tested.  *   * Checks if we'll need to interpolate when applying this matrix as  * a transformation.  *   * Returns: TRUE if all entries of the upper left 2x2 matrix are either   * 0 or 1  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_matrix3_is_simple (const GimpMatrix3 * matrix)
name|gimp_matrix3_is_simple
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|)
block|{
name|gdouble
name|absm
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|2
condition|;
name|j
operator|++
control|)
block|{
name|absm
operator|=
name|fabs
argument_list|(
name|matrix
operator|->
name|coeff
index|[
name|i
index|]
index|[
name|j
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|absm
operator|>
name|EPSILON
operator|&&
name|fabs
argument_list|(
name|absm
operator|-
literal|1.0
argument_list|)
operator|>
name|EPSILON
condition|)
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_matrix4_to_deg (const GimpMatrix4 * matrix,gdouble * a,gdouble * b,gdouble * c)
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
block|{
operator|*
name|a
operator|=
literal|180
operator|*
operator|(
name|asin
argument_list|(
name|matrix
operator|->
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
argument_list|)
operator|/
name|G_PI_2
operator|)
expr_stmt|;
operator|*
name|b
operator|=
literal|180
operator|*
operator|(
name|asin
argument_list|(
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
argument_list|)
operator|/
name|G_PI_2
operator|)
expr_stmt|;
operator|*
name|c
operator|=
literal|180
operator|*
operator|(
name|asin
argument_list|(
name|matrix
operator|->
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
argument_list|)
operator|/
name|G_PI_2
operator|)
expr_stmt|;
block|}
end_function

end_unit

