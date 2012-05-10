begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationerasemode.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_ERASE_MODE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_ERASE_MODE_H__
define|#
directive|define
name|__GIMP_OPERATION_ERASE_MODE_H__
end_define

begin_include
include|#
directive|include
file|"gimpoperationpointlayermode.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_ERASE_MODE
define|#
directive|define
name|GIMP_TYPE_OPERATION_ERASE_MODE
value|(gimp_operation_erase_mode_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_ERASE_MODE (obj)
define|#
directive|define
name|GIMP_OPERATION_ERASE_MODE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_ERASE_MODE, GimpOperationEraseMode))
end_define

begin_define
DECL|macro|GIMP_OPERATION_ERASE_MODE_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_ERASE_MODE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_ERASE_MODE, GimpOperationEraseModeClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_ERASE_MODE (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_ERASE_MODE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_ERASE_MODE))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_ERASE_MODE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_ERASE_MODE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_ERASE_MODE))
end_define

begin_define
DECL|macro|GIMP_OPERATION_ERASE_MODE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_ERASE_MODE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_ERASE_MODE, GimpOperationEraseModeClass))
end_define

begin_typedef
DECL|typedef|GimpOperationEraseMode
typedef|typedef
name|struct
name|_GimpOperationEraseMode
name|GimpOperationEraseMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationEraseModeClass
typedef|typedef
name|struct
name|_GimpOperationEraseModeClass
name|GimpOperationEraseModeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationEraseMode
struct|struct
name|_GimpOperationEraseMode
block|{
DECL|member|parent_instance
name|GimpOperationPointLayerMode
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationEraseModeClass
struct|struct
name|_GimpOperationEraseModeClass
block|{
DECL|member|parent_class
name|GimpOperationPointLayerModeClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_erase_mode_get_type
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
comment|/* __GIMP_OPERATION_ERASE_MODE_H__ */
end_comment

end_unit

