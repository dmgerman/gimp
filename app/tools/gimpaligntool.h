begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ALIGN_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ALIGN_TOOL_H__
define|#
directive|define
name|__GIMP_ALIGN_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_comment
comment|/*  tool function/operation/state/mode  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon298dc8f80103
block|{
DECL|enumerator|ALIGN_TOOL_IDLE
name|ALIGN_TOOL_IDLE
block|,
DECL|enumerator|ALIGN_TOOL_PICK_LAYER
name|ALIGN_TOOL_PICK_LAYER
block|,
DECL|enumerator|ALIGN_TOOL_ADD_LAYER
name|ALIGN_TOOL_ADD_LAYER
block|,
DECL|enumerator|ALIGN_TOOL_PICK_GUIDE
name|ALIGN_TOOL_PICK_GUIDE
block|,
DECL|enumerator|ALIGN_TOOL_ADD_GUIDE
name|ALIGN_TOOL_ADD_GUIDE
block|,
DECL|enumerator|ALIGN_TOOL_PICK_PATH
name|ALIGN_TOOL_PICK_PATH
block|,
DECL|enumerator|ALIGN_TOOL_ADD_PATH
name|ALIGN_TOOL_ADD_PATH
block|,
DECL|enumerator|ALIGN_TOOL_DRAG_BOX
name|ALIGN_TOOL_DRAG_BOX
DECL|typedef|GimpAlignToolFunction
block|}
name|GimpAlignToolFunction
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ALIGN_TOOL
define|#
directive|define
name|GIMP_TYPE_ALIGN_TOOL
value|(gimp_align_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_ALIGN_TOOL (obj)
define|#
directive|define
name|GIMP_ALIGN_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ALIGN_TOOL, GimpAlignTool))
end_define

begin_define
DECL|macro|GIMP_ALIGN_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_ALIGN_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ALIGN_TOOL, GimpAlignToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_ALIGN_TOOL (obj)
define|#
directive|define
name|GIMP_IS_ALIGN_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ALIGN_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_ALIGN_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ALIGN_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ALIGN_TOOL))
end_define

begin_define
DECL|macro|GIMP_ALIGN_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ALIGN_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ALIGN_TOOL, GimpAlignToolClass))
end_define

begin_define
DECL|macro|GIMP_ALIGN_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_ALIGN_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_ALIGN_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpAlignTool
typedef|typedef
name|struct
name|_GimpAlignTool
name|GimpAlignTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpAlignToolClass
typedef|typedef
name|struct
name|_GimpAlignToolClass
name|GimpAlignToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpAlignTool
struct|struct
name|_GimpAlignTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|function
name|GimpAlignToolFunction
name|function
decl_stmt|;
DECL|member|selected_objects
name|GList
modifier|*
name|selected_objects
decl_stmt|;
DECL|member|align_type
name|GimpAlignmentType
name|align_type
decl_stmt|;
DECL|member|x0
DECL|member|y0
DECL|member|x1
DECL|member|y1
name|gint
name|x0
decl_stmt|,
name|y0
decl_stmt|,
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/* rubber-band rectangle */
DECL|member|set_reference
name|gboolean
name|set_reference
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpAlignToolClass
struct|struct
name|_GimpAlignToolClass
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
name|gimp_align_tool_register
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
name|gimp_align_tool_get_type
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
comment|/*  __GIMP_ALIGN_TOOL_H__  */
end_comment

end_unit

