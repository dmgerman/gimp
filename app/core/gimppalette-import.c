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
file|"gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
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
file|"gimpimage-colormap.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette-import.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette-load.h"
end_include

begin_include
include|#
directive|include
file|"gimppickable.h"
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
DECL|function|gimp_palette_import_from_gradient (GimpGradient * gradient,GimpContext * context,gboolean reverse,const gchar * palette_name,gint n_colors)
name|gimp_palette_import_from_gradient
parameter_list|(
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|GimpGradientSegment
modifier|*
name|seg
init|=
name|NULL
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
name|i
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
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
name|context
argument_list|,
name|palette_name
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
name|i
operator|=
literal|0
operator|,
name|cur_x
operator|=
literal|0
init|;
name|i
operator|<
name|n_colors
condition|;
name|i
operator|++
operator|,
name|cur_x
operator|+=
name|dx
control|)
block|{
name|seg
operator|=
name|gimp_gradient_get_color_at
argument_list|(
name|gradient
argument_list|,
name|context
argument_list|,
name|seg
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
DECL|function|gimp_palette_import_store_colors (GHashTable * table,guchar * colors,guchar * colors_real,gint n_colors)
name|gimp_palette_import_store_colors
parameter_list|(
name|GHashTable
modifier|*
name|table
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
name|table
operator|==
name|NULL
condition|)
block|{
name|table
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
name|table
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
name|table
return|;
block|}
name|count_color_entries
operator|++
expr_stmt|;
name|new_color
operator|=
name|g_slice_new
argument_list|(
name|ImgColors
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
name|table
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
name|table
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_import_create_list (gpointer key,gpointer value,gpointer user_data)
name|gimp_palette_import_create_list
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
name|list
init|=
name|user_data
decl_stmt|;
name|ImgColors
modifier|*
name|color_tab
init|=
name|value
decl_stmt|;
operator|*
name|list
operator|=
name|g_slist_prepend
argument_list|(
operator|*
name|list
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
specifier|const
name|ImgColors
modifier|*
name|s1
init|=
name|a
decl_stmt|;
specifier|const
name|ImgColors
modifier|*
name|s2
init|=
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
init|=
name|user_data
decl_stmt|;
name|ImgColors
modifier|*
name|color_tab
init|=
name|data
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
literal|"import-n-colors"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
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
DECL|function|gimp_palette_import_make_palette (GHashTable * table,const gchar * palette_name,GimpContext * context,gint n_colors)
name|gimp_palette_import_make_palette
parameter_list|(
name|GHashTable
modifier|*
name|table
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|list
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|iter
decl_stmt|;
name|palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|context
argument_list|,
name|palette_name
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|table
condition|)
return|return
name|palette
return|;
name|g_hash_table_foreach
argument_list|(
name|table
argument_list|,
name|gimp_palette_import_create_list
argument_list|,
operator|&
name|list
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_sort
argument_list|(
name|list
argument_list|,
name|gimp_palette_import_sort_colors
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
literal|"import-n-colors"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|n_colors
argument_list|)
argument_list|)
expr_stmt|;
name|g_slist_foreach
argument_list|(
name|list
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
literal|"import-n-colors"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Free up used memory    *  Note the same structure is on both the hash list and the sorted    *  list. So only delete it once.    */
name|g_hash_table_destroy
argument_list|(
name|table
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|list
init|;
name|iter
condition|;
name|iter
operator|=
name|iter
operator|->
name|next
control|)
name|g_slice_free
argument_list|(
name|ImgColors
argument_list|,
name|iter
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|list
argument_list|)
expr_stmt|;
return|return
name|palette
return|;
block|}
end_function

begin_function
specifier|static
name|GHashTable
modifier|*
DECL|function|gimp_palette_import_extract (GimpImage * image,GimpPickable * pickable,gint pickable_off_x,gint pickable_off_y,gboolean selection_only,gint x,gint y,gint width,gint height,gint n_colors,gint threshold)
name|gimp_palette_import_extract
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gint
name|pickable_off_x
parameter_list|,
name|gint
name|pickable_off_y
parameter_list|,
name|gboolean
name|selection_only
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|n_colors
parameter_list|,
name|gint
name|threshold
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
name|GeglRectangle
modifier|*
name|mask_roi
init|=
name|NULL
decl_stmt|;
name|GeglRectangle
name|rect
init|=
block|{
name|x
block|,
name|y
block|,
name|width
block|,
name|height
block|}
decl_stmt|;
name|GHashTable
modifier|*
name|colors
init|=
name|NULL
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|mask_bpp
init|=
literal|0
decl_stmt|;
name|buffer
operator|=
name|gimp_pickable_get_buffer
argument_list|(
name|pickable
argument_list|)
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
operator|&
name|rect
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection_only
operator|&&
operator|!
name|gimp_channel_is_empty
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
condition|)
block|{
name|GimpDrawable
modifier|*
name|mask
init|=
name|GIMP_DRAWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
decl_stmt|;
name|rect
operator|.
name|x
operator|=
name|x
operator|+
name|pickable_off_x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|y
operator|+
name|pickable_off_y
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|mask
argument_list|)
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
expr_stmt|;
name|gegl_buffer_iterator_add
argument_list|(
name|iter
argument_list|,
name|buffer
argument_list|,
operator|&
name|rect
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|GEGL_BUFFER_READ
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|mask_roi
operator|=
operator|&
name|iter
operator|->
name|roi
index|[
literal|1
index|]
expr_stmt|;
name|mask_bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|iter
argument_list|)
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|data
init|=
name|iter
operator|->
name|data
index|[
literal|0
index|]
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|mask_data
init|=
name|NULL
decl_stmt|;
name|gint
name|length
init|=
name|iter
operator|->
name|length
decl_stmt|;
if|if
condition|(
name|mask_roi
condition|)
name|mask_data
operator|=
name|iter
operator|->
name|data
index|[
literal|1
index|]
expr_stmt|;
while|while
condition|(
name|length
operator|--
condition|)
block|{
comment|/*  ignore unselected, and completely transparent pixels  */
if|if
condition|(
operator|(
operator|!
name|mask_data
operator|||
operator|*
name|mask_data
operator|)
operator|&&
name|data
index|[
name|ALPHA
index|]
condition|)
block|{
name|guchar
name|rgba
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|guchar
name|rgb_real
index|[
name|MAX_CHANNELS
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|memcpy
argument_list|(
name|rgba
argument_list|,
name|data
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|rgb_real
argument_list|,
name|rgba
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|rgba
index|[
literal|0
index|]
operator|=
operator|(
name|rgba
index|[
literal|0
index|]
operator|/
name|threshold
operator|)
operator|*
name|threshold
expr_stmt|;
name|rgba
index|[
literal|1
index|]
operator|=
operator|(
name|rgba
index|[
literal|1
index|]
operator|/
name|threshold
operator|)
operator|*
name|threshold
expr_stmt|;
name|rgba
index|[
literal|2
index|]
operator|=
operator|(
name|rgba
index|[
literal|2
index|]
operator|/
name|threshold
operator|)
operator|*
name|threshold
expr_stmt|;
name|colors
operator|=
name|gimp_palette_import_store_colors
argument_list|(
name|colors
argument_list|,
name|rgba
argument_list|,
name|rgb_real
argument_list|,
name|n_colors
argument_list|)
expr_stmt|;
block|}
name|data
operator|+=
name|bpp
expr_stmt|;
if|if
condition|(
name|mask_data
condition|)
name|mask_data
operator|+=
name|mask_bpp
expr_stmt|;
block|}
block|}
return|return
name|colors
return|;
block|}
end_function

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_from_image (GimpImage * image,GimpContext * context,const gchar * palette_name,gint n_colors,gint threshold,gboolean selection_only)
name|gimp_palette_import_from_image
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
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
parameter_list|,
name|gboolean
name|selection_only
parameter_list|)
block|{
name|GHashTable
modifier|*
name|colors
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
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
name|gimp_pickable_flush
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection_only
condition|)
block|{
name|gimp_channel_bounds
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|width
operator|-=
name|x
expr_stmt|;
name|height
operator|-=
name|y
expr_stmt|;
block|}
else|else
block|{
name|x
operator|=
literal|0
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|colors
operator|=
name|gimp_palette_import_extract
argument_list|(
name|image
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|image
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|selection_only
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|n_colors
argument_list|,
name|threshold
argument_list|)
expr_stmt|;
return|return
name|gimp_palette_import_make_palette
argument_list|(
name|colors
argument_list|,
name|palette_name
argument_list|,
name|context
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
DECL|function|gimp_palette_import_from_indexed_image (GimpImage * image,GimpContext * context,const gchar * palette_name)
name|gimp_palette_import_from_indexed_image
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
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
specifier|const
name|guchar
modifier|*
name|colormap
decl_stmt|;
name|guint
name|n_colors
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
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_image_get_base_type
argument_list|(
name|image
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
name|context
argument_list|,
name|palette_name
argument_list|)
argument_list|)
expr_stmt|;
name|colormap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|n_colors
operator|=
name|gimp_image_get_colormap_size
argument_list|(
name|image
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
name|n_colors
condition|;
operator|++
name|count
control|)
block|{
name|gchar
name|name
index|[
literal|256
index|]
decl_stmt|;
name|g_snprintf
argument_list|(
name|name
argument_list|,
sizeof|sizeof
argument_list|(
name|name
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Index %d"
argument_list|)
argument_list|,
name|count
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|colormap
index|[
name|count
operator|*
literal|3
operator|+
literal|0
index|]
argument_list|,
name|colormap
index|[
name|count
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
name|colormap
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
name|name
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
comment|/*  create a palette from a drawable  ****************************************/
end_comment

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_from_drawable (GimpDrawable * drawable,GimpContext * context,const gchar * palette_name,gint n_colors,gint threshold,gboolean selection_only)
name|gimp_palette_import_from_drawable
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
parameter_list|,
name|gboolean
name|selection_only
parameter_list|)
block|{
name|GHashTable
modifier|*
name|colors
init|=
name|NULL
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_item_is_attached
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
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
if|if
condition|(
name|selection_only
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_item_mask_intersect
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return
name|NULL
return|;
block|}
else|else
block|{
name|x
operator|=
literal|0
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
name|width
operator|=
name|gimp_item_get_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_item_get_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|colors
operator|=
name|gimp_palette_import_extract
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|GIMP_PICKABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|selection_only
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|n_colors
argument_list|,
name|threshold
argument_list|)
expr_stmt|;
return|return
name|gimp_palette_import_make_palette
argument_list|(
name|colors
argument_list|,
name|palette_name
argument_list|,
name|context
argument_list|,
name|n_colors
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  create a palette from a file  **********************************/
end_comment

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palette_import_from_file (GimpContext * context,const gchar * filename,const gchar * palette_name,GError ** error)
name|gimp_palette_import_from_file
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
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
name|GList
modifier|*
name|palette_list
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
switch|switch
condition|(
name|gimp_palette_load_detect_format
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
name|context
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PALETTE_FILE_FORMAT_ACT
case|:
name|palette_list
operator|=
name|gimp_palette_load_act
argument_list|(
name|context
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PALETTE_FILE_FORMAT_RIFF_PAL
case|:
name|palette_list
operator|=
name|gimp_palette_load_riff
argument_list|(
name|context
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PALETTE_FILE_FORMAT_PSP_PAL
case|:
name|palette_list
operator|=
name|gimp_palette_load_psp
argument_list|(
name|context
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PALETTE_FILE_FORMAT_ACO
case|:
name|palette_list
operator|=
name|gimp_palette_load_aco
argument_list|(
name|context
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PALETTE_FILE_FORMAT_CSS
case|:
name|palette_list
operator|=
name|gimp_palette_load_css
argument_list|(
name|context
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Unknown type of palette file: %s"
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
if|if
condition|(
name|palette_list
condition|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|g_object_ref
argument_list|(
name|palette_list
operator|->
name|data
argument_list|)
decl_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|,
name|palette_name
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|palette_list
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
return|return
name|palette
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

