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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdbusservice.h"
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
if|#
directive|if
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
block|{  }
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* G_OS_WIN32 */
end_comment

end_unit

