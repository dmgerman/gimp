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

begin_comment
comment|/* memcpy */
end_comment

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimpprojection.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|MAX_IMAGE_COLORS
define|#
directive|define
name|MAX_IMAGE_COLORS
value|(10000 * 2)
end_define

begin_comment
comment|/*  create a palette from a gradient  ****************************************/
end_comment

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_from_gradient (GimpGradient * gradient,gboolean reverse,const gchar * palette_name,gint n_colors)
name|gimp_palette_import_from_gradient
parameter_list|(
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|gboolean
name|reverse
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gint
name|n_colors
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|gdouble
name|dx
decl_stmt|,
name|cur_x
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|loop
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GRADIENT
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|palette_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_colors
operator|>
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|palette_name
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|dx
operator|=
literal|1.0
operator|/
operator|(
name|n_colors
operator|-
literal|1
operator|)
expr_stmt|;
for|for
control|(
name|loop
operator|=
literal|0
operator|,
name|cur_x
operator|=
literal|0
init|;
name|loop
operator|<
name|n_colors
condition|;
name|loop
operator|++
operator|,
name|cur_x
operator|+=
name|dx
control|)
block|{
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|cur_x
argument_list|,
name|reverse
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
return|return
name|palette
return|;
block|}
end_function

begin_comment
comment|/*  create a palette from a non-indexed image  *******************************/
end_comment

begin_typedef
DECL|typedef|ImgColors
typedef|typedef
name|struct
name|_ImgColors
name|ImgColors
typedef|;
end_typedef

begin_struct
DECL|struct|_ImgColors
struct|struct
name|_ImgColors
block|{
DECL|member|count
name|guint
name|count
decl_stmt|;
DECL|member|r_adj
name|guint
name|r_adj
decl_stmt|;
DECL|member|g_adj
name|guint
name|g_adj
decl_stmt|;
DECL|member|b_adj
name|guint
name|b_adj
decl_stmt|;
DECL|member|r
name|guchar
name|r
decl_stmt|;
DECL|member|g
name|guchar
name|g
decl_stmt|;
DECL|member|b
name|guchar
name|b
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|count_color_entries
specifier|static
name|gint
name|count_color_entries
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GHashTable
modifier|*
DECL|function|gimp_palette_import_store_colors (GHashTable * h_array,guchar * colors,guchar * colors_real,gint n_colors)
name|gimp_palette_import_store_colors
parameter_list|(
name|GHashTable
modifier|*
name|h_array
parameter_list|,
name|guchar
modifier|*
name|colors
parameter_list|,
name|guchar
modifier|*
name|colors_real
parameter_list|,
name|gint
name|n_colors
parameter_list|)
block|{
name|gpointer
name|found_color
init|=
name|NULL
decl_stmt|;
name|ImgColors
modifier|*
name|new_color
decl_stmt|;
name|guint
name|key_colors
init|=
name|colors
index|[
literal|0
index|]
operator|*
literal|256
operator|*
literal|256
operator|+
name|colors
index|[
literal|1
index|]
operator|*
literal|256
operator|+
name|colors
index|[
literal|2
index|]
decl_stmt|;
if|if
condition|(
name|h_array
operator|==
name|NULL
condition|)
block|{
name|h_array
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|g_direct_equal
argument_list|)
expr_stmt|;
name|count_color_entries
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|found_color
operator|=
name|g_hash_table_lookup
argument_list|(
name|h_array
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|key_colors
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|found_color
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|count_color_entries
operator|>
name|MAX_IMAGE_COLORS
condition|)
block|{
comment|/* Don't add any more new ones */
return|return
name|h_array
return|;
block|}
name|count_color_entries
operator|++
expr_stmt|;
name|new_color
operator|=
name|g_new
argument_list|(
name|ImgColors
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_color
operator|->
name|count
operator|=
literal|1
expr_stmt|;
name|new_color
operator|->
name|r_adj
operator|=
literal|0
expr_stmt|;
name|new_color
operator|->
name|g_adj
operator|=
literal|0
expr_stmt|;
name|new_color
operator|->
name|b_adj
operator|=
literal|0
expr_stmt|;
name|new_color
operator|->
name|r
operator|=
name|colors
index|[
literal|0
index|]
expr_stmt|;
name|new_color
operator|->
name|g
operator|=
name|colors
index|[
literal|1
index|]
expr_stmt|;
name|new_color
operator|->
name|b
operator|=
name|colors
index|[
literal|2
index|]
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|h_array
argument_list|,
name|GUINT_TO_POINTER
argument_list|(
name|key_colors
argument_list|)
argument_list|,
name|new_color
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new_color
operator|=
operator|(
name|ImgColors
operator|*
operator|)
name|found_color
expr_stmt|;
if|if
condition|(
name|new_color
operator|->
name|count
operator|<
operator|(
name|G_MAXINT
operator|-
literal|1
operator|)
condition|)
name|new_color
operator|->
name|count
operator|++
expr_stmt|;
comment|/* Now do the adjustments ...*/
name|new_color
operator|->
name|r_adj
operator|+=
operator|(
name|colors_real
index|[
literal|0
index|]
operator|-
name|colors
index|[
literal|0
index|]
operator|)
expr_stmt|;
name|new_color
operator|->
name|g_adj
operator|+=
operator|(
name|colors_real
index|[
literal|1
index|]
operator|-
name|colors
index|[
literal|1
index|]
operator|)
expr_stmt|;
name|new_color
operator|->
name|b_adj
operator|+=
operator|(
name|colors_real
index|[
literal|2
index|]
operator|-
name|colors
index|[
literal|2
index|]
operator|)
expr_stmt|;
comment|/* Boundary conditions */
if|if
condition|(
name|new_color
operator|->
name|r_adj
operator|>
operator|(
name|G_MAXINT
operator|-
literal|255
operator|)
condition|)
name|new_color
operator|->
name|r_adj
operator|/=
name|new_color
operator|->
name|count
expr_stmt|;
if|if
condition|(
name|new_color
operator|->
name|g_adj
operator|>
operator|(
name|G_MAXINT
operator|-
literal|255
operator|)
condition|)
name|new_color
operator|->
name|g_adj
operator|/=
name|new_color
operator|->
name|count
expr_stmt|;
if|if
condition|(
name|new_color
operator|->
name|b_adj
operator|>
operator|(
name|G_MAXINT
operator|-
literal|255
operator|)
condition|)
name|new_color
operator|->
name|b_adj
operator|/=
name|new_color
operator|->
name|count
expr_stmt|;
block|}
return|return
name|h_array
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_import_create_sorted_list (gpointer key,gpointer value,gpointer user_data)
name|gimp_palette_import_create_sorted_list
parameter_list|(
name|gpointer
name|key
parameter_list|,
name|gpointer
name|value
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GSList
modifier|*
modifier|*
name|sorted_list
init|=
operator|(
name|GSList
operator|*
operator|*
operator|)
name|user_data
decl_stmt|;
name|ImgColors
modifier|*
name|color_tab
init|=
operator|(
name|ImgColors
operator|*
operator|)
name|value
decl_stmt|;
operator|*
name|sorted_list
operator|=
name|g_slist_prepend
argument_list|(
operator|*
name|sorted_list
argument_list|,
name|color_tab
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_palette_import_sort_colors (gconstpointer a,gconstpointer b)
name|gimp_palette_import_sort_colors
parameter_list|(
name|gconstpointer
name|a
parameter_list|,
name|gconstpointer
name|b
parameter_list|)
block|{
name|ImgColors
modifier|*
name|s1
init|=
operator|(
name|ImgColors
operator|*
operator|)
name|a
decl_stmt|;
name|ImgColors
modifier|*
name|s2
init|=
operator|(
name|ImgColors
operator|*
operator|)
name|b
decl_stmt|;
if|if
condition|(
name|s1
operator|->
name|count
operator|>
name|s2
operator|->
name|count
condition|)
return|return
operator|-
literal|1
return|;
if|if
condition|(
name|s1
operator|->
name|count
operator|<
name|s2
operator|->
name|count
condition|)
return|return
literal|1
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_import_create_image_palette (gpointer data,gpointer user_data)
name|gimp_palette_import_create_image_palette
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|ImgColors
modifier|*
name|color_tab
decl_stmt|;
name|gint
name|n_colors
decl_stmt|;
name|gchar
modifier|*
name|lab
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|palette
operator|=
operator|(
name|GimpPalette
operator|*
operator|)
name|user_data
expr_stmt|;
name|color_tab
operator|=
operator|(
name|ImgColors
operator|*
operator|)
name|data
expr_stmt|;
name|n_colors
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
literal|"import_n_colors"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|palette
operator|->
name|n_colors
operator|>=
name|n_colors
condition|)
return|return;
name|lab
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s (occurs %u)"
argument_list|,
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|,
name|color_tab
operator|->
name|count
argument_list|)
expr_stmt|;
comment|/* Adjust the colors to the mean of the the sample */
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|(
name|guchar
operator|)
name|color_tab
operator|->
name|r
operator|+
operator|(
name|color_tab
operator|->
name|r_adj
operator|/
name|color_tab
operator|->
name|count
operator|)
argument_list|,
operator|(
name|guchar
operator|)
name|color_tab
operator|->
name|g
operator|+
operator|(
name|color_tab
operator|->
name|g_adj
operator|/
name|color_tab
operator|->
name|count
operator|)
argument_list|,
operator|(
name|guchar
operator|)
name|color_tab
operator|->
name|b
operator|+
operator|(
name|color_tab
operator|->
name|b_adj
operator|/
name|color_tab
operator|->
name|count
operator|)
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
operator|-
literal|1
argument_list|,
name|lab
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lab
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_image_make_palette (GHashTable * h_array,const gchar * palette_name,gint n_colors)
name|gimp_palette_import_image_make_palette
parameter_list|(
name|GHashTable
modifier|*
name|h_array
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gint
name|n_colors
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GSList
modifier|*
name|sorted_list
init|=
name|NULL
decl_stmt|;
name|g_hash_table_foreach
argument_list|(
name|h_array
argument_list|,
name|gimp_palette_import_create_sorted_list
argument_list|,
operator|&
name|sorted_list
argument_list|)
expr_stmt|;
name|sorted_list
operator|=
name|g_slist_sort
argument_list|(
name|sorted_list
argument_list|,
name|gimp_palette_import_sort_colors
argument_list|)
expr_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|palette_name
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
literal|"import_n_colors"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|n_colors
argument_list|)
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
name|sorted_list
argument_list|,
name|gimp_palette_import_create_image_palette
argument_list|,
name|palette
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
literal|"import_n_colors"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Free up used memory    *  Note the same structure is on both the hash list and the sorted    *  list. So only delete it once.    */
name|g_hash_table_destroy
argument_list|(
name|h_array
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
name|sorted_list
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|sorted_list
argument_list|)
expr_stmt|;
return|return
name|palette
return|;
block|}
end_function

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_from_image (GimpImage * gimage,const gchar * palette_name,gint n_colors,gint threshold)
name|gimp_palette_import_from_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gint
name|n_colors
parameter_list|,
name|gint
name|threshold
parameter_list|)
block|{
name|PixelRegion
name|imagePR
decl_stmt|;
name|guchar
modifier|*
name|image_data
decl_stmt|;
name|guchar
modifier|*
name|idata
decl_stmt|;
name|guchar
name|rgb
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|guchar
name|rgb_real
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|,
name|indexed
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|,
name|alpha
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|void
modifier|*
name|pr
decl_stmt|;
name|GimpImageType
name|d_type
decl_stmt|;
name|GHashTable
modifier|*
name|store_array
init|=
name|NULL
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|palette_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_colors
operator|>
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|threshold
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Get the image information  */
name|d_type
operator|=
name|gimp_projection_get_image_type
argument_list|(
name|gimage
operator|->
name|projection
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|gimp_projection_get_bytes
argument_list|(
name|gimage
operator|->
name|projection
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|d_type
argument_list|)
expr_stmt|;
name|indexed
operator|=
name|GIMP_IMAGE_TYPE_IS_INDEXED
argument_list|(
name|d_type
argument_list|)
expr_stmt|;
name|width
operator|=
name|gimage
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|gimage
operator|->
name|height
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|imagePR
argument_list|,
name|gimp_projection_get_tiles
argument_list|(
name|gimage
operator|->
name|projection
argument_list|)
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
name|alpha
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
comment|/*  iterate over the entire image  */
for|for
control|(
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|imagePR
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|image_data
operator|=
name|imagePR
operator|.
name|data
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|imagePR
operator|.
name|h
condition|;
name|i
operator|++
control|)
block|{
name|idata
operator|=
name|image_data
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|imagePR
operator|.
name|w
condition|;
name|j
operator|++
control|)
block|{
comment|/*  Get the rgb values for the color  */
name|gimp_image_get_color
argument_list|(
name|gimage
argument_list|,
name|d_type
argument_list|,
name|idata
argument_list|,
name|rgb
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rgb_real
argument_list|,
name|rgb
argument_list|,
name|MAX_CHANNELS
argument_list|)
expr_stmt|;
comment|/* Structure copy */
name|rgb
index|[
literal|0
index|]
operator|=
operator|(
name|rgb
index|[
literal|0
index|]
operator|/
name|threshold
operator|)
operator|*
name|threshold
expr_stmt|;
name|rgb
index|[
literal|1
index|]
operator|=
operator|(
name|rgb
index|[
literal|1
index|]
operator|/
name|threshold
operator|)
operator|*
name|threshold
expr_stmt|;
name|rgb
index|[
literal|2
index|]
operator|=
operator|(
name|rgb
index|[
literal|2
index|]
operator|/
name|threshold
operator|)
operator|*
name|threshold
expr_stmt|;
name|store_array
operator|=
name|gimp_palette_import_store_colors
argument_list|(
name|store_array
argument_list|,
name|rgb
argument_list|,
name|rgb_real
argument_list|,
name|n_colors
argument_list|)
expr_stmt|;
name|idata
operator|+=
name|bytes
expr_stmt|;
block|}
name|image_data
operator|+=
name|imagePR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
return|return
name|gimp_palette_import_image_make_palette
argument_list|(
name|store_array
argument_list|,
name|palette_name
argument_list|,
name|n_colors
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  create a palette from an indexed image  **********************************/
end_comment

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_from_indexed_image (GimpImage * gimage,const gchar * palette_name)
name|gimp_palette_import_from_indexed_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|gint
name|count
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|==
name|GIMP_INDEXED
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|palette_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|palette_name
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|count
operator|=
literal|0
init|;
name|count
operator|<
name|gimage
operator|->
name|num_cols
condition|;
operator|++
name|count
control|)
block|{
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|gimage
operator|->
name|cmap
index|[
name|count
operator|*
literal|3
index|]
argument_list|,
name|gimage
operator|->
name|cmap
index|[
name|count
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
name|count
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
return|return
name|palette
return|;
block|}
end_function

begin_comment
comment|/*  create a palette from a file  **********************************/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a3d91ec0103
block|{
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_UNKNOWN
name|GIMP_PALETTE_FILE_FORMAT_UNKNOWN
block|,
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_GPL
name|GIMP_PALETTE_FILE_FORMAT_GPL
block|,
comment|/*  GIMP palette file                    */
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_PAL
name|GIMP_PALETTE_FILE_FORMAT_PAL
block|,
comment|/*  RIFF palette file                    */
DECL|enumerator|GIMP_PALETTE_FILE_FORMAT_ACT
name|GIMP_PALETTE_FILE_FORMAT_ACT
comment|/*  Photoshop binary color palette file  */
DECL|typedef|GimpPaletteFileFormat
block|}
name|GimpPaletteFileFormat
typedef|;
end_typedef

begin_function
specifier|static
name|GimpPaletteFileFormat
DECL|function|gimp_palette_detect_file_format (const gchar * filename)
name|gimp_palette_detect_file_format
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpPaletteFileFormat
name|format
init|=
name|GIMP_PALETTE_FILE_FORMAT_UNKNOWN
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|guchar
name|header
index|[
literal|16
index|]
decl_stmt|;
name|struct
name|stat
name|file_stat
decl_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
condition|)
block|{
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|header
argument_list|,
sizeof|sizeof
argument_list|(
name|header
argument_list|)
argument_list|)
operator|==
sizeof|sizeof
argument_list|(
name|header
argument_list|)
condition|)
block|{
if|if
condition|(
name|strncmp
argument_list|(
name|header
operator|+
literal|0
argument_list|,
literal|"RIFF"
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
operator|&&
name|strncmp
argument_list|(
name|header
operator|+
literal|8
argument_list|,
literal|"PAL data"
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
condition|)
block|{
name|format
operator|=
name|GIMP_PALETTE_FILE_FORMAT_PAL
expr_stmt|;
block|}
if|if
condition|(
name|strncmp
argument_list|(
name|header
argument_list|,
literal|"GIMP Palette"
argument_list|,
literal|12
argument_list|)
operator|==
literal|0
condition|)
block|{
name|format
operator|=
name|GIMP_PALETTE_FILE_FORMAT_GPL
expr_stmt|;
block|}
block|}
if|if
condition|(
name|fstat
argument_list|(
name|fd
argument_list|,
operator|&
name|file_stat
argument_list|)
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
name|file_stat
operator|.
name|st_size
operator|==
literal|768
condition|)
name|format
operator|=
name|GIMP_PALETTE_FILE_FORMAT_ACT
expr_stmt|;
block|}
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
block|}
return|return
name|format
return|;
block|}
end_function

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_from_file (const gchar * filename,const gchar * palette_name,GError ** error)
name|gimp_palette_import_from_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|palette_list
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|guchar
name|color_bytes
index|[
literal|4
index|]
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|palette_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fd
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
switch|switch
condition|(
name|gimp_palette_detect_file_format
argument_list|(
name|filename
argument_list|)
condition|)
block|{
case|case
name|GIMP_PALETTE_FILE_FORMAT_GPL
case|:
name|palette_list
operator|=
name|gimp_palette_load
argument_list|(
name|filename
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|palette_list
condition|)
block|{
name|palette
operator|=
name|palette_list
operator|->
name|data
expr_stmt|;
name|g_list_free
argument_list|(
name|palette_list
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PALETTE_FILE_FORMAT_ACT
case|:
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|palette_name
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|color_bytes
argument_list|,
literal|3
argument_list|)
operator|==
literal|3
condition|)
block|{
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|color_bytes
index|[
literal|0
index|]
argument_list|,
name|color_bytes
index|[
literal|1
index|]
argument_list|,
name|color_bytes
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PALETTE_FILE_FORMAT_PAL
case|:
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|palette_name
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|lseek
argument_list|(
name|fd
argument_list|,
literal|28
argument_list|,
name|SEEK_SET
argument_list|)
expr_stmt|;
while|while
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|color_bytes
argument_list|,
sizeof|sizeof
argument_list|(
name|color_bytes
argument_list|)
argument_list|)
operator|==
sizeof|sizeof
argument_list|(
name|color_bytes
argument_list|)
condition|)
block|{
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|color_bytes
index|[
literal|0
index|]
argument_list|,
name|color_bytes
index|[
literal|1
index|]
argument_list|,
name|color_bytes
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|palette
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Unknown type of palette file:\n%s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
return|return
name|palette
return|;
block|}
end_function

end_unit

