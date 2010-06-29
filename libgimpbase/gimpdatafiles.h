begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * Datafiles module copyight (C) 1996 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/**  * GimpDatafileData:  * @filename: the data file's full path.  * @dirname:  the folder the data file is is.  * @basename: the data file's basename.  * @atime:    the last time the file was accessed for reading.  * @mtime:    the last time the file was modified.  * @ctime:    the time the file was created.  *  * This structure is passed to the #GimpDatafileLoaderFunc given to  * gimp_datafiles_read_directories() for each file encountered in the  * data path.  **/
end_comment

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
DECL|member|dirname
specifier|const
name|gchar
modifier|*
name|dirname
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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATAFILES_H__ */
end_comment

end_unit

