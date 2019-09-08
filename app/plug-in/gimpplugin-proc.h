begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugin-proc.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_PROC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_PROC_H__
define|#
directive|define
name|__GIMP_PLUG_IN_PROC_H__
end_define

begin_function_decl
name|gboolean
name|gimp_plug_in_set_proc_image_types
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plug_in_add_proc_menu_path
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plug_in_set_proc_icon
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|GimpIconType
name|type
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|data_length
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_PROC_H__ */
end_comment

end_unit

