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
name|GtkAccelGroup
modifier|*
modifier|*
name|accel_group
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
name|GtkAccelGroup
modifier|*
modifier|*
name|accel_group
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
name|GtkAccelGroup
modifier|*
modifier|*
name|accel_group
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
name|GtkAccelGroup
modifier|*
modifier|*
name|accel_group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_get_layers_menu
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|menu
parameter_list|,
name|GtkAccelGroup
modifier|*
modifier|*
name|accel_group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_get_channels_menu
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|menu
parameter_list|,
name|GtkAccelGroup
modifier|*
modifier|*
name|accel_group
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_get_paths_menu
parameter_list|(
name|GtkWidget
modifier|*
modifier|*
name|menu
parameter_list|,
name|GtkAccelGroup
modifier|*
modifier|*
name|accel_group
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
name|gint
name|n_menu_entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_destroy
parameter_list|(
name|gchar
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

begin_function_decl
name|void
name|menus_set_sensitive
parameter_list|(
name|gchar
modifier|*
name|path
parameter_list|,
name|gint
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_set_state
parameter_list|(
name|gchar
modifier|*
name|path
parameter_list|,
name|gint
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_last_opened_add
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MENUS_H__ */
end_comment

end_unit

