begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* Create a new scan conversion context.  */
end_comment

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
name|scan_converter
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* set the Pixel-Ratio (width / height) for the pixels.  */
end_comment

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

begin_comment
comment|/* Add "npoints" from "pointlist" to the polygon currently being  * described by "scan_converter". DEPRECATED.  */
end_comment

begin_function_decl
name|void
name|gimp_scan_convert_add_points
parameter_list|(
name|GimpScanConvert
modifier|*
name|scan_converter
parameter_list|,
name|guint
name|n_points
parameter_list|,
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gboolean
name|new_polygon
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Add a polygon with "npoints" "points" that may be open or closed.  * It is not recommended to mix gimp_scan_convert_add_polyline with  * gimp_scan_convert_add_points.  *  * Please note that you should use gimp_scan_convert_stroke() if you  * specify open polygons.  */
end_comment

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
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|gboolean
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Stroke the content of a GimpScanConvert. The next  * gimp_scan_convert_to_channel will result in the outline of the polygon  * defined with the commands above.  *  * You cannot add additional polygons after this command.  *  * Note that if you have nonstandard resolution, "width" gives the  * width (in pixels) for a vertical stroke, i.e. use the X-resolution  * to calculate the width of a stroke when operating with real world  * units.  */
end_comment

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

begin_comment
comment|/* These are more low level version. Expects a tile manager of depth 1.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function_decl
name|void
name|gimp_scan_convert_render
parameter_list|(
name|GimpScanConvert
modifier|*
name|scan_converter
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

begin_comment
comment|/* This is a variant of gimp_scan_convert_render() that composes the  * (unaliased) scan conversion with the existing drawable content.  */
end_comment

begin_function_decl
name|void
name|gimp_scan_convert_compose
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|GimpChannelOps
name|op
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SCAN_CONVERT_H__ */
end_comment

end_unit

