begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainereditor.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_EDITOR_H__
define|#
directive|define
name|__GIMP_CONTAINER_EDITOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_EDITOR
define|#
directive|define
name|GIMP_TYPE_CONTAINER_EDITOR
value|(gimp_container_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_EDITOR (obj)
define|#
directive|define
name|GIMP_CONTAINER_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_EDITOR, GimpContainerEditor))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_EDITOR, GimpContainerEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_EDITOR))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_EDITOR, GimpContainerEditorClass))
end_define

begin_typedef
DECL|typedef|GimpContainerEditorClass
typedef|typedef
name|struct
name|_GimpContainerEditorClass
name|GimpContainerEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerEditor
struct|struct
name|_GimpContainerEditor
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|view
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerEditorClass
struct|struct
name|_GimpContainerEditorClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|select_item
name|void
function_decl|(
modifier|*
name|select_item
function_decl|)
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|activate_item
name|void
function_decl|(
modifier|*
name|activate_item
function_decl|)
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|context_item
name|void
function_decl|(
modifier|*
name|context_item
function_decl|)
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkSelectionMode
name|gimp_container_editor_get_selection_mode
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_editor_set_selection_mode
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GtkSelectionMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|gboolean
name|gimp_container_editor_construct
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_path
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_EDITOR_H__  */
end_comment

end_unit

