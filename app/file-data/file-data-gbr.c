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
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush-load.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush-private.h"
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
file|"core/gimplayer-new.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-resize.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptempbuf.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"file-data-gbr.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpImage
modifier|*
name|file_gbr_brush_to_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpBrush
modifier|*
name|file_gbr_image_to_brush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|file_gbr_load_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_gbr_load_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GInputStream
modifier|*
name|input
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|input
condition|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|gimp_brush_load_brush
argument_list|(
name|context
argument_list|,
name|file
argument_list|,
name|input
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|brush
condition|)
block|{
name|image
operator|=
name|file_gbr_brush_to_image
argument_list|(
name|gimp
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|brush
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|input
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_propagate_prefixed_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: "
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|image
operator|!=
name|NULL
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
name|gimp_value_set_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|GimpValueArray
modifier|*
DECL|function|file_gbr_save_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|file_gbr_save_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gint
name|spacing
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_value_get_drawable
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
name|spacing
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|6
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|brush
operator|=
name|file_gbr_image_to_brush
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|name
argument_list|,
name|spacing
argument_list|)
expr_stmt|;
name|gimp_data_set_file
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|,
name|file
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_data_save
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|GimpLayer
modifier|*
DECL|function|file_gbr_brush_to_layer (GimpImage * image,GimpBrush * brush)
name|file_gbr_brush_to_layer
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gboolean
name|alpha
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|GimpTempBuf
modifier|*
name|mask
decl_stmt|;
name|GimpTempBuf
modifier|*
name|pixmap
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_brush_get_mask
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gimp_brush_get_pixmap
argument_list|(
name|brush
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap
condition|)
name|alpha
operator|=
name|TRUE
expr_stmt|;
else|else
name|alpha
operator|=
name|FALSE
expr_stmt|;
name|width
operator|=
name|gimp_temp_buf_get_width
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_temp_buf_get_height
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|image_width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|>
name|image_width
operator|||
name|height
operator|>
name|image_height
condition|)
block|{
name|gint
name|new_width
init|=
name|MAX
argument_list|(
name|image_width
argument_list|,
name|width
argument_list|)
decl_stmt|;
name|gint
name|new_height
init|=
name|MAX
argument_list|(
name|image_height
argument_list|,
name|height
argument_list|)
decl_stmt|;
name|gimp_image_resize
argument_list|(
name|image
argument_list|,
name|gimp_get_user_context
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
argument_list|,
name|new_width
argument_list|,
name|new_height
argument_list|,
operator|(
name|new_width
operator|-
name|image_width
operator|)
operator|/
literal|2
argument_list|,
operator|(
name|new_height
operator|-
name|image_height
operator|)
operator|/
literal|2
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_width
operator|=
name|new_width
expr_stmt|;
name|image_height
operator|=
name|new_height
expr_stmt|;
block|}
name|format
operator|=
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|alpha
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|format
argument_list|,
name|gimp_object_get_name
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|GIMP_LAYER_MODE_NORMAL
argument_list|)
expr_stmt|;
name|gimp_item_set_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|(
name|image_width
operator|-
name|width
operator|)
operator|/
literal|2
argument_list|,
operator|(
name|image_height
operator|-
name|height
operator|)
operator|/
literal|2
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap
condition|)
block|{
name|guchar
modifier|*
name|pixmap_data
decl_stmt|;
name|guchar
modifier|*
name|mask_data
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
name|guchar
modifier|*
name|m
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
argument_list|,
name|gimp_temp_buf_get_data
argument_list|(
name|pixmap
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|pixmap_data
operator|=
name|gegl_buffer_linear_open
argument_list|(
name|buffer
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mask_data
operator|=
name|gimp_temp_buf_get_data
argument_list|(
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|p
operator|=
name|pixmap_data
operator|,
name|m
operator|=
name|mask_data
init|;
name|i
operator|<
name|width
operator|*
name|height
condition|;
name|i
operator|++
operator|,
name|p
operator|+=
literal|4
operator|,
name|m
operator|+=
literal|1
control|)
block|{
name|p
index|[
literal|3
index|]
operator|=
operator|*
name|m
expr_stmt|;
block|}
name|gegl_buffer_linear_close
argument_list|(
name|buffer
argument_list|,
name|pixmap_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|guchar
modifier|*
name|mask_data
init|=
name|gimp_temp_buf_get_data
argument_list|(
name|mask
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
operator|*
name|height
condition|;
name|i
operator|++
control|)
name|mask_data
index|[
name|i
index|]
operator|=
literal|255
operator|-
name|mask_data
index|[
name|i
index|]
expr_stmt|;
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
argument_list|,
name|mask_data
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
block|}
return|return
name|layer
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|file_gbr_drawable_to_brush (GimpDrawable * drawable,const GeglRectangle * rect,const gchar * name,gdouble spacing)
name|file_gbr_drawable_to_brush
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|spacing
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GimpTempBuf
modifier|*
name|mask
decl_stmt|;
name|GimpTempBuf
modifier|*
name|pixmap
init|=
name|NULL
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|width
operator|=
name|rect
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|rect
operator|->
name|height
expr_stmt|;
name|brush
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"mime-type"
argument_list|,
literal|"image/x-gimp-gbr"
argument_list|,
literal|"spacing"
argument_list|,
name|spacing
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|mask
operator|=
name|gimp_temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|guchar
modifier|*
name|m
init|=
name|gimp_temp_buf_get_data
argument_list|(
name|mask
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GimpRGB
name|white
decl_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|white
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
name|rect
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
name|guint8
modifier|*
name|data
init|=
operator|(
name|guint8
operator|*
operator|)
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|data
decl_stmt|;
name|gint
name|j
decl_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|iter
operator|->
name|length
condition|;
name|j
operator|++
control|)
block|{
name|GimpRGB
name|gray
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|dest
decl_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|gray
argument_list|,
name|data
index|[
literal|0
index|]
argument_list|,
name|data
index|[
literal|0
index|]
argument_list|,
name|data
index|[
literal|0
index|]
argument_list|,
name|data
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|gimp_rgb_composite
argument_list|(
operator|&
name|gray
argument_list|,
operator|&
name|white
argument_list|,
name|GIMP_RGB_COMPOSITE_BEHIND
argument_list|)
expr_stmt|;
name|x
operator|=
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|roi
operator|.
name|x
operator|+
name|j
operator|%
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|roi
operator|.
name|width
expr_stmt|;
name|y
operator|=
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|roi
operator|.
name|y
operator|+
name|j
operator|/
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|roi
operator|.
name|width
expr_stmt|;
name|dest
operator|=
name|y
operator|*
name|width
operator|+
name|x
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|gray
argument_list|,
operator|&
name|m
index|[
name|dest
index|]
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|+=
literal|2
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|rect
argument_list|,
literal|1.0
argument_list|,
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
argument_list|,
name|m
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
block|}
comment|/*  invert  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
operator|*
name|height
condition|;
name|i
operator|++
control|)
name|m
index|[
name|i
index|]
operator|=
literal|255
operator|-
name|m
index|[
name|i
index|]
expr_stmt|;
block|}
else|else
block|{
name|pixmap
operator|=
name|gimp_temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|rect
argument_list|,
literal|1.0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
argument_list|,
name|gimp_temp_buf_get_data
argument_list|(
name|pixmap
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|rect
argument_list|,
literal|1.0
argument_list|,
name|babl_format
argument_list|(
literal|"A u8"
argument_list|)
argument_list|,
name|gimp_temp_buf_get_data
argument_list|(
name|mask
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
block|}
name|brush
operator|->
name|priv
operator|->
name|mask
operator|=
name|mask
expr_stmt|;
name|brush
operator|->
name|priv
operator|->
name|pixmap
operator|=
name|pixmap
expr_stmt|;
return|return
name|brush
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpImage
modifier|*
DECL|function|file_gbr_brush_to_image (Gimp * gimp,GimpBrush * brush)
name|file_gbr_brush_to_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|GimpImageBaseType
name|base_type
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|GimpTempBuf
modifier|*
name|mask
init|=
name|gimp_brush_get_mask
argument_list|(
name|brush
argument_list|)
decl_stmt|;
name|GimpTempBuf
modifier|*
name|pixmap
init|=
name|gimp_brush_get_pixmap
argument_list|(
name|brush
argument_list|)
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
if|if
condition|(
name|pixmap
condition|)
name|base_type
operator|=
name|GIMP_RGB
expr_stmt|;
else|else
name|base_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimp_temp_buf_get_width
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_temp_buf_get_height
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_image_new
argument_list|(
name|gimp
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|base_type
argument_list|,
name|GIMP_PRECISION_U8_NON_LINEAR
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-brush-name"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|name
argument_list|)
operator|+
literal|1
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|layer
operator|=
name|file_gbr_brush_to_layer
argument_list|(
name|image
argument_list|,
name|brush
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_function
specifier|static
name|GimpBrush
modifier|*
DECL|function|file_gbr_image_to_brush (GimpImage * image,GimpDrawable * drawable,const gchar * name,gdouble spacing)
name|file_gbr_image_to_brush
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|spacing
parameter_list|)
block|{
name|gint
name|width
init|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
return|return
name|file_gbr_drawable_to_brush
argument_list|(
name|drawable
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
name|name
argument_list|,
name|spacing
argument_list|)
return|;
block|}
end_function

end_unit

