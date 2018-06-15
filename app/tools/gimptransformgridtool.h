begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_GRID_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_GRID_TOOL_H__
define|#
directive|define
name|__GIMP_TRANSFORM_GRID_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptransformtool.h"
end_include

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
DECL|macro|GIMP_TYPE_TRANSFORM_GRID_TOOL
define|#
directive|define
name|GIMP_TYPE_TRANSFORM_GRID_TOOL
value|(gimp_transform_grid_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_GRID_TOOL (obj)
define|#
directive|define
name|GIMP_TRANSFORM_GRID_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TRANSFORM_GRID_TOOL, GimpTransformGridTool))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_GRID_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TRANSFORM_GRID_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TRANSFORM_GRID_TOOL, GimpTransformGridToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_GRID_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TRANSFORM_GRID_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TRANSFORM_GRID_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_TRANSFORM_GRID_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TRANSFORM_GRID_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TRANSFORM_GRID_TOOL))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_GRID_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TRANSFORM_GRID_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TRANSFORM_GRID_TOOL, GimpTransformGridToolClass))
end_define

begin_define
DECL|macro|GIMP_TRANSFORM_GRID_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_TRANSFORM_GRID_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_TRANSFORM_GRID_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpTransformGridToolClass
typedef|typedef
name|struct
name|_GimpTransformGridToolClass
name|GimpTransformGridToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTransformGridTool
struct|struct
name|_GimpTransformGridTool
block|{
DECL|member|parent_instance
name|GimpTransformTool
name|parent_instance
decl_stmt|;
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
comment|/*  list of all states,                                            head is current == prev_trans_info,                                            tail is original == old_trans_info */
DECL|member|redo_list
name|GList
modifier|*
name|redo_list
decl_stmt|;
comment|/*  list of all undone states,                                            NULL when nothing undone */
DECL|member|hidden_item
name|GimpItem
modifier|*
name|hidden_item
decl_stmt|;
comment|/*  the item that was hidden during                                            the transform                      */
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
DECL|member|boundary_in
name|GimpCanvasItem
modifier|*
name|boundary_in
decl_stmt|;
DECL|member|boundary_out
name|GimpCanvasItem
modifier|*
name|boundary_out
decl_stmt|;
DECL|member|strokes
name|GPtrArray
modifier|*
name|strokes
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
DECL|struct|_GimpTransformGridToolClass
struct|struct
name|_GimpTransformGridToolClass
block|{
DECL|member|parent_class
name|GimpTransformToolClass
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
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
DECL|member|dialog_update
name|void
function_decl|(
modifier|*
name|dialog_update
function_decl|)
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
DECL|member|prepare
name|void
function_decl|(
modifier|*
name|prepare
function_decl|)
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
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
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
DECL|member|update_widget
name|void
function_decl|(
modifier|*
name|update_widget
function_decl|)
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
DECL|member|widget_changed
name|void
function_decl|(
modifier|*
name|widget_changed
function_decl|)
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
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
name|GimpTransformGridTool
modifier|*
name|tg_tool
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
name|gimp_transform_grid_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_transform_grid_tool_push_internal_undo
parameter_list|(
name|GimpTransformGridTool
modifier|*
name|tg_tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TRANSFORM_GRID_TOOL_H__  */
end_comment

end_unit

