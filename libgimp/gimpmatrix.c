begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpmatrix.c  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimpmatrix.h"
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_function
name|void
DECL|function|gimp_matrix_transform_point (GimpMatrix m,double x,double y,double * newx,double * newy)
name|gimp_matrix_transform_point
parameter_list|(
name|GimpMatrix
name|m
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|double
modifier|*
name|newx
parameter_list|,
name|double
modifier|*
name|newy
parameter_list|)
block|{
name|double
name|w
decl_stmt|;
name|w
operator|=
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|x
operator|+
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|y
operator|+
name|m
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
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|x
operator|+
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|y
operator|+
name|m
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
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
name|x
operator|+
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|y
operator|+
name|m
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

begin_function
name|void
DECL|function|gimp_matrix_mult (GimpMatrix m1,GimpMatrix m2)
name|gimp_matrix_mult
parameter_list|(
name|GimpMatrix
name|m1
parameter_list|,
name|GimpMatrix
name|m2
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|GimpMatrix
name|tmp
decl_stmt|;
name|double
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
name|m1
index|[
name|i
index|]
index|[
literal|0
index|]
expr_stmt|;
name|t2
operator|=
name|m1
index|[
name|i
index|]
index|[
literal|1
index|]
expr_stmt|;
name|t3
operator|=
name|m1
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
index|[
name|i
index|]
index|[
name|j
index|]
operator|=
name|t1
operator|*
name|m2
index|[
literal|0
index|]
index|[
name|j
index|]
expr_stmt|;
name|tmp
index|[
name|i
index|]
index|[
name|j
index|]
operator|+=
name|t2
operator|*
name|m2
index|[
literal|1
index|]
index|[
name|j
index|]
expr_stmt|;
name|tmp
index|[
name|i
index|]
index|[
name|j
index|]
operator|+=
name|t3
operator|*
name|m2
index|[
literal|2
index|]
index|[
name|j
index|]
expr_stmt|;
block|}
block|}
comment|/*  put the results in m2 */
name|memcpy
argument_list|(
operator|&
name|m2
index|[
literal|0
index|]
index|[
literal|0
index|]
argument_list|,
operator|&
name|tmp
index|[
literal|0
index|]
index|[
literal|0
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|double
argument_list|)
operator|*
literal|9
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_matrix_identity (GimpMatrix m)
name|gimp_matrix_identity
parameter_list|(
name|GimpMatrix
name|m
parameter_list|)
block|{
specifier|static
name|GimpMatrix
name|identity
init|=
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
decl_stmt|;
name|memcpy
argument_list|(
operator|&
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
argument_list|,
operator|&
name|identity
index|[
literal|0
index|]
index|[
literal|0
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|double
argument_list|)
operator|*
literal|9
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_matrix_translate (GimpMatrix m,double x,double y)
name|gimp_matrix_translate
parameter_list|(
name|GimpMatrix
name|m
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|)
block|{
name|double
name|g
decl_stmt|,
name|h
decl_stmt|,
name|i
decl_stmt|;
name|g
operator|=
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
expr_stmt|;
name|h
operator|=
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
expr_stmt|;
name|i
operator|=
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
expr_stmt|;
name|m
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
name|m
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
name|m
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
name|m
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
name|m
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
name|m
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

begin_function
name|void
DECL|function|gimp_matrix_scale (GimpMatrix m,double x,double y)
name|gimp_matrix_scale
parameter_list|(
name|GimpMatrix
name|m
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|)
block|{
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*=
name|x
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*=
name|x
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*=
name|x
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*=
name|y
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*=
name|y
expr_stmt|;
name|m
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

begin_function
name|void
DECL|function|gimp_matrix_rotate (GimpMatrix m,double theta)
name|gimp_matrix_rotate
parameter_list|(
name|GimpMatrix
name|m
parameter_list|,
name|double
name|theta
parameter_list|)
block|{
name|double
name|t1
decl_stmt|,
name|t2
decl_stmt|;
name|double
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
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|t2
operator|=
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
expr_stmt|;
name|m
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
name|m
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
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
name|t2
operator|=
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
expr_stmt|;
name|m
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
name|m
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
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
name|t2
operator|=
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
expr_stmt|;
name|m
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
name|m
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

begin_function
name|void
DECL|function|gimp_matrix_xshear (GimpMatrix m,double amnt)
name|gimp_matrix_xshear
parameter_list|(
name|GimpMatrix
name|m
parameter_list|,
name|double
name|amnt
parameter_list|)
block|{
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|+=
name|amnt
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|+=
name|amnt
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
expr_stmt|;
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|+=
name|amnt
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_matrix_yshear (GimpMatrix m,double amnt)
name|gimp_matrix_yshear
parameter_list|(
name|GimpMatrix
name|m
parameter_list|,
name|double
name|amnt
parameter_list|)
block|{
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|+=
name|amnt
operator|*
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|+=
name|amnt
operator|*
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
expr_stmt|;
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|+=
name|amnt
operator|*
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
end_function

begin_function
name|double
DECL|function|gimp_matrix_determinant (GimpMatrix m)
name|gimp_matrix_determinant
parameter_list|(
name|GimpMatrix
name|m
parameter_list|)
block|{
name|double
name|determinant
decl_stmt|;
name|determinant
operator|=
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
operator|(
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
expr_stmt|;
name|determinant
operator|-=
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
expr_stmt|;
name|determinant
operator|+=
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|)
expr_stmt|;
return|return
name|determinant
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_matrix_invert (GimpMatrix m,GimpMatrix m_inv)
name|gimp_matrix_invert
parameter_list|(
name|GimpMatrix
name|m
parameter_list|,
name|GimpMatrix
name|m_inv
parameter_list|)
block|{
name|double
name|det_1
decl_stmt|;
name|det_1
operator|=
name|gimp_matrix_determinant
argument_list|(
name|m
argument_list|)
expr_stmt|;
if|if
condition|(
name|det_1
operator|==
literal|0.0
condition|)
return|return;
name|det_1
operator|=
literal|1.0
operator|/
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
operator|(
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
operator|-
operator|(
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
operator|(
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|-
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
operator|-
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
operator|-
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
operator|-
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
name|m_inv
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
operator|(
name|m
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|-
name|m
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|*
name|m
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|)
operator|*
name|det_1
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_matrix_duplicate (GimpMatrix src,GimpMatrix target)
name|gimp_matrix_duplicate
parameter_list|(
name|GimpMatrix
name|src
parameter_list|,
name|GimpMatrix
name|target
parameter_list|)
block|{
name|int
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
name|target
index|[
name|i
index|]
index|[
name|j
index|]
operator|=
name|src
index|[
name|i
index|]
index|[
name|j
index|]
expr_stmt|;
block|}
end_function

end_unit

