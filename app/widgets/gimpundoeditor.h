begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UNDO_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNDO_EDITOR_H__
define|#
directive|define
name|__GIMP_UNDO_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpimageeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_UNDO_EDITOR
define|#
directive|define
name|GIMP_TYPE_UNDO_EDITOR
value|(gimp_undo_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_UNDO_EDITOR (obj)
define|#
directive|define
name|GIMP_UNDO_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UNDO_EDITOR, GimpUndoEditor))
end_define

begin_define
DECL|macro|GIMP_UNDO_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_UNDO_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNDO_EDITOR, GimpUndoEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_UNDO_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_UNDO_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UNDO_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_UNDO_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNDO_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNDO_EDITOR))
end_define

begin_define
DECL|macro|GIMP_UNDO_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_UNDO_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_UNDO_EDITOR, GimpUndoEditorClass))
end_define

begin_typedef
DECL|typedef|GimpUndoEditorClass
typedef|typedef
name|struct
name|_GimpUndoEditorClass
name|GimpUndoEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUndoEditor
struct|struct
name|_GimpUndoEditor
block|{
DECL|member|parent_instance
name|GimpImageEditor
name|parent_instance
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
DECL|member|base_item
name|GimpUndo
modifier|*
name|base_item
decl_stmt|;
DECL|member|undo_button
name|GtkWidget
modifier|*
name|undo_button
decl_stmt|;
DECL|member|redo_button
name|GtkWidget
modifier|*
name|redo_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUndoEditorClass
struct|struct
name|_GimpUndoEditorClass
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
name|gimp_undo_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_undo_editor_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UNDO_EDITOR_H__ */
end_comment

end_unit

