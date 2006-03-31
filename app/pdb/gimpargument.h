begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ARGUMENT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ARGUMENT_H__
define|#
directive|define
name|__GIMP_ARGUMENT_H__
end_define

begin_struct
DECL|struct|_GimpArgument
struct|struct
name|_GimpArgument
block|{
DECL|member|type
name|GimpPDBArgType
name|type
decl_stmt|;
DECL|member|value
name|GValue
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpArgumentSpec
struct|struct
name|_GimpArgumentSpec
block|{
DECL|member|type
name|GimpPDBArgType
name|type
decl_stmt|;
DECL|member|pspec
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_argument_init
parameter_list|(
name|GimpArgument
modifier|*
name|arg
parameter_list|,
name|GimpArgumentSpec
modifier|*
name|spec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_argument_init_compat
parameter_list|(
name|GimpArgument
modifier|*
name|arg
parameter_list|,
name|GimpPDBArgType
name|arg_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_arguments_destroy
parameter_list|(
name|GimpArgument
modifier|*
name|args
parameter_list|,
name|gint
name|n_args
parameter_list|,
name|gboolean
name|full_destroy
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ARGUMENT_H__  */
end_comment

end_unit

