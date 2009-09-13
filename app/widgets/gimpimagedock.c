begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagedock.c  * Copyright (C) 2001-2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagedock.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpImageDock,gimp_image_dock,GIMP_TYPE_DOCK)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpImageDock
argument_list|,
argument|gimp_image_dock
argument_list|,
argument|GIMP_TYPE_DOCK
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_dock_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_image_dock_class_init
parameter_list|(
name|GimpImageDockClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_init (GimpImageDock * dock)
name|gimp_image_dock_init
parameter_list|(
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
block|{ }
end_function

end_unit

