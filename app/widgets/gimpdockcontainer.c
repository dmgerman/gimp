begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdockcontainer.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpdockcontainer.h"
end_include

begin_macro
DECL|function|G_DEFINE_INTERFACE (GimpDockContainer,gimp_dock_container,GTK_TYPE_WIDGET)
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpDockContainer
argument_list|,
argument|gimp_dock_container
argument_list|,
argument|GTK_TYPE_WIDGET
argument_list|)
end_macro

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_dock_container_default_init
parameter_list|(
name|GimpDockContainerInterface
modifier|*
name|iface
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_dock_container_get_docks:  * @container: A #GimpDockContainer  *  * Returns: A list of #GimpDock:s in the dock container. Free with  *          g_list_free() when done.  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_dock_container_get_docks (GimpDockContainer * container)
name|gimp_dock_container_get_docks
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|)
block|{
name|GimpDockContainerInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_DOCK_CONTAINER_GET_IFACE
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_docks
condition|)
return|return
name|iface
operator|->
name|get_docks
argument_list|(
name|container
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_container_get_dialog_factory:  * @container: A #GimpDockContainer  *  * Returns: The #GimpDialogFactory of the #GimpDockContainer  **/
end_comment

begin_function
name|GimpDialogFactory
modifier|*
DECL|function|gimp_dock_container_get_dialog_factory (GimpDockContainer * container)
name|gimp_dock_container_get_dialog_factory
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|)
block|{
name|GimpDockContainerInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_DOCK_CONTAINER_GET_IFACE
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_dialog_factory
condition|)
return|return
name|iface
operator|->
name|get_dialog_factory
argument_list|(
name|container
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_container_get_ui_manager:  * @container: A #GimpDockContainer  *  * Returns: The #GimpUIManager of the #GimpDockContainer  **/
end_comment

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_dock_container_get_ui_manager (GimpDockContainer * container)
name|gimp_dock_container_get_ui_manager
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|)
block|{
name|GimpDockContainerInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_DOCK_CONTAINER_GET_IFACE
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_ui_manager
condition|)
return|return
name|iface
operator|->
name|get_ui_manager
argument_list|(
name|container
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_container_add_dock:  * @container: A #GimpDockContainer  * @dock:      The newly created #GimpDock to add to the container.  * @dock_info: The #GimpSessionInfoDock the @dock was created from.  *  * Add @dock that was created from @dock_info to @container.  **/
end_comment

begin_function
name|void
DECL|function|gimp_dock_container_add_dock (GimpDockContainer * container,GimpDock * dock,GimpSessionInfoDock * dock_info)
name|gimp_dock_container_add_dock
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
name|GimpSessionInfoDock
modifier|*
name|dock_info
parameter_list|)
block|{
name|GimpDockContainerInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCK_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_DOCK_CONTAINER_GET_IFACE
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|add_dock
condition|)
name|iface
operator|->
name|add_dock
argument_list|(
name|container
argument_list|,
name|dock
argument_list|,
name|dock_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dock_container_get_dock_side:  * @container: A #GimpDockContainer  * @dock:      A #GimpDock  *  * Returns: What side @dock is in in @container, either  *          GIMP_ALIGN_LEFT or GIMP_ALIGN_RIGHT, or -1 if the side  *          concept is not applicable.  **/
end_comment

begin_function
name|GimpAlignmentType
DECL|function|gimp_dock_container_get_dock_side (GimpDockContainer * container,GimpDock * dock)
name|gimp_dock_container_get_dock_side
parameter_list|(
name|GimpDockContainer
modifier|*
name|container
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GimpDockContainerInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCK_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_DOCK_CONTAINER_GET_IFACE
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_dock_side
condition|)
return|return
name|iface
operator|->
name|get_dock_side
argument_list|(
name|container
argument_list|,
name|dock
argument_list|)
return|;
return|return
operator|-
literal|1
return|;
block|}
end_function

end_unit

