begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOLS_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__TOOLS_ENUMS_H__
define|#
directive|define
name|__TOOLS_ENUMS_H__
end_define

begin_comment
comment|/*  * these enums are registered with the type system  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_COLOR_PICK_MODE
define|#
directive|define
name|GIMP_TYPE_COLOR_PICK_MODE
value|(gimp_color_pick_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_pick_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70103
block|{
DECL|enumerator|GIMP_COLOR_PICK_MODE_NONE
name|GIMP_COLOR_PICK_MODE_NONE
block|,
comment|/*< desc="Pick only">*/
DECL|enumerator|GIMP_COLOR_PICK_MODE_FOREGROUND
name|GIMP_COLOR_PICK_MODE_FOREGROUND
block|,
comment|/*< desc="Set foreground color">*/
DECL|enumerator|GIMP_COLOR_PICK_MODE_BACKGROUND
name|GIMP_COLOR_PICK_MODE_BACKGROUND
block|,
comment|/*< desc="Set background color">*/
DECL|enumerator|GIMP_COLOR_PICK_MODE_PALETTE
name|GIMP_COLOR_PICK_MODE_PALETTE
comment|/*< desc="Add to palette">*/
DECL|typedef|GimpColorPickMode
block|}
name|GimpColorPickMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_GUIDE
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_GUIDE
value|(gimp_rectangle_guide_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_rectangle_guide_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70203
block|{
DECL|enumerator|GIMP_RECTANGLE_GUIDE_NONE
name|GIMP_RECTANGLE_GUIDE_NONE
block|,
comment|/*< desc="No guides">*/
DECL|enumerator|GIMP_RECTANGLE_GUIDE_CENTER_LINES
name|GIMP_RECTANGLE_GUIDE_CENTER_LINES
block|,
comment|/*< desc="Center lines">*/
DECL|enumerator|GIMP_RECTANGLE_GUIDE_THIRDS
name|GIMP_RECTANGLE_GUIDE_THIRDS
block|,
comment|/*< desc="Rule of thirds">*/
DECL|enumerator|GIMP_RECTANGLE_GUIDE_GOLDEN
name|GIMP_RECTANGLE_GUIDE_GOLDEN
comment|/*< desc="Golden sections">*/
DECL|typedef|GimpRectangleGuide
block|}
name|GimpRectangleGuide
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CROP_MODE
define|#
directive|define
name|GIMP_TYPE_CROP_MODE
value|(gimp_crop_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_crop_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70303
block|{
DECL|enumerator|GIMP_CROP_MODE_CROP
name|GIMP_CROP_MODE_CROP
block|,
comment|/*< desc="Crop">*/
DECL|enumerator|GIMP_CROP_MODE_RESIZE
name|GIMP_CROP_MODE_RESIZE
comment|/*< desc="Resize">*/
DECL|typedef|GimpCropMode
block|}
name|GimpCropMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RECT_SELECT_MODE
define|#
directive|define
name|GIMP_TYPE_RECT_SELECT_MODE
value|(gimp_rect_select_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_rect_select_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70403
block|{
DECL|enumerator|GIMP_RECT_SELECT_MODE_FREE
name|GIMP_RECT_SELECT_MODE_FREE
block|,
comment|/*< desc="Free select">*/
DECL|enumerator|GIMP_RECT_SELECT_MODE_FIXED_SIZE
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
block|,
comment|/*< desc="Fixed size">*/
DECL|enumerator|GIMP_RECT_SELECT_MODE_FIXED_RATIO
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
comment|/*< desc="Fixed aspect ratio">*/
DECL|typedef|GimpRectSelectMode
block|}
name|GimpRectSelectMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_TYPE
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_TYPE
value|(gimp_transform_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70503
block|{
DECL|enumerator|GIMP_TRANSFORM_TYPE_LAYER
name|GIMP_TRANSFORM_TYPE_LAYER
block|,
comment|/*< desc="Transform layer">*/
DECL|enumerator|GIMP_TRANSFORM_TYPE_SELECTION
name|GIMP_TRANSFORM_TYPE_SELECTION
block|,
comment|/*< desc="Transform selection">*/
DECL|enumerator|GIMP_TRANSFORM_TYPE_PATH
name|GIMP_TRANSFORM_TYPE_PATH
comment|/*< desc="Transform path">*/
DECL|typedef|GimpTransformType
block|}
name|GimpTransformType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_VECTOR_MODE
define|#
directive|define
name|GIMP_TYPE_VECTOR_MODE
value|(gimp_vector_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_vector_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70603
block|{
DECL|enumerator|GIMP_VECTOR_MODE_DESIGN
name|GIMP_VECTOR_MODE_DESIGN
block|,
comment|/*< desc="Design">*/
DECL|enumerator|GIMP_VECTOR_MODE_EDIT
name|GIMP_VECTOR_MODE_EDIT
block|,
comment|/*< desc="Edit">*/
DECL|enumerator|GIMP_VECTOR_MODE_MOVE
name|GIMP_VECTOR_MODE_MOVE
comment|/*< desc="Move">*/
DECL|typedef|GimpVectorMode
block|}
name|GimpVectorMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_PREVIEW_TYPE
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_PREVIEW_TYPE
value|(gimp_transform_preview_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_preview_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70703
block|{
DECL|enumerator|GIMP_TRANSFORM_PREVIEW_TYPE_OUTLINE
name|GIMP_TRANSFORM_PREVIEW_TYPE_OUTLINE
block|,
comment|/*< desc="Outline">*/
DECL|enumerator|GIMP_TRANSFORM_PREVIEW_TYPE_GRID
name|GIMP_TRANSFORM_PREVIEW_TYPE_GRID
block|,
comment|/*< desc="Grid">*/
DECL|enumerator|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE
block|,
comment|/*< desc="Image">*/
DECL|enumerator|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID
comment|/*< desc="Image + Grid">*/
DECL|typedef|GimpTransformPreviewType
block|}
name|GimpTransformPreviewType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_GRID_TYPE
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_GRID_TYPE
value|(gimp_transform_grid_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_grid_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2934fbc70803
block|{
DECL|enumerator|GIMP_TRANSFORM_GRID_TYPE_N_LINES
name|GIMP_TRANSFORM_GRID_TYPE_N_LINES
block|,
comment|/*< desc="Number of grid lines">*/
DECL|enumerator|GIMP_TRANSFORM_GRID_TYPE_SPACING
name|GIMP_TRANSFORM_GRID_TYPE_SPACING
comment|/*< desc="Grid line spacing">*/
DECL|typedef|GimpTransformGridType
block|}
name|GimpTransformGridType
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2934fbc70903
block|{
DECL|enumerator|SELECTION_ADD
name|SELECTION_ADD
init|=
name|GIMP_CHANNEL_OP_ADD
block|,
DECL|enumerator|SELECTION_SUBTRACT
name|SELECTION_SUBTRACT
init|=
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
DECL|enumerator|SELECTION_REPLACE
name|SELECTION_REPLACE
init|=
name|GIMP_CHANNEL_OP_REPLACE
block|,
DECL|enumerator|SELECTION_INTERSECT
name|SELECTION_INTERSECT
init|=
name|GIMP_CHANNEL_OP_INTERSECT
block|,
DECL|enumerator|SELECTION_MOVE_MASK
name|SELECTION_MOVE_MASK
block|,
DECL|enumerator|SELECTION_MOVE
name|SELECTION_MOVE
block|,
DECL|enumerator|SELECTION_MOVE_COPY
name|SELECTION_MOVE_COPY
block|,
DECL|enumerator|SELECTION_ANCHOR
name|SELECTION_ANCHOR
DECL|typedef|SelectOps
block|}
name|SelectOps
typedef|;
end_typedef

begin_comment
comment|/*  Tool control actions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2934fbc70a03
block|{
DECL|enumerator|GIMP_TOOL_ACTION_PAUSE
name|GIMP_TOOL_ACTION_PAUSE
block|,
DECL|enumerator|GIMP_TOOL_ACTION_RESUME
name|GIMP_TOOL_ACTION_RESUME
block|,
DECL|enumerator|GIMP_TOOL_ACTION_HALT
name|GIMP_TOOL_ACTION_HALT
DECL|typedef|GimpToolAction
block|}
name|GimpToolAction
typedef|;
end_typedef

begin_comment
comment|/*  Modes of GimpEditSelectionTool  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2934fbc70b03
block|{
DECL|enumerator|GIMP_TRANSLATE_MODE_VECTORS
name|GIMP_TRANSLATE_MODE_VECTORS
block|,
DECL|enumerator|GIMP_TRANSLATE_MODE_CHANNEL
name|GIMP_TRANSLATE_MODE_CHANNEL
block|,
DECL|enumerator|GIMP_TRANSLATE_MODE_LAYER_MASK
name|GIMP_TRANSLATE_MODE_LAYER_MASK
block|,
DECL|enumerator|GIMP_TRANSLATE_MODE_MASK
name|GIMP_TRANSLATE_MODE_MASK
block|,
DECL|enumerator|GIMP_TRANSLATE_MODE_MASK_TO_LAYER
name|GIMP_TRANSLATE_MODE_MASK_TO_LAYER
block|,
DECL|enumerator|GIMP_TRANSLATE_MODE_MASK_COPY_TO_LAYER
name|GIMP_TRANSLATE_MODE_MASK_COPY_TO_LAYER
block|,
DECL|enumerator|GIMP_TRANSLATE_MODE_LAYER
name|GIMP_TRANSLATE_MODE_LAYER
block|,
DECL|enumerator|GIMP_TRANSLATE_MODE_FLOATING_SEL
name|GIMP_TRANSLATE_MODE_FLOATING_SEL
DECL|typedef|GimpTranslateMode
block|}
name|GimpTranslateMode
typedef|;
end_typedef

begin_comment
comment|/*  Motion event report modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2934fbc70c03
block|{
DECL|enumerator|GIMP_MOTION_MODE_EXACT
name|GIMP_MOTION_MODE_EXACT
block|,
DECL|enumerator|GIMP_MOTION_MODE_HINT
name|GIMP_MOTION_MODE_HINT
block|,
DECL|enumerator|GIMP_MOTION_MODE_COMPRESS
name|GIMP_MOTION_MODE_COMPRESS
DECL|typedef|GimpMotionMode
block|}
name|GimpMotionMode
typedef|;
end_typedef

begin_comment
comment|/*  Possible transform functions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2934fbc70d03
block|{
DECL|enumerator|TRANSFORM_CREATING
name|TRANSFORM_CREATING
block|,
DECL|enumerator|TRANSFORM_HANDLE_NW
name|TRANSFORM_HANDLE_NW
block|,
comment|/* north west */
DECL|enumerator|TRANSFORM_HANDLE_NE
name|TRANSFORM_HANDLE_NE
block|,
comment|/* north east */
DECL|enumerator|TRANSFORM_HANDLE_SW
name|TRANSFORM_HANDLE_SW
block|,
comment|/* south west */
DECL|enumerator|TRANSFORM_HANDLE_SE
name|TRANSFORM_HANDLE_SE
block|,
comment|/* south east */
DECL|enumerator|TRANSFORM_HANDLE_CENTER
name|TRANSFORM_HANDLE_CENTER
DECL|typedef|TransformAction
block|}
name|TransformAction
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TOOLS_ENUMS_H__ */
end_comment

end_unit

