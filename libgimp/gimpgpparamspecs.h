begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgpparamspecs.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GP_PARAM_SPECS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GP_PARAM_SPECS_H__
define|#
directive|define
name|__GIMP_GP_PARAM_SPECS_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GP_PARAM_SPECS_H__ */
end_comment

end_unit

