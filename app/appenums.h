begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APPENUMS_H__
end_ifndef

begin_define
DECL|macro|__APPENUMS_H__
define|#
directive|define
name|__APPENUMS_H__
end_define

begin_comment
comment|/* Base image types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0103
block|{
DECL|enumerator|RGB
name|RGB
block|,
DECL|enumerator|GRAY
name|GRAY
block|,
DECL|enumerator|INDEXED
name|INDEXED
DECL|typedef|GimpImageBaseType
block|}
name|GimpImageBaseType
typedef|;
end_typedef

begin_comment
comment|/* Image types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0203
block|{
DECL|enumerator|RGB_GIMAGE
name|RGB_GIMAGE
block|,
comment|/*< nick=RGB_IMAGE>*/
DECL|enumerator|RGBA_GIMAGE
name|RGBA_GIMAGE
block|,
comment|/*< nick=RGBA_IMAGE>*/
DECL|enumerator|GRAY_GIMAGE
name|GRAY_GIMAGE
block|,
comment|/*< nick=GRAY_IMAGE>*/
DECL|enumerator|GRAYA_GIMAGE
name|GRAYA_GIMAGE
block|,
comment|/*< nick=GRAYA_IMAGE>*/
DECL|enumerator|INDEXED_GIMAGE
name|INDEXED_GIMAGE
block|,
comment|/*< nick=INDEXED_IMAGE>*/
DECL|enumerator|INDEXEDA_GIMAGE
name|INDEXEDA_GIMAGE
comment|/*< nick=INDEXEDA_IMAGE>*/
DECL|typedef|GimpImageType
block|}
name|GimpImageType
typedef|;
end_typedef

begin_comment
comment|/* Fill types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0303
block|{
DECL|enumerator|FOREGROUND_FILL
name|FOREGROUND_FILL
block|,
comment|/*< nick=FG_IMAGE_FILL>*/
DECL|enumerator|BACKGROUND_FILL
name|BACKGROUND_FILL
block|,
comment|/*< nick=BG_IMAGE_FILL>*/
DECL|enumerator|WHITE_FILL
name|WHITE_FILL
block|,
comment|/*< nick=WHITE_IMAGE_FILL>*/
DECL|enumerator|TRANSPARENT_FILL
name|TRANSPARENT_FILL
block|,
comment|/*< nick=TRANS_IMAGE_FILL>*/
DECL|enumerator|NO_FILL
name|NO_FILL
comment|/*< nick=NO_IMAGE_FILL>*/
DECL|typedef|GimpFillType
block|}
name|GimpFillType
typedef|;
end_typedef

begin_comment
comment|/* Layer modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0403
block|{
DECL|enumerator|NORMAL_MODE
name|NORMAL_MODE
block|,
DECL|enumerator|DISSOLVE_MODE
name|DISSOLVE_MODE
block|,
DECL|enumerator|BEHIND_MODE
name|BEHIND_MODE
block|,
DECL|enumerator|MULTIPLY_MODE
name|MULTIPLY_MODE
block|,
DECL|enumerator|SCREEN_MODE
name|SCREEN_MODE
block|,
DECL|enumerator|OVERLAY_MODE
name|OVERLAY_MODE
block|,
DECL|enumerator|DIFFERENCE_MODE
name|DIFFERENCE_MODE
block|,
DECL|enumerator|ADDITION_MODE
name|ADDITION_MODE
block|,
DECL|enumerator|SUBTRACT_MODE
name|SUBTRACT_MODE
block|,
DECL|enumerator|DARKEN_ONLY_MODE
name|DARKEN_ONLY_MODE
block|,
DECL|enumerator|LIGHTEN_ONLY_MODE
name|LIGHTEN_ONLY_MODE
block|,
DECL|enumerator|HUE_MODE
name|HUE_MODE
block|,
DECL|enumerator|SATURATION_MODE
name|SATURATION_MODE
block|,
DECL|enumerator|COLOR_MODE
name|COLOR_MODE
block|,
DECL|enumerator|VALUE_MODE
name|VALUE_MODE
block|,
DECL|enumerator|DIVIDE_MODE
name|DIVIDE_MODE
block|,
DECL|enumerator|DODGE_MODE
name|DODGE_MODE
block|,
DECL|enumerator|BURN_MODE
name|BURN_MODE
block|,
DECL|enumerator|HARDLIGHT_MODE
name|HARDLIGHT_MODE
block|,
DECL|enumerator|ERASE_MODE
name|ERASE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|REPLACE_MODE
name|REPLACE_MODE
block|,
comment|/*< skip>*/
DECL|enumerator|ANTI_ERASE_MODE
name|ANTI_ERASE_MODE
comment|/*< skip>*/
DECL|typedef|LayerModeEffects
block|}
name|LayerModeEffects
typedef|;
end_typedef

begin_comment
comment|/* Types of convolutions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0503
block|{
DECL|enumerator|NORMAL_CONVOL
name|NORMAL_CONVOL
block|,
comment|/*  Negative numbers truncated  */
DECL|enumerator|ABSOLUTE_CONVOL
name|ABSOLUTE_CONVOL
block|,
comment|/*  Absolute value              */
DECL|enumerator|NEGATIVE_CONVOL
name|NEGATIVE_CONVOL
comment|/*  add 127 to values           */
DECL|typedef|ConvolutionType
block|}
name|ConvolutionType
typedef|;
end_typedef

begin_comment
comment|/* Brush application types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0603
block|{
DECL|enumerator|HARD
name|HARD
block|,
comment|/* pencil */
DECL|enumerator|SOFT
name|SOFT
block|,
comment|/* paintbrush */
DECL|enumerator|PRESSURE
name|PRESSURE
comment|/* paintbrush with variable pressure */
DECL|typedef|BrushApplicationMode
block|}
name|BrushApplicationMode
typedef|;
end_typedef

begin_comment
comment|/* Paint application modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0703
block|{
DECL|enumerator|CONSTANT
name|CONSTANT
block|,
comment|/*< nick=CONTINUOUS>*/
comment|/* pencil, paintbrush, airbrush, clone */
DECL|enumerator|INCREMENTAL
name|INCREMENTAL
comment|/* convolve, smudge */
DECL|typedef|PaintApplicationMode
block|}
name|PaintApplicationMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0803
block|{
DECL|enumerator|APPLY
name|APPLY
block|,
DECL|enumerator|DISCARD
name|DISCARD
DECL|typedef|MaskApplyMode
block|}
name|MaskApplyMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=ADD_>*/
DECL|enum|__anon2b63d31e0903
block|{
DECL|enumerator|ADD_WHITE_MASK
name|ADD_WHITE_MASK
block|,
DECL|enumerator|ADD_BLACK_MASK
name|ADD_BLACK_MASK
block|,
DECL|enumerator|ADD_ALPHA_MASK
name|ADD_ALPHA_MASK
DECL|typedef|AddMaskType
block|}
name|AddMaskType
typedef|;
end_typedef

begin_comment
comment|/* gradient paint modes */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0a03
block|{
DECL|enumerator|ONCE_FORWARD
name|ONCE_FORWARD
block|,
comment|/* paint through once, then stop */
DECL|enumerator|ONCE_BACKWARDS
name|ONCE_BACKWARDS
block|,
comment|/* paint once, then stop, but run the gradient the other way */
DECL|enumerator|LOOP_SAWTOOTH
name|LOOP_SAWTOOTH
block|,
comment|/* keep painting, looping through the grad start->end,start->end /|/|/| */
DECL|enumerator|LOOP_TRIANGLE
name|LOOP_TRIANGLE
block|,
comment|/* keep paiting, looping though the grad start->end,end->start /\/\/\/  */
DECL|enumerator|ONCE_END_COLOR
name|ONCE_END_COLOR
comment|/* paint once, but keep painting with the end color */
DECL|typedef|GradientPaintMode
block|}
name|GradientPaintMode
typedef|;
end_typedef

begin_comment
comment|/* gradient paint modes */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0b03
block|{
DECL|enumerator|LINEAR_INTERPOLATION
name|LINEAR_INTERPOLATION
block|,
DECL|enumerator|CUBIC_INTERPOLATION
name|CUBIC_INTERPOLATION
block|,
DECL|enumerator|NEAREST_NEIGHBOR_INTERPOLATION
name|NEAREST_NEIGHBOR_INTERPOLATION
DECL|typedef|InterpolationType
block|}
name|InterpolationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e0c03
block|{
DECL|enumerator|ORIENTATION_UNKNOWN
name|ORIENTATION_UNKNOWN
block|,
DECL|enumerator|ORIENTATION_HORIZONTAL
name|ORIENTATION_HORIZONTAL
block|,
DECL|enumerator|ORIENTATION_VERTICAL
name|ORIENTATION_VERTICAL
DECL|typedef|InternalOrientationType
block|}
name|InternalOrientationType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0d03
block|{
DECL|enumerator|HORIZONTAL
name|HORIZONTAL
block|,
DECL|enumerator|VERTICAL
name|VERTICAL
block|,
DECL|enumerator|UNKNOWN
name|UNKNOWN
DECL|typedef|OrientationType
block|}
name|OrientationType
typedef|;
end_typedef

begin_comment
comment|/*  Procedural database types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0e03
block|{
DECL|enumerator|PDB_INT32
name|PDB_INT32
block|,
DECL|enumerator|PDB_INT16
name|PDB_INT16
block|,
DECL|enumerator|PDB_INT8
name|PDB_INT8
block|,
DECL|enumerator|PDB_FLOAT
name|PDB_FLOAT
block|,
DECL|enumerator|PDB_STRING
name|PDB_STRING
block|,
DECL|enumerator|PDB_INT32ARRAY
name|PDB_INT32ARRAY
block|,
DECL|enumerator|PDB_INT16ARRAY
name|PDB_INT16ARRAY
block|,
DECL|enumerator|PDB_INT8ARRAY
name|PDB_INT8ARRAY
block|,
DECL|enumerator|PDB_FLOATARRAY
name|PDB_FLOATARRAY
block|,
DECL|enumerator|PDB_STRINGARRAY
name|PDB_STRINGARRAY
block|,
DECL|enumerator|PDB_COLOR
name|PDB_COLOR
block|,
DECL|enumerator|PDB_REGION
name|PDB_REGION
block|,
DECL|enumerator|PDB_DISPLAY
name|PDB_DISPLAY
block|,
DECL|enumerator|PDB_IMAGE
name|PDB_IMAGE
block|,
DECL|enumerator|PDB_LAYER
name|PDB_LAYER
block|,
DECL|enumerator|PDB_CHANNEL
name|PDB_CHANNEL
block|,
DECL|enumerator|PDB_DRAWABLE
name|PDB_DRAWABLE
block|,
DECL|enumerator|PDB_SELECTION
name|PDB_SELECTION
block|,
DECL|enumerator|PDB_BOUNDARY
name|PDB_BOUNDARY
block|,
DECL|enumerator|PDB_PATH
name|PDB_PATH
block|,
DECL|enumerator|PDB_PARASITE
name|PDB_PARASITE
block|,
DECL|enumerator|PDB_STATUS
name|PDB_STATUS
block|,
DECL|enumerator|PDB_END
name|PDB_END
DECL|typedef|PDBArgType
block|}
name|PDBArgType
typedef|;
end_typedef

begin_comment
comment|/*  Error types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b63d31e0f03
block|{
DECL|enumerator|PDB_EXECUTION_ERROR
name|PDB_EXECUTION_ERROR
block|,
DECL|enumerator|PDB_CALLING_ERROR
name|PDB_CALLING_ERROR
block|,
DECL|enumerator|PDB_PASS_THROUGH
name|PDB_PASS_THROUGH
block|,
DECL|enumerator|PDB_SUCCESS
name|PDB_SUCCESS
block|,
DECL|enumerator|PDB_CANCEL
name|PDB_CANCEL
DECL|typedef|PDBStatusType
block|}
name|PDBStatusType
typedef|;
end_typedef

begin_comment
comment|/*  Procedure types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=PDB_>*/
DECL|enum|__anon2b63d31e1003
block|{
DECL|enumerator|PDB_INTERNAL
name|PDB_INTERNAL
block|,
DECL|enumerator|PDB_PLUGIN
name|PDB_PLUGIN
block|,
DECL|enumerator|PDB_EXTENSION
name|PDB_EXTENSION
block|,
DECL|enumerator|PDB_TEMPORARY
name|PDB_TEMPORARY
DECL|typedef|PDBProcType
block|}
name|PDBProcType
typedef|;
end_typedef

begin_comment
comment|/*  Selection Boolean operations  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=CHANNEL_OP_>*/
DECL|enum|__anon2b63d31e1103
block|{
DECL|enumerator|CHANNEL_OP_ADD
name|CHANNEL_OP_ADD
block|,
DECL|enumerator|CHANNEL_OP_SUB
name|CHANNEL_OP_SUB
block|,
DECL|enumerator|CHANNEL_OP_REPLACE
name|CHANNEL_OP_REPLACE
block|,
DECL|enumerator|CHANNEL_OP_INTERSECT
name|CHANNEL_OP_INTERSECT
DECL|typedef|ChannelOps
block|}
name|ChannelOps
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1203
block|{
DECL|enumerator|SELECTION_ADD
name|SELECTION_ADD
init|=
name|CHANNEL_OP_ADD
block|,
DECL|enumerator|SELECTION_SUB
name|SELECTION_SUB
init|=
name|CHANNEL_OP_SUB
block|,
DECL|enumerator|SELECTION_REPLACE
name|SELECTION_REPLACE
init|=
name|CHANNEL_OP_REPLACE
block|,
DECL|enumerator|SELECTION_INTERSECT
name|SELECTION_INTERSECT
init|=
name|CHANNEL_OP_INTERSECT
block|,
DECL|enumerator|SELECTION_MOVE_MASK
name|SELECTION_MOVE_MASK
block|,
DECL|enumerator|SELECTION_MOVE
name|SELECTION_MOVE
block|,
DECL|enumerator|SELECTION_ANCHOR
name|SELECTION_ANCHOR
DECL|typedef|SelectOps
block|}
name|SelectOps
typedef|;
end_typedef

begin_comment
comment|/*  The possible states for tools  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1303
block|{
DECL|enumerator|INACTIVE
name|INACTIVE
block|,
DECL|enumerator|ACTIVE
name|ACTIVE
block|,
DECL|enumerator|PAUSED
name|PAUSED
DECL|typedef|ToolState
block|}
name|ToolState
typedef|;
end_typedef

begin_comment
comment|/*  Tool control actions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1403
block|{
DECL|enumerator|PAUSE
name|PAUSE
block|,
DECL|enumerator|RESUME
name|RESUME
block|,
DECL|enumerator|HALT
name|HALT
block|,
DECL|enumerator|UPDATE_CURSOR
name|UPDATE_CURSOR
block|,
DECL|enumerator|DESTROY
name|DESTROY
block|,
DECL|enumerator|RECREATE
name|RECREATE
DECL|typedef|ToolAction
block|}
name|ToolAction
typedef|;
end_typedef

begin_comment
comment|/*  Tool types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1503
block|{
DECL|enumerator|TOOL_TYPE_NONE
name|TOOL_TYPE_NONE
init|=
operator|-
literal|1
block|,
DECL|enumerator|FIRST_TOOLBOX_TOOL
name|FIRST_TOOLBOX_TOOL
init|=
literal|0
block|,
DECL|enumerator|RECT_SELECT
name|RECT_SELECT
init|=
name|FIRST_TOOLBOX_TOOL
block|,
DECL|enumerator|ELLIPSE_SELECT
name|ELLIPSE_SELECT
block|,
DECL|enumerator|FREE_SELECT
name|FREE_SELECT
block|,
DECL|enumerator|FUZZY_SELECT
name|FUZZY_SELECT
block|,
DECL|enumerator|BEZIER_SELECT
name|BEZIER_SELECT
block|,
DECL|enumerator|ISCISSORS
name|ISCISSORS
block|,
DECL|enumerator|MOVE
name|MOVE
block|,
DECL|enumerator|MAGNIFY
name|MAGNIFY
block|,
DECL|enumerator|CROP
name|CROP
block|,
DECL|enumerator|ROTATE
name|ROTATE
block|,
DECL|enumerator|SCALE
name|SCALE
block|,
DECL|enumerator|SHEAR
name|SHEAR
block|,
DECL|enumerator|PERSPECTIVE
name|PERSPECTIVE
block|,
DECL|enumerator|FLIP
name|FLIP
block|,
DECL|enumerator|TEXT
name|TEXT
block|,
DECL|enumerator|COLOR_PICKER
name|COLOR_PICKER
block|,
DECL|enumerator|BUCKET_FILL
name|BUCKET_FILL
block|,
DECL|enumerator|BLEND
name|BLEND
block|,
DECL|enumerator|PENCIL
name|PENCIL
block|,
DECL|enumerator|PAINTBRUSH
name|PAINTBRUSH
block|,
DECL|enumerator|AIRBRUSH
name|AIRBRUSH
block|,
DECL|enumerator|INK
name|INK
block|,
DECL|enumerator|CLONE
name|CLONE
block|,
DECL|enumerator|ERASER
name|ERASER
block|,
DECL|enumerator|SMUDGE
name|SMUDGE
block|,
DECL|enumerator|CONVOLVE
name|CONVOLVE
block|,
DECL|enumerator|DODGEBURN
name|DODGEBURN
block|,
DECL|enumerator|MEASURE
name|MEASURE
block|,
DECL|enumerator|LAST_TOOLBOX_TOOL
name|LAST_TOOLBOX_TOOL
init|=
name|MEASURE
block|,
comment|/*  Non-toolbox tools  */
DECL|enumerator|BY_COLOR_SELECT
name|BY_COLOR_SELECT
block|,
DECL|enumerator|COLOR_BALANCE
name|COLOR_BALANCE
block|,
DECL|enumerator|BRIGHTNESS_CONTRAST
name|BRIGHTNESS_CONTRAST
block|,
DECL|enumerator|HUE_SATURATION
name|HUE_SATURATION
block|,
DECL|enumerator|POSTERIZE
name|POSTERIZE
block|,
DECL|enumerator|THRESHOLD
name|THRESHOLD
block|,
DECL|enumerator|CURVES
name|CURVES
block|,
DECL|enumerator|LEVELS
name|LEVELS
block|,
DECL|enumerator|HISTOGRAM
name|HISTOGRAM
DECL|typedef|ToolType
block|}
name|ToolType
typedef|;
end_typedef

begin_comment
comment|/* possible transform functions */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1603
block|{
DECL|enumerator|TRANSFORM_CREATING
name|TRANSFORM_CREATING
block|,
DECL|enumerator|TRANSFORM_HANDLE_1
name|TRANSFORM_HANDLE_1
block|,
DECL|enumerator|TRANSFORM_HANDLE_2
name|TRANSFORM_HANDLE_2
block|,
DECL|enumerator|TRANSFORM_HANDLE_3
name|TRANSFORM_HANDLE_3
block|,
DECL|enumerator|TRANSFORM_HANDLE_4
name|TRANSFORM_HANDLE_4
block|,
DECL|enumerator|TRANSFORM_HANDLE_CENTER
name|TRANSFORM_HANDLE_CENTER
DECL|typedef|TransformAction
block|}
name|TransformAction
typedef|;
end_typedef

begin_comment
comment|/* the different states that the transformation function can be called with */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1703
block|{
DECL|enumerator|TRANSFORM_INIT
name|TRANSFORM_INIT
block|,
DECL|enumerator|TRANSFORM_MOTION
name|TRANSFORM_MOTION
block|,
DECL|enumerator|TRANSFORM_RECALC
name|TRANSFORM_RECALC
block|,
DECL|enumerator|TRANSFORM_FINISH
name|TRANSFORM_FINISH
DECL|typedef|TransformState
block|}
name|TransformState
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1803
block|{
DECL|enumerator|CURSOR_MODE_TOOL_ICON
name|CURSOR_MODE_TOOL_ICON
block|,
DECL|enumerator|CURSOR_MODE_TOOL_CROSSHAIR
name|CURSOR_MODE_TOOL_CROSSHAIR
block|,
DECL|enumerator|CURSOR_MODE_CROSSHAIR
name|CURSOR_MODE_CROSSHAIR
DECL|typedef|CursorMode
block|}
name|CursorMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon2b63d31e1903
block|{
DECL|enumerator|CURSOR_MODIFIER_NONE
name|CURSOR_MODIFIER_NONE
block|,
DECL|enumerator|CURSOR_MODIFIER_PLUS
name|CURSOR_MODIFIER_PLUS
block|,
DECL|enumerator|CURSOR_MODIFIER_MINUS
name|CURSOR_MODIFIER_MINUS
block|,
DECL|enumerator|CURSOR_MODIFIER_INTERSECT
name|CURSOR_MODIFIER_INTERSECT
block|,
DECL|enumerator|CURSOR_MODIFIER_MOVE
name|CURSOR_MODIFIER_MOVE
block|,
DECL|enumerator|CURSOR_MODIFIER_RESIZE
name|CURSOR_MODIFIER_RESIZE
block|,
DECL|enumerator|CURSOR_MODIFIER_CONTROL
name|CURSOR_MODIFIER_CONTROL
block|,
DECL|enumerator|CURSOR_MODIFIER_ANCHOR
name|CURSOR_MODIFIER_ANCHOR
block|,
DECL|enumerator|CURSOR_MODIFIER_FOREGROUND
name|CURSOR_MODIFIER_FOREGROUND
block|,
DECL|enumerator|CURSOR_MODIFIER_BACKGROUND
name|CURSOR_MODIFIER_BACKGROUND
block|,
DECL|enumerator|CURSOR_MODIFIER_PATTERN
name|CURSOR_MODIFIER_PATTERN
block|,
DECL|enumerator|CURSOR_MODIFIER_HAND
name|CURSOR_MODIFIER_HAND
DECL|typedef|CursorModifier
block|}
name|CursorModifier
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APPENUMS_H__ */
end_comment

end_unit

