begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SELECTION_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SELECTION_TOOL_H__
define|#
directive|define
name|__GIMP_SELECTION_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SELECTION_TOOL
define|#
directive|define
name|GIMP_TYPE_SELECTION_TOOL
value|(gimp_selection_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_SELECTION_TOOL (obj)
define|#
directive|define
name|GIMP_SELECTION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SELECTION_TOOL, GimpSelectionTool))
end_define

begin_define
DECL|macro|GIMP_SELECTION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_SELECTION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SELECTION_TOOL, GimpSelectionToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION_TOOL (obj)
define|#
directive|define
name|GIMP_IS_SELECTION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SELECTION_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SELECTION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SELECTION_TOOL))
end_define

begin_define
DECL|macro|GIMP_SELECTION_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SELECTION_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SELECTION_TOOL, GimpSelectionToolClass))
end_define

begin_define
DECL|macro|GIMP_SELECTION_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_SELECTION_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_SELECTION_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpSelectionTool
typedef|typedef
name|struct
name|_GimpSelectionTool
name|GimpSelectionTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSelectionToolClass
typedef|typedef
name|struct
name|_GimpSelectionToolClass
name|GimpSelectionToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSelectionTool
struct|struct
name|_GimpSelectionTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|function
name|SelectFunction
name|function
decl_stmt|;
comment|/*  selection function        */
DECL|member|saved_operation
name|GimpChannelOps
name|saved_operation
decl_stmt|;
comment|/*  saved tool options state  */
DECL|member|change_count
name|gint
name|change_count
decl_stmt|;
DECL|member|saved_show_selection
name|gboolean
name|saved_show_selection
decl_stmt|;
DECL|member|undo
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
DECL|member|redo
name|GimpUndo
modifier|*
name|redo
decl_stmt|;
DECL|member|idle_id
name|gint
name|idle_id
decl_stmt|;
DECL|member|allow_move
name|gboolean
name|allow_move
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSelectionToolClass
struct|struct
name|_GimpSelectionToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_selection_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  protected function  */
end_comment

begin_function_decl
name|gboolean
name|gimp_selection_tool_start_edit
parameter_list|(
name|GimpSelectionTool
modifier|*
name|sel_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_selection_tool_start_change
parameter_list|(
name|GimpSelectionTool
modifier|*
name|sel_tool
parameter_list|,
name|gboolean
name|create
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_selection_tool_end_change
parameter_list|(
name|GimpSelectionTool
modifier|*
name|sel_tool
parameter_list|,
name|gboolean
name|cancel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SELECTION_TOOL_H__ */
end_comment

end_unit

