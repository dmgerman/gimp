begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagedock.h  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_IMAGE_DOCK, GimpImageDock))
end_define

begin_define
DECL|macro|GIMP_IMAGE_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_DOCK, GimpImageDockClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_DOCK (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_DOCK
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_IMAGE_DOCK))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_DOCK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_DOCK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_DOCK))
end_define

begin_typedef
DECL|typedef|GimpImageDockClass
typedef|typedef
name|struct
name|_GimpImageDockClass
name|GimpImageDockClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageDock
struct|struct
name|_GimpImageDock
block|{
DECL|member|parent_instance
name|GimpDock
name|parent_instance
decl_stmt|;
DECL|member|image_container
name|GimpContainer
modifier|*
name|image_container
decl_stmt|;
DECL|member|auto_follow_active
name|gboolean
name|auto_follow_active
decl_stmt|;
DECL|member|option_menu
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
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
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_image_dock_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_dock_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpContainer
modifier|*
name|image_container
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_DOCK_H__ */
end_comment

end_unit

