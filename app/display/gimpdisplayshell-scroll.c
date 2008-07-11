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
file|<stdlib.h>
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
file|"gimpdisplayshell-private.h"
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

begin_comment
comment|/**  * gimp_display_shell_scroll:  * @shell:  * @x_offset_into_image: In image coordinates.  * @y_offset_into_image:  *  * When the viewport is smaller than the image, offset the viewport to  * the specified amount into the image.  *  * TODO: Behave in a sane way when zoomed out.  *  **/
end_comment

begin_function
DECL|function|gimp_display_shell_scroll (GimpDisplayShell * shell,gdouble x_offset_into_image,gdouble y_offset_into_image)
name|void
name|gimp_display_shell_scroll
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x_offset_into_image
parameter_list|,
name|gdouble
name|y_offset_into_image
parameter_list|)
block|{
name|gint
name|x_offset
decl_stmt|;
name|gint
name|y_offset
decl_stmt|;
name|x_offset
operator|=
name|RINT
argument_list|(
name|x_offset_into_image
operator|*
name|shell
operator|->
name|scale_x
operator|-
name|shell
operator|->
name|offset_x
argument_list|)
expr_stmt|;
name|y_offset
operator|=
name|RINT
argument_list|(
name|y_offset_into_image
operator|*
name|shell
operator|->
name|scale_y
operator|-
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll_private
argument_list|(
name|shell
argument_list|,
name|x_offset
argument_list|,
name|y_offset
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_scroll_private (GimpDisplayShell * shell,gint x_offset,gint y_offset)
name|gimp_display_shell_scroll_private
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
name|gimp_display_shell_scroll_clamp_offsets
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
comment|/*  reset the old values so that the tool can accurately redraw  */
name|shell
operator|->
name|offset_x
operator|=
name|old_x
expr_stmt|;
name|shell
operator|->
name|offset_y
operator|=
name|old_y
expr_stmt|;
name|gimp_display_shell_pause
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/*  set the offsets back to the new values  */
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
name|gdk_window_scroll
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
operator|-
name|x_offset
argument_list|,
operator|-
name|y_offset
argument_list|)
expr_stmt|;
comment|/*  Make sure expose events are processed before scrolling again  */
name|gdk_window_process_updates
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  Update scrollbars and rulers  */
name|gimp_display_shell_scale_setup
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_resume
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_scrolled
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_scroll_clamp_offsets (GimpDisplayShell * shell)
name|gimp_display_shell_scroll_clamp_offsets
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
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|image
condition|)
block|{
name|gint
name|sw
decl_stmt|,
name|sh
decl_stmt|;
name|sw
operator|=
name|SCALEX
argument_list|(
name|shell
argument_list|,
name|gimp_image_get_width
argument_list|(
name|shell
operator|->
name|display
operator|->
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
name|shell
operator|->
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
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
literal|0
argument_list|,
name|MAX
argument_list|(
name|sw
operator|-
name|shell
operator|->
name|disp_width
argument_list|,
literal|0
argument_list|)
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
literal|0
argument_list|,
name|MAX
argument_list|(
name|sh
operator|-
name|shell
operator|->
name|disp_height
argument_list|,
literal|0
argument_list|)
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
block|}
end_function

begin_comment
comment|/**  * gimp_display_shell_get_scaled_viewport:  * @shell:  * @x:  * @y:  * @w:  * @h:  *  * Gets the viewport in screen coordinates, with origin at (0, 0) in  * the image  *  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_get_scaled_viewport (const GimpDisplayShell * shell,gint * x,gint * y,gint * w,gint * h)
name|gimp_display_shell_get_scaled_viewport
parameter_list|(
specifier|const
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
if|if
condition|(
name|x
condition|)
operator|*
name|x
operator|=
operator|-
name|shell
operator|->
name|disp_xoffset
operator|+
name|shell
operator|->
name|offset_x
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
operator|-
name|shell
operator|->
name|disp_yoffset
operator|+
name|shell
operator|->
name|offset_y
expr_stmt|;
if|if
condition|(
name|w
condition|)
operator|*
name|w
operator|=
name|shell
operator|->
name|disp_width
expr_stmt|;
if|if
condition|(
name|h
condition|)
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
comment|/**  * gimp_display_shell_get_viewport:  * @shell:  * @x:  * @y:  * @w:  * @h:  *  * Gets the viewport in image coordinates  *  * TODO: Handle when the viewport is zoomed out  *  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_get_viewport (const GimpDisplayShell * shell,gdouble * x,gdouble * y,gdouble * w,gdouble * h)
name|gimp_display_shell_get_viewport
parameter_list|(
specifier|const
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
if|if
condition|(
name|x
condition|)
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
if|if
condition|(
name|y
condition|)
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
if|if
condition|(
name|w
condition|)
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
if|if
condition|(
name|h
condition|)
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

begin_comment
comment|/**  * gimp_display_shell_get_scaled_image_viewport_offset:  * @shell:  * @x:  * @y:  *  * Gets the scaled image offset in viewport coordinates  *  **/
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_get_scaled_image_viewport_offset (const GimpDisplayShell * shell,gint * x,gint * y)
name|gimp_display_shell_get_scaled_image_viewport_offset
parameter_list|(
specifier|const
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
name|x
condition|)
operator|*
name|x
operator|=
name|shell
operator|->
name|disp_xoffset
operator|-
name|shell
operator|->
name|offset_x
expr_stmt|;
if|if
condition|(
name|y
condition|)
operator|*
name|y
operator|=
name|shell
operator|->
name|disp_yoffset
operator|-
name|shell
operator|->
name|offset_y
expr_stmt|;
block|}
end_function

end_unit

