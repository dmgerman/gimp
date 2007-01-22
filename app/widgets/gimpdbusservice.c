begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDBusService  * Copyright (C) 2007 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<dbus/dbus-glib.h>
end_include

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
file|"gimpdbusservice-glue.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.c"
end_include

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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDBusService,gimp_dbus_service,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDBusService
argument_list|,
argument|gimp_dbus_service
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_dbus_service_class_init
parameter_list|(
name|GimpDBusServiceClass
modifier|*
name|klass
parameter_list|)
block|{
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
block|{ }
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
return|return
name|G_OBJECT
argument_list|(
name|service
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_dbus_service_open (GimpDBusService * service,const gchar ** uris,GError ** dbus_error)
name|gimp_dbus_service_open
parameter_list|(
name|GimpDBusService
modifier|*
name|service
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|uris
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
if|if
condition|(
name|uris
operator|&&
operator|*
name|uris
condition|)
block|{
name|file_open_from_command_line
argument_list|(
name|service
operator|->
name|gimp
argument_list|,
name|uris
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* if no URI is passed, raise the toolbox */
specifier|const
name|GList
modifier|*
name|managers
init|=
name|gimp_ui_managers_from_name
argument_list|(
literal|"<Image>"
argument_list|)
decl_stmt|;
if|if
condition|(
name|managers
condition|)
name|gimp_ui_manager_activate_action
argument_list|(
name|managers
operator|->
name|data
argument_list|,
literal|"dialogs"
argument_list|,
literal|"dialogs-toolbox"
argument_list|)
expr_stmt|;
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

begin_comment
comment|/* HAVE_DBUS_GLIB */
end_comment

end_unit

