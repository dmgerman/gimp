begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"paint-funcs/paint-funcs-types.h"
end_include

begin_include
include|#
directive|include
file|"base/base-enums.h"
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
comment|/*  enums  */
end_comment

begin_comment
comment|/* Types of convolutions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28d85b500103
block|{
DECL|enumerator|GIMP_NORMAL_CONVOL
name|GIMP_NORMAL_CONVOL
block|,
comment|/*  Negative numbers truncated  */
DECL|enumerator|GIMP_ABSOLUTE_CONVOL
name|GIMP_ABSOLUTE_CONVOL
block|,
comment|/*  Absolute value              */
DECL|enumerator|GIMP_NEGATIVE_CONVOL
name|GIMP_NEGATIVE_CONVOL
comment|/*  add 127 to values           */
DECL|typedef|GimpConvolutionType
block|}
name|GimpConvolutionType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28d85b500203
block|{
DECL|enumerator|GIMP_VALUE_LUT
name|GIMP_VALUE_LUT
block|,
DECL|enumerator|GIMP_RED_LUT
name|GIMP_RED_LUT
block|,
DECL|enumerator|GIMP_GREEN_LUT
name|GIMP_GREEN_LUT
block|,
DECL|enumerator|GIMP_BLUE_LUT
name|GIMP_BLUE_LUT
block|,
DECL|enumerator|GIMP_ALPHA_LUT
name|GIMP_ALPHA_LUT
block|,
DECL|enumerator|GIMP_GRAY_LUT
name|GIMP_GRAY_LUT
init|=
literal|0
comment|/*< skip>*/
DECL|typedef|GimpChannelLutType
block|}
name|GimpChannelLutType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon28d85b500303
block|{
DECL|enumerator|GIMP_HISTOGRAM_VALUE
name|GIMP_HISTOGRAM_VALUE
init|=
literal|0
block|,
DECL|enumerator|GIMP_HISTOGRAM_RED
name|GIMP_HISTOGRAM_RED
init|=
literal|1
block|,
DECL|enumerator|GIMP_HISTOGRAM_GREEN
name|GIMP_HISTOGRAM_GREEN
init|=
literal|2
block|,
DECL|enumerator|GIMP_HISTOGRAM_BLUE
name|GIMP_HISTOGRAM_BLUE
init|=
literal|3
block|,
DECL|enumerator|GIMP_HISTOGRAM_ALPHA
name|GIMP_HISTOGRAM_ALPHA
init|=
literal|4
DECL|typedef|GimpHistogramChannel
block|}
name|GimpHistogramChannel
typedef|;
end_typedef

begin_comment
comment|/*  types  */
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

