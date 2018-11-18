begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2017 SÃ©bastien Fourey& David TchumperlÃ©  * Copyright (C) 2018 Jehan  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LINEART__
end_ifndef

begin_define
DECL|macro|__GIMP_LINEART__
define|#
directive|define
name|__GIMP_LINEART__
end_define

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_lineart_close
parameter_list|(
name|GeglBuffer
modifier|*
name|line_art
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|gfloat
name|stroke_threshold
parameter_list|,
name|gint
name|minimal_lineart_area
parameter_list|,
name|gint
name|normal_estimate_mask_size
parameter_list|,
name|gfloat
name|end_point_rate
parameter_list|,
name|gint
name|spline_max_length
parameter_list|,
name|gfloat
name|spline_max_angle
parameter_list|,
name|gint
name|end_point_connectivity
parameter_list|,
name|gfloat
name|spline_roundness
parameter_list|,
name|gboolean
name|allow_self_intersections
parameter_list|,
name|gint
name|created_regions_significant_area
parameter_list|,
name|gint
name|created_regions_minimum_area
parameter_list|,
name|gboolean
name|small_segments_from_spline_sources
parameter_list|,
name|gint
name|segments_max_length
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LINEART__ */
end_comment

end_unit

