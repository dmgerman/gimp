begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_UTILS_H__
end_ifndef

begin_define
DECL|macro|__FILE_UTILS_H__
define|#
directive|define
name|__FILE_UTILS_H__
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_function_decl
name|PlugInProcDef
modifier|*
name|file_proc_find
parameter_list|(
name|GSList
modifier|*
name|procs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return values are 0: no match, 1: magic match, 2: size match */
end_comment

begin_function_decl
name|gint
name|file_check_magic_list
parameter_list|(
name|GSList
modifier|*
name|magics_list
parameter_list|,
name|gint
name|headsize
parameter_list|,
name|guchar
modifier|*
name|head
parameter_list|,
name|FILE
modifier|*
name|ifp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|make_thumb_tempbuf
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|readXVThumb
parameter_list|(
specifier|const
name|gchar
modifier|*
name|fnam
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
parameter_list|,
name|gchar
modifier|*
modifier|*
name|imginfo
comment|/* caller frees if != NULL */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|file_save_thumbnail
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|char
modifier|*
name|full_source_filename
parameter_list|,
name|TempBuf
modifier|*
name|tempbuf
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FILE_UTILS_H__ */
end_comment

end_unit

