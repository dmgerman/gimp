begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MENUS_H__
end_ifndef

begin_define
DECL|macro|__MENUS_H__
define|#
directive|define
name|__MENUS_H__
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_function_decl
name|void
name|menus_get_toolbox_menubar
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|menubar
parameter_list|,
name|GtkAcceleratorTable
modifier|*
modifier|*
name|table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_get_image_menu
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|menu
parameter_list|,
name|GtkAcceleratorTable
modifier|*
modifier|*
name|table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_get_load_menu
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|menu
parameter_list|,
name|GtkAcceleratorTable
modifier|*
modifier|*
name|table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_get_save_menu
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|menu
parameter_list|,
name|GtkAcceleratorTable
modifier|*
modifier|*
name|table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_create
parameter_list|(
name|GtkMenuEntry
modifier|*
name|entries
parameter_list|,
name|int
name|nmenu_entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_set_sensitive
parameter_list|(
name|char
modifier|*
name|path
parameter_list|,
name|int
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_set_state
parameter_list|(
name|char
modifier|*
name|path
parameter_list|,
name|int
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_add_path
parameter_list|(
name|char
modifier|*
name|path
parameter_list|,
name|char
modifier|*
name|accelerator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_destroy
parameter_list|(
name|char
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_quit
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
comment|/* MENUS_H */
end_comment

end_unit

