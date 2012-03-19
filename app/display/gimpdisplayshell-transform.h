begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_SHELL_TRANSFORM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_SHELL_TRANSFORM_H__
define|#
directive|define
name|__GIMP_DISPLAY_SHELL_TRANSFORM_H__
end_define

begin_function_decl
name|void
name|gimp_display_shell_transform_coords
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|image_coords
parameter_list|,
name|GimpCoords
modifier|*
name|display_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_untransform_coords
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|display_coords
parameter_list|,
name|GimpCoords
modifier|*
name|image_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_transform_xy
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_untransform_xy
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
modifier|*
name|nx
parameter_list|,
name|gint
modifier|*
name|ny
parameter_list|,
name|gboolean
name|round
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_transform_xy_f
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_untransform_xy_f
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gdouble
modifier|*
name|nx
parameter_list|,
name|gdouble
modifier|*
name|ny
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_transform_segments
parameter_list|(
specifier|const
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpBoundSeg
modifier|*
name|src_segs
parameter_list|,
name|GimpSegment
modifier|*
name|dest_segs
parameter_list|,
name|gint
name|n_segs
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_shell_untransform_viewport
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
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DISPLAY_SHELL_TRANSFORM_H__ */
end_comment

end_unit

