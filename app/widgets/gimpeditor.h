begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpeditor.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EDITOR_H__
define|#
directive|define
name|__GIMP_EDITOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_EDITOR
define|#
directive|define
name|GIMP_TYPE_EDITOR
value|(gimp_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_EDITOR (obj)
define|#
directive|define
name|GIMP_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_EDITOR, GimpEditor))
end_define

begin_define
DECL|macro|GIMP_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_EDITOR, GimpEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_EDITOR))
end_define

begin_define
DECL|macro|GIMP_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_EDITOR, GimpEditorClass))
end_define

begin_typedef
DECL|typedef|GimpEditorClass
typedef|typedef
name|struct
name|_GimpEditorClass
name|GimpEditorClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEditorPrivate
typedef|typedef
name|struct
name|_GimpEditorPrivate
name|GimpEditorPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEditor
struct|struct
name|_GimpEditor
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpEditorPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEditorClass
struct|struct
name|_GimpEditorClass
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
name|gimp_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_editor_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_editor_create_menu
parameter_list|(
name|GimpEditor
modifier|*
name|editor
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
parameter_list|,
name|gpointer
name|popup_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_editor_popup_menu
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|GimpMenuPositionFunc
name|position_func
parameter_list|,
name|gpointer
name|position_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_editor_add_button
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|GCallback
name|extended_callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_editor_add_stock_box
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|GType
name|enum_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_editor_add_action_button
argument_list|(
name|GimpEditor
operator|*
name|editor
argument_list|,
specifier|const
name|gchar
operator|*
name|group_name
argument_list|,
specifier|const
name|gchar
operator|*
name|action_name
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_editor_set_show_name
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_editor_set_name
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_editor_set_box_style
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
name|GtkBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_editor_get_ui_manager
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkBox
modifier|*
name|gimp_editor_get_button_box
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMenuFactory
modifier|*
name|gimp_editor_get_menu_factory
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
modifier|*
name|gimp_editor_get_popup_data
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_editor_get_ui_path
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_EDITOR_H__  */
end_comment

end_unit

