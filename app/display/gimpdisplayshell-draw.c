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
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimp-cairo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas-style.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvaspath.h"
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
file|"gimpdisplayshell-draw.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-render.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayxfer.h"
end_include

begin_comment
comment|/* #define GIMP_DISPLAY_RENDER_ENABLE_SCALING 1 */
end_comment

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_draw_selection_out (GimpDisplayShell * shell,cairo_t * cr,GimpSegment * segs,gint n_segs)
name|gimp_display_shell_draw_selection_out
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpSegment
modifier|*
name|segs
parameter_list|,
name|gint
name|n_segs
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|segs
operator|!=
name|NULL
operator|&&
name|n_segs
operator|>
literal|0
argument_list|)
expr_stmt|;
name|gimp_canvas_set_selection_out_style
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
name|cr
argument_list|,
name|shell
operator|->
name|offset_x
argument_list|,
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_cairo_add_segments
argument_list|(
name|cr
argument_list|,
name|segs
argument_list|,
name|n_segs
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_selection_in (GimpDisplayShell * shell,cairo_t * cr,cairo_pattern_t * mask,gint index)
name|gimp_display_shell_draw_selection_in
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|cairo_pattern_t
modifier|*
name|mask
parameter_list|,
name|gint
name|index
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|mask
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_set_selection_in_style
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
name|cr
argument_list|,
name|index
argument_list|,
name|shell
operator|->
name|offset_x
argument_list|,
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|cairo_mask
argument_list|(
name|cr
argument_list|,
name|mask
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_background (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_draw_background
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|cairo_pattern_t
modifier|*
name|bg_pattern
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
name|window
operator|=
name|gtk_widget_get_window
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|bg_pattern
operator|=
name|gdk_window_get_background_pattern
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|bg_pattern
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_checkerboard (GimpDisplayShell * shell,cairo_t * cr)
name|gimp_display_shell_draw_checkerboard
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|cairo_t
modifier|*
name|cr
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
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_UNLIKELY
argument_list|(
operator|!
name|shell
operator|->
name|checkerboard
argument_list|)
condition|)
block|{
name|GimpCheckSize
name|check_size
decl_stmt|;
name|GimpCheckType
name|check_type
decl_stmt|;
name|guchar
name|check_light
decl_stmt|;
name|guchar
name|check_dark
decl_stmt|;
name|GimpRGB
name|light
decl_stmt|;
name|GimpRGB
name|dark
decl_stmt|;
name|g_object_get
argument_list|(
name|shell
operator|->
name|display
operator|->
name|config
argument_list|,
literal|"transparency-size"
argument_list|,
operator|&
name|check_size
argument_list|,
literal|"transparency-type"
argument_list|,
operator|&
name|check_type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_checks_get_shades
argument_list|(
name|check_type
argument_list|,
operator|&
name|check_light
argument_list|,
operator|&
name|check_dark
argument_list|)
expr_stmt|;
name|gimp_rgb_set_uchar
argument_list|(
operator|&
name|light
argument_list|,
name|check_light
argument_list|,
name|check_light
argument_list|,
name|check_light
argument_list|)
expr_stmt|;
name|gimp_rgb_set_uchar
argument_list|(
operator|&
name|dark
argument_list|,
name|check_dark
argument_list|,
name|check_dark
argument_list|,
name|check_dark
argument_list|)
expr_stmt|;
name|shell
operator|->
name|checkerboard
operator|=
name|gimp_cairo_checkerboard_create
argument_list|(
name|cr
argument_list|,
literal|1
operator|<<
operator|(
name|check_size
operator|+
literal|2
operator|)
argument_list|,
operator|&
name|light
argument_list|,
operator|&
name|dark
argument_list|)
expr_stmt|;
block|}
name|cairo_translate
argument_list|(
name|cr
argument_list|,
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
operator|-
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|cairo_set_source
argument_list|(
name|cr
argument_list|,
name|shell
operator|->
name|checkerboard
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_draw_image (GimpDisplayShell * shell,cairo_t * cr,gint x,gint y,gint w,gint h)
name|gimp_display_shell_draw_image
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
name|gdouble
name|chunk_width
decl_stmt|;
name|gdouble
name|chunk_height
decl_stmt|;
name|gdouble
name|scale
init|=
literal|1.0
decl_stmt|;
name|gint
name|n_rows
decl_stmt|;
name|gint
name|n_cols
decl_stmt|;
name|gint
name|r
decl_stmt|,
name|c
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
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
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
comment|/*  display the image in RENDER_BUF_WIDTH x RENDER_BUF_HEIGHT    *  maximally-sized image-space chunks.  adjust the screen-space    *  chunk size as necessary, to accommodate for the display    *  transform and window scale factor.    */
name|chunk_width
operator|=
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
expr_stmt|;
name|chunk_height
operator|=
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_DISPLAY_RENDER_ENABLE_SCALING
comment|/* if we had this future API, things would look pretty on hires (retina) */
name|scale
operator|*=
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
name|scale
operator|=
name|MIN
argument_list|(
name|scale
argument_list|,
name|GIMP_DISPLAY_RENDER_MAX_SCALE
argument_list|)
expr_stmt|;
name|scale
operator|*=
name|MAX
argument_list|(
name|shell
operator|->
name|scale_x
argument_list|,
name|shell
operator|->
name|scale_y
argument_list|)
expr_stmt|;
name|chunk_width
operator|*=
name|shell
operator|->
name|scale_x
operator|/
name|scale
expr_stmt|;
name|chunk_height
operator|*=
name|shell
operator|->
name|scale_y
operator|/
name|scale
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|rotate_untransform
condition|)
block|{
name|gdouble
name|a
init|=
name|shell
operator|->
name|rotate_angle
operator|*
name|G_PI
operator|/
literal|180.0
decl_stmt|;
name|chunk_width
operator|=
name|chunk_height
operator|=
operator|(
name|MIN
argument_list|(
name|chunk_width
argument_list|,
name|chunk_height
argument_list|)
operator|-
literal|1.0
operator|)
operator|/
operator|(
name|fabs
argument_list|(
name|sin
argument_list|(
name|a
argument_list|)
argument_list|)
operator|+
name|fabs
argument_list|(
name|cos
argument_list|(
name|a
argument_list|)
argument_list|)
operator|)
expr_stmt|;
block|}
comment|/* divide the painted area to evenly-sized chunks */
name|n_rows
operator|=
name|ceil
argument_list|(
name|h
operator|/
name|chunk_height
argument_list|)
expr_stmt|;
name|n_cols
operator|=
name|ceil
argument_list|(
name|w
operator|/
name|chunk_width
argument_list|)
expr_stmt|;
for|for
control|(
name|r
operator|=
literal|0
init|;
name|r
operator|<
name|n_rows
condition|;
name|r
operator|++
control|)
block|{
name|gint
name|y1
init|=
name|y
operator|+
operator|(
literal|2
operator|*
name|r
operator|*
name|h
operator|+
name|n_rows
operator|)
operator|/
operator|(
literal|2
operator|*
name|n_rows
operator|)
decl_stmt|;
name|gint
name|y2
init|=
name|y
operator|+
operator|(
literal|2
operator|*
operator|(
name|r
operator|+
literal|1
operator|)
operator|*
name|h
operator|+
name|n_rows
operator|)
operator|/
operator|(
literal|2
operator|*
name|n_rows
operator|)
decl_stmt|;
for|for
control|(
name|c
operator|=
literal|0
init|;
name|c
operator|<
name|n_cols
condition|;
name|c
operator|++
control|)
block|{
name|gint
name|x1
init|=
name|x
operator|+
operator|(
literal|2
operator|*
name|c
operator|*
name|w
operator|+
name|n_cols
operator|)
operator|/
operator|(
literal|2
operator|*
name|n_cols
operator|)
decl_stmt|;
name|gint
name|x2
init|=
name|x
operator|+
operator|(
literal|2
operator|*
operator|(
name|c
operator|+
literal|1
operator|)
operator|*
name|w
operator|+
name|n_cols
operator|)
operator|/
operator|(
literal|2
operator|*
name|n_cols
operator|)
decl_stmt|;
name|gdouble
name|ix1
decl_stmt|,
name|iy1
decl_stmt|;
name|gdouble
name|ix2
decl_stmt|,
name|iy2
decl_stmt|;
name|gint
name|ix
decl_stmt|,
name|iy
decl_stmt|;
name|gint
name|iw
decl_stmt|,
name|ih
decl_stmt|;
comment|/* map chunk from screen space to image space */
name|gimp_display_shell_untransform_bounds
argument_list|(
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
operator|&
name|ix1
argument_list|,
operator|&
name|iy1
argument_list|,
operator|&
name|ix2
argument_list|,
operator|&
name|iy2
argument_list|)
expr_stmt|;
name|ix
operator|=
name|floor
argument_list|(
name|ix1
operator|*
name|scale
argument_list|)
expr_stmt|;
name|iy
operator|=
name|floor
argument_list|(
name|iy1
operator|*
name|scale
argument_list|)
expr_stmt|;
name|iw
operator|=
name|ceil
argument_list|(
name|ix2
operator|*
name|scale
argument_list|)
operator|-
name|ix
expr_stmt|;
name|ih
operator|=
name|ceil
argument_list|(
name|iy2
operator|*
name|scale
argument_list|)
operator|-
name|iy
expr_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* clip to chunk bounds, in screen space */
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* transform to image space, and apply uneven scaling */
if|if
condition|(
name|shell
operator|->
name|rotate_transform
condition|)
name|cairo_transform
argument_list|(
name|cr
argument_list|,
name|shell
operator|->
name|rotate_transform
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
operator|-
name|shell
operator|->
name|offset_x
argument_list|,
operator|-
name|shell
operator|->
name|offset_y
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|shell
operator|->
name|scale_x
operator|/
name|scale
argument_list|,
name|shell
operator|->
name|scale_y
operator|/
name|scale
argument_list|)
expr_stmt|;
comment|/* render image */
name|gimp_display_shell_render
argument_list|(
name|shell
argument_list|,
name|cr
argument_list|,
name|ix
argument_list|,
name|iy
argument_list|,
name|iw
argument_list|,
name|ih
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* if the GIMP_BRICK_WALL environment variable is defined,            * show chunk bounds            */
block|{
specifier|static
name|gint
name|brick_wall
init|=
operator|-
literal|1
decl_stmt|;
if|if
condition|(
name|brick_wall
operator|<
literal|0
condition|)
name|brick_wall
operator|=
operator|(
name|g_getenv
argument_list|(
literal|"GIMP_BRICK_WALL"
argument_list|)
operator|!=
name|NULL
operator|)
expr_stmt|;
if|if
condition|(
name|brick_wall
condition|)
block|{
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
block|}
end_function

end_unit

