begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Datafiles module copyight (C) 1996 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafiles.h"
end_include

begin_include
include|#
directive|include
file|"gimpenv.h"
end_include

begin_comment
comment|/**  * SECTION: gimpdatafiles  * @title: gimpdatafiles  * @short_description: Functions to handle GIMP data files.  *  * Functions to handle GIMP data files.  **/
end_comment

begin_function_decl
specifier|static
specifier|inline
name|gboolean
name|is_script
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_datafiles_check_extension (const gchar * filename,const gchar * extension)
name|gimp_datafiles_check_extension
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
block|{
name|gint
name|name_len
decl_stmt|;
name|gint
name|ext_len
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
name|g_return_val_if_fail
argument_list|(
name|extension
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|name_len
operator|=
name|strlen
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|ext_len
operator|=
name|strlen
argument_list|(
name|extension
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|name_len
operator|&&
name|ext_len
operator|&&
operator|(
name|name_len
operator|>
name|ext_len
operator|)
operator|)
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|g_ascii_strcasecmp
argument_list|(
operator|&
name|filename
index|[
name|name_len
operator|-
name|ext_len
index|]
argument_list|,
name|extension
argument_list|)
operator|==
literal|0
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_datafiles_read_directories (const gchar * path_str,GFileTest flags,GimpDatafileLoaderFunc loader_func,gpointer user_data)
name|gimp_datafiles_read_directories
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GFileTest
name|flags
parameter_list|,
name|GimpDatafileLoaderFunc
name|loader_func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gchar
modifier|*
name|local_path
decl_stmt|;
name|GList
modifier|*
name|path
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|path_str
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|loader_func
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|local_path
operator|=
name|g_strdup
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_path_parse
argument_list|(
name|local_path
argument_list|,
literal|256
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|path
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|dirname
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
name|dir
operator|=
name|g_dir_open
argument_list|(
name|dirname
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|dir_ent
decl_stmt|;
while|while
condition|(
operator|(
name|dir_ent
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GFileInfo
modifier|*
name|info
decl_stmt|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|dir_ent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|info
operator|=
name|g_file_query_info
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_IS_HIDDEN
literal|","
name|G_FILE_ATTRIBUTE_STANDARD_TYPE
literal|","
name|G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE
literal|","
literal|"time::*"
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
condition|)
block|{
name|GimpDatafileData
name|file_data
decl_stmt|;
name|GFileType
name|file_type
decl_stmt|;
name|file_data
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|file_data
operator|.
name|dirname
operator|=
name|dirname
expr_stmt|;
name|file_data
operator|.
name|basename
operator|=
name|dir_ent
expr_stmt|;
name|file_data
operator|.
name|atime
operator|=
name|g_file_info_get_attribute_uint64
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_TIME_ACCESS
argument_list|)
expr_stmt|;
name|file_data
operator|.
name|mtime
operator|=
name|g_file_info_get_attribute_uint64
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_TIME_MODIFIED
argument_list|)
expr_stmt|;
name|file_data
operator|.
name|ctime
operator|=
name|g_file_info_get_attribute_uint64
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_TIME_CREATED
argument_list|)
expr_stmt|;
name|file_type
operator|=
name|g_file_info_get_file_type
argument_list|(
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_info_get_is_hidden
argument_list|(
name|info
argument_list|)
condition|)
block|{
comment|/* do nothing */
block|}
elseif|else
if|if
condition|(
name|flags
operator|&
name|G_FILE_TEST_EXISTS
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|flags
operator|&
name|G_FILE_TEST_IS_REGULAR
operator|)
operator|&&
operator|(
name|file_type
operator|==
name|G_FILE_TYPE_REGULAR
operator|)
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|flags
operator|&
name|G_FILE_TEST_IS_DIR
operator|)
operator|&&
operator|(
name|file_type
operator|==
name|G_FILE_TYPE_DIRECTORY
operator|)
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|flags
operator|&
name|G_FILE_TEST_IS_SYMLINK
operator|)
operator|&&
operator|(
name|file_type
operator|==
name|G_FILE_TYPE_SYMBOLIC_LINK
operator|)
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|(
name|flags
operator|&
name|G_FILE_TEST_IS_EXECUTABLE
operator|)
operator|&&
operator|(
name|g_file_info_get_attribute_boolean
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE
argument_list|)
operator|||
operator|(
operator|(
name|file_type
operator|==
name|G_FILE_TYPE_REGULAR
operator|)
operator|&&
name|is_script
argument_list|(
name|filename
argument_list|)
operator|)
operator|)
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|local_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
specifier|inline
name|gboolean
DECL|function|is_script (const gchar * filename)
name|is_script
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* On Windows there is no concept like the Unix executable flag.    * There is a weak emulation provided by the MS C Runtime using file    * extensions (com, exe, cmd, bat). This needs to be extended to treat    * scripts (Python, Perl, ...) as executables, too. We use the PATHEXT    * variable, which is also used by cmd.exe.    */
specifier|static
name|gchar
modifier|*
modifier|*
name|exts
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ext
init|=
name|strrchr
argument_list|(
name|filename
argument_list|,
literal|'.'
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|pathext
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|exts
operator|==
name|NULL
condition|)
block|{
name|pathext
operator|=
name|g_getenv
argument_list|(
literal|"PATHEXT"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pathext
operator|!=
name|NULL
condition|)
block|{
name|exts
operator|=
name|g_strsplit
argument_list|(
name|pathext
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
literal|100
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|exts
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|exts
index|[
literal|0
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|i
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|exts
index|[
name|i
index|]
operator|!=
name|NULL
condition|)
block|{
if|if
condition|(
name|g_ascii_strcasecmp
argument_list|(
name|ext
argument_list|,
name|exts
index|[
name|i
index|]
argument_list|)
operator|==
literal|0
condition|)
return|return
name|TRUE
return|;
name|i
operator|++
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* G_OS_WIN32 */
return|return
name|FALSE
return|;
block|}
end_function

end_unit

