begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooleditor.h  * Copyright (C) 2001-2009 Michael Natterer<mitch@gimp.org>  *                         Stephen Griffiths<scgmk5@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_EDITOR_H__
define|#
directive|define
name|__GIMP_TOOL_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_EDITOR
define|#
directive|define
name|GIMP_TYPE_TOOL_EDITOR
value|(gimp_tool_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_EDITOR (obj)
define|#
directive|define
name|GIMP_TOOL_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_EDITOR, GimpToolEditor))
end_define

begin_define
DECL|macro|GIMP_TOOL_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_EDITOR, GimpToolEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_TOOL_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_EDITOR))
end_define

begin_define
DECL|macro|GIMP_TOOL_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_EDITOR, GimpToolEditorClass))
end_define

begin_typedef
DECL|typedef|GimpToolEditorClass
typedef|typedef
name|struct
name|_GimpToolEditorClass
name|GimpToolEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolEditor
struct|struct
name|_GimpToolEditor
block|{
DECL|member|parent_instance
name|GimpContainerTreeView
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolEditorClass
struct|struct
name|_GimpToolEditorClass
block|{
DECL|member|parent_class
name|GimpContainerTreeViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_tool_editor_new
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GList
modifier|*
name|default_tool_order
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_editor_revert_changes
parameter_list|(
name|GimpToolEditor
modifier|*
name|tool_editor
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TOOL_EDITOR_H__  */
end_comment

end_unit

