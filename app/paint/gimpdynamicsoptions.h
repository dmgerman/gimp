begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DYNAMICS_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DYNAMICS_OPTIONS_H__
define|#
directive|define
name|__GIMP_DYNAMICS_OPTIONS_H__
end_define

begin_comment
comment|//#include "core/gimptooloptions.h"
end_comment

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdata.h"
end_include

begin_typedef
DECL|typedef|GimpDynamicOutputOptions
typedef|typedef
name|struct
name|_GimpDynamicOutputOptions
name|GimpDynamicOutputOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicOutputOptions
struct|struct
name|_GimpDynamicOutputOptions
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
DECL|member|fade_length
name|gdouble
name|fade_length
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
DECL|macro|GIMP_PAINT_PRESSURE_SCALE
define|#
directive|define
name|GIMP_PAINT_PRESSURE_SCALE
value|1.5
end_define

begin_define
DECL|macro|GIMP_PAINT_VELOCITY_SCALE
define|#
directive|define
name|GIMP_PAINT_VELOCITY_SCALE
value|1.0
end_define

begin_define
DECL|macro|GIMP_TYPE_DYNAMICS_OPTIONS
define|#
directive|define
name|GIMP_TYPE_DYNAMICS_OPTIONS
value|(gimp_dynamics_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_OPTIONS (obj)
define|#
directive|define
name|GIMP_DYNAMICS_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DYNAMICS_OPTIONS, GimpDynamicsOptions))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_DYNAMICS_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DYNAMICS_OPTIONS, GimpDynamicsOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_DYNAMICS_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DYNAMICS_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_DYNAMICS_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DYNAMICS_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DYNAMICS_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_DYNAMICS_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DYNAMICS_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DYNAMICS_OPTIONS, GimpDynamicsOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpDynamicsOptionsClass
typedef|typedef
name|struct
name|_GimpDynamicsOptionsClass
name|GimpDynamicsOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDynamicsOptions
struct|struct
name|_GimpDynamicsOptions
block|{
DECL|member|parent_instance
name|GimpDataClass
name|parent_instance
decl_stmt|;
DECL|member|opacity_dynamics
name|GimpDynamicOutputOptions
modifier|*
name|opacity_dynamics
decl_stmt|;
DECL|member|hardness_dynamics
name|GimpDynamicOutputOptions
modifier|*
name|hardness_dynamics
decl_stmt|;
DECL|member|rate_dynamics
name|GimpDynamicOutputOptions
modifier|*
name|rate_dynamics
decl_stmt|;
DECL|member|size_dynamics
name|GimpDynamicOutputOptions
modifier|*
name|size_dynamics
decl_stmt|;
DECL|member|aspect_ratio_dynamics
name|GimpDynamicOutputOptions
modifier|*
name|aspect_ratio_dynamics
decl_stmt|;
DECL|member|color_dynamics
name|GimpDynamicOutputOptions
modifier|*
name|color_dynamics
decl_stmt|;
DECL|member|angle_dynamics
name|GimpDynamicOutputOptions
modifier|*
name|angle_dynamics
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDynamicsOptionsClass
struct|struct
name|_GimpDynamicsOptionsClass
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
name|gimp_dynamics_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpData
modifier|*
name|gimp_dynamics_options_new
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DYNAMICS_OPTIONS_H__  */
end_comment

end_unit

