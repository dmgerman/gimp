begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  *  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1999 Tor Lillqvist  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU Lesser General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpenv.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_define
DECL|macro|STRICT
define|#
directive|define
name|STRICT
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_comment
comment|/* For GetModuleFileName */
end_comment

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|S_IWUSR
end_ifndef

begin_define
DECL|macro|S_IWUSR
define|#
directive|define
name|S_IWUSR
value|_S_IWRITE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IWGRP
end_ifndef

begin_define
DECL|macro|S_IWGRP
define|#
directive|define
name|S_IWGRP
value|(_S_IWRITE>>3)
end_define

begin_define
DECL|macro|S_IWOTH
define|#
directive|define
name|S_IWOTH
value|(_S_IWRITE>>6)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_ISDIR
end_ifndef

begin_define
DECL|macro|__S_ISTYPE (mode,mask)
define|#
directive|define
name|__S_ISTYPE
parameter_list|(
name|mode
parameter_list|,
name|mask
parameter_list|)
value|(((mode)& _S_IFMT) == (mask))
end_define

begin_define
DECL|macro|S_ISDIR (mode)
define|#
directive|define
name|S_ISDIR
parameter_list|(
name|mode
parameter_list|)
value|__S_ISTYPE((mode), _S_IFDIR)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|uid_t
define|#
directive|define
name|uid_t
value|gint
end_define

begin_define
DECL|macro|gid_t
define|#
directive|define
name|gid_t
value|gint
end_define

begin_define
DECL|macro|geteuid ()
define|#
directive|define
name|geteuid
parameter_list|()
value|0
end_define

begin_define
DECL|macro|getegid ()
define|#
directive|define
name|getegid
parameter_list|()
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__EMX__
end_ifdef

begin_function_decl
specifier|extern
specifier|const
name|char
modifier|*
name|__XOS2RedirRoot
parameter_list|(
specifier|const
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/**  * gimp_directory:  *  * Returns the user-specific GIMP settings directory. If the environment   * variable GIMP_DIRECTORY exists, it is used. If it is an absolute path,   * it is used as is.  If it is a relative path, it is taken to be a   * subdirectory of the home directory. If it is relative path, and no home   * directory can be determined, it is taken to be a subdirectory of  * gimp_data_directory().  *  * The usual case is that no GIMP_DIRECTORY environment variable exists,   * and then we use the GIMPDIR subdirectory of the home directory. If no   * home directory exists, we use a per-user subdirectory of  * gimp_data_directory().  * In any case, we always return some non-empty string, whether it  * corresponds to an existing directory or not.  *  * The returned string is allocated just once, and should *NOT* be  * freed with g_free().  *  * Returns: The user-specific GIMP settings directory.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_directory (void)
name|gimp_directory
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|gimp_dir
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|env_gimp_dir
decl_stmt|;
name|gchar
modifier|*
name|home_dir
decl_stmt|;
name|gchar
modifier|*
name|home_dir_sep
decl_stmt|;
if|if
condition|(
name|gimp_dir
operator|!=
name|NULL
condition|)
return|return
name|gimp_dir
return|;
name|env_gimp_dir
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_DIRECTORY"
argument_list|)
expr_stmt|;
name|home_dir
operator|=
name|g_get_home_dir
argument_list|()
expr_stmt|;
if|if
condition|(
name|home_dir
operator|!=
name|NULL
operator|&&
name|home_dir
index|[
name|strlen
argument_list|(
name|home_dir
argument_list|)
operator|-
literal|1
index|]
operator|!=
name|G_DIR_SEPARATOR
condition|)
name|home_dir_sep
operator|=
name|G_DIR_SEPARATOR_S
expr_stmt|;
else|else
name|home_dir_sep
operator|=
literal|""
expr_stmt|;
if|if
condition|(
name|NULL
operator|!=
name|env_gimp_dir
condition|)
block|{
if|if
condition|(
name|g_path_is_absolute
argument_list|(
name|env_gimp_dir
argument_list|)
condition|)
name|gimp_dir
operator|=
name|g_strdup
argument_list|(
name|env_gimp_dir
argument_list|)
expr_stmt|;
else|else
block|{
if|if
condition|(
name|NULL
operator|!=
name|home_dir
condition|)
block|{
name|gimp_dir
operator|=
name|g_strconcat
argument_list|(
name|home_dir
argument_list|,
name|home_dir_sep
argument_list|,
name|env_gimp_dir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_dir
operator|=
name|g_strconcat
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|env_gimp_dir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
ifdef|#
directive|ifdef
name|__EMX__
name|gimp_dir
operator|=
name|g_strdup
argument_list|(
name|__XOS2RedirRoot
argument_list|(
name|GIMPDIR
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|gimp_dir
return|;
endif|#
directive|endif
if|if
condition|(
name|NULL
operator|!=
name|home_dir
condition|)
block|{
name|gimp_dir
operator|=
name|g_strconcat
argument_list|(
name|home_dir
argument_list|,
name|home_dir_sep
argument_list|,
name|GIMPDIR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_message
argument_list|(
literal|"warning: no home directory."
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_dir
operator|=
name|g_strconcat
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|GIMPDIR
argument_list|,
literal|"."
argument_list|,
name|g_get_user_name
argument_list|()
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|gimp_dir
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_personal_rc_file:  * @basename: The basename of a rc_file.  *  * Returns the name of a file in the user-specific GIMP settings directory.  *  * The returned string is allocated dynamically and *SHOULD* be freed  * with g_free() after use.  *  * Returns: The name of a file in the user-specific GIMP settings directory.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_personal_rc_file (gchar * basename)
name|gimp_personal_rc_file
parameter_list|(
name|gchar
modifier|*
name|basename
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_directory:  *  * Returns the top directory for GIMP data. If the environment variable   * GIMP_DATADIR exists, that is used.  It should be an absolute pathname.  * Otherwise, on Unix the compile-time defined directory is used.  On  * Win32, the installation directory as deduced from the executable's  * name is used.  *  * The returned string is allocated just once, and should *NOT* be  * freed with g_free().  *  * Returns: The top directory for GIMP data.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_data_directory (void)
name|gimp_data_directory
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|gimp_data_dir
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|env_gimp_data_dir
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_data_dir
operator|!=
name|NULL
condition|)
return|return
name|gimp_data_dir
return|;
name|env_gimp_data_dir
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_DATADIR"
argument_list|)
expr_stmt|;
if|if
condition|(
name|NULL
operator|!=
name|env_gimp_data_dir
condition|)
block|{
if|if
condition|(
operator|!
name|g_path_is_absolute
argument_list|(
name|env_gimp_data_dir
argument_list|)
condition|)
name|g_error
argument_list|(
literal|"GIMP_DATADIR environment variable should be an absolute path."
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|__EMX__
name|gimp_data_dir
operator|=
name|g_strdup
argument_list|(
name|env_gimp_data_dir
argument_list|)
expr_stmt|;
else|#
directive|else
name|gimp_data_dir
operator|=
name|g_strdup
argument_list|(
name|__XOS2RedirRoot
argument_list|(
name|env_gimp_data_dir
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
else|else
block|{
ifndef|#
directive|ifndef
name|G_OS_WIN32
ifndef|#
directive|ifndef
name|__EMX__
name|gimp_data_dir
operator|=
name|DATADIR
expr_stmt|;
else|#
directive|else
name|gimp_data_dir
operator|=
name|g_strdup
argument_list|(
name|__XOS2RedirRoot
argument_list|(
name|DATADIR
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
else|#
directive|else
comment|/* Figure it out from the executable name */
name|gchar
name|filename
index|[
name|MAX_PATH
index|]
decl_stmt|;
name|gchar
modifier|*
name|sep1
decl_stmt|,
modifier|*
name|sep2
decl_stmt|;
if|if
condition|(
name|GetModuleFileName
argument_list|(
name|NULL
argument_list|,
name|filename
argument_list|,
sizeof|sizeof
argument_list|(
name|filename
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
name|g_error
argument_list|(
literal|"GetModuleFilename failed\n"
argument_list|)
expr_stmt|;
comment|/* If the executable file name is of the format        *<foobar>\bin\gimp.exe of<foobar>\plug-ins\filter.exe, * use        *<foobar>. Otherwise, use the directory where the executable        * is.        */
name|sep1
operator|=
name|strrchr
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR
argument_list|)
expr_stmt|;
operator|*
name|sep1
operator|=
literal|'\0'
expr_stmt|;
name|sep2
operator|=
name|strrchr
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR
argument_list|)
expr_stmt|;
if|if
condition|(
name|sep2
operator|!=
name|NULL
condition|)
block|{
if|if
condition|(
name|g_strcasecmp
argument_list|(
name|sep2
operator|+
literal|1
argument_list|,
literal|"bin"
argument_list|)
operator|==
literal|0
operator|||
name|g_strcasecmp
argument_list|(
name|sep2
operator|+
literal|1
argument_list|,
literal|"plug-ins"
argument_list|)
operator|==
literal|0
condition|)
operator|*
name|sep2
operator|=
literal|'\0'
expr_stmt|;
block|}
name|gimp_data_dir
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
return|return
name|gimp_data_dir
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_sysconf_directory:  *  * Returns the top directory for GIMP config files. If the environment  * variable GIMP_SYSCONFDIR exists, that is used.  It should be an  * absolute pathname.  Otherwise, on Unix the compile-time defined  * directory is used.  On Win32, the installation directory as deduced  * from the executable's name is used.  *  * The returned string is allocated just once, and should *NOT* be  * freed with g_free().  *  * Returns: The top directory for GIMP config files.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_sysconf_directory (void)
name|gimp_sysconf_directory
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|gimp_sysconf_dir
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|env_gimp_sysconf_dir
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_sysconf_dir
operator|!=
name|NULL
condition|)
return|return
name|gimp_sysconf_dir
return|;
name|env_gimp_sysconf_dir
operator|=
name|g_getenv
argument_list|(
literal|"GIMP_SYSCONFDIR"
argument_list|)
expr_stmt|;
if|if
condition|(
name|NULL
operator|!=
name|env_gimp_sysconf_dir
condition|)
block|{
if|if
condition|(
operator|!
name|g_path_is_absolute
argument_list|(
name|env_gimp_sysconf_dir
argument_list|)
condition|)
name|g_error
argument_list|(
literal|"GIMP_SYSCONFDIR environment variable should be an absolute path."
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|__EMX__
name|gimp_sysconf_dir
operator|=
name|g_strdup
argument_list|(
name|env_gimp_sysconf_dir
argument_list|)
expr_stmt|;
else|#
directive|else
name|gimp_sysconf_dir
operator|=
name|g_strdup
argument_list|(
name|__XOS2RedirRoot
argument_list|(
name|env_gimp_sysconf_dir
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
else|else
block|{
ifndef|#
directive|ifndef
name|G_OS_WIN32
ifndef|#
directive|ifndef
name|__EMX__
name|gimp_sysconf_dir
operator|=
name|SYSCONFDIR
expr_stmt|;
else|#
directive|else
name|gimp_sysconf_dir
operator|=
name|g_strdup
argument_list|(
name|__XOS2RedirRoot
argument_list|(
name|SYSCONFDIR
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
else|#
directive|else
comment|/* Figure it out from the executable name */
name|gchar
name|filename
index|[
name|MAX_PATH
index|]
decl_stmt|;
name|gchar
modifier|*
name|sep1
decl_stmt|,
modifier|*
name|sep2
decl_stmt|;
if|if
condition|(
name|GetModuleFileName
argument_list|(
name|NULL
argument_list|,
name|filename
argument_list|,
sizeof|sizeof
argument_list|(
name|filename
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
name|g_error
argument_list|(
literal|"GetModuleFilename failed\n"
argument_list|)
expr_stmt|;
comment|/* If the executable file name is of the format        *<foobar>\bin\gimp.exe of<foobar>\plug-ins\filter.exe, * use        *<foobar>. Otherwise, use the directory where the executable        * is.        */
name|sep1
operator|=
name|strrchr
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR
argument_list|)
expr_stmt|;
operator|*
name|sep1
operator|=
literal|'\0'
expr_stmt|;
name|sep2
operator|=
name|strrchr
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR
argument_list|)
expr_stmt|;
if|if
condition|(
name|sep2
operator|!=
name|NULL
condition|)
block|{
if|if
condition|(
name|g_strcasecmp
argument_list|(
name|sep2
operator|+
literal|1
argument_list|,
literal|"bin"
argument_list|)
operator|==
literal|0
operator|||
name|g_strcasecmp
argument_list|(
name|sep2
operator|+
literal|1
argument_list|,
literal|"plug-ins"
argument_list|)
operator|==
literal|0
condition|)
operator|*
name|sep2
operator|=
literal|'\0'
expr_stmt|;
block|}
name|gimp_sysconf_dir
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
return|return
name|gimp_sysconf_dir
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gtkrc:  *  * Returns the name of the GIMP's application-specific gtkrc file.  *  * The returned string is allocated just once, and should *NOT* be  * freed with g_free().  *  * Returns: The name of the GIMP's application-specific gtkrc file.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_gtkrc (void)
name|gimp_gtkrc
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|gimp_gtkrc_filename
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gimp_gtkrc_filename
operator|!=
name|NULL
condition|)
return|return
name|gimp_gtkrc_filename
return|;
name|gimp_gtkrc_filename
operator|=
name|g_strconcat
argument_list|(
name|gimp_sysconf_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
literal|"gtkrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_gtkrc_filename
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_parse:  * @path: A list of directories separated by #G_SEARCHPATH_SEPARATOR.  * @max_paths: The maximum number of directories to return.  * @check: #TRUE if you want the directories to be checked.  * @check_failed: Returns a #GList of path elements for which the  *                check failed. Each list element is guaranteed  *		  to end with a #G_PATH_SEPARATOR.  *  * Returns: A #GList of all directories in @path. Each list element  *	    is guaranteed to end with a #G_PATH_SEPARATOR.  */
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_path_parse (gchar * path,gint max_paths,gboolean check,GList ** check_failed)
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
block|{
name|gchar
modifier|*
name|home
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|patharray
decl_stmt|;
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|fail_list
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|struct
name|stat
name|filestat
decl_stmt|;
name|gint
name|err
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|path
operator|||
operator|!
operator|*
name|path
operator|||
name|max_paths
operator|<
literal|1
operator|||
name|max_paths
operator|>
literal|256
condition|)
return|return
name|NULL
return|;
name|home
operator|=
name|g_get_home_dir
argument_list|()
expr_stmt|;
name|patharray
operator|=
name|g_strsplit
argument_list|(
name|path
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
name|max_paths
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
name|max_paths
condition|;
name|i
operator|++
control|)
block|{
name|GString
modifier|*
name|dir
decl_stmt|;
if|if
condition|(
operator|!
name|patharray
index|[
name|i
index|]
condition|)
break|break;
ifndef|#
directive|ifndef
name|G_OS_WIN32
if|if
condition|(
operator|*
name|patharray
index|[
name|i
index|]
operator|==
literal|'~'
condition|)
block|{
name|dir
operator|=
name|g_string_new
argument_list|(
name|home
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|dir
argument_list|,
name|patharray
index|[
name|i
index|]
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
endif|#
directive|endif
block|{
name|dir
operator|=
name|g_string_new
argument_list|(
name|patharray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|__EMX__
name|_fnslashify
argument_list|(
name|dir
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|check
condition|)
block|{
comment|/*  check if directory exists  */
name|err
operator|=
name|stat
argument_list|(
name|dir
operator|->
name|str
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
name|dir
operator|->
name|str
index|[
name|dir
operator|->
name|len
operator|-
literal|1
index|]
operator|!=
name|G_DIR_SEPARATOR
condition|)
name|g_string_append_c
argument_list|(
name|dir
argument_list|,
name|G_DIR_SEPARATOR
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|err
condition|)
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|dir
operator|->
name|str
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|check_failed
condition|)
name|fail_list
operator|=
name|g_list_prepend
argument_list|(
name|fail_list
argument_list|,
name|g_strdup
argument_list|(
name|dir
operator|->
name|str
argument_list|)
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|dir
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|patharray
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_reverse
argument_list|(
name|list
argument_list|)
expr_stmt|;
if|if
condition|(
name|check
operator|&&
name|check_failed
condition|)
block|{
name|fail_list
operator|=
name|g_list_reverse
argument_list|(
name|fail_list
argument_list|)
expr_stmt|;
operator|*
name|check_failed
operator|=
name|fail_list
expr_stmt|;
block|}
return|return
name|list
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_to_str:  * @path: A list of directories as returned by gimp_path_parse().  *  * Returns: A searchpath string separated by #G_SEARCHPATH_SEPARATOR.  *  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_path_to_str (GList * path)
name|gimp_path_to_str
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|)
block|{
name|GString
modifier|*
name|str
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|retval
init|=
name|NULL
decl_stmt|;
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
if|if
condition|(
name|str
condition|)
block|{
name|g_string_append_c
argument_list|(
name|str
argument_list|,
name|G_SEARCHPATH_SEPARATOR
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|str
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
name|str
operator|=
name|g_string_new
argument_list|(
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
block|}
if|if
condition|(
name|str
condition|)
block|{
name|retval
operator|=
name|str
operator|->
name|str
expr_stmt|;
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_free:  * @path: A list of directories as returned by gimp_path_parse().  *  * This function frees the memory allocated for the list and it's strings.  *  */
end_comment

begin_function
name|void
DECL|function|gimp_path_free (GList * path)
name|gimp_path_free
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|path
condition|)
block|{
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
name|g_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_path_get_user_writable_dir:  * @path: A list of directories as returned by gimp_path_parse().  *  * Note that you have to g_free() the returned string.  *  * Returns: The first directory in @path where the user has write permission.  *  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_path_get_user_writable_dir (GList * path)
name|gimp_path_get_user_writable_dir
parameter_list|(
name|GList
modifier|*
name|path
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|uid_t
name|euid
decl_stmt|;
name|gid_t
name|egid
decl_stmt|;
name|struct
name|stat
name|filestat
decl_stmt|;
name|gint
name|err
decl_stmt|;
name|euid
operator|=
name|geteuid
argument_list|()
expr_stmt|;
name|egid
operator|=
name|getegid
argument_list|()
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
comment|/*  check if directory exists  */
comment|/* ugly hack to handle paths with an extra G_DIR_SEPARATOR        * attached. The stat() in MSVCRT doesn't like that.        */
name|gchar
modifier|*
name|dir
init|=
name|g_strdup
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|p
init|=
name|dir
decl_stmt|;
name|gint
name|pl
decl_stmt|;
if|if
condition|(
name|g_path_is_absolute
argument_list|(
name|dir
argument_list|)
condition|)
name|p
operator|=
name|g_path_skip_root
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|pl
operator|=
name|strlen
argument_list|(
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|pl
operator|>
literal|0
operator|&&
name|p
index|[
name|pl
operator|-
literal|1
index|]
operator|==
name|G_DIR_SEPARATOR
condition|)
name|p
index|[
name|pl
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
name|err
operator|=
name|stat
argument_list|(
name|dir
argument_list|,
operator|&
name|filestat
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
comment|/*  this is tricky:        *  if a file is e.g. owned by the current user but not user-writable,        *  the user has no permission to write to the file regardless        *  of his group's or other's write permissions        */
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
operator|&&
operator|(
operator|(
name|filestat
operator|.
name|st_mode
operator|&
name|S_IWUSR
operator|)
operator|||
operator|(
operator|(
name|filestat
operator|.
name|st_mode
operator|&
name|S_IWGRP
operator|)
operator|&&
operator|(
name|euid
operator|!=
name|filestat
operator|.
name|st_uid
operator|)
operator|)
operator|||
operator|(
operator|(
name|filestat
operator|.
name|st_mode
operator|&
name|S_IWOTH
operator|)
operator|&&
operator|(
name|euid
operator|!=
name|filestat
operator|.
name|st_uid
operator|)
operator|&&
operator|(
name|egid
operator|!=
name|filestat
operator|.
name|st_gid
operator|)
operator|)
operator|)
condition|)
block|{
return|return
name|g_strdup
argument_list|(
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

