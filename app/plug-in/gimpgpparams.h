begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpgpparams.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GP_PARAMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GP_PARAMS_H__
define|#
directive|define
name|__GIMP_GP_PARAMS_H__
end_define

begin_comment
comment|/*  function names start with an underscore because we incude code  *  from libgimp/ which is private there  */
end_comment

begin_function_decl
name|void
name|_gimp_param_spec_to_gp_param_def
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GPParamDef
modifier|*
name|param_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GParamSpec
modifier|*
name|_gimp_gp_param_def_to_param_spec
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GPParamDef
modifier|*
name|param_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|_gimp_gp_params_to_value_array
parameter_list|(
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|,
name|gint
name|n_pspecs
parameter_list|,
name|GPParam
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
name|GPParam
modifier|*
name|_gimp_value_array_to_gp_params
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
comment|/* __GIMP_GP_PARAMS_H__ */
end_comment

end_unit

