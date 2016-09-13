begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_USER_INSTALL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_USER_INSTALL_H__
define|#
directive|define
name|__GIMP_USER_INSTALL_H__
end_define

begin_typedef
DECL|typedef|GimpUserInstall
typedef|typedef
name|struct
name|_GimpUserInstall
name|GimpUserInstall
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUserInstallLogFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpUserInstallLogFunc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GimpUserInstall
modifier|*
name|gimp_user_install_new
parameter_list|(
name|GObject
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_user_install_run
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_user_install_free
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_user_install_set_log_handler
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
name|GimpUserInstallLogFunc
name|log
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __USER_INSTALL_H__ */
end_comment

end_unit

