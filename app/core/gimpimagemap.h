begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGE_MAP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGE_MAP_H__
define|#
directive|define
name|__GIMP_IMAGE_MAP_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGE_MAP
define|#
directive|define
name|GIMP_TYPE_IMAGE_MAP
value|(gimp_image_map_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP (obj)
define|#
directive|define
name|GIMP_IMAGE_MAP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGE_MAP, GimpImageMap))
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGE_MAP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGE_MAP, GimpImageMapClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_MAP (obj)
define|#
directive|define
name|GIMP_IS_IMAGE_MAP
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGE_MAP))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGE_MAP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGE_MAP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGE_MAP))
end_define

begin_define
DECL|macro|GIMP_IMAGE_MAP_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGE_MAP_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGE_MAP, GimpImageMapClass))
end_define

begin_typedef
DECL|typedef|GimpImageMapClass
typedef|typedef
name|struct
name|_GimpImageMapClass
name|GimpImageMapClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImageMapClass
struct|struct
name|_GimpImageMapClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|flush
name|void
function_decl|(
modifier|*
name|flush
function_decl|)
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Image Map functions  */
end_comment

begin_comment
comment|/*  Successive image_map_apply functions can be called, but eventually  *  MUST be followed with an image_map_commit or an image_map_abort call  *  The image map is no longer valid after a call to commit or abort.  */
end_comment

begin_decl_stmt
name|GType
name|gimp_image_map_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpImageMap
modifier|*
name|gimp_image_map_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglNode
modifier|*
name|operation
parameter_list|,
name|GimpImageMapApplyFunc
name|apply_func
parameter_list|,
name|gpointer
name|apply_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_map_apply
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_map_commit
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_map_clear
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_image_map_abort
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_image_map_is_busy
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGE_MAP_H__ */
end_comment

end_unit

