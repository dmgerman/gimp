begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbufferpreview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpbufferpreview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_buffer_preview_class_init
parameter_list|(
name|GimpBufferPreviewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_preview_init
parameter_list|(
name|GimpBufferPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_preview_get_size
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|size
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_preview_render
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_buffer_preview_create_popup
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_buffer_preview_needs_popup
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPreviewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_buffer_preview_get_type (void)
name|gimp_buffer_preview_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|preview_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|preview_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|preview_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBufferPreviewClass
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
name|gimp_buffer_preview_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpBufferPreview
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_buffer_preview_init
block|,       }
decl_stmt|;
name|preview_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PREVIEW
argument_list|,
literal|"GimpBufferPreview"
argument_list|,
operator|&
name|preview_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|preview_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_preview_class_init (GimpBufferPreviewClass * klass)
name|gimp_buffer_preview_class_init
parameter_list|(
name|GimpBufferPreviewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPreviewClass
modifier|*
name|preview_class
decl_stmt|;
name|preview_class
operator|=
name|GIMP_PREVIEW_CLASS
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
name|preview_class
operator|->
name|get_size
operator|=
name|gimp_buffer_preview_get_size
expr_stmt|;
name|preview_class
operator|->
name|render
operator|=
name|gimp_buffer_preview_render
expr_stmt|;
name|preview_class
operator|->
name|create_popup
operator|=
name|gimp_buffer_preview_create_popup
expr_stmt|;
name|preview_class
operator|->
name|needs_popup
operator|=
name|gimp_buffer_preview_needs_popup
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_preview_init (GimpBufferPreview * buffer_preview)
name|gimp_buffer_preview_init
parameter_list|(
name|GimpBufferPreview
modifier|*
name|buffer_preview
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_preview_get_size (GimpPreview * preview,gint size,gint * width,gint * height)
name|gimp_buffer_preview_get_size
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|size
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|gboolean
name|scaling_up
decl_stmt|;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|gimp_preview_calc_size
argument_list|(
name|preview
argument_list|,
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gimp_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|scaling_up
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_preview_render (GimpPreview * preview)
name|gimp_buffer_preview_render
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|buffer_width
decl_stmt|;
name|gint
name|buffer_height
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
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
decl_stmt|;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|buffer_width
operator|=
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|buffer_height
operator|=
name|gimp_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|width
operator|=
name|preview
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|preview
operator|->
name|height
expr_stmt|;
name|gimp_preview_calc_size
argument_list|(
name|preview
argument_list|,
name|buffer_width
argument_list|,
name|buffer_height
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|1.0
argument_list|,
literal|1.0
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
name|preview
operator|->
name|viewable
argument_list|,
name|buffer_width
argument_list|,
name|buffer_height
argument_list|)
expr_stmt|;
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
else|else
block|{
name|render_buf
operator|=
name|gimp_viewable_get_new_preview
argument_list|(
name|preview
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
name|preview_width
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
name|preview_width
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|preview_height
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
name|preview_height
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|render_buf
operator|->
name|x
operator|||
name|render_buf
operator|->
name|y
condition|)
block|{
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|guchar
name|white
index|[
literal|4
index|]
init|=
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|,
literal|255
block|}
decl_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|render_buf
operator|->
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|white
argument_list|)
expr_stmt|;
name|temp_buf_copy_area
argument_list|(
name|render_buf
argument_list|,
name|temp_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|render_buf
operator|->
name|width
argument_list|,
name|render_buf
operator|->
name|height
argument_list|,
name|render_buf
operator|->
name|x
argument_list|,
name|render_buf
operator|->
name|y
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|render_buf
argument_list|)
expr_stmt|;
name|gimp_preview_render_and_flush
argument_list|(
name|preview
argument_list|,
name|temp_buf
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_preview_render_and_flush
argument_list|(
name|preview
argument_list|,
name|render_buf
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|render_buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_buffer_preview_create_popup (GimpPreview * preview)
name|gimp_buffer_preview_create_popup
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|buffer_width
decl_stmt|;
name|gint
name|buffer_height
decl_stmt|;
name|gint
name|popup_width
decl_stmt|;
name|gint
name|popup_height
decl_stmt|;
name|gboolean
name|scaling_up
decl_stmt|;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|buffer_width
operator|=
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|buffer_height
operator|=
name|gimp_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_preview_calc_size
argument_list|(
name|preview
argument_list|,
name|buffer_width
argument_list|,
name|buffer_height
argument_list|,
name|MIN
argument_list|(
name|preview
operator|->
name|width
operator|*
literal|2
argument_list|,
literal|256
argument_list|)
argument_list|,
name|MIN
argument_list|(
name|preview
operator|->
name|height
operator|*
literal|2
argument_list|,
literal|256
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
operator|&
name|popup_width
argument_list|,
operator|&
name|popup_height
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
return|return
name|gimp_preview_new_full
argument_list|(
name|preview
operator|->
name|viewable
argument_list|,
name|buffer_width
argument_list|,
name|buffer_height
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
else|else
block|{
return|return
name|gimp_preview_new_full
argument_list|(
name|preview
operator|->
name|viewable
argument_list|,
name|popup_width
argument_list|,
name|popup_height
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_buffer_preview_needs_popup (GimpPreview * preview)
name|gimp_buffer_preview_needs_popup
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|gint
name|buffer_width
decl_stmt|;
name|gint
name|buffer_height
decl_stmt|;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|preview
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|buffer_width
operator|=
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|buffer_height
operator|=
name|gimp_buffer_get_height
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer_width
operator|>
name|preview
operator|->
name|width
operator|||
name|buffer_height
operator|>
name|preview
operator|->
name|height
condition|)
return|return
name|TRUE
return|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

