begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Datafiles module copyight (C) 1996 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DATAFILES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DATAFILES_H__
define|#
directive|define
name|__GIMP_DATAFILES_H__
end_define

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_struct
DECL|struct|_GimpDatafileData
struct|struct
name|_GimpDatafileData
block|{
DECL|member|filename
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|basename
specifier|const
name|gchar
modifier|*
name|basename
decl_stmt|;
DECL|member|atime
name|time_t
name|atime
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|ctime
name|time_t
name|ctime
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|gboolean
name|gimp_datafiles_check_extension
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_datafiles_read_directories
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GFileTest
name|flags
parameter_list|,
name|GimpDatafileLoaderFunc
name|loader_func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATAFILES_H__ */
end_comment

end_unit

