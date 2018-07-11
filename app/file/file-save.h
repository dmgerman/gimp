begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-save.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_SAVE_H__
end_ifndef

begin_define
DECL|macro|__FILE_SAVE_H__
define|#
directive|define
name|__FILE_SAVE_H__
end_define

begin_function_decl
name|GimpPDBStatusType
name|file_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|file_proc
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|gboolean
name|change_saved_state
parameter_list|,
name|gboolean
name|export_backward
parameter_list|,
name|gboolean
name|export_forward
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
comment|/* __FILE_SAVE_H__ */
end_comment

end_unit

