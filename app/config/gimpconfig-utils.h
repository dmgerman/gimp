begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Utitility functions for GimpConfig.  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_UTILS_H__
define|#
directive|define
name|__GIMP_CONFIG_UTILS_H__
end_define

begin_function_decl
name|void
name|gimp_config_connect
parameter_list|(
name|GObject
modifier|*
name|src
parameter_list|,
name|GObject
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_disconnect
parameter_list|(
name|GObject
modifier|*
name|src
parameter_list|,
name|GObject
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_config_diff
parameter_list|(
name|GimpConfig
modifier|*
name|a
parameter_list|,
name|GimpConfig
modifier|*
name|b
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_sync
parameter_list|(
name|GimpConfig
modifier|*
name|src
parameter_list|,
name|GimpConfig
modifier|*
name|dest
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_reset_properties
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_string_append_escaped
parameter_list|(
name|GString
modifier|*
name|string
parameter_list|,
specifier|const
name|gchar
modifier|*
name|val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_config_build_data_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_config_build_plug_in_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_UTILS_H__ */
end_comment

end_unit

