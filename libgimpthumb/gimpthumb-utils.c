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
file|<errno.h>
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
file|"libgimpbase/gimpwin32-io.h"
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
name|gint
name|gimp_thumb_size
parameter_list|(
name|GimpThumbSize
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_thumb_png_lookup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|basedir
parameter_list|,
name|GimpThumbSize
modifier|*
name|size
parameter_list|)
function_decl|;
end_function_decl

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
DECL|variable|thumb_sizenames
specifier|static
specifier|const
name|gchar
modifier|*
modifier|*
name|thumb_sizenames
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

begin_comment
comment|/**  * gimp_thumb_init:  * @creator: an ASCII string that identifies the thumbnail creator  * @thumb_basedir: an absolute path or %NULL to use the default  *  * This function initializes the thumbnail system. It must be called  * before any other functions from libgimpthumb are used. You may call  * it more than once if you want to change the @thumb_basedir but if  * you do that, you should make sure that no thread is still using the  * library. Apart from this function, libgimpthumb is multi-thread  * safe.  *  * The @creator string must be 7bit ASCII and should contain the name  * of the software that creates the thumbnails. It is used to handle  * thumbnail creation failures. See the spec for more details.  *  * Usually you will pass %NULL for @thumb_basedir. Thumbnails will  * then be stored in the user's personal thumbnail directory as  * defined in the spec. If you wish to use libgimpthumb to store  * application-specific thumbnails, you can specify a different base  * directory here.  *  * Return value: %TRUE if the library was successfully initialized.  **/
end_comment

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
name|g_return_val_if_fail
argument_list|(
name|thumb_basedir
operator|==
name|NULL
operator|||
name|g_path_is_absolute
argument_list|(
name|thumb_basedir
argument_list|)
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
name|thumb_sizenames
operator|=
name|g_new
argument_list|(
specifier|const
name|gchar
operator|*
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
name|thumb_sizenames
index|[
name|i
index|]
operator|=
name|enum_value
operator|->
name|value_nick
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
name|g_type_class_unref
argument_list|(
name|enum_class
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

begin_comment
comment|/**  * gimp_thumb_get_thumb_dir:  * @size: a GimpThumbSize  *  * Retrieve the name of the thumbnail folder for a specific size. The  * returned pointer will become invalid if gimp_thumb_init() is used  * again. It must not be changed or freed.  *  * Return value: the thumbnail directory in the encoding of the filesystem  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_thumb_get_thumb_dir (GimpThumbSize size)
name|gimp_thumb_get_thumb_dir
parameter_list|(
name|GimpThumbSize
name|size
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|size
operator|=
name|gimp_thumb_size
argument_list|(
name|size
argument_list|)
expr_stmt|;
return|return
name|thumb_subdirs
index|[
name|size
index|]
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumb_get_thumb_dir_local:  * @dirname:  * @size: a GimpThumbSize  *  * Retrieve the name of the local thumbnail folder for a specific  * size.  Unlike gimp_thumb_get_thumb_dir() the returned string is not  * constant and should be free'd when it is not any longer needed.  *  * Return value: the thumbnail directory in the encoding of the filesystem  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_thumb_get_thumb_dir_local (const gchar * dirname,GimpThumbSize size)
name|gimp_thumb_get_thumb_dir_local
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|,
name|GimpThumbSize
name|size
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dirname
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|>
name|GIMP_THUMB_SIZE_FAIL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|size
operator|=
name|gimp_thumb_size
argument_list|(
name|size
argument_list|)
expr_stmt|;
return|return
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|thumb_sizenames
index|[
name|size
index|]
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumb_ensure_thumb_dir:  * @size: a GimpThumbSize  * @error: return location for possible errors  *  * This function checks if the directory that is required to store  * thumbnails for a particular @size exist and attempts to create it  * if necessary.  *  * You shouldn't have to call this function directly since  * gimp_thumbnail_save_thumb() and gimp_thumbnail_save_failure() will  * do this for you.  *  * Return value: %TRUE is the directory exists, %FALSE if it could not  *               be created  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_thumb_ensure_thumb_dir (GimpThumbSize size,GError ** error)
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
block|{
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
name|size
operator|=
name|gimp_thumb_size
argument_list|(
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|thumb_subdirs
index|[
name|size
index|]
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
return|return
name|TRUE
return|;
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
name|size
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
name|size
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
name|g_file_test
argument_list|(
name|thumb_subdirs
index|[
name|size
index|]
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
return|return
name|TRUE
return|;
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
name|size
index|]
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumb_ensure_thumb_dir_local:  * @dirname:  * @size: a GimpThumbSize  * @error: return location for possible errors  *  * This function checks if the directory that is required to store  * local thumbnails for a particular @size exist and attempts to  * create it if necessary.  *  * You shouldn't have to call this function directly since  * gimp_thumbnail_save_thumb_local() will do this for you.  *  * Return value: %TRUE is the directory exists, %FALSE if it could not  *               be created  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_thumb_ensure_thumb_dir_local (const gchar * dirname,GimpThumbSize size,GError ** error)
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
block|{
name|gchar
modifier|*
name|basedir
decl_stmt|;
name|gchar
modifier|*
name|subdir
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
name|dirname
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_path_is_absolute
argument_list|(
name|dirname
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|>
name|GIMP_THUMB_SIZE_FAIL
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
name|size
operator|=
name|gimp_thumb_size
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|subdir
operator|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
literal|".thumblocal"
argument_list|,
name|thumb_sizenames
index|[
name|size
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|subdir
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|subdir
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|basedir
operator|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
literal|".thumblocal"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|basedir
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
name|mkdir
argument_list|(
name|subdir
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
operator||
name|S_IXUSR
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|basedir
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|subdir
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|subdir
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
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
name|subdir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|subdir
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumb_name_from_uri:  * @uri: an escaped URI  * @size: a #GimpThumbSize  *  * Creates the name of the thumbnail file of the specified @size that  * belongs to an image file located at the given @uri.  *  * Return value: a newly allocated filename in the encoding of the  *               filesystem or %NULL if @uri points to the user's  *               thumbnail repository.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_thumb_name_from_uri (const gchar * uri,GimpThumbSize size)
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
block|{
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|size
operator|=
name|gimp_thumb_size
argument_list|(
name|size
argument_list|)
expr_stmt|;
return|return
name|g_build_filename
argument_list|(
name|thumb_subdirs
index|[
name|size
index|]
argument_list|,
name|gimp_thumb_png_name
argument_list|(
name|uri
argument_list|)
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumb_name_from_uri_local:  * @uri: an escaped URI  * @size: a #GimpThumbSize  *  * Creates the name of a local thumbnail file of the specified @size  * that belongs to an image file located at the given @uri. Local  * thumbnails have been introduced with version 0.7 of the spec.  *  * Return value: a newly allocated filename in the encoding of the  *               filesystem or %NULL if @uri is a remote file or  *               points to the user's thumbnail repository.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_thumb_name_from_uri_local (const gchar * uri,GimpThumbSize size)
name|gimp_thumb_name_from_uri_local
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpThumbSize
name|size
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|result
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|>
name|GIMP_THUMB_SIZE_FAIL
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
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|baseuri
init|=
name|strrchr
argument_list|(
name|uri
argument_list|,
literal|'/'
argument_list|)
decl_stmt|;
if|if
condition|(
name|baseuri
operator|&&
name|baseuri
index|[
literal|0
index|]
operator|&&
name|baseuri
index|[
literal|1
index|]
condition|)
block|{
name|gchar
modifier|*
name|dirname
init|=
name|g_path_get_dirname
argument_list|(
name|filename
argument_list|)
decl_stmt|;
name|gint
name|i
init|=
name|gimp_thumb_size
argument_list|(
name|size
argument_list|)
decl_stmt|;
name|result
operator|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
literal|".thumblocal"
argument_list|,
name|thumb_sizenames
index|[
name|i
index|]
argument_list|,
name|gimp_thumb_png_name
argument_list|(
name|uri
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumb_find_thumb:  * @uri: an escaped URI  * @size: pointer to a #GimpThumbSize  *  * This function attempts to locate a thumbnail for the given  * @uri. First it tries the size that is stored at @size. If no  * thumbnail of that size is found, it will look for a larger  * thumbnail, then falling back to a smaller size.  *  * If the user's thumbnail repository doesn't provide a thumbnail but  * a local thumbnail repository exists for the folder the image is  * located in, the same search is done among the local thumbnails (if  * there are any).  *  * If a thumbnail is found, it's size is written to the variable  * pointer to by @size and the file location is returned.  *  * Return value: a newly allocated string in the encoding of the  *               filesystem or %NULL if no thumbnail for @uri was found  **/
end_comment

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
name|gchar
modifier|*
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|size
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|*
name|size
operator|>
name|GIMP_THUMB_SIZE_FAIL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_thumb_png_lookup
argument_list|(
name|gimp_thumb_png_name
argument_list|(
name|uri
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|result
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|baseuri
init|=
name|strrchr
argument_list|(
name|uri
argument_list|,
literal|'/'
argument_list|)
decl_stmt|;
if|if
condition|(
name|baseuri
operator|&&
name|baseuri
index|[
literal|0
index|]
operator|&&
name|baseuri
index|[
literal|1
index|]
condition|)
block|{
name|gchar
modifier|*
name|dirname
init|=
name|g_path_get_dirname
argument_list|(
name|filename
argument_list|)
decl_stmt|;
name|result
operator|=
name|gimp_thumb_png_lookup
argument_list|(
name|gimp_thumb_png_name
argument_list|(
name|baseuri
operator|+
literal|1
argument_list|)
argument_list|,
name|dirname
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumb_file_test:  * @filename: a filename in the encoding of the filesystem  * @mtime: return location for modification time  * @size: return location for file size  * @err_no: return location for system "errno"  *  * This is a convenience and portability wrapper around stat(). It  * checks if the given @filename exists and returns modification time  * and file size in 64bit integer values.  *  * Return value: The type of the file, or #GIMP_THUMB_FILE_TYPE_NONE if  *               the file doesn't exist.  **/
end_comment

begin_function
name|GimpThumbFileType
DECL|function|gimp_thumb_file_test (const gchar * filename,gint64 * mtime,gint64 * size,gint * err_no)
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
block|{
name|struct
name|stat
name|s
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|err_no
condition|)
operator|*
name|err_no
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|S_ISREG
argument_list|(
name|s
operator|.
name|st_mode
argument_list|)
condition|)
block|{
return|return
name|GIMP_THUMB_FILE_TYPE_REGULAR
return|;
block|}
elseif|else
if|if
condition|(
name|S_ISDIR
argument_list|(
name|s
operator|.
name|st_mode
argument_list|)
condition|)
block|{
return|return
name|GIMP_THUMB_FILE_TYPE_FOLDER
return|;
block|}
return|return
name|GIMP_THUMB_FILE_TYPE_SPECIAL
return|;
block|}
if|if
condition|(
name|mtime
condition|)
operator|*
name|mtime
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|size
condition|)
operator|*
name|size
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|err_no
condition|)
operator|*
name|err_no
operator|=
name|errno
expr_stmt|;
return|return
name|GIMP_THUMB_FILE_TYPE_NONE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_thumbs_delete_for_uri:  * @uri: an escaped URI  *  * Deletes all thumbnails for the image file specified by @uri from the  * user's thumbnail repository.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_thumbs_delete_for_uri (const gchar * uri)
name|gimp_thumbs_delete_for_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
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
name|gchar
modifier|*
name|filename
init|=
name|gimp_thumb_name_from_uri
argument_list|(
name|uri
argument_list|,
name|thumb_sizes
index|[
name|i
index|]
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|unlink
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
block|}
end_function

begin_comment
comment|/**  * gimp_thumbs_delete_for_uri_local:  * @uri: an escaped URI  *  * Deletes all thumbnails for the image file specified by @uri from  * the local thumbnail repository.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_thumbs_delete_for_uri_local (const gchar * uri)
name|gimp_thumbs_delete_for_uri_local
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_thumb_initialized
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
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
name|gchar
modifier|*
name|filename
init|=
name|gimp_thumb_name_from_uri_local
argument_list|(
name|uri
argument_list|,
name|thumb_sizes
index|[
name|i
index|]
argument_list|)
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|unlink
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
name|g_free
argument_list|(
name|thumb_sizenames
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
name|thumb_sizenames
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
name|gint
DECL|function|gimp_thumb_size (GimpThumbSize size)
name|gimp_thumb_size
parameter_list|(
name|GimpThumbSize
name|size
parameter_list|)
block|{
name|gint
name|i
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|size
operator|>
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
return|return
name|i
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_thumb_png_lookup (const gchar * name,const gchar * basedir,GimpThumbSize * size)
name|gimp_thumb_png_lookup
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|basedir
parameter_list|,
name|GimpThumbSize
modifier|*
name|size
parameter_list|)
block|{
name|gchar
modifier|*
name|thumb_name
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|subdirs
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|n
decl_stmt|;
if|if
condition|(
name|basedir
condition|)
block|{
name|gchar
modifier|*
name|dir
init|=
name|g_build_filename
argument_list|(
name|basedir
argument_list|,
literal|".thumblocal"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|basedir
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|subdirs
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
name|thumb_num_sizes
argument_list|)
expr_stmt|;
name|subdirs
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
comment|/*  GIMP_THUMB_SIZE_FAIL  */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|thumb_num_sizes
condition|;
name|i
operator|++
control|)
name|subdirs
index|[
name|i
index|]
operator|=
name|g_build_filename
argument_list|(
name|dir
argument_list|,
name|thumb_sizenames
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|subdirs
operator|=
name|thumb_subdirs
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|subdirs
condition|)
return|return
name|NULL
return|;
name|i
operator|=
name|n
operator|=
name|gimp_thumb_size
argument_list|(
operator|*
name|size
argument_list|)
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
if|if
condition|(
operator|!
name|subdirs
index|[
name|i
index|]
condition|)
continue|continue;
name|thumb_name
operator|=
name|g_build_filename
argument_list|(
name|subdirs
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
argument_list|,
name|NULL
argument_list|)
operator|==
name|GIMP_THUMB_FILE_TYPE_REGULAR
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
goto|goto
name|finish
goto|;
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
if|if
condition|(
operator|!
name|subdirs
index|[
name|i
index|]
condition|)
continue|continue;
name|thumb_name
operator|=
name|g_build_filename
argument_list|(
name|subdirs
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
argument_list|,
name|NULL
argument_list|)
operator|==
name|GIMP_THUMB_FILE_TYPE_REGULAR
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
goto|goto
name|finish
goto|;
block|}
name|g_free
argument_list|(
name|thumb_name
argument_list|)
expr_stmt|;
block|}
name|thumb_name
operator|=
name|NULL
expr_stmt|;
name|finish
label|:
if|if
condition|(
name|basedir
condition|)
block|{
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
name|subdirs
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|subdirs
argument_list|)
expr_stmt|;
block|}
return|return
name|thumb_name
return|;
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

