begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdocked.c  * Copyright (C) 2003  Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28b8ba5d0103
block|{
DECL|enumerator|TITLE_CHANGED
name|TITLE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_docked_iface_base_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|docked_signals
specifier|static
name|guint
name|docked_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_docked_interface_get_type (void)
name|gimp_docked_interface_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|docked_iface_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|docked_iface_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|docked_iface_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDockedInterface
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|gimp_docked_iface_base_init
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|docked_iface_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INTERFACE
argument_list|,
literal|"GimpDockedInterface"
argument_list|,
operator|&
name|docked_iface_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_interface_add_prerequisite
argument_list|(
name|docked_iface_type
argument_list|,
name|GTK_TYPE_WIDGET
argument_list|)
expr_stmt|;
block|}
return|return
name|docked_iface_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_docked_iface_base_init (GimpDockedInterface * docked_iface)
name|gimp_docked_iface_base_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|initialized
condition|)
block|{
name|docked_signals
index|[
name|TITLE_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"title_changed"
argument_list|,
name|GIMP_TYPE_DOCKED
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDockedInterface
argument_list|,
name|title_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_docked_title_changed (GimpDocked * docked)
name|gimp_docked_title_changed
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKED
argument_list|(
name|docked
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|docked
argument_list|,
name|docked_signals
index|[
name|TITLE_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_docked_set_aux_info (GimpDocked * docked,GList * aux_info)
name|gimp_docked_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GimpDockedInterface
modifier|*
name|docked_iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKED
argument_list|(
name|docked
argument_list|)
argument_list|)
expr_stmt|;
name|docked_iface
operator|=
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|docked
argument_list|)
expr_stmt|;
if|if
condition|(
name|docked_iface
operator|->
name|set_aux_info
condition|)
name|docked_iface
operator|->
name|set_aux_info
argument_list|(
name|docked
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_docked_get_aux_info (GimpDocked * docked)
name|gimp_docked_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpDockedInterface
modifier|*
name|docked_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKED
argument_list|(
name|docked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|docked_iface
operator|=
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|docked
argument_list|)
expr_stmt|;
if|if
condition|(
name|docked_iface
operator|->
name|get_aux_info
condition|)
return|return
name|docked_iface
operator|->
name|get_aux_info
argument_list|(
name|docked
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_docked_get_preview (GimpDocked * docked,GimpContext * context,GtkIconSize size)
name|gimp_docked_get_preview
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkIconSize
name|size
parameter_list|)
block|{
name|GimpDockedInterface
modifier|*
name|docked_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKED
argument_list|(
name|docked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|docked_iface
operator|=
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|docked
argument_list|)
expr_stmt|;
if|if
condition|(
name|docked_iface
operator|->
name|get_preview
condition|)
return|return
name|docked_iface
operator|->
name|get_preview
argument_list|(
name|docked
argument_list|,
name|context
argument_list|,
name|size
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_docked_get_menu (GimpDocked * docked,const gchar ** ui_path,gpointer * popup_data)
name|gimp_docked_get_menu
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|,
name|gpointer
modifier|*
name|popup_data
parameter_list|)
block|{
name|GimpDockedInterface
modifier|*
name|docked_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKED
argument_list|(
name|docked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|ui_path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|popup_data
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|docked_iface
operator|=
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|docked
argument_list|)
expr_stmt|;
if|if
condition|(
name|docked_iface
operator|->
name|get_menu
condition|)
return|return
name|docked_iface
operator|->
name|get_menu
argument_list|(
name|docked
argument_list|,
name|ui_path
argument_list|,
name|popup_data
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_docked_get_title (GimpDocked * docked)
name|gimp_docked_get_title
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpDockedInterface
modifier|*
name|docked_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DOCKED
argument_list|(
name|docked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|docked_iface
operator|=
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|docked
argument_list|)
expr_stmt|;
if|if
condition|(
name|docked_iface
operator|->
name|get_title
condition|)
return|return
name|docked_iface
operator|->
name|get_title
argument_list|(
name|docked
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_docked_set_context (GimpDocked * docked,GimpContext * context,GimpContext * prev_context)
name|gimp_docked_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContext
modifier|*
name|prev_context
parameter_list|)
block|{
name|GimpDockedInterface
modifier|*
name|docked_iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DOCKED
argument_list|(
name|docked
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|prev_context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|prev_context
argument_list|)
argument_list|)
expr_stmt|;
name|docked_iface
operator|=
name|GIMP_DOCKED_GET_INTERFACE
argument_list|(
name|docked
argument_list|)
expr_stmt|;
if|if
condition|(
name|docked_iface
operator|->
name|set_context
condition|)
name|docked_iface
operator|->
name|set_context
argument_list|(
name|docked
argument_list|,
name|context
argument_list|,
name|prev_context
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

