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
unit|This file is parsed by two scripts, enumgen.pl in tools/pdbgen    and glib-mkenums. All enums that are not marked with
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
DECL|enum|__anon2b06d7660103
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
DECL|enum|__anon2b06d7660203
block|{
DECL|enumerator|GIMP_PREVIEW_SIZE_NONE
name|GIMP_PREVIEW_SIZE_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_TINY
name|GIMP_PREVIEW_SIZE_TINY
init|=
literal|16
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_SMALL
name|GIMP_PREVIEW_SIZE_EXTRA_SMALL
init|=
literal|24
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_SMALL
name|GIMP_PREVIEW_SIZE_SMALL
init|=
literal|32
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_MEDIUM
name|GIMP_PREVIEW_SIZE_MEDIUM
init|=
literal|48
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_LARGE
name|GIMP_PREVIEW_SIZE_LARGE
init|=
literal|64
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_EXTRA_LARGE
name|GIMP_PREVIEW_SIZE_EXTRA_LARGE
init|=
literal|96
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_HUGE
name|GIMP_PREVIEW_SIZE_HUGE
init|=
literal|128
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_ENORMOUS
name|GIMP_PREVIEW_SIZE_ENORMOUS
init|=
literal|192
block|,
DECL|enumerator|GIMP_PREVIEW_SIZE_GIGANTIC
name|GIMP_PREVIEW_SIZE_GIGANTIC
init|=
literal|256
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
DECL|enum|__anon2b06d7660303
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
DECL|enum|__anon2b06d7660403
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

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b06d7660503
block|{
DECL|enumerator|GIMP_LINEAR
name|GIMP_LINEAR
block|,
DECL|enumerator|GIMP_BILINEAR
name|GIMP_BILINEAR
block|,
DECL|enumerator|GIMP_RADIAL
name|GIMP_RADIAL
block|,
DECL|enumerator|GIMP_SQUARE
name|GIMP_SQUARE
block|,
DECL|enumerator|GIMP_CONICAL_SYMMETRIC
name|GIMP_CONICAL_SYMMETRIC
block|,
DECL|enumerator|GIMP_CONICAL_ASYMMETRIC
name|GIMP_CONICAL_ASYMMETRIC
block|,
DECL|enumerator|GIMP_SHAPEBURST_ANGULAR
name|GIMP_SHAPEBURST_ANGULAR
block|,
DECL|enumerator|GIMP_SHAPEBURST_SPHERICAL
name|GIMP_SHAPEBURST_SPHERICAL
block|,
DECL|enumerator|GIMP_SHAPEBURST_DIMPLED
name|GIMP_SHAPEBURST_DIMPLED
block|,
DECL|enumerator|GIMP_SPIRAL_CLOCKWISE
name|GIMP_SPIRAL_CLOCKWISE
block|,
DECL|enumerator|GIMP_SPIRAL_ANTICLOCKWISE
name|GIMP_SPIRAL_ANTICLOCKWISE
DECL|typedef|GimpGradientType
block|}
name|GimpGradientType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2b06d7660603
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
DECL|enum|__anon2b06d7660703
block|{
DECL|enumerator|GIMP_GRAD_RGB
name|GIMP_GRAD_RGB
init|=
literal|0
block|,
comment|/* normal RGB */
DECL|enumerator|GIMP_GRAD_HSV_CCW
name|GIMP_GRAD_HSV_CCW
block|,
comment|/* counterclockwise hue */
DECL|enumerator|GIMP_GRAD_HSV_CW
name|GIMP_GRAD_HSV_CW
comment|/* clockwise hue */
DECL|typedef|GimpGradientSegmentColor
block|}
name|GimpGradientSegmentColor
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=_MODE>*/
comment|/*< skip>*/
DECL|enum|__anon2b06d7660803
block|{
DECL|enumerator|GIMP_FG_BG_RGB_MODE
name|GIMP_FG_BG_RGB_MODE
block|,
DECL|enumerator|GIMP_FG_BG_HSV_MODE
name|GIMP_FG_BG_HSV_MODE
block|,
DECL|enumerator|GIMP_FG_TRANS_MODE
name|GIMP_FG_TRANS_MODE
block|,
DECL|enumerator|GIMP_CUSTOM_MODE
name|GIMP_CUSTOM_MODE
DECL|typedef|GimpBlendMode
block|}
name|GimpBlendMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b06d7660903
block|{
DECL|enumerator|GIMP_REPEAT_NONE
name|GIMP_REPEAT_NONE
block|,
DECL|enumerator|GIMP_REPEAT_SAWTOOTH
name|GIMP_REPEAT_SAWTOOTH
block|,
DECL|enumerator|GIMP_REPEAT_TRIANGULAR
name|GIMP_REPEAT_TRIANGULAR
DECL|typedef|GimpRepeatMode
block|}
name|GimpRepeatMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b06d7660a03
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
DECL|enum|__anon2b06d7660b03
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

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
comment|/*< skip>*/
DECL|enum|__anon2b06d7660c03
block|{
DECL|enumerator|GIMP_TRANSFORM_FORWARD
name|GIMP_TRANSFORM_FORWARD
block|,
DECL|enumerator|GIMP_TRANSFORM_BACKWARD
name|GIMP_TRANSFORM_BACKWARD
DECL|typedef|GimpTransformDirection
block|}
name|GimpTransformDirection
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

