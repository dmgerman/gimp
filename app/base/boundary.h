begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
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
DECL|typedef|BoundSeg
typedef|typedef
name|struct
name|_BoundSeg
name|BoundSeg
typedef|;
end_typedef

begin_struct
DECL|struct|_BoundSeg
struct|struct
name|_BoundSeg
block|{
DECL|member|x1
DECL|member|y1
name|int
name|x1
decl_stmt|,
name|y1
decl_stmt|;
DECL|member|x2
DECL|member|y2
name|int
name|x2
decl_stmt|,
name|y2
decl_stmt|;
DECL|member|open
name|int
name|open
decl_stmt|;
DECL|member|visited
name|int
name|visited
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon298fd1660103
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

begin_function_decl
name|BoundSeg
modifier|*
name|find_mask_boundary
parameter_list|(
name|PixelRegion
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|BoundaryType
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|int
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
parameter_list|,
name|int
parameter_list|,
name|int
modifier|*
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

