begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Datafiles module copyight (C) 1996 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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

begin_ifndef
ifndef|#
directive|ifndef
name|S_ISDIR
end_ifndef

begin_define
DECL|macro|S_ISDIR (m)
define|#
directive|define
name|S_ISDIR
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFDIR)
end_define

begin_define
DECL|macro|S_ISREG (m)
define|#
directive|define
name|S_ISREG
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFREG)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IXUSR
end_ifndef

begin_define
DECL|macro|S_IXUSR
define|#
directive|define
name|S_IXUSR
value|_S_IEXEC
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* G_OS_WIN32 */
end_comment

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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_comment
comment|/*  * On Windows there is no concept like the Unix executable flag.  * There is a weak emulation provided by the MS C Runtime using file  * extensions (com, exe, cmd, bat). This needs to be extended to treat  * scripts (Python, Perl, ...) as executables, too. We use the PATHEXT  * variable, which is also used by cmd.exe.  */
end_comment

begin_function
specifier|static
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
name|g_strcasecmp
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
return|return
name|FALSE
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !G_OS_WIN32 */
end_comment

begin_define
DECL|macro|is_script (filename)
define|#
directive|define
name|is_script
parameter_list|(
name|filename
parameter_list|)
value|FALSE
end_define

begin_endif
endif|#
directive|endif
end_endif

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
name|GimpDatafileData
name|file_data
init|=
block|{
literal|0
block|}
decl_stmt|;
name|struct
name|stat
name|filestat
decl_stmt|;
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
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|err
decl_stmt|;
name|GDir
modifier|*
name|dir
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|dir_ent
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
name|file_data
operator|.
name|user_data
operator|=
name|user_data
expr_stmt|;
name|local_path
operator|=
name|g_strdup
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__EMX__
comment|/*    *  Change drive so opendir works.    */
if|if
condition|(
name|local_path
index|[
literal|1
index|]
operator|==
literal|':'
condition|)
block|{
name|_chdrive
argument_list|(
name|local_path
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|path
operator|=
name|gimp_path_parse
argument_list|(
name|local_path
argument_list|,
literal|16
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
name|dir
operator|=
name|g_dir_open
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
block|{
name|g_message
argument_list|(
literal|"error reading datafiles directory \"%s\""
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|filename
operator|=
name|g_build_filename
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
name|dir_ent
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Check the file and see that it is not a sub-directory */
name|err
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|filestat
argument_list|)
expr_stmt|;
name|file_data
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|file_data
operator|.
name|atime
operator|=
name|filestat
operator|.
name|st_atime
expr_stmt|;
name|file_data
operator|.
name|mtime
operator|=
name|filestat
operator|.
name|st_mtime
expr_stmt|;
name|file_data
operator|.
name|ctime
operator|=
name|filestat
operator|.
name|st_ctime
expr_stmt|;
if|if
condition|(
operator|!
name|err
condition|)
block|{
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
name|S_ISREG
argument_list|(
name|filestat
operator|.
name|st_mode
argument_list|)
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
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
name|S_ISDIR
argument_list|(
name|filestat
operator|.
name|st_mode
argument_list|)
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
argument_list|)
expr_stmt|;
block|}
ifndef|#
directive|ifndef
name|G_OS_WIN32
elseif|else
if|if
condition|(
operator|(
name|flags
operator|&
name|G_FILE_TEST_IS_SYMLINK
operator|)
operator|&&
name|S_ISLNK
argument_list|(
name|filestat
operator|.
name|st_mode
argument_list|)
condition|)
block|{
call|(
modifier|*
name|loader_func
call|)
argument_list|(
operator|&
name|file_data
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
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
operator|(
name|filestat
operator|.
name|st_mode
operator|&
name|S_IXUSR
operator|)
operator|||
operator|(
name|S_ISREG
argument_list|(
name|filestat
operator|.
name|st_mode
argument_list|)
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
argument_list|)
expr_stmt|;
block|}
block|}
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

end_unit

