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
file|<gtk/gtk.h>
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
file|"base/boundary.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
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
file|"gimpdisplayshell-transform.h"
end_include

begin_comment
comment|/**  * gimp_display_shell_transform_coordinate:  * @shell:          a #GimpDisplayShell  * @image_coords:   image coordinates  * @display_coords: returns the corresponding display coordinates  *  * Transforms from image coordinates to display coordinates, so that  * objects can be rendered at the correct points on the display.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_transform_coordinate (GimpDisplayShell * shell,GimpCoords * image_coords,GimpCoords * display_coords)
name|gimp_display_shell_transform_coordinate
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|image_coords
parameter_list|,
name|GimpCoords
modifier|*
name|display_coords
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
name|image_coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|display_coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|display_coords
operator|=
operator|*
name|image_coords
expr_stmt|;
name|display_coords
operator|->
name|x
operator|=
name|shell
operator|->
name|scale_x
operator|*
name|image_coords
operator|->
name|x
expr_stmt|;
name|display_coords
operator|->
name|y
operator|=
name|shell
operator|->
name|scale_y
operator|*
name|image_coords
operator|->
name|y
expr_stmt|;
name|display_coords
operator|->
name|x
operator|+=
operator|-
name|shell
operator|->
name|offset_x
operator|+
name|shell
operator|->
name|disp_xoffset
expr_stmt|;
name|display_coords
operator|->
name|y
operator|+=
operator|-
name|shell
operator|->
name|offset_y
operator|+
name|shell
operator|->
name|disp_yoffset
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_untransform_coordinate:  * @shell:          a #GimpDisplayShell  * @display_coords: display coordinates  * @image_coords:   returns the corresponding image coordinates  *  * Transforms from display coordinates to image coordinates, so that  * points on the display can be mapped to points in the image.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_untransform_coordinate (GimpDisplayShell * shell,GimpCoords * display_coords,GimpCoords * image_coords)
name|gimp_display_shell_untransform_coordinate
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCoords
modifier|*
name|display_coords
parameter_list|,
name|GimpCoords
modifier|*
name|image_coords
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
name|display_coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image_coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|image_coords
operator|=
operator|*
name|display_coords
expr_stmt|;
name|image_coords
operator|->
name|x
operator|=
name|display_coords
operator|->
name|x
operator|-
name|shell
operator|->
name|disp_xoffset
operator|+
name|shell
operator|->
name|offset_x
expr_stmt|;
name|image_coords
operator|->
name|y
operator|=
name|display_coords
operator|->
name|y
operator|-
name|shell
operator|->
name|disp_yoffset
operator|+
name|shell
operator|->
name|offset_y
expr_stmt|;
name|image_coords
operator|->
name|x
operator|/=
name|shell
operator|->
name|scale_x
expr_stmt|;
name|image_coords
operator|->
name|y
operator|/=
name|shell
operator|->
name|scale_y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_transform_xy (GimpDisplayShell * shell,gdouble x,gdouble y,gint * nx,gint * ny,gboolean use_offsets)
name|gimp_display_shell_transform_xy
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
block|{
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
name|gint64
name|tx
decl_stmt|,
name|ty
decl_stmt|;
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
name|nx
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ny
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_offsets
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
name|x
operator|+=
name|offset_x
expr_stmt|;
name|y
operator|+=
name|offset_y
expr_stmt|;
block|}
name|tx
operator|=
name|PROJ_ROUND64
argument_list|(
name|x
operator|*
name|shell
operator|->
name|x_src_dec
argument_list|)
operator|+
operator|(
name|shell
operator|->
name|x_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
expr_stmt|;
name|ty
operator|=
name|PROJ_ROUND64
argument_list|(
name|y
operator|*
name|shell
operator|->
name|y_src_dec
argument_list|)
operator|+
operator|(
name|shell
operator|->
name|y_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
expr_stmt|;
name|tx
operator|/=
name|shell
operator|->
name|x_dest_inc
expr_stmt|;
name|ty
operator|/=
name|shell
operator|->
name|y_dest_inc
expr_stmt|;
name|tx
operator|+=
name|shell
operator|->
name|disp_xoffset
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
name|ty
operator|+=
name|shell
operator|->
name|disp_yoffset
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
comment|/* The projected coordinates might overflow a gint in the case of big      images at high zoom levels, so we clamp them here to avoid problems.  */
operator|*
name|nx
operator|=
name|CLAMP
argument_list|(
name|tx
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
operator|*
name|ny
operator|=
name|CLAMP
argument_list|(
name|ty
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_untransform_xy:  * @shell:       a #GimpDisplayShell  * @x:           x coordinate in display coordinates  * @y:           y coordinate in display coordinates  * @nx:          returns x oordinate in image coordinates  * @ny:          returns y coordinate in image coordinates  * @round:       if %TRUE, round the results to the nearest integer;  *               if %FALSE, simply cast them to @gint.  * @use_offsets: if %TRUE, @nx and @ny will be returned in the coordinate  *               system of the active drawable instead of the image  *  * Transform from display coordinates to image coordinates, so that  * points on the display can be mapped to the corresponding points  * in the image.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_untransform_xy (GimpDisplayShell * shell,gint x,gint y,gint * nx,gint * ny,gboolean round,gboolean use_offsets)
name|gimp_display_shell_untransform_xy
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|,
name|gboolean
name|round
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
block|{
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
name|gint64
name|tx
decl_stmt|,
name|ty
decl_stmt|;
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
name|nx
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ny
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_offsets
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
block|}
name|tx
operator|=
name|x
operator|+
name|shell
operator|->
name|offset_x
operator|-
name|shell
operator|->
name|disp_xoffset
expr_stmt|;
name|ty
operator|=
name|y
operator|+
name|shell
operator|->
name|offset_y
operator|-
name|shell
operator|->
name|disp_yoffset
expr_stmt|;
name|tx
operator|*=
name|shell
operator|->
name|x_dest_inc
expr_stmt|;
name|ty
operator|*=
name|shell
operator|->
name|y_dest_inc
expr_stmt|;
name|tx
operator|+=
name|round
condition|?
name|shell
operator|->
name|x_dest_inc
else|:
name|shell
operator|->
name|x_dest_inc
operator|>>
literal|1
expr_stmt|;
name|ty
operator|+=
name|round
condition|?
name|shell
operator|->
name|y_dest_inc
else|:
name|shell
operator|->
name|y_dest_inc
operator|>>
literal|1
expr_stmt|;
name|tx
operator|/=
name|shell
operator|->
name|x_src_dec
expr_stmt|;
name|ty
operator|/=
name|shell
operator|->
name|y_src_dec
expr_stmt|;
operator|*
name|nx
operator|=
name|CLAMP
argument_list|(
name|tx
operator|-
name|offset_x
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
operator|*
name|ny
operator|=
name|CLAMP
argument_list|(
name|ty
operator|-
name|offset_y
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_transform_xy_f:  * @shell:       a #GimpDisplayShell  * @x:           x coordinate of point in image coordinates  * @y:           y coordinate of point in image coordinate  * @nx:          returns the transformed x coordinate  * @ny:          returns the transformed y coordinate  * @use_offsets: if %TRUE, the @x and @y coordinates are in the coordinate  *               system of the active drawable instead of the image  *  * This function is identical to gimp_display_shell_transfrom_xy(),  * except that it returns its results as doubles rather than ints.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_transform_xy_f (GimpDisplayShell * shell,gdouble x,gdouble y,gdouble * nx,gdouble * ny,gboolean use_offsets)
name|gimp_display_shell_transform_xy_f
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
block|{
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
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
name|nx
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ny
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_offsets
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
block|}
operator|*
name|nx
operator|=
name|shell
operator|->
name|scale_x
operator|*
operator|(
name|x
operator|+
name|offset_x
operator|)
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
operator|*
name|ny
operator|=
name|shell
operator|->
name|scale_y
operator|*
operator|(
name|y
operator|+
name|offset_y
operator|)
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
operator|*
name|nx
operator|+=
name|shell
operator|->
name|disp_xoffset
expr_stmt|;
operator|*
name|ny
operator|+=
name|shell
operator|->
name|disp_yoffset
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_untransform_xy_f:  * @shell:       a #GimpDisplayShell  * @x:           x coordinate in display coordinates  * @y:           y coordinate in display coordinates  * @nx:          place to return x coordinate in image coordinates  * @ny:          place to return y coordinate in image coordinates  * @use_offsets: if %TRUE, @nx and @ny will be returned in the coordinate  *               system of the active drawable instead of the image  *  * This function is identical to gimp_display_shell_untransform_xy(),  * except that the input and output coordinates are doubles rather than  * ints, and consequently there is no option related to rounding.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_untransform_xy_f (GimpDisplayShell * shell,gdouble x,gdouble y,gdouble * nx,gdouble * ny,gboolean use_offsets)
name|gimp_display_shell_untransform_xy_f
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
block|{
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
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
name|nx
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|ny
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|x
operator|-=
name|shell
operator|->
name|disp_xoffset
expr_stmt|;
name|y
operator|-=
name|shell
operator|->
name|disp_yoffset
expr_stmt|;
if|if
condition|(
name|use_offsets
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
block|}
operator|*
name|nx
operator|=
operator|(
name|x
operator|+
name|shell
operator|->
name|offset_x
operator|)
operator|/
name|shell
operator|->
name|scale_x
operator|-
name|offset_x
expr_stmt|;
operator|*
name|ny
operator|=
operator|(
name|y
operator|+
name|shell
operator|->
name|offset_y
operator|)
operator|/
name|shell
operator|->
name|scale_y
operator|-
name|offset_y
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_transform_points:  * @shell:       a #GimpDisplayShell  * @points:      array of x, y coordinate pairs  * @coords:      returns the corresponding display coordinates  * @n_points:    number of points  * @use_offsets: if %TRUE, the source coordinates are in the coordinate  *               system of the active drawable instead of the image  *  * Transforms from image coordinates to display coordinates, so that  * objects can be rendered at the correct points on the display.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_transform_points (GimpDisplayShell * shell,const gdouble * points,GdkPoint * coords,gint n_points,gboolean use_offsets)
name|gimp_display_shell_transform_points
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|points
parameter_list|,
name|GdkPoint
modifier|*
name|coords
parameter_list|,
name|gint
name|n_points
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
block|{
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_offsets
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
name|points
index|[
name|i
operator|*
literal|2
index|]
operator|+
name|offset_x
expr_stmt|;
name|y
operator|=
name|points
index|[
name|i
operator|*
literal|2
operator|+
literal|1
index|]
operator|+
name|offset_y
expr_stmt|;
name|x
operator|=
name|PROJ_ROUND64
argument_list|(
name|shell
operator|->
name|x_src_dec
operator|*
name|x
operator|+
operator|(
name|shell
operator|->
name|x_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
argument_list|)
operator|/
name|shell
operator|->
name|x_dest_inc
expr_stmt|;
name|y
operator|=
name|PROJ_ROUND64
argument_list|(
name|shell
operator|->
name|y_src_dec
operator|*
name|y
operator|+
operator|(
name|shell
operator|->
name|y_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
argument_list|)
operator|/
name|shell
operator|->
name|y_dest_inc
expr_stmt|;
name|coords
index|[
name|i
index|]
operator|.
name|x
operator|=
name|CLAMP
argument_list|(
name|x
operator|+
name|shell
operator|->
name|disp_xoffset
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
name|coords
index|[
name|i
index|]
operator|.
name|y
operator|=
name|CLAMP
argument_list|(
name|y
operator|+
name|shell
operator|->
name|disp_yoffset
operator|-
name|shell
operator|->
name|offset_y
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_transform_coords:  * @shell:        a #GimpDisplayShell  * @image_coords: array of image coordinates  * @disp_coords:  returns the corresponding display coordinates  * @n_coords:     number of coordinates  * @use_offsets:  if %TRUE, the source coordinates are in the coordinate  *                system of the active drawable instead of the image  *  * Transforms from image coordinates to display coordinates, so that  * objects can be rendered at the correct points on the display.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_transform_coords (GimpDisplayShell * shell,const GimpCoords * image_coords,GdkPoint * disp_coords,gint n_coords,gboolean use_offsets)
name|gimp_display_shell_transform_coords
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|image_coords
parameter_list|,
name|GdkPoint
modifier|*
name|disp_coords
parameter_list|,
name|gint
name|n_coords
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
block|{
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_offsets
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_coords
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
name|image_coords
index|[
name|i
index|]
operator|.
name|x
operator|+
name|offset_x
expr_stmt|;
name|y
operator|=
name|image_coords
index|[
name|i
index|]
operator|.
name|y
operator|+
name|offset_y
expr_stmt|;
name|x
operator|=
name|PROJ_ROUND64
argument_list|(
name|shell
operator|->
name|x_src_dec
operator|*
name|x
operator|+
operator|(
name|shell
operator|->
name|x_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
argument_list|)
operator|/
name|shell
operator|->
name|x_dest_inc
expr_stmt|;
name|y
operator|=
name|PROJ_ROUND64
argument_list|(
name|shell
operator|->
name|y_src_dec
operator|*
name|y
operator|+
operator|(
name|shell
operator|->
name|y_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
argument_list|)
operator|/
name|shell
operator|->
name|y_dest_inc
expr_stmt|;
name|disp_coords
index|[
name|i
index|]
operator|.
name|x
operator|=
name|CLAMP
argument_list|(
name|x
operator|+
name|shell
operator|->
name|disp_xoffset
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
name|disp_coords
index|[
name|i
index|]
operator|.
name|y
operator|=
name|CLAMP
argument_list|(
name|y
operator|+
name|shell
operator|->
name|disp_yoffset
operator|-
name|shell
operator|->
name|offset_y
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_transform_segments:  * @shell:       a #GimpDisplayShell  * @src_segs:    array of segments in image coordinates  * @dest_segs:   returns the corresponding segments in display coordinates  * @n_segs:      number of segments  * @use_offsets: if %TRUE, the source coordinates are in the coordinate  *               system of the active drawable instead of the image  *  * Transforms from image coordinates to display coordinates, so that  * objects can be rendered at the correct points on the display.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_transform_segments (GimpDisplayShell * shell,const BoundSeg * src_segs,GdkSegment * dest_segs,gint n_segs,gboolean use_offsets)
name|gimp_display_shell_transform_segments
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|BoundSeg
modifier|*
name|src_segs
parameter_list|,
name|GdkSegment
modifier|*
name|dest_segs
parameter_list|,
name|gint
name|n_segs
parameter_list|,
name|gboolean
name|use_offsets
parameter_list|)
block|{
name|gint
name|offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|offset_y
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_offsets
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_active_drawable
argument_list|(
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|item
argument_list|,
operator|&
name|offset_x
argument_list|,
operator|&
name|offset_y
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_segs
condition|;
name|i
operator|++
control|)
block|{
name|gint64
name|x1
decl_stmt|,
name|x2
decl_stmt|;
name|gint64
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|x1
operator|=
name|src_segs
index|[
name|i
index|]
operator|.
name|x1
operator|+
name|offset_x
expr_stmt|;
name|x2
operator|=
name|src_segs
index|[
name|i
index|]
operator|.
name|x2
operator|+
name|offset_x
expr_stmt|;
name|y1
operator|=
name|src_segs
index|[
name|i
index|]
operator|.
name|y1
operator|+
name|offset_y
expr_stmt|;
name|y2
operator|=
name|src_segs
index|[
name|i
index|]
operator|.
name|y2
operator|+
name|offset_y
expr_stmt|;
name|x1
operator|=
operator|(
name|x1
operator|*
name|shell
operator|->
name|x_src_dec
operator|+
operator|(
name|shell
operator|->
name|x_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
operator|)
operator|/
name|shell
operator|->
name|x_dest_inc
expr_stmt|;
name|x2
operator|=
operator|(
name|x2
operator|*
name|shell
operator|->
name|x_src_dec
operator|+
operator|(
name|shell
operator|->
name|x_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
operator|)
operator|/
name|shell
operator|->
name|x_dest_inc
expr_stmt|;
name|y1
operator|=
operator|(
name|y1
operator|*
name|shell
operator|->
name|y_src_dec
operator|+
operator|(
name|shell
operator|->
name|y_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
operator|)
operator|/
name|shell
operator|->
name|y_dest_inc
expr_stmt|;
name|y2
operator|=
operator|(
name|y2
operator|*
name|shell
operator|->
name|y_src_dec
operator|+
operator|(
name|shell
operator|->
name|y_dest_inc
operator|>>
literal|1
operator|)
operator|-
literal|1
operator|)
operator|/
name|shell
operator|->
name|y_dest_inc
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|x1
operator|=
name|CLAMP
argument_list|(
name|x1
operator|+
name|shell
operator|->
name|disp_xoffset
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|x2
operator|=
name|CLAMP
argument_list|(
name|x2
operator|+
name|shell
operator|->
name|disp_xoffset
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|y1
operator|=
name|CLAMP
argument_list|(
name|y1
operator|+
name|shell
operator|->
name|disp_yoffset
operator|-
name|shell
operator|->
name|offset_y
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
name|dest_segs
index|[
name|i
index|]
operator|.
name|y2
operator|=
name|CLAMP
argument_list|(
name|y2
operator|+
name|shell
operator|->
name|disp_yoffset
operator|-
name|shell
operator|->
name|offset_y
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_untransform_viewport:  * @shell:  a #GimpDisplayShell  * @x:      returns image x coordinate of display upper left corner  * @y:      returns image y coordinate of display upper left corner  * @width:  returns width of display measured in image coordinates  * @height: returns height of display measured in image coordinates  *  * This function calculates the part of the image, im image coordinates,  * that corresponds to the display viewport.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_untransform_viewport (GimpDisplayShell * shell,gint * x,gint * y,gint * width,gint * height)
name|gimp_display_shell_untransform_viewport
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_untransform_xy
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_untransform_xy
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|disp_width
argument_list|,
name|shell
operator|->
name|disp_height
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x1
operator|<
literal|0
condition|)
name|x1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|y1
operator|<
literal|0
condition|)
name|y1
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|x2
operator|>
name|shell
operator|->
name|display
operator|->
name|image
operator|->
name|width
condition|)
name|x2
operator|=
name|shell
operator|->
name|display
operator|->
name|image
operator|->
name|width
expr_stmt|;
if|if
condition|(
name|y2
operator|>
name|shell
operator|->
name|display
operator|->
name|image
operator|->
name|height
condition|)
name|y2
operator|=
name|shell
operator|->
name|display
operator|->
name|image
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|x
condition|)
operator|*
name|x
operator|=
name|x1
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
name|y1
expr_stmt|;
if|if
condition|(
name|width
condition|)
operator|*
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
if|if
condition|(
name|height
condition|)
operator|*
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
block|}
end_function

end_unit

