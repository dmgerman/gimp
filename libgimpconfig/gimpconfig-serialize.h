begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Object properties serialization routines  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_SERIALIZE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_SERIALIZE_H__
define|#
directive|define
name|__GIMP_CONFIG_SERIALIZE_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_config_serialize_properties
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_serialize_changed_properties
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_serialize_property
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_serialize_property_by_name
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prop_name
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_serialize_value
parameter_list|(
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GString
modifier|*
name|str
parameter_list|,
name|gboolean
name|escaped
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_SERIALIZE_H__ */
end_comment

end_unit

