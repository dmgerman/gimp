begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*< proxy-skip>*/
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
unit|This file is parsed by three scripts, enumgen.pl in tools/pdbgen,    gimp-mkenums, and gimp-mkproxy. All enums that are not marked with
comment|/*< pdb-skip>*/
end_comment

begin_comment
unit|are exported to libgimp and the PDB. Enums that are    not marked with
comment|/*< skip>*/
end_comment

begin_comment
unit|are registered with the GType system.     If you want the enum to be skipped by both scripts, you have to use
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
unit|are skipped for    both targets.     Anything not between proxy-skip and proxy-resume     pairs will be copied into libgimpproxy by gimp-mkproxy.
endif|#
directive|endif
end_endif

begin_comment
comment|/*   * these enums that are registered with the type system  */
end_comment

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
DECL|enum|__anon2a8d953f0103
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
DECL|enum|__anon2a8d953f0203
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
DECL|enum|__anon2a8d953f0303
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

begin_comment
comment|/*< proxy-resume>*/
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a8d953f0403
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

begin_comment
comment|/*< proxy-skip>*/
end_comment

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
DECL|enum|__anon2a8d953f0503
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
DECL|enum|__anon2a8d953f0603
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
DECL|enum|__anon2a8d953f0703
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
DECL|enum|__anon2a8d953f0803
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
DECL|enum|__anon2a8d953f0903
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
DECL|enum|__anon2a8d953f0a03
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
DECL|enum|__anon2a8d953f0b03
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
DECL|enum|__anon2a8d953f0c03
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
DECL|enum|__anon2a8d953f0d03
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
DECL|enum|__anon2a8d953f0e03
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
DECL|enum|__anon2a8d953f0f03
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
DECL|enum|__anon2a8d953f1003
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
DECL|enum|__anon2a8d953f1103
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
DECL|enum|__anon2a8d953f1203
block|{
comment|/* Type NO_UNDO_GROUP (0) is special - in the gimpimage structure it    * means there is no undo group currently being added to.    */
DECL|enumerator|NO_UNDO_GROUP
name|NO_UNDO_GROUP
init|=
literal|0
block|,
comment|/*< desc="<<invalid>>">*/
DECL|enumerator|FIRST_UNDO_GROUP
name|FIRST_UNDO_GROUP
init|=
name|NO_UNDO_GROUP
block|,
DECL|enumerator|IMAGE_SCALE_UNDO_GROUP
name|IMAGE_SCALE_UNDO_GROUP
block|,
comment|/*< desc="Scale Image">*/
DECL|enumerator|IMAGE_RESIZE_UNDO_GROUP
name|IMAGE_RESIZE_UNDO_GROUP
block|,
comment|/*< desc="Resize Image">*/
DECL|enumerator|IMAGE_CONVERT_UNDO_GROUP
name|IMAGE_CONVERT_UNDO_GROUP
block|,
comment|/*< desc="Convert Image">*/
DECL|enumerator|IMAGE_CROP_UNDO_GROUP
name|IMAGE_CROP_UNDO_GROUP
block|,
comment|/*< desc="Crop Image">*/
DECL|enumerator|IMAGE_LAYERS_MERGE_UNDO_GROUP
name|IMAGE_LAYERS_MERGE_UNDO_GROUP
block|,
comment|/*< desc="Merge Layers">*/
DECL|enumerator|IMAGE_QMASK_UNDO_GROUP
name|IMAGE_QMASK_UNDO_GROUP
block|,
comment|/*< desc="QuickMask">*/
DECL|enumerator|IMAGE_GUIDE_UNDO_GROUP
name|IMAGE_GUIDE_UNDO_GROUP
block|,
comment|/*< desc="Guide">*/
DECL|enumerator|LAYER_PROPERTIES_UNDO_GROUP
name|LAYER_PROPERTIES_UNDO_GROUP
block|,
comment|/*< desc="Layer Properties">*/
DECL|enumerator|LAYER_SCALE_UNDO_GROUP
name|LAYER_SCALE_UNDO_GROUP
block|,
comment|/*< desc="Scale Layer">*/
DECL|enumerator|LAYER_RESIZE_UNDO_GROUP
name|LAYER_RESIZE_UNDO_GROUP
block|,
comment|/*< desc="Resize Layer">*/
DECL|enumerator|LAYER_DISPLACE_UNDO_GROUP
name|LAYER_DISPLACE_UNDO_GROUP
block|,
comment|/*< desc="Move Layer">*/
DECL|enumerator|LAYER_LINKED_UNDO_GROUP
name|LAYER_LINKED_UNDO_GROUP
block|,
comment|/*< desc="Linked Layer">*/
DECL|enumerator|LAYER_APPLY_MASK_UNDO_GROUP
name|LAYER_APPLY_MASK_UNDO_GROUP
block|,
comment|/*< desc="Apply Layer Mask">*/
DECL|enumerator|FS_FLOAT_UNDO_GROUP
name|FS_FLOAT_UNDO_GROUP
block|,
comment|/*< desc="Float Selection">*/
DECL|enumerator|FS_ANCHOR_UNDO_GROUP
name|FS_ANCHOR_UNDO_GROUP
block|,
comment|/*< desc="Anchor Floating Selection">*/
DECL|enumerator|EDIT_PASTE_UNDO_GROUP
name|EDIT_PASTE_UNDO_GROUP
block|,
comment|/*< desc="Paste">*/
DECL|enumerator|EDIT_CUT_UNDO_GROUP
name|EDIT_CUT_UNDO_GROUP
block|,
comment|/*< desc="Cut">*/
DECL|enumerator|EDIT_COPY_UNDO_GROUP
name|EDIT_COPY_UNDO_GROUP
block|,
comment|/*< desc="Copy">*/
DECL|enumerator|TEXT_UNDO_GROUP
name|TEXT_UNDO_GROUP
block|,
comment|/*< desc="Text">*/
DECL|enumerator|TRANSFORM_UNDO_GROUP
name|TRANSFORM_UNDO_GROUP
block|,
comment|/*< desc="Transform">*/
DECL|enumerator|PAINT_UNDO_GROUP
name|PAINT_UNDO_GROUP
block|,
comment|/*< desc="Paint">*/
DECL|enumerator|PARASITE_ATTACH_UNDO_GROUP
name|PARASITE_ATTACH_UNDO_GROUP
block|,
comment|/*< desc="Attach Parasite">*/
DECL|enumerator|PARASITE_REMOVE_UNDO_GROUP
name|PARASITE_REMOVE_UNDO_GROUP
block|,
comment|/*< desc="Remove Parasite">*/
DECL|enumerator|MISC_UNDO_GROUP
name|MISC_UNDO_GROUP
block|,
comment|/*< desc="Plug-In">*/
DECL|enumerator|LAST_UNDO_GROUP
name|LAST_UNDO_GROUP
init|=
name|MISC_UNDO_GROUP
block|,
comment|/*  Undo types which actually do something  */
DECL|enumerator|IMAGE_UNDO
name|IMAGE_UNDO
block|,
comment|/*< desc="Image">*/
DECL|enumerator|IMAGE_MOD_UNDO
name|IMAGE_MOD_UNDO
block|,
comment|/*< desc="Image Mod">*/
DECL|enumerator|IMAGE_TYPE_UNDO
name|IMAGE_TYPE_UNDO
block|,
comment|/*< desc="Image Type">*/
DECL|enumerator|IMAGE_SIZE_UNDO
name|IMAGE_SIZE_UNDO
block|,
comment|/*< desc="Image Size">*/
DECL|enumerator|IMAGE_RESOLUTION_UNDO
name|IMAGE_RESOLUTION_UNDO
block|,
comment|/*< desc="Resolution Change">*/
DECL|enumerator|IMAGE_QMASK_UNDO
name|IMAGE_QMASK_UNDO
block|,
comment|/*< desc="QuickMask">*/
DECL|enumerator|IMAGE_GUIDE_UNDO
name|IMAGE_GUIDE_UNDO
block|,
comment|/*< desc="Guide">*/
DECL|enumerator|MASK_UNDO
name|MASK_UNDO
block|,
comment|/*< desc="Selection Mask">*/
DECL|enumerator|ITEM_RENAME_UNDO
name|ITEM_RENAME_UNDO
block|,
comment|/*< desc="Rename Item">*/
DECL|enumerator|LAYER_ADD_UNDO
name|LAYER_ADD_UNDO
block|,
comment|/*< desc="New Layer">*/
DECL|enumerator|LAYER_REMOVE_UNDO
name|LAYER_REMOVE_UNDO
block|,
comment|/*< desc="Delete Layer">*/
DECL|enumerator|LAYER_MOD_UNDO
name|LAYER_MOD_UNDO
block|,
comment|/*< desc="Layer Mod">*/
DECL|enumerator|LAYER_MASK_ADD_UNDO
name|LAYER_MASK_ADD_UNDO
block|,
comment|/*< desc="Add Layer Mask">*/
DECL|enumerator|LAYER_MASK_REMOVE_UNDO
name|LAYER_MASK_REMOVE_UNDO
block|,
comment|/*< desc="Delete Layer Mask">*/
DECL|enumerator|LAYER_REPOSITION_UNDO
name|LAYER_REPOSITION_UNDO
block|,
comment|/*< desc="Layer Reposition">*/
DECL|enumerator|LAYER_DISPLACE_UNDO
name|LAYER_DISPLACE_UNDO
block|,
comment|/*< desc="Layer Move">*/
DECL|enumerator|CHANNEL_ADD_UNDO
name|CHANNEL_ADD_UNDO
block|,
comment|/*< desc="New Channel">*/
DECL|enumerator|CHANNEL_REMOVE_UNDO
name|CHANNEL_REMOVE_UNDO
block|,
comment|/*< desc="Delete Channel">*/
DECL|enumerator|CHANNEL_MOD_UNDO
name|CHANNEL_MOD_UNDO
block|,
comment|/*< desc="Channel Mod">*/
DECL|enumerator|CHANNEL_REPOSITION_UNDO
name|CHANNEL_REPOSITION_UNDO
block|,
comment|/*< desc="Channel Reposition">*/
DECL|enumerator|VECTORS_ADD_UNDO
name|VECTORS_ADD_UNDO
block|,
comment|/*< desc="New Vectors">*/
DECL|enumerator|VECTORS_REMOVE_UNDO
name|VECTORS_REMOVE_UNDO
block|,
comment|/*< desc="Delete Vectors">*/
DECL|enumerator|VECTORS_MOD_UNDO
name|VECTORS_MOD_UNDO
block|,
comment|/*< desc="Vectors Mod">*/
DECL|enumerator|VECTORS_REPOSITION_UNDO
name|VECTORS_REPOSITION_UNDO
block|,
comment|/*< desc="Vectors Reposition">*/
DECL|enumerator|FS_TO_LAYER_UNDO
name|FS_TO_LAYER_UNDO
block|,
comment|/*< desc="FS to Layer">*/
DECL|enumerator|FS_RIGOR_UNDO
name|FS_RIGOR_UNDO
block|,
comment|/*< desc="FS Rigor">*/
DECL|enumerator|FS_RELAX_UNDO
name|FS_RELAX_UNDO
block|,
comment|/*< desc="FS Relax">*/
DECL|enumerator|TRANSFORM_UNDO
name|TRANSFORM_UNDO
block|,
comment|/*< desc="Transform">*/
DECL|enumerator|PAINT_UNDO
name|PAINT_UNDO
block|,
comment|/*< desc="Paint">*/
DECL|enumerator|PARASITE_ATTACH_UNDO
name|PARASITE_ATTACH_UNDO
block|,
comment|/*< desc="Attach Parasite">*/
DECL|enumerator|PARASITE_REMOVE_UNDO
name|PARASITE_REMOVE_UNDO
block|,
comment|/*< desc="Remove Parasite">*/
DECL|enumerator|CANT_UNDO
name|CANT_UNDO
block|,
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
comment|/*< skip>*/
DECL|enum|__anon2a8d953f1303
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
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2a8d953f1403
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
DECL|enum|__anon2a8d953f1503
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
DECL|enum|__anon2a8d953f1603
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
DECL|enum|__anon2a8d953f1703
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
DECL|enum|__anon2a8d953f1803
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
DECL|enum|__anon2a8d953f1903
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

