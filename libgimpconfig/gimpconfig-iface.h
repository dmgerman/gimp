begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_H__
define|#
directive|define
name|__GIMP_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONFIG
define|#
directive|define
name|GIMP_TYPE_CONFIG
value|(gimp_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONFIG (obj)
define|#
directive|define
name|GIMP_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONFIG, GimpConfig))
end_define

begin_define
DECL|macro|GIMP_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONFIG, GimpConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONFIG))
end_define

begin_define
DECL|macro|GIMP_CONFIG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONFIG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONFIG, GimpConfigClass))
end_define

begin_typedef
DECL|typedef|GimpConfig
typedef|typedef
name|struct
name|_GimpConfig
name|GimpConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpConfigClass
typedef|typedef
name|struct
name|_GimpConfigClass
name|GimpConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpConfig
struct|struct
name|_GimpConfig
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|marching_ants_speed
name|guint
name|marching_ants_speed
decl_stmt|;
DECL|member|preview_size
name|GimpPreviewSize
name|preview_size
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpConfigClass
struct|struct
name|_GimpConfigClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_config_serialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_config_deserialize
parameter_list|(
name|GimpConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_H__ */
end_comment

end_unit

