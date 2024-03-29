begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HANDLE_TRANSFORM_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HANDLE_TRANSFORM_TOOL_H__
define|#
directive|define
name|__GIMP_HANDLE_TRANSFORM_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpgenerictransformtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_HANDLE_TRANSFORM_TOOL
define|#
directive|define
name|GIMP_TYPE_HANDLE_TRANSFORM_TOOL
value|(gimp_handle_transform_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_HANDLE_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_HANDLE_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HANDLE_TRANSFORM_TOOL, GimpHandleTransformTool))
end_define

begin_define
DECL|macro|GIMP_HANDLE_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_HANDLE_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HANDLE_TRANSFORM_TOOL, GimpHandleTransformToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_HANDLE_TRANSFORM_TOOL (obj)
define|#
directive|define
name|GIMP_IS_HANDLE_TRANSFORM_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HANDLE_TRANSFORM_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_HANDLE_TRANSFORM_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HANDLE_TRANSFORM_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HANDLE_TRANSFORM_TOOL))
end_define

begin_define
DECL|macro|GIMP_HANDLE_TRANSFORM_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HANDLE_TRANSFORM_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HANDLE_TRANSFORM_TOOL, GimpHandleTransformToolClass))
end_define

begin_define
DECL|macro|GIMP_HANDLE_TRANSFORM_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_HANDLE_TRANSFORM_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_HANDLE_TRANSFORM_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpHandleTransformTool
typedef|typedef
name|struct
name|_GimpHandleTransformTool
name|GimpHandleTransformTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHandleTransformToolClass
typedef|typedef
name|struct
name|_GimpHandleTransformToolClass
name|GimpHandleTransformToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHandleTransformTool
struct|struct
name|_GimpHandleTransformTool
block|{
DECL|member|parent_instance
name|GimpGenericTransformTool
name|parent_instance
decl_stmt|;
DECL|member|saved_handle_mode
name|GimpTransformHandleMode
name|saved_handle_mode
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHandleTransformToolClass
struct|struct
name|_GimpHandleTransformToolClass
block|{
DECL|member|parent_class
name|GimpGenericTransformToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_handle_transform_tool_register
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
name|gimp_handle_transform_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_HANDLE_TRANSFORM_TOOL_H__  */
end_comment

end_unit

