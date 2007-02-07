begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_SHELL_SCALE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_SHELL_SCALE_H__
define|#
directive|define
name|__GIMP_DISPLAY_SHELL_SCALE_H__
end_define

begin_function_decl
name|void
name|gimp_display_shell_scale_setup
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_scale_revert
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_shell_scale_can_revert
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_set_dot_for_dot
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpZoomType
name|zoom_type
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_to
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpZoomType
name|zoom_type
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_fit_in
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_fit_to
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_by_values
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|resize_window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_shrink_wrap
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_resize
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|resize_window
parameter_list|,
name|gboolean
name|redisplay
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_scale_dialog
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
comment|/*  __GIMP_DISPLAY_SHELL_SCALE_H__  */
end_comment

end_unit

