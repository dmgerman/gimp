begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-remote.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_REMOTE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_REMOTE_H__
define|#
directive|define
name|__GIMP_REMOTE_H__
end_define

begin_function_decl
name|GdkWindow
modifier|*
name|gimp_remote_find_toolbox
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|GdkScreen
modifier|*
name|screen
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|void
name|gimp_remote_launch
argument_list|(
name|GdkScreen
operator|*
name|screen
argument_list|,
specifier|const
name|gchar
operator|*
name|argv0
argument_list|,
specifier|const
name|gchar
operator|*
name|startup_id
argument_list|,
name|gboolean
name|no_splash
argument_list|,
name|GString
operator|*
name|file_list
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_remote_drop_files
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GString
modifier|*
name|file_list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_remote_print_id
parameter_list|(
name|GdkWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_REMOTE_H__ */
end_comment

end_unit

