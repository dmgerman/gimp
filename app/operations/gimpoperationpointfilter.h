begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationpointfilter.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_POINT_FILTER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_POINT_FILTER_H__
define|#
directive|define
name|__GIMP_OPERATION_POINT_FILTER_H__
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

begin_enum
enum|enum
DECL|enum|__anon286dd0010103
block|{
DECL|enumerator|GIMP_OPERATION_POINT_FILTER_PROP_0
name|GIMP_OPERATION_POINT_FILTER_PROP_0
block|,
DECL|enumerator|GIMP_OPERATION_POINT_FILTER_PROP_LINEAR
name|GIMP_OPERATION_POINT_FILTER_PROP_LINEAR
block|,
DECL|enumerator|GIMP_OPERATION_POINT_FILTER_PROP_CONFIG
name|GIMP_OPERATION_POINT_FILTER_PROP_CONFIG
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TYPE_OPERATION_POINT_FILTER
define|#
directive|define
name|GIMP_TYPE_OPERATION_POINT_FILTER
value|(gimp_operation_point_filter_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_POINT_FILTER (obj)
define|#
directive|define
name|GIMP_OPERATION_POINT_FILTER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_POINT_FILTER, GimpOperationPointFilter))
end_define

begin_define
DECL|macro|GIMP_OPERATION_POINT_FILTER_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_POINT_FILTER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_POINT_FILTER, GimpOperationPointFilterClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_POINT_FILTER (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_POINT_FILTER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_POINT_FILTER))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_POINT_FILTER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_POINT_FILTER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_POINT_FILTER))
end_define

begin_define
DECL|macro|GIMP_OPERATION_POINT_FILTER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_POINT_FILTER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_POINT_FILTER, GimpOperationPointFilterClass))
end_define

begin_typedef
DECL|typedef|GimpOperationPointFilterClass
typedef|typedef
name|struct
name|_GimpOperationPointFilterClass
name|GimpOperationPointFilterClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationPointFilter
struct|struct
name|_GimpOperationPointFilter
block|{
DECL|member|parent_instance
name|GeglOperationPointFilter
name|parent_instance
decl_stmt|;
DECL|member|linear
name|gboolean
name|linear
decl_stmt|;
DECL|member|config
name|GObject
modifier|*
name|config
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationPointFilterClass
struct|struct
name|_GimpOperationPointFilterClass
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
name|gimp_operation_point_filter_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_operation_point_filter_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_operation_point_filter_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OPERATION_POINT_FILTER_H__ */
end_comment

end_unit

