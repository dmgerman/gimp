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
DECL|enum|__anon2c88fb8e0103
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
DECL|enum|__anon2c88fb8e0203
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
DECL|enum|__anon2c88fb8e0303
block|{
DECL|enumerator|GIMP_MAKE_PALETTE
name|GIMP_MAKE_PALETTE
block|,
comment|/*< desc="Generate optimum palette">*/
DECL|enumerator|GIMP_REUSE_PALETTE
name|GIMP_REUSE_PALETTE
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_WEB_PALETTE
name|GIMP_WEB_PALETTE
block|,
comment|/*< desc="Use web-optimized palette">*/
DECL|enumerator|GIMP_MONO_PALETTE
name|GIMP_MONO_PALETTE
block|,
comment|/*< desc="Use black and white (1-bit) palette">*/
DECL|enumerator|GIMP_CUSTOM_PALETTE
name|GIMP_CUSTOM_PALETTE
comment|/*< desc="Use custom palette">*/
DECL|typedef|GimpConvertPaletteType
block|}
name|GimpConvertPaletteType
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
DECL|enum|__anon2c88fb8e0403
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
DECL|macro|GIMP_TYPE_ALIGNMENT
define|#
directive|define
name|GIMP_TYPE_ALIGNMENT
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
DECL|enum|__anon2c88fb8e0503
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
DECL|typedef|GimpAlignmentType
block|}
name|GimpAlignmentType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ALIGN_REFERENCE
define|#
directive|define
name|GIMP_TYPE_ALIGN_REFERENCE
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
DECL|enum|__anon2c88fb8e0603
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
DECL|enum|__anon2c88fb8e0703
block|{
DECL|enumerator|GIMP_FOREGROUND_FILL
name|GIMP_FOREGROUND_FILL
block|,
comment|/*< desc="Foreground color">*/
DECL|enumerator|GIMP_BACKGROUND_FILL
name|GIMP_BACKGROUND_FILL
block|,
comment|/*< desc="Background color">*/
DECL|enumerator|GIMP_WHITE_FILL
name|GIMP_WHITE_FILL
block|,
comment|/*< desc="White">*/
DECL|enumerator|GIMP_TRANSPARENT_FILL
name|GIMP_TRANSPARENT_FILL
block|,
comment|/*< desc="Transparency">*/
DECL|enumerator|GIMP_PATTERN_FILL
name|GIMP_PATTERN_FILL
block|,
comment|/*< desc="Pattern">*/
DECL|enumerator|GIMP_NO_FILL
name|GIMP_NO_FILL
comment|/*< desc="None",   pdb-skip>*/
DECL|typedef|GimpFillType
block|}
name|GimpFillType
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
DECL|enum|__anon2c88fb8e0803
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
comment|/*< pdb-skip>*/
DECL|enum|__anon2c88fb8e0903
block|{
DECL|enumerator|GIMP_STROKE_METHOD_LIBART
name|GIMP_STROKE_METHOD_LIBART
block|,
comment|/*< desc="Stroke line">*/
DECL|enumerator|GIMP_STROKE_METHOD_PAINT_CORE
name|GIMP_STROKE_METHOD_PAINT_CORE
comment|/*< desc="Stroke with a paint tool">*/
DECL|typedef|GimpStrokeMethod
block|}
name|GimpStrokeMethod
typedef|;
end_typedef

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
comment|/*< pdb-skip>*/
DECL|enum|__anon2c88fb8e0a03
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
comment|/*< pdb-skip>*/
DECL|enum|__anon2c88fb8e0b03
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
DECL|enum|__anon2c88fb8e0c03
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
DECL|enum|__anon2c88fb8e0d03
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
DECL|enum|__anon2c88fb8e0e03
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
DECL|enum|__anon2c88fb8e0f03
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
DECL|enum|__anon2c88fb8e1003
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
DECL|enum|__anon2c88fb8e1103
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
DECL|enum|__anon2c88fb8e1203
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
DECL|enum|__anon2c88fb8e1303
block|{
DECL|enumerator|GIMP_SELECTION_OFF
name|GIMP_SELECTION_OFF
block|,
DECL|enumerator|GIMP_SELECTION_LAYER_OFF
name|GIMP_SELECTION_LAYER_OFF
block|,
DECL|enumerator|GIMP_SELECTION_LAYER_ON
name|GIMP_SELECTION_LAYER_ON
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
DECL|enum|__anon2c88fb8e1403
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
DECL|enum|__anon2c88fb8e1503
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
DECL|enum|__anon2c88fb8e1603
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
DECL|enum|__anon2c88fb8e1703
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
DECL|enum|__anon2c88fb8e1803
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
DECL|enum|__anon2c88fb8e1903
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
DECL|enum|__anon2c88fb8e1a03
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
DECL|enum|__anon2c88fb8e1b03
block|{
DECL|enumerator|GIMP_GRADIENT_SEGMENT_LINEAR
name|GIMP_GRADIENT_SEGMENT_LINEAR
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_CURVED
name|GIMP_GRADIENT_SEGMENT_CURVED
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SINE
name|GIMP_GRADIENT_SEGMENT_SINE
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
name|GIMP_GRADIENT_SEGMENT_SPHERE_INCREASING
block|,
DECL|enumerator|GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING
name|GIMP_GRADIENT_SEGMENT_SPHERE_DECREASING
DECL|typedef|GimpGradientSegmentType
block|}
name|GimpGradientSegmentType
typedef|;
end_typedef

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
DECL|enum|__anon2c88fb8e1c03
block|{
DECL|enumerator|GIMP_GRADIENT_SEGMENT_RGB
name|GIMP_GRADIENT_SEGMENT_RGB
block|,
comment|/* normal RGB           */
DECL|enumerator|GIMP_GRADIENT_SEGMENT_HSV_CCW
name|GIMP_GRADIENT_SEGMENT_HSV_CCW
block|,
comment|/* counterclockwise hue */
DECL|enumerator|GIMP_GRADIENT_SEGMENT_HSV_CW
name|GIMP_GRADIENT_SEGMENT_HSV_CW
comment|/* clockwise hue        */
DECL|typedef|GimpGradientSegmentColor
block|}
name|GimpGradientSegmentColor
typedef|;
end_typedef

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
DECL|enum|__anon2c88fb8e1d03
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
DECL|enum|__anon2c88fb8e1e03
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
DECL|enum|__anon2c88fb8e1f03
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
comment|/*< desc="Hue">*/
DECL|enumerator|GIMP_SELECT_CRITERION_S
name|GIMP_SELECT_CRITERION_S
block|,
comment|/*< desc="Saturation">*/
DECL|enumerator|GIMP_SELECT_CRITERION_V
name|GIMP_SELECT_CRITERION_V
comment|/*< desc="Value">*/
DECL|typedef|GimpSelectCriterion
block|}
name|GimpSelectCriterion
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
DECL|enum|__anon2c88fb8e2003
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
DECL|enum|__anon2c88fb8e2103
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
comment|/*< desc="Convert to RGB workspace">*/
DECL|typedef|GimpColorProfilePolicy
block|}
name|GimpColorProfilePolicy
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2c88fb8e2203
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
DECL|enumerator|GIMP_CONTEXT_PROP_PATTERN
name|GIMP_CONTEXT_PROP_PATTERN
init|=
literal|12
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_GRADIENT
name|GIMP_CONTEXT_PROP_GRADIENT
init|=
literal|13
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_PALETTE
name|GIMP_CONTEXT_PROP_PALETTE
init|=
literal|14
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_FONT
name|GIMP_CONTEXT_PROP_FONT
init|=
literal|15
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_BUFFER
name|GIMP_CONTEXT_PROP_BUFFER
init|=
literal|16
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_IMAGEFILE
name|GIMP_CONTEXT_PROP_IMAGEFILE
init|=
literal|17
block|,
DECL|enumerator|GIMP_CONTEXT_PROP_TEMPLATE
name|GIMP_CONTEXT_PROP_TEMPLATE
init|=
literal|18
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
DECL|enum|__anon2c88fb8e2303
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
DECL|enumerator|GIMP_CONTEXT_PAINT_INFO_MASK
name|GIMP_CONTEXT_PAINT_INFO_MASK
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_CONTEXT_FOREGROUND_MASK
name|GIMP_CONTEXT_FOREGROUND_MASK
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_CONTEXT_BACKGROUND_MASK
name|GIMP_CONTEXT_BACKGROUND_MASK
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_CONTEXT_OPACITY_MASK
name|GIMP_CONTEXT_OPACITY_MASK
init|=
literal|1
operator|<<
literal|8
block|,
DECL|enumerator|GIMP_CONTEXT_PAINT_MODE_MASK
name|GIMP_CONTEXT_PAINT_MODE_MASK
init|=
literal|1
operator|<<
literal|9
block|,
DECL|enumerator|GIMP_CONTEXT_BRUSH_MASK
name|GIMP_CONTEXT_BRUSH_MASK
init|=
literal|1
operator|<<
literal|10
block|,
DECL|enumerator|GIMP_CONTEXT_DYNAMICS_MASK
name|GIMP_CONTEXT_DYNAMICS_MASK
init|=
literal|1
operator|<<
literal|11
block|,
DECL|enumerator|GIMP_CONTEXT_PATTERN_MASK
name|GIMP_CONTEXT_PATTERN_MASK
init|=
literal|1
operator|<<
literal|12
block|,
DECL|enumerator|GIMP_CONTEXT_GRADIENT_MASK
name|GIMP_CONTEXT_GRADIENT_MASK
init|=
literal|1
operator|<<
literal|13
block|,
DECL|enumerator|GIMP_CONTEXT_PALETTE_MASK
name|GIMP_CONTEXT_PALETTE_MASK
init|=
literal|1
operator|<<
literal|14
block|,
DECL|enumerator|GIMP_CONTEXT_FONT_MASK
name|GIMP_CONTEXT_FONT_MASK
init|=
literal|1
operator|<<
literal|15
block|,
DECL|enumerator|GIMP_CONTEXT_BUFFER_MASK
name|GIMP_CONTEXT_BUFFER_MASK
init|=
literal|1
operator|<<
literal|16
block|,
DECL|enumerator|GIMP_CONTEXT_IMAGEFILE_MASK
name|GIMP_CONTEXT_IMAGEFILE_MASK
init|=
literal|1
operator|<<
literal|17
block|,
DECL|enumerator|GIMP_CONTEXT_TEMPLATE_MASK
name|GIMP_CONTEXT_TEMPLATE_MASK
init|=
literal|1
operator|<<
literal|18
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
name|GIMP_CONTEXT_DYNAMICS_MASK
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
name|GIMP_CONTEXT_PAINT_INFO_MASK
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
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2c88fb8e2403
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
DECL|enum|__anon2c88fb8e2503
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

