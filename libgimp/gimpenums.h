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

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0103
block|{
DECL|enumerator|GIMP_WHITE_MASK
name|GIMP_WHITE_MASK
block|,
DECL|enumerator|GIMP_BLACK_MASK
name|GIMP_BLACK_MASK
block|,
DECL|enumerator|GIMP_ALPHA_MASK
name|GIMP_ALPHA_MASK
DECL|typedef|GimpAddMaskType
block|}
name|GimpAddMaskType
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0203
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0303
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0403
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0503
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0603
block|{
DECL|enumerator|GIMP_OFFSET_BACKGROUND
name|GIMP_OFFSET_BACKGROUND
block|,
DECL|enumerator|GIMP_OFFSET_TRANSPARENT
name|GIMP_OFFSET_TRANSPARENT
DECL|typedef|GimpChannelOffsetType
block|}
name|GimpChannelOffsetType
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0703
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0803
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
DECL|enumerator|GIMP_AUXILLARY_CHANNEL
name|GIMP_AUXILLARY_CHANNEL
DECL|typedef|GimpChannelType
block|}
name|GimpChannelType
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0903
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0a03
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0b03
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0c03
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0d03
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0e03
block|{
DECL|enumerator|GIMP_DODGEBURN_HIGHLIGHTS
name|GIMP_DODGEBURN_HIGHLIGHTS
block|,
DECL|enumerator|GIMP_DODGEBURN_MIDTONES
name|GIMP_DODGEBURN_MIDTONES
block|,
DECL|enumerator|GIMP_DODGEBURN_SHADOWS
name|GIMP_DODGEBURN_SHADOWS
DECL|typedef|GimpDodgeBurnMode
block|}
name|GimpDodgeBurnMode
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f0f03
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1003
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1103
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1203
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1303
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1403
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1503
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1603
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1703
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
DECL|typedef|GimpLayerModeEffects
block|}
name|GimpLayerModeEffects
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1803
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1903
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1a03
block|{
DECL|enumerator|GIMP_MESSAGE_BOX
name|GIMP_MESSAGE_BOX
block|,
DECL|enumerator|GIMP_CONSOLE
name|GIMP_CONSOLE
block|,
DECL|enumerator|GIMP_ERROR_CONSOLE
name|GIMP_ERROR_CONSOLE
DECL|typedef|GimpMessageHandlerType
block|}
name|GimpMessageHandlerType
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1b03
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1c03
block|{
DECL|enumerator|GIMP_PDB_INT32
name|GIMP_PDB_INT32
block|,
DECL|enumerator|GIMP_PDB_INT16
name|GIMP_PDB_INT16
block|,
DECL|enumerator|GIMP_PDB_INT8
name|GIMP_PDB_INT8
block|,
DECL|enumerator|GIMP_PDB_FLOAT
name|GIMP_PDB_FLOAT
block|,
DECL|enumerator|GIMP_PDB_STRING
name|GIMP_PDB_STRING
block|,
DECL|enumerator|GIMP_PDB_INT32ARRAY
name|GIMP_PDB_INT32ARRAY
block|,
DECL|enumerator|GIMP_PDB_INT16ARRAY
name|GIMP_PDB_INT16ARRAY
block|,
DECL|enumerator|GIMP_PDB_INT8ARRAY
name|GIMP_PDB_INT8ARRAY
block|,
DECL|enumerator|GIMP_PDB_FLOATARRAY
name|GIMP_PDB_FLOATARRAY
block|,
DECL|enumerator|GIMP_PDB_STRINGARRAY
name|GIMP_PDB_STRINGARRAY
block|,
DECL|enumerator|GIMP_PDB_COLOR
name|GIMP_PDB_COLOR
block|,
DECL|enumerator|GIMP_PDB_REGION
name|GIMP_PDB_REGION
block|,
DECL|enumerator|GIMP_PDB_DISPLAY
name|GIMP_PDB_DISPLAY
block|,
DECL|enumerator|GIMP_PDB_IMAGE
name|GIMP_PDB_IMAGE
block|,
DECL|enumerator|GIMP_PDB_LAYER
name|GIMP_PDB_LAYER
block|,
DECL|enumerator|GIMP_PDB_CHANNEL
name|GIMP_PDB_CHANNEL
block|,
DECL|enumerator|GIMP_PDB_DRAWABLE
name|GIMP_PDB_DRAWABLE
block|,
DECL|enumerator|GIMP_PDB_SELECTION
name|GIMP_PDB_SELECTION
block|,
DECL|enumerator|GIMP_PDB_BOUNDARY
name|GIMP_PDB_BOUNDARY
block|,
DECL|enumerator|GIMP_PDB_PATH
name|GIMP_PDB_PATH
block|,
DECL|enumerator|GIMP_PDB_PARASITE
name|GIMP_PDB_PARASITE
block|,
DECL|enumerator|GIMP_PDB_STATUS
name|GIMP_PDB_STATUS
block|,
DECL|enumerator|GIMP_PDB_END
name|GIMP_PDB_END
DECL|typedef|GimpPDBArgType
block|}
name|GimpPDBArgType
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1d03
block|{
DECL|enumerator|GIMP_INTERNAL
name|GIMP_INTERNAL
block|,
DECL|enumerator|GIMP_PLUGIN
name|GIMP_PLUGIN
block|,
DECL|enumerator|GIMP_EXTENSION
name|GIMP_EXTENSION
block|,
DECL|enumerator|GIMP_TEMPORARY
name|GIMP_TEMPORARY
DECL|typedef|GimpPDBProcType
block|}
name|GimpPDBProcType
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1e03
block|{
DECL|enumerator|GIMP_PDB_EXECUTION_ERROR
name|GIMP_PDB_EXECUTION_ERROR
block|,
DECL|enumerator|GIMP_PDB_CALLING_ERROR
name|GIMP_PDB_CALLING_ERROR
block|,
DECL|enumerator|GIMP_PDB_PASS_THROUGH
name|GIMP_PDB_PASS_THROUGH
block|,
DECL|enumerator|GIMP_PDB_SUCCESS
name|GIMP_PDB_SUCCESS
block|,
DECL|enumerator|GIMP_PDB_CANCEL
name|GIMP_PDB_CANCEL
DECL|typedef|GimpPDBStatusType
block|}
name|GimpPDBStatusType
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f1f03
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f2003
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f2103
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f2203
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
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f2303
block|{
DECL|enumerator|GIMP_STACK_TRACE_NEVER
name|GIMP_STACK_TRACE_NEVER
block|,
DECL|enumerator|GIMP_STACK_TRACE_QUERY
name|GIMP_STACK_TRACE_QUERY
block|,
DECL|enumerator|GIMP_STACK_TRACE_ALWAYS
name|GIMP_STACK_TRACE_ALWAYS
DECL|typedef|GimpStackTraceMode
block|}
name|GimpStackTraceMode
typedef|;
typedef|typedef
enum|enum
DECL|enum|__anon28d8f04f2403
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
comment|/* This is for backwards compatibility. Don't use these for new plug-ins. */
ifndef|#
directive|ifndef
name|GIMP_DISABLE_COMPAT_CRUFT
DECL|typedef|GFillType
typedef|typedef
name|GimpFillType
name|GFillType
typedef|;
DECL|typedef|GImageType
typedef|typedef
name|GimpImageBaseType
name|GImageType
typedef|;
DECL|typedef|GDrawableType
typedef|typedef
name|GimpImageType
name|GDrawableType
typedef|;
DECL|typedef|GLayerMode
typedef|typedef
name|GimpLayerModeEffects
name|GLayerMode
typedef|;
DECL|typedef|GRunModeType
typedef|typedef
name|GimpRunModeType
name|GRunModeType
typedef|;
DECL|typedef|GOrientation
typedef|typedef
name|GimpOrientationType
name|GOrientation
typedef|;
DECL|typedef|GParamType
typedef|typedef
name|GimpPDBArgType
name|GParamType
typedef|;
DECL|typedef|GProcedureType
typedef|typedef
name|GimpPDBProcType
name|GProcedureType
typedef|;
DECL|typedef|GStatusType
typedef|typedef
name|GimpPDBStatusType
name|GStatusType
typedef|;
DECL|macro|PARAM_INT32
define|#
directive|define
name|PARAM_INT32
value|GIMP_PDB_INT32
DECL|macro|PARAM_INT16
define|#
directive|define
name|PARAM_INT16
value|GIMP_PDB_INT16
DECL|macro|PARAM_INT8
define|#
directive|define
name|PARAM_INT8
value|GIMP_PDB_INT8
DECL|macro|PARAM_FLOAT
define|#
directive|define
name|PARAM_FLOAT
value|GIMP_PDB_FLOAT
DECL|macro|PARAM_STRING
define|#
directive|define
name|PARAM_STRING
value|GIMP_PDB_STRING
DECL|macro|PARAM_INT32ARRAY
define|#
directive|define
name|PARAM_INT32ARRAY
value|GIMP_PDB_INT32ARRAY
DECL|macro|PARAM_INT16ARRAY
define|#
directive|define
name|PARAM_INT16ARRAY
value|GIMP_PDB_INT16ARRAY
DECL|macro|PARAM_INT8ARRAY
define|#
directive|define
name|PARAM_INT8ARRAY
value|GIMP_PDB_INT8ARRAY
DECL|macro|PARAM_FLOATARRAY
define|#
directive|define
name|PARAM_FLOATARRAY
value|GIMP_PDB_FLOATARRAY
DECL|macro|PARAM_STRINGARRAY
define|#
directive|define
name|PARAM_STRINGARRAY
value|GIMP_PDB_STRINGARRAY
DECL|macro|PARAM_COLOR
define|#
directive|define
name|PARAM_COLOR
value|GIMP_PDB_COLOR
DECL|macro|PARAM_REGION
define|#
directive|define
name|PARAM_REGION
value|GIMP_PDB_REGION
DECL|macro|PARAM_DISPLAY
define|#
directive|define
name|PARAM_DISPLAY
value|GIMP_PDB_DISPLAY
DECL|macro|PARAM_IMAGE
define|#
directive|define
name|PARAM_IMAGE
value|GIMP_PDB_IMAGE
DECL|macro|PARAM_LAYER
define|#
directive|define
name|PARAM_LAYER
value|GIMP_PDB_LAYER
DECL|macro|PARAM_CHANNEL
define|#
directive|define
name|PARAM_CHANNEL
value|GIMP_PDB_CHANNEL
DECL|macro|PARAM_DRAWABLE
define|#
directive|define
name|PARAM_DRAWABLE
value|GIMP_PDB_DRAWABLE
DECL|macro|PARAM_SELECTION
define|#
directive|define
name|PARAM_SELECTION
value|GIMP_PDB_SELECTION
DECL|macro|PARAM_BOUNDARY
define|#
directive|define
name|PARAM_BOUNDARY
value|GIMP_PDB_BOUNDARY
DECL|macro|PARAM_PATH
define|#
directive|define
name|PARAM_PATH
value|GIMP_PDB_PATH
DECL|macro|PARAM_PARASITE
define|#
directive|define
name|PARAM_PARASITE
value|GIMP_PDB_PARASITE
DECL|macro|PARAM_STATUS
define|#
directive|define
name|PARAM_STATUS
value|GIMP_PDB_STATUS
DECL|macro|PARAM_END
define|#
directive|define
name|PARAM_END
value|GIMP_PDB_END
DECL|macro|STATUS_EXECUTION_ERROR
define|#
directive|define
name|STATUS_EXECUTION_ERROR
value|GIMP_PDB_EXECUTION_ERROR
DECL|macro|STATUS_CALLING_ERROR
define|#
directive|define
name|STATUS_CALLING_ERROR
value|GIMP_PDB_CALLING_ERROR
DECL|macro|STATUS_PASS_THROUGH
define|#
directive|define
name|STATUS_PASS_THROUGH
value|GIMP_PDB_PASS_THROUGH
DECL|macro|STATUS_SUCCESS
define|#
directive|define
name|STATUS_SUCCESS
value|GIMP_PDB_SUCCESS
DECL|macro|STATUS_CANCEL
define|#
directive|define
name|STATUS_CANCEL
value|GIMP_PDB_CANCEL
DECL|macro|PROC_INTERNAL
define|#
directive|define
name|PROC_INTERNAL
value|GIMP_INTERNAL
DECL|macro|PROC_PLUG_IN
define|#
directive|define
name|PROC_PLUG_IN
value|GIMP_PLUGIN
DECL|macro|PROC_EXTENSION
define|#
directive|define
name|PROC_EXTENSION
value|GIMP_EXTENSION
DECL|macro|PROC_TEMPORARY
define|#
directive|define
name|PROC_TEMPORARY
value|GIMP_TEMPORARY
DECL|macro|ORIENTATION_HORIZONTAL
define|#
directive|define
name|ORIENTATION_HORIZONTAL
value|GIMP_HORIZONTAL
DECL|macro|ORIENTATION_VERTICAL
define|#
directive|define
name|ORIENTATION_VERTICAL
value|GIMP_VERTICAL
DECL|macro|ORIENTATION_UNKNOWN
define|#
directive|define
name|ORIENTATION_UNKNOWN
value|GIMP_UNKNOWN
DECL|macro|FG_IMAGE_FILL
define|#
directive|define
name|FG_IMAGE_FILL
value|GIMP_FG_IMAGE_FILL
DECL|macro|BG_IMAGE_FILL
define|#
directive|define
name|BG_IMAGE_FILL
value|GIMP_BG_IMAGE_FILL
DECL|macro|WHITE_IMAGE_FILL
define|#
directive|define
name|WHITE_IMAGE_FILL
value|GIMP_WHITE_IMAGE_FILL
DECL|macro|TRANS_IMAGE_FILL
define|#
directive|define
name|TRANS_IMAGE_FILL
value|GIMP_TRANS_IMAGE_FILL
DECL|macro|NO_IMAGE_FILL
define|#
directive|define
name|NO_IMAGE_FILL
value|GIMP_NO_IMAGE_FILL
DECL|macro|RGB
define|#
directive|define
name|RGB
value|GIMP_RGB
DECL|macro|GRAY
define|#
directive|define
name|GRAY
value|GIMP_GRAY
DECL|macro|INDEXED
define|#
directive|define
name|INDEXED
value|GIMP_INDEXED
DECL|macro|RGB_IMAGE
define|#
directive|define
name|RGB_IMAGE
value|GIMP_RGB_IMAGE
DECL|macro|RGBA_IMAGE
define|#
directive|define
name|RGBA_IMAGE
value|GIMP_RGBA_IMAGE
DECL|macro|GRAY_IMAGE
define|#
directive|define
name|GRAY_IMAGE
value|GIMP_GRAY_IMAGE
DECL|macro|GRAYA_IMAGE
define|#
directive|define
name|GRAYA_IMAGE
value|GIMP_GRAYA_IMAGE
DECL|macro|INDEXED_IMAGE
define|#
directive|define
name|INDEXED_IMAGE
value|GIMP_INDEXED_IMAGE
DECL|macro|INDEXEDA_IMAGE
define|#
directive|define
name|INDEXEDA_IMAGE
value|GIMP_INDEXEDA_IMAGE
DECL|macro|NORMAL_MODE
define|#
directive|define
name|NORMAL_MODE
value|GIMP_NORMAL_MODE
DECL|macro|DISSOLVE_MODE
define|#
directive|define
name|DISSOLVE_MODE
value|GIMP_DISSOLVE_MODE
DECL|macro|BEHIND_MODE
define|#
directive|define
name|BEHIND_MODE
value|GIMP_BEHIND_MODE
DECL|macro|MULTIPLY_MODE
define|#
directive|define
name|MULTIPLY_MODE
value|GIMP_MULTIPLY_MODE
DECL|macro|SCREEN_MODE
define|#
directive|define
name|SCREEN_MODE
value|GIMP_SCREEN_MODE
DECL|macro|OVERLAY_MODE
define|#
directive|define
name|OVERLAY_MODE
value|GIMP_OVERLAY_MODE
DECL|macro|DIFFERENCE_MODE
define|#
directive|define
name|DIFFERENCE_MODE
value|GIMP_DIFFERENCE_MODE
DECL|macro|ADDITION_MODE
define|#
directive|define
name|ADDITION_MODE
value|GIMP_ADDITION_MODE
DECL|macro|SUBTRACT_MODE
define|#
directive|define
name|SUBTRACT_MODE
value|GIMP_SUBTRACT_MODE
DECL|macro|DARKEN_ONLY_MODE
define|#
directive|define
name|DARKEN_ONLY_MODE
value|GIMP_DARKEN_ONLY_MODE
DECL|macro|LIGHTEN_ONLY_MODE
define|#
directive|define
name|LIGHTEN_ONLY_MODE
value|GIMP_LIGHTEN_ONLY_MODE
DECL|macro|HUE_MODE
define|#
directive|define
name|HUE_MODE
value|GIMP_HUE_MODE
DECL|macro|SATURATION_MODE
define|#
directive|define
name|SATURATION_MODE
value|GIMP_SATURATION_MODE
DECL|macro|COLOR_MODE
define|#
directive|define
name|COLOR_MODE
value|GIMP_COLOR_MODE
DECL|macro|VALUE_MODE
define|#
directive|define
name|VALUE_MODE
value|GIMP_VALUE_MODE
DECL|macro|DIVIDE_MODE
define|#
directive|define
name|DIVIDE_MODE
value|GIMP_DIVIDE_MODE
DECL|macro|RUN_INTERACTIVE
define|#
directive|define
name|RUN_INTERACTIVE
value|GIMP_RUN_INTERACTIVE
DECL|macro|RUN_NONINTERACTIVE
define|#
directive|define
name|RUN_NONINTERACTIVE
value|GIMP_RUN_NONINTERACTIVE
DECL|macro|RUN_WITH_LAST_VALS
define|#
directive|define
name|RUN_WITH_LAST_VALS
value|GIMP_RUN_WITH_LAST_VALS
endif|#
directive|endif
comment|/* GIMP_DISABLE_COMPAT_CRUFT */
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ENUMS_H__ */
end_comment

end_unit

