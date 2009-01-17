begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-locale-domain.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_MANAGER_LOCALE_DOMAIN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_MANAGER_LOCALE_DOMAIN_H__
define|#
directive|define
name|__GIMP_PLUG_IN_MANAGER_LOCALE_DOMAIN_H__
end_define

begin_function_decl
name|void
name|gimp_plug_in_manager_locale_domain_exit
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a locale domain */
end_comment

begin_function_decl
name|void
name|gimp_plug_in_manager_add_locale_domain
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve a plug-ins locale domain */
end_comment

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_plug_in_manager_get_locale_domain
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|locale_path
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve all locale domains */
end_comment

begin_function_decl
name|gint
name|gimp_plug_in_manager_get_locale_domains
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|locale_domains
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|locale_paths
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_MANAGER_LOCALE_DOMAIN_H__ */
end_comment

end_unit

