begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpeditor.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<gtk/gtkvbox.h>
end_include

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

begin_struct
DECL|struct|_GimpEditor
struct|struct
name|_GimpEditor
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|menu_factory
name|GimpMenuFactory
modifier|*
name|menu_factory
decl_stmt|;
DECL|member|ui_manager
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
DECL|member|ui_path
name|gchar
modifier|*
name|ui_path
decl_stmt|;
DECL|member|popup_data
name|gpointer
name|popup_data
decl_stmt|;
DECL|member|button_box
name|GtkWidget
modifier|*
name|button_box
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
name|GtkVBoxClass
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
name|callback_data
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

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_editor_add_action_button
parameter_list|(
name|GimpEditor
modifier|*
name|editor
parameter_list|,
specifier|const
name|gchar
modifier|*
name|group_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_name
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_EDITOR_H__  */
end_comment

end_unit

