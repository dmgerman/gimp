begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererbrush.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererbrush.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_brush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_brush_render
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

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_brush_draw
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_view_renderer_brush_render_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpViewRendererBrush,gimp_view_renderer_brush,GIMP_TYPE_VIEW_RENDERER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpViewRendererBrush
argument_list|,
argument|gimp_view_renderer_brush
argument_list|,
argument|GIMP_TYPE_VIEW_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_brush_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_view_renderer_brush_class_init
parameter_list|(
name|GimpViewRendererBrushClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewRendererClass
modifier|*
name|renderer_class
init|=
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_view_renderer_brush_finalize
expr_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_view_renderer_brush_render
expr_stmt|;
name|renderer_class
operator|->
name|draw
operator|=
name|gimp_view_renderer_brush_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_brush_init (GimpViewRendererBrush * renderer)
name|gimp_view_renderer_brush_init
parameter_list|(
name|GimpViewRendererBrush
modifier|*
name|renderer
parameter_list|)
block|{
name|renderer
operator|->
name|pipe_timeout_id
operator|=
literal|0
expr_stmt|;
name|renderer
operator|->
name|pipe_animation_index
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_brush_finalize (GObject * object)
name|gimp_view_renderer_brush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpViewRendererBrush
modifier|*
name|renderer
init|=
name|GIMP_VIEW_RENDERER_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|renderer
operator|->
name|pipe_timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|renderer
operator|->
name|pipe_timeout_id
argument_list|)
expr_stmt|;
name|renderer
operator|->
name|pipe_timeout_id
operator|=
literal|0
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_brush_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_brush_render
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
name|GimpViewRendererBrush
modifier|*
name|renderbrush
init|=
name|GIMP_VIEW_RENDERER_BRUSH
argument_list|(
name|renderer
argument_list|)
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
if|if
condition|(
name|renderbrush
operator|->
name|pipe_timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|renderbrush
operator|->
name|pipe_timeout_id
argument_list|)
expr_stmt|;
name|renderbrush
operator|->
name|pipe_timeout_id
operator|=
literal|0
expr_stmt|;
block|}
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
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
operator|->
name|width
operator|<
name|renderer
operator|->
name|width
condition|)
name|temp_buf
operator|->
name|x
operator|=
operator|(
name|renderer
operator|->
name|width
operator|-
name|temp_buf
operator|->
name|width
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|temp_buf
operator|->
name|height
operator|<
name|renderer
operator|->
name|height
condition|)
name|temp_buf
operator|->
name|y
operator|=
operator|(
name|renderer
operator|->
name|height
operator|-
name|temp_buf
operator|->
name|height
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|renderer
operator|->
name|is_popup
condition|)
block|{
name|gimp_view_renderer_render_surface
argument_list|(
name|renderer
argument_list|,
name|temp_buf
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_VIEW_BG_WHITE
argument_list|,
name|GIMP_VIEW_BG_WHITE
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_BRUSH_PIPE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
condition|)
block|{
name|renderbrush
operator|->
name|pipe_animation_index
operator|=
literal|0
expr_stmt|;
name|renderbrush
operator|->
name|pipe_timeout_id
operator|=
name|g_timeout_add
argument_list|(
literal|300
argument_list|,
name|gimp_view_renderer_brush_render_timeout
argument_list|,
name|renderbrush
argument_list|)
expr_stmt|;
block|}
return|return;
block|}
name|gimp_view_renderer_render_surface
argument_list|(
name|renderer
argument_list|,
name|temp_buf
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_VIEW_BG_WHITE
argument_list|,
name|GIMP_VIEW_BG_WHITE
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_view_renderer_brush_render_timeout (gpointer data)
name|gimp_view_renderer_brush_render_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpViewRendererBrush
modifier|*
name|renderbrush
init|=
name|GIMP_VIEW_RENDERER_BRUSH
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpViewRenderer
modifier|*
name|renderer
init|=
name|GIMP_VIEW_RENDERER
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpBrushPipe
modifier|*
name|brush_pipe
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
if|if
condition|(
operator|!
name|renderer
operator|->
name|viewable
condition|)
block|{
name|renderbrush
operator|->
name|pipe_timeout_id
operator|=
literal|0
expr_stmt|;
name|renderbrush
operator|->
name|pipe_animation_index
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|brush_pipe
operator|=
name|GIMP_BRUSH_PIPE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|renderbrush
operator|->
name|pipe_animation_index
operator|++
expr_stmt|;
if|if
condition|(
name|renderbrush
operator|->
name|pipe_animation_index
operator|>=
name|brush_pipe
operator|->
name|nbrushes
condition|)
name|renderbrush
operator|->
name|pipe_animation_index
operator|=
literal|0
expr_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|brush_pipe
operator|->
name|brushes
index|[
name|renderbrush
operator|->
name|pipe_animation_index
index|]
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|gimp_viewable_get_new_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|brush
argument_list|)
argument_list|,
name|renderer
operator|->
name|context
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
if|if
condition|(
name|temp_buf
operator|->
name|width
operator|<
name|renderer
operator|->
name|width
condition|)
name|temp_buf
operator|->
name|x
operator|=
operator|(
name|renderer
operator|->
name|width
operator|-
name|temp_buf
operator|->
name|width
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|temp_buf
operator|->
name|height
operator|<
name|renderer
operator|->
name|height
condition|)
name|temp_buf
operator|->
name|y
operator|=
operator|(
name|renderer
operator|->
name|height
operator|-
name|temp_buf
operator|->
name|height
operator|)
operator|/
literal|2
expr_stmt|;
name|gimp_view_renderer_render_surface
argument_list|(
name|renderer
argument_list|,
name|temp_buf
argument_list|,
operator|-
literal|1
argument_list|,
name|GIMP_VIEW_BG_WHITE
argument_list|,
name|GIMP_VIEW_BG_WHITE
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|gimp_view_renderer_update
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_brush_draw (GimpViewRenderer * renderer,GtkWidget * widget,cairo_t * cr,const GdkRectangle * area)
name|gimp_view_renderer_brush_draw
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|GdkRectangle
modifier|*
name|area
parameter_list|)
block|{
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|draw
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|cr
argument_list|,
name|area
argument_list|)
expr_stmt|;
DECL|macro|INDICATOR_WIDTH
define|#
directive|define
name|INDICATOR_WIDTH
value|7
DECL|macro|INDICATOR_HEIGHT
define|#
directive|define
name|INDICATOR_HEIGHT
value|7
if|if
condition|(
name|renderer
operator|->
name|width
operator|>
literal|2
operator|*
name|INDICATOR_WIDTH
operator|&&
name|renderer
operator|->
name|height
operator|>
literal|2
operator|*
name|INDICATOR_HEIGHT
condition|)
block|{
name|gboolean
name|pipe
init|=
name|GIMP_IS_BRUSH_PIPE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|gboolean
name|generated
init|=
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|gint
name|brush_width
decl_stmt|;
name|gint
name|brush_height
decl_stmt|;
if|if
condition|(
name|generated
operator|||
name|pipe
condition|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|y
operator|+
name|area
operator|->
name|height
argument_list|)
expr_stmt|;
name|cairo_rel_line_to
argument_list|(
name|cr
argument_list|,
operator|-
name|INDICATOR_WIDTH
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_rel_line_to
argument_list|(
name|cr
argument_list|,
name|INDICATOR_WIDTH
argument_list|,
operator|-
name|INDICATOR_HEIGHT
argument_list|)
expr_stmt|;
name|cairo_rel_line_to
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
name|INDICATOR_HEIGHT
argument_list|)
expr_stmt|;
if|if
condition|(
name|pipe
condition|)
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
else|else
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|0.5
argument_list|,
literal|0.6
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
name|gimp_viewable_get_size
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
operator|&
name|brush_width
argument_list|,
operator|&
name|brush_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|renderer
operator|->
name|width
operator|<
name|brush_width
operator|||
name|renderer
operator|->
name|height
operator|<
name|brush_height
condition|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|width
operator|-
name|INDICATOR_WIDTH
operator|+
literal|1
argument_list|,
name|area
operator|->
name|y
operator|+
name|area
operator|->
name|height
operator|-
name|INDICATOR_HEIGHT
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|cairo_rel_line_to
argument_list|(
name|cr
argument_list|,
name|INDICATOR_WIDTH
operator|-
literal|2
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
name|area
operator|->
name|x
operator|+
name|area
operator|->
name|width
operator|-
name|INDICATOR_WIDTH
operator|/
literal|2.0
argument_list|,
name|area
operator|->
name|y
operator|+
name|area
operator|->
name|height
operator|-
name|INDICATOR_HEIGHT
operator|+
literal|1
argument_list|)
expr_stmt|;
name|cairo_rel_line_to
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
name|INDICATOR_WIDTH
operator|-
literal|2
argument_list|)
expr_stmt|;
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
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
block|}
undef|#
directive|undef
name|INDICATOR_WIDTH
undef|#
directive|undef
name|INDICATOR_HEIGHT
block|}
end_function

end_unit

