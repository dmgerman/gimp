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
DECL|enum|__anon2900213a0103
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
DECL|enum|__anon2900213a0203
block|{
DECL|enumerator|GIMP_CONVERT_DITHER_NONE
name|GIMP_CONVERT_DITHER_NONE
block|,
DECL|enumerator|GIMP_CONVERT_DITHER_FS
name|GIMP_CONVERT_DITHER_FS
block|,
DECL|enumerator|GIMP_CONVERT_DITHER_FS_LOWBLEED
name|GIMP_CONVERT_DITHER_FS_LOWBLEED
block|,
DECL|enumerator|GIMP_CONVERT_DITHER_FIXED
name|GIMP_CONVERT_DITHER_FIXED
DECL|typedef|GimpConvertDitherType
block|}
name|GimpConvertDitherType
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
DECL|enum|__anon2900213a0303
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
block|,
DECL|enumerator|GIMP_HISTOGRAM_LUMINANCE
name|GIMP_HISTOGRAM_LUMINANCE
DECL|typedef|GimpHistogramChannel
block|}
name|GimpHistogramChannel
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_LAYER_COLOR_SPACE
define|#
directive|define
name|GIMP_TYPE_LAYER_COLOR_SPACE
value|(gimp_layer_color_space_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_color_space_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2900213a0403
block|{
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_AUTO
name|GIMP_LAYER_COLOR_SPACE_AUTO
block|,
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
name|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
block|,
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
name|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
DECL|typedef|GimpLayerColorSpace
block|}
name|GimpLayerColorSpace
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_LAYER_COMPOSITE_MODE
define|#
directive|define
name|GIMP_TYPE_LAYER_COMPOSITE_MODE
value|(gimp_layer_composite_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_composite_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2900213a0503
block|{
DECL|enumerator|GIMP_LAYER_COMPOSITE_AUTO
name|GIMP_LAYER_COMPOSITE_AUTO
block|,
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_OVER
name|GIMP_LAYER_COMPOSITE_SRC_OVER
block|,
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_ATOP
name|GIMP_LAYER_COMPOSITE_SRC_ATOP
block|,
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_IN
name|GIMP_LAYER_COMPOSITE_SRC_IN
block|,
DECL|enumerator|GIMP_LAYER_COMPOSITE_DST_ATOP
name|GIMP_LAYER_COMPOSITE_DST_ATOP
DECL|typedef|GimpLayerCompositeMode
block|}
name|GimpLayerCompositeMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_LAYER_MODE
define|#
directive|define
name|GIMP_TYPE_LAYER_MODE
value|(gimp_layer_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2900213a0603
block|{
DECL|enumerator|GIMP_LAYER_MODE_NORMAL_LEGACY
name|GIMP_LAYER_MODE_NORMAL_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_DISSOLVE
name|GIMP_LAYER_MODE_DISSOLVE
block|,
DECL|enumerator|GIMP_LAYER_MODE_BEHIND_LEGACY
name|GIMP_LAYER_MODE_BEHIND_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_MULTIPLY_LEGACY
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_SCREEN_LEGACY
name|GIMP_LAYER_MODE_SCREEN_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_OVERLAY_LEGACY
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_ADDITION_LEGACY
name|GIMP_LAYER_MODE_ADDITION_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_SUBTRACT_LEGACY
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSV_HUE_LEGACY
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSL_COLOR_LEGACY
name|GIMP_LAYER_MODE_HSL_COLOR_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_DIVIDE_LEGACY
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_DODGE_LEGACY
name|GIMP_LAYER_MODE_DODGE_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_BURN_LEGACY
name|GIMP_LAYER_MODE_BURN_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_COLOR_ERASE_LEGACY
name|GIMP_LAYER_MODE_COLOR_ERASE_LEGACY
block|,
DECL|enumerator|GIMP_LAYER_MODE_OVERLAY
name|GIMP_LAYER_MODE_OVERLAY
block|,
DECL|enumerator|GIMP_LAYER_MODE_LCH_HUE
name|GIMP_LAYER_MODE_LCH_HUE
block|,
DECL|enumerator|GIMP_LAYER_MODE_LCH_CHROMA
name|GIMP_LAYER_MODE_LCH_CHROMA
block|,
DECL|enumerator|GIMP_LAYER_MODE_LCH_COLOR
name|GIMP_LAYER_MODE_LCH_COLOR
block|,
DECL|enumerator|GIMP_LAYER_MODE_LCH_LIGHTNESS
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
block|,
DECL|enumerator|GIMP_LAYER_MODE_NORMAL
name|GIMP_LAYER_MODE_NORMAL
block|,
DECL|enumerator|GIMP_LAYER_MODE_BEHIND
name|GIMP_LAYER_MODE_BEHIND
block|,
DECL|enumerator|GIMP_LAYER_MODE_MULTIPLY
name|GIMP_LAYER_MODE_MULTIPLY
block|,
DECL|enumerator|GIMP_LAYER_MODE_SCREEN
name|GIMP_LAYER_MODE_SCREEN
block|,
DECL|enumerator|GIMP_LAYER_MODE_DIFFERENCE
name|GIMP_LAYER_MODE_DIFFERENCE
block|,
DECL|enumerator|GIMP_LAYER_MODE_ADDITION
name|GIMP_LAYER_MODE_ADDITION
block|,
DECL|enumerator|GIMP_LAYER_MODE_SUBTRACT
name|GIMP_LAYER_MODE_SUBTRACT
block|,
DECL|enumerator|GIMP_LAYER_MODE_DARKEN_ONLY
name|GIMP_LAYER_MODE_DARKEN_ONLY
block|,
DECL|enumerator|GIMP_LAYER_MODE_LIGHTEN_ONLY
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSV_HUE
name|GIMP_LAYER_MODE_HSV_HUE
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSV_SATURATION
name|GIMP_LAYER_MODE_HSV_SATURATION
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSL_COLOR
name|GIMP_LAYER_MODE_HSL_COLOR
block|,
DECL|enumerator|GIMP_LAYER_MODE_HSV_VALUE
name|GIMP_LAYER_MODE_HSV_VALUE
block|,
DECL|enumerator|GIMP_LAYER_MODE_DIVIDE
name|GIMP_LAYER_MODE_DIVIDE
block|,
DECL|enumerator|GIMP_LAYER_MODE_DODGE
name|GIMP_LAYER_MODE_DODGE
block|,
DECL|enumerator|GIMP_LAYER_MODE_BURN
name|GIMP_LAYER_MODE_BURN
block|,
DECL|enumerator|GIMP_LAYER_MODE_HARDLIGHT
name|GIMP_LAYER_MODE_HARDLIGHT
block|,
DECL|enumerator|GIMP_LAYER_MODE_SOFTLIGHT
name|GIMP_LAYER_MODE_SOFTLIGHT
block|,
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_EXTRACT
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
block|,
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_MERGE
name|GIMP_LAYER_MODE_GRAIN_MERGE
block|,
DECL|enumerator|GIMP_LAYER_MODE_VIVID_LIGHT
name|GIMP_LAYER_MODE_VIVID_LIGHT
block|,
DECL|enumerator|GIMP_LAYER_MODE_PIN_LIGHT
name|GIMP_LAYER_MODE_PIN_LIGHT
block|,
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_LIGHT
name|GIMP_LAYER_MODE_LINEAR_LIGHT
block|,
DECL|enumerator|GIMP_LAYER_MODE_HARD_MIX
name|GIMP_LAYER_MODE_HARD_MIX
block|,
DECL|enumerator|GIMP_LAYER_MODE_EXCLUSION
name|GIMP_LAYER_MODE_EXCLUSION
block|,
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_BURN
name|GIMP_LAYER_MODE_LINEAR_BURN
block|,
DECL|enumerator|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
name|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
block|,
DECL|enumerator|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
name|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
block|,
DECL|enumerator|GIMP_LAYER_MODE_LUMINANCE
name|GIMP_LAYER_MODE_LUMINANCE
block|,
DECL|enumerator|GIMP_LAYER_MODE_COLOR_ERASE
name|GIMP_LAYER_MODE_COLOR_ERASE
block|,
DECL|enumerator|GIMP_LAYER_MODE_ERASE
name|GIMP_LAYER_MODE_ERASE
block|,
DECL|enumerator|GIMP_LAYER_MODE_MERGE
name|GIMP_LAYER_MODE_MERGE
block|,
DECL|enumerator|GIMP_LAYER_MODE_SPLIT
name|GIMP_LAYER_MODE_SPLIT
DECL|typedef|GimpLayerMode
block|}
name|GimpLayerMode
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

