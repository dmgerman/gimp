begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpcurve.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurve-map.h"
end_include

begin_function
name|gdouble
DECL|function|gimp_curve_map_value (GimpCurve * curve,gdouble value)
name|gimp_curve_map_value
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CURVE
argument_list|(
name|curve
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|curve
operator|->
name|identity
condition|)
block|{
return|return
name|value
return|;
block|}
if|if
condition|(
name|value
operator|<
literal|0.0
condition|)
block|{
return|return
name|curve
operator|->
name|samples
index|[
literal|0
index|]
return|;
block|}
elseif|else
if|if
condition|(
name|value
operator|>=
literal|1.0
condition|)
block|{
return|return
name|curve
operator|->
name|samples
index|[
name|curve
operator|->
name|n_samples
operator|-
literal|1
index|]
return|;
block|}
else|else
comment|/* interpolate the curve */
block|{
name|gint
name|index
init|=
name|floor
argument_list|(
name|value
operator|*
call|(
name|gdouble
call|)
argument_list|(
name|curve
operator|->
name|n_samples
operator|-
literal|1
argument_list|)
argument_list|)
decl_stmt|;
name|gdouble
name|f
init|=
name|value
operator|*
call|(
name|gdouble
call|)
argument_list|(
name|curve
operator|->
name|n_samples
operator|-
literal|1
argument_list|)
operator|-
name|index
decl_stmt|;
return|return
operator|(
literal|1.0
operator|-
name|f
operator|)
operator|*
name|curve
operator|->
name|samples
index|[
name|index
index|]
operator|+
name|f
operator|*
name|curve
operator|->
name|samples
index|[
name|index
operator|+
literal|1
index|]
return|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_curve_map_pixels (GimpCurve * curve_all,GimpCurve * curve_red,GimpCurve * curve_green,GimpCurve * curve_blue,GimpCurve * curve_alpha,gfloat * src,gfloat * dest,glong samples)
name|gimp_curve_map_pixels
parameter_list|(
name|GimpCurve
modifier|*
name|curve_all
parameter_list|,
name|GimpCurve
modifier|*
name|curve_red
parameter_list|,
name|GimpCurve
modifier|*
name|curve_green
parameter_list|,
name|GimpCurve
modifier|*
name|curve_blue
parameter_list|,
name|GimpCurve
modifier|*
name|curve_alpha
parameter_list|,
name|gfloat
modifier|*
name|src
parameter_list|,
name|gfloat
modifier|*
name|dest
parameter_list|,
name|glong
name|samples
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVE
argument_list|(
name|curve_all
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVE
argument_list|(
name|curve_red
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVE
argument_list|(
name|curve_green
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVE
argument_list|(
name|curve_blue
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURVE
argument_list|(
name|curve_alpha
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|samples
operator|--
condition|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|gimp_curve_map_value
argument_list|(
name|curve_all
argument_list|,
name|gimp_curve_map_value
argument_list|(
name|curve_red
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|gimp_curve_map_value
argument_list|(
name|curve_all
argument_list|,
name|gimp_curve_map_value
argument_list|(
name|curve_green
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|gimp_curve_map_value
argument_list|(
name|curve_all
argument_list|,
name|gimp_curve_map_value
argument_list|(
name|curve_blue
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|)
argument_list|)
expr_stmt|;
comment|/* don't apply the overall curve to the alpha channel */
name|dest
index|[
literal|3
index|]
operator|=
name|gimp_curve_map_value
argument_list|(
name|curve_alpha
argument_list|,
name|src
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

end_unit

