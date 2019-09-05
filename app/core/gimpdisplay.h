begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_H__
define|#
directive|define
name|__GIMP_DISPLAY_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DISPLAY
define|#
directive|define
name|GIMP_TYPE_DISPLAY
value|(gimp_display_get_type ())
end_define

begin_define
DECL|macro|GIMP_DISPLAY (obj)
define|#
directive|define
name|GIMP_DISPLAY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DISPLAY, GimpDisplay))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_CLASS (klass)
define|#
directive|define
name|GIMP_DISPLAY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DISPLAY, GimpDisplayClass))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY (obj)
define|#
directive|define
name|GIMP_IS_DISPLAY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DISPLAY))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DISPLAY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DISPLAY))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DISPLAY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DISPLAY, GimpDisplayClass))
end_define

begin_typedef
DECL|typedef|GimpDisplayClass
typedef|typedef
name|struct
name|_GimpDisplayClass
name|GimpDisplayClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayPrivate
typedef|typedef
name|struct
name|_GimpDisplayPrivate
name|GimpDisplayPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDisplay
struct|struct
name|_GimpDisplay
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|config
name|GimpDisplayConfig
modifier|*
name|config
decl_stmt|;
DECL|member|priv
name|GimpDisplayPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDisplayClass
struct|struct
name|_GimpDisplayClass
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
name|gimp_display_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gint
name|gimp_display_get_id
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplay
modifier|*
name|gimp_display_get_by_id
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Gimp
modifier|*
name|gimp_display_get_gimp
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DISPLAY_H__  */
end_comment

end_unit
