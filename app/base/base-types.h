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

begin_comment
comment|/*  magic constants  */
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
comment|/* Layer modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2937f4950103
block|{
DECL|enumerator|NORMAL_MODE
name|NORMAL_MODE
block|,
DECL|enumerator|DISSOLVE_MODE
name|DISSOLVE_MODE
block|,
DECL|enumerator|BEHIND_MODE
name|BEHIND_MODE
block|,
DECL|enumerator|MULTIPLY_MODE
name|MULTIPLY_MODE
block|,
DECL|enumerator|SCREEN_MODE
name|SCREEN_MODE
block|,
DECL|enumerator|OVERLAY_MODE
name|OVERLAY_MODE
block|,
DECL|enumerator|DIFFERENCE_MODE
name|DIFFERENCE_MODE
block|,
DECL|enumerator|ADDITION_MODE
name|ADDITION_MODE
block|,
DECL|enumerator|SUBTRACT_MODE
name|SUBTRACT_MODE
block|,
DECL|enumerator|DARKEN_ONLY_MODE
name|DARKEN_ONLY_MODE
block|,
DECL|enumerator|LIGHTEN_ONLY_MODE
name|LIGHTEN_ONLY_MODE
block|,
DECL|enumerator|HUE_MODE
name|HUE_MODE
block|,
DECL|enumerator|SATURATION_MODE
name|SATURATION_MODE
block|,
DECL|enumerator|COLOR_MODE
name|COLOR_MODE
block|,
DECL|enumerator|VALUE_MODE
name|VALUE_MODE
block|,
DECL|enumerator|DIVIDE_MODE
name|DIVIDE_MODE
block|,
DECL|enumerator|DODGE_MODE
name|DODGE_MODE
block|,
DECL|enumerator|BURN_MODE
name|BURN_MODE
block|,
DECL|enumerator|HARDLIGHT_MODE
name|HARDLIGHT_MODE
block|,
DECL|enumerator|ERASE_MODE
name|ERASE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|REPLACE_MODE
name|REPLACE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|ANTI_ERASE_MODE
name|ANTI_ERASE_MODE
comment|/*< skip>*/
DECL|typedef|LayerModeEffects
block|}
name|LayerModeEffects
typedef|;
end_typedef

begin_comment
comment|/* Types of convolutions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2937f4950203
block|{
DECL|enumerator|NORMAL_CONVOL
name|NORMAL_CONVOL
block|,
comment|/*  Negative numbers truncated  */
DECL|enumerator|ABSOLUTE_CONVOL
name|ABSOLUTE_CONVOL
block|,
comment|/*  Absolute value              */
DECL|enumerator|NEGATIVE_CONVOL
name|NEGATIVE_CONVOL
comment|/*  add 127 to values           */
DECL|typedef|ConvolutionType
block|}
name|ConvolutionType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2937f4950303
block|{
DECL|enumerator|LINEAR_INTERPOLATION
name|LINEAR_INTERPOLATION
block|,
DECL|enumerator|CUBIC_INTERPOLATION
name|CUBIC_INTERPOLATION
block|,
DECL|enumerator|NEAREST_NEIGHBOR_INTERPOLATION
name|NEAREST_NEIGHBOR_INTERPOLATION
DECL|typedef|InterpolationType
block|}
name|InterpolationType
typedef|;
end_typedef

begin_comment
comment|/*  Transparency representation  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2937f4950403
block|{
DECL|enumerator|LIGHT_CHECKS
name|LIGHT_CHECKS
init|=
literal|0
block|,
DECL|enumerator|GRAY_CHECKS
name|GRAY_CHECKS
init|=
literal|1
block|,
DECL|enumerator|DARK_CHECKS
name|DARK_CHECKS
init|=
literal|2
block|,
DECL|enumerator|WHITE_ONLY
name|WHITE_ONLY
init|=
literal|3
block|,
DECL|enumerator|GRAY_ONLY
name|GRAY_ONLY
init|=
literal|4
block|,
DECL|enumerator|BLACK_ONLY
name|BLACK_ONLY
init|=
literal|5
DECL|typedef|GimpCheckType
block|}
name|GimpCheckType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2937f4950503
block|{
DECL|enumerator|SMALL_CHECKS
name|SMALL_CHECKS
init|=
literal|0
block|,
DECL|enumerator|MEDIUM_CHECKS
name|MEDIUM_CHECKS
init|=
literal|1
block|,
DECL|enumerator|LARGE_CHECKS
name|LARGE_CHECKS
init|=
literal|2
DECL|typedef|GimpCheckSize
block|}
name|GimpCheckSize
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
DECL|typedef|ScanConvertPoint
typedef|typedef
name|struct
name|_ScanConvertPoint
name|ScanConvertPoint
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

