begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************************************/
end_comment

begin_comment
comment|/* GCK - The General Convenience Kit. Generally useful conveniece routines */
end_comment

begin_comment
comment|/* for GIMP plug-in writers and users of the GDK/GTK libraries.            */
end_comment

begin_comment
comment|/* Copyright (C) 1996 Tom Bech                                             */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is free software; you can redistribute it and/or modify    */
end_comment

begin_comment
comment|/* it under the terms of the GNU General Public License as published by    */
end_comment

begin_comment
comment|/* the Free Software Foundation; either version 2 of the License, or       */
end_comment

begin_comment
comment|/* (at your option) any later version.                                     */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is distributed in the hope that it will be useful,         */
end_comment

begin_comment
comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
end_comment

begin_comment
comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
end_comment

begin_comment
comment|/* GNU General Public License for more details.                            */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* You should have received a copy of the GNU General Public License       */
end_comment

begin_comment
comment|/* along with this program; if not, write to the Free Software             */
end_comment

begin_comment
comment|/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,   */
end_comment

begin_comment
comment|/* USA.                                                                    */
end_comment

begin_comment
comment|/***************************************************************************/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GCK_H__
end_ifndef

begin_define
DECL|macro|__GCK_H__
define|#
directive|define
name|__GCK_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
DECL|macro|GCK_CONSTRAIN_RGB
define|#
directive|define
name|GCK_CONSTRAIN_RGB
value|1<<0
DECL|macro|GCK_CONSTRAIN_RGBA
define|#
directive|define
name|GCK_CONSTRAIN_RGBA
value|1<<1
DECL|macro|GCK_CONSTRAIN_GRAY
define|#
directive|define
name|GCK_CONSTRAIN_GRAY
value|1<<2
DECL|macro|GCK_CONSTRAIN_GRAYA
define|#
directive|define
name|GCK_CONSTRAIN_GRAYA
value|1<<3
DECL|macro|GCK_CONSTRAIN_INDEXED
define|#
directive|define
name|GCK_CONSTRAIN_INDEXED
value|1<<4
DECL|macro|GCK_CONSTRAIN_INDEXEDA
define|#
directive|define
name|GCK_CONSTRAIN_INDEXEDA
value|1<<5
DECL|macro|GCK_CONSTRAIN_ALL
define|#
directive|define
name|GCK_CONSTRAIN_ALL
value|0xff
DECL|macro|GCK_HSV_UNDEFINED
define|#
directive|define
name|GCK_HSV_UNDEFINED
value|-1.0
DECL|macro|GCK_HSL_UNDEFINED
define|#
directive|define
name|GCK_HSL_UNDEFINED
value|-1.0
typedef|typedef
enum|enum
DECL|enum|__anon2bc9caab0103
block|{
DECL|enumerator|DITHER_NONE
name|DITHER_NONE
block|,
DECL|enumerator|DITHER_FLOYD_STEINBERG
name|DITHER_FLOYD_STEINBERG
block|,
DECL|enumerator|DITHER_ORDERED
name|DITHER_ORDERED
DECL|typedef|GckDitherType
block|}
name|GckDitherType
typedef|;
typedef|typedef
struct|struct
DECL|struct|__anon2bc9caab0208
block|{
DECL|member|r
DECL|member|g
DECL|member|b
DECL|member|a
name|gdouble
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
DECL|typedef|GckRGB
block|}
name|GckRGB
typedef|;
typedef|typedef
struct|struct
DECL|struct|__anon2bc9caab0308
block|{
DECL|member|r
DECL|member|g
DECL|member|b
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|typedef|GckNamedRGB
block|}
name|GckNamedRGB
typedef|;
typedef|typedef
struct|struct
DECL|struct|__anon2bc9caab0408
block|{
DECL|member|visual
name|GdkVisual
modifier|*
name|visual
decl_stmt|;
DECL|member|colormap
name|GdkColormap
modifier|*
name|colormap
decl_stmt|;
DECL|member|allocedpixels
name|gulong
name|allocedpixels
index|[
literal|256
index|]
decl_stmt|;
DECL|member|colorcube
name|guint32
name|colorcube
index|[
literal|256
index|]
decl_stmt|;
DECL|member|rgbpalette
name|GdkColor
name|rgbpalette
index|[
literal|256
index|]
decl_stmt|;
DECL|member|map_r
DECL|member|map_g
DECL|member|map_b
name|guchar
name|map_r
index|[
literal|256
index|]
decl_stmt|,
name|map_g
index|[
literal|256
index|]
decl_stmt|,
name|map_b
index|[
literal|256
index|]
decl_stmt|;
DECL|member|indextab
name|guchar
name|indextab
index|[
literal|7
index|]
index|[
literal|7
index|]
index|[
literal|7
index|]
decl_stmt|;
DECL|member|invmap_r
DECL|member|invmap_g
DECL|member|invmap_b
name|guchar
name|invmap_r
index|[
literal|256
index|]
decl_stmt|,
name|invmap_g
index|[
literal|256
index|]
decl_stmt|,
name|invmap_b
index|[
literal|256
index|]
decl_stmt|;
DECL|member|shades_r
DECL|member|shades_g
DECL|member|shades_b
DECL|member|numcolors
name|gint
name|shades_r
decl_stmt|,
name|shades_g
decl_stmt|,
name|shades_b
decl_stmt|,
name|numcolors
decl_stmt|;
DECL|member|dithermethod
name|GckDitherType
name|dithermethod
decl_stmt|;
DECL|typedef|GckVisualInfo
block|}
name|GckVisualInfo
typedef|;
DECL|typedef|GckRenderFunction
typedef|typedef
name|void
function_decl|(
modifier|*
name|GckRenderFunction
function_decl|)
parameter_list|(
name|gdouble
parameter_list|,
name|gdouble
parameter_list|,
name|GckRGB
modifier|*
parameter_list|)
function_decl|;
DECL|typedef|GckPutPixelFunction
typedef|typedef
name|void
function_decl|(
modifier|*
name|GckPutPixelFunction
function_decl|)
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|,
name|GckRGB
modifier|*
parameter_list|)
function_decl|;
DECL|typedef|GckProgressFunction
typedef|typedef
name|void
function_decl|(
modifier|*
name|GckProgressFunction
function_decl|)
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|)
function_decl|;
DECL|typedef|GckColorUpdateFunction
typedef|typedef
name|void
function_decl|(
modifier|*
name|GckColorUpdateFunction
function_decl|)
parameter_list|(
name|GckRGB
modifier|*
parameter_list|)
function_decl|;
DECL|typedef|GckEventFunction
typedef|typedef
name|gint
function_decl|(
modifier|*
name|GckEventFunction
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
typedef|typedef
struct|struct
DECL|struct|__anon2bc9caab0508
block|{
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|visinfo
name|GckVisualInfo
modifier|*
name|visinfo
decl_stmt|;
DECL|typedef|GckApplicationWindow
block|}
name|GckApplicationWindow
typedef|;
typedef|typedef
struct|struct
DECL|struct|__anon2bc9caab0608
block|{
DECL|member|x
DECL|member|y
DECL|member|w
DECL|member|h
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
DECL|member|buffer
name|GdkImage
modifier|*
name|buffer
decl_stmt|;
DECL|typedef|_GckBackBuffer
block|}
name|_GckBackBuffer
typedef|;
name|GckVisualInfo
modifier|*
name|gck_visualinfo_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|void
name|gck_visualinfo_destroy
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|)
function_decl|;
name|GckDitherType
name|gck_visualinfo_get_dither
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|)
function_decl|;
name|void
name|gck_visualinfo_set_dither
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|,
name|GckDitherType
name|dithermethod
parameter_list|)
function_decl|;
comment|/* RGB to Gdk routines */
comment|/* =================== */
name|void
name|gck_rgb_to_gdkimage
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|,
name|guchar
modifier|*
name|RGB_data
parameter_list|,
name|GdkImage
modifier|*
name|image
parameter_list|,
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|)
function_decl|;
comment|/* returns a static storage */
name|GdkColor
modifier|*
name|gck_rgb_to_gdkcolor
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
function_decl|;
comment|/* returns a malloc'ed area */
name|GdkColor
modifier|*
name|gck_rgb_to_gdkcolor_r
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
function_decl|;
name|void
name|gck_gc_set_foreground
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
function_decl|;
name|void
name|gck_gc_set_background
parameter_list|(
name|GckVisualInfo
modifier|*
name|visinfo
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
function_decl|;
comment|/********************/
comment|/* Color operations */
comment|/********************/
name|double
name|gck_bilinear
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|double
modifier|*
name|values
parameter_list|)
function_decl|;
name|guchar
name|gck_bilinear_8
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|guchar
modifier|*
name|values
parameter_list|)
function_decl|;
name|guint16
name|gck_bilinear_16
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|guint16
modifier|*
name|values
parameter_list|)
function_decl|;
name|guint32
name|gck_bilinear_32
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|guint32
modifier|*
name|values
parameter_list|)
function_decl|;
name|GckRGB
name|gck_bilinear_rgb
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|GckRGB
modifier|*
name|values
parameter_list|)
function_decl|;
name|GckRGB
name|gck_bilinear_rgba
parameter_list|(
name|double
name|x
parameter_list|,
name|double
name|y
parameter_list|,
name|GckRGB
modifier|*
name|values
parameter_list|)
function_decl|;
comment|/* RGB pixel operations */
comment|/* ==================== */
name|void
name|gck_rgb_add
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|GckRGB
modifier|*
name|q
parameter_list|)
function_decl|;
name|void
name|gck_rgb_sub
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|GckRGB
modifier|*
name|q
parameter_list|)
function_decl|;
name|void
name|gck_rgb_mul
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
name|b
parameter_list|)
function_decl|;
name|void
name|gck_rgb_clamp
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|)
function_decl|;
name|void
name|gck_rgb_set
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
name|r
parameter_list|,
name|double
name|g
parameter_list|,
name|double
name|b
parameter_list|)
function_decl|;
name|void
name|gck_rgb_gamma
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
name|gamma
parameter_list|)
function_decl|;
name|void
name|gck_rgba_add
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|GckRGB
modifier|*
name|q
parameter_list|)
function_decl|;
name|void
name|gck_rgba_sub
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|GckRGB
modifier|*
name|q
parameter_list|)
function_decl|;
name|void
name|gck_rgba_mul
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
name|b
parameter_list|)
function_decl|;
name|void
name|gck_rgba_clamp
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|)
function_decl|;
name|void
name|gck_rgba_set
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
name|r
parameter_list|,
name|double
name|g
parameter_list|,
name|double
name|b
parameter_list|,
name|double
name|a
parameter_list|)
function_decl|;
name|void
name|gck_rgba_gamma
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
name|gamma
parameter_list|)
function_decl|;
comment|/* Colorspace conversions */
comment|/* ====================== */
name|void
name|gck_rgb_to_hsv
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
modifier|*
name|h
parameter_list|,
name|double
modifier|*
name|s
parameter_list|,
name|double
modifier|*
name|v
parameter_list|)
function_decl|;
name|void
name|gck_rgb_to_hsl
parameter_list|(
name|GckRGB
modifier|*
name|p
parameter_list|,
name|double
modifier|*
name|h
parameter_list|,
name|double
modifier|*
name|s
parameter_list|,
name|double
modifier|*
name|l
parameter_list|)
function_decl|;
name|void
name|gck_hsv_to_rgb
parameter_list|(
name|double
name|h
parameter_list|,
name|double
name|s
parameter_list|,
name|double
name|v
parameter_list|,
name|GckRGB
modifier|*
name|p
parameter_list|)
function_decl|;
name|void
name|gck_hsl_to_rgb
parameter_list|(
name|double
name|h
parameter_list|,
name|double
name|s
parameter_list|,
name|double
name|l
parameter_list|,
name|GckRGB
modifier|*
name|p
parameter_list|)
function_decl|;
name|void
name|gck_rgb_to_hwb
parameter_list|(
name|GckRGB
modifier|*
name|rgb
parameter_list|,
name|gdouble
modifier|*
name|hue
parameter_list|,
name|gdouble
modifier|*
name|whiteness
parameter_list|,
name|gdouble
modifier|*
name|blackness
parameter_list|)
function_decl|;
name|void
name|gck_hwb_to_rgb
parameter_list|(
name|gdouble
name|H
parameter_list|,
name|gdouble
name|W
parameter_list|,
name|gdouble
name|B
parameter_list|,
name|GckRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
comment|/* Supersampling */
comment|/* ============= */
name|gulong
name|gck_adaptive_supersample_area
parameter_list|(
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x2
parameter_list|,
name|int
name|y2
parameter_list|,
name|int
name|max_depth
parameter_list|,
name|double
name|threshold
parameter_list|,
name|GckRenderFunction
name|render_func
parameter_list|,
name|GckPutPixelFunction
name|put_pixel_func
parameter_list|,
name|GckProgressFunction
name|progress_func
parameter_list|)
function_decl|;
specifier|extern
name|GckNamedRGB
name|gck_named_colors
index|[]
decl_stmt|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GCK_H__ */
end_comment

end_unit

