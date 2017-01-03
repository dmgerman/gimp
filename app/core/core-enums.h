begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CORE_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__CORE_ENUMS_H__
define|#
directive|define
name|__CORE_ENUMS_H__
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|This file is parsed by two scripts, enumgen.pl in tools/pdbgen,    and gimp-mkenums. All enums that are not marked with
comment|/*< pdb-skip>*/
end_comment

begin_comment
unit|are exported to libgimp and the PDB. Enums that are    not marked with
comment|/*< skip>*/
end_comment

begin_comment
unit|are registered with the GType system.    If you want the enum to be skipped by both scripts, you have to use
comment|/*< pdb-skip, skip>*/
end_comment

begin_endif
unit|.     The same syntax applies to enum values.
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * these enums are registered with the type system  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COMPONENT_MASK
define|#
directive|define
name|GIMP_TYPE_COMPONENT_MASK
value|(gimp_component_mask_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_component_mask_get_type
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
DECL|enum|__anon2b8bc5960103
block|{
DECL|enumerator|GIMP_COMPONENT_MASK_RED
name|GIMP_COMPONENT_MASK_RED
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_COMPONENT_MASK_GREEN
name|GIMP_COMPONENT_MASK_GREEN
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_COMPONENT_MASK_BLUE
name|GIMP_COMPONENT_MASK_BLUE
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_COMPONENT_MASK_ALPHA
name|GIMP_COMPONENT_MASK_ALPHA
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_COMPONENT_MASK_ALL
name|GIMP_COMPONENT_MASK_ALL
init|=
operator|(
name|GIMP_COMPONENT_MASK_RED
operator||
name|GIMP_COMPONENT_MASK_GREEN
operator||
name|GIMP_COMPONENT_MASK_BLUE
operator||
name|GIMP_COMPONENT_MASK_ALPHA
operator|)
DECL|typedef|GimpComponentMask
block|}
name|GimpComponentMask
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_POLICY
define|#
directive|define
name|GIMP_TYPE_CONTAINER_POLICY
value|(gimp_container_policy_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_container_policy_get_type
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
DECL|enum|__anon2b8bc5960203
block|{
DECL|enumerator|GIMP_CONTAINER_POLICY_STRONG
name|GIMP_CONTAINER_POLICY_STRONG
block|,
DECL|enumerator|GIMP_CONTAINER_POLICY_WEAK
name|GIMP_CONTAINER_POLICY_WEAK
DECL|typedef|GimpContainerPolicy
block|}
name|GimpContainerPolicy
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
DECL|enum|__anon2b8bc5960303
block|{
DECL|enumerator|GIMP_NO_DITHER
name|GIMP_NO_DITHER
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_FS_DITHER
name|GIMP_FS_DITHER
block|,
comment|/*< desc="Floyd-Steinberg (normal)">*/
DECL|enumerator|GIMP_FSLOWBLEED_DITHER
name|GIMP_FSLOWBLEED_DITHER
block|,
comment|/*< desc="Floyd-Steinberg (reduced color bleeding)">*/
DECL|enumerator|GIMP_FIXED_DITHER
name|GIMP_FIXED_DITHER
block|,
comment|/*< desc="Positioned">*/
DECL|enumerator|GIMP_NODESTRUCT_DITHER
name|GIMP_NODESTRUCT_DITHER
comment|/*< pdb-skip, skip>*/
DECL|typedef|GimpConvertDitherType
block|}
name|GimpConvertDitherType
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
comment|/*< pdb-skip>*/
DECL|enum|__anon2b8bc5960403
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

begin_define
DECL|macro|GIMP_TYPE_CURVE_TYPE
define|#
directive|define
name|GIMP_TYPE_CURVE_TYPE
value|(gimp_curve_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_curve_type_get_type
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
DECL|enum|__anon2b8bc5960503
block|{
DECL|enumerator|GIMP_CURVE_SMOOTH
name|GIMP_CURVE_SMOOTH
block|,
comment|/*< desc="Smooth">*/
DECL|enumerator|GIMP_CURVE_FREE
name|GIMP_CURVE_FREE
comment|/*< desc="Freehand">*/
DECL|typedef|GimpCurveType
block|}
name|GimpCurveType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GRAVITY_TYPE
define|#
directive|define
name|GIMP_TYPE_GRAVITY_TYPE
value|(gimp_gravity_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gravity_type_get_type
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
DECL|enum|__anon2b8bc5960603
block|{
DECL|enumerator|GIMP_GRAVITY_NONE
name|GIMP_GRAVITY_NONE
block|,
DECL|enumerator|GIMP_GRAVITY_NORTH_WEST
name|GIMP_GRAVITY_NORTH_WEST
block|,
DECL|enumerator|GIMP_GRAVITY_NORTH
name|GIMP_GRAVITY_NORTH
block|,
DECL|enumerator|GIMP_GRAVITY_NORTH_EAST
name|GIMP_GRAVITY_NORTH_EAST
block|,
DECL|enumerator|GIMP_GRAVITY_WEST
name|GIMP_GRAVITY_WEST
block|,
DECL|enumerator|GIMP_GRAVITY_CENTER
name|GIMP_GRAVITY_CENTER
block|,
DECL|enumerator|GIMP_GRAVITY_EAST
name|GIMP_GRAVITY_EAST
block|,
DECL|enumerator|GIMP_GRAVITY_SOUTH_WEST
name|GIMP_GRAVITY_SOUTH_WEST
block|,
DECL|enumerator|GIMP_GRAVITY_SOUTH
name|GIMP_GRAVITY_SOUTH
block|,
DECL|enumerator|GIMP_GRAVITY_SOUTH_EAST
name|GIMP_GRAVITY_SOUTH_EAST
DECL|typedef|GimpGravityType
block|}
name|GimpGravityType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GUIDE_STYLE
define|#
directive|define
name|GIMP_TYPE_GUIDE_STYLE
value|(gimp_guide_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_guide_style_get_type
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
DECL|enum|__anon2b8bc5960703
block|{
DECL|enumerator|GIMP_GUIDE_STYLE_NONE
name|GIMP_GUIDE_STYLE_NONE
block|,
DECL|enumerator|GIMP_GUIDE_STYLE_NORMAL
name|GIMP_GUIDE_STYLE_NORMAL
block|,
DECL|enumerator|GIMP_GUIDE_STYLE_MIRROR
name|GIMP_GUIDE_STYLE_MIRROR
block|,
DECL|enumerator|GIMP_GUIDE_STYLE_MANDALA
name|GIMP_GUIDE_STYLE_MANDALA
block|,
DECL|enumerator|GIMP_GUIDE_STYLE_SPLIT_VIEW
name|GIMP_GUIDE_STYLE_SPLIT_VIEW
DECL|typedef|GimpGuideStyle
block|}
name|GimpGuideStyle
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
DECL|enum|__anon2b8bc5960803
block|{
DECL|enumerator|GIMP_HISTOGRAM_VALUE
name|GIMP_HISTOGRAM_VALUE
init|=
literal|0
block|,
comment|/*< desc="Value">*/
DECL|enumerator|GIMP_HISTOGRAM_RED
name|GIMP_HISTOGRAM_RED
init|=
literal|1
block|,
comment|/*< desc="Red">*/
DECL|enumerator|GIMP_HISTOGRAM_GREEN
name|GIMP_HISTOGRAM_GREEN
init|=
literal|2
block|,
comment|/*< desc="Green">*/
DECL|enumerator|GIMP_HISTOGRAM_BLUE
name|GIMP_HISTOGRAM_BLUE
init|=
literal|3
block|,
comment|/*< desc="Blue">*/
DECL|enumerator|GIMP_HISTOGRAM_ALPHA
name|GIMP_HISTOGRAM_ALPHA
init|=
literal|4
block|,
comment|/*< desc="Alpha">*/
DECL|enumerator|GIMP_HISTOGRAM_LUMINANCE
name|GIMP_HISTOGRAM_LUMINANCE
init|=
literal|5
block|,
comment|/*< desc="Luminance">*/
DECL|enumerator|GIMP_HISTOGRAM_RGB
name|GIMP_HISTOGRAM_RGB
init|=
literal|6
comment|/*< desc="RGB", pdb-skip>*/
DECL|typedef|GimpHistogramChannel
block|}
name|GimpHistogramChannel
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
DECL|enum|__anon2b8bc5960903
block|{
DECL|enumerator|GIMP_NORMAL_MODE
name|GIMP_NORMAL_MODE
block|,
comment|/*< desc="Normal">*/
DECL|enumerator|GIMP_DISSOLVE_MODE
name|GIMP_DISSOLVE_MODE
block|,
comment|/*< desc="Dissolve">*/
DECL|enumerator|GIMP_BEHIND_MODE
name|GIMP_BEHIND_MODE
block|,
comment|/*< desc="Behind">*/
DECL|enumerator|GIMP_MULTIPLY_MODE
name|GIMP_MULTIPLY_MODE
block|,
comment|/*< desc="Multiply">*/
DECL|enumerator|GIMP_SCREEN_MODE
name|GIMP_SCREEN_MODE
block|,
comment|/*< desc="Screen">*/
DECL|enumerator|GIMP_OVERLAY_MODE
name|GIMP_OVERLAY_MODE
block|,
comment|/*< desc="Old broken Overlay">*/
DECL|enumerator|GIMP_DIFFERENCE_MODE
name|GIMP_DIFFERENCE_MODE
block|,
comment|/*< desc="Difference">*/
DECL|enumerator|GIMP_ADDITION_MODE
name|GIMP_ADDITION_MODE
block|,
comment|/*< desc="Addition">*/
DECL|enumerator|GIMP_SUBTRACT_MODE
name|GIMP_SUBTRACT_MODE
block|,
comment|/*< desc="Subtract">*/
DECL|enumerator|GIMP_DARKEN_ONLY_MODE
name|GIMP_DARKEN_ONLY_MODE
block|,
comment|/*< desc="Darken only">*/
DECL|enumerator|GIMP_LIGHTEN_ONLY_MODE
name|GIMP_LIGHTEN_ONLY_MODE
block|,
comment|/*< desc="Lighten only">*/
DECL|enumerator|GIMP_HUE_MODE
name|GIMP_HUE_MODE
block|,
comment|/*< desc="Hue (HSV)">*/
DECL|enumerator|GIMP_SATURATION_MODE
name|GIMP_SATURATION_MODE
block|,
comment|/*< desc="Saturation (HSV)">*/
DECL|enumerator|GIMP_COLOR_MODE
name|GIMP_COLOR_MODE
block|,
comment|/*< desc="Color (HSV)">*/
DECL|enumerator|GIMP_VALUE_MODE
name|GIMP_VALUE_MODE
block|,
comment|/*< desc="Value (HSV)">*/
DECL|enumerator|GIMP_DIVIDE_MODE
name|GIMP_DIVIDE_MODE
block|,
comment|/*< desc="Divide">*/
DECL|enumerator|GIMP_DODGE_MODE
name|GIMP_DODGE_MODE
block|,
comment|/*< desc="Dodge">*/
DECL|enumerator|GIMP_BURN_MODE
name|GIMP_BURN_MODE
block|,
comment|/*< desc="Burn">*/
DECL|enumerator|GIMP_HARDLIGHT_MODE
name|GIMP_HARDLIGHT_MODE
block|,
comment|/*< desc="Hard light">*/
DECL|enumerator|GIMP_SOFTLIGHT_MODE
name|GIMP_SOFTLIGHT_MODE
block|,
comment|/*< desc="Soft light">*/
DECL|enumerator|GIMP_GRAIN_EXTRACT_MODE
name|GIMP_GRAIN_EXTRACT_MODE
block|,
comment|/*< desc="Grain extract">*/
DECL|enumerator|GIMP_GRAIN_MERGE_MODE
name|GIMP_GRAIN_MERGE_MODE
block|,
comment|/*< desc="Grain merge">*/
DECL|enumerator|GIMP_COLOR_ERASE_MODE
name|GIMP_COLOR_ERASE_MODE
block|,
comment|/*< desc="Color erase">*/
DECL|enumerator|GIMP_NEW_OVERLAY_MODE
name|GIMP_NEW_OVERLAY_MODE
block|,
comment|/*< desc="Overlay">*/
DECL|enumerator|GIMP_LCH_HUE_MODE
name|GIMP_LCH_HUE_MODE
block|,
comment|/*< desc="Hue (LCH)">*/
DECL|enumerator|GIMP_LCH_CHROMA_MODE
name|GIMP_LCH_CHROMA_MODE
block|,
comment|/*< desc="Chroma (LCH)">*/
DECL|enumerator|GIMP_LCH_COLOR_MODE
name|GIMP_LCH_COLOR_MODE
block|,
comment|/*< desc="Color (LCH)">*/
DECL|enumerator|GIMP_LCH_LIGHTNESS_MODE
name|GIMP_LCH_LIGHTNESS_MODE
block|,
comment|/*< desc="Lightness (LCH)">*/
comment|/* internal modes, not available to the PDB */
DECL|enumerator|GIMP_ERASE_MODE
name|GIMP_ERASE_MODE
init|=
literal|1000
block|,
comment|/*< pdb-skip, desc="Erase">*/
DECL|enumerator|GIMP_REPLACE_MODE
name|GIMP_REPLACE_MODE
init|=
literal|1001
block|,
comment|/*< pdb-skip, desc="Replace">*/
DECL|enumerator|GIMP_ANTI_ERASE_MODE
name|GIMP_ANTI_ERASE_MODE
init|=
literal|1002
comment|/*< pdb-skip, desc="Anti erase">*/
DECL|typedef|GimpLayerModeEffects
block|}
name|GimpLayerModeEffects
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_MATTING_ENGINE
define|#
directive|define
name|GIMP_TYPE_MATTING_ENGINE
value|(gimp_matting_engine_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_matting_engine_get_type
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
DECL|enum|__anon2b8bc5960a03
block|{
DECL|enumerator|GIMP_MATTING_ENGINE_GLOBAL
name|GIMP_MATTING_ENGINE_GLOBAL
block|,
comment|/*< desc="Matting Global">*/
DECL|enumerator|GIMP_MATTING_ENGINE_LEVIN
name|GIMP_MATTING_ENGINE_LEVIN
block|,
comment|/*< desc="Matting Levin">*/
DECL|typedef|GimpMattingEngine
block|}
name|GimpMattingEngine
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PASTE_TYPE
define|#
directive|define
name|GIMP_TYPE_PASTE_TYPE
value|(gimp_paste_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_paste_type_get_type
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
DECL|enum|__anon2b8bc5960b03
block|{
DECL|enumerator|GIMP_PASTE_TYPE_FLOATING
name|GIMP_PASTE_TYPE_FLOATING
block|,
DECL|enumerator|GIMP_PASTE_TYPE_FLOATING_INTO
name|GIMP_PASTE_TYPE_FLOATING_INTO
block|,
DECL|enumerator|GIMP_PASTE_TYPE_NEW_LAYER
name|GIMP_PASTE_TYPE_NEW_LAYER
DECL|typedef|GimpPasteType
block|}
name|GimpPasteType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ALIGNMENT_TYPE
define|#
directive|define
name|GIMP_TYPE_ALIGNMENT_TYPE
value|(gimp_alignment_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_alignment_type_get_type
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
DECL|enum|__anon2b8bc5960c03
block|{
DECL|enumerator|GIMP_ALIGN_LEFT
name|GIMP_ALIGN_LEFT
block|,
DECL|enumerator|GIMP_ALIGN_HCENTER
name|GIMP_ALIGN_HCENTER
block|,
DECL|enumerator|GIMP_ALIGN_RIGHT
name|GIMP_ALIGN_RIGHT
block|,
DECL|enumerator|GIMP_ALIGN_TOP
name|GIMP_ALIGN_TOP
block|,
DECL|enumerator|GIMP_ALIGN_VCENTER
name|GIMP_ALIGN_VCENTER
block|,
DECL|enumerator|GIMP_ALIGN_BOTTOM
name|GIMP_ALIGN_BOTTOM
block|,
DECL|enumerator|GIMP_ARRANGE_LEFT
name|GIMP_ARRANGE_LEFT
block|,
DECL|enumerator|GIMP_ARRANGE_HCENTER
name|GIMP_ARRANGE_HCENTER
block|,
DECL|enumerator|GIMP_ARRANGE_RIGHT
name|GIMP_ARRANGE_RIGHT
block|,
DECL|enumerator|GIMP_ARRANGE_TOP
name|GIMP_ARRANGE_TOP
block|,
DECL|enumerator|GIMP_ARRANGE_VCENTER
name|GIMP_ARRANGE_VCENTER
block|,
DECL|enumerator|GIMP_ARRANGE_BOTTOM
name|GIMP_ARRANGE_BOTTOM
block|,
DECL|enumerator|GIMP_ARRANGE_HFILL
name|GIMP_ARRANGE_HFILL
block|,
DECL|enumerator|GIMP_ARRANGE_VFILL
name|GIMP_ARRANGE_VFILL
DECL|typedef|GimpAlignmentType
block|}
name|GimpAlignmentType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ALIGN_REFERENCE_TYPE
define|#
directive|define
name|GIMP_TYPE_ALIGN_REFERENCE_TYPE
value|(gimp_align_reference_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_align_reference_type_get_type
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
DECL|enum|__anon2b8bc5960d03
block|{
DECL|enumerator|GIMP_ALIGN_REFERENCE_FIRST
name|GIMP_ALIGN_REFERENCE_FIRST
block|,
comment|/*< desc="First item">*/
DECL|enumerator|GIMP_ALIGN_REFERENCE_IMAGE
name|GIMP_ALIGN_REFERENCE_IMAGE
block|,
comment|/*< desc="Image">*/
DECL|enumerator|GIMP_ALIGN_REFERENCE_SELECTION
name|GIMP_ALIGN_REFERENCE_SELECTION
block|,
comment|/*< desc="Selection">*/
DECL|enumerator|GIMP_ALIGN_REFERENCE_ACTIVE_LAYER
name|GIMP_ALIGN_REFERENCE_ACTIVE_LAYER
block|,
comment|/*< desc="Active layer">*/
DECL|enumerator|GIMP_ALIGN_REFERENCE_ACTIVE_CHANNEL
name|GIMP_ALIGN_REFERENCE_ACTIVE_CHANNEL
block|,
comment|/*< desc="Active channel">*/
DECL|enumerator|GIMP_ALIGN_REFERENCE_ACTIVE_PATH
name|GIMP_ALIGN_REFERENCE_ACTIVE_PATH
comment|/*< desc="Active path">*/
DECL|typedef|GimpAlignReferenceType
block|}
name|GimpAlignReferenceType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_FILL_STYLE
define|#
directive|define
name|GIMP_TYPE_FILL_STYLE
value|(gimp_fill_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_fill_style_get_type
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
DECL|enum|__anon2b8bc5960e03
block|{
DECL|enumerator|GIMP_FILL_STYLE_SOLID
name|GIMP_FILL_STYLE_SOLID
block|,
comment|/*< desc="Solid color">*/
DECL|enumerator|GIMP_FILL_STYLE_PATTERN
name|GIMP_FILL_STYLE_PATTERN
comment|/*< desc="Pattern">*/
DECL|typedef|GimpFillStyle
block|}
name|GimpFillStyle
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DASH_PRESET
define|#
directive|define
name|GIMP_TYPE_DASH_PRESET
value|(gimp_dash_preset_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_dash_preset_get_type
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
DECL|enum|__anon2b8bc5960f03
block|{
DECL|enumerator|GIMP_DASH_CUSTOM
name|GIMP_DASH_CUSTOM
block|,
comment|/*< desc="Custom">*/
DECL|enumerator|GIMP_DASH_LINE
name|GIMP_DASH_LINE
block|,
comment|/*< desc="Line">*/
DECL|enumerator|GIMP_DASH_LONG_DASH
name|GIMP_DASH_LONG_DASH
block|,
comment|/*< desc="Long dashes">*/
DECL|enumerator|GIMP_DASH_MEDIUM_DASH
name|GIMP_DASH_MEDIUM_DASH
block|,
comment|/*< desc="Medium dashes">*/
DECL|enumerator|GIMP_DASH_SHORT_DASH
name|GIMP_DASH_SHORT_DASH
block|,
comment|/*< desc="Short dashes">*/
DECL|enumerator|GIMP_DASH_SPARSE_DOTS
name|GIMP_DASH_SPARSE_DOTS
block|,
comment|/*< desc="Sparse dots">*/
DECL|enumerator|GIMP_DASH_NORMAL_DOTS
name|GIMP_DASH_NORMAL_DOTS
block|,
comment|/*< desc="Normal dots">*/
DECL|enumerator|GIMP_DASH_DENSE_DOTS
name|GIMP_DASH_DENSE_DOTS
block|,
comment|/*< desc="Dense dots">*/
DECL|enumerator|GIMP_DASH_STIPPLES
name|GIMP_DASH_STIPPLES
block|,
comment|/*< desc="Stipples">*/
DECL|enumerator|GIMP_DASH_DASH_DOT
name|GIMP_DASH_DASH_DOT
block|,
comment|/*< desc="Dash, dot">*/
DECL|enumerator|GIMP_DASH_DASH_DOT_DOT
name|GIMP_DASH_DASH_DOT_DOT
comment|/*< desc="Dash, dot, dot">*/
DECL|typedef|GimpDashPreset
block|}
name|GimpDashPreset
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ITEM_SET
define|#
directive|define
name|GIMP_TYPE_ITEM_SET
value|(gimp_item_set_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_item_set_get_type
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
DECL|enum|__anon2b8bc5961003
block|{
DECL|enumerator|GIMP_ITEM_SET_NONE
name|GIMP_ITEM_SET_NONE
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_ITEM_SET_ALL
name|GIMP_ITEM_SET_ALL
block|,
comment|/*< desc="All layers">*/
DECL|enumerator|GIMP_ITEM_SET_IMAGE_SIZED
name|GIMP_ITEM_SET_IMAGE_SIZED
block|,
comment|/*< desc="Image-sized layers">*/
DECL|enumerator|GIMP_ITEM_SET_VISIBLE
name|GIMP_ITEM_SET_VISIBLE
block|,
comment|/*< desc="All visible layers">*/
DECL|enumerator|GIMP_ITEM_SET_LINKED
name|GIMP_ITEM_SET_LINKED
comment|/*< desc="All linked layers">*/
DECL|typedef|GimpItemSet
block|}
name|GimpItemSet
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_VIEW_SIZE
define|#
directive|define
name|GIMP_TYPE_VIEW_SIZE
value|(gimp_view_size_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_view_size_get_type
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
DECL|enum|__anon2b8bc5961103
block|{
DECL|enumerator|GIMP_VIEW_SIZE_TINY
name|GIMP_VIEW_SIZE_TINY
init|=
literal|12
block|,
comment|/*< desc="Tiny">*/
DECL|enumerator|GIMP_VIEW_SIZE_EXTRA_SMALL
name|GIMP_VIEW_SIZE_EXTRA_SMALL
init|=
literal|16
block|,
comment|/*< desc="Very small">*/
DECL|enumerator|GIMP_VIEW_SIZE_SMALL
name|GIMP_VIEW_SIZE_SMALL
init|=
literal|24
block|,
comment|/*< desc="Small">*/
DECL|enumerator|GIMP_VIEW_SIZE_MEDIUM
name|GIMP_VIEW_SIZE_MEDIUM
init|=
literal|32
block|,
comment|/*< desc="Medium">*/
DECL|enumerator|GIMP_VIEW_SIZE_LARGE
name|GIMP_VIEW_SIZE_LARGE
init|=
literal|48
block|,
comment|/*< desc="Large">*/
DECL|enumerator|GIMP_VIEW_SIZE_EXTRA_LARGE
name|GIMP_VIEW_SIZE_EXTRA_LARGE
init|=
literal|64
block|,
comment|/*< desc="Very large">*/
DECL|enumerator|GIMP_VIEW_SIZE_HUGE
name|GIMP_VIEW_SIZE_HUGE
init|=
literal|96
block|,
comment|/*< desc="Huge">*/
DECL|enumerator|GIMP_VIEW_SIZE_ENORMOUS
name|GIMP_VIEW_SIZE_ENORMOUS
init|=
literal|128
block|,
comment|/*< desc="Enormous">*/
DECL|enumerator|GIMP_VIEW_SIZE_GIGANTIC
name|GIMP_VIEW_SIZE_GIGANTIC
init|=
literal|192
comment|/*< desc="Gigantic">*/
DECL|typedef|GimpViewSize
block|}
name|GimpViewSize
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_VIEW_TYPE
define|#
directive|define
name|GIMP_TYPE_VIEW_TYPE
value|(gimp_view_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_view_type_get_type
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
DECL|enum|__anon2b8bc5961203
block|{
DECL|enumerator|GIMP_VIEW_TYPE_LIST
name|GIMP_VIEW_TYPE_LIST
block|,
comment|/*< desc="View as list">*/
DECL|enumerator|GIMP_VIEW_TYPE_GRID
name|GIMP_VIEW_TYPE_GRID
comment|/*< desc="View as grid">*/
DECL|typedef|GimpViewType
block|}
name|GimpViewType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_THUMBNAIL_SIZE
define|#
directive|define
name|GIMP_TYPE_THUMBNAIL_SIZE
value|(gimp_thumbnail_size_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_thumbnail_size_get_type
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
DECL|enum|__anon2b8bc5961303
block|{
DECL|enumerator|GIMP_THUMBNAIL_SIZE_NONE
name|GIMP_THUMBNAIL_SIZE_NONE
init|=
literal|0
block|,
comment|/*< desc="No thumbnails">*/
DECL|enumerator|GIMP_THUMBNAIL_SIZE_NORMAL
name|GIMP_THUMBNAIL_SIZE_NORMAL
init|=
literal|128
block|,
comment|/*< desc="Normal (128x128)">*/
DECL|enumerator|GIMP_THUMBNAIL_SIZE_LARGE
name|GIMP_THUMBNAIL_SIZE_LARGE
init|=
literal|256
comment|/*< desc="Large (256x256)">*/
DECL|typedef|GimpThumbnailSize
block|}
name|GimpThumbnailSize
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_UNDO_MODE
define|#
directive|define
name|GIMP_TYPE_UNDO_MODE
value|(gimp_undo_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_undo_mode_get_type
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
DECL|enum|__anon2b8bc5961403
block|{
DECL|enumerator|GIMP_UNDO_MODE_UNDO
name|GIMP_UNDO_MODE_UNDO
block|,
DECL|enumerator|GIMP_UNDO_MODE_REDO
name|GIMP_UNDO_MODE_REDO
DECL|typedef|GimpUndoMode
block|}
name|GimpUndoMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_UNDO_EVENT
define|#
directive|define
name|GIMP_TYPE_UNDO_EVENT
value|(gimp_undo_event_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_undo_event_get_type
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
DECL|enum|__anon2b8bc5961503
block|{
DECL|enumerator|GIMP_UNDO_EVENT_UNDO_PUSHED
name|GIMP_UNDO_EVENT_UNDO_PUSHED
block|,
comment|/* a new undo has been added to the undo stack */
DECL|enumerator|GIMP_UNDO_EVENT_UNDO_EXPIRED
name|GIMP_UNDO_EVENT_UNDO_EXPIRED
block|,
comment|/* an undo has been freed from the undo stack  */
DECL|enumerator|GIMP_UNDO_EVENT_REDO_EXPIRED
name|GIMP_UNDO_EVENT_REDO_EXPIRED
block|,
comment|/* a redo has been freed from the redo stack   */
DECL|enumerator|GIMP_UNDO_EVENT_UNDO
name|GIMP_UNDO_EVENT_UNDO
block|,
comment|/* an undo has been executed                   */
DECL|enumerator|GIMP_UNDO_EVENT_REDO
name|GIMP_UNDO_EVENT_REDO
block|,
comment|/* a redo has been executed                    */
DECL|enumerator|GIMP_UNDO_EVENT_UNDO_FREE
name|GIMP_UNDO_EVENT_UNDO_FREE
block|,
comment|/* all undo and redo info has been cleared     */
DECL|enumerator|GIMP_UNDO_EVENT_UNDO_FREEZE
name|GIMP_UNDO_EVENT_UNDO_FREEZE
block|,
comment|/* undo has been frozen                        */
DECL|enumerator|GIMP_UNDO_EVENT_UNDO_THAW
name|GIMP_UNDO_EVENT_UNDO_THAW
comment|/* undo has been thawn                         */
DECL|typedef|GimpUndoEvent
block|}
name|GimpUndoEvent
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_UNDO_TYPE
define|#
directive|define
name|GIMP_TYPE_UNDO_TYPE
value|(gimp_undo_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_undo_type_get_type
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
DECL|enum|__anon2b8bc5961603
block|{
comment|/* Type NO_UNDO_GROUP (0) is special - in the gimpimage structure it    * means there is no undo group currently being added to.    */
DECL|enumerator|GIMP_UNDO_GROUP_NONE
name|GIMP_UNDO_GROUP_NONE
init|=
literal|0
block|,
comment|/*< desc="<<invalid>>">*/
DECL|enumerator|GIMP_UNDO_GROUP_FIRST
name|GIMP_UNDO_GROUP_FIRST
init|=
name|GIMP_UNDO_GROUP_NONE
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_SCALE
name|GIMP_UNDO_GROUP_IMAGE_SCALE
block|,
comment|/*< desc="Scale image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_RESIZE
name|GIMP_UNDO_GROUP_IMAGE_RESIZE
block|,
comment|/*< desc="Resize image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_FLIP
name|GIMP_UNDO_GROUP_IMAGE_FLIP
block|,
comment|/*< desc="Flip image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_ROTATE
name|GIMP_UNDO_GROUP_IMAGE_ROTATE
block|,
comment|/*< desc="Rotate image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_CROP
name|GIMP_UNDO_GROUP_IMAGE_CROP
block|,
comment|/*< desc="Crop image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_CONVERT
name|GIMP_UNDO_GROUP_IMAGE_CONVERT
block|,
comment|/*< desc="Convert image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_ITEM_REMOVE
name|GIMP_UNDO_GROUP_IMAGE_ITEM_REMOVE
block|,
comment|/*< desc="Remove item">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_LAYERS_MERGE
name|GIMP_UNDO_GROUP_IMAGE_LAYERS_MERGE
block|,
comment|/*< desc="Merge layers">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_VECTORS_MERGE
name|GIMP_UNDO_GROUP_IMAGE_VECTORS_MERGE
block|,
comment|/*< desc="Merge paths">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_QUICK_MASK
name|GIMP_UNDO_GROUP_IMAGE_QUICK_MASK
block|,
comment|/*< desc="Quick Mask">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_GRID
name|GIMP_UNDO_GROUP_IMAGE_GRID
block|,
comment|/*< desc="Grid">*/
DECL|enumerator|GIMP_UNDO_GROUP_GUIDE
name|GIMP_UNDO_GROUP_GUIDE
block|,
comment|/*< desc="Guide">*/
DECL|enumerator|GIMP_UNDO_GROUP_SAMPLE_POINT
name|GIMP_UNDO_GROUP_SAMPLE_POINT
block|,
comment|/*< desc="Sample Point">*/
DECL|enumerator|GIMP_UNDO_GROUP_DRAWABLE
name|GIMP_UNDO_GROUP_DRAWABLE
block|,
comment|/*< desc="Layer/Channel">*/
DECL|enumerator|GIMP_UNDO_GROUP_DRAWABLE_MOD
name|GIMP_UNDO_GROUP_DRAWABLE_MOD
block|,
comment|/*< desc="Layer/Channel modification">*/
DECL|enumerator|GIMP_UNDO_GROUP_MASK
name|GIMP_UNDO_GROUP_MASK
block|,
comment|/*< desc="Selection mask">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_VISIBILITY
name|GIMP_UNDO_GROUP_ITEM_VISIBILITY
block|,
comment|/*< desc="Item visibility">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_LINKED
name|GIMP_UNDO_GROUP_ITEM_LINKED
block|,
comment|/*< desc="Link/Unlink item">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_PROPERTIES
name|GIMP_UNDO_GROUP_ITEM_PROPERTIES
block|,
comment|/*< desc="Item properties">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_DISPLACE
name|GIMP_UNDO_GROUP_ITEM_DISPLACE
block|,
comment|/*< desc="Move item">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_SCALE
name|GIMP_UNDO_GROUP_ITEM_SCALE
block|,
comment|/*< desc="Scale item">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_RESIZE
name|GIMP_UNDO_GROUP_ITEM_RESIZE
block|,
comment|/*< desc="Resize item">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_ADD
name|GIMP_UNDO_GROUP_LAYER_ADD
block|,
comment|/*< desc="Add layer">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_ADD_MASK
name|GIMP_UNDO_GROUP_LAYER_ADD_MASK
block|,
comment|/*< desc="Add layer mask">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_APPLY_MASK
name|GIMP_UNDO_GROUP_LAYER_APPLY_MASK
block|,
comment|/*< desc="Apply layer mask">*/
DECL|enumerator|GIMP_UNDO_GROUP_FS_TO_LAYER
name|GIMP_UNDO_GROUP_FS_TO_LAYER
block|,
comment|/*< desc="Floating selection to layer">*/
DECL|enumerator|GIMP_UNDO_GROUP_FS_FLOAT
name|GIMP_UNDO_GROUP_FS_FLOAT
block|,
comment|/*< desc="Float selection">*/
DECL|enumerator|GIMP_UNDO_GROUP_FS_ANCHOR
name|GIMP_UNDO_GROUP_FS_ANCHOR
block|,
comment|/*< desc="Anchor floating selection">*/
DECL|enumerator|GIMP_UNDO_GROUP_EDIT_PASTE
name|GIMP_UNDO_GROUP_EDIT_PASTE
block|,
comment|/*< desc="Paste">*/
DECL|enumerator|GIMP_UNDO_GROUP_EDIT_CUT
name|GIMP_UNDO_GROUP_EDIT_CUT
block|,
comment|/*< desc="Cut">*/
DECL|enumerator|GIMP_UNDO_GROUP_TEXT
name|GIMP_UNDO_GROUP_TEXT
block|,
comment|/*< desc="Text">*/
DECL|enumerator|GIMP_UNDO_GROUP_TRANSFORM
name|GIMP_UNDO_GROUP_TRANSFORM
block|,
comment|/*< desc="Transform">*/
DECL|enumerator|GIMP_UNDO_GROUP_PAINT
name|GIMP_UNDO_GROUP_PAINT
block|,
comment|/*< desc="Paint">*/
DECL|enumerator|GIMP_UNDO_GROUP_PARASITE_ATTACH
name|GIMP_UNDO_GROUP_PARASITE_ATTACH
block|,
comment|/*< desc="Attach parasite">*/
DECL|enumerator|GIMP_UNDO_GROUP_PARASITE_REMOVE
name|GIMP_UNDO_GROUP_PARASITE_REMOVE
block|,
comment|/*< desc="Remove parasite">*/
DECL|enumerator|GIMP_UNDO_GROUP_VECTORS_IMPORT
name|GIMP_UNDO_GROUP_VECTORS_IMPORT
block|,
comment|/*< desc="Import paths">*/
DECL|enumerator|GIMP_UNDO_GROUP_MISC
name|GIMP_UNDO_GROUP_MISC
block|,
comment|/*< desc="Plug-In">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAST
name|GIMP_UNDO_GROUP_LAST
init|=
name|GIMP_UNDO_GROUP_MISC
block|,
comment|/*< skip>*/
comment|/*  Undo types which actually do something  */
DECL|enumerator|GIMP_UNDO_IMAGE_TYPE
name|GIMP_UNDO_IMAGE_TYPE
block|,
comment|/*< desc="Image type">*/
DECL|enumerator|GIMP_UNDO_IMAGE_PRECISION
name|GIMP_UNDO_IMAGE_PRECISION
block|,
comment|/*< desc="Image precision">*/
DECL|enumerator|GIMP_UNDO_IMAGE_SIZE
name|GIMP_UNDO_IMAGE_SIZE
block|,
comment|/*< desc="Image size">*/
DECL|enumerator|GIMP_UNDO_IMAGE_RESOLUTION
name|GIMP_UNDO_IMAGE_RESOLUTION
block|,
comment|/*< desc="Image resolution change">*/
DECL|enumerator|GIMP_UNDO_IMAGE_GRID
name|GIMP_UNDO_IMAGE_GRID
block|,
comment|/*< desc="Grid">*/
DECL|enumerator|GIMP_UNDO_IMAGE_COLORMAP
name|GIMP_UNDO_IMAGE_COLORMAP
block|,
comment|/*< desc="Change indexed palette">*/
DECL|enumerator|GIMP_UNDO_IMAGE_COLOR_MANAGED
name|GIMP_UNDO_IMAGE_COLOR_MANAGED
block|,
comment|/*< desc="Change color managed state">*/
DECL|enumerator|GIMP_UNDO_IMAGE_METADATA
name|GIMP_UNDO_IMAGE_METADATA
block|,
comment|/*< desc="Change metadata>*/
DECL|enumerator|GIMP_UNDO_GUIDE
name|GIMP_UNDO_GUIDE
block|,
comment|/*< desc="Guide">*/
DECL|enumerator|GIMP_UNDO_SAMPLE_POINT
name|GIMP_UNDO_SAMPLE_POINT
block|,
comment|/*< desc="Sample Point">*/
DECL|enumerator|GIMP_UNDO_DRAWABLE
name|GIMP_UNDO_DRAWABLE
block|,
comment|/*< desc="Layer/Channel">*/
DECL|enumerator|GIMP_UNDO_DRAWABLE_MOD
name|GIMP_UNDO_DRAWABLE_MOD
block|,
comment|/*< desc="Layer/Channel modification">*/
DECL|enumerator|GIMP_UNDO_MASK
name|GIMP_UNDO_MASK
block|,
comment|/*< desc="Selection mask">*/
DECL|enumerator|GIMP_UNDO_ITEM_METADATA
name|GIMP_UNDO_ITEM_METADATA
block|,
comment|/*< desc="Change metadata>*/
DECL|enumerator|GIMP_UNDO_ITEM_REORDER
name|GIMP_UNDO_ITEM_REORDER
block|,
comment|/*< desc="Reorder item">*/
DECL|enumerator|GIMP_UNDO_ITEM_RENAME
name|GIMP_UNDO_ITEM_RENAME
block|,
comment|/*< desc="Rename item">*/
DECL|enumerator|GIMP_UNDO_ITEM_DISPLACE
name|GIMP_UNDO_ITEM_DISPLACE
block|,
comment|/*< desc="Move item">*/
DECL|enumerator|GIMP_UNDO_ITEM_VISIBILITY
name|GIMP_UNDO_ITEM_VISIBILITY
block|,
comment|/*< desc="Item visibility">*/
DECL|enumerator|GIMP_UNDO_ITEM_LINKED
name|GIMP_UNDO_ITEM_LINKED
block|,
comment|/*< desc="Link/Unlink item">*/
DECL|enumerator|GIMP_UNDO_ITEM_COLOR_TAG
name|GIMP_UNDO_ITEM_COLOR_TAG
block|,
comment|/*< desc="Item color tag">*/
DECL|enumerator|GIMP_UNDO_ITEM_LOCK_CONTENT
name|GIMP_UNDO_ITEM_LOCK_CONTENT
block|,
comment|/*< desc="Lock/Unlock content">*/
DECL|enumerator|GIMP_UNDO_ITEM_LOCK_POSITION
name|GIMP_UNDO_ITEM_LOCK_POSITION
block|,
comment|/*< desc="Lock/Unlock position">*/
DECL|enumerator|GIMP_UNDO_LAYER_ADD
name|GIMP_UNDO_LAYER_ADD
block|,
comment|/*< desc="New layer">*/
DECL|enumerator|GIMP_UNDO_LAYER_REMOVE
name|GIMP_UNDO_LAYER_REMOVE
block|,
comment|/*< desc="Delete layer">*/
DECL|enumerator|GIMP_UNDO_LAYER_MODE
name|GIMP_UNDO_LAYER_MODE
block|,
comment|/*< desc="Set layer mode">*/
DECL|enumerator|GIMP_UNDO_LAYER_OPACITY
name|GIMP_UNDO_LAYER_OPACITY
block|,
comment|/*< desc="Set layer opacity">*/
DECL|enumerator|GIMP_UNDO_LAYER_LOCK_ALPHA
name|GIMP_UNDO_LAYER_LOCK_ALPHA
block|,
comment|/*< desc="Lock/Unlock alpha channel">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_SUSPEND
name|GIMP_UNDO_GROUP_LAYER_SUSPEND
block|,
comment|/*< desc="Suspend group layer resize">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_RESUME
name|GIMP_UNDO_GROUP_LAYER_RESUME
block|,
comment|/*< desc="Resume group layer resize">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_CONVERT
name|GIMP_UNDO_GROUP_LAYER_CONVERT
block|,
comment|/*< desc="Convert group layer">*/
DECL|enumerator|GIMP_UNDO_TEXT_LAYER
name|GIMP_UNDO_TEXT_LAYER
block|,
comment|/*< desc="Text layer">*/
DECL|enumerator|GIMP_UNDO_TEXT_LAYER_MODIFIED
name|GIMP_UNDO_TEXT_LAYER_MODIFIED
block|,
comment|/*< desc="Text layer modification">*/
DECL|enumerator|GIMP_UNDO_TEXT_LAYER_CONVERT
name|GIMP_UNDO_TEXT_LAYER_CONVERT
block|,
comment|/*< desc="Convert text layer">*/
DECL|enumerator|GIMP_UNDO_LAYER_MASK_ADD
name|GIMP_UNDO_LAYER_MASK_ADD
block|,
comment|/*< desc="Add layer mask">*/
DECL|enumerator|GIMP_UNDO_LAYER_MASK_REMOVE
name|GIMP_UNDO_LAYER_MASK_REMOVE
block|,
comment|/*< desc="Delete layer mask">*/
DECL|enumerator|GIMP_UNDO_LAYER_MASK_APPLY
name|GIMP_UNDO_LAYER_MASK_APPLY
block|,
comment|/*< desc="Apply layer mask">*/
DECL|enumerator|GIMP_UNDO_LAYER_MASK_SHOW
name|GIMP_UNDO_LAYER_MASK_SHOW
block|,
comment|/*< desc="Show layer mask">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_ADD
name|GIMP_UNDO_CHANNEL_ADD
block|,
comment|/*< desc="New channel">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_REMOVE
name|GIMP_UNDO_CHANNEL_REMOVE
block|,
comment|/*< desc="Delete channel">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_COLOR
name|GIMP_UNDO_CHANNEL_COLOR
block|,
comment|/*< desc="Channel color">*/
DECL|enumerator|GIMP_UNDO_VECTORS_ADD
name|GIMP_UNDO_VECTORS_ADD
block|,
comment|/*< desc="New path">*/
DECL|enumerator|GIMP_UNDO_VECTORS_REMOVE
name|GIMP_UNDO_VECTORS_REMOVE
block|,
comment|/*< desc="Delete path">*/
DECL|enumerator|GIMP_UNDO_VECTORS_MOD
name|GIMP_UNDO_VECTORS_MOD
block|,
comment|/*< desc="Path modification">*/
DECL|enumerator|GIMP_UNDO_FS_TO_LAYER
name|GIMP_UNDO_FS_TO_LAYER
block|,
comment|/*< desc="Floating selection to layer">*/
DECL|enumerator|GIMP_UNDO_TRANSFORM
name|GIMP_UNDO_TRANSFORM
block|,
comment|/*< desc="Transform">*/
DECL|enumerator|GIMP_UNDO_PAINT
name|GIMP_UNDO_PAINT
block|,
comment|/*< desc="Paint">*/
DECL|enumerator|GIMP_UNDO_INK
name|GIMP_UNDO_INK
block|,
comment|/*< desc="Ink">*/
DECL|enumerator|GIMP_UNDO_FOREGROUND_SELECT
name|GIMP_UNDO_FOREGROUND_SELECT
block|,
comment|/*< desc="Select foreground">*/
DECL|enumerator|GIMP_UNDO_PARASITE_ATTACH
name|GIMP_UNDO_PARASITE_ATTACH
block|,
comment|/*< desc="Attach parasite">*/
DECL|enumerator|GIMP_UNDO_PARASITE_REMOVE
name|GIMP_UNDO_PARASITE_REMOVE
block|,
comment|/*< desc="Remove parasite">*/
DECL|enumerator|GIMP_UNDO_CANT
name|GIMP_UNDO_CANT
comment|/*< desc="Not undoable">*/
DECL|typedef|GimpUndoType
block|}
name|GimpUndoType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DIRTY_MASK
define|#
directive|define
name|GIMP_TYPE_DIRTY_MASK
value|(gimp_dirty_mask_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_dirty_mask_get_type
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
DECL|enum|__anon2b8bc5961703
block|{
DECL|enumerator|GIMP_DIRTY_NONE
name|GIMP_DIRTY_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_DIRTY_IMAGE
name|GIMP_DIRTY_IMAGE
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_DIRTY_IMAGE_SIZE
name|GIMP_DIRTY_IMAGE_SIZE
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_DIRTY_IMAGE_META
name|GIMP_DIRTY_IMAGE_META
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_DIRTY_IMAGE_STRUCTURE
name|GIMP_DIRTY_IMAGE_STRUCTURE
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_DIRTY_ITEM
name|GIMP_DIRTY_ITEM
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_DIRTY_ITEM_META
name|GIMP_DIRTY_ITEM_META
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_DIRTY_DRAWABLE
name|GIMP_DIRTY_DRAWABLE
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_DIRTY_VECTORS
name|GIMP_DIRTY_VECTORS
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_DIRTY_SELECTION
name|GIMP_DIRTY_SELECTION
init|=
literal|1
operator|<<
literal|8
block|,
DECL|enumerator|GIMP_DIRTY_ACTIVE_DRAWABLE
name|GIMP_DIRTY_ACTIVE_DRAWABLE
init|=
literal|1
operator|<<
literal|9
block|,
DECL|enumerator|GIMP_DIRTY_ALL
name|GIMP_DIRTY_ALL
init|=
literal|0xffff
DECL|typedef|GimpDirtyMask
block|}
name|GimpDirtyMask
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_COLOR
define|#
directive|define
name|GIMP_TYPE_GRADIENT_COLOR
value|(gimp_gradient_color_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_color_get_type
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
DECL|enum|__anon2b8bc5961803
block|{
DECL|enumerator|GIMP_GRADIENT_COLOR_FIXED
name|GIMP_GRADIENT_COLOR_FIXED
block|,
DECL|enumerator|GIMP_GRADIENT_COLOR_FOREGROUND
name|GIMP_GRADIENT_COLOR_FOREGROUND
block|,
DECL|enumerator|GIMP_GRADIENT_COLOR_FOREGROUND_TRANSPARENT
name|GIMP_GRADIENT_COLOR_FOREGROUND_TRANSPARENT
block|,
DECL|enumerator|GIMP_GRADIENT_COLOR_BACKGROUND
name|GIMP_GRADIENT_COLOR_BACKGROUND
block|,
DECL|enumerator|GIMP_GRADIENT_COLOR_BACKGROUND_TRANSPARENT
name|GIMP_GRADIENT_COLOR_BACKGROUND_TRANSPARENT
DECL|typedef|GimpGradientColor
block|}
name|GimpGradientColor
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_MESSAGE_SEVERITY
define|#
directive|define
name|GIMP_TYPE_MESSAGE_SEVERITY
value|(gimp_message_severity_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_message_severity_get_type
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
DECL|enum|__anon2b8bc5961903
block|{
DECL|enumerator|GIMP_MESSAGE_INFO
name|GIMP_MESSAGE_INFO
block|,
comment|/*< desc="Message">*/
DECL|enumerator|GIMP_MESSAGE_WARNING
name|GIMP_MESSAGE_WARNING
block|,
comment|/*< desc="Warning">*/
DECL|enumerator|GIMP_MESSAGE_ERROR
name|GIMP_MESSAGE_ERROR
comment|/*< desc="Error">*/
DECL|typedef|GimpMessageSeverity
block|}
name|GimpMessageSeverity
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_COLOR_PROFILE_POLICY
define|#
directive|define
name|GIMP_TYPE_COLOR_PROFILE_POLICY
value|(gimp_color_profile_policy_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_profile_policy_get_type
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
DECL|enum|__anon2b8bc5961a03
block|{
DECL|enumerator|GIMP_COLOR_PROFILE_POLICY_ASK
name|GIMP_COLOR_PROFILE_POLICY_ASK
block|,
comment|/*< desc="Ask what to do">*/
DECL|enumerator|GIMP_COLOR_PROFILE_POLICY_KEEP
name|GIMP_COLOR_PROFILE_POLICY_KEEP
block|,
comment|/*< desc="Keep embedded profile">*/
DECL|enumerator|GIMP_COLOR_PROFILE_POLICY_CONVERT
name|GIMP_COLOR_PROFILE_POLICY_CONVERT
comment|/*< desc="Convert to preferred RGB color profile">*/
DECL|typedef|GimpColorProfilePolicy
block|}
name|GimpColorProfilePolicy
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DYNAMICS_OUTPUT_TYPE
define|#
directive|define
name|GIMP_TYPE_DYNAMICS_OUTPUT_TYPE
value|(gimp_dynamics_output_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_dynamics_output_type_get_type
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
DECL|enum|__anon2b8bc5961b03
block|{
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_OPACITY
name|GIMP_DYNAMICS_OUTPUT_OPACITY
block|,
comment|/*< desc="Opacity">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_SIZE
name|GIMP_DYNAMICS_OUTPUT_SIZE
block|,
comment|/*< desc="Size">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_ANGLE
name|GIMP_DYNAMICS_OUTPUT_ANGLE
block|,
comment|/*< desc="Angle">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_COLOR
name|GIMP_DYNAMICS_OUTPUT_COLOR
block|,
comment|/*< desc="Color">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_HARDNESS
name|GIMP_DYNAMICS_OUTPUT_HARDNESS
block|,
comment|/*< desc="Hardness">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_FORCE
name|GIMP_DYNAMICS_OUTPUT_FORCE
block|,
comment|/*< desc="Force">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_ASPECT_RATIO
name|GIMP_DYNAMICS_OUTPUT_ASPECT_RATIO
block|,
comment|/*< desc="Aspect ratio">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_SPACING
name|GIMP_DYNAMICS_OUTPUT_SPACING
block|,
comment|/*< desc="Spacing">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_RATE
name|GIMP_DYNAMICS_OUTPUT_RATE
block|,
comment|/*< desc="Rate">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_FLOW
name|GIMP_DYNAMICS_OUTPUT_FLOW
block|,
comment|/*< desc="Flow">*/
DECL|enumerator|GIMP_DYNAMICS_OUTPUT_JITTER
name|GIMP_DYNAMICS_OUTPUT_JITTER
block|,
comment|/*< desc="Jitter">*/
DECL|typedef|GimpDynamicsOutputType
block|}
name|GimpDynamicsOutputType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_FILTER_REGION
define|#
directive|define
name|GIMP_TYPE_FILTER_REGION
value|(gimp_filter_region_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_filter_region_get_type
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
DECL|enum|__anon2b8bc5961c03
block|{
DECL|enumerator|GIMP_FILTER_REGION_SELECTION
name|GIMP_FILTER_REGION_SELECTION
block|,
comment|/*< desc="Use the selection as input">*/
DECL|enumerator|GIMP_FILTER_REGION_DRAWABLE
name|GIMP_FILTER_REGION_DRAWABLE
comment|/*< desc="Use the entire layer as input">*/
DECL|typedef|GimpFilterRegion
block|}
name|GimpFilterRegion
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CHANNEL_BORDER_STYLE
define|#
directive|define
name|GIMP_TYPE_CHANNEL_BORDER_STYLE
value|(gimp_channel_border_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_channel_border_style_get_type
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
DECL|enum|__anon2b8bc5961d03
block|{
DECL|enumerator|GIMP_CHANNEL_BORDER_STYLE_HARD
name|GIMP_CHANNEL_BORDER_STYLE_HARD
block|,
comment|/*< desc="Hard">*/
DECL|enumerator|GIMP_CHANNEL_BORDER_STYLE_SMOOTH
name|GIMP_CHANNEL_BORDER_STYLE_SMOOTH
block|,
comment|/*< desc="Smooth">*/
DECL|enumerator|GIMP_CHANNEL_BORDER_STYLE_FEATHERED
name|GIMP_CHANNEL_BORDER_STYLE_FEATHERED
comment|/*< desc="Feathered">*/
DECL|typedef|GimpChannelBorderStyle
block|}
name|GimpChannelBorderStyle
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2b8bc5961e03
block|{
DECL|enumerator|GIMP_CONTEXT_PROP_FIRST
name|GIMP_CONTEXT_PROP_FIRST
init|=
literal|2
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_IMAGE
name|GIMP_CONTEXT_PROP_IMAGE
init|=
name|GIMP_CONTEXT_PROP_FIRST
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_DISPLAY
name|GIMP_CONTEXT_PROP_DISPLAY
init|=
literal|3
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_TOOL
name|GIMP_CONTEXT_PROP_TOOL
init|=
literal|4
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PAINT_INFO
name|GIMP_CONTEXT_PROP_PAINT_INFO
init|=
literal|5
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_FOREGROUND
name|GIMP_CONTEXT_PROP_FOREGROUND
init|=
literal|6
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_BACKGROUND
name|GIMP_CONTEXT_PROP_BACKGROUND
init|=
literal|7
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_OPACITY
name|GIMP_CONTEXT_PROP_OPACITY
init|=
literal|8
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PAINT_MODE
name|GIMP_CONTEXT_PROP_PAINT_MODE
init|=
literal|9
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_BRUSH
name|GIMP_CONTEXT_PROP_BRUSH
init|=
literal|10
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_DYNAMICS
name|GIMP_CONTEXT_PROP_DYNAMICS
init|=
literal|11
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MYBRUSH
name|GIMP_CONTEXT_PROP_MYBRUSH
init|=
literal|12
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PATTERN
name|GIMP_CONTEXT_PROP_PATTERN
init|=
literal|13
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_GRADIENT
name|GIMP_CONTEXT_PROP_GRADIENT
init|=
literal|14
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PALETTE
name|GIMP_CONTEXT_PROP_PALETTE
init|=
literal|15
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_TOOL_PRESET
name|GIMP_CONTEXT_PROP_TOOL_PRESET
init|=
literal|16
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_FONT
name|GIMP_CONTEXT_PROP_FONT
init|=
literal|17
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_BUFFER
name|GIMP_CONTEXT_PROP_BUFFER
init|=
literal|18
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_IMAGEFILE
name|GIMP_CONTEXT_PROP_IMAGEFILE
init|=
literal|19
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_TEMPLATE
name|GIMP_CONTEXT_PROP_TEMPLATE
init|=
literal|20
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_LAST
name|GIMP_CONTEXT_PROP_LAST
init|=
name|GIMP_CONTEXT_PROP_TEMPLATE
DECL|typedef|GimpContextPropType
block|}
name|GimpContextPropType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2b8bc5961f03
block|{
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_IMAGE
name|GIMP_CONTEXT_PROP_MASK_IMAGE
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_DISPLAY
name|GIMP_CONTEXT_PROP_MASK_DISPLAY
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_TOOL
name|GIMP_CONTEXT_PROP_MASK_TOOL
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_PAINT_INFO
name|GIMP_CONTEXT_PROP_MASK_PAINT_INFO
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_FOREGROUND
name|GIMP_CONTEXT_PROP_MASK_FOREGROUND
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_BACKGROUND
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_OPACITY
name|GIMP_CONTEXT_PROP_MASK_OPACITY
init|=
literal|1
operator|<<
literal|8
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_PAINT_MODE
name|GIMP_CONTEXT_PROP_MASK_PAINT_MODE
init|=
literal|1
operator|<<
literal|9
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_BRUSH
name|GIMP_CONTEXT_PROP_MASK_BRUSH
init|=
literal|1
operator|<<
literal|10
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_DYNAMICS
name|GIMP_CONTEXT_PROP_MASK_DYNAMICS
init|=
literal|1
operator|<<
literal|11
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_MYBRUSH
name|GIMP_CONTEXT_PROP_MASK_MYBRUSH
init|=
literal|1
operator|<<
literal|12
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_PATTERN
name|GIMP_CONTEXT_PROP_MASK_PATTERN
init|=
literal|1
operator|<<
literal|13
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_GRADIENT
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
init|=
literal|1
operator|<<
literal|14
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_PALETTE
name|GIMP_CONTEXT_PROP_MASK_PALETTE
init|=
literal|1
operator|<<
literal|15
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_TOOL_PRESET
name|GIMP_CONTEXT_PROP_MASK_TOOL_PRESET
init|=
literal|1
operator|<<
literal|16
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_FONT
name|GIMP_CONTEXT_PROP_MASK_FONT
init|=
literal|1
operator|<<
literal|17
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_BUFFER
name|GIMP_CONTEXT_PROP_MASK_BUFFER
init|=
literal|1
operator|<<
literal|18
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_IMAGEFILE
name|GIMP_CONTEXT_PROP_MASK_IMAGEFILE
init|=
literal|1
operator|<<
literal|19
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_TEMPLATE
name|GIMP_CONTEXT_PROP_MASK_TEMPLATE
init|=
literal|1
operator|<<
literal|20
block|,
comment|/*  aliases  */
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_PAINT
name|GIMP_CONTEXT_PROP_MASK_PAINT
init|=
operator|(
name|GIMP_CONTEXT_PROP_MASK_FOREGROUND
operator||
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
operator||
name|GIMP_CONTEXT_PROP_MASK_OPACITY
operator||
name|GIMP_CONTEXT_PROP_MASK_PAINT_MODE
operator||
name|GIMP_CONTEXT_PROP_MASK_BRUSH
operator||
name|GIMP_CONTEXT_PROP_MASK_DYNAMICS
operator||
name|GIMP_CONTEXT_PROP_MASK_PATTERN
operator||
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
operator|)
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_MASK_ALL
name|GIMP_CONTEXT_PROP_MASK_ALL
init|=
operator|(
name|GIMP_CONTEXT_PROP_MASK_IMAGE
operator||
name|GIMP_CONTEXT_PROP_MASK_DISPLAY
operator||
name|GIMP_CONTEXT_PROP_MASK_TOOL
operator||
name|GIMP_CONTEXT_PROP_MASK_PAINT_INFO
operator||
name|GIMP_CONTEXT_PROP_MASK_MYBRUSH
operator||
name|GIMP_CONTEXT_PROP_MASK_PALETTE
operator||
name|GIMP_CONTEXT_PROP_MASK_FONT
operator||
name|GIMP_CONTEXT_PROP_MASK_BUFFER
operator||
name|GIMP_CONTEXT_PROP_MASK_IMAGEFILE
operator||
name|GIMP_CONTEXT_PROP_MASK_TEMPLATE
operator||
name|GIMP_CONTEXT_PROP_MASK_PAINT
operator|)
DECL|typedef|GimpContextPropMask
block|}
name|GimpContextPropMask
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2b8bc5962003
block|{
DECL|enumerator|GIMP_IMAGE_SCALE_OK
name|GIMP_IMAGE_SCALE_OK
block|,
DECL|enumerator|GIMP_IMAGE_SCALE_TOO_SMALL
name|GIMP_IMAGE_SCALE_TOO_SMALL
block|,
DECL|enumerator|GIMP_IMAGE_SCALE_TOO_BIG
name|GIMP_IMAGE_SCALE_TOO_BIG
DECL|typedef|GimpImageScaleCheckType
block|}
name|GimpImageScaleCheckType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2b8bc5962103
block|{
DECL|enumerator|GIMP_ITEM_TYPE_LAYERS
name|GIMP_ITEM_TYPE_LAYERS
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_ITEM_TYPE_CHANNELS
name|GIMP_ITEM_TYPE_CHANNELS
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_ITEM_TYPE_VECTORS
name|GIMP_ITEM_TYPE_VECTORS
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_ITEM_TYPE_ALL
name|GIMP_ITEM_TYPE_ALL
init|=
operator|(
name|GIMP_ITEM_TYPE_LAYERS
operator||
name|GIMP_ITEM_TYPE_CHANNELS
operator||
name|GIMP_ITEM_TYPE_VECTORS
operator|)
DECL|typedef|GimpItemTypeMask
block|}
name|GimpItemTypeMask
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CORE_ENUMS_H__ */
end_comment

end_unit

