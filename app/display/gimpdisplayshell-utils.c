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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
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
file|"gimpdisplayshell-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|gdouble
DECL|function|gimp_display_shell_get_constrained_line_offset_angle (GimpDisplayShell * shell)
name|gimp_display_shell_get_constrained_line_offset_angle
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|flip_horizontally
operator|^
name|shell
operator|->
name|flip_vertically
condition|)
return|return
operator|+
name|shell
operator|->
name|rotate_angle
return|;
else|else
return|return
operator|-
name|shell
operator|->
name|rotate_angle
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_constrain_line (GimpDisplayShell * shell,gdouble start_x,gdouble start_y,gdouble * end_x,gdouble * end_y,gint n_snap_lines)
name|gimp_display_shell_constrain_line
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|start_x
parameter_list|,
name|gdouble
name|start_y
parameter_list|,
name|gdouble
modifier|*
name|end_x
parameter_list|,
name|gdouble
modifier|*
name|end_y
parameter_list|,
name|gint
name|n_snap_lines
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|end_x
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|end_y
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_constrain_line
argument_list|(
name|start_x
argument_list|,
name|start_y
argument_list|,
name|end_x
argument_list|,
name|end_y
argument_list|,
name|n_snap_lines
argument_list|,
name|gimp_display_shell_get_constrained_line_offset_angle
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_get_line_status:  * @status:    initial status text.  * @separator: separator text between the line information and @status.  * @shell:     #GimpDisplayShell this status text will be displayed for.  * @x1:        abscissa of first point.  * @y1:        ordinate of first point.  * @x2:        abscissa of second point.  * @y2:        ordinate of second point.  *  * Utility function to prepend the status message with a distance and  * angle value. Obviously this is only to be used for tools when it  * makes sense, and in particular when there is a concept of line. For  * instance when shift-clicking a painting tool or in the blend tool,  * etc.  * This utility prevents code duplication but also ensures a common  * display for every tool where such a status is needed. It will take  * into account the shell unit settings and will use the ideal digit  * precision according to current image resolution.  *  * Return value: a newly allocated string containing the enhanced status.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_display_shell_get_line_status (GimpDisplayShell * shell,const gchar * status,const gchar * separator,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|gimp_display_shell_get_line_status
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|status
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separator
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gchar
modifier|*
name|enhanced_status
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|,
name|pixel_dist
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
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
operator|!
name|image
condition|)
block|{
comment|/* This makes no sense to add line information when no image is        * attached to the display. */
return|return
name|g_strdup
argument_list|(
name|status
argument_list|)
return|;
block|}
if|if
condition|(
name|shell
operator|->
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
name|xres
operator|=
name|yres
operator|=
literal|1.0
expr_stmt|;
else|else
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|dx
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|dy
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|pixel_dist
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|dx
argument_list|)
operator|+
name|SQR
argument_list|(
name|dy
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dx
condition|)
block|{
name|angle
operator|=
name|gimp_rad_to_deg
argument_list|(
name|atan
argument_list|(
operator|(
name|dy
operator|/
name|yres
operator|)
operator|/
operator|(
name|dx
operator|/
name|xres
operator|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dx
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|dy
operator|>
literal|0
condition|)
name|angle
operator|=
literal|360.0
operator|-
name|angle
expr_stmt|;
elseif|else
if|if
condition|(
name|dy
operator|<
literal|0
condition|)
name|angle
operator|=
operator|-
name|angle
expr_stmt|;
block|}
else|else
block|{
name|angle
operator|=
literal|180.0
operator|-
name|angle
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|dy
condition|)
block|{
name|angle
operator|=
name|dy
operator|>
literal|0
condition|?
literal|270.0
else|:
literal|90.0
expr_stmt|;
block|}
else|else
block|{
name|angle
operator|=
literal|0.0
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
block|{
name|enhanced_status
operator|=
name|g_strdup_printf
argument_list|(
literal|"%.1f %s, %.2f\302\260%s%s"
argument_list|,
name|pixel_dist
argument_list|,
name|_
argument_list|(
literal|"pixels"
argument_list|)
argument_list|,
name|angle
argument_list|,
name|separator
argument_list|,
name|status
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|inch_dist
decl_stmt|;
name|gdouble
name|unit_dist
decl_stmt|;
name|gint
name|digits
init|=
literal|0
decl_stmt|;
comment|/* The distance in unit. */
name|inch_dist
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|dx
operator|/
name|xres
argument_list|)
operator|+
name|SQR
argument_list|(
name|dy
operator|/
name|yres
argument_list|)
argument_list|)
expr_stmt|;
name|unit_dist
operator|=
name|gimp_unit_get_factor
argument_list|(
name|shell
operator|->
name|unit
argument_list|)
operator|*
name|inch_dist
expr_stmt|;
comment|/* The ideal digit precision for unit in current resolution. */
if|if
condition|(
name|inch_dist
condition|)
name|digits
operator|=
name|gimp_unit_get_scaled_digits
argument_list|(
name|shell
operator|->
name|unit
argument_list|,
name|pixel_dist
operator|/
name|inch_dist
argument_list|)
expr_stmt|;
name|enhanced_status
operator|=
name|g_strdup_printf
argument_list|(
literal|"%.*f %s, %.2f\302\260%s%s"
argument_list|,
name|digits
argument_list|,
name|unit_dist
argument_list|,
name|gimp_unit_get_symbol
argument_list|(
name|shell
operator|->
name|unit
argument_list|)
argument_list|,
name|angle
argument_list|,
name|separator
argument_list|,
name|status
argument_list|)
expr_stmt|;
block|}
return|return
name|enhanced_status
return|;
block|}
end_function

end_unit
