begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenv.h  *  * Copyright (C) 1999 Tor Lillqvist<tml@iki.fi>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
name|gchar
modifier|*
name|gimp_directory
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_personal_rc_file
parameter_list|(
name|gchar
modifier|*
name|basename
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_data_directory
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_sysconf_directory
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_gtkrc
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GList
modifier|*
name|gimp_path_parse
parameter_list|(
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
name|gchar
modifier|*
name|gimp_path_to_str
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|)
function_decl|;
name|void
name|gimp_path_free
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|gimp_path_get_user_writable_dir
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMPENV_H__  */
end_comment

end_unit

