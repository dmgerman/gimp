begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
DECL|macro|GIMP_TYPE_BUTTON_PRESS_TYPE
define|#
directive|define
name|GIMP_TYPE_BUTTON_PRESS_TYPE
value|(gimp_button_press_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_button_press_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2772aa770103
block|{
DECL|enumerator|GIMP_BUTTON_PRESS_NORMAL
name|GIMP_BUTTON_PRESS_NORMAL
block|,
DECL|enumerator|GIMP_BUTTON_PRESS_DOUBLE
name|GIMP_BUTTON_PRESS_DOUBLE
block|,
DECL|enumerator|GIMP_BUTTON_PRESS_TRIPLE
name|GIMP_BUTTON_PRESS_TRIPLE
DECL|typedef|GimpButtonPressType
block|}
name|GimpButtonPressType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_BUTTON_RELEASE_TYPE
define|#
directive|define
name|GIMP_TYPE_BUTTON_RELEASE_TYPE
value|(gimp_button_release_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_button_release_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2772aa770203
block|{
DECL|enumerator|GIMP_BUTTON_RELEASE_NORMAL
name|GIMP_BUTTON_RELEASE_NORMAL
block|,
DECL|enumerator|GIMP_BUTTON_RELEASE_CANCEL
name|GIMP_BUTTON_RELEASE_CANCEL
block|,
DECL|enumerator|GIMP_BUTTON_RELEASE_CLICK
name|GIMP_BUTTON_RELEASE_CLICK
block|,
DECL|enumerator|GIMP_BUTTON_RELEASE_NO_MOTION
name|GIMP_BUTTON_RELEASE_NO_MOTION
DECL|typedef|GimpButtonReleaseType
block|}
name|GimpButtonReleaseType
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
DECL|enum|__anon2772aa770303
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
DECL|enumerator|GIMP_RECTANGLE_GUIDE_FIFTHS
name|GIMP_RECTANGLE_GUIDE_FIFTHS
block|,
comment|/*< desc="Rule of fifths">*/
DECL|enumerator|GIMP_RECTANGLE_GUIDE_GOLDEN
name|GIMP_RECTANGLE_GUIDE_GOLDEN
block|,
comment|/*< desc="Golden sections">*/
DECL|enumerator|GIMP_RECTANGLE_GUIDE_DIAGONALS
name|GIMP_RECTANGLE_GUIDE_DIAGONALS
comment|/*< desc="Diagonal lines">*/
DECL|typedef|GimpRectangleGuide
block|}
name|GimpRectangleGuide
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_CONSTRAINT
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_CONSTRAINT
value|(gimp_rectangle_constraint_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_rectangle_constraint_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2772aa770403
block|{
DECL|enumerator|GIMP_RECTANGLE_CONSTRAIN_NONE
name|GIMP_RECTANGLE_CONSTRAIN_NONE
block|,
DECL|enumerator|GIMP_RECTANGLE_CONSTRAIN_IMAGE
name|GIMP_RECTANGLE_CONSTRAIN_IMAGE
block|,
DECL|enumerator|GIMP_RECTANGLE_CONSTRAIN_DRAWABLE
name|GIMP_RECTANGLE_CONSTRAIN_DRAWABLE
DECL|typedef|GimpRectangleConstraint
block|}
name|GimpRectangleConstraint
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_PRECISION
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_PRECISION
value|(gimp_rectangle_precision_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_rectangle_precision_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2772aa770503
block|{
DECL|enumerator|GIMP_RECTANGLE_PRECISION_INT
name|GIMP_RECTANGLE_PRECISION_INT
block|,
DECL|enumerator|GIMP_RECTANGLE_PRECISION_DOUBLE
name|GIMP_RECTANGLE_PRECISION_DOUBLE
block|, }
DECL|typedef|GimpRectanglePrecision
name|GimpRectanglePrecision
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_RECTANGLE_TOOL_FIXED_RULE
define|#
directive|define
name|GIMP_TYPE_RECTANGLE_TOOL_FIXED_RULE
value|(gimp_rectangle_tool_fixed_rule_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_rectangle_tool_fixed_rule_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2772aa770603
block|{
DECL|enumerator|GIMP_RECTANGLE_TOOL_FIXED_ASPECT
name|GIMP_RECTANGLE_TOOL_FIXED_ASPECT
block|,
comment|/*< desc="Aspect ratio">*/
DECL|enumerator|GIMP_RECTANGLE_TOOL_FIXED_WIDTH
name|GIMP_RECTANGLE_TOOL_FIXED_WIDTH
block|,
comment|/*< desc="Width">*/
DECL|enumerator|GIMP_RECTANGLE_TOOL_FIXED_HEIGHT
name|GIMP_RECTANGLE_TOOL_FIXED_HEIGHT
block|,
comment|/*< desc="Height">*/
DECL|enumerator|GIMP_RECTANGLE_TOOL_FIXED_SIZE
name|GIMP_RECTANGLE_TOOL_FIXED_SIZE
block|,
comment|/*< desc="Size">*/
DECL|typedef|GimpRectangleToolFixedRule
block|}
name|GimpRectangleToolFixedRule
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
DECL|enum|__anon2772aa770703
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
DECL|enum|__anon2772aa770803
block|{
DECL|enumerator|GIMP_TRANSFORM_TYPE_LAYER
name|GIMP_TRANSFORM_TYPE_LAYER
block|,
comment|/*< desc="Layer">*/
DECL|enumerator|GIMP_TRANSFORM_TYPE_SELECTION
name|GIMP_TRANSFORM_TYPE_SELECTION
block|,
comment|/*< desc="Selection">*/
DECL|enumerator|GIMP_TRANSFORM_TYPE_PATH
name|GIMP_TRANSFORM_TYPE_PATH
comment|/*< desc="Path">*/
DECL|typedef|GimpTransformType
block|}
name|GimpTransformType
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
DECL|enum|__anon2772aa770903
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
DECL|enum|__anon2772aa770a03
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
DECL|enum|__anon2772aa770b03
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
DECL|macro|GIMP_TYPE_TOOL_ACTION
define|#
directive|define
name|GIMP_TYPE_TOOL_ACTION
value|(gimp_tool_action_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_tool_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2772aa770c03
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
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2772aa770d03
block|{
DECL|enumerator|SELECTION_SELECT
name|SELECTION_SELECT
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
DECL|typedef|SelectFunction
block|}
name|SelectFunction
typedef|;
end_typedef

begin_comment
comment|/*  Modes of GimpEditSelectionTool  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2772aa770e03
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
DECL|enum|__anon2772aa770f03
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
DECL|enum|__anon2772aa771003
block|{
DECL|enumerator|TRANSFORM_CREATING
name|TRANSFORM_CREATING
block|,
DECL|enumerator|TRANSFORM_HANDLE_NONE
name|TRANSFORM_HANDLE_NONE
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
DECL|enumerator|TRANSFORM_HANDLE_N
name|TRANSFORM_HANDLE_N
block|,
comment|/* north      */
DECL|enumerator|TRANSFORM_HANDLE_S
name|TRANSFORM_HANDLE_S
block|,
comment|/* south      */
DECL|enumerator|TRANSFORM_HANDLE_E
name|TRANSFORM_HANDLE_E
block|,
comment|/* east       */
DECL|enumerator|TRANSFORM_HANDLE_W
name|TRANSFORM_HANDLE_W
block|,
comment|/* west       */
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

