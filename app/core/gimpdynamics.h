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
file|"gimpdata.h"
end_include

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
DECL|typedef|GimpDynamicsClass
typedef|typedef
name|struct
name|_GimpDynamicsClass
name|GimpDynamicsClass
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
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDynamicsClass
struct|struct
name|_GimpDynamicsClass
block|{
DECL|member|parent_class
name|GimpDataClass
name|parent_class
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
name|GimpContext
modifier|*
name|context
parameter_list|,
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
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDynamicsOutput
modifier|*
name|gimp_dynamics_get_output
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_dynamics_get_linear_value
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
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
name|gimp_dynamics_get_angular_value
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
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
name|gimp_dynamics_get_aspect_value
parameter_list|(
name|GimpDynamics
modifier|*
name|dynamics
parameter_list|,
name|GimpDynamicsOutputType
name|type
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
comment|/*  __GIMP_DYNAMICS_H__  */
end_comment

end_unit

