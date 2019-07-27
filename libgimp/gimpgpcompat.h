begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgpcompat.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GP_COMPAT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GP_COMPAT_H__
define|#
directive|define
name|__GIMP_GP_COMPAT_H__
end_define

begin_function_decl
name|GParamSpec
modifier|*
name|_gimp_gp_compat_param_spec
parameter_list|(
name|GimpPDBArgType
name|arg_type
parameter_list|,
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GType
name|_gimp_pdb_arg_type_to_gtype
parameter_list|(
name|GimpPDBArgType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPDBArgType
name|_gimp_pdb_gtype_to_arg_type
parameter_list|(
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|_gimp_pdb_arg_type_to_string
parameter_list|(
name|GimpPDBArgType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|_gimp_pdb_params_to_args
parameter_list|(
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|,
name|gint
name|n_pspecs
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|params
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|gboolean
name|return_values
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpParam
modifier|*
name|_gimp_pdb_args_to_params
parameter_list|(
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gboolean
name|full_copy
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GP_COMPAT_H__ */
end_comment

end_unit

