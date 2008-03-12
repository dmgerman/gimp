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
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
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
name|GtkWidget
modifier|*
name|child
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
name|child
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|child
condition|)
block|{
if|if
condition|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|child
argument_list|)
condition|)
block|{
return|return
name|GIMP_CONTAINER_EDITOR
argument_list|(
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
name|child
argument_list|)
condition|)
block|{
return|return
name|GIMP_CONTAINER_VIEW
argument_list|(
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

begin_function
name|void
DECL|function|gimp_container_view_remove_active (GimpContainerView * view)
name|gimp_container_view_remove_active
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|context
operator|&&
name|container
condition|)
block|{
name|GimpObject
modifier|*
name|active
decl_stmt|;
name|active
operator|=
name|gimp_context_get_by_type
argument_list|(
name|context
argument_list|,
name|container
operator|->
name|children_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
condition|)
block|{
name|GimpObject
modifier|*
name|new
decl_stmt|;
name|new
operator|=
name|gimp_container_get_neighbor_of_active
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|active
argument_list|)
expr_stmt|;
if|if
condition|(
name|new
condition|)
name|gimp_context_set_by_type
argument_list|(
name|context
argument_list|,
name|container
operator|->
name|children_type
argument_list|,
name|new
argument_list|)
expr_stmt|;
name|gimp_container_remove
argument_list|(
name|container
argument_list|,
name|active
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

