begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BASE_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__BASE_ENUMS_H__
define|#
directive|define
name|__BASE_ENUMS_H__
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
comment|/*  * these enums that are registered with the type system  */
end_comment

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
DECL|enum|__anon2c1abadc0103
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
DECL|enum|__anon2c1abadc0203
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
DECL|enumerator|GIMP_HISTOGRAM_RGB
name|GIMP_HISTOGRAM_RGB
init|=
literal|5
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
DECL|enum|__anon2c1abadc0303
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
comment|/*< desc="Overlay">*/
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
comment|/*< desc="Hue">*/
DECL|enumerator|GIMP_SATURATION_MODE
name|GIMP_SATURATION_MODE
block|,
comment|/*< desc="Saturation">*/
DECL|enumerator|GIMP_COLOR_MODE
name|GIMP_COLOR_MODE
block|,
comment|/*< desc="Color">*/
DECL|enumerator|GIMP_VALUE_MODE
name|GIMP_VALUE_MODE
block|,
comment|/*< desc="Value">*/
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
DECL|enumerator|GIMP_ERASE_MODE
name|GIMP_ERASE_MODE
block|,
comment|/*< pdb-skip, desc="Erase">*/
DECL|enumerator|GIMP_REPLACE_MODE
name|GIMP_REPLACE_MODE
block|,
comment|/*< pdb-skip, desc="Replace">*/
DECL|enumerator|GIMP_ANTI_ERASE_MODE
name|GIMP_ANTI_ERASE_MODE
comment|/*< pdb-skip, desc="Anti erase">*/
DECL|typedef|GimpLayerModeEffects
block|}
name|GimpLayerModeEffects
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
DECL|enum|__anon2c1abadc0403
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

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2c1abadc0503
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
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2c1abadc0603
block|{
DECL|enumerator|SIOX_REFINEMENT_NO_CHANGE
name|SIOX_REFINEMENT_NO_CHANGE
init|=
literal|0
block|,
DECL|enumerator|SIOX_REFINEMENT_ADD_FOREGROUND
name|SIOX_REFINEMENT_ADD_FOREGROUND
init|=
operator|(
literal|1
operator|<<
literal|0
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_ADD_BACKGROUND
name|SIOX_REFINEMENT_ADD_BACKGROUND
init|=
operator|(
literal|1
operator|<<
literal|1
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_CHANGE_SENSITIVITY
name|SIOX_REFINEMENT_CHANGE_SENSITIVITY
init|=
operator|(
literal|1
operator|<<
literal|2
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_CHANGE_SMOOTHNESS
name|SIOX_REFINEMENT_CHANGE_SMOOTHNESS
init|=
operator|(
literal|1
operator|<<
literal|3
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_CHANGE_MULTIBLOB
name|SIOX_REFINEMENT_CHANGE_MULTIBLOB
init|=
operator|(
literal|1
operator|<<
literal|4
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_RECALCULATE
name|SIOX_REFINEMENT_RECALCULATE
init|=
literal|0xFF
DECL|typedef|SioxRefinementType
block|}
name|SioxRefinementType
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __BASE_ENUMS_H__ */
end_comment

end_unit

