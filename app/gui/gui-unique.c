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
file|<gegl.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_empty
empty|#import<AppKit/AppKit.h>
end_empty

begin_include
include|#
directive|include
file|<gtkosxapplication.h>
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
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

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

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|GDK_WINDOWING_QUARTZ
argument_list|)
end_elif

begin_function_decl
specifier|static
name|void
name|gui_unique_quartz_init
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
name|gui_unique_quartz_exit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
unit|@
name|interface
name|GimpAppleEventHandler
range|:
name|NSObject
block|{}
operator|-
operator|(
name|void
operator|)
name|handleEvent
operator|:
operator|(
name|NSAppleEventDescriptor
operator|*
operator|)
name|inEvent
name|andReplyWith
operator|:
operator|(
name|NSAppleEventDescriptor
operator|*
operator|)
name|replyEvent
decl_stmt|;
end_decl_stmt

begin_decl_stmt
unit|@
name|end
specifier|static
name|Gimp
modifier|*
name|unique_gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|event_handler
specifier|static
name|GimpAppleEventHandler
modifier|*
name|event_handler
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

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
DECL|variable|dbus_manager
specifier|static
name|GDBusObjectManagerServer
modifier|*
name|dbus_manager
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dbus_name_id
specifier|static
name|guint
name|dbus_name_id
init|=
literal|0
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
name|defined
argument_list|(
name|GDK_WINDOWING_QUARTZ
argument_list|)
name|gui_unique_quartz_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
else|#
directive|else
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
name|defined
argument_list|(
name|GDK_WINDOWING_QUARTZ
argument_list|)
name|gui_unique_quartz_exit
argument_list|()
expr_stmt|;
else|#
directive|else
name|gui_dbus_service_exit
argument_list|()
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c1cd7160108
block|{
DECL|member|file
name|GFile
modifier|*
name|file
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
DECL|function|idle_open_data_new (GFile * file,gboolean as_new)
name|idle_open_data_new
parameter_list|(
name|GFile
modifier|*
name|file
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
name|data
operator|->
name|file
operator|=
name|g_object_ref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|data
operator|->
name|as_new
operator|=
name|as_new
expr_stmt|;
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
name|g_object_unref
argument_list|(
name|data
operator|->
name|file
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
name|file
condition|)
block|{
name|file_open_from_command_line
argument_list|(
name|unique_gimp
argument_list|,
name|data
operator|->
name|file
argument_list|,
name|data
operator|->
name|as_new
argument_list|,
name|NULL
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
name|gimp_display_shell_present
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
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
name|GimpObject
modifier|*
name|display
decl_stmt|;
if|if
condition|(
name|copydata
operator|->
name|cbData
operator|>
literal|0
condition|)
block|{
name|GSource
modifier|*
name|source
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|IdleOpenData
modifier|*
name|data
decl_stmt|;
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|copydata
operator|->
name|lpData
argument_list|)
expr_stmt|;
name|data
operator|=
name|idle_open_data_new
argument_list|(
name|file
argument_list|,
name|copydata
operator|->
name|dwData
operator|!=
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
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
name|G_OBJECT
argument_list|(
name|unique_gimp
argument_list|)
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
comment|/* Deiconify the window if minimized. */
name|display
operator|=
name|gimp_container_get_first_child
argument_list|(
name|unique_gimp
operator|->
name|displays
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
condition|)
name|gimp_display_shell_present
argument_list|(
name|gimp_display_get_shell
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
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

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|GDK_WINDOWING_QUARTZ
argument_list|)
end_elif

begin_function
specifier|static
name|gboolean
DECL|function|gui_unique_quartz_idle_open (GFile * file)
name|gui_unique_quartz_idle_open
parameter_list|(
name|GFile
modifier|*
name|file
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
name|file
condition|)
block|{
name|file_open_from_command_line
argument_list|(
name|unique_gimp
argument_list|,
name|file
argument_list|,
name|FALSE
argument_list|,
name|NULL
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
name|gboolean
DECL|function|gui_unique_quartz_nsopen_file_callback (GtkosxApplication * osx_app,gchar * path,gpointer user_data)
name|gui_unique_quartz_nsopen_file_callback
parameter_list|(
name|GtkosxApplication
modifier|*
name|osx_app
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GSource
modifier|*
name|source
decl_stmt|;
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|closure
operator|=
name|g_cclosure_new
argument_list|(
name|G_CALLBACK
argument_list|(
name|gui_unique_quartz_idle_open
argument_list|)
argument_list|,
name|g_file_new_for_path
argument_list|(
name|path
argument_list|)
argument_list|,
operator|(
name|GClosureNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|g_object_watch_closure
argument_list|(
name|G_OBJECT
argument_list|(
name|unique_gimp
argument_list|)
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
return|return
name|TRUE
return|;
block|}
end_function

begin_expr_stmt
unit|@
name|implementation
name|GimpAppleEventHandler
operator|-
operator|(
name|void
operator|)
name|handleEvent
operator|:
operator|(
name|NSAppleEventDescriptor
operator|*
operator|)
name|inEvent
name|andReplyWith
operator|:
operator|(
name|NSAppleEventDescriptor
operator|*
operator|)
name|replyEvent
block|{
DECL|variable|urlpool
name|NSAutoreleasePool
operator|*
name|urlpool
block|;
DECL|variable|count
name|NSInteger
name|count
block|;
DECL|variable|i
name|NSInteger
name|i
block|;
name|urlpool
operator|=
index|[
index|[
name|NSAutoreleasePool
name|alloc
index|]
name|init
index|]
block|;
name|count
operator|=
index|[
name|inEvent
name|numberOfItems
index|]
block|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<=
name|count
condition|;
name|i
operator|++
control|)
block|{
DECL|variable|url
name|NSURL
modifier|*
name|url
decl_stmt|;
DECL|variable|path
specifier|const
name|gchar
modifier|*
name|path
decl_stmt|;
DECL|variable|source
name|GSource
modifier|*
name|source
decl_stmt|;
DECL|variable|closure
name|GClosure
modifier|*
name|closure
decl_stmt|;
name|url
operator|=
index|[
name|NSURL
name|URLWithString
operator|:
index|[
index|[
name|inEvent
name|descriptorAtIndex
operator|:
name|i
index|]
name|stringValue
index|]
index|]
expr_stmt|;
name|path
operator|=
index|[
index|[
name|url
name|path
index|]
name|UTF8String
index|]
expr_stmt|;
name|closure
operator|=
name|g_cclosure_new
argument_list|(
name|G_CALLBACK
argument_list|(
name|gui_unique_quartz_idle_open
argument_list|)
argument_list|,
name|g_file_new_for_path
argument_list|(
name|path
argument_list|)
argument_list|,
operator|(
name|GClosureNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|g_object_watch_closure
argument_list|(
name|G_OBJECT
argument_list|(
name|unique_gimp
argument_list|)
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
index|[
name|urlpool
name|drain
index|]
expr_stmt|;
end_expr_stmt

begin_function
unit|} @
name|end
specifier|static
name|void
DECL|function|gui_unique_quartz_init (Gimp * gimp)
name|gui_unique_quartz_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GtkosxApplication
modifier|*
name|osx_app
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
name|osx_app
operator|=
name|gtkosx_application_get
argument_list|()
expr_stmt|;
name|unique_gimp
operator|=
name|gimp
expr_stmt|;
name|g_signal_connect
argument_list|(
name|osx_app
argument_list|,
literal|"NSApplicationOpenFile"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_unique_quartz_nsopen_file_callback
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
comment|/* Using the event handler is a hack, it is necessary because    * gtkosx_application will drop the file open events if any    * event processing is done before gtkosx_application_ready is    * called, which we unfortuantly can't avoid doing right now.    */
name|event_handler
operator|=
index|[
index|[
name|GimpAppleEventHandler
name|alloc
index|]
name|init
index|]
expr_stmt|;
index|[
index|[
name|NSAppleEventManager
name|sharedAppleEventManager
index|]
name|setEventHandler
operator|:
name|event_handler
name|andSelector
operator|:
expr|@
name|selector
argument_list|(
argument|handleEvent: andReplyWith:
argument_list|)
name|forEventClass
operator|:
name|kCoreEventClass
name|andEventID
operator|:
name|kAEOpenDocuments
expr|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_unique_quartz_exit (void)
name|gui_unique_quartz_exit
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
index|[
index|[
name|NSAppleEventManager
name|sharedAppleEventManager
index|]
name|removeEventHandlerForEventClass
operator|:
name|kCoreEventClass
name|andEventID
operator|:
name|kAEOpenDocuments
index|]
expr_stmt|;
index|[
name|event_handler
name|release
index|]
expr_stmt|;
name|event_handler
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_function
specifier|static
name|void
DECL|function|gui_dbus_bus_acquired (GDBusConnection * connection,const gchar * name,Gimp * gimp)
name|gui_dbus_bus_acquired
parameter_list|(
name|GDBusConnection
modifier|*
name|connection
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GDBusObjectSkeleton
modifier|*
name|object
decl_stmt|;
name|GObject
modifier|*
name|service
decl_stmt|;
comment|/* this should use GIMP_DBUS_SERVICE_PATH, but that's historically wrong */
name|dbus_manager
operator|=
name|g_dbus_object_manager_server_new
argument_list|(
literal|"/org/gimp/GIMP"
argument_list|)
expr_stmt|;
name|object
operator|=
name|g_dbus_object_skeleton_new
argument_list|(
name|GIMP_DBUS_INTERFACE_PATH
argument_list|)
expr_stmt|;
name|service
operator|=
name|gimp_dbus_service_new
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_dbus_object_skeleton_add_interface
argument_list|(
name|object
argument_list|,
name|G_DBUS_INTERFACE_SKELETON
argument_list|(
name|service
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|service
argument_list|)
expr_stmt|;
name|g_dbus_object_manager_server_export
argument_list|(
name|dbus_manager
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_dbus_object_manager_server_set_connection
argument_list|(
name|dbus_manager
argument_list|,
name|connection
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_dbus_name_acquired (GDBusConnection * connection,const gchar * name,Gimp * gimp)
name|gui_dbus_name_acquired
parameter_list|(
name|GDBusConnection
modifier|*
name|connection
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gui_dbus_name_lost (GDBusConnection * connection,const gchar * name,Gimp * gimp)
name|gui_dbus_name_lost
parameter_list|(
name|GDBusConnection
modifier|*
name|connection
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{ }
end_function

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
name|dbus_name_id
operator|==
literal|0
argument_list|)
expr_stmt|;
name|dbus_name_id
operator|=
name|g_bus_own_name
argument_list|(
name|G_BUS_TYPE_SESSION
argument_list|,
name|GIMP_DBUS_SERVICE_NAME
argument_list|,
name|G_BUS_NAME_OWNER_FLAGS_NONE
argument_list|,
operator|(
name|GBusAcquiredCallback
operator|)
name|gui_dbus_bus_acquired
argument_list|,
operator|(
name|GBusNameAcquiredCallback
operator|)
name|gui_dbus_name_acquired
argument_list|,
operator|(
name|GBusNameLostCallback
operator|)
name|gui_dbus_name_lost
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|g_bus_unown_name
argument_list|(
name|dbus_name_id
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dbus_manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

