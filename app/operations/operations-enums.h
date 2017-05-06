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
DECL|enum|__anon2ad75d9e0103
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
comment|/*< desc="LAB", pdb-skip>*/
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
DECL|enum|__anon2ad75d9e0203
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
DECL|enumerator|GIMP_LAYER_COMPOSITE_DST_ATOP
name|GIMP_LAYER_COMPOSITE_DST_ATOP
block|,
comment|/*< desc="Destination atop">*/
DECL|enumerator|GIMP_LAYER_COMPOSITE_SRC_IN
name|GIMP_LAYER_COMPOSITE_SRC_IN
comment|/*< desc="Source in">*/
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
DECL|enum|__anon2ad75d9e0303
block|{
comment|/*  Modes that exist since ancient times  */
DECL|enumerator|GIMP_LAYER_MODE_NORMAL_LEGACY
name|GIMP_LAYER_MODE_NORMAL_LEGACY
block|,
comment|/*< desc="Normal (legacy)">*/
DECL|enumerator|GIMP_LAYER_MODE_DISSOLVE
name|GIMP_LAYER_MODE_DISSOLVE
block|,
comment|/*< desc="Dissolve">*/
DECL|enumerator|GIMP_LAYER_MODE_BEHIND_LEGACY
name|GIMP_LAYER_MODE_BEHIND_LEGACY
block|,
comment|/*< desc="Behind (legacy)">*/
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
DECL|enumerator|GIMP_LAYER_MODE_HSL_COLOR_LEGACY
name|GIMP_LAYER_MODE_HSL_COLOR_LEGACY
block|,
comment|/*< desc="Color (HSL) (legacy)">*/
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
comment|/*  Since 2.8 (XCF version 2)  */
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
DECL|enumerator|GIMP_LAYER_MODE_COLOR_ERASE_LEGACY
name|GIMP_LAYER_MODE_COLOR_ERASE_LEGACY
block|,
comment|/*< desc="Color erase (legacy)">*/
comment|/*  Since 2.10 (XCF version 9) */
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
comment|/*  Since 2.10 (XCF version 10)  */
DECL|enumerator|GIMP_LAYER_MODE_NORMAL
name|GIMP_LAYER_MODE_NORMAL
block|,
comment|/*< desc="Normal">*/
DECL|enumerator|GIMP_LAYER_MODE_BEHIND
name|GIMP_LAYER_MODE_BEHIND
block|,
comment|/*< desc="Behind">*/
DECL|enumerator|GIMP_LAYER_MODE_MULTIPLY
name|GIMP_LAYER_MODE_MULTIPLY
block|,
comment|/*< desc="Multiply">*/
DECL|enumerator|GIMP_LAYER_MODE_SCREEN
name|GIMP_LAYER_MODE_SCREEN
block|,
comment|/*< desc="Screen">*/
DECL|enumerator|GIMP_LAYER_MODE_DIFFERENCE
name|GIMP_LAYER_MODE_DIFFERENCE
block|,
comment|/*< desc="Difference">*/
DECL|enumerator|GIMP_LAYER_MODE_ADDITION
name|GIMP_LAYER_MODE_ADDITION
block|,
comment|/*< desc="Addition">*/
DECL|enumerator|GIMP_LAYER_MODE_SUBTRACT
name|GIMP_LAYER_MODE_SUBTRACT
block|,
comment|/*< desc="Subtract">*/
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
DECL|enumerator|GIMP_LAYER_MODE_HSL_COLOR
name|GIMP_LAYER_MODE_HSL_COLOR
block|,
comment|/*< desc="Color (HSL)">*/
DECL|enumerator|GIMP_LAYER_MODE_HSV_VALUE
name|GIMP_LAYER_MODE_HSV_VALUE
block|,
comment|/*< desc="Value (HSV)">*/
DECL|enumerator|GIMP_LAYER_MODE_DIVIDE
name|GIMP_LAYER_MODE_DIVIDE
block|,
comment|/*< desc="Divide">*/
DECL|enumerator|GIMP_LAYER_MODE_DODGE
name|GIMP_LAYER_MODE_DODGE
block|,
comment|/*< desc="Dodge">*/
DECL|enumerator|GIMP_LAYER_MODE_BURN
name|GIMP_LAYER_MODE_BURN
block|,
comment|/*< desc="Burn">*/
DECL|enumerator|GIMP_LAYER_MODE_HARDLIGHT
name|GIMP_LAYER_MODE_HARDLIGHT
block|,
comment|/*< desc="Hard light">*/
DECL|enumerator|GIMP_LAYER_MODE_SOFTLIGHT
name|GIMP_LAYER_MODE_SOFTLIGHT
block|,
comment|/*< desc="Soft light">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_EXTRACT
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
block|,
comment|/*< desc="Grain extract">*/
DECL|enumerator|GIMP_LAYER_MODE_GRAIN_MERGE
name|GIMP_LAYER_MODE_GRAIN_MERGE
block|,
comment|/*< desc="Grain merge">*/
DECL|enumerator|GIMP_LAYER_MODE_VIVID_LIGHT
name|GIMP_LAYER_MODE_VIVID_LIGHT
block|,
comment|/*< desc="Vivid light">*/
DECL|enumerator|GIMP_LAYER_MODE_PIN_LIGHT
name|GIMP_LAYER_MODE_PIN_LIGHT
block|,
comment|/*< desc="Pin light">*/
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_LIGHT
name|GIMP_LAYER_MODE_LINEAR_LIGHT
block|,
comment|/*< desc="Linear light">*/
DECL|enumerator|GIMP_LAYER_MODE_HARD_MIX
name|GIMP_LAYER_MODE_HARD_MIX
block|,
comment|/*< desc="Hard mix">*/
DECL|enumerator|GIMP_LAYER_MODE_EXCLUSION
name|GIMP_LAYER_MODE_EXCLUSION
block|,
comment|/*< desc="Exclusion">*/
DECL|enumerator|GIMP_LAYER_MODE_LINEAR_BURN
name|GIMP_LAYER_MODE_LINEAR_BURN
block|,
comment|/*< desc="Linear burn">*/
DECL|enumerator|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
name|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
block|,
comment|/*< desc="Luma/Luminance darken only">*/
DECL|enumerator|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
name|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
block|,
comment|/*< desc="Luma/Luminance lighten only">*/
DECL|enumerator|GIMP_LAYER_MODE_LUMINANCE
name|GIMP_LAYER_MODE_LUMINANCE
block|,
comment|/*< desc="Luminance">*/
DECL|enumerator|GIMP_LAYER_MODE_COLOR_ERASE
name|GIMP_LAYER_MODE_COLOR_ERASE
block|,
comment|/*< desc="Color erase">*/
DECL|enumerator|GIMP_LAYER_MODE_ERASE
name|GIMP_LAYER_MODE_ERASE
block|,
comment|/*< desc="Erase">*/
DECL|enumerator|GIMP_LAYER_MODE_MERGE
name|GIMP_LAYER_MODE_MERGE
block|,
comment|/*< desc="Merge">*/
DECL|enumerator|GIMP_LAYER_MODE_SPLIT
name|GIMP_LAYER_MODE_SPLIT
block|,
comment|/*< desc="Split">*/
comment|/*  Internal modes, not available to the PDB, must be kept at the end  */
DECL|enumerator|GIMP_LAYER_MODE_REPLACE
name|GIMP_LAYER_MODE_REPLACE
block|,
comment|/*< pdb-skip, desc="Replace">*/
DECL|enumerator|GIMP_LAYER_MODE_ANTI_ERASE
name|GIMP_LAYER_MODE_ANTI_ERASE
block|,
comment|/*< pdb-skip, desc="Anti erase">*/
comment|/*  Layer mode menu separator  */
DECL|enumerator|GIMP_LAYER_MODE_SEPARATOR
name|GIMP_LAYER_MODE_SEPARATOR
init|=
operator|-
literal|1
comment|/*< pdb-skip, skip>*/
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
DECL|enum|__anon2ad75d9e0403
block|{
DECL|enumerator|GIMP_LAYER_MODE_GROUP_DEFAULT
name|GIMP_LAYER_MODE_GROUP_DEFAULT
block|,
comment|/*< desc="Default">*/
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
DECL|enum|__anon2ad75d9e0503
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
DECL|enum|__anon2ad75d9e0603
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
DECL|enum|__anon2ad75d9e0703
block|{
DECL|enumerator|GIMP_LAYER_MODE_FLAG_LEGACY
name|GIMP_LAYER_MODE_FLAG_LEGACY
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_BLEND_SPACE_IMMUTABLE
name|GIMP_LAYER_MODE_FLAG_BLEND_SPACE_IMMUTABLE
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_COMPOSITE_SPACE_IMMUTABLE
name|GIMP_LAYER_MODE_FLAG_COMPOSITE_SPACE_IMMUTABLE
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_COMPOSITE_MODE_IMMUTABLE
name|GIMP_LAYER_MODE_FLAG_COMPOSITE_MODE_IMMUTABLE
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_LAYER_MODE_FLAG_SUBTRACTIVE
name|GIMP_LAYER_MODE_FLAG_SUBTRACTIVE
init|=
literal|1
operator|<<
literal|4
DECL|typedef|GimpLayerModeFlags
block|}
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

