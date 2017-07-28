begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-raw-utils.h -- raw file format plug-in  * Copyright (C) 2016 Tobias Ellinghaus<me@houz.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_function_decl
name|gchar
modifier|*
name|file_raw_get_executable_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|main_executable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|suffix
parameter_list|,
specifier|const
name|gchar
modifier|*
name|env_variable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mac_bundle_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|win32_registry_key_base
parameter_list|,
name|gboolean
modifier|*
name|search_path
parameter_list|)
function_decl|;
end_function_decl

end_unit

