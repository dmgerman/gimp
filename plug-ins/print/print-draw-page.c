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
file|<time.h>
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

begin_comment
comment|/* In points */
end_comment

begin_define
DECL|macro|HEADER_HEIGHT
define|#
directive|define
name|HEADER_HEIGHT
value|(20 * 72.0 / 25.4)
end_define

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|0.0001
end_define

begin_function_decl
specifier|static
name|cairo_surface_t
modifier|*
name|create_surface
parameter_list|(
name|guchar
modifier|*
name|pixels
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
name|rowstride
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|draw_info_header
parameter_list|(
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|draw_page_cairo (GtkPrintContext * context,PrintData * data)
name|draw_page_cairo
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
name|gint
name|tile_height
init|=
name|gimp_tile_height
argument_list|()
decl_stmt|;
name|gint32
name|image_id
init|=
name|data
operator|->
name|image_id
decl_stmt|;
name|gint32
name|drawable_id
init|=
name|data
operator|->
name|drawable_id
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPixelRgn
name|region
decl_stmt|;
name|cairo_t
modifier|*
name|cr
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
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|gdouble
name|x0
init|=
literal|0
decl_stmt|;
name|gdouble
name|y0
init|=
literal|0
decl_stmt|;
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
comment|/* export the image */
name|gimp_export_image
argument_list|(
operator|&
name|image_id
argument_list|,
operator|&
name|drawable_id
argument_list|,
name|NULL
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator||
name|GIMP_EXPORT_NEEDS_ALPHA
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|width
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
name|rowstride
operator|=
name|drawable
operator|->
name|bpp
operator|*
name|width
expr_stmt|;
name|cr
operator|=
name|gtk_print_context_get_cairo_context
argument_list|(
name|context
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
name|scale_x
operator|=
name|cr_dpi_x
operator|/
name|data
operator|->
name|xres
expr_stmt|;
name|scale_y
operator|=
name|cr_dpi_y
operator|/
name|data
operator|->
name|yres
expr_stmt|;
if|if
condition|(
name|scale_x
operator|*
name|width
operator|>
name|cr_width
operator|+
name|EPSILON
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Image width (%lg in) is larger than printable width (%lg in)."
argument_list|)
argument_list|,
name|width
operator|/
name|data
operator|->
name|xres
argument_list|,
name|cr_width
operator|/
name|cr_dpi_x
argument_list|)
expr_stmt|;
name|gtk_print_operation_cancel
argument_list|(
name|data
operator|->
name|operation
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|scale_y
operator|*
name|height
operator|>
name|cr_height
operator|+
name|EPSILON
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Image height (%lg in) is larger than printable height (%lg in)."
argument_list|)
argument_list|,
name|height
operator|/
name|data
operator|->
name|yres
argument_list|,
name|cr_height
operator|/
name|cr_dpi_y
argument_list|)
expr_stmt|;
name|gtk_print_operation_cancel
argument_list|(
name|data
operator|->
name|operation
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
comment|/* print header if it is requested */
if|if
condition|(
name|data
operator|->
name|show_info_header
condition|)
block|{
name|draw_info_header
argument_list|(
name|context
argument_list|,
name|cr
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
name|HEADER_HEIGHT
argument_list|)
expr_stmt|;
name|cr_height
operator|-=
name|HEADER_HEIGHT
expr_stmt|;
block|}
name|x0
operator|=
operator|(
name|cr_width
operator|-
name|scale_x
operator|*
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|y0
operator|=
operator|(
name|cr_height
operator|-
name|scale_y
operator|*
name|height
operator|)
operator|/
literal|2
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|x0
argument_list|,
name|y0
argument_list|)
expr_stmt|;
name|cairo_scale
argument_list|(
name|cr
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|1
operator|+
name|width
operator|/
name|gimp_tile_width
argument_list|()
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
name|pixels
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|MIN
argument_list|(
name|height
argument_list|,
name|tile_height
argument_list|)
operator|*
name|rowstride
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|+=
name|tile_height
control|)
block|{
name|gint
name|h
init|=
name|MIN
argument_list|(
name|tile_height
argument_list|,
name|height
operator|-
name|y
argument_list|)
decl_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|region
argument_list|,
name|pixels
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|surface
operator|=
name|create_surface
argument_list|(
name|pixels
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|h
argument_list|,
name|rowstride
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
name|y
argument_list|)
expr_stmt|;
name|cairo_mask_surface
argument_list|(
name|cr
argument_list|,
name|surface
argument_list|,
literal|0
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|y
operator|+
name|h
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_id
operator|!=
name|data
operator|->
name|image_id
condition|)
name|gimp_image_delete
argument_list|(
name|image_id
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
DECL|function|create_surface (guchar * pixels,gint x,gint y,gint width,gint height,gint rowstride)
name|create_surface
parameter_list|(
name|guchar
modifier|*
name|pixels
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
name|rowstride
parameter_list|)
block|{
name|guint32
modifier|*
name|cairo_data
init|=
operator|(
name|guint32
operator|*
operator|)
name|pixels
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
name|gint
name|len
decl_stmt|;
name|gint
name|i
decl_stmt|;
comment|/* knock pixels into the shape requested by cairo:    *    *  CAIRO_FORMAT_ARGB32:    *  each pixel is a 32-bit quantity, with alpha in the upper 8 bits,    *  then red, then green, then blue. The 32-bit quantities are    *  stored native-endian. Pre-multiplied alpha is used.    *    */
name|len
operator|=
name|width
operator|*
name|height
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|p
operator|=
name|pixels
init|;
name|i
operator|<
name|len
condition|;
name|i
operator|++
control|)
block|{
name|guint32
name|r
init|=
operator|*
name|p
operator|++
decl_stmt|;
name|guint32
name|g
init|=
operator|*
name|p
operator|++
decl_stmt|;
name|guint32
name|b
init|=
operator|*
name|p
operator|++
decl_stmt|;
name|guint32
name|a
init|=
operator|*
name|p
operator|++
decl_stmt|;
if|if
condition|(
name|a
operator|!=
literal|255
condition|)
block|{
name|gdouble
name|alpha
init|=
name|a
operator|/
literal|255.0
decl_stmt|;
name|r
operator|*=
name|alpha
expr_stmt|;
name|g
operator|*=
name|alpha
expr_stmt|;
name|b
operator|*=
name|alpha
expr_stmt|;
block|}
name|cairo_data
index|[
name|i
index|]
operator|=
operator|(
name|a
operator|<<
literal|24
operator|)
operator|+
operator|(
name|r
operator|<<
literal|16
operator|)
operator|+
operator|(
name|g
operator|<<
literal|8
operator|)
operator|+
name|b
expr_stmt|;
block|}
return|return
name|cairo_image_surface_create_for_data
argument_list|(
name|pixels
argument_list|,
name|CAIRO_FORMAT_ARGB32
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|rowstride
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_info_header (GtkPrintContext * context,cairo_t * cr,PrintData * data)
name|draw_info_header
parameter_list|(
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|PangoLayout
modifier|*
name|layout
decl_stmt|;
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|gdouble
name|text_height
decl_stmt|;
name|gdouble
name|text_width
decl_stmt|;
name|gdouble
name|fname_text_width
decl_stmt|;
name|gint
name|layout_height
decl_stmt|;
name|gint
name|layout_width
decl_stmt|;
name|gchar
name|date_buffer
index|[
literal|100
index|]
decl_stmt|;
name|GDate
modifier|*
name|date
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name_str
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|end_ptr
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gdouble
name|cr_width
decl_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cr_width
operator|=
name|gtk_print_context_get_width
argument_list|(
name|context
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
name|cr_width
argument_list|,
name|HEADER_HEIGHT
argument_list|)
expr_stmt|;
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|0.8
argument_list|,
literal|0.8
argument_list|,
literal|0.8
argument_list|)
expr_stmt|;
name|cairo_fill_preserve
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|cairo_set_line_width
argument_list|(
name|cr
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cairo_stroke
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|layout
operator|=
name|gtk_print_context_create_pango_layout
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|desc
operator|=
name|pango_font_description_from_string
argument_list|(
literal|"sans 14"
argument_list|)
expr_stmt|;
name|pango_layout_set_font_description
argument_list|(
name|layout
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|pango_layout_set_width
argument_list|(
name|layout
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_set_alignment
argument_list|(
name|layout
argument_list|,
name|PANGO_ALIGN_CENTER
argument_list|)
expr_stmt|;
comment|/* image name */
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|gimp_image_get_name
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|layout_width
argument_list|,
operator|&
name|layout_height
argument_list|)
expr_stmt|;
name|text_height
operator|=
operator|(
name|gdouble
operator|)
name|layout_height
operator|/
name|PANGO_SCALE
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
literal|0.02
operator|*
name|cr_width
argument_list|,
operator|(
name|HEADER_HEIGHT
operator|-
name|text_height
operator|)
operator|/
literal|5
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|layout
argument_list|)
expr_stmt|;
comment|/* user name */
name|name_str
operator|=
name|g_get_real_name
argument_list|()
expr_stmt|;
if|if
condition|(
name|name_str
operator|&&
name|g_utf8_validate
argument_list|(
name|name_str
argument_list|,
operator|-
literal|1
argument_list|,
operator|&
name|end_ptr
argument_list|)
condition|)
block|{
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|name_str
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|layout_width
argument_list|,
operator|&
name|layout_height
argument_list|)
expr_stmt|;
name|text_height
operator|=
operator|(
name|gdouble
operator|)
name|layout_height
operator|/
name|PANGO_SCALE
expr_stmt|;
name|text_width
operator|=
operator|(
name|gdouble
operator|)
name|layout_width
operator|/
name|PANGO_SCALE
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
literal|0.5
operator|*
name|cr_width
operator|-
literal|0.5
operator|*
name|text_width
argument_list|,
operator|(
name|HEADER_HEIGHT
operator|-
name|text_height
operator|)
operator|/
literal|5
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|layout
argument_list|)
expr_stmt|;
block|}
comment|/* date */
name|date
operator|=
name|g_date_new
argument_list|()
expr_stmt|;
name|g_date_set_time_t
argument_list|(
name|date
argument_list|,
name|time
argument_list|(
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_date_strftime
argument_list|(
name|date_buffer
argument_list|,
literal|100
argument_list|,
literal|"%x"
argument_list|,
name|date
argument_list|)
expr_stmt|;
name|g_date_free
argument_list|(
name|date
argument_list|)
expr_stmt|;
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|date_buffer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|layout_width
argument_list|,
operator|&
name|layout_height
argument_list|)
expr_stmt|;
name|text_height
operator|=
operator|(
name|gdouble
operator|)
name|layout_height
operator|/
name|PANGO_SCALE
expr_stmt|;
name|text_width
operator|=
operator|(
name|gdouble
operator|)
name|layout_width
operator|/
name|PANGO_SCALE
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
literal|0.98
operator|*
name|cr_width
operator|-
name|text_width
argument_list|,
operator|(
name|HEADER_HEIGHT
operator|-
name|text_height
operator|)
operator|/
literal|5
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|layout
argument_list|)
expr_stmt|;
comment|/* file name if any */
name|filename
operator|=
name|gimp_image_get_filename
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|pango_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|layout_width
argument_list|,
operator|&
name|layout_height
argument_list|)
expr_stmt|;
name|text_height
operator|=
operator|(
name|gdouble
operator|)
name|layout_height
operator|/
name|PANGO_SCALE
expr_stmt|;
name|fname_text_width
operator|=
operator|(
name|gdouble
operator|)
name|layout_width
operator|/
name|PANGO_SCALE
expr_stmt|;
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
literal|0.02
operator|*
name|cr_width
argument_list|,
literal|4
operator|*
operator|(
name|HEADER_HEIGHT
operator|-
name|text_height
operator|)
operator|/
literal|5
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|layout
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|fname_text_width
operator|=
literal|0
expr_stmt|;
block|}
comment|/* image comment if it is short */
name|parasite
operator|=
name|gimp_image_parasite_find
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
literal|"gimp-comment"
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
condition|)
block|{
name|pango_layout_set_text
argument_list|(
name|layout
argument_list|,
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_size
argument_list|(
name|layout
argument_list|,
operator|&
name|layout_width
argument_list|,
operator|&
name|layout_height
argument_list|)
expr_stmt|;
name|text_height
operator|=
operator|(
name|gdouble
operator|)
name|layout_height
operator|/
name|PANGO_SCALE
expr_stmt|;
name|text_width
operator|=
operator|(
name|gdouble
operator|)
name|layout_width
operator|/
name|PANGO_SCALE
expr_stmt|;
if|if
condition|(
name|fname_text_width
operator|+
name|text_width
operator|<
literal|0.8
operator|*
name|cr_width
operator|&&
name|text_height
operator|<
literal|0.5
operator|*
name|HEADER_HEIGHT
condition|)
block|{
name|cairo_move_to
argument_list|(
name|cr
argument_list|,
literal|0.98
operator|*
name|cr_width
operator|-
name|text_width
argument_list|,
literal|4
operator|*
operator|(
name|HEADER_HEIGHT
operator|-
name|text_height
operator|)
operator|/
literal|5
argument_list|)
expr_stmt|;
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|layout
argument_list|)
expr_stmt|;
block|}
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

