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
typedef|typedef
enum|enum
DECL|enum|__anon2b3a675f0103
block|{
DECL|enumerator|DITHER_NONE
name|DITHER_NONE
block|,
DECL|enumerator|DITHER_FLOYD_STEINBERG
name|DITHER_FLOYD_STEINBERG
DECL|typedef|GckDitherType
block|}
name|GckDitherType
typedef|;
typedef|typedef
struct|struct
DECL|struct|__anon2b3a675f0208
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

