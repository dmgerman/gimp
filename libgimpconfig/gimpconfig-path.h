begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpconfig-path.h  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_PATH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_PATH_H__
define|#
directive|define
name|__GIMP_CONFIG_PATH_H__
end_define

begin_comment
comment|/*  * GIMP_TYPE_CONFIG_PATH  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_CONFIG_PATH
define|#
directive|define
name|GIMP_TYPE_CONFIG_PATH
value|(gimp_config_path_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_CONFIG_PATH (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_CONFIG_PATH
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_CONFIG_PATH))
end_define

begin_decl_stmt
name|GType
name|gimp_config_path_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * GIMP_TYPE_PARAM_CONFIG_PATH  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ab4dac60103
block|{
DECL|enumerator|GIMP_CONFIG_PATH_FILE
name|GIMP_CONFIG_PATH_FILE
block|,
DECL|enumerator|GIMP_CONFIG_PATH_FILE_LIST
name|GIMP_CONFIG_PATH_FILE_LIST
block|,
DECL|enumerator|GIMP_CONFIG_PATH_DIR
name|GIMP_CONFIG_PATH_DIR
block|,
DECL|enumerator|GIMP_CONFIG_PATH_DIR_LIST
name|GIMP_CONFIG_PATH_DIR_LIST
DECL|typedef|GimpConfigPathType
block|}
name|GimpConfigPathType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PARAM_CONFIG_PATH
define|#
directive|define
name|GIMP_TYPE_PARAM_CONFIG_PATH
value|(gimp_param_config_path_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_CONFIG_PATH (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_CONFIG_PATH
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_CONFIG_PATH))
end_define

begin_decl_stmt
name|GType
name|gimp_param_config_path_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_config_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GimpConfigPathType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpConfigPathType
name|gimp_param_spec_config_path_type
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GimpConfigPath utilities  */
end_comment

begin_function_decl
name|gchar
modifier|*
name|gimp_config_path_expand
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|recode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gimp_config_build_writable_path
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
comment|/* __GIMP_CONFIG_PATH_H__ */
end_comment

end_unit

