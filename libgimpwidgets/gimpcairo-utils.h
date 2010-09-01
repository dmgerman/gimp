begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcairo-utils.h  * Copyright (C) 2007 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CAIRO_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CAIRO_UTILS_H__
define|#
directive|define
name|__GIMP_CAIRO_UTILS_H__
end_define

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_comment
comment|/*  This is a bad hack that allows to include this file from the app's  *  non-gui files. I haven't decided yet how to split this header and  *  where to move the non-GTK+ part. --Mitch  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|__GTK_H__
end_ifdef

begin_function_decl
name|gboolean
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|cairo_pattern_t
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
name|cairo_surface_t
modifier|*
name|gimp_cairo_surface_create_from_pixbuf
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  some useful macros for writing directly to a Cairo surface  */
end_comment

begin_comment
comment|/**  * GIMP_CAIRO_RGB24_SET_PIXEL:  * @d: pointer to the destination buffer  * @r: red component  * @g: green component  * @b: blue component  *  * Sets a single pixel in an Cairo image surface in %CAIRO_FORMAT_RGB24.  *  * Since: GIMP 2.6  **/
end_comment

begin_if
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
end_if

begin_define
DECL|macro|GIMP_CAIRO_RGB24_SET_PIXEL (d,r,g,b)
define|#
directive|define
name|GIMP_CAIRO_RGB24_SET_PIXEL
parameter_list|(
name|d
parameter_list|,
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
define|\
value|G_STMT_START { d[0] = (b);  d[1] = (g);  d[2] = (r); } G_STMT_END
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|GIMP_CAIRO_RGB24_SET_PIXEL (d,r,g,b)
define|#
directive|define
name|GIMP_CAIRO_RGB24_SET_PIXEL
parameter_list|(
name|d
parameter_list|,
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
define|\
value|G_STMT_START { d[1] = (r);  d[2] = (g);  d[3] = (b); } G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/**  * GIMP_CAIRO_RGB24_GET_PIXEL:  * @s: pointer to the source buffer  * @r: red component  * @g: green component  * @b: blue component  *  * Gets a single pixel from a Cairo image surface in %CAIRO_FORMAT_RGB24.  *  * Since: GIMP 2.8  **/
end_comment

begin_if
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
end_if

begin_define
DECL|macro|GIMP_CAIRO_RGB24_GET_PIXEL (s,r,g,b)
define|#
directive|define
name|GIMP_CAIRO_RGB24_GET_PIXEL
parameter_list|(
name|s
parameter_list|,
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
define|\
value|G_STMT_START { (b) = s[0]; (g) = s[1]; (r) = s[2]; } G_STMT_END
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|GIMP_CAIRO_RGB24_GET_PIXEL (s,r,g,b)
define|#
directive|define
name|GIMP_CAIRO_RGB24_GET_PIXEL
parameter_list|(
name|s
parameter_list|,
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
define|\
value|G_STMT_START { (r) = s[1]; (g) = s[2]; (b) = s[3]; } G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/**  * GIMP_CAIRO_ARGB32_SET_PIXEL:  * @d: pointer to the destination buffer  * @r: red component, not pre-multiplied  * @g: green component, not pre-multiplied  * @b: blue component, not pre-multiplied  * @a: alpha component  *  * Sets a single pixel in an Cairo image surface in %CAIRO_FORMAT_ARGB32.  *  * Since: GIMP 2.6  **/
end_comment

begin_if
if|#
directive|if
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
end_if

begin_define
DECL|macro|GIMP_CAIRO_ARGB32_SET_PIXEL (d,r,g,b,a)
define|#
directive|define
name|GIMP_CAIRO_ARGB32_SET_PIXEL
parameter_list|(
name|d
parameter_list|,
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|,
name|a
parameter_list|)
define|\
value|G_STMT_START {                                   \     guint tr = (a) * (r) + 0x80;                   \     guint tg = (a) * (g) + 0x80;                   \     guint tb = (a) * (b) + 0x80;                   \     d[0] = (((tb)>> 8) + (tb))>> 8;              \     d[1] = (((tg)>> 8) + (tg))>> 8;              \     d[2] = (((tr)>> 8) + (tr))>> 8;              \     d[3] = (a);                                    \   } G_STMT_END
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|GIMP_CAIRO_ARGB32_SET_PIXEL (d,r,g,b,a)
define|#
directive|define
name|GIMP_CAIRO_ARGB32_SET_PIXEL
parameter_list|(
name|d
parameter_list|,
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|,
name|a
parameter_list|)
define|\
value|G_STMT_START {                                   \     guint tr = (a) * (r) + 0x80;                   \     guint tg = (a) * (g) + 0x80;                   \     guint tb = (a) * (b) + 0x80;                   \     d[0] = (a);                                    \     d[1] = (((tr)>> 8) + (tr))>> 8;              \     d[2] = (((tg)>> 8) + (tg))>> 8;              \     d[3] = (((tb)>> 8) + (tb))>> 8;              \   } G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CAIRO_UTILS_H__ */
end_comment

end_unit

