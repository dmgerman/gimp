begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DYNAMICS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DYNAMICS_H__
define|#
directive|define
name|__GIMP_DYNAMICS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"gimpcurve.h"
end_include

begin_typedef
DECL|typedef|GimpDynamicsOutput
typedef|typedef
name|struct
name|_GimpDynamicsOutput
name|GimpDynamicsOutput
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicsOutput
struct|struct
name|_GimpDynamicsOutput
block|{
DECL|member|pressure
name|gboolean
name|pressure
decl_stmt|;
DECL|member|velocity
name|gboolean
name|velocity
decl_stmt|;
DECL|member|direction
name|gboolean
name|direction
decl_stmt|;
DECL|member|tilt
name|gboolean
name|tilt
decl_stmt|;
DECL|member|random
name|gboolean
name|random
decl_stmt|;
DECL|member|fade
name|gboolean
name|fade
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

begin_define
DECL|macro|GIMP_TYPE_DYNAMICS
define|#
directive|define
name|GIMP_TYPE_DYNAMICS
value|(gimp_dynamics_get_type ())
end_define

begin_define
DECL|macro|GIMP_DYNAMICS (obj)
define|#
directive|define
name|GIMP_DYNAMICS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DYNAMICS, GimpDynamics))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_CLASS (klass)
define|#
directive|define
name|GIMP_DYNAMICS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DYNAMICS, GimpDynamicsClass))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS (obj)
define|#
directive|define
name|GIMP_IS_DYNAMICS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DYNAMICS))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DYNAMICS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DYNAMICS))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DYNAMICS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DYNAMICS, GimpDynamicsClass))
end_define

begin_typedef
DECL|typedef|GimpDynamics
typedef|typedef
name|struct
name|_GimpDynamics
name|GimpDynamics
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamics
struct|struct
name|_GimpDynamics
block|{
DECL|member|parent_instance
name|GimpData
name|parent_instance
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|opacity_dynamics
name|GimpDynamicsOutput
modifier|*
name|opacity_dynamics
decl_stmt|;
DECL|member|hardness_dynamics
name|GimpDynamicsOutput
modifier|*
name|hardness_dynamics
decl_stmt|;
DECL|member|rate_dynamics
name|GimpDynamicsOutput
modifier|*
name|rate_dynamics
decl_stmt|;
DECL|member|size_dynamics
name|GimpDynamicsOutput
modifier|*
name|size_dynamics
decl_stmt|;
DECL|member|aspect_ratio_dynamics
name|GimpDynamicsOutput
modifier|*
name|aspect_ratio_dynamics
decl_stmt|;
DECL|member|color_dynamics
name|GimpDynamicsOutput
modifier|*
name|color_dynamics
decl_stmt|;
DECL|member|angle_dynamics
name|GimpDynamicsOutput
modifier|*
name|angle_dynamics
decl_stmt|;
DECL|member|jitter_dynamics
name|GimpDynamicsOutput
modifier|*
name|jitter_dynamics
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpDynamicsClass
typedef|typedef
name|struct
name|_GimpDynamicsClass
name|GimpDynamicsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicsClass
struct|struct
name|_GimpDynamicsClass
block|{
DECL|member|parent_instance
name|GimpDataClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dynamics_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpData
modifier|*
name|gimp_dynamics_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_dynamics_get_standard
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_get_linear_output_val
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
name|GimpCoords
name|coords
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_get_angular_output_val
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
name|GimpCoords
name|coords
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_get_aspect_output_val
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
name|GimpCoords
name|coords
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_get_scale_output_val
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|,
name|GimpCoords
name|coords
parameter_list|,
name|gdouble
name|fade_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dynamics_output_get_enabled
parameter_list|(
name|GimpDynamicsOutput
modifier|*
name|output
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dynamics_input_fade_enabled
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DYNAMICS_OPTIONS_H__  */
end_comment

end_unit

