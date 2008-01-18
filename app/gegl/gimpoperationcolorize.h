begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationcolorize.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_COLORIZE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_COLORIZE_H__
define|#
directive|define
name|__GIMP_OPERATION_COLORIZE_H__
end_define

begin_include
include|#
directive|include
file|"gegl/gegl-operation-point-filter.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_COLORIZE
define|#
directive|define
name|GIMP_TYPE_OPERATION_COLORIZE
value|(gimp_operation_colorize_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_COLORIZE (obj)
define|#
directive|define
name|GIMP_OPERATION_COLORIZE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_COLORIZE, GimpOperationColorize))
end_define

begin_define
DECL|macro|GIMP_OPERATION_COLORIZE_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_COLORIZE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_COLORIZE, GimpOperationColorizeClass))
end_define

begin_define
DECL|macro|GIMP_OPERATION_COLORIZE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_COLORIZE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_COLORIZE, GimpOperationColorizeClass))
end_define

begin_typedef
DECL|typedef|GimpOperationColorizeClass
typedef|typedef
name|struct
name|_GimpOperationColorizeClass
name|GimpOperationColorizeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationColorize
struct|struct
name|_GimpOperationColorize
block|{
DECL|member|parent_instance
name|GeglOperationPointFilter
name|parent_instance
decl_stmt|;
DECL|member|config
name|GimpColorizeConfig
modifier|*
name|config
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationColorizeClass
struct|struct
name|_GimpOperationColorizeClass
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
name|gimp_operation_colorize_get_type
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
comment|/* __GIMP_OPERATION_COLORIZE_H__ */
end_comment

end_unit

