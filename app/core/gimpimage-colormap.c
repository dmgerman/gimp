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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|guchar
modifier|*
DECL|function|gimp_image_get_colormap (const GimpImage * gimage)
name|gimp_image_get_colormap
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimage
operator|->
name|cmap
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_image_get_colormap_size (const GimpImage * gimage)
name|gimp_image_get_colormap_size
parameter_list|(
specifier|const
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|gimage
operator|->
name|num_cols
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_colormap (GimpImage * gimage,const guchar * cmap,gint n_colors,gboolean push_undo)
name|gimp_image_set_colormap
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|gint
name|n_colors
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cmap
operator|!=
name|NULL
operator|||
name|n_colors
operator|==
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_colors
operator|>=
literal|0
operator|&&
name|n_colors
operator|<=
literal|256
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_colormap
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Set Indexed Palette"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmap
condition|)
block|{
if|if
condition|(
operator|!
name|gimage
operator|->
name|cmap
condition|)
name|gimage
operator|->
name|cmap
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|GIMP_IMAGE_COLORMAP_SIZE
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|gimage
operator|->
name|cmap
argument_list|,
name|cmap
argument_list|,
name|n_colors
operator|*
literal|3
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimage
operator|->
name|cmap
condition|)
name|g_free
argument_list|(
name|gimage
operator|->
name|cmap
argument_list|)
expr_stmt|;
name|gimage
operator|->
name|cmap
operator|=
name|NULL
expr_stmt|;
block|}
name|gimage
operator|->
name|num_cols
operator|=
name|n_colors
expr_stmt|;
name|gimp_image_colormap_changed
argument_list|(
name|gimage
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_get_colormap_entry (GimpImage * gimage,gint color_index,GimpRGB * color)
name|gimp_image_get_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|color_index
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|->
name|cmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color_index
operator|>=
literal|0
operator|&&
name|color_index
operator|<
name|gimage
operator|->
name|num_cols
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
name|color
argument_list|,
name|gimage
operator|->
name|cmap
index|[
name|color_index
operator|*
literal|3
index|]
argument_list|,
name|gimage
operator|->
name|cmap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
name|gimage
operator|->
name|cmap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|,
name|OPAQUE_OPACITY
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_colormap_entry (GimpImage * gimage,gint color_index,const GimpRGB * color,gboolean push_undo)
name|gimp_image_set_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|color_index
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|->
name|cmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color_index
operator|>=
literal|0
operator|&&
name|color_index
operator|<
name|gimage
operator|->
name|num_cols
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_colormap
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Change Indexed Palette Entry"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|gimage
operator|->
name|cmap
index|[
name|color_index
operator|*
literal|3
index|]
argument_list|,
operator|&
name|gimage
operator|->
name|cmap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
operator|&
name|gimage
operator|->
name|cmap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
name|gimp_image_colormap_changed
argument_list|(
name|gimage
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_add_colormap_entry (GimpImage * gimage,const GimpRGB * color)
name|gimp_image_add_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|->
name|cmap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|->
name|num_cols
operator|<
literal|256
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_undo_push_image_colormap
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Add Color to Indexed Palette"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|gimage
operator|->
name|cmap
index|[
name|gimage
operator|->
name|num_cols
operator|*
literal|3
index|]
argument_list|,
operator|&
name|gimage
operator|->
name|cmap
index|[
name|gimage
operator|->
name|num_cols
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
operator|&
name|gimage
operator|->
name|cmap
index|[
name|gimage
operator|->
name|num_cols
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
name|gimage
operator|->
name|num_cols
operator|++
expr_stmt|;
name|gimp_image_colormap_changed
argument_list|(
name|gimage
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

