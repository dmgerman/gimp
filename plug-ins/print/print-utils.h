begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_function_decl
name|GKeyFile
modifier|*
name|print_utils_key_file_load_from_rcfile
parameter_list|(
specifier|const
name|gchar
modifier|*
name|basename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GKeyFile
modifier|*
name|print_utils_key_file_load_from_parasite
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|parasite_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|print_utils_key_file_save_as_rcfile
parameter_list|(
name|GKeyFile
modifier|*
name|key_file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|basename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|print_utils_key_file_save_as_parasite
parameter_list|(
name|GKeyFile
modifier|*
name|key_file
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
specifier|const
name|gchar
modifier|*
name|parasite_name
parameter_list|)
function_decl|;
end_function_decl

end_unit

