begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__INFILE_H
end_ifndef

begin_define
DECL|macro|__INFILE_H
define|#
directive|define
name|__INFILE_H
end_define

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_comment
comment|/* Globals */
end_comment

begin_decl_stmt
specifier|extern
name|gboolean
name|img_has_alpha
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Prototypes */
end_comment

begin_function_decl
name|void
name|infile_copy_to_ppm
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|infile_copy_alpha_to_ppm
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

