begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
DECL|enum|__anon295599a50103
block|{
DECL|enumerator|GIMP_WHITE_MASK
name|GIMP_WHITE_MASK
block|,
DECL|enumerator|GIMP_BLACK_MASK
name|GIMP_BLACK_MASK
block|,
DECL|enumerator|GIMP_ALPHA_MASK
name|GIMP_ALPHA_MASK
block|,
DECL|enumerator|GIMP_SELECTION_MASK
name|GIMP_SELECTION_MASK
block|,
DECL|enumerator|GIMP_INV_SELECTION_MASK
name|GIMP_INV_SELECTION_MASK
DECL|typedef|GimpAddMaskType
block|}
name|GimpAddMaskType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50203
block|{
DECL|enumerator|GIMP_FG_BG_RGB
name|GIMP_FG_BG_RGB
block|,
DECL|enumerator|GIMP_FG_BG_HSV
name|GIMP_FG_BG_HSV
block|,
DECL|enumerator|GIMP_FG_TRANS
name|GIMP_FG_TRANS
block|,
DECL|enumerator|GIMP_CUSTOM
name|GIMP_CUSTOM
DECL|typedef|GimpBlendMode
block|}
name|GimpBlendMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50303
block|{
DECL|enumerator|GIMP_HARD
name|GIMP_HARD
block|,
DECL|enumerator|GIMP_SOFT
name|GIMP_SOFT
block|,
DECL|enumerator|GIMP_PRESSURE
name|GIMP_PRESSURE
DECL|typedef|GimpBrushApplicationMode
block|}
name|GimpBrushApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50403
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
DECL|enum|__anon295599a50503
block|{
DECL|enumerator|GIMP_ADD
name|GIMP_ADD
block|,
DECL|enumerator|GIMP_SUB
name|GIMP_SUB
block|,
DECL|enumerator|GIMP_REPLACE
name|GIMP_REPLACE
block|,
DECL|enumerator|GIMP_INTERSECT
name|GIMP_INTERSECT
DECL|typedef|GimpChannelOps
block|}
name|GimpChannelOps
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50603
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
DECL|enum|__anon295599a50703
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
DECL|enum|__anon295599a50803
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
block|,
DECL|enumerator|GIMP_NODESTRUCT_DITHER
name|GIMP_NODESTRUCT_DITHER
DECL|typedef|GimpConvertDitherType
block|}
name|GimpConvertDitherType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50903
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
DECL|enum|__anon295599a50a03
block|{
DECL|enumerator|GIMP_BLUR_CONVOLVE
name|GIMP_BLUR_CONVOLVE
block|,
DECL|enumerator|GIMP_SHARPEN_CONVOLVE
name|GIMP_SHARPEN_CONVOLVE
block|,
DECL|enumerator|GIMP_CUSTOM_CONVOLVE
name|GIMP_CUSTOM_CONVOLVE
DECL|typedef|GimpConvolveType
block|}
name|GimpConvolveType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50b03
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
DECL|enum|__anon295599a50c03
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
DECL|typedef|GimpChannelLutType
block|}
name|GimpChannelLutType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50d03
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
DECL|enum|__anon295599a50e03
block|{
DECL|enumerator|GIMP_FG_IMAGE_FILL
name|GIMP_FG_IMAGE_FILL
block|,
DECL|enumerator|GIMP_BG_IMAGE_FILL
name|GIMP_BG_IMAGE_FILL
block|,
DECL|enumerator|GIMP_WHITE_IMAGE_FILL
name|GIMP_WHITE_IMAGE_FILL
block|,
DECL|enumerator|GIMP_TRANS_IMAGE_FILL
name|GIMP_TRANS_IMAGE_FILL
block|,
DECL|enumerator|GIMP_NO_IMAGE_FILL
name|GIMP_NO_IMAGE_FILL
DECL|typedef|GimpFillType
block|}
name|GimpFillType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a50f03
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
DECL|enum|__anon295599a51003
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
DECL|enum|__anon295599a51103
block|{
DECL|enumerator|GIMP_LINEAR_INTERPOLATION
name|GIMP_LINEAR_INTERPOLATION
block|,
DECL|enumerator|GIMP_CUBIC_INTERPOLATION
name|GIMP_CUBIC_INTERPOLATION
block|,
DECL|enumerator|GIMP_NEAREST_NEIGHBOR_INTERPOLATION
name|GIMP_NEAREST_NEIGHBOR_INTERPOLATION
DECL|typedef|GimpInterpolationType
block|}
name|GimpInterpolationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a51203
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
DECL|enum|__anon295599a51303
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
DECL|enum|__anon295599a51403
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
DECL|enum|__anon295599a51503
block|{
DECL|enumerator|GIMP_ONCE_FORWARD
name|GIMP_ONCE_FORWARD
block|,
DECL|enumerator|GIMP_ONCE_BACKWARDS
name|GIMP_ONCE_BACKWARDS
block|,
DECL|enumerator|GIMP_LOOP_SAWTOOTH
name|GIMP_LOOP_SAWTOOTH
block|,
DECL|enumerator|GIMP_LOOP_TRIANGLE
name|GIMP_LOOP_TRIANGLE
block|,
DECL|enumerator|GIMP_ONCE_END_COLOR
name|GIMP_ONCE_END_COLOR
DECL|typedef|GimpGradientPaintMode
block|}
name|GimpGradientPaintMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a51603
block|{
DECL|enumerator|GIMP_LINEAR
name|GIMP_LINEAR
block|,
DECL|enumerator|GIMP_BILINEAR
name|GIMP_BILINEAR
block|,
DECL|enumerator|GIMP_RADIAL
name|GIMP_RADIAL
block|,
DECL|enumerator|GIMP_SQUARE
name|GIMP_SQUARE
block|,
DECL|enumerator|GIMP_CONICAL_SYMMETRIC
name|GIMP_CONICAL_SYMMETRIC
block|,
DECL|enumerator|GIMP_CONICAL_ASYMMETRIC
name|GIMP_CONICAL_ASYMMETRIC
block|,
DECL|enumerator|GIMP_SHAPEBURST_ANGULAR
name|GIMP_SHAPEBURST_ANGULAR
block|,
DECL|enumerator|GIMP_SHAPEBURST_SPHERICAL
name|GIMP_SHAPEBURST_SPHERICAL
block|,
DECL|enumerator|GIMP_SHAPEBURST_DIMPLED
name|GIMP_SHAPEBURST_DIMPLED
block|,
DECL|enumerator|GIMP_SPIRAL_CLOCKWISE
name|GIMP_SPIRAL_CLOCKWISE
block|,
DECL|enumerator|GIMP_SPIRAL_ANTICLOCKWISE
name|GIMP_SPIRAL_ANTICLOCKWISE
DECL|typedef|GimpGradientType
block|}
name|GimpGradientType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a51703
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
DECL|enum|__anon295599a51803
block|{
DECL|enumerator|GIMP_APPLY
name|GIMP_APPLY
block|,
DECL|enumerator|GIMP_DISCARD
name|GIMP_DISCARD
DECL|typedef|GimpMaskApplyMode
block|}
name|GimpMaskApplyMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a51903
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
DECL|enum|__anon295599a51a03
block|{
DECL|enumerator|GIMP_HORIZONTAL
name|GIMP_HORIZONTAL
block|,
DECL|enumerator|GIMP_VERTICAL
name|GIMP_VERTICAL
block|,
DECL|enumerator|GIMP_UNKNOWN
name|GIMP_UNKNOWN
DECL|typedef|GimpOrientationType
block|}
name|GimpOrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a51b03
block|{
DECL|enumerator|GIMP_CONTINUOUS
name|GIMP_CONTINUOUS
block|,
DECL|enumerator|GIMP_INCREMENTAL
name|GIMP_INCREMENTAL
DECL|typedef|GimpPaintApplicationMode
block|}
name|GimpPaintApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a51c03
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
DECL|enum|__anon295599a51d03
block|{
DECL|enumerator|GIMP_RUN_INTERACTIVE
name|GIMP_RUN_INTERACTIVE
block|,
DECL|enumerator|GIMP_RUN_NONINTERACTIVE
name|GIMP_RUN_NONINTERACTIVE
block|,
DECL|enumerator|GIMP_RUN_WITH_LAST_VALS
name|GIMP_RUN_WITH_LAST_VALS
DECL|typedef|GimpRunModeType
block|}
name|GimpRunModeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon295599a51e03
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

