begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsettingsbox.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
name|GtkHBox
name|parent_instance
decl_stmt|;
DECL|member|combo
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
DECL|member|import_item
name|GtkWidget
modifier|*
name|import_item
decl_stmt|;
DECL|member|export_item
name|GtkWidget
modifier|*
name|export_item
decl_stmt|;
DECL|member|file_dialog
name|GtkWidget
modifier|*
name|file_dialog
decl_stmt|;
DECL|member|editor_dialog
name|GtkWidget
modifier|*
name|editor_dialog
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|config
name|GObject
modifier|*
name|config
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|import_dialog_title
name|gchar
modifier|*
name|import_dialog_title
decl_stmt|;
DECL|member|export_dialog_title
name|gchar
modifier|*
name|export_dialog_title
decl_stmt|;
DECL|member|file_dialog_help_id
name|gchar
modifier|*
name|file_dialog_help_id
decl_stmt|;
DECL|member|default_folder
name|gchar
modifier|*
name|default_folder
decl_stmt|;
DECL|member|last_filename
name|gchar
modifier|*
name|last_filename
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
name|GtkHBoxClass
name|parent_class
decl_stmt|;
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

