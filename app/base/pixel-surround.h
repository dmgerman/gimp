begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PIXEL_SURROUND_H__
end_ifndef

begin_define
DECL|macro|__PIXEL_SURROUND_H__
define|#
directive|define
name|__PIXEL_SURROUND_H__
end_define

begin_comment
comment|/* PixelSurround describes a (read-only)  *  region around a pixel in a tile manager  */
end_comment

begin_typedef
DECL|struct|_PixelSurround
typedef|typedef
struct|struct
name|_PixelSurround
block|{
DECL|member|tile
name|Tile
modifier|*
name|tile
decl_stmt|;
DECL|member|mgr
name|TileManager
modifier|*
name|mgr
decl_stmt|;
DECL|member|buff
name|guchar
modifier|*
name|buff
decl_stmt|;
DECL|member|buff_size
name|gint
name|buff_size
decl_stmt|;
DECL|member|bpp
name|gint
name|bpp
decl_stmt|;
DECL|member|w
name|gint
name|w
decl_stmt|;
DECL|member|h
name|gint
name|h
decl_stmt|;
DECL|member|bg
name|guchar
name|bg
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
DECL|member|row_stride
name|gint
name|row_stride
decl_stmt|;
DECL|typedef|PixelSurround
block|}
name|PixelSurround
typedef|;
end_typedef

begin_function_decl
name|void
name|pixel_surround_init
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|,
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
specifier|const
name|guchar
name|bg
index|[
name|MAX_CHANNELS
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* return a pointer to a buffer which contains all the surrounding pixels  * strategy: if we are in the middle of a tile, use the tile storage  * otherwise just copy into our own malloced buffer and return that  */
end_comment

begin_function_decl
name|guchar
modifier|*
name|pixel_surround_lock
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|pixel_surround_rowstride
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_surround_release
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_surround_clear
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PIXEL_SURROUND_H__ */
end_comment

end_unit

