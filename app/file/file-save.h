begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|save_procs
decl_stmt|;
end_decl_stmt

begin_function_decl
name|PDBStatusType
name|file_save
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|,
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|RunModeType
name|run_mode
parameter_list|,
name|gboolean
name|set_filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|file_save_with_proc
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gchar
modifier|*
name|full_filename
parameter_list|,
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|set_filename
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

