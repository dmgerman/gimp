begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererbrush.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpbrush.h"
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
name|gimp_view_renderer_brush_class_init
parameter_list|(
name|GimpViewRendererBrushClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_brush_init
parameter_list|(
name|GimpViewRendererBrush
modifier|*
name|renderer
parameter_list|)
function_decl|;
end_function_decl

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
name|gboolean
name|gimp_view_renderer_brush_render_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewRendererClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_view_renderer_brush_get_type (void)
name|gimp_view_renderer_brush_get_type
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
name|GimpViewRendererBrushClass
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
name|gimp_view_renderer_brush_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpViewRendererBrush
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_view_renderer_brush_init
block|,       }
decl_stmt|;
name|renderer_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEW_RENDERER
argument_list|,
literal|"GimpViewRendererBrush"
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
DECL|function|gimp_view_renderer_brush_class_init (GimpViewRendererBrushClass * klass)
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|gint
name|brush_width
decl_stmt|;
name|gint
name|brush_height
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
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|brush_width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|brush_height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
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
name|gimp_view_renderer_render_buffer
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
name|brush
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
name|gimp_view_renderer_render_buffer
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
operator|>=
name|INDICATOR_WIDTH
operator|*
literal|2
operator|&&
name|renderer
operator|->
name|height
operator|>=
name|INDICATOR_HEIGHT
operator|*
literal|2
operator|&&
operator|(
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
operator|||
name|GIMP_IS_BRUSH_PIPE
argument_list|(
name|brush
argument_list|)
operator|||
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
operator|)
condition|)
block|{
DECL|macro|WHT
define|#
directive|define
name|WHT
value|{ 255, 255, 255 }
DECL|macro|BLK
define|#
directive|define
name|BLK
value|{   0,   0,   0 }
DECL|macro|RED
define|#
directive|define
name|RED
value|{ 255, 127, 127 }
DECL|macro|BLU
define|#
directive|define
name|BLU
value|{ 127, 150, 255 }
specifier|static
specifier|const
name|guchar
name|scale_indicator_bits
index|[
literal|7
index|]
index|[
literal|7
index|]
index|[
literal|3
index|]
init|=
block|{
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|guchar
name|scale_pipe_indicator_bits
index|[
literal|7
index|]
index|[
literal|7
index|]
index|[
literal|3
index|]
init|=
block|{
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|WHT
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|RED
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|RED
block|,
name|BLK
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|guchar
name|pipe_indicator_bits
index|[
literal|7
index|]
index|[
literal|7
index|]
index|[
literal|3
index|]
init|=
block|{
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|RED
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|}
block|,
block|{
name|WHT
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|,
name|RED
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|guchar
name|scale_genbrush_indicator_bits
index|[
literal|7
index|]
index|[
literal|7
index|]
index|[
literal|3
index|]
init|=
block|{
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|WHT
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|BLU
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|BLK
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLK
block|,
name|WHT
block|,
name|BLU
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|BLU
block|,
name|BLK
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|guchar
name|genbrush_indicator_bits
index|[
literal|7
index|]
index|[
literal|7
index|]
index|[
literal|3
index|]
init|=
block|{
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLU
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|WHT
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|WHT
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|}
block|,
block|{
name|WHT
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|,
name|BLU
block|}
block|}
decl_stmt|;
undef|#
directive|undef
name|WHT
undef|#
directive|undef
name|BLK
undef|#
directive|undef
name|RED
undef|#
directive|undef
name|BLU
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|b
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
name|gboolean
name|alpha
decl_stmt|;
name|gboolean
name|pipe
decl_stmt|;
name|gboolean
name|genbrush
decl_stmt|;
name|gboolean
name|scale
decl_stmt|;
name|offset_x
operator|=
name|renderer
operator|->
name|width
operator|-
name|INDICATOR_WIDTH
expr_stmt|;
name|offset_y
operator|=
name|renderer
operator|->
name|height
operator|-
name|INDICATOR_HEIGHT
expr_stmt|;
name|buf
operator|=
name|renderer
operator|->
name|buffer
operator|+
operator|(
name|offset_y
operator|*
name|renderer
operator|->
name|rowstride
operator|+
name|offset_x
operator|*
name|renderer
operator|->
name|bytes
operator|)
expr_stmt|;
name|pipe
operator|=
name|GIMP_IS_BRUSH_PIPE
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|genbrush
operator|=
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|scale
operator|=
operator|(
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
operator|)
expr_stmt|;
name|alpha
operator|=
operator|(
name|renderer
operator|->
name|bytes
operator|==
literal|4
operator|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|INDICATOR_HEIGHT
condition|;
name|y
operator|++
control|)
block|{
name|b
operator|=
name|buf
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|INDICATOR_WIDTH
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
name|scale
condition|)
block|{
if|if
condition|(
name|pipe
condition|)
block|{
operator|*
name|b
operator|++
operator|=
name|scale_pipe_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|scale_pipe_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|scale_pipe_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|genbrush
condition|)
block|{
operator|*
name|b
operator|++
operator|=
name|scale_genbrush_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|scale_genbrush_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|scale_genbrush_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
else|else
block|{
operator|*
name|b
operator|++
operator|=
name|scale_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|scale_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|scale_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|pipe
condition|)
block|{
operator|*
name|b
operator|++
operator|=
name|pipe_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|pipe_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|pipe_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|genbrush
condition|)
block|{
operator|*
name|b
operator|++
operator|=
name|genbrush_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|genbrush_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|b
operator|++
operator|=
name|genbrush_indicator_bits
index|[
name|y
index|]
index|[
name|x
index|]
index|[
literal|2
index|]
expr_stmt|;
block|}
if|if
condition|(
name|alpha
condition|)
operator|*
name|b
operator|++
operator|=
literal|255
expr_stmt|;
block|}
name|buf
operator|+=
name|renderer
operator|->
name|rowstride
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
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_view_renderer_render_buffer
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

end_unit

