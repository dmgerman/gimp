begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GRADIENT_HEADER_H__
end_ifndef

begin_define
DECL|macro|__GRADIENT_HEADER_H__
define|#
directive|define
name|__GRADIENT_HEADER_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_comment
comment|/***** Types *****/
end_comment

begin_comment
comment|/* Gradient segment type */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ecd32f0103
block|{
DECL|enumerator|GRAD_LINEAR
name|GRAD_LINEAR
init|=
literal|0
block|,
DECL|enumerator|GRAD_CURVED
name|GRAD_CURVED
block|,
DECL|enumerator|GRAD_SINE
name|GRAD_SINE
block|,
DECL|enumerator|GRAD_SPHERE_INCREASING
name|GRAD_SPHERE_INCREASING
block|,
DECL|enumerator|GRAD_SPHERE_DECREASING
name|GRAD_SPHERE_DECREASING
DECL|typedef|grad_type_t
block|}
name|grad_type_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27ecd32f0203
block|{
DECL|enumerator|GRAD_RGB
name|GRAD_RGB
init|=
literal|0
block|,
comment|/* normal RGB */
DECL|enumerator|GRAD_HSV_CCW
name|GRAD_HSV_CCW
block|,
comment|/* counterclockwise hue */
DECL|enumerator|GRAD_HSV_CW
name|GRAD_HSV_CW
comment|/* clockwise hue */
DECL|typedef|grad_color_t
block|}
name|grad_color_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|grad_segment_t
typedef|typedef
name|struct
name|_grad_segment_t
name|grad_segment_t
typedef|;
end_typedef

begin_struct
DECL|struct|_gradient_t
struct|struct
name|_gradient_t
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|segments
name|grad_segment_t
modifier|*
name|segments
decl_stmt|;
DECL|member|last_visited
name|grad_segment_t
modifier|*
name|last_visited
decl_stmt|;
DECL|member|dirty
name|gboolean
name|dirty
decl_stmt|;
DECL|member|pixmap
name|GdkPixmap
modifier|*
name|pixmap
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_grad_segment_t
struct|struct
name|_grad_segment_t
block|{
DECL|member|left
DECL|member|middle
DECL|member|right
name|double
name|left
decl_stmt|,
name|middle
decl_stmt|,
name|right
decl_stmt|;
comment|/* Left pos, midpoint, right pos */
DECL|member|r0
DECL|member|g0
DECL|member|b0
DECL|member|a0
name|double
name|r0
decl_stmt|,
name|g0
decl_stmt|,
name|b0
decl_stmt|,
name|a0
decl_stmt|;
comment|/* Left color */
DECL|member|r1
DECL|member|g1
DECL|member|b1
DECL|member|a1
name|double
name|r1
decl_stmt|,
name|g1
decl_stmt|,
name|b1
decl_stmt|,
name|a1
decl_stmt|;
comment|/* Right color */
DECL|member|type
name|grad_type_t
name|type
decl_stmt|;
comment|/* Segment's blending function */
DECL|member|color
name|grad_color_t
name|color
decl_stmt|;
comment|/* Segment's coloring type */
DECL|member|prev
DECL|member|next
name|struct
name|_grad_segment_t
modifier|*
name|prev
decl_stmt|,
modifier|*
name|next
decl_stmt|;
comment|/* For linked list of segments */
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GRADIENT_HEADER_H__  */
end_comment

end_unit

