begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BASE_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BASE_ENUMS_H__
define|#
directive|define
name|__GIMP_BASE_ENUMS_H__
end_define

begin_comment
comment|/**  * SECTION: gimpbaseenums  * @title: gimpbaseenums  * @short_description: Basic GIMP enumeration data types.  *  * Basic GIMP enumeration data types.  **/
end_comment

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
DECL|macro|GIMP_TYPE_ADD_MASK_TYPE
define|#
directive|define
name|GIMP_TYPE_ADD_MASK_TYPE
value|(gimp_add_mask_type_get_type ())
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
DECL|enum|__anon2b81eb8a0103
block|{
DECL|enumerator|GIMP_ADD_WHITE_MASK
name|GIMP_ADD_WHITE_MASK
block|,
comment|/*< desc="_White (full opacity)">*/
DECL|enumerator|GIMP_ADD_BLACK_MASK
name|GIMP_ADD_BLACK_MASK
block|,
comment|/*< desc="_Black (full transparency)">*/
DECL|enumerator|GIMP_ADD_ALPHA_MASK
name|GIMP_ADD_ALPHA_MASK
block|,
comment|/*< desc="Layer's _alpha channel">*/
DECL|enumerator|GIMP_ADD_ALPHA_TRANSFER_MASK
name|GIMP_ADD_ALPHA_TRANSFER_MASK
block|,
comment|/*< desc="_Transfer layer's alpha channel">*/
DECL|enumerator|GIMP_ADD_SELECTION_MASK
name|GIMP_ADD_SELECTION_MASK
block|,
comment|/*< desc="_Selection">*/
DECL|enumerator|GIMP_ADD_COPY_MASK
name|GIMP_ADD_COPY_MASK
block|,
comment|/*< desc="_Grayscale copy of layer">*/
DECL|enumerator|GIMP_ADD_CHANNEL_MASK
name|GIMP_ADD_CHANNEL_MASK
comment|/*< desc="C_hannel">*/
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
DECL|enum|__anon2b81eb8a0203
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
comment|/*< desc="FG to transparent">*/
DECL|enumerator|GIMP_CUSTOM_MODE
name|GIMP_CUSTOM_MODE
comment|/*< desc="Custom gradient">*/
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
DECL|enum|__anon2b81eb8a0303
block|{
DECL|enumerator|GIMP_FG_BUCKET_FILL
name|GIMP_FG_BUCKET_FILL
block|,
comment|/*< desc="FG color fill">*/
DECL|enumerator|GIMP_BG_BUCKET_FILL
name|GIMP_BG_BUCKET_FILL
block|,
comment|/*< desc="BG color fill">*/
DECL|enumerator|GIMP_PATTERN_BUCKET_FILL
name|GIMP_PATTERN_BUCKET_FILL
comment|/*< desc="Pattern fill">*/
DECL|typedef|GimpBucketFillMode
block|}
name|GimpBucketFillMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CAGE_MODE
define|#
directive|define
name|GIMP_TYPE_CAGE_MODE
value|(gimp_cage_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cage_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a0403
block|{
DECL|enumerator|GIMP_CAGE_MODE_CAGE_CHANGE
name|GIMP_CAGE_MODE_CAGE_CHANGE
block|,
comment|/*< desc="Create or adjust the cage">*/
DECL|enumerator|GIMP_CAGE_MODE_DEFORM
name|GIMP_CAGE_MODE_DEFORM
comment|/*< desc="Deform the cage to deform the image">*/
DECL|typedef|GimpCageMode
block|}
name|GimpCageMode
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
DECL|enum|__anon2b81eb8a0503
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
DECL|enum|__anon2b81eb8a0603
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
DECL|enum|__anon2b81eb8a0703
block|{
DECL|enumerator|GIMP_CHECK_SIZE_SMALL_CHECKS
name|GIMP_CHECK_SIZE_SMALL_CHECKS
init|=
literal|0
block|,
comment|/*< desc="Small">*/
DECL|enumerator|GIMP_CHECK_SIZE_MEDIUM_CHECKS
name|GIMP_CHECK_SIZE_MEDIUM_CHECKS
init|=
literal|1
block|,
comment|/*< desc="Medium">*/
DECL|enumerator|GIMP_CHECK_SIZE_LARGE_CHECKS
name|GIMP_CHECK_SIZE_LARGE_CHECKS
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
DECL|enum|__anon2b81eb8a0803
block|{
DECL|enumerator|GIMP_CHECK_TYPE_LIGHT_CHECKS
name|GIMP_CHECK_TYPE_LIGHT_CHECKS
init|=
literal|0
block|,
comment|/*< desc="Light checks">*/
DECL|enumerator|GIMP_CHECK_TYPE_GRAY_CHECKS
name|GIMP_CHECK_TYPE_GRAY_CHECKS
init|=
literal|1
block|,
comment|/*< desc="Mid-tone checks">*/
DECL|enumerator|GIMP_CHECK_TYPE_DARK_CHECKS
name|GIMP_CHECK_TYPE_DARK_CHECKS
init|=
literal|2
block|,
comment|/*< desc="Dark checks">*/
DECL|enumerator|GIMP_CHECK_TYPE_WHITE_ONLY
name|GIMP_CHECK_TYPE_WHITE_ONLY
init|=
literal|3
block|,
comment|/*< desc="White only">*/
DECL|enumerator|GIMP_CHECK_TYPE_GRAY_ONLY
name|GIMP_CHECK_TYPE_GRAY_ONLY
init|=
literal|4
block|,
comment|/*< desc="Gray only">*/
DECL|enumerator|GIMP_CHECK_TYPE_BLACK_ONLY
name|GIMP_CHECK_TYPE_BLACK_ONLY
init|=
literal|5
comment|/*< desc="Black only">*/
DECL|typedef|GimpCheckType
block|}
name|GimpCheckType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CLONE_TYPE
define|#
directive|define
name|GIMP_TYPE_CLONE_TYPE
value|(gimp_clone_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_clone_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a0903
block|{
DECL|enumerator|GIMP_IMAGE_CLONE
name|GIMP_IMAGE_CLONE
block|,
comment|/*< desc="Image">*/
DECL|enumerator|GIMP_PATTERN_CLONE
name|GIMP_PATTERN_CLONE
comment|/*< desc="Pattern">*/
DECL|typedef|GimpCloneType
block|}
name|GimpCloneType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DESATURATE_MODE
define|#
directive|define
name|GIMP_TYPE_DESATURATE_MODE
value|(gimp_desaturate_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_desaturate_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a0a03
block|{
DECL|enumerator|GIMP_DESATURATE_LIGHTNESS
name|GIMP_DESATURATE_LIGHTNESS
block|,
comment|/*< desc="Lightness">*/
DECL|enumerator|GIMP_DESATURATE_LUMINOSITY
name|GIMP_DESATURATE_LUMINOSITY
block|,
comment|/*< desc="Luminosity">*/
DECL|enumerator|GIMP_DESATURATE_AVERAGE
name|GIMP_DESATURATE_AVERAGE
comment|/*< desc="Average">*/
DECL|typedef|GimpDesaturateMode
block|}
name|GimpDesaturateMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_DODGE_BURN_TYPE
define|#
directive|define
name|GIMP_TYPE_DODGE_BURN_TYPE
value|(gimp_dodge_burn_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_dodge_burn_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a0b03
block|{
DECL|enumerator|GIMP_DODGE
name|GIMP_DODGE
block|,
comment|/*< desc="Dodge">*/
DECL|enumerator|GIMP_BURN
name|GIMP_BURN
comment|/*< desc="Burn">*/
DECL|typedef|GimpDodgeBurnType
block|}
name|GimpDodgeBurnType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_FOREGROUND_EXTRACT_MODE
define|#
directive|define
name|GIMP_TYPE_FOREGROUND_EXTRACT_MODE
value|(gimp_foreground_extract_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_foreground_extract_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a0c03
block|{
DECL|enumerator|GIMP_FOREGROUND_EXTRACT_SIOX
name|GIMP_FOREGROUND_EXTRACT_SIOX
DECL|typedef|GimpForegroundExtractMode
block|}
name|GimpForegroundExtractMode
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
DECL|enum|__anon2b81eb8a0d03
block|{
DECL|enumerator|GIMP_GRADIENT_LINEAR
name|GIMP_GRADIENT_LINEAR
block|,
comment|/*< desc="Linear">*/
DECL|enumerator|GIMP_GRADIENT_BILINEAR
name|GIMP_GRADIENT_BILINEAR
block|,
comment|/*< desc="Bi-linear">*/
DECL|enumerator|GIMP_GRADIENT_RADIAL
name|GIMP_GRADIENT_RADIAL
block|,
comment|/*< desc="Radial">*/
DECL|enumerator|GIMP_GRADIENT_SQUARE
name|GIMP_GRADIENT_SQUARE
block|,
comment|/*< desc="Square">*/
DECL|enumerator|GIMP_GRADIENT_CONICAL_SYMMETRIC
name|GIMP_GRADIENT_CONICAL_SYMMETRIC
block|,
comment|/*< desc="Conical (sym)">*/
DECL|enumerator|GIMP_GRADIENT_CONICAL_ASYMMETRIC
name|GIMP_GRADIENT_CONICAL_ASYMMETRIC
block|,
comment|/*< desc="Conical (asym)">*/
DECL|enumerator|GIMP_GRADIENT_SHAPEBURST_ANGULAR
name|GIMP_GRADIENT_SHAPEBURST_ANGULAR
block|,
comment|/*< desc="Shaped (angular)">*/
DECL|enumerator|GIMP_GRADIENT_SHAPEBURST_SPHERICAL
name|GIMP_GRADIENT_SHAPEBURST_SPHERICAL
block|,
comment|/*< desc="Shaped (spherical)">*/
DECL|enumerator|GIMP_GRADIENT_SHAPEBURST_DIMPLED
name|GIMP_GRADIENT_SHAPEBURST_DIMPLED
block|,
comment|/*< desc="Shaped (dimpled)">*/
DECL|enumerator|GIMP_GRADIENT_SPIRAL_CLOCKWISE
name|GIMP_GRADIENT_SPIRAL_CLOCKWISE
block|,
comment|/*< desc="Spiral (cw)">*/
DECL|enumerator|GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE
name|GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE
comment|/*< desc="Spiral (ccw)">*/
DECL|typedef|GimpGradientType
block|}
name|GimpGradientType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GRID_STYLE
define|#
directive|define
name|GIMP_TYPE_GRID_STYLE
value|(gimp_grid_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_grid_style_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a0e03
block|{
DECL|enumerator|GIMP_GRID_DOTS
name|GIMP_GRID_DOTS
block|,
comment|/*< desc="Intersections (dots)">*/
DECL|enumerator|GIMP_GRID_INTERSECTIONS
name|GIMP_GRID_INTERSECTIONS
block|,
comment|/*< desc="Intersections (crosshairs)">*/
DECL|enumerator|GIMP_GRID_ON_OFF_DASH
name|GIMP_GRID_ON_OFF_DASH
block|,
comment|/*< desc="Dashed">*/
DECL|enumerator|GIMP_GRID_DOUBLE_DASH
name|GIMP_GRID_DOUBLE_DASH
block|,
comment|/*< desc="Double dashed">*/
DECL|enumerator|GIMP_GRID_SOLID
name|GIMP_GRID_SOLID
comment|/*< desc="Solid">*/
DECL|typedef|GimpGridStyle
block|}
name|GimpGridStyle
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ICON_TYPE
define|#
directive|define
name|GIMP_TYPE_ICON_TYPE
value|(gimp_icon_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_icon_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a0f03
block|{
DECL|enumerator|GIMP_ICON_TYPE_STOCK_ID
name|GIMP_ICON_TYPE_STOCK_ID
block|,
comment|/*< desc="Stock ID">*/
DECL|enumerator|GIMP_ICON_TYPE_INLINE_PIXBUF
name|GIMP_ICON_TYPE_INLINE_PIXBUF
block|,
comment|/*< desc="Inline pixbuf">*/
DECL|enumerator|GIMP_ICON_TYPE_IMAGE_FILE
name|GIMP_ICON_TYPE_IMAGE_FILE
comment|/*< desc="Image file">*/
DECL|typedef|GimpIconType
block|}
name|GimpIconType
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
DECL|enum|__anon2b81eb8a1003
block|{
DECL|enumerator|GIMP_RGB
name|GIMP_RGB
block|,
comment|/*< desc="RGB color">*/
DECL|enumerator|GIMP_GRAY
name|GIMP_GRAY
block|,
comment|/*< desc="Grayscale">*/
DECL|enumerator|GIMP_INDEXED
name|GIMP_INDEXED
comment|/*< desc="Indexed color">*/
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
DECL|enum|__anon2b81eb8a1103
block|{
DECL|enumerator|GIMP_RGB_IMAGE
name|GIMP_RGB_IMAGE
block|,
comment|/*< desc="RGB">*/
DECL|enumerator|GIMP_RGBA_IMAGE
name|GIMP_RGBA_IMAGE
block|,
comment|/*< desc="RGB-alpha">*/
DECL|enumerator|GIMP_GRAY_IMAGE
name|GIMP_GRAY_IMAGE
block|,
comment|/*< desc="Grayscale">*/
DECL|enumerator|GIMP_GRAYA_IMAGE
name|GIMP_GRAYA_IMAGE
block|,
comment|/*< desc="Grayscale-alpha">*/
DECL|enumerator|GIMP_INDEXED_IMAGE
name|GIMP_INDEXED_IMAGE
block|,
comment|/*< desc="Indexed">*/
DECL|enumerator|GIMP_INDEXEDA_IMAGE
name|GIMP_INDEXEDA_IMAGE
comment|/*< desc="Indexed-alpha">*/
DECL|typedef|GimpImageType
block|}
name|GimpImageType
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
DECL|enum|__anon2b81eb8a1203
block|{
DECL|enumerator|GIMP_INTERPOLATION_NONE
name|GIMP_INTERPOLATION_NONE
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_INTERPOLATION_LINEAR
name|GIMP_INTERPOLATION_LINEAR
block|,
comment|/*< desc="Linear">*/
DECL|enumerator|GIMP_INTERPOLATION_CUBIC
name|GIMP_INTERPOLATION_CUBIC
block|,
comment|/*< desc="Cubic">*/
DECL|enumerator|GIMP_INTERPOLATION_LANCZOS
name|GIMP_INTERPOLATION_LANCZOS
comment|/*< desc="Sinc (Lanczos3)">*/
DECL|typedef|GimpInterpolationType
block|}
name|GimpInterpolationType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PAINT_APPLICATION_MODE
define|#
directive|define
name|GIMP_TYPE_PAINT_APPLICATION_MODE
value|(gimp_paint_application_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_paint_application_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1303
block|{
DECL|enumerator|GIMP_PAINT_CONSTANT
name|GIMP_PAINT_CONSTANT
block|,
comment|/*< desc="Constant">*/
DECL|enumerator|GIMP_PAINT_INCREMENTAL
name|GIMP_PAINT_INCREMENTAL
comment|/*< desc="Incremental">*/
DECL|typedef|GimpPaintApplicationMode
block|}
name|GimpPaintApplicationMode
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
DECL|enum|__anon2b81eb8a1403
block|{
DECL|enumerator|GIMP_REPEAT_NONE
name|GIMP_REPEAT_NONE
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_REPEAT_SAWTOOTH
name|GIMP_REPEAT_SAWTOOTH
block|,
comment|/*< desc="Sawtooth wave">*/
DECL|enumerator|GIMP_REPEAT_TRIANGULAR
name|GIMP_REPEAT_TRIANGULAR
comment|/*< desc="Triangular wave">*/
DECL|typedef|GimpRepeatMode
block|}
name|GimpRepeatMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RUN_MODE
define|#
directive|define
name|GIMP_TYPE_RUN_MODE
value|(gimp_run_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_run_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1503
block|{
DECL|enumerator|GIMP_RUN_INTERACTIVE
name|GIMP_RUN_INTERACTIVE
block|,
comment|/*< desc="Run interactively">*/
DECL|enumerator|GIMP_RUN_NONINTERACTIVE
name|GIMP_RUN_NONINTERACTIVE
block|,
comment|/*< desc="Run non-interactively">*/
DECL|enumerator|GIMP_RUN_WITH_LAST_VALS
name|GIMP_RUN_WITH_LAST_VALS
comment|/*< desc="Run with last used values">*/
DECL|typedef|GimpRunMode
block|}
name|GimpRunMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_SIZE_TYPE
define|#
directive|define
name|GIMP_TYPE_SIZE_TYPE
value|(gimp_size_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_size_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1603
block|{
DECL|enumerator|GIMP_PIXELS
name|GIMP_PIXELS
block|,
comment|/*< desc="Pixels">*/
DECL|enumerator|GIMP_POINTS
name|GIMP_POINTS
comment|/*< desc="Points">*/
DECL|typedef|GimpSizeType
block|}
name|GimpSizeType
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
DECL|enum|__anon2b81eb8a1703
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
DECL|enum|__anon2b81eb8a1803
block|{
DECL|enumerator|GIMP_TRANSFORM_FORWARD
name|GIMP_TRANSFORM_FORWARD
block|,
comment|/*< desc="Normal (Forward)">*/
DECL|enumerator|GIMP_TRANSFORM_BACKWARD
name|GIMP_TRANSFORM_BACKWARD
comment|/*< desc="Corrective (Backward)">*/
DECL|typedef|GimpTransformDirection
block|}
name|GimpTransformDirection
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_RESIZE
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_RESIZE
value|(gimp_transform_resize_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_resize_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1903
block|{
DECL|enumerator|GIMP_TRANSFORM_RESIZE_ADJUST
name|GIMP_TRANSFORM_RESIZE_ADJUST
init|=
literal|0
block|,
comment|/*< desc="Adjust">*/
DECL|enumerator|GIMP_TRANSFORM_RESIZE_CLIP
name|GIMP_TRANSFORM_RESIZE_CLIP
init|=
literal|1
block|,
comment|/*< desc="Clip">*/
DECL|enumerator|GIMP_TRANSFORM_RESIZE_CROP
name|GIMP_TRANSFORM_RESIZE_CROP
block|,
comment|/*< desc="Crop to result">*/
DECL|enumerator|GIMP_TRANSFORM_RESIZE_CROP_WITH_ASPECT
name|GIMP_TRANSFORM_RESIZE_CROP_WITH_ASPECT
comment|/*< desc="Crop with aspect">*/
DECL|typedef|GimpTransformResize
block|}
name|GimpTransformResize
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b81eb8a1a03
block|{
DECL|enumerator|GIMP_UNIT_PIXEL
name|GIMP_UNIT_PIXEL
init|=
literal|0
block|,
DECL|enumerator|GIMP_UNIT_INCH
name|GIMP_UNIT_INCH
init|=
literal|1
block|,
DECL|enumerator|GIMP_UNIT_MM
name|GIMP_UNIT_MM
init|=
literal|2
block|,
DECL|enumerator|GIMP_UNIT_POINT
name|GIMP_UNIT_POINT
init|=
literal|3
block|,
DECL|enumerator|GIMP_UNIT_PICA
name|GIMP_UNIT_PICA
init|=
literal|4
block|,
DECL|enumerator|GIMP_UNIT_END
name|GIMP_UNIT_END
init|=
literal|5
block|,
DECL|enumerator|GIMP_UNIT_PERCENT
name|GIMP_UNIT_PERCENT
init|=
literal|65536
comment|/*< pdb-skip>*/
DECL|typedef|GimpUnit
block|}
name|GimpUnit
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PDB_ARG_TYPE
define|#
directive|define
name|GIMP_TYPE_PDB_ARG_TYPE
value|(gimp_pdb_arg_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_pdb_arg_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1b03
block|{
DECL|enumerator|GIMP_PDB_INT32
name|GIMP_PDB_INT32
block|,
DECL|enumerator|GIMP_PDB_INT16
name|GIMP_PDB_INT16
block|,
DECL|enumerator|GIMP_PDB_INT8
name|GIMP_PDB_INT8
block|,
DECL|enumerator|GIMP_PDB_FLOAT
name|GIMP_PDB_FLOAT
block|,
DECL|enumerator|GIMP_PDB_STRING
name|GIMP_PDB_STRING
block|,
DECL|enumerator|GIMP_PDB_INT32ARRAY
name|GIMP_PDB_INT32ARRAY
block|,
DECL|enumerator|GIMP_PDB_INT16ARRAY
name|GIMP_PDB_INT16ARRAY
block|,
DECL|enumerator|GIMP_PDB_INT8ARRAY
name|GIMP_PDB_INT8ARRAY
block|,
DECL|enumerator|GIMP_PDB_FLOATARRAY
name|GIMP_PDB_FLOATARRAY
block|,
DECL|enumerator|GIMP_PDB_STRINGARRAY
name|GIMP_PDB_STRINGARRAY
block|,
DECL|enumerator|GIMP_PDB_COLOR
name|GIMP_PDB_COLOR
block|,
DECL|enumerator|GIMP_PDB_REGION
name|GIMP_PDB_REGION
block|,
DECL|enumerator|GIMP_PDB_DISPLAY
name|GIMP_PDB_DISPLAY
block|,
DECL|enumerator|GIMP_PDB_IMAGE
name|GIMP_PDB_IMAGE
block|,
DECL|enumerator|GIMP_PDB_LAYER
name|GIMP_PDB_LAYER
block|,
DECL|enumerator|GIMP_PDB_CHANNEL
name|GIMP_PDB_CHANNEL
block|,
DECL|enumerator|GIMP_PDB_DRAWABLE
name|GIMP_PDB_DRAWABLE
block|,
DECL|enumerator|GIMP_PDB_SELECTION
name|GIMP_PDB_SELECTION
block|,
DECL|enumerator|GIMP_PDB_COLORARRAY
name|GIMP_PDB_COLORARRAY
block|,
DECL|enumerator|GIMP_PDB_VECTORS
name|GIMP_PDB_VECTORS
block|,
DECL|enumerator|GIMP_PDB_PARASITE
name|GIMP_PDB_PARASITE
block|,
DECL|enumerator|GIMP_PDB_STATUS
name|GIMP_PDB_STATUS
block|,
DECL|enumerator|GIMP_PDB_END
name|GIMP_PDB_END
block|,
comment|/*  the following aliases are deprecated  */
DECL|enumerator|GIMP_PDB_PATH
name|GIMP_PDB_PATH
init|=
name|GIMP_PDB_VECTORS
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_PDB_BOUNDARY
name|GIMP_PDB_BOUNDARY
init|=
name|GIMP_PDB_COLORARRAY
comment|/*< skip>*/
DECL|typedef|GimpPDBArgType
block|}
name|GimpPDBArgType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PDB_ERROR_HANDLER
define|#
directive|define
name|GIMP_TYPE_PDB_ERROR_HANDLER
value|(gimp_pdb_error_handler_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_pdb_error_handler_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1c03
block|{
DECL|enumerator|GIMP_PDB_ERROR_HANDLER_INTERNAL
name|GIMP_PDB_ERROR_HANDLER_INTERNAL
block|,
DECL|enumerator|GIMP_PDB_ERROR_HANDLER_PLUGIN
name|GIMP_PDB_ERROR_HANDLER_PLUGIN
DECL|typedef|GimpPDBErrorHandler
block|}
name|GimpPDBErrorHandler
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PDB_PROC_TYPE
define|#
directive|define
name|GIMP_TYPE_PDB_PROC_TYPE
value|(gimp_pdb_proc_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_pdb_proc_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1d03
block|{
DECL|enumerator|GIMP_INTERNAL
name|GIMP_INTERNAL
block|,
comment|/*< desc="Internal GIMP procedure">*/
DECL|enumerator|GIMP_PLUGIN
name|GIMP_PLUGIN
block|,
comment|/*< desc="GIMP Plug-In">*/
DECL|enumerator|GIMP_EXTENSION
name|GIMP_EXTENSION
block|,
comment|/*< desc="GIMP Extension">*/
DECL|enumerator|GIMP_TEMPORARY
name|GIMP_TEMPORARY
comment|/*< desc="Temporary Procedure">*/
DECL|typedef|GimpPDBProcType
block|}
name|GimpPDBProcType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PDB_STATUS_TYPE
define|#
directive|define
name|GIMP_TYPE_PDB_STATUS_TYPE
value|(gimp_pdb_status_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_pdb_status_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1e03
block|{
DECL|enumerator|GIMP_PDB_EXECUTION_ERROR
name|GIMP_PDB_EXECUTION_ERROR
block|,
DECL|enumerator|GIMP_PDB_CALLING_ERROR
name|GIMP_PDB_CALLING_ERROR
block|,
DECL|enumerator|GIMP_PDB_PASS_THROUGH
name|GIMP_PDB_PASS_THROUGH
block|,
DECL|enumerator|GIMP_PDB_SUCCESS
name|GIMP_PDB_SUCCESS
block|,
DECL|enumerator|GIMP_PDB_CANCEL
name|GIMP_PDB_CANCEL
DECL|typedef|GimpPDBStatusType
block|}
name|GimpPDBStatusType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_MESSAGE_HANDLER_TYPE
define|#
directive|define
name|GIMP_TYPE_MESSAGE_HANDLER_TYPE
value|(gimp_message_handler_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_message_handler_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a1f03
block|{
DECL|enumerator|GIMP_MESSAGE_BOX
name|GIMP_MESSAGE_BOX
block|,
DECL|enumerator|GIMP_CONSOLE
name|GIMP_CONSOLE
block|,
DECL|enumerator|GIMP_ERROR_CONSOLE
name|GIMP_ERROR_CONSOLE
DECL|typedef|GimpMessageHandlerType
block|}
name|GimpMessageHandlerType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_STACK_TRACE_MODE
define|#
directive|define
name|GIMP_TYPE_STACK_TRACE_MODE
value|(gimp_stack_trace_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_stack_trace_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a2003
block|{
DECL|enumerator|GIMP_STACK_TRACE_NEVER
name|GIMP_STACK_TRACE_NEVER
block|,
DECL|enumerator|GIMP_STACK_TRACE_QUERY
name|GIMP_STACK_TRACE_QUERY
block|,
DECL|enumerator|GIMP_STACK_TRACE_ALWAYS
name|GIMP_STACK_TRACE_ALWAYS
DECL|typedef|GimpStackTraceMode
block|}
name|GimpStackTraceMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PROGRESS_COMMAND
define|#
directive|define
name|GIMP_TYPE_PROGRESS_COMMAND
value|(gimp_progress_command_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_progress_command_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a2103
block|{
DECL|enumerator|GIMP_PROGRESS_COMMAND_START
name|GIMP_PROGRESS_COMMAND_START
block|,
DECL|enumerator|GIMP_PROGRESS_COMMAND_END
name|GIMP_PROGRESS_COMMAND_END
block|,
DECL|enumerator|GIMP_PROGRESS_COMMAND_SET_TEXT
name|GIMP_PROGRESS_COMMAND_SET_TEXT
block|,
DECL|enumerator|GIMP_PROGRESS_COMMAND_SET_VALUE
name|GIMP_PROGRESS_COMMAND_SET_VALUE
block|,
DECL|enumerator|GIMP_PROGRESS_COMMAND_PULSE
name|GIMP_PROGRESS_COMMAND_PULSE
block|,
DECL|enumerator|GIMP_PROGRESS_COMMAND_GET_WINDOW
name|GIMP_PROGRESS_COMMAND_GET_WINDOW
DECL|typedef|GimpProgressCommand
block|}
name|GimpProgressCommand
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TEXT_DIRECTION
define|#
directive|define
name|GIMP_TYPE_TEXT_DIRECTION
value|(gimp_text_direction_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_text_direction_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a2203
block|{
DECL|enumerator|GIMP_TEXT_DIRECTION_LTR
name|GIMP_TEXT_DIRECTION_LTR
block|,
comment|/*< desc="From left to right">*/
DECL|enumerator|GIMP_TEXT_DIRECTION_RTL
name|GIMP_TEXT_DIRECTION_RTL
comment|/*< desc="From right to left">*/
DECL|typedef|GimpTextDirection
block|}
name|GimpTextDirection
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TEXT_HINT_STYLE
define|#
directive|define
name|GIMP_TYPE_TEXT_HINT_STYLE
value|(gimp_text_hint_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_text_hint_style_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a2303
block|{
DECL|enumerator|GIMP_TEXT_HINT_STYLE_NONE
name|GIMP_TEXT_HINT_STYLE_NONE
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_TEXT_HINT_STYLE_SLIGHT
name|GIMP_TEXT_HINT_STYLE_SLIGHT
block|,
comment|/*< desc="Slight">*/
DECL|enumerator|GIMP_TEXT_HINT_STYLE_MEDIUM
name|GIMP_TEXT_HINT_STYLE_MEDIUM
block|,
comment|/*< desc="Medium">*/
DECL|enumerator|GIMP_TEXT_HINT_STYLE_FULL
name|GIMP_TEXT_HINT_STYLE_FULL
comment|/*< desc="Full">*/
DECL|typedef|GimpTextHintStyle
block|}
name|GimpTextHintStyle
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TEXT_JUSTIFICATION
define|#
directive|define
name|GIMP_TYPE_TEXT_JUSTIFICATION
value|(gimp_text_justification_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_text_justification_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a2403
block|{
DECL|enumerator|GIMP_TEXT_JUSTIFY_LEFT
name|GIMP_TEXT_JUSTIFY_LEFT
block|,
comment|/*< desc="Left justified">*/
DECL|enumerator|GIMP_TEXT_JUSTIFY_RIGHT
name|GIMP_TEXT_JUSTIFY_RIGHT
block|,
comment|/*< desc="Right justified">*/
DECL|enumerator|GIMP_TEXT_JUSTIFY_CENTER
name|GIMP_TEXT_JUSTIFY_CENTER
block|,
comment|/*< desc="Centered">*/
DECL|enumerator|GIMP_TEXT_JUSTIFY_FILL
name|GIMP_TEXT_JUSTIFY_FILL
comment|/*< desc="Filled">*/
DECL|typedef|GimpTextJustification
block|}
name|GimpTextJustification
typedef|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_define
DECL|macro|GIMP_TYPE_USER_DIRECTORY
define|#
directive|define
name|GIMP_TYPE_USER_DIRECTORY
value|(gimp_user_directory_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_user_directory_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a2503
block|{
DECL|enumerator|GIMP_USER_DIRECTORY_DESKTOP
name|GIMP_USER_DIRECTORY_DESKTOP
block|,
DECL|enumerator|GIMP_USER_DIRECTORY_DOCUMENTS
name|GIMP_USER_DIRECTORY_DOCUMENTS
block|,
DECL|enumerator|GIMP_USER_DIRECTORY_DOWNLOAD
name|GIMP_USER_DIRECTORY_DOWNLOAD
block|,
DECL|enumerator|GIMP_USER_DIRECTORY_MUSIC
name|GIMP_USER_DIRECTORY_MUSIC
block|,
DECL|enumerator|GIMP_USER_DIRECTORY_PICTURES
name|GIMP_USER_DIRECTORY_PICTURES
block|,
DECL|enumerator|GIMP_USER_DIRECTORY_PUBLIC_SHARE
name|GIMP_USER_DIRECTORY_PUBLIC_SHARE
block|,
DECL|enumerator|GIMP_USER_DIRECTORY_TEMPLATES
name|GIMP_USER_DIRECTORY_TEMPLATES
block|,
DECL|enumerator|GIMP_USER_DIRECTORY_VIDEOS
name|GIMP_USER_DIRECTORY_VIDEOS
DECL|typedef|GimpUserDirectory
block|}
name|GimpUserDirectory
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !GIMP_DISABLE_DEPRECATED */
end_comment

begin_define
DECL|macro|GIMP_TYPE_VECTORS_STROKE_TYPE
define|#
directive|define
name|GIMP_TYPE_VECTORS_STROKE_TYPE
value|(gimp_vectors_stroke_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_vectors_stroke_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b81eb8a2603
block|{
DECL|enumerator|GIMP_VECTORS_STROKE_TYPE_BEZIER
name|GIMP_VECTORS_STROKE_TYPE_BEZIER
DECL|typedef|GimpVectorsStrokeType
block|}
name|GimpVectorsStrokeType
typedef|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BASE_ENUMS_H__ */
end_comment

end_unit

