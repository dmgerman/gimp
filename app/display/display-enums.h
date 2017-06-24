begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DISPLAY_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__DISPLAY_ENUMS_H__
define|#
directive|define
name|__DISPLAY_ENUMS_H__
end_define

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
DECL|enum|__anon276ffad40103
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
DECL|enum|__anon276ffad40203
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
DECL|macro|GIMP_TYPE_CURSOR_PRECISION
define|#
directive|define
name|GIMP_TYPE_CURSOR_PRECISION
value|(gimp_cursor_precision_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cursor_precision_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40303
block|{
DECL|enumerator|GIMP_CURSOR_PRECISION_PIXEL_CENTER
name|GIMP_CURSOR_PRECISION_PIXEL_CENTER
block|,
DECL|enumerator|GIMP_CURSOR_PRECISION_PIXEL_BORDER
name|GIMP_CURSOR_PRECISION_PIXEL_BORDER
block|,
DECL|enumerator|GIMP_CURSOR_PRECISION_SUBPIXEL
name|GIMP_CURSOR_PRECISION_SUBPIXEL
DECL|typedef|GimpCursorPrecision
block|}
name|GimpCursorPrecision
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GUIDES_TYPE
define|#
directive|define
name|GIMP_TYPE_GUIDES_TYPE
value|(gimp_guides_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_guides_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40403
block|{
DECL|enumerator|GIMP_GUIDES_NONE
name|GIMP_GUIDES_NONE
block|,
comment|/*< desc="No guides">*/
DECL|enumerator|GIMP_GUIDES_CENTER_LINES
name|GIMP_GUIDES_CENTER_LINES
block|,
comment|/*< desc="Center lines">*/
DECL|enumerator|GIMP_GUIDES_THIRDS
name|GIMP_GUIDES_THIRDS
block|,
comment|/*< desc="Rule of thirds">*/
DECL|enumerator|GIMP_GUIDES_FIFTHS
name|GIMP_GUIDES_FIFTHS
block|,
comment|/*< desc="Rule of fifths">*/
DECL|enumerator|GIMP_GUIDES_GOLDEN
name|GIMP_GUIDES_GOLDEN
block|,
comment|/*< desc="Golden sections">*/
DECL|enumerator|GIMP_GUIDES_DIAGONALS
name|GIMP_GUIDES_DIAGONALS
block|,
comment|/*< desc="Diagonal lines">*/
DECL|enumerator|GIMP_GUIDES_N_LINES
name|GIMP_GUIDES_N_LINES
block|,
comment|/*< desc="Number of lines">*/
DECL|enumerator|GIMP_GUIDES_SPACING
name|GIMP_GUIDES_SPACING
comment|/*< desc="Line spacing">*/
DECL|typedef|GimpGuidesType
block|}
name|GimpGuidesType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HANDLE_TYPE
define|#
directive|define
name|GIMP_TYPE_HANDLE_TYPE
value|(gimp_handle_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_handle_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40503
block|{
DECL|enumerator|GIMP_HANDLE_SQUARE
name|GIMP_HANDLE_SQUARE
block|,
DECL|enumerator|GIMP_HANDLE_FILLED_SQUARE
name|GIMP_HANDLE_FILLED_SQUARE
block|,
DECL|enumerator|GIMP_HANDLE_CIRCLE
name|GIMP_HANDLE_CIRCLE
block|,
DECL|enumerator|GIMP_HANDLE_FILLED_CIRCLE
name|GIMP_HANDLE_FILLED_CIRCLE
block|,
DECL|enumerator|GIMP_HANDLE_DIAMOND
name|GIMP_HANDLE_DIAMOND
block|,
DECL|enumerator|GIMP_HANDLE_FILLED_DIAMOND
name|GIMP_HANDLE_FILLED_DIAMOND
block|,
DECL|enumerator|GIMP_HANDLE_CROSS
name|GIMP_HANDLE_CROSS
block|,
DECL|enumerator|GIMP_HANDLE_CROSSHAIR
name|GIMP_HANDLE_CROSSHAIR
DECL|typedef|GimpHandleType
block|}
name|GimpHandleType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_HANDLE_ANCHOR
define|#
directive|define
name|GIMP_TYPE_HANDLE_ANCHOR
value|(gimp_handle_anchor_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_handle_anchor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40603
block|{
DECL|enumerator|GIMP_HANDLE_ANCHOR_CENTER
name|GIMP_HANDLE_ANCHOR_CENTER
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_NORTH
name|GIMP_HANDLE_ANCHOR_NORTH
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_NORTH_WEST
name|GIMP_HANDLE_ANCHOR_NORTH_WEST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_NORTH_EAST
name|GIMP_HANDLE_ANCHOR_NORTH_EAST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_SOUTH
name|GIMP_HANDLE_ANCHOR_SOUTH
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_SOUTH_WEST
name|GIMP_HANDLE_ANCHOR_SOUTH_WEST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_SOUTH_EAST
name|GIMP_HANDLE_ANCHOR_SOUTH_EAST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_WEST
name|GIMP_HANDLE_ANCHOR_WEST
block|,
DECL|enumerator|GIMP_HANDLE_ANCHOR_EAST
name|GIMP_HANDLE_ANCHOR_EAST
DECL|typedef|GimpHandleAnchor
block|}
name|GimpHandleAnchor
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PATH_STYLE
define|#
directive|define
name|GIMP_TYPE_PATH_STYLE
value|(gimp_path_style_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_path_style_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40703
block|{
DECL|enumerator|GIMP_PATH_STYLE_DEFAULT
name|GIMP_PATH_STYLE_DEFAULT
block|,
DECL|enumerator|GIMP_PATH_STYLE_VECTORS
name|GIMP_PATH_STYLE_VECTORS
block|,
DECL|enumerator|GIMP_PATH_STYLE_OUTLINE
name|GIMP_PATH_STYLE_OUTLINE
DECL|typedef|GimpPathStyle
block|}
name|GimpPathStyle
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
DECL|enum|__anon276ffad40803
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
DECL|enum|__anon276ffad40903
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
DECL|enum|__anon276ffad40a03
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
DECL|macro|GIMP_TYPE_TRANSFORM_FUNCTION
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_FUNCTION
value|(gimp_transform_function_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_function_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40b03
block|{
DECL|enumerator|GIMP_TRANSFORM_FUNCTION_MOVE
name|GIMP_TRANSFORM_FUNCTION_MOVE
block|,
DECL|enumerator|GIMP_TRANSFORM_FUNCTION_SCALE
name|GIMP_TRANSFORM_FUNCTION_SCALE
block|,
DECL|enumerator|GIMP_TRANSFORM_FUNCTION_ROTATE
name|GIMP_TRANSFORM_FUNCTION_ROTATE
block|,
DECL|enumerator|GIMP_TRANSFORM_FUNCTION_SHEAR
name|GIMP_TRANSFORM_FUNCTION_SHEAR
block|,
DECL|enumerator|GIMP_TRANSFORM_FUNCTION_PERSPECTIVE
name|GIMP_TRANSFORM_FUNCTION_PERSPECTIVE
DECL|typedef|GimpTransformFunction
block|}
name|GimpTransformFunction
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_HANDLE_MODE
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_HANDLE_MODE
value|(gimp_transform_handle_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_transform_handle_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40c03
block|{
DECL|enumerator|GIMP_HANDLE_MODE_ADD_TRANSFORM
name|GIMP_HANDLE_MODE_ADD_TRANSFORM
block|,
comment|/*< desc="Add / Transform">*/
DECL|enumerator|GIMP_HANDLE_MODE_MOVE
name|GIMP_HANDLE_MODE_MOVE
block|,
comment|/*< desc="Move">*/
DECL|enumerator|GIMP_HANDLE_MODE_REMOVE
name|GIMP_HANDLE_MODE_REMOVE
comment|/*< desc="Remove">*/
DECL|typedef|GimpTransformHandleMode
block|}
name|GimpTransformHandleMode
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
DECL|enum|__anon276ffad40d03
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
DECL|macro|GIMP_TYPE_ZOOM_FOCUS
define|#
directive|define
name|GIMP_TYPE_ZOOM_FOCUS
value|(gimp_zoom_focus_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_zoom_focus_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon276ffad40e03
block|{
comment|/* Make a best guess */
DECL|enumerator|GIMP_ZOOM_FOCUS_BEST_GUESS
name|GIMP_ZOOM_FOCUS_BEST_GUESS
block|,
comment|/* Use the mouse cursor (if within canvas) */
DECL|enumerator|GIMP_ZOOM_FOCUS_POINTER
name|GIMP_ZOOM_FOCUS_POINTER
block|,
comment|/* Use the image center */
DECL|enumerator|GIMP_ZOOM_FOCUS_IMAGE_CENTER
name|GIMP_ZOOM_FOCUS_IMAGE_CENTER
block|,
comment|/* If the image is centered, retain the centering. Else use    * _BEST_GUESS    */
DECL|enumerator|GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS
name|GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS
DECL|typedef|GimpZoomFocus
block|}
name|GimpZoomFocus
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DISPLAY_ENUMS_H__ */
end_comment

end_unit

