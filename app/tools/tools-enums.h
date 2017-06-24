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
DECL|enum|__anon2bee027a0103
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
DECL|enum|__anon2bee027a0203
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
DECL|enum|__anon2bee027a0303
block|{
DECL|enumerator|GIMP_TOOL_ACTION_PAUSE
name|GIMP_TOOL_ACTION_PAUSE
block|,
DECL|enumerator|GIMP_TOOL_ACTION_RESUME
name|GIMP_TOOL_ACTION_RESUME
block|,
DECL|enumerator|GIMP_TOOL_ACTION_HALT
name|GIMP_TOOL_ACTION_HALT
block|,
DECL|enumerator|GIMP_TOOL_ACTION_COMMIT
name|GIMP_TOOL_ACTION_COMMIT
DECL|typedef|GimpToolAction
block|}
name|GimpToolAction
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_MATTING_DRAW_MODE
define|#
directive|define
name|GIMP_TYPE_MATTING_DRAW_MODE
value|(gimp_matting_draw_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_matting_draw_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bee027a0403
block|{
DECL|enumerator|GIMP_MATTING_DRAW_MODE_FOREGROUND
name|GIMP_MATTING_DRAW_MODE_FOREGROUND
block|,
comment|/*< desc="Draw foreground">*/
DECL|enumerator|GIMP_MATTING_DRAW_MODE_BACKGROUND
name|GIMP_MATTING_DRAW_MODE_BACKGROUND
block|,
comment|/*< desc="Draw background">*/
DECL|enumerator|GIMP_MATTING_DRAW_MODE_UNKNOWN
name|GIMP_MATTING_DRAW_MODE_UNKNOWN
block|,
comment|/*< desc="Draw unknown">*/
DECL|typedef|GimpMattingDrawMode
block|}
name|GimpMattingDrawMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_WARP_BEHAVIOR
define|#
directive|define
name|GIMP_TYPE_WARP_BEHAVIOR
value|(gimp_warp_behavior_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_warp_behavior_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bee027a0503
block|{
DECL|enumerator|GIMP_WARP_BEHAVIOR_MOVE
name|GIMP_WARP_BEHAVIOR_MOVE
block|,
comment|/*< desc="Move pixels">*/
DECL|enumerator|GEGL_WARP_BEHAVIOR_GROW
name|GEGL_WARP_BEHAVIOR_GROW
block|,
comment|/*< desc="Grow area">*/
DECL|enumerator|GEGL_WARP_BEHAVIOR_SHRINK
name|GEGL_WARP_BEHAVIOR_SHRINK
block|,
comment|/*< desc="Shrink area">*/
DECL|enumerator|GEGL_WARP_BEHAVIOR_SWIRL_CW
name|GEGL_WARP_BEHAVIOR_SWIRL_CW
block|,
comment|/*< desc="Swirl clockwise">*/
DECL|enumerator|GEGL_WARP_BEHAVIOR_SWIRL_CCW
name|GEGL_WARP_BEHAVIOR_SWIRL_CCW
block|,
comment|/*< desc="Swirl counter-clockwise">*/
DECL|enumerator|GEGL_WARP_BEHAVIOR_ERASE
name|GEGL_WARP_BEHAVIOR_ERASE
block|,
comment|/*< desc="Erase warping">*/
DECL|enumerator|GEGL_WARP_BEHAVIOR_SMOOTH
name|GEGL_WARP_BEHAVIOR_SMOOTH
comment|/*< desc="Smooth warping">*/
DECL|typedef|GimpWarpBehavior
block|}
name|GimpWarpBehavior
typedef|;
end_typedef

begin_comment
comment|/*  * non-registered enums; register them if needed  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2bee027a0603
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
DECL|enum|__anon2bee027a0703
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
DECL|enum|__anon2bee027a0803
block|{
DECL|enumerator|GIMP_MOTION_MODE_EXACT
name|GIMP_MOTION_MODE_EXACT
block|,
DECL|enumerator|GIMP_MOTION_MODE_COMPRESS
name|GIMP_MOTION_MODE_COMPRESS
DECL|typedef|GimpMotionMode
block|}
name|GimpMotionMode
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

