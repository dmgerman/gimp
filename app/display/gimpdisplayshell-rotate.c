begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpdisplayshell-expose.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-render.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-rotate.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scroll.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_define
DECL|macro|ANGLE_EPSILON
define|#
directive|define
name|ANGLE_EPSILON
value|1e-3
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_save_viewport_center
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_restore_viewport_center
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
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_flip (GimpDisplayShell * shell,gboolean flip_horizontally,gboolean flip_vertically)
name|gimp_display_shell_flip
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|flip_horizontally
parameter_list|,
name|gboolean
name|flip_vertically
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
name|flip_horizontally
operator|=
name|flip_horizontally
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|flip_vertically
operator|=
name|flip_vertically
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|flip_horizontally
operator|!=
name|shell
operator|->
name|flip_horizontally
operator|||
name|flip_vertically
operator|!=
name|shell
operator|->
name|flip_vertically
condition|)
block|{
name|gdouble
name|cx
decl_stmt|,
name|cy
decl_stmt|;
comment|/* Maintain the current center of the viewport. */
name|gimp_display_shell_save_viewport_center
argument_list|(
name|shell
argument_list|,
operator|&
name|cx
argument_list|,
operator|&
name|cy
argument_list|)
expr_stmt|;
comment|/* Adjust the rotation angle so that the image gets reflected across the        * horizontal, and/or vertical, axes in screen space, regardless of the        * current rotation.        */
if|if
condition|(
name|flip_horizontally
operator|==
name|shell
operator|->
name|flip_horizontally
operator|||
name|flip_vertically
operator|==
name|shell
operator|->
name|flip_vertically
condition|)
block|{
if|if
condition|(
name|shell
operator|->
name|rotate_angle
operator|!=
literal|0.0
condition|)
name|shell
operator|->
name|rotate_angle
operator|=
literal|360.0
operator|-
name|shell
operator|->
name|rotate_angle
expr_stmt|;
block|}
name|shell
operator|->
name|flip_horizontally
operator|=
name|flip_horizontally
expr_stmt|;
name|shell
operator|->
name|flip_vertically
operator|=
name|flip_vertically
expr_stmt|;
name|gimp_display_shell_rotated
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_restore_viewport_center
argument_list|(
name|shell
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|)
expr_stmt|;
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_render_invalidate_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_rotate (GimpDisplayShell * shell,gdouble delta)
name|gimp_display_shell_rotate
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|delta
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
name|gimp_display_shell_rotate_to
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|rotate_angle
operator|+
name|delta
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_rotate_to (GimpDisplayShell * shell,gdouble value)
name|gimp_display_shell_rotate_to
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|gdouble
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Maintain the current center of the viewport. */
name|gimp_display_shell_save_viewport_center
argument_list|(
name|shell
argument_list|,
operator|&
name|cx
argument_list|,
operator|&
name|cy
argument_list|)
expr_stmt|;
comment|/* Make sure the angle is within the range [0, 360). */
name|value
operator|=
name|fmod
argument_list|(
name|value
argument_list|,
literal|360.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|<
literal|0.0
condition|)
name|value
operator|+=
literal|360.0
expr_stmt|;
name|shell
operator|->
name|rotate_angle
operator|=
name|value
expr_stmt|;
name|gimp_display_shell_scroll_clamp_and_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_rotated
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_restore_viewport_center
argument_list|(
name|shell
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|)
expr_stmt|;
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_render_invalidate_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_rotate_drag (GimpDisplayShell * shell,gdouble last_x,gdouble last_y,gdouble cur_x,gdouble cur_y,gboolean constrain)
name|gimp_display_shell_rotate_drag
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|last_x
parameter_list|,
name|gdouble
name|last_y
parameter_list|,
name|gdouble
name|cur_x
parameter_list|,
name|gdouble
name|cur_y
parameter_list|,
name|gboolean
name|constrain
parameter_list|)
block|{
name|gdouble
name|pivot_x
decl_stmt|,
name|pivot_y
decl_stmt|;
name|gdouble
name|src_x
decl_stmt|,
name|src_y
decl_stmt|,
name|src_angle
decl_stmt|;
name|gdouble
name|dest_x
decl_stmt|,
name|dest_y
decl_stmt|,
name|dest_angle
decl_stmt|;
name|gdouble
name|delta_angle
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Rotate the image around the center of the viewport. */
name|pivot_x
operator|=
name|shell
operator|->
name|disp_width
operator|/
literal|2.0
expr_stmt|;
name|pivot_y
operator|=
name|shell
operator|->
name|disp_height
operator|/
literal|2.0
expr_stmt|;
name|src_x
operator|=
name|last_x
operator|-
name|pivot_x
expr_stmt|;
name|src_y
operator|=
name|last_y
operator|-
name|pivot_y
expr_stmt|;
name|src_angle
operator|=
name|atan2
argument_list|(
name|src_y
argument_list|,
name|src_x
argument_list|)
expr_stmt|;
name|dest_x
operator|=
name|cur_x
operator|-
name|pivot_x
expr_stmt|;
name|dest_y
operator|=
name|cur_y
operator|-
name|pivot_y
expr_stmt|;
name|dest_angle
operator|=
name|atan2
argument_list|(
name|dest_y
argument_list|,
name|dest_x
argument_list|)
expr_stmt|;
name|delta_angle
operator|=
name|dest_angle
operator|-
name|src_angle
expr_stmt|;
name|shell
operator|->
name|rotate_drag_angle
operator|+=
literal|180.0
operator|*
name|delta_angle
operator|/
name|G_PI
expr_stmt|;
name|gimp_display_shell_rotate_to
argument_list|(
name|shell
argument_list|,
name|constrain
condition|?
name|RINT
argument_list|(
name|shell
operator|->
name|rotate_drag_angle
operator|/
literal|15.0
argument_list|)
operator|*
literal|15.0
else|:
name|shell
operator|->
name|rotate_drag_angle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_rotate_update_transform (GimpDisplayShell * shell)
name|gimp_display_shell_rotate_update_transform
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
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
name|g_clear_pointer
argument_list|(
operator|&
name|shell
operator|->
name|rotate_transform
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|shell
operator|->
name|rotate_untransform
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
if|if
condition|(
name|fabs
argument_list|(
name|shell
operator|->
name|rotate_angle
argument_list|)
operator|<
name|ANGLE_EPSILON
operator|||
name|fabs
argument_list|(
literal|360.0
operator|-
name|shell
operator|->
name|rotate_angle
argument_list|)
operator|<
name|ANGLE_EPSILON
condition|)
name|shell
operator|->
name|rotate_angle
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
operator|(
name|shell
operator|->
name|rotate_angle
operator|!=
literal|0.0
operator|||
name|shell
operator|->
name|flip_horizontally
operator|||
name|shell
operator|->
name|flip_vertically
operator|)
operator|&&
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|gint
name|image_width
decl_stmt|,
name|image_height
decl_stmt|;
name|gdouble
name|cx
decl_stmt|,
name|cy
decl_stmt|;
name|shell
operator|->
name|rotate_transform
operator|=
name|g_new
argument_list|(
name|cairo_matrix_t
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|shell
operator|->
name|rotate_untransform
operator|=
name|g_new
argument_list|(
name|cairo_matrix_t
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_get_image_size
argument_list|(
name|shell
argument_list|,
operator|&
name|image_width
argument_list|,
operator|&
name|image_height
argument_list|)
expr_stmt|;
name|cx
operator|=
operator|-
name|shell
operator|->
name|offset_x
operator|+
name|image_width
operator|/
literal|2
expr_stmt|;
name|cy
operator|=
operator|-
name|shell
operator|->
name|offset_y
operator|+
name|image_height
operator|/
literal|2
expr_stmt|;
name|cairo_matrix_init_translate
argument_list|(
name|shell
operator|->
name|rotate_transform
argument_list|,
name|cx
argument_list|,
name|cy
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|rotate_angle
operator|!=
literal|0.0
condition|)
name|cairo_matrix_rotate
argument_list|(
name|shell
operator|->
name|rotate_transform
argument_list|,
name|shell
operator|->
name|rotate_angle
operator|/
literal|180.0
operator|*
name|G_PI
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|flip_horizontally
condition|)
name|cairo_matrix_scale
argument_list|(
name|shell
operator|->
name|rotate_transform
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|flip_vertically
condition|)
name|cairo_matrix_scale
argument_list|(
name|shell
operator|->
name|rotate_transform
argument_list|,
literal|1.0
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_matrix_translate
argument_list|(
name|shell
operator|->
name|rotate_transform
argument_list|,
operator|-
name|cx
argument_list|,
operator|-
name|cy
argument_list|)
expr_stmt|;
operator|*
name|shell
operator|->
name|rotate_untransform
operator|=
operator|*
name|shell
operator|->
name|rotate_transform
expr_stmt|;
name|cairo_matrix_invert
argument_list|(
name|shell
operator|->
name|rotate_untransform
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_save_viewport_center (GimpDisplayShell * shell,gdouble * x,gdouble * y)
name|gimp_display_shell_save_viewport_center
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
block|{
name|gimp_display_shell_unrotate_xy_f
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|disp_width
operator|/
literal|2
argument_list|,
name|shell
operator|->
name|disp_height
operator|/
literal|2
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_restore_viewport_center (GimpDisplayShell * shell,gdouble x,gdouble y)
name|gimp_display_shell_restore_viewport_center
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
parameter_list|)
block|{
name|gimp_display_shell_rotate_xy_f
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|x
operator|+=
name|shell
operator|->
name|offset_x
operator|-
name|shell
operator|->
name|disp_width
operator|/
literal|2
expr_stmt|;
name|y
operator|+=
name|shell
operator|->
name|offset_y
operator|-
name|shell
operator|->
name|disp_height
operator|/
literal|2
expr_stmt|;
name|gimp_display_shell_scroll_set_offset
argument_list|(
name|shell
argument_list|,
name|RINT
argument_list|(
name|x
argument_list|)
argument_list|,
name|RINT
argument_list|(
name|y
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

