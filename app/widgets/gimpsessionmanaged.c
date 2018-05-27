begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessionmanaged.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimpsessionmanaged.h"
end_include

begin_macro
DECL|function|G_DEFINE_INTERFACE (GimpSessionManaged,gimp_session_managed,GTK_TYPE_WIDGET)
name|G_DEFINE_INTERFACE
argument_list|(
argument|GimpSessionManaged
argument_list|,
argument|gimp_session_managed
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
name|gimp_session_managed_default_init
parameter_list|(
name|GimpSessionManagedInterface
modifier|*
name|iface
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_session_managed_get_aux_info:  * @session_managed: A #GimpSessionManaged  *  * Returns: A list of #GimpSessionInfoAux created with  *          gimp_session_info_aux_new().  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_session_managed_get_aux_info (GimpSessionManaged * session_managed)
name|gimp_session_managed_get_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|)
block|{
name|GimpSessionManagedInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SESSION_MANAGED
argument_list|(
name|session_managed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_SESSION_MANAGED_GET_INTERFACE
argument_list|(
name|session_managed
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|get_aux_info
condition|)
return|return
name|iface
operator|->
name|get_aux_info
argument_list|(
name|session_managed
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_session_managed_get_ui_manager:  * @session_managed: A #GimpSessionManaged  * @aux_info         A list of #GimpSessionInfoAux  *  * Sets aux data previously returned from  * gimp_session_managed_get_aux_info().  **/
end_comment

begin_function
name|void
DECL|function|gimp_session_managed_set_aux_info (GimpSessionManaged * session_managed,GList * aux_info)
name|gimp_session_managed_set_aux_info
parameter_list|(
name|GimpSessionManaged
modifier|*
name|session_managed
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GimpSessionManagedInterface
modifier|*
name|iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SESSION_MANAGED
argument_list|(
name|session_managed
argument_list|)
argument_list|)
expr_stmt|;
name|iface
operator|=
name|GIMP_SESSION_MANAGED_GET_INTERFACE
argument_list|(
name|session_managed
argument_list|)
expr_stmt|;
if|if
condition|(
name|iface
operator|->
name|set_aux_info
condition|)
name|iface
operator|->
name|set_aux_info
argument_list|(
name|session_managed
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

