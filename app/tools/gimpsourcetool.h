begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CLONE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CLONE_TOOL_H__
define|#
directive|define
name|__GIMP_CLONE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimppainttool.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28c1e8610103
block|{
DECL|enumerator|IMAGE_CLONE
name|IMAGE_CLONE
block|,
DECL|enumerator|PATTERN_CLONE
name|PATTERN_CLONE
DECL|typedef|CloneType
block|}
name|CloneType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CLONE_TOOL
define|#
directive|define
name|GIMP_TYPE_CLONE_TOOL
value|(gimp_clone_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_CLONE_TOOL (obj)
define|#
directive|define
name|GIMP_CLONE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CLONE_TOOL, GimpCloneTool))
end_define

begin_define
DECL|macro|GIMP_CLONE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_CLONE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CLONE_TOOL, GimpCloneToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_CLONE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CLONE_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CLONE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CLONE_TOOL))
end_define

begin_define
DECL|macro|GIMP_CLONE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CLONE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CLONE_TOOL, GimpCloneToolClass))
end_define

begin_typedef
DECL|typedef|GimpCloneTool
typedef|typedef
name|struct
name|_GimpCloneTool
name|GimpCloneTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCloneToolClass
typedef|typedef
name|struct
name|_GimpCloneToolClass
name|GimpCloneToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCloneTool
struct|struct
name|_GimpCloneTool
block|{
DECL|member|parent_instance
name|GimpPaintTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCloneToolClass
struct|struct
name|_GimpCloneToolClass
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
name|gimp_clone_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GType
name|gimp_clone_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* FIXME: Old style functions in need of a replacement. The only   * time these are used is to stroke paths or fill selections  * They should be somewhere else.  */
end_comment

begin_function_decl
name|gboolean
name|clone_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpDrawable
modifier|*
name|src_drawable
parameter_list|,
name|CloneType
name|clone_type
parameter_list|,
name|gdouble
name|src_x
parameter_list|,
name|gdouble
name|src_y
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

begin_function_decl
name|gboolean
name|clone_non_gui_default
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
comment|/*  __GIMP_CLONE_TOOL_H__  */
end_comment

end_unit

