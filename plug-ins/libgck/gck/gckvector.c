begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************************************/
end_comment

begin_comment
comment|/* GCK - The General Convenience Kit. Generally useful conveniece routines */
end_comment

begin_comment
comment|/* for GIMP plug-in writers and users of the GDK/GTK libraries.            */
end_comment

begin_comment
comment|/* Copyright (C) 1996 Tom Bech                                             */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is free software; you can redistribute it and/or modify    */
end_comment

begin_comment
comment|/* it under the terms of the GNU General Public License as published by    */
end_comment

begin_comment
comment|/* the Free Software Foundation; either version 2 of the License, or       */
end_comment

begin_comment
comment|/* (at your option) any later version.                                     */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is distributed in the hope that it will be useful,         */
end_comment

begin_comment
comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
end_comment

begin_comment
comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
end_comment

begin_comment
comment|/* GNU General Public License for more details.                            */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* You should have received a copy of the GNU General Public License       */
end_comment

begin_comment
comment|/* along with this program; if not, write to the Free Software             */
end_comment

begin_comment
comment|/* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               */
end_comment

begin_comment
comment|/***************************************************************************/
end_comment

begin_comment
comment|/**********************************************/
end_comment

begin_comment
comment|/* A little collection of useful vector stuff */
end_comment

begin_comment
comment|/**********************************************/
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<gck/gck.h>
end_include

begin_comment
comment|/*************************/
end_comment

begin_comment
comment|/* Some useful constants */
end_comment

begin_comment
comment|/*************************/
end_comment

begin_decl_stmt
DECL|variable|gck_vector2_zero
specifier|const
name|GckVector2
name|gck_vector2_zero
init|=
block|{
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gck_vector2_unit_x
specifier|const
name|GckVector2
name|gck_vector2_unit_x
init|=
block|{
literal|1.0
block|,
literal|0.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gck_vector2_unit_y
specifier|const
name|GckVector2
name|gck_vector2_unit_y
init|=
block|{
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gck_vector3_zero
specifier|const
name|GckVector3
name|gck_vector3_zero
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gck_vector3_unit_x
specifier|const
name|GckVector3
name|gck_vector3_unit_x
init|=
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|0.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gck_vector3_unit_y
specifier|const
name|GckVector3
name|gck_vector3_unit_y
init|=
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|0.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gck_vector3_unit_z
specifier|const
name|GckVector3
name|gck_vector3_unit_z
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**************************************/
end_comment

begin_comment
comment|/* Three dimensional vector functions */
end_comment

begin_comment
comment|/**************************************/
end_comment

begin_function
DECL|function|gck_vector2_inner_product (GckVector2 * a,GckVector2 * b)
name|double
name|gck_vector2_inner_product
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector2_inner_product"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_inner_product"
argument_list|)
expr_stmt|;
return|return
operator|(
name|a
operator|->
name|x
operator|*
name|b
operator|->
name|x
operator|+
name|a
operator|->
name|y
operator|*
name|b
operator|->
name|y
operator|)
return|;
block|}
end_function

begin_function
DECL|function|gck_vector2_cross_product (GckVector2 * a,GckVector2 * b)
name|GckVector3
name|gck_vector2_cross_product
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
block|{
name|GckVector3
name|normal
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_vector2_cross_product"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/*  normal.x=a->y*b->z-a->z*b->y;   normal.y=a->z*b->x-a->x*b->z;   normal.z=a->x*b->y-a->y*b->x;*/
name|g_function_leave
argument_list|(
literal|"gck_vector2_cross_product"
argument_list|)
expr_stmt|;
return|return
operator|(
name|normal
operator|)
return|;
block|}
end_function

begin_function
DECL|function|gck_vector2_length (GckVector2 * a)
name|double
name|gck_vector2_length
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector2_length"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_length"
argument_list|)
expr_stmt|;
return|return
operator|(
name|sqrt
argument_list|(
name|a
operator|->
name|x
operator|*
name|a
operator|->
name|x
operator|+
name|a
operator|->
name|y
operator|*
name|a
operator|->
name|y
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
DECL|function|gck_vector2_normalize (GckVector2 * a)
name|void
name|gck_vector2_normalize
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|)
block|{
name|double
name|len
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_vector2_normalize"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|len
operator|=
name|gck_vector2_length
argument_list|(
name|a
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|!=
literal|0.0
condition|)
block|{
name|len
operator|=
literal|1.0
operator|/
name|len
expr_stmt|;
name|a
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|*
name|len
expr_stmt|;
name|a
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|*
name|len
expr_stmt|;
block|}
else|else
operator|*
name|a
operator|=
name|gck_vector2_zero
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_normalize"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector2_mul (GckVector2 * a,double b)
name|void
name|gck_vector2_mul
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|double
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector2_mul"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|a
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|*
name|b
expr_stmt|;
name|a
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|*
name|b
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_mul"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector2_sub (GckVector2 * c,GckVector2 * a,GckVector2 * b)
name|void
name|gck_vector2_sub
parameter_list|(
name|GckVector2
modifier|*
name|c
parameter_list|,
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector2_sub"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|c
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|c
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|-
name|b
operator|->
name|x
expr_stmt|;
name|c
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|-
name|b
operator|->
name|y
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_sub"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector2_set (GckVector2 * a,double x,double y)
name|void
name|gck_vector2_set
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector2_set"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|a
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|a
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_set"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector2_add (GckVector2 * c,GckVector2 * a,GckVector2 * b)
name|void
name|gck_vector2_add
parameter_list|(
name|GckVector2
modifier|*
name|c
parameter_list|,
name|GckVector2
modifier|*
name|a
parameter_list|,
name|GckVector2
modifier|*
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector2_add"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|c
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|c
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|+
name|b
operator|->
name|x
expr_stmt|;
name|c
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|+
name|b
operator|->
name|y
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_add"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector2_neg (GckVector2 * a)
name|void
name|gck_vector2_neg
parameter_list|(
name|GckVector2
modifier|*
name|a
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector2_neg"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|a
operator|->
name|x
operator|*=
operator|-
literal|1.0
expr_stmt|;
name|a
operator|->
name|y
operator|*=
operator|-
literal|1.0
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_neg"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector2_rotate (GckVector2 * v,double alpha)
name|void
name|gck_vector2_rotate
parameter_list|(
name|GckVector2
modifier|*
name|v
parameter_list|,
name|double
name|alpha
parameter_list|)
block|{
name|GckVector2
name|s
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_vector2_rotate"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|v
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|s
operator|.
name|x
operator|=
name|cos
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|x
operator|+
name|sin
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|y
expr_stmt|;
name|s
operator|.
name|y
operator|=
name|cos
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|y
operator|-
name|sin
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|x
expr_stmt|;
operator|*
name|v
operator|=
name|s
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector2_rotate"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**************************************/
end_comment

begin_comment
comment|/* Three dimensional vector functions */
end_comment

begin_comment
comment|/**************************************/
end_comment

begin_function
DECL|function|gck_vector3_inner_product (GckVector3 * a,GckVector3 * b)
name|double
name|gck_vector3_inner_product
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector3_inner_product"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_inner_product"
argument_list|)
expr_stmt|;
return|return
operator|(
name|a
operator|->
name|x
operator|*
name|b
operator|->
name|x
operator|+
name|a
operator|->
name|y
operator|*
name|b
operator|->
name|y
operator|+
name|a
operator|->
name|z
operator|*
name|b
operator|->
name|z
operator|)
return|;
block|}
end_function

begin_function
DECL|function|gck_vector3_cross_product (GckVector3 * a,GckVector3 * b)
name|GckVector3
name|gck_vector3_cross_product
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
block|{
name|GckVector3
name|normal
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_vector3_cross_product"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|normal
operator|.
name|x
operator|=
name|a
operator|->
name|y
operator|*
name|b
operator|->
name|z
operator|-
name|a
operator|->
name|z
operator|*
name|b
operator|->
name|y
expr_stmt|;
name|normal
operator|.
name|y
operator|=
name|a
operator|->
name|z
operator|*
name|b
operator|->
name|x
operator|-
name|a
operator|->
name|x
operator|*
name|b
operator|->
name|z
expr_stmt|;
name|normal
operator|.
name|z
operator|=
name|a
operator|->
name|x
operator|*
name|b
operator|->
name|y
operator|-
name|a
operator|->
name|y
operator|*
name|b
operator|->
name|x
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_cross_product"
argument_list|)
expr_stmt|;
return|return
operator|(
name|normal
operator|)
return|;
block|}
end_function

begin_function
DECL|function|gck_vector3_length (GckVector3 * a)
name|double
name|gck_vector3_length
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector3_length"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_length"
argument_list|)
expr_stmt|;
return|return
operator|(
name|sqrt
argument_list|(
name|a
operator|->
name|x
operator|*
name|a
operator|->
name|x
operator|+
name|a
operator|->
name|y
operator|*
name|a
operator|->
name|y
operator|+
name|a
operator|->
name|z
operator|*
name|a
operator|->
name|z
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
DECL|function|gck_vector3_normalize (GckVector3 * a)
name|void
name|gck_vector3_normalize
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|)
block|{
name|double
name|len
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_vector3_normalize"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|len
operator|=
name|gck_vector3_length
argument_list|(
name|a
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|!=
literal|0.0
condition|)
block|{
name|len
operator|=
literal|1.0
operator|/
name|len
expr_stmt|;
name|a
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|*
name|len
expr_stmt|;
name|a
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|*
name|len
expr_stmt|;
name|a
operator|->
name|z
operator|=
name|a
operator|->
name|z
operator|*
name|len
expr_stmt|;
block|}
else|else
operator|*
name|a
operator|=
name|gck_vector3_zero
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_normalize"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector3_mul (GckVector3 * a,double b)
name|void
name|gck_vector3_mul
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|double
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector3_mul"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|a
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|*
name|b
expr_stmt|;
name|a
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|*
name|b
expr_stmt|;
name|a
operator|->
name|z
operator|=
name|a
operator|->
name|z
operator|*
name|b
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_mul"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector3_sub (GckVector3 * c,GckVector3 * a,GckVector3 * b)
name|void
name|gck_vector3_sub
parameter_list|(
name|GckVector3
modifier|*
name|c
parameter_list|,
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector3_sub"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|c
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|c
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|-
name|b
operator|->
name|x
expr_stmt|;
name|c
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|-
name|b
operator|->
name|y
expr_stmt|;
name|c
operator|->
name|z
operator|=
name|a
operator|->
name|z
operator|-
name|b
operator|->
name|z
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_sub"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector3_set (GckVector3 * a,double x,double y,double z)
name|void
name|gck_vector3_set
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|,
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|double
name|z
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector3_set"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|a
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|a
operator|->
name|y
operator|=
name|y
expr_stmt|;
name|a
operator|->
name|z
operator|=
name|z
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_set"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector3_add (GckVector3 * c,GckVector3 * a,GckVector3 * b)
name|void
name|gck_vector3_add
parameter_list|(
name|GckVector3
modifier|*
name|c
parameter_list|,
name|GckVector3
modifier|*
name|a
parameter_list|,
name|GckVector3
modifier|*
name|b
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector3_add"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|b
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|c
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|c
operator|->
name|x
operator|=
name|a
operator|->
name|x
operator|+
name|b
operator|->
name|x
expr_stmt|;
name|c
operator|->
name|y
operator|=
name|a
operator|->
name|y
operator|+
name|b
operator|->
name|y
expr_stmt|;
name|c
operator|->
name|z
operator|=
name|a
operator|->
name|z
operator|+
name|b
operator|->
name|z
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_add"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector3_neg (GckVector3 * a)
name|void
name|gck_vector3_neg
parameter_list|(
name|GckVector3
modifier|*
name|a
parameter_list|)
block|{
name|g_function_enter
argument_list|(
literal|"gck_vector3_neg"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|a
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|a
operator|->
name|x
operator|*=
operator|-
literal|1.0
expr_stmt|;
name|a
operator|->
name|y
operator|*=
operator|-
literal|1.0
expr_stmt|;
name|a
operator|->
name|z
operator|*=
operator|-
literal|1.0
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_neg"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gck_vector3_rotate (GckVector3 * v,double alpha,double beta,double gamma)
name|void
name|gck_vector3_rotate
parameter_list|(
name|GckVector3
modifier|*
name|v
parameter_list|,
name|double
name|alpha
parameter_list|,
name|double
name|beta
parameter_list|,
name|double
name|gamma
parameter_list|)
block|{
name|GckVector3
name|s
decl_stmt|,
name|t
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_vector3_rotate"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|v
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* First we rotate it around the Z axis (XY plane).. */
comment|/* ================================================= */
name|s
operator|.
name|x
operator|=
name|cos
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|x
operator|+
name|sin
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|y
expr_stmt|;
name|s
operator|.
name|y
operator|=
name|cos
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|y
operator|-
name|sin
argument_list|(
name|alpha
argument_list|)
operator|*
name|v
operator|->
name|x
expr_stmt|;
comment|/* ..then around the Y axis (XZ plane).. */
comment|/* ===================================== */
name|t
operator|=
name|s
expr_stmt|;
name|v
operator|->
name|x
operator|=
name|cos
argument_list|(
name|beta
argument_list|)
operator|*
name|t
operator|.
name|x
operator|+
name|sin
argument_list|(
name|beta
argument_list|)
operator|*
name|v
operator|->
name|z
expr_stmt|;
name|s
operator|.
name|z
operator|=
name|cos
argument_list|(
name|beta
argument_list|)
operator|*
name|v
operator|->
name|z
operator|-
name|sin
argument_list|(
name|beta
argument_list|)
operator|*
name|t
operator|.
name|x
expr_stmt|;
comment|/* ..and at last around the X axis (YZ plane) */
comment|/* ========================================== */
name|v
operator|->
name|y
operator|=
name|cos
argument_list|(
name|gamma
argument_list|)
operator|*
name|t
operator|.
name|y
operator|+
name|sin
argument_list|(
name|gamma
argument_list|)
operator|*
name|s
operator|.
name|z
expr_stmt|;
name|v
operator|->
name|z
operator|=
name|cos
argument_list|(
name|gamma
argument_list|)
operator|*
name|s
operator|.
name|z
operator|-
name|sin
argument_list|(
name|gamma
argument_list|)
operator|*
name|t
operator|.
name|y
expr_stmt|;
name|g_function_leave
argument_list|(
literal|"gck_vector3_rotate"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/******************************************************************/
end_comment

begin_comment
comment|/* Compute screen (sx,sy)-(sx+w,sy+h) to 3D unit square mapping.  */
end_comment

begin_comment
comment|/* The plane to map to is given in the z field of p. The observer */
end_comment

begin_comment
comment|/* is located at position vp (vp->z!=0.0).                        */
end_comment

begin_comment
comment|/******************************************************************/
end_comment

begin_function
DECL|function|gck_2d_to_3d (int sx,int sy,int w,int h,int x,int y,GckVector3 * vp,GckVector3 * p)
name|void
name|gck_2d_to_3d
parameter_list|(
name|int
name|sx
parameter_list|,
name|int
name|sy
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|GckVector3
modifier|*
name|vp
parameter_list|,
name|GckVector3
modifier|*
name|p
parameter_list|)
block|{
name|double
name|t
init|=
literal|0.0
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_2d_to_3d"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|vp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|p
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|vp
operator|->
name|x
operator|!=
literal|0.0
condition|)
name|t
operator|=
operator|(
name|p
operator|->
name|z
operator|-
name|vp
operator|->
name|z
operator|)
operator|/
name|vp
operator|->
name|z
expr_stmt|;
if|if
condition|(
name|t
operator|!=
literal|0.0
condition|)
block|{
name|p
operator|->
name|x
operator|=
name|vp
operator|->
name|x
operator|+
name|t
operator|*
operator|(
name|vp
operator|->
name|x
operator|-
operator|(
call|(
name|double
call|)
argument_list|(
name|x
operator|-
name|sx
argument_list|)
operator|/
operator|(
name|double
operator|)
name|w
operator|)
operator|)
expr_stmt|;
name|p
operator|->
name|y
operator|=
name|vp
operator|->
name|y
operator|+
name|t
operator|*
operator|(
name|vp
operator|->
name|y
operator|-
operator|(
call|(
name|double
call|)
argument_list|(
name|y
operator|-
name|sy
argument_list|)
operator|/
operator|(
name|double
operator|)
name|h
operator|)
operator|)
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|x
operator|=
call|(
name|double
call|)
argument_list|(
name|x
operator|-
name|sx
argument_list|)
operator|/
operator|(
name|double
operator|)
name|w
expr_stmt|;
name|p
operator|->
name|y
operator|=
call|(
name|double
call|)
argument_list|(
name|y
operator|-
name|sy
argument_list|)
operator|/
operator|(
name|double
operator|)
name|h
expr_stmt|;
block|}
name|g_function_leave
argument_list|(
literal|"gck_2d_to_3d"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*********************************************************/
end_comment

begin_comment
comment|/* Convert the given 3D point to 2D (project it onto the */
end_comment

begin_comment
comment|/* viewing plane, (sx,sy,0)-(sx+w,sy+h,0). The input is  */
end_comment

begin_comment
comment|/* assumed to be in the unit square (0,0,z)-(1,1,z).     */
end_comment

begin_comment
comment|/* The viewpoint of the observer is passed in vp.        */
end_comment

begin_comment
comment|/*********************************************************/
end_comment

begin_function
DECL|function|gck_3d_to_2d (int sx,int sy,int w,int h,double * x,double * y,GckVector3 * vp,GckVector3 * p)
name|void
name|gck_3d_to_2d
parameter_list|(
name|int
name|sx
parameter_list|,
name|int
name|sy
parameter_list|,
name|int
name|w
parameter_list|,
name|int
name|h
parameter_list|,
name|double
modifier|*
name|x
parameter_list|,
name|double
modifier|*
name|y
parameter_list|,
name|GckVector3
modifier|*
name|vp
parameter_list|,
name|GckVector3
modifier|*
name|p
parameter_list|)
block|{
name|double
name|t
decl_stmt|;
name|GckVector3
name|dir
decl_stmt|;
name|g_function_enter
argument_list|(
literal|"gck_3d_to_2d"
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|vp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|p
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gck_vector3_sub
argument_list|(
operator|&
name|dir
argument_list|,
name|p
argument_list|,
name|vp
argument_list|)
expr_stmt|;
name|gck_vector3_normalize
argument_list|(
operator|&
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|.
name|z
operator|!=
literal|0.0
condition|)
block|{
name|t
operator|=
operator|(
operator|-
literal|1.0
operator|*
name|vp
operator|->
name|z
operator|)
operator|/
name|dir
operator|.
name|z
expr_stmt|;
operator|*
name|x
operator|=
operator|(
name|double
operator|)
name|sx
operator|+
operator|(
operator|(
name|vp
operator|->
name|x
operator|+
name|t
operator|*
name|dir
operator|.
name|x
operator|)
operator|*
operator|(
name|double
operator|)
name|w
operator|)
expr_stmt|;
operator|*
name|y
operator|=
operator|(
name|double
operator|)
name|sy
operator|+
operator|(
operator|(
name|vp
operator|->
name|y
operator|+
name|t
operator|*
name|dir
operator|.
name|y
operator|)
operator|*
operator|(
name|double
operator|)
name|h
operator|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|x
operator|=
operator|(
name|double
operator|)
name|sx
operator|+
operator|(
name|p
operator|->
name|x
operator|*
operator|(
name|double
operator|)
name|w
operator|)
expr_stmt|;
operator|*
name|y
operator|=
operator|(
name|double
operator|)
name|sy
operator|+
operator|(
name|p
operator|->
name|y
operator|*
operator|(
name|double
operator|)
name|h
operator|)
expr_stmt|;
block|}
name|g_function_leave
argument_list|(
literal|"gck_3d_to_2d"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

