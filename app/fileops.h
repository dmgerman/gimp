begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__FILE_IO_H__
end_ifndef

begin_define
DECL|macro|__FILE_IO_H__
define|#
directive|define
name|__FILE_IO_H__
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"gimpimageF.h"
end_include

begin_function_decl
name|void
name|file_ops_pre_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_ops_post_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_open_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_save_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_save_as_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_revert_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_load_by_extension_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_save_by_extension_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|file_open
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|char
modifier|*
name|raw_filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|file_save
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|char
modifier|*
name|filename
parameter_list|,
name|char
modifier|*
name|raw_filename
parameter_list|,
name|gint
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* FILE_IO_H */
end_comment

end_unit

