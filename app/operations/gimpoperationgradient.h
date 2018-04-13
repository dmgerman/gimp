begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationgradient.h  * Copyright (C) 2014 Michael Henning<drawoc@darkrefraction.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_GRADIENT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_GRADIENT_H__
define|#
directive|define
name|__GIMP_OPERATION_GRADIENT_H__
end_define

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_GRADIENT
define|#
directive|define
name|GIMP_TYPE_OPERATION_GRADIENT
value|(gimp_operation_gradient_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_GRADIENT (obj)
define|#
directive|define
name|GIMP_OPERATION_GRADIENT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_GRADIENT, GimpOperationGradient))
end_define

begin_define
DECL|macro|GIMP_OPERATION_GRADIENT_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_GRADIENT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_GRADIENT, GimpOperationGradientClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_GRADIENT (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_GRADIENT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_GRADIENT))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_GRADIENT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_GRADIENT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_GRADIENT))
end_define

begin_define
DECL|macro|GIMP_OPERATION_GRADIENT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_GRADIENT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_GRADIENT, GimpOperationGradientClass))
end_define

begin_typedef
DECL|typedef|GimpOperationGradient
typedef|typedef
name|struct
name|_GimpOperationGradient
name|GimpOperationGradient
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationGradientClass
typedef|typedef
name|struct
name|_GimpOperationGradientClass
name|GimpOperationGradientClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationGradient
struct|struct
name|_GimpOperationGradient
block|{
DECL|member|parent_instance
name|GeglOperationFilter
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|gradient
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
DECL|member|start_x
DECL|member|start_y
DECL|member|end_x
DECL|member|end_y
name|gdouble
name|start_x
decl_stmt|,
name|start_y
decl_stmt|,
name|end_x
decl_stmt|,
name|end_y
decl_stmt|;
DECL|member|gradient_type
name|GimpGradientType
name|gradient_type
decl_stmt|;
DECL|member|gradient_repeat
name|GimpRepeatMode
name|gradient_repeat
decl_stmt|;
DECL|member|offset
name|gdouble
name|offset
decl_stmt|;
DECL|member|gradient_reverse
name|gboolean
name|gradient_reverse
decl_stmt|;
DECL|member|gradient_blend_color_space
name|GimpGradientBlendColorSpace
name|gradient_blend_color_space
decl_stmt|;
DECL|member|supersample
name|gboolean
name|supersample
decl_stmt|;
DECL|member|supersample_depth
name|gint
name|supersample_depth
decl_stmt|;
DECL|member|supersample_threshold
name|gdouble
name|supersample_threshold
decl_stmt|;
DECL|member|dither
name|gboolean
name|dither
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationGradientClass
struct|struct
name|_GimpOperationGradientClass
block|{
DECL|member|parent_class
name|GeglOperationFilterClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_gradient_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OPERATION_GRADIENT_H__ */
end_comment

end_unit

