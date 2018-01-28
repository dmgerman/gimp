begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-transform-utils.h"
end_include

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|1e-6
end_define

begin_function
name|void
DECL|function|gimp_transform_get_rotate_center (gint x,gint y,gint width,gint height,gboolean auto_center,gdouble * center_x,gdouble * center_y)
name|gimp_transform_get_rotate_center
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|auto_center
parameter_list|,
name|gdouble
modifier|*
name|center_x
parameter_list|,
name|gdouble
modifier|*
name|center_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|center_x
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|center_y
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|auto_center
condition|)
block|{
operator|*
name|center_x
operator|=
operator|(
name|gdouble
operator|)
name|x
operator|+
operator|(
name|gdouble
operator|)
name|width
operator|/
literal|2.0
expr_stmt|;
operator|*
name|center_y
operator|=
operator|(
name|gdouble
operator|)
name|y
operator|+
operator|(
name|gdouble
operator|)
name|height
operator|/
literal|2.0
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_get_flip_axis (gint x,gint y,gint width,gint height,GimpOrientationType flip_type,gboolean auto_center,gdouble * axis)
name|gimp_transform_get_flip_axis
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gboolean
name|auto_center
parameter_list|,
name|gdouble
modifier|*
name|axis
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|axis
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|auto_center
condition|)
block|{
switch|switch
condition|(
name|flip_type
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
operator|*
name|axis
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|x
operator|+
operator|(
name|gdouble
operator|)
name|width
operator|/
literal|2.0
operator|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
operator|*
name|axis
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|y
operator|+
operator|(
name|gdouble
operator|)
name|height
operator|/
literal|2.0
operator|)
expr_stmt|;
break|break;
default|default:
name|g_return_if_reached
argument_list|()
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_flip (GimpMatrix3 * matrix,GimpOrientationType flip_type,gdouble axis)
name|gimp_transform_matrix_flip
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gdouble
name|axis
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|flip_type
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|axis
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
name|matrix
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
name|axis
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
literal|0.0
argument_list|,
operator|-
name|axis
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
name|matrix
argument_list|,
literal|1.0
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
literal|0.0
argument_list|,
name|axis
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_UNKNOWN
case|:
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_flip_free (GimpMatrix3 * matrix,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|gimp_transform_matrix_flip_free
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
block|{
name|gdouble
name|angle
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|angle
operator|=
name|atan2
argument_list|(
name|y2
operator|-
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
name|gimp_matrix3_identity
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|x1
argument_list|,
operator|-
name|y1
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
name|matrix
argument_list|,
operator|-
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
name|matrix
argument_list|,
literal|1.0
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
name|matrix
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_rotate (GimpMatrix3 * matrix,GimpRotationType rotate_type,gdouble center_x,gdouble center_y)
name|gimp_transform_matrix_rotate
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|)
block|{
name|gdouble
name|angle
init|=
literal|0
decl_stmt|;
switch|switch
condition|(
name|rotate_type
condition|)
block|{
case|case
name|GIMP_ROTATE_90
case|:
name|angle
operator|=
name|G_PI_2
expr_stmt|;
break|break;
case|case
name|GIMP_ROTATE_180
case|:
name|angle
operator|=
name|G_PI
expr_stmt|;
break|break;
case|case
name|GIMP_ROTATE_270
case|:
name|angle
operator|=
operator|-
name|G_PI_2
expr_stmt|;
break|break;
block|}
name|gimp_transform_matrix_rotate_center
argument_list|(
name|matrix
argument_list|,
name|center_x
argument_list|,
name|center_y
argument_list|,
name|angle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_rotate_rect (GimpMatrix3 * matrix,gint x,gint y,gint width,gint height,gdouble angle)
name|gimp_transform_matrix_rotate_rect
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|center_x
operator|=
operator|(
name|gdouble
operator|)
name|x
operator|+
operator|(
name|gdouble
operator|)
name|width
operator|/
literal|2.0
expr_stmt|;
name|center_y
operator|=
operator|(
name|gdouble
operator|)
name|y
operator|+
operator|(
name|gdouble
operator|)
name|height
operator|/
literal|2.0
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|center_x
argument_list|,
operator|-
name|center_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
name|matrix
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|+
name|center_x
argument_list|,
operator|+
name|center_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_rotate_center (GimpMatrix3 * matrix,gdouble center_x,gdouble center_y,gdouble angle)
name|gimp_transform_matrix_rotate_center
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|center_x
argument_list|,
operator|-
name|center_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_rotate
argument_list|(
name|matrix
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|+
name|center_x
argument_list|,
operator|+
name|center_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_scale (GimpMatrix3 * matrix,gint x,gint y,gint width,gint height,gdouble t_x,gdouble t_y,gdouble t_width,gdouble t_height)
name|gimp_transform_matrix_scale
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
name|t_x
parameter_list|,
name|gdouble
name|t_y
parameter_list|,
name|gdouble
name|t_width
parameter_list|,
name|gdouble
name|t_height
parameter_list|)
block|{
name|gdouble
name|scale_x
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|scale_y
init|=
literal|1.0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|>
literal|0
condition|)
name|scale_x
operator|=
name|t_width
operator|/
operator|(
name|gdouble
operator|)
name|width
expr_stmt|;
if|if
condition|(
name|height
operator|>
literal|0
condition|)
name|scale_y
operator|=
name|t_height
operator|/
operator|(
name|gdouble
operator|)
name|height
expr_stmt|;
name|gimp_matrix3_identity
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
name|matrix
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
name|t_x
argument_list|,
name|t_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_shear (GimpMatrix3 * matrix,gint x,gint y,gint width,gint height,GimpOrientationType orientation,gdouble amount)
name|gimp_transform_matrix_shear
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|,
name|gdouble
name|amount
parameter_list|)
block|{
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|==
literal|0
condition|)
name|width
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|height
operator|==
literal|0
condition|)
name|height
operator|=
literal|1
expr_stmt|;
name|center_x
operator|=
operator|(
name|gdouble
operator|)
name|x
operator|+
operator|(
name|gdouble
operator|)
name|width
operator|/
literal|2.0
expr_stmt|;
name|center_y
operator|=
operator|(
name|gdouble
operator|)
name|y
operator|+
operator|(
name|gdouble
operator|)
name|height
operator|/
literal|2.0
expr_stmt|;
name|gimp_matrix3_identity
argument_list|(
name|matrix
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|center_x
argument_list|,
operator|-
name|center_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|gimp_matrix3_xshear
argument_list|(
name|matrix
argument_list|,
name|amount
operator|/
name|height
argument_list|)
expr_stmt|;
else|else
name|gimp_matrix3_yshear
argument_list|(
name|matrix
argument_list|,
name|amount
operator|/
name|width
argument_list|)
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|+
name|center_x
argument_list|,
operator|+
name|center_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_matrix_perspective (GimpMatrix3 * matrix,gint x,gint y,gint width,gint height,gdouble t_x1,gdouble t_y1,gdouble t_x2,gdouble t_y2,gdouble t_x3,gdouble t_y3,gdouble t_x4,gdouble t_y4)
name|gimp_transform_matrix_perspective
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
name|t_x1
parameter_list|,
name|gdouble
name|t_y1
parameter_list|,
name|gdouble
name|t_x2
parameter_list|,
name|gdouble
name|t_y2
parameter_list|,
name|gdouble
name|t_x3
parameter_list|,
name|gdouble
name|t_y3
parameter_list|,
name|gdouble
name|t_x4
parameter_list|,
name|gdouble
name|t_y4
parameter_list|)
block|{
name|GimpMatrix3
name|trafo
decl_stmt|;
name|gdouble
name|scalex
decl_stmt|;
name|gdouble
name|scaley
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|scalex
operator|=
name|scaley
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|width
operator|>
literal|0
condition|)
name|scalex
operator|=
literal|1.0
operator|/
operator|(
name|gdouble
operator|)
name|width
expr_stmt|;
if|if
condition|(
name|height
operator|>
literal|0
condition|)
name|scaley
operator|=
literal|1.0
operator|/
operator|(
name|gdouble
operator|)
name|height
expr_stmt|;
name|gimp_matrix3_translate
argument_list|(
name|matrix
argument_list|,
operator|-
name|x
argument_list|,
operator|-
name|y
argument_list|)
expr_stmt|;
name|gimp_matrix3_scale
argument_list|(
name|matrix
argument_list|,
name|scalex
argument_list|,
name|scaley
argument_list|)
expr_stmt|;
comment|/* Determine the perspective transform that maps from    * the unit cube to the transformed coordinates    */
block|{
name|gdouble
name|dx1
decl_stmt|,
name|dx2
decl_stmt|,
name|dx3
decl_stmt|,
name|dy1
decl_stmt|,
name|dy2
decl_stmt|,
name|dy3
decl_stmt|;
name|dx1
operator|=
name|t_x2
operator|-
name|t_x4
expr_stmt|;
name|dx2
operator|=
name|t_x3
operator|-
name|t_x4
expr_stmt|;
name|dx3
operator|=
name|t_x1
operator|-
name|t_x2
operator|+
name|t_x4
operator|-
name|t_x3
expr_stmt|;
name|dy1
operator|=
name|t_y2
operator|-
name|t_y4
expr_stmt|;
name|dy2
operator|=
name|t_y3
operator|-
name|t_y4
expr_stmt|;
name|dy3
operator|=
name|t_y1
operator|-
name|t_y2
operator|+
name|t_y4
operator|-
name|t_y3
expr_stmt|;
comment|/*  Is the mapping affine?  */
if|if
condition|(
operator|(
name|dx3
operator|==
literal|0.0
operator|)
operator|&&
operator|(
name|dy3
operator|==
literal|0.0
operator|)
condition|)
block|{
name|trafo
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|t_x2
operator|-
name|t_x1
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|t_x4
operator|-
name|t_x2
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|t_x1
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|t_y2
operator|-
name|t_y1
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|t_y4
operator|-
name|t_y2
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|t_y1
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|=
literal|0.0
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
literal|0.0
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|det1
decl_stmt|,
name|det2
decl_stmt|;
name|det1
operator|=
name|dx3
operator|*
name|dy2
operator|-
name|dy3
operator|*
name|dx2
expr_stmt|;
name|det2
operator|=
name|dx1
operator|*
name|dy2
operator|-
name|dy1
operator|*
name|dx2
expr_stmt|;
name|trafo
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
name|det2
operator|==
literal|0.0
operator|)
condition|?
literal|1.0
else|:
name|det1
operator|/
name|det2
expr_stmt|;
name|det1
operator|=
name|dx1
operator|*
name|dy3
operator|-
name|dy1
operator|*
name|dx3
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|=
operator|(
name|det2
operator|==
literal|0.0
operator|)
condition|?
literal|1.0
else|:
name|det1
operator|/
name|det2
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|=
name|t_x2
operator|-
name|t_x1
operator|+
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|t_x2
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|=
name|t_x3
operator|-
name|t_x1
operator|+
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|t_x3
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|=
name|t_x1
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|=
name|t_y2
operator|-
name|t_y1
operator|+
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|*
name|t_y2
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|1
index|]
operator|=
name|t_y3
operator|-
name|t_y1
operator|+
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|*
name|t_y3
expr_stmt|;
name|trafo
operator|.
name|coeff
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|=
name|t_y1
expr_stmt|;
block|}
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
literal|1.0
expr_stmt|;
block|}
name|gimp_matrix3_mult
argument_list|(
operator|&
name|trafo
argument_list|,
name|matrix
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* modified gaussian algorithm  * solves a system of linear equations  *  * Example:  * 1x + 2y + 4z = 25  * 2x + 1y      = 4  * 3x + 5y + 2z = 23  * Solution: x=1, y=2, z=5  *  * Input:  * matrix = { 1,2,4,25,2,1,0,4,3,5,2,23 }  * s = 3 (Number of variables)  * Output:  * return value == TRUE (TRUE, if there is a single unique solution)  * solution == { 1,2,5 } (if the return value is FALSE, the content  * of solution is of no use)  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|mod_gauss (gdouble matrix[],gdouble solution[],gint s)
name|mod_gauss
parameter_list|(
name|gdouble
name|matrix
index|[]
parameter_list|,
name|gdouble
name|solution
index|[]
parameter_list|,
name|gint
name|s
parameter_list|)
block|{
name|gint
name|p
index|[
name|s
index|]
decl_stmt|;
comment|/* row permutation */
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|r
decl_stmt|,
name|temp
decl_stmt|;
name|gdouble
name|q
decl_stmt|;
name|gint
name|t
init|=
name|s
operator|+
literal|1
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|s
condition|;
name|i
operator|++
control|)
block|{
name|p
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
block|}
for|for
control|(
name|r
operator|=
literal|0
init|;
name|r
operator|<
name|s
condition|;
name|r
operator|++
control|)
block|{
comment|/* make sure that (r,r) is not 0 */
if|if
condition|(
name|fabs
argument_list|(
name|matrix
index|[
name|p
index|[
name|r
index|]
operator|*
name|t
operator|+
name|r
index|]
argument_list|)
operator|<=
name|EPSILON
condition|)
block|{
comment|/* we need to permutate rows */
for|for
control|(
name|i
operator|=
name|r
operator|+
literal|1
init|;
name|i
operator|<=
name|s
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|==
name|s
condition|)
block|{
comment|/* if this happens, the linear system has zero or                    * more than one solutions.                    */
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|fabs
argument_list|(
name|matrix
index|[
name|p
index|[
name|i
index|]
operator|*
name|t
operator|+
name|r
index|]
argument_list|)
operator|>
name|EPSILON
condition|)
break|break;
block|}
name|temp
operator|=
name|p
index|[
name|r
index|]
expr_stmt|;
name|p
index|[
name|r
index|]
operator|=
name|p
index|[
name|i
index|]
expr_stmt|;
name|p
index|[
name|i
index|]
operator|=
name|temp
expr_stmt|;
block|}
comment|/* make (r,r) == 1 */
name|q
operator|=
literal|1.0
operator|/
name|matrix
index|[
name|p
index|[
name|r
index|]
operator|*
name|t
operator|+
name|r
index|]
expr_stmt|;
name|matrix
index|[
name|p
index|[
name|r
index|]
operator|*
name|t
operator|+
name|r
index|]
operator|=
literal|1.0
expr_stmt|;
for|for
control|(
name|j
operator|=
name|r
operator|+
literal|1
init|;
name|j
operator|<
name|t
condition|;
name|j
operator|++
control|)
block|{
name|matrix
index|[
name|p
index|[
name|r
index|]
operator|*
name|t
operator|+
name|j
index|]
operator|*=
name|q
expr_stmt|;
block|}
comment|/* make that all entries in column r are 0 (except (r,r)) */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|s
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|==
name|r
condition|)
continue|continue;
for|for
control|(
name|j
operator|=
name|r
operator|+
literal|1
init|;
name|j
operator|<
name|t
condition|;
name|j
operator|++
control|)
block|{
name|matrix
index|[
name|p
index|[
name|i
index|]
operator|*
name|t
operator|+
name|j
index|]
operator|-=
name|matrix
index|[
name|p
index|[
name|r
index|]
operator|*
name|t
operator|+
name|j
index|]
operator|*
name|matrix
index|[
name|p
index|[
name|i
index|]
operator|*
name|t
operator|+
name|r
index|]
expr_stmt|;
block|}
comment|/* we don't need to execute the following line            * since we won't access this element again:            *            * matrix[p[i] * t + r] = 0.0;            */
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|s
condition|;
name|i
operator|++
control|)
block|{
name|solution
index|[
name|i
index|]
operator|=
name|matrix
index|[
name|p
index|[
name|i
index|]
operator|*
name|t
operator|+
name|s
index|]
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_transform_matrix_generic (GimpMatrix3 * matrix,const GimpVector2 * input_points,const GimpVector2 * output_points)
name|gimp_transform_matrix_generic
parameter_list|(
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|input_points
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|output_points
parameter_list|)
block|{
name|GimpMatrix3
name|trafo
decl_stmt|;
name|gdouble
name|coeff
index|[
literal|8
operator|*
literal|9
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|input_points
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|output_points
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|0
index|]
operator|=
name|input_points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|1
index|]
operator|=
name|input_points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|2
index|]
operator|=
literal|1.0
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|3
index|]
operator|=
literal|0.0
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|4
index|]
operator|=
literal|0.0
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|5
index|]
operator|=
literal|0.0
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|6
index|]
operator|=
operator|-
name|input_points
index|[
name|i
index|]
operator|.
name|x
operator|*
name|output_points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|7
index|]
operator|=
operator|-
name|input_points
index|[
name|i
index|]
operator|.
name|y
operator|*
name|output_points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|coeff
index|[
name|i
operator|*
literal|9
operator|+
literal|8
index|]
operator|=
name|output_points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|0
index|]
operator|=
literal|0.0
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|1
index|]
operator|=
literal|0.0
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|2
index|]
operator|=
literal|0.0
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|3
index|]
operator|=
name|input_points
index|[
name|i
index|]
operator|.
name|x
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|4
index|]
operator|=
name|input_points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|5
index|]
operator|=
literal|1.0
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|6
index|]
operator|=
operator|-
name|input_points
index|[
name|i
index|]
operator|.
name|x
operator|*
name|output_points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|7
index|]
operator|=
operator|-
name|input_points
index|[
name|i
index|]
operator|.
name|y
operator|*
name|output_points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
name|coeff
index|[
operator|(
name|i
operator|+
literal|4
operator|)
operator|*
literal|9
operator|+
literal|8
index|]
operator|=
name|output_points
index|[
name|i
index|]
operator|.
name|y
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|mod_gauss
argument_list|(
name|coeff
argument_list|,
operator|(
name|gdouble
operator|*
operator|)
name|trafo
operator|.
name|coeff
argument_list|,
literal|8
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|trafo
operator|.
name|coeff
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|=
literal|1.0
expr_stmt|;
name|gimp_matrix3_mult
argument_list|(
operator|&
name|trafo
argument_list|,
name|matrix
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|w
init|=
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
name|input_points
index|[
name|i
index|]
operator|.
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
name|input_points
index|[
name|i
index|]
operator|.
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
decl_stmt|;
if|if
condition|(
name|w
operator|<=
name|EPSILON
condition|)
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_transform_polygon_is_convex (gdouble x1,gdouble y1,gdouble x2,gdouble y2,gdouble x3,gdouble y3,gdouble x4,gdouble y4)
name|gimp_transform_polygon_is_convex
parameter_list|(
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
name|x3
parameter_list|,
name|gdouble
name|y3
parameter_list|,
name|gdouble
name|x4
parameter_list|,
name|gdouble
name|y4
parameter_list|)
block|{
name|gdouble
name|z1
decl_stmt|,
name|z2
decl_stmt|,
name|z3
decl_stmt|,
name|z4
decl_stmt|;
comment|/* We test if the transformed polygon is convex.  if z1 and z2 have    * the same sign as well as z3 and z4 the polygon is convex.    */
name|z1
operator|=
operator|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
operator|(
name|y4
operator|-
name|y1
operator|)
operator|-
operator|(
name|x4
operator|-
name|x1
operator|)
operator|*
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
expr_stmt|;
name|z2
operator|=
operator|(
operator|(
name|x4
operator|-
name|x1
operator|)
operator|*
operator|(
name|y3
operator|-
name|y1
operator|)
operator|-
operator|(
name|x3
operator|-
name|x1
operator|)
operator|*
operator|(
name|y4
operator|-
name|y1
operator|)
operator|)
expr_stmt|;
name|z3
operator|=
operator|(
operator|(
name|x4
operator|-
name|x2
operator|)
operator|*
operator|(
name|y3
operator|-
name|y2
operator|)
operator|-
operator|(
name|x3
operator|-
name|x2
operator|)
operator|*
operator|(
name|y4
operator|-
name|y2
operator|)
operator|)
expr_stmt|;
name|z4
operator|=
operator|(
operator|(
name|x3
operator|-
name|x2
operator|)
operator|*
operator|(
name|y1
operator|-
name|y2
operator|)
operator|-
operator|(
name|x1
operator|-
name|x2
operator|)
operator|*
operator|(
name|y3
operator|-
name|y2
operator|)
operator|)
expr_stmt|;
return|return
operator|(
name|z1
operator|*
name|z2
operator|>
literal|0
operator|)
operator|&&
operator|(
name|z3
operator|*
name|z4
operator|>
literal|0
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_polygon (const GimpMatrix3 * matrix,const GimpVector2 * vertices,gint n_vertices,gboolean closed,GimpVector2 * t_vertices,gint * n_t_vertices)
name|gimp_transform_polygon
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|vertices
parameter_list|,
name|gint
name|n_vertices
parameter_list|,
name|gboolean
name|closed
parameter_list|,
name|GimpVector2
modifier|*
name|t_vertices
parameter_list|,
name|gint
modifier|*
name|n_t_vertices
parameter_list|)
block|{
name|GimpVector3
name|curr
decl_stmt|;
name|gboolean
name|curr_visible
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|matrix
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|vertices
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_vertices
operator|>=
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|t_vertices
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_t_vertices
operator|!=
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|n_t_vertices
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|n_vertices
operator|==
literal|0
condition|)
return|return;
name|curr
operator|.
name|x
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
operator|*
name|vertices
index|[
literal|0
index|]
operator|.
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
name|vertices
index|[
literal|0
index|]
operator|.
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
expr_stmt|;
name|curr
operator|.
name|y
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
operator|*
name|vertices
index|[
literal|0
index|]
operator|.
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
name|vertices
index|[
literal|0
index|]
operator|.
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
expr_stmt|;
name|curr
operator|.
name|z
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
name|vertices
index|[
literal|0
index|]
operator|.
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
name|vertices
index|[
literal|0
index|]
operator|.
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
name|curr_visible
operator|=
operator|(
name|curr
operator|.
name|z
operator|>=
name|GIMP_TRANSFORM_NEAR_Z
operator|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_vertices
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|curr_visible
condition|)
block|{
name|t_vertices
index|[
operator|(
operator|*
name|n_t_vertices
operator|)
operator|++
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
name|curr
operator|.
name|x
operator|/
name|curr
operator|.
name|z
block|,
name|curr
operator|.
name|y
operator|/
name|curr
operator|.
name|z
block|}
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|<
name|n_vertices
operator|-
literal|1
operator|||
name|closed
condition|)
block|{
name|GimpVector3
name|next
decl_stmt|;
name|gboolean
name|next_visible
decl_stmt|;
name|gint
name|j
init|=
operator|(
name|i
operator|+
literal|1
operator|)
operator|%
name|n_vertices
decl_stmt|;
name|next
operator|.
name|x
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
operator|*
name|vertices
index|[
name|j
index|]
operator|.
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
name|vertices
index|[
name|j
index|]
operator|.
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
expr_stmt|;
name|next
operator|.
name|y
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
operator|*
name|vertices
index|[
name|j
index|]
operator|.
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
name|vertices
index|[
name|j
index|]
operator|.
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
expr_stmt|;
name|next
operator|.
name|z
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
name|vertices
index|[
name|j
index|]
operator|.
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
name|vertices
index|[
name|j
index|]
operator|.
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
name|next_visible
operator|=
operator|(
name|next
operator|.
name|z
operator|>=
name|GIMP_TRANSFORM_NEAR_Z
operator|)
expr_stmt|;
if|if
condition|(
name|next_visible
operator|!=
name|curr_visible
condition|)
block|{
name|gdouble
name|ratio
init|=
operator|(
name|curr
operator|.
name|z
operator|-
name|GIMP_TRANSFORM_NEAR_Z
operator|)
operator|/
operator|(
name|curr
operator|.
name|z
operator|-
name|next
operator|.
name|z
operator|)
decl_stmt|;
name|t_vertices
index|[
operator|(
operator|*
name|n_t_vertices
operator|)
operator|++
index|]
operator|=
operator|(
name|GimpVector2
operator|)
block|{
operator|(
name|curr
operator|.
name|x
operator|+
operator|(
name|next
operator|.
name|x
operator|-
name|curr
operator|.
name|x
operator|)
operator|*
name|ratio
operator|)
operator|/
name|GIMP_TRANSFORM_NEAR_Z
block|,
operator|(
name|curr
operator|.
name|y
operator|+
operator|(
name|next
operator|.
name|y
operator|-
name|curr
operator|.
name|y
operator|)
operator|*
name|ratio
operator|)
operator|/
name|GIMP_TRANSFORM_NEAR_Z
block|}
expr_stmt|;
block|}
name|curr
operator|=
name|next
expr_stmt|;
name|curr_visible
operator|=
name|next_visible
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

