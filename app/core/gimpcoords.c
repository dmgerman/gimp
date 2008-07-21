begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcoords.c  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpcoords.h"
end_include

begin_define
DECL|macro|INPUT_RESOLUTION
define|#
directive|define
name|INPUT_RESOLUTION
value|256
end_define

begin_comment
comment|/*   amul * a + bmul * b = ret_val  */
end_comment

begin_function
name|void
DECL|function|gimp_coords_mix (const gdouble amul,const GimpCoords * a,const gdouble bmul,const GimpCoords * b,GimpCoords * ret_val)
name|gimp_coords_mix
parameter_list|(
specifier|const
name|gdouble
name|amul
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|gdouble
name|bmul
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|ret_val
parameter_list|)
block|{
if|if
condition|(
name|b
condition|)
block|{
name|ret_val
operator|->
name|x
operator|=
name|amul
operator|*
name|a
operator|->
name|x
operator|+
name|bmul
operator|*
name|b
operator|->
name|x
expr_stmt|;
name|ret_val
operator|->
name|y
operator|=
name|amul
operator|*
name|a
operator|->
name|y
operator|+
name|bmul
operator|*
name|b
operator|->
name|y
expr_stmt|;
name|ret_val
operator|->
name|pressure
operator|=
name|amul
operator|*
name|a
operator|->
name|pressure
operator|+
name|bmul
operator|*
name|b
operator|->
name|pressure
expr_stmt|;
name|ret_val
operator|->
name|xtilt
operator|=
name|amul
operator|*
name|a
operator|->
name|xtilt
operator|+
name|bmul
operator|*
name|b
operator|->
name|xtilt
expr_stmt|;
name|ret_val
operator|->
name|ytilt
operator|=
name|amul
operator|*
name|a
operator|->
name|ytilt
operator|+
name|bmul
operator|*
name|b
operator|->
name|ytilt
expr_stmt|;
name|ret_val
operator|->
name|wheel
operator|=
name|amul
operator|*
name|a
operator|->
name|wheel
operator|+
name|bmul
operator|*
name|b
operator|->
name|wheel
expr_stmt|;
name|ret_val
operator|->
name|velocity
operator|=
name|amul
operator|*
name|a
operator|->
name|velocity
operator|+
name|bmul
operator|*
name|b
operator|->
name|velocity
expr_stmt|;
block|}
else|else
block|{
name|ret_val
operator|->
name|x
operator|=
name|amul
operator|*
name|a
operator|->
name|x
expr_stmt|;
name|ret_val
operator|->
name|y
operator|=
name|amul
operator|*
name|a
operator|->
name|y
expr_stmt|;
name|ret_val
operator|->
name|pressure
operator|=
name|amul
operator|*
name|a
operator|->
name|pressure
expr_stmt|;
name|ret_val
operator|->
name|xtilt
operator|=
name|amul
operator|*
name|a
operator|->
name|xtilt
expr_stmt|;
name|ret_val
operator|->
name|ytilt
operator|=
name|amul
operator|*
name|a
operator|->
name|ytilt
expr_stmt|;
name|ret_val
operator|->
name|wheel
operator|=
name|amul
operator|*
name|a
operator|->
name|wheel
expr_stmt|;
name|ret_val
operator|->
name|velocity
operator|=
name|amul
operator|*
name|a
operator|->
name|velocity
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*    (a+b)/2 = ret_average  */
end_comment

begin_function
name|void
DECL|function|gimp_coords_average (const GimpCoords * a,const GimpCoords * b,GimpCoords * ret_average)
name|gimp_coords_average
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|ret_average
parameter_list|)
block|{
name|gimp_coords_mix
argument_list|(
literal|0.5
argument_list|,
name|a
argument_list|,
literal|0.5
argument_list|,
name|b
argument_list|,
name|ret_average
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* a + b = ret_add  */
end_comment

begin_function
name|void
DECL|function|gimp_coords_add (const GimpCoords * a,const GimpCoords * b,GimpCoords * ret_add)
name|gimp_coords_add
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|ret_add
parameter_list|)
block|{
name|gimp_coords_mix
argument_list|(
literal|1.0
argument_list|,
name|a
argument_list|,
literal|1.0
argument_list|,
name|b
argument_list|,
name|ret_add
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* a - b = ret_difference */
end_comment

begin_function
name|void
DECL|function|gimp_coords_difference (const GimpCoords * a,const GimpCoords * b,GimpCoords * ret_difference)
name|gimp_coords_difference
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|,
name|GimpCoords
modifier|*
name|ret_difference
parameter_list|)
block|{
name|gimp_coords_mix
argument_list|(
literal|1.0
argument_list|,
name|a
argument_list|,
operator|-
literal|1.0
argument_list|,
name|b
argument_list|,
name|ret_difference
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* a * f = ret_product  */
end_comment

begin_function
name|void
DECL|function|gimp_coords_scale (const gdouble f,const GimpCoords * a,GimpCoords * ret_product)
name|gimp_coords_scale
parameter_list|(
specifier|const
name|gdouble
name|f
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
name|GimpCoords
modifier|*
name|ret_product
parameter_list|)
block|{
name|gimp_coords_mix
argument_list|(
name|f
argument_list|,
name|a
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|ret_product
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* local helper for measuring the scalarproduct of two gimpcoords. */
end_comment

begin_function
name|gdouble
DECL|function|gimp_coords_scalarprod (const GimpCoords * a,const GimpCoords * b)
name|gimp_coords_scalarprod
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|)
block|{
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
name|pressure
operator|*
name|b
operator|->
name|pressure
operator|+
name|a
operator|->
name|xtilt
operator|*
name|b
operator|->
name|xtilt
operator|+
name|a
operator|->
name|ytilt
operator|*
name|b
operator|->
name|ytilt
operator|+
name|a
operator|->
name|wheel
operator|*
name|b
operator|->
name|wheel
operator|+
name|a
operator|->
name|velocity
operator|*
name|a
operator|->
name|velocity
operator|)
return|;
block|}
end_function

begin_comment
comment|/*  * The "lenght" of the gimpcoord.  * Applies a metric that increases the weight on the  * pressure/xtilt/ytilt/wheel to ensure proper interpolation  */
end_comment

begin_function
name|gdouble
DECL|function|gimp_coords_length_squared (const GimpCoords * a)
name|gimp_coords_length_squared
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|)
block|{
name|GimpCoords
name|upscaled_a
decl_stmt|;
name|upscaled_a
operator|.
name|x
operator|=
name|a
operator|->
name|x
expr_stmt|;
name|upscaled_a
operator|.
name|y
operator|=
name|a
operator|->
name|y
expr_stmt|;
name|upscaled_a
operator|.
name|pressure
operator|=
name|a
operator|->
name|pressure
operator|*
name|INPUT_RESOLUTION
expr_stmt|;
name|upscaled_a
operator|.
name|xtilt
operator|=
name|a
operator|->
name|xtilt
operator|*
name|INPUT_RESOLUTION
expr_stmt|;
name|upscaled_a
operator|.
name|ytilt
operator|=
name|a
operator|->
name|ytilt
operator|*
name|INPUT_RESOLUTION
expr_stmt|;
name|upscaled_a
operator|.
name|wheel
operator|=
name|a
operator|->
name|wheel
operator|*
name|INPUT_RESOLUTION
expr_stmt|;
name|upscaled_a
operator|.
name|velocity
operator|=
name|a
operator|->
name|velocity
operator|*
name|INPUT_RESOLUTION
expr_stmt|;
return|return
name|gimp_coords_scalarprod
argument_list|(
operator|&
name|upscaled_a
argument_list|,
operator|&
name|upscaled_a
argument_list|)
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_coords_length (const GimpCoords * a)
name|gimp_coords_length
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|)
block|{
return|return
name|sqrt
argument_list|(
name|gimp_coords_length_squared
argument_list|(
name|a
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * Distance via manhattan metric, an upper bound for the eucledian metric.  * used for e.g. bezier approximation  */
end_comment

begin_function
name|gdouble
DECL|function|gimp_coords_manhattan_dist (const GimpCoords * a,const GimpCoords * b)
name|gimp_coords_manhattan_dist
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|)
block|{
name|gdouble
name|dist
init|=
literal|0
decl_stmt|;
name|dist
operator|+=
name|ABS
argument_list|(
name|a
operator|->
name|pressure
operator|-
name|b
operator|->
name|pressure
argument_list|)
expr_stmt|;
name|dist
operator|+=
name|ABS
argument_list|(
name|a
operator|->
name|xtilt
operator|-
name|b
operator|->
name|xtilt
argument_list|)
expr_stmt|;
name|dist
operator|+=
name|ABS
argument_list|(
name|a
operator|->
name|ytilt
operator|-
name|b
operator|->
name|ytilt
argument_list|)
expr_stmt|;
name|dist
operator|+=
name|ABS
argument_list|(
name|a
operator|->
name|wheel
operator|-
name|b
operator|->
name|wheel
argument_list|)
expr_stmt|;
name|dist
operator|+=
name|ABS
argument_list|(
name|a
operator|->
name|velocity
operator|-
name|b
operator|->
name|velocity
argument_list|)
expr_stmt|;
name|dist
operator|*=
name|INPUT_RESOLUTION
expr_stmt|;
name|dist
operator|+=
name|ABS
argument_list|(
name|a
operator|->
name|x
operator|-
name|b
operator|->
name|x
argument_list|)
expr_stmt|;
name|dist
operator|+=
name|ABS
argument_list|(
name|a
operator|->
name|y
operator|-
name|b
operator|->
name|y
argument_list|)
expr_stmt|;
return|return
name|dist
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_coords_equal (const GimpCoords * a,const GimpCoords * b)
name|gimp_coords_equal
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|b
parameter_list|)
block|{
return|return
operator|(
name|a
operator|->
name|x
operator|==
name|b
operator|->
name|x
operator|&&
name|a
operator|->
name|y
operator|==
name|b
operator|->
name|y
operator|&&
name|a
operator|->
name|pressure
operator|==
name|b
operator|->
name|pressure
operator|&&
name|a
operator|->
name|xtilt
operator|==
name|b
operator|->
name|xtilt
operator|&&
name|a
operator|->
name|ytilt
operator|==
name|b
operator|->
name|ytilt
operator|&&
name|a
operator|->
name|wheel
operator|==
name|b
operator|->
name|wheel
operator|&&
name|a
operator|->
name|velocity
operator|==
name|b
operator|->
name|velocity
operator|)
return|;
block|}
end_function

end_unit

