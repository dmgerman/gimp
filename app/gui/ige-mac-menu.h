begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK+ Integration for the Mac OS X Menubar.  *  * Copyright (C) 2007 Pioneer Research Center USA, Inc.  * Copyright (C) 2007 Imendio AB  *  * For further information, see:  * http://developer.imendio.com/projects/gtk-macosx/menubar  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; version 2.1  * of the License.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__IGE_MAC_MENU_H__
end_ifndef

begin_define
DECL|macro|__IGE_MAC_MENU_H__
define|#
directive|define
name|__IGE_MAC_MENU_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|IgeMacMenuGroup
typedef|typedef
name|struct
name|_IgeMacMenuGroup
name|IgeMacMenuGroup
typedef|;
end_typedef

begin_function_decl
name|void
name|ige_mac_menu_set_menu_bar
parameter_list|(
name|GtkMenuShell
modifier|*
name|menu_shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ige_mac_menu_set_quit_menu_item
parameter_list|(
name|GtkMenuItem
modifier|*
name|menu_item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|IgeMacMenuGroup
modifier|*
name|ige_mac_menu_add_app_menu_group
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ige_mac_menu_add_app_menu_item
parameter_list|(
name|IgeMacMenuGroup
modifier|*
name|group
parameter_list|,
name|GtkMenuItem
modifier|*
name|menu_item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __IGE_MAC_MENU_H__ */
end_comment

end_unit

