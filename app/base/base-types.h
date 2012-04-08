begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BASE_TYPES_H__
end_ifndef

begin_define
DECL|macro|__BASE_TYPES_H__
define|#
directive|define
name|__BASE_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmathtypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolortypes.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs-types.h"
end_include

begin_include
include|#
directive|include
file|"base/base-enums.h"
end_include

begin_include
include|#
directive|include
file|"config/config-types.h"
end_include

begin_comment
comment|/* convenient defines */
end_comment

begin_define
DECL|macro|MAX_CHANNELS
define|#
directive|define
name|MAX_CHANNELS
value|4
end_define

begin_define
DECL|macro|RED
define|#
directive|define
name|RED
value|0
end_define

begin_define
DECL|macro|GREEN
define|#
directive|define
name|GREEN
value|1
end_define

begin_define
DECL|macro|BLUE
define|#
directive|define
name|BLUE
value|2
end_define

begin_define
DECL|macro|ALPHA
define|#
directive|define
name|ALPHA
value|3
end_define

begin_define
DECL|macro|GRAY
define|#
directive|define
name|GRAY
value|0
end_define

begin_define
DECL|macro|ALPHA_G
define|#
directive|define
name|ALPHA_G
value|1
end_define

begin_define
DECL|macro|INDEXED
define|#
directive|define
name|INDEXED
value|0
end_define

begin_define
DECL|macro|ALPHA_I
define|#
directive|define
name|ALPHA_I
value|1
end_define

begin_comment
comment|/* types */
end_comment

begin_typedef
DECL|typedef|PixelRegionIterator
typedef|typedef
name|struct
name|_PixelRegionIterator
name|PixelRegionIterator
typedef|;
end_typedef

begin_typedef
DECL|typedef|PixelRegion
typedef|typedef
name|struct
name|_PixelRegion
name|PixelRegion
typedef|;
end_typedef

begin_typedef
DECL|typedef|PixelRegionHolder
typedef|typedef
name|struct
name|_PixelRegionHolder
name|PixelRegionHolder
typedef|;
end_typedef

begin_typedef
DECL|typedef|SioxState
typedef|typedef
name|struct
name|_SioxState
name|SioxState
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTempBuf
typedef|typedef
name|struct
name|_GimpTempBuf
name|GimpTempBuf
typedef|;
end_typedef

begin_typedef
DECL|typedef|Tile
typedef|typedef
name|struct
name|_Tile
name|Tile
typedef|;
end_typedef

begin_typedef
DECL|typedef|TileManager
typedef|typedef
name|struct
name|_TileManager
name|TileManager
typedef|;
end_typedef

begin_typedef
DECL|typedef|TilePyramid
typedef|typedef
name|struct
name|_TilePyramid
name|TilePyramid
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|TileValidateProc
typedef|typedef
name|void
function_decl|(
modifier|*
name|TileValidateProc
function_decl|)
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
name|Tile
modifier|*
name|tile
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|PixelProcessorFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|PixelProcessorFunc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __BASE_TYPES_H__ */
end_comment

end_unit

