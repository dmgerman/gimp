begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by enumcode.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ENUMS_H__
define|#
directive|define
name|__GIMP_ENUMS_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0103
block|{
DECL|enumerator|GIMP_ADD_WHITE_MASK
name|GIMP_ADD_WHITE_MASK
block|,
DECL|enumerator|GIMP_ADD_BLACK_MASK
name|GIMP_ADD_BLACK_MASK
block|,
DECL|enumerator|GIMP_ADD_ALPHA_MASK
name|GIMP_ADD_ALPHA_MASK
block|,
DECL|enumerator|GIMP_ADD_ALPHA_TRANSFER_MASK
name|GIMP_ADD_ALPHA_TRANSFER_MASK
block|,
DECL|enumerator|GIMP_ADD_SELECTION_MASK
name|GIMP_ADD_SELECTION_MASK
block|,
DECL|enumerator|GIMP_ADD_COPY_MASK
name|GIMP_ADD_COPY_MASK
DECL|typedef|GimpAddMaskType
block|}
name|GimpAddMaskType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0203
block|{
DECL|enumerator|GIMP_FG_BG_RGB_MODE
name|GIMP_FG_BG_RGB_MODE
block|,
DECL|enumerator|GIMP_FG_BG_HSV_MODE
name|GIMP_FG_BG_HSV_MODE
block|,
DECL|enumerator|GIMP_FG_TRANSPARENT_MODE
name|GIMP_FG_TRANSPARENT_MODE
block|,
DECL|enumerator|GIMP_CUSTOM_MODE
name|GIMP_CUSTOM_MODE
DECL|typedef|GimpBlendMode
block|}
name|GimpBlendMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0303
block|{
DECL|enumerator|GIMP_BRUSH_HARD
name|GIMP_BRUSH_HARD
block|,
DECL|enumerator|GIMP_BRUSH_SOFT
name|GIMP_BRUSH_SOFT
DECL|typedef|GimpBrushApplicationMode
block|}
name|GimpBrushApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0403
block|{
DECL|enumerator|GIMP_FG_BUCKET_FILL
name|GIMP_FG_BUCKET_FILL
block|,
DECL|enumerator|GIMP_BG_BUCKET_FILL
name|GIMP_BG_BUCKET_FILL
block|,
DECL|enumerator|GIMP_PATTERN_BUCKET_FILL
name|GIMP_PATTERN_BUCKET_FILL
DECL|typedef|GimpBucketFillMode
block|}
name|GimpBucketFillMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0503
block|{
DECL|enumerator|GIMP_CHANNEL_OP_ADD
name|GIMP_CHANNEL_OP_ADD
block|,
DECL|enumerator|GIMP_CHANNEL_OP_SUBTRACT
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
DECL|enumerator|GIMP_CHANNEL_OP_REPLACE
name|GIMP_CHANNEL_OP_REPLACE
block|,
DECL|enumerator|GIMP_CHANNEL_OP_INTERSECT
name|GIMP_CHANNEL_OP_INTERSECT
DECL|typedef|GimpChannelOps
block|}
name|GimpChannelOps
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0603
block|{
DECL|enumerator|GIMP_RED_CHANNEL
name|GIMP_RED_CHANNEL
block|,
DECL|enumerator|GIMP_GREEN_CHANNEL
name|GIMP_GREEN_CHANNEL
block|,
DECL|enumerator|GIMP_BLUE_CHANNEL
name|GIMP_BLUE_CHANNEL
block|,
DECL|enumerator|GIMP_GRAY_CHANNEL
name|GIMP_GRAY_CHANNEL
block|,
DECL|enumerator|GIMP_INDEXED_CHANNEL
name|GIMP_INDEXED_CHANNEL
block|,
DECL|enumerator|GIMP_ALPHA_CHANNEL
name|GIMP_ALPHA_CHANNEL
DECL|typedef|GimpChannelType
block|}
name|GimpChannelType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0703
block|{
DECL|enumerator|GIMP_IMAGE_CLONE
name|GIMP_IMAGE_CLONE
block|,
DECL|enumerator|GIMP_PATTERN_CLONE
name|GIMP_PATTERN_CLONE
DECL|typedef|GimpCloneType
block|}
name|GimpCloneType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0803
block|{
DECL|enumerator|GIMP_NO_DITHER
name|GIMP_NO_DITHER
block|,
DECL|enumerator|GIMP_FS_DITHER
name|GIMP_FS_DITHER
block|,
DECL|enumerator|GIMP_FSLOWBLEED_DITHER
name|GIMP_FSLOWBLEED_DITHER
block|,
DECL|enumerator|GIMP_FIXED_DITHER
name|GIMP_FIXED_DITHER
DECL|typedef|GimpConvertDitherType
block|}
name|GimpConvertDitherType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0903
block|{
DECL|enumerator|GIMP_MAKE_PALETTE
name|GIMP_MAKE_PALETTE
block|,
DECL|enumerator|GIMP_REUSE_PALETTE
name|GIMP_REUSE_PALETTE
block|,
DECL|enumerator|GIMP_WEB_PALETTE
name|GIMP_WEB_PALETTE
block|,
DECL|enumerator|GIMP_MONO_PALETTE
name|GIMP_MONO_PALETTE
block|,
DECL|enumerator|GIMP_CUSTOM_PALETTE
name|GIMP_CUSTOM_PALETTE
DECL|typedef|GimpConvertPaletteType
block|}
name|GimpConvertPaletteType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0a03
block|{
DECL|enumerator|GIMP_NORMAL_CONVOL
name|GIMP_NORMAL_CONVOL
block|,
DECL|enumerator|GIMP_ABSOLUTE_CONVOL
name|GIMP_ABSOLUTE_CONVOL
block|,
DECL|enumerator|GIMP_NEGATIVE_CONVOL
name|GIMP_NEGATIVE_CONVOL
DECL|typedef|GimpConvolutionType
block|}
name|GimpConvolutionType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0b03
block|{
DECL|enumerator|GIMP_BLUR_CONVOLVE
name|GIMP_BLUR_CONVOLVE
block|,
DECL|enumerator|GIMP_SHARPEN_CONVOLVE
name|GIMP_SHARPEN_CONVOLVE
DECL|typedef|GimpConvolveType
block|}
name|GimpConvolveType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0c03
block|{
DECL|enumerator|GIMP_DODGE
name|GIMP_DODGE
block|,
DECL|enumerator|GIMP_BURN
name|GIMP_BURN
DECL|typedef|GimpDodgeBurnType
block|}
name|GimpDodgeBurnType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0d03
block|{
DECL|enumerator|GIMP_FOREGROUND_FILL
name|GIMP_FOREGROUND_FILL
block|,
DECL|enumerator|GIMP_BACKGROUND_FILL
name|GIMP_BACKGROUND_FILL
block|,
DECL|enumerator|GIMP_WHITE_FILL
name|GIMP_WHITE_FILL
block|,
DECL|enumerator|GIMP_TRANSPARENT_FILL
name|GIMP_TRANSPARENT_FILL
block|,
DECL|enumerator|GIMP_PATTERN_FILL
name|GIMP_PATTERN_FILL
DECL|typedef|GimpFillType
block|}
name|GimpFillType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0e03
block|{
DECL|enumerator|GIMP_GRADIENT_LINEAR
name|GIMP_GRADIENT_LINEAR
block|,
DECL|enumerator|GIMP_GRADIENT_BILINEAR
name|GIMP_GRADIENT_BILINEAR
block|,
DECL|enumerator|GIMP_GRADIENT_RADIAL
name|GIMP_GRADIENT_RADIAL
block|,
DECL|enumerator|GIMP_GRADIENT_SQUARE
name|GIMP_GRADIENT_SQUARE
block|,
DECL|enumerator|GIMP_GRADIENT_CONICAL_SYMMETRIC
name|GIMP_GRADIENT_CONICAL_SYMMETRIC
block|,
DECL|enumerator|GIMP_GRADIENT_CONICAL_ASYMMETRIC
name|GIMP_GRADIENT_CONICAL_ASYMMETRIC
block|,
DECL|enumerator|GIMP_GRADIENT_SHAPEBURST_ANGULAR
name|GIMP_GRADIENT_SHAPEBURST_ANGULAR
block|,
DECL|enumerator|GIMP_GRADIENT_SHAPEBURST_SPHERICAL
name|GIMP_GRADIENT_SHAPEBURST_SPHERICAL
block|,
DECL|enumerator|GIMP_GRADIENT_SHAPEBURST_DIMPLED
name|GIMP_GRADIENT_SHAPEBURST_DIMPLED
block|,
DECL|enumerator|GIMP_GRADIENT_SPIRAL_CLOCKWISE
name|GIMP_GRADIENT_SPIRAL_CLOCKWISE
block|,
DECL|enumerator|GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE
name|GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE
DECL|typedef|GimpGradientType
block|}
name|GimpGradientType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc0f03
block|{
DECL|enumerator|GIMP_HISTOGRAM_VALUE
name|GIMP_HISTOGRAM_VALUE
block|,
DECL|enumerator|GIMP_HISTOGRAM_RED
name|GIMP_HISTOGRAM_RED
block|,
DECL|enumerator|GIMP_HISTOGRAM_GREEN
name|GIMP_HISTOGRAM_GREEN
block|,
DECL|enumerator|GIMP_HISTOGRAM_BLUE
name|GIMP_HISTOGRAM_BLUE
block|,
DECL|enumerator|GIMP_HISTOGRAM_ALPHA
name|GIMP_HISTOGRAM_ALPHA
DECL|typedef|GimpHistogramChannel
block|}
name|GimpHistogramChannel
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1003
block|{
DECL|enumerator|GIMP_ALL_HUES
name|GIMP_ALL_HUES
block|,
DECL|enumerator|GIMP_RED_HUES
name|GIMP_RED_HUES
block|,
DECL|enumerator|GIMP_YELLOW_HUES
name|GIMP_YELLOW_HUES
block|,
DECL|enumerator|GIMP_GREEN_HUES
name|GIMP_GREEN_HUES
block|,
DECL|enumerator|GIMP_CYAN_HUES
name|GIMP_CYAN_HUES
block|,
DECL|enumerator|GIMP_BLUE_HUES
name|GIMP_BLUE_HUES
block|,
DECL|enumerator|GIMP_MAGENTA_HUES
name|GIMP_MAGENTA_HUES
DECL|typedef|GimpHueRange
block|}
name|GimpHueRange
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1103
block|{
DECL|enumerator|GIMP_ICON_TYPE_STOCK_ID
name|GIMP_ICON_TYPE_STOCK_ID
block|,
DECL|enumerator|GIMP_ICON_TYPE_INLINE_PIXBUF
name|GIMP_ICON_TYPE_INLINE_PIXBUF
block|,
DECL|enumerator|GIMP_ICON_TYPE_IMAGE_FILE
name|GIMP_ICON_TYPE_IMAGE_FILE
DECL|typedef|GimpIconType
block|}
name|GimpIconType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1203
block|{
DECL|enumerator|GIMP_RGB
name|GIMP_RGB
block|,
DECL|enumerator|GIMP_GRAY
name|GIMP_GRAY
block|,
DECL|enumerator|GIMP_INDEXED
name|GIMP_INDEXED
DECL|typedef|GimpImageBaseType
block|}
name|GimpImageBaseType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1303
block|{
DECL|enumerator|GIMP_RGB_IMAGE
name|GIMP_RGB_IMAGE
block|,
DECL|enumerator|GIMP_RGBA_IMAGE
name|GIMP_RGBA_IMAGE
block|,
DECL|enumerator|GIMP_GRAY_IMAGE
name|GIMP_GRAY_IMAGE
block|,
DECL|enumerator|GIMP_GRAYA_IMAGE
name|GIMP_GRAYA_IMAGE
block|,
DECL|enumerator|GIMP_INDEXED_IMAGE
name|GIMP_INDEXED_IMAGE
block|,
DECL|enumerator|GIMP_INDEXEDA_IMAGE
name|GIMP_INDEXEDA_IMAGE
DECL|typedef|GimpImageType
block|}
name|GimpImageType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1403
block|{
DECL|enumerator|GIMP_NORMAL_MODE
name|GIMP_NORMAL_MODE
block|,
DECL|enumerator|GIMP_DISSOLVE_MODE
name|GIMP_DISSOLVE_MODE
block|,
DECL|enumerator|GIMP_BEHIND_MODE
name|GIMP_BEHIND_MODE
block|,
DECL|enumerator|GIMP_MULTIPLY_MODE
name|GIMP_MULTIPLY_MODE
block|,
DECL|enumerator|GIMP_SCREEN_MODE
name|GIMP_SCREEN_MODE
block|,
DECL|enumerator|GIMP_OVERLAY_MODE
name|GIMP_OVERLAY_MODE
block|,
DECL|enumerator|GIMP_DIFFERENCE_MODE
name|GIMP_DIFFERENCE_MODE
block|,
DECL|enumerator|GIMP_ADDITION_MODE
name|GIMP_ADDITION_MODE
block|,
DECL|enumerator|GIMP_SUBTRACT_MODE
name|GIMP_SUBTRACT_MODE
block|,
DECL|enumerator|GIMP_DARKEN_ONLY_MODE
name|GIMP_DARKEN_ONLY_MODE
block|,
DECL|enumerator|GIMP_LIGHTEN_ONLY_MODE
name|GIMP_LIGHTEN_ONLY_MODE
block|,
DECL|enumerator|GIMP_HUE_MODE
name|GIMP_HUE_MODE
block|,
DECL|enumerator|GIMP_SATURATION_MODE
name|GIMP_SATURATION_MODE
block|,
DECL|enumerator|GIMP_COLOR_MODE
name|GIMP_COLOR_MODE
block|,
DECL|enumerator|GIMP_VALUE_MODE
name|GIMP_VALUE_MODE
block|,
DECL|enumerator|GIMP_DIVIDE_MODE
name|GIMP_DIVIDE_MODE
block|,
DECL|enumerator|GIMP_DODGE_MODE
name|GIMP_DODGE_MODE
block|,
DECL|enumerator|GIMP_BURN_MODE
name|GIMP_BURN_MODE
block|,
DECL|enumerator|GIMP_HARDLIGHT_MODE
name|GIMP_HARDLIGHT_MODE
block|,
DECL|enumerator|GIMP_SOFTLIGHT_MODE
name|GIMP_SOFTLIGHT_MODE
block|,
DECL|enumerator|GIMP_GRAIN_EXTRACT_MODE
name|GIMP_GRAIN_EXTRACT_MODE
block|,
DECL|enumerator|GIMP_GRAIN_MERGE_MODE
name|GIMP_GRAIN_MERGE_MODE
block|,
DECL|enumerator|GIMP_COLOR_ERASE_MODE
name|GIMP_COLOR_ERASE_MODE
DECL|typedef|GimpLayerModeEffects
block|}
name|GimpLayerModeEffects
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1503
block|{
DECL|enumerator|GIMP_MASK_APPLY
name|GIMP_MASK_APPLY
block|,
DECL|enumerator|GIMP_MASK_DISCARD
name|GIMP_MASK_DISCARD
DECL|typedef|GimpMaskApplyMode
block|}
name|GimpMaskApplyMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1603
block|{
DECL|enumerator|GIMP_EXPAND_AS_NECESSARY
name|GIMP_EXPAND_AS_NECESSARY
block|,
DECL|enumerator|GIMP_CLIP_TO_IMAGE
name|GIMP_CLIP_TO_IMAGE
block|,
DECL|enumerator|GIMP_CLIP_TO_BOTTOM_LAYER
name|GIMP_CLIP_TO_BOTTOM_LAYER
block|,
DECL|enumerator|GIMP_FLATTEN_IMAGE
name|GIMP_FLATTEN_IMAGE
DECL|typedef|GimpMergeType
block|}
name|GimpMergeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1703
block|{
DECL|enumerator|GIMP_OFFSET_BACKGROUND
name|GIMP_OFFSET_BACKGROUND
block|,
DECL|enumerator|GIMP_OFFSET_TRANSPARENT
name|GIMP_OFFSET_TRANSPARENT
DECL|typedef|GimpOffsetType
block|}
name|GimpOffsetType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1803
block|{
DECL|enumerator|GIMP_ORIENTATION_HORIZONTAL
name|GIMP_ORIENTATION_HORIZONTAL
block|,
DECL|enumerator|GIMP_ORIENTATION_VERTICAL
name|GIMP_ORIENTATION_VERTICAL
block|,
DECL|enumerator|GIMP_ORIENTATION_UNKNOWN
name|GIMP_ORIENTATION_UNKNOWN
DECL|typedef|GimpOrientationType
block|}
name|GimpOrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1903
block|{
DECL|enumerator|GIMP_PAINT_CONSTANT
name|GIMP_PAINT_CONSTANT
block|,
DECL|enumerator|GIMP_PAINT_INCREMENTAL
name|GIMP_PAINT_INCREMENTAL
DECL|typedef|GimpPaintApplicationMode
block|}
name|GimpPaintApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1a03
block|{
DECL|enumerator|GIMP_REPEAT_NONE
name|GIMP_REPEAT_NONE
block|,
DECL|enumerator|GIMP_REPEAT_SAWTOOTH
name|GIMP_REPEAT_SAWTOOTH
block|,
DECL|enumerator|GIMP_REPEAT_TRIANGULAR
name|GIMP_REPEAT_TRIANGULAR
DECL|typedef|GimpRepeatMode
block|}
name|GimpRepeatMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1b03
block|{
DECL|enumerator|GIMP_ROTATE_90
name|GIMP_ROTATE_90
block|,
DECL|enumerator|GIMP_ROTATE_180
name|GIMP_ROTATE_180
block|,
DECL|enumerator|GIMP_ROTATE_270
name|GIMP_ROTATE_270
DECL|typedef|GimpRotationType
block|}
name|GimpRotationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1c03
block|{
DECL|enumerator|GIMP_RUN_INTERACTIVE
name|GIMP_RUN_INTERACTIVE
block|,
DECL|enumerator|GIMP_RUN_NONINTERACTIVE
name|GIMP_RUN_NONINTERACTIVE
block|,
DECL|enumerator|GIMP_RUN_WITH_LAST_VALS
name|GIMP_RUN_WITH_LAST_VALS
DECL|typedef|GimpRunMode
block|}
name|GimpRunMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1d03
block|{
DECL|enumerator|GIMP_SHADOWS
name|GIMP_SHADOWS
block|,
DECL|enumerator|GIMP_MIDTONES
name|GIMP_MIDTONES
block|,
DECL|enumerator|GIMP_HIGHLIGHTS
name|GIMP_HIGHLIGHTS
DECL|typedef|GimpTransferMode
block|}
name|GimpTransferMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c726cdc1e03
block|{
DECL|enumerator|GIMP_PIXELS
name|GIMP_PIXELS
block|,
DECL|enumerator|GIMP_POINTS
name|GIMP_POINTS
DECL|typedef|GimpSizeType
block|}
name|GimpSizeType
typedef|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ENUMS_H__ */
end_comment

end_unit

