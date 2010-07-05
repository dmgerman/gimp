begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcairo-utils.c  * Copyright (C) 2007 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
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
file|"gimpcairo-utils.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcairo-utils  * @title: GimpCairo-utils  * @short_description: Utility functions for cairo  *  * Utility functions that make cairo easier to use with common  * GIMP data types.  **/
end_comment

begin_comment
comment|/**  * gimp_cairo_set_source_rgb:  * @cr:    Cairo context  * @color: GimpRGB color  *  * Sets the source pattern within @cr to the solid opaque color  * described by @color.  *  * This function calls cairo_set_source_rgb() for you.  *  * Since: GIMP 2.6  **/
end_comment

begin_function
name|void
DECL|function|gimp_cairo_set_source_rgb (cairo_t * cr,const GimpRGB * color)
name|gimp_cairo_set_source_rgb
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|color
operator|->
name|r
argument_list|,
name|color
operator|->
name|g
argument_list|,
name|color
operator|->
name|b
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_cairo_set_source_rgba:  * @cr:    Cairo context  * @color: GimpRGB color  *  * Sets the source pattern within @cr to the solid translucent color  * described by @color.  *  * This function calls cairo_set_source_rgba() for you.  *  * Since: GIMP 2.6  **/
end_comment

begin_function
name|void
DECL|function|gimp_cairo_set_source_rgba (cairo_t * cr,const GimpRGB * color)
name|gimp_cairo_set_source_rgba
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|cairo_set_source_rgba
argument_list|(
name|cr
argument_list|,
name|color
operator|->
name|r
argument_list|,
name|color
operator|->
name|g
argument_list|,
name|color
operator|->
name|b
argument_list|,
name|color
operator|->
name|a
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_cairo_set_focus_line_pattern:  * @cr:     Cairo context  * @widget: widget to draw the focus indicator on  *  * Sets color and dash pattern for stroking a focus line on the given  * @cr. The line pattern is taken from @widget.  *  * Return value: %TRUE if the widget style has a focus line pattern,  *               %FALSE otherwise  *  * Since: GIMP 2.6  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_cairo_set_focus_line_pattern (cairo_t * cr,GtkWidget * widget)
name|gimp_cairo_set_focus_line_pattern
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|gint8
modifier|*
name|dash_list
decl_stmt|;
name|gboolean
name|retval
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cr
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"focus-line-pattern"
argument_list|,
operator|(
name|gchar
operator|*
operator|)
operator|&
name|dash_list
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dash_list
index|[
literal|0
index|]
condition|)
block|{
comment|/* Taken straight from gtk_default_draw_focus()        */
name|gint
name|n_dashes
init|=
name|strlen
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|dash_list
argument_list|)
decl_stmt|;
name|gdouble
modifier|*
name|dashes
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|n_dashes
argument_list|)
decl_stmt|;
name|gdouble
name|total_length
init|=
literal|0
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
name|n_dashes
condition|;
name|i
operator|++
control|)
block|{
name|dashes
index|[
name|i
index|]
operator|=
name|dash_list
index|[
name|i
index|]
expr_stmt|;
name|total_length
operator|+=
name|dash_list
index|[
name|i
index|]
expr_stmt|;
block|}
name|cairo_set_dash
argument_list|(
name|cr
argument_list|,
name|dashes
argument_list|,
name|n_dashes
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dashes
argument_list|)
expr_stmt|;
name|retval
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dash_list
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_cairo_checkerboard_create:  * @cr:    Cairo context  * @size:  check size  * @light: light check color or %NULL to use the default light gray  * @dark:  dark check color or %NULL to use the default dark gray  *  * Create a repeating checkerboard pattern.  *  * Return value: a new Cairo pattern that can be used as a source on @cr.  *  * Since: GIMP 2.6  **/
end_comment

begin_function
name|cairo_pattern_t
modifier|*
DECL|function|gimp_cairo_checkerboard_create (cairo_t * cr,gint size,const GimpRGB * light,const GimpRGB * dark)
name|gimp_cairo_checkerboard_create
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|gint
name|size
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|light
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|dark
parameter_list|)
block|{
name|cairo_t
modifier|*
name|context
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|cairo_pattern_t
modifier|*
name|pattern
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cr
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|surface
operator|=
name|cairo_surface_create_similar
argument_list|(
name|cairo_get_target
argument_list|(
name|cr
argument_list|)
argument_list|,
name|CAIRO_CONTENT_COLOR
argument_list|,
literal|2
operator|*
name|size
argument_list|,
literal|2
operator|*
name|size
argument_list|)
expr_stmt|;
name|context
operator|=
name|cairo_create
argument_list|(
name|surface
argument_list|)
expr_stmt|;
if|if
condition|(
name|light
condition|)
name|gimp_cairo_set_source_rgb
argument_list|(
name|context
argument_list|,
name|light
argument_list|)
expr_stmt|;
else|else
name|cairo_set_source_rgb
argument_list|(
name|context
argument_list|,
name|GIMP_CHECK_LIGHT
argument_list|,
name|GIMP_CHECK_LIGHT
argument_list|,
name|GIMP_CHECK_LIGHT
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|size
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|context
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|dark
condition|)
name|gimp_cairo_set_source_rgb
argument_list|(
name|context
argument_list|,
name|dark
argument_list|)
expr_stmt|;
else|else
name|cairo_set_source_rgb
argument_list|(
name|context
argument_list|,
name|GIMP_CHECK_DARK
argument_list|,
name|GIMP_CHECK_DARK
argument_list|,
name|GIMP_CHECK_DARK
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
name|size
argument_list|,
name|size
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|context
argument_list|,
name|size
argument_list|,
literal|0
argument_list|,
name|size
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|pattern
operator|=
name|cairo_pattern_create_for_surface
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|cairo_pattern_set_extend
argument_list|(
name|pattern
argument_list|,
name|CAIRO_EXTEND_REPEAT
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
return|return
name|pattern
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_cairo_surface_create_from_pixbuf:  * @pixbuf: a GdkPixbuf  *  * Create a Cairo image surface from a GdkPixbuf.  *  * You should avoid calling this function as there are probably more  * efficient ways of achieving the result you are looking for.  *  * Since: GIMP 2.6  **/
end_comment

begin_function
name|cairo_surface_t
modifier|*
DECL|function|gimp_cairo_surface_create_from_pixbuf (GdkPixbuf * pixbuf)
name|gimp_cairo_surface_create_from_pixbuf
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
block|{
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|cairo_format_t
name|format
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|src_stride
decl_stmt|;
name|gint
name|dest_stride
decl_stmt|;
name|gint
name|y
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
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
condition|)
block|{
case|case
literal|3
case|:
name|format
operator|=
name|CAIRO_FORMAT_RGB24
expr_stmt|;
break|break;
case|case
literal|4
case|:
name|format
operator|=
name|CAIRO_FORMAT_ARGB32
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
name|surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|format
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|cairo_surface_flush
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|src
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|src_stride
operator|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|dest
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|dest_stride
operator|=
name|cairo_image_surface_get_stride
argument_list|(
name|surface
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|format
condition|)
block|{
case|case
name|CAIRO_FORMAT_RGB24
case|:
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
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gint
name|w
init|=
name|width
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|GIMP_CAIRO_RGB24_SET_PIXEL
argument_list|(
name|d
argument_list|,
name|s
index|[
literal|0
index|]
argument_list|,
name|s
index|[
literal|1
index|]
argument_list|,
name|s
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|s
operator|+=
literal|3
expr_stmt|;
name|d
operator|+=
literal|4
expr_stmt|;
block|}
name|src
operator|+=
name|src_stride
expr_stmt|;
name|dest
operator|+=
name|dest_stride
expr_stmt|;
block|}
break|break;
case|case
name|CAIRO_FORMAT_ARGB32
case|:
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
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
name|gint
name|w
init|=
name|width
decl_stmt|;
while|while
condition|(
name|w
operator|--
condition|)
block|{
name|GIMP_CAIRO_ARGB32_SET_PIXEL
argument_list|(
name|d
argument_list|,
name|s
index|[
literal|0
index|]
argument_list|,
name|s
index|[
literal|1
index|]
argument_list|,
name|s
index|[
literal|2
index|]
argument_list|,
name|s
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|s
operator|+=
literal|4
expr_stmt|;
name|d
operator|+=
literal|4
expr_stmt|;
block|}
name|src
operator|+=
name|src_stride
expr_stmt|;
name|dest
operator|+=
name|dest_stride
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
name|cairo_surface_mark_dirty
argument_list|(
name|surface
argument_list|)
expr_stmt|;
return|return
name|surface
return|;
block|}
end_function

end_unit

