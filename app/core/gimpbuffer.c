begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"gimpbuffer.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_buffer_class_init
parameter_list|(
name|GimpBufferClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_buffer_init
parameter_list|(
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

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
name|TempBuf
modifier|*
name|gimp_buffer_get_new_preview
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_buffer_get_type (void)
name|gimp_buffer_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|buffer_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|buffer_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|buffer_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBufferClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_buffer_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBuffer
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_buffer_init
block|,       }
decl_stmt|;
name|buffer_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
literal|"GimpBuffer"
argument_list|,
operator|&
name|buffer_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|buffer_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_buffer_class_init (GimpBufferClass * klass)
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
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
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
block|{
name|buffer
operator|->
name|tiles
operator|=
name|NULL
expr_stmt|;
block|}
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
decl_stmt|;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|tiles
condition|)
block|{
name|tile_manager_unref
argument_list|(
name|buffer
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|buffer
operator|->
name|tiles
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
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
operator|->
name|tiles
condition|)
name|memsize
operator|+=
name|tile_manager_get_memsize
argument_list|(
name|buffer
operator|->
name|tiles
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
name|TempBuf
modifier|*
DECL|function|gimp_buffer_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_buffer_get_new_preview
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
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|gint
name|buffer_width
decl_stmt|;
name|gint
name|buffer_height
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|buffer_width
operator|=
name|tile_manager_width
argument_list|(
name|buffer
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|buffer_height
operator|=
name|tile_manager_height
argument_list|(
name|buffer
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|tile_manager_bpp
argument_list|(
name|buffer
operator|->
name|tiles
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|buffer_width
argument_list|,
name|buffer_height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer_height
operator|>
name|height
operator|||
name|buffer_width
operator|>
name|width
condition|)
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|buffer_width
argument_list|,
name|buffer_height
argument_list|,
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|destPR
operator|.
name|bytes
operator|=
name|temp_buf
operator|->
name|bytes
expr_stmt|;
name|destPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|w
operator|=
name|temp_buf
operator|->
name|width
expr_stmt|;
name|destPR
operator|.
name|h
operator|=
name|temp_buf
operator|->
name|height
expr_stmt|;
name|destPR
operator|.
name|rowstride
operator|=
name|temp_buf
operator|->
name|width
operator|*
name|destPR
operator|.
name|bytes
expr_stmt|;
name|destPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer_height
operator|>
name|height
operator|||
name|buffer_width
operator|>
name|width
condition|)
block|{
name|gint
name|subsample
decl_stmt|;
comment|/*  calculate 'acceptable' subsample  */
name|subsample
operator|=
literal|1
expr_stmt|;
while|while
condition|(
operator|(
name|width
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|buffer_width
operator|)
operator|&&
operator|(
name|height
operator|*
operator|(
name|subsample
operator|+
literal|1
operator|)
operator|*
literal|2
operator|<
name|buffer_height
operator|)
condition|)
name|subsample
operator|+=
literal|1
expr_stmt|;
name|subsample_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|,
name|subsample
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
return|return
name|temp_buf
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
if|if
condition|(
name|tooltip
condition|)
operator|*
name|tooltip
operator|=
name|NULL
expr_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%d x %d)"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
operator|->
name|name
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
DECL|function|gimp_buffer_new (TileManager * tiles,const gchar * name,gboolean copy_pixels)
name|gimp_buffer_new
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|copy_pixels
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tiles
operator|!=
name|NULL
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
name|width
operator|=
name|tile_manager_width
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|height
operator|=
name|tile_manager_height
argument_list|(
name|tiles
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BUFFER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|copy_pixels
condition|)
block|{
name|buffer
operator|->
name|tiles
operator|=
name|tile_manager_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|tile_manager_bpp
argument_list|(
name|tiles
argument_list|)
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|buffer
operator|->
name|tiles
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|buffer
operator|->
name|tiles
operator|=
name|tiles
expr_stmt|;
block|}
return|return
name|buffer
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
name|tile_manager_width
argument_list|(
name|buffer
operator|->
name|tiles
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
name|tile_manager_height
argument_list|(
name|buffer
operator|->
name|tiles
argument_list|)
return|;
block|}
end_function

end_unit

