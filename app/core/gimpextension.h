begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpextension.h  * Copyright (C) 2018 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EXTENSION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EXTENSION_H__
define|#
directive|define
name|__GIMP_EXTENSION_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_EXTENSION
define|#
directive|define
name|GIMP_TYPE_EXTENSION
value|(gimp_extension_get_type ())
end_define

begin_define
DECL|macro|GIMP_EXTENSION (obj)
define|#
directive|define
name|GIMP_EXTENSION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_EXTENSION, GimpExtension))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_CLASS (klass)
define|#
directive|define
name|GIMP_EXTENSION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_EXTENSION, GimpExtensionClass))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION (obj)
define|#
directive|define
name|GIMP_IS_EXTENSION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_EXTENSION))
end_define

begin_define
DECL|macro|GIMP_IS_EXTENSION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_EXTENSION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_EXTENSION))
end_define

begin_define
DECL|macro|GIMP_EXTENSION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_EXTENSION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_EXTENSION, GimpExtensionClass))
end_define

begin_typedef
DECL|typedef|GimpExtensionPrivate
typedef|typedef
name|struct
name|_GimpExtensionPrivate
name|GimpExtensionPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpExtensionClass
typedef|typedef
name|struct
name|_GimpExtensionClass
name|GimpExtensionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpExtension
struct|struct
name|_GimpExtension
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpExtensionPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpExtensionClass
struct|struct
name|_GimpExtensionClass
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
name|gimp_extension_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpExtension
modifier|*
name|gimp_extension_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dir
parameter_list|,
name|gboolean
name|writable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_extension_get_name
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_extension_get_comment
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_extension_get_description
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_extension_load
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_extension_run
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_extension_stop
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_brush_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_dynamics_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_mypaint_brush_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_pattern_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_gradient_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_palette_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_tool_preset_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_splash_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_extension_get_plug_in_paths
parameter_list|(
name|GimpExtension
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_extension_cmp
parameter_list|(
name|GimpExtension
modifier|*
name|extension1
parameter_list|,
name|GimpExtension
modifier|*
name|extension2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_extension_id_cmp
parameter_list|(
name|GimpExtension
modifier|*
name|extension1
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
comment|/* __GIMP_EXTENSION_H__ */
end_comment

end_unit

