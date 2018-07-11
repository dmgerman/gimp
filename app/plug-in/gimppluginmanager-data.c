begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-data.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
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
file|"gimppluginmanager-data.h"
end_include

begin_typedef
DECL|typedef|GimpPlugInData
typedef|typedef
name|struct
name|_GimpPlugInData
name|GimpPlugInData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInData
struct|struct
name|_GimpPlugInData
block|{
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|bytes
name|gint32
name|bytes
decl_stmt|;
DECL|member|data
name|guint8
modifier|*
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_plug_in_manager_data_free (GimpPlugInManager * manager)
name|gimp_plug_in_manager_data_free
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
name|data_list
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|data_list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInData
modifier|*
name|data
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|identifier
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpPlugInData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|manager
operator|->
name|data_list
argument_list|)
expr_stmt|;
name|manager
operator|->
name|data_list
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_set_data (GimpPlugInManager * manager,const gchar * identifier,gint32 bytes,const guint8 * data)
name|gimp_plug_in_manager_set_data
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint32
name|bytes
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|)
block|{
name|GimpPlugInData
modifier|*
name|plug_in_data
decl_stmt|;
name|GList
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
name|g_return_if_fail
argument_list|(
name|identifier
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|bytes
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|!=
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|data_list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|plug_in_data
operator|=
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|plug_in_data
operator|->
name|identifier
argument_list|,
name|identifier
argument_list|)
condition|)
break|break;
block|}
comment|/* If there isn't already data with the specified identifier, create one */
if|if
condition|(
name|list
operator|==
name|NULL
condition|)
block|{
name|plug_in_data
operator|=
name|g_slice_new0
argument_list|(
name|GimpPlugInData
argument_list|)
expr_stmt|;
name|plug_in_data
operator|->
name|identifier
operator|=
name|g_strdup
argument_list|(
name|identifier
argument_list|)
expr_stmt|;
name|manager
operator|->
name|data_list
operator|=
name|g_list_prepend
argument_list|(
name|manager
operator|->
name|data_list
argument_list|,
name|plug_in_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|plug_in_data
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|plug_in_data
operator|->
name|bytes
operator|=
name|bytes
expr_stmt|;
name|plug_in_data
operator|->
name|data
operator|=
name|g_memdup
argument_list|(
name|data
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|guint8
modifier|*
DECL|function|gimp_plug_in_manager_get_data (GimpPlugInManager * manager,const gchar * identifier,gint32 * bytes)
name|gimp_plug_in_manager_get_data
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint32
modifier|*
name|bytes
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
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
name|g_return_val_if_fail
argument_list|(
name|identifier
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bytes
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|bytes
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|data_list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInData
modifier|*
name|plug_in_data
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|plug_in_data
operator|->
name|identifier
argument_list|,
name|identifier
argument_list|)
condition|)
block|{
operator|*
name|bytes
operator|=
name|plug_in_data
operator|->
name|bytes
expr_stmt|;
return|return
name|plug_in_data
operator|->
name|data
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

