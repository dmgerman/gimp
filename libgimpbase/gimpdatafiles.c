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
file|<glib.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_DIRENT_H
end_ifdef

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_comment
comment|/* (Re)define S_IXUSR as _S_IREAD to get scripts, too. */
end_comment

begin_undef
undef|#
directive|undef
name|S_IXUSR
end_undef

begin_define
DECL|macro|S_IXUSR
define|#
directive|define
name|S_IXUSR
value|_S_IREAD
end_define

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
file|"datafiles.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"general.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_comment
comment|/***** Functions *****/
end_comment

begin_comment
comment|/*****/
end_comment

begin_decl_stmt
DECL|variable|filestat_valid
specifier|static
name|int
name|filestat_valid
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|filestat
specifier|static
name|struct
name|stat
name|filestat
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|datafiles_read_directories (char * path_str,datafile_loader_t loader_func,int flags)
name|datafiles_read_directories
parameter_list|(
name|char
modifier|*
name|path_str
parameter_list|,
name|datafile_loader_t
name|loader_func
parameter_list|,
name|int
name|flags
parameter_list|)
block|{
name|char
modifier|*
name|home
decl_stmt|;
name|char
modifier|*
name|local_path
decl_stmt|;
name|char
modifier|*
name|path
decl_stmt|;
name|char
modifier|*
name|filename
decl_stmt|;
name|char
modifier|*
name|token
decl_stmt|;
name|char
modifier|*
name|next_token
decl_stmt|;
name|int
name|err
decl_stmt|;
name|DIR
modifier|*
name|dir
decl_stmt|;
name|struct
name|dirent
modifier|*
name|dir_ent
decl_stmt|;
if|if
condition|(
name|path_str
operator|==
name|NULL
condition|)
return|return;
comment|/* Set local path to contain temp_path, where (supposedly)    * there may be working files.    */
name|home
operator|=
name|g_get_home_dir
argument_list|()
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
comment|/* Search through all directories in the local path */
name|next_token
operator|=
name|local_path
expr_stmt|;
name|token
operator|=
name|xstrsep
argument_list|(
operator|&
name|next_token
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|)
expr_stmt|;
while|while
condition|(
name|token
condition|)
block|{
if|if
condition|(
operator|*
name|token
operator|==
literal|'~'
condition|)
block|{
name|path
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|home
argument_list|)
operator|+
name|strlen
argument_list|(
name|token
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|path
argument_list|,
literal|"%s%s"
argument_list|,
name|home
argument_list|,
name|token
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|path
operator|=
name|g_malloc
argument_list|(
name|strlen
argument_list|(
name|token
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|path
argument_list|,
name|token
argument_list|)
expr_stmt|;
block|}
comment|/* else */
comment|/* Check if directory exists and if it has any items in it */
name|err
operator|=
name|stat
argument_list|(
name|path
argument_list|,
operator|&
name|filestat
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|err
operator|&&
name|S_ISDIR
argument_list|(
name|filestat
operator|.
name|st_mode
argument_list|)
condition|)
block|{
if|if
condition|(
name|path
index|[
name|strlen
argument_list|(
name|path
argument_list|)
operator|-
literal|1
index|]
operator|!=
name|G_DIR_SEPARATOR
condition|)
name|strcat
argument_list|(
name|path
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
comment|/* Open directory */
name|dir
operator|=
name|opendir
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
name|g_message
argument_list|(
literal|"error reading datafiles directory \"%s\""
argument_list|,
name|path
argument_list|)
expr_stmt|;
else|else
block|{
while|while
condition|(
operator|(
name|dir_ent
operator|=
name|readdir
argument_list|(
name|dir
argument_list|)
operator|)
condition|)
block|{
name|filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s"
argument_list|,
name|path
argument_list|,
name|dir_ent
operator|->
name|d_name
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
if|if
condition|(
operator|!
name|err
operator|&&
name|S_ISREG
argument_list|(
name|filestat
operator|.
name|st_mode
argument_list|)
operator|&&
operator|(
operator|!
operator|(
name|flags
operator|&
name|MODE_EXECUTABLE
operator|)
operator|||
operator|(
name|filestat
operator|.
name|st_mode
operator|&
name|S_IXUSR
operator|)
operator|)
condition|)
block|{
name|filestat_valid
operator|=
literal|1
expr_stmt|;
call|(
modifier|*
name|loader_func
call|)
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filestat_valid
operator|=
literal|0
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
comment|/* while */
name|closedir
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
comment|/* else */
block|}
comment|/* if */
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|token
operator|=
name|xstrsep
argument_list|(
operator|&
name|next_token
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|)
expr_stmt|;
block|}
comment|/* while */
name|g_free
argument_list|(
name|local_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* datafiles_read_directories */
end_comment

begin_function
name|time_t
DECL|function|datafile_atime ()
name|datafile_atime
parameter_list|()
block|{
if|if
condition|(
name|filestat_valid
condition|)
return|return
name|filestat
operator|.
name|st_atime
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|time_t
DECL|function|datafile_mtime ()
name|datafile_mtime
parameter_list|()
block|{
if|if
condition|(
name|filestat_valid
condition|)
return|return
name|filestat
operator|.
name|st_mtime
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|time_t
DECL|function|datafile_ctime ()
name|datafile_ctime
parameter_list|()
block|{
if|if
condition|(
name|filestat_valid
condition|)
return|return
name|filestat
operator|.
name|st_ctime
return|;
return|return
literal|0
return|;
block|}
end_function

end_unit

