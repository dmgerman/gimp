begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GEGL_CONFIG_ARGH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GEGL_CONFIG_ARGH_H__
define|#
directive|define
name|__GIMP_GEGL_CONFIG_ARGH_H__
end_define

begin_function_decl
name|void
name|gimp_gegl_config_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
name|GType
name|config_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_gegl_config_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|GType
name|parent_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_gegl_config_get_container
parameter_list|(
name|GType
name|config_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_config_sync_node
parameter_list|(
name|GimpObject
modifier|*
name|config
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_config_connect_node
parameter_list|(
name|GimpObject
modifier|*
name|config
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GEGL_CONFIG_ARGH_H__ */
end_comment

end_unit

