begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

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
name|gchar
modifier|*
name|gimp_thumb_name_from_uri
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
name|gchar
modifier|*
name|gimp_thumb_find_thumb
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpThumbSize
modifier|*
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
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

