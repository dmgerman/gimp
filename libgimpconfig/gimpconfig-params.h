begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * ParamSpecs for config objects  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_PARAMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_PARAMS_H__
define|#
directive|define
name|__GIMP_CONFIG_PARAMS_H__
end_define

begin_define
DECL|macro|GIMP_PARAM_SERIALIZE
define|#
directive|define
name|GIMP_PARAM_SERIALIZE
value|(1<< (0 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_PARAM_AGGREGATE
define|#
directive|define
name|GIMP_PARAM_AGGREGATE
value|(1<< (1 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_PARAM_RESTART
define|#
directive|define
name|GIMP_PARAM_RESTART
value|(1<< (2 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_PARAM_CONFIRM
define|#
directive|define
name|GIMP_PARAM_CONFIRM
value|(1<< (3 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_CONFIG_PARAM_FLAGS
define|#
directive|define
name|GIMP_CONFIG_PARAM_FLAGS
value|(G_PARAM_READWRITE | \                                  G_PARAM_CONSTRUCT | \                                  GIMP_PARAM_SERIALIZE)
end_define

begin_comment
comment|/*  * GIMP_TYPE_PARAM_COLOR  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_COLOR
define|#
directive|define
name|GIMP_TYPE_PARAM_COLOR
value|(gimp_param_color_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_COLOR (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_COLOR
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_COLOR))
end_define

begin_decl_stmt
name|GType
name|gimp_param_color_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_color
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
specifier|const
name|GimpRGB
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_MATRIX2  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_MATRIX2
define|#
directive|define
name|GIMP_TYPE_PARAM_MATRIX2
value|(gimp_param_matrix2_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_MATRIX2 (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_MATRIX2
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_MATRIX2))
end_define

begin_decl_stmt
name|GType
name|gimp_param_matrix2_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_matrix2
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
specifier|const
name|GimpMatrix2
modifier|*
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_MEMSIZE  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_MEMSIZE
define|#
directive|define
name|GIMP_TYPE_PARAM_MEMSIZE
value|(gimp_param_memsize_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_MEMSIZE (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_MEMSIZE
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_MEMSIZE))
end_define

begin_decl_stmt
name|GType
name|gimp_param_memsize_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_memsize
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
name|gulong
name|minimum
parameter_list|,
name|gulong
name|maximum
parameter_list|,
name|gulong
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_PATH  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6ebf2a0103
block|{
DECL|enumerator|GIMP_PARAM_PATH_FILE
name|GIMP_PARAM_PATH_FILE
block|,
DECL|enumerator|GIMP_PARAM_PATH_FILE_LIST
name|GIMP_PARAM_PATH_FILE_LIST
block|,
DECL|enumerator|GIMP_PARAM_PATH_DIR
name|GIMP_PARAM_PATH_DIR
block|,
DECL|enumerator|GIMP_PARAM_PATH_DIR_LIST
name|GIMP_PARAM_PATH_DIR_LIST
DECL|typedef|GimpParamPathType
block|}
name|GimpParamPathType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PARAM_PATH
define|#
directive|define
name|GIMP_TYPE_PARAM_PATH
value|(gimp_param_path_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_PATH (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_PATH
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_PATH))
end_define

begin_decl_stmt
name|GType
name|gimp_param_path_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_path
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
name|GimpParamPathType
name|type
parameter_list|,
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
name|GimpParamPathType
name|gimp_param_spec_path_type
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * GIMP_TYPE_PARAM_UNIT  */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PARAM_UNIT
define|#
directive|define
name|GIMP_TYPE_PARAM_UNIT
value|(gimp_param_unit_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_PARAM_SPEC_UNIT (pspec)
define|#
directive|define
name|GIMP_IS_PARAM_SPEC_UNIT
parameter_list|(
name|pspec
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), GIMP_TYPE_PARAM_UNIT))
end_define

begin_decl_stmt
name|GType
name|gimp_param_unit_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParamSpec
modifier|*
name|gimp_param_spec_unit
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
name|allow_pixels
parameter_list|,
name|gboolean
name|allow_percent
parameter_list|,
name|GimpUnit
name|default_value
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* some convenience macros to install object properties */
end_comment

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_BOOLEAN (class,id,\\\nname,blurb,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_boolean (name, NULL, blurb,\                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_COLOR
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_COLOR (class,id,\\\nname,blurb,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    gimp_param_spec_color (name, NULL, blurb,\                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_DOUBLE (class,id,\\\nname,blurb,min,max,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_double (name, NULL, blurb,\                                    min, max, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_ENUM
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_ENUM (class,id,\\\nname,blurb,enum_type,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|enum_type
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_enum (name, NULL, blurb,\                                    enum_type, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_INT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_INT (class,id,\\\nname,blurb,min,max,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_int (name, NULL, blurb,\                                    min, max, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_MATRIX2
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_MATRIX2 (class,id,\\\nname,blurb,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    gimp_param_spec_matrix2 (name, NULL, blurb,\                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_MEMSIZE
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_MEMSIZE (class,id,\\\nname,blurb,min,max,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    gimp_param_spec_memsize (name, NULL, blurb,\                                    min, max, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_PATH
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_PATH (class,id,\\\nname,blurb,type,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|type
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    gimp_param_spec_path (name, NULL, blurb,\                                    type, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_STRING
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_STRING (class,id,\\\nname,blurb,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_string (name, NULL, blurb,\                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_UINT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_UINT (class,id,\\\nname,blurb,min,max,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|min
parameter_list|,
name|max
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_uint (name, NULL, blurb,\                                    min, max, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_UNIT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_UNIT (class,id,\\\nname,blurb,pixels,percent,default,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|pixels
parameter_list|,
name|percent
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    gimp_param_spec_unit (name, NULL, blurb,\                                    pixels, percent, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_comment
comment|/*  object properties are _not_ G_PARAM_CONSTRUCT  */
end_comment

begin_define
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,\
DECL|macro|GIMP_CONFIG_INSTALL_PROP_OBJECT (class,id,\\\nname,blurb,object_type,flags)
name|name
parameter_list|,
name|blurb
parameter_list|,
name|object_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|g_object_class_install_property (class, id,\                                    g_param_spec_object (name, NULL, blurb,\                                    object_type,\                                    flags |\                                    G_PARAM_READWRITE | GIMP_PARAM_SERIALIZE))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_PARAMS_H__ */
end_comment

end_unit

