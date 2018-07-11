begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationborder.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_BORDER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_BORDER_H__
define|#
directive|define
name|__GIMP_OPERATION_BORDER_H__
end_define

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_BORDER
define|#
directive|define
name|GIMP_TYPE_OPERATION_BORDER
value|(gimp_operation_border_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_BORDER (obj)
define|#
directive|define
name|GIMP_OPERATION_BORDER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_BORDER, GimpOperationBorder))
end_define

begin_define
DECL|macro|GIMP_OPERATION_BORDER_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_BORDER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_BORDER, GimpOperationBorderClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_BORDER (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_BORDER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_BORDER))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_BORDER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_BORDER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_BORDER))
end_define

begin_define
DECL|macro|GIMP_OPERATION_BORDER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_BORDER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_BORDER, GimpOperationBorderClass))
end_define

begin_typedef
DECL|typedef|GimpOperationBorder
typedef|typedef
name|struct
name|_GimpOperationBorder
name|GimpOperationBorder
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationBorderClass
typedef|typedef
name|struct
name|_GimpOperationBorderClass
name|GimpOperationBorderClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationBorder
struct|struct
name|_GimpOperationBorder
block|{
DECL|member|parent_instance
name|GeglOperationFilter
name|parent_instance
decl_stmt|;
DECL|member|radius_x
name|gint
name|radius_x
decl_stmt|;
DECL|member|radius_y
name|gint
name|radius_y
decl_stmt|;
DECL|member|feather
name|gboolean
name|feather
decl_stmt|;
DECL|member|edge_lock
name|gboolean
name|edge_lock
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationBorderClass
struct|struct
name|_GimpOperationBorderClass
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
name|gimp_operation_border_get_type
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
comment|/* __GIMP_OPERATION_BORDER_H__ */
end_comment

end_unit

