begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagemaptool-settings.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_MAP_TOOL_SETTINGS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_MAP_TOOL_SETTINGS_H__
define|#
directive|define
name|__GIMP_IMAGE_MAP_TOOL_SETTINGS_H__
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_map_tool_real_get_settings_ui
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
name|GimpContainer
modifier|*
name|settings
parameter_list|,
specifier|const
name|gchar
modifier|*
name|settings_filename
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
name|GtkWidget
modifier|*
modifier|*
name|settings_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_map_tool_real_settings_import
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_map_tool_real_settings_export
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_MAP_TOOL_SETTINGS_H__ */
end_comment

end_unit

