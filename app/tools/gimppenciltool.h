begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PENCIL_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PENCIL_TOOL_H__
define|#
directive|define
name|__GIMP_PENCIL_TOOL_H__
end_define

begin_comment
comment|/* FIXME: This whole tool should probably just be a paintbrush tool that  *        has an option of hard edge.  It'll give the "pencil tool" all the  *        flashy stuff the paintbrush tool has, and not duplicate code.  */
end_comment

begin_include
include|#
directive|include
file|"gimppainttool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PENCIL_TOOL
define|#
directive|define
name|GIMP_TYPE_PENCIL_TOOL
value|(gimp_pencil_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_PENCIL_TOOL (obj)
define|#
directive|define
name|GIMP_PENCIL_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PENCIL_TOOL, GimpPencilTool))
end_define

begin_define
DECL|macro|GIMP_IS_PENCIL_TOOL (obj)
define|#
directive|define
name|GIMP_IS_PENCIL_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PENCIL_TOOL))
end_define

begin_define
DECL|macro|GIMP_PENCIL_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_PENCIL_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PENCIL_TOOL, GimpPencilToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_PENCIL_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PENCIL_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PENCIL_TOOL))
end_define

begin_typedef
DECL|typedef|GimpPencilTool
typedef|typedef
name|struct
name|_GimpPencilTool
name|GimpPencilTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPencilToolClass
typedef|typedef
name|struct
name|_GimpPencilToolClass
name|GimpPencilToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPencilTool
struct|struct
name|_GimpPencilTool
block|{
DECL|member|parent_instance
name|GimpPaintTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPencilToolClass
struct|struct
name|_GimpPencilToolClass
block|{
DECL|member|parent_class
name|GimpPaintToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_pencil_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_pencil_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* FIXME: Get rid of this non_gui stuff someday.  Preferably make  *        everything use it interally for ease of macro recording.  */
end_comment

begin_function_decl
name|gboolean
name|pencil_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
name|gdouble
modifier|*
name|stroke_array
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PENCIL_TOOL_H__  */
end_comment

end_unit

