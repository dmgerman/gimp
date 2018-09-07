begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-raw-utils.h -- raw file format plug-in  * Copyright (C) 2016 Tobias Ellinghaus<me@houz.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_include
include|#
directive|include
file|<CoreServices/CoreServices.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"file-raw-utils.h"
end_include

begin_function
name|gchar
modifier|*
DECL|function|file_raw_get_executable_path (const gchar * main_executable,const gchar * suffix,const gchar * env_variable,const gchar * mac_bundle_id,const gchar * win32_registry_key_base,gboolean win32_use_hkcu,gboolean * search_path)
name|file_raw_get_executable_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|main_executable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|suffix
parameter_list|,
specifier|const
name|gchar
modifier|*
name|env_variable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mac_bundle_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|win32_registry_key_base
parameter_list|,
name|gboolean
name|win32_use_hkcu
parameter_list|,
name|gboolean
modifier|*
name|search_path
parameter_list|)
block|{
comment|/*    * First check for the environment variable.    * Next do platform specific checks (bundle lookup on Mac, registry stuff    * on Windows).    * Last resort is hoping for the executable to be in PATH.    */
comment|/*    * Look for env variable. That can be set directly or via an environ file.    * We assume that just appending the suffix to that value will work.    * That means that on Windows there should be no ".exe"!    */
specifier|const
name|gchar
modifier|*
name|dt_env
init|=
name|env_variable
condition|?
name|g_getenv
argument_list|(
name|env_variable
argument_list|)
else|:
name|NULL
decl_stmt|;
if|if
condition|(
name|dt_env
condition|)
return|return
name|g_strconcat
argument_list|(
name|dt_env
argument_list|,
name|suffix
argument_list|,
name|NULL
argument_list|)
return|;
if|#
directive|if
name|defined
argument_list|(
name|GDK_WINDOWING_QUARTZ
argument_list|)
if|if
condition|(
name|mac_bundle_id
condition|)
block|{
name|CFStringRef
name|bundle_id
decl_stmt|;
comment|/* For macOS, attempt searching for an app bundle first. */
name|bundle_id
operator|=
name|CFStringCreateWithCString
argument_list|(
name|NULL
argument_list|,
name|mac_bundle_id
argument_list|,
name|kCFStringEncodingUTF8
argument_list|)
expr_stmt|;
if|if
condition|(
name|bundle_id
condition|)
block|{
name|OSStatus
name|status
decl_stmt|;
name|CFURLRef
name|bundle_url
init|=
name|NULL
decl_stmt|;
name|status
operator|=
name|LSFindApplicationForInfo
argument_list|(
name|kLSUnknownCreator
argument_list|,
name|bundle_id
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|bundle_url
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|>=
literal|0
condition|)
block|{
name|CFBundleRef
name|bundle
decl_stmt|;
name|CFURLRef
name|exec_url
decl_stmt|,
name|absolute_url
decl_stmt|;
name|CFStringRef
name|path
decl_stmt|;
name|gchar
modifier|*
name|ret
decl_stmt|;
name|CFIndex
name|len
decl_stmt|;
name|bundle
operator|=
name|CFBundleCreate
argument_list|(
name|kCFAllocatorDefault
argument_list|,
name|bundle_url
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|bundle_url
argument_list|)
expr_stmt|;
name|exec_url
operator|=
name|CFBundleCopyExecutableURL
argument_list|(
name|bundle
argument_list|)
expr_stmt|;
name|absolute_url
operator|=
name|CFURLCopyAbsoluteURL
argument_list|(
name|exec_url
argument_list|)
expr_stmt|;
name|path
operator|=
name|CFURLCopyFileSystemPath
argument_list|(
name|absolute_url
argument_list|,
name|kCFURLPOSIXPathStyle
argument_list|)
expr_stmt|;
comment|/* This gets us the length in UTF16 characters, we multiply by 2                * to make sure we have a buffer big enough to fit the UTF8 string.                */
name|len
operator|=
name|CFStringGetLength
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|ret
operator|=
name|g_malloc0
argument_list|(
name|len
operator|*
literal|2
operator|*
sizeof|sizeof
argument_list|(
name|gchar
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|CFStringGetCString
argument_list|(
name|path
argument_list|,
name|ret
argument_list|,
literal|2
operator|*
name|len
operator|*
sizeof|sizeof
argument_list|(
name|gchar
argument_list|)
argument_list|,
name|kCFStringEncodingUTF8
argument_list|)
condition|)
name|ret
operator|=
name|NULL
expr_stmt|;
name|CFRelease
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|absolute_url
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|exec_url
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|bundle
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret
condition|)
return|return
name|ret
return|;
block|}
name|CFRelease
argument_list|(
name|bundle_id
argument_list|)
expr_stmt|;
block|}
comment|/* else, app bundle was not found, try path search as last resort. */
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|GDK_WINDOWING_WIN32
argument_list|)
if|if
condition|(
name|win32_registry_key_base
condition|)
block|{
comment|/* Look for the application in the Windows registry. */
name|char
modifier|*
name|registry_key
decl_stmt|;
name|char
name|path
index|[
name|MAX_PATH
index|]
decl_stmt|;
name|DWORD
name|buffer_size
init|=
sizeof|sizeof
argument_list|(
name|path
argument_list|)
decl_stmt|;
name|long
name|status
decl_stmt|;
if|if
condition|(
name|suffix
condition|)
name|registry_key
operator|=
name|g_strconcat
argument_list|(
name|win32_registry_key_base
argument_list|,
name|suffix
argument_list|,
literal|".exe"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|registry_key
operator|=
name|g_strconcat
argument_list|(
name|win32_registry_key_base
argument_list|,
literal|".exe"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|win32_use_hkcu
condition|)
name|status
operator|=
name|RegGetValue
argument_list|(
name|HKEY_CURRENT_USER
argument_list|,
name|registry_key
argument_list|,
literal|""
argument_list|,
name|RRF_RT_ANY
argument_list|,
name|NULL
argument_list|,
operator|(
name|PVOID
operator|)
operator|&
name|path
argument_list|,
operator|&
name|buffer_size
argument_list|)
expr_stmt|;
else|else
name|status
operator|=
name|RegGetValue
argument_list|(
name|HKEY_LOCAL_MACHINE
argument_list|,
name|registry_key
argument_list|,
literal|""
argument_list|,
name|RRF_RT_ANY
argument_list|,
name|NULL
argument_list|,
operator|(
name|PVOID
operator|)
operator|&
name|path
argument_list|,
operator|&
name|buffer_size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|registry_key
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|ERROR_SUCCESS
condition|)
return|return
name|g_strdup
argument_list|(
name|path
argument_list|)
return|;
block|}
endif|#
directive|endif
comment|/* Finally, the last resort. */
operator|*
name|search_path
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|suffix
condition|)
return|return
name|g_strconcat
argument_list|(
name|main_executable
argument_list|,
name|suffix
argument_list|,
name|NULL
argument_list|)
return|;
return|return
name|g_strdup
argument_list|(
name|main_executable
argument_list|)
return|;
block|}
end_function

end_unit

