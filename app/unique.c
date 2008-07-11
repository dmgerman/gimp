begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_if
if|#
directive|if
name|HAVE_DBUS_GLIB
end_if

begin_include
include|#
directive|include
file|<dbus/dbus-glib.h>
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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"unique.h"
end_include

begin_if
if|#
directive|if
name|HAVE_DBUS_GLIB
end_if

begin_function_decl
specifier|static
name|gboolean
name|gimp_unique_dbus_open
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_function_decl
specifier|static
name|gboolean
name|gimp_unique_win32_open
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|gboolean
DECL|function|gimp_unique_open (const gchar ** filenames,gboolean as_new)
name|gimp_unique_open
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
return|return
name|gimp_unique_win32_open
argument_list|(
name|filenames
argument_list|,
name|as_new
argument_list|)
return|;
elif|#
directive|elif
name|HAVE_DBUS_GLIB
return|return
name|gimp_unique_dbus_open
argument_list|(
name|filenames
argument_list|,
name|as_new
argument_list|)
return|;
else|#
directive|else
return|return
name|FALSE
return|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_unique_filename_to_uri (const gchar * filename,const gchar * cwd,GError ** error)
name|gimp_unique_filename_to_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|cwd
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|file_utils_filename_is_uri
argument_list|(
name|filename
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|uri
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
operator|*
name|error
condition|)
block|{
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
name|absolute
init|=
name|g_build_filename
argument_list|(
name|cwd
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
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
block|}
else|else
block|{
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|uri
return|;
block|}
end_function

begin_if
if|#
directive|if
name|HAVE_DBUS_GLIB
end_if

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unique_dbus_open (const gchar ** filenames,gboolean as_new)
name|gimp_unique_dbus_open
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
comment|/*  for the DBus service names  */
include|#
directive|include
file|"widgets/gimpdbusservice.h"
name|DBusGConnection
modifier|*
name|connection
init|=
name|dbus_g_bus_get
argument_list|(
name|DBUS_BUS_SESSION
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|connection
condition|)
block|{
name|DBusGProxy
modifier|*
name|proxy
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|proxy
operator|=
name|dbus_g_proxy_new_for_name
argument_list|(
name|connection
argument_list|,
name|GIMP_DBUS_SERVICE_NAME
argument_list|,
name|GIMP_DBUS_SERVICE_PATH
argument_list|,
name|GIMP_DBUS_SERVICE_INTERFACE
argument_list|)
expr_stmt|;
if|if
condition|(
name|filenames
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|method
init|=
name|as_new
condition|?
literal|"OpenAsNew"
else|:
literal|"Open"
decl_stmt|;
name|gchar
modifier|*
name|cwd
init|=
name|g_get_current_dir
argument_list|()
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|success
operator|=
name|TRUE
init|;
name|filenames
index|[
name|i
index|]
operator|&&
name|success
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|gimp_unique_filename_to_uri
argument_list|(
name|filenames
index|[
name|i
index|]
argument_list|,
name|cwd
argument_list|,
operator|&
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|gboolean
name|retval
decl_stmt|;
comment|/* ignored */
name|success
operator|=
name|dbus_g_proxy_call
argument_list|(
name|proxy
argument_list|,
name|method
argument_list|,
operator|&
name|error
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|uri
argument_list|,
name|G_TYPE_INVALID
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
operator|&
name|retval
argument_list|,
name|G_TYPE_INVALID
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"conversion to uri failed: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|cwd
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|dbus_g_proxy_call
argument_list|(
name|proxy
argument_list|,
literal|"Activate"
argument_list|,
operator|&
name|error
argument_list|,
name|G_TYPE_INVALID
argument_list|,
name|G_TYPE_INVALID
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
name|dbus_g_connection_unref
argument_list|(
name|connection
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
return|return
name|TRUE
return|;
block|}
elseif|else
if|if
condition|(
operator|!
operator|(
name|error
operator|->
name|domain
operator|==
name|DBUS_GERROR
operator|&&
name|error
operator|->
name|code
operator|==
name|DBUS_GERROR_SERVICE_UNKNOWN
operator|)
condition|)
block|{
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_DBUS_GLIB */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unique_win32_open (const gchar ** filenames,gboolean as_new)
name|gimp_unique_win32_open
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
comment|/*  for the proxy window names  */
include|#
directive|include
file|"gui/gui-unique.h"
name|HWND
name|window_handle
init|=
name|FindWindowW
argument_list|(
name|GIMP_UNIQUE_WIN32_WINDOW_CLASS
argument_list|,
name|GIMP_UNIQUE_WIN32_WINDOW_NAME
argument_list|)
decl_stmt|;
if|if
condition|(
name|window_handle
condition|)
block|{
name|COPYDATASTRUCT
name|copydata
decl_stmt|;
name|gchar
modifier|*
name|cwd
init|=
name|g_get_current_dir
argument_list|()
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|filenames
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|gimp_unique_filename_to_uri
argument_list|(
name|filenames
index|[
name|i
index|]
argument_list|,
name|cwd
argument_list|,
operator|&
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|copydata
operator|.
name|lpData
operator|=
name|uri
expr_stmt|;
name|copydata
operator|.
name|cbData
operator|=
name|strlen
argument_list|(
name|uri
argument_list|)
operator|+
literal|1
expr_stmt|;
comment|/* size in bytes   */
name|copydata
operator|.
name|dwData
operator|=
operator|(
name|long
operator|)
name|as_new
expr_stmt|;
name|SendMessage
argument_list|(
name|window_handle
argument_list|,
name|WM_COPYDATA
argument_list|,
name|window_handle
argument_list|,
operator|&
name|copydata
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"conversion to uri failed: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|cwd
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* G_OS_WIN32 */
end_comment

end_unit

