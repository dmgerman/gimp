begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Utitility functions for GimpConfig.  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_GIMP_CONFIG_UTILS_H__
end_ifndef

begin_define
DECL|macro|__APP_GIMP_CONFIG_UTILS_H__
define|#
directive|define
name|__APP_GIMP_CONFIG_UTILS_H__
end_define

begin_function_decl
name|void
name|gimp_config_connect
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_connect_full
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name_a
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name_b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_config_disconnect
parameter_list|(
name|GObject
modifier|*
name|a
parameter_list|,
name|GObject
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APP_GIMP_CONFIG_UTILS_H__ */
end_comment

end_unit

