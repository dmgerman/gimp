begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|SCAN_CONVERT_H
end_ifndef

begin_define
DECL|macro|SCAN_CONVERT_H
define|#
directive|define
name|SCAN_CONVERT_H
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon297c40220108
block|{
DECL|member|x
name|gdouble
name|x
decl_stmt|;
DECL|member|y
name|gdouble
name|y
decl_stmt|;
DECL|typedef|ScanConvertPoint
block|}
name|ScanConvertPoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|ScanConverter
typedef|typedef
name|struct
name|ScanConverterPrivate
name|ScanConverter
typedef|;
end_typedef

begin_comment
comment|/* Create a new scan conversion context.  Set "antialias" to 1 for no  * supersampling, or the amount to supersample by otherwise.  */
end_comment

begin_function_decl
name|ScanConverter
modifier|*
name|scan_converter_new
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

begin_comment
comment|/* Add "npoints" from "pointlist" to the polygon currently being  * described by "scan_converter".  */
end_comment

begin_function_decl
name|void
name|scan_converter_add_points
parameter_list|(
name|ScanConverter
modifier|*
name|scan_converter
parameter_list|,
name|guint
name|npoints
parameter_list|,
name|ScanConvertPoint
modifier|*
name|pointlist
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Scan convert the polygon described by the list of points passed to  * scan_convert_add_points, and return a channel with a bits set if  * they fall within the polygon defined.  The polygon is filled  * according to the even-odd rule.  The polygon is closed by  * joining the final point to the initial point. */
end_comment

begin_function_decl
name|Channel
modifier|*
name|scan_converter_to_channel
parameter_list|(
name|ScanConverter
modifier|*
name|scan_converter
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|scan_converter_free
parameter_list|(
name|ScanConverter
modifier|*
name|scan_converter
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* SCAN_CONVERT_H */
end_comment

end_unit

