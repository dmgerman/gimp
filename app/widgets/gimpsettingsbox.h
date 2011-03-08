begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsettingsbox.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SETTINGS_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SETTINGS_BOX_H__
define|#
directive|define
name|__GIMP_SETTINGS_BOX_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_SETTINGS_BOX
define|#
directive|define
name|GIMP_TYPE_SETTINGS_BOX
value|(gimp_settings_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_SETTINGS_BOX (obj)
define|#
directive|define
name|GIMP_SETTINGS_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SETTINGS_BOX, GimpSettingsBox))
end_define

begin_define
DECL|macro|GIMP_SETTINGS_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_SETTINGS_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SETTINGS_BOX, GimpSettingsBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_SETTINGS_BOX (obj)
define|#
directive|define
name|GIMP_IS_SETTINGS_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SETTINGS_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_SETTINGS_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SETTINGS_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SETTINGS_BOX))
end_define

begin_define
DECL|macro|GIMP_SETTINGS_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SETTINGS_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SETTINGS_BOX, GimpSettingsBoxClass))
end_define

begin_typedef
DECL|typedef|GimpSettingsBoxClass
typedef|typedef
name|struct
name|_GimpSettingsBoxClass
name|GimpSettingsBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSettingsBox
struct|struct
name|_GimpSettingsBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSettingsBoxClass
struct|struct
name|_GimpSettingsBoxClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|file_dialog_setup
name|void
function_decl|(
modifier|*
name|file_dialog_setup
function_decl|)
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
name|GtkFileChooserDialog
modifier|*
name|dialog
parameter_list|,
name|gboolean
name|export
parameter_list|)
function_decl|;
DECL|member|import
name|void
function_decl|(
modifier|*
name|import
function_decl|)
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
DECL|member|export
name|void
function_decl|(
modifier|*
name|export
function_decl|)
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_settings_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_settings_box_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|import_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|export_dialog_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|file_dialog_help_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_folder
parameter_list|,
specifier|const
name|gchar
modifier|*
name|last_filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_settings_box_add_current
parameter_list|(
name|GimpSettingsBox
modifier|*
name|box
parameter_list|,
name|gint
name|max_recent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_settings_box_get_combo
parameter_list|(
name|GimpSettingsBox
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
comment|/*  __GIMP_SETTINGS_BOX_H__  */
end_comment

end_unit

