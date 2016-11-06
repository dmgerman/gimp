begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationprofiletransform.h  * Copyright (C) 2016 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_PROFILE_TRANSFORM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_PROFILE_TRANSFORM_H__
define|#
directive|define
name|__GIMP_OPERATION_PROFILE_TRANSFORM_H__
end_define

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|<operation/gegl-operation-point-filter.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_PROFILE_TRANSFORM
define|#
directive|define
name|GIMP_TYPE_OPERATION_PROFILE_TRANSFORM
value|(gimp_operation_profile_transform_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_PROFILE_TRANSFORM (obj)
define|#
directive|define
name|GIMP_OPERATION_PROFILE_TRANSFORM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_PROFILE_TRANSFORM, GimpOperationProfileTransform))
end_define

begin_define
DECL|macro|GIMP_OPERATION_PROFILE_TRANSFORM_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_PROFILE_TRANSFORM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_PROFILE_TRANSFORM, GimpOperationProfileTransformClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_PROFILE_TRANSFORM (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_PROFILE_TRANSFORM
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_PROFILE_TRANSFORM))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_PROFILE_TRANSFORM_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_PROFILE_TRANSFORM_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_PROFILE_TRANSFORM))
end_define

begin_define
DECL|macro|GIMP_OPERATION_PROFILE_TRANSFORM_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_PROFILE_TRANSFORM_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_PROFILE_TRANSFORM, GimpOperationProfileTransformClass))
end_define

begin_typedef
DECL|typedef|GimpOperationProfileTransform
typedef|typedef
name|struct
name|_GimpOperationProfileTransform
name|GimpOperationProfileTransform
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationProfileTransformClass
typedef|typedef
name|struct
name|_GimpOperationProfileTransformClass
name|GimpOperationProfileTransformClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationProfileTransform
struct|struct
name|_GimpOperationProfileTransform
block|{
DECL|member|parent_instance
name|GeglOperationPointFilter
name|parent_instance
decl_stmt|;
DECL|member|src_profile
name|GimpColorProfile
modifier|*
name|src_profile
decl_stmt|;
DECL|member|src_format
specifier|const
name|Babl
modifier|*
name|src_format
decl_stmt|;
DECL|member|dest_profile
name|GimpColorProfile
modifier|*
name|dest_profile
decl_stmt|;
DECL|member|dest_format
specifier|const
name|Babl
modifier|*
name|dest_format
decl_stmt|;
DECL|member|rendering_intent
name|GimpColorRenderingIntent
name|rendering_intent
decl_stmt|;
DECL|member|black_point_compensation
name|gboolean
name|black_point_compensation
decl_stmt|;
DECL|member|transform
name|GimpColorTransform
modifier|*
name|transform
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationProfileTransformClass
struct|struct
name|_GimpOperationProfileTransformClass
block|{
DECL|member|parent_class
name|GeglOperationPointFilterClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_profile_transform_get_type
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
comment|/* __GIMP_OPERATION_PROFILE_TRANSFORM_H__ */
end_comment

end_unit

