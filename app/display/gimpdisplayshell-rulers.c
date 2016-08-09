begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-rulers.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale.h"
end_include

begin_comment
comment|/**  * gimp_display_shell_rulers_update:  * @shell:  *  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_rulers_update (GimpDisplayShell * shell)
name|gimp_display_shell_rulers_update
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gdouble
name|offset_x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|offset_y
init|=
literal|0.0
decl_stmt|;
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
name|gdouble
name|resolution_x
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|resolution_y
init|=
literal|1.0
decl_stmt|;
name|gdouble
name|horizontal_lower
decl_stmt|;
name|gdouble
name|horizontal_upper
decl_stmt|;
name|gdouble
name|horizontal_max_size
decl_stmt|;
name|gdouble
name|vertical_lower
decl_stmt|;
name|gdouble
name|vertical_upper
decl_stmt|;
name|gdouble
name|vertical_max_size
decl_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|display
condition|)
return|return;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gint
name|image_x
decl_stmt|,
name|image_y
decl_stmt|;
name|gdouble
name|res_x
decl_stmt|,
name|res_y
decl_stmt|;
name|gimp_display_shell_scale_get_image_bounds
argument_list|(
name|shell
argument_list|,
operator|&
name|image_x
argument_list|,
operator|&
name|image_y
argument_list|,
operator|&
name|image_width
argument_list|,
operator|&
name|image_height
argument_list|)
expr_stmt|;
name|gimp_display_shell_get_rotated_scale
argument_list|(
name|shell
argument_list|,
operator|&
name|scale_x
argument_list|,
operator|&
name|scale_y
argument_list|)
expr_stmt|;
name|image_width
operator|/=
name|scale_x
expr_stmt|;
name|image_height
operator|/=
name|scale_y
expr_stmt|;
name|offset_x
operator|=
name|shell
operator|->
name|offset_x
operator|-
name|image_x
expr_stmt|;
name|offset_y
operator|=
name|shell
operator|->
name|offset_y
operator|-
name|image_y
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|res_x
argument_list|,
operator|&
name|res_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|rotate_angle
operator|==
literal|0.0
operator|||
name|res_x
operator|==
name|res_y
condition|)
block|{
name|resolution_x
operator|=
name|res_x
expr_stmt|;
name|resolution_y
operator|=
name|res_y
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|cos_a
init|=
name|cos
argument_list|(
name|G_PI
operator|*
name|shell
operator|->
name|rotate_angle
operator|/
literal|180.0
argument_list|)
decl_stmt|;
name|gdouble
name|sin_a
init|=
name|sin
argument_list|(
name|G_PI
operator|*
name|shell
operator|->
name|rotate_angle
operator|/
literal|180.0
argument_list|)
decl_stmt|;
if|if
condition|(
name|shell
operator|->
name|dot_for_dot
condition|)
block|{
name|resolution_x
operator|=
literal|1.0
operator|/
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|cos_a
operator|/
name|res_x
argument_list|)
operator|+
name|SQR
argument_list|(
name|sin_a
operator|/
name|res_y
argument_list|)
argument_list|)
expr_stmt|;
name|resolution_y
operator|=
literal|1.0
operator|/
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|cos_a
operator|/
name|res_y
argument_list|)
operator|+
name|SQR
argument_list|(
name|sin_a
operator|/
name|res_x
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|resolution_x
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|res_x
operator|*
name|cos_a
argument_list|)
operator|+
name|SQR
argument_list|(
name|res_y
operator|*
name|sin_a
argument_list|)
argument_list|)
expr_stmt|;
name|resolution_y
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|res_y
operator|*
name|cos_a
argument_list|)
operator|+
name|SQR
argument_list|(
name|res_x
operator|*
name|sin_a
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|image_width
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
name|image_height
operator|=
name|shell
operator|->
name|disp_height
expr_stmt|;
block|}
comment|/* Initialize values */
name|horizontal_lower
operator|=
literal|0
expr_stmt|;
name|vertical_lower
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|horizontal_upper
operator|=
name|gimp_pixels_to_units
argument_list|(
name|shell
operator|->
name|disp_width
operator|/
name|scale_x
argument_list|,
name|shell
operator|->
name|unit
argument_list|,
name|resolution_x
argument_list|)
expr_stmt|;
name|horizontal_max_size
operator|=
name|gimp_pixels_to_units
argument_list|(
name|MAX
argument_list|(
name|image_width
argument_list|,
name|image_height
argument_list|)
argument_list|,
name|shell
operator|->
name|unit
argument_list|,
name|resolution_x
argument_list|)
expr_stmt|;
name|vertical_upper
operator|=
name|gimp_pixels_to_units
argument_list|(
name|shell
operator|->
name|disp_height
operator|/
name|scale_y
argument_list|,
name|shell
operator|->
name|unit
argument_list|,
name|resolution_y
argument_list|)
expr_stmt|;
name|vertical_max_size
operator|=
name|gimp_pixels_to_units
argument_list|(
name|MAX
argument_list|(
name|image_width
argument_list|,
name|image_height
argument_list|)
argument_list|,
name|shell
operator|->
name|unit
argument_list|,
name|resolution_y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|horizontal_upper
operator|=
name|image_width
expr_stmt|;
name|horizontal_max_size
operator|=
name|MAX
argument_list|(
name|image_width
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
name|vertical_upper
operator|=
name|image_height
expr_stmt|;
name|vertical_max_size
operator|=
name|MAX
argument_list|(
name|image_width
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
block|}
comment|/* Adjust due to scrolling */
if|if
condition|(
name|image
condition|)
block|{
name|offset_x
operator|*=
name|horizontal_upper
operator|/
name|shell
operator|->
name|disp_width
expr_stmt|;
name|offset_y
operator|*=
name|vertical_upper
operator|/
name|shell
operator|->
name|disp_height
expr_stmt|;
name|horizontal_lower
operator|+=
name|offset_x
expr_stmt|;
name|horizontal_upper
operator|+=
name|offset_x
expr_stmt|;
name|vertical_lower
operator|+=
name|offset_y
expr_stmt|;
name|vertical_upper
operator|+=
name|offset_y
expr_stmt|;
block|}
comment|/* Finally setup the actual rulers */
name|gimp_ruler_set_range
argument_list|(
name|GIMP_RULER
argument_list|(
name|shell
operator|->
name|hrule
argument_list|)
argument_list|,
name|horizontal_lower
argument_list|,
name|horizontal_upper
argument_list|,
name|horizontal_max_size
argument_list|)
expr_stmt|;
name|gimp_ruler_set_unit
argument_list|(
name|GIMP_RULER
argument_list|(
name|shell
operator|->
name|hrule
argument_list|)
argument_list|,
name|shell
operator|->
name|unit
argument_list|)
expr_stmt|;
name|gimp_ruler_set_range
argument_list|(
name|GIMP_RULER
argument_list|(
name|shell
operator|->
name|vrule
argument_list|)
argument_list|,
name|vertical_lower
argument_list|,
name|vertical_upper
argument_list|,
name|vertical_max_size
argument_list|)
expr_stmt|;
name|gimp_ruler_set_unit
argument_list|(
name|GIMP_RULER
argument_list|(
name|shell
operator|->
name|vrule
argument_list|)
argument_list|,
name|shell
operator|->
name|unit
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

