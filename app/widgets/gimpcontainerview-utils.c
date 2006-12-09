begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockable.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpContainerView
modifier|*
DECL|function|gimp_container_view_get_by_dockable (GimpDockable * dockable)
name|gimp_container_view_get_by_dockable
parameter_list|(
name|GimpDockable
modifier|*
name|dockable
parameter_list|)
block|{
name|GtkBin
modifier|*
name|bin
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|bin
operator|=
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
expr_stmt|;
if|if
condition|(
name|bin
operator|->
name|child
condition|)
block|{
if|if
condition|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|bin
operator|->
name|child
argument_list|)
condition|)
block|{
return|return
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|bin
operator|->
name|child
argument_list|)
operator|->
name|view
return|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|bin
operator|->
name|child
argument_list|)
condition|)
block|{
return|return
name|GIMP_CONTAINER_VIEW
argument_list|(
name|bin
operator|->
name|child
argument_list|)
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

