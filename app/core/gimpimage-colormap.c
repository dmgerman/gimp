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
file|<string.h>
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
file|<gdk-pixbuf/gdk-pixbuf.h>
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
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
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototype  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_colormap_set_palette_entry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_image_colormap_init (GimpImage * image)
name|gimp_image_colormap_init
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|GimpContainer
modifier|*
name|palettes
decl_stmt|;
name|gchar
modifier|*
name|palette_name
decl_stmt|;
name|gchar
modifier|*
name|palette_id
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|colormap
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|palette
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|palette_name
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Colormap of Image #%d (%s)"
argument_list|)
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|image
argument_list|)
argument_list|,
name|gimp_image_get_display_name
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|palette_id
operator|=
name|g_strdup_printf
argument_list|(
literal|"gimp-indexed-image-palette-%d"
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|n_colors
operator|=
literal|0
expr_stmt|;
name|private
operator|->
name|colormap
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|GIMP_IMAGE_COLORMAP_SIZE
argument_list|)
expr_stmt|;
name|private
operator|->
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|NULL
argument_list|,
name|palette_name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|babl_palette_rgb
condition|)
block|{
name|gchar
modifier|*
name|format_name
init|=
name|g_strdup_printf
argument_list|(
literal|"-gimp-indexed-format-%d"
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|image
argument_list|)
argument_list|)
decl_stmt|;
name|babl_new_palette
argument_list|(
name|format_name
argument_list|,
operator|&
name|private
operator|->
name|babl_palette_rgb
argument_list|,
operator|&
name|private
operator|->
name|babl_palette_rgba
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|format_name
argument_list|)
expr_stmt|;
block|}
name|gimp_palette_set_columns
argument_list|(
name|private
operator|->
name|palette
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|GIMP_DATA
argument_list|(
name|private
operator|->
name|palette
argument_list|)
argument_list|,
name|palette_id
argument_list|)
expr_stmt|;
name|palettes
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|palettes
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|private
operator|->
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|palette_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|palette_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_colormap_dispose (GimpImage * image)
name|gimp_image_colormap_dispose
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|GimpContainer
modifier|*
name|palettes
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|colormap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|private
operator|->
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|palettes
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|palette_factory
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|palettes
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|private
operator|->
name|palette
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_colormap_free (GimpImage * image)
name|gimp_image_colormap_free
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|colormap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|private
operator|->
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|private
operator|->
name|colormap
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|palette
argument_list|)
expr_stmt|;
comment|/* don't touch the image's babl_palettes because we might still have    * buffers with that palette on the undo stack, and on undoing the    * image back to indexed, we must have exactly these palettes around    */
block|}
end_function

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_image_colormap_get_rgb_format (GimpImage * image)
name|gimp_image_colormap_get_rgb_format
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
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
return|return
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|babl_palette_rgb
return|;
block|}
end_function

begin_function
specifier|const
name|Babl
modifier|*
DECL|function|gimp_image_colormap_get_rgba_format (GimpImage * image)
name|gimp_image_colormap_get_rgba_format
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
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
return|return
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|babl_palette_rgba
return|;
block|}
end_function

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_image_get_colormap_palette (GimpImage * image)
name|gimp_image_get_colormap_palette
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
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
return|return
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|palette
return|;
block|}
end_function

begin_function
specifier|const
name|guchar
modifier|*
DECL|function|gimp_image_get_colormap (GimpImage * image)
name|gimp_image_get_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
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
return|return
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|colormap
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_image_get_colormap_size (GimpImage * image)
name|gimp_image_get_colormap_size
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
operator|->
name|n_colors
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_colormap (GimpImage * image,const guchar * colormap,gint n_colors,gboolean push_undo)
name|gimp_image_set_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|guchar
modifier|*
name|colormap
parameter_list|,
name|gint
name|n_colors
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|colormap
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
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_colormap
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Set Colormap"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|colormap
condition|)
name|memset
argument_list|(
name|private
operator|->
name|colormap
argument_list|,
literal|0
argument_list|,
name|GIMP_IMAGE_COLORMAP_SIZE
argument_list|)
expr_stmt|;
if|if
condition|(
name|colormap
condition|)
block|{
if|if
condition|(
operator|!
name|private
operator|->
name|colormap
condition|)
block|{
name|gimp_image_colormap_init
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|memcpy
argument_list|(
name|private
operator|->
name|colormap
argument_list|,
name|colormap
argument_list|,
name|n_colors
operator|*
literal|3
argument_list|)
expr_stmt|;
block|}
name|private
operator|->
name|n_colors
operator|=
name|n_colors
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|palette
condition|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_data_freeze
argument_list|(
name|GIMP_DATA
argument_list|(
name|private
operator|->
name|palette
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|entry
operator|=
name|gimp_palette_get_entry
argument_list|(
name|private
operator|->
name|palette
argument_list|,
literal|0
argument_list|)
operator|)
condition|)
name|gimp_palette_delete_entry
argument_list|(
name|private
operator|->
name|palette
argument_list|,
name|entry
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|private
operator|->
name|n_colors
condition|;
name|i
operator|++
control|)
name|gimp_image_colormap_set_palette_entry
argument_list|(
name|image
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gimp_data_thaw
argument_list|(
name|GIMP_DATA
argument_list|(
name|private
operator|->
name|palette
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_image_colormap_changed
argument_list|(
name|image
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_unset_colormap (GimpImage * image,gboolean push_undo)
name|gimp_image_unset_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|push_undo
condition|)
name|gimp_image_undo_push_image_colormap
argument_list|(
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Unset Colormap"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|colormap
condition|)
block|{
name|gimp_image_colormap_dispose
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_colormap_free
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|private
operator|->
name|n_colors
operator|=
literal|0
expr_stmt|;
name|gimp_image_colormap_changed
argument_list|(
name|image
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_get_colormap_entry (GimpImage * image,gint color_index,GimpRGB * color)
name|gimp_image_get_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|color_index
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|colormap
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
name|private
operator|->
name|n_colors
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
name|private
operator|->
name|colormap
index|[
name|color_index
operator|*
literal|3
index|]
argument_list|,
name|private
operator|->
name|colormap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
name|private
operator|->
name|colormap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_set_colormap_entry (GimpImage * image,gint color_index,const GimpRGB * color,gboolean push_undo)
name|gimp_image_set_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|image
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
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|colormap
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
name|private
operator|->
name|n_colors
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
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Change Colormap entry"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|private
operator|->
name|colormap
index|[
name|color_index
operator|*
literal|3
index|]
argument_list|,
operator|&
name|private
operator|->
name|colormap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
operator|&
name|private
operator|->
name|colormap
index|[
name|color_index
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|palette
condition|)
name|gimp_image_colormap_set_palette_entry
argument_list|(
name|image
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
name|gimp_image_colormap_changed
argument_list|(
name|image
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_add_colormap_entry (GimpImage * image,const GimpRGB * color)
name|gimp_image_add_colormap_entry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|colormap
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|n_colors
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
name|image
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Add Color to Colormap"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|color
argument_list|,
operator|&
name|private
operator|->
name|colormap
index|[
name|private
operator|->
name|n_colors
operator|*
literal|3
index|]
argument_list|,
operator|&
name|private
operator|->
name|colormap
index|[
name|private
operator|->
name|n_colors
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
operator|&
name|private
operator|->
name|colormap
index|[
name|private
operator|->
name|n_colors
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|palette
condition|)
name|gimp_image_colormap_set_palette_entry
argument_list|(
name|image
argument_list|,
name|private
operator|->
name|n_colors
operator|-
literal|1
argument_list|)
expr_stmt|;
name|private
operator|->
name|n_colors
operator|++
expr_stmt|;
name|gimp_image_colormap_changed
argument_list|(
name|image
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_image_colormap_set_palette_entry (GimpImage * image,gint index)
name|gimp_image_colormap_set_palette_entry
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
init|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gchar
name|name
index|[
literal|64
index|]
decl_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|private
operator|->
name|colormap
index|[
literal|3
operator|*
name|index
operator|+
literal|0
index|]
argument_list|,
name|private
operator|->
name|colormap
index|[
literal|3
operator|*
name|index
operator|+
literal|1
index|]
argument_list|,
name|private
operator|->
name|colormap
index|[
literal|3
operator|*
name|index
operator|+
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|name
argument_list|,
sizeof|sizeof
argument_list|(
name|name
argument_list|)
argument_list|,
literal|"#%d"
argument_list|,
name|index
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_palette_get_n_colors
argument_list|(
name|private
operator|->
name|palette
argument_list|)
operator|<
name|private
operator|->
name|n_colors
condition|)
name|gimp_palette_add_entry
argument_list|(
name|private
operator|->
name|palette
argument_list|,
name|index
argument_list|,
name|name
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_palette_set_entry
argument_list|(
name|private
operator|->
name|palette
argument_list|,
name|index
argument_list|,
name|name
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

