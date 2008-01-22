begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationthreshold.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_THRESHOLD_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_THRESHOLD_H__
define|#
directive|define
name|__GIMP_OPERATION_THRESHOLD_H__
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
DECL|macro|GIMP_TYPE_OPERATION_THRESHOLD
define|#
directive|define
name|GIMP_TYPE_OPERATION_THRESHOLD
value|(gimp_operation_threshold_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_THRESHOLD (obj)
define|#
directive|define
name|GIMP_OPERATION_THRESHOLD
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_THRESHOLD, GimpOperationThreshold))
end_define

begin_define
DECL|macro|GIMP_OPERATION_THRESHOLD_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_THRESHOLD_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_THRESHOLD, GimpOperationThresholdClass))
end_define

begin_define
DECL|macro|GIMP_OPERATION_THRESHOLD_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_THRESHOLD_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_THRESHOLD, GimpOperationThresholdClass))
end_define

begin_typedef
DECL|typedef|GimpOperationThresholdClass
typedef|typedef
name|struct
name|_GimpOperationThresholdClass
name|GimpOperationThresholdClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationThreshold
struct|struct
name|_GimpOperationThreshold
block|{
DECL|member|parent_instance
name|GeglOperationPointFilter
name|parent_instance
decl_stmt|;
DECL|member|low
name|gdouble
name|low
decl_stmt|;
DECL|member|high
name|gdouble
name|high
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationThresholdClass
struct|struct
name|_GimpOperationThresholdClass
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
name|gimp_operation_threshold_get_type
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
comment|/* __GIMP_OPERATION_THRESHOLD_H__ */
end_comment

end_unit

