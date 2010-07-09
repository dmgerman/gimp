begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_decl_stmt
name|G_BEGIN_DECLS
DECL|macro|GIMP_TYPE_BRUSH_APPLICATION_MODE
define|#
directive|define
name|GIMP_TYPE_BRUSH_APPLICATION_MODE
value|(gimp_brush_application_mode_get_type ())
name|GType
name|gimp_brush_application_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60103
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

begin_define
DECL|macro|GIMP_TYPE_BRUSH_GENERATED_SHAPE
define|#
directive|define
name|GIMP_TYPE_BRUSH_GENERATED_SHAPE
value|(gimp_brush_generated_shape_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_brush_generated_shape_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60203
block|{
DECL|enumerator|GIMP_BRUSH_GENERATED_CIRCLE
name|GIMP_BRUSH_GENERATED_CIRCLE
block|,
DECL|enumerator|GIMP_BRUSH_GENERATED_SQUARE
name|GIMP_BRUSH_GENERATED_SQUARE
block|,
DECL|enumerator|GIMP_BRUSH_GENERATED_DIAMOND
name|GIMP_BRUSH_GENERATED_DIAMOND
DECL|typedef|GimpBrushGeneratedShape
block|}
name|GimpBrushGeneratedShape
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONVERT_DITHER_TYPE
define|#
directive|define
name|GIMP_TYPE_CONVERT_DITHER_TYPE
value|(gimp_convert_dither_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convert_dither_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60303
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

begin_define
DECL|macro|GIMP_TYPE_CONVERT_PALETTE_TYPE
define|#
directive|define
name|GIMP_TYPE_CONVERT_PALETTE_TYPE
value|(gimp_convert_palette_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convert_palette_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60403
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

begin_define
DECL|macro|GIMP_TYPE_CONVOLUTION_TYPE
define|#
directive|define
name|GIMP_TYPE_CONVOLUTION_TYPE
value|(gimp_convolution_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convolution_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60503
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

begin_define
DECL|macro|GIMP_TYPE_CONVOLVE_TYPE
define|#
directive|define
name|GIMP_TYPE_CONVOLVE_TYPE
value|(gimp_convolve_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convolve_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60603
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

begin_define
DECL|macro|GIMP_TYPE_FILL_TYPE
define|#
directive|define
name|GIMP_TYPE_FILL_TYPE
value|(gimp_fill_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_fill_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60703
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

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_SEGMENT_COLOR
define|#
directive|define
name|GIMP_TYPE_GRADIENT_SEGMENT_COLOR
value|(gimp_gradient_segment_color_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_segment_color_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60803
block|{
DECL|enumerator|GIMP_GRADIENT_SEGMENT_RGB
name|GIMP_GRADIENT_SEGMENT_RGB
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_HSV_CCW
name|GIMP_GRADIENT_SEGMENT_HSV_CCW
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_HSV_CW
name|GIMP_GRADIENT_SEGMENT_HSV_CW
DECL|typedef|GimpGradientSegmentColor
block|}
name|GimpGradientSegmentColor
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_SEGMENT_TYPE
define|#
directive|define
name|GIMP_TYPE_GRADIENT_SEGMENT_TYPE
value|(gimp_gradient_segment_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_segment_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60903
block|{
DECL|enumerator|GIMP_GRADIENT_SEGMENT_LINEAR
name|GIMP_GRADIENT_SEGMENT_LINEAR
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_CURVED
name|GIMP_GRADIENT_SEGMENT_CURVED
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SINE
name|GIMP_GRADIENT_SEGMENT_SINE
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
name|GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING
name|GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING
DECL|typedef|GimpGradientSegmentType
block|}
name|GimpGradientSegmentType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM_CHANNEL
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM_CHANNEL
value|(gimp_histogram_channel_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_histogram_channel_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60a03
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

begin_define
DECL|macro|GIMP_TYPE_HUE_RANGE
define|#
directive|define
name|GIMP_TYPE_HUE_RANGE
value|(gimp_hue_range_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_hue_range_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60b03
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

begin_define
DECL|macro|GIMP_TYPE_LAYER_MODE_EFFECTS
define|#
directive|define
name|GIMP_TYPE_LAYER_MODE_EFFECTS
value|(gimp_layer_mode_effects_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_mode_effects_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60c03
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

begin_define
DECL|macro|GIMP_TYPE_MASK_APPLY_MODE
define|#
directive|define
name|GIMP_TYPE_MASK_APPLY_MODE
value|(gimp_mask_apply_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_mask_apply_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60d03
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

begin_define
DECL|macro|GIMP_TYPE_MERGE_TYPE
define|#
directive|define
name|GIMP_TYPE_MERGE_TYPE
value|(gimp_merge_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_merge_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60e03
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

begin_define
DECL|macro|GIMP_TYPE_OFFSET_TYPE
define|#
directive|define
name|GIMP_TYPE_OFFSET_TYPE
value|(gimp_offset_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_offset_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d60f03
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

begin_define
DECL|macro|GIMP_TYPE_ORIENTATION_TYPE
define|#
directive|define
name|GIMP_TYPE_ORIENTATION_TYPE
value|(gimp_orientation_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_orientation_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d61003
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

begin_define
DECL|macro|GIMP_TYPE_ROTATION_TYPE
define|#
directive|define
name|GIMP_TYPE_ROTATION_TYPE
value|(gimp_rotation_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_rotation_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d61103
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

begin_define
DECL|macro|GIMP_TYPE_SELECT_CRITERION
define|#
directive|define
name|GIMP_TYPE_SELECT_CRITERION
value|(gimp_select_criterion_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_select_criterion_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ae9c1d61203
block|{
DECL|enumerator|GIMP_SELECT_CRITERION_COMPOSITE
name|GIMP_SELECT_CRITERION_COMPOSITE
block|,
DECL|enumerator|GIMP_SELECT_CRITERION_R
name|GIMP_SELECT_CRITERION_R
block|,
DECL|enumerator|GIMP_SELECT_CRITERION_G
name|GIMP_SELECT_CRITERION_G
block|,
DECL|enumerator|GIMP_SELECT_CRITERION_B
name|GIMP_SELECT_CRITERION_B
block|,
DECL|enumerator|GIMP_SELECT_CRITERION_H
name|GIMP_SELECT_CRITERION_H
block|,
DECL|enumerator|GIMP_SELECT_CRITERION_S
name|GIMP_SELECT_CRITERION_S
block|,
DECL|enumerator|GIMP_SELECT_CRITERION_V
name|GIMP_SELECT_CRITERION_V
DECL|typedef|GimpSelectCriterion
block|}
name|GimpSelectCriterion
typedef|;
end_typedef

begin_function_decl
name|void
name|gimp_enums_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
modifier|*
name|gimp_enums_get_type_names
parameter_list|(
name|gint
modifier|*
name|n_type_names
parameter_list|)
function_decl|;
end_function_decl

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

