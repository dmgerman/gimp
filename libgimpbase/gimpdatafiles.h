begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Datafiles module copyight (C) 1996 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DATAFILES_H__
end_ifndef

begin_define
DECL|macro|__DATAFILES_H__
define|#
directive|define
name|__DATAFILES_H__
end_define

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_define
DECL|macro|INCLUDE_TEMP_DIR
define|#
directive|define
name|INCLUDE_TEMP_DIR
value|0x1
end_define

begin_define
DECL|macro|MODE_EXECUTABLE
define|#
directive|define
name|MODE_EXECUTABLE
value|0x2
end_define

begin_comment
comment|/***** Types *****/
end_comment

begin_typedef
DECL|typedef|GimpDataFileLoaderFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpDataFileLoaderFunc
function_decl|)
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/***** Functions *****/
end_comment

begin_function_decl
name|void
name|datafiles_read_directories
parameter_list|(
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GimpDataFileLoaderFunc
name|loader_func
parameter_list|,
name|gint
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the current datafiles access, modification  *  or change time. The current datafile is the one for  *  which the "DataFileLoaderFunc" function has been called  *  on.  */
end_comment

begin_function_decl
name|time_t
name|datafile_atime
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|datafile_mtime
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|datafile_ctime
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __DATAFILES_H__ */
end_comment

end_unit

