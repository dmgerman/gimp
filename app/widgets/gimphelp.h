begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp.h  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_H__
define|#
directive|define
name|__GIMP_HELP_H__
end_define

begin_comment
comment|/*  the main help function  *  *  there should be no need to use it directly  */
end_comment

begin_function_decl
name|void
name|gimp_help_show
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  checks if the help browser is available  */
end_comment

begin_function_decl
name|gboolean
name|gimp_help_browser_is_installed
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  checks if the user manual is installed locally  */
end_comment

begin_function_decl
name|gboolean
name|gimp_help_user_manual_is_installed
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the configuration changed with respect to the location  *  of the user manual, invalidate the cached information  */
end_comment

begin_function_decl
name|void
name|gimp_help_user_manual_changed
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
comment|/* __GIMP_HELP_H__ */
end_comment

end_unit

