begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_SHELL_APPEARANCE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_SHELL_APPEARANCE_H__
define|#
directive|define
name|__GIMP_DISPLAY_SHELL_APPEARANCE_H__
end_define

begin_function_decl
name|void
name|gimp_display_shell_set_padding
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpDisplayPaddingMode
name|mode
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_fullscreen
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|fullscreen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_fullscreen
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_selection
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_selection
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_layer
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_layer
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_snap_to_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_snap_to_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_menubar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_menubar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_rulers
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_rulers
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_scrollbars
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_scrollbars
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_set_show_statusbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_get_show_statusbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DISPLAY_SHELL_APPEARANCE_H__ */
end_comment

end_unit

