begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_OPEN_H__
end_ifndef

begin_define
DECL|macro|__FILE_OPEN_H__
define|#
directive|define
name|__FILE_OPEN_H__
end_define

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|load_procs
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpImage
modifier|*
name|file_open_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|open_mode
parameter_list|,
name|PlugInProcDef
modifier|*
name|file_proc
parameter_list|,
name|RunModeType
name|run_mode
parameter_list|,
name|gint
modifier|*
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|file_open_absolute_filename
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FILE_OPEN_H__ */
end_comment

end_unit

