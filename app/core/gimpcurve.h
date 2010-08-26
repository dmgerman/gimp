begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CURVE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CURVE_H__
define|#
directive|define
name|__GIMP_CURVE_H__
end_define

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpvector.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CURVE
define|#
directive|define
name|GIMP_TYPE_CURVE
value|(gimp_curve_get_type ())
end_define

begin_define
DECL|macro|GIMP_CURVE (obj)
define|#
directive|define
name|GIMP_CURVE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CURVE, GimpCurve))
end_define

begin_define
DECL|macro|GIMP_CURVE_CLASS (klass)
define|#
directive|define
name|GIMP_CURVE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CURVE, GimpCurveClass))
end_define

begin_define
DECL|macro|GIMP_IS_CURVE (obj)
define|#
directive|define
name|GIMP_IS_CURVE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CURVE))
end_define

begin_define
DECL|macro|GIMP_IS_CURVE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CURVE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CURVE))
end_define

begin_define
DECL|macro|GIMP_CURVE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CURVE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CURVE, GimpCurveClass))
end_define

begin_typedef
DECL|typedef|GimpCurveClass
typedef|typedef
name|struct
name|_GimpCurveClass
name|GimpCurveClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCurve
struct|struct
name|_GimpCurve
block|{
DECL|member|parent_instance
name|GimpData
name|parent_instance
decl_stmt|;
DECL|member|curve_type
name|GimpCurveType
name|curve_type
decl_stmt|;
DECL|member|n_points
name|gint
name|n_points
decl_stmt|;
DECL|member|points
name|GimpVector2
modifier|*
name|points
decl_stmt|;
DECL|member|n_samples
name|gint
name|n_samples
decl_stmt|;
DECL|member|samples
name|gdouble
modifier|*
name|samples
decl_stmt|;
DECL|member|identity
name|gboolean
name|identity
decl_stmt|;
comment|/* whether the curve is an identiy mapping */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCurveClass
struct|struct
name|_GimpCurveClass
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
name|gimp_curve_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpData
modifier|*
name|gimp_curve_new
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
name|gimp_curve_get_standard
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_reset
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gboolean
name|reset_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_set_curve_type
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|GimpCurveType
name|curve_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCurveType
name|gimp_curve_get_curve_type
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_curve_get_n_points
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_curve_get_n_samples
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_curve_get_closest_point
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gdouble
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_set_point
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gint
name|point
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_move_point
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gint
name|point
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_delete_point
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gint
name|point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_get_point
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gint
name|point
parameter_list|,
name|gdouble
modifier|*
name|x
parameter_list|,
name|gdouble
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_set_curve
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_curve_is_identity
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curve_get_uchar
parameter_list|(
name|GimpCurve
modifier|*
name|curve
parameter_list|,
name|gint
name|n_samples
parameter_list|,
name|guchar
modifier|*
name|samples
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CURVE_H__ */
end_comment

end_unit

