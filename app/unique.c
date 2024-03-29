begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

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

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_comment
comment|/*  for the DBus service names  */
end_comment

begin_include
include|#
directive|include
file|"gui/gimpdbusservice.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"unique.h"
end_include

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

begin_function_decl
specifier|static
name|gboolean
name|gimp_unique_dbus_batch_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|batch_interpreter
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
parameter_list|)
function_decl|;
end_function_decl

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
else|#
directive|else
return|return
name|gimp_unique_dbus_open
argument_list|(
name|filenames
argument_list|,
name|as_new
argument_list|)
return|;
endif|#
directive|endif
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_unique_batch_run (const gchar * batch_interpreter,const gchar ** batch_commands)
name|gimp_unique_batch_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|batch_interpreter
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|g_printerr
argument_list|(
literal|"Batch commands cannot be run in existing instance in Win32.\n"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
else|#
directive|else
return|return
name|gimp_unique_dbus_batch_run
argument_list|(
name|batch_interpreter
argument_list|,
name|batch_commands
argument_list|)
return|;
endif|#
directive|endif
block|}
end_function

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
name|GDBusConnection
modifier|*
name|connection
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|connection
operator|=
name|g_bus_get_sync
argument_list|(
name|G_BUS_TYPE_SESSION
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|connection
condition|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
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
name|GFile
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|g_file_new_for_commandline_arg_and_cwd
argument_list|(
name|filenames
index|[
name|i
index|]
argument_list|,
name|cwd
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|GVariant
modifier|*
name|result
decl_stmt|;
name|gchar
modifier|*
name|uri
init|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
decl_stmt|;
name|result
operator|=
name|g_dbus_connection_call_sync
argument_list|(
name|connection
argument_list|,
name|GIMP_DBUS_SERVICE_NAME
argument_list|,
name|GIMP_DBUS_SERVICE_PATH
argument_list|,
name|GIMP_DBUS_INTERFACE_NAME
argument_list|,
name|method
argument_list|,
name|g_variant_new
argument_list|(
literal|"(s)"
argument_list|,
name|uri
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_DBUS_CALL_FLAGS_NO_AUTO_START
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|result
condition|)
name|g_variant_unref
argument_list|(
name|result
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"conversion to uri failed for '%s'\n"
argument_list|,
name|filenames
index|[
name|i
index|]
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
name|GVariant
modifier|*
name|result
decl_stmt|;
name|result
operator|=
name|g_dbus_connection_call_sync
argument_list|(
name|connection
argument_list|,
name|GIMP_DBUS_SERVICE_NAME
argument_list|,
name|GIMP_DBUS_SERVICE_PATH
argument_list|,
name|GIMP_DBUS_INTERFACE_NAME
argument_list|,
literal|"Activate"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_DBUS_CALL_FLAGS_NO_AUTO_START
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|result
condition|)
name|g_variant_unref
argument_list|(
name|result
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|connection
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s\n"
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
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

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
init|=
block|{
literal|0
block|, }
decl_stmt|;
if|if
condition|(
name|filenames
condition|)
block|{
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
name|GFile
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|g_file_new_for_commandline_arg_and_cwd
argument_list|(
name|filenames
index|[
name|i
index|]
argument_list|,
name|cwd
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_file_get_uri
argument_list|(
name|file
argument_list|)
decl_stmt|;
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
operator|(
name|WPARAM
operator|)
name|window_handle
argument_list|,
operator|(
name|LPARAM
operator|)
operator|&
name|copydata
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"conversion to uri failed for '%s'\n"
argument_list|,
name|filenames
index|[
name|i
index|]
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
name|SendMessage
argument_list|(
name|window_handle
argument_list|,
name|WM_COPYDATA
argument_list|,
operator|(
name|WPARAM
operator|)
name|window_handle
argument_list|,
operator|(
name|LPARAM
operator|)
operator|&
name|copydata
argument_list|)
expr_stmt|;
block|}
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

begin_function
specifier|static
name|gboolean
DECL|function|gimp_unique_dbus_batch_run (const gchar * batch_interpreter,const gchar ** batch_commands)
name|gimp_unique_dbus_batch_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|batch_interpreter
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
name|GDBusConnection
modifier|*
name|connection
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|connection
operator|=
name|g_bus_get_sync
argument_list|(
name|G_BUS_TYPE_SESSION
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|connection
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|method
init|=
literal|"BatchRun"
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
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
name|batch_commands
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
name|GVariant
modifier|*
name|result
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|interpreter
decl_stmt|;
comment|/* NULL is not a valid string GVariant. */
name|interpreter
operator|=
name|batch_interpreter
condition|?
name|batch_interpreter
else|:
literal|""
expr_stmt|;
name|result
operator|=
name|g_dbus_connection_call_sync
argument_list|(
name|connection
argument_list|,
name|GIMP_DBUS_SERVICE_NAME
argument_list|,
name|GIMP_DBUS_SERVICE_PATH
argument_list|,
name|GIMP_DBUS_INTERFACE_NAME
argument_list|,
name|method
argument_list|,
name|g_variant_new
argument_list|(
literal|"(ss)"
argument_list|,
name|interpreter
argument_list|,
name|batch_commands
index|[
name|i
index|]
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_DBUS_CALL_FLAGS_NO_AUTO_START
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|result
condition|)
name|g_variant_unref
argument_list|(
name|result
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|connection
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"%s\n"
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
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

end_unit

