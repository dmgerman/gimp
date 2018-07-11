begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationpassthrough.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *               2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_PASS_THROUGH_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_PASS_THROUGH_H__
define|#
directive|define
name|__GIMP_OPERATION_PASS_THROUGH_H__
end_define

begin_include
include|#
directive|include
file|"gimpoperationreplace.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_PASS_THROUGH
define|#
directive|define
name|GIMP_TYPE_OPERATION_PASS_THROUGH
value|(gimp_operation_pass_through_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_PASS_THROUGH (obj)
define|#
directive|define
name|GIMP_OPERATION_PASS_THROUGH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_PASS_THROUGH, GimpOperationPassThrough))
end_define

begin_define
DECL|macro|GIMP_OPERATION_PASS_THROUGH_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_PASS_THROUGH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_PASS_THROUGH, GimpOperationPassThroughClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_PASS_THROUGH (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_PASS_THROUGH
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_PASS_THROUGH))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_PASS_THROUGH_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_PASS_THROUGH_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_PASS_THROUGH))
end_define

begin_define
DECL|macro|GIMP_OPERATION_PASS_THROUGH_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_PASS_THROUGH_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_PASS_THROUGH, GimpOperationPassThroughClass))
end_define

begin_typedef
DECL|typedef|GimpOperationPassThrough
typedef|typedef
name|struct
name|_GimpOperationPassThrough
name|GimpOperationPassThrough
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationPassThroughClass
typedef|typedef
name|struct
name|_GimpOperationPassThroughClass
name|GimpOperationPassThroughClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationPassThrough
struct|struct
name|_GimpOperationPassThrough
block|{
DECL|member|parent_instance
name|GimpOperationReplace
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationPassThroughClass
struct|struct
name|_GimpOperationPassThroughClass
block|{
DECL|member|parent_class
name|GimpOperationReplaceClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_pass_through_get_type
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
comment|/* __GIMP_OPERATION_PASS_THROUGH_H__ */
end_comment

end_unit

