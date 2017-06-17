begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_TOOL_H__
define|#
directive|define
name|__GIMP_TRANSFORM_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c731e010103
block|{
DECL|enumerator|TRANSFORM_CREATING
name|TRANSFORM_CREATING
block|,
DECL|enumerator|TRANSFORM_HANDLE_NONE
name|TRANSFORM_HANDLE_NONE
block|,
DECL|enumerator|TRANSFORM_HANDLE_NW_P
name|TRANSFORM_HANDLE_NW_P
block|,
comment|/* perspective handles */
DECL|enumerator|TRANSFORM_HANDLE_NE_P
name|TRANSFORM_HANDLE_NE_P
block|,
DECL|enumerator|TRANSFORM_HANDLE_SW_P
name|TRANSFORM_HANDLE_SW_P
block|,
DECL|enumerator|TRANSFORM_HANDLE_SE_P
name|TRANSFORM_HANDLE_SE_P
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
block|,
comment|/* for moving */
DECL|enumerator|TRANSFORM_HANDLE_PIVOT
name|TRANSFORM_HANDLE_PIVOT
block|,
comment|/* pivot for rotation and scaling */
DECL|enumerator|TRANSFORM_HANDLE_N_S
name|TRANSFORM_HANDLE_N_S
block|,
comment|/* shearing handles */
DECL|enumerator|TRANSFORM_HANDLE_S_S
name|TRANSFORM_HANDLE_S_S
block|,
DECL|enumerator|TRANSFORM_HANDLE_E_S
name|TRANSFORM_HANDLE_E_S
block|,
DECL|enumerator|TRANSFORM_HANDLE_W_S
name|TRANSFORM_HANDLE_W_S
block|,
DECL|enumerator|TRANSFORM_HANDLE_ROTATION
name|TRANSFORM_HANDLE_ROTATION
block|,
comment|/* rotation handle */
DECL|enumerator|TRANSFORM_HANDLE_NUM
name|TRANSFORM_HANDLE_NUM
comment|/* keep this last so *handles[] is the right size */
DECL|typedef|TransformAction
block|}
name|TransformAction
typedef|;
end_typedef

begin_comment
comment|/* This is not the number of items in the enum above, but the max size  * of the enums at the top of each transformation tool, stored in  * trans_info and related  */
end_comment

begin_define
DECL|macro|TRANS_INFO_SIZE
define|#
directive|define
name|TRANS_INFO_SIZE
value|17
end_define

begin_typedef
DECL|typedef|TransInfo
typedef|typedef
name|gdouble
name|TransInfo
index|[
name|TRANS_INFO_SIZE
index|]
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TRANSFORM_TOOL
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_TOOL
value|(gimp_transform_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformTool))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TRANSFORM_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TRANSFORM_TOOL))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TRANSFORM_TOOL, GimpTransformToolClass))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_TRANSFORM_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_TRANSFORM_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpTransformToolClass
typedef|typedef
name|struct
name|_GimpTransformToolClass
name|GimpTransformToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTransformTool
struct|struct
name|_GimpTransformTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|curx
name|gdouble
name|curx
decl_stmt|;
comment|/*  current x coord                    */
DECL|member|cury
name|gdouble
name|cury
decl_stmt|;
comment|/*  current y coord                    */
DECL|member|lastx
name|gdouble
name|lastx
decl_stmt|;
comment|/*  last x coord                       */
DECL|member|lasty
name|gdouble
name|lasty
decl_stmt|;
comment|/*  last y coord                       */
DECL|member|previousx
name|gdouble
name|previousx
decl_stmt|;
comment|/*  previous x coord                   */
DECL|member|previousy
name|gdouble
name|previousy
decl_stmt|;
comment|/*  previous y coord                   */
DECL|member|mousex
name|gdouble
name|mousex
decl_stmt|;
comment|/*  x coord where mouse was clicked    */
DECL|member|mousey
name|gdouble
name|mousey
decl_stmt|;
comment|/*  y coord where mouse was clicked    */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate         */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords            */
DECL|member|transform
name|GimpMatrix3
name|transform
decl_stmt|;
comment|/*  transformation matrix              */
DECL|member|trans_info
name|TransInfo
name|trans_info
decl_stmt|;
comment|/*  transformation info                */
DECL|member|old_trans_info
name|TransInfo
modifier|*
name|old_trans_info
decl_stmt|;
comment|/*  for resetting everything           */
DECL|member|prev_trans_info
name|TransInfo
modifier|*
name|prev_trans_info
decl_stmt|;
comment|/*  the current finished state         */
DECL|member|undo_list
name|GList
modifier|*
name|undo_list
decl_stmt|;
comment|/*  list of all states,                                           head is current == prev_trans_info,                                           tail is original == old_trans_info */
DECL|member|redo_list
name|GList
modifier|*
name|redo_list
decl_stmt|;
comment|/*  list of all undone states,                                           NULL when nothing undone */
DECL|member|hidden_item
name|GimpItem
modifier|*
name|hidden_item
decl_stmt|;
comment|/*  the item that was hidden during                                           the transform                      */
DECL|member|function
name|TransformAction
name|function
decl_stmt|;
comment|/*  current tool activity              */
DECL|member|use_grid
name|gboolean
name|use_grid
decl_stmt|;
comment|/*  does the tool use the grid         */
DECL|member|does_perspective
name|gboolean
name|does_perspective
decl_stmt|;
comment|/*  does the tool do non-affine                                        *  transformations                                        */
DECL|member|widget
name|GimpToolWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|grab_widget
name|GimpToolWidget
modifier|*
name|grab_widget
decl_stmt|;
DECL|member|preview
name|GimpCanvasItem
modifier|*
name|preview
decl_stmt|;
DECL|member|handles
name|GimpCanvasItem
modifier|*
name|handles
index|[
name|TRANSFORM_HANDLE_NUM
index|]
decl_stmt|;
DECL|member|progress_text
specifier|const
name|gchar
modifier|*
name|progress_text
decl_stmt|;
DECL|member|gui
name|GimpToolGui
modifier|*
name|gui
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTransformToolClass
struct|struct
name|_GimpTransformToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|dialog
name|void
function_decl|(
modifier|*
name|dialog
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|dialog_update
name|void
function_decl|(
modifier|*
name|dialog_update
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|prepare
name|void
function_decl|(
modifier|*
name|prepare
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|get_widget
name|GimpToolWidget
modifier|*
function_decl|(
modifier|*
name|get_widget
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|motion
name|void
function_decl|(
modifier|*
name|motion
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|recalc_matrix
name|void
function_decl|(
modifier|*
name|recalc_matrix
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
DECL|member|get_undo_desc
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_undo_desc
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|pick_function
name|TransformAction
function_decl|(
modifier|*
name|pick_function
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|cursor_update
name|void
function_decl|(
modifier|*
name|cursor_update
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpCursorType
modifier|*
name|cursor
parameter_list|,
name|GimpCursorModifier
modifier|*
name|modifier
parameter_list|)
function_decl|;
DECL|member|draw_gui
name|void
function_decl|(
modifier|*
name|draw_gui
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
DECL|member|transform
name|GeglBuffer
modifier|*
function_decl|(
modifier|*
name|transform
function_decl|)
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GeglBuffer
modifier|*
name|orig_buffer
parameter_list|,
name|gint
name|orig_offset_x
parameter_list|,
name|gint
name|orig_offset_y
parameter_list|,
name|GimpColorProfile
modifier|*
modifier|*
name|buffer_profile
parameter_list|,
name|gint
modifier|*
name|new_offset_x
parameter_list|,
name|gint
modifier|*
name|new_offset_y
parameter_list|)
function_decl|;
DECL|member|ok_button_label
specifier|const
name|gchar
modifier|*
name|ok_button_label
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_transform_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_transform_tool_recalc_matrix
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|,
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_transform_tool_push_internal_undo
parameter_list|(
name|GimpTransformTool
modifier|*
name|tr_tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TRANSFORM_TOOL_H__  */
end_comment

end_unit

