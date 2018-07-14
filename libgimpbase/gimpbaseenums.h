begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * GimpAddMaskType:  * @GIMP_ADD_MASK_WHITE:          White (full opacity)  * @GIMP_ADD_MASK_BLACK:          Black (full transparency)  * @GIMP_ADD_MASK_ALPHA:          Layer's alpha channel  * @GIMP_ADD_MASK_ALPHA_TRANSFER: Transfer layer's alpha channel  * @GIMP_ADD_MASK_SELECTION:      Selection  * @GIMP_ADD_MASK_COPY:           Grayscale copy of layer  * @GIMP_ADD_MASK_CHANNEL:        Channel  *  * Modes of initialising a layer mask.  **/
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
DECL|enum|__anon297d2fae0103
block|{
DECL|enumerator|GIMP_ADD_MASK_WHITE
name|GIMP_ADD_MASK_WHITE
block|,
comment|/*< desc="_White (full opacity)">*/
DECL|enumerator|GIMP_ADD_MASK_BLACK
name|GIMP_ADD_MASK_BLACK
block|,
comment|/*< desc="_Black (full transparency)">*/
DECL|enumerator|GIMP_ADD_MASK_ALPHA
name|GIMP_ADD_MASK_ALPHA
block|,
comment|/*< desc="Layer's _alpha channel">*/
DECL|enumerator|GIMP_ADD_MASK_ALPHA_TRANSFER
name|GIMP_ADD_MASK_ALPHA_TRANSFER
block|,
comment|/*< desc="_Transfer layer's alpha channel">*/
DECL|enumerator|GIMP_ADD_MASK_SELECTION
name|GIMP_ADD_MASK_SELECTION
block|,
comment|/*< desc="_Selection">*/
DECL|enumerator|GIMP_ADD_MASK_COPY
name|GIMP_ADD_MASK_COPY
block|,
comment|/*< desc="_Grayscale copy of layer">*/
DECL|enumerator|GIMP_ADD_MASK_CHANNEL
name|GIMP_ADD_MASK_CHANNEL
comment|/*< desc="C_hannel">*/
DECL|typedef|GimpAddMaskType
block|}
name|GimpAddMaskType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpBlendMode:  * @GIMP_BLEND_FG_BG_RGB:      FG to BG (RGB)  * @GIMP_BLEND_FG_BG_HSV:      FG to BG (HSV)  * @GIMP_BLEND_FG_TRANSPARENT: FG to transparent  * @GIMP_BLEND_CUSTOM:         Custom gradient  *  * Types of gradients.  **/
end_comment

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
DECL|enum|__anon297d2fae0203
block|{
DECL|enumerator|GIMP_BLEND_FG_BG_RGB
name|GIMP_BLEND_FG_BG_RGB
block|,
comment|/*< desc="FG to BG (RGB)">*/
DECL|enumerator|GIMP_BLEND_FG_BG_HSV
name|GIMP_BLEND_FG_BG_HSV
block|,
comment|/*< desc="FG to BG (HSV)">*/
DECL|enumerator|GIMP_BLEND_FG_TRANSPARENT
name|GIMP_BLEND_FG_TRANSPARENT
block|,
comment|/*< desc="FG to transparent">*/
DECL|enumerator|GIMP_BLEND_CUSTOM
name|GIMP_BLEND_CUSTOM
comment|/*< desc="Custom gradient">*/
DECL|typedef|GimpBlendMode
block|}
name|GimpBlendMode
typedef|;
end_typedef

begin_comment
comment|/**  * GimpBrushGeneratedShape:  * @GIMP_BRUSH_GENERATED_CIRCLE:  Circle  * @GIMP_BRUSH_GENERATED_SQUARE:  Square  * @GIMP_BRUSH_GENERATED_DIAMOND: Diamond  *  * Shapes of generated brushes.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_BRUSH_GENERATED_SHAPE
define|#
directive|define
name|GIMP_TYPE_BRUSH_GENERATED_SHAPE
value|(gimp_brush_generated_shape_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_brush_generated_shape_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae0303
block|{
DECL|enumerator|GIMP_BRUSH_GENERATED_CIRCLE
name|GIMP_BRUSH_GENERATED_CIRCLE
block|,
comment|/*< desc="Circle">*/
DECL|enumerator|GIMP_BRUSH_GENERATED_SQUARE
name|GIMP_BRUSH_GENERATED_SQUARE
block|,
comment|/*< desc="Square">*/
DECL|enumerator|GIMP_BRUSH_GENERATED_DIAMOND
name|GIMP_BRUSH_GENERATED_DIAMOND
comment|/*< desc="Diamond">*/
DECL|typedef|GimpBrushGeneratedShape
block|}
name|GimpBrushGeneratedShape
typedef|;
end_typedef

begin_comment
comment|/**  * GimpBucketFillMode:  * @GIMP_BUCKET_FILL_FG:      FG color fill  * @GIMP_BUCKET_FILL_BG:      BG color fill  * @GIMP_BUCKET_FILL_PATTERN: Pattern fill  *  * Bucket fill modes.  */
end_comment

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
DECL|enum|__anon297d2fae0403
block|{
DECL|enumerator|GIMP_BUCKET_FILL_FG
name|GIMP_BUCKET_FILL_FG
block|,
comment|/*< desc="FG color fill">*/
DECL|enumerator|GIMP_BUCKET_FILL_BG
name|GIMP_BUCKET_FILL_BG
block|,
comment|/*< desc="BG color fill">*/
DECL|enumerator|GIMP_BUCKET_FILL_PATTERN
name|GIMP_BUCKET_FILL_PATTERN
comment|/*< desc="Pattern fill">*/
DECL|typedef|GimpBucketFillMode
block|}
name|GimpBucketFillMode
typedef|;
end_typedef

begin_comment
comment|/**  * GimpCapStyle:  * @GIMP_CAP_BUTT:   Butt  * @GIMP_CAP_ROUND:  Round  * @GIMP_CAP_SQUARE: Square  *  * Style of line endings.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_CAP_STYLE
define|#
directive|define
name|GIMP_TYPE_CAP_STYLE
value|(gimp_cap_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cap_style_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae0503
block|{
DECL|enumerator|GIMP_CAP_BUTT
name|GIMP_CAP_BUTT
block|,
comment|/*< desc="Butt">*/
DECL|enumerator|GIMP_CAP_ROUND
name|GIMP_CAP_ROUND
block|,
comment|/*< desc="Round">*/
DECL|enumerator|GIMP_CAP_SQUARE
name|GIMP_CAP_SQUARE
comment|/*< desc="Square">*/
DECL|typedef|GimpCapStyle
block|}
name|GimpCapStyle
typedef|;
end_typedef

begin_comment
comment|/**  * GimpChannelOps:  * @GIMP_CHANNEL_OP_ADD:       Add to the current selection  * @GIMP_CHANNEL_OP_SUBTRACT:  Subtract from the current selection  * @GIMP_CHANNEL_OP_REPLACE:   Replace the current selection  * @GIMP_CHANNEL_OP_INTERSECT: Intersect with the current selection  *  * Operations to combine channels and selections.  **/
end_comment

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
DECL|enum|__anon297d2fae0603
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
comment|/**  * GimpChannelType:  * @GIMP_CHANNEL_RED:     Red  * @GIMP_CHANNEL_GREEN:   Green  * @GIMP_CHANNEL_BLUE:    Blue  * @GIMP_CHANNEL_GRAY:    Gray  * @GIMP_CHANNEL_INDEXED: Indexed  * @GIMP_CHANNEL_ALPHA:   Alpha  *  * Channels (as in color components).  **/
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
DECL|enum|__anon297d2fae0703
block|{
DECL|enumerator|GIMP_CHANNEL_RED
name|GIMP_CHANNEL_RED
block|,
comment|/*< desc="Red">*/
DECL|enumerator|GIMP_CHANNEL_GREEN
name|GIMP_CHANNEL_GREEN
block|,
comment|/*< desc="Green">*/
DECL|enumerator|GIMP_CHANNEL_BLUE
name|GIMP_CHANNEL_BLUE
block|,
comment|/*< desc="Blue">*/
DECL|enumerator|GIMP_CHANNEL_GRAY
name|GIMP_CHANNEL_GRAY
block|,
comment|/*< desc="Gray">*/
DECL|enumerator|GIMP_CHANNEL_INDEXED
name|GIMP_CHANNEL_INDEXED
block|,
comment|/*< desc="Indexed">*/
DECL|enumerator|GIMP_CHANNEL_ALPHA
name|GIMP_CHANNEL_ALPHA
comment|/*< desc="Alpha">*/
DECL|typedef|GimpChannelType
block|}
name|GimpChannelType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpCheckSize:  * @GIMP_CHECK_SIZE_SMALL_CHECKS:  Small  * @GIMP_CHECK_SIZE_MEDIUM_CHECKS: Medium  * @GIMP_CHECK_SIZE_LARGE_CHECKS:  Large  *  * Size of the checkerboard indicating transparency.  **/
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
DECL|enum|__anon297d2fae0803
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

begin_comment
comment|/**  * GimpCheckType:  * @GIMP_CHECK_TYPE_LIGHT_CHECKS: Light checks  * @GIMP_CHECK_TYPE_GRAY_CHECKS:  Mid-tone checks  * @GIMP_CHECK_TYPE_DARK_CHECKS:  Dark checks  * @GIMP_CHECK_TYPE_WHITE_ONLY:   White only  * @GIMP_CHECK_TYPE_GRAY_ONLY:    Gray only  * @GIMP_CHECK_TYPE_BLACK_ONLY:   Black only  *  * Color/Brightness of the checkerboard indicating transparency.  **/
end_comment

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
DECL|enum|__anon297d2fae0903
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

begin_comment
comment|/**  * GimpCloneType:  * @GIMP_CLONE_IMAGE:   Clone from an image/drawable source  * @GIMP_CLONE_PATTERN: Clone from a pattern source  *  * Clone sources.  **/
end_comment

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
DECL|enum|__anon297d2fae0a03
block|{
DECL|enumerator|GIMP_CLONE_IMAGE
name|GIMP_CLONE_IMAGE
block|,
comment|/*< desc="Image">*/
DECL|enumerator|GIMP_CLONE_PATTERN
name|GIMP_CLONE_PATTERN
comment|/*< desc="Pattern">*/
DECL|typedef|GimpCloneType
block|}
name|GimpCloneType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpColorTag:  * @GIMP_COLOR_TAG_NONE:   None  * @GIMP_COLOR_TAG_BLUE:   Blue  * @GIMP_COLOR_TAG_GREEN:  Green  * @GIMP_COLOR_TAG_YELLOW: Yellow  * @GIMP_COLOR_TAG_ORANGE: Orange  * @GIMP_COLOR_TAG_BROWN:  Brown  * @GIMP_COLOR_TAG_RED:    Red  * @GIMP_COLOR_TAG_VIOLET: Violet  * @GIMP_COLOR_TAG_GRAY:   Gray  *  * Possible tag colors.  *  * Since: 2.10  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLOR_TAG
define|#
directive|define
name|GIMP_TYPE_COLOR_TAG
value|(gimp_color_tag_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_tag_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae0b03
block|{
DECL|enumerator|GIMP_COLOR_TAG_NONE
name|GIMP_COLOR_TAG_NONE
block|,
comment|/*< desc="None">*/
DECL|enumerator|GIMP_COLOR_TAG_BLUE
name|GIMP_COLOR_TAG_BLUE
block|,
comment|/*< desc="Blue">*/
DECL|enumerator|GIMP_COLOR_TAG_GREEN
name|GIMP_COLOR_TAG_GREEN
block|,
comment|/*< desc="Green">*/
DECL|enumerator|GIMP_COLOR_TAG_YELLOW
name|GIMP_COLOR_TAG_YELLOW
block|,
comment|/*< desc="Yellow">*/
DECL|enumerator|GIMP_COLOR_TAG_ORANGE
name|GIMP_COLOR_TAG_ORANGE
block|,
comment|/*< desc="Orange">*/
DECL|enumerator|GIMP_COLOR_TAG_BROWN
name|GIMP_COLOR_TAG_BROWN
block|,
comment|/*< desc="Brown">*/
DECL|enumerator|GIMP_COLOR_TAG_RED
name|GIMP_COLOR_TAG_RED
block|,
comment|/*< desc="Red">*/
DECL|enumerator|GIMP_COLOR_TAG_VIOLET
name|GIMP_COLOR_TAG_VIOLET
block|,
comment|/*< desc="Violet">*/
DECL|enumerator|GIMP_COLOR_TAG_GRAY
name|GIMP_COLOR_TAG_GRAY
comment|/*< desc="Gray">*/
DECL|typedef|GimpColorTag
block|}
name|GimpColorTag
typedef|;
end_typedef

begin_comment
comment|/**  * GimpComponentType:  * @GIMP_COMPONENT_TYPE_U8:     8-bit integer  * @GIMP_COMPONENT_TYPE_U16:    16-bit integer  * @GIMP_COMPONENT_TYPE_U32:    32-bit integer  * @GIMP_COMPONENT_TYPE_HALF:   16-bit floating point  * @GIMP_COMPONENT_TYPE_FLOAT:  32-bit floating point  * @GIMP_COMPONENT_TYPE_DOUBLE: 64-bit floating point  *  * Encoding types of image components.  *  * Since: 2.10  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_COMPONENT_TYPE
define|#
directive|define
name|GIMP_TYPE_COMPONENT_TYPE
value|(gimp_component_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_component_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae0c03
block|{
DECL|enumerator|GIMP_COMPONENT_TYPE_U8
name|GIMP_COMPONENT_TYPE_U8
init|=
literal|100
block|,
comment|/*< desc="8-bit integer">*/
DECL|enumerator|GIMP_COMPONENT_TYPE_U16
name|GIMP_COMPONENT_TYPE_U16
init|=
literal|200
block|,
comment|/*< desc="16-bit integer">*/
DECL|enumerator|GIMP_COMPONENT_TYPE_U32
name|GIMP_COMPONENT_TYPE_U32
init|=
literal|300
block|,
comment|/*< desc="32-bit integer">*/
DECL|enumerator|GIMP_COMPONENT_TYPE_HALF
name|GIMP_COMPONENT_TYPE_HALF
init|=
literal|500
block|,
comment|/*< desc="16-bit floating point">*/
DECL|enumerator|GIMP_COMPONENT_TYPE_FLOAT
name|GIMP_COMPONENT_TYPE_FLOAT
init|=
literal|600
block|,
comment|/*< desc="32-bit floating point">*/
DECL|enumerator|GIMP_COMPONENT_TYPE_DOUBLE
name|GIMP_COMPONENT_TYPE_DOUBLE
init|=
literal|700
comment|/*< desc="64-bit floating point">*/
DECL|typedef|GimpComponentType
block|}
name|GimpComponentType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpConvertPaletteType:  * @GIMP_CONVERT_PALETTE_GENERATE: Generate optimum palette  * @GIMP_CONVERT_PALETTE_REUSE:    Don't use this one  * @GIMP_CONVERT_PALETTE_WEB:      Use web-optimized palette  * @GIMP_CONVERT_PALETTE_MONO:     Use black and white (1-bit) palette  * @GIMP_CONVERT_PALETTE_CUSTOM:   Use custom palette  *  * Types of palettes for indexed conversion.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_CONVERT_PALETTE_TYPE
define|#
directive|define
name|GIMP_TYPE_CONVERT_PALETTE_TYPE
value|(gimp_convert_palette_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convert_palette_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae0d03
block|{
DECL|enumerator|GIMP_CONVERT_PALETTE_GENERATE
name|GIMP_CONVERT_PALETTE_GENERATE
block|,
comment|/*< desc="Generate optimum palette">*/
DECL|enumerator|GIMP_CONVERT_PALETTE_REUSE
name|GIMP_CONVERT_PALETTE_REUSE
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_CONVERT_PALETTE_WEB
name|GIMP_CONVERT_PALETTE_WEB
block|,
comment|/*< desc="Use web-optimized palette">*/
DECL|enumerator|GIMP_CONVERT_PALETTE_MONO
name|GIMP_CONVERT_PALETTE_MONO
block|,
comment|/*< desc="Use black and white (1-bit) palette">*/
DECL|enumerator|GIMP_CONVERT_PALETTE_CUSTOM
name|GIMP_CONVERT_PALETTE_CUSTOM
comment|/*< desc="Use custom palette">*/
DECL|typedef|GimpConvertPaletteType
block|}
name|GimpConvertPaletteType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpConvolveType:  * @GIMP_CONVOLVE_BLUR:    Blur  * @GIMP_CONVOLVE_SHARPEN: Sharpen  *  * Types of convolutions.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_CONVOLVE_TYPE
define|#
directive|define
name|GIMP_TYPE_CONVOLVE_TYPE
value|(gimp_convolve_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_convolve_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae0e03
block|{
DECL|enumerator|GIMP_CONVOLVE_BLUR
name|GIMP_CONVOLVE_BLUR
block|,
comment|/*< desc="Blur">*/
DECL|enumerator|GIMP_CONVOLVE_SHARPEN
name|GIMP_CONVOLVE_SHARPEN
comment|/*< desc="Sharpen">*/
DECL|typedef|GimpConvolveType
block|}
name|GimpConvolveType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDesaturateMode:  * @GIMP_DESATURATE_LIGHTNESS:  Lightness (HSL)  * @GIMP_DESATURATE_LUMA:       Luma  * @GIMP_DESATURATE_AVERAGE:    Average (HSI Intensity)  * @GIMP_DESATURATE_LUMINANCE:  Luminance  * @GIMP_DESATURATE_VALUE:      Value (HSV)  *  * Grayscale conversion methods.  **/
end_comment

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
DECL|enum|__anon297d2fae0f03
block|{
DECL|enumerator|GIMP_DESATURATE_LIGHTNESS
name|GIMP_DESATURATE_LIGHTNESS
block|,
comment|/*< desc="Lightness (HSL)">*/
DECL|enumerator|GIMP_DESATURATE_LUMA
name|GIMP_DESATURATE_LUMA
block|,
comment|/*< desc="Luma">*/
DECL|enumerator|GIMP_DESATURATE_AVERAGE
name|GIMP_DESATURATE_AVERAGE
block|,
comment|/*< desc="Average (HSI Intensity)">*/
DECL|enumerator|GIMP_DESATURATE_LUMINANCE
name|GIMP_DESATURATE_LUMINANCE
block|,
comment|/*< desc="Luminance">*/
DECL|enumerator|GIMP_DESATURATE_VALUE
name|GIMP_DESATURATE_VALUE
comment|/*< desc="Value (HSV)">*/
DECL|typedef|GimpDesaturateMode
block|}
name|GimpDesaturateMode
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDodgeBurnType:  * @GIMP_DODGE_BURN_TYPE_DODGE: Dodge  * @GIMP_DODGE_BURN_TYPE_BURN:  Burn  *  * Methods for the dodge/burn operation.  **/
end_comment

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
DECL|enum|__anon297d2fae1003
block|{
DECL|enumerator|GIMP_DODGE_BURN_TYPE_DODGE
name|GIMP_DODGE_BURN_TYPE_DODGE
block|,
comment|/*< desc="Dodge">*/
DECL|enumerator|GIMP_DODGE_BURN_TYPE_BURN
name|GIMP_DODGE_BURN_TYPE_BURN
comment|/*< desc="Burn">*/
DECL|typedef|GimpDodgeBurnType
block|}
name|GimpDodgeBurnType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpFillType:  * @GIMP_FILL_FOREGROUND:  Foreground color  * @GIMP_FILL_BACKGROUND:  Background color  * @GIMP_FILL_WHITE:       White  * @GIMP_FILL_TRANSPARENT: Transparency  * @GIMP_FILL_PATTERN:     Pattern  *  * Types of filling.  **/
end_comment

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
DECL|enum|__anon297d2fae1103
block|{
DECL|enumerator|GIMP_FILL_FOREGROUND
name|GIMP_FILL_FOREGROUND
block|,
comment|/*< desc="Foreground color">*/
DECL|enumerator|GIMP_FILL_BACKGROUND
name|GIMP_FILL_BACKGROUND
block|,
comment|/*< desc="Background color">*/
DECL|enumerator|GIMP_FILL_WHITE
name|GIMP_FILL_WHITE
block|,
comment|/*< desc="White">*/
DECL|enumerator|GIMP_FILL_TRANSPARENT
name|GIMP_FILL_TRANSPARENT
block|,
comment|/*< desc="Transparency">*/
DECL|enumerator|GIMP_FILL_PATTERN
name|GIMP_FILL_PATTERN
comment|/*< desc="Pattern">*/
DECL|typedef|GimpFillType
block|}
name|GimpFillType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpForegroundExtractMode:  * @GIMP_FOREGROUND_EXTRACT_SIOX:    Siox  * @GIMP_FOREGROUND_EXTRACT_MATTING: Matting (Since 2.10)  *  * Foreground extraxt engines.  **/
end_comment

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
DECL|enum|__anon297d2fae1203
block|{
DECL|enumerator|GIMP_FOREGROUND_EXTRACT_SIOX
name|GIMP_FOREGROUND_EXTRACT_SIOX
block|,
DECL|enumerator|GIMP_FOREGROUND_EXTRACT_MATTING
name|GIMP_FOREGROUND_EXTRACT_MATTING
DECL|typedef|GimpForegroundExtractMode
block|}
name|GimpForegroundExtractMode
typedef|;
end_typedef

begin_comment
comment|/**  * GimpGradientBlendColorSpace:  * @GIMP_GRADIENT_BLEND_RGB_PERCEPTUAL: Perceptual RGB  * @GIMP_GRADIENT_BLEND_RGB_LINEAR:     Linear RGB  * @GIMP_GRADIENT_BLEND_CIE_LAB:        CIE Lab  *  * Color space for blending gradients.  *  * Since: 2.10  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_BLEND_COLOR_SPACE
define|#
directive|define
name|GIMP_TYPE_GRADIENT_BLEND_COLOR_SPACE
value|(gimp_gradient_blend_color_space_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_blend_color_space_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae1303
block|{
DECL|enumerator|GIMP_GRADIENT_BLEND_RGB_PERCEPTUAL
name|GIMP_GRADIENT_BLEND_RGB_PERCEPTUAL
block|,
comment|/*< desc="Perceptual RGB", nick=rgb-perceptual>*/
DECL|enumerator|GIMP_GRADIENT_BLEND_RGB_LINEAR
name|GIMP_GRADIENT_BLEND_RGB_LINEAR
block|,
comment|/*< desc="Linear RGB",     nick=rgb-linear>*/
DECL|enumerator|GIMP_GRADIENT_BLEND_CIE_LAB
name|GIMP_GRADIENT_BLEND_CIE_LAB
comment|/*< desc="CIE Lab",        nick=cie-lab>*/
DECL|typedef|GimpGradientBlendColorSpace
block|}
name|GimpGradientBlendColorSpace
typedef|;
end_typedef

begin_comment
comment|/**  * GimpGradientSegmentColor:  * @GIMP_GRADIENT_SEGMENT_RGB:     RGB  * @GIMP_GRADIENT_SEGMENT_HSV_CCW: HSV (counter-clockwise hue)  * @GIMP_GRADIENT_SEGMENT_HSV_CW:  HSV (clockwise hue)  *  * Coloring types for gradient segments.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_SEGMENT_COLOR
define|#
directive|define
name|GIMP_TYPE_GRADIENT_SEGMENT_COLOR
value|(gimp_gradient_segment_color_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_segment_color_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae1403
block|{
DECL|enumerator|GIMP_GRADIENT_SEGMENT_RGB
name|GIMP_GRADIENT_SEGMENT_RGB
block|,
comment|/*< desc="RGB">*/
DECL|enumerator|GIMP_GRADIENT_SEGMENT_HSV_CCW
name|GIMP_GRADIENT_SEGMENT_HSV_CCW
block|,
comment|/*< desc="HSV (counter-clockwise hue)", abbrev="HSV (ccw)">*/
DECL|enumerator|GIMP_GRADIENT_SEGMENT_HSV_CW
name|GIMP_GRADIENT_SEGMENT_HSV_CW
comment|/*< desc="HSV (clockwise hue)",         abbrev="HSV (cw)">*/
DECL|typedef|GimpGradientSegmentColor
block|}
name|GimpGradientSegmentColor
typedef|;
end_typedef

begin_comment
comment|/**  * GimpGradientSegmentType:  * @GIMP_GRADIENT_SEGMENT_LINEAR:            Linear  * @GIMP_GRADIENT_SEGMENT_CURVED:            Curved  * @GIMP_GRADIENT_SEGMENT_SINE:              Sinusoidal  * @GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING: Spherical (increasing)  * @GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING: Spherical (decreasing)  *  * Transition functions for gradient segments.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_GRADIENT_SEGMENT_TYPE
define|#
directive|define
name|GIMP_TYPE_GRADIENT_SEGMENT_TYPE
value|(gimp_gradient_segment_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_gradient_segment_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae1503
block|{
DECL|enumerator|GIMP_GRADIENT_SEGMENT_LINEAR
name|GIMP_GRADIENT_SEGMENT_LINEAR
block|,
comment|/*< desc="Linear">*/
DECL|enumerator|GIMP_GRADIENT_SEGMENT_CURVED
name|GIMP_GRADIENT_SEGMENT_CURVED
block|,
comment|/*< desc="Curved">*/
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SINE
name|GIMP_GRADIENT_SEGMENT_SINE
block|,
comment|/*< desc="Sinusoidal">*/
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
name|GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
block|,
comment|/*< desc="Spherical (increasing)", abbrev="Spherical (inc)">*/
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING
name|GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING
comment|/*< desc="Spherical (decreasing)", abbrev="Spherical (dec)">*/
DECL|typedef|GimpGradientSegmentType
block|}
name|GimpGradientSegmentType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpGradientType:  * @GIMP_GRADIENT_LINEAR:               Linear  * @GIMP_GRADIENT_BILINEAR:             Bi-linear  * @GIMP_GRADIENT_RADIAL:               Radial  * @GIMP_GRADIENT_SQUARE:               Square  * @GIMP_GRADIENT_CONICAL_SYMMETRIC:    Conical (symmetric)  * @GIMP_GRADIENT_CONICAL_ASYMMETRIC:   Conical (asymmetric)  * @GIMP_GRADIENT_SHAPEBURST_ANGULAR:   Shaped (angular)  * @GIMP_GRADIENT_SHAPEBURST_SPHERICAL: Shaped (spherical)  * @GIMP_GRADIENT_SHAPEBURST_DIMPLED:   Shaped (dimpled)  * @GIMP_GRADIENT_SPIRAL_CLOCKWISE:     Spiral (clockwise)  * @GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE: Spiral (counter-clockwise)  *  * Gradient shapes.  **/
end_comment

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
DECL|enum|__anon297d2fae1603
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
comment|/*< desc="Conical (symmetric)",        abbrev="Conical (sym)">*/
DECL|enumerator|GIMP_GRADIENT_CONICAL_ASYMMETRIC
name|GIMP_GRADIENT_CONICAL_ASYMMETRIC
block|,
comment|/*< desc="Conical (asymmetric)",       abbrev="Conical (asym)">*/
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
comment|/*< desc="Spiral (clockwise)",         abbrev="Spiral (cw)">*/
DECL|enumerator|GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE
name|GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE
comment|/*< desc="Spiral (counter-clockwise)", abbrev="Spiral (ccw)">*/
DECL|typedef|GimpGradientType
block|}
name|GimpGradientType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpGridStyle:  * @GIMP_GRID_DOTS:          Intersections (dots)  * @GIMP_GRID_INTERSECTIONS: Intersections (crosshairs)  * @GIMP_GRID_ON_OFF_DASH:   Dashed  * @GIMP_GRID_DOUBLE_DASH:   Double dashed  * @GIMP_GRID_SOLID:         Solid  *  * Rendering types for the display grid.  **/
end_comment

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
DECL|enum|__anon297d2fae1703
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

begin_comment
comment|/**  * GimpHueRange:  * @GIMP_HUE_RANGE_ALL:     All hues  * @GIMP_HUE_RANGE_RED:     Red hues  * @GIMP_HUE_RANGE_YELLOW:  Yellow hues  * @GIMP_HUE_RANGE_GREEN:   Green hues  * @GIMP_HUE_RANGE_CYAN:    Cyan hues  * @GIMP_HUE_RANGE_BLUE:    Blue hues  * @GIMP_HUE_RANGE_MAGENTA: Magenta hues  *  * Hue ranges.  **/
end_comment

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
DECL|enum|__anon297d2fae1803
block|{
DECL|enumerator|GIMP_HUE_RANGE_ALL
name|GIMP_HUE_RANGE_ALL
block|,
DECL|enumerator|GIMP_HUE_RANGE_RED
name|GIMP_HUE_RANGE_RED
block|,
DECL|enumerator|GIMP_HUE_RANGE_YELLOW
name|GIMP_HUE_RANGE_YELLOW
block|,
DECL|enumerator|GIMP_HUE_RANGE_GREEN
name|GIMP_HUE_RANGE_GREEN
block|,
DECL|enumerator|GIMP_HUE_RANGE_CYAN
name|GIMP_HUE_RANGE_CYAN
block|,
DECL|enumerator|GIMP_HUE_RANGE_BLUE
name|GIMP_HUE_RANGE_BLUE
block|,
DECL|enumerator|GIMP_HUE_RANGE_MAGENTA
name|GIMP_HUE_RANGE_MAGENTA
DECL|typedef|GimpHueRange
block|}
name|GimpHueRange
typedef|;
end_typedef

begin_comment
comment|/**  * GimpIconType:  * @GIMP_ICON_TYPE_ICON_NAME:     Icon name  * @GIMP_ICON_TYPE_INLINE_PIXBUF: Inline pixbuf  * @GIMP_ICON_TYPE_IMAGE_FILE:    Image file  *  * Icon types for plug-ins to register.  **/
end_comment

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
DECL|enum|__anon297d2fae1903
block|{
DECL|enumerator|GIMP_ICON_TYPE_ICON_NAME
name|GIMP_ICON_TYPE_ICON_NAME
block|,
comment|/*< desc="Icon name">*/
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

begin_comment
comment|/**  * GimpImageBaseType:  * @GIMP_RGB:     RGB color  * @GIMP_GRAY:    Grayscale  * @GIMP_INDEXED: Indexed color  *  * Image color models.  **/
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
DECL|enum|__anon297d2fae1a03
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

begin_comment
comment|/**  * GimpImageType:  * @GIMP_RGB_IMAGE:      RGB  * @GIMP_RGBA_IMAGE:     RGB-alpha  * @GIMP_GRAY_IMAGE:     Grayscale  * @GIMP_GRAYA_IMAGE:    Grayscale-alpha  * @GIMP_INDEXED_IMAGE:  Indexed  * @GIMP_INDEXEDA_IMAGE: Indexed-alpha  *  * Possible drawable types.  **/
end_comment

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
DECL|enum|__anon297d2fae1b03
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

begin_comment
comment|/**  * GimpInkBlobType:  * @GIMP_INK_BLOB_TYPE_CIRCLE:  Circle  * @GIMP_INK_BLOB_TYPE_SQUARE:  Square  * @GIMP_INK_BLOB_TYPE_DIAMOND: Diamond  *  * Ink tool tips.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_INK_BLOB_TYPE
define|#
directive|define
name|GIMP_TYPE_INK_BLOB_TYPE
value|(gimp_ink_blob_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_ink_blob_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae1c03
block|{
DECL|enumerator|GIMP_INK_BLOB_TYPE_CIRCLE
name|GIMP_INK_BLOB_TYPE_CIRCLE
block|,
comment|/*< desc="Circle">*/
DECL|enumerator|GIMP_INK_BLOB_TYPE_SQUARE
name|GIMP_INK_BLOB_TYPE_SQUARE
block|,
comment|/*< desc="Square">*/
DECL|enumerator|GIMP_INK_BLOB_TYPE_DIAMOND
name|GIMP_INK_BLOB_TYPE_DIAMOND
comment|/*< desc="Diamond">*/
DECL|typedef|GimpInkBlobType
block|}
name|GimpInkBlobType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpInterpolationType:  * @GIMP_INTERPOLATION_NONE:   None  * @GIMP_INTERPOLATION_LINEAR: Linear  * @GIMP_INTERPOLATION_CUBIC:  Cubic  * @GIMP_INTERPOLATION_NOHALO: NoHalo  * @GIMP_INTERPOLATION_LOHALO: LoHalo  *  * Interpolation types.  **/
end_comment

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
DECL|enum|__anon297d2fae1d03
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
DECL|enumerator|GIMP_INTERPOLATION_NOHALO
name|GIMP_INTERPOLATION_NOHALO
block|,
comment|/*< desc="NoHalo">*/
DECL|enumerator|GIMP_INTERPOLATION_LOHALO
name|GIMP_INTERPOLATION_LOHALO
comment|/*< desc="LoHalo">*/
DECL|typedef|GimpInterpolationType
block|}
name|GimpInterpolationType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpJoinStyle:  * @GIMP_JOIN_MITER: Miter  * @GIMP_JOIN_ROUND: Round  * @GIMP_JOIN_BEVEL: Bevel  *  * Line join styles.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_JOIN_STYLE
define|#
directive|define
name|GIMP_TYPE_JOIN_STYLE
value|(gimp_join_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_join_style_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae1e03
block|{
DECL|enumerator|GIMP_JOIN_MITER
name|GIMP_JOIN_MITER
block|,
comment|/*< desc="Miter">*/
DECL|enumerator|GIMP_JOIN_ROUND
name|GIMP_JOIN_ROUND
block|,
comment|/*< desc="Round">*/
DECL|enumerator|GIMP_JOIN_BEVEL
name|GIMP_JOIN_BEVEL
comment|/*< desc="Bevel">*/
DECL|typedef|GimpJoinStyle
block|}
name|GimpJoinStyle
typedef|;
end_typedef

begin_comment
comment|/**  * GimpMaskApplyMode:  * @GIMP_MASK_APPLY:   Apply the mask  * @GIMP_MASK_DISCARD: Discard the mask  *  * Layer mask apply modes.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_MASK_APPLY_MODE
define|#
directive|define
name|GIMP_TYPE_MASK_APPLY_MODE
value|(gimp_mask_apply_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_mask_apply_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae1f03
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

begin_comment
comment|/**  * GimpMergeType:  * @GIMP_EXPAND_AS_NECESSARY:  Expanded as necessary  * @GIMP_CLIP_TO_IMAGE:        Clipped to image  * @GIMP_CLIP_TO_BOTTOM_LAYER: Clipped to bottom layer  * @GIMP_FLATTEN_IMAGE:        Flatten  *  * Types of merging layers.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_MERGE_TYPE
define|#
directive|define
name|GIMP_TYPE_MERGE_TYPE
value|(gimp_merge_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_merge_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae2003
block|{
DECL|enumerator|GIMP_EXPAND_AS_NECESSARY
name|GIMP_EXPAND_AS_NECESSARY
block|,
comment|/*< desc="Expanded as necessary">*/
DECL|enumerator|GIMP_CLIP_TO_IMAGE
name|GIMP_CLIP_TO_IMAGE
block|,
comment|/*< desc="Clipped to image">*/
DECL|enumerator|GIMP_CLIP_TO_BOTTOM_LAYER
name|GIMP_CLIP_TO_BOTTOM_LAYER
block|,
comment|/*< desc="Clipped to bottom layer">*/
DECL|enumerator|GIMP_FLATTEN_IMAGE
name|GIMP_FLATTEN_IMAGE
comment|/*< desc="Flatten">*/
DECL|typedef|GimpMergeType
block|}
name|GimpMergeType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpMessageHandlerType:  * @GIMP_MESSAGE_BOX:   A popup dialog  * @GIMP_CONSOLE:       The terminal  * @GIMP_ERROR_CONSOLE: The error console dockable  *  * How to present messages.  **/
end_comment

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
DECL|enum|__anon297d2fae2103
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

begin_comment
comment|/**  * GimpOffsetType:  * @GIMP_OFFSET_BACKGROUND:  Background  * @GIMP_OFFSET_TRANSPARENT: Transparent  *  * Background fill types for the offset operation.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_OFFSET_TYPE
define|#
directive|define
name|GIMP_TYPE_OFFSET_TYPE
value|(gimp_offset_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_offset_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae2203
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

begin_comment
comment|/**  * GimpOrientationType:  * @GIMP_ORIENTATION_HORIZONTAL: Horizontal  * @GIMP_ORIENTATION_VERTICAL:   Vertical  * @GIMP_ORIENTATION_UNKNOWN:    Unknown  *  * Orientations for various purposes.  **/
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
DECL|enum|__anon297d2fae2303
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

begin_comment
comment|/**  * GimpPaintApplicationMode:  * @GIMP_PAINT_CONSTANT:    Constant  * @GIMP_PAINT_INCREMENTAL: Incremental  *  * Paint application modes.  **/
end_comment

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
DECL|enum|__anon297d2fae2403
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

begin_comment
comment|/**  * GimpPDBArgType:  * @GIMP_PDB_INT32:       32-bit integer  * @GIMP_PDB_INT16:       16-bit integer  * @GIMP_PDB_INT8:        8-bit integer  * @GIMP_PDB_FLOAT:       Float  * @GIMP_PDB_STRING:      String  * @GIMP_PDB_INT32ARRAY:  Array of INT32  * @GIMP_PDB_INT16ARRAY:  Array of INT16  * @GIMP_PDB_INT8ARRAY:   Array of INT8  * @GIMP_PDB_FLOATARRAY:  Array of floats  * @GIMP_PDB_STRINGARRAY: Array of strings  * @GIMP_PDB_COLOR:       Color  * @GIMP_PDB_ITEM:        Item ID  * @GIMP_PDB_DISPLAY:     Display ID  * @GIMP_PDB_IMAGE:       Image ID  * @GIMP_PDB_LAYER:       Layer ID  * @GIMP_PDB_CHANNEL:     Channel ID  * @GIMP_PDB_DRAWABLE:    Drawable ID  * @GIMP_PDB_SELECTION:   Selection ID  * @GIMP_PDB_COLORARRAY:  Array of colors  * @GIMP_PDB_VECTORS:     Vectors (psath) ID  * @GIMP_PDB_PARASITE:    Parasite  * @GIMP_PDB_STATUS:      Procedure return status  * @GIMP_PDB_END:         Marker for last enum value  *  * Parameter types of the PDB.  **/
end_comment

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
DECL|enum|__anon297d2fae2503
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
DECL|enumerator|GIMP_PDB_ITEM
name|GIMP_PDB_ITEM
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
DECL|typedef|GimpPDBArgType
block|}
name|GimpPDBArgType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpPDBErrorHandler:  * @GIMP_PDB_ERROR_HANDLER_INTERNAL: Internal  * @GIMP_PDB_ERROR_HANDLER_PLUGIN:   Plug-In  *  * PDB error handlers.  **/
end_comment

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
DECL|enum|__anon297d2fae2603
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

begin_comment
comment|/**  * GimpPDBProcType:  * @GIMP_INTERNAL:  Internal GIMP procedure  * @GIMP_PLUGIN:    GIMP Plug-In  * @GIMP_EXTENSION: GIMP Extension  * @GIMP_TEMPORARY: Temporary Procedure  *  * Types of PDB procedures.  **/
end_comment

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
DECL|enum|__anon297d2fae2703
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

begin_comment
comment|/**  * GimpPDBStatusType:  * @GIMP_PDB_EXECUTION_ERROR: Execution error  * @GIMP_PDB_CALLING_ERROR:   Calling error  * @GIMP_PDB_PASS_THROUGH:    Pass through  * @GIMP_PDB_SUCCESS:         Success  * @GIMP_PDB_CANCEL:          User cancel  *  * Return status of PDB calls.  **/
end_comment

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
DECL|enum|__anon297d2fae2803
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

begin_comment
comment|/**  * GimpPrecision:  * @GIMP_PRECISION_U8_LINEAR:     8-bit linear integer  * @GIMP_PRECISION_U8_GAMMA:      8-bit gamma integer  * @GIMP_PRECISION_U16_LINEAR:    16-bit linear integer  * @GIMP_PRECISION_U16_GAMMA:     16-bit gamma integer  * @GIMP_PRECISION_U32_LINEAR:    32-bit linear integer  * @GIMP_PRECISION_U32_GAMMA:     32-bit gamma integer  * @GIMP_PRECISION_HALF_LINEAR:   16-bit linear floating point  * @GIMP_PRECISION_HALF_GAMMA:    16-bit gamma floating point  * @GIMP_PRECISION_FLOAT_LINEAR:  32-bit linear floating point  * @GIMP_PRECISION_FLOAT_GAMMA:   32-bit gamma floating point  * @GIMP_PRECISION_DOUBLE_LINEAR: 64-bit linear floating point  * @GIMP_PRECISION_DOUBLE_GAMMA:  64-bit gamma floating point  *  * Precisions for pixel encoding.  *  * Since: 2.10  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_PRECISION
define|#
directive|define
name|GIMP_TYPE_PRECISION
value|(gimp_precision_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_precision_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae2903
block|{
DECL|enumerator|GIMP_PRECISION_U8_LINEAR
name|GIMP_PRECISION_U8_LINEAR
init|=
literal|100
block|,
comment|/*< desc="8-bit linear integer">*/
DECL|enumerator|GIMP_PRECISION_U8_GAMMA
name|GIMP_PRECISION_U8_GAMMA
init|=
literal|150
block|,
comment|/*< desc="8-bit gamma integer">*/
DECL|enumerator|GIMP_PRECISION_U16_LINEAR
name|GIMP_PRECISION_U16_LINEAR
init|=
literal|200
block|,
comment|/*< desc="16-bit linear integer">*/
DECL|enumerator|GIMP_PRECISION_U16_GAMMA
name|GIMP_PRECISION_U16_GAMMA
init|=
literal|250
block|,
comment|/*< desc="16-bit gamma integer">*/
DECL|enumerator|GIMP_PRECISION_U32_LINEAR
name|GIMP_PRECISION_U32_LINEAR
init|=
literal|300
block|,
comment|/*< desc="32-bit linear integer">*/
DECL|enumerator|GIMP_PRECISION_U32_GAMMA
name|GIMP_PRECISION_U32_GAMMA
init|=
literal|350
block|,
comment|/*< desc="32-bit gamma integer">*/
DECL|enumerator|GIMP_PRECISION_HALF_LINEAR
name|GIMP_PRECISION_HALF_LINEAR
init|=
literal|500
block|,
comment|/*< desc="16-bit linear floating point">*/
DECL|enumerator|GIMP_PRECISION_HALF_GAMMA
name|GIMP_PRECISION_HALF_GAMMA
init|=
literal|550
block|,
comment|/*< desc="16-bit gamma floating point">*/
DECL|enumerator|GIMP_PRECISION_FLOAT_LINEAR
name|GIMP_PRECISION_FLOAT_LINEAR
init|=
literal|600
block|,
comment|/*< desc="32-bit linear floating point">*/
DECL|enumerator|GIMP_PRECISION_FLOAT_GAMMA
name|GIMP_PRECISION_FLOAT_GAMMA
init|=
literal|650
block|,
comment|/*< desc="32-bit gamma floating point">*/
DECL|enumerator|GIMP_PRECISION_DOUBLE_LINEAR
name|GIMP_PRECISION_DOUBLE_LINEAR
init|=
literal|700
block|,
comment|/*< desc="64-bit linear floating point">*/
DECL|enumerator|GIMP_PRECISION_DOUBLE_GAMMA
name|GIMP_PRECISION_DOUBLE_GAMMA
init|=
literal|750
comment|/*< desc="64-bit gamma floating point">*/
DECL|typedef|GimpPrecision
block|}
name|GimpPrecision
typedef|;
end_typedef

begin_comment
comment|/**  * GimpProgressCommand:  * @GIMP_PROGRESS_COMMAND_START:      Start a progress  * @GIMP_PROGRESS_COMMAND_END:        End the progress  * @GIMP_PROGRESS_COMMAND_SET_TEXT:   Set the text  * @GIMP_PROGRESS_COMMAND_SET_VALUE:  Set the percentage  * @GIMP_PROGRESS_COMMAND_PULSE:      Pulse the progress  * @GIMP_PROGRESS_COMMAND_GET_WINDOW: Get the window where the progress is shown  *  * Commands for the progress API.  **/
end_comment

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
DECL|enum|__anon297d2fae2a03
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

begin_comment
comment|/**  * GimpRepeatMode:  * @GIMP_REPEAT_NONE:       None (extend)  * @GIMP_REPEAT_SAWTOOTH:   Sawtooth wave  * @GIMP_REPEAT_TRIANGULAR: Triangular wave  * @GIMP_REPEAT_TRUNCATE:   Truncate  *  * Repeat modes for example for gradients.  **/
end_comment

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
DECL|enum|__anon297d2fae2b03
block|{
DECL|enumerator|GIMP_REPEAT_NONE
name|GIMP_REPEAT_NONE
block|,
comment|/*< desc="None (extend)">*/
DECL|enumerator|GIMP_REPEAT_SAWTOOTH
name|GIMP_REPEAT_SAWTOOTH
block|,
comment|/*< desc="Sawtooth wave">*/
DECL|enumerator|GIMP_REPEAT_TRIANGULAR
name|GIMP_REPEAT_TRIANGULAR
block|,
comment|/*< desc="Triangular wave">*/
DECL|enumerator|GIMP_REPEAT_TRUNCATE
name|GIMP_REPEAT_TRUNCATE
comment|/*< desc="Truncate">*/
DECL|typedef|GimpRepeatMode
block|}
name|GimpRepeatMode
typedef|;
end_typedef

begin_comment
comment|/**  * GimpRotationType:  * @GIMP_ROTATE_90:  90 degrees  * @GIMP_ROTATE_180: 180 degrees  * @GIMP_ROTATE_270: 270 degrees  *  * Types of simple rotations.  **/
end_comment

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
DECL|enum|__anon297d2fae2c03
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

begin_comment
comment|/**  * GimpRunMode:  * @GIMP_RUN_INTERACTIVE:    Run interactively  * @GIMP_RUN_NONINTERACTIVE: Run non-interactively  * @GIMP_RUN_WITH_LAST_VALS: Run with last used values  *  * Run modes for plug-ins.  **/
end_comment

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
DECL|enum|__anon297d2fae2d03
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

begin_comment
comment|/**  * GimpSelectCriterion:  * @GIMP_SELECT_CRITERION_COMPOSITE: Composite  * @GIMP_SELECT_CRITERION_R:         Red  * @GIMP_SELECT_CRITERION_G:         Green  * @GIMP_SELECT_CRITERION_B:         Blue  * @GIMP_SELECT_CRITERION_H:         HSV Hue  * @GIMP_SELECT_CRITERION_S:         HSV Saturation  * @GIMP_SELECT_CRITERION_V:         HSV Value  * @GIMP_SELECT_CRITERION_A:         Alpha  * @GIMP_SELECT_CRITERION_LCH_L:     LCh Lightness  * @GIMP_SELECT_CRITERION_LCH_C:     LCh Chroma  * @GIMP_SELECT_CRITERION_LCH_H:     LCh Hue)  *  * Criterions for color similarity.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_SELECT_CRITERION
define|#
directive|define
name|GIMP_TYPE_SELECT_CRITERION
value|(gimp_select_criterion_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_select_criterion_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae2e03
block|{
DECL|enumerator|GIMP_SELECT_CRITERION_COMPOSITE
name|GIMP_SELECT_CRITERION_COMPOSITE
block|,
comment|/*< desc="Composite">*/
DECL|enumerator|GIMP_SELECT_CRITERION_R
name|GIMP_SELECT_CRITERION_R
block|,
comment|/*< desc="Red">*/
DECL|enumerator|GIMP_SELECT_CRITERION_G
name|GIMP_SELECT_CRITERION_G
block|,
comment|/*< desc="Green">*/
DECL|enumerator|GIMP_SELECT_CRITERION_B
name|GIMP_SELECT_CRITERION_B
block|,
comment|/*< desc="Blue">*/
DECL|enumerator|GIMP_SELECT_CRITERION_H
name|GIMP_SELECT_CRITERION_H
block|,
comment|/*< desc="HSV Hue">*/
DECL|enumerator|GIMP_SELECT_CRITERION_S
name|GIMP_SELECT_CRITERION_S
block|,
comment|/*< desc="HSV Saturation">*/
DECL|enumerator|GIMP_SELECT_CRITERION_V
name|GIMP_SELECT_CRITERION_V
block|,
comment|/*< desc="HSV Value">*/
DECL|enumerator|GIMP_SELECT_CRITERION_A
name|GIMP_SELECT_CRITERION_A
block|,
comment|/*< desc="Alpha">*/
DECL|enumerator|GIMP_SELECT_CRITERION_LCH_L
name|GIMP_SELECT_CRITERION_LCH_L
block|,
comment|/*< desc="LCh Lightness">*/
DECL|enumerator|GIMP_SELECT_CRITERION_LCH_C
name|GIMP_SELECT_CRITERION_LCH_C
block|,
comment|/*< desc="LCh Chroma">*/
DECL|enumerator|GIMP_SELECT_CRITERION_LCH_H
name|GIMP_SELECT_CRITERION_LCH_H
block|,
comment|/*< desc="LCh Hue">*/
DECL|typedef|GimpSelectCriterion
block|}
name|GimpSelectCriterion
typedef|;
end_typedef

begin_comment
comment|/**  * GimpSizeType:  * @GIMP_PIXELS: Pixels  * @GIMP_POINTS: Points  *  * Size types for the old-style text API.  **/
end_comment

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
DECL|enum|__anon297d2fae2f03
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

begin_comment
comment|/**  * GimpStackTraceMode:  * @GIMP_STACK_TRACE_NEVER:  Never  * @GIMP_STACK_TRACE_QUERY:  Ask each time  * @GIMP_STACK_TRACE_ALWAYS: Always  *  * When to generate stack traces in case of an error.  **/
end_comment

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
DECL|enum|__anon297d2fae3003
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

begin_comment
comment|/**  * GimpStrokeMethod:  * @GIMP_STROKE_LINE:         Stroke line  * @GIMP_STROKE_PAINT_METHOD: Stroke with a paint tool  *  * Methods of stroking selections and paths.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_STROKE_METHOD
define|#
directive|define
name|GIMP_TYPE_STROKE_METHOD
value|(gimp_stroke_method_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_stroke_method_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon297d2fae3103
block|{
DECL|enumerator|GIMP_STROKE_LINE
name|GIMP_STROKE_LINE
block|,
comment|/*< desc="Stroke line">*/
DECL|enumerator|GIMP_STROKE_PAINT_METHOD
name|GIMP_STROKE_PAINT_METHOD
comment|/*< desc="Stroke with a paint tool">*/
DECL|typedef|GimpStrokeMethod
block|}
name|GimpStrokeMethod
typedef|;
end_typedef

begin_comment
comment|/**  * GimpTextDirection:  * @GIMP_TEXT_DIRECTION_LTR: From left to right  * @GIMP_TEXT_DIRECTION_RTL: From right to left  *  * Text directions.  **/
end_comment

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
DECL|enum|__anon297d2fae3203
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

begin_comment
comment|/**  * GimpTextHintStyle:  * @GIMP_TEXT_HINT_STYLE_NONE:   None  * @GIMP_TEXT_HINT_STYLE_SLIGHT: Slight  * @GIMP_TEXT_HINT_STYLE_MEDIUM: Medium  * @GIMP_TEXT_HINT_STYLE_FULL:   Full  *  * Text hint strengths.  **/
end_comment

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
DECL|enum|__anon297d2fae3303
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

begin_comment
comment|/**  * GimpTextJustification:  * @GIMP_TEXT_JUSTIFY_LEFT:   Left justified  * @GIMP_TEXT_JUSTIFY_RIGHT:  Right justified  * @GIMP_TEXT_JUSTIFY_CENTER: Centered  * @GIMP_TEXT_JUSTIFY_FILL:   Filled  *  * Text justifications.  **/
end_comment

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
DECL|enum|__anon297d2fae3403
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

begin_comment
comment|/**  * GimpTransferMode:  * @GIMP_TRANSFER_SHADOWS:    Shadows  * @GIMP_TRANSFER_MIDTONES:   Midtones  * @GIMP_TRANSFER_HIGHLIGHTS: Highlights  *  * For choosing which brightness ranges to transform.  **/
end_comment

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
DECL|enum|__anon297d2fae3503
block|{
DECL|enumerator|GIMP_TRANSFER_SHADOWS
name|GIMP_TRANSFER_SHADOWS
block|,
comment|/*< desc="Shadows">*/
DECL|enumerator|GIMP_TRANSFER_MIDTONES
name|GIMP_TRANSFER_MIDTONES
block|,
comment|/*< desc="Midtones">*/
DECL|enumerator|GIMP_TRANSFER_HIGHLIGHTS
name|GIMP_TRANSFER_HIGHLIGHTS
comment|/*< desc="Highlights">*/
DECL|typedef|GimpTransferMode
block|}
name|GimpTransferMode
typedef|;
end_typedef

begin_comment
comment|/**  * GimpTransformDirection:  * @GIMP_TRANSFORM_FORWARD:  Normal (Forward)  * @GIMP_TRANSFORM_BACKWARD: Corrective (Backward)  *  * Transform directions.  **/
end_comment

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
DECL|enum|__anon297d2fae3603
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

begin_comment
comment|/**  * GimpTransformResize:  * @GIMP_TRANSFORM_RESIZE_ADJUST:           Adjust  * @GIMP_TRANSFORM_RESIZE_CLIP:             Clip  * @GIMP_TRANSFORM_RESIZE_CROP:             Crop to result  * @GIMP_TRANSFORM_RESIZE_CROP_WITH_ASPECT: Crop with aspect  *  * Ways of clipping the result when transforming drawables.  **/
end_comment

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
DECL|enum|__anon297d2fae3703
block|{
DECL|enumerator|GIMP_TRANSFORM_RESIZE_ADJUST
name|GIMP_TRANSFORM_RESIZE_ADJUST
block|,
comment|/*< desc="Adjust">*/
DECL|enumerator|GIMP_TRANSFORM_RESIZE_CLIP
name|GIMP_TRANSFORM_RESIZE_CLIP
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

begin_comment
comment|/**  * GimpUnit:  * @GIMP_UNIT_PIXEL:   Pixels  * @GIMP_UNIT_INCH:    Inches  * @GIMP_UNIT_MM:      Millimeters  * @GIMP_UNIT_POINT:   Points  * @GIMP_UNIT_PICA:    Picas  * @GIMP_UNIT_END:     Marker for end-of-builtin-units  * @GIMP_UNIT_PERCENT: Pseudo-unit percent  *  * Units used for dimensions in images.  **/
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon297d2fae3803
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

begin_comment
comment|/**  * GimpVectorsStrokeType:  * @GIMP_VECTORS_STROKE_TYPE_BEZIER: A bezier stroke  *  * Possible type of strokes in vectors objects.  **/
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
DECL|enum|__anon297d2fae3903
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

