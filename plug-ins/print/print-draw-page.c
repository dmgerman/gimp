begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"print.h"
end_include

begin_include
include|#
directive|include
file|"print-draw-page.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|cairo_surface_t
modifier|*
name|print_cairo_surface_from_drawable
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
specifier|inline
name|void
DECL|function|convert_from_rgb (const guchar * src,guchar * dest,gint pixels)
name|convert_from_rgb
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|pixels
parameter_list|)
block|{
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
name|dest
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|3
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|convert_from_rgba (const guchar * src,guchar * dest,gint pixels)
name|convert_from_rgba
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|pixels
parameter_list|)
block|{
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|dest
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|,
name|src
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|4
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|convert_from_gray (const guchar * src,guchar * dest,gint pixels)
name|convert_from_gray
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|pixels
parameter_list|)
block|{
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
name|dest
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|1
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|convert_from_graya (const guchar * src,guchar * dest,gint pixels)
name|convert_from_graya
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|pixels
parameter_list|)
block|{
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|dest
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|2
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|convert_from_indexed (const guchar * src,guchar * dest,gint pixels,const guchar * cmap)
name|convert_from_indexed
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|pixels
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|)
block|{
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
specifier|const
name|gint
name|i
init|=
literal|3
operator|*
name|src
index|[
literal|0
index|]
decl_stmt|;
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
name|dest
argument_list|,
name|cmap
index|[
name|i
index|]
argument_list|,
name|cmap
index|[
name|i
operator|+
literal|1
index|]
argument_list|,
name|cmap
index|[
name|i
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|1
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|convert_from_indexeda (const guchar * src,guchar * dest,gint pixels,const guchar * cmap)
name|convert_from_indexeda
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|pixels
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|)
block|{
while|while
condition|(
name|pixels
operator|--
condition|)
block|{
specifier|const
name|gint
name|i
init|=
literal|3
operator|*
name|src
index|[
literal|0
index|]
decl_stmt|;
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|dest
argument_list|,
name|cmap
index|[
name|i
index|]
argument_list|,
name|cmap
index|[
name|i
operator|+
literal|1
index|]
argument_list|,
name|cmap
index|[
name|i
operator|+
literal|2
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|src
operator|+=
literal|2
expr_stmt|;
name|dest
operator|+=
literal|4
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|print_draw_page (GtkPrintContext * context,PrintData * data)
name|print_draw_page
parameter_list|(
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|gdouble
name|cr_width
decl_stmt|;
name|gdouble
name|cr_height
decl_stmt|;
name|gdouble
name|cr_dpi_x
decl_stmt|;
name|gdouble
name|cr_dpi_y
decl_stmt|;
name|cr
operator|=
name|gtk_print_context_get_cairo_context
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|surface
operator|=
name|print_cairo_surface_from_drawable
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|cr_width
operator|=
name|gtk_print_context_get_width
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|cr_height
operator|=
name|gtk_print_context_get_height
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|cr_dpi_x
operator|=
name|gtk_print_context_get_dpi_x
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|cr_dpi_y
operator|=
name|gtk_print_context_get_dpi_y
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|data
operator|->
name|offset_x
operator|/
name|cr_dpi_x
operator|*
literal|72.0
argument_list|,
name|data
operator|->
name|offset_y
operator|/
name|cr_dpi_y
operator|*
literal|72.0
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|cr_dpi_x
operator|/
name|data
operator|->
name|xres
argument_list|,
name|cr_dpi_y
operator|/
name|data
operator|->
name|yres
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|cairo_image_surface_get_width
argument_list|(
name|surface
argument_list|)
argument_list|,
name|cairo_image_surface_get_height
argument_list|(
name|surface
argument_list|)
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|surface
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|cairo_surface_t
modifier|*
DECL|function|print_cairo_surface_from_drawable (gint32 drawable_ID)
name|print_cairo_surface_from_drawable
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
decl_stmt|;
name|GimpPixelRgn
name|region
decl_stmt|;
name|GimpImageType
name|image_type
init|=
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
specifier|const
name|gint
name|width
init|=
name|drawable
operator|->
name|width
decl_stmt|;
specifier|const
name|gint
name|height
init|=
name|drawable
operator|->
name|height
decl_stmt|;
name|guchar
name|cmap
index|[
literal|3
operator|*
literal|256
index|]
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|gint
name|stride
decl_stmt|;
name|guint
name|count
init|=
literal|0
decl_stmt|;
name|guint
name|done
init|=
literal|0
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
name|guchar
modifier|*
name|colors
decl_stmt|;
name|gint
name|num_colors
decl_stmt|;
name|colors
operator|=
name|gimp_image_get_colormap
argument_list|(
name|gimp_drawable_get_image
argument_list|(
name|drawable_ID
argument_list|)
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|cmap
argument_list|,
name|colors
argument_list|,
literal|3
operator|*
name|num_colors
argument_list|)
expr_stmt|;
block|}
name|surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_ID
argument_list|)
condition|?
name|CAIRO_FORMAT_ARGB32
else|:
name|CAIRO_FORMAT_RGB24
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|region
argument_list|,
name|drawable
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
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
for|for
control|(
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|1
argument_list|,
operator|&
name|region
argument_list|)
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|region
operator|.
name|data
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|pixels
operator|+
name|region
operator|.
name|y
operator|*
name|stride
operator|+
name|region
operator|.
name|x
operator|*
literal|4
decl_stmt|;
name|gint
name|y
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|region
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
switch|switch
condition|(
name|image_type
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|convert_from_rgb
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|region
operator|.
name|w
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|convert_from_rgba
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|region
operator|.
name|w
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|convert_from_gray
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|region
operator|.
name|w
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|convert_from_graya
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|region
operator|.
name|w
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|convert_from_indexed
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|region
operator|.
name|w
argument_list|,
name|cmap
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|convert_from_indexeda
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|region
operator|.
name|w
argument_list|,
name|cmap
argument_list|)
expr_stmt|;
break|break;
block|}
name|src
operator|+=
name|region
operator|.
name|rowstride
expr_stmt|;
name|dest
operator|+=
name|stride
expr_stmt|;
block|}
name|done
operator|+=
name|region
operator|.
name|h
operator|*
name|region
operator|.
name|w
expr_stmt|;
if|if
condition|(
name|count
operator|++
operator|%
literal|16
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|done
operator|/
operator|(
name|width
operator|*
name|height
operator|)
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|cmap
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|surface
return|;
block|}
end_function

end_unit

