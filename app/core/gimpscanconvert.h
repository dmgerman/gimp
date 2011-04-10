begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SCAN_CONVERT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SCAN_CONVERT_H__
define|#
directive|define
name|__GIMP_SCAN_CONVERT_H__
end_define

begin_function_decl
name|GimpScanConvert
modifier|*
name|gimp_scan_convert_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_free
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_set_pixel_ratio
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|gdouble
name|ratio_xy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_set_clip_rectangle
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_add_polyline
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|guint
name|n_points
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gboolean
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_add_bezier
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
specifier|const
name|GimpBezierDesc
modifier|*
name|bezier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_stroke
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|gdouble
name|width
parameter_list|,
name|GimpJoinStyle
name|join
parameter_list|,
name|GimpCapStyle
name|cap
parameter_list|,
name|gdouble
name|miter
parameter_list|,
name|gdouble
name|dash_offset
parameter_list|,
name|GArray
modifier|*
name|dash_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_render_full
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|replace
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|guchar
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_render
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gboolean
name|antialias
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_render_value
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|guchar
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_compose
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scan_convert_compose_value
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|TileManager
modifier|*
name|tile_manager
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SCAN_CONVERT_H__ */
end_comment

end_unit

