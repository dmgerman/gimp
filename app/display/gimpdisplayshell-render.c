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
file|"gimpdisplayshell-profile.h"
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
DECL|function|gimp_display_shell_render (GimpDisplayShell * shell,cairo_t * cr,gint x,gint y,gint w,gint h,gdouble scale)
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
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
ifdef|#
directive|ifdef
name|USE_NODE_BLIT
name|GeglNode
modifier|*
name|node
decl_stmt|;
endif|#
directive|endif
name|cairo_surface_t
modifier|*
name|xfer
decl_stmt|;
name|gint
name|xfer_src_x
decl_stmt|;
name|gint
name|xfer_src_y
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
name|cairo_stride
decl_stmt|;
name|guchar
modifier|*
name|cairo_data
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
name|w
operator|<=
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|h
operator|>
literal|0
operator|&&
name|h
operator|<=
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|scale
operator|>
literal|0.0
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
name|buffer
operator|=
name|gimp_pickable_get_buffer
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|USE_NODE_BLIT
name|node
operator|=
name|gimp_projectable_get_graph
argument_list|(
name|GIMP_PROJECTABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_projectable_begin_render
argument_list|(
name|GIMP_PROJECTABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|xfer
operator|=
name|gimp_display_xfer_get_surface
argument_list|(
name|shell
operator|->
name|xfer
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
operator|&
name|xfer_src_x
argument_list|,
operator|&
name|xfer_src_y
argument_list|)
expr_stmt|;
name|cairo_stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|xfer
argument_list|)
expr_stmt|;
name|cairo_data
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|xfer
argument_list|)
operator|+
name|xfer_src_y
operator|*
name|cairo_stride
operator|+
name|xfer_src_x
operator|*
literal|4
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|profile_transform
operator|||
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|gboolean
name|can_convert_to_u8
decl_stmt|;
comment|/*  if there is a profile transform or a display filter, we need        *  to use temp buffers        */
name|can_convert_to_u8
operator|=
name|gimp_display_shell_profile_can_convert_to_u8
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/*  create the filter buffer if we have filters, or can't convert        *  to u8 directly        */
if|if
condition|(
operator|(
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
operator|||
operator|!
name|can_convert_to_u8
operator|)
operator|&&
operator|!
name|shell
operator|->
name|filter_buffer
condition|)
block|{
name|gint
name|fw
init|=
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
decl_stmt|;
name|gint
name|fh
init|=
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
decl_stmt|;
name|shell
operator|->
name|filter_data
operator|=
name|gegl_malloc
argument_list|(
name|fw
operator|*
name|fh
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|shell
operator|->
name|filter_format
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|filter_stride
operator|=
name|fw
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|shell
operator|->
name|filter_format
argument_list|)
expr_stmt|;
name|shell
operator|->
name|filter_buffer
operator|=
name|gegl_buffer_linear_new_from_data
argument_list|(
name|shell
operator|->
name|filter_data
argument_list|,
name|shell
operator|->
name|filter_format
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|fw
argument_list|,
name|fh
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gegl_free
argument_list|,
name|shell
operator|->
name|filter_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
operator|||
name|shell
operator|->
name|filter_transform
condition|)
block|{
comment|/*  if there are no filters, or there is a filter transform,            *  load the projection pixels into the profile_buffer            */
ifndef|#
directive|ifndef
name|USE_NODE_BLIT
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|scale
argument_list|,
name|gimp_projectable_get_format
argument_list|(
name|GIMP_PROJECTABLE
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
name|shell
operator|->
name|profile_data
argument_list|,
name|shell
operator|->
name|profile_stride
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
expr_stmt|;
else|#
directive|else
name|gegl_node_blit
argument_list|(
name|node
argument_list|,
name|scale
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|gimp_projectable_get_format
argument_list|(
name|GIMP_PROJECTABLE
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|,
name|shell
operator|->
name|profile_data
argument_list|,
name|shell
operator|->
name|profile_stride
argument_list|,
name|GEGL_BLIT_CACHE
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
else|else
block|{
comment|/*  otherwise, load the pixels directly into the filter_buffer            */
ifndef|#
directive|ifndef
name|USE_NODE_BLIT
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|scale
argument_list|,
name|shell
operator|->
name|filter_format
argument_list|,
name|shell
operator|->
name|filter_data
argument_list|,
name|shell
operator|->
name|filter_stride
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
expr_stmt|;
else|#
directive|else
name|gegl_node_blit
argument_list|(
name|node
argument_list|,
name|scale
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|shell
operator|->
name|filter_format
argument_list|,
name|shell
operator|->
name|filter_data
argument_list|,
name|shell
operator|->
name|filter_stride
argument_list|,
name|GEGL_BLIT_CACHE
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
comment|/*  if there is a filter transform, convert the pixels from        *  the profile_buffer to the filter_buffer        */
if|if
condition|(
name|shell
operator|->
name|filter_transform
condition|)
block|{
name|gimp_color_transform_process_buffer
argument_list|(
name|shell
operator|->
name|filter_transform
argument_list|,
name|shell
operator|->
name|profile_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|shell
operator|->
name|filter_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  if there are filters, apply them        */
if|if
condition|(
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|GeglBuffer
modifier|*
name|filter_buffer
decl_stmt|;
comment|/*  shift the filter_buffer so that the area passed to            *  the filters is the real render area, allowing for            *  position-dependent filters            */
name|filter_buffer
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_BUFFER
argument_list|,
literal|"source"
argument_list|,
name|shell
operator|->
name|filter_buffer
argument_list|,
literal|"shift-x"
argument_list|,
operator|-
name|x
argument_list|,
literal|"shift-y"
argument_list|,
operator|-
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  convert the filter_buffer in place            */
name|gimp_color_display_stack_convert_buffer
argument_list|(
name|shell
operator|->
name|filter_stack
argument_list|,
name|filter_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|filter_buffer
argument_list|)
expr_stmt|;
block|}
comment|/*  if there is a profile transform...        */
if|if
condition|(
name|shell
operator|->
name|profile_transform
condition|)
block|{
if|if
condition|(
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
condition|)
block|{
comment|/*  if we have filters, convert the pixels in the filter_buffer                *  in-place                */
name|gimp_color_transform_process_buffer
argument_list|(
name|shell
operator|->
name|profile_transform
argument_list|,
name|shell
operator|->
name|filter_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|shell
operator|->
name|filter_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|can_convert_to_u8
condition|)
block|{
comment|/*  otherwise, if we can't convert to u8 directly, convert                *  the pixels from the profile_buffer to the filter_buffer                */
name|gimp_color_transform_process_buffer
argument_list|(
name|shell
operator|->
name|profile_transform
argument_list|,
name|shell
operator|->
name|profile_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|shell
operator|->
name|filter_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GeglBuffer
modifier|*
name|buffer
init|=
name|gegl_buffer_linear_new_from_data
argument_list|(
name|cairo_data
argument_list|,
name|babl_format
argument_list|(
literal|"cairo-ARGB32"
argument_list|)
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|cairo_stride
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
comment|/*  otherwise, convert the profile_buffer directly into                *  the cairo_buffer                */
name|gimp_color_transform_process_buffer
argument_list|(
name|shell
operator|->
name|profile_transform
argument_list|,
name|shell
operator|->
name|profile_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  finally, copy the filter buffer to the cairo-ARGB32 buffer,        *  if necessary        */
if|if
condition|(
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
operator|||
operator|!
name|can_convert_to_u8
condition|)
block|{
name|gegl_buffer_get
argument_list|(
name|shell
operator|->
name|filter_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|babl_format
argument_list|(
literal|"cairo-ARGB32"
argument_list|)
argument_list|,
name|cairo_data
argument_list|,
name|cairo_stride
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/*  otherwise we can copy the projection pixels straight to the        *  cairo-ARGB32 buffer        */
ifndef|#
directive|ifndef
name|USE_NODE_BLIT
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|scale
argument_list|,
name|babl_format
argument_list|(
literal|"cairo-ARGB32"
argument_list|)
argument_list|,
name|cairo_data
argument_list|,
name|cairo_stride
argument_list|,
name|GEGL_ABYSS_CLAMP
argument_list|)
expr_stmt|;
else|#
directive|else
name|gegl_node_blit
argument_list|(
name|node
argument_list|,
name|scale
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"cairo-ARGB32"
argument_list|)
argument_list|,
name|cairo_data
argument_list|,
name|cairo_stride
argument_list|,
name|GEGL_BLIT_CACHE
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
ifdef|#
directive|ifdef
name|USE_NODE_BLIT
name|gimp_projectable_end_render
argument_list|(
name|GIMP_PROJECTABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|shell
operator|->
name|mask
condition|)
block|{
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
argument_list|,
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
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
name|cairo_stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|shell
operator|->
name|mask_surface
argument_list|)
expr_stmt|;
name|cairo_data
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|shell
operator|->
name|mask_surface
argument_list|)
operator|+
name|mask_src_y
operator|*
name|cairo_stride
operator|+
name|mask_src_x
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|shell
operator|->
name|mask
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x
operator|-
name|floor
argument_list|(
name|shell
operator|->
name|mask_offset_x
operator|*
name|scale
argument_list|)
argument_list|,
name|y
operator|-
name|floor
argument_list|(
name|shell
operator|->
name|mask_offset_y
operator|*
name|scale
argument_list|)
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|scale
argument_list|,
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
argument_list|,
name|cairo_data
argument_list|,
name|cairo_stride
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|mask_inverted
condition|)
block|{
name|gint
name|mask_height
init|=
name|h
decl_stmt|;
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
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|cairo_data
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
name|cairo_data
operator|+=
name|cairo_stride
expr_stmt|;
block|}
block|}
block|}
comment|/*  put it to the screen  */
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|xfer
argument_list|,
name|x
operator|-
name|xfer_src_x
argument_list|,
name|y
operator|-
name|xfer_src_y
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
name|x
operator|-
name|mask_src_x
argument_list|,
name|y
operator|-
name|mask_src_y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

