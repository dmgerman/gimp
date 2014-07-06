begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * file-utils.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpthumb/gimpthumb.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"file-procedure.h"
end_include

begin_include
include|#
directive|include
file|"file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gchar
modifier|*
name|file_utils_unescape_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|escaped
parameter_list|,
name|gint
name|len
parameter_list|,
specifier|const
name|gchar
modifier|*
name|illegal_escaped_characters
parameter_list|,
name|gboolean
name|ascii_must_not_be_escaped
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|file_utils_filename_is_uri (const gchar * filename,GError ** error)
name|file_utils_filename_is_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|strstr
argument_list|(
name|filename
argument_list|,
literal|"://"
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|scheme
decl_stmt|;
name|gchar
modifier|*
name|canon
decl_stmt|;
name|scheme
operator|=
name|g_strndup
argument_list|(
name|filename
argument_list|,
operator|(
name|strstr
argument_list|(
name|filename
argument_list|,
literal|"://"
argument_list|)
operator|-
name|filename
operator|)
argument_list|)
expr_stmt|;
name|canon
operator|=
name|g_strdup
argument_list|(
name|scheme
argument_list|)
expr_stmt|;
name|g_strcanon
argument_list|(
argument|canon
argument_list|,
argument|G_CSET_A_2_Z G_CSET_a_2_z G_CSET_DIGITS
literal|"+-."
argument_list|,
literal|'-'
argument_list|)
empty_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|scheme
argument_list|,
name|canon
argument_list|)
operator|||
operator|!
name|g_ascii_isgraph
argument_list|(
name|canon
index|[
literal|0
index|]
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"'%s:' is not a valid URI scheme"
argument_list|)
argument_list|,
name|scheme
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|scheme
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|canon
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_free
argument_list|(
name|scheme
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|canon
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|G_CONVERT_ERROR
argument_list|,
name|G_CONVERT_ERROR_ILLEGAL_SEQUENCE
argument_list|,
name|_
argument_list|(
literal|"Invalid character sequence in URI"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|file_utils_filename_to_uri (Gimp * gimp,const gchar * filename,GError ** error)
name|file_utils_filename_to_uri
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|gchar
modifier|*
name|absolute
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GError
modifier|*
name|temp_error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|filename
argument_list|)
expr_stmt|;
comment|/*  check for prefixes like http or ftp  */
if|if
condition|(
name|file_procedure_find_by_prefix
argument_list|(
name|gimp
operator|->
name|plug_in_manager
operator|->
name|load_procs
argument_list|,
name|file
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|filename
argument_list|)
return|;
block|}
else|else
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|G_CONVERT_ERROR
argument_list|,
name|G_CONVERT_ERROR_ILLEGAL_SEQUENCE
argument_list|,
name|_
argument_list|(
literal|"Invalid character sequence in URI"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|file_utils_filename_is_uri
argument_list|(
name|filename
argument_list|,
operator|&
name|temp_error
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|filename
argument_list|)
return|;
block|}
elseif|else
if|if
condition|(
name|temp_error
condition|)
block|{
name|g_propagate_error
argument_list|(
name|error
argument_list|,
name|temp_error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_path_is_absolute
argument_list|(
name|filename
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|current
decl_stmt|;
name|current
operator|=
name|g_get_current_dir
argument_list|()
expr_stmt|;
name|absolute
operator|=
name|g_build_filename
argument_list|(
name|current
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|current
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|absolute
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|absolute
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|absolute
argument_list|)
expr_stmt|;
return|return
name|uri
return|;
block|}
end_function

begin_function
name|GFile
modifier|*
DECL|function|file_utils_any_to_file (Gimp * gimp,const gchar * filename_or_uri,GError ** error)
name|file_utils_any_to_file
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename_or_uri
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename_or_uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  first try if we got a file uri  */
name|uri
operator|=
name|g_filename_from_uri
argument_list|(
name|filename_or_uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_strdup
argument_list|(
name|filename_or_uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|uri
operator|=
name|file_utils_filename_to_uri
argument_list|(
name|gimp
argument_list|,
name|filename_or_uri
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
return|return
name|file
return|;
block|}
end_function

begin_comment
comment|/**  * file_utils_filename_from_uri:  * @uri: a URI  *  * A utility function to be used as a replacement for  * g_filename_from_uri(). It deals with file: URIs with hostname in a  * platform-specific way. On Win32, a UNC path is created and  * returned, on other platforms the URI is detected as non-local and  * NULL is returned.  *  * Returns: newly allocated filename or %NULL if @uri is a remote file  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|file_utils_filename_from_uri (const gchar * uri)
name|file_utils_filename_from_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|hostname
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
operator|&
name|hostname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filename
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|hostname
condition|)
block|{
comment|/*  we have a file: URI with a hostname                           */
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/*  on Win32, create a valid UNC path and use it as the filename  */
name|gchar
modifier|*
name|tmp
init|=
name|g_build_filename
argument_list|(
literal|"//"
argument_list|,
name|hostname
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|tmp
expr_stmt|;
else|#
directive|else
comment|/*  otherwise return NULL, caller should use URI then             */
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|NULL
expr_stmt|;
endif|#
directive|endif
name|g_free
argument_list|(
name|hostname
argument_list|)
expr_stmt|;
block|}
return|return
name|filename
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|file_utils_uri_with_new_ext (const gchar * uri,const gchar * ext_uri)
name|file_utils_uri_with_new_ext
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ext_uri
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|uri_ext
init|=
name|file_utils_uri_get_ext
argument_list|(
name|uri
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ext_uri_ext
init|=
name|ext_uri
condition|?
name|file_utils_uri_get_ext
argument_list|(
name|ext_uri
argument_list|)
else|:
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|uri_without_ext
init|=
name|g_strndup
argument_list|(
name|uri
argument_list|,
name|uri_ext
operator|-
name|uri
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|ret
init|=
name|g_strconcat
argument_list|(
name|uri_without_ext
argument_list|,
name|ext_uri_ext
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|uri_without_ext
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_comment
comment|/**  * file_utils_uri_get_ext:  * @uri:  *  * Returns the position of the extension (including the .) for an URI. If  * there is no extension the returned position is right after the  * string, at the terminating NULL character.  *  * Returns:  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|file_utils_uri_get_ext (const gchar * uri)
name|file_utils_uri_get_ext
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|ext
init|=
name|NULL
decl_stmt|;
name|int
name|uri_len
init|=
name|strlen
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|int
name|search_len
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|g_strrstr
argument_list|(
name|uri
argument_list|,
literal|".gz"
argument_list|)
condition|)
name|search_len
operator|=
name|uri_len
operator|-
literal|3
expr_stmt|;
elseif|else
if|if
condition|(
name|g_strrstr
argument_list|(
name|uri
argument_list|,
literal|".bz2"
argument_list|)
condition|)
name|search_len
operator|=
name|uri_len
operator|-
literal|4
expr_stmt|;
elseif|else
if|if
condition|(
name|g_strrstr
argument_list|(
name|uri
argument_list|,
literal|".xz"
argument_list|)
condition|)
name|search_len
operator|=
name|uri_len
operator|-
literal|3
expr_stmt|;
else|else
name|search_len
operator|=
name|uri_len
expr_stmt|;
name|ext
operator|=
name|g_strrstr_len
argument_list|(
name|uri
argument_list|,
name|search_len
argument_list|,
literal|"."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ext
condition|)
name|ext
operator|=
name|uri
operator|+
name|uri_len
expr_stmt|;
return|return
name|ext
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|file_utils_uri_to_utf8_filename (const gchar * uri)
name|file_utils_uri_to_utf8_filename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|uri
argument_list|,
literal|"file:"
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_filename_from_uri
argument_list|(
name|uri
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|utf8
operator|=
name|g_filename_to_utf8
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|utf8
condition|)
return|return
name|utf8
return|;
name|g_warning
argument_list|(
literal|"%s: cannot convert filename to UTF-8: %s"
argument_list|,
name|G_STRLOC
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|g_strdup
argument_list|(
name|uri
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|file_utils_uri_to_utf8_basename (const gchar * uri)
name|file_utils_uri_to_utf8_basename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|strstr
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|)
condition|)
block|{
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strstr
argument_list|(
name|filename
argument_list|,
literal|"://"
argument_list|)
condition|)
block|{
name|basename
operator|=
name|strrchr
argument_list|(
name|uri
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|basename
condition|)
name|basename
operator|=
name|g_strdup
argument_list|(
name|basename
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|basename
condition|)
block|{
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|basename
return|;
block|}
return|return
name|filename
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|file_utils_uri_display_basename (const gchar * uri)
name|file_utils_uri_display_basename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
modifier|*
name|basename
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|uri
argument_list|,
literal|"file:"
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_filename_from_uri
argument_list|(
name|uri
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|basename
operator|=
name|g_filename_display_basename
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gchar
modifier|*
name|name
init|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|basename
operator|=
name|strrchr
argument_list|(
name|name
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
name|basename
condition|)
name|basename
operator|=
name|g_strdup
argument_list|(
name|basename
operator|+
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|basename
condition|?
name|basename
else|:
name|file_utils_uri_to_utf8_basename
argument_list|(
name|uri
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|file_utils_uri_display_name (const gchar * uri)
name|file_utils_uri_display_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|uri
argument_list|,
literal|"file:"
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_filename_from_uri
argument_list|(
name|uri
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|name
operator|=
name|g_filename_display_name
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|name
operator|=
name|file_utils_unescape_uri
argument_list|(
name|uri
argument_list|,
operator|-
literal|1
argument_list|,
literal|"/"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|name
condition|?
name|name
else|:
name|g_strdup
argument_list|(
name|uri
argument_list|)
return|;
block|}
end_function

begin_function
name|GdkPixbuf
modifier|*
DECL|function|file_utils_load_thumbnail (const gchar * filename)
name|file_utils_load_thumbnail
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpThumbnail
modifier|*
name|thumbnail
init|=
name|NULL
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|thumbnail
operator|=
name|gimp_thumbnail_new
argument_list|()
expr_stmt|;
name|gimp_thumbnail_set_uri
argument_list|(
name|thumbnail
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gimp_thumbnail_load_thumb
argument_list|(
name|thumbnail
argument_list|,
name|GIMP_THUMBNAIL_SIZE_NORMAL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|gint
name|width
init|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
if|if
condition|(
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
operator|!=
literal|3
condition|)
block|{
name|GdkPixbuf
modifier|*
name|tmp
init|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|FALSE
argument_list|,
literal|8
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
decl_stmt|;
name|gdk_pixbuf_composite_color
argument_list|(
name|pixbuf
argument_list|,
name|tmp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|GDK_INTERP_NEAREST
argument_list|,
literal|255
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|GIMP_CHECK_SIZE_SM
argument_list|,
literal|0x66666666
argument_list|,
literal|0x99999999
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|tmp
expr_stmt|;
block|}
block|}
return|return
name|pixbuf
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|file_utils_save_thumbnail (GimpImage * image,const gchar * filename)
name|file_utils_save_thumbnail
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|image_uri
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|image_uri
operator|=
name|gimp_image_get_uri
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_uri
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|uri
argument_list|,
name|image_uri
argument_list|)
condition|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|imagefile
operator|=
name|gimp_imagefile_new
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_imagefile_save_thumbnail
argument_list|(
name|imagefile
argument_list|,
name|NULL
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|imagefile
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/* the following two functions are copied from glib/gconvert.c */
end_comment

begin_function
specifier|static
name|gint
DECL|function|unescape_character (const gchar * scanner)
name|unescape_character
parameter_list|(
specifier|const
name|gchar
modifier|*
name|scanner
parameter_list|)
block|{
name|gint
name|first_digit
decl_stmt|;
name|gint
name|second_digit
decl_stmt|;
name|first_digit
operator|=
name|g_ascii_xdigit_value
argument_list|(
name|scanner
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|first_digit
operator|<
literal|0
condition|)
return|return
operator|-
literal|1
return|;
name|second_digit
operator|=
name|g_ascii_xdigit_value
argument_list|(
name|scanner
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|second_digit
operator|<
literal|0
condition|)
return|return
operator|-
literal|1
return|;
return|return
operator|(
name|first_digit
operator|<<
literal|4
operator|)
operator||
name|second_digit
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|file_utils_unescape_uri (const gchar * escaped,gint len,const gchar * illegal_escaped_characters,gboolean ascii_must_not_be_escaped)
name|file_utils_unescape_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|escaped
parameter_list|,
name|gint
name|len
parameter_list|,
specifier|const
name|gchar
modifier|*
name|illegal_escaped_characters
parameter_list|,
name|gboolean
name|ascii_must_not_be_escaped
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|in
decl_stmt|,
modifier|*
name|in_end
decl_stmt|;
name|gchar
modifier|*
name|out
decl_stmt|,
modifier|*
name|result
decl_stmt|;
name|gint
name|c
decl_stmt|;
if|if
condition|(
name|escaped
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|len
operator|<
literal|0
condition|)
name|len
operator|=
name|strlen
argument_list|(
name|escaped
argument_list|)
expr_stmt|;
name|result
operator|=
name|g_malloc
argument_list|(
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
name|out
operator|=
name|result
expr_stmt|;
for|for
control|(
name|in
operator|=
name|escaped
operator|,
name|in_end
operator|=
name|escaped
operator|+
name|len
init|;
name|in
operator|<
name|in_end
condition|;
name|in
operator|++
control|)
block|{
name|c
operator|=
operator|*
name|in
expr_stmt|;
if|if
condition|(
name|c
operator|==
literal|'%'
condition|)
block|{
comment|/* catch partial escape sequences past the end of the substring */
if|if
condition|(
name|in
operator|+
literal|3
operator|>
name|in_end
condition|)
break|break;
name|c
operator|=
name|unescape_character
argument_list|(
name|in
operator|+
literal|1
argument_list|)
expr_stmt|;
comment|/* catch bad escape sequences and NUL characters */
if|if
condition|(
name|c
operator|<=
literal|0
condition|)
break|break;
comment|/* catch escaped ASCII */
if|if
condition|(
name|ascii_must_not_be_escaped
operator|&&
name|c
operator|<=
literal|0x7F
condition|)
break|break;
comment|/* catch other illegal escaped characters */
if|if
condition|(
name|strchr
argument_list|(
name|illegal_escaped_characters
argument_list|,
name|c
argument_list|)
operator|!=
name|NULL
condition|)
break|break;
name|in
operator|+=
literal|2
expr_stmt|;
block|}
operator|*
name|out
operator|++
operator|=
name|c
expr_stmt|;
block|}
name|g_assert
argument_list|(
name|out
operator|-
name|result
operator|<=
name|len
argument_list|)
expr_stmt|;
operator|*
name|out
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|in
operator|!=
name|in_end
condition|)
block|{
name|g_free
argument_list|(
name|result
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|result
return|;
block|}
end_function

end_unit

