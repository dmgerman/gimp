begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimptile.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TILE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TILE_H__
define|#
directive|define
name|__GIMP_TILE_H__
end_define

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
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
DECL|struct|_GimpTile
struct|struct
name|_GimpTile
block|{
DECL|member|ewidth
name|guint
name|ewidth
decl_stmt|;
comment|/* the effective width of the tile */
DECL|member|eheight
name|guint
name|eheight
decl_stmt|;
comment|/* the effective height of the tile */
DECL|member|bpp
name|guint
name|bpp
decl_stmt|;
comment|/* the bytes per pixel (1, 2, 3 or 4 ) */
DECL|member|tile_num
name|guint
name|tile_num
decl_stmt|;
comment|/* the number of this tile within the drawable */
DECL|member|ref_count
name|guint16
name|ref_count
decl_stmt|;
comment|/* reference count for the tile */
DECL|member|dirty
name|guint
name|dirty
range|:
literal|1
decl_stmt|;
comment|/* is the tile dirty? has it been modified? */
DECL|member|shadow
name|guint
name|shadow
range|:
literal|1
decl_stmt|;
comment|/* is this a shadow tile */
DECL|member|data
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/* the pixel data for the tile */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* the drawable this tile came from */
block|}
struct|;
name|void
name|gimp_tile_ref
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
name|void
name|gimp_tile_ref_zero
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
name|void
name|gimp_tile_unref
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|,
name|gboolean
name|dirty
parameter_list|)
function_decl|;
name|void
name|gimp_tile_flush
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
name|void
name|gimp_tile_cache_size
parameter_list|(
name|gulong
name|kilobytes
parameter_list|)
function_decl|;
name|void
name|gimp_tile_cache_ntiles
parameter_list|(
name|gulong
name|ntiles
parameter_list|)
function_decl|;
name|guint
name|gimp_tile_width
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|guint
name|gimp_tile_height
parameter_list|(
name|void
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

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TILE_H__ */
end_comment

end_unit

