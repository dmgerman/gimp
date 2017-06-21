begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Vector tool  * Copyright (C) 2003 Simon Budig<simon@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTOR_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTOR_TOOL_H__
define|#
directive|define
name|__GIMP_VECTOR_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_VECTOR_TOOL
define|#
directive|define
name|GIMP_TYPE_VECTOR_TOOL
value|(gimp_vector_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_VECTOR_TOOL (obj)
define|#
directive|define
name|GIMP_VECTOR_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VECTOR_TOOL, GimpVectorTool))
end_define

begin_define
DECL|macro|GIMP_VECTOR_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_VECTOR_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VECTOR_TOOL, GimpVectorToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_VECTOR_TOOL (obj)
define|#
directive|define
name|GIMP_IS_VECTOR_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VECTOR_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_VECTOR_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VECTOR_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VECTOR_TOOL))
end_define

begin_define
DECL|macro|GIMP_VECTOR_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VECTOR_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VECTOR_TOOL, GimpVectorToolClass))
end_define

begin_define
DECL|macro|GIMP_VECTOR_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_VECTOR_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_VECTOR_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpVectorTool
typedef|typedef
name|struct
name|_GimpVectorTool
name|GimpVectorTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVectorToolClass
typedef|typedef
name|struct
name|_GimpVectorToolClass
name|GimpVectorToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpVectorTool
struct|struct
name|_GimpVectorTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|vectors
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
comment|/* the current Vector data           */
DECL|member|saved_mode
name|GimpVectorMode
name|saved_mode
decl_stmt|;
comment|/* used by modifier_key()            */
DECL|member|path
name|GimpToolWidget
modifier|*
name|path
decl_stmt|;
DECL|member|grab_widget
name|GimpToolWidget
modifier|*
name|grab_widget
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpVectorToolClass
struct|struct
name|_GimpVectorToolClass
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
name|gimp_vector_tool_register
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
name|gimp_vector_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_vector_tool_set_vectors
parameter_list|(
name|GimpVectorTool
modifier|*
name|vector_tool
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_VECTOR_TOOL_H__  */
end_comment

end_unit

