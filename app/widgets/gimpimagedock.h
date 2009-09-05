begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagedock.h  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_DOCK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_DOCK_H__
define|#
directive|define
name|__GIMP_IMAGE_DOCK_H__
end_define

begin_include
include|#
directive|include
file|"gimpdock.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_DOCK
define|#
directive|define
name|GIMP_TYPE_IMAGE_DOCK
value|(gimp_image_dock_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_DOCK (obj)
define|#
directive|define
name|GIMP_IMAGE_DOCK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_DOCK, GimpImageDock))
end_define

begin_define
DECL|macro|GIMP_IMAGE_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_DOCK, GimpImageDockClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_DOCK (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_DOCK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_DOCK))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_DOCK))
end_define

begin_define
DECL|macro|GIMP_IMAGE_DOCK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_DOCK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_DOCK, GimpImageDockClass))
end_define

begin_typedef
DECL|typedef|GimpImageDockClass
typedef|typedef
name|struct
name|_GimpImageDockClass
name|GimpImageDockClass
typedef|;
end_typedef

begin_comment
comment|/**  * Adds some GimpImage specific hooks and logic to GimpDock.  */
end_comment

begin_struct
DECL|struct|_GimpImageDock
struct|struct
name|_GimpImageDock
block|{
DECL|member|parent_instance
name|GimpDock
name|parent_instance
decl_stmt|;
DECL|member|ui_manager
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
DECL|member|image_flush_handler_id
name|GQuark
name|image_flush_handler_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageDockClass
struct|struct
name|_GimpImageDockClass
block|{
DECL|member|parent_class
name|GimpDockClass
name|parent_class
decl_stmt|;
DECL|member|ui_manager_name
specifier|const
name|gchar
modifier|*
name|ui_manager_name
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_image_dock_get_type
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
comment|/* __GIMP_IMAGE_DOCK_H__ */
end_comment

end_unit

