begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DYNAMICS_OUTPUT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DYNAMICS_OUTPUT_H__
define|#
directive|define
name|__GIMP_DYNAMICS_OUTPUT_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DYNAMICS_OUTPUT
define|#
directive|define
name|GIMP_TYPE_DYNAMICS_OUTPUT
value|(gimp_dynamics_output_get_type ())
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_OUTPUT (obj)
define|#
directive|define
name|GIMP_DYNAMICS_OUTPUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DYNAMICS_OUTPUT, GimpDynamicsOutput))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_OUTPUT_CLASS (klass)
define|#
directive|define
name|GIMP_DYNAMICS_OUTPUT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DYNAMICS_OUTPUT, GimpDynamicsOutputClass))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS_OUTPUT (obj)
define|#
directive|define
name|GIMP_IS_DYNAMICS_OUTPUT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DYNAMICS_OUTPUT))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS_OUTPUT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DYNAMICS_OUTPUT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DYNAMICS_OUTPUT))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_OUTPUT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DYNAMICS_OUTPUT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DYNAMICS_OUTPUT, GimpDynamicsOutputClass))
end_define

begin_typedef
DECL|typedef|GimpDynamicsOutputClass
typedef|typedef
name|struct
name|_GimpDynamicsOutputClass
name|GimpDynamicsOutputClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicsOutput
struct|struct
name|_GimpDynamicsOutput
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|use_pressure
name|gboolean
name|use_pressure
decl_stmt|;
DECL|member|use_velocity
name|gboolean
name|use_velocity
decl_stmt|;
DECL|member|use_direction
name|gboolean
name|use_direction
decl_stmt|;
DECL|member|use_tilt
name|gboolean
name|use_tilt
decl_stmt|;
DECL|member|use_random
name|gboolean
name|use_random
decl_stmt|;
DECL|member|use_fade
name|gboolean
name|use_fade
decl_stmt|;
DECL|member|pressure_curve
name|GimpCurve
modifier|*
name|pressure_curve
decl_stmt|;
DECL|member|velocity_curve
name|GimpCurve
modifier|*
name|velocity_curve
decl_stmt|;
DECL|member|direction_curve
name|GimpCurve
modifier|*
name|direction_curve
decl_stmt|;
DECL|member|tilt_curve
name|GimpCurve
modifier|*
name|tilt_curve
decl_stmt|;
DECL|member|random_curve
name|GimpCurve
modifier|*
name|random_curve
decl_stmt|;
DECL|member|fade_curve
name|GimpCurve
modifier|*
name|fade_curve
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDynamicsOutputClass
struct|struct
name|_GimpDynamicsOutputClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dynamics_output_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDynamicsOutput
modifier|*
name|gimp_dynamics_output_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dynamics_output_is_enabled
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_output_get_linear_value
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_output_get_angular_value
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_output_get_aspect_value
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DYNAMICS_OUTPUT_H__  */
end_comment

end_unit

