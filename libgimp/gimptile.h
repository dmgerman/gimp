begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimptile.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_struct
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
end_struct

begin_function_decl
name|void
name|gimp_tile_ref
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tile_ref_zero
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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
end_function_decl

begin_function_decl
name|void
name|gimp_tile_flush
parameter_list|(
name|GimpTile
modifier|*
name|tile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tile_cache_size
parameter_list|(
name|gulong
name|kilobytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tile_cache_ntiles
parameter_list|(
name|gulong
name|ntiles
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private function  */
end_comment

begin_function_decl
name|G_GNUC_INTERNAL
name|void
name|_gimp_tile_cache_flush_drawable
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
comment|/* __GIMP_TILE_H__ */
end_comment

end_unit

