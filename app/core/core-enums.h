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
DECL|macro|GIMP_TYPE_ADD_MASK_TYPE
define|#
directive|define
name|GIMP_TYPE_ADD_MASK_TYPE
value|(gimp_add_mask_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_add_mask_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bc4401d0103
block|{
DECL|enumerator|GIMP_ADD_WHITE_MASK
name|GIMP_ADD_WHITE_MASK
block|,
comment|/*< desc="_White (Full Opacity)">*/
DECL|enumerator|GIMP_ADD_BLACK_MASK
name|GIMP_ADD_BLACK_MASK
block|,
comment|/*< desc="_Black (Full Transparency)">*/
DECL|enumerator|GIMP_ADD_ALPHA_MASK
name|GIMP_ADD_ALPHA_MASK
block|,
comment|/*< desc="Layer's _Alpha Channel">*/
DECL|enumerator|GIMP_ADD_SELECTION_MASK
name|GIMP_ADD_SELECTION_MASK
block|,
comment|/*< desc="_Selection">*/
DECL|enumerator|GIMP_ADD_COPY_MASK
name|GIMP_ADD_COPY_MASK
comment|/*< desc="_Grayscale Copy of Layer">*/
DECL|typedef|GimpAddMaskType
block|}
name|GimpAddMaskType
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
DECL|enum|__anon2bc4401d0203
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
DECL|macro|GIMP_TYPE_BUCKET_FILL_MODE
define|#
directive|define
name|GIMP_TYPE_BUCKET_FILL_MODE
value|(gimp_bucket_fill_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_bucket_fill_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bc4401d0303
block|{
DECL|enumerator|GIMP_FG_BUCKET_FILL
name|GIMP_FG_BUCKET_FILL
block|,
comment|/*< desc="FG Color Fill">*/
DECL|enumerator|GIMP_BG_BUCKET_FILL
name|GIMP_BG_BUCKET_FILL
block|,
comment|/*< desc="BG Color Fill">*/
DECL|enumerator|GIMP_PATTERN_BUCKET_FILL
name|GIMP_PATTERN_BUCKET_FILL
comment|/*< desc="Pattern Fill">*/
DECL|typedef|GimpBucketFillMode
block|}
name|GimpBucketFillMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CHANNEL_OPS
define|#
directive|define
name|GIMP_TYPE_CHANNEL_OPS
value|(gimp_channel_ops_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_channel_ops_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bc4401d0403
block|{
DECL|enumerator|GIMP_CHANNEL_OP_ADD
name|GIMP_CHANNEL_OP_ADD
block|,
comment|/*< desc="Add to the current selection">*/
DECL|enumerator|GIMP_CHANNEL_OP_SUBTRACT
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
comment|/*< desc="Subtract from the current selection">*/
DECL|enumerator|GIMP_CHANNEL_OP_REPLACE
name|GIMP_CHANNEL_OP_REPLACE
block|,
comment|/*< desc="Replace the current selection">*/
DECL|enumerator|GIMP_CHANNEL_OP_INTERSECT
name|GIMP_CHANNEL_OP_INTERSECT
comment|/*< desc="Intersect with the current selection">*/
DECL|typedef|GimpChannelOps
block|}
name|GimpChannelOps
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
DECL|enum|__anon2bc4401d0503
block|{
DECL|enumerator|GIMP_RED_CHANNEL
name|GIMP_RED_CHANNEL
block|,
comment|/*< desc="Red">*/
DECL|enumerator|GIMP_GREEN_CHANNEL
name|GIMP_GREEN_CHANNEL
block|,
comment|/*< desc="Green">*/
DECL|enumerator|GIMP_BLUE_CHANNEL
name|GIMP_BLUE_CHANNEL
block|,
comment|/*< desc="Blue">*/
DECL|enumerator|GIMP_GRAY_CHANNEL
name|GIMP_GRAY_CHANNEL
block|,
comment|/*< desc="Gray">*/
DECL|enumerator|GIMP_INDEXED_CHANNEL
name|GIMP_INDEXED_CHANNEL
block|,
comment|/*< desc="Indexed">*/
DECL|enumerator|GIMP_ALPHA_CHANNEL
name|GIMP_ALPHA_CHANNEL
comment|/*< desc="Alpha">*/
DECL|typedef|GimpChannelType
block|}
name|GimpChannelType
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
DECL|enum|__anon2bc4401d0603
block|{
DECL|enumerator|GIMP_NO_DITHER
name|GIMP_NO_DITHER
block|,
comment|/*< desc="No Color Dithering">*/
DECL|enumerator|GIMP_FS_DITHER
name|GIMP_FS_DITHER
block|,
comment|/*< desc="Floyd-Steinberg Color Dithering (Normal)">*/
DECL|enumerator|GIMP_FSLOWBLEED_DITHER
name|GIMP_FSLOWBLEED_DITHER
block|,
comment|/*< desc="Floyd-Steinberg Color Dithering (Reduced Color Bleeding)">*/
DECL|enumerator|GIMP_FIXED_DITHER
name|GIMP_FIXED_DITHER
block|,
comment|/*< desc="Positioned Color Dithering">*/
DECL|enumerator|GIMP_NODESTRUCT_DITHER
name|GIMP_NODESTRUCT_DITHER
comment|/*< skip>*/
DECL|typedef|GimpConvertDitherType
block|}
name|GimpConvertDitherType
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
DECL|enum|__anon2bc4401d0703
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
DECL|enum|__anon2bc4401d0803
block|{
DECL|enumerator|GIMP_FOREGROUND_FILL
name|GIMP_FOREGROUND_FILL
block|,
comment|/*< desc="Foreground">*/
DECL|enumerator|GIMP_BACKGROUND_FILL
name|GIMP_BACKGROUND_FILL
block|,
comment|/*< desc="Background">*/
DECL|enumerator|GIMP_WHITE_FILL
name|GIMP_WHITE_FILL
block|,
comment|/*< desc="White">*/
DECL|enumerator|GIMP_TRANSPARENT_FILL
name|GIMP_TRANSPARENT_FILL
block|,
comment|/*< desc="Transparent">*/
DECL|enumerator|GIMP_NO_FILL
name|GIMP_NO_FILL
comment|/*< desc="None">*/
DECL|typedef|GimpFillType
block|}
name|GimpFillType
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
DECL|enum|__anon2bc4401d0903
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
DECL|macro|GIMP_TYPE_GRID_TYPE
define|#
directive|define
name|GIMP_TYPE_GRID_TYPE
value|(gimp_grid_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_grid_type_get_type
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
DECL|enum|__anon2bc4401d0a03
block|{
DECL|enumerator|GIMP_GRID_TYPE_DOTS
name|GIMP_GRID_TYPE_DOTS
block|,
comment|/*< desc="Dots">*/
DECL|enumerator|GIMP_GRID_TYPE_INTERSECTIONS
name|GIMP_GRID_TYPE_INTERSECTIONS
block|,
comment|/*< desc="Intersections Only">*/
DECL|enumerator|GIMP_GRID_TYPE_ON_OFF_DASH
name|GIMP_GRID_TYPE_ON_OFF_DASH
block|,
comment|/*< desc="Dashed">*/
DECL|enumerator|GIMP_GRID_TYPE_DOUBLE_DASH
name|GIMP_GRID_TYPE_DOUBLE_DASH
block|,
comment|/*< desc="Double Dashed">*/
DECL|enumerator|GIMP_GRID_TYPE_SOLID
name|GIMP_GRID_TYPE_SOLID
comment|/*< desc="Solid">*/
DECL|typedef|GimpGridType
block|}
name|GimpGridType
typedef|;
end_typedef

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
DECL|enum|__anon2bc4401d0b03
block|{
DECL|enumerator|GIMP_RGB
name|GIMP_RGB
block|,
comment|/*< desc="RGB">*/
DECL|enumerator|GIMP_GRAY
name|GIMP_GRAY
block|,
comment|/*< desc="Grayscale">*/
DECL|enumerator|GIMP_INDEXED
name|GIMP_INDEXED
comment|/*< desc="Indexed">*/
DECL|typedef|GimpImageBaseType
block|}
name|GimpImageBaseType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_IMAGE_TYPE
define|#
directive|define
name|GIMP_TYPE_IMAGE_TYPE
value|(gimp_image_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_image_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bc4401d0c03
block|{
DECL|enumerator|GIMP_RGB_IMAGE
name|GIMP_RGB_IMAGE
block|,
comment|/*< desc="RGB">*/
DECL|enumerator|GIMP_RGBA_IMAGE
name|GIMP_RGBA_IMAGE
block|,
comment|/*< desc="RGB-Alpha">*/
DECL|enumerator|GIMP_GRAY_IMAGE
name|GIMP_GRAY_IMAGE
block|,
comment|/*< desc="Grayscale">*/
DECL|enumerator|GIMP_GRAYA_IMAGE
name|GIMP_GRAYA_IMAGE
block|,
comment|/*< desc="Grayscale-Alpha">*/
DECL|enumerator|GIMP_INDEXED_IMAGE
name|GIMP_INDEXED_IMAGE
block|,
comment|/*< desc="Indexed">*/
DECL|enumerator|GIMP_INDEXEDA_IMAGE
name|GIMP_INDEXEDA_IMAGE
comment|/*< desc="Indexed-Alpha">*/
DECL|typedef|GimpImageType
block|}
name|GimpImageType
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
DECL|enum|__anon2bc4401d0d03
block|{
DECL|enumerator|GIMP_ORIENTATION_HORIZONTAL
name|GIMP_ORIENTATION_HORIZONTAL
block|,
comment|/*< desc="Horizontal">*/
DECL|enumerator|GIMP_ORIENTATION_VERTICAL
name|GIMP_ORIENTATION_VERTICAL
block|,
comment|/*< desc="Vertical">*/
DECL|enumerator|GIMP_ORIENTATION_UNKNOWN
name|GIMP_ORIENTATION_UNKNOWN
comment|/*< desc="Unknown">*/
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
comment|/*< pdb-skip>*/
DECL|enum|__anon2bc4401d0e03
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
DECL|enum|__anon2bc4401d0f03
block|{
DECL|enumerator|GIMP_PREVIEW_SIZE_TINY
name|GIMP_PREVIEW_SIZE_TINY
init|=
literal|12
block|,
comment|/*< desc="Tiny">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_SMALL
name|GIMP_PREVIEW_SIZE_EXTRA_SMALL
init|=
literal|16
block|,
comment|/*< desc="Very Small">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_SMALL
name|GIMP_PREVIEW_SIZE_SMALL
init|=
literal|24
block|,
comment|/*< desc="Small">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_MEDIUM
name|GIMP_PREVIEW_SIZE_MEDIUM
init|=
literal|32
block|,
comment|/*< desc="Medium">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_LARGE
name|GIMP_PREVIEW_SIZE_LARGE
init|=
literal|48
block|,
comment|/*< desc="Large">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_LARGE
name|GIMP_PREVIEW_SIZE_EXTRA_LARGE
init|=
literal|64
block|,
comment|/*< desc="Very Large">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_HUGE
name|GIMP_PREVIEW_SIZE_HUGE
init|=
literal|96
block|,
comment|/*< desc="Huge">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_ENORMOUS
name|GIMP_PREVIEW_SIZE_ENORMOUS
init|=
literal|128
block|,
comment|/*< desc="Enormous">*/
DECL|enumerator|GIMP_PREVIEW_SIZE_GIGANTIC
name|GIMP_PREVIEW_SIZE_GIGANTIC
init|=
literal|192
comment|/*< desc="Gigantic">*/
DECL|typedef|GimpPreviewSize
block|}
name|GimpPreviewSize
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
DECL|enum|__anon2bc4401d1003
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
DECL|enum|__anon2bc4401d1103
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
DECL|enum|__anon2bc4401d1203
block|{
DECL|enumerator|GIMP_THUMBNAIL_SIZE_NONE
name|GIMP_THUMBNAIL_SIZE_NONE
init|=
literal|0
block|,
comment|/*< desc="No Thumbnails">*/
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
DECL|enum|__anon2bc4401d1303
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
DECL|enum|__anon2bc4401d1403
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
DECL|enum|__anon2bc4401d1503
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
comment|/* all undo and redo info has been cleared     */
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
DECL|enum|__anon2bc4401d1603
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
comment|/*< desc="Scale Image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_RESIZE
name|GIMP_UNDO_GROUP_IMAGE_RESIZE
block|,
comment|/*< desc="Resize Image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_FLIP
name|GIMP_UNDO_GROUP_IMAGE_FLIP
block|,
comment|/*< desc="Flip Image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_ROTATE
name|GIMP_UNDO_GROUP_IMAGE_ROTATE
block|,
comment|/*< desc="Rotate Image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_CONVERT
name|GIMP_UNDO_GROUP_IMAGE_CONVERT
block|,
comment|/*< desc="Convert Image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_CROP
name|GIMP_UNDO_GROUP_IMAGE_CROP
block|,
comment|/*< desc="Crop Image">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_LAYERS_MERGE
name|GIMP_UNDO_GROUP_IMAGE_LAYERS_MERGE
block|,
comment|/*< desc="Merge Layers">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_QMASK
name|GIMP_UNDO_GROUP_IMAGE_QMASK
block|,
comment|/*< desc="QuickMask">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_GRID
name|GIMP_UNDO_GROUP_IMAGE_GRID
block|,
comment|/*< desc="Grid">*/
DECL|enumerator|GIMP_UNDO_GROUP_IMAGE_GUIDE
name|GIMP_UNDO_GROUP_IMAGE_GUIDE
block|,
comment|/*< desc="Guide">*/
DECL|enumerator|GIMP_UNDO_GROUP_MASK
name|GIMP_UNDO_GROUP_MASK
block|,
comment|/*< desc="Selection Mask">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_PROPERTIES
name|GIMP_UNDO_GROUP_ITEM_PROPERTIES
block|,
comment|/*< desc="Item Properties">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_DISPLACE
name|GIMP_UNDO_GROUP_ITEM_DISPLACE
block|,
comment|/*< desc="Move Item">*/
DECL|enumerator|GIMP_UNDO_GROUP_ITEM_LINKED
name|GIMP_UNDO_GROUP_ITEM_LINKED
block|,
comment|/*< desc="Linked Item">*/
DECL|enumerator|GIMP_UNDO_GROUP_DRAWABLE_VISIBILITY
name|GIMP_UNDO_GROUP_DRAWABLE_VISIBILITY
block|,
comment|/*< desc="Drawable Visibility">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_SCALE
name|GIMP_UNDO_GROUP_LAYER_SCALE
block|,
comment|/*< desc="Scale Layer">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_RESIZE
name|GIMP_UNDO_GROUP_LAYER_RESIZE
block|,
comment|/*< desc="Resize Layer">*/
DECL|enumerator|GIMP_UNDO_GROUP_LAYER_APPLY_MASK
name|GIMP_UNDO_GROUP_LAYER_APPLY_MASK
block|,
comment|/*< desc="Apply Layer Mask">*/
DECL|enumerator|GIMP_UNDO_GROUP_FS_TO_LAYER
name|GIMP_UNDO_GROUP_FS_TO_LAYER
block|,
comment|/*< desc="Floating Selection to Layer">*/
DECL|enumerator|GIMP_UNDO_GROUP_FS_FLOAT
name|GIMP_UNDO_GROUP_FS_FLOAT
block|,
comment|/*< desc="Float Selection">*/
DECL|enumerator|GIMP_UNDO_GROUP_FS_ANCHOR
name|GIMP_UNDO_GROUP_FS_ANCHOR
block|,
comment|/*< desc="Anchor Floating Selection">*/
DECL|enumerator|GIMP_UNDO_GROUP_EDIT_PASTE
name|GIMP_UNDO_GROUP_EDIT_PASTE
block|,
comment|/*< desc="Paste">*/
DECL|enumerator|GIMP_UNDO_GROUP_EDIT_CUT
name|GIMP_UNDO_GROUP_EDIT_CUT
block|,
comment|/*< desc="Cut">*/
DECL|enumerator|GIMP_UNDO_GROUP_EDIT_COPY
name|GIMP_UNDO_GROUP_EDIT_COPY
block|,
comment|/*< desc="Copy">*/
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
comment|/*< desc="Attach Parasite">*/
DECL|enumerator|GIMP_UNDO_GROUP_PARASITE_REMOVE
name|GIMP_UNDO_GROUP_PARASITE_REMOVE
block|,
comment|/*< desc="Remove Parasite">*/
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
DECL|enumerator|GIMP_UNDO_IMAGE
name|GIMP_UNDO_IMAGE
block|,
comment|/*< desc="Image">*/
DECL|enumerator|GIMP_UNDO_IMAGE_MOD
name|GIMP_UNDO_IMAGE_MOD
block|,
comment|/*< desc="Image Mod">*/
DECL|enumerator|GIMP_UNDO_IMAGE_TYPE
name|GIMP_UNDO_IMAGE_TYPE
block|,
comment|/*< desc="Image Type">*/
DECL|enumerator|GIMP_UNDO_IMAGE_SIZE
name|GIMP_UNDO_IMAGE_SIZE
block|,
comment|/*< desc="Image Size">*/
DECL|enumerator|GIMP_UNDO_IMAGE_RESOLUTION
name|GIMP_UNDO_IMAGE_RESOLUTION
block|,
comment|/*< desc="Resolution Change">*/
DECL|enumerator|GIMP_UNDO_IMAGE_QMASK
name|GIMP_UNDO_IMAGE_QMASK
block|,
comment|/*< desc="QuickMask">*/
DECL|enumerator|GIMP_UNDO_IMAGE_GRID
name|GIMP_UNDO_IMAGE_GRID
block|,
comment|/*< desc="Grid">*/
DECL|enumerator|GIMP_UNDO_IMAGE_GUIDE
name|GIMP_UNDO_IMAGE_GUIDE
block|,
comment|/*< desc="Guide">*/
DECL|enumerator|GIMP_UNDO_IMAGE_COLORMAP
name|GIMP_UNDO_IMAGE_COLORMAP
block|,
comment|/*< desc="Change Indexed Palette">*/
DECL|enumerator|GIMP_UNDO_MASK
name|GIMP_UNDO_MASK
block|,
comment|/*< desc="Selection Mask">*/
DECL|enumerator|GIMP_UNDO_ITEM_RENAME
name|GIMP_UNDO_ITEM_RENAME
block|,
comment|/*< desc="Rename Item">*/
DECL|enumerator|GIMP_UNDO_ITEM_DISPLACE
name|GIMP_UNDO_ITEM_DISPLACE
block|,
comment|/*< desc="Move Item">*/
DECL|enumerator|GIMP_UNDO_ITEM_LINKED
name|GIMP_UNDO_ITEM_LINKED
block|,
comment|/*< desc="Set Item Linked">*/
DECL|enumerator|GIMP_UNDO_DRAWABLE_VISIBILITY
name|GIMP_UNDO_DRAWABLE_VISIBILITY
block|,
comment|/*< desc="Drawable Visibility">*/
DECL|enumerator|GIMP_UNDO_LAYER_ADD
name|GIMP_UNDO_LAYER_ADD
block|,
comment|/*< desc="New Layer">*/
DECL|enumerator|GIMP_UNDO_LAYER_REMOVE
name|GIMP_UNDO_LAYER_REMOVE
block|,
comment|/*< desc="Delete Layer">*/
DECL|enumerator|GIMP_UNDO_LAYER_MOD
name|GIMP_UNDO_LAYER_MOD
block|,
comment|/*< desc="Layer Mod">*/
DECL|enumerator|GIMP_UNDO_LAYER_MASK_ADD
name|GIMP_UNDO_LAYER_MASK_ADD
block|,
comment|/*< desc="Add Layer Mask">*/
DECL|enumerator|GIMP_UNDO_LAYER_MASK_REMOVE
name|GIMP_UNDO_LAYER_MASK_REMOVE
block|,
comment|/*< desc="Delete Layer Mask">*/
DECL|enumerator|GIMP_UNDO_LAYER_REPOSITION
name|GIMP_UNDO_LAYER_REPOSITION
block|,
comment|/*< desc="Reposition Layer">*/
DECL|enumerator|GIMP_UNDO_LAYER_MODE
name|GIMP_UNDO_LAYER_MODE
block|,
comment|/*< desc="Set Layer Mode">*/
DECL|enumerator|GIMP_UNDO_LAYER_OPACITY
name|GIMP_UNDO_LAYER_OPACITY
block|,
comment|/*< desc="Set Layer Opacity">*/
DECL|enumerator|GIMP_UNDO_LAYER_PRESERVE_TRANS
name|GIMP_UNDO_LAYER_PRESERVE_TRANS
block|,
comment|/*< desc="Set Preserve Trans">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_ADD
name|GIMP_UNDO_CHANNEL_ADD
block|,
comment|/*< desc="New Channel">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_REMOVE
name|GIMP_UNDO_CHANNEL_REMOVE
block|,
comment|/*< desc="Delete Channel">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_MOD
name|GIMP_UNDO_CHANNEL_MOD
block|,
comment|/*< desc="Channel Mod">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_REPOSITION
name|GIMP_UNDO_CHANNEL_REPOSITION
block|,
comment|/*< desc="Reposition Channel">*/
DECL|enumerator|GIMP_UNDO_CHANNEL_COLOR
name|GIMP_UNDO_CHANNEL_COLOR
block|,
comment|/*< desc="Channel Color">*/
DECL|enumerator|GIMP_UNDO_VECTORS_ADD
name|GIMP_UNDO_VECTORS_ADD
block|,
comment|/*< desc="New Vectors">*/
DECL|enumerator|GIMP_UNDO_VECTORS_REMOVE
name|GIMP_UNDO_VECTORS_REMOVE
block|,
comment|/*< desc="Delete Vectors">*/
DECL|enumerator|GIMP_UNDO_VECTORS_MOD
name|GIMP_UNDO_VECTORS_MOD
block|,
comment|/*< desc="Vectors Mod">*/
DECL|enumerator|GIMP_UNDO_VECTORS_REPOSITION
name|GIMP_UNDO_VECTORS_REPOSITION
block|,
comment|/*< desc="Reposition Vectors">*/
DECL|enumerator|GIMP_UNDO_FS_TO_LAYER
name|GIMP_UNDO_FS_TO_LAYER
block|,
comment|/*< desc="FS to Layer">*/
DECL|enumerator|GIMP_UNDO_FS_RIGOR
name|GIMP_UNDO_FS_RIGOR
block|,
comment|/*< desc="FS Rigor">*/
DECL|enumerator|GIMP_UNDO_FS_RELAX
name|GIMP_UNDO_FS_RELAX
block|,
comment|/*< desc="FS Relax">*/
DECL|enumerator|GIMP_UNDO_TRANSFORM
name|GIMP_UNDO_TRANSFORM
block|,
comment|/*< desc="Transform">*/
DECL|enumerator|GIMP_UNDO_PAINT
name|GIMP_UNDO_PAINT
block|,
comment|/*< desc="Paint">*/
DECL|enumerator|GIMP_UNDO_PARASITE_ATTACH
name|GIMP_UNDO_PARASITE_ATTACH
block|,
comment|/*< desc="Attach Parasite">*/
DECL|enumerator|GIMP_UNDO_PARASITE_REMOVE
name|GIMP_UNDO_PARASITE_REMOVE
block|,
comment|/*< desc="Remove Parasite">*/
DECL|enumerator|GIMP_UNDO_CANT
name|GIMP_UNDO_CANT
comment|/*< desc="EEK: can't undo">*/
DECL|typedef|GimpUndoType
block|}
name|GimpUndoType
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2bc4401d1703
block|{
DECL|enumerator|GIMP_CONTEXT_FIRST_PROP
name|GIMP_CONTEXT_FIRST_PROP
init|=
literal|2
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_IMAGE
name|GIMP_CONTEXT_PROP_IMAGE
init|=
name|GIMP_CONTEXT_FIRST_PROP
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
DECL|enumerator|GIMP_CONTEXT_PROP_FOREGROUND
name|GIMP_CONTEXT_PROP_FOREGROUND
init|=
literal|5
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_BACKGROUND
name|GIMP_CONTEXT_PROP_BACKGROUND
init|=
literal|6
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_OPACITY
name|GIMP_CONTEXT_PROP_OPACITY
init|=
literal|7
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PAINT_MODE
name|GIMP_CONTEXT_PROP_PAINT_MODE
init|=
literal|8
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_BRUSH
name|GIMP_CONTEXT_PROP_BRUSH
init|=
literal|9
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PATTERN
name|GIMP_CONTEXT_PROP_PATTERN
init|=
literal|10
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_GRADIENT
name|GIMP_CONTEXT_PROP_GRADIENT
init|=
literal|11
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PALETTE
name|GIMP_CONTEXT_PROP_PALETTE
init|=
literal|12
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_FONT
name|GIMP_CONTEXT_PROP_FONT
init|=
literal|13
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_BUFFER
name|GIMP_CONTEXT_PROP_BUFFER
init|=
literal|14
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_IMAGEFILE
name|GIMP_CONTEXT_PROP_IMAGEFILE
init|=
literal|15
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_TEMPLATE
name|GIMP_CONTEXT_PROP_TEMPLATE
init|=
literal|16
block|,
DECL|enumerator|GIMP_CONTEXT_LAST_PROP
name|GIMP_CONTEXT_LAST_PROP
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
DECL|enum|__anon2bc4401d1803
block|{
DECL|enumerator|GIMP_CONTEXT_IMAGE_MASK
name|GIMP_CONTEXT_IMAGE_MASK
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_CONTEXT_DISPLAY_MASK
name|GIMP_CONTEXT_DISPLAY_MASK
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_CONTEXT_TOOL_MASK
name|GIMP_CONTEXT_TOOL_MASK
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_CONTEXT_FOREGROUND_MASK
name|GIMP_CONTEXT_FOREGROUND_MASK
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_CONTEXT_BACKGROUND_MASK
name|GIMP_CONTEXT_BACKGROUND_MASK
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_CONTEXT_OPACITY_MASK
name|GIMP_CONTEXT_OPACITY_MASK
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_CONTEXT_PAINT_MODE_MASK
name|GIMP_CONTEXT_PAINT_MODE_MASK
init|=
literal|1
operator|<<
literal|8
block|,
DECL|enumerator|GIMP_CONTEXT_BRUSH_MASK
name|GIMP_CONTEXT_BRUSH_MASK
init|=
literal|1
operator|<<
literal|9
block|,
DECL|enumerator|GIMP_CONTEXT_PATTERN_MASK
name|GIMP_CONTEXT_PATTERN_MASK
init|=
literal|1
operator|<<
literal|10
block|,
DECL|enumerator|GIMP_CONTEXT_GRADIENT_MASK
name|GIMP_CONTEXT_GRADIENT_MASK
init|=
literal|1
operator|<<
literal|11
block|,
DECL|enumerator|GIMP_CONTEXT_PALETTE_MASK
name|GIMP_CONTEXT_PALETTE_MASK
init|=
literal|1
operator|<<
literal|12
block|,
DECL|enumerator|GIMP_CONTEXT_FONT_MASK
name|GIMP_CONTEXT_FONT_MASK
init|=
literal|1
operator|<<
literal|13
block|,
DECL|enumerator|GIMP_CONTEXT_BUFFER_MASK
name|GIMP_CONTEXT_BUFFER_MASK
init|=
literal|1
operator|<<
literal|14
block|,
DECL|enumerator|GIMP_CONTEXT_IMAGEFILE_MASK
name|GIMP_CONTEXT_IMAGEFILE_MASK
init|=
literal|1
operator|<<
literal|15
block|,
DECL|enumerator|GIMP_CONTEXT_TEMPLATE_MASK
name|GIMP_CONTEXT_TEMPLATE_MASK
init|=
literal|1
operator|<<
literal|16
block|,
comment|/*  aliases  */
DECL|enumerator|GIMP_CONTEXT_PAINT_PROPS_MASK
name|GIMP_CONTEXT_PAINT_PROPS_MASK
init|=
operator|(
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_BACKGROUND_MASK
operator||
name|GIMP_CONTEXT_OPACITY_MASK
operator||
name|GIMP_CONTEXT_PAINT_MODE_MASK
operator||
name|GIMP_CONTEXT_BRUSH_MASK
operator||
name|GIMP_CONTEXT_PATTERN_MASK
operator||
name|GIMP_CONTEXT_GRADIENT_MASK
operator|)
block|,
DECL|enumerator|GIMP_CONTEXT_ALL_PROPS_MASK
name|GIMP_CONTEXT_ALL_PROPS_MASK
init|=
operator|(
name|GIMP_CONTEXT_IMAGE_MASK
operator||
name|GIMP_CONTEXT_DISPLAY_MASK
operator||
name|GIMP_CONTEXT_TOOL_MASK
operator||
name|GIMP_CONTEXT_PALETTE_MASK
operator||
name|GIMP_CONTEXT_FONT_MASK
operator||
name|GIMP_CONTEXT_BUFFER_MASK
operator||
name|GIMP_CONTEXT_IMAGEFILE_MASK
operator||
name|GIMP_CONTEXT_TEMPLATE_MASK
operator||
name|GIMP_CONTEXT_PAINT_PROPS_MASK
operator|)
DECL|typedef|GimpContextPropMask
block|}
name|GimpContextPropMask
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2bc4401d1903
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
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2bc4401d1a03
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
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2bc4401d1b03
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
DECL|enum|__anon2bc4401d1c03
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
DECL|enum|__anon2bc4401d1d03
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
comment|/*< skip>*/
DECL|enum|__anon2bc4401d1e03
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CORE_ENUMS_H__ */
end_comment

end_unit

