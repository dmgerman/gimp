begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Datafiles module copyight (C) 1996 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_DATAFILES_H_
end_ifndef

begin_define
DECL|macro|_DATAFILES_H_
define|#
directive|define
name|_DATAFILES_H_
end_define

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
DECL|typedef|datafile_loader_t
typedef|typedef
name|void
function_decl|(
modifier|*
name|datafile_loader_t
function_decl|)
parameter_list|(
name|char
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
name|char
modifier|*
name|path_str
parameter_list|,
name|datafile_loader_t
name|loader_func
parameter_list|,
name|int
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the current datafiles access, modification  *  or change time. The current datafile is the one for  *  which the "datafile_loader_t" function has been called  *  on.  */
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

end_unit

