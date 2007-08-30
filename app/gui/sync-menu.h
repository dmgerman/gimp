begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK+ Integration for the Mac OS X Menubar.  *  * Copyright (C) 2007 Pioneer Research Center USA, Inc.  *  * For further information, see:  * http://developer.imendio.com/projects/gtk-macosx/menubar  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SYNC_MENU_H__
end_ifndef

begin_define
DECL|macro|__SYNC_MENU_H__
define|#
directive|define
name|__SYNC_MENU_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_function_decl
name|G_BEGIN_DECLS
name|void
name|sync_menu_takeover_menu
parameter_list|(
name|GtkMenuShell
modifier|*
name|menu_shell
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
comment|/* __SYNC_MENU_H__ */
end_comment

end_unit

