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

begin_typedef
DECL|typedef|GimpScanConvert
typedef|typedef
name|struct
name|_GimpScanConvert
name|GimpScanConvert
typedef|;
end_typedef

begin_comment
comment|/* Create a new scan conversion context.  Set "antialias" to 1 for no  * supersampling, or the amount to supersample by otherwise.  */
end_comment

begin_function_decl
name|GimpScanConvert
modifier|*
name|gimp_scan_convert_new
parameter_list|(
name|guint
name|width
parameter_list|,
name|guint
name|height
parameter_list|,
name|gboolean
name|antialias
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
comment|/* set the X- and Y-resolution for the ScanConvert.  * Only gets used for stroking.  * The stroke width has to be given in X-Resolution.  */
end_comment

begin_function_decl
name|void
name|gimp_scan_convert_set_resolution
parameter_list|(
name|GimpScanConvert
modifier|*
name|sc
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
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
comment|/* Return a new Channel according to the polygonal shapes defined with  * the commands above.  *  * You cannot add additional polygons after this command.  */
end_comment

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_scan_convert_to_channel
parameter_list|(
name|GimpScanConvert
modifier|*
name|scan_converter
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* This is a more low level version. Expects a tile manager of depth 1.  *  * You cannot add additional polygons after this command.  */
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

