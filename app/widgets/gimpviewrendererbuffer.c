begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererbuffer.c  * Copyright (C) 2004-2006 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"core/gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererbuffer.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_buffer_render
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpViewRendererBuffer,gimp_view_renderer_buffer,GIMP_TYPE_VIEW_RENDERER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpViewRendererBuffer
argument_list|,
argument|gimp_view_renderer_buffer
argument_list|,
argument|GIMP_TYPE_VIEW_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_buffer_class_init
end_define

begin_function
specifier|static
name|void
name|gimp_view_renderer_buffer_class_init
parameter_list|(
name|GimpViewRendererBufferClass
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
name|gimp_view_renderer_buffer_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_buffer_init (GimpViewRendererBuffer * renderer)
name|gimp_view_renderer_buffer_init
parameter_list|(
name|GimpViewRendererBuffer
modifier|*
name|renderer
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_buffer_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_buffer_render
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
name|gint
name|buffer_width
decl_stmt|;
name|gint
name|buffer_height
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
name|GimpTempBuf
modifier|*
name|render_buf
init|=
name|NULL
decl_stmt|;
name|gimp_viewable_get_size
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
operator|&
name|buffer_width
argument_list|,
operator|&
name|buffer_height
argument_list|)
expr_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|buffer_width
argument_list|,
name|buffer_height
argument_list|,
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|,
name|TRUE
argument_list|,
literal|1.0
argument_list|,
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
if|if
condition|(
name|scaling_up
condition|)
block|{
name|GimpTempBuf
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
name|renderer
operator|->
name|context
argument_list|,
name|buffer_width
argument_list|,
name|buffer_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
condition|)
block|{
name|render_buf
operator|=
name|gimp_temp_buf_scale
argument_list|(
name|temp_buf
argument_list|,
name|view_width
argument_list|,
name|view_height
argument_list|)
expr_stmt|;
name|gimp_temp_buf_unref
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
name|renderer
operator|->
name|context
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
name|gimp_view_renderer_render_temp_buf_simple
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|render_buf
argument_list|)
expr_stmt|;
name|gimp_temp_buf_unref
argument_list|(
name|render_buf
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* no preview available */
block|{
specifier|const
name|gchar
modifier|*
name|icon_name
decl_stmt|;
name|icon_name
operator|=
name|gimp_viewable_get_icon_name
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gimp_view_renderer_render_icon
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|icon_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

