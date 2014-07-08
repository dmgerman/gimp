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

begin_function
specifier|static
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
name|GFile
modifier|*
DECL|function|file_utils_filename_to_file (Gimp * gimp,const gchar * filename,GError ** error)
name|file_utils_filename_to_file
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
return|return
name|file
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
return|return
name|file
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
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|absolute
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|absolute
argument_list|)
expr_stmt|;
return|return
name|file
return|;
block|}
end_function

begin_function
name|GFile
modifier|*
DECL|function|file_utils_file_with_new_ext (GFile * file,GFile * ext_file)
name|file_utils_file_with_new_ext
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GFile
modifier|*
name|ext_file
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|file_ext
decl_stmt|;
name|gint
name|file_ext_len
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
name|ext_file_ext
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|uri_without_ext
decl_stmt|;
name|gchar
modifier|*
name|new_uri
decl_stmt|;
name|GFile
modifier|*
name|ret
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|ext_file
operator|==
name|NULL
operator|||
name|G_IS_FILE
argument_list|(
name|ext_file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|file_ext
operator|=
name|file_utils_file_get_ext
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|file_ext
condition|)
block|{
name|file_ext_len
operator|=
name|strlen
argument_list|(
name|file_ext
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|file_ext
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ext_file
condition|)
name|ext_file_ext
operator|=
name|file_utils_file_get_ext
argument_list|(
name|ext_file
argument_list|)
expr_stmt|;
name|uri_without_ext
operator|=
name|g_strndup
argument_list|(
name|uri
argument_list|,
name|strlen
argument_list|(
name|uri
argument_list|)
operator|-
name|file_ext_len
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|new_uri
operator|=
name|g_strconcat
argument_list|(
name|uri_without_ext
argument_list|,
name|ext_file_ext
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ret
operator|=
name|g_file_new_for_uri
argument_list|(
name|new_uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ext_file_ext
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri_without_ext
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_uri
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_comment
comment|/**  * file_utils_file_get_ext:  * @file:  *  * Returns the position of the extension (including the .), or NULL  * if there is no extension.  *  * Returns:  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|file_utils_file_get_ext (GFile * file)
name|file_utils_file_get_ext
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gint
name|uri_len
decl_stmt|;
name|gchar
modifier|*
name|ext
init|=
name|NULL
decl_stmt|;
name|gint
name|search_len
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|uri_len
operator|=
name|strlen
argument_list|(
name|uri
argument_list|)
expr_stmt|;
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
name|ext
condition|)
name|ext
operator|=
name|g_strdup
argument_list|(
name|ext
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
return|return
name|ext
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
name|GFile
modifier|*
name|file
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
name|file
operator|=
name|gimp_image_get_file
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|gchar
modifier|*
name|image_uri
init|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
decl_stmt|;
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
operator|&&
name|image_uri
operator|&&
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
name|image_uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

end_unit

