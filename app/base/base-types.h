begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
comment|/*  magic constants  */
end_comment

begin_comment
comment|/* FIXME: Remove magic constants! */
end_comment

begin_define
DECL|macro|MAX_CHANNELS
define|#
directive|define
name|MAX_CHANNELS
value|4
end_define

begin_define
DECL|macro|GRAY_PIX
define|#
directive|define
name|GRAY_PIX
value|0
end_define

begin_define
DECL|macro|ALPHA_G_PIX
define|#
directive|define
name|ALPHA_G_PIX
value|1
end_define

begin_define
DECL|macro|RED_PIX
define|#
directive|define
name|RED_PIX
value|0
end_define

begin_define
DECL|macro|GREEN_PIX
define|#
directive|define
name|GREEN_PIX
value|1
end_define

begin_define
DECL|macro|BLUE_PIX
define|#
directive|define
name|BLUE_PIX
value|2
end_define

begin_define
DECL|macro|ALPHA_PIX
define|#
directive|define
name|ALPHA_PIX
value|3
end_define

begin_define
DECL|macro|INDEXED_PIX
define|#
directive|define
name|INDEXED_PIX
value|0
end_define

begin_define
DECL|macro|ALPHA_I_PIX
define|#
directive|define
name|ALPHA_I_PIX
value|1
end_define

begin_comment
comment|/* types */
end_comment

begin_typedef
DECL|typedef|BoundSeg
typedef|typedef
name|struct
name|_BoundSeg
name|BoundSeg
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHistogram
typedef|typedef
name|struct
name|_GimpHistogram
name|GimpHistogram
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLut
typedef|typedef
name|struct
name|_GimpLut
name|GimpLut
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorBalance
typedef|typedef
name|struct
name|_ColorBalance
name|ColorBalance
typedef|;
end_typedef

begin_typedef
DECL|typedef|Colorize
typedef|typedef
name|struct
name|_Colorize
name|Colorize
typedef|;
end_typedef

begin_typedef
DECL|typedef|Curves
typedef|typedef
name|struct
name|_Curves
name|Curves
typedef|;
end_typedef

begin_typedef
DECL|typedef|HueSaturation
typedef|typedef
name|struct
name|_HueSaturation
name|HueSaturation
typedef|;
end_typedef

begin_typedef
DECL|typedef|Levels
typedef|typedef
name|struct
name|_Levels
name|Levels
typedef|;
end_typedef

begin_typedef
DECL|typedef|Threshold
typedef|typedef
name|struct
name|_Threshold
name|Threshold
typedef|;
end_typedef

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
DECL|typedef|PixelSurround
typedef|typedef
name|struct
name|_PixelSurround
name|PixelSurround
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
DECL|typedef|TempBuf
typedef|typedef
name|struct
name|_TempBuf
name|TempBuf
typedef|;
end_typedef

begin_typedef
DECL|typedef|MaskBuf
typedef|typedef
name|struct
name|_TempBuf
name|MaskBuf
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
DECL|typedef|PixelDataHandle
typedef|typedef
name|struct
name|_PixelDataHandle
name|PixelDataHandle
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

