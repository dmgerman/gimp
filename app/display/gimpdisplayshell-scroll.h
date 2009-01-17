begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_SHELL_SCROLL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_SHELL_SCROLL_H__
define|#
directive|define
name|__GIMP_DISPLAY_SHELL_SCROLL_H__
end_define

begin_function_decl
name|void
name|gimp_display_shell_scroll_center_image_coordinate
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|image_x
parameter_list|,
name|gdouble
name|image_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_set_offset
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_clamp_offsets
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_clamp_and_update
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_unoverscrollify
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|in_offset_x
parameter_list|,
name|gint
name|in_offset_y
parameter_list|,
name|gint
modifier|*
name|out_offset_x
parameter_list|,
name|gint
modifier|*
name|out_offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_center_image
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|horizontally
parameter_list|,
name|gboolean
name|vertically
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_center_image_on_next_size_allocate
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|horizontally
parameter_list|,
name|gboolean
name|vertically
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_get_scaled_viewport
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_get_viewport
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|,
name|gdouble
modifier|*
name|w
parameter_list|,
name|gdouble
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_get_disp_offset
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
modifier|*
name|disp_xoffset
parameter_list|,
name|gint
modifier|*
name|disp_yoffset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_get_render_start_offset
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
modifier|*
name|offset_x
parameter_list|,
name|gint
modifier|*
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_setup_hscrollbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scroll_setup_vscrollbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DISPLAY_SHELL_SCROLL_H__  */
end_comment

end_unit

