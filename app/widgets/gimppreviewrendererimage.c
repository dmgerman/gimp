begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppreviewrendererimage.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrendererimage.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_preview_renderer_image_class_init
parameter_list|(
name|GimpPreviewRendererImageClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_renderer_image_init
parameter_list|(
name|GimpPreviewRendererImage
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_renderer_image_render
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPreviewRendererClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_preview_renderer_image_get_type (void)
name|gimp_preview_renderer_image_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|renderer_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|renderer_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|renderer_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPreviewRendererImageClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_preview_renderer_image_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpPreviewRendererImage
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_preview_renderer_image_init
block|,       }
decl_stmt|;
name|renderer_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PREVIEW_RENDERER
argument_list|,
literal|"GimpPreviewRendererImage"
argument_list|,
operator|&
name|renderer_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|renderer_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_renderer_image_class_init (GimpPreviewRendererImageClass * klass)
name|gimp_preview_renderer_image_class_init
parameter_list|(
name|GimpPreviewRendererImageClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPreviewRendererClass
modifier|*
name|renderer_class
decl_stmt|;
name|renderer_class
operator|=
name|GIMP_PREVIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_preview_renderer_image_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_renderer_image_init (GimpPreviewRendererImage * renderer)
name|gimp_preview_renderer_image_init
parameter_list|(
name|GimpPreviewRendererImage
modifier|*
name|renderer
parameter_list|)
block|{
name|renderer
operator|->
name|channel
operator|=
operator|-
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_renderer_image_render (GimpPreviewRenderer * renderer,GtkWidget * widget)
name|gimp_preview_renderer_image_render
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpPreviewRendererImage
modifier|*
name|rendererimage
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gint
name|preview_width
decl_stmt|;
name|gint
name|preview_height
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
name|rendererimage
operator|=
name|GIMP_PREVIEW_RENDERER_IMAGE
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|,
name|renderer
operator|->
name|dot_for_dot
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|,
operator|&
name|preview_width
argument_list|,
operator|&
name|preview_height
argument_list|,
operator|&
name|scaling_up
argument_list|)
expr_stmt|;
if|if
condition|(
name|scaling_up
condition|)
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
name|gimage
operator|->
name|width
argument_list|,
name|gimage
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
name|preview_width
argument_list|,
name|preview_height
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
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
name|preview_width
argument_list|,
name|preview_height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|render_buf
condition|)
block|{
name|gint
name|component_index
init|=
operator|-
literal|1
decl_stmt|;
comment|/*  xresolution != yresolution */
if|if
condition|(
name|preview_width
operator|>
name|renderer
operator|->
name|width
operator|||
name|preview_height
operator|>
name|renderer
operator|->
name|height
condition|)
block|{
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|temp_buf
operator|=
name|temp_buf_scale
argument_list|(
name|render_buf
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
name|temp_buf_free
argument_list|(
name|render_buf
argument_list|)
expr_stmt|;
name|render_buf
operator|=
name|temp_buf
expr_stmt|;
block|}
if|if
condition|(
name|preview_width
operator|<
name|renderer
operator|->
name|width
condition|)
name|render_buf
operator|->
name|x
operator|=
operator|(
name|renderer
operator|->
name|width
operator|-
name|preview_width
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|preview_height
operator|<
name|renderer
operator|->
name|height
condition|)
name|render_buf
operator|->
name|y
operator|=
operator|(
name|renderer
operator|->
name|height
operator|-
name|preview_height
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|rendererimage
operator|->
name|channel
operator|!=
operator|-
literal|1
condition|)
name|component_index
operator|=
name|gimp_image_get_component_index
argument_list|(
name|gimage
argument_list|,
name|rendererimage
operator|->
name|channel
argument_list|)
expr_stmt|;
name|gimp_preview_renderer_render_buffer
argument_list|(
name|renderer
argument_list|,
name|render_buf
argument_list|,
name|component_index
argument_list|,
name|GIMP_PREVIEW_BG_CHECKS
argument_list|,
name|GIMP_PREVIEW_BG_WHITE
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
switch|switch
condition|(
name|rendererimage
operator|->
name|channel
condition|)
block|{
case|case
name|GIMP_RED_CHANNEL
case|:
name|stock_id
operator|=
name|GIMP_STOCK_CHANNEL_RED
expr_stmt|;
break|break;
case|case
name|GIMP_GREEN_CHANNEL
case|:
name|stock_id
operator|=
name|GIMP_STOCK_CHANNEL_GREEN
expr_stmt|;
break|break;
case|case
name|GIMP_BLUE_CHANNEL
case|:
name|stock_id
operator|=
name|GIMP_STOCK_CHANNEL_BLUE
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_CHANNEL
case|:
name|stock_id
operator|=
name|GIMP_STOCK_CHANNEL_GRAY
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_CHANNEL
case|:
name|stock_id
operator|=
name|GIMP_STOCK_QUESTION
expr_stmt|;
break|break;
case|case
name|GIMP_ALPHA_CHANNEL
case|:
name|stock_id
operator|=
name|GIMP_STOCK_CHANNEL_ALPHA
expr_stmt|;
break|break;
default|default:
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_preview_renderer_default_render_stock
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

