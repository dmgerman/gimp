begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
unit|This file is parsed by two scripts, enumgen.pl in tools/pdbgen    and gimp-mkenums. All enums that are not marked with
comment|/*< pdb-skip>*/
end_comment

begin_comment
unit|are exported to libgimp and the PDB. Enums that are not marked with
comment|/*< skip>*/
end_comment

begin_comment
unit|are registered with the GType system. If you want the    enum to be skipped by both scripts, you have to use
comment|/*< pdb-skip>*/
end_comment

begin_comment
unit|_before_
comment|/*< skip>*/
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
DECL|macro|GIMP_TYPE_IMAGE_BASE_TYPE
define|#
directive|define
name|GIMP_TYPE_IMAGE_BASE_TYPE
value|(gimp_image_base_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_image_base_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28c857d60103
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

begin_define
DECL|macro|GIMP_TYPE_PREVIEW_SIZE
define|#
directive|define
name|GIMP_TYPE_PREVIEW_SIZE
value|(gimp_preview_size_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_preview_size_get_type
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
DECL|enum|__anon28c857d60203
block|{
DECL|enumerator|GIMP_PREVIEW_SIZE_NONE
name|GIMP_PREVIEW_SIZE_NONE
init|=
literal|0
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_TINY
name|GIMP_PREVIEW_SIZE_TINY
init|=
literal|16
block|,
comment|/*< desc="Tiny">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_SMALL
name|GIMP_PREVIEW_SIZE_EXTRA_SMALL
init|=
literal|24
block|,
comment|/*< desc="Very Small">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_SMALL
name|GIMP_PREVIEW_SIZE_SMALL
init|=
literal|32
block|,
comment|/*< desc="Small">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_MEDIUM
name|GIMP_PREVIEW_SIZE_MEDIUM
init|=
literal|48
block|,
comment|/*< desc="Medium">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_LARGE
name|GIMP_PREVIEW_SIZE_LARGE
init|=
literal|64
block|,
comment|/*< desc="Large">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_LARGE
name|GIMP_PREVIEW_SIZE_EXTRA_LARGE
init|=
literal|96
block|,
comment|/*< desc="Very Large">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_HUGE
name|GIMP_PREVIEW_SIZE_HUGE
init|=
literal|128
block|,
comment|/*< desc="Huge">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_ENORMOUS
name|GIMP_PREVIEW_SIZE_ENORMOUS
init|=
literal|192
block|,
comment|/*< desc="Enormous">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_GIGANTIC
name|GIMP_PREVIEW_SIZE_GIGANTIC
init|=
literal|256
comment|/*< desc="Gigantic">*/
DECL|typedef|GimpPreviewSize
block|}
name|GimpPreviewSize
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_SELECTION_CONTROL
define|#
directive|define
name|GIMP_TYPE_SELECTION_CONTROL
value|(gimp_selection_control_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_selection_control_get_type
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
DECL|enum|__anon28c857d60303
block|{
DECL|enumerator|GIMP_SELECTION_OFF
name|GIMP_SELECTION_OFF
block|,
DECL|enumerator|GIMP_SELECTION_LAYER_OFF
name|GIMP_SELECTION_LAYER_OFF
block|,
DECL|enumerator|GIMP_SELECTION_ON
name|GIMP_SELECTION_ON
block|,
DECL|enumerator|GIMP_SELECTION_PAUSE
name|GIMP_SELECTION_PAUSE
block|,
DECL|enumerator|GIMP_SELECTION_RESUME
name|GIMP_SELECTION_RESUME
DECL|typedef|GimpSelectionControl
block|}
name|GimpSelectionControl
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CHANNEL_TYPE
define|#
directive|define
name|GIMP_TYPE_CHANNEL_TYPE
value|(gimp_channel_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_channel_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28c857d60403
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

begin_define
DECL|macro|GIMP_TYPE_BLEND_MODE
define|#
directive|define
name|GIMP_TYPE_BLEND_MODE
value|(gimp_blend_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_blend_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28c857d60503
block|{
DECL|enumerator|GIMP_FG_BG_RGB_MODE
name|GIMP_FG_BG_RGB_MODE
block|,
comment|/*< desc="FG to BG (RGB)">*/
DECL|enumerator|GIMP_FG_BG_HSV_MODE
name|GIMP_FG_BG_HSV_MODE
block|,
comment|/*< desc="FG to BG (HSV)">*/
DECL|enumerator|GIMP_FG_TRANSPARENT_MODE
name|GIMP_FG_TRANSPARENT_MODE
block|,
comment|/*< desc="FG to Transparent">*/
DECL|enumerator|GIMP_CUSTOM_MODE
name|GIMP_CUSTOM_MODE
comment|/*< desc="Custom Gradient">*/
DECL|typedef|GimpBlendMode
block|}
name|GimpBlendMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_TYPE
define|#
directive|define
name|GIMP_TYPE_GRADIENT_TYPE
value|(gimp_gradient_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28c857d60603
block|{
DECL|enumerator|GIMP_LINEAR
name|GIMP_LINEAR
block|,
comment|/*< desc="Linear">*/
DECL|enumerator|GIMP_BILINEAR
name|GIMP_BILINEAR
block|,
comment|/*< desc="Bi-Linear">*/
DECL|enumerator|GIMP_RADIAL
name|GIMP_RADIAL
block|,
comment|/*< desc="Radial">*/
DECL|enumerator|GIMP_SQUARE
name|GIMP_SQUARE
block|,
comment|/*< desc="Square">*/
DECL|enumerator|GIMP_CONICAL_SYMMETRIC
name|GIMP_CONICAL_SYMMETRIC
block|,
comment|/*< desc="Conical (symmetric)">*/
DECL|enumerator|GIMP_CONICAL_ASYMMETRIC
name|GIMP_CONICAL_ASYMMETRIC
block|,
comment|/*< desc="Conical (asymmetric)">*/
DECL|enumerator|GIMP_SHAPEBURST_ANGULAR
name|GIMP_SHAPEBURST_ANGULAR
block|,
comment|/*< desc="Shapeburst (angular)">*/
DECL|enumerator|GIMP_SHAPEBURST_SPHERICAL
name|GIMP_SHAPEBURST_SPHERICAL
block|,
comment|/*< desc="Shapeburst (spherical)">*/
DECL|enumerator|GIMP_SHAPEBURST_DIMPLED
name|GIMP_SHAPEBURST_DIMPLED
block|,
comment|/*< desc="Shapeburst (dimpled)">*/
DECL|enumerator|GIMP_SPIRAL_CLOCKWISE
name|GIMP_SPIRAL_CLOCKWISE
block|,
comment|/*< desc="Spiral (clockwise)">*/
DECL|enumerator|GIMP_SPIRAL_ANTICLOCKWISE
name|GIMP_SPIRAL_ANTICLOCKWISE
comment|/*< desc="Spiral (anticlockwise)">*/
DECL|typedef|GimpGradientType
block|}
name|GimpGradientType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_REPEAT_MODE
define|#
directive|define
name|GIMP_TYPE_REPEAT_MODE
value|(gimp_repeat_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_repeat_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28c857d60703
block|{
DECL|enumerator|GIMP_REPEAT_NONE
name|GIMP_REPEAT_NONE
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_REPEAT_SAWTOOTH
name|GIMP_REPEAT_SAWTOOTH
block|,
comment|/*< desc="Sawtooth Wave">*/
DECL|enumerator|GIMP_REPEAT_TRIANGULAR
name|GIMP_REPEAT_TRIANGULAR
comment|/*< desc="Triangular Wave">*/
DECL|typedef|GimpRepeatMode
block|}
name|GimpRepeatMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_DIRECTION
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_DIRECTION
value|(gimp_transform_direction_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_direction_get_type
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
DECL|enum|__anon28c857d60803
block|{
DECL|enumerator|GIMP_TRANSFORM_FORWARD
name|GIMP_TRANSFORM_FORWARD
block|,
comment|/*< desc="Forward (Traditional)">*/
DECL|enumerator|GIMP_TRANSFORM_BACKWARD
name|GIMP_TRANSFORM_BACKWARD
comment|/*< desc="Backward (Corrective)">*/
DECL|typedef|GimpTransformDirection
block|}
name|GimpTransformDirection
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28c857d60903
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
comment|/*< skip>*/
DECL|enum|__anon28c857d60a03
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
comment|/*< skip>*/
DECL|enum|__anon28c857d60b03
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
comment|/*< skip>*/
DECL|enum|__anon28c857d60c03
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
comment|/* NEVER USE NODESTRUCT_DITHER EXPLICITLY */
DECL|typedef|GimpConvertDitherType
block|}
name|GimpConvertDitherType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28c857d60d03
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
DECL|enumerator|GIMP_NO_FILL
name|GIMP_NO_FILL
DECL|typedef|GimpFillType
block|}
name|GimpFillType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon28c857d60e03
block|{
DECL|enumerator|GIMP_GRAD_LINEAR
name|GIMP_GRAD_LINEAR
init|=
literal|0
block|,
DECL|enumerator|GIMP_GRAD_CURVED
name|GIMP_GRAD_CURVED
block|,
DECL|enumerator|GIMP_GRAD_SINE
name|GIMP_GRAD_SINE
block|,
DECL|enumerator|GIMP_GRAD_SPHERE_INCREASING
name|GIMP_GRAD_SPHERE_INCREASING
block|,
DECL|enumerator|GIMP_GRAD_SPHERE_DECREASING
name|GIMP_GRAD_SPHERE_DECREASING
DECL|typedef|GimpGradientSegmentType
block|}
name|GimpGradientSegmentType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon28c857d60f03
block|{
DECL|enumerator|GIMP_GRAD_RGB
name|GIMP_GRAD_RGB
block|,
comment|/* normal RGB           */
DECL|enumerator|GIMP_GRAD_HSV_CCW
name|GIMP_GRAD_HSV_CCW
block|,
comment|/* counterclockwise hue */
DECL|enumerator|GIMP_GRAD_HSV_CW
name|GIMP_GRAD_HSV_CW
comment|/* clockwise hue        */
DECL|typedef|GimpGradientSegmentColor
block|}
name|GimpGradientSegmentColor
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28c857d61003
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
comment|/*< skip>*/
DECL|enum|__anon28c857d61103
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
DECL|enumerator|GIMP_ADD_SELECTION_MASK
name|GIMP_ADD_SELECTION_MASK
block|,
DECL|enumerator|GIMP_ADD_INVERSE_SELECTION_MASK
name|GIMP_ADD_INVERSE_SELECTION_MASK
block|,
DECL|enumerator|GIMP_ADD_COPY_MASK
name|GIMP_ADD_COPY_MASK
block|,
DECL|enumerator|GIMP_ADD_INVERSE_COPY_MASK
name|GIMP_ADD_INVERSE_COPY_MASK
DECL|typedef|GimpAddMaskType
block|}
name|GimpAddMaskType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28c857d61203
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
comment|/*< skip>*/
DECL|enum|__anon28c857d61303
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CORE_TYPES_H__ */
end_comment

end_unit

