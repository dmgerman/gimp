begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PIXEL_REGION_H__
end_ifndef

begin_define
DECL|macro|__PIXEL_REGION_H__
define|#
directive|define
name|__PIXEL_REGION_H__
end_define

begin_include
include|#
directive|include
file|"tile_manager.h"
end_include

begin_typedef
DECL|typedef|PixelRegion
typedef|typedef
name|struct
name|_PixelRegion
name|PixelRegion
typedef|;
end_typedef

begin_struct
DECL|struct|_PixelRegion
struct|struct
name|_PixelRegion
block|{
DECL|member|data
name|unsigned
name|char
modifier|*
name|data
decl_stmt|;
comment|/*  pointer to region data  */
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/*  pointer to tiles  */
DECL|member|rowstride
name|int
name|rowstride
decl_stmt|;
comment|/*  bytes per pixel row  */
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  origin  */
DECL|member|w
DECL|member|h
name|int
name|w
decl_stmt|,
name|h
decl_stmt|;
comment|/*  width and  height of region  */
DECL|member|bytes
name|int
name|bytes
decl_stmt|;
comment|/*  bytes per pixel  */
DECL|member|dirty
name|int
name|dirty
decl_stmt|;
comment|/*  will this region be dirtied?  */
DECL|member|process_count
name|int
name|process_count
decl_stmt|;
comment|/*  used internally  */
block|}
struct|;
end_struct

begin_comment
comment|/*  PixelRegion functions  */
end_comment

begin_function_decl
name|void
name|pixel_region_init
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_resize
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_get_row
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_set_row
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_get_col
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_set_col
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|pixel_regions_register
parameter_list|(
name|int
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|pixel_regions_process
parameter_list|(
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_regions_process_stop
parameter_list|(
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PIXEL_REGION_H__ */
end_comment

end_unit

