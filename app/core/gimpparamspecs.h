begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_GIMP_PARAM_SPECS_H__
end_ifndef

begin_define
DECL|macro|__APP_GIMP_PARAM_SPECS_H__
define|#
directive|define
name|__APP_GIMP_PARAM_SPECS_H__
end_define

begin_comment
comment|/*  * GIMP_TYPE_PARAM_STRING  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_STRING
define|#
directive|define
name|GIMP_TYPE_PARAM_STRING
value|(gimp_param_string_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_STRING (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_STRING
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_STRING, GimpParamSpecString))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_STRING (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_STRING
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_STRING))
end_define

begin_typedef
DECL|typedef|GimpParamSpecString
typedef|typedef
name|struct
name|_GimpParamSpecString
name|GimpParamSpecString
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecString
struct|struct
name|_GimpParamSpecString
block|{
DECL|member|parent_instance
name|GParamSpecString
name|parent_instance
decl_stmt|;
DECL|member|allow_non_utf8
name|guint
name|allow_non_utf8
range|:
literal|1
decl_stmt|;
DECL|member|non_empty
name|guint
name|non_empty
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_string_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_string
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
name|gboolean
name|allow_non_utf8
parameter_list|,
name|gboolean
name|null_ok
parameter_list|,
name|gboolean
name|non_empty
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

begin_comment
comment|/*  * GIMP_TYPE_PARAM_ENUM  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_ENUM
define|#
directive|define
name|GIMP_TYPE_PARAM_ENUM
value|(gimp_param_enum_get_type ())
end_define

begin_define
DECL|macro|GIMP_PARAM_SPEC_ENUM (pspec)
define|#
directive|define
name|GIMP_PARAM_SPEC_ENUM
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((pspec), GIMP_TYPE_PARAM_ENUM, GimpParamSpecEnum))
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_ENUM (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_ENUM
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_ENUM))
end_define

begin_typedef
DECL|typedef|GimpParamSpecEnum
typedef|typedef
name|struct
name|_GimpParamSpecEnum
name|GimpParamSpecEnum
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpParamSpecEnum
struct|struct
name|_GimpParamSpecEnum
block|{
DECL|member|parent_instance
name|GParamSpecEnum
name|parent_instance
decl_stmt|;
DECL|member|excluded_values
name|GSList
modifier|*
name|excluded_values
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_param_enum_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_enum
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
name|GType
name|enum_type
parameter_list|,
name|gint
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_param_spec_enum_exclude_value
parameter_list|(
name|GimpParamSpecEnum
modifier|*
name|espec
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  include the declaration of the remaining paramspecs, they are  *  identical app/ and libgimp/.  */
end_comment

begin_define
DECL|macro|GIMP_COMPILATION
define|#
directive|define
name|GIMP_COMPILATION
end_define

begin_include
include|#
directive|include
file|"../../libgimp/gimpparamspecs.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_COMPILATION
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __APP_GIMP_PARAM_SPECS_H__  */
end_comment

end_unit

