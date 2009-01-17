begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrenderergradient.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderergradient.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_gradient_set_context
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_gradient_invalidate
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_gradient_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpViewRendererGradient
argument_list|,
name|gimp_view_renderer_gradient
argument_list|,
name|GIMP_TYPE_VIEW_RENDERER
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_gradient_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_gradient_class_init (GimpViewRendererGradientClass * klass)
name|gimp_view_renderer_gradient_class_init
parameter_list|(
name|GimpViewRendererGradientClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpViewRendererClass
modifier|*
name|renderer_class
init|=
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|renderer_class
operator|->
name|set_context
operator|=
name|gimp_view_renderer_gradient_set_context
expr_stmt|;
name|renderer_class
operator|->
name|invalidate
operator|=
name|gimp_view_renderer_gradient_invalidate
expr_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_view_renderer_gradient_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_gradient_init (GimpViewRendererGradient * renderer)
name|gimp_view_renderer_gradient_init
parameter_list|(
name|GimpViewRendererGradient
modifier|*
name|renderer
parameter_list|)
block|{
name|renderer
operator|->
name|left
operator|=
literal|0.0
expr_stmt|;
name|renderer
operator|->
name|right
operator|=
literal|1.0
expr_stmt|;
name|renderer
operator|->
name|reverse
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_gradient_fg_bg_changed (GimpContext * context,const GimpRGB * color,GimpViewRenderer * renderer)
name|gimp_view_renderer_gradient_fg_bg_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
block|{
if|#
directive|if
literal|0
block|g_printerr ("%s: invalidating %s\n", G_STRFUNC,               gimp_object_get_name (GIMP_OBJECT (renderer->viewable)));
endif|#
directive|endif
name|gimp_view_renderer_invalidate
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_gradient_set_context (GimpViewRenderer * renderer,GimpContext * context)
name|gimp_view_renderer_gradient_set_context
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpViewRendererGradient
modifier|*
name|rendergrad
decl_stmt|;
name|rendergrad
operator|=
name|GIMP_VIEW_RENDERER_GRADIENT
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
if|if
condition|(
name|renderer
operator|->
name|context
operator|&&
name|rendergrad
operator|->
name|has_fg_bg_segments
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|renderer
operator|->
name|context
argument_list|,
name|gimp_view_renderer_gradient_fg_bg_changed
argument_list|,
name|renderer
argument_list|)
expr_stmt|;
block|}
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_context
argument_list|(
name|renderer
argument_list|,
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|renderer
operator|->
name|context
operator|&&
name|rendergrad
operator|->
name|has_fg_bg_segments
condition|)
block|{
name|g_signal_connect
argument_list|(
name|renderer
operator|->
name|context
argument_list|,
literal|"foreground-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_renderer_gradient_fg_bg_changed
argument_list|)
argument_list|,
name|renderer
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|renderer
operator|->
name|context
argument_list|,
literal|"background-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_renderer_gradient_fg_bg_changed
argument_list|)
argument_list|,
name|renderer
argument_list|)
expr_stmt|;
name|gimp_view_renderer_gradient_fg_bg_changed
argument_list|(
name|renderer
operator|->
name|context
argument_list|,
name|NULL
argument_list|,
name|renderer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_gradient_invalidate (GimpViewRenderer * renderer)
name|gimp_view_renderer_gradient_invalidate
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|)
block|{
name|GimpViewRendererGradient
modifier|*
name|rendergrad
decl_stmt|;
name|gboolean
name|has_fg_bg_segments
init|=
name|FALSE
decl_stmt|;
name|rendergrad
operator|=
name|GIMP_VIEW_RENDERER_GRADIENT
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
if|if
condition|(
name|renderer
operator|->
name|viewable
condition|)
name|has_fg_bg_segments
operator|=
name|gimp_gradient_has_fg_bg_segments
argument_list|(
name|GIMP_GRADIENT
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rendergrad
operator|->
name|has_fg_bg_segments
operator|!=
name|has_fg_bg_segments
condition|)
block|{
if|if
condition|(
name|renderer
operator|->
name|context
condition|)
block|{
if|if
condition|(
name|rendergrad
operator|->
name|has_fg_bg_segments
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|renderer
operator|->
name|context
argument_list|,
name|gimp_view_renderer_gradient_fg_bg_changed
argument_list|,
name|renderer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_signal_connect
argument_list|(
name|renderer
operator|->
name|context
argument_list|,
literal|"foreground-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_renderer_gradient_fg_bg_changed
argument_list|)
argument_list|,
name|renderer
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|renderer
operator|->
name|context
argument_list|,
literal|"background-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_renderer_gradient_fg_bg_changed
argument_list|)
argument_list|,
name|renderer
argument_list|)
expr_stmt|;
block|}
block|}
name|rendergrad
operator|->
name|has_fg_bg_segments
operator|=
name|has_fg_bg_segments
expr_stmt|;
block|}
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|invalidate
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_gradient_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_gradient_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpViewRendererGradient
modifier|*
name|rendergrad
init|=
name|GIMP_VIEW_RENDERER_GRADIENT
argument_list|(
name|renderer
argument_list|)
decl_stmt|;
name|GimpGradient
modifier|*
name|gradient
init|=
name|GIMP_GRADIENT
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|dest_stride
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gdouble
name|dx
decl_stmt|,
name|cur_x
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|buf
operator|=
name|g_alloca
argument_list|(
literal|4
operator|*
name|renderer
operator|->
name|width
argument_list|)
expr_stmt|;
name|dx
operator|=
operator|(
name|rendergrad
operator|->
name|right
operator|-
name|rendergrad
operator|->
name|left
operator|)
operator|/
operator|(
name|renderer
operator|->
name|width
operator|-
literal|1
operator|)
expr_stmt|;
name|cur_x
operator|=
name|rendergrad
operator|->
name|left
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|dest
operator|=
name|buf
init|;
name|x
operator|<
name|renderer
operator|->
name|width
condition|;
name|x
operator|++
operator|,
name|dest
operator|+=
literal|4
control|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|seg
operator|=
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|renderer
operator|->
name|context
argument_list|,
name|seg
argument_list|,
name|cur_x
argument_list|,
name|rendergrad
operator|->
name|reverse
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|cur_x
operator|+=
name|dx
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|)
expr_stmt|;
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|dest
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|renderer
operator|->
name|surface
condition|)
name|renderer
operator|->
name|surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|)
expr_stmt|;
name|dest
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|renderer
operator|->
name|surface
argument_list|)
expr_stmt|;
name|dest_stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|renderer
operator|->
name|surface
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|renderer
operator|->
name|height
condition|;
name|y
operator|++
operator|,
name|dest
operator|+=
name|dest_stride
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|buf
argument_list|,
name|renderer
operator|->
name|width
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
name|renderer
operator|->
name|needs_render
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_view_renderer_gradient_set_offsets (GimpViewRendererGradient * renderer,gdouble left,gdouble right,gboolean instant_update)
name|gimp_view_renderer_gradient_set_offsets
parameter_list|(
name|GimpViewRendererGradient
modifier|*
name|renderer
parameter_list|,
name|gdouble
name|left
parameter_list|,
name|gdouble
name|right
parameter_list|,
name|gboolean
name|instant_update
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEW_RENDERER_GRADIENT
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
name|left
operator|=
name|CLAMP
argument_list|(
name|left
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|right
operator|=
name|CLAMP
argument_list|(
name|right
argument_list|,
name|left
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|left
operator|!=
name|renderer
operator|->
name|left
operator|||
name|right
operator|!=
name|renderer
operator|->
name|right
condition|)
block|{
name|renderer
operator|->
name|left
operator|=
name|left
expr_stmt|;
name|renderer
operator|->
name|right
operator|=
name|right
expr_stmt|;
name|gimp_view_renderer_invalidate
argument_list|(
name|GIMP_VIEW_RENDERER
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|instant_update
condition|)
name|gimp_view_renderer_update
argument_list|(
name|GIMP_VIEW_RENDERER
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_view_renderer_gradient_set_reverse (GimpViewRendererGradient * renderer,gboolean reverse)
name|gimp_view_renderer_gradient_set_reverse
parameter_list|(
name|GimpViewRendererGradient
modifier|*
name|renderer
parameter_list|,
name|gboolean
name|reverse
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEW_RENDERER_GRADIENT
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|reverse
operator|!=
name|renderer
operator|->
name|reverse
condition|)
block|{
name|renderer
operator|->
name|reverse
operator|=
name|reverse
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
name|gimp_view_renderer_invalidate
argument_list|(
name|GIMP_VIEW_RENDERER
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_view_renderer_update
argument_list|(
name|GIMP_VIEW_RENDERER
argument_list|(
name|renderer
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

