begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-history.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-history.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginprocedure.h"
end_include

begin_function
name|guint
DECL|function|gimp_plug_in_manager_history_size (GimpPlugInManager * manager)
name|gimp_plug_in_manager_history_size
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
literal|0
argument_list|)
expr_stmt|;
return|return
name|MAX
argument_list|(
literal|1
argument_list|,
name|manager
operator|->
name|gimp
operator|->
name|config
operator|->
name|plug_in_history_size
argument_list|)
return|;
block|}
end_function

begin_function
name|guint
DECL|function|gimp_plug_in_manager_history_length (GimpPlugInManager * manager)
name|gimp_plug_in_manager_history_length
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
literal|0
argument_list|)
expr_stmt|;
return|return
name|g_slist_length
argument_list|(
name|manager
operator|->
name|history
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPlugInProcedure
modifier|*
DECL|function|gimp_plug_in_manager_history_nth (GimpPlugInManager * manager,guint n)
name|gimp_plug_in_manager_history_nth
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|guint
name|n
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
name|g_slist_nth_data
argument_list|(
name|manager
operator|->
name|history
argument_list|,
name|n
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_history_add (GimpPlugInManager * manager,GimpPlugInProcedure * procedure)
name|gimp_plug_in_manager_history_add
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|history_size
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
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
comment|/* return early if the procedure is already at the top */
if|if
condition|(
name|manager
operator|->
name|history
operator|&&
name|manager
operator|->
name|history
operator|->
name|data
operator|==
name|procedure
condition|)
return|return;
name|history_size
operator|=
name|gimp_plug_in_manager_history_size
argument_list|(
name|manager
argument_list|)
expr_stmt|;
name|manager
operator|->
name|history
operator|=
name|g_slist_remove
argument_list|(
name|manager
operator|->
name|history
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|manager
operator|->
name|history
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|history
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_slist_nth
argument_list|(
name|manager
operator|->
name|history
argument_list|,
name|history_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|manager
operator|->
name|history
operator|=
name|g_slist_remove_link
argument_list|(
name|manager
operator|->
name|history
argument_list|,
name|list
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|list
argument_list|)
expr_stmt|;
block|}
name|gimp_plug_in_manager_history_changed
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_history_remove (GimpPlugInManager * manager,GimpPlugInProcedure * procedure)
name|gimp_plug_in_manager_history_remove
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GSList
modifier|*
name|link
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
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|link
operator|=
name|g_slist_find
argument_list|(
name|manager
operator|->
name|history
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
if|if
condition|(
name|link
condition|)
block|{
name|manager
operator|->
name|history
operator|=
name|g_slist_delete_link
argument_list|(
name|manager
operator|->
name|history
argument_list|,
name|link
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_history_changed
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_history_clear (GimpPlugInManager * manager)
name|gimp_plug_in_manager_history_clear
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|history
condition|)
block|{
name|g_slist_free
argument_list|(
name|manager
operator|->
name|history
argument_list|)
expr_stmt|;
name|manager
operator|->
name|history
operator|=
name|NULL
expr_stmt|;
name|gimp_plug_in_manager_history_changed
argument_list|(
name|manager
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

