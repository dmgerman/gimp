begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectors-warp.h  * Copyright (C) 2005 Bill Skaggs<weskaggs@primate.ucdavis.edu>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTORS_WARP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTORS_WARP_H__
define|#
directive|define
name|__GIMP_VECTORS_WARP_H__
end_define

begin_function_decl
name|void
name|gimp_vectors_warp_point
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpCoords
modifier|*
name|point
parameter_list|,
name|GimpCoords
modifier|*
name|point_warped
parameter_list|,
name|gdouble
name|y_offset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_vectors_warp_vectors
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpVectors
modifier|*
name|vectors_in
parameter_list|,
name|gdouble
name|yoffset
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_VECTORS_WARP_H__ */
end_comment

end_unit

