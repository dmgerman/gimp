begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpextensionmanager.h  * Copyright (C) 2018 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EXTENSION_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EXTENSION_MANAGER_H__
define|#
directive|define
name|__GIMP_EXTENSION_MANAGER_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_EXTENSION_MANAGER
define|#
directive|define
name|GIMP_TYPE_EXTENSION_MANAGER
value|(gimp_extension_manager_get_type ())
end_define

begin_define
DECL|macro|GIMP_EXTENSION_MANAGER (obj)
define|#
directive|define
name|GIMP_EXTENSION_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_EXTENSION_MANAGER, GimpExtensionManager))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_EXTENSION_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_EXTENSION_MANAGER, GimpExtensionManagerClass))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION_MANAGER (obj)
define|#
directive|define
name|GIMP_IS_EXTENSION_MANAGER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_EXTENSION_MANAGER))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION_MANAGER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_EXTENSION_MANAGER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_EXTENSION_MANAGER))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_MANAGER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_EXTENSION_MANAGER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_EXTENSION_MANAGER, GimpExtensionManagerClass))
end_define

begin_typedef
DECL|typedef|GimpExtensionManagerClass
typedef|typedef
name|struct
name|_GimpExtensionManagerClass
name|GimpExtensionManagerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpExtensionManagerPrivate
typedef|typedef
name|struct
name|_GimpExtensionManagerPrivate
name|GimpExtensionManagerPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpExtensionManager
struct|struct
name|_GimpExtensionManager
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpExtensionManagerPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpExtensionManagerClass
struct|struct
name|_GimpExtensionManagerClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_extension_manager_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpExtensionManager
modifier|*
name|gimp_extension_manager_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_extension_manager_initialize
parameter_list|(
name|GimpExtensionManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GList
modifier|*
name|gimp_extension_manager_get_system_extensions
parameter_list|(
name|GimpExtensionManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GList
modifier|*
name|gimp_extension_manager_get_user_extensions
parameter_list|(
name|GimpExtensionManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_extension_manager_is_active
parameter_list|(
name|GimpExtensionManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_EXTENSION_MANAGER_H__ */
end_comment

end_unit

