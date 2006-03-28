begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererdrawable.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-preview.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererdrawable.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_drawable_render
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
name|GimpViewRendererDrawable
argument_list|,
name|gimp_view_renderer_drawable
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
value|gimp_view_renderer_drawable_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_class_init (GimpViewRendererDrawableClass * klass)
name|gimp_view_renderer_drawable_class_init
parameter_list|(
name|GimpViewRendererDrawableClass
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
name|render
operator|=
name|gimp_view_renderer_drawable_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_init (GimpViewRendererDrawable * renderer)
name|gimp_view_renderer_drawable_init
parameter_list|(
name|GimpViewRendererDrawable
modifier|*
name|renderer
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_drawable_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_drawable_render
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|view_width
decl_stmt|;
name|gint
name|view_height
decl_stmt|;
name|gboolean
name|scaling_up
decl_stmt|;
name|TempBuf
modifier|*
name|render_buf
init|=
name|NULL
decl_stmt|;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|width
operator|=
name|renderer
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|renderer
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|image
operator|&&
operator|!
name|renderer
operator|->
name|is_popup
condition|)
block|{
name|width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|ROUND
argument_list|(
operator|(
operator|(
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|image
operator|->
name|width
operator|)
operator|*
operator|(
name|gdouble
operator|)
name|item
operator|->
name|width
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|ROUND
argument_list|(
operator|(
operator|(
operator|(
name|gdouble
operator|)
name|height
operator|/
operator|(
name|gdouble
operator|)
name|image
operator|->
name|height
operator|)
operator|*
operator|(
name|gdouble
operator|)
name|item
operator|->
name|height
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|item
operator|->
name|width
argument_list|,
name|item
operator|->
name|height
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|renderer
operator|->
name|dot_for_dot
argument_list|,
name|image
operator|->
name|xresolution
argument_list|,
name|image
operator|->
name|yresolution
argument_list|,
operator|&
name|view_width
argument_list|,
operator|&
name|view_height
argument_list|,
operator|&
name|scaling_up
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_viewable_calc_preview_size
argument_list|(
name|item
operator|->
name|width
argument_list|,
name|item
operator|->
name|height
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|renderer
operator|->
name|dot_for_dot
argument_list|,
name|image
condition|?
name|image
operator|->
name|xresolution
else|:
literal|1.0
argument_list|,
name|image
condition|?
name|image
operator|->
name|yresolution
else|:
literal|1.0
argument_list|,
operator|&
name|view_width
argument_list|,
operator|&
name|view_height
argument_list|,
operator|&
name|scaling_up
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|view_width
operator|*
name|view_height
operator|)
operator|<
operator|(
name|item
operator|->
name|width
operator|*
name|item
operator|->
name|height
operator|*
literal|4
operator|)
condition|)
name|scaling_up
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|scaling_up
condition|)
block|{
if|if
condition|(
name|image
operator|&&
operator|!
name|renderer
operator|->
name|is_popup
condition|)
block|{
name|gint
name|src_x
decl_stmt|,
name|src_y
decl_stmt|;
name|gint
name|src_width
decl_stmt|,
name|src_height
decl_stmt|;
if|if
condition|(
name|gimp_rectangle_intersect
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|item
operator|->
name|width
argument_list|,
name|item
operator|->
name|height
argument_list|,
operator|-
name|item
operator|->
name|offset_x
argument_list|,
operator|-
name|item
operator|->
name|offset_y
argument_list|,
name|image
operator|->
name|width
argument_list|,
name|image
operator|->
name|height
argument_list|,
operator|&
name|src_x
argument_list|,
operator|&
name|src_y
argument_list|,
operator|&
name|src_width
argument_list|,
operator|&
name|src_height
argument_list|)
condition|)
block|{
name|gint
name|dest_width
decl_stmt|;
name|gint
name|dest_height
decl_stmt|;
name|dest_width
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|renderer
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|image
operator|->
name|width
operator|)
operator|*
operator|(
name|gdouble
operator|)
name|src_width
argument_list|)
expr_stmt|;
name|dest_height
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
name|gdouble
operator|)
name|renderer
operator|->
name|height
operator|/
operator|(
name|gdouble
operator|)
name|image
operator|->
name|height
operator|)
operator|*
operator|(
name|gdouble
operator|)
name|src_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_width
operator|<
literal|1
condition|)
name|dest_width
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|dest_height
operator|<
literal|1
condition|)
name|dest_height
operator|=
literal|1
expr_stmt|;
name|render_buf
operator|=
name|gimp_drawable_get_sub_preview
argument_list|(
name|drawable
argument_list|,
name|src_x
argument_list|,
name|src_y
argument_list|,
name|src_width
argument_list|,
name|src_height
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|bytes
init|=
name|gimp_drawable_preview_bytes
argument_list|(
name|drawable
argument_list|)
decl_stmt|;
name|guchar
name|empty
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|render_buf
operator|=
name|temp_buf_new
argument_list|(
literal|1
argument_list|,
literal|1
argument_list|,
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|empty
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|temp_buf
operator|=
name|gimp_viewable_get_new_preview
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|item
operator|->
name|width
argument_list|,
name|item
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
condition|)
block|{
name|render_buf
operator|=
name|temp_buf_scale
argument_list|(
name|temp_buf
argument_list|,
name|view_width
argument_list|,
name|view_height
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|render_buf
operator|=
name|gimp_viewable_get_new_preview
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|view_width
argument_list|,
name|view_height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|render_buf
condition|)
block|{
if|if
condition|(
name|image
operator|&&
operator|!
name|renderer
operator|->
name|is_popup
condition|)
block|{
if|if
condition|(
name|item
operator|->
name|offset_x
operator|!=
literal|0
condition|)
name|render_buf
operator|->
name|x
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
operator|(
name|gdouble
operator|)
name|renderer
operator|->
name|width
operator|/
operator|(
name|gdouble
operator|)
name|image
operator|->
name|width
operator|)
operator|*
operator|(
name|gdouble
operator|)
name|item
operator|->
name|offset_x
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
operator|->
name|offset_y
operator|!=
literal|0
condition|)
name|render_buf
operator|->
name|y
operator|=
name|ROUND
argument_list|(
operator|(
operator|(
operator|(
name|gdouble
operator|)
name|renderer
operator|->
name|height
operator|/
operator|(
name|gdouble
operator|)
name|image
operator|->
name|height
operator|)
operator|*
operator|(
name|gdouble
operator|)
name|item
operator|->
name|offset_y
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|scaling_up
condition|)
block|{
if|if
condition|(
name|render_buf
operator|->
name|x
operator|<
literal|0
condition|)
name|render_buf
operator|->
name|x
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|render_buf
operator|->
name|y
operator|<
literal|0
condition|)
name|render_buf
operator|->
name|y
operator|=
literal|0
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|view_width
operator|<
name|width
condition|)
name|render_buf
operator|->
name|x
operator|=
operator|(
name|width
operator|-
name|view_width
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|view_height
operator|<
name|height
condition|)
name|render_buf
operator|->
name|y
operator|=
operator|(
name|height
operator|-
name|view_height
operator|)
operator|/
literal|2
expr_stmt|;
block|}
name|gimp_view_renderer_render_buffer
argument_list|(
name|renderer
argument_list|,
name|render_buf
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_VIEW_BG_CHECKS
argument_list|,
name|GIMP_VIEW_BG_CHECKS
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|render_buf
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gimp_view_renderer_default_render_stock
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

