begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PIXEL_REGION_P_H__
end_ifndef

begin_define
DECL|macro|__PIXEL_REGION_P_H__
define|#
directive|define
name|__PIXEL_REGION_P_H__
end_define

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PIXEL_REGION_P_H__  */
end_comment

end_unit

