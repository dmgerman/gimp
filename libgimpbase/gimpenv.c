begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenv.c  * Copyright (C) 1999 Tor Lillqvist<tml@iki.fi>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|LIBGIMP_COMPILATION
end_ifndef

begin_define
DECL|macro|LIBGIMP_COMPILATION
define|#
directive|define
name|LIBGIMP_COMPILATION
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpversion.h"
end_include

begin_include
include|#
directive|include
file|"gimpreloc.h"
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

begin_define
DECL|macro|WIN32_LEAN_AND_MEAN
define|#
directive|define
name|WIN32_LEAN_AND_MEAN
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

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

begin_comment
comment|/**  * SECTION: gimpenv  * @title: gimpenv  * @short_description: Functions to access the GIMP environment.  *  * A set of functions to find the locations of GIMP's data directories  * and configuration files.  **/
end_comment

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_env_get_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gimp_env_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|env_dir
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_major_version
specifier|const
name|guint
name|gimp_major_version
init|=
name|GIMP_MAJOR_VERSION
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_minor_version
specifier|const
name|guint
name|gimp_minor_version
init|=
name|GIMP_MINOR_VERSION
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_micro_version
specifier|const
name|guint
name|gimp_micro_version
init|=
name|GIMP_MICRO_VERSION
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_env_init:  * @plug_in: must be %TRUE if this function is called from a plug-in  *  * You don't need to care about this function. It is being called for  * you automatically (by means of the MAIN() macro that every plug-in  * runs). Calling it again will cause a fatal error.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_env_init (gboolean plug_in)
name|gimp_env_init
parameter_list|(
name|gboolean
name|plug_in
parameter_list|)
block|{
specifier|static
name|gboolean
name|gimp_env_initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|gimp_env_initialized
condition|)
name|g_error
argument_list|(
literal|"gimp_env_init() must only be called once!"
argument_list|)
expr_stmt|;
name|gimp_env_initialized
operator|=
name|TRUE
expr_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
if|if
condition|(
name|plug_in
condition|)
block|{
name|_gimp_reloc_init_lib
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|_gimp_reloc_init
argument_list|(
name|NULL
argument_list|)
condition|)
block|{
comment|/* Set $LD_LIBRARY_PATH to ensure that plugins can be loaded. */
specifier|const
name|gchar
modifier|*
name|ldpath
init|=
name|g_getenv
argument_list|(
literal|"LD_LIBRARY_PATH"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|libdir
init|=
name|_gimp_reloc_find_lib_dir
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|ldpath
operator|&&
operator|*
name|ldpath
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|g_strconcat
argument_list|(
name|libdir
argument_list|,
literal|":"
argument_list|,
name|ldpath
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_setenv
argument_list|(
literal|"LD_LIBRARY_PATH"
argument_list|,
name|tmp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_setenv
argument_list|(
literal|"LD_LIBRARY_PATH"
argument_list|,
name|libdir
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|libdir
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/**  * gimp_directory:  *  * Returns the user-specific GIMP settings directory. If the  * environment variable GIMP2_DIRECTORY exists, it is used. If it is  * an absolute path, it is used as is.  If it is a relative path, it  * is taken to be a subdirectory of the home directory. If it is a  * relative path, and no home directory can be determined, it is taken  * to be a subdirectory of gimp_data_directory().  *  * The usual case is that no GIMP2_DIRECTORY environment variable  * exists, and then we use the GIMPDIR subdirectory of the home  * directory. If no home directory exists, we use a per-user  * subdirectory of gimp_data_directory().  In any case, we always  * return some non-empty string, whether it corresponds to an existing  * directory or not.  *  * The returned string is owned by GIMP and must not be modified or  * freed. The returned string is in the encoding used for filenames by  * GLib, which isn't necessarily UTF-8. (On Windows it always is  * UTF-8.)  *  * Returns: The user-specific GIMP settings directory.  **/
end_comment

begin_function
specifier|const
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
specifier|static
name|gchar
modifier|*
name|last_env_gimp_dir
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|env_gimp_dir
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|home_dir
decl_stmt|;
name|env_gimp_dir
operator|=
name|g_getenv
argument_list|(
literal|"GIMP2_DIRECTORY"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dir
condition|)
block|{
name|gboolean
name|gimp2_directory_changed
init|=
name|FALSE
decl_stmt|;
comment|/* We have constructed the gimp_dir already. We can return        * gimp_dir unless some parameter gimp_dir depends on has        * changed. For now we just check for changes to GIMP2_DIRECTORY        */
name|gimp2_directory_changed
operator|=
operator|(
name|env_gimp_dir
operator|==
name|NULL
operator|&&
name|last_env_gimp_dir
operator|!=
name|NULL
operator|)
operator|||
operator|(
name|env_gimp_dir
operator|!=
name|NULL
operator|&&
name|last_env_gimp_dir
operator|==
name|NULL
operator|)
operator|||
operator|(
name|env_gimp_dir
operator|!=
name|NULL
operator|&&
name|last_env_gimp_dir
operator|!=
name|NULL
operator|&&
name|strcmp
argument_list|(
name|env_gimp_dir
argument_list|,
name|last_env_gimp_dir
argument_list|)
operator|!=
literal|0
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp2_directory_changed
condition|)
block|{
return|return
name|gimp_dir
return|;
block|}
else|else
block|{
comment|/* Free the old gimp_dir and go on to update it */
name|g_free
argument_list|(
name|gimp_dir
argument_list|)
expr_stmt|;
name|gimp_dir
operator|=
name|NULL
expr_stmt|;
block|}
block|}
comment|/* Remember the GIMP2_DIRECTORY to next invocation so we can check    * if it changes    */
name|g_free
argument_list|(
name|last_env_gimp_dir
argument_list|)
expr_stmt|;
name|last_env_gimp_dir
operator|=
name|g_strdup
argument_list|(
name|env_gimp_dir
argument_list|)
expr_stmt|;
name|home_dir
operator|=
name|g_get_home_dir
argument_list|()
expr_stmt|;
if|if
condition|(
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
block|{
name|gimp_dir
operator|=
name|g_strdup
argument_list|(
name|env_gimp_dir
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|home_dir
condition|)
block|{
name|gimp_dir
operator|=
name|g_build_filename
argument_list|(
name|home_dir
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
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
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
if|if
condition|(
name|home_dir
condition|)
block|{
name|gimp_dir
operator|=
name|g_build_filename
argument_list|(
name|home_dir
argument_list|,
name|GIMPDIR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|user_name
init|=
name|g_strdup
argument_list|(
name|g_get_user_name
argument_list|()
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|subdir_name
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|gchar
modifier|*
name|p
init|=
name|user_name
decl_stmt|;
while|while
condition|(
operator|*
name|p
condition|)
block|{
comment|/* Replace funny characters in the user name with an                * underscore. The code below also replaces some                * characters that in fact are legal in file names, but                * who cares, as long as the definitely illegal ones are                * caught.                */
if|if
condition|(
operator|!
name|g_ascii_isalnum
argument_list|(
operator|*
name|p
argument_list|)
operator|&&
operator|!
name|strchr
argument_list|(
literal|"-.,@="
argument_list|,
operator|*
name|p
argument_list|)
condition|)
operator|*
name|p
operator|=
literal|'_'
expr_stmt|;
name|p
operator|++
expr_stmt|;
block|}
endif|#
directive|endif
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
name|subdir_name
operator|=
name|g_strconcat
argument_list|(
name|GIMPDIR
literal|"."
argument_list|,
name|user_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dir
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
name|subdir_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|user_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|subdir_name
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|gimp_dir
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_decl_stmt
DECL|variable|libgimpbase_dll
specifier|static
name|HMODULE
name|libgimpbase_dll
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Minimal DllMain that just stores the handle to this DLL */
end_comment

begin_function_decl
name|BOOL
name|WINAPI
comment|/* Avoid silly "no previous prototype" gcc warning */
name|DllMain
parameter_list|(
name|HINSTANCE
name|hinstDLL
parameter_list|,
name|DWORD
name|fdwReason
parameter_list|,
name|LPVOID
name|lpvReserved
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|BOOL
name|WINAPI
DECL|function|DllMain (HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
name|DllMain
parameter_list|(
name|HINSTANCE
name|hinstDLL
parameter_list|,
name|DWORD
name|fdwReason
parameter_list|,
name|LPVOID
name|lpvReserved
parameter_list|)
block|{
switch|switch
condition|(
name|fdwReason
condition|)
block|{
case|case
name|DLL_PROCESS_ATTACH
case|:
name|libgimpbase_dll
operator|=
name|hinstDLL
expr_stmt|;
break|break;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_toplevel_directory (void)
name|gimp_toplevel_directory
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|toplevel
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|toplevel
condition|)
return|return
name|toplevel
return|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
block|{
comment|/* Figure it out from the location of this DLL */
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|sep1
decl_stmt|,
modifier|*
name|sep2
decl_stmt|;
name|wchar_t
name|w_filename
index|[
name|MAX_PATH
index|]
decl_stmt|;
if|if
condition|(
name|GetModuleFileNameW
argument_list|(
name|libgimpbase_dll
argument_list|,
name|w_filename
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|w_filename
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
name|g_error
argument_list|(
literal|"GetModuleFilenameW failed"
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_utf16_to_utf8
argument_list|(
name|w_filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
operator|==
name|NULL
condition|)
name|g_error
argument_list|(
literal|"Converting module filename to UTF-8 failed"
argument_list|)
expr_stmt|;
comment|/* If the DLL file name is of the format      *<foobar>\bin\*.dll, use<foobar>.      * Otherwise, use the directory where the DLL is.      */
name|sep1
operator|=
name|strrchr
argument_list|(
name|filename
argument_list|,
literal|'\\'
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
literal|'\\'
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
name|g_ascii_strcasecmp
argument_list|(
name|sep2
operator|+
literal|1
argument_list|,
literal|"bin"
argument_list|)
operator|==
literal|0
condition|)
block|{
operator|*
name|sep2
operator|=
literal|'\0'
expr_stmt|;
block|}
block|}
name|toplevel
operator|=
name|filename
expr_stmt|;
block|}
else|#
directive|else
name|toplevel
operator|=
name|_gimp_reloc_find_prefix
argument_list|(
name|PREFIX
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|toplevel
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_directory:  *  * Returns the top directory for GIMP data. If the environment  * variable GIMP2_DATADIR exists, that is used.  It should be an  * absolute pathname.  Otherwise, on Unix the compile-time defined  * directory is used. On Windows, the installation directory as deduced  * from the executable's full filename is used.  *  * The returned string is owned by GIMP and must not be modified or  * freed. The returned string is in the encoding used for filenames by  * GLib, which isn't necessarily UTF-8. (On Windows it always is  * UTF-8.)  *  * Returns: The top directory for GIMP data.  **/
end_comment

begin_function
specifier|const
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
if|if
condition|(
operator|!
name|gimp_data_dir
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|_gimp_reloc_find_data_dir
argument_list|(
name|DATADIR
argument_list|)
decl_stmt|;
name|gimp_data_dir
operator|=
name|gimp_env_get_dir
argument_list|(
literal|"GIMP2_DATADIR"
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_data_dir
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_locale_directory:  *  * Returns the top directory for GIMP locale files. If the environment  * variable GIMP2_LOCALEDIR exists, that is used.  It should be an  * absolute pathname.  Otherwise, on Unix the compile-time defined  * directory is used. On Windows, the installation directory as deduced  * from the executable's full filename is used.  *  * The returned string is owned by GIMP and must not be modified or  * freed. The returned string is in the encoding used for filenames by  * the C library, which isn't necessarily UTF-8. (On Windows, unlike  * the other similar functions here, the return value from this  * function is in the system codepage, never in UTF-8. It can thus be  * passed directly to the bindtextdomain() function from libintl which  * does not handle UTF-8.)  *  * Returns: The top directory for GIMP locale files.  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_locale_directory (void)
name|gimp_locale_directory
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|gimp_locale_dir
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_locale_dir
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|_gimp_reloc_find_locale_dir
argument_list|(
name|LOCALEDIR
argument_list|)
decl_stmt|;
name|gimp_locale_dir
operator|=
name|gimp_env_get_dir
argument_list|(
literal|"GIMP2_LOCALEDIR"
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|tmp
operator|=
name|g_win32_locale_filename_from_utf8
argument_list|(
name|gimp_locale_dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimp_locale_dir
argument_list|)
expr_stmt|;
name|gimp_locale_dir
operator|=
name|tmp
expr_stmt|;
endif|#
directive|endif
block|}
return|return
name|gimp_locale_dir
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_sysconf_directory:  *  * Returns the top directory for GIMP config files. If the environment  * variable GIMP2_SYSCONFDIR exists, that is used.  It should be an  * absolute pathname.  Otherwise, on Unix the compile-time defined  * directory is used. On Windows, the installation directory as deduced  * from the executable's full filename is used.  *  * The returned string is owned by GIMP and must not be modified or  * freed. The returned string is in the encoding used for filenames by  * GLib, which isn't necessarily UTF-8. (On Windows it always is  * UTF-8.).  *  * Returns: The top directory for GIMP config files.  **/
end_comment

begin_function
specifier|const
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
if|if
condition|(
operator|!
name|gimp_sysconf_dir
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|_gimp_reloc_find_etc_dir
argument_list|(
name|SYSCONFDIR
argument_list|)
decl_stmt|;
name|gimp_sysconf_dir
operator|=
name|gimp_env_get_dir
argument_list|(
literal|"GIMP2_SYSCONFDIR"
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_sysconf_dir
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_user_directory:  * @type: the type of user directory to retrieve  *  * This procedure is deprecated! Use g_get_user_special_dir() instead.  *  * Returns: The path to the specified user directory, or %NULL if the  *          logical ID was not found.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_user_directory (GimpUserDirectory type)
name|gimp_user_directory
parameter_list|(
name|GimpUserDirectory
name|type
parameter_list|)
block|{
return|return
name|g_get_user_special_dir
argument_list|(
name|type
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_plug_in_directory:  *  * Returns the top directory for GIMP plug_ins and modules. If the  * environment variable GIMP2_PLUGINDIR exists, that is used.  It  * should be an absolute pathname. Otherwise, on Unix the compile-time  * defined directory is used. On Windows, the installation directory as  * deduced from the executable's full filename is used.  *  * The returned string is owned by GIMP and must not be modified or  * freed. The returned string is in the encoding used for filenames by  * GLib, which isn't necessarily UTF-8. (On Windows it always is  * UTF-8.)  *  * Returns: The top directory for GIMP plug_ins and modules.  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_plug_in_directory (void)
name|gimp_plug_in_directory
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|gimp_plug_in_dir
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_plug_in_dir
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|_gimp_reloc_find_plugin_dir
argument_list|(
name|PLUGINDIR
argument_list|)
decl_stmt|;
name|gimp_plug_in_dir
operator|=
name|gimp_env_get_dir
argument_list|(
literal|"GIMP2_PLUGINDIR"
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_plug_in_dir
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_personal_rc_file:  * @basename: The basename of a rc_file.  *  * Returns the name of a file in the user-specific GIMP settings directory.  *  * The returned string is allocated dynamically and *SHOULD* be freed  * with g_free() after use. The returned string is in the encoding  * used for filenames by GLib, which isn't necessarily  * UTF-8. (On Windows it always is UTF-8.)  *  * Returns: The name of a file in the user-specific GIMP settings directory.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_personal_rc_file (const gchar * basename)
name|gimp_personal_rc_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|basename
parameter_list|)
block|{
return|return
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gtkrc:  *  * Returns the name of GIMP's application-specific gtkrc file.  *  * The returned string is owned by GIMP and must not be modified or  * freed. The returned string is in the encoding used for filenames by  * GLib, which isn't necessarily UTF-8. (On Windows it always is  * UTF-8.)  *  * Returns: The name of GIMP's application-specific gtkrc file.  **/
end_comment

begin_function
specifier|const
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
operator|!
name|gimp_gtkrc_filename
condition|)
name|gimp_gtkrc_filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"themes"
argument_list|,
literal|"Default"
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
comment|/**  * gimp_path_runtime_fix:  * @path: A pointer to a string (allocated with g_malloc) that is  *        (or could be) a pathname.  *  * On Windows, this function checks if the string pointed to by @path  * starts with the compile-time prefix, and in that case, replaces the  * prefix with the run-time one.  @path should be a pointer to a  * dynamically allocated (with g_malloc, g_strconcat, etc) string. If  * the replacement takes place, the original string is deallocated,  * and *@path is replaced with a pointer to a new string with the  * run-time prefix spliced in.  *  * On Linux, it does the same thing, but only if BinReloc support is enabled.  * On other Unices, it does nothing because those platforms don't have a  * way to find out where our binary is.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_path_runtime_fix (gchar ** path)
name|gimp_path_runtime_fix
parameter_list|(
name|gchar
modifier|*
modifier|*
name|path
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|&&
name|defined
argument_list|(
name|PREFIX
argument_list|)
name|gchar
modifier|*
name|p
decl_stmt|;
comment|/* Yes, I do mean forward slashes below */
if|if
condition|(
name|strncmp
argument_list|(
operator|*
name|path
argument_list|,
name|PREFIX
literal|"/"
argument_list|,
name|strlen
argument_list|(
name|PREFIX
literal|"/"
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* This is a compile-time entry. Replace the path with the        * real one on this machine.        */
name|p
operator|=
operator|*
name|path
expr_stmt|;
operator|*
name|path
operator|=
name|g_strconcat
argument_list|(
name|gimp_toplevel_directory
argument_list|()
argument_list|,
literal|"\\"
argument_list|,
operator|*
name|path
operator|+
name|strlen
argument_list|(
name|PREFIX
literal|"/"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
comment|/* Replace forward slashes with backslashes, just for    * completeness */
name|p
operator|=
operator|*
name|path
expr_stmt|;
while|while
condition|(
operator|(
name|p
operator|=
name|strchr
argument_list|(
name|p
argument_list|,
literal|'/'
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
operator|*
name|p
operator|=
literal|'\\'
expr_stmt|;
name|p
operator|++
expr_stmt|;
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
comment|/* without defineing PREFIX do something useful too */
name|gchar
modifier|*
name|p
init|=
operator|*
name|path
decl_stmt|;
if|if
condition|(
operator|!
name|g_path_is_absolute
argument_list|(
name|p
argument_list|)
condition|)
block|{
operator|*
name|path
operator|=
name|g_build_filename
argument_list|(
name|gimp_toplevel_directory
argument_list|()
argument_list|,
operator|*
name|path
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
name|gchar
modifier|*
name|p
decl_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
argument|*path
argument_list|,
argument|PREFIX G_DIR_SEPARATOR_S
argument_list|,
argument|strlen (PREFIX G_DIR_SEPARATOR_S)
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* This is a compile-time entry. Replace the path with the        * real one on this machine.        */
name|p
operator|=
operator|*
name|path
expr_stmt|;
operator|*
name|path
operator|=
name|g_build_filename
argument_list|(
name|gimp_toplevel_directory
argument_list|()
argument_list|,
operator|*
name|path
operator|+
name|strlen
argument_list|(
argument|PREFIX G_DIR_SEPARATOR_S
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/**  * gimp_path_parse:  * @path:         A list of directories separated by #G_SEARCHPATH_SEPARATOR.  * @max_paths:    The maximum number of directories to return.  * @check:        %TRUE if you want the directories to be checked.  * @check_failed: Returns a #GList of path elements for which the  *                check failed.  *  * Returns: A #GList of all directories in @path.  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_path_parse (const gchar * path,gint max_paths,gboolean check,GList ** check_failed)
name|gimp_path_parse
parameter_list|(
specifier|const
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
specifier|const
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
name|gboolean
name|exists
init|=
name|TRUE
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
name|gimp_path_runtime_fix
argument_list|(
operator|&
name|patharray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|check
condition|)
name|exists
operator|=
name|g_file_test
argument_list|(
name|dir
operator|->
name|str
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
expr_stmt|;
if|if
condition|(
name|exists
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
comment|/**  * gimp_path_to_str:  * @path: A list of directories as returned by gimp_path_parse().  *  * Returns: A searchpath string separated by #G_SEARCHPATH_SEPARATOR.  **/
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
name|gchar
modifier|*
name|dir
init|=
name|list
operator|->
name|data
decl_stmt|;
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
name|dir
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|str
operator|=
name|g_string_new
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|str
condition|)
name|retval
operator|=
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_free:  * @path: A list of directories as returned by gimp_path_parse().  *  * This function frees the memory allocated for the list and the strings  * it contains.  **/
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
name|g_list_free_full
argument_list|(
name|path
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_path_get_user_writable_dir:  * @path: A list of directories as returned by gimp_path_parse().  *  * Note that you have to g_free() the returned string.  *  * Returns: The first directory in @path where the user has write permission.  **/
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
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|gchar
modifier|*
name|dir
init|=
name|list
operator|->
name|data
decl_stmt|;
comment|/*  check if directory exists  */
name|err
operator|=
name|g_stat
argument_list|(
name|dir
argument_list|,
operator|&
name|filestat
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
name|dir
argument_list|)
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_env_get_dir (const gchar * gimp_env_name,const gchar * env_dir)
name|gimp_env_get_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|gimp_env_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|env_dir
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|env
init|=
name|g_getenv
argument_list|(
name|gimp_env_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|env
condition|)
block|{
if|if
condition|(
operator|!
name|g_path_is_absolute
argument_list|(
name|env
argument_list|)
condition|)
name|g_error
argument_list|(
literal|"%s environment variable should be an absolute path."
argument_list|,
name|gimp_env_name
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|env
argument_list|)
return|;
block|}
else|else
block|{
name|gchar
modifier|*
name|retval
init|=
name|g_strdup
argument_list|(
name|env_dir
argument_list|)
decl_stmt|;
name|gimp_path_runtime_fix
argument_list|(
operator|&
name|retval
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
block|}
end_function

end_unit

