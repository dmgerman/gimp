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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_buffer_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_buffer_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_buffer_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
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
name|gimp_buffer_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|is_popup
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_buffer_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpTempBuf
modifier|*
name|gimp_buffer_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_buffer_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBuffer,gimp_buffer,GIMP_TYPE_VIEWABLE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBuffer
argument_list|,
argument|gimp_buffer
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_buffer_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_buffer_class_init
parameter_list|(
name|GimpBufferClass
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
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_buffer_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_buffer_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gtk-paste"
expr_stmt|;
name|viewable_class
operator|->
name|get_size
operator|=
name|gimp_buffer_get_size
expr_stmt|;
name|viewable_class
operator|->
name|get_preview_size
operator|=
name|gimp_buffer_get_preview_size
expr_stmt|;
name|viewable_class
operator|->
name|get_popup_size
operator|=
name|gimp_buffer_get_popup_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_buffer_get_new_preview
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_buffer_get_description
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_init (GimpBuffer * buffer)
name|gimp_buffer_init
parameter_list|(
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_finalize (GObject * object)
name|gimp_buffer_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
name|GIMP_BUFFER
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|buffer
operator|->
name|buffer
condition|)
block|{
name|g_object_unref
argument_list|(
name|buffer
operator|->
name|buffer
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|buffer
operator|=
name|NULL
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
name|gint64
DECL|function|gimp_buffer_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_buffer_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
name|GIMP_BUFFER
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_gegl_buffer_get_memsize
argument_list|(
name|buffer
operator|->
name|buffer
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_buffer_get_size (GimpViewable * viewable,gint * width,gint * height)
name|gimp_buffer_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
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
init|=
name|GIMP_BUFFER
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
operator|*
name|width
operator|=
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
operator|*
name|height
operator|=
name|gimp_buffer_get_height
argument_list|(
name|buffer
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
DECL|function|gimp_buffer_get_preview_size (GimpViewable * viewable,gint size,gboolean is_popup,gboolean dot_for_dot,gint * width,gint * height)
name|gimp_buffer_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|is_popup
parameter_list|,
name|gboolean
name|dot_for_dot
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
init|=
name|GIMP_BUFFER
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
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
name|dot_for_dot
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_buffer_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_buffer_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
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
name|width
operator|||
name|buffer_height
operator|>
name|height
condition|)
block|{
name|gboolean
name|scaling_up
decl_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|buffer_width
argument_list|,
name|buffer_height
argument_list|,
name|width
operator|*
literal|2
argument_list|,
name|height
operator|*
literal|2
argument_list|,
name|dot_for_dot
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|popup_width
argument_list|,
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
operator|*
name|popup_width
operator|=
name|buffer_width
expr_stmt|;
operator|*
name|popup_height
operator|=
name|buffer_height
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|GimpTempBuf
modifier|*
DECL|function|gimp_buffer_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_buffer_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
name|GIMP_BUFFER
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|GimpTempBuf
modifier|*
name|preview
decl_stmt|;
name|preview
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|gimp_buffer_get_format
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
operator|->
name|buffer
argument_list|,
name|NULL
argument_list|,
name|MIN
argument_list|(
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|gimp_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
operator|(
name|gdouble
operator|)
name|height
operator|/
operator|(
name|gdouble
operator|)
name|gimp_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|temp_buf_get_data
argument_list|(
name|preview
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
return|return
name|preview
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_buffer_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_buffer_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
init|=
name|GIMP_BUFFER
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%d Ã %d)"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|buffer
argument_list|)
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
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_buffer_new (GeglBuffer * buffer,const gchar * name,gint offset_x,gint offset_y,gboolean copy_pixels)
name|gimp_buffer_new
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|copy_pixels
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|gimp_buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GEGL_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_buffer
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BUFFER
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|TRUE
comment|/* FIXME copy_pixels */
condition|)
name|gimp_buffer
operator|->
name|buffer
operator|=
name|gegl_buffer_dup
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
else|else
name|gimp_buffer
operator|->
name|buffer
operator|=
name|g_object_ref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_buffer
operator|->
name|offset_x
operator|=
name|offset_x
expr_stmt|;
name|gimp_buffer
operator|->
name|offset_y
operator|=
name|offset_y
expr_stmt|;
return|return
name|gimp_buffer
return|;
block|}
end_function

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_buffer_new_from_pixbuf (GdkPixbuf * pixbuf,const gchar * name,gint offset_x,gint offset_y)
name|gimp_buffer_new_from_pixbuf
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|gimp_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_PIXBUF
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_pixbuf_create_buffer
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|gimp_buffer
operator|=
name|gimp_buffer_new
argument_list|(
name|buffer
argument_list|,
name|name
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|gimp_buffer
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_buffer_get_width (const GimpBuffer * buffer)
name|gimp_buffer_get_width
parameter_list|(
specifier|const
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|gegl_buffer_get_width
argument_list|(
name|buffer
operator|->
name|buffer
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_buffer_get_height (const GimpBuffer * buffer)
name|gimp_buffer_get_height
parameter_list|(
specifier|const
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|gegl_buffer_get_height
argument_list|(
name|buffer
operator|->
name|buffer
argument_list|)
return|;
block|}
end_function

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_buffer_get_format (const GimpBuffer * buffer)
name|gimp_buffer_get_format
parameter_list|(
specifier|const
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gegl_buffer_get_format
argument_list|(
name|buffer
operator|->
name|buffer
argument_list|)
return|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_buffer_get_buffer (const GimpBuffer * buffer)
name|gimp_buffer_get_buffer
parameter_list|(
specifier|const
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BUFFER
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|buffer
operator|->
name|buffer
return|;
block|}
end_function

end_unit

