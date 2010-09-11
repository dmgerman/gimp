begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbezierstroke.h  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BEZIER_STROKE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BEZIER_STROKE_H__
define|#
directive|define
name|__GIMP_BEZIER_STROKE_H__
end_define

begin_include
include|#
directive|include
file|"gimpstroke.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BEZIER_STROKE
define|#
directive|define
name|GIMP_TYPE_BEZIER_STROKE
value|(gimp_bezier_stroke_get_type ())
end_define

begin_define
DECL|macro|GIMP_BEZIER_STROKE (obj)
define|#
directive|define
name|GIMP_BEZIER_STROKE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BEZIER_STROKE, GimpBezierStroke))
end_define

begin_define
DECL|macro|GIMP_BEZIER_STROKE_CLASS (klass)
define|#
directive|define
name|GIMP_BEZIER_STROKE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BEZIER_STROKE, GimpBezierStrokeClass))
end_define

begin_define
DECL|macro|GIMP_IS_BEZIER_STROKE (obj)
define|#
directive|define
name|GIMP_IS_BEZIER_STROKE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BEZIER_STROKE))
end_define

begin_define
DECL|macro|GIMP_IS_BEZIER_STROKE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BEZIER_STROKE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BEZIER_STROKE))
end_define

begin_define
DECL|macro|GIMP_BEZIER_STROKE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BEZIER_STROKE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BEZIER_STROKE, GimpBezierStrokeClass))
end_define

begin_typedef
DECL|typedef|GimpBezierStrokeClass
typedef|typedef
name|struct
name|_GimpBezierStrokeClass
name|GimpBezierStrokeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBezierStroke
struct|struct
name|_GimpBezierStroke
block|{
DECL|member|parent_instance
name|GimpStroke
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBezierStrokeClass
struct|struct
name|_GimpBezierStrokeClass
block|{
DECL|member|parent_class
name|GimpStrokeClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_bezier_stroke_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_bezier_stroke_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_bezier_stroke_new_from_coords
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|n_coords
parameter_list|,
name|gboolean
name|closed
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_bezier_stroke_new_moveto
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|start
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_stroke_lineto
parameter_list|(
name|GimpStroke
modifier|*
name|bez_stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_stroke_conicto
parameter_list|(
name|GimpStroke
modifier|*
name|bez_stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|control
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_stroke_cubicto
parameter_list|(
name|GimpStroke
modifier|*
name|bez_stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|control1
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|control2
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_bezier_stroke_arcto
parameter_list|(
name|GimpStroke
modifier|*
name|bez_stroke
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|,
name|gdouble
name|angle_rad
parameter_list|,
name|gboolean
name|large_arc
parameter_list|,
name|gboolean
name|sweep
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStroke
modifier|*
name|gimp_bezier_stroke_new_ellipse
parameter_list|(
specifier|const
name|GimpCoords
modifier|*
name|center
parameter_list|,
name|gdouble
name|radius_x
parameter_list|,
name|gdouble
name|radius_y
parameter_list|,
name|gdouble
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpAnchor
modifier|*
name|gimp_bezier_stroke_extend
parameter_list|(
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpAnchor
modifier|*
name|neighbor
parameter_list|,
name|GimpVectorExtendMode
name|extend_mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BEZIER_STROKE_H__ */
end_comment

end_unit

