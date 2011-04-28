begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * ParamSpecs for config objects  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_CONFIG_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_CONFIG_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpconfig/gimpconfig.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * SECTION: gimpconfig-params  * @title: GimpConfig-params  * @short_description: Macros and defines to install config properties.  *  * Macros and defines to install config properties.  **/
end_comment

begin_comment
comment|/*  * GIMP_CONFIG_PARAM_SERIALIZE - A property that can and should be  *                               serialized and deserialized.  * GIMP_CONFIG_PARAM_AGGREGATE - The object property is to be treated as  *                               part of the parent object.  * GIMP_CONFIG_PARAM_RESTART   - Changes to this property take effect only  *                               after a restart.  * GIMP_CONFIG_PARAM_CONFIRM   - Changes to this property should be  *                               confirmed by the user before being applied.  * GIMP_CONFIG_PARAM_DEFAULTS  - Don't serialize this property if it has the  *                               default value.  * GIMP_CONFIG_PARAM_IGNORE    - This property exists for obscure reasons  *                               and is needed for backward compatibility.  *                               Ignore the value read and don't serialize it.  */
end_comment

begin_define
DECL|macro|GIMP_CONFIG_PARAM_SERIALIZE
define|#
directive|define
name|GIMP_CONFIG_PARAM_SERIALIZE
value|(1<< (0 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_CONFIG_PARAM_AGGREGATE
define|#
directive|define
name|GIMP_CONFIG_PARAM_AGGREGATE
value|(1<< (1 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_CONFIG_PARAM_RESTART
define|#
directive|define
name|GIMP_CONFIG_PARAM_RESTART
value|(1<< (2 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_CONFIG_PARAM_CONFIRM
define|#
directive|define
name|GIMP_CONFIG_PARAM_CONFIRM
value|(1<< (3 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_CONFIG_PARAM_DEFAULTS
define|#
directive|define
name|GIMP_CONFIG_PARAM_DEFAULTS
value|(1<< (4 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_CONFIG_PARAM_IGNORE
define|#
directive|define
name|GIMP_CONFIG_PARAM_IGNORE
value|(1<< (5 + G_PARAM_USER_SHIFT))
end_define

begin_define
DECL|macro|GIMP_CONFIG_PARAM_FLAGS
define|#
directive|define
name|GIMP_CONFIG_PARAM_FLAGS
value|(G_PARAM_READWRITE | \                                  G_PARAM_CONSTRUCT | \                                  GIMP_CONFIG_PARAM_SERIALIZE)
end_define

begin_comment
comment|/* some convenience macros to install object properties */
end_comment

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_BOOLEAN (class,id,name,blurb,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_BOOLEAN
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_boolean (name, NULL, blurb,\                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_RGB (class,id,name,blurb,has_alpha,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_RGB
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|has_alpha
parameter_list|,
define|default, flags) \   g_object_class_install_property (class, id,\                                    gimp_param_spec_rgb (name, NULL, blurb,\                                    has_alpha, default, \                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_DOUBLE (class,id,name,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_DOUBLE
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
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
DECL|macro|GIMP_CONFIG_INSTALL_PROP_RESOLUTION (class,id,name,blurb,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_RESOLUTION
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_double (name, NULL, blurb,\                                    GIMP_MIN_RESOLUTION, GIMP_MAX_RESOLUTION, \                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_ENUM (class,id,name,blurb,enum_type,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_ENUM
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|enum_type
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_enum (name, NULL, blurb,\                                    enum_type, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_INT (class,id,name,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_INT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
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
DECL|macro|GIMP_CONFIG_INSTALL_PROP_MATRIX2 (class,id,name,blurb,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_MATRIX2
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    gimp_param_spec_matrix2 (name, NULL, blurb,\                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_MEMSIZE (class,id,name,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_MEMSIZE
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
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
DECL|macro|GIMP_CONFIG_INSTALL_PROP_PATH (class,id,name,blurb,path_type,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_PATH
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|path_type
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    gimp_param_spec_config_path (name, NULL, blurb,\                                    path_type, default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_STRING (class,id,name,blurb,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_STRING
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
define|default, flags)\   g_object_class_install_property (class, id,\                                    g_param_spec_string (name, NULL, blurb,\                                    default,\                                    flags | GIMP_CONFIG_PARAM_FLAGS))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_UINT (class,id,name,blurb,min,max,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_UINT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
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
DECL|macro|GIMP_CONFIG_INSTALL_PROP_UNIT (class,id,name,blurb,pixels,percent,default,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_UNIT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
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
comment|/*  object, boxed and pointer properties are _not_ G_PARAM_CONSTRUCT  */
end_comment

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_OBJECT (class,id,name,blurb,object_type,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_OBJECT
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|object_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|g_object_class_install_property (class, id,\                                    g_param_spec_object (name, NULL, blurb,\                                    object_type,\                                    flags |\                                    G_PARAM_READWRITE |\                                    GIMP_CONFIG_PARAM_SERIALIZE))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_BOXED (class,id,name,blurb,boxed_type,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_BOXED
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|boxed_type
parameter_list|,
name|flags
parameter_list|)
define|\
value|g_object_class_install_property (class, id,\                                    g_param_spec_boxed (name, NULL, blurb,\                                    boxed_type,\                                    flags |\                                    G_PARAM_READWRITE |\                                    GIMP_CONFIG_PARAM_SERIALIZE))
end_define

begin_define
DECL|macro|GIMP_CONFIG_INSTALL_PROP_POINTER (class,id,name,blurb,flags)
define|#
directive|define
name|GIMP_CONFIG_INSTALL_PROP_POINTER
parameter_list|(
name|class
parameter_list|,
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|flags
parameter_list|)
define|\
value|g_object_class_install_property (class, id,\                                    g_param_spec_pointer (name, NULL, blurb,\                                    flags |\                                    G_PARAM_READWRITE |\                                    GIMP_CONFIG_PARAM_SERIALIZE))
end_define

begin_endif
unit|G_END_DECLS
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_PARAMS_H__ */
end_comment

end_unit

