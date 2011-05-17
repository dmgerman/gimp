begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RECTANGLE_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RECTANGLE_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_RECTANGLE_SELECT_TOOL_H__
end_define

begin_function_decl
name|void
name|gimp_test_utils_set_env_to_subpath
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target_env_var
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_test_utils_set_gimp2_directory
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_test_utils_setup_menus_dir
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_test_utils_create_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_test_utils_synthesize_key_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|keyval
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUIManager
modifier|*
name|gimp_test_utils_get_ui_manager
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_test_utils_create_image_from_dalog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RECTANGLE_SELECT_TOOL_H__ */
end_comment

end_unit

