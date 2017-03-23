begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__XCF_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__XCF_PRIVATE_H__
define|#
directive|define
name|__XCF_PRIVATE_H__
end_define

begin_define
DECL|macro|XCF_TILE_WIDTH
define|#
directive|define
name|XCF_TILE_WIDTH
value|64
end_define

begin_define
DECL|macro|XCF_TILE_HEIGHT
define|#
directive|define
name|XCF_TILE_HEIGHT
value|64
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28a182b10103
block|{
DECL|enumerator|PROP_END
name|PROP_END
init|=
literal|0
block|,
DECL|enumerator|PROP_COLORMAP
name|PROP_COLORMAP
init|=
literal|1
block|,
DECL|enumerator|PROP_ACTIVE_LAYER
name|PROP_ACTIVE_LAYER
init|=
literal|2
block|,
DECL|enumerator|PROP_ACTIVE_CHANNEL
name|PROP_ACTIVE_CHANNEL
init|=
literal|3
block|,
DECL|enumerator|PROP_SELECTION
name|PROP_SELECTION
init|=
literal|4
block|,
DECL|enumerator|PROP_FLOATING_SELECTION
name|PROP_FLOATING_SELECTION
init|=
literal|5
block|,
DECL|enumerator|PROP_OPACITY
name|PROP_OPACITY
init|=
literal|6
block|,
DECL|enumerator|PROP_MODE
name|PROP_MODE
init|=
literal|7
block|,
DECL|enumerator|PROP_VISIBLE
name|PROP_VISIBLE
init|=
literal|8
block|,
DECL|enumerator|PROP_LINKED
name|PROP_LINKED
init|=
literal|9
block|,
DECL|enumerator|PROP_LOCK_ALPHA
name|PROP_LOCK_ALPHA
init|=
literal|10
block|,
DECL|enumerator|PROP_APPLY_MASK
name|PROP_APPLY_MASK
init|=
literal|11
block|,
DECL|enumerator|PROP_EDIT_MASK
name|PROP_EDIT_MASK
init|=
literal|12
block|,
DECL|enumerator|PROP_SHOW_MASK
name|PROP_SHOW_MASK
init|=
literal|13
block|,
DECL|enumerator|PROP_SHOW_MASKED
name|PROP_SHOW_MASKED
init|=
literal|14
block|,
DECL|enumerator|PROP_OFFSETS
name|PROP_OFFSETS
init|=
literal|15
block|,
DECL|enumerator|PROP_COLOR
name|PROP_COLOR
init|=
literal|16
block|,
DECL|enumerator|PROP_COMPRESSION
name|PROP_COMPRESSION
init|=
literal|17
block|,
DECL|enumerator|PROP_GUIDES
name|PROP_GUIDES
init|=
literal|18
block|,
DECL|enumerator|PROP_RESOLUTION
name|PROP_RESOLUTION
init|=
literal|19
block|,
DECL|enumerator|PROP_TATTOO
name|PROP_TATTOO
init|=
literal|20
block|,
DECL|enumerator|PROP_PARASITES
name|PROP_PARASITES
init|=
literal|21
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
init|=
literal|22
block|,
DECL|enumerator|PROP_PATHS
name|PROP_PATHS
init|=
literal|23
block|,
DECL|enumerator|PROP_USER_UNIT
name|PROP_USER_UNIT
init|=
literal|24
block|,
DECL|enumerator|PROP_VECTORS
name|PROP_VECTORS
init|=
literal|25
block|,
DECL|enumerator|PROP_TEXT_LAYER_FLAGS
name|PROP_TEXT_LAYER_FLAGS
init|=
literal|26
block|,
DECL|enumerator|PROP_SAMPLE_POINTS
name|PROP_SAMPLE_POINTS
init|=
literal|27
block|,
DECL|enumerator|PROP_LOCK_CONTENT
name|PROP_LOCK_CONTENT
init|=
literal|28
block|,
DECL|enumerator|PROP_GROUP_ITEM
name|PROP_GROUP_ITEM
init|=
literal|29
block|,
DECL|enumerator|PROP_ITEM_PATH
name|PROP_ITEM_PATH
init|=
literal|30
block|,
DECL|enumerator|PROP_GROUP_ITEM_FLAGS
name|PROP_GROUP_ITEM_FLAGS
init|=
literal|31
block|,
DECL|enumerator|PROP_LOCK_POSITION
name|PROP_LOCK_POSITION
init|=
literal|32
block|,
DECL|enumerator|PROP_FLOAT_OPACITY
name|PROP_FLOAT_OPACITY
init|=
literal|33
block|,
DECL|enumerator|PROP_COLOR_TAG
name|PROP_COLOR_TAG
init|=
literal|34
block|,
DECL|enumerator|PROP_COMPOSITE_MODE
name|PROP_COMPOSITE_MODE
init|=
literal|35
block|,
DECL|enumerator|PROP_COMPOSITE_SPACE
name|PROP_COMPOSITE_SPACE
init|=
literal|36
block|,
DECL|enumerator|PROP_BLEND_SPACE
name|PROP_BLEND_SPACE
init|=
literal|37
DECL|typedef|PropType
block|}
name|PropType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28a182b10203
block|{
DECL|enumerator|COMPRESS_NONE
name|COMPRESS_NONE
init|=
literal|0
block|,
DECL|enumerator|COMPRESS_RLE
name|COMPRESS_RLE
init|=
literal|1
block|,
DECL|enumerator|COMPRESS_ZLIB
name|COMPRESS_ZLIB
init|=
literal|2
block|,
comment|/* unused */
DECL|enumerator|COMPRESS_FRACTAL
name|COMPRESS_FRACTAL
init|=
literal|3
comment|/* unused */
DECL|typedef|XcfCompressionType
block|}
name|XcfCompressionType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28a182b10303
block|{
DECL|enumerator|XCF_ORIENTATION_HORIZONTAL
name|XCF_ORIENTATION_HORIZONTAL
init|=
literal|1
block|,
DECL|enumerator|XCF_ORIENTATION_VERTICAL
name|XCF_ORIENTATION_VERTICAL
init|=
literal|2
DECL|typedef|XcfOrientationType
block|}
name|XcfOrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28a182b10403
block|{
DECL|enumerator|XCF_STROKETYPE_STROKE
name|XCF_STROKETYPE_STROKE
init|=
literal|0
block|,
DECL|enumerator|XCF_STROKETYPE_BEZIER_STROKE
name|XCF_STROKETYPE_BEZIER_STROKE
init|=
literal|1
DECL|typedef|XcfStrokeType
block|}
name|XcfStrokeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28a182b10503
block|{
DECL|enumerator|XCF_GROUP_ITEM_EXPANDED
name|XCF_GROUP_ITEM_EXPANDED
init|=
literal|1
DECL|typedef|XcfGroupItemFlagsType
block|}
name|XcfGroupItemFlagsType
typedef|;
end_typedef

begin_typedef
DECL|typedef|XcfInfo
typedef|typedef
name|struct
name|_XcfInfo
name|XcfInfo
typedef|;
end_typedef

begin_struct
DECL|struct|_XcfInfo
struct|struct
name|_XcfInfo
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|progress
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
DECL|member|input
name|GInputStream
modifier|*
name|input
decl_stmt|;
DECL|member|output
name|GOutputStream
modifier|*
name|output
decl_stmt|;
DECL|member|seekable
name|GSeekable
modifier|*
name|seekable
decl_stmt|;
DECL|member|cp
name|goffset
name|cp
decl_stmt|;
DECL|member|bytes_per_offset
name|gint
name|bytes_per_offset
decl_stmt|;
DECL|member|file
name|GFile
modifier|*
name|file
decl_stmt|;
DECL|member|tattoo_state
name|GimpTattoo
name|tattoo_state
decl_stmt|;
DECL|member|active_layer
name|GimpLayer
modifier|*
name|active_layer
decl_stmt|;
DECL|member|active_channel
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
DECL|member|floating_sel_drawable
name|GimpDrawable
modifier|*
name|floating_sel_drawable
decl_stmt|;
DECL|member|floating_sel
name|GimpLayer
modifier|*
name|floating_sel
decl_stmt|;
DECL|member|floating_sel_offset
name|goffset
name|floating_sel_offset
decl_stmt|;
DECL|member|compression
name|XcfCompressionType
name|compression
decl_stmt|;
DECL|member|file_version
name|gint
name|file_version
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __XCF_PRIVATE_H__ */
end_comment

end_unit

