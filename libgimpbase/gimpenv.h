begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenv.h  * Copyright (C) 1999 Tor Lillqvist<tml@iki.fi>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPENV_H__
end_ifndef

begin_define
DECL|macro|__GIMPENV_H__
define|#
directive|define
name|__GIMPENV_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
ifdef|#
directive|ifdef
name|G_OS_WIN32
ifdef|#
directive|ifdef
name|LIBGIMP_COMPILATION
DECL|macro|GIMPVAR
define|#
directive|define
name|GIMPVAR
value|__declspec(dllexport)
else|#
directive|else
comment|/* !LIBGIMP_COMPILATION */
define|#
directive|define
name|GIMPVAR
value|extern __declspec(dllimport)
endif|#
directive|endif
comment|/* !LIBGIMP_COMPILATION */
else|#
directive|else
comment|/* !G_OS_WIN32 */
define|#
directive|define
name|GIMPVAR
value|extern
endif|#
directive|endif
DECL|variable|gimp_major_version
name|GIMPVAR
specifier|const
name|guint
name|gimp_major_version
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_minor_version
name|GIMPVAR
specifier|const
name|guint
name|gimp_minor_version
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_micro_version
name|GIMPVAR
specifier|const
name|guint
name|gimp_micro_version
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_directory
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_data_directory
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_locale_directory
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_sysconf_directory
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_plug_in_directory
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_user_directory
argument_list|(
name|GimpUserDirectory
name|type
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_gtkrc
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gchar
modifier|*
name|gimp_personal_rc_file
argument_list|(
specifier|const
name|gchar
operator|*
name|basename
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GList
modifier|*
name|gimp_path_parse
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gint
name|max_paths
parameter_list|,
name|gboolean
name|check
parameter_list|,
name|GList
modifier|*
modifier|*
name|check_failed
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gchar
modifier|*
name|gimp_path_to_str
argument_list|(
name|GList
operator|*
name|path
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_path_free
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gchar
modifier|*
name|gimp_path_get_user_writable_dir
argument_list|(
name|GList
operator|*
name|path
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  should be considered private, don't use!  */
end_comment

begin_function_decl
name|void
name|gimp_env_init
parameter_list|(
name|gboolean
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMPENV_H__  */
end_comment

end_unit

