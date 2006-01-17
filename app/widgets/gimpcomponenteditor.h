begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcomponenteditor.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPONENT_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPONENT_EDITOR_H__
define|#
directive|define
name|__GIMP_COMPONENT_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpimageeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COMPONENT_EDITOR
define|#
directive|define
name|GIMP_TYPE_COMPONENT_EDITOR
value|(gimp_component_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_COMPONENT_EDITOR (obj)
define|#
directive|define
name|GIMP_COMPONENT_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COMPONENT_EDITOR, GimpComponentEditor))
end_define

begin_define
DECL|macro|GIMP_COMPONENT_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_COMPONENT_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COMPONENT_EDITOR, GimpComponentEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_COMPONENT_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_COMPONENT_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COMPONENT_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_COMPONENT_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COMPONENT_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COMPONENT_EDITOR))
end_define

begin_define
DECL|macro|GIMP_COMPONENT_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COMPONENT_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COMPONENT_EDITOR, GimpComponentEditorClass))
end_define

begin_typedef
DECL|typedef|GimpComponentEditorClass
typedef|typedef
name|struct
name|_GimpComponentEditorClass
name|GimpComponentEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpComponentEditor
struct|struct
name|_GimpComponentEditor
block|{
DECL|member|parent_instance
name|GimpImageEditor
name|parent_instance
decl_stmt|;
DECL|member|view_size
name|gint
name|view_size
decl_stmt|;
DECL|member|model
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
DECL|member|view
name|GtkTreeView
modifier|*
name|view
decl_stmt|;
DECL|member|selection
name|GtkTreeSelection
modifier|*
name|selection
decl_stmt|;
DECL|member|eye_column
name|GtkTreeViewColumn
modifier|*
name|eye_column
decl_stmt|;
DECL|member|eye_cell
name|GtkCellRenderer
modifier|*
name|eye_cell
decl_stmt|;
DECL|member|renderer_cell
name|GtkCellRenderer
modifier|*
name|renderer_cell
decl_stmt|;
DECL|member|clicked_component
name|GimpChannelType
name|clicked_component
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpComponentEditorClass
struct|struct
name|_GimpComponentEditorClass
block|{
DECL|member|parent_class
name|GimpImageEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_component_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_component_editor_new
parameter_list|(
name|gint
name|view_size
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_component_editor_set_view_size
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|view_size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COMPONENT_EDITOR_H__  */
end_comment

end_unit

