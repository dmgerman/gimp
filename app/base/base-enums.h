begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
unit|are registered with the GType system.     If you want the enum to be skipped by both scripts, you have to use
comment|/*< pdb-skip, skip>*/
end_comment

begin_comment
unit|.      All enum values that are marked with
comment|/*< skip>*/
end_comment

begin_endif
unit|are skipped for    both targets.
endif|#
directive|endif
end_endif

begin_comment
comment|/*   * these enums that are registered with the type system  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_CHECK_SIZE
define|#
directive|define
name|GIMP_TYPE_CHECK_SIZE
value|(gimp_check_size_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_check_size_get_type
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
DECL|enum|__anon2c3a741b0103
block|{
DECL|enumerator|GIMP_SMALL_CHECKS
name|GIMP_SMALL_CHECKS
init|=
literal|0
block|,
comment|/*< desc="Small">*/
DECL|enumerator|GIMP_MEDIUM_CHECKS
name|GIMP_MEDIUM_CHECKS
init|=
literal|1
block|,
comment|/*< desc="Medium">*/
DECL|enumerator|GIMP_LARGE_CHECKS
name|GIMP_LARGE_CHECKS
init|=
literal|2
comment|/*< desc="Large">*/
DECL|typedef|GimpCheckSize
block|}
name|GimpCheckSize
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CHECK_TYPE
define|#
directive|define
name|GIMP_TYPE_CHECK_TYPE
value|(gimp_check_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_check_type_get_type
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
DECL|enum|__anon2c3a741b0203
block|{
DECL|enumerator|GIMP_LIGHT_CHECKS
name|GIMP_LIGHT_CHECKS
init|=
literal|0
block|,
comment|/*< desc="Light Checks">*/
DECL|enumerator|GIMP_GRAY_CHECKS
name|GIMP_GRAY_CHECKS
init|=
literal|1
block|,
comment|/*< desc="Mid-Tone Checks">*/
DECL|enumerator|GIMP_DARK_CHECKS
name|GIMP_DARK_CHECKS
init|=
literal|2
block|,
comment|/*< desc="Dark Checks">*/
DECL|enumerator|GIMP_WHITE_ONLY
name|GIMP_WHITE_ONLY
init|=
literal|3
block|,
comment|/*< desc="White Only">*/
DECL|enumerator|GIMP_GRAY_ONLY
name|GIMP_GRAY_ONLY
init|=
literal|4
block|,
comment|/*< desc="Gray Only">*/
DECL|enumerator|GIMP_BLACK_ONLY
name|GIMP_BLACK_ONLY
init|=
literal|5
comment|/*< desc="Black Only">*/
DECL|typedef|GimpCheckType
block|}
name|GimpCheckType
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
DECL|enum|__anon2c3a741b0303
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
comment|/*< pdb-skip>*/
DECL|enum|__anon2c3a741b0403
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
comment|/*< desc="Alpha">*/
DECL|typedef|GimpHistogramChannel
block|}
name|GimpHistogramChannel
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_INTERPOLATION_TYPE
define|#
directive|define
name|GIMP_TYPE_INTERPOLATION_TYPE
value|(gimp_interpolation_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_interpolation_type_get_type
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
DECL|enum|__anon2c3a741b0503
block|{
DECL|enumerator|GIMP_INTERPOLATION_NONE
name|GIMP_INTERPOLATION_NONE
block|,
comment|/*< desc="None (Fastest)">*/
DECL|enumerator|GIMP_INTERPOLATION_LINEAR
name|GIMP_INTERPOLATION_LINEAR
block|,
comment|/*< desc="Linear">*/
DECL|enumerator|GIMP_INTERPOLATION_CUBIC
name|GIMP_INTERPOLATION_CUBIC
comment|/*< desc="Cubic (Best)">*/
DECL|typedef|GimpInterpolationType
block|}
name|GimpInterpolationType
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
DECL|enum|__anon2c3a741b0603
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
block|,
DECL|enumerator|GIMP_ERASE_MODE
name|GIMP_ERASE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_REPLACE_MODE
name|GIMP_REPLACE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_ANTI_ERASE_MODE
name|GIMP_ANTI_ERASE_MODE
comment|/*< skip>*/
DECL|typedef|GimpLayerModeEffects
block|}
name|GimpLayerModeEffects
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFER_MODE
define|#
directive|define
name|GIMP_TYPE_TRANSFER_MODE
value|(gimp_transfer_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transfer_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c3a741b0703
block|{
DECL|enumerator|GIMP_SHADOWS
name|GIMP_SHADOWS
block|,
comment|/*< desc="Shadows">*/
DECL|enumerator|GIMP_MIDTONES
name|GIMP_MIDTONES
block|,
comment|/*< desc="Midtones">*/
DECL|enumerator|GIMP_HIGHLIGHTS
name|GIMP_HIGHLIGHTS
comment|/*< desc="Highlights">*/
DECL|typedef|GimpTransferMode
block|}
name|GimpTransferMode
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2c3a741b0803
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
comment|/*< skip>*/
DECL|enum|__anon2c3a741b0903
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
block|,
DECL|enumerator|GIMP_GRAY_LUT
name|GIMP_GRAY_LUT
init|=
literal|0
comment|/*< skip>*/
DECL|typedef|GimpChannelLutType
block|}
name|GimpChannelLutType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2c3a741b0a03
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __BASE_ENUMS_H__ */
end_comment

end_unit

