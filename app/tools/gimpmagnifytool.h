begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MAGNIFY_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MAGNIFY_TOOL_H__
define|#
directive|define
name|__GIMP_MAGNIFY_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_MAGNIFY_TOOL
define|#
directive|define
name|GIMP_TYPE_MAGNIFY_TOOL
value|(gimp_magnify_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_MAGNIFY_TOOL (obj)
define|#
directive|define
name|GIMP_MAGNIFY_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MAGNIFY_TOOL, GimpMagnifyTool))
end_define

begin_define
DECL|macro|GIMP_MAGNIFY_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_MAGNIFY_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MAGNIFY_TOOL, GimpMagnifyToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_MAGNIFY_TOOL (obj)
define|#
directive|define
name|GIMP_IS_MAGNIFY_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MAGNIFY_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_MAGNIFY_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MAGNIFY_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MAGNIFY_TOOL))
end_define

begin_define
DECL|macro|GIMP_MAGNIFY_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MAGNIFY_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MAGNIFY_TOOL, GimpMagnifyToolClass))
end_define

begin_define
DECL|macro|GIMP_MAGNIFY_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_MAGNIFY_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_MAGNIFY_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpMagnifyTool
typedef|typedef
name|struct
name|_GimpMagnifyTool
name|GimpMagnifyTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMagnifyToolClass
typedef|typedef
name|struct
name|_GimpMagnifyToolClass
name|GimpMagnifyToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMagnifyTool
struct|struct
name|_GimpMagnifyTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|x
DECL|member|y
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  upper left hand coordinate  */
DECL|member|w
DECL|member|h
name|gdouble
name|w
decl_stmt|,
name|h
decl_stmt|;
comment|/*  width and height            */
DECL|member|rectangle
name|GimpCanvasItem
modifier|*
name|rectangle
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMagnifyToolClass
struct|struct
name|_GimpMagnifyToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_magnify_tool_register
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
name|gimp_magnify_tool_get_type
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
comment|/*  __GIMP_MAGNIFY_TOOL_H__  */
end_comment

end_unit

