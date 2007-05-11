begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-procedure.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_PROCEDURE_H__
end_ifndef

begin_define
DECL|macro|__FILE_PROCEDURE_H__
define|#
directive|define
name|__FILE_PROCEDURE_H__
end_define

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|file_procedure_find
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|file_procedure_find_by_prefix
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|file_procedure_find_by_extension
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FILE_PROCEDURE_H__ */
end_comment

end_unit

