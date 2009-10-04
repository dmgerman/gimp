begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDBusService  * Copyright (C) 2007, 2008 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_if
if|#
directive|if
name|HAVE_DBUS_GLIB
end_if

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<dbus/dbus-glib.h>
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
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
file|"file/file-open.h"
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
file|"gimpdbusservice-glue.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ab1f9dc0103
block|{
DECL|enumerator|OPENED
name|OPENED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2ab1f9dc0208
block|{
DECL|member|uri
name|gchar
modifier|*
name|uri
decl_stmt|;
DECL|member|as_new
name|gboolean
name|as_new
decl_stmt|;
DECL|typedef|OpenData
block|}
name|OpenData
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_dbus_service_class_init
parameter_list|(
name|GimpDBusServiceClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dbus_service_init
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dbus_service_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dbus_service_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dbus_service_gimp_opened
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpDBusService
modifier|*
name|service
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dbus_service_queue_open
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_dbus_service_open_idle
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|OpenData
modifier|*
name|gimp_dbus_service_open_data_new
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dbus_service_open_data_free
parameter_list|(
name|OpenData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDBusService
argument_list|,
argument|gimp_dbus_service
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dbus_service_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_dbus_service_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_dbus_service_class_init (GimpDBusServiceClass * klass)
name|gimp_dbus_service_class_init
parameter_list|(
name|GimpDBusServiceClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|gimp_dbus_service_signals
index|[
name|OPENED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"opened"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDBusServiceClass
argument_list|,
name|opened
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__STRING
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_dbus_service_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_dbus_service_finalize
expr_stmt|;
name|dbus_g_object_type_install_info
argument_list|(
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
operator|&
name|dbus_glib_gimp_object_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dbus_service_init (GimpDBusService * service)
name|gimp_dbus_service_init
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|)
block|{
name|service
operator|->
name|queue
operator|=
name|g_queue_new
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|GObject
modifier|*
DECL|function|gimp_dbus_service_new (Gimp * gimp)
name|gimp_dbus_service_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDBusService
modifier|*
name|service
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|service
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DBUS_SERVICE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|service
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp
argument_list|,
literal|"image-opened"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_dbus_service_gimp_opened
argument_list|)
argument_list|,
name|service
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|G_OBJECT
argument_list|(
name|service
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dbus_service_dispose (GObject * object)
name|gimp_dbus_service_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDBusService
modifier|*
name|service
init|=
name|GIMP_DBUS_SERVICE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|service
operator|->
name|source
condition|)
block|{
name|g_source_remove
argument_list|(
name|g_source_get_id
argument_list|(
name|service
operator|->
name|source
argument_list|)
argument_list|)
expr_stmt|;
name|service
operator|->
name|source
operator|=
name|NULL
expr_stmt|;
block|}
while|while
condition|(
operator|!
name|g_queue_is_empty
argument_list|(
name|service
operator|->
name|queue
argument_list|)
condition|)
block|{
name|gimp_dbus_service_open_data_free
argument_list|(
name|g_queue_pop_head
argument_list|(
name|service
operator|->
name|queue
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dbus_service_finalize (GObject * object)
name|gimp_dbus_service_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDBusService
modifier|*
name|service
init|=
name|GIMP_DBUS_SERVICE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|service
operator|->
name|queue
condition|)
block|{
name|g_queue_free
argument_list|(
name|service
operator|->
name|queue
argument_list|)
expr_stmt|;
name|service
operator|->
name|queue
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_dbus_service_open (GimpDBusService * service,const gchar * uri,gboolean * success,GError ** dbus_error)
name|gimp_dbus_service_open
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
modifier|*
name|success
parameter_list|,
name|GError
modifier|*
modifier|*
name|dbus_error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DBUS_SERVICE
argument_list|(
name|service
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|success
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|success
operator|=
name|gimp_dbus_service_queue_open
argument_list|(
name|service
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_dbus_service_open_as_new (GimpDBusService * service,const gchar * uri,gboolean * success,GError ** dbus_error)
name|gimp_dbus_service_open_as_new
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
modifier|*
name|success
parameter_list|,
name|GError
modifier|*
modifier|*
name|dbus_error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DBUS_SERVICE
argument_list|(
name|service
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|uri
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|success
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
operator|*
name|success
operator|=
name|gimp_dbus_service_queue_open
argument_list|(
name|service
argument_list|,
name|uri
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_dbus_service_activate (GimpDBusService * service,GError ** dbus_error)
name|gimp_dbus_service_activate
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
name|GError
modifier|*
modifier|*
name|dbus_error
parameter_list|)
block|{
name|GimpObject
modifier|*
name|display
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DBUS_SERVICE
argument_list|(
name|service
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  We want to be called again later in case that GIMP is not fully    *  started yet.    */
if|if
condition|(
operator|!
name|gimp_is_restored
argument_list|(
name|service
operator|->
name|gimp
argument_list|)
condition|)
return|return
name|TRUE
return|;
name|display
operator|=
name|gimp_container_get_first_child
argument_list|(
name|service
operator|->
name|gimp
operator|->
name|displays
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
condition|)
block|{
name|GtkWidget
modifier|*
name|toplevel
decl_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|toplevel
argument_list|)
condition|)
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|toplevel
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dbus_service_gimp_opened (Gimp * gimp,const gchar * uri,GimpDBusService * service)
name|gimp_dbus_service_gimp_opened
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpDBusService
modifier|*
name|service
parameter_list|)
block|{
name|g_signal_emit
argument_list|(
name|service
argument_list|,
name|gimp_dbus_service_signals
index|[
name|OPENED
index|]
argument_list|,
literal|0
argument_list|,
name|uri
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * Adds a request to open a file to the end of the queue and  * starts an idle source if it is not already running.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dbus_service_queue_open (GimpDBusService * service,const gchar * uri,gboolean as_new)
name|gimp_dbus_service_queue_open
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
name|g_queue_push_tail
argument_list|(
name|service
operator|->
name|queue
argument_list|,
name|gimp_dbus_service_open_data_new
argument_list|(
name|service
argument_list|,
name|uri
argument_list|,
name|as_new
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|service
operator|->
name|source
condition|)
block|{
name|service
operator|->
name|source
operator|=
name|g_idle_source_new
argument_list|()
expr_stmt|;
name|g_source_set_priority
argument_list|(
name|service
operator|->
name|source
argument_list|,
name|G_PRIORITY_LOW
argument_list|)
expr_stmt|;
name|g_source_set_callback
argument_list|(
name|service
operator|->
name|source
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_dbus_service_open_idle
argument_list|,
name|service
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_source_attach
argument_list|(
name|service
operator|->
name|source
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_source_unref
argument_list|(
name|service
operator|->
name|source
argument_list|)
expr_stmt|;
block|}
comment|/*  The call always succeeds as it is handled in one way or another.    *  Even presenting an error message is considered success ;-)    */
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * Idle callback that removes the first request from the queue and  * handles it. If there are no more requests, the idle source is  * removed.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_dbus_service_open_idle (GimpDBusService * service)
name|gimp_dbus_service_open_idle
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|)
block|{
name|OpenData
modifier|*
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|service
operator|->
name|gimp
operator|->
name|restored
condition|)
return|return
name|TRUE
return|;
name|data
operator|=
name|g_queue_pop_tail
argument_list|(
name|service
operator|->
name|queue
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
block|{
name|file_open_from_command_line
argument_list|(
name|service
operator|->
name|gimp
argument_list|,
name|data
operator|->
name|uri
argument_list|,
name|data
operator|->
name|as_new
argument_list|)
expr_stmt|;
name|gimp_dbus_service_open_data_free
argument_list|(
name|data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|service
operator|->
name|source
operator|=
name|NULL
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|OpenData
modifier|*
DECL|function|gimp_dbus_service_open_data_new (GimpDBusService * service,const gchar * uri,gboolean as_new)
name|gimp_dbus_service_open_data_new
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|gboolean
name|as_new
parameter_list|)
block|{
name|OpenData
modifier|*
name|data
init|=
name|g_slice_new
argument_list|(
name|OpenData
argument_list|)
decl_stmt|;
name|data
operator|->
name|uri
operator|=
name|g_strdup
argument_list|(
name|uri
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
DECL|function|gimp_dbus_service_open_data_free (OpenData * data)
name|gimp_dbus_service_open_data_free
parameter_list|(
name|OpenData
modifier|*
name|data
parameter_list|)
block|{
name|g_free
argument_list|(
name|data
operator|->
name|uri
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|OpenData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_DBUS_GLIB */
end_comment

end_unit

