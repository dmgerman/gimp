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
file|<stdlib.h>
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
name|gint
name|sw
decl_stmt|,
name|sh
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
name|sw
operator|=
name|SCALEX
argument_list|(
name|shell
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|sh
operator|=
name|SCALEY
argument_list|(
name|shell
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|disp_width
operator|<
name|sw
condition|)
block|{
name|min_offset_x
operator|=
literal|0
operator|-
name|shell
operator|->
name|disp_width
operator|*
name|OVERPAN_FACTOR
expr_stmt|;
name|max_offset_x
operator|=
name|sw
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
name|sw
operator|*
operator|(
literal|1.0
operator|-
name|OVERPAN_FACTOR
operator|)
expr_stmt|;
name|min_offset_x
operator|=
literal|0
operator|-
name|overpan_amount
expr_stmt|;
name|max_offset_x
operator|=
name|sw
operator|+
name|overpan_amount
operator|-
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
operator|<
name|sh
condition|)
block|{
name|min_offset_y
operator|=
literal|0
operator|-
name|shell
operator|->
name|disp_height
operator|*
name|OVERPAN_FACTOR
expr_stmt|;
name|max_offset_y
operator|=
name|sh
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
name|sh
operator|*
operator|(
literal|1.0
operator|-
name|OVERPAN_FACTOR
operator|)
expr_stmt|;
name|min_offset_y
operator|=
literal|0
operator|-
name|overpan_amount
expr_stmt|;
name|max_offset_y
operator|=
name|sh
operator|+
name|overpan_amount
operator|-
name|shell
operator|->
name|disp_height
expr_stmt|;
block|}
comment|/* Handle scrollbar stepper sensitiity */
name|gtk_range_set_lower_stepper_sensitivity
argument_list|(
name|GTK_RANGE
argument_list|(
name|shell
operator|->
name|hsb
argument_list|)
argument_list|,
name|min_offset_x
operator|<
name|shell
operator|->
name|offset_x
condition|?
name|GTK_SENSITIVITY_ON
else|:
name|GTK_SENSITIVITY_OFF
argument_list|)
expr_stmt|;
name|gtk_range_set_upper_stepper_sensitivity
argument_list|(
name|GTK_RANGE
argument_list|(
name|shell
operator|->
name|hsb
argument_list|)
argument_list|,
name|max_offset_x
operator|>
name|shell
operator|->
name|offset_x
condition|?
name|GTK_SENSITIVITY_ON
else|:
name|GTK_SENSITIVITY_OFF
argument_list|)
expr_stmt|;
name|gtk_range_set_lower_stepper_sensitivity
argument_list|(
name|GTK_RANGE
argument_list|(
name|shell
operator|->
name|vsb
argument_list|)
argument_list|,
name|min_offset_y
operator|<
name|shell
operator|->
name|offset_y
condition|?
name|GTK_SENSITIVITY_ON
else|:
name|GTK_SENSITIVITY_OFF
argument_list|)
expr_stmt|;
name|gtk_range_set_upper_stepper_sensitivity
argument_list|(
name|GTK_RANGE
argument_list|(
name|shell
operator|->
name|vsb
argument_list|)
argument_list|,
name|max_offset_y
operator|>
name|shell
operator|->
name|offset_y
condition|?
name|GTK_SENSITIVITY_ON
else|:
name|GTK_SENSITIVITY_OFF
argument_list|)
expr_stmt|;
comment|/* Clamp */
name|shell
operator|->
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
name|shell
operator|->
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
name|GimpImage
modifier|*
name|image
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
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|/
literal|2
argument_list|,
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|/
literal|2
argument_list|,
operator|&
name|center_x
argument_list|,
operator|&
name|center_y
argument_list|)
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon276f26830108
block|{
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
DECL|member|vertically
name|gboolean
name|vertically
decl_stmt|;
DECL|member|horizontally
name|gboolean
name|horizontally
decl_stmt|;
DECL|typedef|CenterImageData
block|}
name|CenterImageData
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_scroll_center_image_callback (GtkWidget * canvas,GtkAllocation * allocation,CenterImageData * data)
name|gimp_display_shell_scroll_center_image_callback
parameter_list|(
name|GtkWidget
modifier|*
name|canvas
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|CenterImageData
modifier|*
name|data
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|canvas
argument_list|,
name|gimp_display_shell_scroll_center_image_callback
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll_center_image
argument_list|(
name|data
operator|->
name|shell
argument_list|,
name|data
operator|->
name|horizontally
argument_list|,
name|data
operator|->
name|vertically
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|CenterImageData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_scroll_center_image_on_size_allocate:  * @shell:  *  * Centers the image in the display as soon as the canvas has got its  * new size.  *  * Only call this if you are sure the canvas size will change.  * (Otherwise the signal connection and centering will lurk until the  * canvas size is changed e.g. by toggling the rulers.)  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_scroll_center_image_on_size_allocate (GimpDisplayShell * shell,gboolean horizontally,gboolean vertically)
name|gimp_display_shell_scroll_center_image_on_size_allocate
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
name|CenterImageData
modifier|*
name|data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|=
name|g_slice_new
argument_list|(
name|CenterImageData
argument_list|)
expr_stmt|;
name|data
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
name|data
operator|->
name|horizontally
operator|=
name|horizontally
expr_stmt|;
name|data
operator|->
name|vertically
operator|=
name|vertically
expr_stmt|;
name|g_signal_connect
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
literal|"size-allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_scroll_center_image_callback
argument_list|)
argument_list|,
name|data
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

