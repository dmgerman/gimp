begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BOUNDARY_H__
end_ifndef

begin_define
DECL|macro|__BOUNDARY_H__
define|#
directive|define
name|__BOUNDARY_H__
end_define

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28ec09d20103
block|{
DECL|enumerator|WithinBounds
name|WithinBounds
block|,
DECL|enumerator|IgnoreBounds
name|IgnoreBounds
DECL|typedef|BoundaryType
block|}
name|BoundaryType
typedef|;
end_typedef

begin_struct
DECL|struct|_BoundSeg
struct|struct
name|_BoundSeg
block|{
DECL|member|x1
name|gint
name|x1
decl_stmt|;
DECL|member|y1
name|gint
name|y1
decl_stmt|;
DECL|member|x2
name|gint
name|x2
decl_stmt|;
DECL|member|y2
name|gint
name|y2
decl_stmt|;
DECL|member|open
name|gboolean
name|open
decl_stmt|;
DECL|member|visited
name|gboolean
name|visited
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|BoundSeg
modifier|*
name|find_mask_boundary
parameter_list|(
name|PixelRegion
modifier|*
name|maskPR
parameter_list|,
name|gint
modifier|*
name|num_elems
parameter_list|,
name|BoundaryType
name|type
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|BoundSeg
modifier|*
name|sort_boundary
parameter_list|(
name|BoundSeg
modifier|*
name|segs
parameter_list|,
name|gint
name|num_segs
parameter_list|,
name|gint
modifier|*
name|num_groups
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __BOUNDARY_H__  */
end_comment

end_unit

