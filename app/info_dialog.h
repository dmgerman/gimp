begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__INFO_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__INFO_DIALOG_H__
define|#
directive|define
name|__INFO_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"linked.h"
end_include

begin_typedef
DECL|typedef|InfoField
typedef|typedef
name|struct
name|_info_field
name|InfoField
typedef|;
end_typedef

begin_struct
DECL|struct|_info_field
struct|struct
name|_info_field
block|{
DECL|member|w
name|GtkWidget
modifier|*
name|w
decl_stmt|;
DECL|member|text_ptr
name|char
modifier|*
name|text_ptr
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|InfoDialog
typedef|typedef
name|struct
name|_info_dialog
name|InfoDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_info_dialog
struct|struct
name|_info_dialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|info_area
name|GtkWidget
modifier|*
name|info_area
decl_stmt|;
DECL|member|labels
name|GtkWidget
modifier|*
name|labels
decl_stmt|;
DECL|member|values
name|GtkWidget
modifier|*
name|values
decl_stmt|;
DECL|member|field_list
name|link_ptr
name|field_list
decl_stmt|;
DECL|member|user_data
name|void
modifier|*
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Info Dialog functions  */
end_comment

begin_function_decl
name|InfoDialog
modifier|*
name|info_dialog_new
parameter_list|(
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_free
parameter_list|(
name|InfoDialog
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_add_field
parameter_list|(
name|InfoDialog
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_popup
parameter_list|(
name|InfoDialog
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_popdown
parameter_list|(
name|InfoDialog
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_update
parameter_list|(
name|InfoDialog
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __INFO_DIALOG_H__  */
end_comment

end_unit

