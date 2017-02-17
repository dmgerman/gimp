begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * operations-enums.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__OPERATIONS_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__OPERATIONS_ENUMS_H__
define|#
directive|define
name|__OPERATIONS_ENUMS_H__
end_define

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
comment|/*< pdb-skip>*/
DECL|enum|__anon27a9042b0103
block|{
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_AUTO
name|GIMP_LAYER_COLOR_SPACE_AUTO
block|,
comment|/*< desc="Auto">*/
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
name|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
block|,
comment|/*< desc="RGB (linear)">*/
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
name|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
block|,
comment|/*< desc="RGB (perceptual)">*/
DECL|enumerator|GIMP_LAYER_COLOR_SPACE_LAB
name|GIMP_LAYER_COLOR_SPACE_LAB
block|,
comment|/*< desc="LAB">*/
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
DECL|enum|__anon27a9042b0203
block|{
DECL|enumerator|GIMP_LAYER_COMPOSITE_AUTO
name|GIMP_LAYER_COMPOSITE_AUTO
block|,
comment|/*< desc="Auto">*/
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_OVER
name|GIMP_LAYER_COMPOSITE_SRC_OVER
block|,
comment|/*< desc="Source over">*/
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_ATOP
name|GIMP_LAYER_COMPOSITE_SRC_ATOP
block|,
comment|/*< desc="Source atop">*/
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_IN
name|GIMP_LAYER_COMPOSITE_SRC_IN
block|,
comment|/*< desc="Source in">*/
DECL|enumerator|GIMP_LAYER_COMPOSITE_DST_ATOP
name|GIMP_LAYER_COMPOSITE_DST_ATOP
comment|/*< desc="Destination atop">*/
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
DECL|enum|__anon27a9042b0303
block|{
comment|/*  Modes that exist since ancient times  */
DECL|enumerator|GIMP_LAYER_MODE_NORMAL
name|GIMP_LAYER_MODE_NORMAL
block|,
comment|/*< desc="Normal">*/
DECL|enumerator|GIMP_LAYER_MODE_DISSOLVE
name|GIMP_LAYER_MODE_DISSOLVE
block|,
comment|/*< desc="Dissolve">*/
DECL|enumerator|GIMP_LAYER_MODE_BEHIND
name|GIMP_LAYER_MODE_BEHIND
block|,
comment|/*< desc="Behind">*/
DECL|enumerator|GIMP_LAYER_MODE_MULTIPLY_LEGACY
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
block|,
comment|/*< desc="Multiply (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_SCREEN_LEGACY
name|GIMP_LAYER_MODE_SCREEN_LEGACY
block|,
comment|/*< desc="Screen (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_OVERLAY_LEGACY
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
block|,
comment|/*< desc="Old broken Overlay">*/
DECL|enumerator|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
block|,
comment|/*< desc="Difference (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_ADDITION_LEGACY
name|GIMP_LAYER_MODE_ADDITION_LEGACY
block|,
comment|/*< desc="Addition (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_SUBTRACT_LEGACY
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
block|,
comment|/*< desc="Subtract (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
block|,
comment|/*< desc="Darken only (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
block|,
comment|/*< desc="Lighten only (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_HUE_LEGACY
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
block|,
comment|/*< desc="Hue (HSV) (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
block|,
comment|/*< desc="Saturation (HSV) (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
block|,
comment|/*< desc="Color (HSV) (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
block|,
comment|/*< desc="Value (HSV) (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_DIVIDE_LEGACY
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
block|,
comment|/*< desc="Divide (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_DODGE_LEGACY
name|GIMP_LAYER_MODE_DODGE_LEGACY
block|,
comment|/*< desc="Dodge (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_BURN_LEGACY
name|GIMP_LAYER_MODE_BURN_LEGACY
block|,
comment|/*< desc="Burn (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
block|,
comment|/*< desc="Hard light (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
block|,
comment|/*< desc="Soft light (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
block|,
comment|/*< desc="Grain extract (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
block|,
comment|/*< desc="Grain merge (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_COLOR_ERASE
name|GIMP_LAYER_MODE_COLOR_ERASE
block|,
comment|/*< desc="Color erase">*/
comment|/*  Since 2.8  */
DECL|enumerator|GIMP_LAYER_MODE_OVERLAY
name|GIMP_LAYER_MODE_OVERLAY
block|,
comment|/*< desc="Overlay">*/
DECL|enumerator|GIMP_LAYER_MODE_LCH_HUE
name|GIMP_LAYER_MODE_LCH_HUE
block|,
comment|/*< desc="Hue (LCH)">*/
DECL|enumerator|GIMP_LAYER_MODE_LCH_CHROMA
name|GIMP_LAYER_MODE_LCH_CHROMA
block|,
comment|/*< desc="Chroma (LCH)">*/
DECL|enumerator|GIMP_LAYER_MODE_LCH_COLOR
name|GIMP_LAYER_MODE_LCH_COLOR
block|,
comment|/*< desc="Color (LCH)">*/
DECL|enumerator|GIMP_LAYER_MODE_LCH_LIGHTNESS
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
block|,
comment|/*< desc="Lightness (LCH)">*/
comment|/*  Since 2.10  */
DECL|enumerator|GIMP_LAYER_MODE_NORMAL_LINEAR
name|GIMP_LAYER_MODE_NORMAL_LINEAR
block|,
comment|/*< desc="Normal (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_BEHIND_LINEAR
name|GIMP_LAYER_MODE_BEHIND_LINEAR
block|,
comment|/*< desc="Behind (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_MULTIPLY
name|GIMP_LAYER_MODE_MULTIPLY
block|,
comment|/*< desc="Multiply">*/
DECL|enumerator|GIMP_LAYER_MODE_MULTIPLY_LINEAR
name|GIMP_LAYER_MODE_MULTIPLY_LINEAR
block|,
comment|/*< desc="Multiply (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_SCREEN
name|GIMP_LAYER_MODE_SCREEN
block|,
comment|/*< desc="Screen">*/
DECL|enumerator|GIMP_LAYER_MODE_SCREEN_LINEAR
name|GIMP_LAYER_MODE_SCREEN_LINEAR
block|,
comment|/*< desc="Screen (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_OVERLAY_LINEAR
name|GIMP_LAYER_MODE_OVERLAY_LINEAR
block|,
comment|/*< desc="Overlay (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_DIFFERENCE
name|GIMP_LAYER_MODE_DIFFERENCE
block|,
comment|/*< desc="Difference">*/
DECL|enumerator|GIMP_LAYER_MODE_DIFFERENCE_LINEAR
name|GIMP_LAYER_MODE_DIFFERENCE_LINEAR
block|,
comment|/*< desc="Difference (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_ADDITION
name|GIMP_LAYER_MODE_ADDITION
block|,
comment|/*< desc="Addition">*/
DECL|enumerator|GIMP_LAYER_MODE_ADDITION_LINEAR
name|GIMP_LAYER_MODE_ADDITION_LINEAR
block|,
comment|/*< desc="Addition (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_SUBTRACT
name|GIMP_LAYER_MODE_SUBTRACT
block|,
comment|/*< desc="Subtract">*/
DECL|enumerator|GIMP_LAYER_MODE_SUBTRACT_LINEAR
name|GIMP_LAYER_MODE_SUBTRACT_LINEAR
block|,
comment|/*< desc="Subtract (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_DARKEN_ONLY
name|GIMP_LAYER_MODE_DARKEN_ONLY
block|,
comment|/*< desc="Darken only">*/
DECL|enumerator|GIMP_LAYER_MODE_LIGHTEN_ONLY
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
block|,
comment|/*< desc="Lighten only">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_HUE
name|GIMP_LAYER_MODE_HSV_HUE
block|,
comment|/*< desc="Hue (HSV)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_SATURATION
name|GIMP_LAYER_MODE_HSV_SATURATION
block|,
comment|/*< desc="Saturation (HSV)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_COLOR
name|GIMP_LAYER_MODE_HSV_COLOR
block|,
comment|/*< desc="Color (HSV)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_VALUE
name|GIMP_LAYER_MODE_HSV_VALUE
block|,
comment|/*< desc="Value (HSV)">*/
DECL|enumerator|GIMP_LAYER_MODE_DIVIDE
name|GIMP_LAYER_MODE_DIVIDE
block|,
comment|/*< desc="Divide">*/
DECL|enumerator|GIMP_LAYER_MODE_DIVIDE_LINEAR
name|GIMP_LAYER_MODE_DIVIDE_LINEAR
block|,
comment|/*< desc="Divide (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_DODGE
name|GIMP_LAYER_MODE_DODGE
block|,
comment|/*< desc="Dodge">*/
DECL|enumerator|GIMP_LAYER_MODE_DODGE_LINEAR
name|GIMP_LAYER_MODE_DODGE_LINEAR
block|,
comment|/*< desc="Dodge (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_BURN
name|GIMP_LAYER_MODE_BURN
block|,
comment|/*< desc="Burn">*/
DECL|enumerator|GIMP_LAYER_MODE_BURN_LINEAR
name|GIMP_LAYER_MODE_BURN_LINEAR
block|,
comment|/*< desc="Burn (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_HARDLIGHT
name|GIMP_LAYER_MODE_HARDLIGHT
block|,
comment|/*< desc="Hard light">*/
DECL|enumerator|GIMP_LAYER_MODE_HARDLIGHT_LINEAR
name|GIMP_LAYER_MODE_HARDLIGHT_LINEAR
block|,
comment|/*< desc="Hard light (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_SOFTLIGHT
name|GIMP_LAYER_MODE_SOFTLIGHT
block|,
comment|/*< desc="Soft light">*/
DECL|enumerator|GIMP_LAYER_MODE_SOFTLIGHT_LINEAR
name|GIMP_LAYER_MODE_SOFTLIGHT_LINEAR
block|,
comment|/*< desc="Soft light (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_EXTRACT
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
block|,
comment|/*< desc="Grain extract">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_EXTRACT_LINEAR
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LINEAR
block|,
comment|/*< desc="Grain extract (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_MERGE
name|GIMP_LAYER_MODE_GRAIN_MERGE
block|,
comment|/*< desc="Grain merge">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_MERGE_LINEAR
name|GIMP_LAYER_MODE_GRAIN_MERGE_LINEAR
block|,
comment|/*< desc="Grain merge (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_VIVID_LIGHT
name|GIMP_LAYER_MODE_VIVID_LIGHT
block|,
comment|/*< desc="Vivid light">*/
DECL|enumerator|GIMP_LAYER_MODE_VIVID_LIGHT_LINEAR
name|GIMP_LAYER_MODE_VIVID_LIGHT_LINEAR
block|,
comment|/*< desc="Vivid light (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_PIN_LIGHT
name|GIMP_LAYER_MODE_PIN_LIGHT
block|,
comment|/*< desc="Pin light">*/
DECL|enumerator|GIMP_LAYER_MODE_PIN_LIGHT_LINEAR
name|GIMP_LAYER_MODE_PIN_LIGHT_LINEAR
block|,
comment|/*< desc="Pin light (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_LIGHT
name|GIMP_LAYER_MODE_LINEAR_LIGHT
block|,
comment|/*< desc="Linear light">*/
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_LIGHT_LINEAR
name|GIMP_LAYER_MODE_LINEAR_LIGHT_LINEAR
block|,
comment|/*< desc="Linear light (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_HARD_MIX
name|GIMP_LAYER_MODE_HARD_MIX
block|,
comment|/*< desc="Hard mix">*/
DECL|enumerator|GIMP_LAYER_MODE_HARD_MIX_LINEAR
name|GIMP_LAYER_MODE_HARD_MIX_LINEAR
block|,
comment|/*< desc="Hard mix (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_EXCLUSION
name|GIMP_LAYER_MODE_EXCLUSION
block|,
comment|/*< desc="Exclusion">*/
DECL|enumerator|GIMP_LAYER_MODE_EXCLUSION_LINEAR
name|GIMP_LAYER_MODE_EXCLUSION_LINEAR
block|,
comment|/*< desc="Exclusion (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_BURN
name|GIMP_LAYER_MODE_LINEAR_BURN
block|,
comment|/*< desc="Linear burn">*/
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_BURN_LINEAR
name|GIMP_LAYER_MODE_LINEAR_BURN_LINEAR
block|,
comment|/*< desc="Linear burn (linear)">*/
DECL|enumerator|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
name|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
block|,
comment|/*< desc="Luma darken only">*/
DECL|enumerator|GIMP_LAYER_MODE_LUMINANCE_DARKEN_ONLY
name|GIMP_LAYER_MODE_LUMINANCE_DARKEN_ONLY
block|,
comment|/*< desc="Luminance darken only">*/
DECL|enumerator|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
name|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
block|,
comment|/*< desc="Luma lighten only">*/
DECL|enumerator|GIMP_LAYER_MODE_LUMINANCE_LIGHTEN_ONLY
name|GIMP_LAYER_MODE_LUMINANCE_LIGHTEN_ONLY
block|,
comment|/*< desc="Luminance lighten only">*/
comment|/*  Internal modes, not available to the PDB, must be kept at the end  */
DECL|enumerator|GIMP_LAYER_MODE_ERASE
name|GIMP_LAYER_MODE_ERASE
block|,
comment|/*< pdb-skip, desc="Erase">*/
DECL|enumerator|GIMP_LAYER_MODE_REPLACE
name|GIMP_LAYER_MODE_REPLACE
block|,
comment|/*< pdb-skip, desc="Replace">*/
DECL|enumerator|GIMP_LAYER_MODE_ANTI_ERASE
name|GIMP_LAYER_MODE_ANTI_ERASE
comment|/*< pdb-skip, desc="Anti erase">*/
DECL|typedef|GimpLayerMode
block|}
name|GimpLayerMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_LAYER_MODE_GROUP
define|#
directive|define
name|GIMP_TYPE_LAYER_MODE_GROUP
value|(gimp_layer_mode_group_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_mode_group_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon27a9042b0403
block|{
DECL|enumerator|GIMP_LAYER_MODE_GROUP_DEFAULT
name|GIMP_LAYER_MODE_GROUP_DEFAULT
block|,
comment|/*< desc="Default">*/
DECL|enumerator|GIMP_LAYER_MODE_GROUP_LINEAR
name|GIMP_LAYER_MODE_GROUP_LINEAR
block|,
comment|/*< desc="Linear light">*/
DECL|enumerator|GIMP_LAYER_MODE_GROUP_PERCEPTUAL
name|GIMP_LAYER_MODE_GROUP_PERCEPTUAL
block|,
comment|/*< desc="Perceptual">*/
DECL|enumerator|GIMP_LAYER_MODE_GROUP_LEGACY
name|GIMP_LAYER_MODE_GROUP_LEGACY
block|,
comment|/*< desc="Legacy">*/
DECL|typedef|GimpLayerModeGroup
block|}
name|GimpLayerModeGroup
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_LAYER_MODE_CONTEXT
define|#
directive|define
name|GIMP_TYPE_LAYER_MODE_CONTEXT
value|(gimp_layer_mode_context_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_layer_mode_context_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon27a9042b0503
block|{
DECL|enumerator|GIMP_LAYER_MODE_CONTEXT_LAYER
name|GIMP_LAYER_MODE_CONTEXT_LAYER
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_LAYER_MODE_CONTEXT_GROUP
name|GIMP_LAYER_MODE_CONTEXT_GROUP
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_LAYER_MODE_CONTEXT_PAINT
name|GIMP_LAYER_MODE_CONTEXT_PAINT
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_LAYER_MODE_CONTEXT_FADE
name|GIMP_LAYER_MODE_CONTEXT_FADE
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_LAYER_MODE_CONTEXT_ALL
name|GIMP_LAYER_MODE_CONTEXT_ALL
init|=
operator|(
name|GIMP_LAYER_MODE_CONTEXT_LAYER
operator||
name|GIMP_LAYER_MODE_CONTEXT_GROUP
operator||
name|GIMP_LAYER_MODE_CONTEXT_PAINT
operator||
name|GIMP_LAYER_MODE_CONTEXT_FADE
operator|)
DECL|typedef|GimpLayerModeContext
block|}
name|GimpLayerModeContext
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon27a9042b0603
block|{
DECL|enumerator|GIMP_LAYER_MODE_AFFECT_NONE
name|GIMP_LAYER_MODE_AFFECT_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_LAYER_MODE_AFFECT_DST
name|GIMP_LAYER_MODE_AFFECT_DST
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_LAYER_MODE_AFFECT_SRC
name|GIMP_LAYER_MODE_AFFECT_SRC
init|=
literal|1
operator|<<
literal|1
DECL|typedef|GimpLayerModeAffectMask
block|}
name|GimpLayerModeAffectMask
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon27a9042b0703
block|{
DECL|enumerator|GIMP_LAYER_MODE_FLAG_LEGACY
name|GIMP_LAYER_MODE_FLAG_LEGACY
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_WANTS_LINEAR_DATA
name|GIMP_LAYER_MODE_FLAG_WANTS_LINEAR_DATA
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_BLEND_SPACE_IMMUTABLE
name|GIMP_LAYER_MODE_FLAG_BLEND_SPACE_IMMUTABLE
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_COMPOSITE_SPACE_IMMUTABLE
name|GIMP_LAYER_MODE_FLAG_COMPOSITE_SPACE_IMMUTABLE
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_COMPOSITE_MODE_IMMUTABLE
name|GIMP_LAYER_MODE_FLAG_COMPOSITE_MODE_IMMUTABLE
init|=
literal|1
operator|<<
literal|4
block|, }
DECL|typedef|GimpLayerModeFlags
name|GimpLayerModeFlags
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __OPERATIONS_ENUMS_H__ */
end_comment

end_unit

