begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_TOOL_H__
define|#
directive|define
name|__GIMP_OPERATION_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpfiltertool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_TOOL
define|#
directive|define
name|GIMP_TYPE_OPERATION_TOOL
value|(gimp_operation_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_TOOL (obj)
define|#
directive|define
name|GIMP_OPERATION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_TOOL, GimpOperationTool))
end_define

begin_define
DECL|macro|GIMP_OPERATION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_OPERATION_TOOL, GimpOperationToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_TOOL (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_OPERATION_TOOL))
end_define

begin_define
DECL|macro|GIMP_OPERATION_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_OPERATION_TOOL, GimpOperationToolClass))
end_define

begin_typedef
DECL|typedef|GimpOperationTool
typedef|typedef
name|struct
name|_GimpOperationTool
name|GimpOperationTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationToolClass
typedef|typedef
name|struct
name|_GimpOperationToolClass
name|GimpOperationToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationTool
struct|struct
name|_GimpOperationTool
block|{
DECL|member|parent_instance
name|GimpFilterTool
name|parent_instance
decl_stmt|;
DECL|member|operation
name|gchar
modifier|*
name|operation
decl_stmt|;
DECL|member|description
name|gchar
modifier|*
name|description
decl_stmt|;
DECL|member|aux_inputs
name|GList
modifier|*
name|aux_inputs
decl_stmt|;
comment|/* dialog */
DECL|member|options_box
name|GtkWidget
modifier|*
name|options_box
decl_stmt|;
DECL|member|options_gui_ref
name|GWeakRef
name|options_gui_ref
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationToolClass
struct|struct
name|_GimpOperationToolClass
block|{
DECL|member|parent_class
name|GimpFilterToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_operation_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_operation_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_operation_tool_set_operation
parameter_list|(
name|GimpOperationTool
modifier|*
name|op_tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|description
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_OPERATION_TOOL_H__  */
end_comment

end_unit

