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

begin_define
DECL|macro|MENU_SEPARATOR (path)
define|#
directive|define
name|MENU_SEPARATOR
parameter_list|(
name|path
parameter_list|)
define|\
value|{ { (path), NULL, NULL, 0, "<Separator>" }, NULL, NULL, NULL }
end_define

begin_define
DECL|macro|MENU_BRANCH (path)
define|#
directive|define
name|MENU_BRANCH
parameter_list|(
name|path
parameter_list|)
define|\
value|{ { (path), NULL, NULL, 0, "<Branch>" }, NULL, NULL, NULL }
end_define

begin_decl_stmt
specifier|extern
name|GimpMenuFactory
modifier|*
name|global_menu_factory
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|menus_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_clear
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_last_opened_add
parameter_list|(
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_filters_subdirs_to_top
parameter_list|(
name|GtkMenu
modifier|*
name|menu
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

