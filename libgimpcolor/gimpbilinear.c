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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpbilinear.h"
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
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
literal|0.0
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
name|x
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|x
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
name|x
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|x
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
name|y
operator|)
operator|*
name|m0
operator|+
name|y
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
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
literal|0
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
name|x
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|x
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
name|x
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|x
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
name|y
operator|)
operator|*
name|m0
operator|+
name|y
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
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
literal|0
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
name|x
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|x
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
name|x
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|x
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
name|y
operator|)
operator|*
name|m0
operator|+
name|y
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
name|m0
decl_stmt|,
name|m1
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
literal|0
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
name|x
operator|)
operator|*
name|values
index|[
literal|0
index|]
operator|+
name|x
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
name|x
operator|)
operator|*
name|values
index|[
literal|2
index|]
operator|+
name|x
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
name|y
operator|)
operator|*
name|m0
operator|+
name|y
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
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
name|v
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
name|gdouble
name|a0
decl_stmt|,
name|a1
decl_stmt|,
name|a2
decl_stmt|,
name|a3
decl_stmt|,
name|alpha
decl_stmt|;
name|GimpRGB
name|v
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|,
name|v
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
name|a0
operator|=
name|values
index|[
literal|0
index|]
operator|.
name|a
expr_stmt|;
name|a1
operator|=
name|values
index|[
literal|1
index|]
operator|.
name|a
expr_stmt|;
name|a2
operator|=
name|values
index|[
literal|2
index|]
operator|.
name|a
expr_stmt|;
name|a3
operator|=
name|values
index|[
literal|3
index|]
operator|.
name|a
expr_stmt|;
comment|/* Alpha */
name|m0
operator|=
name|ix
operator|*
name|a0
operator|+
name|x
operator|*
name|a1
expr_stmt|;
name|m1
operator|=
name|ix
operator|*
name|a2
operator|+
name|x
operator|*
name|a3
expr_stmt|;
name|alpha
operator|=
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
if|if
condition|(
name|alpha
operator|>
literal|0
condition|)
block|{
comment|/* Red */
name|m0
operator|=
name|ix
operator|*
name|a0
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
name|a1
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
name|a2
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
name|a3
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
operator|(
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
operator|)
operator|/
name|alpha
expr_stmt|;
comment|/* Green */
name|m0
operator|=
name|ix
operator|*
name|a0
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
name|a1
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
name|a2
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
name|a3
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
operator|(
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
operator|)
operator|/
name|alpha
expr_stmt|;
comment|/* Blue */
name|m0
operator|=
name|ix
operator|*
name|a0
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
name|a1
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
name|a2
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
name|a3
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
operator|(
name|iy
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
operator|)
operator|/
name|alpha
expr_stmt|;
block|}
return|return
name|v
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_bilinear_pixels_8:  * @dest: Pixel, where interpolation result is to be stored.  * @x: x-coordinate (0.0 to 1.0).  * @y: y-coordinate (0.0 to 1.0).  * @bpp: Bytes per pixel.  @dest and each @values item is an array of  *    @bpp bytes.  * @has_alpha: %TRUE if the last channel is an alpha channel.  * @values: Array of four pointers to pixels.  *  * Computes bilinear interpolation of four pixels.  *  * When @has_alpha is %FALSE, it's identical to gimp_bilinear_8() on  * each channel separately.  When @has_alpha is %TRUE, it handles  * alpha channel correctly.  *  * The pixels in @values correspond to corner x, y coordinates in the  * following order: [0,0], [1,0], [0,1], [1,1].  **/
end_comment

begin_function
name|void
DECL|function|gimp_bilinear_pixels_8 (guchar * dest,gdouble x,gdouble y,guint bpp,gboolean has_alpha,guchar ** values)
name|gimp_bilinear_pixels_8
parameter_list|(
name|guchar
modifier|*
name|dest
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|guint
name|bpp
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|guchar
modifier|*
modifier|*
name|values
parameter_list|)
block|{
name|guint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|dest
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
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
if|if
condition|(
name|has_alpha
condition|)
block|{
name|guint
name|ai
init|=
name|bpp
operator|-
literal|1
decl_stmt|;
name|gdouble
name|alpha0
init|=
name|values
index|[
literal|0
index|]
index|[
name|ai
index|]
decl_stmt|;
name|gdouble
name|alpha1
init|=
name|values
index|[
literal|1
index|]
index|[
name|ai
index|]
decl_stmt|;
name|gdouble
name|alpha2
init|=
name|values
index|[
literal|2
index|]
index|[
name|ai
index|]
decl_stmt|;
name|gdouble
name|alpha3
init|=
name|values
index|[
literal|3
index|]
index|[
name|ai
index|]
decl_stmt|;
name|gdouble
name|alpha
init|=
operator|(
operator|(
literal|1.0
operator|-
name|y
operator|)
operator|*
operator|(
operator|(
literal|1.0
operator|-
name|x
operator|)
operator|*
name|alpha0
operator|+
name|x
operator|*
name|alpha1
operator|)
operator|+
name|y
operator|*
operator|(
operator|(
literal|1.0
operator|-
name|x
operator|)
operator|*
name|alpha2
operator|+
name|x
operator|*
name|alpha3
operator|)
operator|)
decl_stmt|;
name|dest
index|[
name|ai
index|]
operator|=
operator|(
name|guchar
operator|)
name|alpha
expr_stmt|;
if|if
condition|(
name|dest
index|[
name|ai
index|]
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ai
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|m0
init|=
operator|(
operator|(
literal|1.0
operator|-
name|x
operator|)
operator|*
name|values
index|[
literal|0
index|]
index|[
name|i
index|]
operator|*
name|alpha0
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
index|[
name|i
index|]
operator|*
name|alpha1
operator|)
decl_stmt|;
name|gdouble
name|m1
init|=
operator|(
operator|(
literal|1.0
operator|-
name|x
operator|)
operator|*
name|values
index|[
literal|2
index|]
index|[
name|i
index|]
operator|*
name|alpha2
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
index|[
name|i
index|]
operator|*
name|alpha3
operator|)
decl_stmt|;
name|dest
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
operator|(
literal|1.0
operator|-
name|y
operator|)
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
operator|)
operator|/
name|alpha
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bpp
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|m0
init|=
operator|(
literal|1.0
operator|-
name|x
operator|)
operator|*
name|values
index|[
literal|0
index|]
index|[
name|i
index|]
operator|+
name|x
operator|*
name|values
index|[
literal|1
index|]
index|[
name|i
index|]
decl_stmt|;
name|gdouble
name|m1
init|=
operator|(
literal|1.0
operator|-
name|x
operator|)
operator|*
name|values
index|[
literal|2
index|]
index|[
name|i
index|]
operator|+
name|x
operator|*
name|values
index|[
literal|3
index|]
index|[
name|i
index|]
decl_stmt|;
name|dest
index|[
name|i
index|]
operator|=
call|(
name|guchar
call|)
argument_list|(
operator|(
literal|1.0
operator|-
name|y
operator|)
operator|*
name|m0
operator|+
name|y
operator|*
name|m1
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

