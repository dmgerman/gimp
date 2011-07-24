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

begin_define
DECL|macro|TRANS_INFO_SIZE
define|#
directive|define
name|TRANS_INFO_SIZE
value|8
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a3d4d920103
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
comment|/*  current x coord                   */
DECL|member|cury
name|gdouble
name|cury
decl_stmt|;
comment|/*  current y coord                   */
DECL|member|lastx
name|gdouble
name|lastx
decl_stmt|;
comment|/*  last x coord                      */
DECL|member|lasty
name|gdouble
name|lasty
decl_stmt|;
comment|/*  last y coord                      */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate        */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords           */
DECL|member|cx
DECL|member|cy
name|gdouble
name|cx
decl_stmt|,
name|cy
decl_stmt|;
comment|/*  center point (for rotation)       */
DECL|member|aspect
name|gdouble
name|aspect
decl_stmt|;
comment|/*  original aspect ratio             */
DECL|member|tx1
DECL|member|ty1
name|gdouble
name|tx1
decl_stmt|,
name|ty1
decl_stmt|;
comment|/*  transformed handle coords         */
DECL|member|tx2
DECL|member|ty2
name|gdouble
name|tx2
decl_stmt|,
name|ty2
decl_stmt|;
DECL|member|tx3
DECL|member|ty3
name|gdouble
name|tx3
decl_stmt|,
name|ty3
decl_stmt|;
DECL|member|tx4
DECL|member|ty4
name|gdouble
name|tx4
decl_stmt|,
name|ty4
decl_stmt|;
DECL|member|tcx
DECL|member|tcy
name|gdouble
name|tcx
decl_stmt|,
name|tcy
decl_stmt|;
DECL|member|transform
name|GimpMatrix3
name|transform
decl_stmt|;
comment|/*  transformation matrix             */
DECL|member|trans_info
name|TransInfo
name|trans_info
decl_stmt|;
comment|/*  transformation info               */
DECL|member|old_trans_info
name|TransInfo
name|old_trans_info
decl_stmt|;
comment|/*  for resetting everything          */
DECL|member|prev_trans_info
name|TransInfo
name|prev_trans_info
decl_stmt|;
comment|/*  for cancelling a drag operation   */
DECL|member|function
name|TransformAction
name|function
decl_stmt|;
comment|/*  current tool activity             */
DECL|member|use_grid
name|gboolean
name|use_grid
decl_stmt|;
comment|/*  does the tool use the grid        */
DECL|member|use_handles
name|gboolean
name|use_handles
decl_stmt|;
comment|/*  uses the corner handles           */
DECL|member|use_center
name|gboolean
name|use_center
decl_stmt|;
comment|/*  uses the center handle            */
DECL|member|use_mid_handles
name|gboolean
name|use_mid_handles
decl_stmt|;
comment|/*  use handles at midpoints of edges */
DECL|member|handles
name|GimpCanvasItem
modifier|*
name|handles
index|[
name|TRANSFORM_HANDLE_CENTER
operator|+
literal|1
index|]
decl_stmt|;
DECL|member|undo_desc
specifier|const
name|gchar
modifier|*
name|undo_desc
decl_stmt|;
DECL|member|progress_text
specifier|const
name|gchar
modifier|*
name|progress_text
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
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
parameter_list|)
function_decl|;
DECL|member|transform
name|TileManager
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
name|TileManager
modifier|*
name|orig_tiles
parameter_list|,
name|gint
name|orig_offset_x
parameter_list|,
name|gint
name|orig_offset_y
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

