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

begin_include
include|#
directive|include
file|"pixel_processor.h"
end_include

begin_comment
comment|/* this is temporary, */
end_comment

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
name|guchar
modifier|*
name|data
decl_stmt|;
comment|/*  pointer to region data        */
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
comment|/*  pointer to tiles              */
DECL|member|curtile
name|Tile
modifier|*
name|curtile
decl_stmt|;
comment|/*  current tile                  */
DECL|member|offx
name|gint
name|offx
decl_stmt|;
comment|/*  tile offsets                  */
DECL|member|offy
name|gint
name|offy
decl_stmt|;
comment|/*  tile offsets                  */
DECL|member|rowstride
name|gint
name|rowstride
decl_stmt|;
comment|/*  bytes per pixel row           */
DECL|member|x
name|gint
name|x
decl_stmt|;
comment|/*  origin                        */
DECL|member|y
name|gint
name|y
decl_stmt|;
comment|/*  origin                        */
DECL|member|w
name|gint
name|w
decl_stmt|;
comment|/*  width of region               */
DECL|member|h
name|gint
name|h
decl_stmt|;
comment|/*  height of region              */
DECL|member|bytes
name|gint
name|bytes
decl_stmt|;
comment|/*  bytes per pixel               */
DECL|member|dirty
name|gboolean
name|dirty
decl_stmt|;
comment|/*  will this region be dirtied?  */
DECL|member|process_count
name|gint
name|process_count
decl_stmt|;
comment|/*  used internally               */
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PixelRegionHolder
typedef|typedef
name|struct
name|_PixelRegionHolder
name|PixelRegionHolder
typedef|;
end_typedef

begin_struct
DECL|struct|_PixelRegionHolder
struct|struct
name|_PixelRegionHolder
block|{
DECL|member|PR
name|PixelRegion
modifier|*
name|PR
decl_stmt|;
DECL|member|original_data
name|guchar
modifier|*
name|original_data
decl_stmt|;
DECL|member|startx
name|gint
name|startx
decl_stmt|;
DECL|member|starty
name|gint
name|starty
decl_stmt|;
DECL|member|count
name|gint
name|count
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|PixelRegionIterator
typedef|typedef
name|struct
name|_PixelRegionIterator
name|PixelRegionIterator
typedef|;
end_typedef

begin_struct
DECL|struct|_PixelRegionIterator
struct|struct
name|_PixelRegionIterator
block|{
DECL|member|pixel_regions
name|GSList
modifier|*
name|pixel_regions
decl_stmt|;
DECL|member|dirty_tiles
name|gint
name|dirty_tiles
decl_stmt|;
DECL|member|region_width
name|gint
name|region_width
decl_stmt|;
DECL|member|region_height
name|gint
name|region_height
decl_stmt|;
DECL|member|portion_width
name|gint
name|portion_width
decl_stmt|;
DECL|member|portion_height
name|gint
name|portion_height
decl_stmt|;
DECL|member|process_count
name|gint
name|process_count
decl_stmt|;
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
name|PR
parameter_list|,
name|TileManager
modifier|*
name|tiles
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gboolean
name|dirty
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_resize
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_get_async
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|gint
name|ulx
parameter_list|,
name|gint
name|uly
parameter_list|,
name|gint
name|lrx
parameter_list|,
name|gint
name|lry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_get_row
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|subsample
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_set_row
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_get_col
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|h
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|,
name|gint
name|subsample
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_region_set_col
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|h
parameter_list|,
name|guchar
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|pixel_region_has_alpha
parameter_list|(
name|PixelRegion
modifier|*
name|PR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|pixel_regions_register
parameter_list|(
name|gint
name|num_regions
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|pixel_regions_process
parameter_list|(
name|gpointer
name|PRI_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|pixel_regions_process_stop
parameter_list|(
name|gpointer
name|PRI_ptr
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

