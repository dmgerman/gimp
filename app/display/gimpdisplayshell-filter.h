begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1999 Manish Singh  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_SHELL_FILTER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_SHELL_FILTER_H__
define|#
directive|define
name|__GIMP_DISPLAY_SHELL_FILTER_H__
end_define

begin_typedef
DECL|typedef|ColorDisplayNode
typedef|typedef
name|struct
name|_ColorDisplayNode
name|ColorDisplayNode
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorDisplayNode
struct|struct
name|_ColorDisplayNode
block|{
DECL|member|color_display
name|GimpColorDisplay
modifier|*
name|color_display
decl_stmt|;
DECL|member|cd_name
name|gchar
modifier|*
name|cd_name
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|ColorDisplayNode
modifier|*
name|gimp_display_shell_filter_attach
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ColorDisplayNode
modifier|*
name|gimp_display_shell_filter_attach_clone
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_filter_detach
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_filter_detach_destroy
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_filter_detach_all
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_filter_reorder_up
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_filter_reorder_down
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_filter_configure
parameter_list|(
name|ColorDisplayNode
modifier|*
name|node
parameter_list|,
name|GFunc
name|ok_func
parameter_list|,
name|gpointer
name|ok_data
parameter_list|,
name|GFunc
name|cancel_func
parameter_list|,
name|gpointer
name|cancel_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_filter_configure_cancel
parameter_list|(
name|ColorDisplayNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DISPLAY_SHELL_FILTER_H__ */
end_comment

end_unit

