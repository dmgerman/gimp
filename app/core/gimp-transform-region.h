begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_REGION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_REGION_H__
define|#
directive|define
name|__GIMP_TRANSFORM_REGION_H__
end_define

begin_function_decl
name|void
name|gimp_transform_region
parameter_list|(
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|TileManager
modifier|*
name|orig_tiles
parameter_list|,
name|gint
name|orig_offset_x
parameter_list|,
name|gint
name|orig_offset_y
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gint
name|dest_x1
parameter_list|,
name|gint
name|dest_y1
parameter_list|,
name|gint
name|dest_x2
parameter_list|,
name|gint
name|dest_y2
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|matrix
parameter_list|,
name|GimpInterpolationType
name|interpolation_type
parameter_list|,
name|gint
name|recursion_level
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TRANSFORM_REGION_H__ */
end_comment

end_unit

