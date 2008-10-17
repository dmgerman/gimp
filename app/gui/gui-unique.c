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
file|<gtk/gtk.h>
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

begin_if
if|#
directive|if
name|HAVE_DBUS_GLIB
end_if

begin_define
DECL|macro|DBUS_API_SUBJECT_TO_CHANGE
define|#
directive|define
name|DBUS_API_SUBJECT_TO_CHANGE
end_define

begin_include
include|#
directive|include
file|<dbus/dbus-glib.h>
end_include

begin_include
include|#
directive|include
file|<dbus/dbus-glib-lowlevel.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gui/gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdbusservice.h"
end_include

begin_include
include|#
directive|include
file|"gui-unique.h"
end_include

begin_if
if|#
directive|if
name|HAVE_DBUS_GLIB
end_if

begin_function_decl
specifier|static
name|void
name|gui_dbus_service_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_dbus_service_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|dbus_connection
specifier|static
name|DBusGConnection
modifier|*
name|dbus_connection
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
file|"file/file-open.h"
end_include

begin_function_decl
specifier|static
name|void
name|gui_unique_win32_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_unique_win32_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|unique_gimp
specifier|static
name|Gimp
modifier|*
name|unique_gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|proxy_window
specifier|static
name|HWND
name|proxy_window
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|gui_unique_init (Gimp * gimp)
name|gui_unique_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|gui_unique_win32_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
elif|#
directive|elif
name|HAVE_DBUS_GLIB
name|gui_dbus_service_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gui_unique_exit (void)
name|gui_unique_exit
parameter_list|(
name|void
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|gui_unique_win32_exit
argument_list|()
expr_stmt|;
elif|#
directive|elif
name|HAVE_DBUS_GLIB
name|gui_dbus_service_exit
argument_list|()
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_if
if|#
directive|if
name|HAVE_DBUS_GLIB
end_if

begin_function
specifier|static
name|void
DECL|function|gui_dbus_service_init (Gimp * gimp)
name|gui_dbus_service_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dbus_connection
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|dbus_connection
operator|=
name|dbus_g_bus_get
argument_list|(
name|DBUS_BUS_SESSION
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|dbus_connection
condition|)
block|{
name|GObject
modifier|*
name|service
init|=
name|gimp_dbus_service_new
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
name|dbus_bus_request_name
argument_list|(
name|dbus_g_connection_get_connection
argument_list|(
name|dbus_connection
argument_list|)
argument_list|,
name|GIMP_DBUS_SERVICE_NAME
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dbus_g_connection_register_g_object
argument_list|(
name|dbus_connection
argument_list|,
name|GIMP_DBUS_SERVICE_PATH
argument_list|,
name|service
argument_list|)
expr_stmt|;
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
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_dbus_service_exit (void)
name|gui_dbus_service_exit
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|dbus_connection
condition|)
block|{
name|dbus_g_connection_unref
argument_list|(
name|dbus_connection
argument_list|)
expr_stmt|;
name|dbus_connection
operator|=
name|NULL
expr_stmt|;
block|}
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bd464130108
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|as_new
name|gboolean
name|as_new
decl_stmt|;
DECL|typedef|IdleOpenData
block|}
name|IdleOpenData
typedef|;
end_typedef

begin_function
specifier|static
name|IdleOpenData
modifier|*
DECL|function|idle_open_data_new (const gchar * name,gint len,gboolean as_new)
name|idle_open_data_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|len
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
name|IdleOpenData
modifier|*
name|data
init|=
name|g_slice_new0
argument_list|(
name|IdleOpenData
argument_list|)
decl_stmt|;
if|if
condition|(
name|len
operator|>
literal|0
condition|)
block|{
name|data
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|data
operator|->
name|as_new
operator|=
name|as_new
expr_stmt|;
block|}
return|return
name|data
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|idle_open_data_free (IdleOpenData * data)
name|idle_open_data_free
parameter_list|(
name|IdleOpenData
modifier|*
name|data
parameter_list|)
block|{
name|g_free
argument_list|(
name|data
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|IdleOpenData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_unique_win32_idle_open (IdleOpenData * data)
name|gui_unique_win32_idle_open
parameter_list|(
name|IdleOpenData
modifier|*
name|data
parameter_list|)
block|{
comment|/*  We want to be called again later in case that GIMP is not fully    *  started yet.    */
if|if
condition|(
operator|!
name|gimp_is_restored
argument_list|(
name|unique_gimp
argument_list|)
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|data
operator|->
name|name
condition|)
block|{
name|file_open_from_command_line
argument_list|(
name|unique_gimp
argument_list|,
name|data
operator|->
name|name
argument_list|,
name|data
operator|->
name|as_new
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  raise the first display  */
name|GimpObject
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gimp_container_get_first_child
argument_list|(
name|unique_gimp
operator|->
name|displays
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|LRESULT
name|CALLBACK
DECL|function|gui_unique_win32_message_handler (HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
name|gui_unique_win32_message_handler
parameter_list|(
name|HWND
name|hWnd
parameter_list|,
name|UINT
name|uMsg
parameter_list|,
name|WPARAM
name|wParam
parameter_list|,
name|LPARAM
name|lParam
parameter_list|)
block|{
switch|switch
condition|(
name|uMsg
condition|)
block|{
case|case
name|WM_COPYDATA
case|:
if|if
condition|(
name|unique_gimp
condition|)
block|{
name|COPYDATASTRUCT
modifier|*
name|copydata
init|=
operator|(
name|COPYDATASTRUCT
operator|*
operator|)
name|lParam
decl_stmt|;
name|GSource
modifier|*
name|source
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|IdleOpenData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
name|idle_open_data_new
argument_list|(
name|copydata
operator|->
name|lpData
argument_list|,
name|copydata
operator|->
name|cbData
argument_list|,
name|copydata
operator|->
name|dwData
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|closure
operator|=
name|g_cclosure_new
argument_list|(
name|G_CALLBACK
argument_list|(
name|gui_unique_win32_idle_open
argument_list|)
argument_list|,
name|data
argument_list|,
operator|(
name|GClosureNotify
operator|)
name|idle_open_data_free
argument_list|)
expr_stmt|;
name|g_object_watch_closure
argument_list|(
name|unique_gimp
argument_list|,
name|closure
argument_list|)
expr_stmt|;
name|source
operator|=
name|g_idle_source_new
argument_list|()
expr_stmt|;
name|g_source_set_priority
argument_list|(
name|source
argument_list|,
name|G_PRIORITY_LOW
argument_list|)
expr_stmt|;
name|g_source_set_closure
argument_list|(
name|source
argument_list|,
name|closure
argument_list|)
expr_stmt|;
name|g_source_attach
argument_list|(
name|source
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_source_unref
argument_list|(
name|source
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
default|default:
return|return
name|DefWindowProcW
argument_list|(
name|hWnd
argument_list|,
name|uMsg
argument_list|,
name|wParam
argument_list|,
name|lParam
argument_list|)
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_unique_win32_init (Gimp * gimp)
name|gui_unique_win32_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|WNDCLASSW
name|wc
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|unique_gimp
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|unique_gimp
operator|=
name|gimp
expr_stmt|;
comment|/* register window class for proxy window */
name|memset
argument_list|(
operator|&
name|wc
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|wc
argument_list|)
argument_list|)
expr_stmt|;
name|wc
operator|.
name|hInstance
operator|=
name|GetModuleHandle
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|wc
operator|.
name|lpfnWndProc
operator|=
name|gui_unique_win32_message_handler
expr_stmt|;
name|wc
operator|.
name|lpszClassName
operator|=
name|GIMP_UNIQUE_WIN32_WINDOW_CLASS
expr_stmt|;
name|RegisterClassW
argument_list|(
operator|&
name|wc
argument_list|)
expr_stmt|;
name|proxy_window
operator|=
name|CreateWindowExW
argument_list|(
literal|0
argument_list|,
name|GIMP_UNIQUE_WIN32_WINDOW_CLASS
argument_list|,
name|GIMP_UNIQUE_WIN32_WINDOW_NAME
argument_list|,
name|WS_POPUP
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|wc
operator|.
name|hInstance
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_unique_win32_exit (void)
name|gui_unique_win32_exit
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|unique_gimp
argument_list|)
argument_list|)
expr_stmt|;
name|unique_gimp
operator|=
name|NULL
expr_stmt|;
name|DestroyWindow
argument_list|(
name|proxy_window
argument_list|)
expr_stmt|;
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

