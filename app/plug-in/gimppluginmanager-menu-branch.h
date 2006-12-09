begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-menu-branch.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_MANAGER_MENU_BRANCH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_MANAGER_MENU_BRANCH_H__
define|#
directive|define
name|__GIMP_PLUG_IN_MANAGER_MENU_BRANCH_H__
end_define

begin_struct
DECL|struct|_GimpPlugInMenuBranch
struct|struct
name|_GimpPlugInMenuBranch
block|{
DECL|member|prog_name
name|gchar
modifier|*
name|prog_name
decl_stmt|;
DECL|member|menu_path
name|gchar
modifier|*
name|menu_path
decl_stmt|;
DECL|member|menu_label
name|gchar
modifier|*
name|menu_label
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_plug_in_manager_menu_branch_exit
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a menu branch */
end_comment

begin_function_decl
name|void
name|gimp_plug_in_manager_add_menu_branch
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_MANAGER_MENU_BRANCH_H__ */
end_comment

end_unit

