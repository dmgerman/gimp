begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_MAP_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_MAP_TOOL_H__
define|#
directive|define
name|__GIMP_IMAGE_MAP_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_MAP_TOOL
define|#
directive|define
name|GIMP_TYPE_IMAGE_MAP_TOOL
value|(gimp_image_map_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_TOOL (obj)
define|#
directive|define
name|GIMP_IMAGE_MAP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_MAP_TOOL, GimpImageMapTool))
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_MAP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_MAP_TOOL, GimpImageMapToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_MAP_TOOL (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_MAP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_MAP_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_MAP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_MAP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_MAP_TOOL))
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_MAP_TOOL, GimpImageMapToolClass))
end_define

begin_typedef
DECL|typedef|GimpImageMapTool
typedef|typedef
name|struct
name|_GimpImageMapTool
name|GimpImageMapTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageMapToolClass
typedef|typedef
name|struct
name|_GimpImageMapToolClass
name|GimpImageMapToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageMapTool
struct|struct
name|_GimpImageMapTool
block|{
DECL|member|parent_instance
name|GimpTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImageMapToolClass
struct|struct
name|_GimpImageMapToolClass
block|{
DECL|member|parent_class
name|GimpToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_image_map_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_IMAGE_MAP_TOOL_H__  */
end_comment

end_unit

