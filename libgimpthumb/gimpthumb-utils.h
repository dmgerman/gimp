begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_THUMB_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_THUMB_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpthumb/gimpthumb.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THUMB_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THUMB_UTILS_H__
define|#
directive|define
name|__GIMP_THUMB_UTILS_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
name|gboolean
name|gimp_thumb_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|creator
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumb_basedir
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gchar
modifier|*
name|gimp_thumb_find_thumb
argument_list|(
specifier|const
name|gchar
operator|*
name|uri
argument_list|,
name|GimpThumbSize
operator|*
name|size
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpThumbFileType
name|gimp_thumb_file_test
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint64
modifier|*
name|mtime
parameter_list|,
name|gint64
modifier|*
name|size
parameter_list|,
name|gint
modifier|*
name|err_no
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gchar
modifier|*
name|gimp_thumb_name_from_uri
argument_list|(
specifier|const
name|gchar
operator|*
name|uri
argument_list|,
name|GimpThumbSize
name|size
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_thumb_get_thumb_dir
parameter_list|(
name|GimpThumbSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_thumb_ensure_thumb_dir
parameter_list|(
name|GimpThumbSize
name|size
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_thumbs_delete_for_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|gchar
modifier|*
name|gimp_thumb_name_from_uri_local
argument_list|(
specifier|const
name|gchar
operator|*
name|uri
argument_list|,
name|GimpThumbSize
name|size
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gchar
modifier|*
name|gimp_thumb_get_thumb_dir_local
argument_list|(
specifier|const
name|gchar
operator|*
name|dirname
argument_list|,
name|GimpThumbSize
name|size
argument_list|)
name|G_GNUC_MALLOC
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_thumb_ensure_thumb_dir_local
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|,
name|GimpThumbSize
name|size
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_thumbs_delete_for_uri_local
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  for internal use only   */
end_comment

begin_function_decl
name|G_GNUC_INTERNAL
name|void
name|_gimp_thumbs_delete_others
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpThumbSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gchar
modifier|*
name|_gimp_thumb_filename_from_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
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
comment|/* __GIMP_THUMB_UTILS_H__ */
end_comment

end_unit

