begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpprocedureconfig-private.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROCEDURE_CONFIG_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROCEDURE_CONFIG_PRIVATE_H__
define|#
directive|define
name|__GIMP_PROCEDURE_CONFIG_PRIVATE_H__
end_define

begin_function_decl
name|gboolean
name|_gimp_procedure_config_load_default
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
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
name|_gimp_procedure_config_save_default
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
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
name|_gimp_procedure_config_load_last
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
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
name|_gimp_procedure_config_save_last
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
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
name|_gimp_procedure_config_load_parasite
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpImage
modifier|*
name|image
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
name|_gimp_procedure_config_save_parasite
parameter_list|(
name|GimpProcedureConfig
modifier|*
name|config
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROCEDURE_CONFIG_PRIVATE_H__ */
end_comment

end_unit

