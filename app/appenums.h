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
comment|/* Fill types */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon296e9e220103
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
DECL|enum|__anon296e9e220203
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
DECL|enum|__anon296e9e220303
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
DECL|enum|__anon296e9e220403
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
DECL|enum|__anon296e9e220503
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
comment|/*< chop=ADD_>*/
DECL|enum|__anon296e9e220603
block|{
DECL|enumerator|ADD_WHITE_MASK
name|ADD_WHITE_MASK
block|,
DECL|enumerator|ADD_BLACK_MASK
name|ADD_BLACK_MASK
block|,
DECL|enumerator|ADD_ALPHA_MASK
name|ADD_ALPHA_MASK
block|,
DECL|enumerator|ADD_SELECTION_MASK
name|ADD_SELECTION_MASK
block|,
DECL|enumerator|ADD_INV_SELECTION_MASK
name|ADD_INV_SELECTION_MASK
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
DECL|enum|__anon296e9e220703
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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon296e9e220803
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
DECL|enum|__anon296e9e220903
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
DECL|enum|__anon296e9e220a03
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

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon296e9e220b03
block|{
DECL|enumerator|GIMP_ZOOM_IN
name|GIMP_ZOOM_IN
block|,
DECL|enumerator|GIMP_ZOOM_OUT
name|GIMP_ZOOM_OUT
DECL|typedef|GimpZoomType
block|}
name|GimpZoomType
typedef|;
end_typedef

begin_comment
comment|/*  Procedural database types  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon296e9e220c03
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
DECL|enum|__anon296e9e220d03
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
DECL|enum|__anon296e9e220e03
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
DECL|enum|__anon296e9e220f03
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
DECL|enum|__anon296e9e221003
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
comment|/*  Plug-In run modes  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon296e9e221103
block|{
DECL|enumerator|RUN_INTERACTIVE
name|RUN_INTERACTIVE
init|=
literal|0
block|,
DECL|enumerator|RUN_NONINTERACTIVE
name|RUN_NONINTERACTIVE
init|=
literal|1
block|,
DECL|enumerator|RUN_WITH_LAST_VALS
name|RUN_WITH_LAST_VALS
init|=
literal|2
DECL|typedef|RunModeType
block|}
name|RunModeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon296e9e221203
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
DECL|enum|__anon296e9e221303
block|{
DECL|enumerator|GIMP_HISTOGRAM_VALUE
name|GIMP_HISTOGRAM_VALUE
init|=
literal|0
block|,
DECL|enumerator|GIMP_HISTOGRAM_RED
name|GIMP_HISTOGRAM_RED
init|=
literal|1
block|,
DECL|enumerator|GIMP_HISTOGRAM_GREEN
name|GIMP_HISTOGRAM_GREEN
init|=
literal|2
block|,
DECL|enumerator|GIMP_HISTOGRAM_BLUE
name|GIMP_HISTOGRAM_BLUE
init|=
literal|3
block|,
DECL|enumerator|GIMP_HISTOGRAM_ALPHA
name|GIMP_HISTOGRAM_ALPHA
init|=
literal|4
DECL|typedef|GimpHistogramChannel
block|}
name|GimpHistogramChannel
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon296e9e221403
block|{
DECL|enumerator|GIMP_TOOL_CURSOR_NONE
name|GIMP_TOOL_CURSOR_NONE
block|,
DECL|enumerator|GIMP_RECT_SELECT_TOOL_CURSOR
name|GIMP_RECT_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ELLIPSE_SELECT_TOOL_CURSOR
name|GIMP_ELLIPSE_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FREE_SELECT_TOOL_CURSOR
name|GIMP_FREE_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FUZZY_SELECT_TOOL_CURSOR
name|GIMP_FUZZY_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BEZIER_SELECT_TOOL_CURSOR
name|GIMP_BEZIER_SELECT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SCISSORS_TOOL_CURSOR
name|GIMP_SCISSORS_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_MOVE_TOOL_CURSOR
name|GIMP_MOVE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ZOOM_TOOL_CURSOR
name|GIMP_ZOOM_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_CROP_TOOL_CURSOR
name|GIMP_CROP_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_RESIZE_TOOL_CURSOR
name|GIMP_RESIZE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ROTATE_TOOL_CURSOR
name|GIMP_ROTATE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SHEAR_TOOL_CURSOR
name|GIMP_SHEAR_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PERSPECTIVE_TOOL_CURSOR
name|GIMP_PERSPECTIVE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
name|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_FLIP_VERTICAL_TOOL_CURSOR
name|GIMP_FLIP_VERTICAL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_TEXT_TOOL_CURSOR
name|GIMP_TEXT_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_COLOR_PICKER_TOOL_CURSOR
name|GIMP_COLOR_PICKER_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BUCKET_FILL_TOOL_CURSOR
name|GIMP_BUCKET_FILL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BLEND_TOOL_CURSOR
name|GIMP_BLEND_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PENCIL_TOOL_CURSOR
name|GIMP_PENCIL_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_PAINTBRUSH_TOOL_CURSOR
name|GIMP_PAINTBRUSH_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_AIRBRUSH_TOOL_CURSOR
name|GIMP_AIRBRUSH_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_INK_TOOL_CURSOR
name|GIMP_INK_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_CLONE_TOOL_CURSOR
name|GIMP_CLONE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_ERASER_TOOL_CURSOR
name|GIMP_ERASER_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_SMUDGE_TOOL_CURSOR
name|GIMP_SMUDGE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BLUR_TOOL_CURSOR
name|GIMP_BLUR_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_DODGE_TOOL_CURSOR
name|GIMP_DODGE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_BURN_TOOL_CURSOR
name|GIMP_BURN_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_MEASURE_TOOL_CURSOR
name|GIMP_MEASURE_TOOL_CURSOR
block|,
DECL|enumerator|GIMP_LAST_STOCK_TOOL_CURSOR_ENTRY
name|GIMP_LAST_STOCK_TOOL_CURSOR_ENTRY
DECL|typedef|GimpToolCursorType
block|}
name|GimpToolCursorType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon296e9e221503
block|{
DECL|enumerator|GIMP_CURSOR_MODIFIER_NONE
name|GIMP_CURSOR_MODIFIER_NONE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_PLUS
name|GIMP_CURSOR_MODIFIER_PLUS
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_MINUS
name|GIMP_CURSOR_MODIFIER_MINUS
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_INTERSECT
name|GIMP_CURSOR_MODIFIER_INTERSECT
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_MOVE
name|GIMP_CURSOR_MODIFIER_MOVE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_RESIZE
name|GIMP_CURSOR_MODIFIER_RESIZE
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_CONTROL
name|GIMP_CURSOR_MODIFIER_CONTROL
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_ANCHOR
name|GIMP_CURSOR_MODIFIER_ANCHOR
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_FOREGROUND
name|GIMP_CURSOR_MODIFIER_FOREGROUND
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_BACKGROUND
name|GIMP_CURSOR_MODIFIER_BACKGROUND
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_PATTERN
name|GIMP_CURSOR_MODIFIER_PATTERN
block|,
DECL|enumerator|GIMP_CURSOR_MODIFIER_HAND
name|GIMP_CURSOR_MODIFIER_HAND
block|,
DECL|enumerator|GIMP_LAST_CURSOR_MODIFIER_ENTRY
name|GIMP_LAST_CURSOR_MODIFIER_ENTRY
DECL|typedef|GimpCursorModifier
block|}
name|GimpCursorModifier
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

