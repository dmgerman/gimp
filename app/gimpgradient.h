begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GRADIENT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GRADIENT_H__
define|#
directive|define
name|__GIMP_GRADIENT_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28b6276f0103
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
DECL|typedef|GimpGradientSegmentType
block|}
name|GimpGradientSegmentType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28b6276f0203
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
DECL|typedef|GimpGradientSegmentColor
block|}
name|GimpGradientSegmentColor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGradientSegment
typedef|typedef
name|struct
name|_GimpGradientSegment
name|GimpGradientSegment
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGradientSegment
struct|struct
name|_GimpGradientSegment
block|{
DECL|member|left
DECL|member|middle
DECL|member|right
name|gdouble
name|left
decl_stmt|,
name|middle
decl_stmt|,
name|right
decl_stmt|;
DECL|member|left_color
name|GimpRGB
name|left_color
decl_stmt|;
DECL|member|right_color
name|GimpRGB
name|right_color
decl_stmt|;
DECL|member|type
name|GimpGradientSegmentType
name|type
decl_stmt|;
comment|/*  Segment's blending function  */
DECL|member|color
name|GimpGradientSegmentColor
name|color
decl_stmt|;
comment|/*  Segment's coloring type      */
DECL|member|prev
name|GimpGradientSegment
modifier|*
name|prev
decl_stmt|;
DECL|member|next
name|GimpGradientSegment
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_GRADIENT
define|#
directive|define
name|GIMP_TYPE_GRADIENT
value|(gimp_gradient_get_type ())
end_define

begin_define
DECL|macro|GIMP_GRADIENT (obj)
define|#
directive|define
name|GIMP_GRADIENT
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_GRADIENT, GimpGradient))
end_define

begin_define
DECL|macro|GIMP_GRADIENT_CLASS (klass)
define|#
directive|define
name|GIMP_GRADIENT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GRADIENT, GimpGradientClass))
end_define

begin_define
DECL|macro|GIMP_IS_GRADIENT (obj)
define|#
directive|define
name|GIMP_IS_GRADIENT
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_GRADIENT))
end_define

begin_define
DECL|macro|GIMP_IS_GRADIENT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GRADIENT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GRADIENT))
end_define

begin_typedef
DECL|typedef|GimpGradientClass
typedef|typedef
name|struct
name|_GimpGradientClass
name|GimpGradientClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGradient
struct|struct
name|_GimpGradient
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|dirty
name|gboolean
name|dirty
decl_stmt|;
DECL|member|segments
name|GimpGradientSegment
modifier|*
name|segments
decl_stmt|;
comment|/* EEK */
DECL|member|last_visited
name|GimpGradientSegment
modifier|*
name|last_visited
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
DECL|struct|_GimpGradientClass
struct|struct
name|_GimpGradientClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_gradient_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGradient
modifier|*
name|gimp_gradient_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGradient
modifier|*
name|gimp_gradient_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_save
parameter_list|(
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_get_color_at
parameter_list|(
name|GimpGradient
modifier|*
name|gradient
parameter_list|,
name|gdouble
name|pos
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  gradient segment functions  */
end_comment

begin_function_decl
name|GimpGradientSegment
modifier|*
name|gimp_gradient_segment_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGradientSegment
modifier|*
name|gimp_gradient_get_segment_at
parameter_list|(
name|GimpGradient
modifier|*
name|grad
parameter_list|,
name|gdouble
name|pos
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGradientSegment
modifier|*
name|gimp_gradient_segment_get_last
parameter_list|(
name|GimpGradientSegment
modifier|*
name|seg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_segment_free
parameter_list|(
name|GimpGradientSegment
modifier|*
name|seg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_segments_free
parameter_list|(
name|GimpGradientSegment
modifier|*
name|seg
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GRADIENT_H__ */
end_comment

end_unit

