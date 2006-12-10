begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcontrollerwheel.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTROLLER_WHELL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTROLLER_WHEEL_H__
define|#
directive|define
name|__GIMP_CONTROLLER_WHEEL_H__
end_define

begin_define
DECL|macro|GIMP_ENABLE_CONTROLLER_UNDER_CONSTRUCTION
define|#
directive|define
name|GIMP_ENABLE_CONTROLLER_UNDER_CONSTRUCTION
end_define

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpcontroller.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTROLLER_WHEEL
define|#
directive|define
name|GIMP_TYPE_CONTROLLER_WHEEL
value|(gimp_controller_wheel_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_WHEEL (obj)
define|#
directive|define
name|GIMP_CONTROLLER_WHEEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTROLLER_WHEEL, GimpControllerWheel))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_WHEEL_CLASS (klass)
define|#
directive|define
name|GIMP_CONTROLLER_WHEEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTROLLER_WHEEL, GimpControllerWheelClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_WHEEL (obj)
define|#
directive|define
name|GIMP_IS_CONTROLLER_WHEEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTROLLER_WHEEL))
end_define

begin_define
DECL|macro|GIMP_IS_CONTROLLER_WHEEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTROLLER_WHEEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTROLLER_WHEEL))
end_define

begin_define
DECL|macro|GIMP_CONTROLLER_WHEEL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTROLLER_WHEEL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTROLLER_WHEEL, GimpControllerWheelClass))
end_define

begin_typedef
DECL|typedef|GimpControllerWheelClass
typedef|typedef
name|struct
name|_GimpControllerWheelClass
name|GimpControllerWheelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpControllerWheel
struct|struct
name|_GimpControllerWheel
block|{
DECL|member|parent_instance
name|GimpController
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpControllerWheelClass
struct|struct
name|_GimpControllerWheelClass
block|{
DECL|member|parent_class
name|GimpControllerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_controller_wheel_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_controller_wheel_scroll
parameter_list|(
name|GimpControllerWheel
modifier|*
name|wheel
parameter_list|,
specifier|const
name|GdkEventScroll
modifier|*
name|sevent
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONTROLLER_WHEEL_H__ */
end_comment

end_unit

