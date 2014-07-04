begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DYNAMICS_LOAD_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DYNAMICS_LOAD_H__
define|#
directive|define
name|__GIMP_DYNAMICS_LOAD_H__
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_FILE_EXTENSION
define|#
directive|define
name|GIMP_DYNAMICS_FILE_EXTENSION
value|".gdyn"
end_define

begin_function_decl
name|GList
modifier|*
name|gimp_dynamics_load
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GInputStream
modifier|*
name|input
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DYNAMICS_LOAD_H__ */
end_comment

end_unit

