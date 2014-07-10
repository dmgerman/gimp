begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * file-remote.h  * Copyright (C) 2014  Michael Natterer<mitch@gimp.org>  *  * Based on: URI plug-in, GIO/GVfs backend  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_REMOTE_H__
end_ifndef

begin_define
DECL|macro|__FILE_REMOTE_H__
define|#
directive|define
name|__FILE_REMOTE_H__
end_define

begin_function_decl
name|GFile
modifier|*
name|file_remote_download_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|gboolean
modifier|*
name|mounted
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GFile
modifier|*
name|file_remote_upload_image_prepare
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|gboolean
modifier|*
name|mounted
parameter_list|,
name|GimpProgress
modifier|*
name|progress
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
name|file_remote_upload_image_finish
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GFile
modifier|*
name|local_file
parameter_list|,
name|gboolean
name|mounted
parameter_list|,
name|GimpProgress
modifier|*
name|progress
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
comment|/* __FILE_REMOTE_H__ */
end_comment

end_unit

