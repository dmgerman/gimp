begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SELECTION_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SELECTION_EDITOR_H__
define|#
directive|define
name|__GIMP_SELECTION_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_comment
comment|/* temp hack */
end_comment

begin_define
DECL|macro|GIMP_TYPE_SELECTION_EDITOR
define|#
directive|define
name|GIMP_TYPE_SELECTION_EDITOR
value|(gimp_selection_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_SELECTION_EDITOR (obj)
define|#
directive|define
name|GIMP_SELECTION_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SELECTION_EDITOR, GimpSelectionEditor))
end_define

begin_define
DECL|macro|GIMP_SELECTION_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_SELECTION_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SELECTION_EDITOR, GimpSelectionEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_SELECTION_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SELECTION_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SELECTION_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SELECTION_EDITOR))
end_define

begin_define
DECL|macro|GIMP_SELECTION_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SELECTION_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SELECTION_EDITOR, GimpSelectionEditorClass))
end_define

begin_typedef
DECL|typedef|GimpSelectionEditorClass
typedef|typedef
name|struct
name|_GimpSelectionEditorClass
name|GimpSelectionEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSelectionEditor
struct|struct
name|_GimpSelectionEditor
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|invert_button
name|GtkWidget
modifier|*
name|invert_button
decl_stmt|;
DECL|member|all_button
name|GtkWidget
modifier|*
name|all_button
decl_stmt|;
DECL|member|none_button
name|GtkWidget
modifier|*
name|none_button
decl_stmt|;
DECL|member|save_button
name|GtkWidget
modifier|*
name|save_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSelectionEditorClass
struct|struct
name|_GimpSelectionEditorClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_selection_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_selection_editor_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_selection_editor_set_image
parameter_list|(
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|,
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
comment|/* __GIMP_SELECTION_EDITOR_H__ */
end_comment

end_unit

