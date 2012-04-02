begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1997-2004 Adam D. Moss<adam@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable-convert.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-colormap.h"
end_include

begin_function
name|void
DECL|function|gimp_drawable_convert_rgb (GimpDrawable * drawable,GimpImage * dest_image,gboolean push_undo)
name|gimp_drawable_convert_rgb
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpImageType
name|type
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|dest_image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|type
operator|=
name|GIMP_IMAGE_TYPE_WITH_ALPHA
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|gimp_image_get_format
argument_list|(
name|dest_image
argument_list|,
name|type
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_set_buffer
argument_list|(
name|drawable
argument_list|,
name|push_undo
argument_list|,
name|NULL
argument_list|,
name|dest_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_convert_grayscale (GimpDrawable * drawable,GimpImage * dest_image,gboolean push_undo)
name|gimp_drawable_convert_grayscale
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpImageType
name|type
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|dest_image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|type
operator|=
name|GIMP_IMAGE_TYPE_WITH_ALPHA
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|gimp_image_get_format
argument_list|(
name|dest_image
argument_list|,
name|type
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_set_buffer
argument_list|(
name|drawable
argument_list|,
name|push_undo
argument_list|,
name|NULL
argument_list|,
name|dest_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_drawable_convert_indexed (GimpDrawable * drawable,GimpImage * dest_image,gboolean push_undo)
name|gimp_drawable_convert_indexed
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpImage
modifier|*
name|dest_image
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|dest_image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|format
operator|=
name|gimp_image_colormap_get_rgba_format
argument_list|(
name|dest_image
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|gimp_image_colormap_get_rgb_format
argument_list|(
name|dest_image
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_set_buffer
argument_list|(
name|drawable
argument_list|,
name|push_undo
argument_list|,
name|NULL
argument_list|,
name|dest_buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

