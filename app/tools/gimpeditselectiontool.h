begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EDIT_SELECTION_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EDIT_SELECTION_TOOL_H__
define|#
directive|define
name|__GIMP_EDIT_SELECTION_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_EDIT_SELECTION_TOOL
define|#
directive|define
name|GIMP_TYPE_EDIT_SELECTION_TOOL
value|(gimp_edit_selection_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_EDIT_SELECTION_TOOL (obj)
define|#
directive|define
name|GIMP_EDIT_SELECTION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_EDIT_SELECTION_TOOL, GimpEditSelectionTool))
end_define

begin_define
DECL|macro|GIMP_EDIT_SELECTION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_EDIT_SELECTION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_EDIT_SELECTION_TOOL, GimpEditSelectionToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_EDIT_SELECTION_TOOL (obj)
define|#
directive|define
name|GIMP_IS_EDIT_SELECTION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_EDIT_SELECTION_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_EDIT_SELECTION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_EDIT_SELECTION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_EDIT_SELECTION_TOOL))
end_define

begin_decl_stmt
name|GType
name|gimp_edit_selection_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_edit_selection_tool_start
parameter_list|(
name|GimpTool
modifier|*
name|parent_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpTranslateMode
name|edit_mode
parameter_list|,
name|gboolean
name|propagate_release
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_edit_selection_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_edit_selection_tool_translate
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpTransformType
name|translate_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GtkWidget
modifier|*
name|type_box
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_EDIT_SELECTION_TOOL_H__  */
end_comment

end_unit

