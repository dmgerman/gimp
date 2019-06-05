begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationoffset.h  * Copyright (C) 2019 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_OFFSET_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_OFFSET_H__
define|#
directive|define
name|__GIMP_OPERATION_OFFSET_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_OPERATION_OFFSET
define|#
directive|define
name|GIMP_TYPE_OPERATION_OFFSET
value|(gimp_operation_offset_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_OFFSET (obj)
define|#
directive|define
name|GIMP_OPERATION_OFFSET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_OFFSET, GimpOperationOffset))
end_define

begin_define
DECL|macro|GIMP_OPERATION_OFFSET_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_OFFSET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_OFFSET, GimpOperationOffsetClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_OFFSET (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_OFFSET
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_OFFSET))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_OFFSET_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_OFFSET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_OFFSET))
end_define

begin_define
DECL|macro|GIMP_OPERATION_OFFSET_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_OFFSET_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_OFFSET, GimpOperationOffsetClass))
end_define

begin_typedef
DECL|typedef|GimpOperationOffset
typedef|typedef
name|struct
name|_GimpOperationOffset
name|GimpOperationOffset
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationOffsetClass
typedef|typedef
name|struct
name|_GimpOperationOffsetClass
name|GimpOperationOffsetClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationOffset
struct|struct
name|_GimpOperationOffset
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
DECL|member|type
name|GimpOffsetType
name|type
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationOffsetClass
struct|struct
name|_GimpOperationOffsetClass
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
name|gimp_operation_offset_get_type
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
comment|/* __GIMP_OPERATION_OFFSET_H__ */
end_comment

end_unit

