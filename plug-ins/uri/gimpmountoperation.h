begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) Christian Kellner<gicmo@gnome.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS  * file for a list of people on the GTK+ Team.  See the ChangeLog  * files for a list of changes.  These files are distributed with  * GTK+ at ftp://ftp.gtk.org/pub/gtk/.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MOUNT_OPERATION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MOUNT_OPERATION_H__
define|#
directive|define
name|__GIMP_MOUNT_OPERATION_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkscreen.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtkwindow.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_MOUNT_OPERATION
define|#
directive|define
name|GIMP_TYPE_MOUNT_OPERATION
value|(gimp_mount_operation_get_type ())
end_define

begin_define
DECL|macro|GIMP_MOUNT_OPERATION (o)
define|#
directive|define
name|GIMP_MOUNT_OPERATION
parameter_list|(
name|o
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((o), GIMP_TYPE_MOUNT_OPERATION, GimpMountOperation))
end_define

begin_define
DECL|macro|GIMP_MOUNT_OPERATION_CLASS (k)
define|#
directive|define
name|GIMP_MOUNT_OPERATION_CLASS
parameter_list|(
name|k
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST((k), GIMP_TYPE_MOUNT_OPERATION, GimpMountOperationClass))
end_define

begin_define
DECL|macro|GIMP_IS_MOUNT_OPERATION (o)
define|#
directive|define
name|GIMP_IS_MOUNT_OPERATION
parameter_list|(
name|o
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((o), GIMP_TYPE_MOUNT_OPERATION))
end_define

begin_define
DECL|macro|GIMP_IS_MOUNT_OPERATION_CLASS (k)
define|#
directive|define
name|GIMP_IS_MOUNT_OPERATION_CLASS
parameter_list|(
name|k
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((k), GIMP_TYPE_MOUNT_OPERATION))
end_define

begin_define
DECL|macro|GIMP_MOUNT_OPERATION_GET_CLASS (o)
define|#
directive|define
name|GIMP_MOUNT_OPERATION_GET_CLASS
parameter_list|(
name|o
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((o), GIMP_TYPE_MOUNT_OPERATION, GimpMountOperationClass))
end_define

begin_typedef
DECL|typedef|GimpMountOperation
typedef|typedef
name|struct
name|GimpMountOperation
name|GimpMountOperation
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMountOperationClass
typedef|typedef
name|struct
name|GimpMountOperationClass
name|GimpMountOperationClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMountOperationPrivate
typedef|typedef
name|struct
name|GimpMountOperationPrivate
name|GimpMountOperationPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|GimpMountOperation
struct|struct
name|GimpMountOperation
block|{
DECL|member|parent_instance
name|GMountOperation
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpMountOperationPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|GimpMountOperationClass
struct|struct
name|GimpMountOperationClass
block|{
DECL|member|parent_class
name|GMountOperationClass
name|parent_class
decl_stmt|;
comment|/* Padding for future expansion */
DECL|member|_gtk_reserved1
name|void
function_decl|(
modifier|*
name|_gtk_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved2
name|void
function_decl|(
modifier|*
name|_gtk_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved3
name|void
function_decl|(
modifier|*
name|_gtk_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved4
name|void
function_decl|(
modifier|*
name|_gtk_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_mount_operation_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GMountOperation
modifier|*
name|gimp_mount_operation_new
parameter_list|(
name|GtkWindow
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_mount_operation_is_showing
parameter_list|(
name|GimpMountOperation
modifier|*
name|op
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_mount_operation_set_parent
parameter_list|(
name|GimpMountOperation
modifier|*
name|op
parameter_list|,
name|GtkWindow
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWindow
modifier|*
name|gimp_mount_operation_get_parent
parameter_list|(
name|GimpMountOperation
modifier|*
name|op
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_mount_operation_set_screen
parameter_list|(
name|GimpMountOperation
modifier|*
name|op
parameter_list|,
name|GdkScreen
modifier|*
name|screen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkScreen
modifier|*
name|gimp_mount_operation_get_screen
parameter_list|(
name|GimpMountOperation
modifier|*
name|op
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MOUNT_OPERATION_H__ */
end_comment

end_unit

