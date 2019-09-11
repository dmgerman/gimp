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
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay-foreach.h"
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
file|"gimpdisplayshell-rulers.h"
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
file|"gimpdisplayshell-scrollbars.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_define
DECL|macro|OVERPAN_FACTOR
define|#
directive|define
name|OVERPAN_FACTOR
value|0.5
end_define

begin_comment
comment|/**  * gimp_display_shell_scroll:  * @shell:  * @x_offset:  * @y_offset:  *  * This function scrolls the image in the shell's viewport. It does  * actual scrolling of the pixels, so only the newly scrolled-in parts  * are freshly redrawn.  *  * Use it for incremental actual panning.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll (GimpDisplayShell * shell,gint x_offset,gint y_offset)
name|gimp_display_shell_scroll
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|)
block|{
name|gint
name|old_x
decl_stmt|;
name|gint
name|old_y
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
name|x_offset
operator|==
literal|0
operator|&&
name|y_offset
operator|==
literal|0
condition|)
return|return;
name|old_x
operator|=
name|shell
operator|->
name|offset_x
expr_stmt|;
name|old_y
operator|=
name|shell
operator|->
name|offset_y
expr_stmt|;
comment|/* freeze the active tool */
name|gimp_display_shell_pause
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|offset_x
operator|+=
name|x_offset
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|+=
name|y_offset
expr_stmt|;
name|gimp_display_shell_scroll_clamp_and_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/*  the actual changes in offset  */
name|x_offset
operator|=
operator|(
name|shell
operator|->
name|offset_x
operator|-
name|old_x
operator|)
expr_stmt|;
name|y_offset
operator|=
operator|(
name|shell
operator|->
name|offset_y
operator|-
name|old_y
operator|)
expr_stmt|;
if|if
condition|(
name|x_offset
operator|||
name|y_offset
condition|)
block|{
name|gimp_display_shell_scrolled
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_overlay_box_scroll
argument_list|(
name|GIMP_OVERLAY_BOX
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
operator|-
name|x_offset
argument_list|,
operator|-
name|y_offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|render_cache
condition|)
block|{
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|surface
operator|=
name|cairo_surface_create_similar_image
argument_list|(
name|shell
operator|->
name|render_cache
argument_list|,
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|shell
operator|->
name|disp_width
operator|*
name|shell
operator|->
name|render_scale
argument_list|,
name|shell
operator|->
name|disp_height
operator|*
name|shell
operator|->
name|render_scale
argument_list|)
expr_stmt|;
name|cr
operator|=
name|cairo_create
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_set_operator
argument_list|(
name|cr
argument_list|,
name|CAIRO_OPERATOR_SOURCE
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|shell
operator|->
name|render_cache
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cr
operator|=
name|cairo_create
argument_list|(
name|shell
operator|->
name|render_cache
argument_list|)
expr_stmt|;
name|cairo_set_operator
argument_list|(
name|cr
argument_list|,
name|CAIRO_OPERATOR_SOURCE
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|surface
argument_list|,
operator|-
name|x_offset
operator|*
name|shell
operator|->
name|render_scale
argument_list|,
operator|-
name|y_offset
operator|*
name|shell
operator|->
name|render_scale
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|render_cache_valid
condition|)
block|{
name|cairo_rectangle_int_t
name|rect
decl_stmt|;
name|cairo_region_translate
argument_list|(
name|shell
operator|->
name|render_cache_valid
argument_list|,
operator|-
name|x_offset
argument_list|,
operator|-
name|y_offset
argument_list|)
expr_stmt|;
name|rect
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|shell
operator|->
name|disp_height
expr_stmt|;
name|cairo_region_intersect_rectangle
argument_list|(
name|shell
operator|->
name|render_cache_valid
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* re-enable the active tool */
name|gimp_display_shell_resume
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_set_offsets:  * @shell:  * @offset_x:  * @offset_y:  *  * This function scrolls the image in the shell's viewport. It redraws  * the entire canvas.  *  * Use it for setting the scroll offset on freshly scaled images or  * when the window is resized. For panning, use  * gimp_display_shell_scroll().  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_set_offset (GimpDisplayShell * shell,gint offset_x,gint offset_y)
name|gimp_display_shell_scroll_set_offset
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
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
if|if
condition|(
name|shell
operator|->
name|offset_x
operator|==
name|offset_x
operator|&&
name|shell
operator|->
name|offset_y
operator|==
name|offset_y
condition|)
return|return;
name|gimp_display_shell_scale_save_revert_values
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/* freeze the active tool */
name|gimp_display_shell_pause
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|shell
operator|->
name|offset_x
operator|=
name|offset_x
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
name|offset_y
expr_stmt|;
name|gimp_display_shell_scroll_clamp_and_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_scrolled
argument_list|(
name|shell
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
comment|/* re-enable the active tool */
name|gimp_display_shell_resume
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_clamp_and_update:  * @shell:  *  * Helper function for calling two functions that are commonly called  * in pairs.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_clamp_and_update (GimpDisplayShell * shell)
name|gimp_display_shell_scroll_clamp_and_update
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|shell
operator|->
name|show_all
condition|)
block|{
name|gint
name|bounds_x
decl_stmt|;
name|gint
name|bounds_y
decl_stmt|;
name|gint
name|bounds_width
decl_stmt|;
name|gint
name|bounds_height
decl_stmt|;
name|gint
name|min_offset_x
decl_stmt|;
name|gint
name|max_offset_x
decl_stmt|;
name|gint
name|min_offset_y
decl_stmt|;
name|gint
name|max_offset_y
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gimp_display_shell_rotate_update_transform
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_get_image_bounds
argument_list|(
name|shell
argument_list|,
operator|&
name|bounds_x
argument_list|,
operator|&
name|bounds_y
argument_list|,
operator|&
name|bounds_width
argument_list|,
operator|&
name|bounds_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|disp_width
operator|<
name|bounds_width
condition|)
block|{
name|min_offset_x
operator|=
name|bounds_x
operator|-
name|shell
operator|->
name|disp_width
operator|*
name|OVERPAN_FACTOR
expr_stmt|;
name|max_offset_x
operator|=
name|bounds_x
operator|+
name|bounds_width
operator|-
name|shell
operator|->
name|disp_width
operator|*
operator|(
literal|1.0
operator|-
name|OVERPAN_FACTOR
operator|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|overpan_amount
decl_stmt|;
name|overpan_amount
operator|=
name|shell
operator|->
name|disp_width
operator|-
name|bounds_width
operator|*
operator|(
literal|1.0
operator|-
name|OVERPAN_FACTOR
operator|)
expr_stmt|;
name|min_offset_x
operator|=
name|bounds_x
operator|-
name|overpan_amount
expr_stmt|;
name|max_offset_x
operator|=
name|bounds_x
operator|+
name|bounds_width
operator|-
name|shell
operator|->
name|disp_width
operator|+
name|overpan_amount
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|disp_height
operator|<
name|bounds_height
condition|)
block|{
name|min_offset_y
operator|=
name|bounds_y
operator|-
name|shell
operator|->
name|disp_height
operator|*
name|OVERPAN_FACTOR
expr_stmt|;
name|max_offset_y
operator|=
name|bounds_y
operator|+
name|bounds_height
operator|-
name|shell
operator|->
name|disp_height
operator|*
operator|(
literal|1.0
operator|-
name|OVERPAN_FACTOR
operator|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|overpan_amount
decl_stmt|;
name|overpan_amount
operator|=
name|shell
operator|->
name|disp_height
operator|-
name|bounds_height
operator|*
operator|(
literal|1.0
operator|-
name|OVERPAN_FACTOR
operator|)
expr_stmt|;
name|min_offset_y
operator|=
name|bounds_y
operator|-
name|overpan_amount
expr_stmt|;
name|max_offset_y
operator|=
name|bounds_y
operator|+
name|bounds_height
operator|+
name|overpan_amount
operator|-
name|shell
operator|->
name|disp_height
expr_stmt|;
block|}
comment|/* Clamp */
name|offset_x
operator|=
name|CLAMP
argument_list|(
name|shell
operator|->
name|offset_x
argument_list|,
name|min_offset_x
argument_list|,
name|max_offset_x
argument_list|)
expr_stmt|;
name|offset_y
operator|=
name|CLAMP
argument_list|(
name|shell
operator|->
name|offset_y
argument_list|,
name|min_offset_y
argument_list|,
name|max_offset_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|offset_x
operator|!=
name|shell
operator|->
name|offset_x
operator|||
name|offset_y
operator|!=
name|shell
operator|->
name|offset_y
condition|)
block|{
name|shell
operator|->
name|offset_x
operator|=
name|offset_x
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
name|offset_y
expr_stmt|;
name|gimp_display_shell_rotate_update_transform
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
comment|/* Set scrollbar stepper sensitiity */
name|gimp_display_shell_scrollbars_update_steppers
argument_list|(
name|shell
argument_list|,
name|min_offset_x
argument_list|,
name|max_offset_x
argument_list|,
name|min_offset_y
argument_list|,
name|max_offset_y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Set scrollbar stepper sensitiity */
name|gimp_display_shell_scrollbars_update_steppers
argument_list|(
name|shell
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|,
name|G_MININT
argument_list|,
name|G_MAXINT
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|shell
operator|->
name|offset_x
operator|=
literal|0
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
literal|0
expr_stmt|;
block|}
name|gimp_display_shell_scrollbars_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_rulers_update
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_unoverscrollify:  * @shell:  * @in_offset_x:  * @in_offset_y:  * @out_offset_x:  * @out_offset_y:  *  * Takes a scroll offset and returns the offset that will not result  * in a scroll beyond the image border. If the image is already  * overscrolled, the return value is 0 for that given axis.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_unoverscrollify (GimpDisplayShell * shell,gint in_offset_x,gint in_offset_y,gint * out_offset_x,gint * out_offset_y)
name|gimp_display_shell_scroll_unoverscrollify
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|in_offset_x
parameter_list|,
name|gint
name|in_offset_y
parameter_list|,
name|gint
modifier|*
name|out_offset_x
parameter_list|,
name|gint
modifier|*
name|out_offset_y
parameter_list|)
block|{
name|gint
name|sw
decl_stmt|,
name|sh
decl_stmt|;
name|gint
name|out_offset_x_dummy
decl_stmt|,
name|out_offset_y_dummy
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
operator|!
name|out_offset_x
condition|)
name|out_offset_x
operator|=
operator|&
name|out_offset_x_dummy
expr_stmt|;
if|if
condition|(
operator|!
name|out_offset_y
condition|)
name|out_offset_y
operator|=
operator|&
name|out_offset_y_dummy
expr_stmt|;
operator|*
name|out_offset_x
operator|=
name|in_offset_x
expr_stmt|;
operator|*
name|out_offset_y
operator|=
name|in_offset_y
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|show_all
condition|)
block|{
name|gimp_display_shell_scale_get_image_size
argument_list|(
name|shell
argument_list|,
operator|&
name|sw
argument_list|,
operator|&
name|sh
argument_list|)
expr_stmt|;
if|if
condition|(
name|in_offset_x
operator|<
literal|0
condition|)
block|{
operator|*
name|out_offset_x
operator|=
name|MAX
argument_list|(
name|in_offset_x
argument_list|,
name|MIN
argument_list|(
literal|0
argument_list|,
literal|0
operator|-
name|shell
operator|->
name|offset_x
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_offset_x
operator|>
literal|0
condition|)
block|{
name|gint
name|min_offset
init|=
name|sw
operator|-
name|shell
operator|->
name|disp_width
decl_stmt|;
operator|*
name|out_offset_x
operator|=
name|MIN
argument_list|(
name|in_offset_x
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
name|min_offset
operator|-
name|shell
operator|->
name|offset_x
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|in_offset_y
operator|<
literal|0
condition|)
block|{
operator|*
name|out_offset_y
operator|=
name|MAX
argument_list|(
name|in_offset_y
argument_list|,
name|MIN
argument_list|(
literal|0
argument_list|,
literal|0
operator|-
name|shell
operator|->
name|offset_y
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|in_offset_y
operator|>
literal|0
condition|)
block|{
name|gint
name|min_offset
init|=
name|sh
operator|-
name|shell
operator|->
name|disp_height
decl_stmt|;
operator|*
name|out_offset_y
operator|=
name|MIN
argument_list|(
name|in_offset_y
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
name|min_offset
operator|-
name|shell
operator|->
name|offset_y
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_center_image_xy:  * @shell:  * @image_x:  * @image_y:  *  * Center the viewport around the passed image coordinate  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_center_image_xy (GimpDisplayShell * shell,gdouble image_x,gdouble image_y)
name|gimp_display_shell_scroll_center_image_xy
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|image_x
parameter_list|,
name|gdouble
name|image_y
parameter_list|)
block|{
name|gint
name|viewport_x
decl_stmt|;
name|gint
name|viewport_y
decl_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|image_x
argument_list|,
name|image_y
argument_list|,
operator|&
name|viewport_x
argument_list|,
operator|&
name|viewport_y
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll
argument_list|(
name|shell
argument_list|,
name|viewport_x
operator|-
name|shell
operator|->
name|disp_width
operator|/
literal|2
argument_list|,
name|viewport_y
operator|-
name|shell
operator|->
name|disp_height
operator|/
literal|2
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_center_image:  * @shell:  * @horizontally:  * @vertically:  *  * Centers the image in the display shell on the desired axes.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_center_image (GimpDisplayShell * shell,gboolean horizontally,gboolean vertically)
name|gimp_display_shell_scroll_center_image
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|horizontally
parameter_list|,
name|gboolean
name|vertically
parameter_list|)
block|{
name|gint
name|image_x
decl_stmt|;
name|gint
name|image_y
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gint
name|center_x
decl_stmt|;
name|gint
name|center_y
decl_stmt|;
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
if|if
condition|(
operator|!
name|shell
operator|->
name|display
operator|||
operator|!
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
operator|||
operator|(
operator|!
name|vertically
operator|&&
operator|!
name|horizontally
operator|)
condition|)
return|return;
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
if|if
condition|(
name|shell
operator|->
name|disp_width
operator|>
name|image_width
condition|)
block|{
name|image_x
operator|-=
operator|(
name|shell
operator|->
name|disp_width
operator|-
name|image_width
operator|)
operator|/
literal|2
expr_stmt|;
name|image_width
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|disp_height
operator|>
name|image_height
condition|)
block|{
name|image_y
operator|-=
operator|(
name|shell
operator|->
name|disp_height
operator|-
name|image_height
operator|)
operator|/
literal|2
expr_stmt|;
name|image_height
operator|=
name|shell
operator|->
name|disp_height
expr_stmt|;
block|}
name|center_x
operator|=
name|image_x
operator|+
name|image_width
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
name|image_y
operator|+
name|image_height
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|horizontally
condition|)
name|offset_x
operator|=
name|center_x
operator|-
name|shell
operator|->
name|disp_width
operator|/
literal|2
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
if|if
condition|(
name|vertically
condition|)
name|offset_y
operator|=
name|center_y
operator|-
name|shell
operator|->
name|disp_height
operator|/
literal|2
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
name|gimp_display_shell_scroll
argument_list|(
name|shell
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_center_image:  * @shell:  * @horizontally:  * @vertically:  *  * Centers the image content in the display shell on the desired axes.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_center_content (GimpDisplayShell * shell,gboolean horizontally,gboolean vertically)
name|gimp_display_shell_scroll_center_content
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|horizontally
parameter_list|,
name|gboolean
name|vertically
parameter_list|)
block|{
name|gint
name|content_x
decl_stmt|;
name|gint
name|content_y
decl_stmt|;
name|gint
name|content_width
decl_stmt|;
name|gint
name|content_height
decl_stmt|;
name|gint
name|center_x
decl_stmt|;
name|gint
name|center_y
decl_stmt|;
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
if|if
condition|(
operator|!
name|shell
operator|->
name|display
operator|||
operator|!
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
operator|||
operator|(
operator|!
name|vertically
operator|&&
operator|!
name|horizontally
operator|)
condition|)
return|return;
name|gimp_display_shell_scale_get_image_bounding_box
argument_list|(
name|shell
argument_list|,
operator|&
name|content_x
argument_list|,
operator|&
name|content_y
argument_list|,
operator|&
name|content_width
argument_list|,
operator|&
name|content_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|disp_width
operator|>
name|content_width
condition|)
block|{
name|content_x
operator|-=
operator|(
name|shell
operator|->
name|disp_width
operator|-
name|content_width
operator|)
operator|/
literal|2
expr_stmt|;
name|content_width
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|disp_height
operator|>
name|content_height
condition|)
block|{
name|content_y
operator|-=
operator|(
name|shell
operator|->
name|disp_height
operator|-
name|content_height
operator|)
operator|/
literal|2
expr_stmt|;
name|content_height
operator|=
name|shell
operator|->
name|disp_height
expr_stmt|;
block|}
name|center_x
operator|=
name|content_x
operator|+
name|content_width
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
name|content_y
operator|+
name|content_height
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|horizontally
condition|)
name|offset_x
operator|=
name|center_x
operator|-
name|shell
operator|->
name|disp_width
operator|/
literal|2
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
if|if
condition|(
name|vertically
condition|)
name|offset_y
operator|=
name|center_y
operator|-
name|shell
operator|->
name|disp_height
operator|/
literal|2
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
name|gimp_display_shell_scroll
argument_list|(
name|shell
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_get_scaled_viewport:  * @shell:  * @x:  * @y:  * @w:  * @h:  *  * Gets the viewport in screen coordinates, with origin at (0, 0) in  * the image.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_get_scaled_viewport (GimpDisplayShell * shell,gint * x,gint * y,gint * w,gint * h)
name|gimp_display_shell_scroll_get_scaled_viewport
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
name|w
parameter_list|,
name|gint
modifier|*
name|h
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
operator|*
name|x
operator|=
name|shell
operator|->
name|offset_x
expr_stmt|;
operator|*
name|y
operator|=
name|shell
operator|->
name|offset_y
expr_stmt|;
operator|*
name|w
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
operator|*
name|h
operator|=
name|shell
operator|->
name|disp_height
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_get_viewport:  * @shell:  * @x:  * @y:  * @w:  * @h:  *  * Gets the viewport in image coordinates.  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_get_viewport (GimpDisplayShell * shell,gdouble * x,gdouble * y,gdouble * w,gdouble * h)
name|gimp_display_shell_scroll_get_viewport
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
parameter_list|,
name|gdouble
modifier|*
name|w
parameter_list|,
name|gdouble
modifier|*
name|h
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
operator|*
name|x
operator|=
name|shell
operator|->
name|offset_x
operator|/
name|shell
operator|->
name|scale_x
expr_stmt|;
operator|*
name|y
operator|=
name|shell
operator|->
name|offset_y
operator|/
name|shell
operator|->
name|scale_y
expr_stmt|;
operator|*
name|w
operator|=
name|shell
operator|->
name|disp_width
operator|/
name|shell
operator|->
name|scale_x
expr_stmt|;
operator|*
name|h
operator|=
name|shell
operator|->
name|disp_height
operator|/
name|shell
operator|->
name|scale_y
expr_stmt|;
block|}
end_function

end_unit

