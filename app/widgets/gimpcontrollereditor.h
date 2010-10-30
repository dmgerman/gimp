begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontrollereditor.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTROLLER_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTROLLER_EDITOR_H__
define|#
directive|define
name|__GIMP_CONTROLLER_EDITOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CONTROLLER_EDITOR
define|#
directive|define
name|GIMP_TYPE_CONTROLLER_EDITOR
value|(gimp_controller_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_EDITOR (obj)
define|#
directive|define
name|GIMP_CONTROLLER_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTROLLER_EDITOR, GimpControllerEditor))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_CONTROLLER_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTROLLER_EDITOR, GimpControllerEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_CONTROLLER_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTROLLER_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTROLLER_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTROLLER_EDITOR))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTROLLER_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTROLLER_EDITOR, GimpControllerEditorClass))
end_define

begin_typedef
DECL|typedef|GimpControllerEditorClass
typedef|typedef
name|struct
name|_GimpControllerEditorClass
name|GimpControllerEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpControllerEditor
struct|struct
name|_GimpControllerEditor
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|info
name|GimpControllerInfo
modifier|*
name|info
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|sel
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
DECL|member|grab_button
name|GtkWidget
modifier|*
name|grab_button
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
DECL|member|edit_dialog
name|GtkWidget
modifier|*
name|edit_dialog
decl_stmt|;
DECL|member|edit_sel
name|GtkTreeSelection
modifier|*
name|edit_sel
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpControllerEditorClass
struct|struct
name|_GimpControllerEditorClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_controller_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_controller_editor_new
parameter_list|(
name|GimpControllerInfo
modifier|*
name|info
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTROLLER_EDITOR_H__  */
end_comment

end_unit

