begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpbilinear.h"
end_include

begin_include
include|#
directive|include
file|"gimpmath.h"
end_include

begin_function
name|gdouble
DECL|function|gimp_bilinear (gdouble x,gdouble y,gdouble * values)
name|gimp_bilinear
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|xx
decl_stmt|,
name|yy
decl_stmt|;
name|gdouble
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_assert
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|xx
operator|=
name|fmod
argument_list|(
name|x
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|yy
operator|=
name|fmod
argument_list|(
name|y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0.0
condition|)
name|x
operator|+=
literal|1.0
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0.0
condition|)
name|y
operator|+=
literal|1.0
expr_stmt|;
name|m0
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|1
index|]
expr_stmt|;
name|m1
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|3
index|]
expr_stmt|;
return|return
operator|(
literal|1.0
operator|-
name|yy
operator|)
operator|*
name|m0
operator|+
name|yy
operator|*
name|m1
return|;
block|}
end_function

begin_function
name|guchar
DECL|function|gimp_bilinear_8 (gdouble x,gdouble y,guchar * values)
name|gimp_bilinear_8
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guchar
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|xx
decl_stmt|,
name|yy
decl_stmt|;
name|gdouble
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_assert
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|xx
operator|=
name|fmod
argument_list|(
name|x
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|yy
operator|=
name|fmod
argument_list|(
name|y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0.0
condition|)
name|x
operator|+=
literal|1.0
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0.0
condition|)
name|y
operator|+=
literal|1.0
expr_stmt|;
name|m0
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|1
index|]
expr_stmt|;
name|m1
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|3
index|]
expr_stmt|;
return|return
call|(
name|guchar
call|)
argument_list|(
operator|(
literal|1.0
operator|-
name|yy
operator|)
operator|*
name|m0
operator|+
name|yy
operator|*
name|m1
argument_list|)
return|;
block|}
end_function

begin_function
name|guint16
DECL|function|gimp_bilinear_16 (gdouble x,gdouble y,guint16 * values)
name|gimp_bilinear_16
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint16
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|xx
decl_stmt|,
name|yy
decl_stmt|;
name|gdouble
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_assert
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|xx
operator|=
name|fmod
argument_list|(
name|x
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|yy
operator|=
name|fmod
argument_list|(
name|y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0.0
condition|)
name|x
operator|+=
literal|1.0
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0.0
condition|)
name|y
operator|+=
literal|1.0
expr_stmt|;
name|m0
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|1
index|]
expr_stmt|;
name|m1
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|3
index|]
expr_stmt|;
return|return
call|(
name|guint16
call|)
argument_list|(
operator|(
literal|1.0
operator|-
name|yy
operator|)
operator|*
name|m0
operator|+
name|yy
operator|*
name|m1
argument_list|)
return|;
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_bilinear_32 (gdouble x,gdouble y,guint32 * values)
name|gimp_bilinear_32
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint32
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|xx
decl_stmt|,
name|yy
decl_stmt|;
name|gdouble
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_assert
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|xx
operator|=
name|fmod
argument_list|(
name|x
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|yy
operator|=
name|fmod
argument_list|(
name|y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0.0
condition|)
name|x
operator|+=
literal|1.0
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0.0
condition|)
name|y
operator|+=
literal|1.0
expr_stmt|;
name|m0
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|1
index|]
expr_stmt|;
name|m1
operator|=
operator|(
literal|1.0
operator|-
name|xx
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|xx
operator|*
name|values
index|[
literal|3
index|]
expr_stmt|;
return|return
call|(
name|guint32
call|)
argument_list|(
operator|(
literal|1.0
operator|-
name|yy
operator|)
operator|*
name|m0
operator|+
name|yy
operator|*
name|m1
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpRGB
DECL|function|gimp_bilinear_rgb (gdouble x,gdouble y,GimpRGB * values)
name|gimp_bilinear_rgb
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|gdouble
name|ix
decl_stmt|,
name|iy
decl_stmt|;
name|GimpRGB
name|v
decl_stmt|;
name|g_assert
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|x
operator|=
name|fmod
argument_list|(
name|x
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|y
operator|=
name|fmod
argument_list|(
name|y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|+=
literal|1.0
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|+=
literal|1.0
expr_stmt|;
name|ix
operator|=
literal|1.0
operator|-
name|x
expr_stmt|;
name|iy
operator|=
literal|1.0
operator|-
name|y
expr_stmt|;
comment|/* Red */
name|m0
operator|=
name|ix
operator|*
name|values
index|[
literal|0
index|]
operator|.
name|r
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
operator|.
name|r
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|values
index|[
literal|2
index|]
operator|.
name|r
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
operator|.
name|r
expr_stmt|;
name|v
operator|.
name|r
operator|=
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
expr_stmt|;
comment|/* Green */
name|m0
operator|=
name|ix
operator|*
name|values
index|[
literal|0
index|]
operator|.
name|g
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
operator|.
name|g
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|values
index|[
literal|2
index|]
operator|.
name|g
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
operator|.
name|g
expr_stmt|;
name|v
operator|.
name|g
operator|=
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
expr_stmt|;
comment|/* Blue */
name|m0
operator|=
name|ix
operator|*
name|values
index|[
literal|0
index|]
operator|.
name|b
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
operator|.
name|b
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|values
index|[
literal|2
index|]
operator|.
name|b
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
operator|.
name|b
expr_stmt|;
name|v
operator|.
name|b
operator|=
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
expr_stmt|;
return|return
name|v
return|;
block|}
end_function

begin_function
name|GimpRGB
DECL|function|gimp_bilinear_rgba (gdouble x,gdouble y,GimpRGB * values)
name|gimp_bilinear_rgba
parameter_list|(
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GimpRGB
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|gdouble
name|ix
decl_stmt|,
name|iy
decl_stmt|;
name|GimpRGB
name|v
decl_stmt|;
name|g_assert
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|x
operator|=
name|fmod
argument_list|(
name|x
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|y
operator|=
name|fmod
argument_list|(
name|y
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|+=
literal|1.0
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|+=
literal|1.0
expr_stmt|;
name|ix
operator|=
literal|1.0
operator|-
name|x
expr_stmt|;
name|iy
operator|=
literal|1.0
operator|-
name|y
expr_stmt|;
comment|/* Red */
name|m0
operator|=
name|ix
operator|*
name|values
index|[
literal|0
index|]
operator|.
name|r
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
operator|.
name|r
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|values
index|[
literal|2
index|]
operator|.
name|r
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
operator|.
name|r
expr_stmt|;
name|v
operator|.
name|r
operator|=
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
expr_stmt|;
comment|/* Green */
name|m0
operator|=
name|ix
operator|*
name|values
index|[
literal|0
index|]
operator|.
name|g
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
operator|.
name|g
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|values
index|[
literal|2
index|]
operator|.
name|g
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
operator|.
name|g
expr_stmt|;
name|v
operator|.
name|g
operator|=
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
expr_stmt|;
comment|/* Blue */
name|m0
operator|=
name|ix
operator|*
name|values
index|[
literal|0
index|]
operator|.
name|b
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
operator|.
name|b
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|values
index|[
literal|2
index|]
operator|.
name|b
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
operator|.
name|b
expr_stmt|;
name|v
operator|.
name|b
operator|=
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
expr_stmt|;
comment|/* Alpha */
name|m0
operator|=
name|ix
operator|*
name|values
index|[
literal|0
index|]
operator|.
name|a
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
operator|.
name|a
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|values
index|[
literal|2
index|]
operator|.
name|a
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
operator|.
name|a
expr_stmt|;
name|v
operator|.
name|a
operator|=
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
expr_stmt|;
return|return
name|v
return|;
block|}
end_function

end_unit

