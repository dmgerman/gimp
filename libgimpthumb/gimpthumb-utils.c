begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<libgimpbase/gimpwin32-io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"gimpthumb-error.h"
end_include

begin_include
include|#
directive|include
file|"gimpthumb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpthumb-utils.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_thumb_png_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_thumb_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_thumb_initialized
specifier|static
name|gboolean
name|gimp_thumb_initialized
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thumb_num_sizes
specifier|static
name|gint
name|thumb_num_sizes
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thumb_sizes
specifier|static
name|gint
modifier|*
name|thumb_sizes
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thumb_dir
specifier|static
name|gchar
modifier|*
name|thumb_dir
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thumb_subdirs
specifier|static
name|gchar
modifier|*
modifier|*
name|thumb_subdirs
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thumb_fail_subdir
specifier|static
name|gchar
modifier|*
name|thumb_fail_subdir
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|gboolean
DECL|function|gimp_thumb_init (const gchar * creator,const gchar * thumb_basedir)
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
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|creator
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_thumb_initialized
condition|)
name|gimp_thumb_exit
argument_list|()
expr_stmt|;
name|thumb_dir
operator|=
operator|(
name|thumb_basedir
condition|?
name|g_strdup
argument_list|(
name|thumb_basedir
argument_list|)
else|:
name|g_build_filename
argument_list|(
name|g_get_home_dir
argument_list|()
argument_list|,
literal|".thumbnails"
argument_list|,
name|NULL
argument_list|)
operator|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_THUMB_SIZE
argument_list|)
expr_stmt|;
name|thumb_num_sizes
operator|=
name|enum_class
operator|->
name|n_values
expr_stmt|;
name|thumb_sizes
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|thumb_num_sizes
argument_list|)
expr_stmt|;
name|thumb_subdirs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|thumb_num_sizes
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|enum_value
operator|=
name|enum_class
operator|->
name|values
init|;
name|i
operator|<
name|enum_class
operator|->
name|n_values
condition|;
name|i
operator|++
operator|,
name|enum_value
operator|++
control|)
block|{
name|thumb_sizes
index|[
name|i
index|]
operator|=
name|enum_value
operator|->
name|value
expr_stmt|;
name|thumb_subdirs
index|[
name|i
index|]
operator|=
name|g_build_filename
argument_list|(
name|thumb_dir
argument_list|,
name|enum_value
operator|->
name|value_nick
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|thumb_fail_subdir
operator|=
name|thumb_subdirs
index|[
literal|0
index|]
expr_stmt|;
name|thumb_subdirs
index|[
literal|0
index|]
operator|=
name|g_build_filename
argument_list|(
name|thumb_fail_subdir
argument_list|,
name|creator
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_thumb_initialized
operator|=
name|TRUE
expr_stmt|;
return|return
name|gimp_thumb_initialized
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_thumb_ensure_thumb_dirs (GError ** error)
name|gimp_thumb_ensure_thumb_dirs
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
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
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|thumb_num_sizes
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|thumb_subdirs
index|[
name|i
index|]
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_file_test
argument_list|(
name|thumb_dir
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
operator|||
operator|(
name|mkdir
argument_list|(
name|thumb_dir
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
operator||
name|S_IXUSR
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
if|if
condition|(
name|i
operator|==
literal|0
condition|)
name|mkdir
argument_list|(
name|thumb_fail_subdir
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
operator||
name|S_IXUSR
argument_list|)
expr_stmt|;
name|mkdir
argument_list|(
name|thumb_subdirs
index|[
name|i
index|]
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
operator||
name|S_IXUSR
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|thumb_subdirs
index|[
name|i
index|]
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_THUMB_ERROR
argument_list|,
name|GIMP_THUMB_ERROR_MKDIR
argument_list|,
name|_
argument_list|(
literal|"Failed to create thumbnail folder '%s'."
argument_list|)
argument_list|,
name|thumb_subdirs
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_thumb_name_from_uri (const gchar * uri,GimpThumbSize * size)
name|gimp_thumb_name_from_uri
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
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|strstr
argument_list|(
name|uri
argument_list|,
name|thumb_dir
argument_list|)
condition|)
return|return
name|NULL
return|;
name|name
operator|=
name|gimp_thumb_png_name
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|size
operator|!=
name|GIMP_THUMB_SIZE_FAIL
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|thumb_num_sizes
operator|&&
name|thumb_sizes
index|[
name|i
index|]
operator|<
operator|*
name|size
condition|;
name|i
operator|++
control|)
comment|/* nothing */
empty_stmt|;
if|if
condition|(
name|i
operator|==
name|thumb_num_sizes
condition|)
name|i
operator|--
expr_stmt|;
block|}
operator|*
name|size
operator|=
name|thumb_sizes
index|[
name|i
index|]
expr_stmt|;
return|return
name|g_build_filename
argument_list|(
name|thumb_subdirs
index|[
name|i
index|]
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_thumb_find_thumb (const gchar * uri,GimpThumbSize * size)
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
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|thumb_name
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|n
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_thumb_png_name
argument_list|(
name|uri
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|thumb_num_sizes
operator|&&
name|thumb_sizes
index|[
name|i
index|]
operator|<
operator|*
name|size
condition|;
name|i
operator|++
control|)
comment|/* do nothing */
empty_stmt|;
name|n
operator|=
name|i
expr_stmt|;
for|for
control|(
init|;
name|i
operator|<
name|thumb_num_sizes
condition|;
name|i
operator|++
control|)
block|{
name|thumb_name
operator|=
name|g_build_filename
argument_list|(
name|thumb_subdirs
index|[
name|i
index|]
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_thumb_file_test
argument_list|(
name|thumb_name
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
operator|*
name|size
operator|=
name|thumb_sizes
index|[
name|i
index|]
expr_stmt|;
return|return
name|thumb_name
return|;
block|}
name|g_free
argument_list|(
name|thumb_name
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
name|n
operator|-
literal|1
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
block|{
name|thumb_name
operator|=
name|g_build_filename
argument_list|(
name|thumb_subdirs
index|[
name|i
index|]
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_thumb_file_test
argument_list|(
name|thumb_name
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
operator|*
name|size
operator|=
name|thumb_sizes
index|[
name|i
index|]
expr_stmt|;
return|return
name|thumb_name
return|;
block|}
name|g_free
argument_list|(
name|thumb_name
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_thumb_file_test (const gchar * filename,gint64 * mtime,gint64 * size)
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
block|{
name|struct
name|stat
name|s
decl_stmt|;
if|if
condition|(
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|s
argument_list|)
operator|==
literal|0
operator|&&
operator|(
name|S_ISREG
argument_list|(
name|s
operator|.
name|st_mode
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|mtime
condition|)
operator|*
name|mtime
operator|=
name|s
operator|.
name|st_mtime
expr_stmt|;
if|if
condition|(
name|size
condition|)
operator|*
name|size
operator|=
name|s
operator|.
name|st_size
expr_stmt|;
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
specifier|static
name|void
DECL|function|gimp_thumb_exit (void)
name|gimp_thumb_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_free
argument_list|(
name|thumb_dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|thumb_sizes
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|thumb_num_sizes
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|thumb_subdirs
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|thumb_subdirs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|thumb_fail_subdir
argument_list|)
expr_stmt|;
name|thumb_num_sizes
operator|=
literal|0
expr_stmt|;
name|thumb_sizes
operator|=
name|NULL
expr_stmt|;
name|thumb_dir
operator|=
name|NULL
expr_stmt|;
name|thumb_subdirs
operator|=
name|NULL
expr_stmt|;
name|thumb_fail_subdir
operator|=
name|NULL
expr_stmt|;
name|gimp_thumb_initialized
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_thumb_png_name (const gchar * uri)
name|gimp_thumb_png_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
specifier|static
name|gchar
name|name
index|[
literal|40
index|]
decl_stmt|;
name|guchar
name|digest
index|[
literal|16
index|]
decl_stmt|;
name|guchar
name|n
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_md5_get_digest
argument_list|(
name|uri
argument_list|,
operator|-
literal|1
argument_list|,
name|digest
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|16
condition|;
name|i
operator|++
control|)
block|{
name|n
operator|=
operator|(
name|digest
index|[
name|i
index|]
operator|>>
literal|4
operator|)
operator|&
literal|0xF
expr_stmt|;
name|name
index|[
name|i
operator|*
literal|2
index|]
operator|=
operator|(
name|n
operator|>
literal|9
operator|)
condition|?
literal|'a'
operator|+
name|n
operator|-
literal|10
else|:
literal|'0'
operator|+
name|n
expr_stmt|;
name|n
operator|=
name|digest
index|[
name|i
index|]
operator|&
literal|0xF
expr_stmt|;
name|name
index|[
name|i
operator|*
literal|2
operator|+
literal|1
index|]
operator|=
operator|(
name|n
operator|>
literal|9
operator|)
condition|?
literal|'a'
operator|+
name|n
operator|-
literal|10
else|:
literal|'0'
operator|+
name|n
expr_stmt|;
block|}
name|strncpy
argument_list|(
name|name
operator|+
literal|32
argument_list|,
literal|".png"
argument_list|,
literal|5
argument_list|)
expr_stmt|;
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|name
return|;
block|}
end_function

end_unit

