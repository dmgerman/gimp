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
name|guint
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
comment|/* Add "npoints" from "pointlist" to the polygon currently being  * described by "scan_converter".  */
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
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Scan convert the polygon described by the list of points passed to  * scan_convert_add_points, and return a channel with a bits set if  * they fall within the polygon defined.  The polygon is filled  * according to the even-odd rule.  The polygon is closed by  * joining the final point to the initial point.  */
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SCAN_CONVERT_H__ */
end_comment

end_unit

