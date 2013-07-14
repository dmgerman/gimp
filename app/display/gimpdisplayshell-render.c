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
file|"libgimpcolor/gimpcolor.h"
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
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
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
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojectable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojection.h"
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

begin_include
include|#
directive|include
file|"gimpdisplayshell-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-render.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scroll.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayxfer.h"
end_include

begin_function
name|void
DECL|function|gimp_display_shell_render (GimpDisplayShell * shell,cairo_t * cr,gint x,gint y,gint w,gint h)
name|gimp_display_shell_render
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpProjection
modifier|*
name|projection
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gdouble
name|window_scale
init|=
literal|1.0
decl_stmt|;
name|gint
name|viewport_offset_x
decl_stmt|;
name|gint
name|viewport_offset_y
decl_stmt|;
name|gint
name|viewport_width
decl_stmt|;
name|gint
name|viewport_height
decl_stmt|;
name|cairo_surface_t
modifier|*
name|xfer
decl_stmt|;
name|gint
name|src_x
decl_stmt|;
name|gint
name|src_y
decl_stmt|;
name|gint
name|mask_src_x
init|=
literal|0
decl_stmt|;
name|gint
name|mask_src_y
init|=
literal|0
decl_stmt|;
name|gint
name|stride
decl_stmt|;
name|guchar
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
name|g_return_if_fail
argument_list|(
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|w
operator|>
literal|0
operator|&&
name|h
operator|>
literal|0
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
name|projection
operator|=
name|gimp_image_get_projection
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_pickable_get_buffer
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|projection
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_DISPLAY_RENDER_ENABLE_SCALING
comment|/* if we had this future API, things would look pretty on hires (retina) */
name|window_scale
operator|=
name|gdk_window_get_scale_factor
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|window_scale
operator|=
name|MIN
argument_list|(
name|window_scale
argument_list|,
name|GIMP_DISPLAY_RENDER_MAX_SCALE
argument_list|)
expr_stmt|;
name|gimp_display_shell_scroll_get_scaled_viewport
argument_list|(
name|shell
argument_list|,
operator|&
name|viewport_offset_x
argument_list|,
operator|&
name|viewport_offset_y
argument_list|,
operator|&
name|viewport_width
argument_list|,
operator|&
name|viewport_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|rotate_transform
condition|)
block|{
name|xfer
operator|=
name|cairo_surface_create_similar_image
argument_list|(
name|cairo_get_target
argument_list|(
name|cr
argument_list|)
argument_list|,
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|w
operator|*
name|window_scale
argument_list|,
name|h
operator|*
name|window_scale
argument_list|)
expr_stmt|;
name|cairo_surface_mark_dirty
argument_list|(
name|xfer
argument_list|)
expr_stmt|;
name|src_x
operator|=
literal|0
expr_stmt|;
name|src_y
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|xfer
operator|=
name|gimp_display_xfer_get_surface
argument_list|(
name|shell
operator|->
name|xfer
argument_list|,
name|w
operator|*
name|window_scale
argument_list|,
name|h
operator|*
name|window_scale
argument_list|,
operator|&
name|src_x
argument_list|,
operator|&
name|src_y
argument_list|)
expr_stmt|;
block|}
name|stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|xfer
argument_list|)
expr_stmt|;
name|data
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|xfer
argument_list|)
expr_stmt|;
name|data
operator|+=
name|src_y
operator|*
name|stride
operator|+
name|src_x
operator|*
literal|4
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
operator|(
name|x
operator|+
name|viewport_offset_x
operator|)
operator|*
name|window_scale
argument_list|,
operator|(
name|y
operator|+
name|viewport_offset_y
operator|)
operator|*
name|window_scale
argument_list|,
name|w
operator|*
name|window_scale
argument_list|,
name|h
operator|*
name|window_scale
argument_list|)
argument_list|,
name|shell
operator|->
name|scale_x
operator|*
name|window_scale
argument_list|,
name|babl_format
argument_list|(
literal|"cairo-ARGB32"
argument_list|)
argument_list|,
name|data
argument_list|,
name|stride
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
comment|/*  apply filters to the rendered projection  */
if|if
condition|(
name|shell
operator|->
name|filter_stack
condition|)
block|{
name|cairo_surface_t
modifier|*
name|image
init|=
name|cairo_image_surface_create_for_data
argument_list|(
name|data
argument_list|,
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|w
operator|*
name|window_scale
argument_list|,
name|h
operator|*
name|window_scale
argument_list|,
name|stride
argument_list|)
decl_stmt|;
name|gimp_color_display_stack_convert_surface
argument_list|(
name|shell
operator|->
name|filter_stack
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|mask
condition|)
block|{
name|gint
name|mask_height
decl_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|mask_surface
condition|)
block|{
name|shell
operator|->
name|mask_surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_A8
argument_list|,
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
operator|*
name|GIMP_DISPLAY_RENDER_MAX_SCALE
argument_list|,
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
operator|*
name|GIMP_DISPLAY_RENDER_MAX_SCALE
argument_list|)
expr_stmt|;
block|}
name|cairo_surface_mark_dirty
argument_list|(
name|shell
operator|->
name|mask_surface
argument_list|)
expr_stmt|;
name|stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|shell
operator|->
name|mask_surface
argument_list|)
expr_stmt|;
name|data
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|shell
operator|->
name|mask_surface
argument_list|)
expr_stmt|;
name|data
operator|+=
name|mask_src_y
operator|*
name|stride
operator|+
name|mask_src_x
operator|*
literal|4
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|shell
operator|->
name|mask
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
operator|(
name|x
operator|+
name|viewport_offset_x
operator|)
operator|*
name|window_scale
argument_list|,
operator|(
name|y
operator|+
name|viewport_offset_y
operator|)
operator|*
name|window_scale
argument_list|,
name|w
operator|*
name|window_scale
argument_list|,
name|h
operator|*
name|window_scale
argument_list|)
argument_list|,
name|shell
operator|->
name|scale_x
operator|*
name|window_scale
argument_list|,
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
argument_list|,
name|data
argument_list|,
name|stride
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
comment|/* invert the mask so what is *not* the foreground object is masked */
name|mask_height
operator|=
name|h
operator|*
name|window_scale
expr_stmt|;
while|while
condition|(
name|mask_height
operator|--
condition|)
block|{
name|gint
name|mask_width
init|=
name|w
operator|*
name|window_scale
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|data
decl_stmt|;
while|while
condition|(
name|mask_width
operator|--
condition|)
block|{
name|guchar
name|inv
init|=
literal|255
operator|-
operator|*
name|d
decl_stmt|;
operator|*
name|d
operator|++
operator|=
name|inv
expr_stmt|;
block|}
name|data
operator|+=
name|stride
expr_stmt|;
block|}
block|}
comment|/*  put it to the screen  */
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
literal|1.0
operator|/
name|window_scale
argument_list|,
literal|1.0
operator|/
name|window_scale
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|xfer
argument_list|,
operator|(
name|x
operator|-
name|src_x
operator|)
operator|*
name|window_scale
argument_list|,
operator|(
name|y
operator|-
name|src_y
operator|)
operator|*
name|window_scale
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|rotate_transform
condition|)
block|{
name|cairo_pattern_t
modifier|*
name|pattern
decl_stmt|;
name|pattern
operator|=
name|cairo_get_source
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_pattern_set_extend
argument_list|(
name|pattern
argument_list|,
name|CAIRO_EXTEND_PAD
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_stroke_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|xfer
argument_list|)
expr_stmt|;
block|}
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|mask
condition|)
block|{
name|gimp_cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
operator|&
name|shell
operator|->
name|mask_color
argument_list|)
expr_stmt|;
name|cairo_mask_surface
argument_list|(
name|cr
argument_list|,
name|shell
operator|->
name|mask_surface
argument_list|,
operator|(
name|x
operator|-
name|mask_src_x
operator|)
operator|*
name|window_scale
argument_list|,
operator|(
name|y
operator|-
name|mask_src_y
operator|)
operator|*
name|window_scale
argument_list|)
expr_stmt|;
block|}
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

