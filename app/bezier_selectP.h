begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__BEZIER_SELECTP_H__
end_ifndef

begin_define
DECL|macro|__BEZIER_SELECTP_H__
define|#
directive|define
name|__BEZIER_SELECTP_H__
end_define

begin_define
DECL|macro|BEZIER_ANCHOR
define|#
directive|define
name|BEZIER_ANCHOR
value|1
end_define

begin_define
DECL|macro|BEZIER_CONTROL
define|#
directive|define
name|BEZIER_CONTROL
value|2
end_define

begin_typedef
DECL|typedef|BezierPoint
typedef|typedef
name|struct
name|_bezier_point
name|BezierPoint
typedef|;
end_typedef

begin_struct
DECL|struct|_bezier_point
struct|struct
name|_bezier_point
block|{
DECL|member|type
name|int
name|type
decl_stmt|;
comment|/* type of point (anchor or control) */
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/* location of point in image space  */
DECL|member|sx
DECL|member|sy
name|int
name|sx
decl_stmt|,
name|sy
decl_stmt|;
comment|/* location of point in screen space */
DECL|member|next
name|BezierPoint
modifier|*
name|next
decl_stmt|;
comment|/* next point on curve               */
DECL|member|prev
name|BezierPoint
modifier|*
name|prev
decl_stmt|;
comment|/* prev point on curve               */
block|}
struct|;
end_struct

begin_comment
comment|/*  Functions  */
end_comment

begin_function_decl
name|int
name|bezier_select_load
parameter_list|(
name|void
modifier|*
parameter_list|,
name|BezierPoint
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __BEZIER_SELECTP_H__ */
end_comment

end_unit

