begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmisc.h  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk   *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MISC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MISC_H__
define|#
directive|define
name|__GIMP_MISC_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28c95db00108
block|{
DECL|member|col
DECL|member|row
name|gint
name|col
decl_stmt|,
name|row
decl_stmt|;
DECL|member|img_width
name|gint
name|img_width
decl_stmt|;
DECL|member|img_height
name|gint
name|img_height
decl_stmt|;
DECL|member|sel_x1
DECL|member|sel_y1
DECL|member|sel_x2
DECL|member|sel_y2
name|gint
name|sel_x1
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y2
decl_stmt|;
DECL|member|img_bpp
name|gint
name|img_bpp
decl_stmt|;
DECL|member|img_has_alpha
name|gint
name|img_has_alpha
decl_stmt|;
DECL|member|tile_width
DECL|member|tile_height
name|gint
name|tile_width
decl_stmt|,
name|tile_height
decl_stmt|;
DECL|member|bg_color
name|guchar
name|bg_color
index|[
literal|4
index|]
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|tile
name|GimpTile
modifier|*
name|tile
decl_stmt|;
DECL|typedef|GimpPixelFetcher
block|}
name|GimpPixelFetcher
typedef|;
end_typedef

begin_function_decl
name|GimpPixelFetcher
modifier|*
name|gimp_pixel_fetcher_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pixel_fetcher_set_bg_color
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pixel_fetcher_get_pixel
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|guchar
modifier|*
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pixel_fetcher_destroy
parameter_list|(
name|GimpPixelFetcher
modifier|*
name|pf
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MISC_H__ */
end_comment

end_unit

