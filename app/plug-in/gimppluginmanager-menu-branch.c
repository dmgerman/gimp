begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-menu-branch.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-menu-branch.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-menu-path.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_plug_in_manager_menu_branch_exit (GimpPlugInManager * manager)
name|gimp_plug_in_manager_menu_branch_exit
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|menu_branches
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GimpPlugInMenuBranch
modifier|*
name|branch
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_free
argument_list|(
name|branch
operator|->
name|prog_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|branch
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|branch
operator|->
name|menu_label
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpPlugInMenuBranch
argument_list|,
name|branch
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|manager
operator|->
name|menu_branches
argument_list|)
expr_stmt|;
name|manager
operator|->
name|menu_branches
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_add_menu_branch (GimpPlugInManager * manager,const gchar * prog_name,const gchar * menu_path,const gchar * menu_label)
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
block|{
name|GimpPlugInMenuBranch
modifier|*
name|branch
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|prog_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|menu_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|menu_label
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|branch
operator|=
name|g_slice_new
argument_list|(
name|GimpPlugInMenuBranch
argument_list|)
expr_stmt|;
name|branch
operator|->
name|prog_name
operator|=
name|g_strdup
argument_list|(
name|prog_name
argument_list|)
expr_stmt|;
name|branch
operator|->
name|menu_path
operator|=
name|plug_in_menu_path_map
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|branch
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|menu_label
argument_list|)
expr_stmt|;
name|manager
operator|->
name|menu_branches
operator|=
name|g_slist_append
argument_list|(
name|manager
operator|->
name|menu_branches
argument_list|,
name|branch
argument_list|)
expr_stmt|;
name|g_signal_emit_by_name
argument_list|(
name|manager
argument_list|,
literal|"menu-branch-added"
argument_list|,
name|branch
operator|->
name|prog_name
argument_list|,
name|branch
operator|->
name|menu_path
argument_list|,
name|branch
operator|->
name|menu_label
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|VERBOSE
name|g_print
argument_list|(
literal|"added menu branch \"%s\" at path \"%s\"\n"
argument_list|,
name|branch
operator|->
name|menu_label
argument_list|,
name|branch
operator|->
name|menu_path
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
name|GSList
modifier|*
DECL|function|gimp_plug_in_manager_get_menu_branches (GimpPlugInManager * manager)
name|gimp_plug_in_manager_get_menu_branches
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|manager
operator|->
name|menu_branches
return|;
block|}
end_function

end_unit

