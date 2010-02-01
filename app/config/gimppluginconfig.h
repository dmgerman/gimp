begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpPluginConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUGIN_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUGIN_CONFIG_H__
define|#
directive|define
name|__GIMP_PLUGIN_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PLUGIN_CONFIG
define|#
directive|define
name|GIMP_TYPE_PLUGIN_CONFIG
value|(gimp_plugin_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_PLUGIN_CONFIG (obj)
define|#
directive|define
name|GIMP_PLUGIN_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PLUGIN_CONFIG, GimpPluginConfig))
end_define

begin_define
DECL|macro|GIMP_PLUGIN_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_PLUGIN_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PLUGIN_CONFIG, GimpPluginConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_PLUGIN_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_PLUGIN_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PLUGIN_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_PLUGIN_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PLUGIN_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PLUGIN_CONFIG))
end_define

begin_typedef
DECL|typedef|GimpPluginConfigClass
typedef|typedef
name|struct
name|_GimpPluginConfigClass
name|GimpPluginConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPluginConfig
struct|struct
name|_GimpPluginConfig
block|{
DECL|member|parent_instance
name|GimpGuiConfig
name|parent_instance
decl_stmt|;
DECL|member|fractalexplorer_path
name|gchar
modifier|*
name|fractalexplorer_path
decl_stmt|;
DECL|member|gfig_path
name|gchar
modifier|*
name|gfig_path
decl_stmt|;
DECL|member|gflare_path
name|gchar
modifier|*
name|gflare_path
decl_stmt|;
DECL|member|gimpressionist_path
name|gchar
modifier|*
name|gimpressionist_path
decl_stmt|;
DECL|member|script_fu_path
name|gchar
modifier|*
name|script_fu_path
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPluginConfigClass
struct|struct
name|_GimpPluginConfigClass
block|{
DECL|member|parent_class
name|GimpGuiConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_plugin_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_PLUGIN_CONFIG_H__ */
end_comment

end_unit

